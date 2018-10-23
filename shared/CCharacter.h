#pragma once

#include "CUnit.h"

#include "PCharacter.h"

class btPairCachingGhostObject;
class btKinematicCharacterController;

class CCharacter : public CUnit
{
	URHO3D_OBJECT( CCharacter, CUnit );
public:
										CCharacter( Context * pcContext );
									   ~CCharacter() override;

	void								Start() override;
	void								Update( float fTime ) override;
	void								FixedUpdate( float fTime ) override;

	void								SetTargetPosition( const Vector3 & sDest );
	void								ResetTargetPosition();

	const BOOL							IsFollowingTarget() const{ return bFollowingTarget; }

	void								SetTargetDirection( const Vector3 & sDir ){ cTargetDirection = sDir; }
	const Vector3					  & GetTargetDirection() const{ return cTargetDirection; }

	btKinematicCharacterController	  * GetBulletController() const{ return pBulletController; }
	const VariantMap					GetVariablesMap() const;
private:
	void 								HandleCrowdAgentReposition( StringHash cEventType, VariantMap & vEventData );
public:
	float								fHeight;
	float								fDiameter;

	BOOL								bFollowingTarget;
	Vector3								cTargetDirection;

	btPairCachingGhostObject		  * pGhostObject;
	btKinematicCharacterController	  * pBulletController;

	WeakPtr<Connection>					pConnection;
};