// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAV5V6ExtMmrMultiMeasureSetStCmd.cpp 
//    Class managing the dialog command to edit CAAV5V6ExtMultiMeasureSet objects.
//
// Note : CAAV5V6ExtMmrMultiMeasureSetStCmd is the same use case as CAAMmrMultiMeasureSetStCmd. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrMeasureSetStCmd.h"
#include "CAAIV5V6ExtMmrMultiMeasureFactory.h"

// CATMecModUIUseItf Framework
#include "CATPrtUpdateCom.h"  

// CATMecModUseItf
#include "CATIMmiPrtContainer.h"
#include "CATIMmiUseBasicInsertion.h"

// CATMecModLiveUseItf
#include "CATIMmiUsePrtPart.h"
#include "CATIMmiMechanicalFeature.h"

// DialogEngine Framework 
#include "CATDialogState.h"
#include "CATPathElementAgent.h"

// VisualizationInterfaces Framework
#include "CATPathElement.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATCreateExternalObject.h" 

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
#include "CATMMUIStateCommand.h"   // Needed to derive from 

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 

// MecModInterfaces
#include "CATIPrtPart.h"

#endif


CATCreateClass(CAAV5V6ExtMmrMeasureSetStCmd);

//--------------------------------------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
CAAV5V6ExtMmrMeasureSetStCmd::CAAV5V6ExtMmrMeasureSetStCmd():CATMmrStateCommand( "CAAV5V6ExtMmrMeasureSetStCmd" )
#else
//============================================== 
// V5 only
//============================================== 
CAAV5V6ExtMmrMeasureSetStCmd::CAAV5V6ExtMmrMeasureSetStCmd():CATMMUIStateCommand("CAAV5V6ExtMmrMeasureSetStCmd")
#endif
{
}

CAAV5V6ExtMmrMeasureSetStCmd::~CAAV5V6ExtMmrMeasureSetStCmd()
{
}

//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void CAAV5V6ExtMmrMeasureSetStCmd::BuildGraph()
{
  // TODO: Define the StateChart 
  // ---------------------------
  CATDialogState* InitialState = GetInitialState("Insert A MultiMeasureSet");
    
  AddTransition(InitialState, 
                NULL, //FinalState
                Condition((ConditionMethod) &CAAV5V6ExtMmrMeasureSetStCmd::InstantiateNewMechanicalSet), //Instantation must be OK to Close Command
                NULL);
}

//-------------------------------------------------------------------------
// SelectFeature ()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrMeasureSetStCmd::InstantiateNewMechanicalSet( void *data )
{
  CATBoolean RCBool = FALSE;
	HRESULT rc = S_OK;
  
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
	CATIMmiUsePrtPart_var spPart = GetPart();
#else
//============================================== 
// V5 only
//==============================================
	CATIPrtPart_var spPart0 = GetPart();
    CATIMmiUsePrtPart_var spPart = spPart0;
#endif
 
  CATIMmiMechanicalFeature_var spMechFeat = spPart;

  if (spMechFeat != NULL_var)
  {
	// Get container
    CATIMmiPrtContainer_var spPrtCont=NULL_var;
    rc = spMechFeat->GetPrtContainer(spPrtCont);
    if (SUCCEEDED(rc) && spPrtCont != NULL_var)
	{
	  // Create MeasureSet instance
      CAAIV5V6ExtMmrMultiMeasureFactory_var spMmrMechaSetFactory = spPrtCont;
      if (spMmrMechaSetFactory != NULL_var)
      {
        CATBaseUnknown *pMeasureSetInstance = NULL;
        rc = spMmrMechaSetFactory->CreateMmrMeasureSet(pMeasureSetInstance);
        if (SUCCEEDED(rc) && pMeasureSetInstance != NULL)
        {
          // Aggregate the created MeasureSetInstance under the MechanicalPart
		  CATIMmiUseBasicInsertion_var spBasicInsertion = pMeasureSetInstance;

		  if (spBasicInsertion != NULL_var)
		  {
			rc = spBasicInsertion->InsertInside(spMechFeat);  
			if (SUCCEEDED(rc))
			{
			  RCBool = TRUE;

			  //Set as current object
			  if (spPart != NULL_var)
			  {
			    CATIMmiMechanicalFeature_var spMeasureSet = pMeasureSetInstance;
			    rc = spPart->SetInWorkObject(spMeasureSet);
			  }
			  
			  //Launch Update
			  CATPrtUpdateCom *pUpdateCommand = new CATPrtUpdateCom(pMeasureSetInstance);
			}
          }
          pMeasureSetInstance->Release();
		  pMeasureSetInstance = NULL;
        }
      }
    }
  }
  return RCBool;
}
