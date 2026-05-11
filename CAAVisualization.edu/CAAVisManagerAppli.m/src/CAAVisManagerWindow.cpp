// COPYRIGHT DASSAULT SYSTEMES 1999
#include "CAAVisManagerWindow.h"

// Visualization FrameWork
#include "CATViewer.h"
#include "CATNavigation3DViewer.h"
#include "CAT2DViewpoint.h"
#include "CAT3DViewpoint.h"
#include "CATIndicator.h"
#include "CATVisManager.h"
#include "CATPathElement.h"
#include "CATI3DGeoVisu.h"
#include "CATI2DGeoVisu.h"
#include "CAAIVis2DGraphVisu.h"
#include "CAT3DIndicator.h"

//Local FrameWork
#include "CAAVisManagerWindowDeleteNotif.h"
#include "CAAVisManagerWindowActivateNotif.h"
#include "CAAVisManagerApplication.h"
#include "CAAVisManagerEditor.h"
#include "CAAVisManagerCmdSelector.h"
#include "CAAVisManagerDocument.h"

// Dialog Framework
#include "CATDlgDocument.h"

// C++ Standard Library
#include <iostream.h>


//-------------------------------------------------------------------------------

CATImplementClass( CAAVisManagerWindow, Implementation, CATDlgDialog, CATNull ) ;

//-------------------------------------------------------------------------------

CATImplementCBEvent(CAAVisManagerWindow, WINDOW_ACTIVATED  , "WINDOW_ACTIVATED"  )
CATImplementCBEvent(CAAVisManagerWindow, WINDOW_DEACTIVATED, "WINDOW_DEACTIVATED")
CATImplementCBEvent(CAAVisManagerWindow, WINDOW_DELETED    , "WINDOW_DELETED"    )
CATImplementCBEvent(CAAVisManagerWindow, WINDOW_CREATED    , "WINDOW_CREATED"    )
CATImplementCBEvent(CAAVisManagerWindow, VIEWER_SELECTED   , "VIEWER_SELECTED"   )
CATImplementCBEvent(CAAVisManagerWindow, VIEWER_ACTIVATED  , "VIEWER_ACTIVATED"  )
CATImplementCBEvent(CAAVisManagerWindow, VIEWPOINT_CHANGED , "VIEWPOINT_CHANGED" )
CATImplementCBEvent(CAAVisManagerWindow,VIEWER_SHOW,"VIEWER_SHOW")
CATImplementCBEvent(CAAVisManagerWindow,VIEWER_NO_SHOW,"VIEWER_NO_SHOW")
  
//-------------------------------------------------------------------------------

CAAVisManagerWindow::CAAVisManagerWindow(CAAVisManagerEditor *iEditor,
                                         const CATString &iWindowId) 
             :CATDlgDialog((CATDialog*)CAAVisManagerApplication::GetFrame(),
                           iWindowId,
                           CATDlgWndNoButton|CATDlgWndChildMDI)
             ,_pViewer(NULL)
             ,_pRootObjectPath(NULL)
             ,_pSavedBackgrdIndicator(NULL)
             ,_pDocBackgrdIndicator(NULL)
             ,_pEditor(iEditor)
{
    cout << "CAAVisManagerWindow::CAAVisManagerWindow"<< endl;
}

//-------------------------------------------------------------------------------

CAAVisManagerWindow::~CAAVisManagerWindow()
{
   cout << "CAAVisManagerWindow::~CAAVisManagerWindow"<< endl;
   _pViewer = NULL;
   
   if ( NULL != _pRootObjectPath )
   {
      _pRootObjectPath->Release() ;
      _pRootObjectPath = NULL ;
   }
      
   _pEditor = NULL ;

   _pSavedBackgrdIndicator = NULL ;

   // this indicator is deleted in the DeleteWindow method
   // This method must be called before the destructor 
   // 
   _pDocBackgrdIndicator = NULL ;

}

//-------------------------------------------------------------------------------

CAAVisManagerWindow * CAAVisManagerWindow::DuplicateWindow()
{
  return NULL;
}

//-------------------------------------------------------------------------------
void CAAVisManagerWindow::Build()
{
   if ( NULL != _pEditor )
   {
      _pViewer = new CATNavigation3DViewer(this,"Nav3D",
                                   CATDlgFraNoTitle|CATDlgFraNoFrame,300,400);

      // Behavior of the  Viewer: Preselect permise
      _pViewer->SetPreselectModeOn();

      // pViewer takes the full place in the window
      Attach4Sides( _pViewer );

      // Callbacks on the window
      AddCB();

      // Relationship with the visu manager
      Attach();

      ChangeBackgroundIndicator();
   }
}
//-------------------------------------------------------------------------------

