// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgBBSenderApplication.h"
#include "CAADlgBBSenderWindow.h"

//C++ Standard Library
#include <iostream.h>
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

CAADlgBBSenderApplication::CAADlgBBSenderApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier)
{
  cout << endl <<"The CAADlgBBSenderApplication begins..... " <<endl << endl;
}

//------------------------------------------------------------------------

CAADlgBBSenderApplication::~CAADlgBBSenderApplication() 
{
  cout << endl <<"The CAADlgBBSenderApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAADlgBBSenderApplication::BeginApplication() 
{
  cout <<"CAADlgBBSenderApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAADlgBBSenderWindow::Exit method.
  //
  CAADlgBBSenderWindow * pMainWindow ;
  pMainWindow = new CAADlgBBSenderWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);

}

//------------------------------------------------------------------------

int CAADlgBBSenderApplication::EndApplication() 
{
  cout << endl << "CAADlgBBSenderApplication::EndApplication" << endl;

  // OK
  return(0);
}


//------------------------------------------------------------------------

// Application created
CAADlgBBSenderApplication ApplicationInstance("BBSender");


