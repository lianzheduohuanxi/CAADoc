/**
 * @quickReview AW4 12:05:23 'CATOsmSUHandler.h' instead of 'CATCatalogFactoryServices.h' and 'CATICatalog.h'
 * @quickReview sqa 04:01:09
 * @quickReview frn 03:06:26
 */
// COPYRIGHT DASSAULT SYSTEMES 1999
// All right reserved

//==========================================================================
//	Sample code for : Part Interfaces
//	Mission	                : Build of two UserPad features
//	
//	Type                    : Batch program
//	Inputs                  : Two paths to record the created features
//	Outputs	                : Return code is 0 if program worked ok, >0 otherwise
//	 
//	Illustrates             : CATIBuild and CATIBuildShape creation
//
//	
//  Steps :
//    1. Creation of a rectangular sketch in the (o,x,y) plane
//    2. Creation of a UserPad with this sketch
//       The UserPad is created reading the catalog and instantiating the startup
//    3. Creation of a rectangular sketch in a perpendicular plane than the first 
//       sketch plane
//    4. Creation of a second UserPad with the second sketch 
//       The UserPad is created in the same way than the first
//
// 
//==========================================================================

//==========================================================================
// How to execute :
// 
//   CAAPriBuildUserPad Part1 Part2
//
//   with : Part1 path to the first saved part
//          Part2 path to the second saved part
//         
//
// Example :
//   CAAPriBuildUserPad E:\CAA2WS\tmp\UserPad1.CATPart E:\CAA2WS\tmp\UserPad2.CATPart      
//
// NB : the startup catalog must be in the directory resources/graphic
//
//
// Return code :
//   0 successful execution
//   1 number of arguments incorrect
//   2 problem during session creation
//   3 problem during first UserPad creation
//   4 problem during first UserPad record
//   5 problem during second UserPad creation
//   6 problem during second UserPad record
//   7 problem during session closing
// 
//==========================================================================


// ObjectModelerBase Framework
#include "CATSession.h"	            // needed to manage session
#include "CATDocument.h"            // needed to manage the CATPart document
#include "CATDocumentServices.h"    // needed to create the document
#include "CATSessionServices.h"     // needed to create the session
#include "CATInit.h"                // needed to access Mechanical design container

// Mathematics Framework
#include "CATMathPlane.h"           // needed to create the 2 sketches
#include "CATMathDirection.h"       // needed to define the sketches direction
#include "CATMathPoint.h"           // needed to define the planes origins
 

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
#include "CATIPrtPart.h"

// PartInterfaces Framework
#include "CATIPrtFactory.h"         // needed to create UserPad profile
#include "CATIPrtProfile.h"         // needed to valuate UserPad attribute

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"         // needed to query interface
#include "CATISpecAttrAccess.h"			// needed to access Userpad attributes
#include "CATISpecAttrKey.h"				// needed to access Userpad attribute keys
#include "CATIDescendants.h"        // needed to aggregate Userpad attribute
#include "CATOsmSUHandler.h"        //needed to Access catalog and instaniciate Startup


// MechanicalModeler Framework
#include "CATMfDefs.h"              // needed to define the keys of the procedural report
#include "CATIPrtProceduralView.h"  // needed to insert UserPad feature in the procedural view



