// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForComponent.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysComponent.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForComponent);

// To declare that the class is a Code extension of CAASysComponent
//
CATImplementClass(CAAESysCreateInstanceForComponent, CodeExtension, CATBaseUnknown, CAASysComponent);
// 
// To declare that CAAESysCreateInstanceForComponent implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysComponent CATICreateInstance  libCAASysComponentImpl
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForComponent::CAAESysCreateInstanceForComponent() 
{
  cout << "CAAESysCreateInstanceForComponent::CAAESysCreateInstanceForComponent" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForComponent::~CAAESysCreateInstanceForComponent()
{
  cout << "CAAESysCreateInstanceForComponent::~CAAESysCreateInstanceForComponent" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForComponent::CreateInstance(void ** oppv)
{
   CAASysComponent * pt = new CAASysComponent();
   if (NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







