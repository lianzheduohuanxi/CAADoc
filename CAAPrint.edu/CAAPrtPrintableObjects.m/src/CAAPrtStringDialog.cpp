// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAPrtStringDialog.h"    // header file of the current class
#include "CAAPrtPrintableString.h"  

#include "CATPrintDialog.h"        // To instantiate the dialog command which manages printing

//Dialog Framework
#include "CATDlgLabel.h"           // To instantiate a dialog which enables a file choice
#include "CATDlgEditor.h"          // To instantiate the menu bar

#include "CATUnicodeString.h"      // To instantiate the menu bar

//--------------------------------------------------------------------------
CAAPrtStringDialog::CAAPrtStringDialog(CATDialog *iParent,
                                const CATString  &iIdentifier) :
  CATDlgDialog(iParent, iIdentifier, CATDlgWndModal|CATDlgWndAPPLY|CATDlgWndCANCEL),
  _pParent(iParent), 
  _pPrintableString(NULL),
  _pEditor(NULL)
{	
}

//--------------------------------------------------------------------------
void CAAPrtStringDialog::Init()
{  
  // Creates a label and an editor to enables the user to enter the string
  // to print
  CATDlgLabel * Label = new CATDlgLabel(this, "StringLabel");
  _pEditor = new CATDlgEditor(this, "StringEditor");

  // Subscribes to the window's closing		
  AddAnalyseNotificationCB(this, GetWindCloseNotification(), 
                (CATCommandMethod) &CAAPrtStringDialog::ExitCB, NULL );
  AddAnalyseNotificationCB(this, GetDiaAPPLYNotification(), 
                (CATCommandMethod) &CAAPrtStringDialog::ApplyCB, NULL );
  AddAnalyseNotificationCB(this, GetDiaCANCELNotification(), 
                (CATCommandMethod) &CAAPrtStringDialog::ExitCB, NULL );
}

//--------------------------------------------------------------------
CAAPrtStringDialog::~CAAPrtStringDialog()
{
  if (NULL != _pPrintableString) 
  {
     _pPrintableString -> Release();
     _pPrintableString = NULL ;
  }
  _pParent = NULL ;
  _pEditor = NULL ;

}

//--------------------------------------------------------------------
void CAAPrtStringDialog::ApplyCB(CATCommand           *iPublishingCommand, 
                                 CATNotification      *iNotification, 
                                 CATCommandClientData  iUsefulData )
{
  // Retrieves the string from the editor
  CATUnicodeString & String = _pEditor -> GetText();

  // Instantiates a printable object which will be able to draw the string
  // The Print dialog needs a printable object, not directly the image, that's
  // why this object is necessary.
  // Another solution is to make the image printable by making it implement the
  // CATIPrintable interface. This done in the sample about the test image in the
  // same module.
  // This instance is stored as a data member because CATPrintDialog does not 
  // Addref it.
  if (NULL != _pPrintableString) _pPrintableString->Release();
  _pPrintableString = new CAAPrtPrintableString (String); 

  // Instantiates the Print command
  // The current dialog is the parent of the Print dialog.
  // The Print dialog manages its deallocation itself.
  CATPrintDialog * PrintCmd = new CATPrintDialog(this, "StringPrint", _pPrintableString);

  // Shows the print Dialog
  PrintCmd-> SetVisibility(CATDlgShow);    
}

//--------------------------------------------------------------------
void CAAPrtStringDialog::ExitCB(CATCommand          *iPublishingCommand, 
                                CATNotification     *iNotification, 
                                CATCommandClientData iUsefulData )
{ 
  RequestDelayedDestruction();
}












