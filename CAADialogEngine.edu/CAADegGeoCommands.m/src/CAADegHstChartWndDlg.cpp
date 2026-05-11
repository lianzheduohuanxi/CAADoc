// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADegHstChartWndDlg.h"
#include "CAADegEditor1SelectedNotification.h"
#include "CAADegEditor1DeselectedNotification.h"

// Dialog Framework
#include "CATDlgLabel.h"
#include "CATDlgFrame.h"
#include "CATDlgRadioButton.h"
#include "CATDlgEditor.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"

// C++ Standard Library
#include "iostream.h"

//------------------------------------------------------------------------------------------

CAADegHstChartWndDlg::CAADegHstChartWndDlg(CATDialog * iParent): 
      CATDlgDialog (iParent,
                    "HstChartWndDlgId",
                     CATDlgWndBtnOKCancel|CATDlgGridLayout)

                             
{
  cout << "CAADegHstChartWndDlg::CAADegHstChartWndDlg" << endl; 
}

//--------------------------------------------------------------------------------------

CAADegHstChartWndDlg::~CAADegHstChartWndDlg()
{
  cout << "CAADegHstChartWndDlg::~CAADegHstChartWndDlg" << endl;
}

//--------------------------------------------------------------------------------------

void CAADegHstChartWndDlg::Build()
{
   cout << "CAADegHstChartWndDlg::Build" << endl;

  CATUnicodeString MessageNoChoosen = CATMsgCatalog::BuildMessage("CAADegHstChartWndDlg",
                                        "MessageNoChoosen",NULL,0,"No Indication");
  // Frame 1 ->Graphic
  // Frame visible and with text
  CATDlgFrame * pFrameGraphic = new CATDlgFrame(this,"FrameGraphicId",CATDlgGridLayout);
	                                             
  pFrameGraphic->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

		CATDlgLabel * pPosition = new CATDlgLabel(pFrameGraphic,"PositionId");
        pPosition->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

		CATDlgRadioButton * pVertical = new CATDlgRadioButton(pFrameGraphic,"VerticalId");
		pVertical->SetGridConstraints(0,1,1,1,CATGRID_LEFT);
        CATDlgRadioButton * pHorizont = new CATDlgRadioButton(pFrameGraphic,"HorizontId");
		pHorizont->SetGridConstraints(0,2,1,1,CATGRID_LEFT);
        
  // Frame 2 ->Max height 
  CATDlgFrame * pFrameMaxHeight = new CATDlgFrame(this,"FrameMaxHeightId",CATDlgGridLayout);
  pFrameMaxHeight->SetGridConstraints(1,0,1,1,CATGRID_LEFT);

        CATDlgLabel * pPoint1 = new CATDlgLabel(pFrameMaxHeight,"Point1Id");
        pPoint1->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

		CATDlgEditor * pEditor1 = new CATDlgEditor(pFrameMaxHeight,"Editor1Id",CATDlgEdtReadOnly );
        pEditor1->SetLine(MessageNoChoosen);
		pEditor1->SetGridConstraints(0,1,1,1,CATGRID_LEFT);

        CATDlgLabel * pPoint2 = new CATDlgLabel(pFrameMaxHeight,"Point2Id");
        pPoint2->SetGridConstraints(1,0,1,1,CATGRID_LEFT);

		CATDlgEditor * pEditor2 = new CATDlgEditor(pFrameMaxHeight,"Editor2Id",CATDlgEdtReadOnly );
        pEditor2->SetGridConstraints(1,1,1,1,CATGRID_LEFT);
		pEditor2->SetLine(MessageNoChoosen);

		CATDlgLabel * pMaxHeight = new CATDlgLabel(pFrameMaxHeight,"MaxHeightId");
        pMaxHeight->SetGridConstraints(2,0,1,1,CATGRID_LEFT);
		CATDlgEditor * pMaxHeightEditor = new CATDlgEditor(pFrameMaxHeight,"MaxHeightEditorId",CATDlgEdtReadOnly );
        
		// Default value is 100 mm 
		pMaxHeightEditor->SetLine("100");
		pMaxHeightEditor->SetGridConstraints(2,1,1,1,CATGRID_LEFT);

  // Callback for the first frame
  AddAnalyseNotificationCB(pVertical, 
	                       pVertical->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAADegHstChartWndDlg::PositionHistogramChange, NULL);
  AddAnalyseNotificationCB(pHorizont, 
	                       pHorizont->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAADegHstChartWndDlg::PositionHistogramChange, NULL);
  //Callbacks to end 
  AddAnalyseNotificationCB(this, this->GetDiaOKNotification(),
                (CATCommandMethod)&CAADegHstChartWndDlg::ClickClose,
                            NULL);
  AddAnalyseNotificationCB(this, this->GetDiaCANCELNotification(),
                (CATCommandMethod)&CAADegHstChartWndDlg::ClickClose,
                            NULL);

  // When the editor1 is selected
  AddAnalyseNotificationCB(pEditor1, pEditor1->GetEditFocusInNotification(),
                (CATCommandMethod)&CAADegHstChartWndDlg::Editor1Selected,
                            NULL);

  // When the editor1 is deselected
  AddAnalyseNotificationCB(pEditor1, pEditor1->GetEditFocusOutNotification(),
                (CATCommandMethod)&CAADegHstChartWndDlg::Editor1Deselected,
                            NULL);

  // The Cursor is set on the First Frame 
  pVertical->SetState(CATDlgCheck);
}

//--------------------------------------------------------------------------------------

void CAADegHstChartWndDlg::ClickClose    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout << "CAADegHstChartWndDlg::EnterCB" << endl;
 
   // This notification enables the state command to receive it and 
   // to value its dialog agent. 
   SendNotification(GetFather(),iNotification);
}

//--------------------------------------------------------------------------------------

void CAADegHstChartWndDlg::PositionHistogramChange    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
}

//--------------------------------------------------------------------------------------

void CAADegHstChartWndDlg::Editor1Selected    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout << "CAADegHstChartWndDlg::Editor1Selected" << endl;
 
   // This notification enables the state command to receive it and 
   // to value its dialog agent. 
   // This notification is deleted by the send/receive protocole 

   CAADegEditor1SelectedNotification * pEdt1Notification = NULL ;
   pEdt1Notification = new CAADegEditor1SelectedNotification();     
   SendNotification(GetFather(),pEdt1Notification);
   pEdt1Notification = NULL ;
}

//--------------------------------------------------------------------------------------

void CAADegHstChartWndDlg::Editor1Deselected    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout << "CAADegHstChartWndDlg::Editor1Deselected" << endl;
 
   // This notification enables the state command to receive it and 
   // to value its dialog agent. 
   // This notification is deleted by the send/receive protocole 

   CAADegEditor1DeselectedNotification * pEdt1Notification = NULL ;
   pEdt1Notification = new CAADegEditor1DeselectedNotification();     
   SendNotification(GetFather(),pEdt1Notification);
   pEdt1Notification = NULL ;
}

