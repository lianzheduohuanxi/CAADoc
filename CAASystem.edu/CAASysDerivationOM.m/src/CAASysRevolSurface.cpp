// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAASysRevolSurface.h"

// C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------
// To declare that the class is a component main class which OM derives from
// the CAASysSurface component.
CATImplementClass(CAASysRevolSurface, Implementation, CAASysSurface, CATNull);
//
//-----------------------------------------------------------------------------


CAASysRevolSurface::CAASysRevolSurface() 
{
  cout << "Constructs a CAASysRevolSurface" << endl;
}

CAASysRevolSurface::~CAASysRevolSurface()
{
  cout << "Deletes a CAASysRevolSurface" << endl;
}






