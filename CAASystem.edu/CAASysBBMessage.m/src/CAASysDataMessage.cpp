// COPYRIGHT DASSAULT SYSTEMES 2000	

#include  "CAASysDataMessage.h"

//C++ Standard library
#include <iostream.h>       

// System Framework
#include <CATErrorDef.h>    // for the SUCCEEDED macro
#include "CATIBBStreamer.h" // To stream 
#include "CATICommMsg.h"    


//---------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIStreamMsg.h"
TIE_CATIStreamMsg(CAASysDataMessage);

// To create the TIE object
#include "TIE_CAAISysDataRequest.h"
TIE_CAAISysDataRequest(CAASysDataMessage);

// To declare that the class is a component main class which OM derives from
// the CATBBMessage component
//
CATImplementClass(CAASysDataMessage, Implementation, CATBBMessage, CATNull);

// 
// To declare that CAASysDataMessage implements CAAISysDataRequest and 
// CATIStreamMsg, insert these following lines in the interface dictionary:
//
//    CAASysDataMessage  CAAISysDataRequest  libCAASysBBMessage
//    CAASysDataMessage  CATIStreamMsg       libCAASysBBMessage
//   
//---------------------------------------------------------------------------

CAASysDataMessage::CAASysDataMessage():_ColorOfCircle(NULL),_NbOfCircle(0),_RadiusOfCircle(0.f)
{
   cout << "CAASysDataMessage::CAASysDataMessage()"<< endl;
   _SagOfCircle[0] = 0.0f ;
   _SagOfCircle[1] = 0.0f ;
   _SagOfCircle[2] = 0.0f ;
}

//---------------------------------------------------------------------------

CAASysDataMessage::~CAASysDataMessage()
{
   cout << "CAASysDataMessage::~CAASysDataMessage()"<< endl;

   if ( NULL != _ColorOfCircle ) 
   {
      delete [] _ColorOfCircle ;
      _ColorOfCircle = NULL ;
   }
}

//---------------------------------------------------------------------------

HRESULT CAASysDataMessage::StreamData( void **oBuffer, uint32 *oLen)
{

  cout << "CAASysDataMessage::StreamData"<< endl;

  // CATIBBStreamer is implemented by the CATBBMessage component. 
  //
  // The CAASysDataMessage component derives from the CATBBMessage component
  // so this component inherits from the CATBBMessage component interface.
  // 
  CATIBBStreamer * pICATIBBStreamer = NULL ;
  HRESULT rc = QueryInterface(IID_CATIBBStreamer,(void**)&pICATIBBStreamer);

  if ( SUCCEEDED(rc) )
  {
     // Always begin by this instruction 
     pICATIBBStreamer->BeginStream();

     // Stream depending data type 
     // --------------------------
     pICATIBBStreamer->StreamFloat(_RadiusOfCircle); 
     pICATIBBStreamer->StreamInt(_NbOfCircle); 
     pICATIBBStreamer->StreamString(_ColorOfCircle); 
     pICATIBBStreamer->StreamFixedFloatArray(_SagOfCircle,3); 
     // --------------------------

     // Always begin by these 3 instructions 
     int Len ; 
     *oBuffer = pICATIBBStreamer->EndStream(&Len);
     *oLen = Len ;

     pICATIBBStreamer->Release();
     pICATIBBStreamer = NULL ;

  }

  return rc;
}

//---------------------------------------------------------------------------

HRESULT CAASysDataMessage::UnstreamData( void *iBuffer, uint32 iLen)
{
  cout << "CAASysDataMessage::UnstreamData"<< endl;

  // CATIBBStreamer is implemented by the CATBBMessage component.
  //
  // The CAASysDataMessage component derives from the CATBBMessage component
  // so this component inherits from the CATBBMessage component interface.
  //
  CATIBBStreamer * pICATIBBStreamer = NULL ;
  HRESULT rc = QueryInterface(IID_CATIBBStreamer,(void**)&pICATIBBStreamer);

  if ( SUCCEEDED(rc) )
  {
     // Always begin by this instruction
     pICATIBBStreamer->BeginUnstream(iBuffer,iLen);

     // Unstream depending data type
     // --------------------------
     pICATIBBStreamer->UnstreamFloat(&_RadiusOfCircle);
     pICATIBBStreamer->UnstreamInt(&_NbOfCircle);

     int Len ;
     pICATIBBStreamer->UnstreamNeededStringLength(&Len);
     _ColorOfCircle = new char [Len] ;
     pICATIBBStreamer->UnstreamString(_ColorOfCircle);

     pICATIBBStreamer->UnstreamFixedFloatArray(_SagOfCircle,3);
     // --------------------------


     // Always end by this instruction
     rc = pICATIBBStreamer->EndUnstream();

     pICATIBBStreamer->Release();
     pICATIBBStreamer = NULL ;
  }

  return rc;
}

