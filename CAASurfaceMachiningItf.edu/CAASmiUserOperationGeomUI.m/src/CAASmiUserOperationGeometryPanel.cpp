// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiUserOperationGeometryPanel :
//
// Sample code for : CAA Machining Features Management (sample 4)
//
// Mission         : Geometry frame for CAASmg machining feature.
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
#include "CAASmiUserOperationGeometryPanel.h"
#include "CAASmiUserOperationGeometrySelCom.h"
#include "CAAISmiUserMachFeature.h"

// Surface Machining Interfaces
#include "CATISmgFactory.h"
#include "CATISmgNcGeometryParameter.h"

// Manufacturing Interfaces
#include "CATIMfgManufacturingFactories.h"

// Application Frame Interfaces
#include "CATIEdit.h"

// System Interfaces
#include "CATInstantiateComponent.h"
#include "CATLISTV_CATBaseUnknown.h"

// Visualization Interfaces
#include "CATIModelEvents.h"
#include "CATNotificationDispatcher.h"

// Dialog Interfaces
#include "CATDlgPushButton.h"
#include "CATDlgLabel.h"
#include "CATDlgGridConstraints.h"


//========================================================================
// Constructor
//========================================================================
CAASmiUserOperationGeometryPanel::CAASmiUserOperationGeometryPanel(CATDialog *iFather, const CATBaseUnknown_var &ispMachFeature)
	: CATDlgFrame (iFather, "CAASmiUserOperationGeometryPanel", CATDlgGridLayout)
	,_pSelCurveButton(NULL)
	,_pSelZoneButton(NULL)
	,_pNewZoneButton(NULL)
	,_pExportButton(NULL)

