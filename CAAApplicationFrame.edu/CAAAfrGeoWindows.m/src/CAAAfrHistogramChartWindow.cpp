// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrHistogramChartWindow.h"

// ObjectModelerBase Framework
#include "CATDocument.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"

// ApplicationFrame.h
#include "CATISO.h"

// Visualization Framework 
#include "CATNavigation2DViewer.h"
#include "CATVisManager.h"
#include "CAAIVisHistogramChartVisu.h"
#include "CATPathElement.h"
#include "CATViewpoint.h"
#include "CATPSO.h"
#include "CATHSO.h"

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
              ! !  -------------------   ! !   by CATApplicationFrame::GetFrame()->GetMainWindow()
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


CAAAfrHistogramChartWindow :: CAAAfrHistogramChartWindow ( const CATString &iName, CATFrmEditor * iEditor )
                   : CATFrmWindow(iName,iEditor), 
		            _pViewer(NULL),
		            _pRootObjectPath(NULL)

{
  cout << "Construction CAAAfrHistogramChartWindow" << endl ;
}

//------------------------------------------------------------------------------

CAAAfrHistogramChartWindow :: ~CAAAfrHistogramChartWindow ()
{
   cout << "Destruction CAAAfrHistogramChartWindow" << endl ;

   // --------------------------------------------------------------
   // Destruction of the Root Object Path created in the constructor
   // --------------------------------------------------------------
   if ( NULL != _pRootObjectPath) _pRootObjectPath->Release() ;
   _pRootObjectPath = NULL ;

   // No need to delete the viewer
   _pViewer = NULL ;
}

//------------------------------------------------------------------------------

void CAAAfrHistogramChartWindow :: Build ()
{
  cout << "CAAAfrHistogramChartWindow::Build" << endl ;
    
//  --------------
//  1- Dialog Part
//  ---------------

   //  In this sample the window contains a 2D viewer which is defined 
   //  in the Visualization Framework. Refer to it to have more information . 
    
   //------------------------
   //  1-a Viewer creation 
   //------------------------
 
   // Retrieves the Dialog Object wich will contain this window
   // See the shema above. 
   CATDlgFrame * pFrameWindow = GetViewerFrame() ;

   // Creates the 2D viewer
   CATString ViewerName = "HistogramChar2DViewer" ;
   int width  = 200 ;
   int height = 200 ;
   CATDlgStyle DlgStyle = CATDlgFraNoTitle | CATDlgFraNoFrame ;
   _pViewer = new CATNavigation2DViewer(pFrameWindow,ViewerName,DlgStyle,width,height) ;
   _pViewer->SetBackgroundColor(0.7f,0.7f,0.7f);
   _pViewer->SetGraduatedBackground(0);

   //---------------------------------------
   //  1-b Arranges viewer in the frame 
   //---------------------------------------

   pFrameWindow->Attach4Sides(_pViewer);

   // -----------------------------
   //  1-c Sets the current viewer 
   // -----------------------------

   _pViewer->ReframeOn(0.f,300.f,-20.f,300.f);

   // SetViewer sets the current viewer 
   // CATFrmWindow::GetViewer retrieves the current viewer.
   SetViewer(_pViewer);

//  -------------------------------
//  2- Interactivity Managment Part
//  -------------------------------

   //--------------------
   //  2-a Retrieves data 
   //--------------------  
   
   // Retrieve the editor
   CATFrmEditor * pEditor = GetEditor();

   // Retrieves the unique visu manager 
   CATVisManager * pVisuManager = CATVisManager::GetVisManager();

   if ( (NULL != pEditor) && ( NULL != pVisuManager) )
   {
      // Retrieves the document to show 
      CATDocument    * pDocument   =  pEditor->GetDocument();

      // Retrieves the root object path 
      // don't use the CATIDocumentEdit::GetActiveObject which is the first
      // root object.
      // This histogram chart is applied to the current UIActiveObject
      //
      CATBaseUnknown * pRootObject = NULL ;	
      if ( NULL != pDocument )
      {
         CATPathElement path = pEditor->GetUIActiveObject();
        _pRootObjectPath = new CATPathElement(path);
      }

   // --------------------------------
   //  2-b Visu manager  modifications
   // --------------------------------

      if ( NULL != _pRootObjectPath )       
	  {    	    
        
         // Retrieves the CommandSelector ( parent of all commands for a document )
         CATCommand * pCommandSelector = (CATCommand*) pEditor->GetCommandSelector();

         // List of CATIVisu interfaces used to display the model 
         list<IID> ListIVisu;
         IID visu = IID_CAAIVisHistogramChartVisu;
         ListIVisu.fastadd(&visu);

         // Retrieves the viewpoint 
         CATViewpoint  * pViewPoint = NULL ;
         pViewPoint = (CATViewpoint*) &(_pViewer->GetMain2DViewpoint());

         // CommandSelector will be the parent of a manipulator created  
         // in the AttachTo visu manager method. 
         // When this manipulator detects events from the mouse, it 
         // sends a notification to the CommandSelector. 
         pVisuManager->AttachTo(_pRootObjectPath,pViewPoint,ListIVisu,pCommandSelector);


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
         CATPSO * pPSO = pEditor->GetPSO() ;   
         pVisuManager->AttachPSOTo( pPSO,pViewPoint);

      // Highlighted Set Objects 
         CATHSO * pHSO = pEditor->GetHSO() ; 
         pVisuManager->AttachHSOTo( pHSO,pViewPoint);

      // -------------------------------------------------------------
      //  2-d Iso ( Interactiv Set Objects : objects out the model )
      // -------------------------------------------------------------
         CATISO * pISO = pEditor->GetISO()  ;  
		 pISO->AddViewer(_pViewer);
      }
   }
}

