// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForLine.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysLine.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForLine);

// To declare that the class is a Code extension of CAASysLine
//
CATImplementClass(CAAESysCreateInstanceForLine, CodeExtension, CATBaseUnknown, CAASysLine);
// 
// To declare that CAAESysCreateInstanceForLine implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysLine CATICreateInstance  libCAASysGeoModelComp
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForLine::CAAESysCreateInstanceForLine() 
{
  cout << "CAAESysCreateInstanceForLine::CAAESysCreateInstanceForLine" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForLine::~CAAESysCreateInstanceForLine()
{
  cout << "CAAESysCreateInstanceForLine::~CAAESysCreateInstanceForLine" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForLine::CreateInstance(void ** oppv)
{
   CAASysLine * pt = new CAASysLine();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







