// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEDlgCreateInstanceForEditorMessage.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAADlgBBEditorMessage.h"

// System Framework
#include <CATErrorDef.h>

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAEDlgCreateInstanceForEditorMessage);

// To declare that the class is a Code extension of CAADlgBBEditorMessage
//
CATImplementClass(CAAEDlgCreateInstanceForEditorMessage, CodeExtension, CATBaseUnknown, CAADlgBBEditorMessage);
// 
// To declare that CAAEDlgCreateInstanceForEditorMessage implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAADlgBBEditorMessage CATICreateInstance  libCAADlgBBMessage
//
//------------------------------------------------------------------------------------

CAAEDlgCreateInstanceForEditorMessage::CAAEDlgCreateInstanceForEditorMessage() 
{
  cout << "CAAEDlgCreateInstanceForEditorMessage::CAAEDlgCreateInstanceForEditorMessage" << endl;
}

//------------------------------------------------------------------------------------

CAAEDlgCreateInstanceForEditorMessage::~CAAEDlgCreateInstanceForEditorMessage()
{
  cout << "CAAEDlgCreateInstanceForEditorMessage::~CAAEDlgCreateInstanceForEditorMessage" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAEDlgCreateInstanceForEditorMessage::CreateInstance(void ** oppv)
{
   CAADlgBBEditorMessage * pt = new CAADlgBBEditorMessage();
   
   if (NULL == pt) 
   {
      return(E_OUTOFMEMORY);
   }

   *oppv = (void *)pt;

   return(S_OK);
}







