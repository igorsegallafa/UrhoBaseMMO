#pragma once

#include "CCharacter.h"

#define INGAME						(SCREENMANAGER->GetActiveScreenType() == SCREEN_World)

#define CHARACTERGAME				(CHARACTERHANDLER->GetCharacter())

class CCharacterHandler : public Object
{
	URHO3D_OBJECT( CCharacterHandler, Object );
public:
									CCharacterHandler( Context * pcContext );
	virtual						   ~CCharacterHandler();

	void							Load();

	void							HandleCharacterSync( MemoryBuffer cBuffer );
	void							HandleUpdate( StringHash cEventType, VariantMap & vEventData );
	void							HandlePostUpdate( StringHash cEventType, VariantMap & vEventData );
	void							HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData );

	const BOOL						IsWalking() const{ return bIsWalking; }

	//Getters
	CCharacter					  * GetCharacter(){ return pCharacter; }
private:
	//Eventos Registrados
	void							HandleMouseDown( StringHash cEventType, VariantMap & vEventData );
private:
	int								iCharacterID;

	BOOL							bIsWalking;

	Node						  * pSelectedNode;
	WeakPtr<CCharacter>				pCharacter;
};

