#ifndef CAABasicAuthenticationPanelWindow_h
#define CAABasicAuthenticationPanelWindow_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Window of the application which contains alls Dialog's object. 
// 
//=============================================================================
//  Inheritance:
//  ------------
//           CATDlgDocument (Dialog Framework)
//             CATDlgWindow (Dialog Framework)
//               CATDialog (Dialog Framework)
//                 CATCommand (System Framework)
//                   CATEventSubscriber (System Framework)
//                     CATBaseUnknown (System Framework)
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h"   // To derive from

// Dialog FrameWork
class CATInteractiveApplication;  // Application kept in data member

class CAABasicAuthenticationPanelWindow : public CATDlgDocument
{
  // Declares the CAABasicAuthenticationPanelWindow.CATNls file as the dialog message catalog
  DeclareResource(CAABasicAuthenticationPanelWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAABasicAuthenticationPanelWindow(CATInteractiveApplication * iParentCommand,
				       const CATString           & iDialogBoxId,
					   CATDlgStyle                 iDialogBoxStyle);
    virtual ~CAABasicAuthenticationPanelWindow();

   /*
    * Constructs, initializes and positions all the widgets contained
    * by the dialog window
    */
    void     Build();

  private:

    /*
    * These member functions are Dialog callbacks. They are invoked
    * when events occur in the widgets of the dialog window.
    */

    /*
    * Callback function invoked when the 'Dismiss' button is pressed.
    * It shuts down the application.
    */
    void Dismiss            (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAABasicAuthenticationPanelWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAABasicAuthenticationPanelWindow(const CAABasicAuthenticationPanelWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAABasicAuthenticationPanelWindow & operator = (const CAABasicAuthenticationPanelWindow &iObjectToCopy);

  private:

// The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pCAABasicApplication;
};
#endif
