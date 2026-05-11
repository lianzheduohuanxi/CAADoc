// COPYRIGHT Dassault Systemes 2006
#include "CAAxPDMDRMTemplatePanel.h"

//include System
#include "CATMsgCatalog.h"
#include "CATListOfCATUnicodeString.h"
#include "CATSysDRMRights.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
//include Dialog
#include "CATDlgDialog.h"
#include "CATDlgNotify.h"
#include "CATDlgFrame.h"
#include "CATDlgPushButton.h"
#include "CATDlgMultiList.h"
#include "CATDlgSeparator.h"
#include "CATDlgLabel.h"
#include "CATDlgRadioButton.h"
//include CAAxPDMIntegration
#include "CAASysDRMCtrl.h"


//------------------------------------------------------------------------
CAAxPDMDRMTemplatePanel::CAAxPDMDRMTemplatePanel(CATDialog* parent)
:CATDlgDialog(parent,"DRMTemplate",CATDlgWndBtnOKCancel|CATDlgWndHELP|CATDlgWndTitleBarHelp)
{
   strTRUE = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","StatusOK",NULL,0,"True");
   BuildPanel();
}
//------------------------------------------------------------------------
CAAxPDMDRMTemplatePanel::~CAAxPDMDRMTemplatePanel()
{
   _Multi=NULL;
   _rad0=_rad1=_rad2=NULL;
   _RemoveBut=NULL;
}

