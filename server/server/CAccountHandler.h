#pragma once

#include "CUser.h"
#include "CAccount.h"

class CAccountHandler : public Object
{
	URHO3D_OBJECT( CAccountHandler, Object );
public:
								CAccountHandler( Context * pcContext );
	virtual					   ~CAccountHandler();

	BOOL						HandleAccountLogin( Connection * pSender, VariantMap vEventData );
};
