#include "stdafx.h"
#include "CCameraManager.h"

#include "CGame.h"

CCameraManager::CCameraManager( Context * pcContext ) : Object( pcContext )
{
	fCameraDistance			= 100.0f;
	fCameraPitch			= 0.0f;
	fCameraYaw				= 0.0f;
	fMouseYaw				= 0.0f;
	fDeltaMouseMoveWheel	= 0.0f;

	eType					= CAMERATYPE_Undefined;
	pTargetNode				= NULL;

	pCameraNode				= NULL;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::SetCameraPosition( Vector3 cPosition, Quaternion cRotation )
{
	GetCameraNode()->SetPosition( cPosition );
	GetCameraNode()->SetRotation( cRotation );

	UpdateCameraBase();
}

void CCameraManager::UpdateCameraBase()
{
	if( eType == CAMERATYPE_Orbit && pTargetNode )
	{
		auto * pHeadNode = pTargetNode->GetChild( "Bip01 Head", true );

		if( pHeadNode )
			cLookAtBase = pHeadNode->GetPosition().UP + Vector3( 0.0f, 0.8f, 0.0f );
	}
}

Node * CCameraManager::GetCameraNode()
{
	if( !pCameraNode )
	{
		Node * pFindCameraNode = ACTIVESCREEN->GetScene()->GetChild( "Camera", true );
		if( pFindCameraNode )
			pCameraNode = pFindCameraNode;
		else
		{
			pCameraNode = ACTIVESCREEN->GetScene()->CreateChild( "Camera", LOCAL );
			auto * pCamera = pCameraNode->CreateComponent<Camera>();
		}
	}

	return pCameraNode;
}

Node * CCameraManager::GetNodeRaycast()
{
	if( ACTIVESCREEN->GetScene() )
	{
		IntVector2 cMousePosition = INPUT->GetMousePosition();

		float fX = (float)cMousePosition.x_ / GRAPHICS->GetWidth();
		float fY = (float)cMousePosition.y_ / GRAPHICS->GetHeight();

		Ray cCameraRay = CAMERA->GetScreenRay( fX, fY );
		PODVector<PhysicsRaycastResult> sResult;
		PhysicsWorld * pPhysicsWorld = ACTIVESCREEN->GetScene()->GetComponent<PhysicsWorld>();

		if( pPhysicsWorld )
		{
			pPhysicsWorld->Raycast( sResult, cCameraRay, SELECTUNIT_MAX_DISTANCE );

			for( const auto &pResult : sResult )
			{
				if( pResult.body_ )
				{
					Node * pFoundNode = pResult.body_->GetNode();

					//Encontrou algum nodo?
					if( pFoundNode )
						//O nodo é selecionavel?
						if( pFoundNode->HasTag( "Selectable" ) )
						{
							auto * pParentNode = pFoundNode->GetParent();

							if( pParentNode )
								pFoundNode = pParentNode;

							return pFoundNode;
						}
				}
			}
		}
	}

	return NULL;
}

void CCameraManager::HandlePostUpdate( StringHash cEventType, VariantMap & vEventData )
{
	float fTimeStep = vEventData[Update::P_TIMESTEP].GetFloat();

	OnMoveCamera( fTimeStep );

	if( eType == CAMERATYPE_Orbit && pTargetNode )
	{
		GetCameraNode()->SetRotation( Quaternion( fCameraPitch, fCameraYaw, 0.0f ) );
		GetCameraNode()->SetPosition( pTargetNode->GetPosition() + cLookAtBase + GetCameraNode()->GetRotation() * Vector3::BACK * fCameraDistance );
	}
}

void CCameraManager::OnMoveCamera( float fTime )
{
	if( eType == CAMERATYPE_Orbit && pTargetNode )
	{
		//Mover a camera para cima e para baixo
		if( INPUT->GetKeyDown( KEY_UP ) )
			fCameraDistance -= 0.1f;
		else if( INPUT->GetKeyDown( KEY_DOWN ) )
			fCameraDistance += 0.1f;

		//Limitar a distancia da camera para não sair do range
		fCameraDistance = Clamp( fCameraDistance, CAMERA_MIN_DISTANCE, CAMERA_MAX_DISTANCE );

		//Mover a camera para os lados
		if( INPUT->GetKeyDown( KEY_LEFT ) )
			fCameraYaw += 0.5f;
		else if( INPUT->GetKeyDown( KEY_RIGHT ) )
			fCameraYaw -= 0.5f;

		//Aumentar pitch da camera (mouse scroll)
		if( INPUT->GetMouseMoveWheel() )
			fDeltaMouseMoveWheel += INPUT->GetMouseMoveWheel() * 0.05f;

		if( fDeltaMouseMoveWheel )
		{
			if( fDeltaMouseMoveWheel < 0.0f )
			{
				fDeltaMouseMoveWheel += 0.001f;

				if( fDeltaMouseMoveWheel >= 0.0f )
					fDeltaMouseMoveWheel = 0.0f;
			}
			else
			{
				fDeltaMouseMoveWheel -= 0.001f;

				if( fDeltaMouseMoveWheel <= 0.0f )
					fDeltaMouseMoveWheel = 0.0f;
			}

			fCameraPitch += fDeltaMouseMoveWheel;
		}

		//Limitar o Pitch da Camera para não sair do range
		fCameraPitch = Clamp( fCameraPitch, 1.0f, 90.0f );

		//Pegar o Arco Tangente da posição do Mouse em relação ao centro da tela
		fMouseYaw = Atan2( INPUT->GetMousePosition().y_ - (GRAPHICS->GetSize().y_ >> 1), INPUT->GetMousePosition().x_ - (GRAPHICS->GetSize().x_ >> 1) ) + 90.0f;
	}
}
