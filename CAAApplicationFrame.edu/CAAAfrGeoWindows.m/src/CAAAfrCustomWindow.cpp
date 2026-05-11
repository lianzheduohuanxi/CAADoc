// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrCustomWindow.h"

// ObjectModelerBase Framework
#include "CATDocument.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"

// ApplicationFrame.h
#include "CATIDocumentEdit.h"
#include "CATISO.h"

// Visualization Framework 
#include "CATNavigation3DViewer.h"
#include "CATNavigation2DViewer.h"
#include "CATVisManager.h"
#include "CATI3DGeoVisu.h"
#include "CATI2DGeoVisu.h"
#include "CATPathElement.h"
#include "CATViewpoint.h"
#include "CATPSO.h"
#include "CATHSO.h"

// Dialog Framework
#include "CATDlgGridConstraints.h"

// C++ standard library
#include <iostream.h>


//--------------------------------------------------------------------------
/*
           -----------------------------------------
           ! CATIA V5                              !
           -----------------------------------------

       
              ------------------------------
              !                            !
              !  ------------------------- !
              ! !                        ! !    
              ! !  ----------------------------> 1) Open/Create a new document
              ! !  ! MyDocument 1.1  !   ! !
              ! !  -------------------   ! !
              ! !  ! Window 1        !   !----> Invisible Frame Retrieves by GetViewerFrame
              ! !  !                 !   ! !
              ! !  !                 !   ! !
              ! !  !                 !   ! !
              ! !  !                 !   ! !---> Invisible Object Named Decorator. You retrieve it
              ! !  -------------------   ! !     by CATApplicationFrame::GetFrame()->GetMainWindow()
              ! !                        ! !
              ! !  ----------------------------> 2) Window/New Window 
              ! !  ! MyDocument 1.2  !   ! !        The DuplicateWindow method is called
              ! !  -------------------   ! !
              ! !  ! Window 2        !   ! ! 
              ! !  !                 !   ! ! 
              ! !  !                 !   ! ! 
              ! !  !                 !   ! !
              ! !  !                 !   ! !
              ! !  -------------------   ! !
              ! !                        ! !
              ! -------------------------! !
              !                            !
              -----------------------------!

*/
//--------------------------------------------------------------------------


CAAAfrCustomWindow :: CAAAfrCustomWindow ( const CATString &iName, CATFrmEditor * iEditor )
                   : CATFrmWindow(iName,iEditor), 
		            _pViewer1(NULL),_pViewer2(NULL),_pViewer3(NULL),
		            _pRootObjectPath(NULL)

{
  cout << "Construction CAAAfrCustomWindow" << endl ;
}

//------------------------------------------------------------------------------

CAAAfrCustomWindow :: ~CAAAfrCustomWindow ()
{
   cout << "Destruction CAAAfrCustomWindow" << endl ;

   // --------------------------------------------------------------
   // Destruction of the Root Object Path created in the constructor
   // --------------------------------------------------------------
   if ( NULL != _pRootObjectPath) _pRootObjectPath->Release() ;
   _pRootObjectPath = NULL ;

   // No need to delete the viewer 
   _pViewer1 = NULL ;
   _pViewer2 = NULL ;
   _pViewer3 = NULL ;
}

//------------------------------------------------------------------------------

