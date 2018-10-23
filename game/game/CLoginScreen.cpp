#include "stdafx.h"
#include "CLoginScreen.h"

#include "CGame.h"

CLoginScreen::CLoginScreen( Context * pcContext ) : CScreen( pcContext )
{
	pWindow = NULL;
}

CLoginScreen::~CLoginScreen()
{
}

void CLoginScreen::Init()
{
	CScreen::Init();

	//Criar a Cena
	CreateScene();

	//Criar a UI
	CreateUserInterface();

	//Definir a Viewport
	SetupViewport();
}

void CLoginScreen::SetGameServerList( Vector<String> vGameServerList )
{
	UIElement * pGameServerList = pWindow->GetChildStaticCast<UIElement>( "GameServerList", true );
	UIElement * pLoginInput = pWindow->GetChildStaticCast<UIElement>( "LoginInput", true );
	if( pGameServerList && pLoginInput )
	{
		pGameServerList->RemoveAllChildren();

		Text * pSelectServerText = new Text( context_ );
		pSelectServerText->SetText( "Selecione um Servidor" );
		pSelectServerText->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Anonymous Pro.ttf" ), 12 );
		pSelectServerText->SetColor( Color::WHITE );
		pSelectServerText->SetPosition( 0, 0 );
		pSelectServerText->SetTextEffect( TextEffect::TE_STROKE );
		pSelectServerText->SetAlignment( HA_CENTER, VA_TOP );
		pGameServerList->AddChild( pSelectServerText );

		int iTotalServers = 0;
		for( const auto pServerName : vGameServerList )
		{
			Button * pTextButton = new Button( context_ );
			pTextButton->SetAlignment( HA_CENTER, VA_TOP );
			pTextButton->SetSize( 150, 20 );
			pTextButton->SetPosition( 0, 50 + (30 * iTotalServers) );
			pTextButton->SetStyleAuto();
			pGameServerList->AddChild( pTextButton );
			SubscribeToEvent( pTextButton, E_PRESSED, std::bind( &CLoginScreen::HandleGameServerPressed, this, iTotalServers )  );

			Text * pServerText = new Text( context_ );
			pServerText->SetText( pServerName );
			pServerText->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Anonymous Pro.ttf" ), 12 );
			pServerText->SetColor( Color::WHITE );
			pServerText->SetPosition( 0, 50 + (30 * iTotalServers));
			pServerText->SetTextEffect( TextEffect::TE_SHADOW );
			pServerText->SetAlignment( HA_CENTER, VA_TOP );
			pGameServerList->AddChild( pServerText );

			iTotalServers++;
		}

		pLoginInput->SetVisible( false );
		pGameServerList->SetVisible( true );
	}
}

void CLoginScreen::CreateScene()
{
	XMLFile * pXMLFile = RESOURCECACHE->GetResource<XMLFile>( "Scenes/Login.xml" );

	if( pXMLFile )
		pScene->LoadXML( pXMLFile->GetRoot() );
}

void CLoginScreen::CreateUserInterface()
{
	auto * pStyle = RESOURCECACHE->GetResource<XMLFile>( "UI/DefaultStyle.xml" );

	//Carregar a janela do XML
	pWindow = USERINTERFACE->LoadLayout( RESOURCECACHE->GetResource<XMLFile>( "UI/Login.xml" ), pStyle );

	//Registrar os Eventos dos botões
	Button * pLoginButton = pWindow->GetChildStaticCast<Button>( "ButtonLogin", true );
	if( pLoginButton )
		SubscribeToEvent( pLoginButton, E_RELEASED, URHO3D_HANDLER( CLoginScreen, HandleLoginPressed ) );

	//Adicionar a janela à User Interface do jogo
	USERINTERFACE->GetRoot()->AddChild( pWindow );
}

void CLoginScreen::SetupViewport()
{
	auto * pRenderer = GetSubsystem<Renderer>();

	//Create Viewport and Set it
	SharedPtr<Viewport> pViewport( new Viewport( context_, pScene, CAMERA ) );
	pRenderer->SetViewport( 0, pViewport );
}

void CLoginScreen::HandleGameServerPressed( int iServerIndex )
{
	if( iServerIndex >= 0 && iServerIndex < GAMECONFIG->Get().iTotalServers )
	{
		const Config::ServerInfo * psServerInfo = GAMECONFIG->Get().GetServerInfo( iServerIndex );
		ACCOUNTHANDLER->ProcessSelectGameServer( psServerInfo );
	}
}

void CLoginScreen::HandleLoginPressed( StringHash cEventType, VariantMap & vEventData )
{
	LineEdit * pLineEditAccount = pWindow->GetChildStaticCast<LineEdit>( "LineEditAccount", true );
	LineEdit * pLineEditPassword = pWindow->GetChildStaticCast<LineEdit>( "LineEditPassword", true );

	if( pLineEditAccount && pLineEditPassword )
	{
		ACCOUNTHANDLER->ProcessAccountLogin( pLineEditAccount->GetText(), pLineEditPassword->GetText() );
	}
}