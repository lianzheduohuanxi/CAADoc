// COPYRIGHT DASSAULT SYSTEMES 2003

#include "CAADlgHelloApplication.h"

#include "CAADlgHelloWindow.h"

//C++ Standard Library
#include <iostream.h>
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

CAADlgHelloApplication::CAADlgHelloApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) 
{

  cout << endl <<"The CAADlgHelloApplication begins..... " <<endl << endl;
}

//------------------------------------------------------------------------

CAADlgHelloApplication::~CAADlgHelloApplication() 
{
  cout << endl <<"The CAADlgHelloApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAADlgHelloApplication::BeginApplication() 
{
  cout <<"CAADlgHelloApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAADlgHelloWindow::Exit method.
  //
  CAADlgHelloWindow * pMainWindow = NULL;
  pMainWindow = new CAADlgHelloWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);
}

//------------------------------------------------------------------------

int CAADlgHelloApplication::EndApplication() 
{
  cout << endl << "CAADlgHelloApplication::EndApplication" << endl;

  // OK
  return(0);
}


//------------------------------------------------------------------------

// Application created
CAADlgHelloApplication ApplicationInstance("Hello");


