#pragma once

#include "UITitleBox.h"

class CUserInterfaceHandler : public Object
{
	URHO3D_OBJECT( CUserInterfaceHandler, Object );
public:
	//Construtor
								CUserInterfaceHandler( Context * pcContext );
	virtual					   ~CUserInterfaceHandler();

	BOOL						Init();

	void						HandleUpdate( StringHash cEventType, VariantMap & vEventData );
protected:
	SharedPtr<GUI::TitleBox>	pTitleBox;
};