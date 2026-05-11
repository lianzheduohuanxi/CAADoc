// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMPropertyCmd.h"
#include "CAAxPDMPropertyPanel.h"

//include System
#include "CATListOfCATUnicodeString.h"
//include ApplicationFrame
#include "CATFrmEditor.h"
#include "CATHSO.h"
#include "CATApplicationFrame.h"
#include "CATDlgNotify.h"
//include DialogEngine
#include "CATDialogState.h"
#include "CATDialogTransition.h"
#include "CATPathElementAgent.h"
//include VisualizationBase
#include "CATPathElement.h"
//include ObjectModelerBase
#include "CATILinkableObject.h"
#include "CATDocument.h"
//include ProductStructure
#include "CATIProduct.h"
//include CATxPDMInterfaces
#include "CATIxPDMItem.h"
#include "CATIxPDMSession.h"
#include "CATxPDMSessionServices.h"


#include "CATCreateExternalObject.h"
CATCreateClass(CAAxPDMPropertyCmd);


CATImplementClass(CAAxPDMPropertyCmd, Implementation, CATStateCommand,CATNull);

//-----------------------------------------------------------------------------
// RetrieveNameFromPath
//-----------------------------------------------------------------------------
CATUnicodeString RetrieveNameFromPath(CATUnicodeString& iPath);


//========================================================================
// Commande
//========================================================================

//------------------------------------------------------------------------
//	Constructeur/Destructeur
//------------------------------------------------------------------------
CAAxPDMPropertyCmd::CAAxPDMPropertyCmd():CATStateCommand("DisplayProperty"),
_ElementAcq(NULL),_PanelCANCELAcq(NULL),_Panel(NULL),_PanelDeactivateInstance(NULL),_PanelActivateInstance(NULL)
{
}
//------------------------------------------------------------------------
CAAxPDMPropertyCmd::~CAAxPDMPropertyCmd()
{
   _Panel=NULL;
   _ElementAcq=NULL;
   _PanelCANCELAcq=NULL;
   _PanelDeactivateInstance=NULL;
   _PanelActivateInstance=NULL;
}
//------------------------------------------------------------------------
void CAAxPDMPropertyCmd::BuildGraph()
{
   CATApplicationFrame* AppliFr = CATApplicationFrame::GetApplicationFrame();
   if (NULL==AppliFr) {RequestDelayedDestruction();return;}
   CATDialog * TempoParent = (CATDialog *) AppliFr -> GetMainWindow();
   _Panel = new CAAxPDMPropertyPanel(TempoParent);
   if (NULL==_Panel) {RequestDelayedDestruction();return;}
   
   //--------------Create Selections's Agents--------
   //selection in panel
   _PanelCANCELAcq = new CATDialogAgent ("AgentCANCEL"); 
   if (NULL==_PanelCANCELAcq) {RequestDelayedDestruction();return;}
   _ElementAcq = new CATPathElementAgent ("ElementSelect",CATILinkableObject::ClassName(),CATDlgEngWithPrevaluation|CATDlgEngWithPSOHSO); 
   if (NULL==_PanelCANCELAcq) {RequestDelayedDestruction();return;}
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaCANCELNotification());
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetWindCloseNotification());
   _PanelDeactivateInstance = new CATDialogAgent("AgentDeactivate");
   _PanelDeactivateInstance->AcceptOnNotify(NULL,CAAxPDMPropertyPanelNotification1::ClassName());
   _PanelActivateInstance = new CATDialogAgent("AgentActivate");
   _PanelActivateInstance->AcceptOnNotify(NULL,CAAxPDMPropertyPanelNotification2::ClassName());
   
   //--------------Define Statechart's States--------------
   CATDialogState* state1 = GetInitialState("Property");
   if (NULL==state1) {RequestDelayedDestruction();return;}
   state1->AddDialogAgent(_PanelCANCELAcq);
   state1->AddDialogAgent(_ElementAcq);
   state1->AddDialogAgent(_PanelDeactivateInstance);
   state1->AddDialogAgent(_PanelActivateInstance);
   
   //-----------Define Statechart's Transitions-----------
   // CANCEL
   AddTransition (state1,NULL,IsOutputSetCondition(_PanelCANCELAcq),Action((ActionMethod)&CAAxPDMPropertyCmd::Quit));
   // Select element
   AddTransition (state1,state1,IsOutputSetCondition(_ElementAcq),  Action((ActionMethod)&CAAxPDMPropertyCmd::SelectElement));
   //Activate/Deactivate instance
   AddTransition (state1,state1,IsOutputSetCondition(_PanelActivateInstance),Action((ActionMethod)&CAAxPDMPropertyCmd::ActivateInstance));
   AddTransition (state1,state1,IsOutputSetCondition(_PanelDeactivateInstance),Action((ActionMethod)&CAAxPDMPropertyCmd::DeactivateInstance));
}


