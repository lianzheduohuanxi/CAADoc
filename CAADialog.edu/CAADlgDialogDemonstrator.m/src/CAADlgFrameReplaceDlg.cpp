// COPYRIGHT Dassault Systemes 2001
//===================================================================

// Local Framework
#include "CAADlgFrameReplaceDlg.h"

// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgInclude.h"
#include "CATDlgUtility.h"
#include "CATMsgCatalog.h"          // To retrieve the Combo lines

// System Framework
#include "CATSettingRepository.h"

// C++ standard Library
#include "iostream.h"

#define Coordinates  0
#define CircleCenter 1
#define Between      2

//-------------------------------------------------------------------------

CAADlgFrameReplaceDlg::CAADlgFrameReplaceDlg(CATDialog * pParentDlg) :
  CATDlgDialog (pParentDlg,"CAADlgFrameReplaceDlg",
      CATDlgWndAutoResize | CATDlgWndBtnOKCancel |CATDlgWndNoResize ),
      _CurrentSelection(0),_pComboPointType(NULL),_pSpinnerX(NULL),
      _pSpinnerY(NULL),_pSpinnerZ(NULL)
{
   cout <<" CAADlgFrameReplaceDlg::CAADlgFrameReplaceDlg" << endl;

   RequestStatusChange (CATCommandMsgRequestExclusiveMode);

   // Retrieve the previous values if any
   _pSettingFrameReplace = CATSettingRepository::GetRepository("CAADlgFrameReplaceDlg" );

}

//-------------------------------------------------------------------------

CAADlgFrameReplaceDlg::~CAADlgFrameReplaceDlg()
{
    cout <<" CAADlgFrameReplaceDlg::~CAADlgFrameReplaceDlg" << endl;
    _pSettingFrameReplace = NULL ;
    _pComboPointType      = NULL ;
    _pSpinnerX            = NULL ;
    _pSpinnerY            = NULL ;
    _pSpinnerZ            = NULL ;
}

//-------------------------------------------------------------------------

