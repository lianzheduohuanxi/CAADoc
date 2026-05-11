// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAASysPoint.h"

// C++ standard library
#include <iostream.h>

//-----------------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysPoint, Implementation, CATBaseUnknown, CATNull);
// 

//-----------------------------------------------------------------------------

CAASysPoint::CAASysPoint()
{
   cout << "CAASysPoint::CAASysPoint" << endl ;
}

//-----------------------------------------------------------------------------

CAASysPoint::~CAASysPoint()
{
   cout << "CAASysPoint::~CAASysPoint" << endl ;
}

//-----------------------------------------------------------------------------
