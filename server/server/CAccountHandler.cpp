#include "stdafx.h"
#include "CAccountHandler.h"

#include "CServer.h"

CAccountHandler::CAccountHandler( Context * pcContext ) : Object( pcContext )
{
}

CAccountHandler::~CAccountHandler()
{
}

BOOL CAccountHandler::HandleAccountLogin( Connection * pSender, VariantMap vEventData )
{
	if( !pSender )
		return FALSE;

	BOOL bRet = FALSE;

	using namespace Account;
	ELoginStatus eLoginStatus = LOGINSTATUS_Successful;

	//Escrever o pacote para enviar para o Client
	VectorBuffer cMessage;
	cMessage.WriteInt( eLoginStatus );

	//Se o login foi feito com sucesso, então escrever a lista de Game Server's
	if( eLoginStatus == LOGINSTATUS_Successful )
	{
		cMessage.WriteByte( SERVERCONFIG->Get().iTotalServers - 1 );

		//Escrever as informações daquela Game Server (Nome, IP e Porta)
		for( int i = 1; i < SERVERCONFIG->Get().iTotalServers; i++ )
		{
			const Config::ServerInfo * p = SERVERCONFIG->Get().saServerInfo + i;

			cMessage.WriteString( p->strName );
			cMessage.WriteString( p->strIP );
			cMessage.WriteUShort( p->iPort );
		}

		bRet = TRUE;
	}
	else
		//Caso o login não foi feito com sucesso, então desconectar o Client
		pSender->Disconnect( 500 );

	//Enviar o pacote para o Client para confirmar o login
	SENDPACKET( pSender, PKTHDR_LoginConnect, cMessage );

	return bRet;
}