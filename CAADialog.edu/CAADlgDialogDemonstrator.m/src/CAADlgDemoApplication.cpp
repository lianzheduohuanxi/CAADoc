// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgDemoApplication.h"

#include "CAADlgDemoWindow.h"

//C++ Standard Library
#include <iostream.h>
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

CAADlgDemoApplication::CAADlgDemoApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) 
{

  cout << endl <<"The CAADlgDemoApplication begins..... " <<endl << endl;
}

//------------------------------------------------------------------------

CAADlgDemoApplication::~CAADlgDemoApplication() 
{
  cout << endl <<"The CAADlgDemoApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAADlgDemoApplication::BeginApplication() 
{
  cout <<"CAADlgDemoApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAADlgDemoWindow::Exit method.
  //
  CAADlgDemoWindow * pMainWindow ;
  pMainWindow = new CAADlgDemoWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);
}

//------------------------------------------------------------------------

int CAADlgDemoApplication::EndApplication() 
{
  cout << endl << "CAADlgDemoApplication::EndApplication" << endl;

  // OK
  return(0);
}


//------------------------------------------------------------------------

// Application created
CAADlgDemoApplication ApplicationInstance("DialogDemonstrator");


