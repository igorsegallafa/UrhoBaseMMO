#include "stdafx.h"
#include "CServerNetwork.h"

#include "CServer.h"

CServerNetwork::CServerNetwork( Context * pcContext ) : Object( pcContext )
{
	pServerNet = new CServerNet( pcContext );
}

CServerNetwork::~CServerNetwork()
{
}

BOOL CServerNetwork::Init()
{
	//Inicializar o Socket / Server
	NETWORK->StartServer( SERVER_PORT );
	//NETWORK->SetSimulatedLatency( 300 );

	//Carregar o Server Net
	pServerNet->Load();

	//Registrar os Eventos do Servidor
	SubscribeToEvent( E_CLIENTIDENTITY, URHO3D_HANDLER( CServerNetwork, HandleClientIdentity ) );
	SubscribeToEvent( E_NETWORKMESSAGE, URHO3D_HANDLER( CServerNetwork, HandleNetworkMessage ) );
	SubscribeToEvent( E_SERVERCONNECTED, URHO3D_HANDLER( CServerNetwork, HandleConnectionStatus ) );
	SubscribeToEvent( E_SERVERDISCONNECTED, URHO3D_HANDLER( CServerNetwork, HandleConnectionStatus ) );
	SubscribeToEvent( E_CONNECTFAILED, URHO3D_HANDLER( CServerNetwork, HandleConnectionStatus ) );
	SubscribeToEvent( E_CLIENTCONNECTED, URHO3D_HANDLER( CServerNetwork, HandleClientConnected ) );
	SubscribeToEvent( E_CLIENTDISCONNECTED, URHO3D_HANDLER( CServerNetwork, HandleClientDisconnected ) );

	//Conectar todos os servidores encontrados para o Server Net
	pServerNet->ConnectAll();

	return TRUE;
}

void CServerNetwork::SendPacket( Connection * c, EPKTHDR eHeader, VectorBuffer cMessage, bool bReliable, bool bInOrder )
{
	if( c )
		c->SendMessage( eHeader, bReliable, bInOrder, cMessage );
}

void CServerNetwork::HandleClientIdentity( StringHash cEventType, VariantMap & vEventData )
{
	Connection * pSender = dynamic_cast<Connection*>(GetEventSender());

	if( pSender )
	{
		//Se for Login Server, então verificar os dados recebidos
		if( LOGIN_SERVER )
			ACCOUNTHANDLER->HandleAccountLogin( pSender, vEventData );

		//Carregar o User (LSERVER e GSERVER)
		USERHANDLER->LoadUser( USERHANDLER->GetUserByConnection( pSender ), vEventData[Account::E_ACCOUNTNAME].GetString() );
	}
}

void CServerNetwork::HandleNetworkMessage( StringHash cEventType, VariantMap & vEventData )
{
	using namespace NetworkMessage;

	//Recuperar a data do pacote e setar no Memory Buffer para assim conseguir ler
	const PODVector<unsigned char> & vData = vEventData[P_DATA].GetBuffer();
	MemoryBuffer cBuffer( vData );

	//Recuperar quem enviou o pacote
	auto * pSender = static_cast<Connection*>(vEventData[P_CONNECTION].GetPtr());

	//Recuperar Header do Pacote
	EPKTHDR eHeader = (EPKTHDR)vEventData[P_MESSAGEID].GetInt();

	//Recuperar o User que recebeu o pacote
	CUser * pUser = USERHANDLER->GetUserByConnection( pSender );

	//Verificar Header recebido
	switch( eHeader )
	{
		case PKTHDR_SelectCharacter:
			CHARACTERHANDLER->HandleSelectCharacter( pUser, cBuffer );
			break;
	}

	pServerNet->HandleNetworkMessage( cEventType, vEventData );
}

void CServerNetwork::HandleConnectionStatus( StringHash cEventType, VariantMap & vEventData )
{
	pServerNet->HandleConnectionStatus( cEventType, vEventData );
}

void CServerNetwork::HandleClientConnected( StringHash eventType, VariantMap & eventData )
{
	auto * pConnection = static_cast<Connection*>(eventData[ClientConnected::P_CONNECTION].GetPtr());

	//Usuário conectado? Então adicionar ao vetor de usuarios conectados
	if( pConnection )
		USERHANDLER->AddUser( pConnection );
}

void CServerNetwork::HandleClientDisconnected( StringHash eventType, VariantMap & eventData )
{
	auto * pConnection = static_cast<Connection*>(eventData[ClientConnected::P_CONNECTION].GetPtr());

	//Deletar o usuario do servidor
	USERHANDLER->DelUser( pConnection );
}
