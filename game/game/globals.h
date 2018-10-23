#pragma once

#include "packet.h"

//INI
#include "INIParser.h"

//ProcSky
#include "ProcSky.h"

#include "UI.h"

#define GAME_VERSION				1000

#define RESOURCECACHE				(GetSubsystem<ResourceCache>())
#define INPUT						(GetSubsystem<Input>())
#define GRAPHICS					(GetSubsystem<Graphics>())
#define RENDERER					(GetSubsystem<Renderer>())
#define FILESYSTEM					(GetSubsystem<FileSystem>())
#define NETWORK						(GetSubsystem<Network>())
#define USERINTERFACE				(GetSubsystem<UI>())

//Urho3D Logging
#define LOGTRACE(message)			(Urho3D::Log::Write(Urho3D::LOG_TRACE, message))
#define LOGDEBUG(message)			(Urho3D::Log::Write(Urho3D::LOG_DEBUG, message))
#define LOGINFO(message)			(Urho3D::Log::Write(Urho3D::LOG_INFO, message))
#define LOGWARNING(message)			(Urho3D::Log::Write(Urho3D::LOG_WARNING, message))
#define LOGERROR(message)			(Urho3D::Log::Write(Urho3D::LOG_ERROR, message))
#define LOGRAW(message)				(Urho3D::Log::WriteRaw(message))
#define LOGTRACEF(format, ...)		(Urho3D::Log::Write(Urho3D::LOG_TRACE, Urho3D::ToString(format, ##__VA_ARGS__)))
#define LOGDEBUGF(format, ...)		(Urho3D::Log::Write(Urho3D::LOG_DEBUG, Urho3D::ToString(format, ##__VA_ARGS__)))
#define LOGINFOF(format, ...)		(Urho3D::Log::Write(Urho3D::LOG_INFO, Urho3D::ToString(format, ##__VA_ARGS__)))
#define LOGWARNINGF(format, ...)	(Urho3D::Log::Write(Urho3D::LOG_WARNING, Urho3D::ToString(format, ##__VA_ARGS__)))
#define LOGERRORF(format, ...)		(Urho3D::Log::Write(Urho3D::LOG_ERROR, Urho3D::ToString(format, ##__VA_ARGS__)))
#define LOGRAWF(format, ...)		(Urho3D::Log::WriteRaw(Urho3D::ToString(format, ##__VA_ARGS__)))