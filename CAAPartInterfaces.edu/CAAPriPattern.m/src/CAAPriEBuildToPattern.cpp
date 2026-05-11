/**
 * @quickReview BAG 04:02:25
 * @quickReview frn 03:06:26
 */
// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved


// Local Framework
#include "CAAPriEBuildToPattern.h"


// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h" // needed to manage list of bodies

// PartInterfaces Framework
#include "CATIShapeFeatureBody.h"        // needed to access to the ResultIN/ResultOUT
                                        // of the feature

// MechanicalModeler Framework
#include "CATIMfProcReport.h"            // needed to manage the proc report
#include "CATIGeometricalElement.h"      // needed to delete the scope of the ResultOUT
#include "CATMfBRepDefs.h"               // needed to access to data of the proc report
#include "CATMfErrUpdate.h"             // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"            // needed to associate an error to a feature


// NewTopologicalObjects Framework
#include "CATBody.h"                     // needed to access to the built shape

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // needed to manage ResultIN/ResultOUT 
#include "CATLISTV_CATISpecAttribute.h"  // needed to access to the BodyIN

// GeometricObjects Framework
#include "CATGeoFactory.h"               // needed to create the boolean operation
#include "CATCGMJournalList.h"           // needed to manage the Topological journal

// TopologicalOperators Framework
#include "CATDynBoolean.h"               // needed to perform boolean operation

// MecModInterfaces Framework
#include "CATIBuildShape.h"              // needed to call the built shape operation
#include "CATIPrtContainer.h"            // needed to access to solid container

// Mathematics
#include "CATSoftwareConfiguration.h"  // needed to define the inputs of the 
                                       // topological operators


// To declare that the class 
// is a DataExtension of (late type) CAAPriPatternPad
CATImplementClass(CAAPriEBuildToPattern, 
                  DataExtension,
                  CATBaseUnknown, 
                  CAAPriPatternPad);

#include "TIE_CATIBuild.h" // needed to tie the implementation to its interface
TIE_CATIBuild(CAAPriEBuildToPattern);

// To declare that PatternPad implements CATIBuild, insert 
// the following line in the interface dictionary:
//
// CAAPriPatternPad  CATIBuild  libCAAPriPattern


