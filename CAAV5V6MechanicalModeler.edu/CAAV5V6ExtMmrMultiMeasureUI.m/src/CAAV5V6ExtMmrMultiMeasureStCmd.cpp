// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAV5V6ExtMmrMultiMeasureStCmd.cpp 
//    Class managing the dialog command to edit CAAV5V6ExtMultiMeasure objects.
//
// Note : CAAV5V6ExtMmrMultiMeasureStCmd is the same use case as CAAMmrMultiMeasureCmd. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CATIAV5Level.h"

// Local CAAMechanicalModelerExtend.edu Framework
#include "CAAV5V6ExtMmrMultiMeasureStCmd.h"
#include "CAAIV5V6ExtMmrMultiMeasure.h"         
#include "CAAIV5V6ExtMmrMultiMeasureFactory.h"

// CATMecModUseItf Framework
#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiUseBasicInsertion.h"
#include "CATIMmiPrtContainer.h"

// CATMecModLiveUseItf
#include "CATIMmiUsePrtPart.h"
#include "CATIMmiMechanicalFeature.h"
#include "CATLISTV_CATIMmiMechanicalFeature.h"

// CATMecModExtendItf
#include "CATIMmiMechanicalSetServices.h"
#include "CATMmiExtendServicesFactory.h"

// CATMecModUIUseItf Framework
#include "CATPrtUpdateCom.h"   

// DialogEngine Framework 
#include "CATDialogState.h"
#include "CATPathElementAgent.h"

// VisualizationInterfaces Framework for V6
// VisualizationBase Framework for V5
#include "CATPathElement.h"

// System Framemwork
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATCreateExternalObject.h" 
#include "CATLISTV_CATBaseUnknown.h"

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
#include "CATMMUIPanelStateCmd.h"   // Needed to derive from
#endif


CATCreateClass(CAAV5V6ExtMmrMultiMeasureStCmd);

//--------------------------------------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
CAAV5V6ExtMmrMultiMeasureStCmd::CAAV5V6ExtMmrMultiMeasureStCmd(CAAIV5V6ExtMmrMultiMeasure *piMmrMultiMeasure):
CATMmrStateCommand( "CAAV5V6ExtMmrMultiMeasureStCmd" ),
  _pPathAgent (NULL),
  _piMmrMultiMeasure  (NULL)
#else
//============================================== 
// V5 only
//============================================== 
CAAV5V6ExtMmrMultiMeasureStCmd::CAAV5V6ExtMmrMultiMeasureStCmd(CAAIV5V6ExtMmrMultiMeasure *piMmrMultiMeasure):
CATMMUIStateCommand( "CAAV5V6ExtMmrMultiMeasureStCmd" ),
  _pPathAgent (NULL),
  _piMmrMultiMeasure  (NULL)
#endif

{
  _mode = 1; // creation mode

  if(piMmrMultiMeasure!=NULL)
  {
    //Edition Mode
    _mode = 0; 
    // Memorises the MultiMeasure.
    _piMmrMultiMeasure = piMmrMultiMeasure;
    _piMmrMultiMeasure->AddRef();
  }
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

CAAV5V6ExtMmrMultiMeasureStCmd::~CAAV5V6ExtMmrMultiMeasureStCmd()
{
  // Releases member data pointers before leaving.
  if ( _piMmrMultiMeasure != NULL )
	{
    _piMmrMultiMeasure->Release();
    _piMmrMultiMeasure = NULL; 
  }
  if(_pPathAgent != NULL)
	{
    _pPathAgent -> Release();
    _pPathAgent = NULL;
  }
}

//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void CAAV5V6ExtMmrMultiMeasureStCmd::BuildGraph()
{
  //Initialize DataMembers
  _pPathAgent = new CATPathElementAgent("SelectFeature", "CATIMmiUseGeometricalElement");
  if ( _pPathAgent == NULL ) 
	{
    return;
  }
  _pPathAgent->AddElementType("CATIBRepAccess");
  _pPathAgent->SetBehavior(CATDlgEngWithPSOHSO | 
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
      Action((ActionMethod) &CAAV5V6ExtMmrMultiMeasureStCmd::ComputeLength) );
  }
  else // Edition Mode
  {
    // TODO: Define the StateChart 
    // ---------------------------
    CATDialogState* InitialState = GetInitialState("Choose your New Input");

    InitialState->AddDialogAgent(_pPathAgent);
    
    AddTransition(InitialState, NULL, IsOutputSetCondition(_pPathAgent), 
      Action((ActionMethod) &CAAV5V6ExtMmrMultiMeasureStCmd::ReplaceInput) );
  }
}

//-------------------------------------------------------------------------
// OkAction ()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrMultiMeasureStCmd::OkAction( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// Cancel ()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrMultiMeasureStCmd::Cancel( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  return TRUE;
}

