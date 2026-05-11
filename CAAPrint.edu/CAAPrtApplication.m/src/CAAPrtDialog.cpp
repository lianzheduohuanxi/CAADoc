// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAPrtDialog.h"          // header file of the current class
#include "CAAPrtTestImage.h"       // To display and print the test image
#include "CAAPrtStringDialog.h"    // To launch the command which prints a string

//Print Framework
#include "CATPrint2DRep.h"         // To create a visualisation representation from a file containing an image
#include "CATPrintParameters.h"    // To define print parameters
#include "CATPrintFileImage.h"     // To create an image from the input file
#include "CATPrintDialog.h"        // To instantiate the dialog command which manages printing
#include "CATPrintCaptureDialog.h" // To instantiate the dialog command which enables image capture
#include "CATPrintAlbumDialog.h"   // To instantiate the dialog command which manages albums
#include "CATPrinterManagerDialog.h" // To instantiate the dialog command which manages printers 

//Visualization Framework
#include "CAT2DViewer.h"           // To instantiate a 2D viewer

//ApplicationFrame Framework
#include "CATInteractiveApplication.h" // To display a busy cursor 

//Dialog Framework
#include "CATDlgFile.h"          // To instantiate a dialog which enables a file choice
#include "CATDlgBarMenu.h"       // To instantiate the menu bar
#include "CATDlgSubMenu.h"       // To instantiate the File menu
#include "CATDlgPushItem.h"      // To instantiate the menu items
#include "CATDlgSeparatorItem.h" // To instantiate the menu separator

//To have cout
#include <iostream.h>

//--------------------------------------------------------------------------
CAAPrtDialog::CAAPrtDialog(CATInteractiveApplication *iParent, 
                           const CATString           &iIdentifier, 
                           CATDlgStyle               iStyle) :
  CATDlgDocument(iParent, iIdentifier, iStyle),
  _pApplication(iParent),
  _pRepImage(NULL),
  _pFileDialog(NULL),
  _pViewer(NULL),
  _pPrintableTest(NULL),
  _pCapture(NULL)
{	
}

//--------------------------------------------------------------------------
void CAAPrtDialog::Init()
{  
  // Creates the menu bar with its File and Printable menus
  // These Dialog's object are destructed by the infrastructure.
  // No need to delete  it in the destructor.
  CATDlgBarMenu * menuBar = new CATDlgBarMenu(this, "MainMenu");

     CATDlgSubMenu * fileMenu = new CATDlgSubMenu(menuBar, "File");
  
       CATDlgPushItem * openItem       = new CATDlgPushItem(fileMenu, "Open");
       CATDlgPushItem * printItem      = new CATDlgPushItem(fileMenu, "Print");
       CATDlgPushItem * captureItem    = new CATDlgPushItem(fileMenu, "Capture");
       CATDlgPushItem * albumItem      = new CATDlgPushItem(fileMenu, "Album");
       CATDlgPushItem * printManItem   = new CATDlgPushItem(fileMenu, "PrintMan");
       CATDlgSeparatorItem * separItem = new CATDlgSeparatorItem(fileMenu, "sep");
       CATDlgPushItem * exitItem       = new CATDlgPushItem(fileMenu, "Exit");

     CATDlgSubMenu * PrintableMenu = new CATDlgSubMenu(menuBar, "Printable");

       CATDlgPushItem * testDisplay  = new CATDlgPushItem(PrintableMenu, "TestDisplay");
       CATDlgPushItem * testPrint    = new CATDlgPushItem(PrintableMenu, "TestPrint");
       CATDlgPushItem * labelPrint   = new CATDlgPushItem(PrintableMenu, "LabelPrint");
   
  //---------------------------------------------------------------------------
  // Creates the viewer

  _pViewer = new CAT2DViewer(this, "MainViewer",CATDlgFraNoTitle,640, 480);

  // Sets a white background color
  _pViewer->SetBackgroundColor( 0.8f, 0.8f, 0.8f );

  // attachs the viewer to the window
  Attach4Sides( _pViewer );


  //---------------------------------------------------------------------------
  // subscribes to the menu items		
  AddAnalyseNotificationCB(openItem, 
                           openItem->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::OpenCB, 
                           NULL);
  AddAnalyseNotificationCB(printItem, 
                           printItem->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::PrintCB,
                           NULL);
  AddAnalyseNotificationCB(captureItem, 
                           captureItem->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAPrtDialog::CaptureCB,
                           NULL);
  AddAnalyseNotificationCB(albumItem, 
                           albumItem->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::AlbumCB,
                           NULL);
  AddAnalyseNotificationCB(printManItem, 
                           printManItem->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::PrinterManagerCB,
                           NULL);
  AddAnalyseNotificationCB(exitItem, 
                           exitItem->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAPrtDialog::ExitCB,
                           NULL);

  AddAnalyseNotificationCB(testDisplay, 
                           testDisplay->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::TestDisplayCB, 
                           NULL);
  AddAnalyseNotificationCB(testPrint, 
                           testPrint->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::TestPrintCB, 
                           NULL);
  AddAnalyseNotificationCB(labelPrint, 
                           labelPrint->GetMenuIActivateNotification(), 
                           (CATCommandMethod)& CAAPrtDialog::LabelPrintCB, 
                           NULL);

}

