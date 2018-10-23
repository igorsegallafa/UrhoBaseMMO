#include "stdafx.h"
#include "CCharacterScreen.h"

#include "CGame.h"

CCharacterScreen::CCharacterScreen( Context * pcContext ) : CScreen( pcContext )
{
}

CCharacterScreen::~CCharacterScreen()
{
}

void CCharacterScreen::CreateScene()
{
	XMLFile * pXMLFile = RESOURCECACHE->GetResource<XMLFile>( "Scenes/SelectCharacter.xml" );

	if( pXMLFile )
		pScene->LoadXML( pXMLFile->GetRoot() );
}

void CCharacterScreen::CreateUserInterface()
{
	/*auto * pStyle = RESOURCECACHE->GetResource<XMLFile>( "UI/DefaultStyle.xml" );

	//Setar o Estilo Padrão para a UI
	if( pUserInterface )
		pUserInterface->SetDefaultStyle( pStyle );

	//TextBox para digitar o Nick do Char
	LineEdit * pLineEditCharacterNick = new LineEdit( context_ );
	pLineEditCharacterNick->SetPosition( 170, 20 );
	pLineEditCharacterNick->SetName( "LineEditCharacterNick" );
	pLineEditCharacterNick->SetSize( 275, 30 );
	pLineEditCharacterNick->SetStyleAuto();
	pUserInterface->AddChild( pLineEditCharacterNick );

	//Botão para Logar com o Char
	Button * pButtonTemp = new Button( context_ );
	pButtonTemp->SetName( "ButtonLogin" );
	pButtonTemp->SetSize( 140, 30 );
	pButtonTemp->SetPosition( 0, 20 );
	pButtonTemp->SetStyleAuto();
	pButtonTemp->SetAlignment( HA_CENTER, VA_TOP );
	pUserInterface->AddChild( pButtonTemp );
	SubscribeToEvent( pButtonTemp, E_RELEASED, URHO3D_HANDLER( CCharacterScreen, HandleNewCharacterPressed ) );*/
}

void CCharacterScreen::SetupViewport()
{
	auto * pRenderer = GetSubsystem<Renderer>();

	//Create Viewport and Set it
	SharedPtr<Viewport> pViewport( new Viewport( context_, pScene, CAMERA ) );
	pRenderer->SetViewport( 0, pViewport );
}

void CCharacterScreen::HandleNewCharacterPressed( StringHash cEventType, VariantMap & vEventData )
{
	/*LineEdit * pLineEditCharacterNick = pUserInterface->GetChildStaticCast<LineEdit>( "LineEditCharacterNick", true );

	if( pLineEditCharacterNick )
		ACCOUNTHANDLER->SelectCharacter( TRUE, pLineEditCharacterNick->GetText(), CHARACTERCLASS_Fighter );*/
}

void CCharacterScreen::Init()
{
	CScreen::Init();

	//Criar a Cena
	CreateScene();

	//Criar a UI
	CreateUserInterface();

	//Definir a Viewport
	SetupViewport();
}