{		
	// Creates a push button for CURVE SELECTION
	_pSelCurveButton = new CATDlgPushButton (this,"SelCurveButton");
	if (_pSelCurveButton)
	{
		_pSelCurveButton->SetIconName("I_CAASmiSelectCurve");;
		_pSelCurveButton->SetGridConstraints( 0, 0, 1, 1, CATGRID_4SIDES);

		// Adds a callback 
		AddAnalyseNotificationCB(
					_pSelCurveButton,
					_pSelCurveButton->GetPushBActivateNotification(),
					(CATCommandMethod) &CAASmiUserOperationGeometryPanel::SelectCurve,NULL);
	}
	// Creates a label for CURVE SELECTION
	CATDlgLabel *pSelCurveLabel = new CATDlgLabel(this,"SelCurveLabel");
	if (pSelCurveLabel)
	{
		pSelCurveLabel->SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	}

	// Creates a push button for ZONE SELECTION
	_pSelZoneButton = new CATDlgPushButton (this,"SelZoneButton");
	if (_pSelZoneButton)
	{
		_pSelZoneButton->SetIconName("I_CAASmiSelectZone");;
		_pSelZoneButton->SetGridConstraints( 1, 0, 1, 1, CATGRID_4SIDES);

		// Adds a callback 
		AddAnalyseNotificationCB(
					_pSelZoneButton,
					_pSelZoneButton->GetPushBActivateNotification(),
					(CATCommandMethod) &CAASmiUserOperationGeometryPanel::SelectZone,NULL);
	}
	// Creates a label for ZONE SELECTION
	CATDlgLabel * pSelZoneLabel = new CATDlgLabel(this,"SelZoneLabel");
	if (pSelZoneLabel)
	{
		pSelZoneLabel->SetGridConstraints( 1, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	}

	// Creates a push button for REMOVE
	CATDlgPushButton * pRemoveButton = new CATDlgPushButton (this,"RemoveButton");
	if (pRemoveButton)
	{
		pRemoveButton->SetIconName("I_CAASmiRemoveAll");;
		pRemoveButton->SetGridConstraints( 2, 0, 1, 1, CATGRID_4SIDES);

		// Adds a callback 
		AddAnalyseNotificationCB(
					pRemoveButton,
					pRemoveButton->GetPushBActivateNotification(),
					(CATCommandMethod) &CAASmiUserOperationGeometryPanel::RemoveAll,NULL);
	}
	// Creates a label for REMOVE
	CATDlgLabel * pRemoveLabel = new CATDlgLabel(this,"RemoveLabel");
	if (pRemoveLabel)
	{
		pRemoveLabel->SetGridConstraints( 2, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	}

	// Creates a push button for NEW ZONE
	_pNewZoneButton = new CATDlgPushButton (this,"NewZoneButton");
	if (_pNewZoneButton)
	{
		_pNewZoneButton->SetIconName("I_CAASmiNewZone");;
		_pNewZoneButton->SetGridConstraints( 3, 0, 1, 1, CATGRID_4SIDES);

		// Adds a callback 
		AddAnalyseNotificationCB(
					_pNewZoneButton,
					_pNewZoneButton->GetPushBActivateNotification(),
					(CATCommandMethod) &CAASmiUserOperationGeometryPanel::NewZone,NULL);
	}
	// Creates a label for NEW ZONE
	CATDlgLabel *pNewZoneLabel = new CATDlgLabel(this,"NewZoneLabel");
	if (pNewZoneLabel)
	{
		pNewZoneLabel->SetGridConstraints( 3, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	}

	// Creates a push button for EXPORT
	_pExportButton = new CATDlgPushButton (this,"ExportButton");
	if (_pExportButton)
	{
		_pExportButton->SetIconName("I_CAASmiExport");;
		_pExportButton->SetGridConstraints( 4, 0, 1, 1, CATGRID_4SIDES);

		// Adds a callback 
		AddAnalyseNotificationCB(
					_pExportButton,
					_pExportButton->GetPushBActivateNotification(),
					(CATCommandMethod) &CAASmiUserOperationGeometryPanel::Export,NULL);
	}
	// Creates a label for EXPORT
	CATDlgLabel *pExportLabel = new CATDlgLabel(this,"ExportLabel");
	if (pExportLabel)
	{
		pExportLabel->SetGridConstraints( 4, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
	}


	// Gets guide parameter of CAA machining feature
	_spGuide = NULL_var;
	if (!!ispMachFeature)
	{
		CAAISmiUserMachFeature * pUserMachFeature = NULL;
		HRESULT RC = ispMachFeature->QueryInterface(IID_CAAISmiUserMachFeature, (void**) &pUserMachFeature);
		if (SUCCEEDED(RC))
		{
			pUserMachFeature->GetGuideParameter(_spGuide);
			if (!!_spGuide)
			{
				// Adds a callback on the Guide in order to set the sensitivity of push buttons
				CATIModelEvents * pModelEvents = NULL;
				RC = _spGuide->QueryInterface(IID_CATIModelEvents, (void**) &pModelEvents);
				if (SUCCEEDED(RC))
				{
					CATNotificationDispatcher * pDispatch = pModelEvents->GetDispatcher();
					if (pDispatch)
					{
						AddCallback(pDispatch,
									pDispatch->GetConnexion(),
									(CATSubscriberMethod)&CAASmiUserOperationGeometryPanel::UpdateButtons,NULL);
						UpdateButtons(NULL,NULL,NULL,NULL,NULL);
					}

					pModelEvents->Release();
					pModelEvents = NULL;
				}
			}
			pUserMachFeature->Release();
			pUserMachFeature = NULL;
		}
	}
}

//========================================================================
// Destructor
//========================================================================
CAASmiUserOperationGeometryPanel::~CAASmiUserOperationGeometryPanel()
{
	_pSelCurveButton = NULL;
	_pSelZoneButton  = NULL;
	_pNewZoneButton  = NULL;
	_pExportButton   = NULL;
}

//========================================================================
// CB SelectCurve
//========================================================================
void CAASmiUserOperationGeometryPanel::SelectCurve ( CATCommand          *iPublisher,
													 CATNotification     *iNotification,
													 CATCommandClientData iUsefulData)
{
	// Sends Selection command
	new CAASmiUserOperationGeometrySelCom (this,_spGuide);
}

//========================================================================
// CB SelectZone
//========================================================================
void CAASmiUserOperationGeometryPanel::SelectZone ( CATCommand          *iPublisher,
													CATNotification     *iNotification,
													CATCommandClientData iUsefulData)
{
	if (!!_spGuide)
	{
		CATIEdit * pEdit = NULL;
		HRESULT RC = _spGuide->QueryInterface(IID_CATIEdit, (void**) &pEdit);
		if (SUCCEEDED(RC))
		{
			// For zone management
			pEdit->Activate(NULL);
			pEdit->Release();
			pEdit = NULL;
		}
	}
}

//========================================================================
// CB RemoveAll
//========================================================================
void CAASmiUserOperationGeometryPanel::RemoveAll ( CATCommand          *iPublisher,
												   CATNotification     *iNotification,
												   CATCommandClientData iUsefulData)
{
	if (!!_spGuide)
	{
		CATISmgNcGeometryParameter * pSmgParameter = NULL;
		HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
		if (SUCCEEDED(RC))
		{
			pSmgParameter->RemoveAll();
			pSmgParameter->Release();
			pSmgParameter = NULL;
		}
	}
}

//========================================================================
// CB NewZone
//========================================================================
void CAASmiUserOperationGeometryPanel::NewZone ( CATCommand          *iPublisher,
												 CATNotification     *iNotification,
												 CATCommandClientData iUsefulData)
{
	// Get Manufacturing Feature Container
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
		CATBaseUnknown_var spNcFeature = NULL_var;;
		
		// Creates a empty zone
		CATISmgFactory * pSmgFactory = NULL;
		HRESULT RC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**)&pSmgFactory);
		if (SUCCEEDED(RC))
		{
			pSmgFactory->CreateNcGeometryFeature(SmgEdgeType,spNcFeature);
			pSmgFactory->Release();
			pSmgFactory = NULL;
		}

		// Adds it in the guide parameter
		if (!!_spGuide && !!spNcFeature)
		{
			CATISmgNcGeometryParameter * pSmgParameter = NULL;
			RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
			if (SUCCEEDED(RC))
			{
				pSmgParameter->Add(spNcFeature);
				pSmgParameter->Release();
				pSmgParameter = NULL;
			}
		}

	}
}

//========================================================================
// CB Export
//========================================================================
void CAASmiUserOperationGeometryPanel::Export ( CATCommand          *iPublisher,
												CATNotification     *iNotification,
												CATCommandClientData iUsefulData)
{
	if (!!_spGuide)
	{
		CATISmgNcGeometryParameter * pSmgParameter = NULL;
		HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
		if (SUCCEEDED(RC))
		{
			pSmgParameter->Export();
			pSmgParameter->Release();
			pSmgParameter = NULL;
		}
	}
}

//========================================================================
// CB UpdateButtons
//========================================================================
void CAASmiUserOperationGeometryPanel::UpdateButtons( CATCallbackEvent  iEvent, 
													  void            * iFrom,
													  CATNotification * iNotification,
													  CATSubscriberData iClientData,
													  CATCallback       iCallBack ) 
{
	if (!!_spGuide)
	{
		CATISmgNcGeometryParameter * pSmgParameter = NULL;
		HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
		if (SUCCEEDED(RC))
		{
			CATListValCATBaseUnknown_var ListeOfZones;
			pSmgParameter->GetNcGeometryFeatures(ListeOfZones);
			if (ListeOfZones.Size() >0)
			{
				_pSelCurveButton->SetSensitivity(CATDlgDisable);
				_pExportButton->SetSensitivity(CATDlgDisable);
				_pNewZoneButton->SetSensitivity(CATDlgEnable);
				_pSelZoneButton->SetSensitivity(CATDlgEnable);
			}
			else
			{
				CATLISTP(CATGeometry) ListOfGeometry;
				pSmgParameter->GetGeometricElements(ListOfGeometry);
				if (ListOfGeometry.Size() > 0)
				{
					_pSelCurveButton->SetSensitivity(CATDlgEnable);
					_pExportButton->SetSensitivity(CATDlgEnable);
					_pNewZoneButton->SetSensitivity(CATDlgDisable);
					_pSelZoneButton->SetSensitivity(CATDlgDisable);
				}
				else
				{
					_pSelCurveButton->SetSensitivity(CATDlgEnable);
					_pExportButton->SetSensitivity(CATDlgEnable);
					_pNewZoneButton->SetSensitivity(CATDlgEnable);
					_pSelZoneButton->SetSensitivity(CATDlgEnable);
				}
			}

			pSmgParameter->Release();
			pSmgParameter = NULL;
		}
	}
}
