// COPYRIGHT DASSAULT SYSTEMES 2008

//Local Framework
#include "CAAIDDBurgerApplication.h"
#include "CATDlgDocument.h"
#include "CAAIDDBurgerDialog.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAAIDDBurgerApplication::CAAIDDBurgerApplication(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAAIDDBurgerApplication::CAAIDDBurgerApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAIDDBurgerApplication::BeginApplication()
{
  cout << "CAAIDDBurgerApplication::BeginApplication" << endl;

  // Creation of root document & designed child dialog box
  //
  CATDlgDocument* pDocument = new CATDlgDocument(this, "Document");
  CAAIDDBurgerDialog * pMainWindow ;
  pMainWindow = new CAAIDDBurgerDialog(pDocument, "BurgerId");

  // Register to root document closure
  AddAnalyseNotificationCB(pDocument, pDocument->GetWindCloseNotification(), (CATCommandMethod)&CAAIDDBurgerApplication::onExit, NULL);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  // Make root document & dialog visible
  pDocument->SetVisibility(CATDlgShow);
  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAAIDDBurgerApplication::EndApplication()
{              
  cout << "CAAIDDBurgerApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAAIDDBurgerApplication::~CAAIDDBurgerApplication()
{
  cout << "CAAIDDBurgerApplication::~CAAIDDBurgerApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAIDDBurgerApplication::onExit(CATCommand* iSendingCommand, CATNotification* iSentNotification, CATCommandClientData iUsefulData) {
	this->Destroy();
}


//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAAIDDBurgerApplication ApplicationInstance("CAAIDDBurger");
