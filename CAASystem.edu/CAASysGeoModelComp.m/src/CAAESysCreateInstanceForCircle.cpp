// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForCircle.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysCircle.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForCircle);

// To declare that the class is a Code extension of CAASysCircle
//
CATImplementClass(CAAESysCreateInstanceForCircle, CodeExtension, CATBaseUnknown, CAASysCircle);
// 
// To declare that CAAESysCreateInstanceForCircle implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysCircle CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForCircle::CAAESysCreateInstanceForCircle() 
{
  cout << "CAAESysCreateInstanceForCircle::CAAESysCreateInstanceForCircle" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForCircle::~CAAESysCreateInstanceForCircle()
{
  cout << "CAAESysCreateInstanceForCircle::~CAAESysCreateInstanceForCircle" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForCircle::CreateInstance(void ** oppv)
{
   CAASysCircle * pt = new CAASysCircle();
   if (NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







