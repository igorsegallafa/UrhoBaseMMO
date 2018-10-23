#include "stdafx.h"
#include "CCharacter.h"

#undef new

CCharacter::CCharacter( Context * pcContext ) : CUnit( pcContext )
{
	pConnection			= NULL;

	pGhostObject		= NULL;
	pBulletController	= NULL;

	fHeight				= 2.3f;
	fDiameter			= 0.7f;

	bFollowingTarget	= FALSE;

	cTargetDirection	= Vector3::ZERO;

	//Registrar os Eventos
	SubscribeToEvent( E_CROWD_AGENT_REPOSITION, URHO3D_HANDLER( CCharacter, HandleCrowdAgentReposition ) );
}

CCharacter::~CCharacter()
{
	if( node_ )
		node_->Remove();
}

void CCharacter::Start()
{
	//Transform inicial do Node
	btTransform cStartTransform;
	cStartTransform.setIdentity();
	cStartTransform.setOrigin( btVector3( 0, 5, 0 ) );
	cStartTransform.setRotation( ToBtQuaternion( Quaternion( 90, 0, 0 ) ) );

	//Capsula usada para a colisão
	btConvexShape * pCapsule = new btCapsuleShape( fDiameter * 0.5f, fHeight - fDiameter );

	//World do PhysicsWorld
	btDiscreteDynamicsWorld * pWorld = GetScene()->GetComponent<PhysicsWorld>()->GetWorld();

	if( pWorld )
	{
		pGhostObject = new btPairCachingGhostObject();
		pGhostObject->setWorldTransform( cStartTransform );
		pWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback( new btGhostPairCallback() );
		pGhostObject->setCollisionShape( pCapsule );
		pGhostObject->setCollisionFlags( btCollisionObject::CF_CHARACTER_OBJECT );
		pBulletController = new btKinematicCharacterController( pGhostObject, pCapsule, 0.3f, btVector3( 0, 0, 1 ) );
		pBulletController->setGravity( pWorld->getGravity() );

		pWorld->addCollisionObject( pGhostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::AllFilter );
		pWorld->addAction( pBulletController );
		pBulletController->setMaxJumpHeight( 1.5 );
	}
}

void CCharacter::Update( float fTime )
{
}

void CCharacter::FixedUpdate( float fTime )
{
	if( pConnection )
	{
		//Recuperar os últimos controles da conexão
		const Controls & cControls = pConnection->GetControls();

#ifdef _GAME
		//Recuperar a rotação
		Quaternion cRotation = Quaternion{};
		Vector3 cMoveDirection = Vector3::ZERO;

		auto * pTransform = GetComponent<SmoothedTransform>();

		//Se o componente SmoothedTransform não existir, não prosseguir com a o Update
		if( !pTransform )
			return;

		//Está andando com o mouse?
		if( cControls.buttons_ & CHARACTERCONTROL_Forward )
		{
			cMoveDirection += Vector3::FORWARD;
			cMoveDirection = node_->GetWorldRotation() * cMoveDirection;
			cRotation = Quaternion( 0.0f, cControls.yaw_, 0.0f );
			pTransform->SetTargetRotation( cRotation );
		}

		//Está seguindo algum target? Então setar a direção para o Target
		if( bFollowingTarget )
		{
			cMoveDirection = cTargetDirection;
			cRotation.FromLookRotation( cTargetDirection );
			pTransform->SetTargetRotation( cRotation );
		}

		//O vetor da direção é válido?
		if( cMoveDirection.LengthSquared() > 0.0f )
		{
			//Está no chão?
			if( pBulletController->onGround() )
				pBulletController->setWalkDirection( ToBtVector3( cMoveDirection * fTime * 10.0f ) );
			else
				pBulletController->setWalkDirection( ToBtVector3( cMoveDirection * fTime * 10.0f * 0.5f ) );
		}
		else
			pBulletController->setWalkDirection( btVector3( 0, 0, 0 ) );

		btTransform cTransform;
		cTransform = pBulletController->getGhostObject()->getWorldTransform();

		//Setar a nova posição para o Node
		Vector3 cNewPosition = ToVector3( cTransform.getOrigin() ) + Vector3::DOWN * fHeight * 0.5f;
		node_->SetWorldPosition( cNewPosition );
#else
		node_->SetRotation( pConnection->GetRotation() );
		node_->SetPosition( pConnection->GetPosition() );
#endif

		auto * p = node_->GetComponent<AnimationController>( true );
		if( cControls.buttons_ & CHARACTERCONTROL_Forward )
		{
			p->PlayExclusive( "Models/run.ani", 0, true, 0.3f );
		}
		else
			p->PlayExclusive( "Models/idle.ani", 0, true, 0.3f );
	}
}

void CCharacter::SetTargetPosition( const Vector3 & sDest )
{
#ifdef _GAME
	//Resetar o destino se já tiver algum em andamento
	ResetTargetPosition();

	//Node válido?
	if( node_ )
	{
		Scene * pScene = node_->GetScene();
		CrowdManager * pCrowdManager = pScene->GetComponent<CrowdManager>();

		if( pCrowdManager )
			pCrowdManager->SetCrowdTarget( sDest, node_ );
	}
#endif
}

void CCharacter::ResetTargetPosition()
{
#ifdef _GAME
	//Node válido?
	if( node_ )
	{
		Scene * pScene = node_->GetScene();
		CrowdManager * pCrowdManager = pScene->GetComponent<CrowdManager>();

		if( pCrowdManager )
		{
			bFollowingTarget = FALSE; 
			cTargetDirection = Vector3::ZERO;

			pCrowdManager->ResetCrowdTarget( node_ );
		}
	}
#endif
}

const VariantMap CCharacter::GetVariablesMap() const
{
	VariantMap vVars = VariantMap();

	return vVars;
}

void CCharacter::HandleCrowdAgentReposition( StringHash cEventType, VariantMap & vEventData )
{
#ifdef _GAME
	CrowdAgent * pCrowdAgent = static_cast<CrowdAgent*>(vEventData[CrowdAgentReposition::P_CROWD_AGENT].GetPtr());
	bool bArrived = vEventData[CrowdAgentReposition::P_ARRIVED].GetBool();

	if( pCrowdAgent )
	{
		Vector3 cDesiredVelocity = pCrowdAgent->GetDesiredVelocity();

		//Chegou no destino? Então resetar o target
		if( bArrived && bFollowingTarget )
		{
			ResetTargetPosition();
			return;
		}

		//Se a velocidade do crowd agent é válida, então atualizar a direção do Target
		if( cDesiredVelocity != Vector3::ZERO )
		{
			cTargetDirection = cDesiredVelocity.Normalized();
			bFollowingTarget = TRUE;
		}
	}
#endif
}