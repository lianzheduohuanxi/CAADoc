// =========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
// =========================================================================
// Shape Design And Styling 
//---------------------------------------------------------------------
// 
// CAAGSMCircleSweepTgCmd 
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent command 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------
// 
// ===== Define to set up safe manipulation of feature in UI ( / As it is done in GSD ) 
//#define V5R17_FORBID_MODIFICATION_FEATURE_MODE_ATEDIT 
// ===============================================================================


// MINC 
#include "CATBody.h"
#include "CATBooleanDef.h"
#include "CATDiaAction.h"
#include "CATDialogState.h"
#include "CATDlgEngUtility.h"
#include "CATDlgNotify.h"
#include "CATDlgUtility.h"
#include "CATDlgWindow.h"
#include "CATIGeometricalElement.h"
#include "CATMfErrUpdate.h"
#include "CATPathElementAgent.h"
#include "CATSO.h"
#include "CATString.h"

#include "CAAGsiServices.h"
#include "CAAGsiServicesBody.h"


// Local  Framework
#include "CAAGSMCircleSweepTgCmd.h"
#include "CAAGSMCircleSweepTgDlg.h"        // needed to create an edition dialog box
#include "CAAGSMCircleSweepTgUINotifications.h"

#include "CAAGsiFeaturesSplUI.h"
#include "CAAGSMIntegrationCmdServices.h"

//Visualization framework 
#include "CATIModelEvents.h"
#include "CATModify.h"

// #include "CAAGSMCircleSweepTgModel.h"	
#include "CAAIGSMFeaturesSplFactory.h"
#include "CAAIGSMCircleSweepTg.h" 

// ApplicationFrame Framework
#include "CATFrmEditor.h"                 // needed to retrieve the editor and then to highight objects
#include "CATApplicationFrame.h"
// Dialog Framework
#include "CATDlgDialog.h"                 // needed to return the dialog box to GiveMyPanel method of
// father class CATMMUiPanelStateCommand

// DialogEngine Framework
#include "CATFeatureImportAgent.h"        // needed to be able to pick any element whatever its context is

// ObjectModelerBase Framework
#include "CATIContainer.h"                // needed to create a GSM tool in case it is necessary

// ObjectSpecsModeler Framework

#include "CATISpecObject.h"               // needed to manage feature

// MechanicalModeler Framework
#include "CATIMechanicalRootFactory.h"    // needed to create a GSM tool in case it is necessary
#include "CATIGSMTool.h"                  // needed to manage GSM tools
#include "CATMmrLinearBodyServices.h" 

// MechanicalModelerUI Framework
#include "CATPrtUpdateCom.h"              // needed to update the feature according to the user's update settings
#include "CATIUpdateError.h"              // needed to update the feature according to the user's update settings

// MecModInterfaces Framework
#include "CATIPrtPart.h"                  // needed to look for a GSM tool
#include "CATIMfBRep.h"                // needed to declare the modes of BRep feature creation
#include "CATMfBRepDefs.h"                // needed to declare the modes of BRep feature creation

//System
#include "CATUnicodeString.h"

// Visualization Framework
#include "CATPathElement.h"               // needed to highlight objects
#include "CATHSO.h"                       // needed to highlight objects
#include "CATIVisProperties.h"            // needed to change Combined Curve's graphical appearance

#include "CATIGSMFactory.h"
#include "CATIGSMUIFactory.h"
#include "CATIGSMProceduralView.h"
#include "CATIMmiNonOrderedGeometricalSet.h"
#include "CATIMmiOrderedGeometricalSet.h"
#include "CATIMechanicalTool.h"
#include "CATMmrFeatureAttributes.h" //BS in OGS 

#include "CATStateActivateNotification.h"
#include "CATCSO.h"
#include "CATCommandGlobalUndo.h"
#include "CATIRedrawEvent.h"


// #define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 



#define HighlightField1 (ActionMethod)&CAAGSMCircleSweepTgCmd::Highlight_Field1
#define HighlightField2 (ActionMethod)&CAAGSMCircleSweepTgCmd::Highlight_Field2
#define ResetHighlight  (ActionMethod)&CAAGSMCircleSweepTgCmd::Reset_Highlight


// This Command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 


CATCreateClass(CAAGSMCircleSweepTgCmd);


//---------------------------------------------------------------------
// Tests if a given feature is aggregated to a ShapeBody
//---------------------------------------------------------------------
int GetFeatureToolType (const CATISpecObject_var & feature)
{
	int iExit=0;
	CATISpecObject_var curobject = feature;
	if (!!curobject)
	{
		int iTypeFound = 0 ; 
		CATISpecObject* father = curobject->GetFather();
		while(father)
		{
			CATIMmiNonOrderedGeometricalSet_var spNonOrderedGeomSet = father  ; 
			CATIMmiOrderedGeometricalSet_var    spOrderedGeomSet    = father ; 
			CATIMechanicalTool_var              spMechanicalSet     = father ; 
			if ( NULL_var != spNonOrderedGeomSet )  {
				iTypeFound = 1 ; 
			}
			else if ( NULL_var != spOrderedGeomSet ) {
				iTypeFound = 2 ; 
			}
			else if (NULL_var !=  spMechanicalSet  ) {
				iTypeFound = 3 ; 
			}
			if (iTypeFound > 0 ) break ; 
			else
			{
				curobject = father;
				father -> Release();
				father = curobject -> GetFather();
			}
		}
		if(father)
		{
			iExit = iTypeFound ; 	 
			father -> Release();
			father = NULL;
		}
	}
	return iExit;
}

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : constructor / CmdInfo 
// Deriving from CATMMUIPanelStateCmd provides an association between 
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
CAAGSMCircleSweepTgCmd::CAAGSMCircleSweepTgCmd():
CATMMUIPanelStateCmd("CircleSweepTgCommand"),
_pCurveRefAgent            (NULL),
_pSurfaceSupportAgent      (NULL),
_pCurveRefFieldAgent       (NULL),
_pSurfaceSupportFieldAgent (NULL),
_RemoveElement			   (NULL),
_InvertOri				   (NULL), 
_ValueChanged              (NULL),
_TrimChanged               (NULL), 
_piCircleSweepTg           (NULL),
_panel	                   (NULL),
_editor			           (NULL),
_HSO			           (NULL),
_FeatureModeChanged        (CATFalse)
{
	 _ActiveField = 0;
	_mode = 1;
	_piCircleSweepTg = NULL ;

  SetUndoTitleToTheCmd();
}

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between 
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
CAAGSMCircleSweepTgCmd::CAAGSMCircleSweepTgCmd( CAAIGSMCircleSweepTg *i_piCircleSweepTg):
CATMMUIPanelStateCmd("CircleSweepTgCommand"),
_pCurveRefAgent              (NULL),
_pSurfaceSupportAgent        (NULL),
_pCurveRefFieldAgent         (NULL),
_pSurfaceSupportFieldAgent   (NULL),
_RemoveElement				 (NULL),
_InvertOri					 (NULL),
_ValueChanged                (NULL),
_TrimChanged                 (NULL),  
_piCircleSweepTg             (NULL),
_panel			             (NULL),
_editor			             (NULL),
_HSO		                 (NULL),
_FeatureModeChanged (CATFalse)
{
	_ActiveField = 0;
	_mode = 1;

	if (i_piCircleSweepTg) {
		_piCircleSweepTg = i_piCircleSweepTg;
		if (NULL != _piCircleSweepTg ) { 
			_piCircleSweepTg->AddRef();
			_mode = 0;

		}
	}
  SetUndoTitleToTheCmd();
}

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : destructor
//-----------------------------------------------------------------------------
CAAGSMCircleSweepTgCmd::~CAAGSMCircleSweepTgCmd()
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::~CAAGSMCircleSweepTgCmd) "  << endl; 
#endif

	_piCircleSweepTg                   = NULL ; 
	_pCurveRefAgent          = NULL ;
	_pSurfaceSupportAgent        = NULL ;

	_pCurveRefFieldAgent     = NULL ;
	_pSurfaceSupportFieldAgent   = NULL ;
	_panel                 = NULL ;

	_editor                = NULL ;
	_HSO                   = NULL ;
	_RemoveElement		   = NULL;
	_InvertOri			   = NULL;
	_ValueChanged  = NULL;
	_TrimChanged  = NULL;

}


