//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators:
//                   CREATE PATTERNS 
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Preliminary declarations
//                   2- Identify input body and faces to be patterned
//                   3- Create pattern from a list of faces
//                   4- Create pattern from a tool body
//                   5- Release  the configuration
//                   6- Write the model 
//
// How to run it   : CAAGMOperatorsPattern inputfile.NCGM outputfile.NCGM
//                   The input file is  PatternInputs.NCGM which is delivered in
//                   GMOperatorsInterfaces/FunctionTests/InputData
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator
#include "CATLISTP_CATMathTransformation.h"
#include "CATMathVector.h"
#include "CATMathTransformation.h"
#include "CATMathPoint.h"

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management
#include "CATCGMJournalList.h"

// GMModelInterfaces
#include "CATBody.h"                   // body
#include "CATFace.h"
#include "CATPlane.h"
#include "CATTopData.h"

// GMOperatorsInterfaces
#include "CATICGMTopPattern.h"
#include "CATICGMSolidCylinder.h"

int CAATopPatternFromFaces(CATGeoFactory *iFactory, CATTopData *iTopData, CATBody *iBody, 
						   CATLISTP(CATFace) &iFaces, CATBody *&oResultBody)
{
    int rc = 0;

    if (NULL == iFactory || NULL == iTopData || NULL == iBody)
    { 
        cout << "Null pointer in CAATopPatternFromFaces" << endl;
        return (1);
    }
 
	// ----------------------------------------------------------------------------
	// 1 -  Create a list of transformations for a 1D pattern
	// -----------------------------------------------------------------------------
	CATLISTP(CATMathTransformation) translationList;

	int nbOccurrences = 9;
 
	// Translation distance
	double distToNext = 40.0;
 
	int i = 1;
for (; i <= nbOccurrences; i++)
	{			
		CATMathTransformation *pTrans =
			new CATMathTransformation(CATMathVector(i * distToNext, 0, 0));
		translationList.Append(pTrans);
	}
 
	// ----------------------------------------------------------------------------
	// 2 -  Create a plane representing the pattern plane (performance)
	// -----------------------------------------------------------------------------
	CATMathPlane patternMathPlane(CATMathPoint(0, 0, 10), CATMathVector(0, 0, 1));
	CATPlane* pPatternPlane = iFactory->CreatePlane(patternMathPlane);
 
	// ----------------------------------------------------------------------------
	// 3 -  Create the pattern operator
	// -----------------------------------------------------------------------------
	CATICGMTopPattern *pPatternOp =
		CATCGMCreateTopPattern(iFactory, iTopData, iBody, pPatternPlane, iFaces, &translationList);

	if (NULL == pPatternOp)
	{
		return (1);
	}

	// ----------------------------------------------------------------------------
	// 4 -  Identify the pattern type (performance)
	// -----------------------------------------------------------------------------
	pPatternOp->SetRectPattern(nbOccurrences , translationList[1], 1, NULL);

	// ----------------------------------------------------------------------------
	// 5 -  Run the pattern operator
	// -----------------------------------------------------------------------------
	pPatternOp->Run();
	oResultBody = pPatternOp->GetResult();

	// ----------------------------------------------------------------------------
	// 6 -  Clean up
	// -----------------------------------------------------------------------------
	pPatternOp->Release();
	pPatternOp = NULL;

	for (i = 1; i <= translationList.Size(); i++)
	{
		CATMathTransformation *pTrans = translationList[i];
		delete pTrans;
		pTrans = NULL;
	}

	iFactory->Remove(pPatternPlane, CATICGMContainer::RemoveDependancies);
	pPatternPlane = NULL;

	if (NULL == oResultBody)
	{
		return (1);
	}

	return rc;
}

