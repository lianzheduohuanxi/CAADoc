// COPYRIGHT Dassault Systemes 2007
//===================================================================
// CAAV5V6MmrPartWksFreezeUnfreezeCmd.cpp
// The state chart based command: CAAV5V6MmrPartWksFreezeUnfreezeCmd
//
// Note : CAAV5V6MmrPartWksFreezeUnfreezeCmd is the same source as CAAMmrPartWksFreezeUnfreezeCmd. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//===================================================================
// Mission	:	The Use Case retrieves the freeze status of an Internal Copy with Link and 
//              switches its state (Freeze/Unfreeze)
//              An Internal Copy is a feature copied within a 3D Shape. 
//              It can be frozen while a feature copied across 3D Shapes (External Reference) 
//              cannot be frozen
//              The Use Case is executed through an Interactive State Command defined in this cpp, 
//              integrated in the Spec Tree toolbar, a Part Workshop Add-in within CATIA. 
//              On activating this state command, it prompts an end-user to select a copied feature 
//              within the product hierarchy. 
//              The Selection Agent associated with the State Command restricts the user-selection to 
//              only those entities which implement CATIMmiResultFreeze. An Internal Copy is one of them.
//              The default state of an Internal Copy is Unfrozen. In this state, the copied geometry 
//              is synchronized with its source. On freezing it, the link between the source and its copy, 
//              is deactivated, implying that the geometry of the copied feature is not recomputed, 
//              in response to any modification in the source geometry. 
//              On unfreezing, this link is restored and the copied feature is yet again in sync 
//              with its source.
//              It is significant to note that immediately after an Unfreeze, an explicit call to the 
//              Update is essential to achieve synchronization. 
//              However, any further modifications in the source geometry, are automatically 
//              reflected in the copied feature, since it is implicitly handled by the Update mechanism.
//				   
//============================================================================================
// Steps			1- Define a StateChart Command with the BuildGraph method
//					   1-1- Create a PathElement agent to select an entity (copied feature)
//						    from the spec tree. 
//						    Restrict the selection to only those entities which implement
//							CATIMmiResultFreeze
//					   1-2- Create a state, which prompts the user to select an entity of the type
//							defined above
//					   1-3- Associate this state with the path element agent, previously defined
//					   1-4- Associate an incoming Transition to the same state, in response to 
//						    the selection agent modification
//						    The action associated with this transition is to call a routine 
//						    which seeks the freeze status of the selected feature and switches it
//					2- Action Method triggered on an Incoming Transition associated with the State Command
//						2-1- Retrieve the selected as a CATPathElement object, from the selection agent
//						2-2- Seek the last element of this path, which represents just the copied feature
//						2-3- Seek the CATIMmiResultFreeze* type on this feature
//						2-4- Check for its freeze status
//							2-4-a- If frozen, unfreeze the feature
//							2-4-b- Update the feature
//								2-4-b-1- Seek the CATIUseEntity handler on the feature
//								2-5-b-2- Update the feature, to recompute its geometry
//							2-4-b- If unfrozen, freeze the feature
//
//===================================================================

#include "CATIAV5Level.h"

#include "CAAV5V6MmrPartWksFreezeUnfreezeCmd.h"

// MecModInterfaces Framework for V5
// CATMecModUseItf Framework for V6
#include "CATIMmiResultFreeze.h"

// Visualizationbase  Framework for V5
// VisualizationInterfaces  Framework for V6
#include "CATPathElement.h"

//Dialog Engine Framework
#include "CATDialogState.h"
#include "CATDialogTransition.h"
#include "CATPathElementAgent.h"

// System Framework
#include "CATCreateExternalObject.h"
CATCreateClass( CAAV5V6MmrPartWksFreezeUnfreezeCmd);

// C++ Standard library
#include "iostream.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// DataCommonProtocolUse Framework
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

#else
//============================================== 
// V5 only
//==============================================

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

#endif

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAV5V6MmrPartWksFreezeUnfreezeCmd::CAAV5V6MmrPartWksFreezeUnfreezeCmd() :
  CATStateCommand ("CAAV5V6MmrPartWksFreezeUnfreezeCmdId"),
  _daObjectToSelect(NULL) 
{
	cout <<" CAAV5V6MmrPartWksFreezeUnfreezeCmd::CAAV5V6MmrPartWksFreezeUnfreezeCmd" << endl;
} 

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAV5V6MmrPartWksFreezeUnfreezeCmd::~CAAV5V6MmrPartWksFreezeUnfreezeCmd()
{
	cout <<" CAAV5V6MmrPartWksFreezeUnfreezeCmd::~CAAV5V6MmrPartWksFreezeUnfreezeCmd" << endl;
	// Delete the Selection Agent
	if (NULL != _daObjectToSelect) 
	{
		_daObjectToSelect->RequestDelayedDestruction();
		_daObjectToSelect = NULL;
	}
}