//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::BuildPanel()
{
   CATDlgFrame* frame0 = new CATDlgFrame(this,"frame0",CATDlgFraNoFrame);
   CATDlgLabel* lab0 = new CATDlgLabel(frame0,"lab0");
   CATDlgSeparator* sep0 = new CATDlgSeparator(frame0,"sep0",CATDlgCtrHorizontal);
   frame0->SetHorizontalAttachment(0,CATDlgCenter,lab0,sep0,NULL);
   frame0->SetVerticalAttachment(0,CATDlgTopOrLeft,lab0,NULL);
   frame0->SetVerticalAttachment(1,CATDlgTopOrLeft,sep0,NULL);
   frame0->SetVerticalAttachment(2,CATDlgRightOrBottomRelative,sep0,NULL);

   CATDlgFrame* frame1 = new CATDlgFrame(this,"frame1",CATDlgFraNoFrame);
   _rad0 = new CATDlgRadioButton(frame1,"Rad0");
   _rad1 = new CATDlgRadioButton(frame1,"Rad1");
   _rad2 = new CATDlgRadioButton(frame1,"Rad2");
   frame1->SetVerticalAttachment(1,CATDlgTopOrLeft,_rad0,NULL);
   frame1->SetVerticalAttachment(2,CATDlgRightOrBottomRelative,_rad0,NULL);
   frame1->SetVerticalAttachment(3,CATDlgTopOrLeft,_rad1,NULL);
   frame1->SetVerticalAttachment(4,CATDlgRightOrBottomRelative,_rad1,NULL);
   frame1->SetVerticalAttachment(5,CATDlgTopOrLeft,_rad2,NULL);
   frame1->SetVerticalAttachment(6,CATDlgRightOrBottomRelative,_rad2,NULL);
   frame1->SetHorizontalAttachment(0,CATDlgCenter,_rad0,_rad1,_rad2,NULL);

   CATDlgFrame* frame2 = new CATDlgFrame(this,"frame2",CATDlgFraNoFrame);
   CATDlgLabel* lab2 = new CATDlgLabel(frame2,"lab2");
   CATDlgSeparator* sep2 = new CATDlgSeparator(frame2,"sep2",CATDlgCtrHorizontal);
   frame2->SetHorizontalAttachment(0,CATDlgCenter,lab2,sep2,NULL);
   frame2->SetVerticalAttachment(0,CATDlgTopOrLeft,lab2,NULL);
   frame2->SetVerticalAttachment(1,CATDlgTopOrLeft,sep2,NULL);
   frame2->SetVerticalAttachment(2,CATDlgRightOrBottomRelative,sep2,NULL);

   CATDlgFrame* frame3 = new CATDlgFrame(this,"frame3",CATDlgFraNoFrame);
   _Multi=new CATDlgMultiList(frame3, "DRMUsersList",CATDlgLstAutoSort);

   _Multi->SetColumnEditable(0,TRUE);
   _Multi->SetColumnSortMethod(1,AlphabeticalOrder);
   _Multi->SetColumnTextWidth(0,10);
   _Multi->SetTitlesVisibility(CATDlgShow);
   _Multi->SetVisibleLineCount(10);

   const int nbcolumn=11;
   _Multi->SetVisibleColumnCount(nbcolumn);
   CATUnicodeString lTitles[nbcolumn];
   lTitles[0] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles0",NULL,0,"User Name");
   lTitles[1] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles1",NULL,0,"Open");
   lTitles[2] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles2",NULL,0,"Save");
   lTitles[3] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles3",NULL,0,"SaveAs");
   lTitles[4] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles4",NULL,0,"InheritSaveAs");
   lTitles[5] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles5",NULL,0,"Export");
   lTitles[6] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles6",NULL,0,"DuplicateSpec");
   lTitles[7] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles7",NULL,0,"Change Right");
   lTitles[8] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles8",NULL,0,"Collaborate");
   lTitles[9] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles9",NULL,0,"Copy-Cut");
   lTitles[10] = CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","multiListTitles10",NULL,0,"Copy Geometry");
   _Multi->SetColumnTitles(nbcolumn,lTitles);

   _Multi->SetColumnTextWidth(1,4);//CATDRM_READ;
   _Multi->SetColumnTextWidth(2,4);//CATDRM_SAVE;
   _Multi->SetColumnTextWidth(3,11);//CATDRM_SAVEAS;
   _Multi->SetColumnTextWidth(4,10);//CATDRM_INHERIT_SAVEAS;
   _Multi->SetColumnTextWidth(5,4);//CATDRM_EXPORT;
   _Multi->SetColumnTextWidth(6,8);//CATDRM_DUPLICATE_SPECS;
   _Multi->SetColumnTextWidth(7,7);//CATDRM_EDITRIGHT;
   _Multi->SetColumnTextWidth(8,6);//CATDRM_COLLABORATION;
   _Multi->SetColumnTextWidth(9,5);//CATDRM_COPY;
   _Multi->SetColumnTextWidth(10,8);//CATDRM_COPY_GEOMETRY;

   for (int i=1;i<=nbcolumn-1;i++)
      _Multi->SetColumnSortMethod(i,AlphabeticalOrder);

   CATDlgFrame* frame31 = new CATDlgFrame(frame3,"frame31",CATDlgFraNoFrame);
   if (NULL==frame31) return;
   CATDlgPushButton* Push1 =new CATDlgPushButton(frame31, "AddUser");
   CATDlgPushButton* Push2 =new CATDlgPushButton(frame31, "AddSupplier");
   CATDlgPushButton* Push3 =new CATDlgPushButton(frame31, "AddSupplier2");
   _RemoveBut =new CATDlgPushButton(frame31, "RemoveUser");
   _RemoveBut->SetSensitivity(CATDlgDisable);
   frame31->SetHorizontalAttachment(0,CATDlgTopOrLeft,Push1,NULL);
   frame31->SetHorizontalAttachment(1,CATDlgTopOrLeft,Push2,NULL);
   frame31->SetHorizontalAttachment(2,CATDlgTopOrLeft,Push3,NULL);
   frame31->SetHorizontalAttachment(3,CATDlgTopOrLeft,_RemoveBut,NULL);
   frame31->SetVerticalAttachment(0,CATDlgTopOrLeft,Push1,Push2,Push3,_RemoveBut,NULL);
   frame31->SetVerticalAttachment(1,CATDlgRightOrBottomRelative,Push1,Push2,Push3,_RemoveBut,NULL);

   AddAnalyseNotificationCB( _Multi, _Multi->GetListSelectNotification(),(CATCommandMethod)& CAAxPDMDRMTemplatePanel::SelectCB, NULL);
   AddAnalyseNotificationCB( _Multi, _Multi->GetListActivateNotification(),(CATCommandMethod)& CAAxPDMDRMTemplatePanel::ActivateCB, NULL);
   AddAnalyseNotificationCB( Push1, Push1->GetPushBActivateNotification(),(CATCommandMethod)& CAAxPDMDRMTemplatePanel::Add1CB, NULL);
   AddAnalyseNotificationCB( Push2, Push2->GetPushBActivateNotification(),(CATCommandMethod)& CAAxPDMDRMTemplatePanel::Add2CB, NULL);
   AddAnalyseNotificationCB( Push3, Push3->GetPushBActivateNotification(),(CATCommandMethod)& CAAxPDMDRMTemplatePanel::Add3CB, NULL);
   AddAnalyseNotificationCB( _RemoveBut, _RemoveBut->GetPushBActivateNotification(),(CATCommandMethod)& CAAxPDMDRMTemplatePanel::RemoveCB, NULL);

   frame3->SetHorizontalAttachment(0,CATDlgTopOrLeft,_Multi,frame31,NULL);
   frame3->SetHorizontalAttachment(1,CATDlgRightOrBottomRelative,_Multi,frame31,NULL);
   frame3->SetVerticalAttachment(0,CATDlgTopOrLeft,_Multi,NULL);
   frame3->SetVerticalAttachment(1,CATDlgRightOrBottomRelative,_Multi,NULL);
   frame3->SetVerticalAttachment(2,CATDlgTopOrLeft,frame31,NULL);


   SetHorizontalAttachment(0,CATDlgTopOrLeft,frame0,NULL);
   SetHorizontalAttachment(1,CATDlgTopOrLeft,frame1,NULL);
   SetHorizontalAttachment(2,CATDlgTopOrLeft,frame2,NULL);
   SetHorizontalAttachment(3,CATDlgTopOrLeft,frame3,NULL);
   SetHorizontalAttachment(4,CATDlgRightOrBottomRelative,frame3,NULL);
   SetVerticalAttachment(0,CATDlgTopOrLeft,frame0,frame1,frame2,frame3,NULL);
   SetVerticalAttachment(1,CATDlgRightOrBottomRelative,frame0,frame1,frame2,frame3,NULL);
   SetDefaultButton(NULL);
}