///////////////////////////
// Launching the Command //
///////////////////////////


//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : CreateStartFeat
//-----------------------------------------------------------------------------

void CAAGSMCircleSweepTgCmd::CreateStartFeat()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::CreateStartFeat() "  << endl; 
#endif 
	HRESULT rc = S_OK ; 

	// Editor 
	// ----------------------------------------------
	_editor = CATFrmEditor::GetCurrentEditor();
	_HSO = NULL ;

	if ( NULL != _editor ){	
		_HSO = _editor->GetHSO();
	}
	// Edition mode.
	// ---------------------------------------------------------------
	if ( _mode == 0 ) 
	{
	}
	
	// Creation mode.
	// ---------------------------------------------------------------
	else 
	{
		CATIContainer_var cont = CAAGsiGetCurrentContainer();
		// CAAIGSMFeaturesSplFactory
		// gets a pointer on CATIMechanicalRootFactory from this feature container
		CAAIGSMFeaturesSplFactory_var pFeaturesSplFactory = cont;
		if ( !!  pFeaturesSplFactory  ) 
		{
			_piCircleSweepTg  = pFeaturesSplFactory  -> CreateCircleSweepTg (NULL , NULL , 10.0 );
			if (NULL != _piCircleSweepTg) { 
				CATISpecObject_var piSpecOnCircleSweepTg           = _piCircleSweepTg;
				CATIGSMProceduralView_var Obj            = piSpecOnCircleSweepTg; 
				Obj                                      -> InsertInProceduralView() ;
			}
			else {
				// Error Panel Displayed
				ErrorPanel("Error", "Error in <CAAGSMCircleSweepTgCmd::CreateStartFeat()> Creation feature failed  ", 1 );
			}

		}
	}
}



