// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgInterWindow.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAADlgInterWindow::CAADlgInterWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, "CAADlgInterWindowId"),_pApplication(iParentCommand)

{
  cout << "CAADlgInterWindow::CAADlgInterWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAADlgInterWindow::~CAADlgInterWindow()
{ 
  cout << "CAADlgInterWindow::~CAADlgInterWindow" << endl; 
  _pApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAADlgInterWindow::Build()
{
  cout << "CAADlgInterWindow::Build" << endl;

  // On the Close 
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAADlgInterWindow::Exit, NULL);

}

//--------------------------------------------------------------------------------------

void CAADlgInterWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}


