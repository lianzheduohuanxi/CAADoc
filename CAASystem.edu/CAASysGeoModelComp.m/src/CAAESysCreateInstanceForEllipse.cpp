// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForEllipse.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysEllipse.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForEllipse);

// To declare that the class is a Code extension of CAASysEllipse
//
CATImplementClass(CAAESysCreateInstanceForEllipse, CodeExtension, CATBaseUnknown, CAASysEllipse);
// 
// To declare that CAAESysCreateInstanceForEllipse implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysEllipse CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForEllipse::CAAESysCreateInstanceForEllipse() 
{
  cout << "CAAESysCreateInstanceForEllipse::CAAESysCreateInstanceForEllipse" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForEllipse::~CAAESysCreateInstanceForEllipse()
{
  cout << "CAAESysCreateInstanceForEllipse::~CAAESysCreateInstanceForEllipse" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForEllipse::CreateInstance(void ** oppv)
{
   CAASysEllipse * pt = new CAASysEllipse();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







