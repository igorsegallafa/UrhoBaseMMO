#pragma once

#include "CScreen.h"

class CTestScreen : public CScreen
{
	URHO3D_OBJECT( CTestScreen, CScreen );
public:
	//Construtor
							CTestScreen( Context * pcContext );
	virtual				   ~CTestScreen();
protected:
	virtual void			Init();
private:
	void					CreateScene();
	void					SetupViewport();

	void					BuildWindow();

	//Read input and moves the camera
	void					MoveCamera( float fTimeStep );

	//Handle the logic update event
	void					HandleUpdate( StringHash cEventType, VariantMap & vEventData );
private:
	SharedPtr<Window>		pWindow;
	SharedPtr<Node>			pCameraNode;
};