CATViewer * CAAVisManagerWindow::GetViewer(void)
{
  return _pViewer;
}

//-------------------------------------------------------------------------------

void  CAAVisManagerWindow::DeleteWindow()
{
   if ( NULL != _pEditor )
   {
      // Manage detachment of viewpoints from the Visu Manager
      Detach();

      // Manage the deletion of the Background indicator
      ResetBackgroundIndicator() ;
   }
}

//-------------------------------------------------------------------------------

void CAAVisManagerWindow::AddCB(void)
{
  AddAnalyseNotificationCB(this,
    GetWindCloseNotification()   ,
    (CATCommandMethod)&CAAVisManagerWindow::MDICB ,
    (CATCommandClientData)CATINT32ToPtr(0));

   AddAnalyseNotificationCB(this,
			    GetMDICloseNotification()   ,
			    (CATCommandMethod)&CAAVisManagerWindow::MDICB ,
			    (CATCommandClientData)CATINT32ToPtr(0));

   AddAnalyseNotificationCB(this,
			    GetMDIActivateNotification()   ,
			    (CATCommandMethod)&CAAVisManagerWindow::MDICB ,
          (CATCommandClientData)CATINT32ToPtr(1));
   
   AddAnalyseNotificationCB(this,
     GetMDIMaximizeNotification()   ,
     (CATCommandMethod)&CAAVisManagerWindow::MDICB ,
     (CATCommandClientData)CATINT32ToPtr(2));

   AddAnalyseNotificationCB(this,
     GetMDIRestoreNotification()   ,
     (CATCommandMethod)&CAAVisManagerWindow::MDICB ,
     (CATCommandClientData)CATINT32ToPtr(3));

   AddAnalyseNotificationCB(this,
     GetMDIMinimizeNotification()   ,
     (CATCommandMethod)&CAAVisManagerWindow::MDICB ,
     (CATCommandClientData)CATINT32ToPtr(4));
}


//-------------------------------------------------------------------------------

void CAAVisManagerWindow::MDICB(CATCommand *command, CATNotification *notification, CATCommandClientData data)
{
  int cmd = CATPtrToINT32(data);
  
  switch ( cmd )
  {
  case 0 : 
    WindowToDelete();
    break;
  case 1:
    WindowToActivate();
    break;
  case 2 :
    if ( NULL != CAAVisManagerApplication::GetFrame() )
    {
       CATDlgDocument * pFrame = CAAVisManagerApplication::GetFrame() ;
       pFrame->MDIMaximize(this);
    }
    break;
  case 3:
    if ( NULL != CAAVisManagerApplication::GetFrame() )
    {
       CATDlgDocument * pFrame = CAAVisManagerApplication::GetFrame() ;
       pFrame->MDIRestore(this);
    }
    break;
  case 4:
    if ( NULL != CAAVisManagerApplication::GetFrame() )
    {
       CATDlgDocument * pFrame = CAAVisManagerApplication::GetFrame() ;
       pFrame->MDIMinimize(this);
    }
    break;
    
   };
}

//-------------------------------------------------------------------------------
void CAAVisManagerWindow::Attach()
{
   CATVisManager *vm  = CATVisManager::GetVisManager();

   CAAVisManagerDocument * pDocument = _pEditor->GetDocument();

   CAAVisManagerCmdSelector * pSelector = _pEditor->GetSelector();

   if ( (NULL != pDocument) && (NULL != pDocument->GetRootContainer()) )
   {
       CATBaseUnknown * pRootObject = pDocument->GetRootContainer();
      _pRootObjectPath = new CATPathElement(pRootObject);
   }

   if ( (NULL != _pViewer) && ( NULL!= _pRootObjectPath) )
   {
      // we visualize the Model within the main 3D
      // viewpoint of the window
      // ---------------------------------------------------

      CAT3DViewpoint * pMain3DViewpoint = &(_pViewer->GetMain3DViewpoint());

      list<IID> liste_iid_3D;
      liste_iid_3D += new IID ( IID_CATI3DGeoVisu);
      vm->AttachTo (_pRootObjectPath, pMain3DViewpoint,
                     liste_iid_3D,pSelector);
      vm->AttachHSOTo(_pEditor->GetHSO(),pMain3DViewpoint);
      vm->AttachPSOTo(_pEditor->GetPSO(),pMain3DViewpoint);
      delete liste_iid_3D[0];

      // we visualize the Model within the main 2D
      // viewpoint of the window
      // ---------------------------------------------------

      CAT2DViewpoint * pMain2DViewpoint = &(_pViewer->GetMain2DViewpoint());

      if ( NULL != pMain2DViewpoint )
      {
         list<IID> liste_iid_2D;
         liste_iid_2D += new IID ( IID_CAAIVis2DGraphVisu);
         vm->AttachTo (_pRootObjectPath, pMain2DViewpoint,
                    liste_iid_2D,pSelector);
         vm->AttachHSOTo(_pEditor->GetHSO(),pMain2DViewpoint);
         vm->AttachPSOTo(_pEditor->GetPSO(),pMain2DViewpoint);
         delete liste_iid_2D[0];

         // we set the 2Dviewpoint correctly so that 2D boxes do not
         // spread too much above the 3D viewpoint.
         pMain2DViewpoint->SetZoom(0.5f);
         CATMathPoint2Df Eye2D(150.f,90.f);
         pMain2DViewpoint->SetOrigin( Eye2D);
      }
   }
}

