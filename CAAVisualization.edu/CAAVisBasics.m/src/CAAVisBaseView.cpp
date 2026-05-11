// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAVisBaseView.h"

//Visualization Framework
#include "CATNavigation3DViewer.h"
#include "CAT3DRep.h"

//Dialog Framework
#include "CATDlgDocument.h"

//-------------------------------------------------------------------------------

CATImplementCBEvent(CAAVisBaseView, WINDOW_ACTIVATED  , "WINDOW_ACTIVATED"  )
CATImplementCBEvent(CAAVisBaseView, WINDOW_DELETED    , "WINDOW_DELETED"    )

//-------------------------------------------------------------------------------
  
CAAVisBaseView::CAAVisBaseView(CATDialog *iDialogParent,
                               CATBaseUnknown *iDocument,
                               const char *iName)
: CATDlgDialog(iDialogParent, iName, CATDlgWndNoButton | CATDlgWndChildMDI)
{
  _pDocument    = iDocument;
  _pDlgDocument = (CATDlgDocument *)iDialogParent ;
  _pViewer      = NULL ;
}

//-------------------------------------------------------------------------------

CAAVisBaseView::~CAAVisBaseView()
{
  _pDocument    = NULL ;
  _pViewer      = NULL ;
  _pDlgDocument = NULL ;
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::Build()
{
  //Here we are creating the 3D viewer which remains inside our
  //window
  CreateViewer();

  //In order to be warned when the window is
  //activated, maximized, ...
  AddMDICallbacks();
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::DeleteView()
{
  // Warns the other objects that we're deleting the window.
  // The objects which took out a subscription to the
  // WINDOW_ACTIVATED event will be warned, thanks to this call:
  ::GetDefaultCallbackManager(this)->DispatchCallbacks(WINDOW_DELETED(), NULL, (void *)this);
  
  // Deallocates the dialog. A window deallocation must be postponed until all
  // the notifications already sent are treated. That's why the  
  // RequestDelayedDestruction method must be used instead of Release.

  RequestDelayedDestruction();

  SetVisibility(CATDlgHide);
}

//-------------------------------------------------------------------------------

CATBaseUnknown * CAAVisBaseView::GetDocument()
{
  return _pDocument;
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::CreateViewer()
{
  _pViewer = new CATNavigation3DViewer(this, "3DViewer",
                                      CATDlgFraNoTitle | CATDlgFraNoFrame,
                                      500, 500);
  //We want the viewer to be as large as the window
  Attach4Sides(_pViewer);
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::AddMDICallbacks()
{

  AddAnalyseNotificationCB(this,
                           GetMDICloseNotification()   ,
                           (CATCommandMethod)&CAAVisBaseView::MDICB ,
                           (CATCommandClientData)CATINT32ToPtr(0));
  
  AddAnalyseNotificationCB(this,
                           GetMDIActivateNotification()   ,
                           (CATCommandMethod)&CAAVisBaseView::MDICB ,
                           (CATCommandClientData)CATINT32ToPtr(1));
  
  AddAnalyseNotificationCB(this,
                           GetMDIMaximizeNotification()   ,
                           (CATCommandMethod)&CAAVisBaseView::MDICB ,
                           (CATCommandClientData)CATINT32ToPtr(2));
  
  AddAnalyseNotificationCB(this,
                           GetMDIRestoreNotification()   ,
                           (CATCommandMethod)&CAAVisBaseView::MDICB ,
                           (CATCommandClientData)CATINT32ToPtr(3));
  
  AddAnalyseNotificationCB(this,
                           GetMDIMinimizeNotification()   ,
                           (CATCommandMethod)&CAAVisBaseView::MDICB ,
                           (CATCommandClientData)CATINT32ToPtr(4)); 
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::Add3DRep(CAT3DRep * rep)
{
  _pViewer->AddRep(rep);
}

//-------------------------------------------------------------------------------

CATViewer * CAAVisBaseView::GetViewer()
{
  return _pViewer;
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::MDICB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  int cmd = CATPtrToINT32(iData);
  
  switch ( cmd )
    {
    case 0 : 
      DeleteView();
      break;
    case 1:
      OnWindowActivated();
      break;
    case 2 :
      _pDlgDocument->MDIMaximize(this);
      break;
    case 3:
      _pDlgDocument->MDIRestore(this);
      break;
    case 4:
      _pDlgDocument->MDIMinimize(this);
      break;
    };
}

//-------------------------------------------------------------------------------

void CAAVisBaseView::OnWindowActivated()
{
  //The objects which took out a subscription to the
  // WINDOW_ACTIVATED event will be warned, thanks to this call:
  ::GetDefaultCallbackManager(this)->DispatchCallbacks(WINDOW_ACTIVATED(), NULL, (void *)this);
}

//-------------------------------------------------------------------------------
