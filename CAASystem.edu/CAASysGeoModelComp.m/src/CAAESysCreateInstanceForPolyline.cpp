// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForPolyline.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysPolyline.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForPolyline);

// To declare that the class is a Code extension of CAASysPolyline
//
CATImplementClass(CAAESysCreateInstanceForPolyline, CodeExtension, CATBaseUnknown, CAASysPolyline);
// 
// To declare that CAAESysCreateInstanceForPolyline implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysPolyline CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForPolyline::CAAESysCreateInstanceForPolyline() 
{
  cout << "CAAESysCreateInstanceForPolyline::CAAESysCreateInstanceForPolyline" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForPolyline::~CAAESysCreateInstanceForPolyline()
{
  cout << "CAAESysCreateInstanceForPolyline::~CAAESysCreateInstanceForPolyline" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForPolyline::CreateInstance(void ** oppv)
{
   CAASysPolyline * pt = new CAASysPolyline();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







