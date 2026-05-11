// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAASysSurface.h"

// C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------
// To declare that the class is a component main class 
//
CATImplementClass(CAASysSurface, Implementation, CATBaseUnknown, CATNull);
//
//-----------------------------------------------------------------------------


CAASysSurface::CAASysSurface() 
{
  cout << "Constructs a CAASysSurface" << endl;
}

CAASysSurface::~CAASysSurface()
{
  cout << "Deletes a CAASysSurface" << endl;
}






