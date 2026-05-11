
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2008
//                 
// Mission         : Use of CATICGMDynAdvancedDraft.
//                   Create an advanced draft on an input body, enabling untwisting.
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Identity the input body, the faces to be drafted, and the neutral face
//                   2- Perform the advanced draft operation
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATMathDirection.h"

// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory

// TopologicalOperators
#include "CATICGMDynAdvancedDraft.h"
#include "CATDynDraftAngle.h"                      // Topological wire
#include "CATDynDraftRibbon.h" 
#include "CATDynDraftDomain.h" 

// NewTopologicalObjects
#include "CATBody.h"
#include "CATFace.h"
#include "CATTopData.h"                      // Topdata of an operator

int CAAAdvancedDraft(CATGeoFactory *iFactory, CATTopData *iTopData, CATBody *iBody, CATLISTP(CATFace) &iFaces, 
					 CATFace *iNeutralFace, double iDraftAngle, CATMathDirection& iDraftDir)
{
    int rc = 0;

    if (NULL==iFactory || NULL==iTopData || NULL==iBody || NULL == iNeutralFace)
    { 
        cout << "Null pointer in CAAAdvancedDraft" << endl;
        return (1);
    } 
 
	// ----------------------------------------------------------------------------
	// 1 -  Create the draft
	// -----------------------------------------------------------------------------
	//
	// (a) - Create a draft angle from the specified list of faces and an angle
	//
	CATDynDraftAngle *pDraftAngle = new CATDynDraftAngle(iFaces, iDraftAngle); 
	CATListPtrCATDynDraftAngle listDraftAngles;
	listDraftAngles.Append(pDraftAngle);
	//
	// (b) - Create a draft ribbon from the specified list of angles
	//
	CATDynDraftRibbon *pDraftRibbon = new CATDynDraftRibbon(listDraftAngles); 
 
	//
	// (c) - Create a draft domain from the specified list of ribbons, draft direction and neutral face.
	//
	CATListPtrCATDynDraftRibbon listRibbons;
	listRibbons.Append(pDraftRibbon);
	CATDynDraftDomain *pDraftDomain = new CATDynDraftDomain(iDraftDir, CATDynDraftDomainNeutral, iNeutralFace, listRibbons);
 
	//
	// (d) - Create the advanced draft operator, append the draft domain and enable untwisting
	//
	CATICGMDynAdvancedDraft *pDraftOp = CATCGMCreateDynAdvancedDraft(iFactory, iTopData, iBody, CATDynBasic);
	if (NULL==pDraftOp)
	{
		return (1);
	}
	pDraftOp->Add(pDraftDomain);
	pDraftOp->SetAutomaticUntwistMode(TRUE);

	// ----------------------------------------------------------------------------
	// 2 -  Run the draft operation
	// -----------------------------------------------------------------------------
	cout << "Run the operator ..." << endl;
	pDraftOp->Run(); 

	// ----------------------------------------------------------------------------
	// 3 -  Retrieve the drafted body
	// -----------------------------------------------------------------------------
	CATBody * pDraftBody = NULL;
	pDraftBody = pDraftOp->GetResult();

	// ----------------------------------------------------------------------------
	// 4 -  Clean up
	// -----------------------------------------------------------------------------
	if(NULL != pDraftAngle)
	{
		delete pDraftAngle;
		pDraftAngle = NULL;
	}
	if(NULL != pDraftRibbon)
	{
		delete pDraftRibbon;
		pDraftRibbon = NULL;
	}
	if(NULL != pDraftDomain)
	{
		delete pDraftDomain;
		pDraftDomain = NULL;
	}
	if(NULL != pDraftOp)
	{
		pDraftOp->Release();
		pDraftOp = NULL;
	}

	return rc;
}

CATBody *GetInputs(CATGeoFactory *iFactory, CATFace *&oNeutralFace, CATLISTP(CATFace) &oFaces)
{
    // -----------------------------------------------------------
    // 1 - Identify the body and the faces to be drafted
    // -----------------------------------------------------------
	CATBody *pRetBody = NULL;
	if (NULL != iFactory)
	{
		//The input body
		pRetBody = (CATBody *) iFactory->FindObjectFromTag(814);

		//The neutral face
		oNeutralFace = (CATFace *) iFactory->FindObjectFromTag(1003);

		//Draft faces
		CATFace* pRetface = (CATFace *) iFactory->FindObjectFromTag(1017);
		oFaces.Append(pRetface);
		pRetface = (CATFace *) iFactory->FindObjectFromTag(979);
		oFaces.Append(pRetface);
		pRetface = (CATFace *) iFactory->FindObjectFromTag(1023);
		oFaces.Append(pRetface);
	}

	return pRetBody;
}

int CAATopAdvancedDraft(CATGeoFactory *iFactory, CATTopData *iTopData)
{
	int rc = 0;
   
	cout << "Advanced draft" << endl ;
    if (NULL == iFactory || NULL == iTopData)
    { 
        cout << "Null pointer in CAATopAdvancedDraft" << endl;
        return (1);
    } 

	// --------------------------------------------------------------------------
    // 1 - Identity the input body, the faces to be drafted, and the neutral face
    // -------------------------------------------------------------------------- 
    //
	CATFace *pNeutralFace = NULL;
	CATLISTP(CATFace) draftFaces;
	CATBody *piInputBody = GetInputs(iFactory, pNeutralFace, draftFaces);
	if (NULL == piInputBody || NULL == pNeutralFace)
	{
        cout << "Null pointer in CAATopAdvancedDraft" << endl;
        return (1);
	}

	// --------------------------------------------------------------------------
    // 2 - Perform the advanced draft operation
    // -------------------------------------------------------------------------- 
    //
	double draftAngle = 25;
	CATMathDirection draftDir(0, 0, 1);
	rc = CAAAdvancedDraft(iFactory, iTopData, piInputBody, draftFaces, pNeutralFace, draftAngle, draftDir);

	return rc;
}
