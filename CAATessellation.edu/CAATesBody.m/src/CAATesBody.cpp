/**
* @quickReview CRE 04:01:28
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Tessellation
// Mission         : How to use a tessellation operator. 
//
// Type            : Batch program
// Inputs          : path to a location to write the result
// Outputs         : Return Codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer 
//
// Illustrates:
//					1- Creates the geometric factory
//					2- Creates the body representing a quarter of sphere.
//					3- Tessellates the body
//					4- Retrieves the vertices in one shot
//					     Retrieves the strips one by one and draw geometric lines
//						 Retrieves the isolated triangles one by one and draw geometric lines
//					5- Stores the model
//
// How to run it   : CAATesBody            // to run whithout storing the NCGM file
//                   CAATesBody  file.NCGM // to run and store the result in file.NCGM   
//=============================================================================

#include <iostream.h>
#include <assert.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMath.h"                   // Mathematical base function
#include "CATMathPoint.h"              // Mathematical point
#include "CATMathAxis.h"               // Axis system
#include "CATMathConstant.h"           // for the CATPI constant
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Geometry factory management
#include "CATSphere.h"                 // Geometric sphere                
#include "CATLine.h"                   // Geometric line
#include "CATSurLimits.h"              // Limits on a surface
 
// Topology
#include "CATFace.h"                   // Face
#include "CATBody.h"                   // Body
#include "CATTopData.h"                // TopData of an operator

// TopologicalOperators
#include "CATTopSkin.h"                // to create the body to tessellate

// Tessellation
#include "CATBodyTessellator.h"        // Body tessellator
#include "CATTessPointIter.h"          // Result of the tessellation: the points
#include "CATTessStripeIter.h"         // Result of the tessellation: the stripe
#include "CATTessPolyIter.h"           // Result of the tessellation: the polygons
#include "CATTessTrianIter.h"          // Result of the tessellation: the triangles 
#include "CATTessFanIter.h"            // Result of the tessellation: the triangles 

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
 // 1-Initializes the factory
 //-----------------------------------------------------------------------------
	
 CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
 if (NULL==piGeomFactory) return (1);
	
 //-----------------------------------------------------------------------------
 // 2-Creates a geometric sphere
 //-----------------------------------------------------------------------------
	
 CATSphere * piSphere=piGeomFactory->CreateSphere
     (CATMathAxis(CATMathPoint(20,0,0)),10,0,CATPIBY2,0,CATPIBY2);
 if (NULL==piSphere)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

	
 //
 // ... and the body
 //
 CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
 CATTopData topdata(pConfig);
 CATSurLimits limits;
 piSphere->GetLimits(limits);
 CATTopSkin *pSkinOper = ::CATCreateTopSkin (piGeomFactory,&topdata,piSphere,&limits);
 if (NULL==pSkinOper)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 pSkinOper->Run();
 CATBody * piBody=pSkinOper->GetResult();
 if (NULL==piBody)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 delete pSkinOper;
 pSkinOper = NULL;
 pConfig->Release();

 //-----------------------------------------------------------------------------
 // 3- Tessellates the body
 //-----------------------------------------------------------------------------
 // step and angle by default
 //
 double sag   = 0.1;
 CATBodyTessellator * pTessellator = new CATBodyTessellator(piBody,sag);
 if (NULL==pTessellator)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 pTessellator -> Run();
	
 //-----------------------------------------------------------------------------
 // 4- Gets the results
 //-----------------------------------------------------------------------------
 CATBoolean isPlanar;
 CATTessPointIter *    pVertices  = NULL;
 CATTessStripeIter *   pStrips    = NULL;
 CATTessFanIter *      pFans      = NULL;
 CATTessPolyIter *     pPolygons  = NULL;
 CATTessTrianIter *    pTriangles = NULL;

 float  (* aCoord)[3] = NULL;
 int     * aNuPts     = NULL;
 CATLine * piln       = NULL;
	
 // Retrieves all the body faces. 
 //
 CATLISTP(CATCell) faces;
 piBody->GetAllCells( faces,2); 
 int numberOfFaces = faces.Size();
	
 for (int i=1 ; i<=numberOfFaces ; i++)
 { 
   // 
   // for each face, retrieve the tessellation results.
   //
   CATFace * piFace = (CATFace*) faces[i];	
   pTessellator -> GetFace(piFace,isPlanar,&pVertices,&pStrips,&pFans,&pPolygons,&pTriangles);
   //
   // vertices (in one shot)
   //
   if(NULL != pVertices)
   {
   CATLONG32 nbp=pVertices->GetNbPoint();
   aCoord = new float[nbp][3];
   pVertices->GetPointXyzAll(aCoord);
   }
		
   //
   // strips (one by one) 
   //
   if(NULL != pStrips)
	 {
     // size of the maximum allocation
     CATLONG32 nbs=0;
     while (0==(pStrips->IsExhausted()))
     {
       nbs=CATMax(nbs,pStrips->GetStriNbPts());
       pStrips->GoToNext();
     }
     //
     // allocation
     //
     aNuPts=new int[nbs];
     //
     // from the beginning again to retrieve the results
     //
     pStrips->Reset();
     while (0==(pStrips->IsExhausted()))
     {	
       nbs=pStrips->GetStriNbPts();
				
       pStrips->GetStriNuPts(aNuPts);
       // interior lines of the strip
       int j = 0;
for (;j<nbs-1;j++)
		{
         piln= piGeomFactory->CreateLine(
             CATMathPoint( aCoord[aNuPts[j]][0]  ,aCoord[aNuPts[j]][1]  ,aCoord[aNuPts[j]][2]),
             CATMathPoint( aCoord[aNuPts[j+1]][0],aCoord[aNuPts[j+1]][1],aCoord[aNuPts[j+1]][2]) );
		}
       // boundary of the strip
				
       for (j=0;j<nbs-2;j=j+2)
		{
         piln= piGeomFactory->CreateLine(
             CATMathPoint( aCoord[aNuPts[j]][0]  ,aCoord[aNuPts[j]][1]  ,aCoord[aNuPts[j]][2]),
             CATMathPoint( aCoord[aNuPts[j+2]][0],aCoord[aNuPts[j+2]][1],aCoord[aNuPts[j+2]][2]) );
		}
				
				
       for (j=1;j<nbs-2;j=j+2)
		{
         piln= piGeomFactory->CreateLine(
             CATMathPoint( aCoord[aNuPts[j]][0]  ,aCoord[aNuPts[j]][1]  ,aCoord[aNuPts[j]][2]),
             CATMathPoint( aCoord[aNuPts[j+2]][0],aCoord[aNuPts[j+2]][1],aCoord[aNuPts[j+2]][2]) );
		}
							
       pStrips->GoToNext();
     }
     delete [] aNuPts;
     aNuPts = NULL;
	 }
   //
   // isolated triangles (one by one)
   //
		
   if(NULL != pTriangles)
   {
     pTriangles->Reset();
     while (0==(pTriangles->IsExhausted()))
     {	
       int aNuP[3];
       pTriangles->GetTrianNuPts(aNuP);
       piln= piGeomFactory->CreateLine(
           CATMathPoint( aCoord[aNuP[0]][0],aCoord[aNuP[0]][1],aCoord[aNuP[0]][2]),
           CATMathPoint( aCoord[aNuP[1]][0],aCoord[aNuP[1]][1],aCoord[aNuP[1]][2]) );
       piln= piGeomFactory->CreateLine(
           CATMathPoint( aCoord[aNuP[1]][0],aCoord[aNuP[1]][1],aCoord[aNuP[1]][2]),
           CATMathPoint( aCoord[aNuP[2]][0],aCoord[aNuP[2]][1],aCoord[aNuP[2]][2]) );
       piln= piGeomFactory->CreateLine(
           CATMathPoint( aCoord[aNuP[0]][0],aCoord[aNuP[0]][1],aCoord[aNuP[0]][2]),
           CATMathPoint( aCoord[aNuP[2]][0],aCoord[aNuP[2]][1],aCoord[aNuP[2]][2]) );
				
       pTriangles->GoToNext();
     }
			
   }

   //
   // fans
   //
   
   if(NULL != pFans)
   {
       // size of the maximum allocation
       CATLONG32 nbs=0;
       while (0==(pFans->IsExhausted()))
       {
           cout << pFans->GetFanNbPts() << endl;
           nbs=CATMax(nbs,pFans->GetFanNbPts());
           pFans->GoToNext();
       }
       //
       // allocation
       //
       aNuPts=new int[nbs];
       
       // from the beginning again to retrieve the results
       //
       pFans->Reset();
       while (0==(pFans->IsExhausted()))
       {	
           nbs=pFans->GetFanNbPts();
           
           pFans->GetFanNuPts(aNuPts);
           // 
           for (int j=0;j<nbs-2;j++)
           {
               piln= piGeomFactory->CreateLine(
                   CATMathPoint( aCoord[aNuPts[0]][0],aCoord[aNuPts[0]][1]  ,aCoord[aNuPts[0]][2]),
                   CATMathPoint( aCoord[aNuPts[j+1]][0],aCoord[aNuPts[j+1]][1],aCoord[aNuPts[j+1]][2]) );
               piln= piGeomFactory->CreateLine(
                   CATMathPoint( aCoord[aNuPts[j+1]][0]  ,aCoord[aNuPts[j+1]][1]  ,aCoord[aNuPts[j+1]][2]),
                   CATMathPoint( aCoord[aNuPts[j+2]][0],aCoord[aNuPts[j+2]][1],aCoord[aNuPts[j+2]][2]) );
           }
           
           piln= piGeomFactory->CreateLine(
               CATMathPoint( aCoord[aNuPts[0]][0]  ,aCoord[aNuPts[0]][1]  ,aCoord[aNuPts[0]][2]),
               CATMathPoint( aCoord[aNuPts[nbs-1]][0],aCoord[aNuPts[nbs-1]][1],aCoord[aNuPts[nbs-1]][2]) );  
           
           pFans->GoToNext();
       }
       delete [] aNuPts;
       aNuPts = NULL;
   }
delete [] aCoord;
aCoord = NULL;
}
   
	
 delete pTessellator;
 pTessellator = NULL;

 //-----------------------------------------------------------------------------
 // 5- Writes the model
 //-----------------------------------------------------------------------------
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


