// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAAfrPlaneEditCmd.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgSpinner.h"
#include "CATDlgGridConstraints.h"

// CAASystem.edu Framework
#include "CAAISysPlane.h" 

// Visualization Framework 
#include "CATModify.h"
#include "CATIModelEvents.h"

// Mathematic Framework
#include "CATMathPoint.h"

// C++ standrad library
#include "iostream.h"

//-----------------------------------------------------------------------------

CAAAfrPlaneEditCmd::CAAAfrPlaneEditCmd(
                              CATDialog *       iParent,                              
                              const CATString & iName,
                              CATDlgStyle       iStyle,
                               CAAISysPlane   * ipEdit)
                            : CATDlgDialog (iParent, iName, iStyle),
                              _piSysPlaneEdit(ipEdit),
                              _XSpinner(NULL),_YSpinner(NULL),_ZSpinner(NULL)
{
   cout << "CAAAfrPlaneEditCmd::CAAAfrPlaneEditCmd" << endl; 

   // Changes the default command mode ( CATCommandModeUndefined ) to 
   // CATCommandMsgRequestExclusiveMode so that the command can take the
   // focus. So Cancel, Desactivate and Activate can be redefined 
   // to manage the command lifecycle .
   //
   RequestStatusChange(CATCommandMsgRequestExclusiveMode);

   //an interface pointer in data member must be Addref'ed
   if (NULL != _piSysPlaneEdit)
   {
      _piSysPlaneEdit-> AddRef();
   }
}

//-----------------------------------------------------------------------------

CAAAfrPlaneEditCmd::~CAAAfrPlaneEditCmd() 
{
   cout << "CAAAfrPlaneEditCmd::~CAAAfrPlaneEditCmd"<< endl ;   

   if ( NULL != _piSysPlaneEdit) 
   {
      _piSysPlaneEdit -> Release();
      _piSysPlaneEdit = NULL ;
   }
   _XSpinner = NULL ;
   _YSpinner = NULL ;
   _ZSpinner = NULL ;
}

//-----------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::Build()
{
  cout << "CAAAfrPlaneEditCmd::Build" << endl;
   
   if ( NULL != _piSysPlaneEdit) 
   {
      //----------------------------
      // Retrieves the plane origin 
      //----------------------------
      CATMathPoint point ;
      _piSysPlaneEdit->GetOrigin(point);

      // Saves values for Cancel 
      _Xfirst = (float) point.GetX() ;
      _Yfirst = (float) point.GetY() ;
      _Zfirst = (float) point.GetZ() ;
  
      //-------------------------------------
      // Frames, labels and spinners creation
      //-------------------------------------
      CATDlgFrame * pXYZFrame = NULL ;
      CATDlgFrame * pXFrame   = NULL ;
      CATDlgFrame * pYFrame   = NULL ;
      CATDlgFrame * pZFrame   = NULL ;

      pXYZFrame = new CATDlgFrame(this, "XYZFrame",
                              CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);

      pXFrame = new CATDlgFrame(pXYZFrame, "XFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
      pYFrame = new CATDlgFrame(pXYZFrame, "YFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
      pZFrame = new CATDlgFrame(pXYZFrame, "ZFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);

      CATDlgLabel   * pXLabel = NULL ;
      CATDlgLabel   * pYLabel = NULL ;
      CATDlgLabel   * pZLabel = NULL;

      pXLabel = new CATDlgLabel(pXFrame, "XLabel");

      pYLabel = new CATDlgLabel(pYFrame, "YLabel");

      pZLabel = new CATDlgLabel(pZFrame, "ZLabel");


      _XSpinner = new CATDlgSpinner(pXFrame, "XSpinner", CATDlgSpnEntry);
      _XSpinner->SetRange(-10000., 10000., 20000);
      _XSpinner->SetCurrentValue(_Xfirst); 
      _YSpinner = new CATDlgSpinner(pYFrame, "YSpinner", CATDlgSpnEntry);
      _YSpinner->SetRange(-10000., 10000., 20000);
      _YSpinner->SetCurrentValue(_Yfirst); 
      _ZSpinner = new CATDlgSpinner(pZFrame, "ZSpinner", CATDlgSpnEntry);
      _ZSpinner->SetRange(-10000., 10000., 20000);
      _ZSpinner->SetCurrentValue(_Zfirst); 

      //-----------
      // Arrangment
      //-----------
      pXYZFrame->SetGridConstraints(0,0,1,1,CATGRID_CENTER);

      pXFrame->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
      pYFrame->SetGridConstraints(1,0,1,1,CATGRID_CENTER);
      pZFrame->SetGridConstraints(2,0,1,1,CATGRID_CENTER);
 
      pXLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
      pYLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
      pZLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);

      _XSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
      _YSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
      _ZSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);

      //-------------------
      // Sets up callbacks
      //-------------------
      AddAnalyseNotificationCB(this, this->GetDiaOKNotification(),
                               (CATCommandMethod)&CAAAfrPlaneEditCmd::ClickOK,
                               NULL);

      AddAnalyseNotificationCB(this, this->GetDiaPREVIEWNotification(),
                               (CATCommandMethod)&CAAAfrPlaneEditCmd::ClickPreview,
                               NULL);

      AddAnalyseNotificationCB(this, this->GetDiaCANCELNotification(),
                               (CATCommandMethod)&CAAAfrPlaneEditCmd::ClickCancel,
                               NULL);

      AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                               (CATCommandMethod)&CAAAfrPlaneEditCmd::ClickClose,
                               NULL);
   }
}

