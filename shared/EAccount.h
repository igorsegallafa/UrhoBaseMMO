#pragma once

namespace Account
{
	enum ELoginStatus
	{
		LOGINSTATUS_Undefined,

		LOGINSTATUS_Failed,
		LOGINSTATUS_Successful,
		LOGINSTATUS_WrongPassword,
		LOGINSTATUS_Banned,
		LOGINSTATUS_PermanetlyBanned,
		LOGINSTATUS_Unverified,
		LOGINSTATUS_WrongVersion,
		LOGINSTATUS_DoesNotExist,
	};
}