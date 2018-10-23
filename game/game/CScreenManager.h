#pragma once

#include "CScreen.h"

#include "CLoginScreen.h"
#include "CCharacterScreen.h"
#include "CTestScreen.h"
#include "CWorldScreen.h"

#define ACTIVESCREEN			(SCREENMANAGER->GetActiveScreen())

class CScreenManager : public Object
{
	URHO3D_OBJECT( CScreenManager, Object );

	enum EFadeStep
	{
		FADESTEP_Prepare,
		FADESTEP_Out,
		FADESTEP_ReleaseScreen,
		FADESTEP_CreateScreen,
		FADESTEP_In,
		FADESTEP_Finished,
	};

public:
	//Construtor
								CScreenManager( Context * pcContext );
							   ~CScreenManager();

	BOOL						Init();

	void						HandleUpdate( StringHash cEventType, VariantMap & vEventData );
	void						HandlePostUpdate( StringHash cEventType, VariantMap & vEventData );

	CScreen					  * GetActiveScreen(){ return pActiveScreen; }
	EScreen						GetActiveScreenType(){ return eActiveScreen; }
	void						SetActiveScreen( EScreen eScreen );
private:
	void						HandleSetLevelQueue( StringHash cEventType, VariantMap & vEventData );
	void						HandleResolutionChange( StringHash cEventType, VariantMap & vEventData );

	void						BuildWindow();
private:
	List<int>					pScreenQueue;
	SharedPtr<CScreen>			pActiveScreen;

	SharedPtr<Window>			pWindow;

	float						fFadeTime;
	EFadeStep					eFadeStep;

	EScreen						eActiveScreen;
};

