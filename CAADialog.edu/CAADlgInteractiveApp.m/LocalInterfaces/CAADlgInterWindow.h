#ifndef CAADlgInterWindow_h
#define CAADlgInterWindow_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  This class is the frame of the application
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h"   // To derive from

// Dialog Framework
class CATInteractiveApplication;  // Application kept in data member


class CAADlgInterWindow : public CATDlgDocument
{
  // Declares the CAADlgInterWindow.CATNls file as the dialog message catalog
  // This file is set in the Cnext\resources\msgcatalog of the current FW
  //
  DeclareResource(CAADlgInterWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAADlgInterWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAADlgInterWindow();

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
    CAADlgInterWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgInterWindow(const CAADlgInterWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgInterWindow & operator = (const CAADlgInterWindow &iObjectToCopy);

  private:


    // The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pApplication;

    
};
#endif
