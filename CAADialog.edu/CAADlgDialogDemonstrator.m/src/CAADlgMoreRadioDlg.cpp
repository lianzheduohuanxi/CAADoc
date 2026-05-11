// COPYRIGHT Dassault Systemes 2001
//===================================================================
#include "CAADlgMoreRadioDlg.h"

// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgInclude.h"
#include "CATDlgUtility.h"

// C++ standard Library
#include "iostream.h"

//-------------------------------------------------------------------------

CAADlgMoreRadioDlg::CAADlgMoreRadioDlg(CATDialog * pParentDlg):
  CATDlgDialog (pParentDlg,"CAADlgMoreRadioDlg",CATDlgWndAutoResize | CATDlgWndBtnOKCancel | CATDlgWndNoResize),
      _pFrameDetailA(NULL),_pFrameDetailB(NULL)
{
   cout <<" CAADlgMoreRadioDlg::CAADlgMoreRadioDlg" << endl;

   RequestStatusChange (CATCommandMsgRequestExclusiveMode);
}


//-------------------------------------------------------------------------

CAADlgMoreRadioDlg::~CAADlgMoreRadioDlg()
{
   cout <<" CAADlgMoreRadioDlg::~CAADlgMoreRadioDlg" << endl;
   _pFrameDetailA = NULL ;
   _pFrameDetailB = NULL ;
} 

//-------------------------------------------------------------------------

void CAADlgMoreRadioDlg::Build()
{

  //define a first permanent frame
  //------------------------------
  CATDlgFrame * pFrameMain = new CATDlgFrame(this, "FrameMain", CATDlgGridLayout );

  //we use a vertical tabulation layout
  SetVerticalAttachment(0, CATDlgTopOrLeft,pFrameMain,NULL);
  
  CATDlgRadioButton * pRadioButtonND = new CATDlgRadioButton(pFrameMain, "RadioButtonND");
  pRadioButtonND -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
  pRadioButtonND -> SetState(CATDlgCheck,0);

  CATDlgRadioButton * pRadioButtonDA = new CATDlgRadioButton(pFrameMain, "RadioButtonDA");
  pRadioButtonDA -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

  CATDlgRadioButton * pRadioButtonDB = new CATDlgRadioButton(pFrameMain, "RadioButtonDB");
  pRadioButtonDB -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);

  //define an invisible optional frame A
  //------------------------------------
  _pFrameDetailA = new CATDlgFrame(this, "FrameDetailA", CATDlgGridLayout);
  
  CATDlgLabel * pLabel008 = new CATDlgLabel(_pFrameDetailA, "Label008");
  pLabel008 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
  CATDlgEditor *pEditor010 = new CATDlgEditor(_pFrameDetailA, "Editor010");
  pEditor010 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
  CATDlgLabel * pLabel010 = new CATDlgLabel(_pFrameDetailA, "Label010");
  pLabel010 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
  CATDlgEditor *pEditor012 = new CATDlgEditor(_pFrameDetailA, "Editor012");
  pEditor012 -> SetGridConstraints(3, 0, 1, 1, CATGRID_4SIDES);
  _pFrameDetailA->SetVisibility(CATDlgHide); 

  //define an invisible optional frame B
  //------------------------------------
  _pFrameDetailB = new CATDlgFrame(this, "FrameDetailB", CATDlgGridLayout);
 
  CATDlgLabel * Label009 = new CATDlgLabel(_pFrameDetailB, "Label009");
  Label009 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
  CATDlgEditor *pEditor011 = new CATDlgEditor(_pFrameDetailB, "Editor011");
  pEditor011 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
  _pFrameDetailB->SetVisibility(CATDlgHide); 


   // When the end user clicks a radio button
   AddAnalyseNotificationCB (pRadioButtonND, 
                               pRadioButtonND->GetRadBModifyNotification(),
                               (CATCommandMethod)&CAADlgMoreRadioDlg::OnRadioButtonNDRadBModifyNotification,
                               NULL);
   AddAnalyseNotificationCB (pRadioButtonDB, 
                               pRadioButtonDB->GetRadBModifyNotification(),
                               (CATCommandMethod)&CAADlgMoreRadioDlg::OnRadioButtonDBRadBModifyNotification,
                               NULL);

   AddAnalyseNotificationCB (pRadioButtonDA, 
                               pRadioButtonDA->GetRadBModifyNotification(),
                               (CATCommandMethod)&CAADlgMoreRadioDlg::OnRadioButtonDARadBModifyNotification,
                               NULL);

   // Close Window necessary
   AddAnalyseNotificationCB (this, 
                               GetWindCloseNotification(),
                               (CATCommandMethod)&CAADlgMoreRadioDlg::CloseWindow,
                               NULL);
   AddAnalyseNotificationCB (this, 
                               GetDiaCANCELNotification(),
                               (CATCommandMethod)&CAADlgMoreRadioDlg::CloseWindow,
                               NULL);
   AddAnalyseNotificationCB (this, 
                               GetDiaOKNotification(),
                               (CATCommandMethod)&CAADlgMoreRadioDlg::CloseWindow,
                               NULL);

}

