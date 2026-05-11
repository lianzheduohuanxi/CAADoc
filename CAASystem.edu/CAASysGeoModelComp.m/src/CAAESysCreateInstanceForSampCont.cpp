// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForSampCont.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysSampCont.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForSampCont);

// To declare that the class is a Code extension of CAASysSampCont
//
CATImplementClass(CAAESysCreateInstanceForSampCont, CodeExtension, CATBaseUnknown, CAASysSampCont);
// 
// To declare that CAAESysCreateInstanceForSampCont implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysSampCont CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSampCont::CAAESysCreateInstanceForSampCont() 
{
  cout << "CAAESysCreateInstanceForSampCont::CAAESysCreateInstanceForSampCont" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSampCont::~CAAESysCreateInstanceForSampCont()
{
  cout << "CAAESysCreateInstanceForSampCont::~CAAESysCreateInstanceForSampCont" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForSampCont::CreateInstance(void ** oppv)
{
   CAASysSampCont * pt = new CAASysSampCont();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







