/**
* @quickReview CRE 03:10:17
*/
//=============================================================================
//  
// COPYRIGHT DASSAULT SYSTEMES  2002
// Sample code for : Geometric Modeler
// Mission         : Explain how to compute the area of a CATFace and the length of a CATEdge 
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Create the geometric factory
//   how to          2- Create the olid sphere
//                   3- Scan the topology  
//                   4- Compute the area of each face
//                   5- Compute the length of each edge
//                   6- Write the model and close the container  
//
// How to run it   : CAATopProperties  // to run whithout storing the NCGM file
//                   CAATopProperties file.NCGM // to run and store the result 
//                   in file.NCGM                                  
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"              // Mathematical point
#include "CATSoftwareConfiguration.h" 

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Management of the geometry factory

// NewTopological objects
#include "CATBody.h" 
#include "CATFace.h" 
#include "CATEdge.h"

// TopologicalOperators
#include "CATSolidSphere.h"
#include "CATDynMassProperties3D.h" 

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
	
 //-----------------------------------------------------------------------------
 // 1- Initialize the factory
 //-----------------------------------------------------------------------------
	
 CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
 if (NULL==piGeomFactory) return (1);
 
 //-----------------------------------------------------------------------------
 // 2- Create the sphere 
 //-----------------------------------------------------------------------------

 CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
 CATTopData topdata(pConfig); 
 
 CATMathPoint p1(0,0,0);  // the sphere center
 
 CATSolidSphere * pSphereOpe = ::CATCreateSolidSphere(piGeomFactory, 
     &topdata,
     p1,
     100.0); // the radius

 if (NULL == pSphereOpe)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }	
  
 pSphereOpe -> Run();
 
 CATBody * pBodySphere = pSphereOpe -> GetResult();
 if (NULL == pBodySphere)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	
 delete pSphereOpe; pSphereOpe=NULL;

 //-----------------------------------------------------------------------------
 // 2- Scan the topology
 //-----------------------------------------------------------------------------

 CATLISTP(CATCell) listFaces = NULL;  // the list of faces
 CATLISTP(CATCell) listEdges = NULL;  // the list of edges

 pBodySphere ->GetAllCells(listFaces,2);
 pBodySphere ->GetAllCells(listEdges,1);
 CATLONG32 nbFaces = listFaces.Size(); 
 CATLONG32 nbEdges = listEdges.Size();
 
 cout << "nb faces " << nbFaces << endl;  // 4 faces are expected
 cout << "nb edges " << nbEdges << endl;  // 6 edges are expected

 //-----------------------------------------------------------------------------
 // 3- Retrieve the area of each face 
 //-----------------------------------------------------------------------------

 int i = 1;
for (;(i <= nbFaces)  ;i++) 
 {
     CATFace * pFace = (CATFace *)listFaces[i];
     CATDynMassProperties3D * pDynMassOpe0 = 
         CATDynCreateMassProperties3D(&topdata, pFace ) ;
     if (NULL == pDynMassOpe0)
     {
      ::CATCloseCGMContainer(piGeomFactory);
       return (1);
     }	
     // Expected area 4*PI*(R**2)/4
     cout << "Face " << i << " area: " << pDynMassOpe0->GetWetArea() << endl;
     delete pDynMassOpe0; pDynMassOpe0=NULL;
 }


 //-----------------------------------------------------------------------------
 // 4- Retrieve the length of each edge
 //-----------------------------------------------------------------------------

 for (i=1;(i <= nbEdges)  ;i++) 
 {
     CATEdge * pEdge = (CATEdge *)listEdges[i];
     if (pEdge == NULL) return 1;
     CATDynMassProperties3D * pDynMassOpe1 = 
         CATDynCreateMassProperties3D(&topdata, pEdge ) ;
     if (NULL == pDynMassOpe1)
     {
         ::CATCloseCGMContainer(piGeomFactory);
         return (1);
     }	
     
     cout << "Edge " << i << " length: " << pDynMassOpe1->GetLength() << endl;
     cout << pEdge->GetPersistentTag() << endl;
     delete pDynMassOpe1; pDynMassOpe1=NULL;
 }

 //-----------------------------------------------------------------------------
 // 7- Write the model and close the container
 //-----------------------------------------------------------------------------
 //
 // Release the configuration
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
