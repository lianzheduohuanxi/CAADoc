// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrBoundingElementCmd.h"

// CAASystem.edu Framework
#include "CAAISysCollection.h"
#include "CAAISysPoint.h"
#include "CAAISysLine.h"
#include "CAAISysGeomFactory.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgSeparator.h"
#include "CATDlgProgress.h"
#include "CATDlgCheckButton.h"
#include "CATDlgPushButton.h"
#include "CATDlgGridConstraints.h"

//Application Frame Framework
#include "CATApplicationFrame.h"

//To get the container and the UI active object
// Visualization Framework
#include "CATPathElement.h" 

// CAASystem.edu Framework
#include "CAAISysAccess.h"    

// ApplicationFrame framework
#include "CATFrmEditor.h"

// To retrieve the Viewer  
#include "CATFrmWindow.h"  // ApplicationFrame FW
#include "CATFrmLayout.h"  // ApplicationFrame FW
#include "CATViewer.h"     // Visualization FW

// To compute bounding element
// Visualization Framework
#include "CAT3DRep.h"
#include "CAT3DBoundingSphere.h"
#include "CATVisManager.h"
#include "CAT3DViewpoint.h"

// To show the bounding sphere
// CAASystem.edu Framework
#include "CAAISysCircle.h" 

// ApplicationFrame framework
#include "CATISO.h" 


// To update display progress bar
// Dialog framework
#include "CATInteractiveApplication.h"

// C++ standard library
#include "iostream.h"

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAAfrBoundingElementCmd);

//-----------------------------------------------------------------------------

CAAAfrBoundingElementCmd::CAAAfrBoundingElementCmd()
:CATDlgDialog ((CATApplicationFrame::GetFrame())->GetMainWindow(), 
                          "CAAAfrBoundingElementId",
                          CATDlgGridLayout | CATDlgWndBtnClose ),