//-------------------------------------------------------------------------

void CAADlgMoreRadioDlg::OnRadioButtonNDRadBModifyNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   cout <<"no option"<<endl;
}

//-------------------------------------------------------------------------

void CAADlgMoreRadioDlg::OnRadioButtonDARadBModifyNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
  
  CATDlgRadioButton * pRadioButton = (CATDlgRadioButton *) cmd ;
  if ( (NULL != _pFrameDetailA) && ( NULL != pRadioButton) )
  {
     if (pRadioButton->GetState() == CATDlgCheck) 
     {
        cout <<"Show Option Panel A"<<endl;

        // Display option frame B
        // To do that, define a new tabulation
        SetVerticalAttachment(10, CATDlgTopOrLeft, _pFrameDetailA, NULL);

        // show the frame
        _pFrameDetailA->SetVisibility(CATDlgShow);         
     } 
     else 
     {
        cout <<"Hide Option Panel A"<<endl;

        //remove any attachment and hide frame B
        ResetAttachment(_pFrameDetailA);         
       _pFrameDetailA->SetVisibility(CATDlgHide);         
     }
  }

}

//-------------------------------------------------------------------------

void CAADlgMoreRadioDlg::OnRadioButtonDBRadBModifyNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
  
   CATDlgRadioButton * pRadioButton = (CATDlgRadioButton *) cmd ;
   if ( (NULL != _pFrameDetailB) && (NULL != pRadioButton) )
   { 
      if ( CATDlgCheck == pRadioButton->GetState() ) 
      {
         cout <<"Show Option Panel B"<<endl;

         // Display option frame B
         // To do that, define a new tabulation
         SetVerticalAttachment(10, CATDlgTopOrLeft, _pFrameDetailB, NULL);

         // show the frame
         _pFrameDetailB->SetVisibility(CATDlgShow);         
      } 
      else 
      {
         cout <<"Hide Option Panel B"<<endl;

         //remove any attachment and hide frame B
         ResetAttachment(_pFrameDetailB);         
         _pFrameDetailB->SetVisibility(CATDlgHide);         
      }
   }
  
}


//-------------------------------------------------------------------------

void CAADlgMoreRadioDlg::CloseWindow(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   SetVisibility (CATDlgHide);
   RequestDelayedDestruction();
}

//-------------------------------------------------------------------------

CATStatusChangeRC CAADlgMoreRadioDlg::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
{
  SetVisibility (CATDlgHide);
  RequestDelayedDestruction();
  return (CATStatusChangeRCCompleted);
}

//-------------------------------------------------------------------------

CATStatusChangeRC CAADlgMoreRadioDlg::Activate( CATCommand * iFromClient, CATNotification * iEvtDat)
{

  SetVisibility(CATDlgShow);
  return (CATStatusChangeRCCompleted);
}

//-------------------------------------------------------------------------

CATStatusChangeRC CAADlgMoreRadioDlg::Desactivate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
  SetVisibility (CATDlgHide);
  return (CATStatusChangeRCCompleted);
}

//-------------------------------------------------------------------------

