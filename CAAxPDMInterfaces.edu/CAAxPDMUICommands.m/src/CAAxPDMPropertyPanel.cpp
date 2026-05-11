// COPYRIGHT Dassault Systemes 2006
#include "CAAxPDMPropertyPanel.h"

//include System
#include "CATMsgCatalog.h"
#include "CATListOfCATUnicodeString.h"
//include ObjectModelerBase
#include "CATIAlias.h"
#include "CATIReporter.h"
//include Mathematics
#include "CATMathTransformation.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
//include Dialog
#include "CATDlgDialog.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgFrame.h"
#include "CATDlgPushButton.h"
#include "CATDlgEditor.h"
#include "CATDlgMultiList.h"
#include "CATDlgTabPage.h"
#include "CATDlgTabContainer.h"
#include "CATDlgContextualMenu.h"
#include "CATDlgPushItem.h"
//include CATxPDMInterfaces
#include "CATListOfCATIxPDMItem.h"
#include "CATIxPDMProductItem.h"
#include "CATIxPDMPartItem.h"
#include "CATxPDMProductServices.h"
//include CAAxPDMInterfaces.edu
#include "CAAxPDMItemPreviewFrame.h"
#include "CAAxPDMDeactivateImpactPanel.h"


//------------------------------------------------------------------------
CATImplementClass(CAAxPDMPropertyPanelNotification1,Implementation,CATNotification,CATNull);
CAAxPDMPropertyPanelNotification1::CAAxPDMPropertyPanelNotification1()
{}
CAAxPDMPropertyPanelNotification1::~CAAxPDMPropertyPanelNotification1()
{}
//------------------------------------------------------------------------
CATImplementClass(CAAxPDMPropertyPanelNotification2,Implementation,CATNotification,CATNull);
CAAxPDMPropertyPanelNotification2::CAAxPDMPropertyPanelNotification2()
{}
CAAxPDMPropertyPanelNotification2::~CAAxPDMPropertyPanelNotification2()
{}



