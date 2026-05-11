// -------------------------------------------------------------------
// Copyright Dassault Systemes 2006
//---------------------------------------------------------------------
#include "CAAxPDMDeactivateImpactPanel.h"

//include System
#include "CATMsgCatalog.h"
#include "CATListOfCATUnicodeString.h"
#include "CATSession.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
//include InteractiveInterfaces
#include "CATIIniInteractiveSession.h"
//include Dialog
#include "CATDlgDialog.h"
#include "CATDlgLabel.h"
#include "CATDlgMultiList.h"
//include CATxPDMInterfaces
#include "CATIxPDMItem.h"
#include "CATListOfCATIxPDMItem.h"


CATUnicodeString SplitNameFromPath(CATUnicodeString& iPath,CATUnicodeString& Dir);


//------------------------------------------------------------------------
CAAxPDMDeactivateImpactPanel::CAAxPDMDeactivateImpactPanel(CATDialog* parent)
:CATDlgDialog(parent,"CheckSession",CATDlgWndBtnClose|CATDlgWndHELP|CATDlgWndTitleBarHelp)
{
   BuildPanel();
   _oItemsWithError=NULL;
}
//------------------------------------------------------------------------
CAAxPDMDeactivateImpactPanel::~CAAxPDMDeactivateImpactPanel()
{
   _list=NULL;
   _errorhelp=NULL;
   if (_oItemsWithError) delete _oItemsWithError; _oItemsWithError=NULL;
}

//------------------------------------------------------------------------
void CAAxPDMDeactivateImpactPanel::BuildPanel()
{
   _list = new CATDlgMultiList(this,"List1");
   if (NULL==_list) return;
   CATUnicodeString aTitle;
   CATUnicodeString multiListTitles[6]; 
   multiListTitles[0] = CATMsgCatalog::BuildMessage("CAAxPDMDeactivateImpactPanel","multiListTitles0",NULL,0,"Item");
   multiListTitles[1] = CATMsgCatalog::BuildMessage("CAAxPDMDeactivateImpactPanel","multiListTitles1",NULL,0,"Type");
   multiListTitles[2] = CATMsgCatalog::BuildMessage("CAAxPDMDeactivateImpactPanel","multiListTitles2",NULL,0,"Error");
   multiListTitles[3] = CATMsgCatalog::BuildMessage("CAAxPDMDeactivateImpactPanel","multiListTitles3",NULL,0,"Object");
   multiListTitles[4] = CATMsgCatalog::BuildMessage("CAAxPDMDeactivateImpactPanel","multiListTitles4",NULL,0,"Description");
   multiListTitles[5] = CATMsgCatalog::BuildMessage("CAAxPDMDeactivateImpactPanel","multiListTitles5",NULL,0,"Path");
   _list->SetColumnTitles(6, multiListTitles);
   _list->SetColumnVisibility(0, CATDlgShow);
   _list->SetColumnVisibility(1, CATDlgShow);
   _list->SetColumnVisibility(2, CATDlgShow);
   _list->SetColumnVisibility(3, CATDlgShow);
   _list->SetColumnVisibility(4, CATDlgShow);
   _list->SetColumnVisibility(5, CATDlgShow);
   _list->SetColumnTextWidth(0,6);
   _list->SetColumnTextWidth(1,4);
   _list->SetColumnTextWidth(2,3);
   _list->SetColumnTextWidth(3,8);
   _list->SetColumnTextWidth(4,35);
   _list->SetColumnTextWidth(5,15);
   _list->SetVisibleTextWidth(80);
   _errorhelp = new CATDlgLabel(this,"errorhelp");
   _errorhelp->SetTitle("");

   AddAnalyseNotificationCB (_list,_list->GetListSelectNotification(),
	   (CATCommandMethod) &CAAxPDMDeactivateImpactPanel::SelectLineCB,NULL);
   AddAnalyseNotificationCB (_list,_list->GetListActivateNotification(),
	   (CATCommandMethod) &CAAxPDMDeactivateImpactPanel::ActivateLineCB,NULL);
   AddAnalyseNotificationCB (this,this->GetWindCloseNotification(),
	   (CATCommandMethod) &CAAxPDMDeactivateImpactPanel::Quit,NULL);
   AddAnalyseNotificationCB (this,this->GetDiaCLOSENotification(),
	   (CATCommandMethod) &CAAxPDMDeactivateImpactPanel::Quit,NULL);
   

   SetVerticalAttachment(0,CATDlgTopOrLeft,_list,_errorhelp,NULL);
   SetVerticalAttachment(1,CATDlgRightOrBottomRelative,_list,_errorhelp,NULL);
   SetHorizontalAttachment(1,CATDlgTopOrLeft,_list,NULL);
   SetHorizontalAttachment(2,CATDlgRightOrBottomRelative,_list,NULL);
   SetHorizontalAttachment(3,CATDlgTopOrLeft,_errorhelp,NULL);
}

