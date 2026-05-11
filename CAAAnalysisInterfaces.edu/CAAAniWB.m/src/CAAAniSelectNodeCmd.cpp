// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CAAAniSelectNodeCmd.cpp
// Header definition of CAAAniSelectNodeCmd
//===================================================================

#include "CAAAniSelectNodeCmd.h"

#include "CATBSTR.h"
#include "CATPathElementAgent.h"
#include "CATCreateExternalObject.h"

// customize highlight
#include "CATMSHCustomHighlight.h"
#include "CATGraphicAttributeSet.h"
#include "CAT3DMarkerGP.h"
#include "CAT3DCustomRep.h"
#include "CATIMSHSelectedNode.h"
#include "CATMSHNode.h"

// Dialog PreReq
#include "CATDlgDialog.h"
#include "CATApplicationFrame.h"
#include "CATDlgLabel.h"

CATCreateClassArg (CAAAniSelectNodeCmd,CATUnicodeString);

CATImplementClass( CAAAniSelectNodeCmd,Implementation,CATStateCommand,CATNull );
 
//-----------------------------------------------------------------------------
// CAAAniSelectNodeCmd : constructor
//-----------------------------------------------------------------------------
CAAAniSelectNodeCmd::CAAAniSelectNodeCmd(const CATUnicodeString *iEntityType,const CATString &iName,CATCommandMode iStatus):
    CATStateCommand(iName,iStatus)
{
  _FeatSelectionAgent = NULL;
  _Agent = NULL;	
  _AgentCancel = NULL;
  _Panel	= NULL;
}

//-----------------------------------------------------------------------------
// CAAAniSelectNodeCmd : destructor
//-----------------------------------------------------------------------------
CAAAniSelectNodeCmd::~CAAAniSelectNodeCmd()
{
  if (_FeatSelectionAgent)_FeatSelectionAgent -> Release();		_FeatSelectionAgent = NULL;
  if (_Agent)             _Agent -> Release();					_Agent = NULL;
  if (_AgentCancel)       _AgentCancel -> Release(); 			_AgentCancel = NULL;
  if (_Panel)			        _Panel -> RequestDelayedDestruction(); _Panel=NULL;
}

//-----------------------------------------------------------------------------
// CAAAniSelectNodeCmd : BuildGraph
//-----------------------------------------------------------------------------
void CAAAniSelectNodeCmd::BuildGraph()
{
  _FeatSelectionAgent = new CATPathElementAgent ("FeatSelectionAgent");
  if ( _FeatSelectionAgent) {
    _FeatSelectionAgent->AddElementType(IID_CATIMSHSelectedNode);
  	_FeatSelectionAgent -> SetBehavior ( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation );
    AddCSOClient(_FeatSelectionAgent);
  }

// Create MSHcustoHighlight calling your own highlight method and set it as filter
   CATMSHCustomHighlight* pFilter = new CATMSHCustomHighlight((CATMSHMethodHilight) &HighlightCustoNode,(void*)this);
  _FeatSelectionAgent->SetFilter(pFilter); 

// creation of the result panel
   _Panel = new  CATDlgDialog(CATApplicationFrame::GetFrame()->GetMainWindow(), "SelectNode");  
   CATDlgLabel *pLabel = new CATDlgLabel (_Panel, "One node has been selected !");
   	  
  CATDialogState* InitialState = GetInitialState("Init");
  if (InitialState) InitialState->AddDialogAgent(_FeatSelectionAgent);

  CATDialogState  *pState2 = AddDialogState ("CustomLoadState");
  AddTransition(InitialState, pState2, IsOutputSetCondition(_FeatSelectionAgent), 
								Action((ActionMethod) &CAAAniSelectNodeCmd::SelectNode, NULL,NULL,(void*)0));

  _Agent = new CATDialogAgent ("AgentOK");
  _Agent->AcceptOnNotify (_Panel,_Panel->GetDiaOKNotification());
  _AgentCancel = new CATDialogAgent ("AgentCancel");
  _AgentCancel->AcceptOnNotify (_Panel,_Panel->GetDiaCANCELNotification());
  _AgentCancel->AcceptOnNotify (_Panel,_Panel->GetWindCloseNotification());
  pState2->AddDialogAgent(_Agent);
  pState2->AddDialogAgent(_AgentCancel);
  pState2->AddDialogAgent(_Panel);
  
  AddTransition(pState2,NULL,IsOutputSetCondition(_Agent),
                Action ((ActionMethod) & CAAAniSelectNodeCmd::SelectNode,NULL,NULL,(void*)1));

  // transition de sortie
  AddTransition(pState2,GetCancelState(),IsOutputSetCondition(_AgentCancel));
}

//------------------------------------------------------------------------------
// CAAAniSelectNodeCmd::ChangeStatus 
//------------------------------------------------------------------------------
CATBoolean CAAAniSelectNodeCmd::SelectNode(void *data)
{
  return TRUE;
}
//------------------------------------------------------------------------------
// CAAAniSelectNodeCmd::HighlightCustoNode 
//------------------------------------------------------------------------------
HRESULT CAAAniSelectNodeCmd::HighlightCustoNode (CAT3DCustomRep * iRep, CATBaseUnknown * iEntity, void * iHData) 
{ 
  if (NULL == iEntity || NULL == iRep) return E_INVALIDARG;
 
	CATIMSHSelectedNode * piSelectNode = NULL;
	iEntity -> QueryInterface (IID_CATIMSHSelectedNode,(void **) &piSelectNode);
	if (!piSelectNode) return E_FAIL;
 
	 CATMSHNode * node = piSelectNode -> GetNode ();
	 piSelectNode -> Release (); piSelectNode = NULL;
   if (!node) return E_FAIL;
 
	 float						 xyz[3];
	 const double * coor = node -> GetCoordinates ();
	 xyz[0] = (float) coor[0];
   xyz[1] = (float) coor[1];
   xyz[2] = (float) coor[2];

   CATGraphicAttributeSet attribute;
   attribute.SetColor ( GREEN );
   
   CAT3DMarkerGP * marker = new CAT3DMarkerGP ( xyz, 1 , CROSS );
   iRep -> AddGP ( marker , attribute );
 
    return S_OK; 
} 
