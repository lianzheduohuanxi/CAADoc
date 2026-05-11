// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForGeomCont.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysGeomCont.h"

// System Framework
#include <CATErrorDef.h>


//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForGeomCont);

// To declare that the class is a Code extension of CAASysGeomCont
//
CATImplementClass(CAAESysCreateInstanceForGeomCont, CodeExtension, CATBaseUnknown, CAASysGeomCont);
// 
// To declare that CAAESysCreateInstanceForGeomCont implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysGeomCont CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForGeomCont::CAAESysCreateInstanceForGeomCont() 
{
  cout << "CAAESysCreateInstanceForGeomCont::CAAESysCreateInstanceForGeomCont" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForGeomCont::~CAAESysCreateInstanceForGeomCont()
{
  cout << "CAAESysCreateInstanceForGeomCont::~CAAESysCreateInstanceForGeomCont" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForGeomCont::CreateInstance(void ** oppv)
{
   CAASysGeomCont * pt = new CAASysGeomCont();
   if (NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







