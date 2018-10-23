#pragma once

#include "CUserInterfaceHandler.h"
#include "CAccountHandler.h"
#include "CCharacterHandler.h"

#define USERINTERFACEHANDLER			(GAMEHANDLER->GetUserInterfaceHandler())
#define	ACCOUNTHANDLER					(GAMEHANDLER->GetAccountHandler())
#define CHARACTERHANDLER				(GAMEHANDLER->GetCharacterHandler())

class CGameHandler : public Object
{
	URHO3D_OBJECT( CGameHandler, Object );
public:
	//Construtor
										CGameHandler( Context * pcContext );
	virtual							   ~CGameHandler();

	BOOL								Init();

	//Eventos Registrados
	void								HandleUpdate( StringHash cEventType, VariantMap & vEventData );
	void								HandlePostUpdate( StringHash cEventType, VariantMap & vEventData );
	void								HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData );

	//Getters
	CUserInterfaceHandler			  * GetUserInterfaceHandler(){ return pUserInterfaceHandler; }
	CAccountHandler					  * GetAccountHandler(){ return pAccountHandler; }
	CCharacterHandler				  * GetCharacterHandler(){ return pCharacterHandler; }
protected:
	SharedPtr<CAccountHandler>			pAccountHandler;
	SharedPtr<CUserInterfaceHandler>	pUserInterfaceHandler;
	SharedPtr<CCharacterHandler>		pCharacterHandler;
};