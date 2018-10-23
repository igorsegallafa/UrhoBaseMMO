#pragma once

#include "CUnit.h"

#include "PNonPlayerCharacter.h"

class CNonPlayerCharacter : public CUnit
{
	URHO3D_OBJECT( CNonPlayerCharacter, CUnit );
public:
									CNonPlayerCharacter( Context * pcContext );
								   ~CNonPlayerCharacter();
};