// COPYRIGHT DASSAULT SYSTEMES 2006

//Local Framework
#include "CAABasicAuthenticationPanelApplication.h"
#include "CAABasicAuthenticationPanelWindow.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAABasicAuthenticationPanelApplication::CAABasicAuthenticationPanelApplication(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAABasicAuthenticationPanelApplication::CAABasicAuthenticationPanelApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAABasicAuthenticationPanelApplication::BeginApplication()
{
  cout << "CAABasicAuthenticationPanelApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAABasicAuthenticationPanelWindow::Dismiss method.
  //
  CAABasicAuthenticationPanelWindow * pMainWindow ;
  pMainWindow = new CAABasicAuthenticationPanelWindow(this, "BasicAuthenticationPanelId", CATDlgGridLayout);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();
  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAABasicAuthenticationPanelApplication::EndApplication()
{              
  cout << "CAABasicAuthenticationPanelApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAABasicAuthenticationPanelApplication::~CAABasicAuthenticationPanelApplication()
{
  cout << "CAABasicAuthenticationPanelApplication::~CAABasicAuthenticationPanelApplication" << endl;
}

//-------------------------------------------------------------------------------


//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAABasicAuthenticationPanelApplication ApplicationInstance("BasicAuthenticationPanel");
