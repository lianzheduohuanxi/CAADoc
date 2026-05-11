//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2008
//                 
// Sample code for : TopologicalObjects
//                   Explains how to modify the orientation of an edge in
//                   a skin body made up of a single face.
//                   NOTE that it is not recommended to modify default orientations of
//                   geometry and topology as well. As illustrated in the use case below, it is
//                   not easy to modify topological object orientation.
//                   Operators manage automatically orientations and guarantee
//                   the consistency of the generated bodies. 
//                   As far as possible, use operators.
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1 - Preliminary declarations
//                   2 - Retrieve the external loop of the face
//                   3 - Touch the edge to be modified
//                   4 - Create a smart duplicator
//                   5 - Create the new edge
//                   6 - Replace the previous edge with the new one
//                   7 - Invert the matter side with respect to the face
//                   8 - Reset the new edge orientation with respect the underlying curve
//                   9 - Close the application
//
// How to run it   : CAATobReverseEdgeOrientation  inputFile.ncgm  outputFile.ncgm 
//                   inputfile to be used is tobereversed.ncgm 
//                   tobereversed.ncgm is provided in the 
//                   FunctionTests/InputData folder
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             
#include "CATCGMContainerMngt.h"       // Geometry factory management                
#include "CATCurve.h" 
#include "CATPCurve.h"
#include "CATGeometry.h" 
#include "CATPointOnEdgeCurve.h"
#include "CATCrvParam.h"
#include "CATEdgeCurveIterator.h"