void CAADlgFrameReplaceDlg::Build()
{
   //To avoid the dialog box closure
   SetDefaultButton(NULL);
 
   // The frame with the combo
   //
   CATDlgFrame * pFrameCombo = new CATDlgFrame(this, "FrameCombo", 
                                           CATDlgGridLayout );
   SetHorizontalAttachment(0,CATDlgTopOrLeft,pFrameCombo,NULL);

      CATDlgLabel *pLabelChoice = new CATDlgLabel(pFrameCombo, "LabelChoice");  
      pLabelChoice -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

      _pComboPointType = new CATDlgCombo(pFrameCombo, "ComboChoice",
                                                   CATDlgCmbDropDown);
      _pComboPointType -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);


      CATUnicodeString LineNLS ; 
      
      LineNLS = CATMsgCatalog::BuildMessage("CAADlgFrameReplaceDlg",
                                          "ComboChoice.Coordinates",NULL,0,"Coordinates");   
      _pComboPointType->SetLine(LineNLS);

      LineNLS = CATMsgCatalog::BuildMessage("CAADlgFrameReplaceDlg",
                                            "ComboChoice.CircleCenter",NULL,0,"CircleCenter");
      _pComboPointType->SetLine(LineNLS);

      LineNLS = CATMsgCatalog::BuildMessage("CAADlgFrameReplaceDlg",
                                            "ComboChoice.Between",NULL,0,"Between");
      _pComboPointType->SetLine(LineNLS);
      

   // Frame for definition by coordinates 
   CATDlgFrame * pFrameCoord = new CATDlgFrame(this, "FrameCoord", 
                                           CATDlgGridLayout );
   pFrameCoord->SetVisibility(CATDlgHide);
   _pListFrame[Coordinates] = pFrameCoord ;

      CATDlgLabel *pLabelX = new CATDlgLabel(pFrameCoord, "LabelX");
      pLabelX -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
      CATDlgLabel *pLabelY = new CATDlgLabel(pFrameCoord, "LabelY");
      pLabelY -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
      CATDlgLabel *pLabelZ = new CATDlgLabel(pFrameCoord, "LabelZ");
      pLabelZ -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);

      double X(0.0f),Y(0.0f),Z(0.0f);
      if ( NULL != _pSettingFrameReplace )
      {
         _pSettingFrameReplace->ReadSetting("XCoord",&X);
         _pSettingFrameReplace->ReadSetting("YCoord",&Y);
         _pSettingFrameReplace->ReadSetting("ZCoord",&Z);
      }
      _pSpinnerX = new CATDlgSpinner(pFrameCoord, "SpinnerX",CATDlgSpnEntry|CATDlgSpnDouble);
      _pSpinnerX ->SetMinMaxStep(-100000.f,100000.0f,.1f) ;
      _pSpinnerX -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
      _pSpinnerX ->SetValue(X,0); // no notif
      _pSpinnerY = new CATDlgSpinner(pFrameCoord, "SpinnerY",CATDlgSpnEntry|CATDlgSpnDouble);
      _pSpinnerY ->SetMinMaxStep(-100000.f,100000.0f,.1f) ;
      _pSpinnerY -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
      _pSpinnerY ->SetValue(Y,0); // no notif
      _pSpinnerZ = new CATDlgSpinner(pFrameCoord, "SpinnerZ",CATDlgSpnEntry|CATDlgSpnDouble);
      _pSpinnerZ ->SetMinMaxStep(-100000.f,100000.0f,.1f) ;
      _pSpinnerZ -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
      _pSpinnerZ ->SetValue(Z,0); // no notif

   // Frame for definition by circle center
   CATDlgFrame * pFrameCircleCenter = new CATDlgFrame(this, "FrameCircleCenter", 
                                           CATDlgGridLayout );  
   _pListFrame[CircleCenter] = pFrameCircleCenter ;
   pFrameCircleCenter->SetVisibility(CATDlgHide);

      CATDlgLabel *pLabelCircle = new CATDlgLabel(pFrameCircleCenter, "LabelCircle");
      pLabelCircle -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

      CATDlgSelectorList *pCircle = new CATDlgSelectorList(pFrameCircleCenter, "Circle");
      pCircle -> SetVisibleTextHeight(1);
      pCircle -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

   // Frame for definition by between
   CATDlgFrame * pFrameBetween = new CATDlgFrame(this, "FrameBetween", 
                                           CATDlgGridLayout );  
   _pListFrame[Between] = pFrameBetween ;
   pFrameBetween->SetVisibility(CATDlgHide);

      CATDlgLabel *pP1 = new CATDlgLabel(pFrameBetween, "P1");
      pP1 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
      CATDlgLabel *pP2 = new CATDlgLabel(pFrameBetween, "P2");
      pP2 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
      CATDlgLabel *pRatio = new CATDlgLabel(pFrameBetween, "Ratio");
      pRatio -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
      CATDlgPushButton *pMiddlePoint = new CATDlgPushButton(pFrameBetween, "MiddlePoint");
      pMiddlePoint -> SetGridConstraints(3, 0, 1, 1, CATGRID_4SIDES);

      CATDlgSelectorList *P1Sel = new CATDlgSelectorList(pFrameBetween, "P1Sel");
      P1Sel -> SetVisibleTextHeight(1);
      P1Sel -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
      CATDlgSelectorList *P2Sel = new CATDlgSelectorList(pFrameBetween, "P2Sel");
      P2Sel -> SetVisibleTextHeight(1);
      P2Sel -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
      CATDlgEditor *pRatioEdt = new CATDlgEditor(pFrameBetween, "RatioEdt");
      pRatioEdt -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);


   // Attach the first frame according to the saved value
   _CurrentSelection = Coordinates ;
   if ( NULL != _pSettingFrameReplace )
   {
      _pSettingFrameReplace->ReadSetting("ComboPointType",&_CurrentSelection);
   }
   _pComboPointType->SetSelect(_CurrentSelection,0); // no notif
   SetHorizontalAttachment(5,CATDlgTopOrLeft,_pListFrame[_CurrentSelection],NULL);
   _pListFrame[_CurrentSelection]->SetVisibility(CATDlgShow);


    // when the end user clicks on the combo
   AddAnalyseNotificationCB (_pComboPointType, 
                 _pComboPointType->GetComboSelectNotification(),
                 (CATCommandMethod)&CAADlgFrameReplaceDlg::OnComboSelectNotification,
                               NULL);

   // To close the window
   AddAnalyseNotificationCB (this, 
                               GetDiaCANCELNotification(),
                               (CATCommandMethod)&CAADlgFrameReplaceDlg::CloseWindow,
                               NULL);

   AddAnalyseNotificationCB (this, 
                               GetDiaOKNotification(),
                               (CATCommandMethod)&CAADlgFrameReplaceDlg::CloseWindowOK,
                               NULL);
   AddAnalyseNotificationCB (this, 
                               GetWindCloseNotification(),
                               (CATCommandMethod)&CAADlgFrameReplaceDlg::CloseWindow,
                               NULL);

}

