#include "stdafx.h"
#include "CGameHandler.h"

CGameHandler::CGameHandler( Context * pcContext ) : Object( pcContext )
{
	pUserInterfaceHandler = new CUserInterfaceHandler( pcContext );
	pAccountHandler = new CAccountHandler( pcContext );
	pCharacterHandler = new CCharacterHandler( pcContext );
}

CGameHandler::~CGameHandler()
{
}

BOOL CGameHandler::Init()
{
	BOOL bRet = TRUE;

	if( !pUserInterfaceHandler->Init() )
		bRet = FALSE;

	return bRet;
}

void CGameHandler::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	pUserInterfaceHandler->HandleUpdate( cEventType, vEventData );
	pCharacterHandler->HandleUpdate( cEventType, vEventData );
}

void CGameHandler::HandlePostUpdate( StringHash cEventType, VariantMap & vEventData )
{
	pCharacterHandler->HandlePostUpdate( cEventType, vEventData );
}

void CGameHandler::HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData )
{
	pCharacterHandler->HandlePhysicsPreStep( cEventType, vEventData );
}