//-------------------------------------------------------------------------------
void CAAVisManagerWindow::ChangeBackgroundIndicator()
{
   if ( NULL != _pViewer) 
   {
      // we add a background indicator to the current viewer.
      // Since there is already one background indicator within a viewer,
      // it's better to create its own indicator and to declare it
      // as the new background indicator to the viewer.
      // Do not forget to restore the old background indicator when our
      // own indicator is useless.

      _pDocBackgrdIndicator = new CAT3DIndicator(_pEditor->GetSelector(),
                                              "DocIndicator",
                                               _pViewer->GetMain3DViewpoint());

      // we make the doc indicator have a multi-selection behavior.
      // It allows end-user to select objects with a trap.
      // 1= Multi-Sel is enable; 0 = Multi-Sel disable.

      _pDocBackgrdIndicator->SetMultiSelBehavior(1);

      // This method returns the old indicator
      _pSavedBackgrdIndicator = _pViewer->SetIndicator(_pDocBackgrdIndicator,Background);

   }
}

//-------------------------------------------------------------------------------
void CAAVisManagerWindow::Detach()
{
   CATVisManager * pVisuManager = CATVisManager::GetVisManager();

   if ( (NULL != _pViewer) && (NULL != _pRootObjectPath) )
   {
      // 3D
      // --

      CAT3DViewpoint * pMain3DViewpoint = &(_pViewer->GetMain3DViewpoint());

      pVisuManager->DetachPSOFrom(pMain3DViewpoint);
      pVisuManager->DetachHSOFrom(pMain3DViewpoint);

      pVisuManager->DetachFrom(_pRootObjectPath, pMain3DViewpoint);

      // 2D
      // --

      CAT2DViewpoint * pMain2DViewpoint = &(_pViewer->GetMain2DViewpoint());

      pVisuManager->DetachPSOFrom(pMain2DViewpoint);
      pVisuManager->DetachHSOFrom(pMain2DViewpoint);

      pVisuManager->DetachFrom(_pRootObjectPath, pMain2DViewpoint);
   }

}
//-------------------------------------------------------------------------------
void CAAVisManagerWindow::ResetBackgroundIndicator()
{
   if (NULL != _pDocBackgrdIndicator)
   {
      // Restore the old indicator
      _pViewer->SetIndicator(_pSavedBackgrdIndicator,Background);

      // Use this method to delete the indicator ( which is a manipulator )
      _pDocBackgrdIndicator->Destroy();
      _pDocBackgrdIndicator = NULL;

      _pSavedBackgrdIndicator = NULL;
   }
}

//-------------------------------------------------------------------------------

void  CAAVisManagerWindow::WindowToDelete()
{
   // we send a notification to warn anyone that a window is under removal. 
   // --------------------------------------------------------------------

   // The application should be called back
   // in order to manage the list of window  of it's document

   // Solution : The application is the father of any window. 
   // Thus the window could benefit from  the send/receive mechanism 
   // of CATCommand to warn the application that a document should be deleted.

   // Notice: No need to destroy notification because 
   // it will be destroyed automatically .
   //
   
   CAAVisManagerWindowDeleteNotif * pNotif = NULL ;
   pNotif = new CAAVisManagerWindowDeleteNotif();
   SendNotification(GetFather(),pNotif);
}

//-------------------------------------------------------------------------------

void CAAVisManagerWindow::WindowToActivate()
{
   // we send an event to the application to warn it that a document 
   // has to be activated
   // --------------------------------------------------------------

   // Solution : The application is the father of any window. 
   // Thus the window could benefit from  the send/receive mechanism 
   // of CATCommand to warn the application that a document should be deleted.
   
   // Notice: No need to destroy notification because 
   // it will be destroyed automatically .
   //
   CAAVisManagerWindowActivateNotif * pNotif = NULL ;
   pNotif = new CAAVisManagerWindowActivateNotif();

   SendNotification(GetFather(),pNotif);
}


//-------------------------------------------------------------------------------

CAAVisManagerEditor * CAAVisManagerWindow::GetEditor()
{
  return _pEditor ; 
}
