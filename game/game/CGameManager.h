#pragma once

#include "CScreenManager.h"
#include "CCameraManager.h"

#define SCREENMANAGER			(GAMEMANAGER->GetScreenManager())
#define CAMERAMANAGER			(GAMEMANAGER->GetCameraManager())

class CGameManager : public Object
{
	URHO3D_OBJECT( CGameManager, Object );
public:
	//Construtor
								CGameManager( Context * pcContext );
	virtual					   ~CGameManager();

	BOOL						Init();

	//Eventos Registrados
	void						HandleUpdate( StringHash cEventType, VariantMap & vEventData );
	void						HandlePostUpdate( StringHash cEventType, VariantMap & vEventData );
	void						HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData );

	//Getters
	SharedPtr<CScreenManager>	GetScreenManager(){ return pScreenManager; }
	SharedPtr<CCameraManager>	GetCameraManager(){ return pCameraManager; }
protected:
	SharedPtr<CScreenManager>	pScreenManager;
	SharedPtr<CCameraManager>	pCameraManager;
};