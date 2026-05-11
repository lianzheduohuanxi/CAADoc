// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEVisCreateInstanceForWireBox.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAAVisWireBox.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAEVisCreateInstanceForWireBox);

// To declare that the class is a Code extension of CAAVisWireBox
//
CATImplementClass(CAAEVisCreateInstanceForWireBox, CodeExtension, CATBaseUnknown, CAAVisWireBox);
// 
// To declare that CAAEVisCreateInstanceForWireBox implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAAVisWireBox CATICreateInstance  libCAAVisWireBoxComp
//
//------------------------------------------------------------------------------------

CAAEVisCreateInstanceForWireBox::CAAEVisCreateInstanceForWireBox() 
{
  cout << "CAAEVisCreateInstanceForWireBox::CAAEVisCreateInstanceForWireBox" << endl;
}

//------------------------------------------------------------------------------------

CAAEVisCreateInstanceForWireBox::~CAAEVisCreateInstanceForWireBox()
{
  cout << "CAAEVisCreateInstanceForWireBox::~CAAEVisCreateInstanceForWireBox" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAEVisCreateInstanceForWireBox::CreateInstance(void ** oppv)
{
   CAAVisWireBox * pt = new CAAVisWireBox();
   if ( NULL == pt) return(E_OUTOFMEMORY);

   *oppv = (void *)pt;


   return(S_OK);
}







