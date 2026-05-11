// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForPlane.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysPlane.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForPlane);

// To declare that the class is a Code extension of CAASysPlane
//
CATImplementClass(CAAESysCreateInstanceForPlane, CodeExtension, CATBaseUnknown, CAASysPlane);
// 
// To declare that CAAESysCreateInstanceForPlane implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysPlane CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForPlane::CAAESysCreateInstanceForPlane() 
{
  cout << "CAAESysCreateInstanceForPlane::CAAESysCreateInstanceForPlane" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForPlane::~CAAESysCreateInstanceForPlane()
{
  cout << "CAAESysCreateInstanceForPlane::~CAAESysCreateInstanceForPlane" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForPlane::CreateInstance(void ** oppv)
{
   CAASysPlane * pt = new CAASysPlane();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







