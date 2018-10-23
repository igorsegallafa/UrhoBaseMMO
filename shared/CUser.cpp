#include "stdafx.h"
#include "CUser.h"

CUser::CUser( Context * pcContext, Connection * pConnection_ ) : Object( pcContext ), pConnection( pConnection_ )
{
	bInUse			= FALSE;

	pCharacter		= NULL;
}

CUser::~CUser()
{
	if( pCharacter )
		if( pCharacter->GetNode() )
			pCharacter->GetNode()->Remove();
}

void CUser::Init( String strAccountName_ )
{
	bInUse = TRUE;

	strAccountName = strAccountName_;
}