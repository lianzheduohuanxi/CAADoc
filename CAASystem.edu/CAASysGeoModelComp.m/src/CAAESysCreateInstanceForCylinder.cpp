// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForCylinder.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysCylinder.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForCylinder);

// To declare that the class is a Code extension of CAASysCylinder
//
CATImplementClass(CAAESysCreateInstanceForCylinder, CodeExtension, CATBaseUnknown, CAASysCylinder);
// 
// To declare that CAAESysCreateInstanceForCylinder implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysCylinder CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForCylinder::CAAESysCreateInstanceForCylinder() 
{
  cout << "CAAESysCreateInstanceForCylinder::CAAESysCreateInstanceForCylinder" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForCylinder::~CAAESysCreateInstanceForCylinder()
{
  cout << "CAAESysCreateInstanceForCylinder::~CAAESysCreateInstanceForCylinder" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForCylinder::CreateInstance(void ** oppv)
{
   CAASysCylinder * pt = new CAASysCylinder();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







