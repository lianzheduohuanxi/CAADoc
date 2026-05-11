// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationGeometryEditor :
//
// Sample code for : CAA Machining Features Management (sample 4)
//
// Mission         : Overloads the Geometry Tabpage of the edition panel of an user operation ("CAASmgOperation").
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a CAASmg operation
//                   3- Select the geometry tabpage
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct and CAAUserMachiningFeatures.CATfct
//                    in the resources\graphic directory of the runtime view.
//
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationGeometryEditor.h"
#include "CAASmiUserOperationGeometryPanel.h"

// Surface Machining Interfaces
#include "CATISmgNcGeometryManager.h"

// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgViewAccess.h"
#include "CATIMfgManufacturingFactories.h"

// Object Modeler Base Interfaces
#include "CATInstantiateComponent.h"
#include "CATOsmSUHandler.h"

// Object Specs Modeler Interfaces
#include "CATISpecObject.h"

// Tie the implementation to its interface
CATImplementBOA (CATIMfgGeometryActivity, CAAESmiUserOperationGeometryEditor);
CATImplementClass( CAAESmiUserOperationGeometryEditor, CacheExtension, CATIMfgGeometryActivity,	CAASmgOperation);

//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationGeometryEditor::CAAESmiUserOperationGeometryEditor()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationGeometryEditor::~CAAESmiUserOperationGeometryEditor()
{
}

//========================================================================
// GetMainPanelEditor
//========================================================================
HRESULT CAAESmiUserOperationGeometryEditor::GetMainPanelEditor (CATDialog * iFather, CATDlgFrame*& oFrame, CATDlgStyle iStyle)
{
	HRESULT oRC = S_OK;
	CATBaseUnknown_var spMachFeature(NULL_var);

	// Associates a machining feature
	CATIMfgActivity * pActivity = NULL;
	oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
	if (SUCCEEDED(oRC))
	{
		spMachFeature = pActivity->GetFeature(); 
		if (NULL_var == spMachFeature)
		{
			// Create a user machining feature
			oRC = CreateCAAMachiningFeature(spMachFeature);
			if (SUCCEEDED(oRC))
			{
				// Link the machining feature to the activity
				pActivity->SetFeature(spMachFeature);
			}
		}
		pActivity->Release();
		pActivity = NULL;
	}

	// Creates the frame
	oFrame = new CAASmiUserOperationGeometryPanel(iFather,spMachFeature);

	return oRC;
}

//========================================================================
// CreateCAAMachiningFeature
//========================================================================
HRESULT CAAESmiUserOperationGeometryEditor::CreateCAAMachiningFeature(CATBaseUnknown_var & oFeature)
{
	HRESULT oRC = S_OK;

	// Get Manufacturing Resources Container
	CATIContainer_var spFeatCont(NULL_var);
	CATIMfgManufacturingFactories *piFact =NULL;
	CATString ClassName("CATMfgManufacturingFactories");
	CATInstantiateComponent (ClassName,	CATIMfgManufacturingFactories::ClassId(), (void**)& piFact);
	if (piFact)
	{
		piFact->GetManufacturingFeatureFactory(spFeatCont);
		piFact->Release();
	}

	if (!!spFeatCont)
	{
		// Loads catalog	  
		CATUnicodeString CatalogFeature ("CAAUserMachiningFeatures.CATfct");	
		CATUnicodeString ClientID ("CAAManufacturing");
		CATUnicodeString NewSUFeatType("CAASmgMachiningFeature");
		CATOsmSUHandler novelSUHandler(NewSUFeatType, ClientID, CatalogFeature);

		CATISpecObject_var spInstance = NULL_var;
		oRC = novelSUHandler.Instanciate(spInstance, spFeatCont, "");
		if (FAILED(oRC)) return oRC;

		// Creates the machining feature (associated in Catalog)	  
		if (SUCCEEDED(oRC))
		{
			oFeature = spInstance;

			// Adds a geometric parameter "CAASmgGuide"
			CATISmgNcGeometryManager_var spSmgManager = oFeature;
			if (spSmgManager != NULL_var)
				oRC = spSmgManager->AddNcGeometryParameter("CAASmgGuide",SmgEdgeType);
		}

		// Adds the feature in the MfgView
		SEQUENCE(CATBaseUnknown_ptr) ListOfMfgView;
		spFeatCont->ListMembersHere(CATIMfgViewAccess::ClassName(), ListOfMfgView);

		int NbMfgView = ListOfMfgView.length();
		if(NbMfgView)
		{
			CATBaseUnknown * pBaseView = ListOfMfgView[NbMfgView - 1];
			if (pBaseView)
			{
				CATIMfgViewAccess_var spMfgView = pBaseView;
				if (spMfgView != NULL_var)
					spMfgView->AddFeature(oFeature);
				pBaseView->Release();
			}
		}
	}

	return oRC;
}
