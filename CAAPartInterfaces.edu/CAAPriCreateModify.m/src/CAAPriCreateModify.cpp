/**
 * @quickReview frn 03:06:26
 */
// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: - Creates and modifies a pad 
//										- Saves the pad before and after the modification
//	
//  Type						: Batch program
//  Inputs					: Two paths to record the two pads
//  Outputs					:	Return code is 0 if program worked ok, >0 otherwise
//	 
//  Illustrates			: Using Mechanical Design factory for creation and 
//										modification of a part
//
//==========================================================================

//==========================================================================
//  How to execute :
//  
//  CAAPriCreateModify Part1 Part2
//  with:
//		Part1 representing the path of the first created part
//    Part2 representing the path of the second created part
//    
//	Example:
// 
//   CAAPriCreateModify E:\CAA2WS\tmp\Pad1.CATPart E:\CAA2WS\tmp\Pad2.CATPart
//
//  Return code:
//  
//   0 successful execution
//   1 bad number of arguments
//   2 problem during document creation
//   3 problem during first pad creation
//   4 problem during first pad recording
//   5 problem during modified pad recording
//    
//========================================================================== 



//ObjectModelerBase Framework
#include "CATSession.h"          // needed to manage session
#include "CATDocument.h"				 // needed to manage documents
#include "CATDocumentServices.h" // needed to create/save documents
#include "CATSessionServices.h"  // needed to create/delete session
#include "CATInit.h"             // needed to retrieve root container from document

// Mathematics Framework
#include "CATMathPlane.h"        // needed to manage planes
#include "CATMathDirection.h"    // needed to manage directions
#include "CATMathPoint.h"        // needed to manage points

// SketcherInterfaces Framework
#include "CATISketchFactory.h"   // needed to create sketchs
#include "CATI2DWFFactory.h"     // needed to create 2D elements
#include "CATISketch.h"          // needed to edit/modify sketch
#include "CATI2DCurve.h"         // needed to define the start and end point
                                 // of a sketch
#include "CATI2DPoint.h"         // needed to define the start and end point
                                 // of a sketch

// PartInterfaces Framework
#include "CATIPrtFactory.h"      // needed to create pad feature
#include "CATIPad.h"             // needed to manage pad
#include "CATLimitDefs.h"        // needed to access limit type of the pad feature

// MecModInterfaces Framework
#include "CATIPrtContainer.h"    // needed to retrieve factories
#include "CATIPrtPart.h"         // needed to access reference planes