//------------------------------------------------------------------------
//   Mise a jour du panel
//------------------------------------------------------------------------
void CAAxPDMDeactivateImpactPanel::SetListInfo(const CATListOfCATUnicodeString& ListName,const CATListOfCATUnicodeString& ListError,
                                           const CATListOfCATUnicodeString& ListStatus,
                                           CATListValCATIxPDMItem_var* oItemsWithError)
{
   if (_list && _errorhelp)
   {
      _list->ClearLine();
      _errorhelp->SetTitle("");
      if (_oItemsWithError) delete _oItemsWithError; _oItemsWithError=NULL;
      _oItemsWithError = oItemsWithError;
      int iSize=ListName.Size();
      for (int kk=1;kk<=iSize;kk++)
      {
         _list->SetColumnItem(3,ListName[kk]);
         if (ListError.Size()>=kk)
            _list->SetColumnItem(2,ListError[kk]);
         else
            _list->SetColumnItem(2,"Unknown");
         if (ListStatus.Size()>=kk)
            _list->SetColumnItem(4,ListStatus[kk]);
         else
            _list->SetColumnItem(4,"Unknown");
         if (_oItemsWithError && _oItemsWithError->Size()>=kk)
         {
            CATIxPDMItem_var item = (*_oItemsWithError)[kk];
            if (!!item)
            {
               CATUnicodeString oFileType;
               item->GetItemType(oFileType);
               _list->SetColumnItem(1,oFileType);
               CATUnicodeString oDocFilePathName,oDir;
	            item->GetDocFileName(oDocFilePathName);
               CATUnicodeString Name = SplitNameFromPath(oDocFilePathName,oDir);
               _list->SetColumnItem(0,Name);
               _list->SetColumnItem(5,oDir);
            }
         }
      }
   }
}

void CAAxPDMDeactivateImpactPanel::Quit (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   RequestDelayedDestruction();
}
#include "CATxPDMSessionServices.h"
void CAAxPDMDeactivateImpactPanel::SelectLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_list && _errorhelp)
   {
      int nbselected = _list->GetSelectCount();
      if (nbselected==1)
      {
         int selectedline=0;
         _list->GetSelect(&selectedline,nbselected);
         //Display full message
         CATUnicodeString texte;
         _list->GetColumnItem(4,texte,selectedline);
         _errorhelp->SetTitle(texte);

      }
   }
}

void CAAxPDMDeactivateImpactPanel::ActivateLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_list && _oItemsWithError)
   {
      int nbselected = _list->GetSelectCount();
      if (nbselected==1)
      {
         int selectedline=0;
         _list->GetSelect(&selectedline,nbselected);
         if (_oItemsWithError->Size()>=selectedline)
         {
            CATIxPDMItem_var item = (*_oItemsWithError)[selectedline+1];
            if (!!item)
            {
               CATUnicodeString oDocFilePathName;
	            item->GetDocFileName(oDocFilePathName);
               CATSession * ses = CATSession::GetPtrSession();
               CATIIniInteractiveSession * ises = NULL;
               if (ses && SUCCEEDED(ses->QueryInterface(IID_CATIIniInteractiveSession, (void **) &ises)) && ses)
               {
                  CATIEditor* ed = NULL;
                  HRESULT  bil = ises->Open(oDocFilePathName,FALSE, &ed);
                  ises->Release(); ises=NULL;
               }
            }
         }
      }
   }
}
