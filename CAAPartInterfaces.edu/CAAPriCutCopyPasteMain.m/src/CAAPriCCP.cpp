/**
 * @quickReview AW4 12:05:23 'CATOsmSUHandler.h' instead of 'CATCatalogFactoryServices.h' and 'CATICatalog.h'
 * @quickReview sqa 04:01:09
 * @quickReview frn 03:06:26
 * @quickReview JDE 03:02:20
 */
// COPYRIGHT DASSAULT SYSTEMES 1999
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission         : Build of two UserPad features
//	
//  Type            : Batch program
//  Inputs          : Two paths to record the created features
//  Outputs         :	Return code is 0 if program worked ok, >0 otherwise
//	 
//  Illustrates     : Cut/Copy/Paste
//
//	
//  Steps :
//    1. Creation of a rectangular sketch in the (o,x,y) plane
//    2. Creation of a UserPad with this sketch
//       The UserPad is created reading the catalog and instantiating the startup
//    3. Creation of a rectangular sketch in a parallel plane to the first sketch 
//       plane
//    4. Creation of a second rectangular sketch
//    5. Copy/Paste operation from the UserPad to the second sketch
// 
//==========================================================================

//==========================================================================
// How to execute :
// 
//   CAAPriCCP Part1 Part2
//
//   with : Part1 path to the first saved part
//          Part2 path to the second saved part
//         
//
// Example :
//   CAAPriCCP E:\CAA2WS\tmp\CCPPad1.CATPart E:\CAA2WS\tmp\CCPPad2.CATPart      
//
// NB : the startup catalog must be in the directory resources/graphic
//
//
// Return code :
//   0 successful execution
//   1 number of arguments incorrect
//   2 problem during session creation
//   3 problem during first UserPad creation
//   4 problem during first UserPad recording
//   5 problem during CATIShapeFeatureProperties test
//   6 problem during Copy/Paste operation recording
//==========================================================================


// ObjectModelerBase Framework
#include "CATSession.h"             // needed to manage session
#include "CATDocument.h"            // needed to manage the CATPart document
#include "CATDocumentServices.h"    // needed to create the document
#include "CATSessionServices.h"     // needed to create the session
#include "CATInit.h"                // needed to access Mechanical design container
#include "CATICutAndPastable.h"     // needed to perform Cut/Copy/Paste operation

// Mathematics Framework
#include "CATMathPlane.h"           // needed to create the 2 sketches
#include "CATMathDirection.h"       // needed to define the sketches direction
#include "CATMathPoint.h"           // needed to define the planes origins
 
// SketcherInterfaces Framework
#include "CATISketchFactory.h"      // needed to create sketches
#include "CATI2DWFFactory.h"        // needed to draw the sketches
#include "CATISketch.h"             // needed to manage sketches
#include "CATI2DCurve.h"            // needed to draw the lines of the sketches
#include "CATI2DPoint.h"            // needed to access the points of the sketches


// MecModInterfaces Framework
#include "CATIPrtContainer.h"       // needed to manage Mechanical Design features
#include "CATIPrtPart.h"            // needed to update after Copy/Paste operation

// PartInterfaces Framework
#include "CATIPrtFactory.h"         // needed to create UserPad profile
#include "CATIPrtProfile.h"         // needed to valuate UserPad attribute

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"         // needed to query interface
#include "CATISpecAttrAccess.h"			// needed to access Userpad attributes
#include "CATISpecAttrKey.h"				// needed to access Userpad attribute keys
#include "CATIDescendants.h"        // needed to aggregate Userpad attribute
//#include "CATICatalog.h"            // needed to access UserPad startup   // Use CATOsmSUHandler instead
//#include "CATCatalogFactoryServices.h" //needed to open StartUp catalog   // Use CATOsmSUHandler instead
#include "CATOsmSUHandler.h"


