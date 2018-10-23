#pragma once

const float MAX_FADE_TIME = 1.0f;

namespace Screen
{
	static const StringHash E_SET_SCREEN = StringHash( "Set Screen" );
}

enum EScreen
{
	SCREEN_None,

	SCREEN_Login,
	SCREEN_Character,
	SCREEN_World,
	SCREEN_Test,
};

class CScreen : public Object
{
	URHO3D_OBJECT( CScreen, Object );
public:
	//Construtor
						CScreen( Context * pcContext ) : Object( pcContext ) {}
	virtual			   ~CScreen() { Dispose(); }

	virtual void		Init();

	//Eventos Registrados
	virtual void		HandleUpdate( StringHash cEventType, VariantMap & vEventData ){};
	virtual void		HandlePostUpdate( StringHash cEventType, VariantMap & vEventData ){};
	virtual void		HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData ){};

	Scene			  * GetScene(){ return pScene; }
protected:
	virtual void		Run();
	virtual void		Pause();
	virtual void		Dispose();
protected:
	SharedPtr<Scene>	pScene;
};