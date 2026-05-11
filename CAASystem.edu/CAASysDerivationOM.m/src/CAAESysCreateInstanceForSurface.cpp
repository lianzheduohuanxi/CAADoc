// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForSurface.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysSurface.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForSurface);

// To declare that the class is a Code extension of CAASysSurface
//
CATImplementClass(CAAESysCreateInstanceForSurface, CodeExtension, CATBaseUnknown, CAASysSurface);
// 
// To declare that CAAESysCreateInstanceForSurface implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysSurface CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSurface::CAAESysCreateInstanceForSurface() 
{
  cout << "CAAESysCreateInstanceForSurface::CAAESysCreateInstanceForSurface" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSurface::~CAAESysCreateInstanceForSurface()
{
  cout << "CAAESysCreateInstanceForSurface::~CAAESysCreateInstanceForSurface" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForSurface::CreateInstance(void ** oppv)
{
   CAASysSurface * pt = new CAASysSurface();
   if (NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;

   return(S_OK);
}







