#pragma once

#include "ENet.h"

enum EServerType;

struct NetConnection
{
	bool				  bOriginal;
	char				  szIP[32];
	int					  iPort;
	Urho3D::SharedPtr<Urho3D::Connection> pConnection;
	EServerType			  iServerType;
	bool				  bAuthorized;
};