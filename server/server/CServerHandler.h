#pragma once

#include "CAccountHandler.h"
#include "CUserHandler.h"
#include "CMapHandler.h"
#include "CCharacterHandler.h"

#define ACCOUNTHANDLER			(SERVERHANDLER->GetAccountHandler())
#define USERHANDLER				(SERVERHANDLER->GetUserHandler())
#define MAPHANDLER				(SERVERHANDLER->GetMapHandler())
#define CHARACTERHANDLER		(SERVERHANDLER->GetCharacterHandler())

class CServerHandler : public Object
{
	URHO3D_OBJECT( CServerHandler, Object );
public:
	//Construtor
								CServerHandler( Context * pcContext );
	virtual					   ~CServerHandler();

	BOOL						Init();

	//Getters
	CAccountHandler			  * GetAccountHandler() const{ return pAccountHandler; }
	CUserHandler			  * GetUserHandler() const{ return pUserHandler; }
	CMapHandler				  * GetMapHandler() const{ return pMapHandler; }
	CCharacterHandler		  * GetCharacterHandler() const{ return pCharacterHandler; }
protected:
	SharedPtr<CAccountHandler>	pAccountHandler;
	SharedPtr<CUserHandler>		pUserHandler;
	SharedPtr<CMapHandler>		pMapHandler;
	SharedPtr<CCharacterHandler>pCharacterHandler;
};