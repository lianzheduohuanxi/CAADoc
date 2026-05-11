// COPYRIGHT DASSAULT SYSTEMES 1999 - 2000

// CAALiteralFeatures headers
#include "CAALifApplication2.h"
#include "CAALifWindow2.h"
#include "CAALifServices.h"

// C++ Standard library
#include "iostream.h"


CATImplementClass(CAALifApplication2, Implementation, CATApplication,
CATNull );

//---------------------------------------------------------------------
CAALifApplication2::CAALifApplication2(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAALifApplication2::CAALifApplication2" << endl;
  _services = new CAALifServices();

}

//---------------------------------------------------------------------

void CAALifApplication2::BeginApplication()
{
  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy method called in the 
  // CAALifWindow::Exit method.
  //
  CAALifWindow2 * pMainWindow ;
  pMainWindow = new CAALifWindow2(this);

       
  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  pMainWindow->SetVisibility(CATDlgShow);

}

//-----------------------------------------------------------------------

int CAALifApplication2::EndApplication()
{              
  int rc =  0;
  // Closes the application
  // OK 
  return rc;
}

void CAALifApplication2::GetServices(CAALifServices** oServices)
{
	*oServices = _services;
}

//-----------------------------------------------------------------------

CAALifApplication2::~CAALifApplication2()
{
  	delete _services;
		_services = NULL;	
  	cout << "CAALifApplication2::~CAALifApplication2" << endl;
}

//-----------------------------------------------------------------------


//----------------------------------
//  Instantiation of the Application
//----------------------------------
CAALifApplication2 ApplicationInstance("CAALifAppplicationInstance");