int main(int iArgc, 			// Number of arguments (2)
         char *iArgv[])   // Paths for the created and modified pad
{
  // Creates a Pad with a rectangular sketch, first limit length equals to 10
  // and second limit length equals to 0
  // Checks the two limit lengths 
  // Modifies the Pad first limit up to a defined plane

  int rc=0;

  // Checks arguments
  if(3 != iArgc) return 1;

  // Opens a session
  CATSession * pSampleSession = NULL;
  Create_Session("SampleSession",pSampleSession);

  // Opens a CATPart document and initializes the data
  CATDocument * pDoc= NULL;
  CATDocumentServices::New("CATPart",pDoc);
  if(NULL == pDoc) return 2;

  CATInit_var spInitOnDoc(pDoc);
  if(NULL_var == spInitOnDoc) return 2;

  // Retrieves the root container
  CATIPrtContainer * piPrtCont = 
    (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	
	
	
  // Retrieves the sketch factory to instantiate objects
  CATISketchFactory_var spSketchFactOnPrtCont(piPrtCont);
	
  // Creates the sketch plane
  // retrieves the reference planes of the part
  CATIPrtPart_var spPart;
  if(piPrtCont)
    spPart = piPrtCont->GetPart();
  CATListValCATISpecObject_var spListRefPlanes = spPart->GetReferencePlanes();
  
  // defines the xy plane as the first sketch plane
  CATISpecObject_var spSketchPlane = spListRefPlanes[1];


  // Instantiates the sketch with the plane
  CATISketch_var spSketch = spSketchFactOnPrtCont->CreateSketch(spSketchPlane);
      
  // Retrieves the 2D factory to create the lines and points of the sketch
  CATI2DWFFactory_var spWF2DFactOnSketch(spSketch);


  // Creates the elements of the sketch
  double pt1[2] = {10., 5.}, 
         pt2[2] = {-10., 5.}, 
         pt3[2] = {-10., -5.}, 
         pt4[2] = {10., -5.};

  // Edits the sketch and draws the lines and the endpoints.
  spSketch->OpenEdition();
  CATISpecObject_var spLine1 = spWF2DFactOnSketch->CreateLine(pt1,pt2);
  CATISpecObject_var spLine2 = spWF2DFactOnSketch->CreateLine(pt2,pt3);
  CATISpecObject_var spLine3 = spWF2DFactOnSketch->CreateLine(pt3,pt4);
  CATISpecObject_var spLine4 = spWF2DFactOnSketch->CreateLine(pt4,pt1);

  CATI2DCurve_var spCurveOnLine1(spLine1);
  spCurveOnLine1->GetStartPoint();
  spCurveOnLine1->GetEndPoint();
  CATI2DCurve_var spCurveOnLine2(spLine2);
  spCurveOnLine2->GetStartPoint();
  spCurveOnLine2->GetEndPoint();
  CATI2DCurve_var spCurveOnLine3(spLine3);
  spCurveOnLine3->GetStartPoint();
  spCurveOnLine3->GetEndPoint();
  CATI2DCurve_var spCurveOnLine4(spLine4);
  spCurveOnLine4->GetStartPoint();
  spCurveOnLine4->GetEndPoint();

  // Closes the sketch edition
  spSketch->CloseEdition();
	
	
	
  // Creates the pad
  // arguments :  a sketch
  //              2 limits
  //              a direction

  double firstLimit = 20.; // First and second limits of the pad
  double secondLimit = 0.;
	
  CATMathDirection dirZ(0., 0., 1.); // Direction of the pad

  // Retrieves the Mechanical Design factory to create the pad
  CATIPrtFactory_var		spPrtFactOnPrtCont(piPrtCont);
  if(piPrtCont)
  {
    piPrtCont->Release();
    piPrtCont = NULL;
  }

  CATISpecObject_var spSpecObj = spPrtFactOnPrtCont->CreatePad(spSketch);

  CATIPad_var spPadOnSpecObj(spSpecObj);
  spPadOnSpecObj->ModifyDirection(dirZ);
  spPadOnSpecObj->ModifyEndType(catOffsetLimit);
  spPadOnSpecObj->ModifyEndOffset(firstLimit);
  spPadOnSpecObj->ModifyStartType(catOffsetLimit);
  spPadOnSpecObj->ModifyStartOffset(secondLimit);

  spSpecObj->Update(); // Builds the pad


  // Checks limits of the created pad
  if (spPadOnSpecObj->GetEndOffset() != firstLimit 
    || spPadOnSpecObj->GetStartOffset() != secondLimit)
    return 3;


  // Saves the created pad in the first input path
  HRESULT boolSave = E_FAIL;
  char *nomPart1 = iArgv[1];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart1);
  if(!SUCCEEDED(boolSave))
    return 4;

  // Modifies the pad changing the extrusion direction
  // and applying the symetry
  
  CATMathDirection dir2(0., 1., 1.); // Direction of the pad


  // Modifies the first limit type
  spPadOnSpecObj->ModifySym(1);

  // Modifies the first limit
  spPadOnSpecObj->ModifyDirection(dir2);


  spSpecObj->Update(); // Builds the pad


  // Saves the modified pad in the second input path
  boolSave = E_FAIL;
  char *nomPart2 = iArgv[2];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart2);
  if(!SUCCEEDED(boolSave))
    return 5;

  // Closes the session   
  ::Delete_Session("SampleSession"); 

  return rc;
};
