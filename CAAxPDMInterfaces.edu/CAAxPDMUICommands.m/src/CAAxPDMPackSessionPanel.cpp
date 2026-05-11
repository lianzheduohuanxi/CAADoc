// COPYRIGHT Dassault Systemes 2006
/**
* 05:10:25
* 06:03:21 Add Check of Design Rules before Save
* 06:04:20 Add of Preview frame
*/
#include "CAAxPDMPackSessionPanel.h"

//include System
#include "CATMsgCatalog.h"
#include "CATListOfCATUnicodeString.h"
//include ObjectModelerBase
#include "CATIDocEnvironment.h"
#include "CATIDocId.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
//include Dialog
#include "CATDlgDialog.h"
#include "CATDlgLabel.h"
#include "CATDlgFrame.h"
#include "CATDlgEditor.h"
#include "CATDlgMultiList.h"
#include "CATDlgCheckButton.h"
#include "CATDlgPushButton.h"
#include "CATDlgFile.h"
//include CATxPDMInterfaces
#include "CATIxPDMItem.h" 
#include "CATListOfCATIxPDMItem.h" 
//include CAAxPDMInterfaces.edu
#include "CAAxPDMItemPreviewFrame.h"


CATUnicodeString RetrieveNameFromPath(CATUnicodeString& iPath);

