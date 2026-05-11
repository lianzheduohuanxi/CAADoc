// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysCircle.h"

//C++ standard library
#include "iostream.h"

//------------------------------------------------------------------------------------

// To declare that the class is a component main class 
CATImplementClass(CAASysCircle, Implementation, CATBaseUnknown, CATNull);

//------------------------------------------------------------------------------------

CAASysCircle::CAASysCircle() 
{
  cout << "CAASysCircle::CAASysCircle" << endl;
}

CAASysCircle::~CAASysCircle()
{
  cout << "CAASysCircle::~CAASysCircle" << endl;
}









