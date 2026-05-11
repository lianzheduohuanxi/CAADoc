// COPYRIGHT DASSAULT SYSTEMES 2007

#ifdef _WINDOWS_SOURCE
#pragma warning (disable : 4355)
// "this" used in base initializer list warning.  This
// can be disabled because we are not using "this" in
// the constructor for these objects, rather we are
// just storing it for future use...
#endif /* _WINDOWS_SOURCE */

#include "CATTestListViewAppli.h"
#include "CATTestListViewDocument.h"

CATTestListViewAppli::CATTestListViewAppli() 
                     :CATInteractiveApplication(this, "CATViewTester")
{
  _doc = NULL;
}

CATTestListViewAppli::~CATTestListViewAppli()
{
  _doc = NULL;
}

void CATTestListViewAppli::BeginApplication()
{
  // This window is deleted when the application is deleted.
  // The application is deleted by the Destroy Method called in the 
  // CATTestListViewAppli::DestroyApplication method.
  //------------------------------------------------------------------
  _doc = new CATTestListViewDocument(this, "P3Visu",0);
  _doc->SetTitle("CATView Test");
  _doc->SetVisibility(CATDlgShow);
}

int CATTestListViewAppli::EndApplication()
{
  return 0;
}

void CATTestListViewAppli::DestroyApplication()
{
  Destroy();
}
//----------------------------------
//  Instantiation of the Applicaton
//----------------------------------
CATTestListViewAppli CATViewTest;
