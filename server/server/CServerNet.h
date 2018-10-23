#pragma once

#include "CNet.h"

class CServerNet : public Object
{
	URHO3D_OBJECT( CServerNet, Object );
public:
	//Construtor
									CServerNet( Context * pcContext );
								   ~CServerNet();
								   
	void							Load();

	void							AddConnection( char * pszIP, int iPort, EServerType iServerType );
	NetConnection				  * AddNetConnection( Connection * pServerConnection );

	void							ConnectAll();
	void							Connect( NetConnection * nc );

	void							DisconnectAll( bool bClosing );
	void							Disconnect( NetConnection * nc );
	void							Disconnected( Connection * pConnection );

	void							SendPacket( EServerType iServerType, ENETPKTHDR eHeader, VectorBuffer cMessage = VectorBuffer(), bool bReliable = true, bool bInOrder = true );
	void							SendPacket( NetConnection * nc, ENETPKTHDR eHeader, VectorBuffer cMessage = VectorBuffer(), bool bReliable = true, bool bInOrder = true );

	//Getters
	std::vector<NetConnection*>		GetConnections(){ return vNetConnections; }
	NetConnection				  * GetNetConnectionByConnection( Connection * pConnection );

	void							HandleNetworkMessage( StringHash cEventType, VariantMap & vEventData );
	void							HandleConnectionStatus( StringHash cEventType, VariantMap & vEventData );
private:
	bool							CorrectPassword( String strPassword );
private:
	VectorBuffer					cMessageNetPassword;
	std::vector<NetConnection*>		vNetConnections;
};