/* -*-c++-*- */
#ifndef CAAxPDMPropertyPanel_H 
#define CAAxPDMPropertyPanel_H 
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATDlgDialog.h"
#include "CATListOfCATString.h"
#include "CATIxPDMItem.h"
#include "CATListOfCATIxPDMItem.h"

class CATDlgLabel;
class CATDlgMultiList;
class CATDlgEditor;
class CATDlgTabPage;
class CATDlgTabContainer;
class CAAxPDMItemPreviewFrame;

//========================================================================
class CAAxPDMPropertyPanelNotification1: public CATNotification
{
public:
	CATDeclareClass;
   CAAxPDMPropertyPanelNotification1();
   virtual ~CAAxPDMPropertyPanelNotification1();
};

//========================================================================
class CAAxPDMPropertyPanelNotification2: public CATNotification
{
public:
	CATDeclareClass;
   CAAxPDMPropertyPanelNotification2();
   virtual ~CAAxPDMPropertyPanelNotification2();
};


//========================================================================
// Edition Panel
//========================================================================
class CAAxPDMPropertyPanel : public CATDlgDialog
{
   DeclareResource(CAAxPDMPropertyPanel,CATDlgDialog)
public:
   CAAxPDMPropertyPanel(CATDialog*);
   ~CAAxPDMPropertyPanel();
   void BuildPanel();


   void SetItem(CATIxPDMItem_var& item,int BackToFirstPage=0);
   void ActivateDeactivateProduct(CATBoolean mode);

protected:
   void ActivateChildCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void ActivateImportCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void ActivateContextCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void SelectTabCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void SelectPreviousCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);

   void ActivateProductChildCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void DeactivateProductChildCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);

private:
   CATDlgLabel*       _lab_name,*_lab_type;
   CATDlgLabel*       _lab_right,*_lab_status;
   CATDlgLabel*       _lab_name2,*_lab_version;
   CATDlgEditor*      _lab_path,*_lab_path2;

   CATDlgTabContainer* _tabcont;
   CATDlgTabPage*      _importedpage;
   
   CATDlgMultiList*   _list,*_listchild,*_listimport,*_listcontext;

   CAAxPDMItemPreviewFrame* _previewframe;

   CATIxPDMItem_var              _CurrentItem;
   CATListValCATIxPDMItem_var    _ChildrenList;
   CATListValCATIxPDMItem_var    _ContextList;
   CATLISTV(CATBaseUnknown_var)  _oInstanceChildrenList;

   CATListValCATIxPDMItem_var    _ImportList;

   CATListValCATIxPDMItem_var    _PreviousItems;

   //notifs
   CAAxPDMPropertyPanelNotification1*   _notif1;
   CAAxPDMPropertyPanelNotification2*   _notif2;
};

#endif
