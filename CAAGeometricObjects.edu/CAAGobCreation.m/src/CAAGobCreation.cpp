/**
* @quickReview GDR 03:10:17
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the geometric factory
//                   Creation of geometric objects. In particular, creation of foreign surfaces
//                    Definition of a foreign surface: CATForeignSurfaceData is derived. 
//                    The mathematical definition use the CAAAmtForeignFct already defined
//                    in the CAAAdvancedMathematics.edu framework mathematical function: the egg box.
//                   The CAAGobForeignSurfaceData class is defined in CAAGobForeignSurfaceData.h 
//                   The code is in CAAGobForeignSurfaceData.cpp
//                   The main creates instances of the foreign function. 
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (in this case, the file is nor saved)
//                   1- Null pointer detection
//                   2- Foreign curve limits are false
//                   3- The duplication of the curve also duplicates the underlying surface
//                   4- The transformation of the curve does not duplicated the underlying surface
//                   51 to 55- Foreign curve implementation problem
//
// Illustrates     : 1- Geometric factory creation
//                   2- Foreign surface creation
//                   3- PLine on the foreign surface creation
//                   4- Geometric object copy: the CATCloneManager
//                   5- Geometric object transformation: the CATTransfoManager 
//                   6- Evaluators: creation of the trimmed lines corresponding 
//                                  to the normals at the four corners
//                   7- Model write and factory closure.
//
// How to run it   : CAAGobCreation            // to run without storing the NCGM file
//                   CAAGobCreation  file.NCGM // to run and store the result in file.NCGM                              
//=============================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"               // Mathematica point
#include "CATMathDirection.h"           // Mathematical unitary vector
#include "CATMathTransformation.h"      // Mathematical transformation
#include "CATMathVector.h"              // Mathematical vector
#include "CATMathVector2D.h"            // Mathematical 2D vector
 
// GeometricObjects
#include "CATCGMContainerMngt.h"        // Geometric Factory management
#include "CATGeoFactory.h"              // Geometric Factory

#include "CATIForeignSurface.h"         // Foreign Surface
#include "CATSurParam.h"                // Parameter on a surface
#include "CATSurLimits.h"               // Limits on a surface
#include "CATPLine.h"                   // PLine

#include "CATCloneManager.h"            // to duplicate geometric objects
#include "CATTransfoManager.h"          // to transform geometric objects

// CAAGeometricObjects.edu
#include "CAAGobForeignSurfaceData.h"   // the new class of surface


//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
 int rc=0;
 if(2<iArgc) return (1);

 char *pfileName = NULL;
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
 // 2-Creates a foreign surface  
 // S(u,v) = iOrigin + u*iUDirection + v*iVDirection + iHeight*cos(u)*cos(v)*iUDirection^iVDirection, 
 // uMin<=u<=uMax, vMin<=v<=vMax. </pre>
 //-----------------------------------------------------------------------------

 CATMathPoint origin(50.,-10.,5.);
 CATMathDirection directionU(1.,0.,0.), directionV(0.,1.,0.);
 double uPeriod = 3. ;
 double vPeriod = 5. ;
 double height  = 7. ;
 double uMin    = -10. ;
 double uMax    = 23. ;
 double vMin    = -11. ;
 double vMax    = 34. ;

   // ------------ Creates the foreign data 
 CAAGobForeignSurfaceData* pData = 
     new CAAGobForeignSurfaceData(origin, 
                                  uPeriod*directionU,
                                  vPeriod*directionV,
                                  height/(uPeriod * vPeriod),
                                  uMin,
                                  uMax,
                                  vMin,
                                  vMax) ;
 if (NULL==pData)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 // ------------ Creates the surface
 CATIForeignSurface* piEggBox = NULL;
 piEggBox = piGeomFactory ->CreateForeignSurface(pData) ;
 if (NULL==piEggBox)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 // ------------ Just tests the the limits 
 // Retrieves them
 CATSurLimits surLimits;
 piEggBox ->GetLimits(surLimits);
 CATSurParam lowParam, highParam;
 surLimits.GetExtremities(lowParam, highParam);

 //  Tests that they are right!
 if ( (lowParam.GetParamU())  != uMin ||    
      (lowParam.GetParamV())  != vMin ||
      (highParam.GetParamU()) != uMax ||
      (highParam.GetParamV()) != vMax )     
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (2);
 }

 // Tests the set limits method
  double saveU=uMax+15.;
  highParam.SetParamU(saveU);
  surLimits.SetHigh(highParam); 
  piEggBox ->SetLimits(surLimits);// affects the new limits
  piEggBox ->GetLimits(surLimits); // reads again the limits
  CATSurParam newParam;
  surLimits.GetHigh(newParam);
  if ( saveU!=newParam.GetParamU() ) // and compares
  {
   ::CATCloseCGMContainer(piGeomFactory);
   return (51);
  }

  // Tests the max limits 
  CATSurLimits maxLimits;
  piEggBox ->GetMaxLimits(maxLimits);
  if (0==maxLimits.IsContaining(surLimits))
  {
   ::CATCloseCGMContainer(piGeomFactory);
   return (52);
  }

  //... and the internal max limits
  CATSurLimits intLimits;
  piEggBox ->GetInternalMaxLimits(1,1,intLimits);
  if (maxLimits!=intLimits)
  {
   ::CATCloseCGMContainer(piGeomFactory);
   return (53);
  }

 // Tests the extrapolation mode
 CATBoolean test= piEggBox ->Extrapolate(CATMathVector2D(1,0),NULL);
 if (test!=FALSE) 
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (54);
 }

 // Tests the knot vector methods
 if ( (NULL!= piEggBox ->GetKnotVectorU()) ||(NULL!= piEggBox ->GetKnotVectorV()) ) 
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (55);
 }
 


 //----------------------------------------------------------------------------- 
 // 3- Creates a Pline on the foreign surface
 //-----------------------------------------------------------------------------
 //
 // Defines the parameters of the Pline to create.
 // start = (1- 0.5)*surLimits.GetLow.GetParamU  + 0.5*surLimits.GetLow.GetParamV,
 //         (1- 0.2)*surLimits.GetHihg.GetParamU + 0.2*surLimits.GetHigh.GetParamV.
 CATSurParam start (0.5,0.2,surLimits);
 CATSurParam end   (0.8,0.3,surLimits);

 // Creates the Pline
 CATPLine * piPLine = piGeomFactory->CreatePLine(start,end,piEggBox);
 if (NULL==piPLine)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 //----------------------------------------------------------------------------- 
 // 4- Clones (duplicates) the PLine 
 //-----------------------------------------------------------------------------
 CATCloneManager * pCloneManager= new CATCloneManager(piGeomFactory); // single duplication by default
 if (NULL==pCloneManager)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 // Asks for the dulication of the PLine
 pCloneManager->Add(piPLine);
 // Runs the operator
 pCloneManager->Run();
 CATICGMObject* piClonedPLine=NULL;
 // Retrieves the object corresponding to the transformation of the PLine
 piClonedPLine = pCloneManager->ReadImage(piPLine);
 if (NULL==piClonedPLine)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
   
 // Retrieves the persistent tags of the underlying surface of the initial and duplicated Plines
 // as the duplication mode is single, the underlying surface must be the same
 CATULONG32  tagSurfCloned = ( ((CATPLine *)piClonedPLine )->GetSurface())->GetPersistentTag();
 CATULONG32  tagSurfPLine  = (              piPLine        ->GetSurface())->GetPersistentTag();

 if (tagSurfCloned != tagSurfPLine)    
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (3);
 }          
 delete pCloneManager;
 pCloneManager = NULL;

 //----------------------------------------------------------------------------- 
 // 5- Transforms the PLine 
 //-----------------------------------------------------------------------------
 CATMathTransformation mathTransf(CATMathVector(20.,10.,40.));

 // duplication of non-invariant objects by default
 CATTransfoManager * pTransfoManager = new CATTransfoManager(mathTransf,piGeomFactory); 
 if (NULL==pTransfoManager)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 // Asks for the transformation of piPLine
 pTransfoManager->Add(piPLine);
 // Runs the operator
 pTransfoManager->Run();
 // Retrieves the object corresponding to the transformation of the PLine
 CATICGMObject* piTransfPLine=NULL;
 piTransfPLine = pTransfoManager->ReadImage(piPLine);
 if (NULL==piTransfPLine)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 // In this case, the underlying surface is also duplicated.
 CATULONG32  tagSurfTransf = ( ((CATPLine *)piTransfPLine )->GetSurface())->GetPersistentTag();
 if (tagSurfTransf == tagSurfPLine)    
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (4);
 }             

 //-----------------------------------------------------------------------------
 // 6- Evaluates the normals at the 4 corners
 //-----------------------------------------------------------------------------
 // Retrieves the duplicated surface
 CATSurface * piTransfEggBox = (CATSurface*)(pTransfoManager->ReadImage(piEggBox));
 if (NULL==piTransfEggBox)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 // Gets its limits
 piTransfEggBox ->GetLimits(surLimits); 

 // First corner
 CATSurParam surParam(1.,1.,surLimits);
 CATMathDirection normal;
 CATMathPoint mPoint;
 piTransfEggBox->EvalPoint(surParam, mPoint);
 piTransfEggBox->EvalNormal(surParam, normal);
 // Creates of the trimmed line representing the tangent
 piGeomFactory->CreateLine(mPoint,mPoint+10*normal);

 // Second corner
 surParam.SetParam(0.,1.,surLimits);
 piTransfEggBox->EvalPoint(surParam, mPoint);
 piTransfEggBox->EvalNormal(surParam, normal);
 // Creates of the trimmed line representing the tangent
 piGeomFactory->CreateLine(mPoint,mPoint+10*normal);

 // Third corner
 surParam.SetParam(0.,0.,surLimits);
 piTransfEggBox->EvalPoint(surParam, mPoint);
 piTransfEggBox->EvalNormal(surParam, normal);
 // Creates of the trimmed line representing the tangent
 piGeomFactory->CreateLine(mPoint,mPoint+10*normal);

 // Fourth corner
 surParam.SetParam(1.,0.,surLimits);
 piTransfEggBox->EvalPoint(surParam, mPoint);
 piTransfEggBox->EvalNormal(surParam, normal);
 // Creates of the trimmed line representing the tangent
 piGeomFactory->CreateLine(mPoint,mPoint+10*normal);

 delete pTransfoManager;
 pTransfoManager = NULL;


 //-----------------------------------------------------------------------------
 // 7- Writes the model
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
	
 return rc;
}


