#pragma once

enum EPKTHDR
{
	PKTHDR_Undefined			= 22,

	PKTHDR_LoginConnect,
	PKTHDR_GameServerData,

	PKTHDR_SelectCharacter,
	PKTHDR_CharacterSync,		//Client
};

enum ENETPKTHDR
{
	NETPKTHDR_None				= 10000,

	NETPKTHDR_NetPassword,
	NETPKTHDR_NetSource,
	NETPKTHDR_NetKeepAlive,
};