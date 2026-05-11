// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAACafComboApplication.h"
#include "CAACafComboWindow.h"

//C++ Standard Library
#include <iostream.h>


//-------------------------------------------------------------------------

CAACafComboApplication::CAACafComboApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) 
{
  cout << endl <<"The CAACafComboApplication begins..... " <<endl << endl;
}

//------------------------------------------------------------------------

CAACafComboApplication::~CAACafComboApplication() 
{
  cout << endl <<"The CAACafComboApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAACafComboApplication::BeginApplication() 
{
  cout <<"CAACafComboApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAACafComboWindow::Exit method.
  //
  CAACafComboWindow * pMainWindow ;
  pMainWindow = new CAACafComboWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);
}

//------------------------------------------------------------------------

int CAACafComboApplication::EndApplication() 
{
  cout << endl << "CAACafComboApplication::EndApplication" << endl;

  // OK
  return(0);
}


//------------------------------------------------------------------------

// Application created
CAACafComboApplication ApplicationInstance("GraphicPropertiesCombo");


