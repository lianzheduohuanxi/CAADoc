// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserMachFeature :
//
// Sample code for : CAA Machining Features Management (sample 3)
//
// Mission         : Allows you to access data of "CAASmg Machining Feature".
//
// Type            : Interactive functionality
//
//=============================================================================

// Includes
#include "CAAESmiUserMachFeature.h"
 
// Surface Machining Interfaces
#include "CATISmgNcGeometryManager.h"
#include "CATISmgNcGeometryParameter.h"

// System Interfaces
#include "CATListOfCATBaseUnknown.h"

// Tie the implementation to its interface
#include "TIE_CAAISmiUserMachFeature.h"
TIE_CAAISmiUserMachFeature( CAAESmiUserMachFeature);

#include "TIE_CATIMfgFeatureAccess.h"
TIEchain_CATIMfgFeatureAccess( CAAESmiUserMachFeature);

CATImplementClass( CAAESmiUserMachFeature,
                   CodeExtension,
                   CATBaseUnknown,
                   CAASmgMachiningFeature );
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserMachFeature::CAAESmiUserMachFeature():
    CATBaseUnknown()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserMachFeature::~CAAESmiUserMachFeature()
{
}
 
//========================================================================
// GetGuideParameter
//========================================================================
HRESULT CAAESmiUserMachFeature::GetGuideParameter (CATBaseUnknown_var &oParameter)
{
	HRESULT RC = S_OK;
	
	CATISmgNcGeometryManager * pSmgManager = NULL;
	RC = QueryInterface(IID_CATISmgNcGeometryManager, (void**) &pSmgManager);
	if (SUCCEEDED(RC))
	{
		RC = pSmgManager->GetNcGeometryParameter("CAASmgGuide",oParameter);
		pSmgManager->Release();
		pSmgManager = NULL;
	}
	
	return RC;
}

//========================================================================
// GetGuides
//========================================================================
HRESULT CAAESmiUserMachFeature::GetGuides(CATLISTP(CATGeometry) & oGeometries)
{
	HRESULT RC = S_OK;

	// Gets CAAGuide parameter
	CATBaseUnknown_var spParameter = NULL_var;
	RC = GetGuideParameter(spParameter);
	if (SUCCEEDED(RC))
	{
		CATISmgNcGeometryParameter * pSmgParameter = NULL;
		RC = spParameter->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
		if (SUCCEEDED(RC))
		{
			pSmgParameter->GetGeometricElements(oGeometries);
			pSmgParameter->Release();
			pSmgParameter = NULL;
		}
	}			
	return RC;
}

//========================================================================
// IsComplete
//========================================================================
HRESULT CAAESmiUserMachFeature::IsComplete(int &oIsComplete)
{
	HRESULT RC = S_OK;
	oIsComplete = 0;

	// Checks if geometry is selected
	CATLISTP(CATGeometry) ListOfGeometry;
	RC = GetGuides (ListOfGeometry);
	if (ListOfGeometry.Size() >0) oIsComplete = 1;

	return RC;
}
