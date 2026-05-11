/**
 * @fullreview PEY 02:01:18
 */

// COPYRIGHT DASSAULT SYSTEMES 2000

//============================================================================================
// Sample code for : Generative Shape Design Interfaces
// Mission         : - Creates a parametric nozzle form using Generative Shape Design Feature
//                   - Saves the resulting Part 
//
// Type		   : Batch program
// Inputs	   : Path for saving the resulting Part (If no argument specified the part is not saved) 
// Outputs         : Return code is 0 if program worked ok, >0 otherwise
//	 
// Illustrates     : o How to Create a Part Document
//                   o How to Create a GSMTool and set it as current  
//                   o How to Create Points, Lines, Planes, Circles, Sweeps and Lofts
//                   o How to Save a Part Document  
//==========================================================================
//  How to execute :
//  
//     CAAGsiNozzle Part 
//          with:   Part representing the path of the created part
//    
//  Example:
// 
//   CAAGsiNozzle  E:\tmp\CAAGsiNozzle.CATPart 
//
//  Return code:
//  
//   0 successful execution
//   1 bad number of arguments
//   2 problem during document creation
//   3 problem during document deletion 
//   4 problem during Part Save 
//============================================================================================
#include "CAAGsiUserTools.h"         // To call Creation Services and Init,Save, Close.

#include <iostream.h>                // To have cout 

