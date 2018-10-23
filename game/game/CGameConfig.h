#pragma once

#define MAX_SERVERINFO		5

struct Config
{
	struct ServerInfo
	{
							ServerInfo() = default;
							ServerInfo( String _strName, String _strIP, int _iPort ){ strName = _strName; strIP = _strIP; iPort = _iPort; }

		String				strName;
		String				strIP;
		int					iPort;
	};

	int						iTotalServers;
	ServerInfo				saServerInfo[MAX_SERVERINFO];

	int						iWindowWidth;
	int						iWindowHeight;
	BOOL					bWindowed;

	const ServerInfo	  * GetServerInfo( int iServerIndex ) const{ return saServerInfo + iServerIndex; }
};

class CGameConfig : public Object
{
	URHO3D_OBJECT( CGameConfig, Object );
public:
	//Construtor
							CGameConfig( Context * pcContext, std::string strFile );
						   ~CGameConfig();

	//Ler e Escrever configurações do Game
	BOOL					Read();
	void					Write();

	//Getters and Setters
	Config				  & Get() { return sConfig; }
	void					Set( Config sNewConfig ){ sConfig = sNewConfig; }
private:
	std::string				strFilePath;

	Config					sConfig;
};