//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : BuildGraph()
//-----------------------------------------------------------------------------
void CAAGSMCircleSweepTgCmd::BuildGraph()
{


#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::BuildGraph) "  << endl; 
#endif     
	// creates the dialog box
	// ---------------------------------------------------------------
	_panel = new CAAGSMCircleSweepTgDlg(this);
	_panel->Build();


	// Agent _HSO
	_pCurveRefAgent               = new CATFeatureImportAgent ( "CurveRefAgent"     , NULL , NULL , MfNoDuplicateFeature ) ;
	_pSurfaceSupportAgent         = new CATFeatureImportAgent ( "SurfaceSupportAgent"     , NULL , NULL , MfNoDuplicateFeature ) ;
	_pCurveRefFieldAgent          = new CATDialogAgent  ( "CurveRefFieldAgent"    ) ;
	_pSurfaceSupportFieldAgent    = new CATDialogAgent  ( "SurfaceSupportFieldAgent"    ) ;
	_RemoveElement				  = new CATDialogAgent  ( "Clear Selection"          ) ;
	_InvertOri				      = new CATDialogAgent  ( "Invert Orientation"          ) ;
	_ValueChanged 			      = new CATDialogAgent  ( "Value Changed "          ) ;
	_TrimChanged 			      = new CATDialogAgent  ( "Trim  Changed "          ) ;

	//-----------------------------------------------------------------------------
	// Selection Agents
	//-----------------------------------------------------------------------------


	_pCurveRefAgent -> SetOrderedElementType ( "CATIMfMonoDimResult" );
	_pCurveRefAgent -> AddOrderedElementType ( "CATCurve"            );
	_pCurveRefAgent -> AddOrderedElementType ( "CATEdge"             );
	_pCurveRefAgent -> AddOrderedElementType ( "CATWire"             );
	_pCurveRefAgent -> SetFilter (Filter ((FilterMethod) &CAAGSMCircleSweepTgCmd::IsAValidCurve, NULL));  // prevent Axis Selection
	_pCurveRefAgent ->  SetBehavior      ( CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot  );
	_pCurveRefAgent-> SetAgentBehavior ( MfPermanentBody           | MfLastFeatureSupport | MfRelimitedFeaturization );

	_pSurfaceSupportAgent -> SetOrderedElementType ( "CATIMfBiDimResult" );
	_pSurfaceSupportAgent -> AddOrderedElementType ( "CATSurface"         );
	_pSurfaceSupportAgent -> AddOrderedElementType ( "CATFace"            );
	_pSurfaceSupportAgent -> AddOrderedElementType ( "CATShell"             );
	_pSurfaceSupportAgent -> SetBehavior      ( CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot         );
	_pSurfaceSupportAgent -> SetAgentBehavior ( MfPermanentBody           | MfLastFeatureSupport | MfRelimitedFeaturization );

	// _pCurveRefFieldAgent and _pSurfaceSupportFieldAgent to change current acquisition type
	_pCurveRefFieldAgent           -> AcceptOnNotify (_panel, CAACircleSweepTgUICurveRefFieldActivate::ClassName() );
	_pSurfaceSupportFieldAgent     -> AcceptOnNotify (_panel, CAACircleSweepTgUISupportFieldActivate::ClassName() );


	//-----------------------------------------------------------------------------
	// Clear Selection 
	//-----------------------------------------------------------------------------
	_RemoveElement -> AcceptOnNotify(NULL, CAACircleSweepTgUIRemoveElement::ClassName());
	_ValueChanged  -> AcceptOnNotify(NULL, CAACircleSweepTgUIValueChanged::ClassName());
	_TrimChanged   -> AcceptOnNotify(NULL, CAACircleSweepTgUITrimChanged::ClassName());

	//-----------------------------------------------------------------------------
	// Invert Input Direction
	//-----------------------------------------------------------------------------
	_InvertOri -> AcceptOnNotify(NULL, CAACircleSweepTgUIInvertOrientation::ClassName());

	//-----------------------------------------------------------------------------
	// Command States
	//-----------------------------------------------------------------------------

	// Uses "PanelStates" instead of standard "DialogStates".
	// Theses states are provided by father class CATMMUIPanelStateCommand.
	// They make it possible for you not to worry about transition to OK and Cancel States.


	// State 1
	CATDialogState *WaitingForCurveRef= GetInitialPanelState("Select a Curve ");
	WaitingForCurveRef -> AddDialogAgent ( _pCurveRefAgent           ); 
	WaitingForCurveRef -> AddDialogAgent ( _pCurveRefFieldAgent ); 
	WaitingForCurveRef -> AddDialogAgent ( _pSurfaceSupportFieldAgent ); 
	WaitingForCurveRef -> AddDialogAgent ( _RemoveElement ); 
	WaitingForCurveRef -> AddDialogAgent ( _InvertOri ); 
	WaitingForCurveRef -> AddDialogAgent ( _ValueChanged ); 
	WaitingForCurveRef -> AddDialogAgent ( _TrimChanged ); 

	// State 2
	CATDialogState *WaitingForSurfSupport = AddPanelState("Select Surface support");
	WaitingForSurfSupport -> AddDialogAgent ( _pSurfaceSupportAgent   ); 
	WaitingForSurfSupport -> AddDialogAgent ( _pCurveRefFieldAgent ); 
	WaitingForSurfSupport -> AddDialogAgent ( _pSurfaceSupportFieldAgent ); 
	WaitingForSurfSupport -> AddDialogAgent ( _RemoveElement );  
	WaitingForSurfSupport -> AddDialogAgent ( _ValueChanged );  
	WaitingForSurfSupport -> AddDialogAgent ( _TrimChanged );  
	WaitingForSurfSupport -> AddDialogAgent ( _InvertOri ); 

	// Final State
	CATDialogState *FinalState= AddPanelState("Click OK,Cancel or Preview");
	FinalState -> AddDialogAgent ( _pCurveRefFieldAgent ); 
	FinalState -> AddDialogAgent ( _pSurfaceSupportFieldAgent ); 
	FinalState -> AddDialogAgent ( _RemoveElement );  
	FinalState -> AddDialogAgent ( _InvertOri ); 
	FinalState -> AddDialogAgent ( _ValueChanged );  
	FinalState -> AddDialogAgent ( _TrimChanged );  
	//------------------------------------------------------------------------------
	//   Actions : entering/leaving a state // To manage correctly Undo/Redo of highlight
	//------------------------------------------------------------------------------

	CATDiaAction * EnterAction1 = Action(HighlightField1);
	if(EnterAction1 ) EnterAction1 -> SetAfterRedoMethod(HighlightField1);
	CATDiaAction * LeaveAction1 = Action(NULL);
	if(LeaveAction1 ) LeaveAction1 -> SetAfterUndoMethod(HighlightField1);

	CATDiaAction * EnterAction2 = Action(HighlightField2);
	if(EnterAction2 ) EnterAction2 -> SetAfterRedoMethod(HighlightField2);
	CATDiaAction * LeaveAction2 = Action(NULL);
	if(LeaveAction2 ) LeaveAction2 -> SetAfterUndoMethod(HighlightField2);

	CATDiaAction * EnterAction3 = Action(ResetHighlight);
	if(EnterAction3 ) EnterAction3 -> SetAfterRedoMethod(ResetHighlight);
	CATDiaAction * LeaveAction3 = Action(NULL);
	if(LeaveAction3 ) LeaveAction3 -> SetAfterUndoMethod(ResetHighlight);



	WaitingForCurveRef -> SetEnterAction(EnterAction1);
	WaitingForCurveRef -> SetLeaveAction(LeaveAction1);
	WaitingForSurfSupport   -> SetEnterAction(EnterAction2);
	WaitingForSurfSupport   -> SetLeaveAction(LeaveAction2);

	FinalState   -> SetEnterAction(EnterAction3);
	FinalState   -> SetLeaveAction(LeaveAction3);


	//------------------------------------------------------------------------------
	//   Actions : Update Model
	//------------------------------------------------------------------------------
	CATDiaAction   * CurveRefSelection  = NULL;
	CurveRefSelection = Action((ActionMethod)&CAAGSMCircleSweepTgCmd::ElementSelected, NULL, NULL, (void *) _pCurveRefAgent);
	if (CurveRefSelection) { 
		CurveRefSelection -> SetAfterUndoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
		CurveRefSelection -> SetAfterRedoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
	}

	CATDiaAction   * SurfaceSupportSelection  = NULL;
	SurfaceSupportSelection = Action((ActionMethod)&CAAGSMCircleSweepTgCmd::ElementSelected, NULL, NULL, (void *) _pSurfaceSupportAgent);
	if (SurfaceSupportSelection) {
		SurfaceSupportSelection -> SetAfterUndoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
		SurfaceSupportSelection -> SetAfterRedoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
	}
	//------------------------------------------------------------------------------
	//   Actions : UI selection
	//------------------------------------------------------------------------------
	CATDiaAction   * Field1Selection  = NULL;
	Field1Selection = Action(HighlightField1);
	if (Field1Selection){
		Field1Selection -> SetAfterUndoMethod(HighlightField1);
		Field1Selection -> SetAfterRedoMethod(HighlightField1);
	}

	CATDiaAction   * Field2Selection  = NULL;
	Field2Selection = Action(HighlightField2);
	if (Field2Selection){
		Field2Selection -> SetAfterUndoMethod(HighlightField2);
		Field2Selection -> SetAfterRedoMethod(HighlightField2);
	}
	//------------------------------------------------------------------------------
	//   Actions : Clear selection
	//------------------------------------------------------------------------------
	CATDiaAction   * ClearSelection  = NULL;
	ClearSelection = Action((ActionMethod)&CAAGSMCircleSweepTgCmd::ClearSelection);
	if (ClearSelection){
		ClearSelection -> SetAfterUndoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::UndoClearSelection);
		ClearSelection -> SetAfterRedoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::ClearSelection);
	}
	//------------------------------------------------------------------------------
	//   Actions : InvertInputOrientation
	//------------------------------------------------------------------------------
	CATDiaAction   * InvertInputOrientation  = NULL;
	InvertInputOrientation = Action((ActionMethod)&CAAGSMCircleSweepTgCmd::InvertInputOrientation);
	if (InvertInputOrientation){
		InvertInputOrientation -> SetAfterUndoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
		InvertInputOrientation -> SetAfterRedoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
	}
	//------------------------------------------------------------------------------
	//   Actions : InvertInputOrientation
	//------------------------------------------------------------------------------
	CATDiaAction   * ValueChangedInPanel  = NULL;
	ValueChangedInPanel = Action((ActionMethod)&CAAGSMCircleSweepTgCmd::ValueChanged);
	if (ValueChangedInPanel){
		ValueChangedInPanel -> SetAfterUndoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
		ValueChangedInPanel -> SetAfterRedoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
	}
	//------------------------------------------------------------------------------
	//   Actions : InvertInputOrientation
	//------------------------------------------------------------------------------
	CATDiaAction   * TrimChangedInPanel  = NULL;
	TrimChangedInPanel = Action((ActionMethod)&CAAGSMCircleSweepTgCmd::TrimChanged);
	if (TrimChangedInPanel){
		TrimChangedInPanel -> SetAfterUndoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
		TrimChangedInPanel -> SetAfterRedoMethod((ActionMethod)&CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel);
	}
	//-----------------------------------------------------------------------------
	// Transitions
	//-----------------------------------------------------------------------------
	//State1 
	AddTransition ( WaitingForCurveRef, WaitingForSurfSupport,IsOutputSetCondition ( _pCurveRefAgent  ) ,CurveRefSelection );
	AddTransition ( WaitingForCurveRef ,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceSupportFieldAgent ) ,Field2Selection );
	AddTransition ( WaitingForCurveRef ,WaitingForCurveRef,IsOutputSetCondition ( _pCurveRefFieldAgent ) ,Field1Selection );
	AddTransition ( WaitingForCurveRef ,WaitingForCurveRef,IsOutputSetCondition ( _RemoveElement ) ,ClearSelection );
	AddTransition ( WaitingForCurveRef ,WaitingForCurveRef,IsOutputSetCondition ( _InvertOri ) ,InvertInputOrientation );
	AddTransition ( WaitingForCurveRef ,WaitingForCurveRef,IsOutputSetCondition ( _ValueChanged ) ,ValueChangedInPanel );
	AddTransition ( WaitingForCurveRef ,WaitingForCurveRef,IsOutputSetCondition ( _TrimChanged ) ,TrimChangedInPanel );


	// State2 
	AddTransition ( WaitingForSurfSupport,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceSupportFieldAgent  ) ,Field2Selection );
	AddTransition ( WaitingForSurfSupport ,FinalState, IsOutputSetCondition ( _pSurfaceSupportAgent ) ,SurfaceSupportSelection );
	AddTransition ( WaitingForSurfSupport ,WaitingForCurveRef,IsOutputSetCondition ( _pCurveRefFieldAgent ) ,Field1Selection );
	AddTransition ( WaitingForSurfSupport ,WaitingForSurfSupport,IsOutputSetCondition ( _RemoveElement ) ,ClearSelection );
	AddTransition ( WaitingForSurfSupport ,WaitingForSurfSupport,IsOutputSetCondition ( _InvertOri ) ,InvertInputOrientation );
	AddTransition ( WaitingForSurfSupport ,WaitingForSurfSupport,IsOutputSetCondition ( _ValueChanged ) ,ValueChangedInPanel );
	AddTransition ( WaitingForSurfSupport ,WaitingForSurfSupport,IsOutputSetCondition ( _TrimChanged ) ,TrimChangedInPanel );

	// Final 
	AddTransition ( FinalState,WaitingForSurfSupport,IsOutputSetCondition ( _pSurfaceSupportFieldAgent  ) ,Field2Selection );
	AddTransition ( FinalState ,WaitingForCurveRef,IsOutputSetCondition ( _pCurveRefFieldAgent ) ,Field1Selection );
	AddTransition ( FinalState ,FinalState,IsOutputSetCondition ( _RemoveElement ) ,ClearSelection );
	AddTransition ( FinalState ,FinalState,IsOutputSetCondition ( _InvertOri ) ,InvertInputOrientation );
	AddTransition ( FinalState ,FinalState,IsOutputSetCondition ( _ValueChanged ) ,ValueChangedInPanel );
	AddTransition ( FinalState ,FinalState,IsOutputSetCondition ( _TrimChanged ) ,TrimChangedInPanel );


	// Created the first Feature;
	CreateStartFeat();    


	// Fills in the dialog panel fields.
	UpdatePanelFields();
	
}