//------------------------------------------------------------------------
CAAxPDMPropertyPanel::CAAxPDMPropertyPanel(CATDialog* parent)
:CATDlgDialog(parent,"Property",CATDlgWndOK|CATDlgWndCANCEL|CATDlgWndHELP|CATDlgWndTitleBarHelp)
{
   _notif1 = 0;
   _notif2 = 0;
   _lab_name=_lab_type=_lab_right=_lab_status=_lab_name2=_lab_version=NULL;
   _lab_path=_lab_path2=NULL;
   _list=_listchild=_listimport=_listcontext=NULL;
   _importedpage=NULL;
   _tabcont=NULL;
   BuildPanel();
}
//------------------------------------------------------------------------
CAAxPDMPropertyPanel::~CAAxPDMPropertyPanel()
{
   if (_notif2) _notif2->Release(); _notif2=NULL;
   if (_notif1) _notif1->Release(); _notif1=NULL;
   _lab_name=_lab_type=_lab_right=_lab_status=_lab_name2=_lab_version=NULL;
   _lab_path=_lab_path2=NULL;
   _list=_listchild=_listimport=_listcontext=NULL;
   _importedpage=NULL;
   _tabcont=NULL;
   _previewframe=NULL;
   _ChildrenList.RemoveAll();
   _ContextList.RemoveAll();
   _oInstanceChildrenList.RemoveAll();
}
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::BuildPanel()
{
   _notif1 = new CAAxPDMPropertyPanelNotification1();
   _notif2 = new CAAxPDMPropertyPanelNotification2();

   CATDlgFrame* frame0 = new CATDlgFrame(this,"frame0",CATDlgFraNoFrame);
   if (NULL==frame0) return;
   Attach4Sides(frame0);

   _tabcont = new CATDlgTabContainer(frame0,"Tabs");
   frame0->Attach4Sides(_tabcont);
   AddAnalyseNotificationCB(_tabcont,_tabcont->GetTabSelectNotification(),
	   (CATCommandMethod) &CAAxPDMPropertyPanel::SelectTabCB,NULL);

   CATDlgTabPage* page1 = new CATDlgTabPage(_tabcont,"General");
   CATDlgFrame* frame1 = new CATDlgFrame(page1,"frame1",CATDlgFraNoFrame|CATDlgGridLayout);
   page1->Attach4Sides(frame1);

   CATDlgLabel* lab1 = new CATDlgLabel(frame1,"lab1");
   CATDlgLabel* lab101 = new CATDlgLabel(frame1,"lab101"); lab101->SetTitle("  ");
   CATDlgLabel* lab2 = new CATDlgLabel(frame1,"lab2");
   _lab_name = new CATDlgLabel(frame1,"labname");
   CATDlgLabel* lab3 = new CATDlgLabel(frame1,"lab3");
   _lab_type = new CATDlgLabel(frame1,"labtype");
   CATDlgLabel* lab4 = new CATDlgLabel(frame1,"lab4");
   _lab_path = new CATDlgEditor(frame1,"labpath",CATDlgEdtReadOnly);
   _lab_path->SetVisibleTextWidth(20);
   CATDlgLabel* lab401 = new CATDlgLabel(frame1,"lab401");
   _previewframe = new CAAxPDMItemPreviewFrame(frame1,"preview",CATDlgFraNoFrame);
   
   CATDlgLabel* lab5 = new CATDlgLabel(frame1,"lab5");
   CATDlgLabel* lab6 = new CATDlgLabel(frame1,"lab6");
   _lab_right = new CATDlgLabel(frame1,"labright");
   CATDlgLabel* lab7 = new CATDlgLabel(frame1,"lab7");
   _lab_status = new CATDlgLabel(frame1,"labstatus");

   CATDlgLabel* lab801 = new CATDlgLabel(frame1,"lab81"); lab801->SetTitle("    ");
   CATDlgLabel* lab8 = new CATDlgLabel(frame1,"lab8");
   CATDlgLabel* lab9 = new CATDlgLabel(frame1,"lab9");
   _lab_name2 = new CATDlgLabel(frame1,"labname2");
   CATDlgLabel* lab10 = new CATDlgLabel(frame1,"lab10");
   _lab_version = new CATDlgLabel(frame1,"labversion");
   CATDlgLabel* lab11 = new CATDlgLabel(frame1,"lab11");
   _lab_path2 = new CATDlgEditor(frame1,"labpath2",CATDlgEdtReadOnly);
   _lab_path2->SetVisibleTextWidth(20);
   
   lab1 ->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
   lab101->SetGridConstraints(0,1,1,1,CATGRID_LEFT);
   lab2 ->SetGridConstraints(0,2,1,1,CATGRID_LEFT);
   lab3 ->SetGridConstraints(1,2,1,1,CATGRID_LEFT);
   lab4 ->SetGridConstraints(2,2,1,1,CATGRID_LEFT);
   lab401->SetGridConstraints(3,2,1,1,CATGRID_LEFT);
   lab5 ->SetGridConstraints(5,0,1,1,CATGRID_LEFT);
   lab6 ->SetGridConstraints(5,2,1,1,CATGRID_LEFT);
   lab7 ->SetGridConstraints(6,2,1,1,CATGRID_LEFT);
   lab801->SetGridConstraints(7,2,1,1,CATGRID_LEFT);
   lab8 ->SetGridConstraints(8,0,1,1,CATGRID_LEFT);
   lab9 ->SetGridConstraints(8,2,1,1,CATGRID_LEFT);
   lab10->SetGridConstraints(9,2,1,1,CATGRID_LEFT);
   lab11->SetGridConstraints(10,2,1,1,CATGRID_LEFT);
   _lab_name    ->SetGridConstraints(0,3,1,1,CATGRID_LEFT);
   _lab_type    ->SetGridConstraints(1,3,1,1,CATGRID_LEFT);
   _lab_path    ->SetGridConstraints(2,3,1,1,CATGRID_LEFT | CATGRID_RIGHT);
   _previewframe->SetGridConstraints(3,3,1,1,CATGRID_LEFT);
   _lab_right   ->SetGridConstraints(5,3,1,1,CATGRID_LEFT);
   _lab_status  ->SetGridConstraints(6,3,1,1,CATGRID_LEFT);
   _lab_name2   ->SetGridConstraints(8,3,1,1,CATGRID_LEFT);
   _lab_version ->SetGridConstraints(9,3,1,1,CATGRID_LEFT);
   _lab_path2   ->SetGridConstraints(10,3,1,1,CATGRID_LEFT | CATGRID_RIGHT);
   frame1->SetGridColumnResizable(3);

   CATDlgTabPage* page2 = new CATDlgTabPage(_tabcont,"Properties");
   
   CATDlgFrame* frame2 = new CATDlgFrame(page2,"frame2",CATDlgFraNoFrame);
   _list = new CATDlgMultiList(frame2,"List1");
   if (NULL==_list) return;
   CATUnicodeString aTitle;
   CATUnicodeString multiListTitles[2]; 
   multiListTitles[0] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListTitles0",NULL,0,"Name");
   multiListTitles[1] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListTitles1",NULL,0,"Value");
   _list->SetColumnTitles(2, multiListTitles);
   _list->SetColumnVisibility(0, CATDlgShow);
   _list->SetColumnVisibility(1, CATDlgShow);
   _list->SetColumnTextWidth(0,20);
   _list->SetColumnTextWidth(1,20);
   _list->SetVisibleTextWidth(50);
   _list->SetColumnEditable(1,TRUE);
   frame2->Attach4Sides(_list);
   page2->Attach4Sides(frame2);

   CATDlgTabPage* page3 = new CATDlgTabPage(_tabcont,"Child");
   
   CATDlgFrame* frame3 = new CATDlgFrame(page3,"frame3",CATDlgFraNoFrame);
   _listchild = new CATDlgMultiList(frame3,"List3");
   if (NULL==_listchild) return;
   AddAnalyseNotificationCB(_listchild,_listchild->GetListActivateNotification(),(CATCommandMethod) &CAAxPDMPropertyPanel::ActivateChildCB,NULL);
   CATUnicodeString multiListTitles2[3]; 
   multiListTitles2[0] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListChildTitles0",NULL,0,"Name");
   multiListTitles2[1] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListChildTitles1",NULL,0,"Instance");
   multiListTitles2[2] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListChildTitles2",NULL,0,"Path");
   _listchild->SetColumnTitles(3, multiListTitles2);
   _listchild->SetColumnVisibility(0, CATDlgShow);
   _listchild->SetColumnVisibility(1, CATDlgShow);
   _listchild->SetColumnVisibility(2, CATDlgShow);
   _listchild->SetColumnTextWidth(0,12);
   _listchild->SetColumnTextWidth(1,10);
   _listchild->SetColumnTextWidth(2,23);
   _listchild->SetVisibleTextWidth(50);
   frame3->Attach4Sides(_listchild);
   page3->Attach4Sides(frame3);

   //CATDlgContextualMenu* contextmenu = _listchild->GetContextualMenu();
   CATDlgContextualMenu* contextmenu = new CATDlgContextualMenu(_listchild,"contextmenu");
   if (contextmenu)
   {
      CATDlgPushItem* item1 = new CATDlgPushItem(contextmenu,"Activate");
      CATDlgPushItem* item2 = new CATDlgPushItem(contextmenu,"Deactivate");
      AddAnalyseNotificationCB(item1,item1->GetMenuIActivateNotification(),(CATCommandMethod) &CAAxPDMPropertyPanel::ActivateProductChildCB ,NULL);
      AddAnalyseNotificationCB(item2,item2->GetMenuIActivateNotification(),(CATCommandMethod) &CAAxPDMPropertyPanel::DeactivateProductChildCB ,NULL);
   }


   _importedpage = new CATDlgTabPage(_tabcont,"Import");
   
   CATDlgFrame* frame4 = new CATDlgFrame(_importedpage,"frame4",CATDlgFraNoFrame);
   CATDlgLabel* label401 = new CATDlgLabel(frame4,"labImported");
   _listimport = new CATDlgMultiList(frame4,"List4");
   if (NULL==_listimport) return;
   AddAnalyseNotificationCB(_listimport,_listimport->GetListActivateNotification(),(CATCommandMethod) &CAAxPDMPropertyPanel::ActivateImportCB,NULL);
   CATUnicodeString multiListTitles4[2]; 
   multiListTitles4[0] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListChildTitles0",NULL,0,"Name");
   multiListTitles4[1] = CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","multiListChildTitles2",NULL,0,"Path");
   _listimport->SetColumnTitles(2, multiListTitles4);
   _listimport->SetColumnVisibility(0, CATDlgShow);
   _listimport->SetColumnVisibility(1, CATDlgShow);
   _listimport->SetColumnTextWidth(0,12);
   _listimport->SetColumnTextWidth(1,28);
   _listimport->SetVisibleTextWidth(50);
   _listimport->SetVisibleLineCount(4);
   CATDlgLabel* label402 = new CATDlgLabel(frame4,"labContext");
   _listcontext = new CATDlgMultiList(frame4,"List5");
   if (NULL==_listcontext) return;
   AddAnalyseNotificationCB(_listcontext,_listcontext->GetListActivateNotification(),(CATCommandMethod) &CAAxPDMPropertyPanel::ActivateContextCB,NULL);
   _listcontext->SetColumnTitles(2, multiListTitles4);
   _listcontext->SetColumnVisibility(0, CATDlgShow);
   _listcontext->SetColumnVisibility(1, CATDlgShow);
   _listcontext->SetColumnTextWidth(0,12);
   _listcontext->SetColumnTextWidth(1,28);
   _listcontext->SetVisibleTextWidth(50);
   _listcontext->SetVisibleLineCount(4);
   frame4->SetVerticalAttachment(0,CATDlgTopOrLeft,label401,_listimport,label402,_listcontext,NULL);
   frame4->SetVerticalAttachment(1,CATDlgRightOrBottomRelative,label401,_listimport,label402,_listcontext,NULL);
   frame4->SetHorizontalAttachment(0,CATDlgTopOrLeft,label401,NULL);
   frame4->SetHorizontalAttachment(1,CATDlgTopOrLeft,_listimport,NULL);
   frame4->SetHorizontalAttachment(2,CATDlgRightOrBottomRelative,_listimport,NULL);
   frame4->SetHorizontalAttachment(3,CATDlgTopOrLeft,label402,NULL);
   frame4->SetHorizontalAttachment(4,CATDlgTopOrLeft,_listcontext,NULL);
   frame4->SetHorizontalAttachment(5,CATDlgRightOrBottomRelative,_listcontext,NULL);
   _importedpage->Attach4Sides(frame4);

   SetOKSensitivity(CATDlgDisable);
   SetOKTitle(CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","OK.Title",NULL,0,"Previous"));
   SetCANCELTitle(CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","CANCEL.Title",NULL,0,"Close"));
   AddAnalyseNotificationCB(this,this->GetDiaOKNotification(),
	   (CATCommandMethod) &CAAxPDMPropertyPanel::SelectPreviousCB,NULL);
}


CATUnicodeString RetrieveNameAndPathFromPath(CATUnicodeString& iPath,CATUnicodeString& oPath)
{
   CATUnicodeString rc;
   int Length = -1;
   int idxBackSlash = iPath.SearchSubString("\\", 0, CATUnicodeString::CATSearchModeBackward);
   int idxSlash = iPath.SearchSubString("/", 0, CATUnicodeString::CATSearchModeBackward);
   if (idxBackSlash!=-1)
      Length=idxBackSlash;
   if (idxSlash!=-1 && idxSlash>Length)
      Length=idxSlash;
   if (Length != -1)
   {
      int NbLength = iPath.GetLengthInChar();
      rc = iPath.SubString(Length + 1, NbLength - (Length+1));
      oPath = iPath.SubString(0,Length);
   }
   else
      rc=iPath;
   return rc;
}

//------------------------------------------------------------------------
//   Update Panel
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::SetItem(CATIxPDMItem_var& item,int BackToFirstPage)
{
   //Nothing to update if item is alreadt selected
   if (!!item && item==_CurrentItem)
      return;

   if (!!_CurrentItem)
      _PreviousItems.Append(_CurrentItem);
   if (_PreviousItems.Size())
      SetOKSensitivity(CATDlgEnable);
   else
      SetOKSensitivity(CATDlgDisable);
   
   _CurrentItem = item;
   if (_lab_name && _lab_type && _lab_path && _lab_right && _lab_status && _lab_name2 && _lab_version && _lab_path2 && _list
      && _listimport && _importedpage && _tabcont && _listcontext)
   {
      if (BackToFirstPage)
         _tabcont->SetSelectedPage(0,1);
      _lab_name->SetTitle("");
      _lab_type->SetTitle("");
      _lab_path->SetText("");
      _lab_right->SetTitle("");
      _lab_status->SetTitle("");
      _lab_name2->SetTitle("");
      _lab_version->SetTitle("");
      _lab_path2->SetText("");
      _list->ClearLine();      
      _listchild->ClearLine();      
      _listimport->ClearLine();
      _listcontext->ClearLine();
      _ChildrenList.RemoveAll();
      _ContextList.RemoveAll();
      _ImportList.RemoveAll();
      _oInstanceChildrenList.RemoveAll();
      _importedpage->SetSensitivity(CATDlgDisable);
      if (!!item)
      {
         //---------------------------------------------------------------
         CATUnicodeString type;
         if (SUCCEEDED(item->GetItemType(type)))
            _lab_type->SetTitle(type);
         CATUnicodeString fullpath;
         if (SUCCEEDED(item->GetDocFileName(fullpath)))
         {
            CATUnicodeString path;
            CATUnicodeString name = RetrieveNameAndPathFromPath(fullpath,path);
            _lab_name->SetTitle(name);
            _lab_path->SetText(path);
         }
         
         //---------------------------------------------------------------
         CATUnicodeString status,savepath;
         CATBoolean tobesaved=FALSE;
         item->NeedToBeSaved(tobesaved);
         if (item->GetLastSavePath(savepath)==S_FALSE)
            status=CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","StatusNew",NULL,0,"N");
         else if (tobesaved)
            status=CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","StatusModified",NULL,0,"M");
         else
            status=CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","StatusOpen",NULL,0,"O");
         _lab_status->SetTitle(status);

         CATBoolean readonly=FALSE;
         if (SUCCEEDED(item->GetReadOnlyStatus(readonly)))
         {
            if (readonly)
               status=CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","ReadOnly",NULL,0,"RO");
            else
               status=CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","ReadWrite",NULL,0,"RW");
            _lab_right->SetTitle(status);
         }
         
         //---------------------------------------------------------------
         if (item->GetLastSavePath(fullpath)==S_OK)
         {
            CATUnicodeString path;
            CATUnicodeString name = RetrieveNameAndPathFromPath(fullpath,path);
            _lab_name2->SetTitle(name);
            _lab_path2->SetText(path);
         }
         CATUnicodeString version;
         if (item->GetLastSaveVersion(version)==S_OK)
         {
            version.ReplaceSubString("<Version>","V");
            version.ReplaceSubString("</Version>"," ");
            version.ReplaceSubString("<Release>","R");
            version.ReplaceSubString("</Release>"," ");
            version.ReplaceSubString("<ServicePack>","SP");
            version.ReplaceSubString("</ServicePack>"," ");
            version.ReplaceSubString("<HotFix>","HF");
            version.ReplaceSubString("</HotFix>","");
            _lab_version->SetTitle(version);
         }
         //---------------------------------------------------------------
         CATListOfCATUnicodeString oListPropertyNames;
         if (SUCCEEDED(item->GetPropertyNames(oListPropertyNames)))
         {
            int size = oListPropertyNames.Size();
            CATUnicodeString propname,propvalue;
            for (int i=1;i<=size;i++)
            {
               propname = oListPropertyNames[i];
               if (SUCCEEDED(item->GetProperty(propname,propvalue)))
               {
                  _list->SetColumnItem(0,propname);
                  _list->SetColumnItem(1,propvalue);
               }
            }
         }
         //---------------------------------------------------------------
         CATIxPDMProductItem_var product = item;
         CATLISTV(CATBaseUnknown_var) oInstanceChildrenList;
         CATLISTP(CATMathTransformation) oChildrenLocationList;
         HRESULT rc=E_FAIL;
         if (!!product)
            rc = product->GetChildrenItems(_ChildrenList,_oInstanceChildrenList);
         else
            rc = item->GetChildrenItems(_ChildrenList,oChildrenLocationList);
         if (SUCCEEDED(rc))
         {
            int size = _ChildrenList.Size();
            for (int i=1;i<=size;i++)
            {
               CATUnicodeString childname,childpath,instancename;
               CATIxPDMItem_var child = _ChildrenList[i];
               if (!!item)
               {
                  CATUnicodeString fullpath;
                  if (SUCCEEDED(child->GetDocFileName(fullpath)))
                     childname = RetrieveNameAndPathFromPath(fullpath,childpath);
               }
               if (_oInstanceChildrenList.Size()>=i)
               {
                  CATIAlias_var instance = _oInstanceChildrenList[i];
                  if (!!instance)
                     instancename = instance->GetAlias();
               }
               _listchild->SetColumnItem(0,childname);
               _listchild->SetColumnItem(1,instancename);
               _listchild->SetColumnItem(2,childpath);
            }
         }
         //Clean Memory
         int nbele = oChildrenLocationList.Size();
         if ( nbele > 0 )
         {
            for (int i=1; i<=nbele; ++i)
            {
               CATMathTransformation *p = oChildrenLocationList[i];
               if ( NULL != p )
               {delete p;p = NULL;}
            }
            oChildrenLocationList.RemoveAll();
         }
         //---------------------------------------------------------------
         if (_previewframe)
            _previewframe->UpdatePixelIconViewer(item);
         //---------------------------------------------------------------
         CATIxPDMPartItem_var part = item;
         if (!!part)
            _importedpage->SetSensitivity(CATDlgEnable);
      }
   }
}

//------------------------------------------------------------------------
//   Update content of tab with Import Links
// This tab is updated asynchronously to avoid useless data loading if
// user want only to display attributes.
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::SelectTabCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (iCmd && _listimport)
   {
      CATDlgTabContainer* tabcont = (CATDlgTabContainer*)iCmd;
      if (tabcont && tabcont->GetSelectedPagePtr()==_importedpage)
      {
         //---------------------------------------------------------------
         CATIxPDMPartItem_var part = _CurrentItem;
         if (!!part)
         {
            _listimport->ClearLine();
            _ImportList.RemoveAll();
            _listcontext->ClearLine();
            _ContextList.RemoveAll();
            CATBoolean oHasExternalLinks=FALSE;
            if (SUCCEEDED(part->HasExternalLinks(oHasExternalLinks)) && oHasExternalLinks)
            {
               //Display Content
               HRESULT rc = part->GetImportedItems(_ImportList);
               if (SUCCEEDED(rc))
               {
                  int size = _ImportList.Size();
                  for (int i=1;i<=size;i++)
                  {
                     CATUnicodeString childname,childpath;
                     CATIxPDMItem_var child = _ImportList[i];
                     if (!!child)
                     {
                        CATUnicodeString fullpath;
                        if (SUCCEEDED(child->GetDocFileName(fullpath)))
                           childname = RetrieveNameAndPathFromPath(fullpath,childpath);
                     }
                     _listimport->SetColumnItem(0,childname);
                     _listimport->SetColumnItem(1,childpath);
                  }
               }
               else
               {
                  CATError * pError = CATError::CATGetLastError(rc);
                  if ( NULL != pError )
                     _listimport->SetColumnItem(1,pError->GetNLSMessage());
                  else
                     _listimport->SetColumnItem(1,"Impossible to retrieve pointed items");
                  CATError::CATCleanLastError();
               }
               HRESULT rc2 = part->GetContextItems(_ContextList);
               if (SUCCEEDED(rc2))
               {
                  int size = _ContextList.Size();
                  for (int i=1;i<=size;i++)
                  {
                     CATUnicodeString childname,childpath;
                     CATIxPDMItem_var child = _ContextList[i];
                     if (!!child)
                     {
                        CATUnicodeString fullpath;
                        if (SUCCEEDED(child->GetDocFileName(fullpath)))
                           childname = RetrieveNameAndPathFromPath(fullpath,childpath);
                     }
                     _listcontext->SetColumnItem(0,childname);
                     _listcontext->SetColumnItem(1,childpath);
                  }
               }
               else
               {
                  CATError * pError = CATError::CATGetLastError(rc2);
                  if ( NULL != pError )
                     _listcontext->SetColumnItem(1,pError->GetNLSMessage());
                  else
                     _listcontext->SetColumnItem(1,"Impossible to load context");
                  CATError::CATCleanLastError();
               }
            }
            else
            {
               _listimport->SetColumnItem(1,"Impossible check if there is relational links.");
               _listcontext->SetColumnItem(1,"Impossible check if there is relational links.");
            }
         }
      }
   }
}

//------------------------------------------------------------------------
//   Change current item from Children page
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::ActivateChildCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_listchild)
   {
      int iselect=0;
      _listchild->GetSelect(&iselect,1);
      iselect++;
      CATIxPDMItem_var child;
	  // ecn : on verifie tout d'abord si, sous le composant, on a pas une rep de type model V4
	  int IsAModel=0;
	  if (iselect>0 && iselect<=_ChildrenList.Size())
	  {
		  child = _ChildrenList[iselect];
		  CATUnicodeString type;
		  if (!!child && SUCCEEDED(child->GetItemType(type)) && type=="model" )
		  {
			  // On a une Rep de type .model : on va prendre le child dans _ChildrenList
			  IsAModel=1;
		  }
		  else
		  {
			  child=NULL;
		  }
	  }

      if (iselect>0 && iselect<=_oInstanceChildrenList.Size()&& 0==IsAModel)
      {
         CATBaseUnknown_var iInstanceChildToLoad = _oInstanceChildrenList[iselect];
         CATIxPDMProductItem_var product = _CurrentItem;
         if (!!product)
            product->LoadChildForPropertiesEdition(iInstanceChildToLoad,child);
      }
      if (!child && iselect>0 && iselect<=_ChildrenList.Size())
         child = _ChildrenList[iselect];
      if (!!child)
         SetItem(child,1);
   }
}

