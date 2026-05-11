// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgBBReceiverApplication.h"

#include "CAADlgBBReceiverWindow.h"

//C++ Standard Library
#include <iostream.h>
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

CAADlgBBReceiverApplication::CAADlgBBReceiverApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) 
{

  cout << endl <<"The CAADlgBBReceiverApplication begins..... " <<endl << endl;
}

//------------------------------------------------------------------------

CAADlgBBReceiverApplication::~CAADlgBBReceiverApplication() 
{
  cout << endl <<"The CAADlgBBReceiverApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAADlgBBReceiverApplication::BeginApplication() 
{
  cout <<"CAADlgBBReceiverApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAADlgBBReceiverWindow::Exit method.
  //
  CAADlgBBReceiverWindow * pMainWindow ;
  pMainWindow = new CAADlgBBReceiverWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);
}

//------------------------------------------------------------------------

int CAADlgBBReceiverApplication::EndApplication() 
{
  cout << endl << "CAADlgBBReceiverApplication::EndApplication" << endl;

  // OK
  return(0);
}


//------------------------------------------------------------------------

// Application created
CAADlgBBReceiverApplication ApplicationInstance("BBReceiver");