////////////////////////////////////////////////////////////////////
// Actions launched with UI notifications received from the panel //
////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd :: Action entering or leaving a State()
//-----------------------------------------------------------------------------

CATBoolean CAAGSMCircleSweepTgCmd::Highlight_Field1(void *)
{ SetActiveField(1); _pCurveRefFieldAgent->InitializeAcquisition(); return TRUE; }

CATBoolean CAAGSMCircleSweepTgCmd::Highlight_Field2(void *)
{ SetActiveField(2); _pSurfaceSupportFieldAgent->InitializeAcquisition(); return TRUE; }

CATBoolean CAAGSMCircleSweepTgCmd::Reset_Highlight(void *)
{ SetActiveField(0); return TRUE; } //Clear Select of Highlighted Field for Final State of the Automat



//-----------------------------------------------------------------------------
// CAAMmrCombCrvPanelStCmd : ClearSelection()
//
//-----------------------------------------------------------------------------
CATBoolean CAAGSMCircleSweepTgCmd::ClearSelection(void * data)
{

	int activefield = _ActiveField;
	CATISpecObject * ipSpecSel  = NULL;

	// Unset attributes by sending a NULL pointer
	UpdateDataInModel(ipSpecSel);

	UpdatePanelFields();

	// gets ready for next acquisition
	_RemoveElement -> InitializeAcquisition();

	return CATTrue;

}



///////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods used by father command CATMMUIPanelStateCommand or by the dialog Panel to Retrieve data   //
///////////////////////////////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : GiveMyPanel()
//-----------------------------------------------------------------------------
CATDlgDialog* CAAGSMCircleSweepTgCmd::GiveMyPanel()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::GiveMyPanel) "  << endl; 
#endif 
	// Used by father class CATMMUiPanelStateCommand to be notified of events
	// sent by the OK and CANCEl press button.
	return (_panel);
}

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd::GiveMyFeature()
//-----------------------------------------------------------------------------
CATISpecObject_var CAAGSMCircleSweepTgCmd::GiveMyFeature()
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::GiveMyFeature) "  << endl; 
#endif 
	CATISpecObject_var MyFeature(_piCircleSweepTg);
	return MyFeature;
}

