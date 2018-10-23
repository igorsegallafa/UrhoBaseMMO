#include "stdafx.h"
#include "CUserHandler.h"

#include "CServer.h"

CUserHandler::CUserHandler( Context * pcContext ) : Object( pcContext )
{
}

CUserHandler::~CUserHandler()
{
}

BOOL CUserHandler::LoadUser( CUser * pUser, String strAccountName )
{
	if( pUser )
	{
		//Inicializar a classe do usuário
		pUser->Init( strAccountName );

		if( GAME_SERVER )
		{
			VectorBuffer cMessage;

			/*
			 * ESCREVER OS PERSONAGENS ENCONTRADOS DAQUELA CONTA (NICK,LEVEL,CLASSE,MAPA)
			 */

			SERVERNETWORK->SendPacket( pUser->GetConnection(), PKTHDR_GameServerData, cMessage );
		}
	}

	return TRUE;
}

BOOL CUserHandler::AddUser( Connection * pConnection )
{
	Hash_Users::Iterator i = vUsers.Find( pConnection );

	//Usuário foi encontrado? Então quer dizer que já tem um usuário com está conexão, apenas retornar FALSE
	if( i != vUsers.End() )
		return FALSE;

	//Caso contrário, adicionar o usuário no servidor
	SharedPtr<CUser> pUser( new CUser( context_, pConnection ) );
	vUsers[pConnection] = pUser;
}

void CUserHandler::DelUser( Connection * pConnection )
{
	Hash_Users::Iterator i = vUsers.Find( pConnection );

	//Usuário foi encontrado? Então deletar
	if( i != vUsers.End() )
		vUsers.Erase( pConnection );
}