// COPYRIGHT DASSAULT SYSTEMES 1999 - 2000

// CAALiteralFeatures headers
#include "CAALifApplication.h"
#include "CAALifWindow.h"
#include "CAALifServices.h"

// C++ Standard library
#include "iostream.h"

//---------------------------------------------------------------------
CAALifApplication::CAALifApplication(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAALifApplication::CAALifApplication" << endl;
  _services = new CAALifServices();

}

//---------------------------------------------------------------------

void CAALifApplication::BeginApplication()
{
  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy method called in the 
  // CAALifWindow::Exit method.
  //
  CAALifWindow * pMainWindow ;
  pMainWindow = new CAALifWindow(this);

       
  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);

}

//-----------------------------------------------------------------------

int CAALifApplication::EndApplication()
{              
  int rc =  0;
  // Closes the application
  // OK 
  return rc;
}

void CAALifApplication::GetServices(CAALifServices** oServices)
{
	*oServices = _services;
}

//-----------------------------------------------------------------------

CAALifApplication::~CAALifApplication()
{
  	delete _services;
		_services = NULL;	
  	cout << "CAALifApplication::~CAALifApplication" << endl;
}

//-----------------------------------------------------------------------


//----------------------------------
//  Instantiation of the Application
//----------------------------------
CAALifApplication ApplicationInstance("CAALifAppplicationInstance");