#include "CATISpecObject.h"          // To handle Feature 
#include "CATLISTV_CATISpecObject.h" // To handle List of Features
#include "CATIGSMTool.h"             // To handle GSMTool  

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Main 
// Test Create a nozzle form 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int iArgc, 			// Number of arguments (1)
         char *iArgv[])                 // Path for the created Part 
{
  // Create a parametric nozzle form using Generative Shape Design Feature
  int RetCode = 0 ;
  HRESULT rc  = S_OK;

  // Checks arguments
  cout << "(CAAGsiNozzle) iArgc = "<< iArgc << endl;
  for (int i=0;i<iArgc;i++) cout << "(CAAGsiNozzle) iArgv =[ "<<i<<" ]= "<< iArgv[i] << endl;
  if ( 3 <  iArgc) return 1;

  char*  pPartName = NULL;
  pPartName=  iArgv[1];

  // V5R13SP2 / Update to suport GS/OGS 
  int  pTypeOfTool= 0;
  if (iArgc == 3 )  { 
      pTypeOfTool =atoi (iArgv[2]); 
  } 
  // V5R13SP2

  // Create Tool Object 
   CAAGsiUserTools CAAGsiObjTool;

   cout << "====================================================================" << endl;
   cout << "=========        Batch : Start Design a Nozzle             =========" << endl;
   cout << "====================================================================" << endl;
   cout << "(CAAGsiNozzle) Start"  << endl;
   cout << endl;
  
   // ----------------------------------------------------------------------------
   // USE CASE 
   // ----------------------------------------------------------------------------

    // --------------------------------------------------------------
    // -1- Init 
    // --------------------------------------------------------------

    cout << "(CAAGsiNozzle) Init session " << endl;
    cout << " Init Session  " << endl;
    char* pSessionName = "CAA2SampleSession";
    rc = CAAGsiObjTool.Init( pSessionName);
    if (FAILED(rc)) return 2;        

    //---------------------------------------------------------------
    // -2- Open Body Creation 
    //---------------------------------------------------------------
    
    CATLISTV(CATISpecObject_var) aObjectParameters;
   
    // Create GSM Tool and set this GSMTool as Current Object in order to create all Features
	// in this Open Body    
    int setAsCurrent = 1;
    int CreationLocation =0 ;
// V5R13SP2 / Update to suport GS/OGS 
    int TypeOfGeometricalSet  =  pTypeOfTool ;
// V5R13SP2
    CATIGSMTool_var spTool  = CAAGsiObjTool.CreateGSMTool("Nozzle",setAsCurrent,0,TypeOfGeometricalSet);
    
    // ----------------------------------------------------------------------------
    // 3- Creating  Features 
    // ----------------------------------------------------------------------------

    // ----------------------------------------------------------------------------
    //  WIREFRAME DESIGN
    // ----------------------------------------------------------------------------

    // Reference Points 
    // -----------------------------------
    cout << "(CAAGsiNozzle) Creating Points" << endl; 
    CATISpecObject_var spCurrent = NULL_var;

    // Profile  definition in XY Plane 
    // .........................................................
    // Point (17,0,0) 
    CAAGsiObjTool.CreateLength("X", 17.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint1 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (-17,0,0) 
    CAAGsiObjTool.CreateLength("X",-17.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint2 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (17,10,0) 
    CAAGsiObjTool.CreateLength("X", 17.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 10.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint3 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (-17,10,0) 
    CAAGsiObjTool.CreateLength("X",-17.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 10.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint4 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (15,15,0) 
    CAAGsiObjTool.CreateLength("X", 15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint5 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (-15,15,0) 
    CAAGsiObjTool.CreateLength("X",-15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint6 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (15,20,0) 
    CAAGsiObjTool.CreateLength("X", 15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 20.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint7 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (-15,20,0) 
    CAAGsiObjTool.CreateLength("X",-15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 20.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint8 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();

    // Point ( 45,20,0) 
    CAAGsiObjTool.CreateLength("X", 45.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 20.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint11 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (105,20,0) 
    CAAGsiObjTool.CreateLength("X",-45.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y", 20.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint12 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();

    // Planes
    // -----------------------------------	
    cout << "(CAAGsiNozzle) Creating Planes" << endl;

    // Analytic plane Y = 0
    CAAGsiObjTool.CreateReal("A", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("B", 1.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("C", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("D", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPlaneY0 = CAAGsiObjTool.CreatePlaneEquation(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Analytic plane Z = 0
    CAAGsiObjTool.CreateReal("A", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("B", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("C", 1.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("D", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPlaneXY = CAAGsiObjTool.CreatePlaneEquation(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Analytic plane Y = 10
    CAAGsiObjTool.CreateReal("A", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("B", 1.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("C", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("D",10.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPlaneY10 = CAAGsiObjTool.CreatePlaneEquation(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Analytic plane Y = 15
    CAAGsiObjTool.CreateReal("A", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("B", 1.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("C", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("D",15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPlaneY15 = CAAGsiObjTool.CreatePlaneEquation(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Analytic plane Y = 20
    CAAGsiObjTool.CreateReal("A", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("B", 1.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("C", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("D",20.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPlaneY20 = CAAGsiObjTool.CreatePlaneEquation(aObjectParameters);
    aObjectParameters.RemoveAll();

    
    // Lines 
    // -----------------------------------	
   
    // Guiding line definition in XY horizontal plane 
    aObjectParameters.Append(spPoint1);
    aObjectParameters.Append(spPoint3);		
    CATISpecObject_var spLine2 = CAAGsiObjTool.CreateLinePtPt(aObjectParameters);
    aObjectParameters.RemoveAll();
   
   // Guiding line definition in XY horizontal plane
    aObjectParameters.Append(spPoint3);
    aObjectParameters.Append(spPoint5);		
    CATISpecObject_var spLine3 = CAAGsiObjTool.CreateLinePtPt(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Guiding line definition in XY horizontal plane 
    aObjectParameters.Append(spPoint5);
    aObjectParameters.Append(spPoint7);		
    CATISpecObject_var spLine4 = CAAGsiObjTool.CreateLinePtPt(aObjectParameters);
    aObjectParameters.RemoveAll();

    // Guiding line definition in XY horizontal plane 
    aObjectParameters.Append(spPoint7);
    aObjectParameters.Append(spPoint8);		
    CATISpecObject_var spLine5 = CAAGsiObjTool.CreateLinePtPt(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Vertical line definition a point  (100,0,0)
    // ----------------------------------------------------------	
    // Point (100,0,0) 
    CAAGsiObjTool.CreateLength("X",100.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint9 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Point (100,0,10) 
    CAAGsiObjTool.CreateLength("X",100.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Y",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Z", 10.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint10 = CAAGsiObjTool.CreatePointCoord(aObjectParameters);
    aObjectParameters.RemoveAll();

    // Vertical linne at Point (100,0,0) 
    // -----------------------------------	
    aObjectParameters.Append(spPoint9);
    aObjectParameters.Append(spPoint10);		
    CATISpecObject_var spLineVert = CAAGsiObjTool.CreateLinePtPt(aObjectParameters);
    aObjectParameters.RemoveAll();

    // Plane Angle definition a point  (100,0,0)
    // ----------------------------------------------------------	
    // Plan Angle of 35 Degres with  PlaneRef = Plane XZ / RotationLine= LineVert
    aObjectParameters.Append(spPlaneY0);
    aObjectParameters.Append(spLineVert);
    CAAGsiObjTool.CreateAngle("Angle",35.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPlaneAngle35 = CAAGsiObjTool.CreatePlaneAngle(aObjectParameters,FALSE);
    aObjectParameters.RemoveAll();
    


    // Circles 
    // -----------------------------------		
    cout << "(CAAGsiNozzle) Creating Circles" << endl;

    // Circle profile in Plane Y=0
    aObjectParameters.Append(spPoint1);
    aObjectParameters.Append(spPoint2);
    aObjectParameters.Append(spPlaneY0);
    CAAGsiObjTool.CreateLength("Radius", 17.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spCircle1 = CAAGsiObjTool.CreateCircle2PointsRad(aObjectParameters,FALSE,TRUE);
    aObjectParameters.RemoveAll();
    
    // Circle profile in Plane Y=10
    aObjectParameters.Append(spPoint3);
    aObjectParameters.Append(spPoint4);
    aObjectParameters.Append(spPlaneY10);
    CAAGsiObjTool.CreateLength("Radius", 17.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spCircle2 = CAAGsiObjTool.CreateCircle2PointsRad(aObjectParameters,FALSE,TRUE);
    aObjectParameters.RemoveAll();
    
    // Circle profile in Plane Y=15
    aObjectParameters.Append(spPoint5);
    aObjectParameters.Append(spPoint6);
    aObjectParameters.Append(spPlaneY15);
    CAAGsiObjTool.CreateLength("Radius", 15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spCircle3 = CAAGsiObjTool.CreateCircle2PointsRad(aObjectParameters,FALSE,TRUE);
    aObjectParameters.RemoveAll();
    
    // Circle profile in Plane Y=20
    aObjectParameters.Append(spPoint7);
    aObjectParameters.Append(spPoint8);
    aObjectParameters.Append(spPlaneY20);
    CAAGsiObjTool.CreateLength("Radius", 15.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spCircle4 = CAAGsiObjTool.CreateCircle2PointsRad(aObjectParameters,FALSE,TRUE);
    aObjectParameters.RemoveAll();
 
    // Circle guiding crv 
    aObjectParameters.Append(spPoint11);
    aObjectParameters.Append(spPoint7);
    aObjectParameters.Append(spPlaneXY);
    CAAGsiObjTool.CreateAngle("Angle1",   0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateAngle("Angle2", -90.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spCircle5 = CAAGsiObjTool.CreateCircleCenterRad(aObjectParameters,FALSE);
    aObjectParameters.RemoveAll();
    cout << "(CAAGsiNozzle) Circle5 created" << endl;
    
    aObjectParameters.Append(spPoint9);
    aObjectParameters.Append(spPoint8);
    aObjectParameters.Append(spPlaneXY);
    CAAGsiObjTool.CreateLength("Angle1",   0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Angle2", -90.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spCircle6 = CAAGsiObjTool.CreateCircleCenterRad(aObjectParameters,FALSE);
    aObjectParameters.RemoveAll();    
    
    
    // Split of circle guiding curve with Plane Angle in order to relimit circle 
    // ----------------------------------------------------------------------------------	
    cout << "(CAAGsiNozzle) Creating Splits" << endl;
    aObjectParameters.Append(spCircle6);
    aObjectParameters.Append(spPlaneAngle35);
    CATISpecObject_var spSplit1 = CAAGsiObjTool.CreateSplit(aObjectParameters,TRUE);
    aObjectParameters.RemoveAll(); 
    
    aObjectParameters.Append(spCircle5);
    aObjectParameters.Append(spPlaneAngle35);
    CATISpecObject_var spSplit2 = CAAGsiObjTool.CreateSplit(aObjectParameters,TRUE);
    aObjectParameters.RemoveAll(); 
    
    // Extremity of splited circle 
    // ----------------------------------------------------------------------------------	
    cout << "(CAAGsiNozzle) Creating Points On Curve" << endl;
    spCurrent = NULL_var;
    aObjectParameters.Append(spSplit1);
    aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("Parm", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint13 = CAAGsiObjTool.CreatePointOnCurve(aObjectParameters,TRUE);
    aObjectParameters.RemoveAll();
     
    spCurrent = NULL_var;
    aObjectParameters.Append(spSplit2);
    aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("Parm", 0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint14 = CAAGsiObjTool.CreatePointOnCurve(aObjectParameters,TRUE);
    aObjectParameters.RemoveAll();
    
    // Middle point of the line between extremity of splited circle 
    // ----------------------------------------------------------------------------------	
    spCurrent = NULL_var;
    aObjectParameters.Append(spLine5);
    aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("Parm", 0.5, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint15 = CAAGsiObjTool.CreatePointOnCurve(aObjectParameters,TRUE);
    aObjectParameters.RemoveAll();
    
    // Line between extremity of splited circle 
    // ----------------------------------------------------------------------------------	
    cout << "(CAAGsiNozzle) Creating Line pt-pt" << endl;
    aObjectParameters.Append(spPoint13);
    aObjectParameters.Append(spPoint14);
    CATISpecObject_var spLine6 = CAAGsiObjTool.CreateLinePtPt(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // Middle point of the line between extremity of splited circle 
    // ----------------------------------------------------------------------------------	
    cout << "(CAAGsiNozzle) Creating Point On Curve" << endl;
    spCurrent = NULL_var;
    aObjectParameters.Append(spLine6);
    aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateReal("Parm", 0.5, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint16 = CAAGsiObjTool.CreatePointOnCurve(aObjectParameters,TRUE);
    aObjectParameters.RemoveAll();
    
    // Normal Line to line 5 and line 6 through the middle points to XY plane   
    // ----------------------------------------------------------------------------------	
    cout << "(CAAGsiNozzle) Creating Line Normal Curve" << endl;
    aObjectParameters.Append(spLine5);
    aObjectParameters.Append(spPlaneXY);
    aObjectParameters.Append(spPoint15);
    CAAGsiObjTool.CreateLength("Start",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("End"  , 10.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spLine7 = CAAGsiObjTool.CreateLineNormalCrv(aObjectParameters,FALSE,FALSE);
    aObjectParameters.RemoveAll();
    
    aObjectParameters.Append(spLine6);
    aObjectParameters.Append(spPlaneXY);
    aObjectParameters.Append(spPoint16);
    CAAGsiObjTool.CreateLength("Start",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("End"  , 10.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spLine8 = CAAGsiObjTool.CreateLineNormalCrv(aObjectParameters,FALSE,FALSE);
    aObjectParameters.RemoveAll();
    
    // Normal Line to line 6 the middle points  to plane angle 
    // ----------------------------------------------------------------------------------	
    aObjectParameters.Append(spLine6);
    aObjectParameters.Append(spPlaneAngle35);
    aObjectParameters.Append(spPoint16);
    CAAGsiObjTool.CreateLength("Start",  0.0, spCurrent); aObjectParameters.Append(spCurrent);
    CAAGsiObjTool.CreateLength("End"  , 20.0, spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spLine9 = CAAGsiObjTool.CreateLineNormalCrv(aObjectParameters,FALSE,FALSE);
    aObjectParameters.RemoveAll();
    
    // Extremity of line 9
    // ----------------------------------------------------------------------------------	
    aObjectParameters.Append(spLine9);
    aObjectParameters.Append(spPoint16);
    CAAGsiObjTool.CreateReal("Parm", 1., spCurrent); aObjectParameters.Append(spCurrent);
    CATISpecObject_var spPoint17 = CAAGsiObjTool.CreatePointOnCurve(aObjectParameters,FALSE);
    aObjectParameters.RemoveAll();
    
    // Circle profile in Plane Angle a=35 
    cout << "(CAAGsiNozzle) Creating Circle 3 Points" << endl;
    aObjectParameters.Append(spPoint13);
    aObjectParameters.Append(spPoint17);
    aObjectParameters.Append(spPoint14);
    CATISpecObject_var spCircle7 = CAAGsiObjTool.CreateCircle3Points(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    // ----------------------------------------------------------------------------
    // SKIN FEATURES 
    // ----------------------------------------------------------------------------

    // Sweep 
    // ------------------
    cout << "(CAAGsiNozzle) Creating Sweeps" << endl;
    aObjectParameters.Append(spLine2);
    aObjectParameters.Append(spCircle1);
    CATISpecObject_var spSweep1 = CAAGsiObjTool.CreateSweepOneGuide(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    
    aObjectParameters.Append(spLine4);
    aObjectParameters.Append(spCircle3);
    CATISpecObject_var spSweep2 = CAAGsiObjTool.CreateSweepOneGuide(aObjectParameters);
    aObjectParameters.RemoveAll();
    
    
    // Loft 
    // ------------------
    cout << "(CAAGsiNozzle) Creating Spine" << endl;
    aObjectParameters.Append(spPoint15);
    aObjectParameters.Append(spPoint16);
    CATISpecObject_var spDir1 = CAAGsiObjTool.CreateDirection(spLine7);
    CATISpecObject_var spDir2 = CAAGsiObjTool.CreateDirection(spLine8);
    CATISpecObject_var spSpline = CAAGsiObjTool.CreateSpline(aObjectParameters,spDir1,FALSE,spDir2,TRUE);
    aObjectParameters.RemoveAll();
    
    
    cout << "(CAAGsiNozzle) Creating Lofts" << endl;
    CATLISTV(CATISpecObject_var) aObjectParametersSections;
    aObjectParametersSections.Append(spCircle2);
    aObjectParametersSections.Append(spCircle3);
    aObjectParameters.Append(spLine3);
    CATISpecObject_var spUnused = NULL_var;
    CATISpecObject_var spLoft1 = CAAGsiObjTool.CreateLoft(aObjectParametersSections,aObjectParameters,spUnused);
    aObjectParameters.RemoveAll();
    aObjectParametersSections.RemoveAll();
    
    aObjectParametersSections.Append(spCircle7);
    aObjectParametersSections.Append(spCircle4);
    aObjectParameters.Append(spSplit1);
    aObjectParameters.Append(spSplit2);
    CATISpecObject_var spLoft2 = CAAGsiObjTool.CreateLoft(aObjectParametersSections,aObjectParameters,spSpline);
    aObjectParameters.RemoveAll();
    aObjectParametersSections.RemoveAll();
    
    
    // ----------------------------------------------------------------------------
    // 4- Exit 
    // ----------------------------------------------------------------------------

    // Save Part 
    // ------------------------------------
    // Saves the modified pad in the second input path
  
    if ( NULL != pPartName ) {
      cout << "(CAAGsiNozzle) Save : "<< pPartName  << endl;
      rc = CAAGsiObjTool.Save(pPartName);
      if (FAILED(rc)) RetCode = 4 ;        
    }
  
    // Close Session
    // ------------------------------------
    cout << "(CAAGsiNozzle) Close session " << endl;
    rc = CAAGsiObjTool.Close(pSessionName);
    if (FAILED(rc)) return 3;        

    cout << "(CAAGsiNozzle) End "  << RetCode << endl;
    cout << "====================================================================" << endl;
    cout << "=========        Batch : End Design a Nozzle               =========" << endl;
    cout << "====================================================================" << endl;
    cout << endl;
   
    return RetCode ;
}

