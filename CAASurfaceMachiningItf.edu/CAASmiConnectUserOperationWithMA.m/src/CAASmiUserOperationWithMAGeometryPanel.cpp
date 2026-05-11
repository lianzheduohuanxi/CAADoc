// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiUserOperationWithMAGeometryPanel :
//
// Sample code for : CAA User Operation connected with 3D Machining Area (sample 6)
//
// Mission         : Geometry frame for a user operation connected with a Machining Area.
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a CAASmg operation
//                   3- Select the geometry tabpage
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct in the resources\graphic directory of the runtime view.
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAASmiUserOperationWithMAGeometryPanel.h"

// Dialog Interfaces
#include "CATDlgLabel.h"
#include "CATDlgCombo.h"
#include "CATDlgGridConstraints.h"

// Manufacturing Interfaces
#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgActivity.h"

// Application Frame Interfaces
#include "CATIEdit.h"

// Object Modeler Base Interfaces
#include "CATIAlias.h"
#include "CATInstantiateComponent.h"

// Visualization
#include "CATModify.h"
#include "CATIModelEvents.h"


//========================================================================
// Constructor
//========================================================================
CAASmiUserOperationWithMAGeometryPanel::CAASmiUserOperationWithMAGeometryPanel(CATDialog *iFather, const CATBaseUnknown_var &iObject)
	: CATDlgFrame (iFather, "CAASmiUserOperationWithMAGeometryPanel", CATDlgGridLayout)
{
	_spBaseActivity = iObject;
		
	// Creates a icon
	CATDlgLabel * pIcon = new CATDlgLabel (this,"Icon");
	if (pIcon)
	{
		pIcon->SetIconName("I_M3xFeature");;
		pIcon->SetGridConstraints( 0, 0, 1, 1, CATGRID_4SIDES);
	}

	// Creates a combo box
	_pDlgCombo = new CATDlgCombo(this,"DlgCombo",CATDlgCmbDropDown);
	if (_pDlgCombo)
	{
		_pDlgCombo->SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);

		// Gets current machining area
		CATBaseUnknown_var spCurrentMachArea = NULL_var;
		CATIMfgActivity * pActivity = NULL;
		HRESULT RC = iObject->QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
		if (SUCCEEDED(RC))
		{
			spCurrentMachArea = pActivity->GetFeature();
			pActivity->Release();
			pActivity = NULL;
		}
		
		// Gets Manufacturing Feature Container
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
		
		// Fills the combo box
		if (!!spFeatCont)
		{
			// Finds all machining areas inside the model
            SEQUENCE(CATBaseUnknown_ptr) SeqMAs;

// VIOI - mkCheckSource error filtered (ListMembersHere)
// @CSC-Filter VIOI
            spFeatCont->ListMembersHere("CATIM3xFeature",SeqMAs);	
   			_pListOfMAs = SeqMAs;
            
            int NumbOfMAs = _pListOfMAs.Size();
			for (int i=1;i<=NumbOfMAs;i++)
			{  				
				CATUnicodeString Name;
				CATBaseUnknown_var spMachArea = _pListOfMAs[i];
				if (!!spMachArea)
				{
					CATIAlias * pAlias = NULL;
					HRESULT RC = spMachArea->QueryInterface(IID_CATIAlias, (void**) &pAlias);
					if (SUCCEEDED(RC))
					{
						Name = pAlias->GetAlias();
						_pDlgCombo->SetLine(Name);
						pAlias->Release();
						pAlias = NULL;
					}

					if (spMachArea->IsEqual(spCurrentMachArea) == 1)
						_pDlgCombo->SetSelect(i-1,0);
				}
			}
		}
  
		// Adds a callback 
		AddAnalyseNotificationCB(
					_pDlgCombo,
					_pDlgCombo->GetComboSelectNotification(),
					(CATCommandMethod) &CAASmiUserOperationWithMAGeometryPanel::SelectMachArea,NULL);

		// Creates the Machining Area editor
		if (!!spCurrentMachArea)
		{
			CATIEdit * pEdit = NULL;
			RC = spCurrentMachArea->QueryInterface(IID_CATIEdit, (void**) &pEdit);
			if (SUCCEEDED(RC))
			{
				CATDlgFrame * pMAFrame = pEdit->GetPanelItem(this,"MAFrameID");
				if (pMAFrame) 
					pMAFrame->SetGridConstraints( 1, 0, 2, 1, CATGRID_4SIDES);
				pEdit->Release();
				pEdit = NULL;
			}
		}		
	}
}

//========================================================================
// Destructor
//========================================================================
CAASmiUserOperationWithMAGeometryPanel::~CAASmiUserOperationWithMAGeometryPanel()
{
	_pDlgCombo = NULL;

	// Delete _pListOfMAs
	int NumbOfMAs = _pListOfMAs.Size();
	for (int i=0;i<NumbOfMAs;i++)
	{  
		CATBaseUnknown* pEltMA = _pListOfMAs[i+1];
		if (NULL != pEltMA) pEltMA->Release();
	}
}

//========================================================================
// CB SelMachArea
//========================================================================
void CAASmiUserOperationWithMAGeometryPanel::SelectMachArea ( CATCommand *iPublisher,
													 CATNotification *iNotification,
													 CATCommandClientData iUsefulData)
{
	int NumbOfMAs = _pListOfMAs.Size();
	
	// Gets the selected row of the combo box
	int SelectedRow = _pDlgCombo->GetSelect();
	if (SelectedRow >= 0 && SelectedRow < NumbOfMAs)
	{
		// Gets the selected MA
		CATBaseUnknown_var spMA = _pListOfMAs[SelectedRow+1];
		if (!!spMA)
		{
			// Switch the machining area
			CATIMfgActivity * pActivity = NULL;
			HRESULT RC = _spBaseActivity->QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
			if (SUCCEEDED(RC))
			{
				CATBaseUnknown_var spOldMA = pActivity->GetFeature();    
				pActivity->RemoveFeature(spOldMA);
				pActivity->SetFeature(spMA);

				pActivity->Release();
				pActivity = NULL;
			}

			// Refresh Machining Area Editor
			CATIEdit * pEdit = NULL;
			RC = spMA->QueryInterface(IID_CATIEdit, (void**) &pEdit);
			if (SUCCEEDED(RC))
			{
				// As a frame called "MAFrameID" has already been created, the method GetPanelItem
				// will refresh it
				pEdit->GetPanelItem(this,"MAFrameID");
				pEdit->Release();
				pEdit = NULL;
			}

			// Update Replay button
			CATModify Info (_spBaseActivity);
			CATIModelEvents_var spModelEvt(_spBaseActivity);
			if(!!spModelEvt) spModelEvt->Dispatch(Info);
	
		}
	}
}