//------------------------------------------------------------------------------

CATFrmWindow * CAAAfrHistogramChartWindow :: DuplicateWindow()
{

   cout << "DuplicateWindow CAAAfrHistogramChartWindow" << endl ;
 
   CATString NameOfThis = GetBaseName().ConvertToChar() ;
   CAAAfrHistogramChartWindow * pWindowToReturn = new CAAAfrHistogramChartWindow(NameOfThis,GetEditor() )  ;
   pWindowToReturn->Build();

   // BaseNames must be identicals 
   pWindowToReturn->SetBaseName(GetBaseName());

   // New window just created 
   return  pWindowToReturn ;
}

//------------------------------------------------------------------------------

void CAAAfrHistogramChartWindow :: DeleteWindow()
{

   cout << "DeleteWindow CAAAfrHistogramChartWindow" << endl ;

   if ((NULL != GetEditor() ) && (NULL != _pViewer) )
   {  

   // -----------------------------
   // Detaches Viewers from the ISO 
   // -----------------------------
            
      CATISO * pISO = NULL ;
      pISO = GetEditor()->GetISO();

      if  (NULL != pISO)   pISO->RemoveViewer(_pViewer);
   
   // ---------------------
   // Retrieves Viewpoint 
   // ---------------------

      CATViewpoint  * pViewPoint = NULL ;
      pViewPoint = (CATViewpoint*) &(_pViewer->GetMain2DViewpoint());

   // ----------------------------------
   // Retrieves the unique visu manager 
   // ----------------------------------

      CATVisManager * pVisuManager = CATVisManager::GetVisManager();

      if ( (NULL != pViewPoint) &&  ( NULL != pVisuManager) )
      {
   // -------------------------------
   // Detaches Viewpoint PSO and HSO   
   // -------------------------------
         pVisuManager->DetachPSOFrom(pViewPoint) ;
         pVisuManager->DetachHSOFrom(pViewPoint);
 
   // ----------------------------------------
   // Detaches Viewpoint from the controller 
   // ----------------------------------------
         pVisuManager->DetachFrom(_pRootObjectPath,pViewPoint);

      }
   }

 // No Need to delete viewers. As any Dialog framework derived objects, 
 // there are deleted by their parents .

 // ----------------------------------------
 // Mandatory to call the parent destructor
 // ----------------------------------------
 CATFrmWindow::DeleteWindow();

}