int CAAGSMCircleSweepTgCmd::GetActiveField()
{
	return _ActiveField;
}

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : GetMode()
//-----------------------------------------------------------------------------
int CAAGSMCircleSweepTgCmd::GetMode()
{
	// This very simple methods checks if the user is creating or editing the Combined Curve.
	// This data is used by father command CATMMUIPanelStateCommand and by CATPrtUpdateCom.
	// They both provide standard edition command behaviour :
	// for example, it is not possible to create a sick Combined Curve ( a Combined Curve generating an error )

	return _mode;  // 0 : edit mode /  1 : creation mode    
}

//////////////////////
// Panel Management //
//////////////////////

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : UpdatePanelFields()
//-----------------------------------------------------------------------------
void CAAGSMCircleSweepTgCmd::UpdatePanelFields()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::UpdatePanelFields) "  << endl; 
#endif 
	// Run Generic MVC Update of Panel 
	_panel -> UpdatePanel() ;
	return ;
}


//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : SetActiveField()
//-----------------------------------------------------------------------------
void CAAGSMCircleSweepTgCmd::SetActiveField(int ActiveField)
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::SetActiveField) Field = "  <<ActiveField << endl; 
#endif 
	// This method main goal is to show the user that the acquisition one of the spec input field
	_ActiveField = ActiveField;

	// first let's empty current highlighted objects
	if (_HSO) _HSO->Empty();  

	// Put Current field Spec Element in HSO 
	if (NULL!= _piCircleSweepTg) { 
		CATISpecObject_var spoSpecOnGeomElem ;
		if (_ActiveField ==1 ) { 
			_piCircleSweepTg ->GetCurveRef(spoSpecOnGeomElem) ; 
		}
		else {
			_piCircleSweepTg ->GetSurfaceSupport(spoSpecOnGeomElem); 
		}

        // Analyse selction 
        if (!! spoSpecOnGeomElem)
        {
            CATPathElement* pPathElement = NULL;
            CATTry
            {
                pPathElement = GivePathElementFrom(spoSpecOnGeomElem);
                if(NULL != pPathElement)
                {
                    if (_HSO) _HSO->AddElement(pPathElement); 

                }
            }
            CATCatch (CATError, Error)
            {
              	ErrorPanel("Error", "Error in <CAAGSMCircleSweepTgCmd :: SetActiveField> Unable to create PathElement ", 1 );
                Flush(Error);
            }
            CATEndTry;
            if (pPathElement != NULL) { 
                pPathElement->Release();  pPathElement = NULL ;
            }
        }


	}
	_panel->HighLightCurrentPanelField(ActiveField); // puts the focus on the Active Field in the Combined Curve edition dialog box	
}




/////////////////////////////////////
// Dialog with GSD shared commands //
/////////////////////////////////////

//------------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd::Activate
//------------------------------------------------------------------------------
CATStatusChangeRC CAAGSMCircleSweepTgCmd::Activate (CATCommand *iCmd, CATNotification *iNotif)
{
	//all the following code aims at forcing the selection of the created feature as an input for Combined Curve
	//the feature, created with the contextual menu, has no parents and is in the CSO

	if (NULL != iNotif ) {

		if (((CATStateActivateNotification*)iNotif)->GetType() == CATStateActivateNotification::Resume)
		{


			CATDialogState * CurState = GetCurrentState();

			//  we find the CATPathElementAgent which is associated to it
			//    Note: in fact, we get the first agent which is a CATPathElementAgent!
			CATCommand * CurAgent = NULL;
			if(CurState) {

				CurState -> InitAgentList();
				while(CurAgent=CurState->GetNextAgent()) {
                    if(CurAgent ->IsAKindOf("CATPathElementAgent")){
                       break; 
                    }
				}
			}

			// we do the transfer from the  CSO to the waiting agent
			if(CurAgent) {

				CATCSO * CurCSO = GetCSO();
				if(CurCSO) {

					CATSO* listOfPathInCSO= NULL;
					int CSOSize = CurCSO -> GetSize();
					if(CSOSize != 0) {
						// === Getting the PathElements which are in the CSO ==========
						// we put all the paths in the list listOfPathInCSO
						CurCSO -> InitElementList();

						CATBaseUnknown *hUnknown= NULL;
						while (hUnknown= CurCSO->NextElement()) { // no addref

							if (!listOfPathInCSO) listOfPathInCSO= new CATSO(); // you must not free listOfPathInCSO. Warning SO begin with indice 0
							if(hUnknown->IsAKindOf(CATPathElement::ClassName()))
								listOfPathInCSO-> AddElement(hUnknown);
						}

						// === we value the waiting agent with the content of the CSO ==========
						CATPathElementAgent * CurPathAgent = (CATPathElementAgent *) CurAgent;
						if (CurPathAgent) {

							// (1) we save manually  because the agent valuation done after do not do it
							CATCommandGlobalUndo * GlobalUndo = new CATCommandGlobalUndo();
							if(GlobalUndo)
							{
								AddLocalUndo(GlobalUndo,"Object Selection");
								GlobalUndo -> Release();
								GlobalUndo = NULL;
							}

							CATDlgEngBehavior iBehavior = CurPathAgent -> GetBehavior();

							if(iBehavior & CATDlgEngMonoAcquisition) {

								if (listOfPathInCSO) {

									// that is THE line
									// we value CurPathAgent with the first element of the list, that means the last created one
									CurPathAgent -> SetValue( (CATPathElement *) (*listOfPathInCSO)[0]);
								}
							}
							else if (iBehavior & CATDlgEngMultiAcquisition) {

								if (listOfPathInCSO) CurPathAgent -> SetListOfValues(listOfPathInCSO);

							}


							CurPathAgent -> SetValuation();

							// (2) once got, we remove what was taken from the CSO
							if (listOfPathInCSO) 
							{
								if (CurCSO) 
								{
									for (int index= 0; index<= (listOfPathInCSO->GetSize())-1; index++)	
									{
										CurCSO -> RemoveElement((CATPathElement *) (*listOfPathInCSO)[index], 0);
									}
									CurCSO -> DispatchChange();
								}
							}

							// (3) but we put it candidate for the HSO
							if (listOfPathInCSO) {

								CATHSO *HSO = GetHSO();
								for (int k=0; k<= (listOfPathInCSO->GetSize())-1; k++){				
									if (HSO) HSO -> AddElements((CATPathElement *) (*listOfPathInCSO)[k]);
								}
								if (HSO) HSO-> EndAddElements();
							}

						}
					}


					//Clean Up 
					if(listOfPathInCSO) {listOfPathInCSO->Release();listOfPathInCSO=NULL;}

				}
			}

		}
		else
			EmptySO();

	}
	return(CATMMUIPanelStateCmd::Activate(iCmd,iNotif));

}




///////////////
// UNDO/REDO //
///////////////


