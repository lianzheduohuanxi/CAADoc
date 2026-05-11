// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrPointEditDlg.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgSpinner.h"
#include "CATDlgGridConstraints.h"

// Visualization Framework 
#include "CATModify.h"
#include "CATIModelEvents.h"

// CAASystem.edu Framework
#include "CAAISysPoint.h" 

// C++ Standard library
#include "iostream.h"


//-----------------------------------------------------------------------------

CAAAfrPointEditDlg::CAAAfrPointEditDlg(
                              CATDialog *       iParent,                              
                              const CATString & iName,
                              CATDlgStyle       iStyle,
                              CAAISysPoint *       ipEdit)
                            : CATDlgDialog (iParent, iName, iStyle),
                              _piSysPointEdit(ipEdit),
                              _XSpinner(NULL),
                              _YSpinner(NULL),
                              _ZSpinner(NULL)
{
  cout << "CAAAfrPointEditDlg::CAAAfrPointEditDlg" << endl; 
  if ( NULL != _piSysPointEdit) 
  {
     _piSysPointEdit-> AddRef();
  }
}

//-----------------------------------------------------------------------------

CAAAfrPointEditDlg::~CAAAfrPointEditDlg()
{
  cout << "CAAAfrPointEditDlg::~CAAAfrPointEditDlg" << endl;
  if ( NULL != _piSysPointEdit) 
  {
     _piSysPointEdit-> Release();
     _piSysPointEdit = NULL ;
  }
  
  // Dialog's Object automatically deleted 
  _XSpinner = NULL ;
  _YSpinner = NULL ;
  _ZSpinner = NULL ;
}

//-----------------------------------------------------------------------------

void CAAAfrPointEditDlg::Build()
{
  cout << "CAAAfrPointEditDlg::Build" << endl;
  
   //----------------------------
   // Retrieves the plane origin 
   //----------------------------
   if ( NULL != _piSysPointEdit )
   {
      _piSysPointEdit->GetCoord(_Xfirst,_Yfirst, _Zfirst);


      //-------------------------------------
      // Frames, labels and spinners creation
      //-------------------------------------

      CATDlgFrame * pXYZFrame = NULL ;
      CATDlgFrame * pXFrame   = NULL ;
      CATDlgFrame * pYFrame   = NULL ;
      CATDlgFrame * pZFrame   = NULL ;

      pXFrame = new CATDlgFrame(this, "XFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
      pYFrame = new CATDlgFrame(this, "YFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
      pZFrame = new CATDlgFrame(this, "ZFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);

      CATDlgLabel   * pXLabel = NULL ;
      CATDlgLabel   * pYLabel = NULL ;
      CATDlgLabel   * pZLabel = NULL ;

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
                               (CATCommandMethod)&CAAAfrPointEditDlg::ClickOK,
                                NULL);


      AddAnalyseNotificationCB(this, this->GetDiaPREVIEWNotification(),
                               (CATCommandMethod)&CAAAfrPointEditDlg::ClickPreview,
                               NULL);

      AddAnalyseNotificationCB(this, this->GetDiaCANCELNotification(),
                               (CATCommandMethod)&CAAAfrPointEditDlg::ClickCancel,
                               NULL);

      AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                               (CATCommandMethod)&CAAAfrPointEditDlg::ClickClose,
                               NULL);
   }
}

//-----------------------------------------------------------------------------

void CAAAfrPointEditDlg::ClickOK   (CATCommand          *iPublisher,
                                    CATNotification     *iNotification,
                                    CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPointEditDlg::ClickOK" << endl;

   if ( (NULL != _XSpinner) && ( NULL != _YSpinner) && ( NULL != _ZSpinner) )
   {
      // Modification of the model and  of the visualization
      ModifyModelAndVisu(_XSpinner->GetCurrentValue(),
                         _YSpinner->GetCurrentValue(),
                         _ZSpinner->GetCurrentValue());
   }

   CloseBox() ;
}

//-----------------------------------------------------------------------------

void CAAAfrPointEditDlg::ClickCancel(CATCommand          *iPublisher,
                                     CATNotification     *iNotification,
                                     CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPointEditDlg::ClickCancel" << endl;
   ModifyModelAndVisu(_Xfirst,_Yfirst,_Zfirst) ;	                  
   CloseBox();
}

//----------------------------------------------------------------------------- 

void CAAAfrPointEditDlg::ClickClose(CATCommand          *iPublisher,
                                    CATNotification     *iNotification,
                                    CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPointEditDlg::ClickClose" << endl;

   CloseBox();
}

//-----------------------------------------------------------------------------

void CAAAfrPointEditDlg::ClickPreview(CATCommand          *iPublisher,
                                    CATNotification     *iNotification,
                                    CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPointEditDlg::ClickPreview" << endl;

   if ( (NULL != _XSpinner) && ( NULL != _YSpinner) && ( NULL != _ZSpinner) )
   {
      ModifyModelAndVisu(_XSpinner->GetCurrentValue(),
                         _YSpinner->GetCurrentValue(),
                         _ZSpinner->GetCurrentValue()) ;
   }

}

//-----------------------------------------------------------------------------

void CAAAfrPointEditDlg::CloseBox()
{
  SetVisibility(CATDlgHide);
                             
  SendNotification(GetFather(),CATDlgDialog::GetWindCloseNotification());
}

//-----------------------------------------------------------------------------

void CAAAfrPointEditDlg::ModifyModelAndVisu(const float iX, const float iY, const float iZ)
{

  if ( NULL != _piSysPointEdit )
  {
     //----------------------------------------
     // Modification of the point coordinnates
     //----------------------------------------

     _piSysPointEdit->SetCoord(iX, iY, iZ);

     //-----------------------------------
     // Notification to update the display
     //----------------------------------- 
     CATIModelEvents * pModelEvents = NULL;                
     HRESULT rc = _piSysPointEdit -> QueryInterface(IID_CATIModelEvents, (void**)&pModelEvents);
     if (SUCCEEDED(rc))
     {
       CATModify Notif (pModelEvents);
       pModelEvents->Dispatch(Notif);

       pModelEvents-> Release();
       pModelEvents = NULL ;
     }
  } 
}
