#ifndef CAADlgHelloWindow_h
#define CAADlgHelloWindow_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  This class is the frame of the CAADlgHelloApplication
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h"   // To derive from

// Dialog Framework
class CATInteractiveApplication;  // Application kept in data member


class CAADlgHelloWindow : public CATDlgDocument
{
  // Declares the CAADlgHelloWindow.CATNls file as the dialog message catalog
  // This file is set in the Cnext\resources\msgcatalog of the current FW
  //
  DeclareResource(CAADlgHelloWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAADlgHelloWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAADlgHelloWindow();

    //
    // Build
    // -----
    // This method constructs at least the dialog's objects.
    //  
    //
    void     Build();

  private:

    // Callback to the close 
    void Exit (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);


    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgHelloWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgHelloWindow(const CAADlgHelloWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgHelloWindow & operator = (const CAADlgHelloWindow &iObjectToCopy);

  private:


    // The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pHelloApplication;

    
};
#endif