// NewTopologicalObjects
#include "CATBody.h"                  
#include "CATFace.h"
#include "CATDomain.h"
#include "CATCell.h" 
#include "CATEdge.h" 
#include "CATVertex.h" 
#include "CATTopData.h"               
#include "CATLoop.h"
#include "CATSmartBodyDuplicator.h"

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
    CATTopData topdata(pConfig, NULL);
    //
    // (c)- Retrieve the input data from the input ncgm
    //
	// the edge to be reversed
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(436); 
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATEdge* piEdge = (CATEdge *) piCGMObj1;
	//
    // the body it belongs to 
	CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(431); 
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody* piBody = (CATBody *) piCGMObj2;
	//
	// the face bounded by the edge
	CATICGMObject * piCGMObj3 = piGeomFactory->FindObjectFromTag(433); 
    if (piCGMObj3 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATFace* piFace = (CATFace *) piCGMObj3;

	// -----------------------------------------------------------
    // 2 - Retrieve the external loop from the CATFace
    // -----------------------------------------------------------
	//
	CATLoop  *  piLoop = NULL;
	int NbDomains=piFace->GetNbDomains();
	CATDomain * piLoopDomain = NULL;
	int j = 0;
	for( j=1;j<=NbDomains;j++)
	{
		CATDomain *pDomain=piFace->GetDomain(j);
		CATLocation Location=pDomain->GetLocation();
		if(Location==CATLocationOuter)
		{
			piLoopDomain=pDomain;   // the external loop
			if  (  piLoopDomain  &&  piLoopDomain->IsATypeOf(CATLoopType)  )  
			{  
				piLoop  =  (CATLoop  *)  piLoopDomain; 
			}
			break; 
		}
	}
     
    // -----------------------------------------------------------
    // 3 - Touch the edge to be reversed (this allows you to modify 
	// the edge after the body owning is "smartduplicated"
    // -----------------------------------------------------------
    //
    piEdge->Touch(piBody);
     
    // ------------------------------------------------------------
    // 4 - Create a smart duplicator in order to modify  
    //     the topology
    // ------------------------------------------------------------
    //
    CATBody * copBody = piGeomFactory->CreateBody();
    CATSmartBodyDuplicator * smartDuplicator = 
        copBody->CreateSmartDuplicator(piBody, topdata);
    if (smartDuplicator == NULL) return (1); 
    smartDuplicator->SetFullDuplication(1);  // you duplicate the link
    smartDuplicator->Run();

    // Retrieve the duplicated edge
    CATEdge * duplicatedEdge= (CATEdge *)smartDuplicator->GetDuplicatedCell(piEdge);
    if (duplicatedEdge == NULL) return (1); 

    CATFace * duplicatedFace= (CATFace *)smartDuplicator->GetDuplicatedCell(piFace);
    if (duplicatedFace == NULL) return (1); 

	CATLoop * duplicatedLoop= (CATLoop *)smartDuplicator->GetDuplicatedDomain(piLoop);
	if (duplicatedLoop == NULL) return (1); 
    
	// ------------------------------------------------------------
    // 5 - Create the new edge
	// ------------------------------------------------------------
	//
	short EdgVsECrv;                                        // Orientation of the edge curve vs the edge
	CATVertex * OldEndVtx[2]={NULL, NULL};                  // The vertices to be switched
    CATEdgeCurve * ecrv = piEdge -> GetCurve(&EdgVsECrv);   // Retrieve the edge curve & initial orientation
	CATVertex * EndVtx[2]={NULL, NULL};                     // The new vertices after the edge orientation      
	CATPointOnEdgeCurve * OldEndPoec[2]={NULL, NULL};       // The initial point on edge curve
	piEdge -> GetVertices(OldEndVtx, OldEndVtx+1);          // Retrieve the initial vertices

	// Retrieve the points on edge curve
	OldEndPoec[0] = OldEndVtx[0]->GetGeometryOnEdge(piEdge);   
	OldEndPoec[1] = OldEndVtx[1]->GetGeometryOnEdge(piEdge);  

    // Retrieve the duplicated initial vertices
	EndVtx[0] = (CATVertex*) (smartDuplicator -> GetDuplicatedCell(OldEndVtx[0])); 
	EndVtx[1] = (CATVertex*) (smartDuplicator -> GetDuplicatedCell(OldEndVtx[1]));
    
	// Create a new edge
	CATEdge * ReplEdg = copBody -> CreateEdge();
	// Associate the new edge with a geometry and reversed curve orientation
	ReplEdg -> SetCurve(ecrv, -EdgVsECrv); // Associate the new edge with a geometry and reversed orientation
	// REMINDER:
	// CATSide defines matter side on a vertex of an edge
	// STANDARD
	// CATSideLeft: the vertex is at the edge beginning 
	// CATSideRight: the vertex is at the edge end
	static int NaturalSide[2] = { CATSideLeft, CATSideRight };
    // Specifies the boundary of this new edge
    // EndVtx[1], CATSideLeft, OldEndPoec[1] 
	// EndVtx[0], CATSideRight, OldEndPoec[0]   
	int k =0 ;
	for ( k=0; k<2; k++) {
		ReplEdg -> AddBoundingCell(EndVtx[1-k], NaturalSide[k], 0, OldEndPoec[1-k]);
	}
	EndVtx[0] -> SetGeometryOnEdge(ReplEdg, CATSideRight, OldEndPoec[0]);
	EndVtx[1] -> SetGeometryOnEdge(ReplEdg, CATSideLeft,  OldEndPoec[1]);

	// ------------------------------------------------------------
    // 6 - Replace the old edge with the new edge
	// ------------------------------------------------------------
	//
	// Get the rank of the edge in the duplicated loop
	CATOrientation ori;
	CATLONG32 Rank = duplicatedLoop -> GetCellRank(duplicatedEdge, &ori);
	// Insert the new edge at the same rank
	duplicatedLoop -> InsertEdge(ReplEdg, Rank, -ori);
	// Remove the old edge
	duplicatedLoop -> RemoveCell(duplicatedEdge);

	// ------------------------------------------------------------
    // 7 - Invert the matter side with respect to the face
	// ------------------------------------------------------------
	// 
    CATSide newside;
	CATSide curside = piEdge->GetSideOnFace(piFace) ;  // the previous side
	// Invert the side
	if(curside  ==  CATSideRight) 
	{ newside = CATSideLeft;}
	else if (curside  ==  CATSideLeft) 
	{ newside = CATSideRight;}
	else {cout << "pb" << endl;} // 
	ReplEdg -> SetSideOnFace(duplicatedFace, newside);

    // ------------------------------------------------------------
    // 8 - Reset the new edge orientation vs the underlying PCurve
	// ------------------------------------------------------------
	// 
	CATEdgeCurveIterator EdgeCurveIterator(ecrv);
	CATCurve * CurCurve = NULL;
    CATPCurve  * CurPCurve = NULL;
	while ( ( CurCurve = EdgeCurveIterator.Next() )  )
	{
		if ( ! ( CurCurve -> IsATypeOf(CATPCurveType) ) )
		{
			cout << "not a CATPCurve " << endl;
			continue;
		}
		CurPCurve  = ( CATPCurve * ) CurCurve;
	}
	
	ReplEdg -> SetGeometryOnFace(duplicatedFace,
		newside,
		CurPCurve);
 
    // ----------------------------------------------------------
    // 9 - Close the application
    // ----------------------------------------------------------
    //
	if (smartDuplicator)
		delete smartDuplicator;
	smartDuplicator = NULL;
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