CATBoolean CAAGSMCircleSweepTgCmd::SynchronizeViewWithModel(void* data)
{
	HRESULT rc=S_OK;
	UpdatePanelFields();
	return TRUE;
}




CATBoolean CAAGSMCircleSweepTgCmd::UndoClearSelection(void *  )
{ 
	CATBoolean result = SynchronizeViewWithModel(NULL);  
	return TRUE;
} 


///////////////////////////////////////////////////////////
// Actions launched at pushing OK/Preview/Cancel Buttons //
///////////////////////////////////////////////////////////





//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : Ok / Apply / Cancel 
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
CATBoolean CAAGSMCircleSweepTgCmd::PreviewAction(void* iData)
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::Preview) "  << endl; 
#endif 

	CATBoolean returnCode = TRUE;
	int result = ComputeBody();	
	returnCode = CATMMUIPanelStateCmd::PreviewAction(iData);
	return (returnCode);
	return TRUE;
}


CATBoolean CAAGSMCircleSweepTgCmd::OkAction(void* iData)
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::Ok) "  << endl; 
#endif 
	CATBoolean returnCode = TRUE;
	int result = ComputeBody();	
	returnCode = CATMMUIPanelStateCmd::OkAction(iData);
	return (returnCode);
}


CATBoolean CAAGSMCircleSweepTgCmd::CancelAction(void* iData)
{
	ExecuteUndoAtEnd();	
	CATBoolean   returnCode = CATMMUIPanelStateCmd::CancelAction(iData);
	return (returnCode);
}


CATStatusChangeRC CAAGSMCircleSweepTgCmd::Cancel(CATCommand *iCommand, CATNotification *iNotif)
{
	if(_panel){       _panel->RequestDelayedDestruction();_panel=NULL;}

	_editor                = NULL ;
	if (_HSO)_HSO->Empty() ;
	_HSO = NULL;

	if(_editor)        {_editor->Release(); _editor=NULL ;}

	if(_pCurveRefAgent)           {_pCurveRefAgent           ->RequestDelayedDestruction(); _pCurveRefAgent=NULL;}
	if(_pSurfaceSupportAgent)     {_pSurfaceSupportAgent     ->RequestDelayedDestruction(); _pSurfaceSupportAgent=NULL    ;}
	
	if(_pSurfaceSupportFieldAgent){_pSurfaceSupportFieldAgent->RequestDelayedDestruction(); _pSurfaceSupportFieldAgent=NULL ;}
	if(_pCurveRefFieldAgent)      {_pCurveRefFieldAgent      ->RequestDelayedDestruction(); _pCurveRefFieldAgent=NULL   ;}

	if(_RemoveElement)            {_RemoveElement            ->RequestDelayedDestruction(); _RemoveElement=NULL   ;}
	if(_InvertOri)                {_InvertOri                ->RequestDelayedDestruction(); _InvertOri=NULL   ;}
	if(_ValueChanged)             {_ValueChanged             ->RequestDelayedDestruction(); _ValueChanged=NULL;}
	if(_TrimChanged)              {_TrimChanged              ->RequestDelayedDestruction(); _TrimChanged=NULL;}

	if(_piCircleSweepTg)               {_piCircleSweepTg->Release();_piCircleSweepTg=NULL;}
	return(CATMMUIPanelStateCmd::Cancel(iCommand,iNotif));
}




////////////////////////////////////////////////////////////
// Selection of Feature, Update of the Model, Computation //
////////////////////////////////////////////////////////////






//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : ElementSelected()
//-----------------------------------------------------------------------------
CATBoolean CAAGSMCircleSweepTgCmd::ElementSelected(void * Data)
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::ElementSelected) Field = "  <<_ActiveField << endl; 
#endif 


	CATBoolean RetStatus = FALSE; 
	// Retrieves Acquisition Agent
	CATFeatureImportAgent *CurrAgent = (CATFeatureImportAgent *) Data; // C-style cast
	if (CurrAgent) {

		RetStatus = TRUE; 
		// Translates the selection into a  pointer on a CATBaseUnknwon model element
		CATBaseUnknown *pSelection = CurrAgent->GetElementValue(CurrAgent -> GetValue());

		// Update data in Model
		if ( NULL != pSelection )
		{
			CATISpecObject * ipSpecSel  = NULL;
			// gets a pointer on CATISpecObject for this element
			HRESULT rc = pSelection->QueryInterface(IID_CATISpecObject, (void**)&ipSpecSel);
			if ( SUCCEEDED(rc)) { 
				UpdateDataInModel(ipSpecSel);

				// Updates Panel 
				UpdatePanelFields();	

				if (ipSpecSel) {ipSpecSel->Release(); ipSpecSel = NULL ;}
			}
			else { 
				RetStatus = FALSE;
			}
		}
		else { 
			RetStatus = FALSE;
		}

		// Gets ready for next acquisition
		CurrAgent->InitializeAcquisition();
	}

	return RetStatus ;
}      



//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : UpdateDataInModel()
//-----------------------------------------------------------------------------
void CAAGSMCircleSweepTgCmd::UpdateDataInModel(CATISpecObject *  pSelection)
{
	HRESULT rc = S_OK;
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::UpdateDataInModel) Field = "  <<_ActiveField << endl; 
#endif 

	CATISpecObject_var ispSelected  = pSelection; 


	// we replace the old selected element by the new one.
	switch ( _ActiveField )
	{
	case 1 :
		{ 

			// Update of the feature Combined Curve
			if (_piCircleSweepTg){
				rc = _piCircleSweepTg -> SetCurveRef (ispSelected);
			}
			break;
		}
	case 2 :
		{
			// Update of the feature Combined Curve
			if (_piCircleSweepTg){
				rc = _piCircleSweepTg -> SetSurfaceSupport (ispSelected);

				if (SUCCEEDED(rc)) { 
					// Launch refresh event on absorbent set to UnGohst features
					// Edit Mode :  Absorbed Feature updated 
					if (_mode ==0) { 
						_FeatureModeChanged = CATTrue; //To  Refresh visu in OGS/ Body Father - UnGhost previous absorbed Elts 
					}
				}
			}
			break;
		}

	}


	return;

}       

CATBoolean CAAGSMCircleSweepTgCmd::InvertInputOrientation(void* data)
{
	HRESULT rc = S_OK ; 
	int Sol;  
	_InvertOri->InitializeAcquisition();
	if(_piCircleSweepTg)	{
		rc =_piCircleSweepTg -> GetSolution (Sol);
		if ( 1 == Sol )  rc =_piCircleSweepTg -> SetSolution (2);
		if ( 2 == Sol )  rc =_piCircleSweepTg -> SetSolution (1);

	}

	// Inverse generates automatically preview  
	CATBoolean Bool = PreviewAction(NULL);
	return TRUE;
}