//--------------------------------------------------------------------
CAAPrtDialog::~CAAPrtDialog()
{
  if( NULL != _pPrintableTest) 
  {
     _pPrintableTest->Release();
     _pPrintableTest = NULL;
  }

  _pApplication = NULL ;
  _pRepImage    = NULL ;
  _pFileDialog  = NULL ;
  _pViewer      = NULL ;
  _pCapture     = NULL ;
}

//--------------------------------------------------------------------
void CAAPrtDialog::Clean()
{
  // Releases the representation
  // Objets to be released before the destructor because the
  // Viewer is always available.
  if ( NULL != _pRepImage)
  {
    _pViewer->RemoveRep(_pRepImage);
    _pRepImage->Destroy();
    _pRepImage = NULL;
  }

  // Caution: If the CATPrintCaptureDialog object exists, it must be deleted
  // before the Viewer. The Viewer should be deleted automatically by the
  // application. In normal case _PCapture should be deleted too by the application.
  // but you don't control the order of these 2 destructions. So You ask 
  // explicitely the destruction of _pCapture 
  //  
  if ( NULL != _pCapture ) 
  {
     _pCapture->DetachViewer();
     _pCapture->RequestDelayedDestruction();
     _pCapture = NULL ;
  }

}

//--------------------------------------------------------------------
void CAAPrtDialog::DisplayImage(const char *iPath)
{
  CAT2DRep * rep=NULL;
  
  // Checks that the input file is a TIFF file
  const int len = strlen(iPath);
  if ( len>4 && strcmp(iPath+len-4, ".tif")==0 )
  {
    // 3- Creates an image from the input TIFF file
    CATPrintFileImage* image = new CATPrintFileImage(iPath, "TIFF");

    // standard print parameters
    CATPrintParameters parameters;

    // To avoid clipping, set the margins to null.
    parameters.SetMargins(0.f,0.f,0.f,0.f);

    // To display an image, you need a representation device and a 
    // representation driver which are encapsulated into the CATPrint2Rep
    // class.
    rep = new CATPrint2DRep(image, parameters);  

    // Releases the image
    image -> Release();
  }
    
  // Adds the representation into the viewer
  if (NULL !=  rep)
  {
    // Removes the possible previous representation and releases it.
    if (NULL !=  _pRepImage)
    {
      _pViewer->RemoveRep(_pRepImage);
      _pRepImage -> Destroy();
    }
    // Adds the representation
    _pViewer->AddRep(rep);
    // Redraws 
    _pViewer->Reframe();
    // Keeps the new representation 
    _pRepImage = rep;
  }
}