//--------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::ClickOK    (CATCommand          *iPublisher,
                                     CATNotification     *iNotification,
                                     CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPlaneEditCmd::ClickOK" << endl;
   if ( (NULL != _XSpinner) && ( NULL != _YSpinner) && ( NULL != _ZSpinner) )
   {
      ModifyModelAndVisu(_XSpinner->GetCurrentValue(),
                         _YSpinner->GetCurrentValue(),
                         _ZSpinner->GetCurrentValue());
   }

   CloseBox();
}

//--------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::ClickPreview (CATCommand          *iPublisher,
                                     CATNotification     *iNotification,
                                     CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPlaneEditCmd::ClickPreview" << endl;
   
   if ( (NULL != _XSpinner) && ( NULL != _YSpinner) && ( NULL != _ZSpinner) )
   {
      ModifyModelAndVisu(_XSpinner->GetCurrentValue(),
                         _YSpinner->GetCurrentValue(),
                         _ZSpinner->GetCurrentValue()) ;
   }
}

//--------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::ClickCancel(CATCommand          *iPublisher,
                                     CATNotification     *iNotification,
                                     CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPlaneEditCmd::ClickCancel" << endl;

   ModifyModelAndVisu(_Xfirst,_Yfirst,_Zfirst) ;
	                  			            
   CloseBox();
}

//--------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::ClickClose(CATCommand          *iPublisher,
                                    CATNotification     *iNotification,
                                    CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPlaneEditCmd::ClickClose" << endl;

   CloseBox();
}

//--------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::CloseBox()
{
   cout << "CAAAfrPlaneEditCmd::CloseBox" << endl;
   
   SetVisibility(CATDlgHide);

   //Suicide ( The Cancel method is not called after CloseBox)
   RequestDelayedDestruction();

}

//--------------------------------------------------------------------------

void CAAAfrPlaneEditCmd::ModifyModelAndVisu(const float iX, const float iY, const float iZ)
{
  if ( NULL != _piSysPlaneEdit )
  {
     //-----------------------------
     // Modification of plane origin
     //----------------------------- 

     CATMathPoint point(iX,iY,iZ);
     _piSysPlaneEdit->SetOrigin(point);

     //-----------------------------------
     // Notification to update the display 
     //-----------------------------------
     CATIModelEvents * piModelEvents = NULL;                
     HRESULT rc = _piSysPlaneEdit ->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
     if (SUCCEEDED(rc))
     {
        // the CATModify Notification allows to redraw the plane
        // at its new position
        CATModify Notif (piModelEvents);
        piModelEvents->Dispatch(Notif);

        piModelEvents -> Release();
        piModelEvents = NULL ;
     }
  } 
}

//--------------------------------------------------------------------------

CATStatusChangeRC CAAAfrPlaneEditCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
   cout << " CAAAfrPlaneEditCmd::Activate" << endl;

   SetVisibility(CATDlgShow);
   return (CATStatusChangeRCCompleted) ;
}

//--------------------------------------------------------------------------

CATStatusChangeRC CAAAfrPlaneEditCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
   cout << " CAAAfrPlaneEditCmd::Desactivate" << endl;
    
   // The Dialog Box is hidden 
   SetVisibility(CATDlgHide);

   return (CATStatusChangeRCCompleted) ;
}

//--------------------------------------------------------------------------

CATStatusChangeRC CAAAfrPlaneEditCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
   cout << " CAAAfrPlaneEditCmd::Cancel" << endl;
   CloseBox();
   return (CATStatusChangeRCCompleted) ;
}