CATBoolean CAAGSMCircleSweepTgCmd::ValueChanged (void *data)
{
	HRESULT rc = S_OK ; 
	double Rad = 0.0 ; 
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::ValueChanged) "  << endl; 
#endif     
	Rad = _panel -> GetRadiusValue () ; 
	if(_piCircleSweepTg)	{
		rc =_piCircleSweepTg -> SetRadius (Rad) ;
#ifdef DEBUG_GSD_CAASAMPLE
		cout << "(CAAGSMCircleSweepTgCmd::ValueChanged) radius set in model =  "<< Rad   << endl; 
#endif 
	}

	/*
	CATISpecObject_var spCurve  ,   spSurface; 
	_piCircleSweepTg->GetCurveRef(spCurve); 
	_piCircleSweepTg->GetSurfaceSupport(spSurface); 
	if ( !! spCurve && !!spSurface ){
		CATBoolean Bool = PreviewAction(NULL);
	}
	*/ 

	_ValueChanged->InitializeAcquisition();
	return TRUE;
}

CATBoolean CAAGSMCircleSweepTgCmd::TrimChanged (void *data)
{
	HRESULT rc = S_OK ; 
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::TrimChanged) "  << endl; 
#endif     
	int Trim = 0 ;
	Trim = _panel -> GetTrimMode () ; 
	if(_piCircleSweepTg)	{
#ifdef DEBUG_GSD_CAASAMPLE
		cout << "(CAAGSMCircleSweepTgCmd::TrimChanged) trim  =  "<< Trim   << endl; 
#endif 
		rc =_piCircleSweepTg -> SetTrimMode (Trim) ;

		// PEY 06/03/20 - Launch refresh event on absorbent set to UnGohst features
		_FeatureModeChanged = CATTrue; //To  Refresh visu in OGS/ Body Father - UnGhost Absorbed Elts 
	}

	/*
	CATISpecObject_var spCurve  ,   spSurface; 
	_piCircleSweepTg->GetCurveRef(spCurve); 
	_piCircleSweepTg->GetSurfaceSupport(spSurface); 
	
	if ( !! spCurve && !!spSurface ){
		//Preview
		CATBoolean Bool = PreviewAction(NULL);
	}
	*/ 
	_TrimChanged->InitializeAcquisition();
	return TRUE;
}


//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : Compute Body 
//-----------------------------------------------------------------------------

// ***********************************************
// *** Calcul                                  ***
// ***********************************************
int  CAAGSMCircleSweepTgCmd::ComputeBody()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::ComputeBody) "  << endl; 
#endif 
	int result = 0;

	CATTry  {

		//----------------------------------------------------------------------------------
		//
		// Update Panel 
		//
		//----------------------------------------------------------------------------------
		// UpdatePanelFields();	


		CATISpecObject_var piSpecOnCircleSweepTg = _piCircleSweepTg; 
		//----------------------------------------------------------------------------------
		//
		// -##- Setting attribute default / type for BS 
		//
		//----------------------------------------------------------------------------------

		if (_FeatureModeChanged ){ 
			
			// Trim = Modification 
			int iTrimMode = 0 ; 
			if (NULL!= _piCircleSweepTg) { 
				_piCircleSweepTg ->GetTrimMode(iTrimMode);
				if (iTrimMode ==1 ) { 
					CATMmrFeatureAttributes::SetFeatureType(piSpecOnCircleSweepTg, CATIInputDescription::FeatureType_Modification);
				}
				// No Trim = Creation 	
				else {
					CATMmrFeatureAttributes::SetFeatureType(piSpecOnCircleSweepTg, CATIInputDescription::FeatureType_Creation);
				}
			}
		}
		//----------------------------------------------------------------------------------
		//
		// Uses CATPrtUpdateCom to  update current created/edited feature (Locally  
		//
		//----------------------------------------------------------------------------------


		// Notes : 
		// Uses CATPrtUpdateCom to update the Circle Sweep Tg feature ( manual update mode )
		// But not the whole part 
		// CATPrtUpdateCom also encapsulates interactive error management ( edit / delete, etc...)
		// piSpecOnCombinedCurve= the feature to update, translated into part->update in case of automatic update
		// 0      = Update only the feature / respects update interactive setting ( manual / automatic ) is done on UpdateOKAction 
		// GetMode= creation or modification. Prevents the user from creating a feature in error
		//

		CATPrtUpdateCom *pUpdateCommand =  new CATPrtUpdateCom ( piSpecOnCircleSweepTg ,  
			0                    ,  
			GetMode()       );   


		CATIUpdateError_var UpdateError = piSpecOnCircleSweepTg ;
		CATMfErrUpdate *Error=NULL;
		Error = UpdateError->GetUpdateError();
		if(Error) { 
			// cout << "(CAAGSMCircleSweepTgCmd::ComputeBody) Error Diag = "<< Error -> GetDiagnostic() <<endl ;
			result = 1;
		}

		if (result ==0) { 
			//----------------------------------------------------------------------------------
			//
			// Check Linearity / usefull for absorbant feature(Modification)  inserted  in OGS/HybridBody  
			// !!!! Mandatory for modification features 
			//
			//----------------------------------------------------------------------------------
			CATISpecObject_var spFather = piSpecOnCircleSweepTg->GetFather();
			if ( NULL_var  != spFather )
			{
				spFather -> Release();
				CATIGSMTool *piGSMToolFather = NULL;
				HRESULT rc =spFather->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFather);
				if ( SUCCEEDED(rc) ) { 

					// Manage Absorbed elements
					int IsAnAbsorbentSet = -1 ;
					piGSMToolFather->GetType(IsAnAbsorbentSet) ;
					if ( 1 == IsAnAbsorbentSet ) {
						CATBaseUnknown_var spUnkwnSpec = piSpecOnCircleSweepTg;
						rc = CATMmrLinearBodyServices::Insert(spUnkwnSpec) ; 
					} 

					// PEY 06/03/20 - Launch refresh event on absorbent set to UnGohst features
					// Send Modify Notification To OGS Father - To refresh Visualisation 
					if (_FeatureModeChanged) { 
						// --> Model event for modify  / update visualization 
						CATIModelEvents_var IME(piGSMToolFather);
						if(NULL_var != IME) {
							CATModify info(piGSMToolFather->GetImpl());
							IME->Dispatch(info);
						}
						_FeatureModeChanged = CATFalse; 
					}
					piGSMToolFather->Release() ; piGSMToolFather=NULL; 
				}   
			}
			//
		}

	}


	CATCatch (CATError, Error)  {

		result = 1 ; 
		// Error Panel Displayed
		ErrorPanel("Error", "Error in <CAAGSMCircleSweepTgCmd :: ComputeBody()> ", 1 );

	}

	CATEndTry;

	return result;


}



