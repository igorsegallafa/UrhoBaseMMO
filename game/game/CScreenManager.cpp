#include "stdafx.h"
#include "CScreenManager.h"

#include "CGame.h"

CScreenManager::CScreenManager( Context * pcContext ) : Object( pcContext )
{
	pcContext->RegisterFactory<CScreenManager>( "Manager" );
	pcContext->RegisterFactory<CLoginScreen>( "Screen" );
	pcContext->RegisterFactory<CCharacterScreen>( "Screen" );
	pcContext->RegisterFactory<CTestScreen>( "Screen" );
	pcContext->RegisterFactory<CWorldScreen>( "Screen" );

	SubscribeToEvent( Screen::E_SET_SCREEN, URHO3D_HANDLER( CScreenManager, HandleSetLevelQueue ) );
	SubscribeToEvent( E_SCREENMODE, URHO3D_HANDLER( CScreenManager, HandleResolutionChange ) );
}

CScreenManager::~CScreenManager()
{
}

BOOL CScreenManager::Init()
{
	SetActiveScreen( SCREEN_Login );

	return TRUE;
}

void CScreenManager::HandlePostUpdate( StringHash cEventType, VariantMap & vEventData )
{
	if( pActiveScreen )
		pActiveScreen->HandlePostUpdate( cEventType, vEventData );
}

void CScreenManager::SetActiveScreen( EScreen eScreen )
{
	VariantMap & vEventData = GetEventDataMap();
	vEventData[Screen::E_SET_SCREEN] = eScreen;
	SendEvent( Screen::E_SET_SCREEN, vEventData );
}

void CScreenManager::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	//Recuperar o Time Step
	float fTime = vEventData[Update::P_TIMESTEP].GetFloat();

	//Move sprites, scale movement with time step
	fFadeTime -= fTime;

	//Prepare to fade out
	if( eFadeStep == FADESTEP_Prepare )
	{
		//No active screen?
		if( !pActiveScreen )
			eFadeStep = FADESTEP_Out;
		else
		{
			BuildWindow();

			if( pWindow )
				pWindow->SetOpacity( 0.0f );

			fFadeTime = MAX_FADE_TIME;
			eFadeStep = FADESTEP_Out;
		}
	}
	else if( eFadeStep == FADESTEP_Out )
	{
		//No active screen?
		if( !pActiveScreen )
			eFadeStep = FADESTEP_ReleaseScreen;
		else
		{
			pWindow->SetOpacity( 1.0f - fFadeTime / MAX_FADE_TIME );

			//Fade time its over? So go to the next step
			if( fFadeTime <= 0.0f )
				eFadeStep = FADESTEP_ReleaseScreen;
		}
	}
	else if( eFadeStep == FADESTEP_ReleaseScreen )
	{
		//No active screen?
		if( !pActiveScreen )
			eFadeStep = FADESTEP_CreateScreen;
		else
		{
			//We can not create new screen here, or it may cause errors, we have to create it at the next update point
			pActiveScreen = SharedPtr<CScreen>();
			eFadeStep = FADESTEP_CreateScreen;
		}
	}
	else if( eFadeStep == FADESTEP_CreateScreen )
	{
		//Create new Screen
		switch( pScreenQueue.Front() )
		{
			case SCREEN_World:
				pActiveScreen = new CWorldScreen( context_ );
				break;
			case SCREEN_Test:
				pActiveScreen = new CTestScreen( context_ );
				break;
			case SCREEN_Login:
				pActiveScreen = new CLoginScreen( context_ );
				break;
			case SCREEN_Character:
				pActiveScreen = new CCharacterScreen( context_ );
				break;
		}

		pActiveScreen->Init();

		eActiveScreen = (EScreen)pScreenQueue.Front();

		//Remove the old fade layer
		if( pWindow )
			pWindow->Remove();

		//Add a new fade layer
		BuildWindow();

		if( pWindow )
			pWindow->SetOpacity( 1.0f );

		fFadeTime = MAX_FADE_TIME;
		eFadeStep = FADESTEP_In;
	}
	else if( eFadeStep == FADESTEP_In )
	{
		if( pWindow )
			pWindow->SetOpacity( fFadeTime / MAX_FADE_TIME );

		//Fade time its over? So go to the next step
		if( fFadeTime <= 0.0f )
			eFadeStep = FADESTEP_Finished;
	}
	else if( eFadeStep == FADESTEP_Finished )
	{
		//Remove fade layer
		if( pWindow )
		{
			pWindow->Remove();
			pWindow = SharedPtr<Window>();
		}

		//Unsubscribe update event
		UnsubscribeFromEvent( E_UPDATE );

		//Remove the task
		pScreenQueue.PopFront();

		//Release all unused resources
		RESOURCECACHE->ReleaseAllResources( false );
	}

	if( pActiveScreen )
		pActiveScreen->HandleUpdate( cEventType, vEventData );
}

void CScreenManager::HandleSetLevelQueue( StringHash eventType, VariantMap & eventData )
{
	//Busy now
	if( pScreenQueue.Size() )
		return;

	//Push to queue
	pScreenQueue.Push( eventData[Screen::E_SET_SCREEN].GetInt() );

	//Init fade status
	eFadeStep = FADESTEP_Prepare;
}

void CScreenManager::HandleResolutionChange( StringHash cEventType, VariantMap & vEventData )
{
}

void CScreenManager::BuildWindow()
{
	pWindow = new Window( context_ );

	//Make the window and setup it
	GetSubsystem<UI>()->GetRoot()->AddChild( pWindow );
	pWindow->SetSize( GetSubsystem<Graphics>()->GetWidth(), GetSubsystem<Graphics>()->GetHeight() );
	pWindow->SetLayout( LM_FREE );
	pWindow->SetAlignment( HA_CENTER, VA_CENTER );
	pWindow->SetColor( Color( 0.0f, 0.0f, 0.0f, 1.0f ) );
	pWindow->BringToFront();
}