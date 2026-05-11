#ifndef CAACafComboWindow_h
#define CAACafComboWindow_h

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
class CATComboColor;  
class CATComboDashed;  
class CATComboSymbol;  
class CATComboWeight;  


class CAACafComboWindow : public CATDlgDocument
{
  // Declares the CAACafComboWindow.CATNls file as the dialog message catalog
  // This file is set in the Cnext\resources\msgcatalog of the current FW
  //
  DeclareResource(CAACafComboWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAACafComboWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAACafComboWindow();

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


    // Callback to the get the color selected 
    void ColorSelected (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // Callback to the get the symbol selected 
    void SymbolSelected (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);
     
    // Callback to the get the line type selected 
    void LineTypeSelected (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);
     
    // Callback to the get the line weight selected 
    void LineWeightSelected (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);
     
    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafComboWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafComboWindow(const CAACafComboWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafComboWindow & operator = (const CAACafComboWindow &iObjectToCopy);

  private:


    /* The parent widget (a CATInteractiveApplication instance) */
    CATInteractiveApplication * _pApplication;

    /* combos */
    CATComboColor  * _pComboColor ;
    CATComboDashed * _pComboDashed ;
    CATComboWeight * _pComboWeight ;
    CATComboSymbol * _pComboSymbol ;
    
};
#endif
