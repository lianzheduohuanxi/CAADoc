// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysEllipse.h"

//C++ standard library
#include "iostream.h"


//----------------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysEllipse, Implementation, CATBaseUnknown, CATNull);


//----------------------------------------------------------------------------

CAASysEllipse::CAASysEllipse() 
{
  cout << "CAASysEllipse::CAASysEllipse" << endl;
}

CAASysEllipse::~CAASysEllipse()
{
  cout << "CAASysEllipse::~CAASysEllipse" << endl;
}