//-------------------------------------------------------------------------
// BuildGraph()
// 1- Defining a StateChart Command
//-------------------------------------------------------------------------
void CAAV5V6MmrPartWksFreezeUnfreezeCmd::BuildGraph()
{
	// Statechart definition
	cout << "CAAV5V6MmrPartWksFreezeUnfreezeCmd::BuildGraph" << endl;

	// 1-1- Create a PathElement Selection agent to select an entity from the spec tree,
	// a copied feature which necessarily implements CATIMmiResultFreeze
	// Valid features are copies of Point, Line, Plane, Curve
	// Invalid features are copies of PartBody, Geometrical Set, Sketch
	_daObjectToSelect = new CATPathElementAgent("SelCopiedFeature");
	_daObjectToSelect->AddElementType(IID_CATIMmiResultFreeze);
 
	// Defining the Agent behavior
	_daObjectToSelect->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation | CATDlgEngRepeat);
 
	// 1-2- Create the first and only state, that of selecting the copied feature
	CATDialogState* stGetObjState = GetInitialState("stGetObjStateId");
	// 1-3- Associate this state with a dialog agent, previously defined
	stGetObjState->AddDialogAgent(_daObjectToSelect);

	// 1-4- Associate an Incoming Transition to the same state, in response to the selection
	//      agent modification
	CATDialogTransition* pTransition1 = AddTransition(stGetObjState,
													  stGetObjState,
													  IsLastModifiedAgentCondition(_daObjectToSelect),
													  Action((ActionMethod) & CAAV5V6MmrPartWksFreezeUnfreezeCmd::FreezeOrUnfreeze)
													  );
}

// 2- Action Method triggered on an Incoming Transition associated with the State Command
//    Retrieve the selected entity and process it
//    The processing involves seeking the freeze status of the selected entity and switching it
CATBoolean CAAV5V6MmrPartWksFreezeUnfreezeCmd::FreezeOrUnfreeze(void* iData)
{
	cout <<" CAAV5V6MmrPartWksFreezeUnfreezeCmd::FreezeOrUnfreeze" << endl;
	// 2-1- Retrieve the selected entity, as a CATPathElement object from the selection agent
	// This object contains the selected entity with all its ancestors up the product model hierarchy
	// until and including Root
	CATPathElement* pathModel = _daObjectToSelect->GetValue();
	CATBaseUnknown* pSelectedObj = NULL;

	if ((NULL != pathModel)&&(pathModel->GetSize()>0))
	{
	    // 2-2- Seek the last element of the path. It represents just the copied feature
		pSelectedObj = (*pathModel)[pathModel->GetSize()-1];
		if (NULL == pSelectedObj)
			return TRUE ;

	    // 2-3- Seek the CATIMmiResultFreeze* type on the copied feature
		CATIMmiResultFreeze* pIMmiResultFreezeOnSelFeat = NULL;
		HRESULT hr = pSelectedObj->QueryInterface(IID_CATIMmiResultFreeze,(void**)&pIMmiResultFreezeOnSelFeat);
					           
		if (SUCCEEDED(hr))
		{
			cout << "Copied feature implements CATIMmrResultFreeze" << endl;
	        // 2-4- Check for the freeze status of the copied feature
			CATBoolean FreezeStatus = pIMmiResultFreezeOnSelFeat->IsFrozen();
			if (TRUE == FreezeStatus)
			{
		        // 2-4-a- If frozen, unfreeze the selected Feature
				hr = pIMmiResultFreezeOnSelFeat->Unfreeze();
				if ( SUCCEEDED(hr) )
				{
                    cout << "Feature is unfrozen " << endl;
		            // 2-4-b- Update the feature
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
			        // 2-4-b-1- Seek the CATIUseEntity handler type on the feature
					CATIUseEntity *pUseEntityOnSelFeat= NULL;
                    hr = pIMmiResultFreezeOnSelFeat->QueryInterface(IID_CATIUseEntity , (void**)& pUseEntityOnSelFeat);
	                if ( SUCCEEDED(hr) )
	                {
	                   hr = DataCommonProtocolServices::Update(pUseEntityOnSelFeat);
	                   pUseEntityOnSelFeat->Release(); pUseEntityOnSelFeat = NULL ;
	                } 
#else
//============================================== 
// V5 only
//==============================================
					CATISpecObject_var spSpecObjOnSelFeat = pIMmiResultFreezeOnSelFeat;
 
				    CATTry	
				    {
			           // 2-4-b-2- Update the feature to recompute its geometry
				       spSpecObjOnSelFeat->Update(); 
					   cout << "Feature is right updated" << endl;	
				    }
				    CATCatch(CATError,error)			
				    {
					   cout << "update error:" << (error->GetNLSMessage()).ConvertToChar() << endl;
					   Flush(error);		
				    }
				    CATEndTry
#endif
				}
			}
			else
			{
		       // 2-4-b- If unfrozen, freeze the feature
				hr = pIMmiResultFreezeOnSelFeat->Freeze();
				if ( SUCCEEDED (hr) )
				{
				   cout << "Feature frozen" << endl;
				} 
			}
			// release the useless pointer on the selected feature
			pIMmiResultFreezeOnSelFeat->Release();
		    pIMmiResultFreezeOnSelFeat = NULL;
		}
	} 
	return TRUE ;
}
