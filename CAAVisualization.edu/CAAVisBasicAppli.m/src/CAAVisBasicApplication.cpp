// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBasicApplication.h"
#include "CAAVisBasicWindow.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAAVisBasicApplication::CAAVisBasicApplication(const CATString& iApplicationId)
                           : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAAVisBasicApplication::CAAVisBasicApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAVisBasicApplication::BeginApplication()
{
  cout << "CAAVisBasicApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAAVisBasicWindow::Exit method.
  //
  CAAVisBasicWindow * pMainWindow ;
  pMainWindow = new CAAVisBasicWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAAVisBasicApplication::EndApplication()
{              
  cout << "CAAVisBasicApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAAVisBasicApplication::~CAAVisBasicApplication()
{
  cout << "CAAVisBasicApplication::~CAAVisBasicApplication" << endl;
}

//-------------------------------------------------------------------------------


//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAAVisBasicApplication ApplicationInstance("CAAVisBasicAppplicationInstance");
