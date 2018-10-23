#include "stdafx.h"
#include "CMapHandler.h"

#include "CServer.h"

CMapHandler::CMapHandler( Context * pcContext ) : Object( pcContext )
{
	pScene = new Scene( context_ );
}

CMapHandler::~CMapHandler()
{
	for( auto &pMap : vMaps )
	{
		delete pMap;
		pMap = NULL;
	}

	vMaps.Clear();
}

BOOL CMapHandler::Init()
{
	//Carregar os mapas apenas se o servidor for do tipo Game Server
	if( GAME_SERVER )
	{
		LOGINFO( "Loading Maps..." );

		//Carregar Mapas
		Load();

		//Criar a Cena dos mapas
		CreateScene();
	}

	return TRUE;
}

void CMapHandler::Load()
{
	CMap * pNewMap = NULL;
	CBaseMap * pNewBaseMap = NULL;

	{	//GM Room
		pNewMap = new CMap( "GM Room" );
		pNewBaseMap = new CBaseMap();
		pNewBaseMap->SetFileName( "Maps/Test.mdl" );
		pNewBaseMap->SetType( MAPTYPE_Dungeon );
		pNewBaseMap->AddSpawnPosition( Vector3( 0.0f, 0.5f, 0.0f ) );

		pNewMap->SetBaseMap( pNewBaseMap );
		vMaps.Push( pNewMap );

		LoadMap( pNewMap );
	}
}

void CMapHandler::CreateScene()
{
	pScene = new Scene( context_ );

	pScene->CreateComponent<Octree>( LOCAL );
	pScene->CreateComponent<PhysicsWorld>( LOCAL );

	//Carregar a colisão de cada mapa e em seguida carrega-lo
	for( const auto &pMap : vMaps )
	{
		//Criar o node correspondente ao Mapa
		Node * pNewMapNode = pScene->CreateChild( pMap->GetName(), LOCAL );
		pNewMapNode->SetPosition( Vector3( 0, 0, 0 ) );
		pNewMapNode->SetScale( Vector3( 100.0f, 1.0f, 100.0f ) );

		auto * pMapRigidBody = pNewMapNode->CreateComponent<RigidBody>();
		pMapRigidBody->SetFriction( 1.0f );

		auto * pMapCollisionShape = pNewMapNode->CreateComponent<CollisionShape>();
		pMapCollisionShape->SetBox( Vector3::ONE );

		//Setar o Node no mapa
		pMap->SetNode( pNewMapNode );

		//Carregar Mapa
		LoadMap( pMap );
	}
}

CMap * CMapHandler::GetMap( String strMapName )
{
	for( auto &pMap : vMaps )
		if( pMap->GetName().Compare( strMapName, false ) == 0 )
			return pMap;

	return NULL;
}

CMap * CMapHandler::GetMap( EMapID iID )
{
	if( iID >= 0 && iID < (int)vMaps.Size() )
		return vMaps[iID];

	return NULL;
}

void CMapHandler::LoadMap( CMap * pMap )
{
	LoadNPCs( pMap );
}

void CMapHandler::LoadNPCs( CMap * pMap )
{
	/**   CARREGAR OS NPCS DA DATABASE   **/

	XMLFile * pXMLFile = RESOURCECACHE->GetResource<XMLFile>( "Objects/NPC.xml" );
	if( pXMLFile )
	{
		auto * pNPCNode = MAPHANDLER->GetScene()->InstantiateXML( pXMLFile->GetRoot(), pMap->GetBaseMap()->GetRandomSpawnPosition() + Vector3(2.0f, 0.0f), Quaternion::IDENTITY );
		pNPCNode->SetOwner( nullptr );
		pNPCNode->CreateComponent<SmoothedTransform>();

		auto * pNickNode = pNPCNode->GetChild( "Nick", true );
		if( pNickNode )
			pNickNode->GetComponent<Text3D>()->SetText( "NPC #1" );

		CNonPlayerCharacter * pNPC = pNPCNode->GetOrCreateComponent<CNonPlayerCharacter>();
		pNPC->Load( MAPHANDLER->GetScene(), UNITTYPE_Character );
		
		pMap->AddNPC( pNPC );
	}
}