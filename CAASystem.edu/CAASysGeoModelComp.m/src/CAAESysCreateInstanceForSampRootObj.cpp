// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForSampRootObj.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysSampRootObj.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForSampRootObj);

// To declare that the class is a Code extension of CAASysSampRootObj
//
CATImplementClass(CAAESysCreateInstanceForSampRootObj, CodeExtension, CATBaseUnknown, CAASysSampRootObj);
// 
// To declare that CAAESysCreateInstanceForSampRootObj implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysSampRootObj CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSampRootObj::CAAESysCreateInstanceForSampRootObj() 
{
  cout << "CAAESysCreateInstanceForSampRootObj::CAAESysCreateInstanceForSampRootObj" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSampRootObj::~CAAESysCreateInstanceForSampRootObj()
{
  cout << "CAAESysCreateInstanceForSampRootObj::~CAAESysCreateInstanceForSampRootObj" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForSampRootObj::CreateInstance(void ** oppv)
{
   CAASysSampRootObj * pt = new CAASysSampRootObj();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







