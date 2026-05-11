// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAACafCircleWindowCmd.h"
#include "CAAICafGeometryEltSettingAtt.h"
#include "GetCAACafGeometryEltSettingCtrl.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"

// Mathematics Framework
#include "CATMathPoint2D.h"

//Visualization Framework
#include "CAT2DViewer.h"
#include "CAT2DCustomRep.h"
#include "CAT2DBagRep.h"
#include "CAT2DCustomRep.h"
#include "CAT2DMarkerGP.h"
#include "CAT2DLineGP.h"
#include "CAT2DBoundingSphere.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgGridConstraints.h"

// System Framework
#include "CATSettingRepository.h" // for the event 

// C++ standard library
#include "iostream.h"

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAACafCircleWindowCmd);

//-----------------------------------------------------------------------------

CAACafCircleWindowCmd::CAACafCircleWindowCmd()
          :CATDlgDialog ((CATApplicationFrame::GetFrame())->GetMainWindow(), 
                          "CAACafCircleWindowId",
                          CATDlgWndNoResize | CATDlgWndBtnClose ),
						  _pIBUController(NULL),
						  _p2DViewer(NULL),
						  _pTheModelToDisplay(NULL),
						  _pCircleRep(NULL)
{
  //
  // The father of this command is (CATApplicationFrame::GetFrame())->GetMainWindow()
  // it's a Dialog object dedicated to the current document, Try to select an another
  // document, same type or not, during this command, the Dialog box is hidden.
  // 
  // This commmand is dedicated to CNEXT application, so CATApplicationFrame::GetFrame()
  // is not NULL when this command is launched
  //
  // This command is in Undefined Mode: not Shared and not Exclusive

  cout << "CAACafCircleWindowCmd::CAACafCircleWindowCmd" << endl; 

  // Constructs the contents of the dialog box
  CATDlgFrame * pFrameViewer = new CATDlgFrame(this,"Circle2DIdFrame", 
	                             CATDlgFraNoFrame|CATDlgGridLayout|CATDlgFraNoTitle);
  _p2DViewer = new CAT2DViewer( pFrameViewer, "Circle2DId",CATDlgFraNoTitle|CATDlgFraNoFrame, 250, 250);
  
  // The viewer is with the same color
  _p2DViewer->SetGraduatedBackground(0);                                          
  _p2DViewer->SetGridConstraints( 0,0,1,1,CATGRID_4SIDES );

  // This bag contains the CAT2DCustomRep to represent the circle
  // At eatch new display of the circle, the bag is the same
  // The CAT2DCustomRep of the circle is removed from the bag, deleted and a new
  // rep is built and added in this bag.
  //
  _pTheModelToDisplay = new CAT2DBagRep();

  _p2DViewer->AddRep((CAT2DRep*)_pTheModelToDisplay);

  // Retrieves a interface pointer of the controller. 
  // This controller is CAACafGeometryEltSettingCtrl and it's a component
  // accessible by theirs interfaces. 
  HRESULT rc = ::GetCAACafGeometryEltSettingCtrl(IID_CATBaseUnknown, (void**)& _pIBUController);
  
  // The controller exists ...
  if ( SUCCEEDED(rc) )
  {
	 // The first circle is drawn
     DisplayCircle();
 
     // To be prevent when a commit is done in the controller.  
	 // So we can redisplay the circle with the new value of the count of 
	 // point to discretize a circle.
	 //
	 // CATSettingRepository::Repository_Modified() is an event sent by the repository
	 // and retransmit by the controller component.
	 //
     ::AddCallback(this,
                 _pIBUController,
				  CATSettingRepository::Repository_Modified(),
                  (CATSubscriberMethod)&CAACafCircleWindowCmd::DisplayCircleCB,
                  NULL);

  }

  // The Window is visible
  SetVisibility(CATDlgShow);

  //========================================
  // Subscribes to the Close event
  //========================================

  AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                (CATCommandMethod)&CAACafCircleWindowCmd::ClickClose,
                            NULL);
  AddAnalyseNotificationCB(this, this->GetDiaCLOSENotification(),
                (CATCommandMethod)&CAACafCircleWindowCmd::ClickClose,
                            NULL);

  // ========================================
  // To delete the command when the editor is closed, and that the command
  // is already active
  // ========================================
  _pEditor = CATFrmEditor::GetCurrentEditor();
  if ( (NULL != _pEditor) && (NULL != CATFrmLayout::GetCurrentLayout()) )
  {
     ::AddCallback(this,
                CATFrmLayout::GetCurrentLayout(),
		  CATFrmEditor::EDITOR_CLOSE_ENDED(),
		  (CATSubscriberMethod)&CAACafCircleWindowCmd::EditorClose,
		  NULL);
  }
}

