#pragma once

#include "CMap.h"

class CMapHandler : public Object
{
	URHO3D_OBJECT( CMapHandler, Object );
public:
	//Construtor
								CMapHandler( Context * pcContext );
	virtual					   ~CMapHandler();

	BOOL						Init();

	void						Load();
	void						CreateScene();

	//Getters
	Scene					  * GetScene() const{ return pScene; }

	CMap					  * GetMap( String strMapName );
	CMap					  * GetMap( EMapID iID );

	void						LoadMap( CMap * pMap );
private:
	inline void					LoadNPCs( CMap * pMap );
protected:
	SharedPtr<Scene>			pScene;
	Vector<CMap*>				vMaps;
};
