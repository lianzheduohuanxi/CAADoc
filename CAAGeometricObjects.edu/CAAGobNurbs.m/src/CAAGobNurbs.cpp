/**
* @quickReview CRE 03:10:17
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of NURBS curves
//
// Type            : Batch program
// Inputs          : None
// Outputs         : cout
//
// Illustrates     : 1- Factory creation
//                   2- knot vector definition
//                   3- NURBS curve creation 
//                      Point creation
//                   4- Non uniform knot vector creation
//                   5- Point creation at the arc limits.
//                   6- Rational curve creation 
//                   7- Model write factory closure. 
//
// How to run it   : CAAGobNurbs            // to run without storing the NCGM file
//                   CAAGobNurbs  file.NCGM // to run and store the result in file.NCGM                              
//=============================================================================
#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"              // Mathematical point
#include "CATMathSetOfPoints.h"        // Set of mathematical points

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Management of the geometry factory

#include "CATCrvParam.h"               // Parameter on a curve
#include "CATCrvEvalLocal.h"           // Result of a curve evaluation
#include "CATCrvEvalCommand.h"         // Type of evaluation
#include "CATCartesianPoint.h"         // Geometric Cartesian point
#include "CATNurbsCurve.h"             // NURBS curve
#include "CATKnotVector.h"             // knot vector

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
 // 1- Initializes the factory
 //-----------------------------------------------------------------------------
	
 CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
 if (NULL==piGeomFactory) return (1);	

 //-----------------------------------------------------------------------------
 // 2- Creates a knot vector of one arc of degree 3 --> 4 control points
 //-----------------------------------------------------------------------------
	
 // by default, the constructor builds such a knot vector
 CATKnotVector bezierKnot;
 // only polynomial
 CATLONG32 isRational=0;
 // hence, no weight
 double * aWeights=NULL;
 // the four control points
 CATMathSetOfPoints vertices(4);
 vertices.SetPoint(CATMathPoint(-20.,0.,0.),0);
 vertices.SetPoint(CATMathPoint(-20.,5.,0.),1);
 vertices.SetPoint(CATMathPoint(-10.,5.,0.),2);
 vertices.SetPoint(CATMathPoint(-10.,0.,0.),3);

 // Creates the NURBS	
 CATNurbsCurve * piFirstCurve = piGeomFactory->
		CATCreateNurbsCurve(bezierKnot,isRational,vertices,aWeights);
 if (NULL==piFirstCurve)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	
 // Creates the geometric points to visualize the control points
 CATCartesianPoint* piCP1= piGeomFactory->CreateCartesianPoint(CATMathPoint(-20.,0.,0.));
 CATCartesianPoint* piCP2= piGeomFactory->CreateCartesianPoint(CATMathPoint(-20.,5.,0.));
 CATCartesianPoint* piCP3= piGeomFactory->CreateCartesianPoint(CATMathPoint(-10.,5.,0.));
 CATCartesianPoint* piCP4= piGeomFactory->CreateCartesianPoint(CATMathPoint(-10.,0.,0.));
 if (NULL==piCP1 || NULL==piCP2 || NULL==piCP3 || NULL==piCP4)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	

	
 //----------------------------------------------------------------------------- 
 // 3- Another example with the same knot vector: one of the control point is moved
 //-----------------------------------------------------------------------------


 vertices.SetPoint(CATMathPoint(-5,15,0),2);
 CATNurbsCurve * piSecondCurve = piGeomFactory->
		CATCreateNurbsCurve(bezierKnot,isRational,vertices,aWeights);
 if (NULL==piSecondCurve)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 CATCartesianPoint* piCP3bis= piGeomFactory->CreateCartesianPoint(CATMathPoint(-5.,15.,0.));
 if (NULL==piCP3bis)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }	


 //-----------------------------------------------------------------------------
 // 4- Knot vector non uniform, with 3 arcs (4 knots) of degree 3, continuity C2 --> 6 control points
 //-----------------------------------------------------------------------------
 const CATLONG32 nbknots=4;
 double aKnots[nbknots];
 aKnots[0]=0;
 aKnots[1]=2;
 aKnots[2]=8;
 aKnots[3]=9;
 CATLONG32 isPeriodic=0;
 CATLONG32 continuity=2;
 CATKnotVector nonUniformKnot(isPeriodic,nbknots,aKnots,continuity);
	
 // the six control points
 CATMathSetOfPoints otherVertices(6);
 otherVertices.SetPoint(CATMathPoint( 20., 0.,0.),0);
 otherVertices.SetPoint(CATMathPoint( 22.,10.,0.),1);
 otherVertices.SetPoint(CATMathPoint( 30.,20.,0.),2);
 otherVertices.SetPoint(CATMathPoint( 40., 0.,0.),3);
 otherVertices.SetPoint(CATMathPoint( 43.,15.,0.),4);
 otherVertices.SetPoint(CATMathPoint( 50.,20.,0.),5);
	
	
 CATNurbsCurve * piThirdCurve = piGeomFactory->
		CATCreateNurbsCurve(nonUniformKnot,isRational,otherVertices,aWeights);
 if (NULL==piThirdCurve)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	
 //   Creation of the geometric points to visualize the control points
 CATCartesianPoint* piCPN1= piGeomFactory->CreateCartesianPoint(CATMathPoint( 20., 0.,0.));
 CATCartesianPoint* piCPN2= piGeomFactory->CreateCartesianPoint(CATMathPoint( 22.,10.,0.));
 CATCartesianPoint* piCPN3= piGeomFactory->CreateCartesianPoint(CATMathPoint( 30.,20.,0.));
 CATCartesianPoint* piCPN4= piGeomFactory->CreateCartesianPoint(CATMathPoint( 40., 0.,0.));
 CATCartesianPoint* piCPN5= piGeomFactory->CreateCartesianPoint(CATMathPoint( 43.,15.,0.));
 CATCartesianPoint* piCPN6= piGeomFactory->CreateCartesianPoint(CATMathPoint( 50.,20.,0.));
 if (NULL==piCPN1 || NULL==piCPN2 || NULL==piCPN3 || NULL==piCPN4 || NULL==piCPN5 || NULL==piCPN6)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

	
 //-----------------------------------------------------------------------------
 // 5- Creation of the geometric points corresponding to the arc limits.
 //  By default, the CATNurbsCurve constructor adapts the parameterization of the knots, according to
 // the length of the curve. Hence, if you ask for the CATKnotVector of ThirdCurve, you
 // find new knot values. If you want your curve keeps the initial parameterization, set
 // the CATParameterizationOption to CatKeepParameterization (optional argument).
 //   The first and last knot value correspond to the first and last control point.
 //-----------------------------------------------------------------------------

 CATCrvParam param;
 CATCrvEvalLocal result;
 CATMathPoint mathPoint;
 // new CATKnotVector 
 const CATKnotVector * pNewKnotVector=piThirdCurve->GetKnotVector();
 if (NULL==pNewKnotVector)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 const double * aNewKnots=NULL;
 pNewKnotVector->GetKnots(aNewKnots);
 if (NULL==aNewKnots)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 // second knot value 
 piThirdCurve->CreateParam(aNewKnots[1] ,param);
 piThirdCurve->Eval(param,CATCrvEvalCommand::EvalPoint,result);
	
 result.GetPoint(mathPoint);
 CATCartesianPoint* piCPAL2= piGeomFactory->CreateCartesianPoint(mathPoint);
 if (NULL==piCPAL2 )
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	
 // third knot value 
 piThirdCurve->CreateParam(aNewKnots[2] ,param);
 piThirdCurve->Eval(param,CATCrvEvalCommand::EvalPoint,result);
 result.GetPoint(mathPoint);
 CATCartesianPoint* piCPAL3= piGeomFactory->CreateCartesianPoint(mathPoint);
  if (NULL==piCPAL3 )
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	
 //-----------------------------------------------------------------------------
 // 6- now, a rational one
 //-----------------------------------------------------------------------------
 isRational=1;
 aWeights=new double[6];
 aWeights[0]=1;
 aWeights[1]=1;
 aWeights[2]=10;
 aWeights[3]=20;
 aWeights[4]=5;
 aWeights[5]=1;
 CATNurbsCurve * piFourthCurve = piGeomFactory->
		CATCreateNurbsCurve(nonUniformKnot,isRational,otherVertices,aWeights);
 if (NULL==piFourthCurve)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 } 
	
 delete [] aWeights;
 aWeights = NULL;

 // new CATKnotVector 
 pNewKnotVector=piThirdCurve->GetKnotVector();
 if (NULL==pNewKnotVector)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }

 pNewKnotVector->GetKnots(aNewKnots);
 if (NULL==aNewKnots)
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
 // knot value = 2
 piFourthCurve->CreateParam(aNewKnots[1] ,param);
 piFourthCurve->Eval(param,CATCrvEvalCommand::EvalPoint,result);
	
 result.GetPoint(mathPoint);
 CATCartesianPoint* piCPAL2R= piGeomFactory->CreateCartesianPoint(mathPoint);
 if (NULL==piCPAL2R )
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }
	
 // knot value = 8
 piFourthCurve->CreateParam(aNewKnots[2] ,param);
 piFourthCurve->Eval(param,CATCrvEvalCommand::EvalPoint,result);
 result.GetPoint(mathPoint);
 CATCartesianPoint* piCPAL3R= piGeomFactory->CreateCartesianPoint(mathPoint);
 if (NULL==piCPAL3R )
 {
   ::CATCloseCGMContainer(piGeomFactory);
   return (1);
 }	
	
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
	
 return (rc);
}
