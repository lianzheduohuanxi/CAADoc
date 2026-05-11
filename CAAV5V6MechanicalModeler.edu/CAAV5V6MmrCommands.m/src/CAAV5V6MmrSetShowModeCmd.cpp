// COPYRIGHT DASSAULT SYSTEMES 2012


//Local Framework
#include "CAAV5V6MmrSetShowModeCmd.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// AfrFoundation Framework for V6
// ApplicationFrame Framework for V5
#include "CATFrmEditor.h"

// VisualizationInterfaces Framework for V6
// VisualizationBase Framework for V5
#include "CATPathElement.h"

// VisualizationInterfaces Framework for V6
// Visualization Framework for V5
#include "CATIVisProperties.h"
#include "CATVisPropertiesValues.h"
#include "CATIModelEvents.h"
#include "CATI3DGeoVisu.h"
#include "CATModifyVisProperties.h"

// VisualizationFoundation for V6
// VisualizationBase for V5
#include "CATRep.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"

//CATMecModUseItf
#include "CATI3DGeometricalElement.h"
#include "CATIMmiPartModelEventManagement.h"
#include "CATIMfMonoDimResult.h"
#include "CATIMfPlane.h"
#include "CATIMfPoint.h"
#include "CATIMfLine.h"
#include "CATIMfZeroDimResult.h"
#include "CATIMfBiDimResult.h"
#include "CATIMfTriDimResult.h"
#include "CATIMfInfiniteResult.h"

//CATMecModLiveUseItf
#include "CATIMmiMechanicalFeature.h"

// C++ Standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAV5V6MmrSetShowModeCmd);

//-------------------------------------------------------------------------

CAAV5V6MmrSetShowModeCmd::CAAV5V6MmrSetShowModeCmd(): 
CATStateCommand("CAAV5V6MmrSetShowModeCmdId"),
  _daObjectToSelect(NULL) 
{
	cout << "   CAAV5V6MmrSetShowModeCmd void constructor" << endl ;
}

//--------------------------------------------------------------------------

CAAV5V6MmrSetShowModeCmd::~CAAV5V6MmrSetShowModeCmd()
{
	cout << "   CAAV5V6MmrSetShowModeCmd destructor" << endl ;

	if (NULL != _daObjectToSelect) 
	{
		_daObjectToSelect->RequestDelayedDestruction();
		_daObjectToSelect = NULL;
	}
}

//-------------------------------------------------------------------------
// BuildGraph()
// Defining a StateChart Command
//-------------------------------------------------------------------------
void CAAV5V6MmrSetShowModeCmd::BuildGraph()
{
	// Statechart definition
	cout << "CAAV5V6MmrSetShowModeCmd::BuildGraph" << endl;

	// Create a PathElement Selection agent to select an entity from the spec tree,
	// Valid objects are geometrical features.
	_daObjectToSelect = new CATPathElementAgent("SelMechanicalFeature");
	
	// The CATI3DGeometricalElement interface is sufficient to filter geometrical features.
	// The other interfaces are just to show the use of these filter interfaces.
    _daObjectToSelect->SetOrderedElementType("CATI3DGeometricalElement");
	_daObjectToSelect->SetOrderedElementType("CATIMfZeroDimResult");
    _daObjectToSelect->AddOrderedElementType("CATIMfMonoDimResult");
	_daObjectToSelect->AddOrderedElementType("CATIMfBiDimResult");
	_daObjectToSelect->AddOrderedElementType("CATIMfTriDimResult");
	_daObjectToSelect->AddOrderedElementType("CATIMfInfiniteResult");
    _daObjectToSelect->AddOrderedElementType("CATIMfPoint");
    _daObjectToSelect->AddOrderedElementType("CATIMfLine");
	_daObjectToSelect->AddOrderedElementType("CATIMfPlane");
	
	// Define the Agent behavior
	_daObjectToSelect->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation | CATDlgEngRepeat);
 
	// Create the first and only state, that of selecting the feature
	CATDialogState* stGetObjState = GetInitialState("stGetObjStateId");
	
	// Associate this state with a dialog agent, previously defined
	stGetObjState->AddDialogAgent(_daObjectToSelect);

	// Associate an Incoming Transition to the same state, in response to the selection
	// agent modification
	CATDialogTransition* pTransition1 = AddTransition(stGetObjState,
													  stGetObjState,
													  IsLastModifiedAgentCondition(_daObjectToSelect),
													  Action((ActionMethod) & CAAV5V6MmrSetShowModeCmd::SwapShowMode)
													  );
}

//--------------------------------------------------------------------------

// Action Method triggered on an Incoming Transition associated with the State Command
// Retrieve the selected entity and process it : swap show mode and check immediately the status

