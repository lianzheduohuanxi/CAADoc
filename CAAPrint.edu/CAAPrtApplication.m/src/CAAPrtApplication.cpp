// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAPrtApplication.h"  // header file of the current class
#include "CAAPrtDialog.h"       // Print dialog window

#include <iostream.h>
//-------------------------------------------------------------------------
CAAPrtApplication::CAAPrtApplication(const CATString& iIdentifier):
              CATInteractiveApplication(NULL, iIdentifier) 
{
}

//-------------------------------------------------------------------------
CAAPrtApplication::~CAAPrtApplication()
{
}

//-------------------------------------------------------------------------
void CAAPrtApplication::BeginApplication()
{
  //-----------------------------------------------------------------
  // 1- Creates the Application Window
  //-----------------------------------------------------------------
  CAAPrtDialog * pMainWindow = NULL ;
  pMainWindow  = new CAAPrtDialog(this,               // Dialog parent   
                                  "mainWindow",        // Identifier 
                                  CATDlgWndNoResize);  // Dialog style
  // Creates the window contents
  pMainWindow->Init();
  
  // Shows the window  
  pMainWindow->SetVisibility(CATDlgShow);

  //-----------------------------------------------------------------
  // 2- Subscribes to the window closing 
  //-----------------------------------------------------------------
  AddAnalyseNotificationCB(pMainWindow,  // The publisher 
                           pMainWindow->GetWindCloseNotification(), 
                                         // The notification of window closing
                           (CATCommandMethod)& CAAPrtApplication:: DestroyCB, 
                                         // The method to execute when receiving the notification
                           NULL);        // Data to pass to the method

  //-----------------------------------------------------------------
  // 3- Retrieves the command line argument and calls the image displaying
  //    method if needed
  //-----------------------------------------------------------------
  int argc;
  char** argv = NULL ;
  GetArgs(&argc, &argv);

  if ( 2 == argc )
  {
        pMainWindow->DisplayImage(argv[1]);
  }
}

//-------------------------------------------------------------------------
void CAAPrtApplication::DestroyCB(CATCommand            * iPublishingCommand, 
                                   CATNotification      * iNotification, 
                                   CATCommandClientData   iUsefulData)
{ 
  // Destruction of the application, and of the main window 
  Destroy();
}

//-------------------------------------------------------------------------
int CAAPrtApplication::EndApplication()
{    
    return 0;
}


//-------------------------------------------------------------------------
CAAPrtApplication printApp("CAAPrtApplication");










