// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForSimpleMessage.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysSimpleMessage.h"

// System Framework
#include "CATErrorDef.h" 

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForSimpleMessage);

// To declare that the class is a Code extension of CAASysSimpleMessage
//
CATImplementClass(CAAESysCreateInstanceForSimpleMessage, CodeExtension, CATBaseUnknown, CAASysSimpleMessage);
// 
// To declare that CAAESysCreateInstanceForSimpleMessage implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysSimpleMessage CATICreateInstance  libCAASysBBMessage
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSimpleMessage::CAAESysCreateInstanceForSimpleMessage() 
{
  cout << "CAAESysCreateInstanceForSimpleMessage::CAAESysCreateInstanceForSimpleMessage" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForSimpleMessage::~CAAESysCreateInstanceForSimpleMessage()
{
  cout << "CAAESysCreateInstanceForSimpleMessage::~CAAESysCreateInstanceForSimpleMessage" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForSimpleMessage::CreateInstance(void ** oppv)
{
   CAASysSimpleMessage * pt = new CAASysSimpleMessage();

   if (NULL == pt) 
   {
	   return(E_OUTOFMEMORY);
   }

   *oppv = (void *)pt;


   return(S_OK);
}







