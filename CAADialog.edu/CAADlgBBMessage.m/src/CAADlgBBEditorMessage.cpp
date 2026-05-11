// COPYRIGHT DASSAULT SYSTEMES 2000	

// Local framework
#include  "CAADlgBBEditorMessage.h"

//System Framework 
#include <CATErrorDef.h>    // For the SUCCEEDED macro
#include "CATICommMsg.h"    // Used to specifie options and message class name 
#include "CATIBBStreamer.h" // Interface which helps to stream/unstream ...

//C++ Standard library
#include <iostream.h>       

//---------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIStreamMsg.h"
TIE_CATIStreamMsg(CAADlgBBEditorMessage);

// To create the TIE object
#include "TIE_CAAIDlgDataRequest.h"
TIE_CAAIDlgDataRequest(CAADlgBBEditorMessage);

// To declare that the class is a component main class which OM derives from
// CATBBMessage (DS component).
//
CATImplementClass(CAADlgBBEditorMessage, Implementation, CATBBMessage, CATNull);

// 
// To declare that CAADlgBBEditorMessage implements CAAIDlgDataRequest and 
// CATIStreamMsg , insert the following lines in the interface dictionary:
//
//    CAADlgBBEditorMessage CAAIDlgDataRequest  libCAADlgBBMessage
//    CAADlgBBEditorMessage CATIStreamMsg       libCAADlgBBMessage
//

//---------------------------------------------------------------------------

CAADlgBBEditorMessage::CAADlgBBEditorMessage():_Text(NULL)
{
   cout << "CAADlgBBEditorMessage::CAADlgBBEditorMessage()"<< endl;
}

//---------------------------------------------------------------------------

CAADlgBBEditorMessage::~CAADlgBBEditorMessage()
{
   cout << "CAADlgBBEditorMessage::~CAADlgBBEditorMessage()"<< endl;

   if ( NULL != _Text )
   {
      delete [] _Text ;
      _Text = NULL ;
   }
}

//---------------------------------------------------------------------------

HRESULT CAADlgBBEditorMessage::StreamData( void **oBuffer, uint32 *oLen)
{

  cout << "CAADlgBBEditorMessage::StreamData"<< endl;

  // CATIBBStreamer is implemented by the CATBBMessage component. 
  //
  // The CAADlgBBEditorMessage component derives from the CATBBMessage component
  // so this component inherits from the CATBBMessage component interface.
  //
  CATIBBStreamer * pICATIBBStreamer = NULL ;
  HRESULT rc = QueryInterface(IID_CATIBBStreamer,(void**)&pICATIBBStreamer);

  if ( SUCCEEDED(rc) )
  {
	 // Always begin by this instruction 
     pICATIBBStreamer->BeginStream();

	 // --------------------------
     pICATIBBStreamer->StreamString(_Text); 
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

HRESULT CAADlgBBEditorMessage::UnstreamData( void *iBuffer, uint32 iLen)
{
  cout << "CAADlgBBEditorMessage::UnstreamData"<< endl;

  // CATIBBStreamer is implemented by the CATBBMessage component. 
  //
  // The CAADlgBBEditorMessage component derives from the CATBBMessage component
  // so this component inherits from the CATBBMessage component interface.
  // 
  CATIBBStreamer * pICATIBBStreamer = NULL ;
  HRESULT rc = QueryInterface(IID_CATIBBStreamer,(void**)&pICATIBBStreamer);

  if ( SUCCEEDED(rc) )
  {
	 // Always begin by this instruction 
     pICATIBBStreamer->BeginUnstream(iBuffer,iLen);

	 // --------------------------
     int Len ;
     pICATIBBStreamer->UnstreamNeededStringLength(&Len); 
     _Text = new char [Len] ;
     pICATIBBStreamer->UnstreamString(_Text); 
     // --------------------------


	 // Always end by this instruction 
     rc = pICATIBBStreamer->EndUnstream();

     pICATIBBStreamer->Release();
     pICATIBBStreamer = NULL ;
  }

  return rc;
}


//---------------------------------------------------------------------------

HRESULT CAADlgBBEditorMessage::FreeStreamData( void *iBuffer, uint32 iLen)
{
  cout << "CAADlgBBEditorMessage::FreeStreamData"<< endl;

  // CATIBBStreamer is implemented by the CATBBMessage component. 
  //
  // The CAADlgBBEditorMessage component derives from the CATBBMessage component
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

HRESULT CAADlgBBEditorMessage::SetMessageSpecifications()
{
  cout << " CAADlgBBEditorMessage::SetMessageSpecifications"<< endl; 

  HRESULT rc = E_FAIL ;

  CATICommMsg * pICommMsg = NULL ;
  rc = QueryInterface(IID_CATICommMsg,(void**)&pICommMsg);
  if ( SUCCEEDED(rc) )
  {
     // The name of the message class is mandatory to create 
     // the component by it's name. (This name is streamed in the header 
	 // of the message)
     // CAADlgBBEditorMessage is the name of the component.
     //
     rc = pICommMsg->SetMessageClass("CAADlgBBEditorMessage");
 
     pICommMsg->Release();
     pICommMsg = NULL ;

     rc = S_OK ;
  }

  return rc ;
}

//---------------------------------------------------------------------------

HRESULT CAADlgBBEditorMessage::SetData(const char  * iText )        
{
   if ( NULL != iText )
   {
      _Text = new char [strlen(iText)+1];
      strcpy(_Text,iText);
   }

   return S_OK ;
}

//---------------------------------------------------------------------------

HRESULT CAADlgBBEditorMessage::GetData(char  ** oText ) 
{
   HRESULT rc = E_FAIL ;

   if ( NULL != oText )
   {
      if ( NULL != _Text )
      {
         *oText = new char [strlen(_Text)+1];
         strcpy(*oText,_Text);
      }else 
      {
         *oText = NULL ;
      }

      rc = S_OK ;
   }

   return rc ;
}

