// COPYRIGHT DASSAULT SYSTEMES 2007 

// Local  Framework
#include "CAAMmrMeasureSetStCmd.h"

// CAAMechanicalModeler.edu framework
#include "CAAIMmrMultiMeasureAndMeasureSetFactory.h"

// MechanicalModelerUI framework
#include "CATMMUIStateCommand.h"

// MechanicalModelerInterface framework
#include "CATIPrtPart.h"

// Dialog Engine framework & Visualization Base
#include "CATDialogState.h"
#include "CATPathElement.h"
#include "CATPathElementAgent.h"

// ObjectSpecsModeler framework
#include "CATISpecObject.h"
#include "CATIDescendants.h"
#include "CATIContainer.h"

// Include System
#include "CATBoolean.h"

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 

CATCreateClass(CAAMmrMeasureSetStCmd);

//--------------------------------------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------------------------------------
CAAMmrMeasureSetStCmd::CAAMmrMeasureSetStCmd():CATMMUIStateCommand( "CAAMmrMeasureSetStCmd" )
{
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

CAAMmrMeasureSetStCmd::~CAAMmrMeasureSetStCmd()
{
}

//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void CAAMmrMeasureSetStCmd::BuildGraph()
{
  // TODO: Define the StateChart 
  // ---------------------------
  CATDialogState* InitialState = GetInitialState("Insert A MmrMeasureSet");
    
  AddTransition(InitialState, 
                NULL, //FinalState
                Condition((ConditionMethod) &CAAMmrMeasureSetStCmd::InstantiateNewMechanicalSet), //Instantation must be OK to Close Command
                NULL);
  }

//-------------------------------------------------------------------------
// SelectFeature ()
//-------------------------------------------------------------------------
CATBoolean CAAMmrMeasureSetStCmd::InstantiateNewMechanicalSet( void *data )
{
  CATBoolean RCBool = FALSE;
  
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  
  CATIPrtPart_var spPart = GetPart();

  if (spPart != NULL_var)
  {
    CATISpecObject_var hPartSO = spPart;
    if (hPartSO != NULL_var)
    {
      CATIContainer_var hFeatCont = hPartSO -> GetFeatContainer();
      if (hFeatCont != NULL_var)
      {
        CAAIMmrMultiMeasureAndMeasureSetFactory *pMmrMechaSetFactory = NULL;
        HRESULT rc = hFeatCont -> QueryInterface( IID_CAAIMmrMultiMeasureAndMeasureSetFactory , (void**) &pMmrMechaSetFactory);
        if(SUCCEEDED(rc) && pMmrMechaSetFactory!=NULL)
        {
          CATISpecObject *pMeasureSetInstance = NULL;
          rc = pMmrMechaSetFactory -> CreateMmrMeasureSet(&pMeasureSetInstance);
          if(SUCCEEDED(rc) && pMeasureSetInstance != NULL)
          {
            //Aggregates the pMultiMeasureInstance created under the first CAAMmrMeasureSet or the MechanicalPart
            CATIDescendants_var hPartDescendants = hPartSO;
            if(!!hPartDescendants)
              hPartDescendants -> Append(pMeasureSetInstance);
            
            RCBool = TRUE;
          }
          pMmrMechaSetFactory -> Release();
          pMmrMechaSetFactory = NULL;
        }
      }
    }
  }
  return RCBool;
}