//--------------------------------------------------------------------
void CAAPrtDialog::OpenCB(CATCommand          *iPublishingCommand,
                        CATNotification     *iNotification,  
                        CATCommandClientData iUsefulData)
{
  // Instantiates the standard dialog which enables the user to choose a file
  // The FileDialog's parent is the current window.
  _pFileDialog = new CATDlgFile(this, "OpenFile");

  // Sets the search filter. Only TIFF files are allowed.
#ifdef _WINDOWS_SOURCE
  
  CATUnicodeString nameExtension   = CATUnicodeString("TIFF File (*.tif)");
  CATString        filterExtension = CATString("*.tif");

  _pFileDialog->SetFilterStrings(&nameExtension, &filterExtension, 1);

#else

  _pFileDialog->SetFilterPattern("*.tif");
 
#endif

  // Subscribes to the event sent when the user selects the Ok button or
  // double-clicks a file
  AddAnalyseNotificationCB(_pFileDialog, 
                           _pFileDialog->GetDiaOKNotification(), 
		           (CATCommandMethod)& CAAPrtDialog::OpenOKCB,
                            NULL);

  // Subscribes to the event sent when the user selects the Cancel button or
  // closes the dialog
  AddAnalyseNotificationCB(_pFileDialog, 
                           _pFileDialog->GetDiaCANCELNotification(), 
		           (CATCommandMethod)&CAAPrtDialog::OpenCANCELCB,
                           NULL);
  // Shows the dialog				
  _pFileDialog->SetVisibility(CATDlgShow);
}

//--------------------------------------------------------------------
void CAAPrtDialog::OpenOKCB(CATCommand          *iPublishingCommand, 
                          CATNotification     *iNotification, 
                          CATCommandClientData iUsefulData)
{
  // Replaces the mouse cursor by a busy cursor
  // The busy cursor disappears automatically at the end of the callback
  _pApplication->SetBusyCursor();

  // Retrieves the selected file name
  CATUnicodeString fileName;
  _pFileDialog->GetSelection(fileName);

  // Displays the file image
  DisplayImage(fileName);
    
  // Deallocates the dialog. A window deallocation must be postponed until all
  // the notifications already sent are treated. That's why the  
  // RequestDelayedDestruction method must be used instead of Release.
  _pFileDialog->RequestDelayedDestruction();
}

//--------------------------------------------------------------------
void CAAPrtDialog::OpenCANCELCB(CATCommand          *iPublishingCommand,
                              CATNotification     *iNotification,    
                              CATCommandClientData iUsefulData)
{
  // Deallocates the dialog. A window deallocation must be postponed until all
  // the notifications already sent are treated. That's why the  
  // RequestDelayedDestruction method must be used instead of Release.
  _pFileDialog->RequestDelayedDestruction();
}

//--------------------------------------------------------------------
void CAAPrtDialog::PrintCB(CATCommand          *iPublishingCommand, 
                         CATNotification     *iNotification,   
                         CATCommandClientData iUsefulData)
{
  // Replaces the mouse cursor by a busy cursor
  // The busy cursor disappears automatically at the end of the callback
  _pApplication->SetBusyCursor();

  // Instantiates the Print command
  // The current dialog is the parent of the Print dialog.
  // The printable object given to the Print dialog is the viewer;
  // so the dialog will print the image drawn in the viewer.
  // The Print dialog manages its deallocation itself.
  CATPrintDialog * print = new CATPrintDialog(this, "Print", _pViewer);
    
  // shows the dialog window.
  print->SetVisibility(CATDlgShow);
}

//--------------------------------------------------------------------
void CAAPrtDialog::CaptureCB(CATCommand          *iPublishingCommand,
                           CATNotification     *iNotification,  
                           CATCommandClientData iUsefulData)
{
  // Instantiates the Capture command 
  // The current dialog is the parent of the Capture dialog.
  // The Capture dialog needs a viewer's pointer to capture an image from  
  // the viewer.
  // The Capture dialog manages its deallocation itself.

   _pCapture = new CATPrintCaptureDialog(this, "Capture", _pViewer);
   _pCapture->SetVisibility(CATDlgShow);

  // It's necessary to be prevent when the Dialog object is closed
  // to reset the pointer 
  //
    AddAnalyseNotificationCB(_pCapture, 
                             _pCapture->GetWindCloseNotification(),
                              (CATCommandMethod)&CAAPrtDialog::CloseCaptureCB, 
                              NULL );

}

//--------------------------------------------------------------------
void CAAPrtDialog::AlbumCB(CATCommand          *iPublishingCommand,
                         CATNotification     *iNotification,  
                         CATCommandClientData iUsefulData )
{
  // Instantiates the Album command 
  // The current dialog is the parent of the Album dialog.
  // The Album dialog manages its deallocation itself.
  CATPrintAlbumDialog *album = new CATPrintAlbumDialog(this, "Album");

  // shows the dialog window.
  album->SetVisibility(CATDlgShow);
}

