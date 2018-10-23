#include "stdafx.h"
#include "CServerConfig.h"

CServerConfig::CServerConfig( Context * pcContext, std::string strFile ) : Object( pcContext ), strFilePath( strFile )
{
	ZeroMemory( &sConfig, sizeof( Config ) );
}

CServerConfig::~CServerConfig()
{
}

BOOL CServerConfig::Read()
{
	auto pConfigFile = RESOURCECACHE->GetResource<INI::Parser>( "server.ini" );
	if( pConfigFile )
	{
		//Informações da Game Server
		{
			sConfig.iTotalServers = pConfigFile->GetInt( "Server", "GameServers" ) + 1;
			sConfig.iServerInfoID = pConfigFile->GetInt( pConfigFile->GetString( "Server", "Type" ), "ID" );

			if( sConfig.iServerInfoID >= 0 )
			{
				sConfig.saServerInfo[0] = Config::ServerInfo( SERVERTYPE_Login, pConfigFile->GetString( "LoginServer", "Name" ).CString(), pConfigFile->GetString( "LoginServer", "IP" ).CString(), pConfigFile->GetInt( "LoginServer", "Port" ) );

				for( int i = 1; i < sConfig.iTotalServers; i++ )
				{
					char szGameServer[32] = { 0 };
					StringCbPrintfA( szGameServer, _countof( szGameServer ), "GameServer%d", i );

					sConfig.saServerInfo[i] = Config::ServerInfo( SERVERTYPE_Game, pConfigFile->GetString( szGameServer, "Name" ).CString(), pConfigFile->GetString( szGameServer, "IP" ).CString(), pConfigFile->GetInt( szGameServer, "Port" ) );
				}
			}
		}

		return TRUE;
	}

	return FALSE;
}

void CServerConfig::Write()
{
}
