#include "stdafx.h"
#include "CGameNetwork.h"

#include "CGame.h"

CGameNetwork::CGameNetwork( Context * pcContext ) : Object( pcContext )
{
}

CGameNetwork::~CGameNetwork()
{
}

BOOL CGameNetwork::Init()
{
	//Subscribe Events
	SubscribeToEvent( E_NETWORKMESSAGE, URHO3D_HANDLER( CGameNetwork, HandleNetworkMessage ) );
	SubscribeToEvent( E_SERVERCONNECTED, URHO3D_HANDLER( CGameNetwork, HandleConnectionStatus ) );
	SubscribeToEvent( E_SERVERDISCONNECTED, URHO3D_HANDLER( CGameNetwork, HandleConnectionStatus ) );
	SubscribeToEvent( E_CONNECTFAILED, URHO3D_HANDLER( CGameNetwork, HandleConnectionStatus ) );

	return TRUE;
}

void CGameNetwork::HandleNetworkMessage( StringHash cEventType, VariantMap & vEventData )
{
	auto * pNetwork = GetSubsystem<Network>();
	using namespace NetworkMessage;

	//Recuperar a Data do Pacote e setar no Memory Buffer para assim conseguir ler
	const PODVector<unsigned char> & vData = vEventData[P_DATA].GetBuffer();
	MemoryBuffer cBuffer( vData );

	//Recuperar o Header do Pacote
	EPKTHDR eHeader = (EPKTHDR)vEventData[P_MESSAGEID].GetInt();

	//Verificar Header Recebido
	switch( eHeader )
	{
		case PKTHDR_LoginConnect:
			ACCOUNTHANDLER->HandleLoginConnect( cBuffer );
			break;
		case PKTHDR_GameServerData:
			ACCOUNTHANDLER->HandleGameServerData( cBuffer );
			break;
		case PKTHDR_CharacterSync:
			CHARACTERHANDLER->HandleCharacterSync( cBuffer );
		default:
			break;
	}
}

void CGameNetwork::HandleConnectionStatus( StringHash cEventType, VariantMap & vEventData )
{
	auto * pServerConnection = static_cast<Connection*>(vEventData[NetworkMessage::P_CONNECTION].GetPtr());
	if( pServerConnection )
	{
		if( cEventType == E_SERVERDISCONNECTED || cEventType == E_CONNECTFAILED )
			ACCOUNTHANDLER->Reset();
	}
}

void CGameNetwork::SendPacket( Connection * pConnection, EPKTHDR eHeader, VectorBuffer cMessage, bool bReliable, bool bInOrder )
{
	if( pConnection != NULL )
		pConnection->SendMessage( eHeader, bReliable, bInOrder, cMessage );
}

void CGameNetwork::ConnectServerL( const char * pszIP, int iPort, VariantMap & vEventData )
{
	CloseServerL();

	SetConnectionL( NETWORK->Connect( pszIP, iPort, NULL, vEventData ) );
}

void CGameNetwork::ConnectServerG( const char * pszIP, int iPort, VariantMap & vEventData )
{
	CloseServerG();

	SetConnectionG( NETWORK->Connect( pszIP, iPort, NULL, vEventData ) );
}

void CGameNetwork::CloseServerL()
{
	if( SOCKETL != NULL )
	{
		SOCKETL->Disconnect();

		SetConnectionL( NULL );
	}
}

void CGameNetwork::CloseServerG()
{
	if( SOCKETG != NULL )
	{
		SOCKETG->Disconnect();

		SetConnectionG( NULL );
	}
}

void CGameNetwork::CloseConnections()
{
	CloseServerL();
	CloseServerG();
}