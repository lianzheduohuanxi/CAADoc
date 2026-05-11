// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgInterApplication.h"

#include "CAADlgInterWindow.h"

//C++ Standard Library
#include <iostream.h>
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

CAADlgInterApplication::CAADlgInterApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) 
{

  cout << endl <<"The CAADlgInterApplication begins..... " <<endl << endl;
}

//------------------------------------------------------------------------

CAADlgInterApplication::~CAADlgInterApplication() 
{
  cout << endl <<"The CAADlgInterApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAADlgInterApplication::BeginApplication() 
{
  cout <<"CAADlgInterApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAADlgInterWindow::Exit method.
  //
  CAADlgInterWindow * pMainWindow ;
  pMainWindow = new CAADlgInterWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);
}

//------------------------------------------------------------------------

int CAADlgInterApplication::EndApplication() 
{
  cout << endl << "CAADlgInterApplication::EndApplication" << endl;

  // OK
  return(0);
}


//------------------------------------------------------------------------

// Application created
CAADlgInterApplication ApplicationInstance("Inter");


