#include "stdafx.h"
#include "CCharacterHandler.h"

#include "CServer.h"

CCharacterHandler::CCharacterHandler( Context * pcContext ) : Object( pcContext )
{
}

CCharacterHandler::~CCharacterHandler()
{
}

CCharacter * CCharacterHandler::LoadCharacter( CUser * pUser, String strCharacterName )
{
	//Carregar o objeto do personagem pelo XML
	XMLFile * pXMLFile = RESOURCECACHE->GetResource<XMLFile>( "Objects/Character.xml" );

	//Arquivo encontrado?
	if( pXMLFile )
	{
		//Instanciar o Node no mapa
		auto * pCharacterNode = MAPHANDLER->GetScene()->InstantiateXML( pXMLFile->GetRoot(), MAPHANDLER->GetMap( MAPID_Test )->GetBaseMap()->GetRandomSpawnPosition(), Quaternion::IDENTITY );
		pCharacterNode->SetOwner( pUser->GetConnection() );

		//Setar o nick no personagem
		auto * pNickNode = pCharacterNode->GetChild( "Nick", true );
		if( pNickNode )
			pNickNode->GetComponent<Text3D>()->SetText( strCharacterName );

		//Criar o componente da Unit, no caso o Character
		CCharacter * pCharacter = pCharacterNode->GetOrCreateComponent<CCharacter>();
		pCharacter->pConnection = pUser->GetConnection();
		pCharacter->Load( MAPHANDLER->GetScene(), UNITTYPE_Character );

		return pCharacter;
	}

	return NULL;
}

void CCharacterHandler::HandleSelectCharacter( CUser * pUser, MemoryBuffer cBuffer )
{
	if( !GAME_SERVER || !pUser )
		return;

	BOOL bCreatingCharacter = cBuffer.ReadBool() ? TRUE : FALSE;
	String strCharacterName = cBuffer.ReadString();

	//Definir o Usuario no servidor
	pUser->GetConnection()->SetScene( MAPHANDLER->GetScene() );

	//Setar o Personagem ao Usuario
	pUser->SetCharacter( LoadCharacter( pUser, strCharacterName ) );

	//Personagem foi criado com sucesso? Então enviar a ID para o Client
	if( pUser->GetCharacter()->GetID() > 0 )
	{
		VectorBuffer cMessage;
		cMessage.WriteInt( pUser->GetCharacter()->GetID() );
		SENDPACKET( pUser->GetConnection(), PKTHDR_CharacterSync, cMessage );
	}
}