//-------------------------------------------------------------------------------

CAACafCircleWindowCmd::~CAACafCircleWindowCmd() 
{
   cout << "CAACafCircleWindowCmd::~CAACafCircleWindowCmd"<< endl ;  
   
   //
   // warning : if the end user exits from CNEXT without closing this panel 
   // the ClickClose method is not called 
   //
   if ( NULL != _pIBUController )
   {
       // Callback set in the constructor
       ::RemoveSubscriberCallbacks(this, _pIBUController);

	   _pIBUController->Release();
	   _pIBUController = NULL ;
   }

  if ( NULL != _pTheModelToDisplay )
  {
     // The bag and its children are deleted
     _pTheModelToDisplay->Destroy();
     _pTheModelToDisplay = NULL ;

	 // The rep of the circle is deleted by the bag deletion
	 _pCircleRep = NULL ;
  }

  _p2DViewer = NULL ;

   if ( (NULL !=  _pEditor) && ( NULL != CATFrmLayout::GetCurrentLayout()) )
   {
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());
   }

   _pEditor = NULL ;

}


//---------------------------------------------------------------------------

void CAACafCircleWindowCmd::ClickClose(CATCommand           * iPublishingCommand,
                                          CATNotification      * iNotification,
                                          CATCommandClientData   iUsefulData)
{
  cout << "CAACafCircleWindowCmd::ClickClose" << endl;

  SetVisibility(CATDlgHide);

  //Suicide 
  RequestDelayedDestruction();

}

//---------------------------------------------------------------------------
void CAACafCircleWindowCmd::DisplayCircleCB(CATCallbackEvent  iEvent,
                            void             *iPublisher,
                            CATNotification  *iNotification,
                            CATSubscriberData iUsefulData,
                            CATCallback       iCallBack ) 
{
   DisplayCircle();
}

//---------------------------------------------------------------------------
HRESULT CAACafCircleWindowCmd::DisplayCircle()
                                                     
{
   // Retrieves the interface which gives values of each attribut of the
   // setting file. 
   CAAICafGeometryEltSettingAtt * pISettingAtt = NULL ;
   HRESULT rc = _pIBUController->QueryInterface(IID_CAAICafGeometryEltSettingAtt,(void**)& pISettingAtt);
   if ( SUCCEEDED(rc) )
   {
	   int NbPoint ;
       pISettingAtt->GetMaxPointCurve(NbPoint);
 
	   if ( NULL != _pCircleRep )
	   {
	       _pTheModelToDisplay->RemoveChild(*_pCircleRep);
		   _pCircleRep->Destroy();
		   _pCircleRep = NULL ;
       }
       _pCircleRep = new CAT2DCustomRep();

	   CATGraphicAttributeSet aGP ;
       float * TabCoord  = new float[ NbPoint*2] ;

       double angle = ( CAT2PI ) / NbPoint ;

       CATMathPoint2D center(100,100) ;
	   float radius = 100 ;

	   for ( int i= 0 ; i < NbPoint; i++ )
	   {
		   TabCoord[i*2]   = cos(angle * (i) ) * radius + center.GetX() ;
           TabCoord[i*2+1] = sin(angle * (i) ) * radius + center.GetY () ;
	   }

	   // Data are duplicate in the primitive
	   CAT2DMarkerGP * pGPm = new CAT2DMarkerGP(TabCoord, NbPoint, DOT);
       _pCircleRep->AddGP(pGPm,aGP);

	   // Data are duplicate in the primitive
	   CAT2DLineGP * pGPl = new CAT2DLineGP(TabCoord, NbPoint, ALLOCATE,LINE_LOOP);
       _pCircleRep->AddGP(pGPl,aGP);

	   // The data can be deleted
	   delete [] TabCoord ;
	   TabCoord = NULL ;

	   CAT2DBoundingSphere be(center,radius+10.f);
       _pCircleRep->SetBoundingElement(be) ;

       _pTheModelToDisplay->AddChild(*_pCircleRep);

       pISettingAtt->Release();
	   pISettingAtt = NULL ;

	   _p2DViewer->Draw();
   }
   return rc ;
}


//-------------------------------------------------------------------------------

void CAACafCircleWindowCmd::EditorClose(CATCallbackEvent  iEvent, 
                                              void            * iFrom,
                                              CATNotification * iNotification,
                                              CATSubscriberData iClientData,
                                              CATCallback       iCallBack ) 
{
 
  if ( _pEditor == iFrom )
   {
   
      // Now this extension will receive any message.
      //
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());

      // Suicide
      RequestDelayedDestruction();

      _pEditor = NULL ; 
   }
}

