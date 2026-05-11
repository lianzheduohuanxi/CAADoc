// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework
#include "CAASysComponentBOA.h"

//C++ standard library
#include "iostream.h"

CATImplementClass(CAASysComponentBOA, Implementation, CATBaseUnknown, CATNull);

CAASysComponentBOA::CAASysComponentBOA() 
{
  cout << "CAASysComponentBOA::CAASysComponentBOA" << endl;
}

//------------------------------------------------------------------------------------

CAASysComponentBOA::~CAASysComponentBOA()
{
  cout << "CAASysComponentBOA::~CAASysComponentBOA" << endl;
}