//================================================================================
// method for the creation of a UserPad feature
// steps :
//  1. Opens the startup catalog
//  2. Retrieves the UserPad startup and instanciates it
//  3. Valuates the attribute
//
// NB : To be found at runtime the catalog must in the directory resources/graphic
//=================================================================================
CATISpecObject_var CreateUserPad(const CATIContainer_var& ispPrtCont,
                                 const CATISpecObject_var& ispSketch)
{

  // Step 1 and 2 Opens the startup catalog. Retrieves the UserPad startup and instanciates it

	CATUnicodeString startupType = "CAAPriUserPad";
  CATUnicodeString ClientId = "SAMPLES";
  CATUnicodeString StorageName = "CAAPriFormFeature.CATfct";

	CATOsmSUHandler novelSUHandler(startupType, ClientId, StorageName );

  CATISpecObject_var spUserPad;
	HRESULT rc = novelSUHandler.Instanciate(spUserPad, ispPrtCont, CATUnicodeString("CAAOsmNovel1"));
	
	if( FAILED(rc) ) 
    return NULL_var;

  if (NULL_var != spUserPad)
  { 
    // insert the feature in the procedural view
    CATIPrtProceduralView_var spProcViewOnUserPad(spUserPad);
    spProcViewOnUserPad->InsertInProceduralView(NULL_var);


    // Step 3 - Valuates the attribute

    // Creates a profile
    CATIPrtFactory_var spPrtFactoryOnContainer(ispPrtCont);
    CATISpecObject_var spProfile = spPrtFactoryOnContainer->CreateProfile();


    // Retrieves the profile attribute
		CATISpecAttrAccess * piSpecAttrAccessOnUserPad = NULL; 
		rc = spUserPad->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnUserPad);
		
		if ( SUCCEEDED(rc) ) 
		{ 
			// Gets a pointer on the Profile attribute key
			CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
			piSpecAttrKeyOnProfile = piSpecAttrAccessOnUserPad->GetAttrKey("Profile");
			
			if ( NULL != piSpecAttrKeyOnProfile )
			{
				piSpecAttrAccessOnUserPad->SetSpecObject(piSpecAttrKeyOnProfile, spProfile);
				
				piSpecAttrKeyOnProfile->Release();
				piSpecAttrKeyOnProfile = NULL ;
				
				// Aggregates the profile
				CATIDescendants_var spRootOnUserPad(spUserPad);
				spRootOnUserPad->Append(spProfile);
				
				// Valuates the profile
				if (NULL_var != ispSketch)
				{
					CATIPrtProfile_var spPrtProfileOnProfile(spProfile);
					spPrtProfileOnProfile->AddElement(ispSketch);
				}
			}
			else
				spUserPad = NULL_var;
			
			piSpecAttrAccessOnUserPad->Release();
			piSpecAttrAccessOnUserPad = NULL;

		}
		else
			spUserPad = NULL_var;
	}

  return spUserPad;
}


