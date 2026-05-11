// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationToolEditor :
//
// Sample code for : CAA Activities Management (sample 2)
//
// Mission         : Manage allowed and default tools on user operations.
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a CAASmg operation
//                   3- Select the tool tabpage
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct and CAAUserMachiningFeatures.CATfct
//                    in the resources\graphic directory of the runtime view.
//					 
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationToolEditor.h"
 
// Manufacturing Interfaces
#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgResourceFactory.h"
#include "CATIMfgActivity.h"
#include "CATIMfgTool.h"
#include "CATMfgToolConstant.h"

// Object Modeler Base Interfaces
#include "CATIContainer.h"

// System Interfaces
#include "CATInstantiateComponent.h"
#include "CATString.h"

// Tie the implementation to its interface
CATImplementBOA (CATIMfgToolActivity, CAAESmiUserOperationToolEditor);

CATBeginImplementClass( CAAESmiUserOperationToolEditor, CacheExtension, CATIMfgToolActivity, CAASmgOperation );
CATAddExtendedImplementation(CAASmgOperationWithMA);
CATEndImplementClass(CAAESmiUserOperationToolEditor);
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationToolEditor::CAAESmiUserOperationToolEditor()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationToolEditor::~CAAESmiUserOperationToolEditor()
{
}
 
//========================================================================
// GetAuthorizedToolTypeList
//========================================================================
HRESULT CAAESmiUserOperationToolEditor::GetAuthorizedToolTypeList (CATListOfCATUnicodeString & oToolTypeList)
{ 
   // Allowed Tools	
   oToolTypeList.Append(CATEMfgEndMillTool);
   oToolTypeList.Append(CATEMfgDrillTool);

   return S_OK;
}

//========================================================================
// CreateDefaultTool
//========================================================================
HRESULT CAAESmiUserOperationToolEditor::CreateDefaultTool (CATBaseUnknown_var & oTool)
{
	HRESULT oRC = E_FAIL;
    oTool = NULL_var;

	// Get Manufacturing Resources Container
	CATIContainer_var spResourceContainer;
	CATIMfgManufacturingFactories *piFact =NULL;
	CATString ClassName("CATMfgManufacturingFactories");
	CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingFactories::ClassId(),
                            (void**)& piFact);
	if (piFact)
	{
	    piFact->GetManufacturingToolFactory(spResourceContainer);
	    piFact->Release();
	}

    // Retrieves Resource Factory
	if (!!spResourceContainer)
	{
		CATIMfgResourceFactory * pResourceFactory = NULL;
		oRC = spResourceContainer->QueryInterface(IID_CATIMfgResourceFactory, (void**) &pResourceFactory);
		if (SUCCEEDED(oRC))
		{
			// Creates Default Tool
			CATUnicodeString ToolTypeToCreate = MfgEndMillTool;
            oRC = pResourceFactory->CreateResource (ToolTypeToCreate, oTool);
			pResourceFactory->Release();
			pResourceFactory = NULL;
			
			// Defines a Default tool for our user operation
			if(!!oTool && SUCCEEDED(oRC))
			{
			   CATIMfgTool * pMfgTool = NULL;
			   oRC = oTool->QueryInterface(IID_CATIMfgTool, (void**) &pMfgTool);
			   if (SUCCEEDED(oRC) )
			   {
				   pMfgTool->SetDefaultValues();
 				   pMfgTool->SetDefaultName();
				   pMfgTool->Release();
				   pMfgTool = NULL;
			   }

			   CATIMfgActivity * pActivity = NULL;
			   oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
			   if (SUCCEEDED(oRC))
			   {
				   pActivity->SetDefaultTool(oTool);
				   pActivity->Release();
				   pActivity = NULL;
			   }
			}
		}
	}

    return oRC;
}

//========================================================================
// GetFirstToolCompensation
//========================================================================
HRESULT CAAESmiUserOperationToolEditor::GetFirstToolCompensation (int & oFirstNumber)
{
	oFirstNumber = 1;
	return S_OK;
}

//========================================================================
// GetSecondToolCompensation
//========================================================================
HRESULT CAAESmiUserOperationToolEditor::GetSecondToolCompensation (int & oSecondNumber)
{
	oSecondNumber = 1;
	return S_OK;
}

