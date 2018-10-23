#pragma once

enum EMapID
{
	MAPID_Unknown	= -1,

	MAPID_Test,
};

enum EMapType
{
	MAPTYPE_Unknown				= 0x0000, //0
	MAPTYPE_Town				= 0x0100, //256
	MAPTYPE_Forest				= 0x0200, //512
	MAPTYPE_Desert				= 0x0300, //768
	MAPTYPE_Wasteland			= 0x0400, //1024
	MAPTYPE_Dungeon				= 0x0500, //1280
	MAPTYPE_Iron				= 0x0600, //1536
	MAPTYPE_ChessRoom			= 0x0800, //2048
	MAPTYPE_Ice					= 0x0900, //2304
	MAPTYPE_BlessCastle			= 0x0A00, //2560
	MAPTYPE_Flat				= 0x0B00, //2816
	MAPTYPE_BattleTown			= 0x0C00, //3072
};