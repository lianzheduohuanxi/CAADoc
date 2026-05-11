#ifndef CAADlgDemoWindow_h
#define CAADlgDemoWindow_h

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


class CAADlgDemoWindow : public CATDlgDocument
{
  // Declares the CAADlgDemoWindow.CATNls file as the dialog message catalog
  // This file is set in the Cnext\resources\msgcatalog of the current FW
  //
  DeclareResource(CAADlgDemoWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAADlgDemoWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAADlgDemoWindow();

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

    // Callbacks to the Tabulation Menu
    void MoreRadioButton (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    void MoreLessMoreButton (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    void FrameReplace (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgDemoWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgDemoWindow(const CAADlgDemoWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgDemoWindow & operator = (const CAADlgDemoWindow &iObjectToCopy);

  private:


    // The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pApplication;

    
};
#endif
