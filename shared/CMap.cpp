#include "stdafx.h"
#include "CMap.h"

CBaseMap::CBaseMap()
{
}

CBaseMap::~CBaseMap()
{
}

Vector3 CBaseMap::GetRandomSpawnPosition()
{
	int iSpawnIndex = Random( 0, vSpawnPositions.Size() - 1 );
	return vSpawnPositions[iSpawnIndex];
}

CMap::CMap( String strMapName ) : strName( strMapName )
{
}

CMap::~CMap()
{
	if( pBaseMap )
	{
		delete pBaseMap;
		pBaseMap = NULL;
	}
}

void CMap::AddNPC( CNonPlayerCharacter * pNPC )
{
	vNPCs.Push( pNPC );
}

BOOL CMap::RemoveNPC( CNonPlayerCharacter * pNPC )
{
	for( Vector<CNonPlayerCharacter*>::Iterator i = vNPCs.Begin(); i != vNPCs.End(); ++i )
	{
		if( pNPC == (*i) )
		{
			vNPCs.Erase( i );
			return TRUE;
		}
	}
	
	return FALSE;
}
