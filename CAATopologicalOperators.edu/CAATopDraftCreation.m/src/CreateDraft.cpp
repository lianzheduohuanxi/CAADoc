
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2008
//                 
// Mission         : Use of CATDynDraft.
//                   Create a draft on a solid block.
//
// Type            : Routine CAATopDraft
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Create the solid to be drafted
//                   2- Create a draft domain
//                   3- Create the draft
//                   4- Delete the operator
//
// Mission         : Use of CATDynDraft with limiting element.
//                   Create a draft on a solid block with a limiting element.
//
// Type            : Routine CAATopDraftLimitingElement
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Create the solid to be drafted
//                   2- Create a draft domain
//                   3- Create a limiting element
//                   4- Create the draft
//                   5- Delete the operator
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATMathVector.h"

// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory
#include "CATPlane.h"
#include "CATCrvLimits.h"                    // Curve limits definition
#include "CATSurLimits.h"

// TopologicalOperators
#include "CATDynDraft.h"
#include "CATDynDraftAngle.h"                      // Topological wire
#include "CATDynDraftRibbon.h" 
#include "CATDynDraftDomain.h" 
#include "CATSolidCuboid.h"
#include "CATICGMTopSkin.h"

// NewTopologicalObjects
#include "CATBody.h"
#include "CATFace.h"
#include "CATTopData.h"                      // Topdata of an operator

CATBody* CreateDraftBody(CATGeoFactory *iFactory, CATTopData *iTopData)
{
	CATMathPoint vO1(0, 0., 0.),  vOI1(50., 0., 0), vOJ1(0., 30., 0.),  vOK1(0., 0., 15.);
    //
    // (a) - Create the CATSolidCuboid operator
    //
    CATSolidCuboid *pBlockOp1 = ::CATCreateSolidCuboid( iFactory, 
        iTopData, 
        vO1, 
        vOI1, 
        vOJ1, 
        vOK1);
    if (NULL==pBlockOp1)
    {
        return NULL;
    }
    //
    // (b) - Retrieve the result
    //
    CATBody *piBlockBody1=NULL;
    piBlockBody1 = pBlockOp1->GetResult();
	//
	// (c) - Delete the operator
	//
	delete pBlockOp1;
	pBlockOp1 = NULL;

	return piBlockBody1;
}

CATDynDraftDomain* CreateDraftDomain( CATBody* piBlockBody1, CATDynDraftAngle *& pdraftAngle, CATDynDraftRibbon *& pdraftRibbon, CATMathDirection & oDraftDirection )
{
	if (NULL == piBlockBody1)
	{
		return NULL;
	}

	// (a) Retrieve the faces of the cylinder
	CATLISTP(CATCell) cellList;
	piBlockBody1->GetAllCells(cellList,2);

	// (b) Face to be drafted
	CATLISTP(CATFace) faceList;
	CATFace *facetoBeDrafted = (CATFace *)cellList[1];
	faceList.Append(facetoBeDrafted);
 
    // (c) Neutral face
	CATFace *neutralFace = (CATFace *)cellList[2];
    if (NULL==neutralFace)
    {
        return NULL;
    }

	// (d) Angle
    CATAngle angle = 10.0;

	// (e) Pulling direction 
	// normal to the neutral face (this is an example)
	CATMathVector  Vector;
	const  CATSurLimits*  pBox2D  =  neutralFace->Get2DBoundingBox();  
	CATSurParam  Param  (0.5,  0.5,  *pBox2D);  
	neutralFace->EvalNormal(Param,  Vector);  
	oDraftDirection  =  Vector;  

	// (f) Create the draft domain, i.e. the set of parameters
	// defining where the drafts are to be created on the initial body along with the
	// angles and pulling direction
	pdraftAngle    =  new  CATDynDraftAngle(faceList,angle); 
	CATLISTP(CATDynDraftAngle) facesAndAngles;
	facesAndAngles.Append(pdraftAngle);
	pdraftRibbon  =  new  CATDynDraftRibbon(facesAndAngles ); 
	CATLISTP(CATDynDraftRibbon) ribbons;
	ribbons.Append(pdraftRibbon);
	CATDynDraftDomain * pdraftDomain  =  new  CATDynDraftDomain(oDraftDirection,  
		CATDynDraftDomainNeutral, 
		neutralFace, 
		ribbons);  

	return pdraftDomain;
}

CATBody* CreateLimitingElement(CATGeoFactory *iFactory, CATTopData *iTopData, const CATMathDirection & iDraftDirection)
{
	CATBody* pResultBody = NULL;
	if (NULL==iFactory)
	{
		return NULL;
	}

	// (a) Create a plane
	CATPlane* pLimitingPlane = iFactory->CreatePlane(iDraftDirection, 10.0);
	if (NULL == pLimitingPlane)
	{
		return NULL;
	}

	CATSurLimits surLimits;
	pLimitingPlane->GetLimits(surLimits);

	// (b) Claim ownership of the plane object
	pLimitingPlane->SetMode(CatCGMExplicit);

	// (c) Create a body from the plane object
    CATICGMTopSkin* pSkinOp = CATCGMCreateTopSkin(iFactory, iTopData, pLimitingPlane, &surLimits);
	if (NULL == pSkinOp)
	{
		return NULL;
	}

	pSkinOp->Run();

	pResultBody = pSkinOp->GetResult();

	// (d) Delete the operator
	pSkinOp->Release();
	pSkinOp = NULL;

	// (e) Relinquish ownership of the plane object
	iFactory->Remove(pLimitingPlane, CATICGMContainer::RemoveDependancies);

	return pResultBody;
}

