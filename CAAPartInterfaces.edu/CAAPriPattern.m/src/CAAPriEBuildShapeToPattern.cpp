/**
 * @quickReview sqa 05:08:10
 * @quickReview BAG 04:02:25
 * @quickReview sqa 04:01:09
 * @quickReview frn 03:06:26
 */
// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved


// Local Framework
#include <CAAPriEBuildShapeToPattern.h>

// ObjectModelerBase Framework
#include "CATIContainer.h"             // needed to access the geometry factory
#include "CATLISTV_CATBaseUnknown.h"   // needed to manage keys

// PartInterfaces Framework
#include "CATIPrtProfile.h"            // needed to manage the profile of the feature
#include "CATIPrtManageFeatBuild.h"    // needed to indicate if the buildshape is in 
                                       // pattern context

// MechanicalModeler Framework
#include "CATIMfProcReport.h"          // needed to manage the procedural report
#include "CATIGeometricalElement.h"	   // needed to delete the scope of the ResultOUT
#include "CATMfBRepDefs.h"             // needed to manage the proc report
#include "CATMfErrUpdate.h"            // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"           // needed to associate an error to a feature

// MecModInterfaces Framework
#include "CATIPrtContainer.h"          // needed to access to the solid container

// NewTopologicalObjects Framework
#include "CATBody.h"                   // needed to manage the profile and the BodyOUT
#include "CATDomain.h"                 // needed to manage the wire of the profile 
#include "CATWire.h"                   // needed to manage the wire of the profile

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"            // needed to manage the profile
#include "CATISpecAttrAccess.h"				 // needed to access feature attributes
#include "CATISpecAttrKey.h"					 // needed to access feature attribute keys

// GeometricObjects	Framework			
#include "CATGeoFactory.h"             // needed to create the prism operator
#include "CATCGMJournalList.h"         // needed to manage the topological journal

// TopologicalOperators Framework
#include "CATTopPrism.h"               // needed to create the prism operator
#include "CATDynTransformation.h"      // needed to drive the pattern transformation

// Mathematics Framework
#include "CATMathDirection.h"          // needed to define the extrusion direction 
#include "CATMathVector.h"             // needed to define the extrusion direction
#include "CATMathPlane.h"              // needed to define the extrusion direction

// System
#include "CATListOfCATUnicodeString.h" // needed to manage the key list

// Mathematics
#include "CATSoftwareConfiguration.h"  // needed to define the inputs of the 
                                       // topological operators


// To declare that the class 
// is a DataExtension of (late type) CAAPriPatternPad
CATImplementClass(CAAPriEBuildShapeToPattern,
                  DataExtension, 
                  CATBaseUnknown,
                  CAAPriPatternPad);

#include "TIE_CATIBuildShape.h" // needed to tie the implementation to its interface
TIE_CATIBuildShape(CAAPriEBuildShapeToPattern);

// To declare that PatternPad implements CATIBuildShape, insert 
// the following line in the interface dictionary:
//
// CAAPriPatternPad  CATIBuildShape  libCAAPriPattern

