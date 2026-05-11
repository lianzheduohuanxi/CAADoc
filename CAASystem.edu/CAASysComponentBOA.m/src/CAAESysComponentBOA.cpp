// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework
#include "CAAESysComponentBOA.h"

//C++ standard library
#include "iostream.h"

//------------------------------------------------------------------------------------
// To declare that the class CAAESysComponentBOA is a component implementing CAAISysInterface
// as a data extension of the component CAASysComponentBOA
CATImplementClass(CAAESysComponentBOA, DataExtension, CAAISysInterface, CAASysComponentBOA);

//------------------------------------------------------------------------------------
// To declare that CAASysComponent implements CAAISysInterface, insert 
// the following line in the interface dictionary:
//
//    CAASysComponentBOA CAAISysInterface  libCAASysComponentBOA
//

//------------------------------------------------------------------------------------
// To declare that the class is a BOA
//
CATImplementBOA(CAAISysInterface,CAAESysComponentBOA);

CAAESysComponentBOA::CAAESysComponentBOA() 
{
  cout << "CAAESysComponentBOA::CAAESysComponentBOA" << endl;
}

//------------------------------------------------------------------------------------

CAAESysComponentBOA::~CAAESysComponentBOA()
{
  cout << "CAAESysComponentBOA::~CAAESysComponentBOA" << endl;
}

//------------------------------------------------------------------------------------

HRESULT CAAESysComponentBOA::ToString()
{
   cout << "CAAESysComponentBOA::ToString"<< endl; 
   return(S_OK);
}
