#include "stdafx.h"
#include "CUnit.h"

#include "CCharacter.h"

CUnit::CUnit( Context * pcContext ) : LogicComponent( pcContext )
{
	iID		= -1;
}

CUnit::~CUnit()
{
}

BOOL CUnit::Load( Scene * pScene, EUnitType eType )
{
	if( !pScene )
		return FALSE;

	iID = GetNode()->GetID();

	return TRUE;
}