//--------------------------------------------------------------------
void CAAPrtDialog::PrinterManagerCB(CATCommand          *iPublishingCommand,
                                  CATNotification     *iNotification,  
                                  CATCommandClientData iUsefulData)
{
  // Instantiates the Printer Manager command 
  // The current dialog is the parent of the Printer Manager dialog.
  // The Printer Manager dialog manages its deallocation itself.
  // Makes the dialog modal to prevent users's interactions outside the dialog.
  CATPrinterManagerDialog *printMan = new CATPrinterManagerDialog(this, 
              "PrintMan", CATDlgWndModal);

  // shows the dialog window.
  printMan->SetVisibility(CATDlgShow);
}

//--------------------------------------------------------------------
void CAAPrtDialog::ExitCB(CATCommand           *iPublishingCommand,  
                        CATNotification      *iNotification, 
                        CATCommandClientData  iUsefulData)
{ 
  // Releases objects used by the viewer
  // The viewer is always available here.
  Clean();
  
  // Requests application destruction by sending a close notification.
  // The application receives the same notification as if the user
  // had chosen to close the window.
  // Always send a notification to the current dialog'sparent. 
  // In this case, the parent is exactly the application.
  SendNotification(GetFather(), GetWindCloseNotification());
}

//--------------------------------------------------------------------
void CAAPrtDialog::TestDisplayCB(CATCommand            *iPublishingCommand, 
                               CATNotification       *iNotification, 
                               CATCommandClientData   iUsefulData)
{ 
  CAT2DRep * rep;
  
  // Creates an image from the input TIFF file
  CATPrintImage* image = new CAAPrtTestImage();

  // standard print parameters
  CATPrintParameters parameters;

  // To display an image, you need a representation device and a 
  // representation driver which are encapsulated into the CATPrint2Rep
  // class.
  rep = new CATPrint2DRep(image, parameters);  

  // Releases the image
  image -> Release();
   
  // Adds the representation into the viewer
  if (NULL != rep)
  {
    // Removes the possible previous representation and releases it.
    if (NULL != _pRepImage)
    {
      _pViewer->RemoveRep(_pRepImage);
      _pRepImage -> Destroy();
    }
    // Adds the representation
    _pViewer->AddRep(rep);
    // Redraws 
    _pViewer->Reframe();
    // Keeps the new representation 
    _pRepImage = rep;
  }
}

//--------------------------------------------------------------------
void CAAPrtDialog::TestPrintCB(CATCommand          *iPublishingCommand, 
                             CATNotification     *iNotification, 
                             CATCommandClientData iUsefulData)
{ 
  // Instantiates the printable object, which is also the image.
  // This instance is stored as a data member because CATPrintDialog does not 
  // Addref it.
  if (NULL != _pPrintableTest) _pPrintableTest->Release();
  _pPrintableTest = new CAAPrtTestImage ();

  // Instantiates the Print command
  // The current dialog is the parent of the Print dialog.
  // The Print dialog manages its deallocation itself.
  CATPrintDialog * Print = new CATPrintDialog(this, "StringPrint", _pPrintableTest);
  Print -> SetVisibility(CATDlgShow);    
}

//--------------------------------------------------------------------
void CAAPrtDialog::LabelPrintCB(CATCommand           *iPublishingCommand, 
                              CATNotification      *iNotification,
                              CATCommandClientData  iUsefulData)
{ 
  // Instantiates the command which manages its life cycle itself.
  CAAPrtStringDialog * labelPrintCmd = new CAAPrtStringDialog(this, "labelPrintCmd");

  // Fills the dialog window.
  labelPrintCmd->Init();

  // Shows the dialog window.
  labelPrintCmd->SetVisibility(CATDlgShow);
}


//--------------------------------------------------------------------

void CAAPrtDialog::CloseCaptureCB(CATCommand          *iPublishingCommand,
                                  CATNotification     *iNotification,
                                  CATCommandClientData iUsefulData)
{
   cout << "The Dialog Object Capture is Closed" << endl;
   _pCapture = NULL ;
}





