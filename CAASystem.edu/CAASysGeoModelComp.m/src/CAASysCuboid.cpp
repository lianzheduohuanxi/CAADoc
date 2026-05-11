// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAASysCuboid.h"

// C++ standard library
#include <iostream.h>

//-----------------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysCuboid, Implementation, CATBaseUnknown, CATNull);
// 

//-----------------------------------------------------------------------------

CAASysCuboid::CAASysCuboid()
{
   cout << "CAASysCuboid::CAASysCuboid" << endl ;
}

//-----------------------------------------------------------------------------

CAASysCuboid::~CAASysCuboid()
{
   cout << "CAASysCuboid::~CAASysCuboid" << endl ;
}

//-----------------------------------------------------------------------------
