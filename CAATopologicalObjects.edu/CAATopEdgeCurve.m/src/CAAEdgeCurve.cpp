#include <iostream.h>
#include "fstream.h"

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management 

// NewTopologicalObjects
#include "CATEdge.h"

// GeometricObjects
#include "CATEdgeCurve.h"
#include "CATEdgeCurveIterator.h"
#include "CATCurve.h"
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
   
    // -----------------------------------------------------------
    // 2 - Retrieve the initial edge
    // -----------------------------------------------------------
	//
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(1857);  
	
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATEdge * piEdge = (CATEdge *) piCGMObj1;
	
    // -----------------------------------------------------------
    // 3 - Retrieve the edge curve
    // -----------------------------------------------------------
    //
	// (a) - retrieve the edge curve from the edge
	//
	CATOrientation  OriECrvVsEdge  =  CATOrientationUnknown;
	CATEdgeCurve * pEdgeCurve = piEdge->GetCurve(&OriECrvVsEdge );
	//
    // (b) - retrieve the "ref curve"
	//
	CATCurve * RefCurve = pEdgeCurve->GetRefCurve();
    if (!RefCurve) return(1);
    int rctag = RefCurve->GetPersistentTag(); // debug
	cout << "ref curve " <<  rctag << endl;  
    //
    // (c) - scans the edge curve
	//       In this particular case, the scanned edge curve embeddes
	//       two edge curves. 
	//               !----------- Simcurve 393 
    //               !                    !--------- PLine 385
	//               !                    !--------- PLine 386
	//               !----------- Intcurve 1843
    //               !                    !--------- PLine 1841
	//               !                    !--------- PLine 1842
	//       SetLeafScan(1) returns the four PLines. 
    //                                               385
    //                                               386
    //                                              1841
    //                                              1842
    //       SetLeafScan(0) returns all the curves (the edge curve itself + sub edge curves + Pcurves).
	//                                              1858
	//                                               393
    //                                               385
    //                                               386
	//                                              1843
    //                                              1841
    //                                              1842
	CATLISTP(CATCurve) oLCurve ;
	const CATCurve* CrvInsideEC = NULL;
	CATEdgeCurveIterator Iterator(pEdgeCurve);   // create the iterator
	Iterator.SetLeafScan(0);                     
	Iterator.SetRepetitions(0);  

	while ( CrvInsideEC = Iterator.Next() )
	{
		rctag = CrvInsideEC->GetPersistentTag();
		if (CrvInsideEC->IsATypeOf(CATEdgeCurveType))
		{
			cout << "curve with tag " << rctag << " is an edge curve" <<  endl; //debug
		}
		else
            cout << "curve with tag " << rctag << " is a CATCurve imbedded in an edge curve" <<  endl; //debug
	}

	// ----------------------------------------------------------
	// 4 - Close the application
	// ----------------------------------------------------------
	//
	//pConfig->Release();
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
