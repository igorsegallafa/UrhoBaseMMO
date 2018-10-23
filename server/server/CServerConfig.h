#pragma once

#define MAX_SERVERINFO		5

enum EServerType
{
	SERVERTYPE_Unknown		= 0,
	SERVERTYPE_Login		= 1,
	SERVERTYPE_Game			= 2,
	SERVERTYPE_Multi		= 3,
};

struct Config
{
							Config() = default;

	struct ServerInfo
	{
							ServerInfo() = default;
							ServerInfo( EServerType _eType, std::string _strName, std::string _strIP, int _iPort ){ eType = _eType; strName.AppendWithFormat("%s",_strName.c_str()); strIP.AppendWithFormat("%s",_strIP.c_str()); iPort = _iPort; }

		EServerType			eType;
		String				strName;
		String				strIP;
		int					iPort;
	};

	int						iServerInfoID;
	int						iTotalServers;
	ServerInfo				saServerInfo[MAX_SERVERINFO];

	const ServerInfo	  * GetServerInfo() const{ return saServerInfo + iServerInfoID; }
};

class CServerConfig : public Object
{
	URHO3D_OBJECT( CServerConfig, Object );
public:
	//Construtor
							CServerConfig( Context * pcContext, std::string strFile );
						   ~CServerConfig();

	//Ler e Escrever as configurações do Servidor
	BOOL					Read();
	void					Write();

	//Getters and Setters
	const Config		  & Get() const{ return sConfig; }
	void					Set( Config sNewConfig ){ sConfig = sNewConfig; }
private:
	std::string				strFilePath;

	Config					sConfig;
};

