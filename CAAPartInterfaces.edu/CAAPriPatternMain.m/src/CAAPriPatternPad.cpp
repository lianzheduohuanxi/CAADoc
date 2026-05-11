/**
 * @quickReview AW4 12:05:23 'CATOsmSUHandler.h' instead of 'CATCatalogFactoryServices.h' and 'CATICatalog.h'
 * @quickReview sqa 04:01:09
 * @quickReview frn 03:06:26
 */
// COPYRIGHT DASSAULT SYSTEMES 1999


//==========================================================================
//  Sample code for : Part Interfaces
//  Mission         : Build of a PatternPad pattern
//	
//  Type            : Batch program
//  Inputs          : Two paths to record the created features
//  Outputs         : Return code is 0 if program worked ok, >0 otherwise
//	 
//  Illustrates     : CATIBuildShape in pattern context
//
//	
//  Steps :
//    1. Creation of a rectangular sketch in the (o,x,y) plane
//    2. Creation of a PatternPad with this sketch
//       The PatternPad is created reading the catalog and instantiating the startup
//    3. Save the created part
//    4. Creation of a pattern using PatternPad and keep specification option
//    5. Save the second created part
//
// 
//==========================================================================

//==========================================================================
// How to execute :
// 
//   CAAPriPatternPad Part1 Part2
//
//   with : Part1 path to the first saved part
//          Part2 path to the second saved part
//         
//
// Example :
//   CAAPriPatternPad E:\CAA2WS\tmp\PatternPad1.CATPart E:\CAA2WS\tmp\PatternPad2.CATPart      
//
// NB : the startup catalog must be in the directory resources/graphic
//
//
// Return code :
//   0 successful execution
//   1 number of arguments incorrect
//   2 problem during session creation
//   3 problem during PatternPad creation
//   4 problem during PatternPad record
//   5 problem during rectangular pattern of PatternPad creation
//   6 problem during rectangular pattern of PatternPad record
//   7 problem during dession closing
//==========================================================================


// ObjectModelerBase Framework
#include "CATSession.h"	            // needed to manage session
#include "CATDocument.h"            // needed to manage the CATPart document
#include "CATDocumentServices.h"    // needed to create the document
#include "CATSessionServices.h"     // needed to create the session
#include "CATInit.h"                // needed to access Mechanical design container

// Mathematics Framework
#include "CATMathPlane.h"           // needed to create the sketch
#include "CATMathDirection.h"       // needed to define the sketch and line
									// direction
#include "CATMathPoint.h"           // needed to define the plane and pattern 
                                    // origin

// SketcherInterfaces Framework
#include "CATISketchFactory.h"      // needed to create sketches
#include "CATI2DWFFactory.h"        // needed to draw the sketches
#include "CATISketch.h"             // needed to manage sketches
#include "CATI2DCurve.h"            // needed to define the start and end point
                                    // of a sketch
#include "CATI2DPoint.h"            // needed to define the start and end point
                                    // of a sketch

// MecModInterfaces Framework
#include "CATIPrtContainer.h"       // needed to manage Mechanical Design features
#include "CATIPrtPart.h"            // needed to access reference planes

// PartInterfaces Framework
#include "CATIPrtFactory.h"         // needed to create PatternPad profile
                                    // and rectangular pattern

#include "CATIPrtProfile.h"         // needed to valuate PatternPad attribute
#include "CATIPrtPattern.h"         // needed to define the design intent
                                    // of the pattern

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"         // needed to query interface
#include "CATISpecAttrAccess.h"			// needed to access PatternPad attributes
#include "CATISpecAttrKey.h"				// needed to access PatternPad attribute keys
#include "CATIDescendants.h"        // needed to aggregate PatternPad attribute
//#include "CATICatalog.h"            // needed to access UserPad startup   // Use CATOsmSUHandler instead
//#include "CATCatalogFactoryServices.h" //needed to open StartUp catalog   // Use CATOsmSUHandler instead
#include "CATOsmSUHandler.h"        //needed to Access catalog and instaniciate Startup

// MechanicalModeler Framework
#include "CATMfDefs.h"              // needed to define the keys of the procedural report
#include "CATIPrtProceduralView.h"  // needed to insert PatternPad feature in the procedural view


