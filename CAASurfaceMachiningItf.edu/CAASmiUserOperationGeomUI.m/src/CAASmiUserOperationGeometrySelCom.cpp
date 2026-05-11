// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiUserOperationGeometrySelCom :
//
// Sample code for : CAA Machining Features Management (sample 4)
//
// Mission         : Command to select the geometry of the CAASmg machining feature.
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a CAASmg operation
//                   3- Launch the command in the geometry tabpage
//
//=============================================================================

// Includes
#include "CAASmiUserOperationGeometrySelCom.h"

// Surface Machining Interfaces
#include "CATISmgNcGeometryParameter.h"

// Manufacturing Interfaces
#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgGeometryFactory.h"

// Object  Modeler Base Interfaces
#include "CATIProduct.h"
#include "CATILinkableObject.h"

// Geometric Object Interfaces
#include "CATCurve.h"

// System Interfaces
#include "CATInstantiateComponent.h"

// DialogEngine Interfaces
#include "CATPathElement.h"
#include "CATPathElementAgent.h"

// Dialog Interfaces
#include "CATDlgDialog.h"


//========================================================================
// Constructor
//========================================================================
CAASmiUserOperationGeometrySelCom::CAASmiUserOperationGeometrySelCom(CATCommand *iFather,const CATBaseUnknown_var &ispGuide) :
	 CATStateCommand("GeometrySel",NULL,CATCommandModeShared)
{  
	_spGuide = ispGuide;
	_pPanel = NULL;
    _pPanelAgent = NULL;
  
	// Creates selection agent
	_pSelectAgent = new CATPathElementAgent("Curve", NULL,
              CATDlgEngRepeat|CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithUndo);
	if (_pSelectAgent)
       _pSelectAgent->SetOrderedElementType (CATCurve::ClassName());

	// Gets the Edition panel (pFather)
	int Found = 0;
	int I     = 1;
    CATCommand * pFather = iFather;
    while (pFather && Found == 0 && I < 10)
    {
       if (pFather->IsAKindOf("CATMfgMachiningOperationFrmDialog") || pFather->IsAKindOf("CATDlgDialog")) Found = 1;
       else pFather = pFather->GetFather();
       I++;
    }  

    // Creates an agent panel   
    if (Found == 1)
    {
       _pPanel = (CATDlgDialog*) pFather; 

       _pPanelAgent = new CATDialogAgent("PanelAgent", CATDlgEngRepeat),
       _pPanelAgent->AcceptOnNotify (_pPanel,_pPanel->GetDiaCANCELNotification());
       _pPanelAgent->AcceptOnNotify (_pPanel,_pPanel->GetDiaOKNotification());

       // Hides the Edition panel
	   _pPanel->Minimize();   
       _pPanel->SetVisibility(CATDlgHide);   
	}
}

//========================================================================
// Destructor
//========================================================================
CAASmiUserOperationGeometrySelCom::~CAASmiUserOperationGeometrySelCom()
{	
	_pPanel = NULL;

    if( _pSelectAgent)
		_pSelectAgent->RequestDelayedDestruction();    
	_pSelectAgent = NULL;

    if( _pPanelAgent)
		_pPanelAgent->RequestDelayedDestruction();    
	_pPanelAgent = NULL;
}

//========================================================================
// BuildGraph
//========================================================================
void CAASmiUserOperationGeometrySelCom::BuildGraph()
{
	CATDialogState * InitState = GetInitialState("SelCurve");
	if (InitState)
		InitState->AddDialogAgent (_pSelectAgent);
 
	if (_pPanelAgent) 
	{
		InitState->AddDialogAgent (_pPanelAgent);
		AddTransition (InitState,NULL,IsOutputSetCondition (_pPanelAgent));
	}

	AddTransition (InitState,NULL,IsOutputSetCondition (_pSelectAgent),
                  Action((ActionMethod)& CAASmiUserOperationGeometrySelCom::SelCurve));
}

//========================================================================
// SelCurve
//========================================================================
CATBoolean CAASmiUserOperationGeometrySelCom::SelCurve (void * data)
{
	// Gets selection
	CATBaseUnknown * pSelect = _pSelectAgent->GetElementValue();
	CATILinkableObject_var spLinkable = pSelect;
	if (!!spLinkable)
	{
	    // Scan for the product
	    CATIProduct_var spProduct = NULL_var;
	    CATPathElement * pPath = _pSelectAgent->GetValue();
	    if (pPath)
		{ 
		    pPath->InitToLeafElement();

		    CATBaseUnknown * pElem = NULL;
		    while((pElem = pPath->NextFatherElement()) && (NULL_var == spProduct))
			{
				spProduct = pElem;
			} 
		}
	
		// Gets Manufacturing Feature Container
		CATIContainer_var spFeatCont(NULL_var);
		CATIMfgManufacturingFactories * piFact = NULL;
		CATString ClassName("CATMfgManufacturingFactories");
		CATInstantiateComponent (ClassName,
								CATIMfgManufacturingFactories::ClassId(),
								(void**)& piFact);
		if (piFact)
		{
 			piFact->GetManufacturingFeatureFactory(spFeatCont);
			piFact->Release();
		}
		
		// Creates a Manufacturing Geometry from the selected curve
		CATBaseUnknown_var spMfgGeom = NULL_var;			
		CATIMfgGeometryFactory_var spFactory = spFeatCont;
		if (!!spFactory)
		{
			CATBaseUnknown_var spBaseProduct = spProduct;
			spFactory->CreateGeometry(spLinkable,spBaseProduct,spMfgGeom);
		}

		// Add the Manufacturing Geometry to the guide parameter
		if (!!spMfgGeom && !!_spGuide)
		{
			CATBaseUnknown_var spBaseProduct = spProduct;
			CATISmgNcGeometryParameter * pSmgParameter = NULL;
			HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
			if (SUCCEEDED(RC))
			{
				pSmgParameter->Add(spMfgGeom);
				pSmgParameter->Release();
				pSmgParameter = NULL;
			}
		}
	}

	// Restores edition panel
	if (_pPanel)
	{
       _pPanel->SetVisibility(CATDlgShow);   
       _pPanel->Restore(); 
	}

	return TRUE;
}

