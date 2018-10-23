#include "stdafx.h"
#include "CGameManager.h"

CGameManager::CGameManager( Context * pcContext ) : Object( pcContext )
{
	pScreenManager = new CScreenManager( pcContext );
	pCameraManager = new CCameraManager( pcContext );
}

CGameManager::~CGameManager()
{
}

BOOL CGameManager::Init()
{
	BOOL bRet = TRUE;

	if( !pScreenManager->Init() )
		bRet = FALSE;

	return bRet;
}

void CGameManager::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	pScreenManager->HandleUpdate( cEventType, vEventData );
}

void CGameManager::HandlePostUpdate( StringHash cEventType, VariantMap & vEventData )
{
	pScreenManager->HandlePostUpdate( cEventType, vEventData );
	pCameraManager->HandlePostUpdate( cEventType, vEventData );
}

void CGameManager::HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData )
{
}