//------------------------------------------------------------------------
//   Update Panel
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::Refresh()
{
   CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
   if (ctrl == NULL) return ;
   CATUnicodeString * DRMUser=NULL;
   DWORD*             DRMRight=NULL;
   int                DRMUserNb=0;
   ctrl->GetAuthorization(DRMUser,DRMRight,DRMUserNb);
   if (DRMUserNb)
   {
      for (int i=0; i< DRMUserNb; i++ )
      {
         CATUnicodeString user = DRMUser [i];
         _Multi->SetColumnItem(0, user);
         DWORD Right = DRMRight [i];
         if ((Right &CATDRM_READ) ==CATDRM_READ)                        _Multi->SetColumnItem(1, strTRUE); else _Multi->SetColumnItem(1, "");
         if ((Right &CATDRM_SAVE) ==CATDRM_SAVE)                        _Multi->SetColumnItem(2, strTRUE); else _Multi->SetColumnItem(2, "");
         if ((Right &CATDRM_SAVEAS) ==CATDRM_SAVEAS)                    _Multi->SetColumnItem(3, strTRUE); else _Multi->SetColumnItem(3, "");
         if ((Right &CATDRM_INHERIT_SAVEAS) ==CATDRM_INHERIT_SAVEAS)    _Multi->SetColumnItem(4, strTRUE); else _Multi->SetColumnItem(4, "");
         if ((Right &CATDRM_EXPORT) ==CATDRM_EXPORT)                    _Multi->SetColumnItem(5, strTRUE); else _Multi->SetColumnItem(5, "");
         if ((Right &CATDRM_DUPLICATE_SPECS) ==CATDRM_DUPLICATE_SPECS)  _Multi->SetColumnItem(6, strTRUE); else _Multi->SetColumnItem(6, "");
         if ((Right &CATDRM_EDITRIGHT) ==CATDRM_EDITRIGHT)              _Multi->SetColumnItem(7, strTRUE); else _Multi->SetColumnItem(7, "");
         if ((Right &CATDRM_COLLABORATION) ==CATDRM_COLLABORATION)      _Multi->SetColumnItem(8, strTRUE); else _Multi->SetColumnItem(8, "");
         if ((Right &CATDRM_COPY) ==CATDRM_COPY)                        _Multi->SetColumnItem(9, strTRUE); else _Multi->SetColumnItem(9, "");
         if ((Right &CATDRM_COPY_GEOMETRY) ==CATDRM_COPY_GEOMETRY)      _Multi->SetColumnItem(10, strTRUE); else _Multi->SetColumnItem(10, "");
      }
   }
   if (DRMUser) delete [] DRMUser; DRMUser=NULL;
   if (DRMRight) delete [] DRMRight; DRMRight=NULL;

   int iDRMActivation=0;
   if (_rad0) _rad0->SetState(CATDlgCheck);
   ctrl->GetDRMActivation(iDRMActivation);
   if (iDRMActivation && _rad1 && _rad2)
   {
      ctrl->GetSymetricKeySize(iDRMActivation);
      if (iDRMActivation==16)
         _rad1->SetState(CATDlgCheck);
      else
         _rad2->SetState(CATDlgCheck);
   }
}

