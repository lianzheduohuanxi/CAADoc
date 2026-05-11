// COPYRIGHT DASSAULT SYSTEMES 2008

//Local Framework
#include "CAAIDDBasicCalcApplication.h"
#include "CATDlgDocument.h"
#include "CAAIDDBasicCalcDialog.h"

// C++ Standard library
#include "iostream.h"

//-------------------------------------------------------------------------------
CAAIDDBasicCalcApplication::CAAIDDBasicCalcApplication(const CATString& iApplicationId)
                    : CATInteractiveApplication(NULL, iApplicationId)
{
  cout << "CAAIDDBasicCalcApplication::CAAIDDBasicCalcApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAIDDBasicCalcApplication::BeginApplication()
{
  cout << "CAAIDDBasicCalcApplication::BeginApplication" << endl;

  // Creation of root document & designed child dialog box
  //
  CATDlgDocument* pDocument = new CATDlgDocument(this, "Document");
  CAAIDDBasicCalcDialog * pMainWindow ;
  pMainWindow = new CAAIDDBasicCalcDialog(pDocument, "BurgerId");

  // Register to root document closure
  AddAnalyseNotificationCB(pDocument, pDocument->GetWindCloseNotification(), (CATCommandMethod)&CAAIDDBasicCalcApplication::onExit, NULL);

  // Constructs all Dialog'objects of the window
  pMainWindow->Build();

  // Make root document & dialog visible
  pDocument->SetVisibility(CATDlgShow);
  pMainWindow->SetVisibility(CATDlgShow);

}

//-------------------------------------------------------------------------------

int CAAIDDBasicCalcApplication::EndApplication()
{              
  cout << "CAAIDDBasicCalcApplication::EndApplication Begin" << endl;

  // OK 
  return 0;
}

//-------------------------------------------------------------------------------

CAAIDDBasicCalcApplication::~CAAIDDBasicCalcApplication()
{
  cout << "CAAIDDBasicCalcApplication::~CAAIDDBasicCalcApplication" << endl;
}

//-------------------------------------------------------------------------------

void CAAIDDBasicCalcApplication::onExit(CATCommand* iSendingCommand, CATNotification* iSentNotification, CATCommandClientData iUsefulData) {
	this->Destroy();
}


//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CAAIDDBasicCalcApplication ApplicationInstance("CAAIDDBasicCalc");