//================================================================================
// method for the creation of a PatternPad feature
// steps :
//  1. Opens the startup catalog
//  2. Retrieves the PatternPad startup and instanciates it
//  3. Valuates the attribute
//
// NB : To be found at runtime the catalog must in the directory resources/graphic
//=================================================================================
CATISpecObject_var CreatePatternPad(const CATIContainer_var& ispPrtCont,
                                    const CATISpecObject_var& ispSketch)
{

  // Step 1 and 2 Opens the startup catalog. Retrieves the UserPad startup and instanciates it

	CATUnicodeString startupType = "CAAPriPatternPad";
  CATUnicodeString ClientId = "SAMPLES";
  CATUnicodeString StorageName = "CAAPriFormFeature.CATfct";

	CATOsmSUHandler novelSUHandler(startupType, ClientId, StorageName );

	CATISpecObject_var spPatternPad;  
	HRESULT rc = novelSUHandler.Instanciate(spPatternPad, ispPrtCont, CATUnicodeString("CAAOsmNovel1"));

  if( FAILED(rc) ) 
    return NULL_var;

	if (NULL_var != spPatternPad)
  {    
    // insert the feature in the procedural view
    CATIPrtProceduralView_var spProcViewOnPatternPad(spPatternPad);
    spProcViewOnPatternPad->InsertInProceduralView(NULL_var);


    // Step 3 - Valuates the attribute

    // Creates a profile
    CATIPrtFactory_var spPrtFactoryOnContainer(ispPrtCont);
    CATISpecObject_var spProfile = spPrtFactoryOnContainer->CreateProfile();


    // Retrieves the profile attribute
    CATISpecAttrAccess * piSpecAttrAccessOnPatternPad = NULL;

		rc = spPatternPad->QueryInterface(IID_CATISpecAttrAccess, 
																		(void**) & piSpecAttrAccessOnPatternPad);
		
		if ( SUCCEEDED(rc) ) 
		{ 
			// Gets a pointer on the Profile attribute key
			CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
			piSpecAttrKeyOnProfile = piSpecAttrAccessOnPatternPad->GetAttrKey("Profile");
			
			if ( NULL != piSpecAttrKeyOnProfile )
			{
				piSpecAttrAccessOnPatternPad->SetSpecObject(piSpecAttrKeyOnProfile, spProfile);
				
				piSpecAttrKeyOnProfile->Release();
				piSpecAttrKeyOnProfile = NULL ;
				
				// Aggregates the profile
				CATIDescendants_var spRootOnPatternPad(spPatternPad);
				spRootOnPatternPad->Append(spProfile);
				
				// Valuates the profile
				if (NULL_var != ispSketch)
				{
					CATIPrtProfile_var spPrtProfileOnProfile(spProfile);
					spPrtProfileOnProfile->AddElement(ispSketch);
				}
			}
			else
				spPatternPad = NULL_var;

			piSpecAttrAccessOnPatternPad->Release();
			piSpecAttrAccessOnPatternPad = NULL;
		}
		else
      spPatternPad = NULL_var;
  }

  return spPatternPad;
}



