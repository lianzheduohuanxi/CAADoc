#ifndef CAADlgBurgerWindow_h
#define CAADlgBurgerWindow_h

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
class CATDlgRadioButton;      // Dialog object used in the application window
class CATDlgCheckButton;      // Dialog object used in the application window
class CATDlgSlider;           // Dialog object used in the application window
class CATDlgCombo;            // Dialog object used in the application window
class CATDlgEditor;           // Dialog object used in the application window
class CATDlgSelectorList;     // Dialog object used in the application window
class CATDlgSpinner;          // Dialog object used in the application window

class CATDlgNotify;               // Notification sends by the order's window 
class CATInteractiveApplication;  // Application kept in data member


class CAADlgBurgerWindow : public CATDlgDocument
{
  // Declares the CAADlgBurgerWindow.CATNls file as the dialog message catalog
  DeclareResource(CAADlgBurgerWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAADlgBurgerWindow(CATInteractiveApplication * iParentCommand,
				       const CATString           & iDialogBoxId,
					   CATDlgStyle                 iDialogBoxStyle);
    virtual ~CAADlgBurgerWindow();

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
    * Callback function invoked when the value of the CATDlgxxx changes.
    * It simply displays a NLS message in the console.
    */
    void Cooking            (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    void Seasoning          (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    void HamburgerQuantity  (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    void FriesSize          (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    void FriesQuantity      (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    void DrinkList          (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    void DrinkQuantity      (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    
    /*
    * Callback function invoked when the 'Apply' button is pressed.
    * It constructs a large NLS message which lists the items ordered.
    * It then uses a modal CATDlgNotify window to display it.
    */
    void Apply              (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    
    /*
    * Callback function invoked when the 'Dismiss' button is pressed.
    * It shuts down the application.
    */
    void Dismiss            (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);
    
    /*
    * Callback function invoked when the 'Reset' button is pressed.
    * It resets the state of all the widgets contained by the dialog window.
    */
    void Reset              (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);

    /*
    * Callback function invoked when the 'Ok' button of the child CATDlgNotify 
    * window is pressed.
    */
    void NotifyOK           (CATCommand * iSendingCommand, CATNotification * iSentNotification, CATCommandClientData iUsefulData);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBurgerWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBurgerWindow(const CAADlgBurgerWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBurgerWindow & operator = (const CAADlgBurgerWindow &iObjectToCopy);

  private:
   /*
    * These member variables are pointers to some of the widgets which 
    * have been instantiated in the dialog window.
    * We only keep pointers to widgets whose state we want to query
    * at some point in the program. We do not need to keep pointers
    * to stateless widgets (labels, frames, separators...) since
    * they will automatically be destroyed when the main Dialog window
    * is destroyed.
    */
   
    CATDlgRadioButton     * _pRare,    * _pMedium,   * _pWellDone;
    CATDlgCheckButton     * _pKetchup, * _pMustard,  * _pPickle,
                          * _pOnion,   * _pMayonnaise;
    CATDlgSlider          * _pHamburgerQuantity;
    CATDlgCombo           * _pFriesSize;
    CATDlgEditor          * _pFriesQuantity;
    CATDlgSelectorList    * _pDrinkList;
    CATDlgSpinner         * _pDrinkQuantity;

    /*
    * The dialog window can trigger a child modal window. Since this second window
    * is very simple, it does not have a class of its own and its pointer and callback
    * are hosted by the main dialog window.
    */
    CATDlgNotify * _pOrderWindow;

// The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pCAABurgerApplication;
};
#endif
