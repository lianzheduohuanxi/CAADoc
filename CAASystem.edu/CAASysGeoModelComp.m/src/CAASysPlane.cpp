// COPYRIGHT DASSAULT SYSTEMES 1999

//LocalFramework
#include "CAASysPlane.h"

//C++ Standard library
#include "iostream.h"


//---------------------------------------------------------------------------

// To declare that the class is a component main class
//
CATImplementClass(CAASysPlane, Implementation, CATBaseUnknown, CATNull);

//---------------------------------------------------------------------------

CAASysPlane::CAASysPlane() 
{
  cout << "CAASysPlane::CAASysPlane" << endl;
}

CAASysPlane::~CAASysPlane()
{
  cout << "CAASysPlane::~CAASysPlane" << endl;
}