_pLineCheck(NULL),
_pPBarFrame(NULL),
_pPointCheck(NULL),
_pProgressBar(NULL)
{
  //
  // The father of this command is (CATApplicationFrame::GetFrame())->GetMainWindow()
  // it's a Dialog object dedicated to the current model, Try to select an another
  // model, same type or not, during this command, the Dialog box is hidden.
  // 
  // This commmand is dedicated to CNEXT application, so CATApplicationFrame::GetFrame()
  // is not NULL when this command is launched
  //
  // This command is in Undefined Mode: not Shared and not Exclusive

  cout << "CAAAfrBoundingElementCmd::CAAAfrBoundingElementCmd" << endl; 


  //========================================
  // Retrieves the Set of Interactive Objects and the model container
  //========================================

  HRESULT     rc   = E_FAIL ;
  _pContainer      = NULL ;
  _pUIActiveObject = NULL ;
  _pISO            = NULL ;
 
  // Retrieves the editor in the command constructor,but never after
  // 
  _pEditor = CATFrmEditor::GetCurrentEditor();
  if ( NULL != _pEditor )
  {
    // Retrieves the ISO from the current editor 
    _pISO = _pEditor->GetISO() ;

    // Retrives the model container, while this object implements a factory
    // to create circle. 
    //
    CATPathElement path = _pEditor->GetUIActiveObject();
    if ( 0 != path.GetSize() )
    {
      // The leaf of the path is the UI active object 
      // 
      _pUIActiveObject = path[path.GetSize()-1];
      if ( NULL != _pUIActiveObject )
      {
        // When you keep a interface pointer, you must addrefe'd it. 
        _pUIActiveObject->AddRef();

        // The UI active object implements an interface CAAISysAccess which
        // gives the container which has created it. 
        // 
        CAAISysAccess * piSysAccess = NULL;                
        rc = _pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
        if (SUCCEEDED(rc))
        {
           piSysAccess->GetContainer(&_pContainer);
           piSysAccess -> Release();
           piSysAccess= NULL ;
        }
      }
    }  
  }


  //========================================
  // Creates temporary circles to simulate bounding spheres
  //========================================

  _piBoundingSphere[0] = NULL ; 
  _piBoundingSphere[1] = NULL ;
  _piBoundingSphere[2] = NULL ;

  if ( NULL != _pContainer )
  {
     CAAISysGeomFactory * piSysFactory = NULL;                
     rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysFactory);
     if (SUCCEEDED(rc))
     {
       for ( int i=0 ; i < 3 ; i++)
       {
         rc = piSysFactory -> Create(CAAISysGeomFactory::Circle, IID_CAAISysCircle, 
                             (CATBaseUnknown**)&_piBoundingSphere[i]);
       }      
       // No more need of this pointer 
       piSysFactory -> Release(); 
       piSysFactory = NULL ;

       // Circle are created, but not set in the Interactive Set Object 
       _IsBoundingSphereInISO = 0 ;

       if ( SUCCEEDED(rc) )
       {
          // Circle in (0,0,0) in the (y,z) plane
          CATMathVector normal(1.f,0.f,0.f);
          CATMathVector axis(0.f,1.f,0.f);
          _piBoundingSphere[0]->SetPlanar(normal,axis);

          // Circle in (0,0,0) in the (x,z) plane
          normal.SetCoord(0.f,1.f,0.f) ;
          axis.SetCoord(1.f,0.f,0.f) ;
          _piBoundingSphere[1]->SetPlanar(normal,axis);

          // 3ieme Circle in (0,0,0) to create a sphere effect 
          normal.SetCoord(0.74f,0.74f,0.f) ;
          axis.SetCoord(0.f,0.f,1.f) ;
          _piBoundingSphere[2]->SetPlanar(normal,axis);
        } 
     }
  }

  // ------------------------
  // Retrieves the viewpoint
  // ------------------------
  _pViewpoint = NULL ;

  CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
  if ( NULL !=  pLayout )
  {
      CATFrmWindow * pWindow = pLayout->GetCurrentWindow();
      if ( NULL !=  pWindow )
      {
         CATViewer * pViewer = pWindow->GetViewer();
              
         if ( NULL != pViewer )
         {
            CAT3DViewpoint & Main3DViewpoint = pViewer->GetMain3DViewpoint();
            _pViewpoint = (CATViewpoint*)(& Main3DViewpoint);
         }
      }
   }

  if ( SUCCEEDED(rc) )
  {
     //===========================================
     // Widget are created only if we have created 
     // the temporary 3 circles
     //===========================================

     //========================================
     // Creates the dialog widgets
     //========================================

     // Frames, check Buttons, progress bar creation
     CATDlgFrame * pPointLineGlobalFrame  = new CATDlgFrame(this, "PointLineGlobalFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
     CATDlgFrame * pPointLineCheckFrame  = new CATDlgFrame(pPointLineGlobalFrame, "PointLineCheckFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
     CATDlgFrame * pPointLineHeaderFrame  = new CATDlgFrame (pPointLineGlobalFrame, "PointLineHeaderFrameId",CATDlgGridLayout|CATDlgFraNoFrame);

	 CATDlgLabel * pPointLineLabel = new CATDlgLabel(pPointLineHeaderFrame, "LabelPointLineId");
	 CATDlgSeparator * pPointLineSep   = new CATDlgSeparator(pPointLineHeaderFrame,"SepId",CATDlgCtrHorizontal);
     _pPointCheck     = new CATDlgCheckButton(pPointLineCheckFrame, "PointId");
     _pLineCheck      = new CATDlgCheckButton(pPointLineCheckFrame, "LineId" );
	 CATDlgLabel * pLineSpaceLabel = new CATDlgLabel(pPointLineCheckFrame, "LineSpaceLabelId");
	 CATDlgLabel * pPointSpaceLabel = new CATDlgLabel(pPointLineCheckFrame, "PointSpaceLabelId");

	 CATDlgPushButton * pComputeButton   = new CATDlgPushButton(pPointLineCheckFrame, "ComputeButtonId" );
                
     _pPBarFrame = new CATDlgFrame(this, "PBarFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
	 CATDlgFrame * pPBarHeaderFrame  = new CATDlgFrame (_pPBarFrame, "PBarHeaderFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
	 CATDlgLabel * pPBarLabel = new CATDlgLabel(pPBarHeaderFrame, "PBarLabelId");
	 CATDlgSeparator * pPBarSep   = new CATDlgSeparator(pPBarHeaderFrame,"SepId",CATDlgCtrHorizontal);
     _pProgressBar      = new CATDlgProgress(_pPBarFrame,"ProgressBarId") ;
   
     // Arrangement Information Block
     pPointLineLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
	 pPointLineSep  ->SetGridConstraints(0,1,1,1,CATGRID_4SIDES|CATGRID_CST_HEIGHT);

	 pPointSpaceLabel ->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
     _pPointCheck   ->SetGridConstraints(0,1,1,1,CATGRID_LEFT);
	 pLineSpaceLabel ->SetGridConstraints(1,0,1,1,CATGRID_LEFT);
     _pLineCheck    ->SetGridConstraints(1,1,1,1,CATGRID_LEFT);
	 pComputeButton ->SetGridConstraints(1,2,1,1,CATGRID_RIGHT);

     pPointLineGlobalFrame->SetGridConstraints(0,0,1,1,CATGRID_4SIDES);
     pPointLineGlobalFrame->SetGridColumnResizable(0,1);

	 pPointLineHeaderFrame->SetGridConstraints(0,0,1,1,CATGRID_4SIDES);
	 pPointLineCheckFrame->SetGridConstraints(1,0,1,1,CATGRID_4SIDES);
     pPointLineHeaderFrame->SetGridColumnResizable(1,1);
     pPointLineCheckFrame->SetGridColumnResizable(1,1);
     
	 // Arrangement Compute Block	 
     pPBarLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
	 pPBarSep  ->SetGridConstraints(0,1,1,1,CATGRID_4SIDES|CATGRID_CST_HEIGHT);

	 _pProgressBar->SetGridConstraints(1,0,1,1,CATGRID_LEFT);

	 _pPBarFrame->SetGridConstraints(1,0,1,1,CATGRID_4SIDES);
     _pPBarFrame->SetGridColumnResizable(0,1);

	 // Progress bar visible when the end user clisks compute
	 pPBarHeaderFrame->SetGridConstraints(0,0,1,1,CATGRID_4SIDES);
     pPBarHeaderFrame->SetGridColumnResizable(1,1);

	 SetGridColumnResizable(0,1);

     //========================================
     // Subscribes to the Apply event
     //========================================

     AddAnalyseNotificationCB(pComputeButton, pComputeButton->GetPushBActivateNotification(),
                (CATCommandMethod)&CAAAfrBoundingElementCmd::ClickApply,
                            NULL);
  }
  // The window is shown
  SetVisibility(CATDlgShow);


  //========================================
  // Subscribes to the Close event
  //========================================

  AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                (CATCommandMethod)&CAAAfrBoundingElementCmd::ClickClose,
                            NULL);
  AddAnalyseNotificationCB(this, this->GetDiaCLOSENotification(),
                (CATCommandMethod)&CAAAfrBoundingElementCmd::ClickClose,
                            NULL);

  // ========================================
  // To delete the command when the editor is closed, and that the command
  // is already active
  // ========================================
  if ( (NULL != _pEditor) && (NULL != CATFrmLayout::GetCurrentLayout()) )
  {
     ::AddCallback(this,
                CATFrmLayout::GetCurrentLayout(),
		  CATFrmEditor::EDITOR_CLOSE_ENDED(),
		  (CATSubscriberMethod)&CAAAfrBoundingElementCmd::EditorClose,
		  NULL);
  }

}

//-------------------------------------------------------------------------------

CAAAfrBoundingElementCmd::~CAAAfrBoundingElementCmd() 
{
   cout << "CAAAfrBoundingElementCmd::~CAAAfrBoundingElementCmd"<< endl ;  
   
   //
   // warning : if the end user exits from CNEXT without closing this panel 
   // the ClickClose method is not called 
   //

   if ( NULL != _pContainer)   _pContainer->Release();  
   _pContainer = NULL ;

   if ( NULL != _pUIActiveObject)  _pUIActiveObject->Release();
   _pUIActiveObject = NULL ;

   if ( NULL != _piBoundingSphere[0])  
   { 
     _piBoundingSphere[0]->Release(); 
     _piBoundingSphere[0] = NULL ;
     _piBoundingSphere[1]->Release();
     _piBoundingSphere[1] = NULL ;
     _piBoundingSphere[2]->Release();
     _piBoundingSphere[2] = NULL ;
   }
   _pISO = NULL ;

  // Dialog's object delete by the current command
   _pLineCheck   = NULL ;
   _pPointCheck  = NULL ;
   _pProgressBar = NULL ;
   _pPBarFrame = NULL ;
   _pViewpoint = NULL ;

   if ( (NULL !=  _pEditor) && ( NULL != CATFrmLayout::GetCurrentLayout()) )
   {
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());
   }

   _pEditor = NULL ;

}

//-----------------------------------------------------------------------------

void CAAAfrBoundingElementCmd::ClickApply (   CATCommand          * iPublishingCommand,
                                              CATNotification     * iNotification,
                                              CATCommandClientData  iUsefulData)
{
  cout << "CAAAfrBoundingElementCmd::ClickApply" << endl;
   
  //
  // Retrieves the state of the check buttons to know which elements must
  // be surrounded

  if ( _pISO != NULL )
  {
     CATBoolean PointRead = FALSE;
     CATBoolean LineRead = FALSE ;

     if ( _pPointCheck->GetState() == CATDlgCheck ) 
       PointRead = TRUE ;

     if ( _pLineCheck->GetState() == CATDlgCheck ) 
       LineRead = TRUE ;

     CAT3DBoundingSphere sphereB ;
     int NbElt (0) ;
     HRESULT BeValide = ComputeBoundingSphere(sphereB,NbElt,PointRead,LineRead);

     if ( SUCCEEDED(BeValide) )
     {
        // Simulation of a long task
        // It's just a sample of a progress bar in a Dialog Box 

        CATInteractiveApplication * pApplication = NULL  ;
        pApplication = (CATInteractiveApplication *)CATApplication::MainApplication();

        _pProgressBar->SetRange(0, 100);       // progress 
        _pProgressBar->SetStep(1);             // with 1% steps 
        _pProgressBar->SetPos(0);    

        if ( NULL != pApplication)
        {
          pApplication->UpdateDisplay();
        }

        double a =1 ;

        for ( int k= 0 ; k <= 100 ; k++ )
        {
          // Sets the Cursor busy at each loop
          // because UpdateDisplay(), unsets it. 
          CATApplicationFrame::SetBusyCursor();

          // The long task
          for (int j=0 ; j < 10000000 ; j++) a = a * a;

          // Changes the progress bar value
         _pProgressBar->StepIt();

         // Updates the display of the progress bar 
         if ( NULL != pApplication )
         {
           pApplication->UpdateDisplay();
         }
        }
   
        // Bounding sphere update 
        CATMathPoint center ;
        CATMathPointf centerf = sphereB.GetCenter() ;
        centerf.GetValue(center);
  
        for ( int i=0 ; i < 3 ; i++)
        {
           _piBoundingSphere[i]->SetCenter(center);
           _piBoundingSphere[i]->SetRadius(sphereB.GetRadius());
           if ( 1 == _IsBoundingSphereInISO )
              _pISO->UpdateElement(_piBoundingSphere[i]) ;
           else
              _pISO->AddElement(_piBoundingSphere[i]) ;
        }
        _IsBoundingSphereInISO = 1 ;

	    // To reset the progress bar
	    _pProgressBar->SetPos(0); 
     }
     else
     {
       // If there is a bounding sphere displayed, we remove it from the
       // Interactive Set Object
       if ( 1 == _IsBoundingSphereInISO )
       {
          _IsBoundingSphereInISO = 0 ;
          _pISO->RemoveElement(_piBoundingSphere[0]);
          _pISO->RemoveElement(_piBoundingSphere[1]);
          _pISO->RemoveElement(_piBoundingSphere[2]);
       }
     }
  }
}

//---------------------------------------------------------------------------

void CAAAfrBoundingElementCmd::ClickClose(CATCommand           * iPublishingCommand,
                                          CATNotification      * iNotification,
                                          CATCommandClientData   iUsefulData)
{
  cout << "CAAAfrBoundingElementCmd::ClickClose" << endl;

  SetVisibility(CATDlgHide);
                         
  // If the end user exits from CNEXT without closing this panel,
  // ISO will be not valid in the destructor, so it is here where 
  // circles must be removed from the ISO
  //
  if ( (1 == _IsBoundingSphereInISO)  && ( NULL!=_pISO) ) 
  {
    _pISO->RemoveElement(_piBoundingSphere[0]);
    _pISO->RemoveElement(_piBoundingSphere[1]);
    _pISO->RemoveElement(_piBoundingSphere[2]);
    _IsBoundingSphereInISO = 0;
  }

  //Suicide 
  RequestDelayedDestruction();

}

//---------------------------------------------------------------------------
HRESULT CAAAfrBoundingElementCmd::ComputeBoundingSphere(CAT3DBoundingSphere & iBoundingSphere,
                                                        int                 & oNbElt,
                                                        CATBoolean            iPointRead,
                                                        CATBoolean            iLineRead)
                                                     
{
  
  //===============================================
  // This method is called by the ClickApply method
  // So the _pContainer is not NULL 
  //===============================================
  
  HRESULT BeValide = E_FAIL ;

  if ( NULL == _pContainer ) return E_FAIL ;

  CAAISysCollection * piSysCollection = NULL;                
  
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);

  if  ( SUCCEEDED(rc) )
  {
    piSysCollection->GetNumberOfObjects(&oNbElt);

    if ( oNbElt > 1 ) 
    {
      //
      // The model is not empty. It contains at least: 
      // the UIActive object + one geometrical object 
      //
      if ( (iPointRead == TRUE) && (iLineRead == TRUE) )
      {
        // In this model (CAAGeometry), the graphic representation of the
        // UI active object is a CAT3DBagRep which contains alls graphic 
        // representation of objects in the model
        //
        CAT3DRep * pRep = NULL ;
        HRESULT find = Get3DRep(NULL,&pRep);
        if ( SUCCEEDED(find) )
        {
           iBoundingSphere = pRep->GetBoundingElement();
           BeValide = S_OK ;
        }


      } else
      {
         //
         // Point or Line must be excluded of the Bounding sphere
         // so, we retrieve all object of the model, and we compute
         // the total bounding sphere in excluing point or line object
         //

         // In the container, the first element is the UIActive object
         // so we begin with 2 and not 1
         //
         for ( int i=2 ; i <= oNbElt ; i++)
         {
            CATBoolean ToCompute = TRUE ;
            CATBaseUnknown * pObject =NULL;
            rc = piSysCollection->GetObject(i,&pObject);
            if (SUCCEEDED(rc))
            {
               CAAISysPoint * piSysPoint = NULL;                
               HRESULT rc = pObject ->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
               if (SUCCEEDED(rc))
               {
                  if (iPointRead == FALSE) 
                  {
                     // It's a point, but the bounding sphere don't take care of point 
                     ToCompute = FALSE ;
                  }
                  piSysPoint -> Release();
                  piSysPoint = NULL ;
               }

               CAAISysLine * piSysLine = NULL;                
               rc = pObject ->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
               if (SUCCEEDED(rc))
               {
                  if (iLineRead == FALSE)
                  {
                     // It's a line, but the bounding sphere don't take care of line 
                     ToCompute = FALSE ;
                  }
                  piSysLine -> Release();
                  piSysLine = NULL ;
               }
          
               if ( TRUE == ToCompute )
               {
                  CAT3DRep * pRep = NULL ;
                  HRESULT find = Get3DRep(pObject,&pRep);
                  if ( SUCCEEDED(find) )
                  {
                     iBoundingSphere += pRep->GetBoundingElement();
                     BeValide = S_OK ;
                  }
               }
               // 
               pObject  -> Release();
               pObject = NULL ;
            }
         } 
      }
    }

    // Done with this pointer
    piSysCollection-> Release(); 
    piSysCollection= NULL ;

  }

  return BeValide ;
}