int CAATopPatternFromTool(CATGeoFactory *iFactory, CATTopData *iTopData, CATBody *iBody, CATBody *&oResultBody)
{
    int rc = 0;

    if (NULL == iFactory || NULL == iTopData || NULL == iBody)
    { 
        cout << "Null pointer in CAATopPatternFromTool" << endl;
        return (1);
    }
 
    // -------------------------------------------------------------------------
    // 1 - Create a solid cylinder to serve as a tool body
    // -------------------------------------------------------------------------
    //
	CATMathPoint firstPointOnAxis(-10, 190, 0);
	CATMathPoint secondPointOnAxis(-10, 190, 120);
	double cylRadius = 10.0;
    //
    // (a) - Create the operator
    //
	CATICGMSolidCylinder* pCylinderOp =
		CATCGMCreateSolidCylinder(iFactory, iTopData, firstPointOnAxis, secondPointOnAxis, cylRadius);

    if (NULL == pCylinderOp)
    {
        return (1);
    }
	pCylinderOp->Run();
    //
    // (b) - Retrieve the result
    //
    CATBody *piCylindricalTool = pCylinderOp->GetResult();
    if (NULL == piCylindricalTool)
    {
        return (1);
    }
    //
    // (c) - Delete the operator
    //
    pCylinderOp->Release();
    pCylinderOp = NULL;
    
	// ----------------------------------------------------------------------------
	// 2 -  Create a list of transformations for a 2D pattern
	// -----------------------------------------------------------------------------
	CATLISTP(CATMathTransformation) translationList;

	int nbOccurrencesX = 10;
	int nbOccurrencesY = 3;
 
	double distToNextX = 40.0;
	double distToNextY = 30.0;
 
	int i = 1;
for (; i <= nbOccurrencesX; i++)
	{			
		for (int j = 1; j <= nbOccurrencesY; j++)
		{
			CATMathTransformation * pTrans =
				new CATMathTransformation(CATMathVector(i * distToNextX, -j * distToNextY, 0));
			translationList.Append( pTrans );
		}
	}
 
	// ----------------------------------------------------------------------------
	// 3 -  Create a plane representing the pattern plane (performance)
	// -----------------------------------------------------------------------------
	CATMathPlane patternMathPlane(CATMathPoint(0, 0, 10), CATMathVector(0, 0, 1));
	CATPlane* pPatternPlane = iFactory->CreatePlane(patternMathPlane);
 
	// ----------------------------------------------------------------------------
	// 4 -  Create the pattern operator
	// -----------------------------------------------------------------------------
	CATICGMTopPattern *pPatternOp =
		CATCGMCreateTopPattern(iFactory, iTopData, CATBoolRemoval, iBody, pPatternPlane, piCylindricalTool, &translationList);

	if (NULL == pPatternOp)
	{
		return (1);
	}

	// ----------------------------------------------------------------------------
	// 5 -  Identify the pattern type (performance)
	// -----------------------------------------------------------------------------
	CATMathTransformation translation1X(CATMathVector(distToNextX, 0, 0));
	CATMathTransformation translation1Y(CATMathVector(0, -distToNextY, 0));
	pPatternOp->SetRectPattern(nbOccurrencesX, &translation1X, nbOccurrencesY, &translation1Y);

	// ----------------------------------------------------------------------------
	// 6 -  Run the pattern operator
	// -----------------------------------------------------------------------------
	pPatternOp->Run();
	oResultBody = pPatternOp->GetResult();

	// ----------------------------------------------------------------------------
	// 7 -  Clean up
	// -----------------------------------------------------------------------------
	pPatternOp->Release();
	pPatternOp = NULL;

	for (i = 1; i <= translationList.Size(); i++)
	{
		CATMathTransformation *pTrans = translationList[i];
		delete pTrans;
		pTrans = NULL;
	}
    
	iFactory->Remove(piCylindricalTool, CATICGMContainer::RemoveDependancies);
	piCylindricalTool = NULL;
	iFactory->Remove(pPatternPlane, CATICGMContainer::RemoveDependancies);
	pPatternPlane = NULL;
    if (NULL == oResultBody)
	{
		return (1);
	}
	return rc;
}

CATBody *GetInputs(CATGeoFactory *iFactory, CATLISTP(CATFace) &oFaces)
{
    // -----------------------------------------------------------
    // 1 - Identify the body and the faces to be patterned
    // -----------------------------------------------------------
	CATBody *pRetBody = NULL;
	if (NULL != iFactory)
	{

		pRetBody = (CATBody *)iFactory->FindObjectFromTag(876);

		CATFace* pRetFace = (CATFace *)iFactory->FindObjectFromTag(979);
		oFaces.Append(pRetFace);
		pRetFace = (CATFace *)iFactory->FindObjectFromTag(983);
		oFaces.Append(pRetFace);
		pRetFace = (CATFace *)iFactory->FindObjectFromTag(987);
		oFaces.Append(pRetFace);
		pRetFace = (CATFace *)iFactory->FindObjectFromTag(991);
		oFaces.Append(pRetFace);
	}

	return pRetBody;
}

int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc = 0;
	if (iArgc < 2) return (1);
    
	CATBody *piInputBody = NULL;
	char *pInputFileName = iArgv[1];
    char *pOutputFileName = NULL;
    int  toStore = 0;
	if (3 == iArgc)
	{
		toStore = 1; 
		pOutputFileName = iArgv[2];
	}

#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pInputFileName, ios::binary );
#else
    ifstream filetoread(pInputFileName);
#endif
    //
    // -----------------------------------------------------------
    // 1 - Preliminary declarations
    // -----------------------------------------------------------
    //
    // (a) Loads the container 
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL == piGeomFactory) return (1);
    //
    // (b) Configuration management
    //
    CATSoftwareConfiguration* pConfig = new CATSoftwareConfiguration();
	//
    // (c) - Create the topdata
	//
    CATTopData topdata(pConfig);

    // -----------------------------------------------------------
    // 2 - Identify input body and faces to be patterned
    // -----------------------------------------------------------
	CATLISTP(CATFace) listOfFaces;
	piInputBody = GetInputs(piGeomFactory, listOfFaces);
	if (NULL == piInputBody)
	{
        cout << "No object with the specified tag" << endl;
		return 1;
	}

	// -------------------------------------------------------------------------
    // 3 - Create pattern from a list of faces 
    // -------------------------------------------------------------------------
	CATBody *pResultBody = NULL;
	rc += CAATopPatternFromFaces(piGeomFactory, &topdata, piInputBody, listOfFaces, pResultBody);

	// -------------------------------------------------------------------------
    // 4 - Create pattern from a tool body 
    // -------------------------------------------------------------------------
	rc += CAATopPatternFromTool(piGeomFactory, &topdata, piInputBody, pResultBody);

	//piGeomFactory->Remove(piInputBody, CATICGMContainer::RemoveDependancies);
	//piGeomFactory->Remove(pResultBody, CATICGMContainer::RemoveDependancies);

    // --------------------------------------------------------------------------
    // 5 - Release  the configuration
    // --------------------------------------------------------------------------
    pConfig->Release();
    
    //---------------------------------------------------------------------------
    // 6 - Write the model
    //---------------------------------------------------------------------------
    if (1 == toStore)
    {
        cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pOutputFileName, ios::binary );
#else
        ofstream filetowrite(pOutputFileName, ios::out, filebuf::openprot);
#endif
        
        ::CATSaveCGMContainer(piGeomFactory, filetowrite);
        filetowrite.close();
    }	

    ::CATCloseCGMContainer(piGeomFactory);
    return (rc);
}