//------------------------------------------------------------------------
//   Validate
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::Validate()
{
   CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
   if (ctrl == NULL) return ;

   int oProfile=0;
   if (SUCCEEDED(ctrl->DRMGetProfile(oProfile)) && oProfile==0)
   {
      CATUnicodeString * DRMUser=NULL;
      DWORD*             DRMRight=NULL;
      int                DRMUserNb=0;
      if (_Multi)
      {
         DRMUserNb = _Multi->GetLineCount();
         if (DRMUserNb)
         {
            DRMUser = new CATUnicodeString [DRMUserNb];
            DRMRight = new DWORD [DRMUserNb];
            for (int i=0; i< DRMUserNb; i++ )
            {
               // Update of user name
               CATUnicodeString User;
               _Multi->GetColumnItem( 0, User, i);
               DRMUser [i] = User;
               //Update Rights
               DWORD Right = 0;
               CATUnicodeString strRight;
               _Multi->GetColumnItem( 1, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_READ;
               _Multi->GetColumnItem( 2, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_SAVE;
               _Multi->GetColumnItem( 3, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_SAVEAS;
               _Multi->GetColumnItem( 4, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_INHERIT_SAVEAS;
               _Multi->GetColumnItem( 5, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_EXPORT;
               _Multi->GetColumnItem( 6, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_DUPLICATE_SPECS;
               _Multi->GetColumnItem( 7, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_EDITRIGHT;
               _Multi->GetColumnItem( 8, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_COLLABORATION;
               _Multi->GetColumnItem( 9, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_COPY;
               _Multi->GetColumnItem(10, strRight, i);  if (strRight==strTRUE)  Right |= CATDRM_COPY_GEOMETRY;
               DRMRight [i] = Right;
            }
         }
      }
      ctrl->SetAuthorization(DRMUser,DRMRight,DRMUserNb);

      if (_rad0 && _rad0->GetState()==CATDlgCheck)
         ctrl->SetDRMActivation(0);
      else
      {
         ctrl->SetDRMActivation(1);
         int criptmode = 16;
         if (_rad2 && _rad2->GetState()==CATDlgCheck)
            criptmode = 32;
         ctrl->SetSymetricKeySize(criptmode);
      }
      if (DRMUser) delete [] DRMUser; DRMUser=NULL;
      if (DRMRight) delete [] DRMRight; DRMRight=NULL;
   }
   else
   {
      //Only author can modify session rights
      CATDlgNotify* notif = new CATDlgNotify(this,"Error",CATDlgNfyError);
      CATUnicodeString texte=CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","NoChangeDRM");
      CATUnicodeString title=CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","Error");
      notif->DisplayBlocked(texte,title);
      notif->RequestDelayedDestruction(); notif=NULL;
   }
}

//------------------------------------------------------------------------
//   Add User with default rights (None)
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::Add1CB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   //Add New User
   if ( _Multi==NULL) return;
   CATUnicodeString User=CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","NewUser",NULL,0,"User");
   _Multi->SetColumnItem( 0, User);
   //Init rights
   _Multi->SetColumnItem(1,strTRUE); //CATDRM_READ;
   _Multi->SetColumnItem(2,strTRUE); //CATDRM_SAVE;
   _Multi->SetColumnItem(3,strTRUE); //CATDRM_SAVEAS;
   _Multi->SetColumnItem(4,"");      //CATDRM_INHERIT_SAVEAS;
   _Multi->SetColumnItem(5,strTRUE); //CATDRM_EXPORT;
   _Multi->SetColumnItem(6,strTRUE); //CATDRM_DUPLICATE_SPECS;
   _Multi->SetColumnItem(7,strTRUE); //CATDRM_EDITRIGHT;
   _Multi->SetColumnItem(8,strTRUE); //CATDRM_COLLABORATION;
   _Multi->SetColumnItem(9,strTRUE); //CATDRM_COPY;
   _Multi->SetColumnItem(10,strTRUE);//CATDRM_COPY_GEOMETRY;
   //Select new user
   int line = _Multi->GetLineCount()-1; //multilist start at 0
   _Multi->SetSelect(&line,1);
}
//------------------------------------------------------------------------
//   Add New Design Supplier
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::Add2CB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if ( _Multi==NULL) return;
   CATUnicodeString User=CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","NewSupplier",NULL,0,"Supplier");
   _Multi->SetColumnItem( 0, User);
   //Init rights
   _Multi->SetColumnItem(1,strTRUE); //CATDRM_READ;
   _Multi->SetColumnItem(2,strTRUE); //CATDRM_SAVE;
   _Multi->SetColumnItem(3,"");      //CATDRM_SAVEAS;
   _Multi->SetColumnItem(4,strTRUE); //CATDRM_INHERIT_SAVEAS;
   _Multi->SetColumnItem(5,"");      //CATDRM_EXPORT;
   _Multi->SetColumnItem(6,"");      //CATDRM_DUPLICATE_SPECS;
   _Multi->SetColumnItem(7,"");      //CATDRM_EDITRIGHT;
   _Multi->SetColumnItem(8,"");      //CATDRM_COLLABORATION;
   _Multi->SetColumnItem(9,"");      //CATDRM_COPY;
   _Multi->SetColumnItem(10,"");     //CATDRM_COPY_GEOMETRY;
   //Select new user
   int line = _Multi->GetLineCount()-1; //multilist start at 0
   _Multi->SetSelect(&line,1);
}
//------------------------------------------------------------------------
//   Add New Downstream Supplier
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::Add3CB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if ( _Multi==NULL) return;
   CATUnicodeString User=CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","NewSupplier2",NULL,0,"Supplier");
   _Multi->SetColumnItem( 0, User);
   //Init rights
   _Multi->SetColumnItem(1,strTRUE); //CATDRM_READ;
   _Multi->SetColumnItem(2,"");      //CATDRM_SAVE;
   _Multi->SetColumnItem(3,"");      //CATDRM_SAVEAS;
   _Multi->SetColumnItem(4,"");      //CATDRM_INHERIT_SAVEAS;
   _Multi->SetColumnItem(5,"");      //CATDRM_EXPORT;
   _Multi->SetColumnItem(6,"");      //CATDRM_DUPLICATE_SPECS;
   _Multi->SetColumnItem(7,"");      //CATDRM_EDITRIGHT;
   _Multi->SetColumnItem(8,"");      //CATDRM_COLLABORATION;
   _Multi->SetColumnItem(9,"");      //CATDRM_COPY;
   _Multi->SetColumnItem(10,strTRUE);//CATDRM_COPY_GEOMETRY;
   //Select new user
   int line = _Multi->GetLineCount()-1; //multilist start at 0
   _Multi->SetSelect(&line,1);
}
//------------------------------------------------------------------------
//   Remove User
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::RemoveCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if ( _Multi==NULL) return;
   if (_Multi && _Multi->GetSelectCount()==1)
   {
      //Get deleted user
      int oline=0;
      _Multi->GetSelect(&oline,1);
      _Multi->ClearLine(oline);
      _RemoveBut->SetSensitivity(CATDlgDisable);
   }
}

//------------------------------------------------------------------------
//   
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::SelectCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_Multi && _Multi->GetSelectCount() && _RemoveBut)
      _RemoveBut->SetSensitivity(CATDlgEnable);
   else
      _RemoveBut->SetSensitivity(CATDlgDisable);
}

//------------------------------------------------------------------------
//   
//------------------------------------------------------------------------
void CAAxPDMDRMTemplatePanel::ActivateCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_Multi && _Multi->GetLineCount())
   {
      int oRowIndex=0, oColumnIndex=0;
      oColumnIndex = _Multi->GetSelectedColumn();
      _Multi->GetSelect(&oRowIndex,1);
      if (oColumnIndex!=0)
      {
         CATUnicodeString value;
         _Multi->GetColumnItem(oColumnIndex,value,oRowIndex);
         if (value==strTRUE)
            _Multi->SetColumnItem(oColumnIndex,"",oRowIndex,CATDlgDataModify);
         else
         {
            _Multi->SetColumnItem(oColumnIndex,strTRUE,oRowIndex,CATDlgDataModify);
            //Rights CATDRM_INHERIT_SAVEAS and CATDRM_SAVEAS are exclusive
            if (oColumnIndex==3)
               _Multi->SetColumnItem(4,"",oRowIndex,CATDlgDataModify);
            if (oColumnIndex==4)
               _Multi->SetColumnItem(3,"",oRowIndex,CATDlgDataModify);
         }
      }
   }
}

