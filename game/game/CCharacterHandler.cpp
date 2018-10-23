#include "stdafx.h"
#include "CCharacterHandler.h"

#include "CGame.h"

CCharacterHandler::CCharacterHandler( Context * pcContext ) : Object( pcContext )
{
	//Registrar os Objetos
	pcContext->RegisterFactory<CCharacter>();

	iCharacterID		= -1;
	pCharacter			= NULL;
	pSelectedNode		= NULL;

	bIsWalking			= FALSE;

	SubscribeToEvent( E_MOUSEBUTTONDOWN, URHO3D_HANDLER( CCharacterHandler, HandleMouseDown ) );
}

CCharacterHandler::~CCharacterHandler()
{
	if( pCharacter )
	{
		pCharacter->Remove();
		pCharacter = NULL;
	}
}

void CCharacterHandler::Load()
{
	Node * pCharacterNode = pCharacter->GetNode();

	if( pCharacterNode )
	{
		Node * pCollisionNode = pCharacterNode->GetChild( "Collision", true );
		if( pCollisionNode )
			pCharacterNode->RemoveChild( pCollisionNode );

		//Setar Conexão da Game Server
		pCharacter->pConnection = SOCKETG;

		//Carregar a Unit
		pCharacter->Load( ACTIVESCREEN->GetScene(), UNITTYPE_Character );

		//Definir a camera como Orbit e setar o Target como o personagem
		CAMERAMANAGER->SetCameraType( CAMERATYPE_Orbit, pCharacter->GetNode() );
	}
}

void CCharacterHandler::HandleCharacterSync( MemoryBuffer cBuffer )
{
	UINT iID = cBuffer.ReadUInt();

	//Setar a ID recebida correspondente ao personagem logado
	if( iID > 0 )
		iCharacterID = iID;
}

void CCharacterHandler::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	if( INGAME && pCharacter && SOCKETG )
	{
		auto * pCharacterNode = pCharacter->GetNode();

		if( pCharacterNode )
		{
			pSelectedNode = CAMERAMANAGER->GetNodeRaycast();

			//Se estiver selecionando a si próprio, ignorar
			if( pSelectedNode == (CHARACTERGAME ? CHARACTERGAME->GetNode() : NULL) )
				pSelectedNode = NULL;

			//Verificar se selecionou o Target com o botão esquerdo do mouse
			if( INPUT->GetMouseButtonPress( MOUSEB_LEFT ) )
			{
				if( pSelectedNode )
				{
					Vector3 pathPos = pCharacterNode->GetScene()->GetComponent<DynamicNavigationMesh>()->FindNearestPoint( pSelectedNode->GetPosition(), Vector3( 1.0f, 1.0f, 1.0f ) );
					CHARACTERGAME->SetTargetPosition( pathPos );
				}
				else
					CHARACTERGAME->ResetTargetPosition();
			}

			//Definir os Controles da Conexão
			Controls cControls;
			cControls.yaw_ = CAMERAMANAGER->GetCameraYaw() + CAMERAMANAGER->GetMouseYaw();
			cControls.Set( CHARACTERCONTROL_Forward, INPUT->GetMouseButtonDown( MOUSEB_LEFT ) || bIsWalking || CHARACTERGAME->IsFollowingTarget() );

			SOCKETG->SetPosition( pCharacterNode->GetPosition() );
			SOCKETG->SetRotation( pCharacterNode->GetRotation() );
			SOCKETG->SetControls( cControls );
		}
	}
}

void CCharacterHandler::HandlePostUpdate( StringHash cEventType, VariantMap & vEventData )
{
	if( !INGAME )
		return;

	float fTimeStep = vEventData[Update::P_TIMESTEP].GetFloat();

	//Se ainda o personagem não está carregado no game, carregar
	if( !pCharacter )
	{
		auto * pCharacterNode = SCREENMANAGER->GetActiveScreen()->GetScene()->GetNode( iCharacterID );

		//Node do personagem foi encontrado?
		if( pCharacterNode )
		{
			pCharacter = pCharacterNode->GetComponent<CCharacter>( true );

			//Criar o Crowd Agent do Personagem
			CrowdAgent * pCrowdAgent = pCharacterNode->CreateComponent<CrowdAgent>();
			if( pCrowdAgent )
			{
				pCrowdAgent->SetHeight( 2.0f );
				pCrowdAgent->SetRadius( 1.5f );
				pCrowdAgent->SetMaxSpeed( 1.0f );
				pCrowdAgent->SetUpdateNodePosition( false );
			}

			//Componente Unit encontrado? Carregar o personagem
			if( pCharacter )
				Load();
		}
	}
}

void CCharacterHandler::HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData )
{
}

void CCharacterHandler::HandleMouseDown( StringHash cEventType, VariantMap & vEventData )
{
	if( vEventData[MouseButtonDown::P_CLICKS].GetInt() == 2 )
		bIsWalking = TRUE;
	else
		bIsWalking = FALSE;
}
