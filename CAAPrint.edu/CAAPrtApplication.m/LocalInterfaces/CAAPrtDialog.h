#ifndef CAAPrtDialog_H
#define CAAPrtDialog_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Main window class.
//  The window is composed of a menu bar and a 2D viewer. 
//  The menu bar contains only two menus: 
//  File with the items:
//    Open... 
//    Print...
//    Capture...
//    Album...
//    Printer Manager...
//    Exit
//  Printable objects with the items:
//    Display a test image
//    Print a test image
//    Print a label
//
//  The class creates the viewer and the menu bar in an Init method and 
//  subscribes to the menu items.
//
//  File menu:
//  The callbacks associated with the Print, Capture, Album, Printer Manager
//  items only instantiate a dialog command provided by the Print framework. 
//  Only reading the image file is managed by the class itself, in the 
//  DisplayImage method.
//
//  Printable objects mneu:
//  Most of the code dealing with this menu is in another module: 
//  CAPrtPrintableObjects.m. 
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
//  Main Method:
//  ------------
//
//  Init: creates of the window contents
//  DisplayImage: reads the input TIFF file and displays the image 
//
//=============================================================================


//Dialog Framework
#include "CATDlgDocument.h"  // To derive from CATDlgDocument


//Dialog Framework
class CATDlgFile;        // To instantiate a dialog which enables a file choice

//Print Framework
class CATPrintDialog;        // To use the Print command
class CATPrintCaptureDialog; // To use the Capture command
class CATPrintImage;         // To read the input TIFF file
class CATPrintCaptureDialog; // The Capture Dialog object

//Visualization Framework    
class CAT2DViewer;           // To create a viewer
class CAT2DRep;              // To display an image   

class CAAPrtDialog : public CATDlgDocument
{
  // Declares the CAAPrtDialog.CATNls file as the dialog message catalog
  DeclareResource(CAAPrtDialog, CATDlgDocument); 

public:

  // Constructs the dialog window given its parent, its identifier
  // and its style.
  // Parameters
  //    iParent
  //        The dialog's parent which must be an application
  //    iIdentifier
  //        The identifier
  //    iStyle
  //        The dialog style
  CAAPrtDialog(CATInteractiveApplication  *iParent, 
                 const CATString          &iIdentifier, 
                 CATDlgStyle              iStyle=NULL);

  virtual ~CAAPrtDialog();

  // Releases some data members.
  void Clean();
	
  // Reads a TIFF image file and displays it.
  // Parameters
  //    iPath
  //        The path of the TIFF image file.
  void DisplayImage(const char *iPath);

  // Creates the window contents and subscribes to the menu items
  void Init();


private:

  //=======================================================================
  // Callbacks associated with a subscription by the AddAnalyseNotificationCB
  // method. 
  // They all have the following parameters:
  //    iPublishingCommand: 
  //        The publisher of the iNotification notification 
  //    iNotification: 
  //        The received notification 
  //    iUsefulData: 
  //        The data sent. NULL here. 
  //=======================================================================

  // Instanciates the Print command 
  // Called when the user choses the Print item in the File menu.
  void PrintCB(CATCommand               *iPublishingCommand, 
                CATNotification         *iNotification, 
                CATCommandClientData     iUsefulData);

  // Instanciates the Capture command 
  // Called when the user choses the Capture item in the File menu.
  void CaptureCB(CATCommand             *iPublishingCommand, 
                  CATNotification       *iNotification, 
                  CATCommandClientData   iUsefulData);

  // Instanciates the Album command 
  // Called when the user choses the Album item in the File menu.
  void AlbumCB(CATCommand               *iPublishingCommand, 
                CATNotification         *iNotification, 
                CATCommandClientData     iUsefulData);

  // Instanciates the Printer Manager command 
  // Called when the user choses the Printer Manager item in the File menu.
  void PrinterManagerCB(CATCommand      *iPublishingCommand, 
                   CATNotification      *iNotification, 
                   CATCommandClientData  iUsefulData);

  // Requests application destruction 
  // Called when the user choses the Exit item in the File menu or the close 
  // command of the main window.
  void ExitCB(CATCommand                *iPublishingCommand, 
                  CATNotification       *iNotification, 
                  CATCommandClientData   iUsefulData);

  // Instanciates the CATDlgFile dialog which enables the user to chose a
  // file and subscribes to its Ok, Cancel buttons. 
  // Called when the user choses the Open item in the File menu. 
  void OpenCB(CATCommand                *iPublishingCommand, 
                  CATNotification       *iNotification, 
                  CATCommandClientData   iUsefulData);

  // Requests the file selected by the user to be read.
  // Called when the user confirms the choice of a file in the Open dialog
  // (by clicking the Ok button or double-clicking the file name). 
  // Precisely, it
  // * retrieves the file.
  // * calls the DisplayImage method.
  // * deallocates the Open dialog.
  void OpenOKCB(CATCommand               *iPublishingCommand, 
                  CATNotification        *iNotification, 
                  CATCommandClientData    iUsefulData);

  // Deallocates the Open dialog.
  // Called when the user requests the dialog closing (by clicking the Cancel
  // button or selecting the close command of the dialog). 
  void OpenCANCELCB(CATCommand           *iPublishingCommand, 
                     CATNotification     *iNotification, 
                     CATCommandClientData iUsefulData);



  // Displays a test image that is to say an image with different 
  // elements, styles and colors.
  // Called when the user choses the "Display a test image" item in 
  // the Printable Objects menu.
  void TestDisplayCB(CATCommand          *iPublishingCommand, 
                     CATNotification     *iNotification, 
                     CATCommandClientData iUsefulData);

  // Launches the Print dialog using a printable object to print a 
  // test image.
  // Called when the user choses the "Print a test image" item in the 
  // Printable Objects menu.
  void TestPrintCB(CATCommand            *iPublishingCommand, 
                     CATNotification     *iNotification, 
                     CATCommandClientData iUsefulData);

  // Launches a dialog which enables the user to enter a string in order 
  // to print a label containing this string.
  // Called when the user choses the "Print a label" item in the Printable 
  // Objects menu.
  void LabelPrintCB(CATCommand            *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);


  // Resets the _PCapture object when the dialog object is closed
  //
  void CloseCaptureCB(CATCommand            *iPublishingCommand, 
                      CATNotification      *iNotification, 
                      CATCommandClientData  iUsefulData);

  // Default constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtDialog ();

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtDialog(const CAAPrtDialog &iObjectToCopy);
  
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtDialog & operator = (const CAAPrtDialog &iObjectToCopy);
  
private :
  //------------------
  // Dialog objects
  //------------------

  // The application which is the current dialog's parent.
  CATInteractiveApplication * _pApplication;

  // The dialog window which enables the user to choose a file 
  CATDlgFile                * _pFileDialog;
 

  //------------------
  // Visualization objects
  //------------------

  // The representation to display an image
  CAT2DRep    * _pRepImage;
  // The viewer
  CAT2DViewer * _pViewer;


  // The printable object for the test image
  CATBaseUnknown * _pPrintableTest;
  
  // Mandatory to keep this object, to make its destruction
  // at the end of the application, if the Dialog object exists.
  //
  CATPrintCaptureDialog * _pCapture ;
};

#endif