// MechanicalModeler Framework
#include "CATMfDefs.h"              // needed to define the keys of the procedural report
#include "CATIPrtProceduralView.h"  // needed to insert UserPad feature in the procedural view
#include "CATIShapeFeatureProperties.h" // needed to test that the userpas is a form feature
// Visualization Framework
#include "CATPathElement.h"         // needed to create a path element on a sketch


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

  // Step 1 - Opens the startup catalog

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
// Creates a UserPad with a rectangular sketch
// and performs a Copy/Paste operation on a second sketch
//
// Steps:
//  1. Opens a session
//  2. Creates a first sketch
//  3. Creates a UserPad with the first sketch
//  4. Saves the first UserPad
//  5. Creates a second sketch
//  6. Performs a Copy of the UserPad pn the second sketch
//  7. Saves the second UserPad
//================================================================================
int main(int iArgc,			// Number of arguments (2)
				 char *iArgv[]) // Paths for the 2 created parts
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

  // Locks the document
  // it prevents from losing data during Cut/Copy/Patste operation
  // when performing a batch. Don't forget to unlock document
  // before closing it.
  CATLockDocument((*pDoc));

  CATIPrtContainer *spPrtCont = 
    (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	

	
  // Retrieves the sketcher factory to instantiate objects
  CATISketchFactory_var spSketchFactOnPrtCont(spPrtCont);

  // Step 2 - Creates a first sketch

  // Creates the sketch plane	for the first UserPad
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
	
  // Creates the second sketch plane for the copy/paste of the UserPad.
  // Defines the yz reference plane
  CATISpecObject_var spSketchPlane2 = spListRefPlanes[2];
	
  // Instantiates the sketch with the plane
  CATISketch_var spSketch2 = spSketchFactOnPrtCont->CreateSketch(spSketchPlane2);

  // Retrieves the 2D factory to create the lines and points of the sketch
  CATI2DWFFactory_var spWF2DFactOnSketch2(spSketch2);

  // Creates the elements of the sketch
  double pt1Sk2[2] = {15., 5.}, 
         pt2Sk2[2] = {25., 5.},
         pt3Sk2[2] = {25., 25.}, 
         pt4Sk2[2] = {15., 25.};

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


  // Step 6 - Check the type of the userPad
  CATIShapeFeatureProperties * pShapeFeaturePropertiesOnUserPad1 = NULL ;
  HRESULT hr = spUserPad1->QueryInterface(IID_CATIShapeFeatureProperties, 
                                   (void **) &pShapeFeaturePropertiesOnUserPad1) ;
  if ( SUCCEEDED(hr) )
  {
     int ContFeat = pShapeFeaturePropertiesOnUserPad1->IsAContextualFeature();
     if ( 1 == ContFeat )
         return 5 ;
     int FormFeat = pShapeFeaturePropertiesOnUserPad1->IsAFreeFormFeature();
     if ( 0 == FormFeat )
         return 5 ;

     pShapeFeaturePropertiesOnUserPad1->Release();
     pShapeFeaturePropertiesOnUserPad1 = NULL ;
  }else
  {
      return 5 ;
  }

  // Step 7 - Copy/Paste operation
  // We perform a copy of the UserPad and paste it on Sketch2 

  // Constructs a feature to allow Cut/Copy/Paste queries
  CATICutAndPastable_var spStartCAPOnPrtCont(spPrtCont);

  // Appends in a list the path element of Sketch2
  CATLISTV(CATBaseUnknown_var) listTargets;
  if ( spSketch2 != NULL_var )
	{
    CATPathElement *pathTarget = new CATPathElement((CATISketch*)spSketch2); 
    pathTarget->AddFatherElement (CATISpecObject_var(spSketch2)->GetFather()); 
    listTargets.Append(pathTarget);
    pathTarget->Release();
	}

  // Appends in the list the feature to be copied, here is the UserPad
  CATLISTV(CATBaseUnknown_var) listObjectsToCopy;
  listObjectsToCopy.Append(spUserPad1);


  // Determines the specified list of object to be copied with the UserPad
  // Here we add the sketch used by UserPad. This sketch is mandatory to
  // build UserPad after paste operation.
  // The third argument defines a format that specifies the type of container 
  // used. Here we are in a part container and we can used the default value.
  // It precises also that the copy is performed using the specifications of 
  // the feature and not using the geometric result only.
  CATLISTV(CATBaseUnknown_var) listObjectsAlreadyInBoundary;
  int resultat = spStartCAPOnPrtCont->BoundaryExtract(listObjectsAlreadyInBoundary, 
                                                      &listObjectsToCopy,
                                                      NULL);
  
  // Creates a structure to receive the boundary object in the requested format.
  // This structure is created in the clipboard, that is a temporary area
  // that contains all data that will be pasted.
  CATBaseUnknown_var spEltCopy = spStartCAPOnPrtCont->Extract(listObjectsAlreadyInBoundary,
                                                              NULL);



  // Makes Cut/Copy/Paste queries on this new structure
  CATICutAndPastable_var spCAPOnEltCopy(spEltCopy);
 
  // Determines the list of object to be copied with UserPad
  // from the clipboard to the destination container
  CATLISTV(CATBaseUnknown_var) listObjects;
  int resultat2 = spCAPOnEltCopy->BoundaryExtract(listObjects,NULL,NULL);

  // Perfoms the paste operation
  CATICutAndPastable_var spEndCAPOnPrtCont(spPrtCont); 

  // We instantiate the feature in the destination container.
  // It consists in creating the feature, aggregating it at the appropriate position
  // according to the specified target and updating it in its new context
  CATLISTV(CATBaseUnknown_var) spFinalObject = spEndCAPOnPrtCont->Paste(listObjects, 
                                                                        &listTargets,
                                                                        NULL);


  CATISpecObject_var spSpecOnPart(spPart);
  if(NULL_var != spSpecOnPart)
    spSpecOnPart->Update();


  // Step 8 - Saves the result of the Copy/Paste 

  boolSave = E_FAIL;
  char *nomPart2 = iArgv[2];
  boolSave = CATDocumentServices::SaveAs(*pDoc,nomPart2);
  if(!SUCCEEDED(boolSave))
    return 6;

  // Releases the unused pointer
  if(spPrtCont)
  {
    spPrtCont->Release();
    spPrtCont = NULL;
  }

  // Unlocks the document.
  // The document has been locked it is necessary
  // to unlock it before closing.
  CATUnLockDocument((*pDoc));

  // Close the document
  boolSave = CATDocumentServices::Remove(*pDoc);
  if(!SUCCEEDED(boolSave))
    rc = 6;
  else
    rc = 0;
  pDoc = NULL;

   
  // Closes the session 
  boolSave = ::Delete_Session("SampleSession"); 
  if(!SUCCEEDED(boolSave))
    rc = 6;
  else
    rc = 0;

  return rc;
}
