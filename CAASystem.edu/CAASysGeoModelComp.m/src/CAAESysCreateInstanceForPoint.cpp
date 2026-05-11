// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForPoint.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysPoint.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForPoint);

// To declare that the class is a Code extension of CAASysPoint
//
CATImplementClass(CAAESysCreateInstanceForPoint, CodeExtension, CATBaseUnknown, CAASysPoint);
// 
// To declare that CAAESysCreateInstanceForPoint implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysPoint CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForPoint::CAAESysCreateInstanceForPoint() 
{
  cout << "CAAESysCreateInstanceForPoint::CAAESysCreateInstanceForPoint" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForPoint::~CAAESysCreateInstanceForPoint()
{
  cout << "CAAESysCreateInstanceForPoint::~CAAESysCreateInstanceForPoint" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForPoint::CreateInstance(void ** oppv)
{
   CAASysPoint * pt = new CAASysPoint();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







