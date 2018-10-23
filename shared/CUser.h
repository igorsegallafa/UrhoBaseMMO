#pragma once

#include "CUnit.h"

#include "PUser.h"

class CUser : public Object
{
	URHO3D_OBJECT( CUser, Object );
public:
							CUser( Context * pcContext, Connection * pConnection_ );
						   ~CUser();

	void					Init( String strAccountName_ );

	Connection			  * GetConnection() const{ return pConnection; }

	void					SetCharacter( CCharacter * pCharacter_ ){ pCharacter = pCharacter_; }
	CCharacter			  * GetCharacter() const{ return pCharacter; }
private:
	BOOL					bInUse;

	String					strAccountName;

	Connection			  * pConnection;
	CCharacter			  * pCharacter;
};