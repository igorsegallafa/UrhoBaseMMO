#pragma once

#include "CScreen.h"

class CWorldScreen : public CScreen
{
	URHO3D_OBJECT( CWorldScreen, CScreen );
public:
	//Construtor
							CWorldScreen( Context * pcContext );
	virtual				   ~CWorldScreen();

	void					HandleUpdate( StringHash cEventType, VariantMap & vEventData );
private:
	void					CreateScene();
	void					CreateUserInterface();

	void					SetupViewport();

	void					BuildDebugWindow();
	void					UpdateDebug();

	void					HandlePostRenderUpdate( StringHash cEventType, VariantMap & vEventData );
protected:
	virtual void			Init();
private:
	//Camera Properties
	float					fCameraDistance;
	float					fCameraPitch;
	float					fCameraYaw;

	Window				  * pWindowDebug;

	BOOL					bDebug;
};