#include "stdafx.h"
#include "CServerHandler.h"

CServerHandler::CServerHandler( Context * pcContext ) : Object( pcContext )
{
	pAccountHandler		= new CAccountHandler( pcContext );
	pUserHandler		= new CUserHandler( pcContext );
	pMapHandler			= new CMapHandler( pcContext );
	pCharacterHandler	= new CCharacterHandler( pcContext );
}

CServerHandler::~CServerHandler()
{
}

BOOL CServerHandler::Init()
{
	BOOL bRet = TRUE;

	if( !pMapHandler->Init() )
		bRet = FALSE;

	return bRet;
}