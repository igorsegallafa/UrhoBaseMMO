#pragma once

#include "CServerNet.h"
#include "CAccount.h"
#include "CUser.h"

#define SERVERNET				(SERVERNETWORK->GetServerNet())

#define SENDPACKET(c,h,m)		(SERVERNETWORK->SendPacket(c,h,m))

class CServerNetwork : public Object
{
	URHO3D_OBJECT( CServerNetwork, Object );
public:
	//Construtor
								CServerNetwork( Context * pcContext );
							   ~CServerNetwork();

	BOOL						Init();

	void						SendPacket( Connection * c, EPKTHDR eHeader, VectorBuffer cMessage = VectorBuffer(), bool bReliable = true, bool bInOrder = true );

	//Getters and Setters
	CServerNet				  * GetServerNet() const{ return pServerNet; }
private:
	void						HandleClientIdentity( StringHash cEventType, VariantMap & vEventData );
	void						HandleNetworkMessage( StringHash cEventType, VariantMap & vEventData );
	void						HandleConnectionStatus( StringHash cEventType, VariantMap & vEventData );

	//Usuário conectado ao servidor
	void						HandleClientConnected( StringHash cEventType, VariantMap & vEventData );

	//Usuário desconectado do servidor
	void						HandleClientDisconnected( StringHash cEventType, VariantMap & vEventData );
protected:
	SharedPtr<CServerNet>		pServerNet;
};