//================================================================================
// Main Method 
// 
// Creates two UserPad with rectangular sketchs
//
// Steps:
//  1. Opens a session
//  2. Creates a first sketch
//  3. Creates a UserPad with the first sketch
//  4. Saves the first UserPad
//  5. Creates a second sketch
//  6. Creates a UserPad with the second sketch
//  7. Saves the second UserPad
//================================================================================
int main(int iArgc,         // Number of arguments (2)
		 char *iArgv[])     // Paths for the 2 created parts
{
  int rc=0;

  // Step 1. Opens a session

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

	
  // Retrieves the sketcher factory to instantiate objects
  CATISketchFactory_var spSketchFactOnPrtCont(spPrtCont);

  // Step 2 - Creates a first sketch

  // Creates the sketch plane	for the first UserPad
  // retrieves the reference planes of the part
  CATISketch_var spSketch1;
  CATListValCATISpecObject_var spListRefPlanes;

  if(spPrtCont && NULL_var!=spSketchFactOnPrtCont)
  {
    CATIPrtPart_var spPart = spPrtCont->GetPart();
    if(NULL_var!=spPart)
    {
      spListRefPlanes = spPart->GetReferencePlanes();

      // defines the yz plane as the first sketch plane
      CATISpecObject_var spSketchPlane = spListRefPlanes[1];

      // Instantiates the sketch with the plane
      spSketch1 = spSketchFactOnPrtCont->CreateSketch(spSketchPlane);

      // Retrieves the 2D factory to create the lines and points of the sketch
      CATI2DWFFactory_var spWF2DFactOnSketch1(spSketch1);

      if(NULL_var!=spSketch1 && NULL_var!=spWF2DFactOnSketch1)
      {
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
        if(NULL_var!=spCurveOnLine1Sk1)
        {
          spCurveOnLine1Sk1->GetStartPoint();
          spCurveOnLine1Sk1->GetEndPoint();
        }
        CATI2DCurve_var spCurveOnLine2Sk1(spLine2Sk1);
        if(NULL_var!=spCurveOnLine2Sk1)
        {
          spCurveOnLine2Sk1->GetStartPoint();
          spCurveOnLine2Sk1->GetEndPoint();
        }
        CATI2DCurve_var spCurveOnLine3Sk1(spLine3Sk1);
        if(NULL_var!=spCurveOnLine3Sk1)
        {
          spCurveOnLine3Sk1->GetStartPoint();
          spCurveOnLine3Sk1->GetEndPoint();
        }
        CATI2DCurve_var spCurveOnLine4Sk1(spLine4Sk1);
        if(NULL_var!=spCurveOnLine4Sk1)
        {
          spCurveOnLine4Sk1->GetStartPoint();
          spCurveOnLine4Sk1->GetEndPoint();
        }

        // Closes the sketch edition
        spSketch1->CloseEdition();
      }      
    }
  }
	
	
  // Creates the UserPad by instantiating the startup
	

  // Step 3 - Creates a UserPad with the first sketch

  CATISpecObject_var spUserPad1 = CreateUserPad(spPrtCont,
                                                spSketch1);
  if(NULL_var == spUserPad1)
    return 3;
	
  spUserPad1->Update(); // Builds the pad

  
  // Step 4 - Saves the first UserPad

  // Saves the created pad in the first input path
  HRESULT boolSave = E_FAIL;
  char *nomPart1 = iArgv[1];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart1);
  if(!SUCCEEDED(boolSave))
    return 4;

  // Step 5 -  Creates a second sketch
	
  // Creates the second sketch plane for the second UserPad	
  // Defines the zx plane as the second sketch plane
  CATISpecObject_var spSketchPlane2 = spListRefPlanes[3];

  // Instantiates the sketch with the plane
  CATISketch_var spSketch2 = spSketchFactOnPrtCont->CreateSketch(spSketchPlane2);
      
  // Retrieves the 2D factory to create the lines and points of the sketch
  CATI2DWFFactory_var spWF2DFactOnSketch2(spSketch2);


  // Creates the elements of the sketch
  double pt1Sk2[2] = {5., 4.}, 
         pt2Sk2[2] = {-5., 4.},
         pt3Sk2[2] = {-5., -4.},
         pt4Sk2[2] = {5., -4.};

  // Edits the sketch, draws the lines and creates the start and end points.
  spSketch2->OpenEdition();
  // defines the lines
  CATISpecObject_var spLine1Sk2 = spWF2DFactOnSketch2->CreateLine(pt1Sk2,pt2Sk2);
  CATISpecObject_var spLine2Sk2 = spWF2DFactOnSketch2->CreateLine(pt2Sk2,pt3Sk2);
  CATISpecObject_var spLine3Sk2 = spWF2DFactOnSketch2->CreateLine(pt3Sk2,pt4Sk2);
  CATISpecObject_var spLine4Sk2 = spWF2DFactOnSketch2->CreateLine(pt4Sk2,pt1Sk2);

  // defines the points
  CATI2DCurve_var spCurveOnLine1Sk2(spLine1Sk2);
  spCurveOnLine1Sk2->GetStartPoint();
  spCurveOnLine1Sk2->GetEndPoint();
  CATI2DCurve_var spCurveOnLine2Sk2(spLine2Sk2);
  spCurveOnLine2Sk2->GetStartPoint();
  spCurveOnLine2Sk2->GetEndPoint();
  CATI2DCurve_var spCurveOnLine3Sk2(spLine3Sk2);
  spCurveOnLine3Sk2->GetStartPoint();
  spCurveOnLine3Sk2->GetEndPoint();
  CATI2DCurve_var spCurveOnLine4Sk2(spLine4Sk2);
  spCurveOnLine4Sk2->GetStartPoint();
  spCurveOnLine4Sk2->GetEndPoint();

  // Closes the sketch edition
  spSketch2->CloseEdition();
	
	
  // Step 6 - Creates a UserPad with the second sketch

  // Creates the second UserPad
  CATISpecObject_var spUserPad2 = CreateUserPad(spPrtCont,
                                                spSketch2);

  if(NULL_var == spUserPad2)
    return 5;
  spUserPad2->Update();


  // Step 7 - Saves the second UserPad

  // Saves the second UserPad in the second input path
  boolSave = E_FAIL;
  char *nomPart2 = iArgv[2];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart2);
  if(!SUCCEEDED(boolSave))
    return 4;

  // Releases the unused pointer
  if(spPrtCont)
  {
    spPrtCont->Release();
    spPrtCont = NULL;
  }


  // Closes the session   
  boolSave = ::Delete_Session("SampleSession"); 
  if(!SUCCEEDED(boolSave))
    rc = 7;
  else
    rc = 0;

  return rc;
}
