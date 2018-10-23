#include "stdafx.h"
#include "DatabaseSubArray.h"

#include "DatabaseKey.h"

namespace Database
{
void SubArray::AppendValue( Key & sKey )
{
	cArray.append( sKey.Documentation().doc );
}

void SubArray::AppendValue( Key && sKey )
{
	cArray.append( sKey.Documentation().doc );
}
}