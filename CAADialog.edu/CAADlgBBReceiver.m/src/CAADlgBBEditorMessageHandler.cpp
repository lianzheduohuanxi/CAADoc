// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAADlgBBEditorMessageHandler.h"

//C++ Standard library
#include <iostream.h>       // To display traces 

// System framework
#include <CATErrorDef.h> // For the SUCCEDED macro 
#include "CATCallbackManager.h" // to send a notification

// Local Framework
#include "CAAIDlgDataRequest.h"
#include "CAADlgBBMessageNotification.h"

//---------------------------------------------------------------------------

// To create the TIE object
#include "TIE_CATIMessageReceiver.h"
TIE_CATIMessageReceiver(CAADlgBBEditorMessageHandler);

// To declare that the class is a component main class
//
CATImplementClass(CAADlgBBEditorMessageHandler, Implementation, CATBaseUnknown, CATNull);

// 
// To declare that CAADlgBBEditorMessageHandler implements CATIMessageReceiver 
// insert the following line in the interface dictionary:
//
//    CAADlgBBEditorMessageHandler CATIMessageReceiver  libCAADlgBBReceiver
//
//---------------------------------------------------------------------------

CAADlgBBEditorMessageHandler::CAADlgBBEditorMessageHandler()
{
   cout << "CAADlgBBEditorMessageHandler::CAADlgBBEditorMessageHandler()"<< endl;
}

//---------------------------------------------------------------------------

CAADlgBBEditorMessageHandler::~CAADlgBBEditorMessageHandler()
{
   cout << "CAADlgBBEditorMessageHandler::~CAADlgBBEditorMessageHandler()"<< endl;
}

//---------------------------------------------------------------------------

void CAADlgBBEditorMessageHandler::HandleMessage(CATICommMsg* iMessage)
{
  //
  // This Handle is dedicated to the CAADlgBBEditorMessage class message 
  //
  cout << "CAADlgBBEditorMessageHandler::HandleMessage " << endl ;
  cout <<endl<< endl;

  if ( NULL != iMessage )
  {
     CAAIDlgDataRequest * pIRequest = NULL ;
     HRESULT hr = iMessage->QueryInterface(IID_CAAIDlgDataRequest,(void**) &pIRequest);
     if ( SUCCEEDED(hr) )
     {
        char * Text = NULL ;
        pIRequest->GetData(&Text);
        pIRequest->Release();
        pIRequest= NULL ;

        CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this) ;
        if ( NULL != pCBManager )
        {
           CAADlgBBMessageNotification * pNotification = new CAADlgBBMessageNotification(Text);
           pCBManager->DispatchCallbacks(pNotification, this);
           pNotification->Release();
           pNotification = NULL ;
        }

        delete [] Text ;
        Text = NULL ;

     }
  } 
}