//-------------------------------------------------------------------------
// Build method
//-------------------------------------------------------------------------
int CAAPriEBuildToPattern::Build()
{

  int rc = 1;

  // Removes all possible update error associated with the UserPad
  // Gets a pointer on CATIUpdateError
  CATIUpdateError *piUpdateErrorOnUserPad = NULL;
  HRESULT boolQuery = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnUserPad); 
  if ( FAILED(boolQuery) )
    return E_FAIL;
    
  // removes all error associated to the UserPad
  piUpdateErrorOnUserPad->UnsetUpdateError();


  // Getting access to the containers used 
  // spCont		  : Features container
  // spPrtCont		: Mechanical Design features container
  // spSolidCont : Solid container

  CATIContainer_var spFeatCont = CATISpecObject_var(this)->GetFeatContainer();
  CATIPrtContainer_var spPrtContOnFeatCont(spFeatCont);
  CATIContainer_var spSolidCont = spPrtContOnFeatCont->GetSolidContainer();


  // Retrieves the ResultOUT
  CATIShapeFeatureBody_var spFeatBody(this);
  CATISpecObject_var spResultOut = NULL_var;
  spResultOut = spFeatBody->GetResultOUT();

  // Scope deletion
  CATIGeometricalElement_var spGeomEltOnResultOut(spResultOut);
  spGeomEltOnResultOut->DeleteScope();


  // Performs the buildshape operation
  // It builds the shape of the UserPad 
  CATISpecObject_var spUserPad(this);
  CATIBuildShape *piBuildShape = NULL;
  HRESULT hr = spUserPad->QueryInterface(IID_CATIBuildShape,(void**)&piBuildShape);
  if ( SUCCEEDED(hr))
  {
    rc = piBuildShape->BuildShape();
    piBuildShape->Release();
    if(0 != rc)
      return 2;
  }
  else
    return 1;


  // Since topological operator may raise errors, 
  // it is now much safer to work into a CATTry/CATCatch bloc.

  CATDynBoolean *pOperatorBool = NULL;
 
  CATTry
  {
    // Retrieves the shape built during BuildShape operation
    CATListValCATBaseUnknown_var *pListResult = 
      spFeatBody->GetShape("CATBody");
    if (NULL != pListResult)
	{
      CATBody_var spSolid = (*pListResult)[1];
      delete pListResult;

      // If a built shape exists then we build the final geometry
      // associated with the UserPad feature.
      if (NULL_var != spSolid)
	  {
        // Retrieves the previous feature
        CATISpecObject_var spResultIn;
        CATListValCATISpecAttribute_var *pListSpecAttribute = 
          spFeatBody->GetBodyINAttributes();
        CATISpecAttribute_var spSpecAttribute = (*pListSpecAttribute)[1];
        spResultIn = spSpecAttribute->GetSpecObject();
        delete pListSpecAttribute;
        if (NULL_var != spResultIn)
		{
          // To compute the final geometry of the UserPad we perform
          // a boolean operation between the computed shape and the
          // geometry of the previous feature.
				
          // Retrieves the geometry of the previous feature
          CATListValCATBaseUnknown_var *pListBodyIn = 
            spFeatBody->GetBodyIN("CATBody");
          CATBody_var spSolidIn = (*pListBodyIn)[1];		
          delete pListBodyIn;
          if (NULL_var != spSolidIn)
		  {
            // Creation of the procedural report
            CATLISTV(CATBaseUnknown_var) listSpec;
            listSpec.Append(spResultIn);
            listSpec.Append(this);	
            CATLISTV(CATUnicodeString) listKey;
            listKey.Append(MfKeyNone);
            listKey.Append(MfKeyNone);
            int boolOper = 1;				
            CATIMfProcReport_var spReport(this);	
            spReport->CreateProcReport(listSpec, listKey, boolOper);
					
            // Creates the boolean operator for an union operation
            // between the shape built by the UserPad feature
            // and the the geometry of the previous feature.
					
            CATDynBooleanType internalOperType = CATBoolUnion;
            CATGeoFactory_var spGeoFactOnSolidCont(spSolidCont);
            CATCGMJournalList *pCurrentJournal = NULL;
            pCurrentJournal = spReport->GetCGMJournalList();

            // The inputs of the topological operator
            CATSoftwareConfiguration* pSoftConfig = new CATSoftwareConfiguration();
            CATTopData topData(pSoftConfig, pCurrentJournal);
            
            pOperatorBool = CATCreateDynBoolean(spGeoFactOnSolidCont,
                                                &topData,
                                                internalOperType,
                                                spSolidIn,
                                                spSolid);
 
            if(pOperatorBool)
            {
              // Performs the boolean operation
              pOperatorBool->Run();
              // Retrieves the result of the boolean operation
              CATBody_var spSolidOut = pOperatorBool->GetResult();
              if(NULL_var == spSolidOut)
              {
                CATMfErrUpdate *pErrorBooleanOperation = new CATMfErrUpdate();
                CATUnicodeString Diagnostic("Error during boolean operation");
                pErrorBooleanOperation->SetDiagnostic(1,Diagnostic);
                CATThrow(pErrorBooleanOperation);
              }
              delete pOperatorBool;
              pOperatorBool = NULL;
              
			        if (pSoftConfig)
                      pSoftConfig->Release();
              
              // Stores the procedural report
              spReport->StoreProcReport(spSolidOut, Copy, boolOper);
            }
		  }
          else
		  {
            CATMfErrUpdate *pErrorPreviousFeature = new CATMfErrUpdate();
            CATUnicodeString Diagnostic("The previous feature has no geometry");
            pErrorPreviousFeature->SetDiagnostic(1,Diagnostic);
            CATThrow(pErrorPreviousFeature);
		  }
		}
	  }
	}
	if (piUpdateErrorOnUserPad)
	{
		piUpdateErrorOnUserPad->Release();
		piUpdateErrorOnUserPad = NULL;
	}
  }
  CATCatch( CATMfErrUpdate , pUpdateError)
  {
    //------------------------------------------------------------------------------
    // Catches CATMfErrUpdate errors
    //------------------------------------------------------------------------------
        
    // Builds a new update error.
    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    // Add it the diagnostic coming from the error previously caugth.
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

    // Deletes the topological operator
    if ( pOperatorBool)
	{
      delete pOperatorBool;
      pOperatorBool = NULL;
	}
  }
  CATEndTry
  return rc;
}

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAPriEBuildToPattern::CAAPriEBuildToPattern()
{
}


//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAPriEBuildToPattern::~CAAPriEBuildToPattern(){}

//-------------------------------------------------------------------------
// Copy Constructor
//-------------------------------------------------------------------------
CAAPriEBuildToPattern::CAAPriEBuildToPattern(const CAAPriEBuildToPattern &ipObjectToCopy)
{
}
