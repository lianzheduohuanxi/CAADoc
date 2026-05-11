/**
* @quickReview CRE 04:03:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//                 
// Sample code for : AdvancedTopologicalOpe
// Mission         : Use of CATTopCleanCrvOperator
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Create the geometry factory 
//                   2- Create the curves making up the wire to be corrected 
//                   3- Create the wire to be corrected
//                      a - create the operator
//                      b - run it
//                   4- Create the CATTopCleanCrvOperator operator      
//                     4.1 - Create an operator instance
//                     4.2 - Set the parameters
//                        (a) No angle specified for the tangency criteria
//                        (b) No angle specified for the tangency criteria
//                            Cell reduction requested
//                        (c) Angle specified for the tangency criteria: 15 deg
//                            Cell reduction requested
//                            Criteria to be met on priority is deformation
//                            Maximum deformation of 0.02 specified
//                   5- Release the configuration,
//                      store the model and close the container 
//
// How to run it   : CAAAdtCleanCrv           // to run whithout storing the NCGM file
//                   CAAAdtCleanCrv file.NCGM // to run and store the result in file.NCGM 
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"        // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory
#include "CATCGMContainerMngt.h"             // Geometry factory management
#include "CATLine.h"                         // Geometrical line
#include "CATCrvLimits.h"                    // Curve limits definition

// TopologicalOperators
#include "CATTopWire.h"                      // Topological wire
                    
// NewTopologicalObjects
#include "CATTopData.h"                      // Topdata of an operator
#include "CATTopCleanCrvOperator.h"          // 

//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(2<iArgc) return (1);
    
    char *pfileName = 0;
    int  toStore = 0;
    if (2==iArgc) 
    {
        toStore = 1; 
        pfileName = iArgv[1];
    }
    
    // --------------------------------------------------------------------------
    // 1 - Initialize the factory 
    // --------------------------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL == piGeomFactory)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // --------------------------------------------------------------------------
    // 2 - Create curves  
    // -------------------------------------------------------------------------- 
    //
    CATMathPoint P0(0,0,0);
    CATMathPoint P1(10,7.5,0);
    CATMathPoint P2(20,15,-2);
    CATMathPoint P3(45,20,-5);
    CATMathPoint P4(77,23,-7);
    
    CATLine * piLine0 = piGeomFactory->CreateLine(P0,P1);
    CATLine * piLine1 = piGeomFactory->CreateLine(P1,P2);
    CATLine * piLine2 = piGeomFactory->CreateLine(P2,P3);
    CATLine * piLine3 = piGeomFactory->CreateLine(P3,P4);
    
    if (NULL==piLine0 || NULL==piLine1 || NULL==piLine2 || NULL==piLine3)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    
    // --------------------------------------------------------------------------
    // 3 - Create the wire to be corrected from the curves above
    // --------------------------------------------------------------------------
    //
    // a - Specify the arguments to be passed in the 
    //     CATCreateTopWire method   
    //
    CATLONG32 nbcurve0 = 4;
    CATCurve ** ListOfCurves0 = new CATCurve * [nbcurve0];
    CATCrvLimits * curLimits0 = new CATCrvLimits[nbcurve0];
    short * wireOrientations0 = new short[nbcurve0];
    
    ListOfCurves0[0] = (CATCurve *)piLine0;
    ListOfCurves0[1] = (CATCurve *)piLine1;
    ListOfCurves0[2] = (CATCurve *)piLine2;
    ListOfCurves0[3] = (CATCurve *)piLine3;
    
    int i = 0;
for (; i < nbcurve0 ; i++)
    {
		CATCurve * pLocalCurve = ListOfCurves0[i];
		if ( pLocalCurve != NULL )
            pLocalCurve->GetLimits(curLimits0[i]);
        wireOrientations0[i]=short(1);
    } 
    
    // b - Create the CATTopWire operator - run it - get the resulting body
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    CATTopWire * pWire0 = ::CATCreateTopWire(piGeomFactory, 
        &topdata,
        nbcurve0,
        ListOfCurves0,
        curLimits0,
        wireOrientations0);
    
    if (NULL==pWire0)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    pWire0->Run();
    
    CATBody * pWireBody0 = pWire0->GetResult();
    if (NULL==pWireBody0)
    {
        cout << "pWireBody0 NULL" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    //
    // c - Clean data
    //
    delete[] wireOrientations0; wireOrientations0=NULL;
    delete[] curLimits0; curLimits0=NULL;
    
    for (i=0; i < nbcurve0; i++)
        piGeomFactory -> Remove (ListOfCurves0[i]);
    delete [] ListOfCurves0;
    
    delete pWire0; pWire0=NULL;
    
    // --------------------------------------------------------------------
    // 4 - Create the CATTopCleanCrvOperator operator
    // --------------------------------------------------------------------
    //
    CATTopCleanCrvOperator * pCleanCrvOpe0 = NULL;
    CATBody * piCleanBody = NULL;
    
    // 4.1 - Create the operator
    //
    pCleanCrvOpe0 =::CATCreateTopCleanCrvOperator(piGeomFactory, 
        &topdata,
        pWireBody0);  
    
    if (NULL == pCleanCrvOpe0)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // 4.2 - Set the parameters
    //
    // (a) No angle specified for the tangency criteria
    //     (by default this angle is 0.5 deg)
    //     RESULT: The wire is not corrected
    //     
    // pCleanCrvOpe0->SetContinuityLevel(CATFrFCurvatureCont) ; /* Target: G2 */
    
    // (b) Angle specified for the tangency criteria: 32 deg
    //     Cell reduction requested
    //     RESULT: The wire is corrected (G2 achieved) 
    //             The Cell reduction is performed
    //
      pCleanCrvOpe0->SetContinuityLevel(CATFrFCurvatureCont) ; /* Target: G2 */
      pCleanCrvOpe0->SetCellReduction(TRUE) ;
      CATAngle tanAngle = 32;
      pCleanCrvOpe0->SetTangencyAngle(tanAngle);
      
    
    // (c) - Angle specified for the tangency criteria: 32 deg
    //     - Cell reduction requested
    //     - Criteria to be met on priority is deformation
    //     - Maximum deformation of 0.2 specified
    //     RESULT: The wire is corrected (G2 achieved)  
    //             The Cell reduction is performed
    //    
    //pCleanCrvOpe0->SetContinuityLevel(CATFrFCurvatureCont) ;  /* Target: G2 */ 
   // pCleanCrvOpe0->SetCellReduction(TRUE) ;
   // pCleanCrvOpe0->SetPriorityMode(CatTopCleanCrvDeformation) ;
   // pCleanCrvOpe0->SetMaxDeformation(0.2) ;
   // CATAngle tanAngle = 32;
   // pCleanCrvOpe0->SetTangencyAngle(tanAngle);
    
    // 4.3 -Run the operator and retrieve the resulting body
    //
    pCleanCrvOpe0->Run();
    piCleanBody = pCleanCrvOpe0->GetResult();
    cout << "Maximum deformation " << pCleanCrvOpe0->GetMaxReachedDeformation() << endl;
    
    if (NULL==piCleanBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    delete pCleanCrvOpe0;
    pCleanCrvOpe0 = NULL;
    
    // --------------------------------------------------------------------
    //  5 - Release the configuration - store the model and close the container
    // --------------------------------------------------------------------
    // 
    pConfig->Release();
    
    if(1==toStore)
    {
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pfileName, ios::binary ) ;
#else
        ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    
    ::CATCloseCGMContainer(piGeomFactory);
    return (rc);
    
}