CATBoolean CAAV5V6MmrSetShowModeCmd::SwapShowMode(void* iData)
{
	cout << "   CAAV5V6MmrSetShowModeCmd Activate" << endl ;

	HRESULT rc = S_OK;

	// Retrieve the selected entity, as a CATPathElement object from the selection agent
	CATPathElement* pathModel = _daObjectToSelect->GetValue();
	CATBaseUnknown* pSelectedObj = NULL;


	if ((NULL != pathModel)&&(pathModel->GetSize()>0))
	{
	  // Seek the last element of the path. 
	  pSelectedObj = (*pathModel)[pathModel->GetSize()-1];
	  if (NULL == pSelectedObj)
		return TRUE ;

	  // Test to check the type of the selected geometry: this is not particularly usefull for this scenario
	  // but its just to show the use of these filter interfaces.
		
	  CATIMfZeroDimResult_var zero = pSelectedObj;
	  if (!!zero)
		  cout << "selection is of dim 0" << endl;
	  CATIMfPoint_var pt = pSelectedObj;
      if (!!pt)
		  cout << "selection is a point" << endl;

	  CATIMfMonoDimResult_var mono = pSelectedObj;
	  if (!!mono)
		  cout << "selection is of dim 1" << endl; 
	  CATIMfLine_var ln = pSelectedObj;
      if (!!ln)
		  cout << "selection is a line" << endl;
    
	  CATIMfBiDimResult_var bi = pSelectedObj;
      if (!!bi)
		  cout << "selection is of dim 2" << endl;
    
	  CATIMfInfiniteResult_var infinite = pSelectedObj;
	  if (!!infinite)
		  cout << "selection is infinite" << endl;
    
	  CATIMfPlane_var pln = pSelectedObj;
	  if (!!pln)
		  cout << "selection is a plane" << endl; 
    
	  CATIMfTriDimResult_var tri = pSelectedObj;
      if (!!tri)
		  cout << "selection is of dim 3" << endl;


    // Query the CATIVisProperties Interface
    CATIVisProperties_var MyFeatureProperties = pSelectedObj;

    if (NULL_var != MyFeatureProperties)
    {
		CATVisPropertiesValues visValues;

		// Get the current value of the show attribute
	    rc = MyFeatureProperties->GetPropertiesAtt(visValues,CATVPShow,CATVPGlobalType);  
     
		// Swap the value of show attribute
		if (SUCCEEDED(rc))
		{
		   CATShowAttribut ShowAttr  =  CATShowAttr;
		   visValues.GetShowAttr(ShowAttr); 
 
		   if (ShowAttr == CATShowAttr)
              ShowAttr = CATNoShowAttr;
		   else if (ShowAttr == CATNoShowAttr)
			  ShowAttr = CATShowAttr;
     
            visValues.SetShow(ShowAttr);

            // Modify the property
	        rc = MyFeatureProperties->SetPropertiesAtt(visValues,CATVPShow,CATVPGlobalType);  
     
            // Sending the visualization event to refresh the 3D
            CATIModelEvents_var MyFeatureModelEvents = pSelectedObj;
            if (SUCCEEDED(rc) && NULL_var != MyFeatureModelEvents)
            {
	          CATModifyVisProperties ModifyNotification(pSelectedObj, NULL, CATVPGlobalType, CATVPShow, visValues); 
	          MyFeatureModelEvents->Dispatch(ModifyNotification);
            }

            //ask for the immediate process of visu events
            CATIMmiMechanicalFeature_var spMechFeat = pSelectedObj;
            if (NULL_var != spMechFeat)
            {
			  CATIMmiMechanicalFeature_var spPart;
              rc = spMechFeat->GetMechanicalPart(spPart);

              if (NULL_var != spPart)
              {
			     CATIMmiPartModelEventManagement * piPartModelEvtMgnt	= NULL;
			     rc = spPart->QueryInterface(CATIMmiPartModelEventManagement::ClassId(), (void **) &piPartModelEvtMgnt);
			     if (SUCCEEDED(rc) && piPartModelEvtMgnt) 
			     {
				    piPartModelEvtMgnt->CommitNow();
				    piPartModelEvtMgnt->Release();
				    piPartModelEvtMgnt = NULL;
			     }
		         else
			        cout <<" error casting part to CATIMmiPartModelEventManagement" <<endl;
              }
            }

            // Check that the modification has been taken into account
            int isHidden = 0;
            CATI3DGeoVisu * p3DGeoVisu = NULL;
            rc = MyFeatureModelEvents->QueryInterface(IID_CATI3DGeoVisu, (void **)&p3DGeoVisu);
            if (SUCCEEDED(rc) && NULL != p3DGeoVisu)
            {
	          CATRep * pRep = p3DGeoVisu->GiveRep();
	          if (pRep != NULL)
		        isHidden = pRep->IsHidden();	
              p3DGeoVisu->Release();
              p3DGeoVisu = NULL;
            }

			if (isHidden && ShowAttr == CATShowAttr)
			  cout<<"error the feature shouldn't be hidden in the 3D"<<endl;
			else if (isHidden && ShowAttr == CATNoShowAttr)
	          cout<<"As expected, the feature is now hidden in the 3D"<<endl;
			else if (!isHidden && ShowAttr == CATNoShowAttr)
			  cout<<"error the feature should be hidden in the 3D"<<endl;
			else if (!isHidden && ShowAttr == CATShowAttr)
              cout<<"As expected, the feature isn't hidden"<<endl;
		  }
	  }
  }	
  return TRUE ;
	
}




