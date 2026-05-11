#ifndef CAAPrtStringDialog_H
#define CAAPrtStringDialog_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Dialog command which 
//    - enables the user to enter a string
//    - displays the Print dialog in order to print the label built from the 
//      specified string.
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATDlgDialog (Dialog Framework)
//             CATDlgWindow (Dialog Framework)
//               CATDialog (Dialog Framework)
//                 CATCommand (System Framework)
//                   CATEventSubscriber (System Framework)
//                     CATBaseUnknown (System Framework)
//
//=============================================================================
//  Main Methods:
//  -------------
//
//  Init   : Creates an editor and subscribes to its modifications
//  ApplyCB: Retrieves the string entered in the editor and instantiates the 
//           Print dialog 
//
//=============================================================================

//Dialog Framework
#include "CATDlgDialog.h"  // To derive from CATDlgDialog

//Local Framework
#include "CAAPrtPrintableObjects.h" // To export this class


//Dialog Framework
class CATDlgEditor;        // To instantiate a dialog which enables a file choice

//Local framework
class CAAPrtPrintableString;  // To store the printable object

class ExportedByCAAPrtPrintableObjects CAAPrtStringDialog : public CATDlgDialog
{
public:

  // Declares the CAAPrtStringDialog.CATNls file as the dialog message catalog
  DeclareResource(CAAPrtStringDialog, CATDlgDialog); 


  // Constructs the dialog window given its parent, its identifier.
  // Parameters
  //    iParent
  //        The dialog's parent which must be an application
  //    iIdentifier
  //        The identifier

  CAAPrtStringDialog(CATDialog *iParent, const CATString &iIdentifier);

  virtual ~CAAPrtStringDialog();
	
  // Creates the window contents and subscribes to events
  void Init();

private:


  //=======================================================================
  // Callbacks associated with a subscription by the AddAnalyseNotificationCB
  // method. 
  // They all have the following parameters:
  //    iPublisher: 
  //        The publisher of the iNotification notification 
  //    iNotification: 
  //        The received notification 
  //    iData: 
  //        The data sent. NULL here. 
  //=======================================================================

  // Retrieves the string entered by the user and instantiates the Print dialog. 
  // Called when the user clicks Apply or types Enter.
  void ApplyCB(CATCommand            *iPublishingCommand, 
                CATNotification      *iNotification, 
                CATCommandClientData  iUsefulData);

  // Requests application destruction 
  // Called when the user closes the window or clicks Cancel
  void ExitCB(CATCommand             *iPublishingCommand, 
                CATNotification      *iNotification, 
                CATCommandClientData  iUsefulData);

  // Default constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtStringDialog();  

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtStringDialog (const CAAPrtStringDialog &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtStringDialog & operator = (const CAAPrtStringDialog &iObjectToCopy);

private:

  //------------------
  // Dialog objects
  //------------------

  // The editor which enables the user to enter a string
  CATDlgEditor          *_pEditor;
 
  // the dialog's parent
  CATDialog             *_pParent;

  // Printable object
  CAAPrtPrintableString *_pPrintableString ;
};

#endif
