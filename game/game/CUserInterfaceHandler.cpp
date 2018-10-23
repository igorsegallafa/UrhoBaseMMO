#include "stdafx.h"
#include "CUserInterfaceHandler.h"

CUserInterfaceHandler::CUserInterfaceHandler( Context * pcContext ) : Object( pcContext )
{
	pTitleBox = new GUI::TitleBox( pcContext );
}

CUserInterfaceHandler::~CUserInterfaceHandler()
{
}

BOOL CUserInterfaceHandler::Init()
{
	BOOL bRet = TRUE;

	if( !pTitleBox->Init() )
		bRet = FALSE;

	return bRet;
}

void CUserInterfaceHandler::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	pTitleBox->HandleUpdate( cEventType, vEventData );
}