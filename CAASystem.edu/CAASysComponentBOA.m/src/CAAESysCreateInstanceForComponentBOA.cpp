// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework
#include "CAAESysCreateInstanceForComponentBOA.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysComponentBOA.h"

// System Framework
#include "CATErrorDef.h"

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForComponentBOA);

//-----------------------------------------------------------------------------------
// To declare that the class is a Code extension of CAASysComponent
CATImplementClass(CAAESysCreateInstanceForComponentBOA, CodeExtension, CATBaseUnknown, CAASysComponentBOA);

//-----------------------------------------------------------------------------------
// To declare that CAAESysCreateInstanceForComponent implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysComponentBOA CATICreateInstance libCAASysComponentBOA
//

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForComponentBOA::CAAESysCreateInstanceForComponentBOA() 
{
  cout << "CAAESysCreateInstanceForComponentBOA::CAAESysCreateInstanceForComponentBOA" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForComponentBOA::~CAAESysCreateInstanceForComponentBOA()
{
  cout << "CAAESysCreateInstanceForComponentBOA::~CAAESysCreateInstanceForComponentBOA" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForComponentBOA::CreateInstance(void ** oppv)
{
   CAASysComponentBOA *pt = new CAASysComponentBOA();
   if (NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;

   return(S_OK);
}