//------------------------------------------------------------------------
//   Action : Update Panel Display
//------------------------------------------------------------------------
boolean CAAxPDMPropertyCmd::RefreshPanel(CATIxPDMItem_var & oItem)
{
   boolean sortie=TRUE;
   if (_Panel)
      _Panel->SetItem(oItem);
   return sortie;
}

//------------------------------------------------------------------------
//   Action : Select an element
//------------------------------------------------------------------------
boolean CAAxPDMPropertyCmd::SelectElement(void*)
{
   if (_ElementAcq)
   {
      //To identify selected item
      CATDocument* doc=NULL;
      CATPathElement* path = _ElementAcq->GetValue();
      if (path)
      {
         CATILinkableObject* link = (CATILinkableObject*)path->FindElement(CATILinkableObject::ClassId()) ;
         if (link)
         {
            CATIProduct* product=NULL;
            if (SUCCEEDED(link->QueryInterface(IID_CATIProduct,(void**)&product)))
            {
               CATIProduct_var refproduct = product->GetReferenceProduct();
               if (!!refproduct)
               {
                  link->Release(); link=NULL;
                  refproduct->QueryInterface(IID_CATILinkableObject,(void**)&link);
               }
               product->Release(); product=NULL;
            }
            if (link)
            {
               doc = link->GetDocument();
               link->Release(); link=NULL;
            }
         }
      }
      CATIxPDMItem_var oPDMItem;
      if (doc && SUCCEEDED(CATxPDMSessionServices::GetItemFromDocument(doc,oPDMItem)))
      {
         //To refresh panel content with selected item
         RefreshPanel(oPDMItem);
         //To update highlight
         CATFrmEditor* editor = GetEditor();
         if (editor)
         {
            CATHSO* hso = editor->GetHSO();
            if (hso)
               hso->Empty();
         }
         _ElementAcq->PutIntoHSO();
      }
      //To allow other selection and avoid CPU loop in DialogEngine
      _ElementAcq->InitializeAcquisition();
   }
   return TRUE;
}
//------------------------------------------------------------------------
//   Action : 
//------------------------------------------------------------------------
boolean CAAxPDMPropertyCmd::ActivateInstance(void*)
{
   if (_Panel)
      _Panel->ActivateDeactivateProduct(TRUE);
   if (_PanelActivateInstance)
      _PanelActivateInstance->InitializeAcquisition();
   return TRUE;
}
//------------------------------------------------------------------------
//   Action : 
//------------------------------------------------------------------------
boolean CAAxPDMPropertyCmd::DeactivateInstance(void*)
{
   if (_Panel)
      _Panel->ActivateDeactivateProduct(FALSE);
   if (_PanelDeactivateInstance)
      _PanelDeactivateInstance->InitializeAcquisition();
   return TRUE;
}

//------------------------------------------------------------------------
//   Action : Close button
//------------------------------------------------------------------------
boolean CAAxPDMPropertyCmd::Quit(void*)
{
   //ExecuteUndoAtEnd();
   return TRUE;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMPropertyCmd::Activate(CATCommand*, CATNotification*)
{
   CATApplicationFrame *pApplication = CATApplicationFrame::GetFrame();
   CATIxPDMSession_var xPDMSession(pApplication);
   CATIxPDMItem_var oItem;
   if ( NULL_var != xPDMSession )
      xPDMSession->GetCurrentItem(oItem);
   if (!!oItem)
   {
      RefreshPanel(oItem);
      _Panel->SetVisibility(CATDlgShow);
   }
   else if (pApplication)
   {
      CATDlgNotify* notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyInformation);
      CATUnicodeString texte=CATMsgCatalog::BuildMessage("CAAxPDMPropertyPanel","Warning1",NULL,0,"Nothing");
      notif->DisplayBlocked(texte,"Warning");
      notif->RequestDelayedDestruction();
      RequestDelayedDestruction();
   }
   return CATStatusChangeRCCompleted;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMPropertyCmd::Cancel(CATCommand* cmd, CATNotification* notif)
{
   if (_Panel) _Panel->RequestDelayedDestruction();
   _Panel = NULL;
   if (_ElementAcq) _ElementAcq->RequestDelayedDestruction();
   _ElementAcq = NULL;
   if (_PanelCANCELAcq) _PanelCANCELAcq->RequestDelayedDestruction();
   _PanelCANCELAcq = NULL;
   if (_PanelDeactivateInstance) _PanelDeactivateInstance->RequestDelayedDestruction();
   _PanelDeactivateInstance = NULL;
   if (_PanelActivateInstance) _PanelActivateInstance->RequestDelayedDestruction();
   _PanelActivateInstance = NULL;
   return CATStateCommand::Cancel(cmd, notif);
}

