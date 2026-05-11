// COPYRIGHT DASSAULT SYSTEMES 2011

//Local Framework
#include "CAAMmrSetShowModeCmd.h"

// System Framework
#include "CATFrmEditor.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

//VisualizationInterfaces Framework
#include "CATPathElement.h"
#include "CATIVisProperties.h"
#include "CATVisPropertiesValues.h"
#include "CATIModelEvents.h"
#include "CATI3DGeoVisu.h"
#include "CATModifyVisProperties.h"

// VisualizationFoundation
#include "CATRep.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"

//CATMecModUseItf
//#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiPartModelEventManagement.h"

//CATMecModLiveUseItf
//#include "CATIMmiMechanicalFeature.h"

//MecModInterfaces
#include "CATIGeometricalElement.h"
#include "CATIMechanicalFeature.h"

//ObjectSpecsModeler
#include "CATISpecObject.h"

// C++ Standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAMmrSetShowModeCmd);

//-------------------------------------------------------------------------

CAAMmrSetShowModeCmd::CAAMmrSetShowModeCmd(): 
CATStateCommand("CAAMmrSetShowModeCmdId"),
  _daObjectToSelect(NULL) 
{
	cout << "   CAAMmrSetShowModeCmd void constructor" << endl ;
}

//--------------------------------------------------------------------------

CAAMmrSetShowModeCmd::~CAAMmrSetShowModeCmd()
{
	cout << "   CAAMmrSetShowModeCmd destructor" << endl ;

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
void CAAMmrSetShowModeCmd::BuildGraph()
{
	// Statechart definition
	cout << "CAAMmrSetShowModeCmd::BuildGraph" << endl;

	// Create a PathElement Selection agent to select an entity from the spec tree,
	// Valid objects are geometrical features.
	_daObjectToSelect = new CATPathElementAgent("SelMechanicalFeature");
	//_daObjectToSelect->AddElementType(IID_CATIMmiUseGeometricalElement);
	_daObjectToSelect->AddElementType(IID_CATIGeometricalElement);
 
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
													  Action((ActionMethod) & CAAMmrSetShowModeCmd::SwapShowMode)
													  );
}

//--------------------------------------------------------------------------

// Action Method triggered on an Incoming Transition associated with the State Command
// Retrieve the selected entity and process it : swap show mode and check immediately the status

CATBoolean CAAMmrSetShowModeCmd::SwapShowMode(void* iData)
{
	cout << "   CAAMmrSetShowModeCmd Activate" << endl ;

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

	  // Seek the CATIMmiUseGeometricalElement type on the selected feature
		//CATIMmiUseGeometricalElement_var spMmiMechFeat = pSelectedObj;
		CATIGeometricalElement_var spMmiMechFeat = pSelectedObj;

	  if (spMmiMechFeat != NULL_var)
		{
			cout << "Selected feature is a geometrical feature" << endl;

      // Query the CATIVisProperties Interface
      CATIVisProperties_var MyFeatureProperties = spMmiMechFeat;

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
          CATIModelEvents_var MyFeatureModelEvents = spMmiMechFeat;
          if (SUCCEEDED(rc) && NULL_var != MyFeatureModelEvents)
          {
	          CATModifyVisProperties ModifyNotification(spMmiMechFeat, NULL, CATVPGlobalType, CATVPShow, visValues); 
	          MyFeatureModelEvents->Dispatch(ModifyNotification);
          }

          //ask for the immediate process of visu events
          //CATIMmiMechanicalFeature_var spMechFeat = spMmiMechFeat;
					CATIMechanicalFeature_var spMechFeat = spMmiMechFeat;
          if (NULL_var != spMechFeat)
          {
						//CATIMmiMechanicalFeature_var spPart;
            //rc = spMechFeat->GetMechanicalPart(spPart);
            CATISpecObject_var spPart = spMechFeat->GetPart();

            if (NULL_var != spPart)
            {
              CATIMmiPartModelEventManagement * PartModelEvtMgnt = NULL;
              rc = spPart->QueryInterface(IID_CATIMmiPartModelEventManagement,(void**)&PartModelEvtMgnt);
              if (SUCCEEDED(rc)&& NULL != PartModelEvtMgnt)
              {
                PartModelEvtMgnt->CommitNow();
                PartModelEvtMgnt->Release();
                PartModelEvtMgnt = NULL;
              }
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

					cout << "======================================================="<<endl;
          if (isHidden && ShowAttr == CATShowAttr)
	          cout<<"!!! ERROR the feature shouldn't be hidden in the 3D"<<endl;
					else if (isHidden && ShowAttr == CATNoShowAttr)
	          cout<<"As expected, the feature is now hidden in the 3D"<<endl;
          else if (!isHidden && ShowAttr == CATNoShowAttr)
						cout<<"!!! ERROR the feature should be hidden in the 3D"<<endl;
					else if (!isHidden && ShowAttr == CATShowAttr)
            cout<<"As expected, the feature isn't hidden"<<endl;
					cout << "======================================================="<<endl;
			  }
		  }
	  }
	}
	
	return TRUE ;
	
}




