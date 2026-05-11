// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAV5V6ExtMmrCCDataExtensionStCmd :
// Manages the instantiation of the data extension
// 
// Note :  CAAV5V6ExtMmrAddCCExtension is the same use case as  CAAMmrAddCCExtension. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//=================================================================================================

#include "CATIAV5Level.h"

// CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrCCDataExtensionStCmd.h"
#include "CAAIV5V6ExtMmrCCDataExtension.h"         
#include "CAAV5V6ExtMmrAddCCExtension.h"
#include "CAAIV5V6ExtMmrCombinedCurve.h"

// DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogState.h"

// VisualizationBase Framework for V5
// VisualizationInterfaces Framework in V6
#include "CATPathElement.h"

// System Framework
#include "CATCreateExternalObject.h" 
#include "CATBoolean.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// CATMecModUIExtendItf Framework
#include "CATMmrPanelStateCmd.h"   // Needed to derive from 
#else
//============================================== 
// V5 only
//============================================== 
// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"
#endif

CATCreateClass(CAAV5V6ExtMmrCCDataExtensionStCmd);


//--------------------------------------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
CAAV5V6ExtMmrCCDataExtensionStCmd::CAAV5V6ExtMmrCCDataExtensionStCmd():CATMmrStateCommand( "V5V6ExtMmrCBTExtFeatureCmd" )
#else
//============================================== 
// V5 only
//============================================== 
CAAV5V6ExtMmrCCDataExtensionStCmd::CAAV5V6ExtMmrCCDataExtensionStCmd():CATMMUIStateCommand("V5V6ExtMmrCBTExtFeatureCmd")
#endif
{
  _pPathAgent = NULL;
  _pDACancel = NULL; 
}


//--------------------------------------------------------------------------------------------------------

CAAV5V6ExtMmrCCDataExtensionStCmd::~CAAV5V6ExtMmrCCDataExtensionStCmd()
{
  if(_pPathAgent != NULL){
    _pPathAgent -> Release();
    _pPathAgent = NULL;
  }
  if(_pDACancel != NULL){
    _pDACancel -> Release();
    _pDACancel = NULL;
  }
}

//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void CAAV5V6ExtMmrCCDataExtensionStCmd::BuildGraph()
{
  //Initialize DataMembers
  _pPathAgent = new CATPathElementAgent("Extend A V5V6ExtCombinedCurve", "CAAIV5V6ExtMmrCombinedCurve");
  if ( _pPathAgent == NULL ) {
    return;
  }
  _pPathAgent->SetBehavior(CATDlgEngWithPSOHSO | 
                           CATDlgEngWithPrevaluation |
                           CATDlgEngWithoutUndo );
  _pPathAgent->InitializeAcquisition();
  
  // Definition of _pDACancel
  _pDACancel = new CATDialogAgent("Cancel");
  if (_pDACancel == NULL) {
    return;
  }
  // TODO: Define the StateChart 
  // ---------------------------
  CATDialogState* InitialState = GetInitialState("Select A V5V6ExtCombinedCurve As Your Base Feature To Extend");
    
  InitialState->AddDialogAgent(_pPathAgent);
  InitialState->AddDialogAgent(_pDACancel);

  AddTransition(InitialState, NULL, IsOutputSetCondition(_pPathAgent), 
    Action((ActionMethod) &CAAV5V6ExtMmrCCDataExtensionStCmd::SelectFeatureAndExtend) );
}

//-------------------------------------------------------------------------
// OkAction ()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCCDataExtensionStCmd::OkAction( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// Cancel ()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCCDataExtensionStCmd::Cancel( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// SelectFeature ()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrCCDataExtensionStCmd::SelectFeatureAndExtend( void *data )
{
  CATBoolean RCBool = TRUE;
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  if(_pPathAgent == NULL) 
    return FALSE;

  CATPathElement* pPath = _pPathAgent->GetValue();
  if(pPath == NULL) 
    return FALSE;

  if ( pPath->GetSize() <= 0 ) {
    return FALSE;
  }

  CATBaseUnknown* pSelection = ( *pPath )[pPath->GetSize()-1];
  if ( pSelection == NULL ) 
    return FALSE;
 
  CAAIV5V6ExtMmrCCDataExtension *piMmrCCDataExtension = NULL;
  HRESULT rc = ::CAAV5V6ExtMmrAddCCExtension(pSelection, &piMmrCCDataExtension);
  if (FAILED(rc)) RCBool = FALSE;

  if ( NULL != piMmrCCDataExtension )
  {
     piMmrCCDataExtension -> Release();
     piMmrCCDataExtension = NULL;
  }
  
  return RCBool ;
}