void CAAAfrCustomWindow :: Build ()
{
  cout << "CAAAfrCustomWindow :: Build" << endl ;
    
//  --------------
//  1- Dialog Part
//  ---------------

   //  In this sample the window contains 2 types of viewers which are defined 
   //  in the Visualization Framework. Refer to it to have more information . 
    
   //------------------------
   //  1-a Viewers creation 
   //------------------------
   int width, height ;
   CATString  ViewerName ; 

   // Retrieves the Dialog Object wich will contain this window
   // See the shema above. 
   CATDlgFrame * pFrameWindow = GetViewerFrame() ;

   // Creates a frame with the CATDlgGridLayout Style between pFrameWindow and itself
   CATString FrameName ="FrameName";
   CATDlgFrame * Frame = new CATDlgFrame(pFrameWindow,FrameName,CATDlgGridLayout|CATDlgFraNoFrame);

   // Creates the 3 viewers
   ViewerName = "Viewer3Dnum1" ;
   width = 200 ; height = 200 ;
   _pViewer1 = new CATNavigation3DViewer(Frame,ViewerName,width,height) ;
    
   ViewerName = "Viewer3Dnum2" ;
   width = 200 ; height = 300 ;
   _pViewer2 = new CATNavigation3DViewer(Frame,ViewerName,width,height) ;

   ViewerName = "Viewer2D" ;
   width = 200 ; height = 500 ;
   _pViewer3 = new CATNavigation2DViewer(Frame,ViewerName,width,height) ;    

   //---------------------------------------
   //  1-b Arranges viewers in the frame 
   //---------------------------------------

   pFrameWindow->Attach4Sides(Frame);

   _pViewer1->SetGridConstraints(0,0,1,1,CATGRID_4SIDES);
   _pViewer2->SetGridConstraints(0,1,1,1,CATGRID_4SIDES);
   _pViewer3->SetGridConstraints(1,0,2,1,CATGRID_4SIDES);

   Frame->SetGridRowResizable(0,1);
   Frame->SetGridRowResizable(1,1);
   Frame->SetGridColumnResizable(0,1);
   Frame->SetGridColumnResizable(1,1);

   // -----------------------------
   //  1-c Sets the current viewer 
   // -----------------------------
   _pViewer1->Reframe();
   SetViewer(_pViewer1);


//  -------------------------------
//  2- Interactivity Managment Part
//  -------------------------------

   //--------------------
   //  2-a Retrieves data 
   //--------------------  
   
   // Retrieves the editor
   CATFrmEditor * pEditeur = GetEditor();
   if ( NULL != pEditeur )
   {
      // Retrieves the unique visu manager 
      CATVisManager * pVisuManager = CATVisManager::GetVisManager();

      // Retrieves the document to show 
      CATDocument    * pDocument   = NULL;
      if (NULL != pEditeur) pDocument = pEditeur->GetDocument();

      // Retrieves the root object to create after the path 
      CATBaseUnknown * pRootObject = NULL ;	
      if (NULL != pDocument)
      {   
         // Interface implemented by the document 
         CATIDocumentEdit * piDocumentEdit = NULL;                
         HRESULT rc = pDocument->QueryInterface(IID_CATIDocumentEdit, (void**)&piDocumentEdit);
         if (SUCCEEDED(rc))
         {
            // to retrieve the first Active object 
            CATPathElement pathactive = piDocumentEdit->GetActiveObject() ;
            if (  0 != pathactive.GetSize() )
            { 
               pRootObject = pathactive[0];
            }
            piDocumentEdit -> Release();
            piDocumentEdit = NULL ;
         }
      }
 
      cout <<" creation pRootObject" << endl;
      // --------------------------------
      //  2-b Visu manager  modifications
      // --------------------------------

      if (   (NULL != pEditeur  ) && (NULL != pRootObject ) &&
          (NULL != pDocument) && (NULL != pVisuManager) )           
      {    	    
         // Creates a path with this root object
         _pRootObjectPath = new CATPathElement(pRootObject);
        
         // Retrieves the CommandSelector ( parent of all commands for a document )
         CATCommand * pCommandSelector = (CATCommand*) pEditeur->GetCommandSelector();

         // List of CATIVisu interfaces used to display the model 
         list<IID> ListIVisu3d;
         list<IID> ListIVisu2d;
         IID visu3d = IID_CATI3DGeoVisu ;
         IID visu2d = IID_CATI2DGeoVisu ;
         ListIVisu3d.fastadd(&visu3d);
         ListIVisu2d.fastadd(&visu2d);

         // Retrieves the viewpoint 
         CATViewpoint  * pViewPoint1 = NULL ;
         CATViewpoint  * pViewPoint2 = NULL ;
         CATViewpoint  * pViewPoint3 = NULL ;

         pViewPoint1 = (CATViewpoint*) &(_pViewer1->GetMain3DViewpoint());

         // CommandSelector will be the parent of a manipulator created  
         // in the AttachTo visu manager method. 
         // When this manipulator detects events from the mouse, it 
         // sends a notification to the CommandSelector. 
         pVisuManager->AttachTo(_pRootObjectPath,pViewPoint1,ListIVisu3d,pCommandSelector);

         pViewPoint2 = (CATViewpoint*) &(_pViewer2->GetMain3DViewpoint());
         pVisuManager->AttachTo(_pRootObjectPath,pViewPoint2,ListIVisu3d,pCommandSelector);

         pViewPoint3 = (CATViewpoint*) &(_pViewer3->GetMain2DViewpoint());
         pVisuManager->AttachTo(_pRootObjectPath,pViewPoint3,ListIVisu2d,pCommandSelector);

         cout <<" pVisuManager attach to" << endl;
         // --------------------------------------------
         //  2-c Control manipulations on the data model
         // --------------------------------------------

         //
         // When the CommandSelector receives a notification from the visu manager
         // manipulator, it sends a notification to the PSO/HSO  ( via the Editor ),and 
         // the PSO/HSO send a notif to the visu manager which takes the appropriate
         // action.
         //

         // Preselected Set Objects
         CATPSO * pPSO = pEditeur->GetPSO() ;   

         // Highlighted Set Objects 
         CATHSO * pHSO = pEditeur->GetHSO() ; 

         pVisuManager->AttachPSOTo( pPSO,pViewPoint1);
         pVisuManager->AttachPSOTo( pPSO,pViewPoint2);
         pVisuManager->AttachPSOTo( pPSO,pViewPoint3);
         pVisuManager->AttachHSOTo( pHSO,pViewPoint1);
         pVisuManager->AttachHSOTo( pHSO,pViewPoint2);
         pVisuManager->AttachHSOTo( pHSO,pViewPoint3);		

         // -------------------------------------------------------------
         //  2-d Iso ( Interactiv Set Objects : objects out the model )
         // -------------------------------------------------------------
         CATISO * pISO = pEditeur->GetISO()  ; 
         pISO->AddViewer(_pViewer1);
         pISO->AddViewer(_pViewer2);
         pISO->AddViewer(_pViewer3);
      }
   }
}

