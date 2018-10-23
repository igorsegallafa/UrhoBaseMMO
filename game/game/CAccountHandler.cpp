#include "stdafx.h"
#include "CAccountHandler.h"

#include "CGame.h"

CAccountHandler::CAccountHandler( Context * pcContext ) : Object( pcContext )
{
}

CAccountHandler::~CAccountHandler()
{
}

void CAccountHandler::Reset()
{
	vEventData = GetEventDataMap();
}

void CAccountHandler::HandleLoginConnect( MemoryBuffer cBuffer )
{
	using namespace Account;

	ELoginStatus eLoginStatus = (ELoginStatus)cBuffer.ReadInt();

	//Verificar o Status do Login
	switch( eLoginStatus )
	{
		case LOGINSTATUS_Successful:
			GAMECONFIG->Get().iTotalServers = cBuffer.ReadByte();

			Vector<String> vGameServerList;

			//Verificar as Game Server's recebidas do Login Server
			for( int i = 0; i < GAMECONFIG->Get().iTotalServers; i++ )
			{
				//Recuperar as informações da Game Server (Nome, IP e Porta)
				String strName = cBuffer.ReadString();
				String strIP = cBuffer.ReadString();
				int iPort = cBuffer.ReadUShort();

				vGameServerList.Push( strName );

				//Adicionar a Game Server para a configuração do Game
				GAMECONFIG->Get().saServerInfo[i] = Config::ServerInfo( strName, strIP, iPort );

				//Adicionar a lista de Game Server's para a tela de Login
				CLoginScreen * pLoginScreen = (CLoginScreen*)SCREENMANAGER->GetActiveScreen();
				if( pLoginScreen )
					pLoginScreen->SetGameServerList( vGameServerList );
			}

			break;
	}
}

void CAccountHandler::HandleGameServerData( MemoryBuffer cBuffer )
{
	SCREENMANAGER->SetActiveScreen( SCREEN_Character );
}

BOOL CAccountHandler::ProcessAccountLogin( String strAccountName, String strPassword )
{
	if( strAccountName.Length() > 0 && strPassword.Length() > 0 )
	{
		vEventData = GetEventDataMap();
		vEventData[Account::E_ACCOUNTNAME] = strAccountName;
		vEventData[Account::E_ACCOUNTPW] = strPassword;
		vEventData[Account::E_GAMEVERSION] = GAME_VERSION;

		GAMENETWORK->ConnectServerL( "127.0.0.1", 52078, vEventData );
		return TRUE;
	}

	return FALSE;
}

BOOL CAccountHandler::ProcessSelectGameServer( const Config::ServerInfo * psServerInfo )
{
	if( !SOCKETL )
		return FALSE;

	if( psServerInfo->strIP.Length() > 0 && psServerInfo->iPort > 0 )
	{
		GAMENETWORK->ConnectServerG( psServerInfo->strIP.CString(), psServerInfo->iPort, vEventData );
		return TRUE;
	}

	return FALSE;
}

void CAccountHandler::SelectCharacter( BOOL bCreating, String strCharacterName, ECharacterClass eCharacterClass )
{
	SCREENMANAGER->SetActiveScreen( SCREEN_World );

	//Limpar o Pacote antes de Escrever
	cSelectCharacterMessage.Clear();

	cSelectCharacterMessage.WriteBool( bCreating ? true : false );
	cSelectCharacterMessage.WriteString( strCharacterName );

	//Está criando um novo personagem? Então enviar a classe desejada
	if( bCreating )
		cSelectCharacterMessage.WriteInt( eCharacterClass );
}

void CAccountHandler::ProcessSelectCharacter()
{
	SENDPACKET( SOCKETG, PKTHDR_SelectCharacter, cSelectCharacterMessage );
}