//================================================================================
// Main Method 
// 
// Creates two UserPad with rectangular sketchs
//
// Steps:
//  1. Opens a session
//  2. Creates a sketch
//  3. Creates a PatternPad with the sketch
//  4. Saves the PatternPad
//  5. Creates a rectangular pattern with the PatternPad
//  6. Saves the rectangular pattern
//================================================================================
int main(int iArgc,     // Number of arguments (2)
         char *iArgv[]) // Paths for the 2 created parts
{
  int rc=0;

  // Step 1 - Opens a session

  // Checks arguments
  if(3 != iArgc) return 1;


  // Opens a session
  CATSession *pSampleSession = NULL;
  Create_Session("SampleSession",pSampleSession);

  CATDocument *pDoc= NULL;
  CATDocumentServices::New("CATPart",pDoc);
  if(NULL == pDoc) return 2;

  CATInit_var spInitOnDoc(pDoc);
  if(NULL_var == spInitOnDoc) return 2; 
	
  CATIPrtContainer *spPrtCont = 
    (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	

	
  // Retrieve the sketcher factory to instantiate objects
  CATISketchFactory_var spSketchFactOnPrtCont(spPrtCont);


  // Step 2 - Creates a sketch


  // Creates the sketch plane	
  // retrieves the reference planes of the part
  CATIPrtPart_var spPart;
  if(spPrtCont)
    spPart = spPrtCont->GetPart();
  CATListValCATISpecObject_var spListRefPlanes = spPart->GetReferencePlanes();
  
  // defines the xy plane as the first sketch plane
  CATISpecObject_var spSketchPlane = spListRefPlanes[1];
  
  // Instantiates the sketch with the plane
  CATISketch_var spSketch1 = spSketchFactOnPrtCont->CreateSketch(spSketchPlane);
      
  // Retrieves the 2D factory to create the lines and points of the sketch
  CATI2DWFFactory_var spWF2DFactOnSketch1(spSketch1);

  // Creates the elements of the sketch
  double pt1Sk1[2] = {10., 5.}, 
         pt2Sk1[2] = {-10., 5.}, 
         pt3Sk1[2] = {-10., -5.}, 
         pt4Sk1[2] = {10., -5.};

  // Edits the sketch, draws the lines and creates the start and end points.
  spSketch1->OpenEdition();
  // defines the lines
  CATISpecObject_var spLine1Sk1 = spWF2DFactOnSketch1->CreateLine(pt1Sk1,pt2Sk1);
  CATISpecObject_var spLine2Sk1 = spWF2DFactOnSketch1->CreateLine(pt2Sk1,pt3Sk1);
  CATISpecObject_var spLine3Sk1 = spWF2DFactOnSketch1->CreateLine(pt3Sk1,pt4Sk1);
  CATISpecObject_var spLine4Sk1 = spWF2DFactOnSketch1->CreateLine(pt4Sk1,pt1Sk1);

  // defines the points
  CATI2DCurve_var spCurveOnLine1Sk1(spLine1Sk1);
  spCurveOnLine1Sk1->GetStartPoint();
  spCurveOnLine1Sk1->GetEndPoint();
  CATI2DCurve_var spCurveOnLine2Sk1(spLine2Sk1);
  spCurveOnLine2Sk1->GetStartPoint();
  spCurveOnLine2Sk1->GetEndPoint();
  CATI2DCurve_var spCurveOnLine3Sk1(spLine3Sk1);
  spCurveOnLine3Sk1->GetStartPoint();
  spCurveOnLine3Sk1->GetEndPoint();
  CATI2DCurve_var spCurveOnLine4Sk1(spLine4Sk1);
  spCurveOnLine4Sk1->GetStartPoint();
  spCurveOnLine4Sk1->GetEndPoint();

  // Closes the sketch edition
  spSketch1->CloseEdition();
	
	

  // Step 3 - Creates a PatternPad with the sketch


  CATISpecObject_var spPattPad = CreatePatternPad(spPrtCont,
                                                  spSketch1);
																										
  if(NULL_var == spPattPad)
    return 3;

  spPattPad->Update(); // Builds the pad


  // Step 4 - Saves the PatternPad

  // Saves the created pad in the first input path
  HRESULT boolSave = E_FAIL;
  char *nomPart1 = iArgv[1];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart1);
  if(!SUCCEEDED(boolSave))
    return 4;



  // Step 5 - Creates a rectangular pattern with the PatternPad

  int nb1 = 3, nb2 = 3;             // defines the number of instances in the first 
                                    // and second directions
  double step1 = 40., step2 = 40.;  // defines the step in the first and second 
                                    // direction
  double angle1 =0.;                // defines the rotation angle  
  
   // Creation of the pattern
  // The directions are defined using the plane xy.

  CATIPrtFactory_var spPrtFactOnPrtCont(spPrtCont);
  CATISpecObject_var spRectPatternOfPattPad=
    spPrtFactOnPrtCont->CreateRectPatt(spPattPad, 
                                       spSketchPlane,
                                       spSketchPlane,
                                       TRUE,
                                       TRUE,
                                       nb1,
                                       nb2,
                                       (float)step1,
                                       (float)step2,
                                       1,
                                       1,
                                       (float)angle1);
	
 
  if(NULL_var == spRectPatternOfPattPad)
    return 5;

  spRectPatternOfPattPad->Update();


  CATIPrtPattern_var spUserPatt(spRectPatternOfPattPad);
  
  // Sets the keep specification option  
  if(NULL_var != spUserPatt)
  {
    int dsgInt = spUserPatt->GetIfDesignIntent();
    if(0 == dsgInt)
      spUserPatt->SetDesignIntent(1);
  }

  // Builds the pattern
  spRectPatternOfPattPad->Update();

  
	
  // Step 6 - Saves the rectangular pattern

  // Saves the pattern in the second input path
  boolSave = E_FAIL;
  char *nomPart2 = iArgv[2];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart2);
  if(!SUCCEEDED(boolSave))
    return 6;

  // Unused pointer deletion
  if(spPrtCont)
  {
    spPrtCont->Release();
    spPrtCont = NULL;
  }
  
  // Close of the session 
  boolSave = ::Delete_Session("SampleSession"); 
  if(!SUCCEEDED(boolSave))
    rc = 7;
  else
    rc = 0;
  
  return rc;
};
