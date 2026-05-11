// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysCylinder.h"

//C++ standard library
#include "iostream.h"

//------------------------------------------------------------------------------------

// To declare that the class is a component main class 
CATImplementClass(CAASysCylinder, Implementation, CATBaseUnknown, CATNull);

//------------------------------------------------------------------------------------

CAASysCylinder::CAASysCylinder() 
{
  cout << "CAASysCylinder::CAASysCylinder" << endl;
}

CAASysCylinder::~CAASysCylinder()
{
  cout << "CAASysCylinder::~CAASysCylinder" << endl;
}









