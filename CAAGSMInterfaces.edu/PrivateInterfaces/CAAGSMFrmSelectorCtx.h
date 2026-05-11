#ifndef CAAGSMFrmSelectorCtx_H
#define CAAGSMFrmSelectorCtx_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMFrmSelectorCtx
//---------------------------------------------------------------------
// 
//  Dialog widget integrating  GSD contextual menu  activation 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

#include "CAAGsiFeaturesSplUI.h"

#include "CATISpecObject.h"
#include "CATListPV.h"
#include "CATListOfCATUnicodeString.h"

#include "CAAGSMFrmSelectorCtxMenuDef.h"

//Notif
#include  "CATDlgFrame.h"

class CATMMUIPanelStateCmd ;
class CATDlgLabel;
class CATDlgSelectorList;
class CATDlgPushButton;
class CATListValCATISpecObject_var;
class CATDlgPushItem;

class  ExportedByCAAGsiFeaturesSplUI CAAGSMFrmSelectorCtx : public CATDlgFrame
{
   DeclareResource (CAAGSMFrmSelectorCtx,CATDlgFrame)
   public:

      CAAGSMFrmSelectorCtx(CATMMUIPanelStateCmd  * iFatherCmd, CATDialog * iParent , const CATString& iDialogObjectName,const CAAGSMFrmSelectorCtxMenuDef  iAvailableCtxMenu);
      virtual ~CAAGSMFrmSelectorCtx ();
    
	  void SetContextualItems(CATListOfCATUnicodeString & Name, CATListOfCATUnicodeString & Icon, CATListOfCATUnicodeString & StartUp) ;
      void ItemContextualMenu(CATUnicodeString Label ,CATUnicodeString Icon_Name,CATUnicodeString StartUpName,int EditMode, CATDlgContextualMenu* & Ctx,int iInfo=0, CATUnicodeString strInfo ="");
	  void InitContextualItems(CATDlgContextualMenu* & Ctx);

	  void AnalyseNotifs(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData modifId);
	  void ContextualMenuActivation(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData data);
      void ContextualMenuSelection(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData data);
	 
	  CATDlgSelectorList* GetEditor();
	  CATDlgLabel       * GetLabel();

	  virtual void	      SetSelect  ();
	  virtual void		  ClearSelect();
	  CATBoolean IsSelected() ;

	  void SendNotif(CATCommand *c, CATNotification *n, CATCommandClientData d);
      CATNotification* GetSelectNotification();
	  void SetClearNotification(CATNotification * Notif );
 
      HRESULT Select();
      void SetFeature(const CATISpecObject_var ispSpecCurrent, CATBoolean ibCleanHSO = CATFalse) ; 



   private:


	   CATISpecObject              * _pCurrentFeature; 
	   CAAGSMFrmSelectorCtxMenuDef  _CtxMenu;

	   CATBoolean IsAnInfiniteFeature(CATISpecObject * Feat);

	   CATDlgFrame				* _Frame;
	   CATDlgLabel              * _label_dlg ;
	   CATDlgSelectorList       * _sel_selector;
	   CATDlgContextualMenu     * _contextual; 
	  

	   CATListOfCATUnicodeString  _Name , _Icon, _StartUp ; 
	   CATListPV				 _InfosList;

	   CATNotification           * _DlgClearSelection; 
	   CATMMUIPanelStateCmd      * _iFatherCmd ; 

};

#endif
