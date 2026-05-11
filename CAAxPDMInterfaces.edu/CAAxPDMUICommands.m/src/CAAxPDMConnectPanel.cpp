// -------------------------------------------------------------------
// Copyright Dassault Systemes 2006
//---------------------------------------------------------------------
#include "CAAxPDMConnectPanel.h"

//include System
#include "CATMsgCatalog.h"
//include Dialog
#include "CATDlgDialog.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgFrame.h"
#include "CATDlgCombo.h"
//include CAAxPDMInterfaces
#include "CAASysDRMCtrl.h"

//========================================================================
//========================================================================
//                       ConnectPanel
//========================================================================
//========================================================================
CAAxPDMConnectPanel::CAAxPDMConnectPanel(CATDialog* parent)
:CATDlgDialog(parent,"Connect",CATDlgWndOK|CATDlgWndCANCEL|CATDlgWndTitleBarHelp)
{
   _edt1=_edt2=NULL;
   _cmb1=NULL;
   BuildPanel();
}

//------------------------------------------------------------------------
CAAxPDMConnectPanel::~CAAxPDMConnectPanel()
{
   _edt1=_edt2=NULL;
   _cmb1=NULL;
}
//------------------------------------------------------------------------
void CAAxPDMConnectPanel::BuildPanel()
{
   CATDlgFrame* frame0 = new CATDlgFrame(this,"frame0",CATDlgFraNoFrame);
   CATDlgLabel* lab0 = new CATDlgLabel(frame0,"lab0");

   CATDlgFrame* frame1 = new CATDlgFrame(this,"frame1",CATDlgFraNoFrame);
   if (NULL==frame1) return;
   
   CATDlgLabel* lab1 = new CATDlgLabel(frame1,"lab1");
   CATDlgLabel* lab2 = new CATDlgLabel(frame1,"lab2");
   CATDlgLabel* lab3 = new CATDlgLabel(frame1,"lab3");
   _edt1 = new CATDlgEditor(frame1,"Edt2",CATDlgEdtAlphanumerical|CATDlgEdtNoCR|CATDlgPowerInputLink);
   _edt2 = new CATDlgEditor(frame1,"Edt3",CATDlgEdtNoCR|CATDlgEdtPassword);
   _cmb1 = new CATDlgCombo(frame1,"Cmb1",CATDlgCmbDropDown);
   AddAnalyseNotificationCB (_cmb1,_cmb1->GetComboSelectNotification(),(CATCommandMethod) &CAAxPDMConnectPanel::ChangeRole,NULL);
   frame1->SetVerticalAttachment(0,CATDlgTopOrLeft,lab1,lab2,lab3,NULL);
   frame1->SetVerticalAttachment(1,CATDlgTopOrLeft,_edt1,_edt2,_cmb1,NULL);
   frame1->SetVerticalAttachment(2,CATDlgRightOrBottomRelative,_edt1,_edt2,_cmb1,NULL);
   frame1->SetHorizontalAttachment(1,CATDlgCenter,lab1,_edt1,NULL);
   frame1->SetHorizontalAttachment(2,CATDlgCenter,lab2,_edt2,NULL);
   frame1->SetHorizontalAttachment(3,CATDlgCenter,lab3,_cmb1,NULL);

   SetVerticalAttachment(0,CATDlgTopOrLeft,frame0,frame1,NULL);
   SetVerticalAttachment(1,CATDlgRightOrBottomRelative,frame0,frame1,NULL);
   SetHorizontalAttachment(0,CATDlgTopOrLeft,frame0,NULL);
   SetHorizontalAttachment(1,CATDlgTopOrLeft,frame1,NULL);
   SetHorizontalAttachment(2,CATDlgRightOrBottomRelative,frame1,NULL);

   _cmb1->SetLine(CATMsgCatalog::BuildMessage("CAAxPDMConnectPanel","AuthorRole"));
   _cmb1->SetLine(CATMsgCatalog::BuildMessage("CAAxPDMConnectPanel","DesignRole"));
   _cmb1->SetLine(CATMsgCatalog::BuildMessage("CAAxPDMConnectPanel","DownStreamRole"));
   _cmb1->SetSelect(0);
   _cmb1->SetVisibleTextWidth(15);
}

void CAAxPDMConnectPanel::ChangeRole(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_cmb1)
   {
      int selected = _cmb1->GetSelect();
      if (selected==0)
         _cmb1->SetShortHelp(CATMsgCatalog::BuildMessage("CAAxPDMConnectPanel","AuthorRoleHelp"));
      else if (selected==1)
         _cmb1->SetShortHelp(CATMsgCatalog::BuildMessage("CAAxPDMConnectPanel","DesignRoleHelp"));
      else if (selected==2)
         _cmb1->SetShortHelp(CATMsgCatalog::BuildMessage("CAAxPDMConnectPanel","DownStreamRoleHelp"));    
   }
}
int CAAxPDMConnectPanel::GetRole()
{
   int role=0;
   if (_cmb1)
      role = _cmb1->GetSelect();
   return role;
}

