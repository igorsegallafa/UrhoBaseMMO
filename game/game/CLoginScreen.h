#pragma once

#include "CScreen.h"

class CLoginScreen : public CScreen
{
	URHO3D_OBJECT( CLoginScreen, CScreen );
public:
	//Construtor
							CLoginScreen( Context * pcContext );
	virtual				   ~CLoginScreen();

	void					SetGameServerList( Vector<String> vGameServerList );
protected:
	virtual void			Init();
private:
	void					CreateScene();
	void					CreateUserInterface();

	void					SetupViewport();

	void					HandleGameServerPressed( int iServerIndex );
	void					HandleLoginPressed( StringHash cEventType, VariantMap & vEventData );
private:
	SharedPtr<UIElement>	pWindow;
};