//------------------------------------------------------------------------
//   Activate a Product Child
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::DeactivateProductChildCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   SendNotification(GetFather(),_notif1);
}

void CAAxPDMPropertyPanel::ActivateProductChildCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   SendNotification(GetFather(),_notif2);
}

void CAAxPDMPropertyPanel::ActivateDeactivateProduct(CATBoolean mode)
{
   if (_listchild)
   {
      int iselect=0;
      _listchild->GetSelect(&iselect,1);
      iselect++;
      CATIxPDMItem_var child;
      if (iselect>0 && iselect<=_oInstanceChildrenList.Size())
      {
         CATBaseUnknown_var iInstanceChildToLoad = _oInstanceChildrenList[iselect];
         CATIReporter* oReporter=NULL;
         CATListValCATIxPDMItem_var* oItemsWithError=NULL;
         HRESULT rc = CATxPDMProductServices::SetProductInstanceActivation(iInstanceChildToLoad,mode,oItemsWithError,oReporter);
         if (SUCCEEDED(rc) && oReporter)
         {
            CAAxPDMDeactivateImpactPanel* panel = new CAAxPDMDeactivateImpactPanel(this);
            panel->SetVisibility(CATDlgShow);
            const CATLISTP(CATIReporterInfo) listerror = oReporter->GetListReporterInfo();
            CATListOfCATUnicodeString list1,list2,list3;
            for (int i=1;i<=listerror.Size();i++)
            {
               CATIReporterInfo* info = listerror[i];
               if (info)
               {
                  CATUnicodeString oStr;
                  info->GetAssociatedString(oStr);
                  CATError* error=NULL;
                  info->GetError(error);
                  if (error)
                  {
                     list1.Append(oStr);
                     int ier = error->GetId();
                     CATUnicodeString err;
                     err.BuildFromNum(ier);
                     list2.Append(err);
                     list3.Append(error->GetNLSMessage());
                     error->Release(); error=NULL;
                  }
               }
            }
            panel->SetListInfo(list1,list2,list3,oItemsWithError);
         }
         if (oReporter) oReporter->Release(); oReporter=NULL;
         //No delete, lifecycle is managed by panel
         //if (oItemsWithError) delete oItemsWithError; oItemsWithError=NULL;
      }
   }
}

