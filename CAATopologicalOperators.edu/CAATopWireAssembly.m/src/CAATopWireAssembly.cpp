//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: assembly of a non manifold wire and projection
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes. If not NULL, the model is not saved 
//                   0: ok
//                   1: pb in the caller
//                   10: error in the assembly operator
//                   11: error in the projection operator     
//
// Illustrates     : 1- Creation of the geometric factory
//                   2- Wire body creation: CATWireOperator
//                   3- Assembly
//                   4- Create the plane Body
//                   5- Projection
//                   6- factory write and close. 
//
// How to run it   : CAATopWireAssembly            // to run whithout storing the NCGM file
//                   CAATopWireAssembly  file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include <assert.h>
#include <iomanip.h>
#include "fstream.h"

// CATError
#include "CATError.h"                        // to catch errors
#include "CATErrorMacros.h"

// Mathematics
#include "CATMathPlane.h"                    // mathematical plane: CATMathOIJ
#include "CATSoftwareConfiguration.h"        // Configuration of the operator
   
// GeometricObjects
#include "CATGeoFactory.h"                   // geometry factory
#include "CATCGMContainerMngt.h"             // geometry factory management
#include "CATPlane.h"                        // geometric plane

// TopologicalObjects
#include "CATBody.h"                         //  body
#include "CATTopData.h"                      // TopData of an operator

// BasicTopologicalOpe
#include "CATTopPointOperator.h"             // point body creation
#include "CATTopLineOperator.h"              // line body creation

// TopologicalOperators
#include "CATCreateTopAssemble.h"            // wire assembly
#include "CATHybAssemble.h"                  // the projection operator
#include "CATTopSkin.h"                      // skin body creation
#include "CATCreateTopProject.h"             // projection on a body
#include "CATHybProject.h"                   // projection on a body



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

 //
 // 1-Initializes the factory 
 //
	
 CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
 if (NULL == piGeomFactory)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
 else {
  
 ////////////////////////////////////////////////////////////////////////
 // 2- Creates the lines and circles of the profile
 ////////////////////////////////////////////////////////////////////////

 ListPOfCATBody bodies;
 CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
 if (NULL == pConfig)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
 else {
 CATTopData topdata(pConfig);
 // first point body
 CATBody * piPoint1 = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,0., 50.,0.);
 // second point body
 CATBody * piPoint2 = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,0.,100.,0.);
 // first line body
 CATBody * piBody   = ::CATCreateTopLineFromPoints(piGeomFactory,&topdata,piPoint1,piPoint2);
 bodies.Append(piBody);

 CATBody * piPoint3 = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,-45.,100.,0.);
 piBody   = ::CATCreateTopLineFromPoints(piGeomFactory,&topdata,piPoint2,piPoint3);
 bodies.Append(piBody);

 CATBody * piPoint4 = ::CATCreateTopPointXYZ(piGeomFactory, &topdata,45.,100.,0.);
 piBody   = ::CATCreateTopLineFromPoints(piGeomFactory,&topdata,piPoint2,piPoint4);
 bodies.Append(piBody);

 // Removes the unused objects
 // the cells that are used by the line bodies are however not removed
 piGeomFactory->Remove(piPoint1, CATICGMContainer::RemoveDependancies);
 piGeomFactory->Remove(piPoint2, CATICGMContainer::RemoveDependancies);
 piGeomFactory->Remove(piPoint3, CATICGMContainer::RemoveDependancies);
 piGeomFactory->Remove(piPoint4, CATICGMContainer::RemoveDependancies);

 ////////////////////////////////////////////////////////////////////////
 // 3- Assembles the wires
 ////////////////////////////////////////////////////////////////////////

 CATHybOperator* pHybOp=NULL;
 CATBody * piAssembledBody=NULL;
 CATTry                  // to catch the errors
 {
   CATHybAssemble* pHybOp = ::CATCreateTopAssemble(piGeomFactory, &topdata,&bodies);	  

   if (NULL!=pHybOp)
   {
	  pHybOp->Run();
      piAssembledBody = pHybOp->GetResult();
	  delete pHybOp;
	  pHybOp = NULL;
   }
 }
 CATCatch(CATError,err)
 {
	 cout << (err->GetNLSMessage()).ConvertToChar() << endl;
   return(10);
 }
 CATEndTry
 if (NULL==piAssembledBody)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 ////////////////////////////////////////////////////////////////////////
 // 4- Creates the plane body for the future projection.	
 ////////////////////////////////////////////////////////////////////////
 CATPlane * piPlane = piGeomFactory->CreatePlane(CATMathOIJ);
 if (NULL==piPlane)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 CATSurLimits limits;
 piPlane->GetLimits(limits);
 CATTopSkin * piPlaneOp = CATCreateTopSkin(piGeomFactory,&topdata,piPlane,&limits);

 CATBody * piPlaneBody=NULL;
 if (NULL!= piPlaneOp)
 {
    piPlaneOp->Run();
	  piPlaneBody = piPlaneOp->GetResult();
	  delete piPlaneOp;
	  piPlaneOp = NULL;
 }
 if (NULL==piPlaneBody)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 ////////////////////////////////////////////////////////////////////////
 // 5- Projects 
 ////////////////////////////////////////////////////////////////////////
 CATBody * piProjectedBody=NULL;
 CATTry
 {
   CATHybProject * pHybPro = ::CATCreateTopProject(piGeomFactory,&topdata,piAssembledBody,piPlaneBody);

   if (NULL!=pHybPro)
   {
	   pHybPro->Run();
       piProjectedBody = pHybPro->GetResult();
	   delete pHybPro;
	   pHybPro = NULL;
   }
 }
 CATCatch(CATError,err)
 {
	 cout << (err->GetNLSMessage()).ConvertToChar() << endl;
      return(11);
 }
 CATEndTry

 // Removes the unused objects
 piGeomFactory->Remove(piAssembledBody, CATICGMContainer::RemoveDependancies);
 piGeomFactory->Remove(bodies[1], CATICGMContainer::RemoveDependancies);
 piGeomFactory->Remove(bodies[2], CATICGMContainer::RemoveDependancies);
 piGeomFactory->Remove(bodies[3], CATICGMContainer::RemoveDependancies);

 // Releases the configuration
 pConfig->Release();

}
 ////////////////////////////////////////////////////////////////////////
 // 6-Writes the model
 ////////////////////////////////////////////////////////////////////////
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
 //
 // Closes the container
 //
	
 ::CATCloseCGMContainer(piGeomFactory);
 return (rc);
}
}
