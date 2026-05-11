// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombinedCurveBehavior
//    Implementation of interface CATIFmFeatureBehaviorCustomization for V5V6ExtCombinedCurve 
//
// Note :  CAAEV5V6ExtMmrCombinedCurveBehavior is the same use case as CAAEMmrCombinedCurveBuild. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//====================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrCombinedCurveBehavior.h"
#include "CAAIV5V6ExtMmrCombinedCurve.h"

// FeatureModelerExt Framework
#include "CATIFmFeatureBehaviorCustomization.h"

// CATMecModUseItf Framework
#include "CATIMechanicalProperties.h"     // Active/Desactive status 
#include "CATIMmiUseGeometricalElement.h" // Needed for GetBodyResult
#include "CATIMmiUseMfBRep.h"

// CATMecModLiveUseItf Framework
#include "CATMfBRepDefs.h"                // Useful for the procedural report 
#include "CATIMmiMechanicalFeature.h"

// CATMecModExtendItf Framework
#include "CATIMmiAlgoConfigServices.h"
#include "CATMmiExtendServicesFactory.h" // needs to be backported from V6 to V5        
#include "CATIMmiErrUpdate.h"
#include "CATIMmiUpdateError.h"

// GMOperatorsInterfaces Framework 
#include "CATICGMTopPrism.h"              // Needed to extrude curves
#include "CATCGMCreateTopIntersect.h"     // Needed to intersect extruded surfaces
#include "CATICGMHybOperator.h"           // Needed to intersect extruded surfaces
#include "CATICGMHybIntersect.h"          // needed for intersection

// GMModelInterfaces Framework
#include "CATBody.h"

// Mathematics Framework
#include "CATMathDirection.h"             // Direction of extrusion

// CATMathStream Framework
#include "CATSoftwareConfiguration.h"     // Needed to create topological data

// GeometricObjects Framework
#include "CATGeoFactory.h"                // To extrude input curves along the input directions
#include "CATLine.h"                      // To query a direction

// System Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATListOfCATUnicodeString.h"   // For the list of keys 
#include "CATError.h"
#include "CATErrorMacros.h"

// C++ Standard library
#include "iostream.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// CATMecModExtendItf Framework
#include "CATIMmiProcReport.h"            // needs to be backported
#else
//============================================== 
// V5 only
//============================================== 
// MecModInterfaces Framework
#include "CATIMfProcReport.h"

#endif

CATImplementClass(CAAEV5V6ExtMmrCombinedCurveBehavior, DataExtension, CATIFmFeatureBehaviorCustomization, V5V6ExtCombinedCurve);
CATImplementBOA(CATIFmFeatureBehaviorCustomization,CAAEV5V6ExtMmrCombinedCurveBehavior);

// To declare that V5V6ExtCombinedCurve implements CATIFmFeatureBehaviorCustomization, insert 
// the following line in the interface dictionary:
//
// V5V6ExtCombinedCurve  CATIFmFeatureBehaviorCustomization  libCAAV5V6MmrCombinedCurve
//
//-------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurveBehavior : constructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurveBehavior::CAAEV5V6ExtMmrCombinedCurveBehavior():
    CATIFmFeatureBehaviorCustomization()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurveBehavior : destructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurveBehavior::~CAAEV5V6ExtMmrCombinedCurveBehavior()
{}