//-------------------------------------------------------------------------
// ComputeLength()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrMultiMeasureStCmd::ComputeLength( void *data )
{
  CATBoolean RCBool = FALSE;
	HRESULT rc = S_OK;

  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------
  if (_pPathAgent == NULL) 
    return RCBool;

  CATPathElement* pPath = _pPathAgent->GetValue();
  if (pPath == NULL) 
    return RCBool;

  if (pPath->GetSize() <= 0)
    return RCBool;

  pPath->InitToLeafElement();

  CATBaseUnknown* pSelection = pPath->NextFatherElement();
  if (pSelection == NULL) 
    return RCBool;

  CATIMmiUsePrtPart *piPart = NULL;
  piPart = (CATIMmiUsePrtPart *)(pPath->FindElement(IID_CATIMmiUsePrtPart));

  if (piPart != NULL)
  {
    //Get container
	CATIMmiMechanicalFeature_var spMechPart = piPart;

	if (spMechPart != NULL_var)
	{
      CATIMmiPrtContainer_var spPrtCont=NULL_var;
      rc = spMechPart->GetPrtContainer(spPrtCont);
      if (SUCCEEDED(rc) && spPrtCont != NULL_var)
	  {
        CAAIV5V6ExtMmrMultiMeasureFactory_var spMmrMultiMeasureFactory = spPrtCont;
        if (spMmrMultiMeasureFactory != NULL_var)
        {
		  //Create a MultiMeasure instance
          CATBaseUnknown *pMultiMeasureInstance = NULL;
          rc = spMmrMultiMeasureFactory->CreateMmrMultiMeasure(pSelection, pMultiMeasureInstance);

          if (SUCCEEDED(rc) && pMultiMeasureInstance!= NULL)
          {
            //Aggregate the created MultiMeasureInstance under the the current CAAMmrMeasureSet or the last one 
		    CATIMmiMechanicalFeature_var spMeasureSet = NULL_var;
						
			// Create CATIMmiMechanicalSetServices component
	        CATIMmiMechanicalSetServices *piMechSetServices = NULL;  
            rc = CATMmiExtendServicesFactory::CreateMechanicalSetServicesAccess(piMechSetServices);
            
			if (SUCCEEDED(rc) && piMechSetServices)
			{
			  // Get list of aggregated mechanical sets 
			  CATListValCATIMmiMechanicalFeature_var hListeOfAggregatedSet;
			  rc = piMechSetServices->GetAggregatedMechanicalSets(piPart, hListeOfAggregatedSet);

			  // Get In Work object
              CATIMmiMechanicalFeature_var spInWork = NULL_var;
			  rc = piPart->GetInWorkObject(spInWork);

			  // Loop until wil  find in work object
			  for (int i=1; i<=hListeOfAggregatedSet.Size(); i++)
			  {
                CATIMmiMechanicalFeature_var spMeasureSetLoop = hListeOfAggregatedSet[i];

				if (spInWork == spMeasureSetLoop)
				{
                  spMeasureSet = spMeasureSetLoop;
				  break;
				}
				// if not current set, we take the last one
				else if (spMeasureSet == NULL_var && i == hListeOfAggregatedSet.Size())
                   spMeasureSet = spMeasureSetLoop;
			  }
			  piMechSetServices->Release();
			}
              
						
			if (spMeasureSet == NULL_var)
			{
              // if there isn't any MeasureSet in the Part, create a MeasureSet to aggregate in it
              CATBaseUnknown *pMeasureSetInstance = NULL;
              rc = spMmrMultiMeasureFactory->CreateMmrMeasureSet(pMeasureSetInstance);
              if (SUCCEEDED(rc) && pMeasureSetInstance != NULL)
              {
                //Aggregate the created MeasureSetInstance under the MechanicalPart
			  	CATIMmiUseBasicInsertion_var spBasicInsertion = pMeasureSetInstance;
				if (spBasicInsertion != NULL_var)
				{
				  rc = spBasicInsertion->InsertInside(spMechPart);
				  if (SUCCEEDED(rc))
				  {
					spMeasureSet = pMeasureSetInstance;

					//Set the new MeasureSet as current object
					rc = piPart->SetInWorkObject(spMeasureSet);
				  }
				}
                pMeasureSetInstance->Release();
                pMeasureSetInstance = NULL; 
			  }
		    }
            
			if (spMeasureSet != NULL_var)
			{
              CATIMmiUseBasicInsertion_var spBasicInsertion = pMultiMeasureInstance;
			  if (spBasicInsertion != NULL_var)
			  { 
                rc = spBasicInsertion->InsertInside(spMeasureSet);
			    if (SUCCEEDED(rc))
				  RCBool = TRUE;
			  }
			}

			//Launch Update, the mode is creation mode
			if (SUCCEEDED(rc))
			  CATPrtUpdateCom *pUpdateCommand = new CATPrtUpdateCom(spMeasureSet);

			pMultiMeasureInstance->Release();
			pMultiMeasureInstance = NULL;
		  }
        }
      }
    }
    piPart->Release();
    piPart = NULL;
  }

  return RCBool;
}

//-------------------------------------------------------------------------
// ReplaceInput()
//-------------------------------------------------------------------------
CATBoolean CAAV5V6ExtMmrMultiMeasureStCmd::ReplaceInput( void *data )
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
	{
     RCBool = TRUE;

		//Launch Update in edition mode
		CATPrtUpdateCom *pUpdateCommand = new CATPrtUpdateCom(_piMmrMultiMeasure, 1, 1);
	}

	
  return RCBool;
}