//-------------------------------------------------------------------------

void CAADlgFrameReplaceDlg::OnComboSelectNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   cout <<" CAADlgFrameReplaceDlg::OnComboSelectNotification" << endl;
   if ( NULL != _pComboPointType )
   {
      int NewCurrentSelection = _pComboPointType->GetSelect() ;
     
      ResetAttachment(_pListFrame[_CurrentSelection]);
      _pListFrame[_CurrentSelection]->SetVisibility(CATDlgHide);

      SetHorizontalAttachment(5, CATDlgTopOrLeft, _pListFrame[NewCurrentSelection], NULL);
      _pListFrame[NewCurrentSelection]->SetVisibility(CATDlgShow);
      
      _CurrentSelection = NewCurrentSelection ;
   }
}

//-------------------------------------------------------------------------

void CAADlgFrameReplaceDlg::CloseWindowOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   SetVisibility (CATDlgHide);

   // Save the values to retrieve them 
   // when the command will be relaunched
   //
   if ( NULL != _pSettingFrameReplace )
   {
       if ( NULL != _pComboPointType )
       {
          int PointType = _pComboPointType->GetSelect() ;
          _pSettingFrameReplace->WriteSetting("ComboPointType",&PointType);
       }

       if ( (NULL !=_pSpinnerX) && (NULL !=_pSpinnerY) && (NULL !=_pSpinnerZ) )
       {
          double XVal = _pSpinnerX->GetValue() ;
          _pSettingFrameReplace->WriteSetting("XCoord",&XVal);
          double YVal = _pSpinnerY->GetValue() ;
          _pSettingFrameReplace->WriteSetting("YCoord",&YVal);
          double ZVal = _pSpinnerZ->GetValue() ;
          _pSettingFrameReplace->WriteSetting("ZCoord",&ZVal);
       }

       // The values are saved on a setting file
       // to retrieve the values between two sessions
       _pSettingFrameReplace->SaveRepository();

   }

   this->RequestDelayedDestruction();
}

//-------------------------------------------------------------------------

void CAADlgFrameReplaceDlg::CloseWindow(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   SetVisibility (CATDlgHide);
   this->RequestDelayedDestruction();
}
// ----------------------------------------------------

CATStatusChangeRC CAADlgFrameReplaceDlg::Activate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
   SetVisibility(CATDlgShow);
   return (CATStatusChangeRCCompleted);
}

// ----------------------------------------------------

CATStatusChangeRC CAADlgFrameReplaceDlg::Desactivate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
   SetVisibility (CATDlgHide);
   return (CATStatusChangeRCCompleted);
}

// ----------------------------------------------------

CATStatusChangeRC CAADlgFrameReplaceDlg::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
{
   SetVisibility (CATDlgHide);
   RequestDelayedDestruction();
   return (CATStatusChangeRCCompleted);
}


