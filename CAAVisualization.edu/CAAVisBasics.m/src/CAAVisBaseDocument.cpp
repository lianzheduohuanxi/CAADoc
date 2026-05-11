// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAVisBaseDocument.h"
#include "CAAVisBaseView.h"

//Visualization Framework
#include "CAT3DBagRep.h"
#include "CATReadWriteCgr.h"  //For the InsertModel method
#include "CATViewer.h"

int CAAVisBaseDocument::_ViewName = 0;

//-------------------------------------------------------------------------------

CAAVisBaseDocument::CAAVisBaseDocument(CATDialog *iDialogParent,
                                       const char * iDocumentName)
{
  _pRootContainer = NULL;
  
  //Creation of the document's view:
  // - Creates a dialog object (window)
  // - Creates a viewer in this window, where
  //   our 3D graphical data will be visualized.
  CreateDocView(iDialogParent, iDocumentName);
}

//-------------------------------------------------------------------------------

CAAVisBaseDocument::~CAAVisBaseDocument()
{
  //We must deallocate the memory used for the model.
  DeleteModel();

  _pView = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseDocument::CreateDocView(CATDialog * iDialogParent,
                                       const char *iDocViewName)
{
  char viewName[20];
  
  sprintf(viewName, "View%d", _ViewName);
  _ViewName++;
  
  _pView = new CAAVisBaseView(iDialogParent, this, viewName);
  
  _pView->Build();

  //Set the document view window title.
  //We want our window to have the name of the
  //file we load, with its path.
  //So, we're passing through a SetTitle
  //and not through a NLS file.
  CATUnicodeString viewTitle(iDocViewName);
  _pView->SetTitle(viewTitle);

  _pView->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------------

CAAVisBaseView * CAAVisBaseDocument::GetView()
{
  return _pView;
}

//-------------------------------------------------------------------------------

void CAAVisBaseDocument::CreateModel()
{
  //The implementation is let to the inherited classes.
}

//-------------------------------------------------------------------------------

void CAAVisBaseDocument::DeleteModel()
{
  if( NULL != _pRootContainer)
  {
      // An object inherited from CATRep must never be
      // deallocated by "delete". One must called the
      // "Destroy" method on it.
      _pRootContainer->Destroy();
      _pRootContainer = NULL;
  }
}

//-------------------------------------------------------------------------------

CAT3DBagRep * CAAVisBaseDocument::GetModel()
{
  return _pRootContainer;
}

//-------------------------------------------------------------------------------

void CAAVisBaseDocument::InsertModel(const char *iCGRFileName)
{
  if(NULL == _pRootContainer)
  {
      //If no container exists, one must create it:
      _pRootContainer = new CAT3DBagRep;
  }

  //Reading of the CGR file. We get a pointer to CAT3DRep. 
  CAT3DRep *pBagToInsert = CATReadCgr((char *)iCGRFileName,
                                      USE_LODS_TEXTURE_EDGE);
  if(NULL != pBagToInsert)
  {
      _pRootContainer->AddChild(*pBagToInsert);
  }

  CATViewer *pViewer = _pView->GetViewer();

  if(NULL != pViewer)
  {
     pViewer->Draw();
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseDocument::AddRepToViewer()
{
  _pView->Add3DRep(_pRootContainer);
}

//-------------------------------------------------------------------------------
