#pragma once

#include "CNonPlayerCharacter.h"

#include "PMap.h"

class CBaseMap
{
public:
											CBaseMap();
										   ~CBaseMap();

	void									SetFileName( String strFile ){ strFileName = strFile; }
	String									GetFileName(){ return strFileName; }

	void									SetType( EMapType eMapType ){ eType = eMapType; }

	Vector3									GetRandomSpawnPosition();
	void									AddSpawnPosition( Vector3 cPosition ){ vSpawnPositions.Push( cPosition ); }
private:
	String									strFileName;
	Vector<Vector3>							vSpawnPositions;

	EMapID									eID;
	EMapType								eType;
};

class CMap
{
public:
											CMap( String strMapName );
										   ~CMap();

	String									GetName(){ return strName; }

	void									SetBaseMap( CBaseMap * pBase ){ pBaseMap = pBase; }
	CBaseMap							  * GetBaseMap(){ return pBaseMap; }

	void									SetNode( Node * pNode ){ pMapNode = pNode; }
	Node								  * GetNode(){ return pMapNode; }

	void									AddNPC( CNonPlayerCharacter * pNPC );
	BOOL									RemoveNPC( CNonPlayerCharacter * pNPC );
private:
	String									strName;

	CBaseMap							  * pBaseMap;
	Node								  * pMapNode;

	Vector<CNonPlayerCharacter *>			vNPCs;
};