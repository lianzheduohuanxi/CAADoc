// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgBBSenderWindow.h"
#include "CAAIDlgDataRequest.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgPushButton.h"
#include "CATDlgFrame.h"
#include "CATDlgGridConstraints.h"  

// System Framework
#include "CATICommunicator.h"  //  Interface which represents the logical backbone
                               //  bus connexion.
#include "CATICommMsg.h"       //  to send the message 
#include "CATInstantiateComponent.h" 

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAADlgBBSenderWindow::CAADlgBBSenderWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, "CAADlgBBSenderWindowId"),
  _pApplication(iParentCommand),
  _pEditor(NULL),
  _pICommunicator(NULL)

{
  cout << "CAADlgBBSenderWindow::CAADlgBBSenderWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAADlgBBSenderWindow::~CAADlgBBSenderWindow()
{ 
  cout << "CAADlgBBSenderWindow::~CAADlgBBSenderWindow" << endl; 
  _pEditor      = NULL ;
  _pApplication = NULL ;

  if ( NULL != _pICommunicator )
  {
     _pICommunicator ->Release();
     _pICommunicator = NULL ;
  }
}

//--------------------------------------------------------------------------------------

void CAADlgBBSenderWindow::Build()
{
  cout << "CAADlgBBSenderWindow::Build" << endl;
  
  // Initialize the backbone bus connexion to send message from this
  // current application to the receiver application which is described
  // in the CAADlgBBReceiver.m module.
  //
  HRESULT Init = BackboneInit() ;

  if ( SUCCEEDED(Init) )
  {
     // Dialog's objects
     CATDlgFrame  * pFrame  = new CATDlgFrame(this, "FrameId", CATDlgFraNoFrame | CATDlgGridLayout );
  
     CATDlgLabel  * pLabel  = new CATDlgLabel (pFrame,"LabelEditorId");
     pLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

     _pEditor = new CATDlgEditor(pFrame,"EditorId",CATDlgEdtAlphanumerical);
     _pEditor->SetGridConstraints(0,1,1,1,CATGRID_LEFT); 

     CATDlgPushButton *pButton = new CATDlgPushButton(pFrame, "SendButtonId");
     pButton->SetGridConstraints(0,2,1,1,CATGRID_CENTER); 

	 // When the end user clicks on the push button, the message is sent
     AddAnalyseNotificationCB(pButton,
                           pButton->GetPushBActivateNotification(),
                           (CATCommandMethod)&CAADlgBBSenderWindow::PushSend, NULL);
  
  }

  // To end the application
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAADlgBBSenderWindow::Exit, NULL);

  

}

//--------------------------------------------------------------------------------------

void CAADlgBBSenderWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAADlgBBSenderWindow::PushSend(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   cout << "CAADlgBBSenderWindow::PushSend" << endl; 
   
   // Text in the editor 
   CATUnicodeString Line ;
   _pEditor->GetLine(Line);

   // Creation of the CAADlgBBEditorMessage component thanks the
   // CATICreateInstance interface that it implements.
   //
   CAAIDlgDataRequest * pIDataRequest = NULL ;
   HRESULT hr = ::CATInstantiateComponent("CAADlgBBEditorMessage",
	                       IID_CAAIDlgDataRequest,
			       (void **)&pIDataRequest);
                                                           
   if ( SUCCEEDED(hr) )
   {
      // Sets the text to send into the message
      pIDataRequest->SetData(Line.ConvertToChar());

      // Retrieves the CATICommMsg interface pointer to send the message
      //
      CATICommMsg * pICommMsg =NULL;
      hr = pIDataRequest->QueryInterface(IID_CATICommMsg,(void**)&pICommMsg);
                                                 
      if ( SUCCEEDED(hr) )
      {
         // Name of the application to send the message. This name is an 
         // identifier for which the application is known on the backbone bus.
         // See CATDlgBBReceiver.m 
         //
         CATApplicationClass ReceiverApplicationId = "CAADlgBBReceiver" ;
         hr = _pICommunicator->SendRequest(ReceiverApplicationId, pICommMsg);
         if ( SUCCEEDED(hr))
         {
            cout << " Send is successful" << endl;
         }else
         {
             cout << " Send is unsuccessful" << endl;
         } 

         pICommMsg->Release();
         pICommMsg = NULL ;
      }
   
      pIDataRequest->Release();
      pIDataRequest = NULL ;
    }
}

//--------------------------------------------------------------------------------------
HRESULT  CAADlgBBSenderWindow::BackboneInit()
{
   HRESULT  rc = E_FAIL ;
   
   //----------------------------------------------------
   // Retrieves an instance of a backbone bus 
   //----------------------------------------------------

   _pICommunicator = ::CATGetBackboneConnection() ;

   if ( NULL != _pICommunicator )
   {
      // -------------------------------------------------------------
      // Declares the application, CAADlgBBSender, on the backbone bus
      // This id represents the application on the backbone bus.
      // -------------------------------------------------------------
      CATApplicationClass ApplicationSenderId = "CAADlgBBSender" ;
      
      rc =_pICommunicator->Declare(ApplicationSenderId);
      if ( FAILED(rc) )
      { 
         cout << "Unable to declare the application on the backbone bus "<<endl;
      }else
      {
         cout<<"The application CAADlgBBSender is declared on the backbone bus"<<endl;
      }

   }else
   {
      cout << "Unable to contact the backbone bus"<< endl;
   }

   return rc ;
}
