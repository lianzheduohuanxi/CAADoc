// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAASysPolyline.h"

// C++ Standard library
#include "iostream.h"


//----------------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysPolyline,Implementation,CATBaseUnknown,CATNull);

//----------------------------------------------------------------------------

CAASysPolyline::CAASysPolyline()
{
  cout << "CAASysPolyline::CAASysPolyline" << endl;
}

CAASysPolyline::~CAASysPolyline()
{
  cout << "CAASysPolyline::~CAASysPolyline" << endl;
}

