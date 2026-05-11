// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgBBReceiverWindow.h"
#include "CAADlgBBEditorMessageHandler.h"
#include "CAADlgBBMessageNotification.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgFrame.h"
#include "CATDlgGridConstraints.h"  

// System Framework
#include "CATICommunicator.h"
#include "CATIMessageReceiver.h"

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAADlgBBReceiverWindow::CAADlgBBReceiverWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, "CAADlgBBReceiverWindowId"),
  _pApplication(iParentCommand),
  _pEditor(NULL),
  _pICommunicator(NULL),
  _pIMessageReceiver(NULL),
  _pBaseUnknownMessageHandler(NULL)
{
  cout << "CAADlgBBReceiverWindow::CAADlgBBReceiverWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAADlgBBReceiverWindow::~CAADlgBBReceiverWindow()
{ 
  cout << "CAADlgBBReceiverWindow::~CAADlgBBReceiverWindow" << endl; 

  _pApplication = NULL ;
  _pEditor = NULL ;

  if ( NULL != _pBaseUnknownMessageHandler)
  {
    ::RemoveSubscriberCallbacks(this,_pBaseUnknownMessageHandler );

    _pBaseUnknownMessageHandler->Release();
    _pBaseUnknownMessageHandler= NULL ;
  }
 

  if ( NULL !=  _pICommunicator )
  {
      if ( NULL != _pIMessageReceiver )
      {

         CATMessageClass MessageClassName = "CAADlgBBEditorMessage" ; 
         _pICommunicator->RemoveHandler("CAADlgBBReceiver",
                                         MessageClassName,
                                         _pIMessageReceiver);
         _pIMessageReceiver->Release();
         _pIMessageReceiver = NULL ;
      }

      _pICommunicator->Release();
      _pICommunicator = NULL ;
   }

}

//--------------------------------------------------------------------------------------

void CAADlgBBReceiverWindow::Build()
{
  cout << "CAADlgBBReceiverWindow::Build" << endl;

  // Initialize the backbone bus connexion to receive message sent by a
  // sender application described in the CAADlgBBSender.m module.
  // 
  HRESULT Init = BackboneInit();

  if ( SUCCEEDED(Init) )
  {

     // Dialog's objects
     //
     CATDlgFrame  * pFrame  = new CATDlgFrame(this, 
                                       "FrameId", 
                             CATDlgFraNoFrame | CATDlgGridLayout );
  
     CATDlgLabel  * pLabel  = new CATDlgLabel (pFrame,"LabelEditorId");
     pLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

     _pEditor = new CATDlgEditor(pFrame,"EditorId",CATDlgEdtReadOnly);
     _pEditor->SetGridConstraints(0,1,1,1,CATGRID_LEFT); 
  
     // Callback to update the editor with the text sent by the sender 
     // application.
     // The component CAADlgBBMessageHandler sends a a notification  
     // when the message is handled. 
     //
     _pIMessageReceiver->QueryInterface(IID_CATBaseUnknown,
                              (void**)&_pBaseUnknownMessageHandler);
     ::AddCallback(this,
                 _pBaseUnknownMessageHandler,
                 "CAADlgBBMessageNotification",
                 (CATSubscriberMethod)&CAADlgBBReceiverWindow::ModifyEditor,
                 NULL);
  }

  // to end the application
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAADlgBBReceiverWindow::Exit, NULL);

}

//--------------------------------------------------------------------------------------
void CAADlgBBReceiverWindow::ModifyEditor(CATCallbackEvent  ievent,
                                          void             *ipublisher,
                                          CATNotification  *iNotification,
                                          CATSubscriberData iData,
                                          CATCallback       iCallback)
{
   char * Text = NULL ;

   CAADlgBBMessageNotification * iNotif = NULL ;
   iNotif = (CAADlgBBMessageNotification*) iNotification;

   if ( NULL != iNotif )
   {
      iNotif->GetText(&Text);
      _pEditor->SetLine(Text);

      delete [] Text ;
      Text = NULL ;
   }
}
//--------------------------------------------------------------------------------------

void CAADlgBBReceiverWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}

//--------------------------------------------------------------------------------------

HRESULT CAADlgBBReceiverWindow::BackboneInit()
{
   HRESULT rc = E_FAIL ;
   
   // ReceiverApplicationId is the identificator of the current application
   // on the backbone bus.
   // 
   CATApplicationClass ReceiverApplicationId = "CAADlgBBReceiver";

   _pICommunicator = ::CATGetBackboneConnection() ;

   if ( NULL == _pICommunicator )
   {
      cout << "Unable to contact the backbone bus"<< endl;
   }else
   {

      //--------------------------------------------------
      // Declares the Application on the backbone bus
      //--------------------------------------------------
      
      rc= _pICommunicator->Declare( ReceiverApplicationId );
      if ( FAILED(rc) )
      { 
         cout << "Unable to declare on the backbone bus "<< endl;;
      }else
      {
         cout << "CAADlgBBReceiver is declared on the backbone bus" << endl;
      }
   }
   
   if ( SUCCEEDED(rc) && (NULL != _pICommunicator) )
   {
      //-----------------------------------------------------------
      //   Declares the handler associated to this message class
      //-----------------------------------------------------------
      CAADlgBBEditorMessageHandler * pHandlerForMessage = NULL ;
      pHandlerForMessage = new  CAADlgBBEditorMessageHandler();
         
      if ( NULL != pHandlerForMessage )
      {
         // An object can handle message if it implements the
         // CATIMessageReceiver interface.
         rc = pHandlerForMessage->QueryInterface(IID_CATIMessageReceiver,
                                                 (void**)& _pIMessageReceiver);
           
        if ( SUCCEEDED(rc) )
	{
           CATMessageClass MessageClassName = "CAADlgBBEditorMessage" ;   
           rc = _pICommunicator->AssociateHandler(ReceiverApplicationId, 
                                            MessageClassName,
                                            _pIMessageReceiver);
          if ( FAILED(rc) )
          {
              cout << "Unable to associate Handler to the backbone bus"<< endl;
          }else
          {   
              cout << "OK to associate Handler to the backbone bus"<< endl;
          } 
	}

        pHandlerForMessage->Release();
        pHandlerForMessage = NULL ;
     }
      
   }

   return rc;
}
