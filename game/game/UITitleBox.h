#pragma once

namespace GUI
{
class TitleBox : public Object
{
	URHO3D_OBJECT( TitleBox, Object );
public:
	//Construtor
									TitleBox( Context * pcContext );
	virtual						   ~TitleBox();

	BOOL							Init();

	void							HandleUpdate( StringHash cEventType, VariantMap & vEventData );
private:
	void							BuildWindow1();
};
}