//------------------------------------------------------------------------------

CATFrmWindow * CAAAfrCustomWindow :: DuplicateWindow()
{

   cout << "DuplicateWindow CAAAfrCustomWindow" << endl ;
 
   CATString NameOfThis = GetBaseName().ConvertToChar() ;
   CAAAfrCustomWindow * pWindowToReturn = new CAAAfrCustomWindow(NameOfThis,GetEditor() )  ;
   pWindowToReturn->Build();

   // BaseNames must be identicals 
   pWindowToReturn->SetBaseName(GetBaseName());


   // Here you can tranfer information from the current viewers 
   // to the new viewers. 
   // For exemple the color of the BackGround of the first viewer 
   float r,v,b ;
   if ( NULL != _pViewer1 ) _pViewer1->GetBackgroundColor(&r,&v,&b);

   // Get the new viewers 
   CATNavigation3DViewer * pV1 = NULL ;
   CATNavigation3DViewer * pV2 = NULL ;
   CATNavigation2DViewer * pV3 = NULL ;
   pWindowToReturn->GetViewers(&pV1,&pV2,&pV3);

   if ( NULL != pV1 ) pV1->SetBackgroundColor(r,v,b);
 
   // New window just created 
   return  pWindowToReturn ;
}

//------------------------------------------------------------------------------

void CAAAfrCustomWindow :: DeleteWindow()
{

   cout << "DeleteWindow CAAAfrCustomWindow" << endl ;

   if ((NULL != GetEditor() ) && (NULL != _pViewer1) && 
       (NULL != _pViewer2)    && (NULL != _pViewer3) )
   {  

   // -----------------------------
   // Detaches Viewers from the ISO 
   // -----------------------------
            
      CATISO * pISO = NULL ;
      pISO = GetEditor()->GetISO();

      if  (NULL != pISO)   pISO->RemoveViewer(_pViewer1);
      if  (NULL != pISO)   pISO->RemoveViewer(_pViewer2);
      if  (NULL != pISO)   pISO->RemoveViewer(_pViewer3);
   
   // ---------------------
   // Retrieves Viewpoint 
   // ---------------------

      CATViewpoint  * pViewPoint1 = NULL ;
      CATViewpoint  * pViewPoint2 = NULL ;
      CATViewpoint  * pViewPoint3 = NULL ;
      pViewPoint1 = (CATViewpoint*) &(_pViewer1->GetMain3DViewpoint());
      pViewPoint2 = (CATViewpoint*) &(_pViewer2->GetMain3DViewpoint());
      pViewPoint3 = (CATViewpoint*) &(_pViewer3->GetMain2DViewpoint());

   // ----------------------------------
   // Retrieves the unique visu manager 
   // ----------------------------------

      CATVisManager * pVisuManager = CATVisManager::GetVisManager();

      if ( (NULL != pViewPoint1) && 
           (NULL != pViewPoint2) && 
           (NULL != pViewPoint3) && ( NULL != pVisuManager) )
      {
   // -------------------------------
   // Detaches Viewpoint PSO and HSO   
   // -------------------------------
         pVisuManager->DetachPSOFrom(pViewPoint1);
         pVisuManager->DetachPSOFrom(pViewPoint2);
         pVisuManager->DetachPSOFrom(pViewPoint3);
         pVisuManager->DetachHSOFrom(pViewPoint1);
         pVisuManager->DetachHSOFrom(pViewPoint2);
         pVisuManager->DetachHSOFrom(pViewPoint3);

   // ----------------------------------------
   // Detaches Viewpoints from the controller 
   // ----------------------------------------
         pVisuManager->DetachFrom(_pRootObjectPath,pViewPoint1);
         pVisuManager->DetachFrom(_pRootObjectPath,pViewPoint2);
         pVisuManager->DetachFrom(_pRootObjectPath,pViewPoint3);
      }
   }

 // No Need to delete viewers. As any Dialog framework derived objects, 
 // there are deleted by their parents .

 // ----------------------------------------
 // Mandatory to call the parent destructor
 // ----------------------------------------
 CATFrmWindow::DeleteWindow();

}

//------------------------------------------------------------------------------

void CAAAfrCustomWindow :: GetViewers(CATNavigation3DViewer ** oV1 ,
                                      CATNavigation3DViewer ** oV2 , 
                                      CATNavigation2DViewer ** oV3)
{
   *oV1 = _pViewer1 ;
   *oV2 = _pViewer2 ;
   *oV3 = _pViewer3 ;
}
