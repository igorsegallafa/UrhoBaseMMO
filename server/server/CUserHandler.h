#pragma once

#include "CUser.h"

typedef HashMap<Connection*, SharedPtr<CUser>> Hash_Users;

class CUserHandler : public Object
{
	URHO3D_OBJECT( CUserHandler, Object );
public:
	//Construtor
									CUserHandler( Context * pcContext );
	virtual						   ~CUserHandler();

	BOOL							LoadUser( CUser * pUser, String strAccountName );

	CUser						  * GetUserByConnection( Connection * pConnection ){ return vUsers[pConnection]; }
	BOOL							AddUser( Connection * pConnection );
	void							DelUser( Connection * pConnection );
private:
	Hash_Users                      vUsers;
};