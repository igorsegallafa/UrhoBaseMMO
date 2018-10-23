#pragma once

#include "CUser.h"

class CCharacterHandler : public Object
{
	URHO3D_OBJECT( CCharacterHandler, Object );
public:
	//Construtor
								CCharacterHandler( Context * pcContext );
	virtual					   ~CCharacterHandler();

	void						HandleSelectCharacter( CUser * pUser, MemoryBuffer cBuffer );
private:
	CCharacter				  * LoadCharacter( CUser * pUser, String strCharacterName );
};