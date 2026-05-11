// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAADlgHelloWindow.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgInclude.h"                // For the label

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAADlgHelloWindow::CAADlgHelloWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, "CAADlgHelloWindowId"),_pHelloApplication(iParentCommand)

{
  cout << "CAADlgHelloWindow::CAADlgHelloWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAADlgHelloWindow::~CAADlgHelloWindow()
{ 
  cout << "CAADlgHelloWindow::~CAADlgHelloWindow" << endl; 
  _pHelloApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAADlgHelloWindow::Build()
{
  cout << "CAADlgHelloWindow::Build" << endl;

  // The text
  CATDlgLabel * pLabel = new CATDlgLabel(this,"MessageId");

  // On the Close 
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAADlgHelloWindow::Exit, NULL);

}

//--------------------------------------------------------------------------------------

void CAADlgHelloWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pHelloApplication->Destroy();
   _pHelloApplication = NULL ;
}