//-----------------------------------------------------------------------------
// Update CombinedCurve
// This is called whenever one of the combined curve attributes is modified  
//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::Build()
{
  cout <<" CAAEV5V6ExtMmrCombinedCurveBehavior::Build " << endl;

  HRESULT rc = E_FAIL;

  //========================================================================================
  //
  // The build method takes place as follows :
  //
  // CATTry
  //   o -0- Checking the deactivation status
  //   o -1- Cleaning last update error
  //   o -2- Retrieving data for the procedural report
  //   o  -2-1 Retrieving the two input curves and the two input directions
  //   o  -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
  //   o  -2-3 Retrieving the two bodies corresponding to the two input curves
  //   o -3- Creating the procedural report
  //   o  -3-1 Filling the list of specifications to follow 
  //   o  -3-2 Creating the procedural report
  //   o -4- Running the topological operators 
  //   o  -4-1 Retrieving the geometrical factory
  //   o  -4-2 Retrieving the topological journal
  //   o  -4-3 Retrieving the Algorithm Configuration
  //   o  -4-4 Running the topological operator - extruding curves
  //   o  -4-5 Running the topological operator - computing combined curve
  //   o -5- Storing the procedural report
  //   o -6- Storing the Algorithm Configuration
  //   o -6- Cleaning useless data
  // CATCatch
  //     o -7-1 Managing Update Error
  //     o -7-2 Managing other Error's types
  //
  //========================================================================================
    
  // You declare here the pointers :
  //  - used in the CATTry and CATThrow sections, like piUpdateErrorOnThis 
  //  - initialized in the CATTry section, and not released before a 
  //    method which can throw an error. 
  //
  CATICGMTopPrism *piCurve1Extrude = NULL;
  CATICGMTopPrism *piCurve2Extrude = NULL;
  CATICGMHybOperator *piIntersect = NULL;
  CATBody * pCurve1ExtrudeBody = NULL;
  CATBody * pCurve2ExtrudeBody = NULL;

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  CATIMmiProcReport_var spProcReport = NULL_var;
#else
//============================================== 
// V5 only
//============================================== 
  CATIMfProcReport_var  spProcReport = NULL_var;
#endif

  CATGeoFactory *pGeomFactory = NULL;
  CATSoftwareConfiguration *pSoftConfig = NULL;
  int IsConfigToStore = NULL;
  CATIMmiMechanicalFeature *piCombinedCurveFeat = NULL;
  CATIMmiAlgoConfigServices *piAlgoConfigServices = NULL;  

  CATIMmiUpdateError_var spUpdateErrorOnThis = NULL_var;
            
  CATTry 
  {
    //========================================================================================
    // -0- Checking the deactivation
    //========================================================================================

    int DeactivateState = 0;
    CATIMechanicalProperties_var spMechProp = this;
    if (spMechProp != NULL_var)
    {
      DeactivateState = spMechProp->IsInactive();     
     
      if (1 == DeactivateState)
      {
        spProcReport = this; 
		if (spProcReport != NULL_var)
        rc = spProcReport->InactivateResult();
      }
    }

    //========================================================================================
    // -1- Cleaning last update error
    //========================================================================================
    if (DeactivateState == 0)
    {
      spUpdateErrorOnThis = this;
      if (spUpdateErrorOnThis != NULL_var)
        spUpdateErrorOnThis->UnsetMmiUpdateError();

      //========================================================================================
      //
      // -2- Retrieving Data for the procedural report
      //
      //========================================================================================

      //=====================================================================================
      //
      // -2-1 Retrieving the two input curves and the two input directions
      //
      //=====================================================================================
       
      CATBaseUnknown  *pCurve1 = NULL;
      CATBaseUnknown  *pCurve2 = NULL;
      CATBaseUnknown  *pDirection1 = NULL; 
      CATBaseUnknown  *pDirection2 = NULL; 

      CAAIV5V6ExtMmrCombinedCurve_var spCombinedCurve = this;
      if (spCombinedCurve != NULL_var)
      {
        // Retrieves curves and directions
        rc = spCombinedCurve->GetCurve(1, pCurve1);
        if (SUCCEEDED(rc))
        {
          rc = spCombinedCurve->GetDirection(1, pDirection1);
          if (SUCCEEDED(rc))
          {
            rc = spCombinedCurve->GetCurve(2, pCurve2);
            if (SUCCEEDED(rc))
                rc = spCombinedCurve->GetDirection(2, pDirection2);
          }
        }
     
        if (FAILED(rc))
        {
					// Clean up 
          if (NULL != pCurve1)
					{
						pCurve1->Release();
            pCurve1 = NULL;
          }
          if (NULL != pCurve2)
          {
            pCurve2->Release();
            pCurve2 = NULL;
          }
          if (NULL != pDirection1)
          {
            pDirection1->Release();
            pDirection1 = NULL; 
          }
          if (NULL != pDirection2)
          {
            pDirection2->Release();
            pDirection2 = NULL; 
		  }

		  // An error is created 
          // Access to Update Error

          CATIMmiErrUpdate *piErrorAccess = NULL;
          rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

          CATError * pErrorNoValidInput = NULL;
          if (SUCCEEDED(rc) && NULL != piErrorAccess)
          {
            // Builds a new update error.
            piErrorAccess->CreateNewError(pErrorNoValidInput);
            CATUnicodeString Diagnostic("One of the inputs is wrong.");
            piErrorAccess->SetMmiDiagnostic(pErrorNoValidInput,Diagnostic);
			CATThrow(pErrorNoValidInput);
          }
        }
      }

      //=====================================================================================
      //
      // -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
      //
      //=====================================================================================

      CATMathDirection MathDirection1,MathDirection2;

      if (SUCCEEDED(rc) && pDirection1)
      {
        // Get a pointer on CATline for first direction
        CATLine *pLine1 = NULL;    
        rc = pDirection1->QueryInterface(IID_CATLine, (void**) &pLine1);
    
        if (SUCCEEDED(rc))
        {
          // Get first mathematical direction
          pLine1->GetDirection(MathDirection1);
    
          // Release pointer
          pLine1->Release();
          pLine1 = NULL;
        }
      }

      if (SUCCEEDED(rc) && pDirection2)
      {
        // Get a pointer on CATline for second direction
        CATLine *pLine2 = NULL;
        rc = pDirection2->QueryInterface(IID_CATLine, ( void**) &pLine2);
    
        if (SUCCEEDED(rc))
        {
          pLine2->GetDirection(MathDirection2);
   
          // Release pointer
          pLine2->Release();
          pLine2 = NULL;
        }
      }

      //=====================================================================================
      //
      // -2-3 Retrieving the two bodies corresponding to the two input curves
      //
      //=====================================================================================

      CATBody_var spBodyOfCurve1, spBodyOfCurve2;
      
      if (SUCCEEDED(rc) && pCurve1)
      {
        CATIMmiUseGeometricalElement_var spGeometricalElementOnCurve1 = pCurve1;
      
        if (spGeometricalElementOnCurve1 != NULL_var)
          rc = spGeometricalElementOnCurve1->GetBodyResult(spBodyOfCurve1);
				else 
				{
					// is it a BRep feature?
					CATIMmiUseMfBRep_var spBRepCrv1 = pCurve1;
					if (spBRepCrv1 != NULL_var)
						rc = spBRepCrv1->GetBody(spBodyOfCurve1);
				}
      }

      if (SUCCEEDED(rc) && pCurve2)
      {
        // gets a pointer on CATIMmiUseGeometricalElement on the second input curve
        CATIMmiUseGeometricalElement_var spGeometricalElementOnCurve2 = pCurve2;
        if (spGeometricalElementOnCurve2 != NULL_var)
          rc = spGeometricalElementOnCurve2->GetBodyResult(spBodyOfCurve2);
				else 
				{
					// is it a BRep feature?
					CATIMmiUseMfBRep_var spBRepCrv2 = pCurve2;
					if (spBRepCrv2 != NULL_var)
						rc = spBRepCrv2->GetBody(spBodyOfCurve2);
				}
      }

      //========================================================================================
      //
      // -3- Creating the procedural report
      //     
      //========================================================================================

      //======================================================================================
      // -3-1 Filling the lists of the specifications to follow by the procedural report
      //      
      //======================================================================================

      CATLISTV(CATBaseUnknown_var) ListFeat;
      CATListOfCATUnicodeString ListKeys;

			if (SUCCEEDED(rc))
      {
        ListFeat.Append(pCurve1); 
        ListKeys.Append(MfKeyNone);    
        ListFeat.Append(pDirection1); 
        ListKeys.Append(MfKeyNone);
        ListFeat.Append(pCurve2); 
        ListKeys.Append(MfKeyNone);
        ListFeat.Append(pDirection2); 
        ListKeys.Append(MfKeyNone);
      }
 
      // No more need of those pointers 
      if (pCurve1)
      {
        pCurve1->Release();
        pCurve1 = NULL;
      }
      if (pCurve2)
      {
        pCurve2->Release();
        pCurve2 = NULL;
      }
      if (pDirection1)
      {
        pDirection1->Release();
        pDirection1 = NULL; 
      }
      if (pDirection2)
      {
        pDirection2->Release();
        pDirection2 = NULL; 
      }

      // Once the pointers are released, Checking that the bodies of the      
      // curve exist
      //
      if (SUCCEEDED(rc))
      {
        if (spBodyOfCurve1 == NULL_var || spBodyOfCurve2 == NULL_var)
        {

          CATIMmiErrUpdate *piErrorAccess = NULL;
          rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

          CATError * pErrorNoValidInput = NULL;
          if (SUCCEEDED(rc) && NULL != piErrorAccess)
          {
            // An error is created 
            piErrorAccess->CreateNewError(pErrorNoValidInput);
            CATUnicodeString Diagnostic("One of the curves has no topology.");
            piErrorAccess->SetMmiDiagnostic(pErrorNoValidInput,Diagnostic);
            CATThrow(pErrorNoValidInput);
          }
        }
      } 

      //======================================================================================
      // -3-2 Creating the procedural report with the list
      //     
      //======================================================================================

      if (SUCCEEDED(rc))
      {
        spProcReport = this;
        if (spProcReport != NULL_var)
        {
          // Creates the procedural report- the result is associated with the
          // feature itself - so BoolOper is 0
          int BoolOper = 0;
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
          rc = spProcReport->CreateProcReport(ListFeat, ListKeys, BoolOper); 
#else
//============================================== 
// V5 only
//==============================================
		  spProcReport->CreateProcReport(ListFeat,ListKeys,BoolOper); 
#endif
        }
      }

      //========================================================================================
      //
      // -4- Running the procedural report
      //
      //========================================================================================
       
      //=====================================================================================
      //
      // -4-1 Retrieving the geometrical factory
      //
      //=====================================================================================
      if (SUCCEEDED(rc) && spProcReport != NULL_var)
      {
		CATGeoFactory_var LocalFactory;
        rc = spProcReport->GetGeoFactoryFromFeature(LocalFactory);
		if (SUCCEEDED(rc) && NULL_var != LocalFactory)
        rc  = LocalFactory->QueryInterface(IID_CATGeoFactory, (void**) &pGeomFactory);		 
      }

      //=====================================================================================
      //
      // -4-2 Retrieving the topological journal which contains the description
      //      of all basic topological operations.
      //
      //=====================================================================================

	  rc = QueryInterface(IID_CATIMmiMechanicalFeature,(void **) & piCombinedCurveFeat);

	  // Create CATIMmiAlgoConfigServicesServices component
      rc = CATMmiExtendServicesFactory::CreateAlgoConfigServicesAccess(piAlgoConfigServices);
	
      CATTopData TopData;
      if (SUCCEEDED(rc) && spProcReport != NULL_var)
      {
        // do not release this pointer
        // This method can throw an error
        CATCGMJournalList *pCGMJournalList = NULL;
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
		rc = spProcReport->GetCGMJournalList(pCGMJournalList);  
#else 
//============================================== 
// V5 only
//==============================================
		pCGMJournalList = spProcReport->GetCGMJournalList();  
#endif
        TopData.SetJournal(pCGMJournalList) ;
             
        //=====================================================================================
        //
        // -4-3 Retrieving the Algorithm Configuration which contains datas used to
        //      version features
        //
        //=====================================================================================

		if (piCombinedCurveFeat && piAlgoConfigServices)
		{
		  rc = piAlgoConfigServices->GetConfiguration(piCombinedCurveFeat ,pSoftConfig ,IsConfigToStore);
               
          if (SUCCEEDED(rc))
          {
		     // SetSoftwareConfig	
		     TopData.SetSoftwareConfiguration(pSoftConfig);
		     // release pSoftConfig after the procedural report ending
		  }
        }
      }

      //=====================================================================================
      //
      // -4-4 Running the topological operator extruding the two curves in both senses 
      //      defined by each direction
      //
      //=====================================================================================

      if (SUCCEEDED(rc))
      {
        CATLength StartOffset = 1000;
        CATLength EndOffset   = -StartOffset;

        // First topological operator : extrudes the first curve
        // This method can throw an error
        piCurve1Extrude = ::CATCGMCreateTopPrism(pGeomFactory,
					                                      &TopData,
					                                      spBodyOfCurve1,
					                                      &MathDirection1,
					                                      StartOffset ,
					                                      EndOffset);
          
        if (piCurve1Extrude)
        {
          CATLONG32 nbError = 0;
          CATError ** pListError = NULL;
          CATBoolean Check = piCurve1Extrude->CheckOperands(nbError,pListError);
          if (TRUE == Check)
          {
            // Runs the first topological operator
            piCurve1Extrude->Run();
	   
            // Gets the first resulting extrusion
            pCurve1ExtrudeBody = piCurve1Extrude->GetResult();
          }
          else
            CATThrow(pListError[0]);; 
        }        
       
        if (SUCCEEDED(rc) && NULL != pCurve1ExtrudeBody)
        {
          //  Second topological operator : extrudes the second curve
          // This method can throw an error
          piCurve2Extrude = ::CATCGMCreateTopPrism(pGeomFactory,
                                                   &TopData,
			                                        spBodyOfCurve2,
			                                        &MathDirection2,
			                                        StartOffset,
			                                        EndOffset);
	   
          if (piCurve2Extrude)
          {
            CATLONG32 nbError = 0;
            CATError ** pListError = NULL;
            CATBoolean Check = piCurve2Extrude->CheckOperands(nbError,pListError);
            if (TRUE == Check)
            {
              // Runs the second topological operator
              piCurve2Extrude->Run();
        
              // Gets the second resulting extrusion
              pCurve2ExtrudeBody = piCurve2Extrude->GetResult();
            }
            else                   
              CATThrow(pListError[0]);
          }
        }
      }
 
      //=====================================================================================
      //
      // -4-5 Running the topological operator computing the intersection of 
      //      the two surfaces 
      //      
      //=====================================================================================

      CATBody *pResultBody = NULL;

      if (SUCCEEDED(rc) &&  pCurve2ExtrudeBody && pCurve1ExtrudeBody)
      {
        // third topological operator : computes the intersection between two surfaces
        // This method can throw an error
        piIntersect = ::CATCGMCreateTopIntersect(pGeomFactory,
					                                       &TopData,
					                                       pCurve1ExtrudeBody,
					                                       pCurve2ExtrudeBody);
   
        if (NULL != piIntersect)
        {
          // Runs the topological operator
          piIntersect->Run();
            
          // Gets the result of the intersection
          pResultBody = piIntersect->GetResult();             
        }
      }

      //========================================================================================
      //
      // -5- Storing the procedural report
      //
      //========================================================================================

      if (SUCCEEDED(rc) && spProcReport != NULL_var)
      {
        if (pResultBody)
        {
          int BoolOper = 0 ; // same as CreateProcReport
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
          rc = spProcReport->StoreProcReport(pResultBody, NoCopy, BoolOper); 
#else
//============================================== 
// V5 only
//==============================================
		   spProcReport->StoreProcReport(pResultBody,NoCopy,BoolOper); 
#endif

          //===============================================================================
          //
          // -6- Storing the Algorithm Configuration
          //
          //===============================================================================

		  if (IsConfigToStore == 1)
		  {
			if (piCombinedCurveFeat && piAlgoConfigServices)
            rc = piAlgoConfigServices->StoreConfiguration(piCombinedCurveFeat ,pSoftConfig);
		  }
        }
        else
        {
          // creates an error if the intersection failed
          CATIMmiErrUpdate *piErrorAccess = NULL;
          rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

          CATError * pErrorNoIntersection = NULL;
          if (SUCCEEDED(rc) && NULL != piErrorAccess)
          {
            // Builds a new update error.
            piErrorAccess->CreateNewError(pErrorNoIntersection);
            CATUnicodeString Diagnostic("The two extruded curves do not intersect.");
            piErrorAccess->SetMmiDiagnostic(pErrorNoIntersection,Diagnostic);
            CATThrow(pErrorNoIntersection);
          }
        }
      }
        
      //========================================================================================   
      //
      // -7- Cleaning Useless Data, the possible solutions are:
      //
      //========================================================================================
       
      // Removes the intermediates bodies from the geometric container
      if (pGeomFactory && pCurve1ExtrudeBody)
      {
        pGeomFactory->Remove(pCurve1ExtrudeBody);
        pCurve1ExtrudeBody = NULL;
      }

      if (pGeomFactory && pCurve2ExtrudeBody)
      {
        pGeomFactory->Remove(pCurve2ExtrudeBody);
        pCurve2ExtrudeBody = NULL;
      }
       
      // Deletes the first topological operator
      if (piCurve1Extrude)
      {
        piCurve1Extrude->Release();
        piCurve1Extrude = NULL;
      }

      // Deletes the second topological operator
      if (piCurve2Extrude)
      {
        piCurve2Extrude->Release();
        piCurve2Extrude = NULL;
      }
      // Deletes the third topological operator
      if (piIntersect)
      {
        piIntersect->Release();
        piIntersect = NULL;
      }

      // Releases the software configuration
      if (pSoftConfig)
      {
	      pSoftConfig->Release();
	      pSoftConfig = NULL;
      }

      // Releases the geometrical factory
      if (pGeomFactory) 
      {
        pGeomFactory->Release();
        pGeomFactory = NULL;
      }

	  // Releases AlgoConfigservices
	  if (piAlgoConfigServices)
	  {
		piAlgoConfigServices->Release();
		piAlgoConfigServices = NULL;
	  }

	  // Release pointer on this
	  if (piCombinedCurveFeat)
	  {
        piCombinedCurveFeat->Release();
		piCombinedCurveFeat = NULL;
	  }
    }
  }   

  //========================================================================================
  //
  // -7- Managing errors 
  //
  //========================================================================================
      
  CATCatch (CATError , pError)
  {
		CATError * pErrorToThrow = NULL;

    // Create access to Update Error
    CATIMmiErrUpdate *piErrorAccess = NULL;
    rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

    if (SUCCEEDED(rc) && NULL != piErrorAccess)
    {
	  // Check if the error is already an update error or not
	  if (S_OK == piErrorAccess->IsAnUpdateError(pError))
	  {
		// Associates the error with the Combined Curve
        if(NULL_var != spUpdateErrorOnThis)
		  spUpdateErrorOnThis->SetMmiUpdateError(pError);
	  }
	  else
	  {
        // Builds a new update error.
        piErrorAccess->CreateNewError(pErrorToThrow);
	    piErrorAccess->SetMmiDiagnostic(pErrorToThrow,pError->GetNLSMessage());

		// Clean-up
		::Flush(pError);

        // Associates the error with the Combined Curve
        if (spUpdateErrorOnThis != NULL_var) 
        spUpdateErrorOnThis->SetMmiUpdateError(pErrorToThrow);
	  }
    }

    // Releases or deletes the pointer which can be valuated
    // but not released before an error
    //
   
    // Deletes the result ( proc report + pResultBody )
    if (spProcReport != NULL_var)
      spProcReport->DeleteProcReport();

    // Deletes the first topological operator
    if (piCurve1Extrude)
    {
      piCurve1Extrude->Release();
      piCurve1Extrude = NULL ;
    }
    // Deletes the second topological operator
    if (piCurve2Extrude )
    {
      piCurve2Extrude->Release();
      piCurve2Extrude = NULL ;
    }
    // Deletes the third topological operator
    if (piIntersect)
    {
      piIntersect->Release();
      piIntersect = NULL ;
    }

    // Removes the intermediate CATBody
    if (pGeomFactory && pCurve1ExtrudeBody)
    {
      pGeomFactory->Remove(pCurve1ExtrudeBody);
      pCurve1ExtrudeBody = NULL;
    }

    if (pGeomFactory && pCurve2ExtrudeBody)
    {
      pGeomFactory->Remove(pCurve2ExtrudeBody);
      pCurve2ExtrudeBody = NULL ;
    }

    // Deletes the pointer on the geometric container
    if (pGeomFactory) 
    {
      pGeomFactory->Release();
      pGeomFactory = NULL;
    }

		// Releases AlgoConfigservices
		if (piAlgoConfigServices)
		{
		  piAlgoConfigServices->Release();
			piAlgoConfigServices = NULL;
		}

		// Release pointer on this
		if (piCombinedCurveFeat)
		{
      piCombinedCurveFeat->Release();
		  piCombinedCurveFeat = NULL;
		}
  
    // Releases the software configuration
    if (pSoftConfig)
    {
	    pSoftConfig->Release();
	    pSoftConfig = NULL ;
    }
        
     // Re-dispatches the error.
     // In interactive mode, this errror will be caught by CATPrtUpdateCom that
     // knows how to handle such errors.
		if (pErrorToThrow)
     CATThrow(pErrorToThrow);
		else
		 CATRethrow;
  }
        
  CATEndTry;
    
  return rc;

}            


//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CanBeRemoved(CATBoolean &) const
{
	return E_NOTIMPL;
}


HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::BeforeRemove()
{
  return E_NOTIMPL;
}

//
HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CcpRegisterAdditionalObjectsForCopy(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const

{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CcpUpdate(const CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}
HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CcpUpdate(CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CcpPaste(const CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}
HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CcpPaste(CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCombinedCurveBehavior::CcpRegisterAdditionalObjectsForRemove(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const

{
	return E_NOTIMPL; 
}


