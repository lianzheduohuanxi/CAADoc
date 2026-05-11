// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisRepApplication.h"
#include "CAAVisRepWindow.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAAVisRepApplication::CAAVisRepApplication(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAAVisRepApplication::CAAVisRepApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAVisRepApplication::BeginApplication()
{
  cout << "CAAVisRepApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAAVisRepWindow::Exit method.
  //
  CAAVisRepWindow * pMainWindow ;
  pMainWindow = new CAAVisRepWindow(this);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAAVisRepApplication::EndApplication()
{              
  cout << "CAAVisRepApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAAVisRepApplication::~CAAVisRepApplication()
{
  cout << "CAAVisRepApplication::~CAAVisRepApplication" << endl;
}

//-------------------------------------------------------------------------------


//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAAVisRepApplication ApplicationInstance("CAAVisRepAppplicationInstance");