//------------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd::UpdateOKAction()
//------------------------------------------------------------------------------
int CAAGSMCircleSweepTgCmd::GetContext()
{
	int iSensitivity = 1 ; 
	CATISpecObject_var spSpecCur =_piCircleSweepTg;  

	// Forbid  computation mode 9(Trim) to be changed  at Edit 
	// ->  Launch refresh even on absorbent Set to unGohst features
	// if (!!spSpecCur &&  _mode == 0  &&  GetFeatureToolType( spSpecCur) != 1){ 

#ifdef V5R17_FORBID_MODIFICATION_FEATURE_MODE_ATEDIT 
	if (!!spSpecCur &&  _mode == 0 ) { 
		iSensitivity= 0 ; 
	}
	else {
		iSensitivity= 1  ; 
	} 
#else
	iSensitivity= 1  ; 
#endif 
	return iSensitivity;
}





//------------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd::UpdateOKAction()
//------------------------------------------------------------------------------

CATBoolean CAAGSMCircleSweepTgCmd::UpdateOKAction(void*data)
{
	//----------------------------------------------------------------------------------
	// Uses CATPrtUpdateCom to propagate the update if impact detected 
	//----------------------------------------------------------------------------------
	CATTry  {


		CATString UpdateMode("AutoUpdate"); 
		CATPrtUpdateCom *pUpdateCommand =  new CATPrtUpdateCom (&UpdateMode);

		//     CATISpecObject_var piSpecOnCircleSweepTg = _piCircleSweepTg; 
		//     CATPrtUpdateCom *pUpdateCommand =  new CATPrtUpdateCom (piSpecOnCircleSweepTg ,  
		//     0                    ,  
		//     GetMode()       );   
		//  CATIUpdateError_var UpdateError = _piCircleSweepTg;
		// CATMfErrUpdate *Error=NULL;
		// Error = UpdateError->GetUpdateError();


	}        
	CATCatch (CATError, Error)  {

		// Error Panel Displayed
		ErrorPanel("Error", "Error in <CAAGSMCircleSweepTgCmd :: UpdateOKAction ()> ", 1 );

	}

	CATEndTry;

	//----------------------------------------------------------------------------------
	// DatumMode  ? 
	//----------------------------------------------------------------------------------
	int iCreationMode = GetMode() ; 
	if (iCreationMode ==1 ) { 
		CAAGSMIntegrationCmdServices::ValidateResult(_piCircleSweepTg); 
	}

	//----------------------------------------------------------------------------------
	// Redraw events 
	//----------------------------------------------------------------------------------
	CATIRedrawEvent_var redraw = _piCircleSweepTg;
	if (!!redraw)
	{
		redraw->RedrawParent();
		redraw->Redraw();
	}

	return (CATMMUIPanelStateCmd::UpdateOKAction(data));
}


///////////////////
// General tools //
///////////////////

//-----------------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd : ErrorPanel()
// param iType : =1 ErrorMessage
//				 =2 WarningMessage
//				 =3 InformationMessage
//				 default ErrorMsg
//-----------------------------------------------------------------------------
void CAAGSMCircleSweepTgCmd::ErrorPanel(CATUnicodeString Title, CATUnicodeString Text, int iType )
{
	//Recuperation de la fenetre mere
	CATDlgWindow* FatherWindow=(CATApplicationFrame::GetFrame())->GetApplicationDocument();


	CATDlgStyle Style=CATDlgNfyOK | CATDlgWndModal;
	switch(iType)
	{
	case 1:Style=Style|CATDlgNfyError;break;
	case 2:Style=Style|CATDlgNfyWarning;break;
	case 3:Style=Style|CATDlgNfyInformation;break;
	default:Style=Style|CATDlgNfyError;break;
	}

	//creation du panel
	CATDlgNotify *Panel=new CATDlgNotify(FatherWindow, "ErrorPanel",Style);

	//creation des textes
	int selectedButton = Panel->DisplayBlocked(Text,Title);
	if (selectedButton == 1)
	{
		Panel->RequestDelayedDestruction();
	}
	Panel=NULL;
}





//-----------------------------------------------------------------------------
// CAATmcCombCrvPanelStCmd::IsAValidCurve() : Selection Filter for Curve Agent
// Prevents users from selecting Infinite Elements
//-----------------------------------------------------------------------------

boolean CAAGSMCircleSweepTgCmd::IsAValidCurve(CATDialogAgent * iAgent, void * data)
{

#ifdef DEBUG_GSD_CAASAMPLE
	cout << "(CAAGSMCircleSweepTgCmd::IsAValidCurve) Field = "  <<_ActiveField << endl; 
#endif 

	boolean returnCode  = TRUE;
	CATFeatureImportAgent * featAgent= (CATFeatureImportAgent *) iAgent;

	if (featAgent!=NULL) {

		CATSO * ListOfFeat= featAgent->GetListOfValues(); 

		int newNbOfVal = 0;
		if (ListOfFeat) 
			newNbOfVal = ListOfFeat->GetSize();

		CATPathElement* Path = NULL;
		CATISpecObject_var  piSpecSelected = NULL_var;
		Path = (CATPathElement *) (*ListOfFeat)[newNbOfVal-1];

		if (Path){
			Path -> InitToLeafElement();
			piSpecSelected = Path -> NextFatherElement();
		}

		if (!! piSpecSelected ) {

			// queries the interface CATIGeometricalElement on the Feature selected
			CATIGeometricalElement * piGeometricalElement = NULL;
			HRESULT rc = piSpecSelected->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElement );

			if ( SUCCEEDED(rc) ) {

				// uses GetBodyResult to retrieve the first body
				CATBody_var spiBodyOfCurve = piGeometricalElement->GetBodyResult();

				//prevents the selection of Infinite Elements
				if(!!spiBodyOfCurve) {
					if (spiBodyOfCurve->HasInfiniteGeometry()) {returnCode = FALSE;}		  
				}
				piGeometricalElement->Release(); piGeometricalElement = NULL;
			}
		}
	}
#ifdef DEBUG_GSD_CAASAMPLE
	if (returnCode) 
		cout << "(CAAGSMCircleSweepTgCmd::IsAValidCurve)Return =  TRUE "<< endl; 
	else 
		cout << "(CAAGSMCircleSweepTgCmd::IsAValidCurve)Return =  FALSE  "<< endl; 
#endif 
	return returnCode;
}

void CAAGSMCircleSweepTgCmd::SetUndoTitleToTheCmd()
{
  CATUnicodeString undoTitle = "";
	undoTitle = CATMsgCatalog::BuildMessage("CAAGSMCircleSweepTgCmd", "CircleSweepTgCommand.UndoTitle");
  SetUndoTitle(undoTitle);
}