//--------------------------------------------------------------------------

HRESULT CAASysDataMessage::FreeStreamData( void *iBuffer, uint32 iLen)
{
  cout << "CAASysDataMessage::FreeStreamData"<< endl;

  // CATIBBStreamer is implemented by the CATBBMessage component. 
  //
  // The CAASysDataMessage component derives from the CATBBMessage component
  // so this component inherits from the CATBBMessage component interface.
  // 

  CATIBBStreamer * pICATIBBStreamer = NULL ;
  HRESULT rc = QueryInterface(IID_CATIBBStreamer,(void**)&pICATIBBStreamer);

  if ( SUCCEEDED(rc) )
  {
     pICATIBBStreamer->ResetStreamData();

     pICATIBBStreamer->Release();
     pICATIBBStreamer = NULL ;
  }

  return rc ;
}

//---------------------------------------------------------------------------

HRESULT CAASysDataMessage::SetMessageSpecifications()
{
  cout << " CAASysDataMessage::SetMessageSpecifications"<< endl; 

  HRESULT rc = E_FAIL ;
  
  // CATICommMsg is implemented by the CATBBMessage component. 
  //
  
  CATICommMsg * pICommMsg = NULL ;
  rc = QueryInterface(IID_CATICommMsg,(void**)&pICommMsg);
  if ( SUCCEEDED(rc) )
  {
     // The name of the message class is mandatory to create 
     // the component by it's name. (This name is streamed )
     // CAASysDataMessage is the name of the component. 
     //
	 CATMessageClass MessageClassName= "CAASysDataMessage" ;
     rc = pICommMsg->SetMessageClass(MessageClassName);
 
     pICommMsg->Release();
     pICommMsg = NULL ;

     rc = S_OK ;
  }

  return rc ;
}

//---------------------------------------------------------------------------

HRESULT CAASysDataMessage::SetData(const float iRadiusOfCircle   ,
                                   const int   iNbOfCircle    ,
                                   char       *iColorOfCircle ,
                                   float      *iSagOfCircle )
{
   _RadiusOfCircle = iRadiusOfCircle ;

   _NbOfCircle     = iNbOfCircle ;

   if ( NULL != iColorOfCircle )
   {
      _ColorOfCircle = new char [strlen(iColorOfCircle)+1];
      strcpy(_ColorOfCircle,iColorOfCircle);
   }

   _SagOfCircle[0] = iSagOfCircle[0] ;
   _SagOfCircle[1] = iSagOfCircle[1] ;
   _SagOfCircle[2] = iSagOfCircle[2] ;

   return S_OK ;
}

//---------------------------------------------------------------------------

HRESULT CAASysDataMessage::GetData(float  & oRadiusOfCircle   ,
                                   int    & oNbOfCircle    ,
                                   char  ** oColorOfCircle ,
                                   float ** oSagOfCircle )
{
   HRESULT rc = E_FAIL ;

   if ( (NULL != oSagOfCircle) && ( NULL != oColorOfCircle) )
   {
      oRadiusOfCircle = _RadiusOfCircle ;

      oNbOfCircle     = _NbOfCircle ;

      if ( NULL != _ColorOfCircle )
      {
         *oColorOfCircle = new char [strlen(_ColorOfCircle)+1];
         strcpy(*oColorOfCircle,_ColorOfCircle);
      }else 
      {
         *oColorOfCircle = NULL ;
      }

      *oSagOfCircle = new float[3] ;

      (*oSagOfCircle)[0] = _SagOfCircle[0] ;
      (*oSagOfCircle)[1] = _SagOfCircle[1] ;
      (*oSagOfCircle)[2] = _SagOfCircle[2] ;

      rc = S_OK ;
   }
   return rc ;
}
