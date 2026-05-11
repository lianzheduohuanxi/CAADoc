#ifndef CAADlgBBReceiverWindow_h
#define CAADlgBBReceiverWindow_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  
//    - Initialize the backbone bus: 
//
//      - Declare a communication with the backbone bus
//      - Create a component CAADlgBBEditorMessageHandler 
//        which can handle message received from a sender application
//
//    - if no problem with the backbone commnunication :
//
//      - Retrieve the Message's Manager to set a callback when this 
//        manager sends a notification when the CAADlgBBEditorMessageHandler 
//        has handled a message.
//      - Create a CATDlgEditor with will contain the text sent by the
//        sender application
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h"   // To derive from

// Dialog Framework
class CATInteractiveApplication;  // Application kept in data member
class CATDlgEditor ;              // Widget used in the dialog box

// System Framework
class CATIMessageReceiver ;
class CATICommunicator ;
class CATBaseUnknown ;

// System Framework
#include "CATEventSubscriber.h"  // To receive event

// Local Framework
class CAADlgBBMessageManager;    

class CAADlgBBReceiverWindow : public CATDlgDocument
{
  // Declares the CAADlgBBReceiverWindow.CATNls file as the dialog message catalog
  DeclareResource(CAADlgBBReceiverWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAADlgBBReceiverWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAADlgBBReceiverWindow();

    //
    // Build
    // -----
    // This method calls the BackboneInit method and if all is OK
    // creates an Editor. This Editor is modified by the message 
    // received from the Sender Application
    //
    void     Build();

  private:

    // Method calls when the end user click on the close button
    //
    void Exit (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // Method calls when the Message's Manager sends  a  
    // CAADlgBBMessageNotification notification. It sends this
    // event when the message is handled by the CAADlgBBEditorMessageHandler
    // component.
    //
    void ModifyEditor(CATCallbackEvent  iEvent,
                      void             *iPublisher,
                      CATNotification  *iNotification,
                      CATSubscriberData iData,
                      CATCallback       iCallback);

    // Method to initialize the backbone bus and to declare the
    // message class 
    HRESULT BackboneInit() ;

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBReceiverWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBReceiverWindow(const CAADlgBBReceiverWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBReceiverWindow & operator = (const CAADlgBBReceiverWindow &iObjectToCopy);

  private:


    // The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pApplication;

    // Data received
    CATDlgEditor              * _pEditor ;

    // Interface of a component which manages the connexion 
    // to the backbone bus.
    CATICommunicator          * _pICommunicator ;

    // Interface of the component CAADlgBBEditorMessageHandler
    // This component plays the role of a Callback
    CATIMessageReceiver       * _pIMessageReceiver  ;

    // Pointer of the same component 
    CATBaseUnknown            * _pBaseUnknownMessageHandler ;
   
};
#endif
