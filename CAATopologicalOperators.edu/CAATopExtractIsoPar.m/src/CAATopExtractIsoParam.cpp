/**
* @quickReview CRE 04:07:29
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//
// Sample code for : Geometric Modeler
// Mission         : Use of the GeometricObjects and TopologicalOperators frameworks
//                   Extracting the isoparametric curves passing through a point on 
//                   a surface.
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (in this case, the file is not saved)
//                   0- OK
//                   1- Null pointer detection
//
// Coding steps    : 1- Preliminary operations
//                   2- Extract isoparametric curves
//                   3- Create the isoparametric wire along V
//                   4- Relimit the wire
//                   5- Close the application
//
// How to run it   : CAATopExtractIsoParam inputfile.ncgm outputfile.ncgm 
//                   Inputfile corresponding to the tags specified herebelow is 
//                   delivered in the FunctionTeste/InputData folder of CAATopologicalOperators.edu
//                   under the name ExtractIsopar.ncgm
// ================================================================================     
//
#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"

// GeometricObjects
#include "CATGeoFactory.h"               // Geometry factory
#include "CATCGMContainerMngt.h"         // Management of the geometry factory
#include "CATPointOnSurface.h"
#include "CATSurface.h"
#include "CATCrvLimits.h"
#include "CATICGMObject.h"
 
// TopologicalOperators
#include "CATHybIntersect.h"
#include "CATCreateTopIntersect.h"  
#include "CATTopWire.h" 

// NewTopologicalObjects
#include "CATBody.h"
#include "CATFace.h"

// Error management
#include "CATError.h"              // errors
#include "CATErrorMacros.h"        // to catch errors
// -------------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(3<iArgc) return (1);
    
    char *pFileName1 = 0;
    int  toStore = 0;
    
    
    char *pFileName = NULL;
    if( 3 != iArgc ) 
    {
        cout << "one .ncgm file is missing" << endl;
        return (1);
    }
    else
    {
        toStore = 1; 
        pFileName = iArgv[1];
        pFileName1 = iArgv[2];
    }
    
    
#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pFileName, ios::binary ) ;
#else
    ifstream filetoread(pFileName) ;
#endif
    
	// -----------------------------------------------------------------------
	// (1) - Preliminary operations
	// -----------------------------------------------------------------------
	//       (a) - Get the factory
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
	if (NULL == piGeomFactory) return (1);
    CATGeoFactory * piImplicitFactory = piGeomFactory->GetImplicitGeoFactory( );
    if (NULL == piImplicitFactory) return (1);
	// 
	//       (b) - Retrieve the body which contains the surface
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(10730958);
    if (piCGMObj1 == NULL) cout << "No object with the specified tag" <<endl;
    CATBody * pInitialSurface = (CATBody *) piCGMObj1;
	if (NULL==pInitialSurface)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
	// 
	//       (c) - Retrieve the PointOnSurface
    CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(10733507);
    if (piCGMObj2 == NULL) cout << "No object with the specified tag" <<endl;
	CATPointOnSurface * pPnt = (CATPointOnSurface*) piCGMObj2;
    if (NULL==pPnt)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
	CATSurParam surParamPt;
	pPnt->GetParam(surParamPt);

	// -----------------------------------------------------------------------
	// (2) - Extract the isoparametric curves passing through pPnt
	// -----------------------------------------------------------------------
	//
    //       (a) - Get face and surface
	CATLISTP(CATCell)  faceList;      
    pInitialSurface->GetAllCells( faceList,2);
    cout << "number of faces " <<  faceList.Size() << endl;
    CATFace * myFace = (CATFace *) faceList[1];
	if (myFace == NULL) 
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    CATSurface * mySurface = myFace->GetSurface();

    //       (b) - Get face limits
    CATSurLimits *FaceLim; 
    FaceLim = (CATSurLimits *)myFace->Get2DBoundingBox();
    CATCrvLimits CurveLimits, IsoParLimit;

	//       (c) - Extract IsoParU
    CATIsoParameter isoParU = CATIsoParamU;
	CATCurve* pCATCurveU = mySurface->ExtractIsoParametricCurve(isoParU, 
		surParamPt, piGeomFactory);
	if (pCATCurveU == NULL) 
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
	//       (d) - Reset the boundary to the limits of the face
	pCATCurveU->GetLimits(CurveLimits);
	IsoParLimit = CurveLimits;
	CATSurLimits surLim;
    mySurface->GetLimits(surLim);
	IsoParLimit.GetEquivalentLimits(surLim,*FaceLim,isoParU,CurveLimits);
	//       (e) - Extract IsoParU
	CATIsoParameter isoParV = CATIsoParamV;
	CATCurve* pCATCurveV = mySurface->ExtractIsoParametricCurve(isoParV, 
		surParamPt, piGeomFactory);
	if (pCATCurveV == NULL) 
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
	//        (f) - Reset the boundaries to the limits of the face
  	pCATCurveV->GetLimits(CurveLimits);
	IsoParLimit = CurveLimits;
	CATSurLimits surLim1;
    mySurface->GetLimits(surLim1);
	IsoParLimit.GetEquivalentLimits(surLim1,*FaceLim,isoParV,CurveLimits);
    
    // -----------------------------------------------------------------------
    // (3) - Create the wire along V - result intersects the face borders
	// -----------------------------------------------------------------------
	//
    // (3a) - Create topdata
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig, NULL);

	short orientations[1] = {1};
	CATTopWire* pTopWire = CATCreateTopWire(piImplicitFactory, &topdata,
		1, &pCATCurveV, &CurveLimits, orientations);
	if (pTopWire == NULL)
	{
        ::CATCloseCGMContainer(piGeomFactory);
		if (pConfig != NULL) { pConfig->Release(); pConfig = NULL; }
        return (1);
    }
	pTopWire->Run();
	CATBody* pBody = pTopWire->GetResult();
	delete pTopWire; pTopWire=NULL;
    
	// -----------------------------------------------------------------------
    // (4) - Relimit the wire
	// -----------------------------------------------------------------------
	//
	CATHybIntersect * pIntersectOpe = NULL;
	CATTry
	{
		pIntersectOpe = CATCreateTopIntersect(piImplicitFactory, &topdata, pInitialSurface, pBody);
	}
	CATCatch(CATError,error)
	{
		cout << (error->GetNLSMessage()).ConvertToChar() << endl;
		Flush(error);
		::CATCloseCGMContainer(piGeomFactory);
		if (pConfig != NULL) { pConfig->Release(); pConfig = NULL; }
        return (1);
	}
	CATEndTry
	if (NULL != pIntersectOpe) 
	{
		pIntersectOpe->Run();
		CATBody * pBodyIntersect = pIntersectOpe->GetResult();		
		//pBodyIntersect->SetMode(CatCGMExplicit);
		delete pIntersectOpe; pIntersectOpe=NULL;
	}

	// -----------------------------------------------------------------------
    // (5) - Clean unused objects - write the model and close the container 
	// -----------------------------------------------------------------------
	//
    piImplicitFactory->Remove(pBody, CATICGMContainer::RemoveDependancies);
    pConfig->Release(); pConfig = NULL;

    if(1==toStore)
    {
        cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName1, ios::binary ) ;
#else
        ofstream filetowrite(pFileName1,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    filetoread.close();
    CATCloseCGMContainer(piGeomFactory);
	if (pConfig != NULL) { pConfig->Release(); pConfig = NULL; }
    return rc;
}
