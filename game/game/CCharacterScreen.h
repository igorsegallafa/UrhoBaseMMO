#pragma once

#include "CScreen.h"

class CCharacterScreen : public CScreen
{
	URHO3D_OBJECT( CCharacterScreen, CScreen );
public:
	//Construtor
							CCharacterScreen( Context * pcContext );
	virtual				   ~CCharacterScreen();
private:
	void					CreateScene();
	void					CreateUserInterface();

	void					SetupViewport();

	void					HandleNewCharacterPressed( StringHash cEventType, VariantMap & vEventData );
protected:
	virtual void			Init();
};