// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForGeomRootObj.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysGeomRootObj.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForGeomRootObj);

// To declare that the class is a Code extension of CAASysGeomRootObj
//
CATImplementClass(CAAESysCreateInstanceForGeomRootObj, CodeExtension, CATBaseUnknown, CAASysGeomRootObj);
// 
// To declare that CAAESysCreateInstanceForGeomRootObj implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysGeomRootObj CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForGeomRootObj::CAAESysCreateInstanceForGeomRootObj() 
{
  cout << "CAAESysCreateInstanceForGeomRootObj::CAAESysCreateInstanceForGeomRootObj" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForGeomRootObj::~CAAESysCreateInstanceForGeomRootObj()
{
  cout << "CAAESysCreateInstanceForGeomRootObj::~CAAESysCreateInstanceForGeomRootObj" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForGeomRootObj::CreateInstance(void ** oppv)
{
   CAASysGeomRootObj * pt = new CAASysGeomRootObj();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







