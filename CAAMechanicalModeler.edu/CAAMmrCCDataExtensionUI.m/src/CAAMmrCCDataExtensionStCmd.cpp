// COPYRIGHT DASSAULT SYSTEMES 2007 

// Local  Framework
#include "CAAMmrCCDataExtensionStCmd.h"

// CAAMechanicalModeler.edu framework
#include "CAAIMmrCCDataExtension.h"         
#include "CAAMmrAddCCExtension.h"
#include "CAAIMmrCombinedCurve.h"

// MechanicalModelerUI framework
#include "CATMMUIStateCommand.h"

// DialogEngine framework
#include "CATPathElementAgent.h"
#include "CATDialogState.h"

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 

#include "CATPathElement.h"
#include "CATISpecObject.h"

// Include System
#include "CATBoolean.h"

#include "CAAIMmrCCDataExtensionFactory.h"
#include "CATDocument.h"
#include "CATInit.h"
#include "CATILinkableObject.h"
#include "CATIPrtContainer.h"

CATCreateClass(CAAMmrCCDataExtensionStCmd);

//--------------------------------------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------------------------------------
CAAMmrCCDataExtensionStCmd::CAAMmrCCDataExtensionStCmd():CATMMUIStateCommand( "MmrCBTExtFeatureCmd" )
{
  _pPathAgent = NULL;
  _pDACancel = NULL; 
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

CAAMmrCCDataExtensionStCmd::~CAAMmrCCDataExtensionStCmd()
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
void CAAMmrCCDataExtensionStCmd::BuildGraph()
{
  //Initialize DataMembers
  _pPathAgent = new CATPathElementAgent("Extend A CombinedCurve", "CAAIMmrCombinedCurve");
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
  CATDialogState* InitialState = GetInitialState("Select A CombinedCurve As Your Base Feature To Extend");
    
  InitialState->AddDialogAgent(_pPathAgent);
  InitialState->AddDialogAgent(_pDACancel);

  AddTransition(InitialState, NULL, IsOutputSetCondition(_pPathAgent), 
    Action((ActionMethod) &CAAMmrCCDataExtensionStCmd::SelectFeatureAndExtend) );
}

//-------------------------------------------------------------------------
// OkAction ()
//-------------------------------------------------------------------------
CATBoolean CAAMmrCCDataExtensionStCmd::OkAction( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// Cancel ()
//-------------------------------------------------------------------------
CATBoolean CAAMmrCCDataExtensionStCmd::Cancel( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// SelectFeature ()
//-------------------------------------------------------------------------
CATBoolean CAAMmrCCDataExtensionStCmd::SelectFeatureAndExtend( void *data )
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
 

  //Rajout pour test
	CATILinkableObject* pIlink = NULL;
  HRESULT rc = pSelection->QueryInterface( IID_CATILinkableObject, ( void**) &pIlink );
	if (pIlink)
	{
		CATDocument * pDoc = pIlink -> GetDocument();
		if (pDoc)
		{
	    CATInit_var spiInitOnDoc(pDoc);
      if (NULL_var != spiInitOnDoc) 
			{
        // retrieves the root container
        CATIPrtContainer *spiPrtCont = (CATIPrtContainer*) spiInitOnDoc->GetRootContainer("CATIPrtContainer");	
        if ( NULL == spiPrtCont )
        {
          return FALSE; 
        }
	      // create a MmrCCDataExtension factory
        CAAIMmrCCDataExtensionFactory *pDataExtensionFactory = NULL;
        rc = spiPrtCont->QueryInterface( IID_CAAIMmrCCDataExtensionFactory , ( void**) &pDataExtensionFactory );
        if ( FAILED ( rc ) )
        {
          
          return FALSE;
        }

        // No need container more
        spiPrtCont->Release();

  
	      // updating the part
				/*
        int PartUpdate = spSpecOnPart->Update();
        if ( PartUpdate == 0 )
          cerr << "  part update OK " << endl;
        else
          cerr << "  part update KO " << endl;
*/

        // creates MmrCCDataExtension Instance
        CAAIMmrCCDataExtension *pMmrCCDataExtension = NULL;

        rc = pDataExtensionFactory -> CreateMmrCCDataExtension(pSelection, &pMmrCCDataExtension);
        pDataExtensionFactory -> Release();
        pDataExtensionFactory = NULL ;
			}
		}
		pIlink -> Release();
		pIlink = NULL;
	}

  CAAIMmrCCDataExtension *piMmrCCDataExtension = NULL;
  rc = ::CAAMmrAddCCExtension(pSelection, &piMmrCCDataExtension);
  if (FAILED(rc)) RCBool = FALSE;

  if ( NULL != piMmrCCDataExtension )
  {
     piMmrCCDataExtension -> Release();
     piMmrCCDataExtension = NULL;
  }
  
  return RCBool ;
}

