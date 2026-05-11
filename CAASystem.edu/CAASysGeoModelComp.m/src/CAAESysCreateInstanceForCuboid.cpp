// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForCuboid.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysCuboid.h"

//System Framework
#include "CATErrorDef.h"

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForCuboid);

// To declare that the class is a Code extension of CAASysCuboid
//
CATImplementClass(CAAESysCreateInstanceForCuboid, CodeExtension, CATBaseUnknown, CAASysCuboid);
// 
// To declare that CAAESysCreateInstanceForCuboid implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysCuboid CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForCuboid::CAAESysCreateInstanceForCuboid() 
{
  cout << "CAAESysCreateInstanceForCuboid::CAAESysCreateInstanceForCuboid" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForCuboid::~CAAESysCreateInstanceForCuboid()
{
  cout << "CAAESysCreateInstanceForCuboid::~CAAESysCreateInstanceForCuboid" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForCuboid::CreateInstance(void ** oppv)
{
   CAASysCuboid * pt = new CAASysCuboid();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