//------------------------------------------------------------------------
//   Change current item from Import page
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::ActivateImportCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_listimport)
   {
      int iselect=0;
      _listimport->GetSelect(&iselect,1);
      iselect++;
      CATIxPDMItem_var child;
      if (iselect>0 && iselect<=_ImportList.Size())
         child = _ImportList[iselect];
      if (!!child)
         SetItem(child,1);
   }
}

//------------------------------------------------------------------------
//   Change current item from Import page
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::ActivateContextCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_listcontext)
   {
      int iselect=0;
      _listcontext->GetSelect(&iselect,1);
      iselect++;
      CATIxPDMItem_var child;
      if (iselect>0 && iselect<=_ContextList.Size())
         child = _ContextList[iselect];
      if (!!child)
         SetItem(child,1);
   }
}

//------------------------------------------------------------------------
//   Go to previous item
//------------------------------------------------------------------------
void CAAxPDMPropertyPanel::SelectPreviousCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData)
{
   if (_PreviousItems.Size())
   {
      CATIxPDMItem_var previousitem = _PreviousItems[_PreviousItems.Size()];
      if (!!previousitem)
      {
         _PreviousItems.RemovePosition(_PreviousItems.Size());
         _CurrentItem = NULL_var;
         SetItem(previousitem);
      }
   }
}

