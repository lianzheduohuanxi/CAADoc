#ifndef CAADlgBBSenderWindow_h
#define CAADlgBBSenderWindow_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//    - Initialize the backbone bus 
//
//      - Declare a communication with the backbone bus
//
//    - If no problem with the backbone commnunication :
// 
//      - Create a CATDlgEditor to get a text 
//      - Create a CATDlgPushButton to send the text to an application
//           
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h"   // To derive from

// Dialog Framework
class CATInteractiveApplication;  // Application kept in data member
class CATDlgEditor ;

// System Framework
class CATICommunicator ;

class CAADlgBBSenderWindow : public CATDlgDocument
{
  // Declares the CAADlgBBSenderWindow.CATNls file as the dialog message catalog
  DeclareResource(CAADlgBBSenderWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAADlgBBSenderWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAADlgBBSenderWindow();

    //
    // Build
    // -----
    // This method constructs:
    //  
    //
    void     Build();

  private:

    // Method calls when the end user click on the close button
    //
    void Exit (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // Method calls when the end user click on the push button
    // This method creates a CAADlgBBEditorMessage with the text
    // contained in the CATDlgEditor.
    // This message is sent to the backbone bus .
    //
    void PushSend (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // Method to initialize the communicabackbone bus 
    HRESULT BackboneInit() ;

    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBSenderWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBSenderWindow(const CAADlgBBSenderWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBSenderWindow & operator = (const CAADlgBBSenderWindow &iObjectToCopy);

  private:


    // The parent widget (a CATInteractiveApplication instance)
    CATInteractiveApplication * _pApplication;

    // Data to send 
    CATDlgEditor              * _pEditor ;


    CATICommunicator          * _pICommunicator  ;
    
};
#endif
