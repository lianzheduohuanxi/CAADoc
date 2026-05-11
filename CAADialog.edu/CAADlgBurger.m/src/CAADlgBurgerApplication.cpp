// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADlgBurgerApplication.h"
#include "CAADlgBurgerWindow.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAADlgBurgerApplication::CAADlgBurgerApplication(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAADlgBurgerApplication::CAADlgBurgerApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAADlgBurgerApplication::BeginApplication()
{
  cout << "CAADlgBurgerApplication::BeginApplication" << endl;

  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CAADlgBurgerWindow::Dismiss method.
  //
  CAADlgBurgerWindow * pMainWindow ;
  pMainWindow = new CAADlgBurgerWindow(this, "BurgerId", CATDlgGridLayout);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();
  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAADlgBurgerApplication::EndApplication()
{              
  cout << "CAADlgBurgerApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAADlgBurgerApplication::~CAADlgBurgerApplication()
{
  cout << "CAADlgBurgerApplication::~CAADlgBurgerApplication" << endl;
}

//-------------------------------------------------------------------------------


//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAADlgBurgerApplication ApplicationInstance("Burger");
