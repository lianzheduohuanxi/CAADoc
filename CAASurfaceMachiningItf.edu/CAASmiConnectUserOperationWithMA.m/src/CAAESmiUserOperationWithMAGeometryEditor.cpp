// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationWithMAGeometryEditor :
//
// Sample code for : CAA User Operation connected with 3D Machining Area (sample 6)
//
// Mission         : Overloads Geometry Tabpage of the edition panel of an user operation connected
//                   with a Machining Area
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a user operation
//                   3- Select the geometry tabpage
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct in the resources\graphic directory of the runtime view.
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationWithMAGeometryEditor.h"
#include "CAASmiUserOperationWithMAGeometryPanel.h"

// Surface Machining Interfaces
#include "CATISmgFactory.h"
#include "CATISmgMachiningAreaParts.h"
 
// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgManufacturingFactories.h"

// Object Modeler Base Interfaces
#include "CATInstantiateComponent.h"

// Tie the implementation to its interface
CATImplementBOA (CATIMfgGeometryActivity, CAAESmiUserOperationWithMAGeometryEditor);
CATImplementClass( CAAESmiUserOperationWithMAGeometryEditor,
                   CacheExtension,
                   CATIMfgGeometryActivity,
                   CAASmgOperationWithMA );
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationWithMAGeometryEditor::CAAESmiUserOperationWithMAGeometryEditor()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationWithMAGeometryEditor::~CAAESmiUserOperationWithMAGeometryEditor()
{
}
 
//========================================================================
// GetMainPanelEditor
//========================================================================
HRESULT CAAESmiUserOperationWithMAGeometryEditor::GetMainPanelEditor (CATDialog * iFather, CATDlgFrame*&  oFrame , CATDlgStyle  iStyle)
{
	HRESULT oRC = S_OK;

    // Gets activity
	CATIMfgActivity * pActivity = NULL;
	oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
	if (SUCCEEDED(oRC))
    {
        // Gets machining area
		CATBaseUnknown_var spMachFeature = pActivity->GetFeature(); 
		if (NULL_var == spMachFeature)
		{
			// Gets Manufacturing Resources Container
			CATIContainer_var spFeatCont(NULL_var);
			CATIMfgManufacturingFactories *piFact =NULL;
			CATString ClassName("CATMfgManufacturingFactories");
			CATInstantiateComponent (ClassName,
									CATIMfgManufacturingFactories::ClassId(),
									(void**)& piFact);
			if (piFact)
			{
				piFact->GetManufacturingFeatureFactory(spFeatCont);
				piFact->Release();
			}

			if (!!spFeatCont)
			{
				CATISmgFactory * pSmgFactory = NULL;
				oRC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**) &pSmgFactory);
				if (SUCCEEDED(oRC))
				{
					// Creates a empty machining area
					oRC = pSmgFactory->CreateMachiningArea(spMachFeature);
					if (SUCCEEDED(oRC))
					{
						// Modify the geometry status of parts
			            CATISmgMachiningAreaParts * pParts = NULL;
			            oRC = spMachFeature->QueryInterface(IID_CATISmgMachiningAreaParts, (void**) &pParts);
			            if (SUCCEEDED(oRC))
                        {
                            pParts->SetStatus(0); // 0 : optional geometry
                            pParts->Release();
                            pParts = NULL;
                        }                        
                        
                        // Link the machining area to the activity
						pActivity->SetFeature(spMachFeature);
					}

					pSmgFactory->Release();
					pSmgFactory = NULL;
				}
			}
		}
		pActivity->Release();
		pActivity = NULL;
	}
   
    // Creates the geometry frame
    oFrame = new CAASmiUserOperationWithMAGeometryPanel(iFather,this);
	
    return oRC;
}
