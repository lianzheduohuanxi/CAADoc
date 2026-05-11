// COPYRIGHT Dassault Systemes 2003
//===================================================================

// Local Framework
#include "CAADlgMoreButtonDlg.h"

// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgInclude.h"
#include "CATDlgUtility.h"
#include "CATMsgCatalog.h"          // To retrieve the More and Less NLS 

// C++ standard Library
#include "iostream.h"

//-------------------------------------------------------------------------

CAADlgMoreButtonDlg::CAADlgMoreButtonDlg(CATDialog * pParentDlg) :
  CATDlgDialog (pParentDlg,"CAADlgMoreButtonDlg",CATDlgWndAutoResize | CATDlgWndBtnOKCancel |CATDlgWndNoResize ),
  _IsMoreWindowOpen(FALSE),_pFrameRightMore(NULL)

{
   cout <<" CAADlgMoreButtonDlg::CAADlgMoreButtonDlg" << endl;

   RequestStatusChange (CATCommandMsgRequestExclusiveMode);
}

//-------------------------------------------------------------------------

CAADlgMoreButtonDlg::~CAADlgMoreButtonDlg()
{
    _pFrameRightMore      = NULL ;
    cout <<" CAADlgMoreButtonDlg::~CAADlgMoreButtonDlg" << endl;
}

//-------------------------------------------------------------------------

void CAADlgMoreButtonDlg::Build()
{
   // The left More frame : always displayed
   //
   CATDlgFrame * pFrameLeftMore = new CATDlgFrame(this, "FrameLeftMore", 
                                           CATDlgGridLayout );
   SetVerticalAttachment(0, CATDlgTopOrLeft, pFrameLeftMore,NULL);
  
      // The frame with options 
      // Insert inside all the base options
      CATDlgFrame * pFrameBase = new CATDlgFrame(pFrameLeftMore, "FrameBase", 
                                                     CATDlgGridLayout );
      pFrameBase -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
	

         CATDlgLabel *pLabel004 = new CATDlgLabel(pFrameBase, "Label004");  
         pLabel004 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

         CATDlgLabel *pLabel005 = new CATDlgLabel(pFrameBase, "Label005");
         pLabel005 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

         CATDlgEditor *pEditor006 = new CATDlgEditor(pFrameBase, "Editor006");
         pEditor006 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

      // The more/less push button
      CATDlgPushButton * pPushButtonMore = new CATDlgPushButton(pFrameLeftMore, "PushButtonMore");
      pPushButtonMore -> SetGridConstraints(1, 0, 1, 1, CATGRID_RIGHT);

      _MoreMsg = CATMsgCatalog::BuildMessage("CAADlgMoreButtonDlg","ButtonMore",NULL,0,"More>>");
      _LessMsg = CATMsgCatalog::BuildMessage("CAADlgMoreButtonDlg","ButtonLess",NULL,0,"Less>>");                                       
      pPushButtonMore->SetTitle(_MoreMsg);

   // The right More frame: displayed when the end user clicks more
   // Insert inside all the more options
   //
   _pFrameRightMore = new CATDlgFrame(this, "FrameRightMore", CATDlgGridLayout );
   _pFrameRightMore->SetVisibility(CATDlgHide);

      CATDlgLabel *pLabel007 = new CATDlgLabel(_pFrameRightMore, "Label007");
      pLabel007 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

      CATDlgEditor * pEditor010 = new CATDlgEditor(_pFrameRightMore, "Editor010");
      pEditor010 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
      
      CATDlgLabel *pLabel008 = new CATDlgLabel(_pFrameRightMore, "Label008");
      pLabel008 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);

      CATDlgEditor * pEditor011 = new CATDlgEditor(_pFrameRightMore, "Editor011");
      pEditor011 -> SetGridConstraints(3, 0, 1, 1, CATGRID_4SIDES);
      
   // when the end user clicks More or Less
   AddAnalyseNotificationCB (pPushButtonMore, 
                 pPushButtonMore->GetPushBActivateNotification(),
                 (CATCommandMethod)&CAADlgMoreButtonDlg::OnPushButtonMorePushBActivateNotification,
                               NULL);

   // To close the window
   AddAnalyseNotificationCB (this, 
                               GetDiaCANCELNotification(),
                               (CATCommandMethod)&CAADlgMoreButtonDlg::CloseWindow,
                               NULL);

   AddAnalyseNotificationCB (this, 
                               GetDiaOKNotification(),
                               (CATCommandMethod)&CAADlgMoreButtonDlg::CloseWindow,
                               NULL);
   AddAnalyseNotificationCB (this, 
                               GetWindCloseNotification(),
                               (CATCommandMethod)&CAADlgMoreButtonDlg::CloseWindow,
                               NULL);

}

//-------------------------------------------------------------------------

void CAADlgMoreButtonDlg::OnPushButtonMorePushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{

   CATDlgPushButton * pButton = (CATDlgPushButton *) cmd ;
   if ( (NULL != pButton ) && (NULL !=_pFrameRightMore) )
   {
      if( TRUE == _IsMoreWindowOpen)
      {
         // To do that, reset the attachment 
         ResetAttachment(_pFrameRightMore);         

         // hide the more panel
         _pFrameRightMore->SetVisibility(CATDlgHide);         

         pButton->SetTitle (_MoreMsg);

         _IsMoreWindowOpen= FALSE;
      }
	  else
      {
         // To do that, define a new tabulation
         SetVerticalAttachment(10, CATDlgTopOrLeft, _pFrameRightMore, NULL);

         // show the more panel
         _pFrameRightMore->SetVisibility(CATDlgShow);         

         pButton->SetTitle (_LessMsg);

         _IsMoreWindowOpen = TRUE;
      }
   }
}

//-------------------------------------------------------------------------

void CAADlgMoreButtonDlg::CloseWindow(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   SetVisibility (CATDlgHide);
   this->RequestDelayedDestruction();
}

// ----------------------------------------------------

CATStatusChangeRC CAADlgMoreButtonDlg::Activate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
   SetVisibility(CATDlgShow);
   return (CATStatusChangeRCCompleted);
}

// ----------------------------------------------------

CATStatusChangeRC CAADlgMoreButtonDlg::Desactivate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
   SetVisibility (CATDlgHide);
   return (CATStatusChangeRCCompleted);
}

// ----------------------------------------------------

CATStatusChangeRC CAADlgMoreButtonDlg::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
{
   SetVisibility (CATDlgHide);
   RequestDelayedDestruction();
   return (CATStatusChangeRCCompleted);
}


