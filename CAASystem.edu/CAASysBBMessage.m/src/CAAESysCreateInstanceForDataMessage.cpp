// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCreateInstanceForDataMessage.h"

//C++ standard library
#include "iostream.h"

// The class to create
#include "CAASysDataMessage.h"

// System Framework
#include "CATErrorDef.h" 

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForDataMessage);

// To declare that the class is a Code extension of CAASysDataMessage
//
CATImplementClass(CAAESysCreateInstanceForDataMessage, CodeExtension, CATBaseUnknown, CAASysDataMessage);
// 
// To declare that CAAESysCreateInstanceForDataMessage implements CATICreateInstance, insert 
// the following line in the interface dictionary:
//
//    CAASysDataMessage CATICreateInstance  libCAASysBBMessage
//
//------------------------------------------------------------------------------------

CAAESysCreateInstanceForDataMessage::CAAESysCreateInstanceForDataMessage() 
{
  cout << "CAAESysCreateInstanceForDataMessage::CAAESysCreateInstanceForDataMessage" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCreateInstanceForDataMessage::~CAAESysCreateInstanceForDataMessage()
{
  cout << "CAAESysCreateInstanceForDataMessage::~CAAESysCreateInstanceForDataMessage" << endl;
}

//------------------------------------------------------------------------------------

HRESULT __stdcall CAAESysCreateInstanceForDataMessage::CreateInstance(void ** oppv)
{
   CAASysDataMessage * pt = new CAASysDataMessage();

   if (NULL == pt) 
   {
	   return(E_OUTOFMEMORY);
   }

   *oppv = (void *)pt;


   return(S_OK);
}







