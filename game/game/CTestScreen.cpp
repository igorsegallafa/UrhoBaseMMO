#include "stdafx.h"
#include "CTestScreen.h"

#include "CGame.h"

CTestScreen::CTestScreen( Context * pcContext ) : CScreen( pcContext )
{
	Init();
}

CTestScreen::~CTestScreen()
{
}

void CTestScreen::Init()
{
	CScreen::Init();

	//Create Scene
	CreateScene();

	//Setup Viewport
	SetupViewport();

	//Build Window
	BuildWindow();

	//Subscribe HandleUpdate() function for processing update events
	SubscribeToEvent( E_UPDATE, URHO3D_HANDLER( CTestScreen, HandleUpdate ) );
}

void CTestScreen::CreateScene()
{
}

void CTestScreen::SetupViewport()
{
}

void CTestScreen::BuildWindow()
{
}

void CTestScreen::MoveCamera( float fTimeStep )
{
	auto * pInput = GetSubsystem<Input>();
	pInput->SetMouseMode(MM_ABSOLUTE, true);

	//Movement speed as world units per second
	const float MOVE_SPEED = 500.0f;

	//Mouse sensitivity as degrees per pixel
	const float MOUSE_SENSITIVITY = 0.1f;

	//Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
	IntVector2 mouseMove = pInput->GetMouseMove();
	float yaw_ = pCameraNode->GetRotation().YawAngle() + MOUSE_SENSITIVITY * mouseMove.x_;
	float pitch_ = pCameraNode->GetRotation().PitchAngle() + MOUSE_SENSITIVITY * mouseMove.y_;
	pitch_ = Clamp( pitch_, -90.0f, 90.0f );

	//Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
	pCameraNode->SetRotation( Quaternion( pitch_, yaw_, 0.0f ) );

	//Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
	if( pInput->GetKeyDown( KEY_W ) )
		pCameraNode->Translate( Vector3::FORWARD * MOVE_SPEED * fTimeStep );
	if( pInput->GetKeyDown( KEY_S ) )
		pCameraNode->Translate( Vector3::BACK * MOVE_SPEED * fTimeStep );
	if( pInput->GetKeyDown( KEY_A ) )
		pCameraNode->Translate( Vector3::LEFT * MOVE_SPEED * fTimeStep );
	if( pInput->GetKeyDown( KEY_D ) )
		pCameraNode->Translate( Vector3::RIGHT * MOVE_SPEED * fTimeStep );
}

void CTestScreen::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	//Take the frame time step, which is stored as a float
	float fTimeStep = vEventData[Update::P_TIMESTEP].GetFloat();

	MoveCamera( fTimeStep );
}