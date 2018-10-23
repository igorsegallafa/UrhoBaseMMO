#pragma once

#include "CGameConfig.h"
#include "CCharacter.h"
#include "CAccount.h"

class CAccountHandler : public Object
{
	URHO3D_OBJECT( CAccountHandler, Object );
public:
								CAccountHandler( Context * pcContext );
	virtual					   ~CAccountHandler();

	void						Reset();

	void						HandleLoginConnect( MemoryBuffer cBuffer );
	void						HandleGameServerData( MemoryBuffer cBuffer );

	BOOL						ProcessAccountLogin( String strAccountName, String strPassword );
	BOOL						ProcessSelectGameServer( const Config::ServerInfo * psServerInfo );

	void						SelectCharacter( BOOL bCreating, String strCharacterName, ECharacterClass eCharacterClass = CHARACTERCLASS_Undefined );
	void						ProcessSelectCharacter();
private:
	VariantMap					vEventData;
	VectorBuffer				cSelectCharacterMessage;
};