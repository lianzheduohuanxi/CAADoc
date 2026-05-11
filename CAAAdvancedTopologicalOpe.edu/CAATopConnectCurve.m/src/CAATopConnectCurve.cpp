/**
* @quickReview CRE 07:08:21
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//                 
// Sample code for : TopologicalOperators
// Mission         : Use of CATTopSimilarCurve operator to create a connecting 
//                   curve between two curves and by specifying a base curve
//                   
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1 - Preliminary declarations
//                   2 - Retrieve the input data
//                   3 - Create the bodies to be specified as start and end points
//                   4 - Create the connection by specifying the base curve
//                   5 - Close the application
//
// How to run it   : CAATopConnectCurve  inputFile.ncgm  outputFile.ncgm 
//                   inputfile to be used is  connectCurve.ncgm
//
//                   connectCurve.ncgm is provided in the 
//                   FunctionTests/InputData folder
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management 
#include "CATPoint.h"              

// NewTopologicalObjects
#include "CATBody.h"                   
#include "CATFace.h"
#include "CATDomain.h"
#include "CATCell.h" 
#include "CATVertex.h"
#include "CATTopData.h"                // TopData of an operator

// BasicTopologicalOpe
#include "CATTopPointOperator.h"
#include "CATHybProject.h"
#include "CATCreateTopProject.h"
// TopologicalOperators
#include "CATTopSimilarCurve.h"
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (3) 
         char** iArgv)   
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
    //
    // -----------------------------------------------------------
    // 1 - Preliminary declarations
    // -----------------------------------------------------------
    //
    // (a) Loads the container 
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    //
    // (b) Configuration management
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	//
    // (c) - Create the CATTopData
	//
    CATTopData topdata(pConfig, NULL);
	
	//
    // -----------------------------------------------------------
    // 2 - Retrieve the data
    // -----------------------------------------------------------
    //
	// (a) - the Base Curve
	//
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(804);  
	
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBodyBaseCurve= (CATBody *) piCGMObj1;
	
	// (b) - First curve
	// 
	//
    CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(4810);  
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBodyCurve1= (CATBody *) piCGMObj2;
	
	//
	// (c) - Second curve
	//
	CATICGMObject * piCGMObj3 = piGeomFactory->FindObjectFromTag(5053);  
    if (piCGMObj3 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBodyCurve2= (CATBody *) piCGMObj3;
    
	// 
	// (d) - Vertex on 1st curve
    // 
	CATICGMObject * piCGMObj4 = piGeomFactory->FindObjectFromTag(4335);  
    if (piCGMObj4 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATVertex * piVertex1= (CATVertex *) piCGMObj4;
	
    // 
	// (e) - Vertex on 2nd curve
	//
    //
	CATICGMObject * piCGMObj5 = piGeomFactory->FindObjectFromTag(3833);  
	
    if (piCGMObj5 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATVertex * piVertex2= (CATVertex *) piCGMObj5;
	
	//
    // -----------------------------------------------------------
    // 3 - Create the bodies to be specified as start and end points
    // -----------------------------------------------------------
	//
	CATPoint * p1 = piVertex1->GetPoint();
    CATPoint * p2 = piVertex2->GetPoint();
	
	CATBody * BodyPoint1 = CATCreateTopPointXYZ(piGeomFactory, 
		&topdata, p1->GetX(), p1->GetY(), p1->GetZ());
	//cout << "BodyPoint1" << BodyPoint1->GetPersistentTag() << endl;
	CATBody * BodyPoint2 = CATCreateTopPointXYZ(piGeomFactory, 
		&topdata, p2->GetX(), p2->GetY(), p2->GetZ());
	//cout << "BodyPoint2" << BodyPoint2->GetPersistentTag() << endl;
	
    // -----------------------------------------------------------
    // 4 - Project points onto wires
    // -----------------------------------------------------------
	//
	CATHybProject * topLayDownOpe1 = NULL;
	topLayDownOpe1 =::CATCreateTopProject(piGeomFactory,
		&topdata, BodyPoint1, piBodyCurve1);
	if (NULL==topLayDownOpe1)
	{
		cout << "No operator created" << endl;
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	topLayDownOpe1->SetMaxDistanceValue(0);
	topLayDownOpe1->Run();
	CATBody * piBodyV1 = topLayDownOpe1->GetResult();
	delete topLayDownOpe1; 
	topLayDownOpe1 = NULL;
	//
	CATHybProject * topLayDownOpe2 = NULL;
	topLayDownOpe2 =::CATCreateTopProject(piGeomFactory,
		&topdata, BodyPoint2, piBodyCurve2);
	if (NULL==topLayDownOpe2)
	{
		cout << "No operator created" << endl;
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	topLayDownOpe2->SetMaxDistanceValue(0);
	topLayDownOpe2->Run();
	CATBody * piBodyV2 = topLayDownOpe2->GetResult();
	delete topLayDownOpe2; 
	topLayDownOpe2 = NULL;
    //
    // -----------------------------------------------------------
    // 4 - Create the bodies to be specified as start and end points
    // -----------------------------------------------------------
	//
	
	CATTopSimilarCurve * pSimilarCurve = CATCreateTopSimilarCurve(piGeomFactory, 
		&topdata, 
		piBodyBaseCurve, // the base curve
		piBodyCurve1,    // the first wire
		piBodyCurve2);   // the second wire

	if (NULL == pSimilarCurve)
	{
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
	
	pSimilarCurve->SetStartPoint(piBodyV1,piBodyCurve1); // specifies the start point
	pSimilarCurve->SetEndPoint(piBodyV2,piBodyCurve2);   // specidies the end point
	pSimilarCurve->Run();
	CATBody * pSimilCurvBody = pSimilarCurve->GetResult();
	delete pSimilarCurve;
    pSimilarCurve=NULL;
				
	// ----------------------------------------------------------
	// 5 - Close the application
	// ----------------------------------------------------------
	//
	pConfig->Release();
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
				return rc;
    }