//---------------------------------------------------------------------------

HRESULT CAAAfrBoundingElementCmd::Get3DRep(CATBaseUnknown *iObject, CAT3DRep ** oRep)
{
   HRESULT rc = E_FAIL ;

   if ( NULL == oRep ) return rc ;

   CATVisManager * pVisManager = CATVisManager::GetVisManager();

   if ( NULL != pVisManager )
   {
      // Create a path with the Root object
      
      CATPathElement Path ;

      Path.AddChildElement( _pUIActiveObject );
      if ( NULL != iObject )
      {
        Path.AddChildElement( iObject );
      }
           
      // The returned path 
      CATRepPath RepPath  ;

      // Generation of the rep
      pVisManager->GenerateRepPathFromPathElement(Path,_pViewpoint,RepPath);

      if ( RepPath.Size() >= 1 )
      {                   
         *oRep = (CAT3DRep*) RepPath[RepPath.Size()-1];
         if ( NULL != *oRep )
         {
            rc = S_OK ;
         }
       }
    }
    return rc ;
}

//-------------------------------------------------------------------------------

void CAAAfrBoundingElementCmd::EditorClose(CATCallbackEvent  iEvent, 
                                              void            * iFrom,
                                              CATNotification * iNotification,
                                              CATSubscriberData iClientData,
                                              CATCallback       iCallBack ) 
{
  if ( _pEditor == iFrom )
   {
      // Suicide
      RequestDelayedDestruction();

   }
}
