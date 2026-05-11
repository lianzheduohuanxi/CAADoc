// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysLine.h"

//C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------

// To declare that the class is a component main class 
//
CATImplementClass(CAASysLine, Implementation, CATBaseUnknown, CATNull);

//----------------------------------------------------------------------------

CAASysLine::CAASysLine() 
{
  cout << "CAASysLine::CAASysLine" << endl;
}

CAASysLine::~CAASysLine()
{
  cout << "CAASysLine::~CAASysLine" << endl;
}

