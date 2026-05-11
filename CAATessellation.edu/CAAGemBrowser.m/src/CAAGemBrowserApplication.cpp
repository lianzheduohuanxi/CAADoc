
// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAGemBrowserApplication.h"
#include "CAAGemBrowserDocument.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAAGemBrowserApplication::CAAGemBrowserApplication(const CATString& iApplicationId)
                           : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAAGemBrowserApplication::CAAGemBrowserApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAGemBrowserApplication::BeginApplication()
{
  cout << "CAAGemBrowserApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAAGemBrowserDocument::Exit method.
  //
  CAAGemBrowserDocument * pMainWindow =NULL;
  pMainWindow = new CAAGemBrowserDocument(this);

  // Constructs all Dialog objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAAGemBrowserApplication::EndApplication()
{              
  cout << "CAAGemBrowserApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAAGemBrowserApplication::~CAAGemBrowserApplication()
{
  cout << "CAAGemBrowserApplication::~CAAGemBrowserApplication" << endl;
}

//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAAGemBrowserApplication ApplicationInstance("CAAGemBrowserApplicationInstance");
//CAAGemBrowserApplication ApplicationInstance("CAAVisBasicAppplicationInstance");
//




