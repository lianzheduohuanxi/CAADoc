// COPYRIGHT DASSAULT SYSTEMES 2000	

#include  "CAASysSimpleMessage.h"

//C++ Standard library
#include <iostream.h>       

// System Framework
#include "CATICommMsg.h" // To specifies the message
#include <CATErrorDef.h> // for SUCCEEDED macro

//---------------------------------------------------------------------------

// To create the TIE object
#include "TIE_CATIStreamMsg.h"
TIE_CATIStreamMsg(CAASysSimpleMessage);

// To declare that the class is a component main class which OM derives from
// the CATBBMessage component
//
CATImplementClass(CAASysSimpleMessage, Implementation, CATBBMessage, CATNull);

// 
// To declare that CAASysSimpleMessage implements CATIStreamMsg 
// insert the following line in the interface dictionary:
//
//    CAASysSimpleMessage  CATIStreamMsg     libCAASysBBMessage
//
//---------------------------------------------------------------------------

CAASysSimpleMessage::CAASysSimpleMessage()
{
   cout << "CAASysSimpleMessage::CAASysSimpleMessage()"<< endl;
}

//---------------------------------------------------------------------------

CAASysSimpleMessage::~CAASysSimpleMessage()
{
   cout << "CAASysSimpleMessage::~CAASysSimpleMessage()"<< endl;
}

//---------------------------------------------------------------------------

HRESULT CAASysSimpleMessage::UnstreamData( void *iBuffer, uint32 iLen)
{
  cout << "CAASysSimpleMessage::UnstreamData"<< endl;
  
  return S_OK;
}

//---------------------------------------------------------------------------

HRESULT CAASysSimpleMessage::StreamData( void **oBuffer, uint32 *oLen)
{

  cout << "CAASysSimpleMessage::StreamData"<< endl;

  // no data to stream 
  *oBuffer = NULL ;
  *oLen = 0 ;

  return S_OK;
}

//---------------------------------------------------------------------------

HRESULT CAASysSimpleMessage::FreeStreamData( void *iBuffer, uint32 iLen)
{
  cout << "CAASysSimpleMessage::FreeStreamData"<< endl;
  return S_OK;
}

//---------------------------------------------------------------------------

HRESULT CAASysSimpleMessage::SetMessageSpecifications()
{
  cout << " CAASysSimpleMessage::SetMessageSpecifications"<< endl; 

  HRESULT rc = E_FAIL ;
  
  // CATICommMsg is implemented by the CATBBMessage component. 
  //
  
  CATICommMsg * pICommMsg = NULL ;
  rc = QueryInterface(IID_CATICommMsg,(void**)&pICommMsg);
  if ( SUCCEEDED(rc) )
  {
     // The name of the message class is mandatory to create 
     // the component by it's name. (This name is streamed )
     // CAASysSimpleMessage is the name of the component. 
     //
     CATMessageClass MessageClassName = "CAASysSimpleMessage";
     rc = pICommMsg->SetMessageClass(MessageClassName);
 
     pICommMsg->Release();
     pICommMsg = NULL ;

     rc = S_OK ;
  }

  return rc ;
}

