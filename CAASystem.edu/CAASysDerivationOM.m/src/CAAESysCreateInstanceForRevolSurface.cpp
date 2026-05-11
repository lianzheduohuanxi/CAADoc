// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForRevolSurface.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysRevolSurface.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForRevolSurface);

// To declare that the class is a Code extension of CAASysRevolSurface
//
CATImplementClass(CAAESysCreateInstanceForRevolSurface, CodeExtension, CATBaseUnknown, CAASysRevolSurface);
// 
// To declare that CAAESysCreateInstanceForRevolSurface implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysRevolSurface CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForRevolSurface::CAAESysCreateInstanceForRevolSurface() 
{
  cout << "CAAESysCreateInstanceForRevolSurface::CAAESysCreateInstanceForRevolSurface" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForRevolSurface::~CAAESysCreateInstanceForRevolSurface()
{
  cout << "CAAESysCreateInstanceForRevolSurface::~CAAESysCreateInstanceForRevolSurface" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForRevolSurface::CreateInstance(void ** oppv)
{
   CAASysRevolSurface * pt = new CAASysRevolSurface();
   if ( NULL == pt ) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