int CAATopDraft(CATGeoFactory *iFactory, CATTopData *iTopData)
{
	int rc = 0;

	cout << "CAATopDraft" << endl ;
    if (NULL == iFactory || NULL == iTopData)
    { 
        cout << "Null pointer in CAATopDraft" << endl;
        return (1);
    }

	// --------------------------------------------------------------------------
    // 1 - Create the solid to be drafted
    // -------------------------------------------------------------------------- 
    //
	CATBody* piBlockBody1 = CreateDraftBody(iFactory, iTopData);
    if (NULL==piBlockBody1)
    {
        return (1);
    }

	// --------------------------------------------------------------------------
	// 2 - Create a draft domain
	// -------------------------------------------------------------------------- 
	//
	CATDynDraftAngle * pdraftAngle = NULL;
	CATDynDraftRibbon * pdraftRibbon = NULL;
	CATMathDirection draftDirection;
	CATDynDraftDomain * pdraftDomain = CreateDraftDomain(piBlockBody1, pdraftAngle, pdraftRibbon, draftDirection);

	// --------------------------------------------------------------------------
	// 3 - Create the draft
	// -------------------------------------------------------------------------- 
	//
	// (a) Create the CATDynDraft operator
	CATDynDraft* pDraftOpe = CATCreateDynDraft (iFactory, iTopData, piBlockBody1, CATDynAutoJoint);
	 if (NULL==pDraftOpe)
    {
        return (1);
    }

	// (b) Add the draft domain to the operator
	pDraftOpe->Add(pdraftDomain);
	
	// (c) Run the operator
	pDraftOpe->Run();

	// (d) Get the result
	CATBody * result = pDraftOpe->GetResult();

	// --------------------------------------------------------------------------
	// 4 - Delete the operator
	// --------------------------------------------------------------------------
	//
	delete pdraftAngle; pdraftAngle=NULL;
    delete pdraftRibbon; pdraftRibbon=NULL;
	delete pdraftDomain; pdraftDomain=NULL;
	delete pDraftOpe;
	pDraftOpe = NULL;

	return rc;
}

int CAATopDraftLimitingElement(CATGeoFactory *iFactory, CATTopData *iTopData)
{
	int rc = 0;

	cout << "CAATopDraft" << endl ;
    if (NULL == iFactory || NULL == iTopData)
    { 
        cout << "Null pointer in CAATopDraft" << endl;
        return (1);
    }

	// --------------------------------------------------------------------------
    // 1 - Create the solid to be drafted
    // -------------------------------------------------------------------------- 
    //
	CATBody * piBlockBody1 = CreateDraftBody(iFactory, iTopData);
    if (NULL==piBlockBody1)
    {
        return (1);
    }

	// --------------------------------------------------------------------------
	// 2 - Create a draft domain
	// -------------------------------------------------------------------------- 
	//
	CATDynDraftAngle * pdraftAngle = NULL;
	CATDynDraftRibbon * pdraftRibbon = NULL;
	CATMathDirection draftDirection;
	CATDynDraftDomain * pdraftDomain = CreateDraftDomain(piBlockBody1, pdraftAngle, pdraftRibbon, draftDirection);
    if (NULL==pdraftDomain)
    {
        return (1);
    }

	// --------------------------------------------------------------------------
	// 3 - Create a limiting element
	// -------------------------------------------------------------------------- 
	//
	CATBody * piLimitingBody = CreateLimitingElement(iFactory, iTopData, draftDirection);
    if (NULL==piLimitingBody)
    {
        return (1);
    }

	// --------------------------------------------------------------------------
	// 4 - Create the draft
	// -------------------------------------------------------------------------- 
	//
	// (a) Create the CATDynDraft operator
	CATDynDraft* pDraftOpe = CATCreateDynDraft (iFactory, iTopData, piBlockBody1, CATDynAutoJoint);
	 if (NULL==pDraftOpe)
    {
        return (1);
    }

	// (b) Add the draft domain to the operator
	pDraftOpe->Add(pdraftDomain);

#ifdef CATIACGMV5R23
	// (c) Specify the limiting element
	pDraftOpe->AddLimiting(piLimitingBody);
#endif

	// (d) Run the operator
	pDraftOpe->Run();

	// (e) Get the result
	CATBody * result = pDraftOpe->GetResult();

	// --------------------------------------------------------------------------
	// 5 - Delete the operator
	// --------------------------------------------------------------------------
	//
	delete pdraftAngle; pdraftAngle=NULL;
    delete pdraftRibbon; pdraftRibbon=NULL;
	delete pdraftDomain; pdraftDomain=NULL;
	delete pDraftOpe;
	pDraftOpe = NULL;

	return rc;
}

