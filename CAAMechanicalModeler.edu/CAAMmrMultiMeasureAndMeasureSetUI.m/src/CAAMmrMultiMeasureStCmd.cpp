// COPYRIGHT DASSAULT SYSTEMES 2007 

// Local  Framework
#include "CAAMmrMultiMeasureStCmd.h"

// CAAMechanicalModeler.edu framework
#include "CAAIMmrMultiMeasure.h"         
#include "CAAIMmrMultiMeasureAndMeasureSetFactory.h"
#include "CATIGeometricalElement.h"

// MechanicalModelerUI framework
#include "CATMMUIStateCommand.h"

// MechanicalModelerInterface framework
#include "CATIPrtPart.h"
#include "CATIReplace.h"

// Dialog Engine framework & Visualization Base
#include "CATDialogState.h"
#include "CATPathElement.h"
#include "CATPathElementAgent.h"

// ObjectSpecsModeler framework
#include "CATISpecObject.h"
#include "CATIDescendants.h"
#include "CATIContainer.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"

// Include System
#include "CATBoolean.h"
#include "CATUnicodeString.h"

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h" 

CATCreateClass(CAAMmrMultiMeasureStCmd);

//--------------------------------------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------------------------------------
CAAMmrMultiMeasureStCmd::CAAMmrMultiMeasureStCmd(CAAIMmrMultiMeasure *piMmrMultiMeasure):
CATMMUIStateCommand( "CAAMmrMultiMeasureStCmd" ),
  _pPathAgent (NULL),
  _piMmrMultiMeasure  (NULL)
{
  _mode = 1; // creation mode

  if(piMmrMultiMeasure!=NULL)
  {
    //Edition Mode
    _mode = 0; 
    // Memorises the MultiMeasure.
    _piMmrMultiMeasure = piMmrMultiMeasure;
    _piMmrMultiMeasure -> AddRef();
  }
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

CAAMmrMultiMeasureStCmd::~CAAMmrMultiMeasureStCmd()
{
  // Releases member data pointers before leaving.
  if ( _piMmrMultiMeasure != NULL ){
    _piMmrMultiMeasure -> Release();
    _piMmrMultiMeasure       = NULL ;
  }
  if(_pPathAgent != NULL){
    _pPathAgent -> Release();
    _pPathAgent = NULL;
  }
}

//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void CAAMmrMultiMeasureStCmd::BuildGraph()
{
  //Initialize DataMembers
  _pPathAgent = new CATPathElementAgent("SelectFeature", "CATIGeometricalElement");
  if ( _pPathAgent == NULL ) {
    return;
  }
  _pPathAgent -> AddElementType ("CATIBRepAccess");
  _pPathAgent -> SetBehavior(CATDlgEngWithPSOHSO | 
                           CATDlgEngWithPrevaluation |
                           CATDlgEngWithoutUndo );
  _pPathAgent->InitializeAcquisition();
  
  if(_mode == 1) // Creation Mode
  {  
    // TODO: Define the StateChart 
    // ---------------------------

    CATDialogState* InitialState = GetInitialState("Select A GeometricalElement");

    InitialState->AddDialogAgent(_pPathAgent);
    
    AddTransition(InitialState, NULL, IsOutputSetCondition(_pPathAgent), 
      Action((ActionMethod) &CAAMmrMultiMeasureStCmd::ComputeLength) );
  }
  else // Edition Mode
  {
    // TODO: Define the StateChart 
    // ---------------------------
    CATDialogState* InitialState = GetInitialState("Choose your New Input");

    InitialState->AddDialogAgent(_pPathAgent);
    
    AddTransition(InitialState, NULL, IsOutputSetCondition(_pPathAgent), 
      Action((ActionMethod) &CAAMmrMultiMeasureStCmd::ReplaceInput) );
  }
}

//-------------------------------------------------------------------------
// OkAction ()
//-------------------------------------------------------------------------
CATBoolean CAAMmrMultiMeasureStCmd::OkAction( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// Cancel ()
//-------------------------------------------------------------------------
CATBoolean CAAMmrMultiMeasureStCmd::Cancel( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// ComputeLength()
//-------------------------------------------------------------------------
CATBoolean CAAMmrMultiMeasureStCmd::ComputeLength( void *data )
{
  CATBoolean RCBool = FALSE;
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  if(_pPathAgent == NULL) 
    return RCBool;

  CATPathElement* pPath = _pPathAgent->GetValue();
  if(pPath == NULL) 
    return RCBool;

  if ( pPath->GetSize() <= 0 ) {
    return RCBool;
  }

  pPath -> InitToLeafElement();

  CATBaseUnknown* pSelection = pPath -> NextFatherElement();
  if ( pSelection == NULL ) 
    return RCBool;

  CATIPrtPart * piPart = NULL;
  piPart = (CATIPrtPart *)(pPath ->  FindElement(IID_CATIPrtPart));

  if (piPart != NULL)
  {
    CATISpecObject_var hPartSO = piPart;
    if (hPartSO != NULL_var)
    {
      CATIContainer_var hFeatCont = hPartSO -> GetFeatContainer();
      if (hFeatCont != NULL_var)
      {
        CAAIMmrMultiMeasureAndMeasureSetFactory *pMmrMultiMeasureFactory = NULL;
        HRESULT rc = hFeatCont -> QueryInterface( IID_CAAIMmrMultiMeasureAndMeasureSetFactory , (void**) &pMmrMultiMeasureFactory);
        if(SUCCEEDED(rc) && pMmrMultiMeasureFactory!=NULL)
        {
          CATISpecObject * pMultiMeasureInstance = NULL;

          //Creates a MultiMeasure instance

          rc = pMmrMultiMeasureFactory -> CreateMmrMultiMeasure (pSelection ,&pMultiMeasureInstance);
          if (SUCCEEDED(rc) && pMultiMeasureInstance!= NULL)
          {
            //Aggregates the pMultiMeasureInstance created under the first CAAMmrMeasureSet or the MechanicalPart
            CATIDescendants_var hPartDescendants = hPartSO;
            if(!!hPartDescendants)
            {
              CATListValCATISpecObject_var hListeOfAggregatedSet;
              hPartDescendants -> GetDirectChildren ("CATISpecObject",hListeOfAggregatedSet);

              CATIDescendants_var hDescendantsOnMmrMeasureSet;

              for (int i = 0; i < hListeOfAggregatedSet.Size(); i++)
              {
                CATBaseUnknown* pAggreagatedSet = NULL;
                hListeOfAggregatedSet[i+1] -> QueryInterface( IID_CATBaseUnknown, (void**) &pAggreagatedSet );
                if(pAggreagatedSet != NULL)
                {
                  if(pAggreagatedSet -> IsAKindOf("CAAMmrMeasureSet"))
                  {
                    hDescendantsOnMmrMeasureSet = hListeOfAggregatedSet[i+1];
                    break;
                  }
                  pAggreagatedSet -> Release();
                  pAggreagatedSet = NULL;
                }
              }
              if(!!hDescendantsOnMmrMeasureSet)
                hDescendantsOnMmrMeasureSet -> Append(pMultiMeasureInstance);
              else
              {
                // if There is not any MeasureSet in the Part creates à MeasureSet
                // And aggregate in it!
                
                CATISpecObject *pMeasureSetInstance = NULL;
                rc = pMmrMultiMeasureFactory -> CreateMmrMeasureSet(&pMeasureSetInstance);
                if(SUCCEEDED(rc) && pMeasureSetInstance != NULL)
                {
                  {
                    //Aggregates the pMultiMeasureInstance created under the first CAAMmrMeasureSet or the MechanicalPart
                    CATIDescendants_var hPartDescendants = hPartSO;
                    if(!!hPartDescendants)
                      hPartDescendants -> Append(pMeasureSetInstance);
            
                    hDescendantsOnMmrMeasureSet = pMeasureSetInstance;

                    if (!!hDescendantsOnMmrMeasureSet)
                    {
                      hDescendantsOnMmrMeasureSet -> Append(pMultiMeasureInstance);
                      RCBool = TRUE;
                    }
                  }
                }
              }
            }
          }
          pMmrMultiMeasureFactory -> Release();
          pMmrMultiMeasureFactory = NULL;
        }
      }
    }
    piPart -> Release();
    piPart = NULL;
  }

  return RCBool;
}

//-------------------------------------------------------------------------
// ReplaceInput()
//-------------------------------------------------------------------------
CATBoolean CAAMmrMultiMeasureStCmd::ReplaceInput( void *data )
{
  CATBoolean RCBool = FALSE;
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  if(_pPathAgent == NULL) 
    return RCBool;

  CATPathElement* pPath = _pPathAgent->GetValue();
  if(pPath == NULL) 
    return RCBool;

  if ( pPath->GetSize() <= 0 ) {
    return RCBool;
  }

  pPath -> InitToLeafElement();

  CATBaseUnknown* pSelection = pPath -> NextFatherElement();
  if ( pSelection == NULL ) 
    return RCBool;

  HRESULT rc=S_OK;
	if (_piMmrMultiMeasure)
    rc= _piMmrMultiMeasure->SetInputGeomFeature(pSelection);
	
  if (SUCCEEDED(rc))
     RCBool = TRUE;

  return RCBool;
}
