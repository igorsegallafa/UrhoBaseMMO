#pragma once

#include "PUnit.h"

class CUnit : public LogicComponent
{
	URHO3D_OBJECT( CUnit, LogicComponent );
public:
	explicit						CUnit( Context * pcContext );
								   ~CUnit() override;

	BOOL							Load( Scene * pScene, EUnitType eType = UNITTYPE_Undefined );

	void							SetID( int iUnitID ){ iID = iUnitID; }
	const int						GetID() const{ return iID; }

	virtual const VariantMap	    GetVariablesMap() const{ return VariantMap(); }
private:
	int								iID;
};