//-------------------------------------------------------------------------
// BuildShape method
//-------------------------------------------------------------------------
int CAAPriEBuildShapeToPattern::BuildShape()
{
  int rc = 1;
	
  // Removes all possible update error associated with the UserPad
  // Gets a pointer on CATIUpdateError
  CATIUpdateError *piUpdateErrorOnUserPad = NULL;
  HRESULT boolQuery = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnUserPad); 
  if ( FAILED(boolQuery) )
    return 2;
    
  // removes all error associated to the UserPad
  piUpdateErrorOnUserPad->UnsetUpdateError();

  // Retrieving the different containers
  CATIContainer_var spFeatCont = CATISpecObject_var(this)->GetFeatContainer();  
  CATIPrtContainer_var spPrtContOnFeatCont(spFeatCont);
  CATIContainer_var spSolidCont = spPrtContOnFeatCont->GetSolidContainer();  

  // Since topological operator may raise errors, 
  // it is now much safer to work into a CATTry/CATCatch bloc.

  // Retrieves the geometry factory
  CATGeoFactory_var spGeoFactoryOnSolidCont(spSolidCont);


  CATTopPrism* pOperatorPrism = NULL;
  CATBody_var spProfileBody = NULL_var;

  CATTry
  {


    // Step 1 - Defines a flag to determine if the BuildShape method is called in context
    CATIPrtManageFeatBuild_var spManageBuild(this);		
    int pattern = spManageBuild->IsInPatternContext();	// Pattern = 1 for pattern context.
	

    // Retrieving and defining the elements of the pad operation
		
    // Retrieves the used profile 
    CATISpecObject_var spSpecObj(this);
		CATIPrtProfile_var spPrtProfile = NULL_var;
		CATISpecAttrAccess * piSpecAttrAccessOnThis = NULL;

		HRESULT hr = E_FAIL;
		if(NULL_var != spSpecObj)
			hr = spSpecObj->QueryInterface(IID_CATISpecAttrAccess, 
											(void**) & piSpecAttrAccessOnThis);
		
		if ( SUCCEEDED(hr) ) 
		{ 
			// Gets a pointer on the Profile attribute key
			CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
			piSpecAttrKeyOnProfile = piSpecAttrAccessOnThis->GetAttrKey("Profile");
			
			if ( NULL != piSpecAttrKeyOnProfile )
			{
				CATISpecObject_var spProfile = piSpecAttrAccessOnThis->GetSpecObject(piSpecAttrKeyOnProfile);
				
				piSpecAttrKeyOnProfile->Release();
				piSpecAttrKeyOnProfile = NULL ;

        piSpecAttrAccessOnThis->Release();
			  piSpecAttrAccessOnThis = NULL;

				if( NULL_var != spProfile )
					spProfile->Release();
				spPrtProfile = spProfile;
				
				if( NULL_var != spPrtProfile )
				{
					// Checks if the profile is made with a closed contour
					int nbContour = spPrtProfile->GetContourCount();
					int isClosed = 0;
					if (1 == nbContour)
					{
						CATBody_var spClosedBody;
						spPrtProfile->GetBody(0,spClosedBody);
						CATDomain * pDomain = NULL;
						if( NULL_var != spClosedBody )
							pDomain = spClosedBody->GetDomain(1);
						
						CATWire_var spWireOnDomain(pDomain);
						if ( NULL_var != spWireOnDomain )
						{
							isClosed = spWireOnDomain->IsClosed();
							if(TRUE != isClosed) 
							{
								CATMfErrUpdate *pErrorNotClosedProfile = new CATMfErrUpdate();
								CATUnicodeString Diagnostic("The associated profile is not closed");
								pErrorNotClosedProfile->SetDiagnostic(1,Diagnostic);
								piUpdateErrorOnUserPad->SetUpdateError(pErrorNotClosedProfile);
								CATThrow(pErrorNotClosedProfile);
							}
						}
					}
					else
					{
						
						CATMfErrUpdate *pErrorNotValidProfile = new CATMfErrUpdate();
						CATUnicodeString Diagnostic("No valid profile");
						pErrorNotValidProfile->SetDiagnostic(1,Diagnostic);
						CATThrow(pErrorNotValidProfile);
					}
				}
			}
      else
      {
			  piSpecAttrAccessOnThis->Release();
			  piSpecAttrAccessOnThis = NULL;
      }
		}
    else
		{
      CATMfErrUpdate *pErrorSpecification = new CATMfErrUpdate();
      CATUnicodeString Diagnostic("Specification can not be taken into account");
      pErrorSpecification->SetDiagnostic(1,Diagnostic);
      CATThrow(pErrorSpecification);
		}

    // Defines the PatternPad direction
    // The direction is perpendicular to the sketch plane
    CATMathPlane sketchPlane;
    spPrtProfile->GetPlane(sketchPlane);
    CATMathVector normalDir;
    sketchPlane.GetNormal(normalDir);
    CATMathDirection direction(normalDir);	


    // Definition of the limits 
    CATTopLimitType endLimitType = CatLimOffsetFromProfile;
    CATLength endOffset = 30.;
    CATTopLimitType startLimitType = CatLimOffsetFromProfile;
    CATLength startOffset = 0.;
	
	
    // Definition of the propagation mode
    CATTopPropagationType endPropagType = CatPropagSingle;
    CATTopPropagationType startPropagType = CatPropagSingle;
	


    // Creating the procedural report	
    CATIMfProcReport_var spReport(this);

      // Step 2 - In pattern context, you do not delete the scope
    if (!pattern)
      CATIGeometricalElement_var(this)->DeleteScope();
		
    CATLISTV(CATBaseUnknown_var) listSpec;
    CATLISTV(CATUnicodeString) listKey;
    CATUnicodeString strKey = MfKeyExtrudedFrom;
    CATISpecObject_var spElt;
    spPrtProfile->GetElement(1, spElt);
    listSpec.Append(spElt);
    listKey.Append(strKey);
    spReport->CreateProcReport(listSpec, listKey);
    CATCGMJournalList* pCurrentJournal = NULL;
    pCurrentJournal = spReport->GetCGMJournalList();
	
      // Step 3 - Sets the list of operands.
      //          These operands will be used to compute the pattern shape.
    if (pattern)
      spManageBuild->SetOperand(listSpec, listKey);
		
		
    // Performing the shape building	
    CATBody_var spSolid;
    spPrtProfile->GetBody(1, spProfileBody);
    CATBody_var spTransformBody = spProfileBody;

      // Step 4 - In the pattern context, we must transform geometries
      //          generated from specifications 
	if (pattern)
	{
		// Retrieves the mathematical transformation computed by the pattern
		CATMathTransformation transfo = spManageBuild->GetLocalSketchTransfo();

		// Transformation of the geometry of the profile:

		// Creates a transformation operator and sets its attributes

		// The inputs of the topological operator
		CATSoftwareConfiguration* pSoftConfig = new CATSoftwareConfiguration();
		CATTopData topData(pSoftConfig, pCurrentJournal);

		CATDynTransformation *pTransformation = CATCreateDynTransformation(spGeoFactoryOnSolidCont,
			&topData,
			spProfileBody);

		if(pTransformation)
		{
			pTransformation->SetReportMode(CATDynTransformation::CATDynModification);
			pTransformation->SetTransformation(transfo);
			// Performs the transformation
			pTransformation->Run();
			// Retrieves the resulting geometry
			spTransformBody = pTransformation->GetResult();

			delete pTransformation;
			pTransformation = NULL;
		}


		// Transformation of the pad direction

		CATMathLine axis;
		CATAngle angle(0.);
		CATBoolean isRotated = transfo.IsRotation(axis, angle);
		if (isRotated)
		{
			direction = transfo * direction;
		}
		//MLK
		if (pSoftConfig)
			pSoftConfig->Release();
		pSoftConfig = NULL;
	}
    
    // Defines the prism operator
    CATTopPrism* pOperatorPrism = NULL;

    if (NULL_var != spTransformBody)
	{
      // The inputs of the topological operator
      CATSoftwareConfiguration* pSoftConfig = new CATSoftwareConfiguration();
      CATTopData topData(pSoftConfig, pCurrentJournal);
      pOperatorPrism = CATCreateTopPrism(spGeoFactoryOnSolidCont,
                                         &topData,
                                         spTransformBody, 
                                         &direction, 
                                         startOffset, 
                                         endOffset);


      if(pOperatorPrism)
      {
        pOperatorPrism->SetOperation(CatBoolUnion);
        pOperatorPrism->SetLimit(CatLimStart, 
                                 startLimitType, 
                                 1, 
                                 startOffset, 
                                 NULL, 
                                 CATBody_var(NULL_var), 
                                 startPropagType, 
                                 FALSE);
        pOperatorPrism->SetLimit(CatLimEnd, 
                                 endLimitType, 
                                 0, 
                                 endOffset, 
                                 NULL, 
                                 CATBody_var(NULL_var), 
                                 endPropagType, 
                                 FALSE);
        pOperatorPrism->Run();
        // Retrieves the performed body
        spSolid = pOperatorPrism->GetResult();
      }
	  if (pSoftConfig)
        pSoftConfig->Release();
    }
    if(NULL_var == spSolid)
		{
      CATMfErrUpdate *pErrorBuildShape = new CATMfErrUpdate();
      CATUnicodeString Diagnostic("Error during BuildShape operation");
      pErrorBuildShape->SetDiagnostic(1,Diagnostic);
      CATThrow(pErrorBuildShape);
		}


      // Step 5 - In the Pattern context, the procedural report is not stored
      //          Sets topological journal and the geometry performed.
	    //          There will be used to compute the pattern shape. 
    if (!pattern )
		{ 
      // Store the procedural report
      spReport->StoreProcReport(spSolid, NoCopy);
		}
    else
		{
      // Sets the geometry performed
      spManageBuild->SetBody(spSolid);
      // Sets the topological journal
      spManageBuild->SetCurrentJournal(pCurrentJournal); 
		}
    
    // Cleans the building
    delete pOperatorPrism;
    pOperatorPrism = NULL;
	if (piUpdateErrorOnUserPad)
	{
		piUpdateErrorOnUserPad->Release();
		piUpdateErrorOnUserPad = NULL;
	}

    spGeoFactoryOnSolidCont->Remove(spProfileBody);
    rc = 0;
	}
  CATCatch (CATMfErrUpdate , pUpdateError)
	{
    //------------------------------------------------------------------------------
    // Catches CATMfErrUpdate errors
    //------------------------------------------------------------------------------
        
    // Builds a new update error.
    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    // Add it the diagnostic comming from the error previously caugth.
    pErrorToThrow->SetDiagnostic(1,pUpdateError->GetDiagnostic());
    // Destroys the previous error.
    ::Flush(pUpdateError);
    // Associates the error with the UserPad.
    if(piUpdateErrorOnUserPad)
    {
      piUpdateErrorOnUserPad->SetUpdateError(pErrorToThrow);
      piUpdateErrorOnUserPad->Release();
      piUpdateErrorOnUserPad = NULL;
    }

    // Cleans the building
    if(pOperatorPrism)
		{
      delete pOperatorPrism;
      pOperatorPrism = NULL;
		}
    spGeoFactoryOnSolidCont->Remove(spProfileBody);
	}
  CATEndTry
  return rc;
}

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAPriEBuildShapeToPattern::CAAPriEBuildShapeToPattern()
{
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAPriEBuildShapeToPattern::~CAAPriEBuildShapeToPattern()
{
}

//-------------------------------------------------------------------------
// Copy Constructor
//-------------------------------------------------------------------------
CAAPriEBuildShapeToPattern:: CAAPriEBuildShapeToPattern(const CAAPriEBuildShapeToPattern &ipObjectToCopy)
{
}
