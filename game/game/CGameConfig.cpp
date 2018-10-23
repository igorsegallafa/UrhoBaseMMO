#include "stdafx.h"
#include "CGameConfig.h"

CGameConfig::CGameConfig( Context * pcContext, std::string strFile ) : Object( pcContext ), strFilePath( strFile )
{
	ZeroMemory( &sConfig, sizeof( Config ) );
}

CGameConfig::~CGameConfig()
{
}

BOOL CGameConfig::Read()
{
	auto pConfigFile = RESOURCECACHE->GetResource<INI::Parser>( "game.ini" );
	if( pConfigFile )
	{
		//Configurações de Tela
		sConfig.iWindowWidth = pConfigFile->GetInt( "Screen", "Width", 1024 );
		sConfig.iWindowHeight = pConfigFile->GetInt( "Screen", "Height", 768 );
		sConfig.bWindowed = pConfigFile->GetBool( "Screen", "Windowed", TRUE );

		return TRUE;
	}

	return FALSE;
}

void CGameConfig::Write()
{
}
