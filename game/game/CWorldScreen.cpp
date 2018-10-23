#include "stdafx.h"
#include "CWorldScreen.h"

#include "CGame.h"

extern bool test;
extern Vector3 pos;

CWorldScreen::CWorldScreen( Context * pcContext ) : CScreen( pcContext )
{
	fCameraDistance = 100.0f;
	fCameraPitch	= 0.0f;
	fCameraYaw		= 0.0f;

	pWindowDebug	= NULL;

	bDebug			= FALSE;

	SubscribeToEvent( E_POSTRENDERUPDATE, URHO3D_HANDLER( CWorldScreen, HandlePostRenderUpdate ) );
}

CWorldScreen::~CWorldScreen()
{
}

void CWorldScreen::HandleUpdate( StringHash cEventType, VariantMap & vEventData )
{
	//Atualizar as informações de Debug
	UpdateDebug();
}

void CWorldScreen::CreateScene()
{
	XMLFile * pXMLFile = RESOURCECACHE->GetResource<XMLFile>( "Scenes/World.xml" );

	if( pXMLFile )
		pScene->LoadXML( pXMLFile->GetRoot() );

	if( pScene->GetOrCreateComponent<DynamicNavigationMesh>() )
		pScene->GetOrCreateComponent<DynamicNavigationMesh>()->Build();
}

void CWorldScreen::CreateUserInterface()
{	
	BuildDebugWindow();
}

void CWorldScreen::SetupViewport()
{
	auto * pRenderer = GetSubsystem<Renderer>();

	//Create Viewport and Set it
	SharedPtr<Viewport> pViewport( new Viewport( context_, pScene, CAMERA ) );
	pRenderer->SetViewport( 0, pViewport );
}

void CWorldScreen::BuildDebugWindow()
{
	/*pWindowDebug = pUserInterface->GetRoot()->CreateChild<Window>();
	pWindowDebug->SetPosition( 5, 5 );
	pWindowDebug->SetSize( 600, 600 );
	pWindowDebug->SetLayoutMode( LM_VERTICAL );
	pWindowDebug->SetOpacity( 0.0f );

	Text * pFPSText = pWindowDebug->CreateChild<Text>();
	pFPSText->SetName( "FPS" );
	pFPSText->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Arial.ttf" ), 10 );
	pFPSText->SetTextAlignment( HA_LEFT );
	pFPSText->SetColor( Color::WHITE );
	pFPSText->SetPosition( 5, 5 );
	pFPSText->SetText( "FPS: 0" );

	Text * pPositionText = pWindowDebug->CreateChild<Text>();
	pPositionText->SetName( "Position" );
	pPositionText->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Arial.ttf" ), 10 );
	pPositionText->SetTextAlignment( HA_LEFT );
	pPositionText->SetColor( Color::WHITE );
	pPositionText->SetPosition( 5, 5 );
	pPositionText->SetText( "Position: 0 0 0" );

	Text * pHoveredNodeText = pWindowDebug->CreateChild<Text>();
	pHoveredNodeText->SetName( "SelectedNode" );
	pHoveredNodeText->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Arial.ttf" ), 10 );
	pHoveredNodeText->SetTextAlignment( HA_LEFT );
	pHoveredNodeText->SetColor( Color::WHITE );
	pHoveredNodeText->SetPosition( 5, 5 );
	pHoveredNodeText->SetText( "Selected Node: None" );

	Text * pCrowdAgentPosition = pWindowDebug->CreateChild<Text>();
	pCrowdAgentPosition->SetName( "CrowdAgentPosition" );
	pCrowdAgentPosition->SetFont( RESOURCECACHE->GetResource<Font>( "Fonts/Arial.ttf" ), 10 );
	pCrowdAgentPosition->SetTextAlignment( HA_LEFT );
	pCrowdAgentPosition->SetColor( Color::WHITE );
	pCrowdAgentPosition->SetPosition( 5, 5 );
	pCrowdAgentPosition->SetText( "Crowd Agent Reposition: 0 0 0" );*/
}

void CWorldScreen::UpdateDebug()
{
	if( (pWindowDebug && INGAME && CHARACTERGAME) && CHARACTERGAME->GetNode() )
	{
		auto * pFPSText = pWindowDebug->GetChildStaticCast<Text>( "FPS", true );
		if( pFPSText )
			pFPSText->SetText( "FPS: " + String( 1.0f / RENDERER->GetFrameInfo().timeStep_) );

		auto * pPositionText = pWindowDebug->GetChildStaticCast<Text>( "Position", true );
		if( pPositionText )
			pPositionText->SetText( "Position: " + CHARACTERGAME->GetNode()->GetPosition().ToString() );
	}
}

void CWorldScreen::HandlePostRenderUpdate( StringHash cEventType, VariantMap & vEventData )
{
	/*if( pScene )
	{
		RENDERER->DrawDebugGeometry( false );

		pScene->GetComponent<PhysicsWorld>()->DrawDebugGeometry( pScene->GetComponent<DebugRenderer>(), false );
		pScene->GetComponent<DynamicNavigationMesh>()->DrawDebugGeometry( true );
		pScene->GetComponent<CrowdManager>()->DrawDebugGeometry( true );
	}*/
}

void CWorldScreen::Init()
{
	CScreen::Init();

	//Setar a Scene na conexão com a Game Server
	if( SOCKETG )
		SOCKETG->SetScene( pScene );

	//Criar a Cena
	CreateScene();

	//Criar a UI
	CreateUserInterface();

	//Definir a Viewport
	SetupViewport();


	Node* skyNode( pScene->GetChild( "ProcSky" ) );
	if( skyNode )
	{
		ProcSky* procSky( skyNode->GetComponent<ProcSky>() );
		if( procSky )
		{
			// Can set other parameters here; e.g., SetUpdateMode(), SetUpdateInterval(), SetRenderSize()
			procSky->Initialize();
		}
		else
		{
			LOGWARNING( "ProcSky node missing ProcSky component." );
		}
	}
	else
	{
		LOGWARNING( "ProcSky node not found in scene." );
	}

	//Enviar para o servidor que o personagem foi selecionado e já pode carregar a Cena
	ACCOUNTHANDLER->ProcessSelectCharacter();
}