//------------------------------------------------------------------------
CAAxPDMPackSessionPanel::CAAxPDMPackSessionPanel(CATDialog* parent)
:CATDlgDialog(parent,"SaveSessionToDir",CATDlgWndOK|CATDlgWndAPPLY|CATDlgWndCANCEL|CATDlgWndHELP|CATDlgWndTitleBarHelp)
{
   _edt=NULL;
   _dirSelPopup=NULL;
   _itemlist=NULL;
   _chk1=_chk2=_chk3=_chk4=_chk5=_chk6=_chk7=NULL;
   BuildPanel();
}
//------------------------------------------------------------------------
CAAxPDMPackSessionPanel::~CAAxPDMPackSessionPanel()
{
   _edt=NULL;
   _list=NULL;
   _but1=NULL;
   _itemlist=NULL;
   _dirSelPopup=NULL;
   _chk1=_chk2=_chk3=_chk4=_chk5=_chk6=_chk7=NULL;
   _previewframe=NULL;
}
//------------------------------------------------------------------------
void CAAxPDMPackSessionPanel::BuildPanel()
{
   CATDlgFrame* frame1 = new CATDlgFrame(this,"frame1",CATDlgFraNoFrame);
   if (NULL==frame1) return;
   CATDlgLabel* lab1 = new CATDlgLabel(frame1,"lab1");
   _edt = new CATDlgEditor(frame1,"Edt1",CATDlgPowerInputLink);
   _edt->SetVisibleTextWidth(15);
   _but1 = new CATDlgPushButton(frame1,"but1");
   frame1->SetVerticalAttachment(0,CATDlgTopOrLeft,lab1,NULL);
   frame1->SetVerticalAttachment(1,CATDlgTopOrLeft,_edt,NULL);
   frame1->SetVerticalAttachment(2,CATDlgRightOrBottomRelative,_edt,NULL);
   frame1->SetVerticalAttachment(3,CATDlgTopOrLeft,_but1,NULL);
   frame1->SetHorizontalAttachment(0,CATDlgCenter,lab1,_edt,_but1,NULL);
   
   CATDlgFrame* frame2 = new CATDlgFrame(this,"frame2",CATDlgFraNoFrame);
   if (NULL==frame2) return;
   _list = new CATDlgMultiList(frame2,"List1");
   if (NULL==_list) return;
   CATUnicodeString aTitle;
   CATUnicodeString multiListTitles[4]; 
   multiListTitles[0] = CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","multiListTitles0",NULL,0,"Default Name");
   multiListTitles[1] = CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","multiListTitles1",NULL,0,"Status");
   multiListTitles[2] = CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","multiListTitles2",NULL,0,"Access");
   multiListTitles[3] = CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","multiListTitles3",NULL,0,"New Name");
   _list->SetColumnTitles(4, multiListTitles);
   _list->SetColumnVisibility(0, CATDlgShow);
   _list->SetColumnVisibility(1, CATDlgShow);
   _list->SetColumnVisibility(2, CATDlgShow);
   _list->SetColumnVisibility(3, CATDlgShow);
   _list->SetColumnTextWidth(0,20);
   _list->SetColumnTextWidth(1,4);
   _list->SetColumnTextWidth(2,4);
   _list->SetColumnTextWidth(3,15);
   _list->SetVisibleTextWidth(50);
   _list->SetColumnEditable(3,TRUE);
   _previewframe = new CAAxPDMItemPreviewFrame(frame2,"preview",CATDlgFraNoFrame);
   frame2->SetVerticalAttachment(0,CATDlgTopOrLeft,_list,NULL);
   frame2->SetVerticalAttachment(1,CATDlgRightOrBottomRelative,_list,NULL);
   frame2->SetVerticalAttachment(2,CATDlgTopOrLeft,_previewframe,NULL);
   frame2->SetHorizontalAttachment(0,CATDlgTopOrLeft,_list,_previewframe,NULL);
   frame2->SetHorizontalAttachment(1,CATDlgRightOrBottomRelative,_list,NULL);

   CATDlgLabel* label = new CATDlgLabel(this,"ActivateCheck");
   CATDlgFrame* frame3 = new CATDlgFrame(this,"frame3",CATDlgFraNoFrame);
   frame3->SetDefaultOrientation(Vertical);
   _chk1 = new CATDlgCheckButton(frame3,"RESOLVED_IMPORT");
   _chk2 = new CATDlgCheckButton(frame3,"SYNCHRONIZED_IMPORT");
   _chk3 = new CATDlgCheckButton(frame3,"NESTED_IMPORT");
   _chk4 = new CATDlgCheckButton(frame3,"NESTED_LEVEL");
   _chk5 = new CATDlgCheckButton(frame3,"CYCLES");
   _chk6 = new CATDlgCheckButton(frame3,"ONLY_PUBLICATIONS");
   _chk7 = new CATDlgCheckButton(frame3,"READONLY_CONSISTENCY");
   frame3->SetVerticalAttachment(0,CATDlgTopOrLeft,_chk1,_chk2,_chk6,NULL);
   frame3->SetVerticalAttachment(2,CATDlgTopOrLeft,_chk3,_chk5,_chk4,NULL);
   frame3->SetVerticalAttachment(4,CATDlgTopOrLeft,_chk7,NULL);
   frame3->SetHorizontalAttachment(0,CATDlgTopOrLeft,_chk1,_chk3,_chk7,NULL);
   frame3->SetHorizontalAttachment(2,CATDlgTopOrLeft,_chk2,_chk5,NULL);
   frame3->SetHorizontalAttachment(4,CATDlgTopOrLeft,_chk6,_chk4,NULL);

   SetVerticalAttachment(0,CATDlgTopOrLeft,frame1,frame2,label,frame3,NULL);
   SetVerticalAttachment(2,CATDlgRightOrBottomRelative,frame1,frame2,label,frame3,NULL);
   SetHorizontalAttachment(0,CATDlgTopOrLeft,frame1,NULL);
   SetHorizontalAttachment(1,CATDlgTopOrLeft,frame2,NULL);
   SetHorizontalAttachment(2,CATDlgRightOrBottomRelative,frame2,NULL);
   SetHorizontalAttachment(3,CATDlgTopOrLeft,label,NULL);
   SetHorizontalAttachment(4,CATDlgTopOrLeft,frame3,NULL);

   AddAnalyseNotificationCB (_but1,_but1->GetPushBActivateNotification(),
	   (CATCommandMethod) &CAAxPDMPackSessionPanel::SelectDirCB,NULL);
   AddAnalyseNotificationCB (_list,_list->GetListSelectNotification(),
	   (CATCommandMethod) &CAAxPDMPackSessionPanel::ActivateLineCB,NULL);

   SetAPPLYTitle(CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","APPLYButton.Title",NULL,0,"Check"));
}

CATUnicodeString CAAxPDMPackSessionPanel::GetCurrentPath()
{
   CATUnicodeString sortie;
   if (_edt)
      sortie=_edt->GetText();
   return sortie;
}

//------------------------------------------------------------------------
//   Mise a jour du panel
//------------------------------------------------------------------------
void CAAxPDMPackSessionPanel::SetListInfo(const CATListOfCATUnicodeString& ListName,const CATListOfCATUnicodeString& ListStatus,
                                          const CATListOfCATString& ListAccess)
{
   if (_list)
   {
      _list->ClearLine();
      int iSize=ListName.Size();
      for (int kk=1;kk<=iSize;kk++)
      {
         _list->SetColumnItem(0,ListName[kk]);
         _list->SetColumnItem(1,ListStatus[kk]);
         _list->SetColumnItem(2,"",ListAccess[kk]);
      }
      if (iSize)
      {
         int tab=0;
         _list->SetSelect(&tab,1);
      }
   }
}

//------------------------------------------------------------------------
boolean CAAxPDMPackSessionPanel::RefreshPanel(CATListValCATIxPDMItem_var* ListItem)
{
   _itemlist=ListItem;
   boolean sortie=FALSE;
   CATListOfCATUnicodeString ListName;
   CATListOfCATUnicodeString ListStatus;
   CATListOfCATString ListAccess;

   CATUnicodeString strNew = CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","StatusNew",NULL,0,"N");
   CATUnicodeString strModified = CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","StatusModified",NULL,0,"M");

   if (ListItem)
   {
      if (ListItem->Size())
         sortie=TRUE;
      CATLISTP_FORWARD_LOOP(*ListItem,kk)
      {
         CATIxPDMItem_var item = (*ListItem)[kk];
         if (!!item)
         {
            //Name
            CATUnicodeString name;
            CATIDocId* docid=NULL;
            if (SUCCEEDED(item->GetDocId(docid)) && docid)
            {
               CATIDocEnvironment* pDocEnv = NULL;
               HRESULT hr = docid->GetDocEnvironment(&pDocEnv);
               if (SUCCEEDED(hr) && pDocEnv != NULL)
                  hr = pDocEnv->GetDocDisplayName(docid, name);
               if (pDocEnv != NULL)
                  pDocEnv->Release();
               pDocEnv=NULL;
               if (docid != NULL)
                  docid->Release();
               docid=NULL;
            }
            //Name
            if (!name.GetLengthInChar())
               item->GetDocFileName(name);
            name = RetrieveNameFromPath(name);
            //Status computation
            CATUnicodeString status,savepath;
            CATBoolean tobesaved=FALSE;
            item->NeedToBeSaved(tobesaved);
            if (item->GetLastSavePath(savepath)==S_FALSE)
               status=strNew;
            else if (tobesaved)
               status=strModified;
            //Access computation
            CATString access;
            CATBoolean readonly=FALSE;
            item->GetReadOnlyStatus(readonly);
            if (readonly)
            {
               if (tobesaved)
                  access="I_CAAPX1StatusCheckInModif";
               else
                  access="I_CAAPX1StatusCheckIn";
            }
            //Fill Lists
            ListName.Append(name);
            ListStatus.Append(status);
            ListAccess.Append(access);
         }
      }
      CATLISTP_END_LOOP;
   }
   SetListInfo(ListName,ListStatus,ListAccess);
   return sortie;
}

void CAAxPDMPackSessionPanel::SetCurrentPath(const CATUnicodeString& iCurEnv)
{
   if (NULL==_edt) return;
   _edt->SetText(iCurEnv);
}
CATListOfCATUnicodeString CAAxPDMPackSessionPanel::GetListOfRenamedItems()
{
   CATListOfCATUnicodeString sortie;
   if (_list)
   {
      int nb = _list->GetLineCount();
      CATUnicodeString name;
      for (int i=0;i<nb;i++)
      {
         _list->GetColumnItem(3,name,i);
         sortie.Append(name);
      }
   }
   return sortie;
}

CATListOfCATString CAAxPDMPackSessionPanel::GetListOfChecks()
{
   CATListOfCATString sortie;
   if (_chk1 && _chk1->GetState()==CATDlgCheck)
      sortie.Append(_chk1->GetName());
   if (_chk2 && _chk2->GetState()==CATDlgCheck)
      sortie.Append(_chk2->GetName());
   if (_chk3 && _chk3->GetState()==CATDlgCheck)
   {
      CATString name = _chk3->GetName() + "=3";
      sortie.Append(name);
   }
   if (_chk4 && _chk4->GetState()==CATDlgCheck)
   {
      CATString name = _chk4->GetName() + "=4";
      sortie.Append(name);
   }
   if (_chk5 && _chk5->GetState()==CATDlgCheck)
      sortie.Append(_chk5->GetName());
   if (_chk6 && _chk6->GetState()==CATDlgCheck)
      sortie.Append(_chk6->GetName());
   if (_chk7 && _chk7->GetState()==CATDlgCheck)
      sortie.Append(_chk7->GetName());
   return sortie;
}

void CAAxPDMPackSessionPanel::SelectDirCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{ 

	if (!_dirSelPopup)
	{
      CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame();
      if (!CATSysCheckExpression(pFrame)) return;
      
      _dirSelPopup = new CATDlgFile(this,"SelDir",CATDlgWndModal|CATDlgFolderChooser);
      if (_dirSelPopup)
      {
         _dirSelPopup->SetDirectory ( GetCurrentPath() );
         _dirSelPopup->SetTitle (CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","SelectDir",NULL,0,"Directory"));
	
         AddAnalyseNotificationCB (_dirSelPopup,_dirSelPopup->GetDiaCANCELNotification(),
            (CATCommandMethod)&CAAxPDMPackSessionPanel::DirCancelledCB,NULL);
         
         AddAnalyseNotificationCB (_dirSelPopup,_dirSelPopup->GetDiaOKNotification(),
            (CATCommandMethod)&CAAxPDMPackSessionPanel::DirSelectedCB,NULL);
         
         _dirSelPopup->SetVisibility (CATDlgShow);
      }
	}
}

void CAAxPDMPackSessionPanel::DirCancelledCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   CATAssert( _dirSelPopup );
   _dirSelPopup->RequestDelayedDestruction();
   _dirSelPopup->Release();
   _dirSelPopup = NULL;
}


void CAAxPDMPackSessionPanel::DirSelectedCB (CATCommand*, CATNotification* iNotif, CATCommandClientData iData)
{
   CATAssert( _dirSelPopup );
   
   CATUnicodeString str;
   _dirSelPopup->GetDirectory (str);
   
   SetCurrentPath( str );
   _dirSelPopup->RequestDelayedDestruction();
   _dirSelPopup->Release();
   _dirSelPopup = NULL;
}

void CAAxPDMPackSessionPanel::ActivateLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_list && _itemlist)
   {
      int nbselected = _list->GetSelectCount();
      if (nbselected==1)
      {
         int selectedline=0;
         _list->GetSelect(&selectedline,nbselected);
         if (_itemlist->Size()>=selectedline)
         {
            CATIxPDMItem_var item = (*_itemlist)[selectedline+1];
            if (!!item)
               _previewframe->UpdatePixelIconViewer(item);
         }
      }
   }
}
