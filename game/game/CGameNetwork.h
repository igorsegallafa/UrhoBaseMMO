#pragma once

#define SOCKETL					(GAMENETWORK->GetConnectionL())
#define SOCKETG					(GAMENETWORK->GetConnectionG())

#define SENDPACKET(c,h,m)		(GAMENETWORK->SendPacket(c,h,m))
#define SENDCPACKET(c,h,m,r,o)	(GAMENETWORK->SendPacket(c,h,m,r,o))

class CGameNetwork : public Object
{
	URHO3D_OBJECT( CGameNetwork, Object );
public:
	//Construtor
								CGameNetwork( Context * pcContext );
	virtual					   ~CGameNetwork();

	BOOL						Init();

	void						HandleNetworkMessage( StringHash cEventType, VariantMap & vEventData );
	void						HandleConnectionStatus( StringHash cEventType, VariantMap & vEventData );

	void						SendPacket( Connection * pConnection, EPKTHDR eHeader, VectorBuffer cMessage = VectorBuffer(), bool bReliable = true, bool bInOrder = true );

	void						ConnectServerL( const char * pszIP, int iPort, VariantMap & vEventData );
	void						ConnectServerG( const char * pszIP, int iPort, VariantMap & vEventData );
	void						CloseServerL();
	void						CloseServerG();
	void						CloseConnections();

	inline void					SetConnectionL( Connection * pConnection ){ pConnectionL = pConnection; }
	inline void					SetConnectionG( Connection * pConnection ){ pConnectionG = pConnection; }
	inline Connection		  * GetConnectionL(){ return pConnectionL; }
	inline Connection		  * GetConnectionG(){ return pConnectionG; }
private:
	SharedPtr<Connection>		pConnectionL;
	SharedPtr<Connection>		pConnectionG;
};