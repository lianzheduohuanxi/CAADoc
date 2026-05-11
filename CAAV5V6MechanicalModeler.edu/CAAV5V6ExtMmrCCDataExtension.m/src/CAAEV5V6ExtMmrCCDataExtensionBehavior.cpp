// COPYRIGHT DASSAULT SYSTEMES 2012
//===================================================================================================
//
//  CAAEV5V6ExtMmrCCDataExtensionBehavior
//    Implementation of interface CATIFmFeatureBehaviorCustomization for CAAV5V6ExtMmrCCDataExtension 
//
// Note : CAAEV5V6ExtMmrCCDataExtensionBehavior is the same use case as CAAEMmrCCDataExtensionBehavior. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//===================================================================================================

// Local CAAMechanicalModelerExtend.edu framework 
#include "CAAEV5V6ExtMmrCCDataExtensionBehavior.h"
#include "CAAIV5V6ExtMmrCCDataExtension.h"

// FeatureModelerExt framework
#include "CATIFmFeatureBehaviorCustomization.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h" 
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

// CATMathStream Framework
#include "CATSoftwareConfiguration.h"  // Needed to create topological data

// CATMecModUseItf framework
#include "CATIMmiUseGeometricalElement.h" // Needed for GetBodyResult

// CATMecModLiveUseItf Framework           
#include "CATIMmiUseMfBRep.h"
#include "CATIMmiMechanicalFeature.h"

// CATMecModExtendItf Framework          
#include "CATIMmiAlgoConfigServices.h"
#include "CATMmiExtendServicesFactory.h"
#include "CATIMmiErrUpdate.h"
#include "CATIMmiUpdateError.h"

// GMOperatorsInterfaces framework 
#include "CATICGMDynMassProperties3D.h"

// GMModelInterfaces Framework
#include "CATBody.h"
#include "CATTopData.h"

// System framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATUnicodeString.h" 
#include "CATBoolean.h"
#include "CATError.h"
#include "CATErrorMacros.h"

// KnowledgeInterfaces Framework
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATCkeGlobalFunctions.h"
#include "CATIParmAsStored.h"

// SpecialAPI Framework
#include "CATDataType.h"

// C++ Standard library
#include "iostream.h"


CATImplementClass(CAAEV5V6ExtMmrCCDataExtensionBehavior, DataExtension, CATIFmFeatureBehaviorCustomization, CAAV5V6ExtMmrCCDataExtension);
CATImplementBOA(CATIFmFeatureBehaviorCustomization,CAAEV5V6ExtMmrCCDataExtensionBehavior);


// To declare that CAAV5V6ExtMmrCCDataExtension implements CATIFmFeatureBehaviorCustomization, insert 
// the following line in the interface dictionary:
//
// CAAV5V6ExtMmrCCDataExtension  CATIFmFeatureBehaviorCustomization  libCAAMmrCCDataExtension

//-------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCCDataExtensionBehavior : constructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCCDataExtensionBehavior::CAAEV5V6ExtMmrCCDataExtensionBehavior():
    CATIFmFeatureBehaviorCustomization()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCCDataExtensionBehavior : destructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCCDataExtensionBehavior::~CAAEV5V6ExtMmrCCDataExtensionBehavior()
{}

//-----------------------------------------------------------------------------
// Update CCDataExtension
// This is called whenever one of the combined curve attributes is modified  
//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::Build()
{
  cout << "==============================================" <<endl;
  cout <<" CAAEV5V6ExtMmrCCDataExtensionBehavior::Build()" << endl;
  cout << "==============================================" <<endl;

  HRESULT rc = E_FAIL;

  /*-----------------------------
  Build Steps:
  1 - Retrieve the GeomFeature
  2 - Verify GeomFeature is a Geometrical Element
  3 - 2 cases :
  3 - a]It's not a Geometrical Feature => Set Area Parameter as NULL and Rise Information Window
  b - b]It's a Geometrical Feature => Compute Area Value and store it in the Area Parameter
  -----------------------------*/

  CATSoftwareConfiguration *pSoftConfig = NULL;
  CAAIV5V6ExtMmrCCDataExtension *pCCDataExtension = NULL;
  CATIMmiUpdateError *pUpdateErrorOnBaseFeature = NULL;
  CATIMmiUpdateError *piUpdateErrorOnThis = NULL;
  CATUnicodeString ErrorDiagnosis;
  
  CATTry
  {           
    rc = QueryInterface(IID_CATIMmiUpdateError, (void**) &piUpdateErrorOnThis);
    if (SUCCEEDED(rc))
      rc = piUpdateErrorOnThis->UnsetMmiUpdateError();

    //Build Credentials to access features in the catalog
    CATFmCredentials CredentialForDataExt;
    CATUnicodeString ClientId("CAAMmrUseCase");
    CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
    CATUnicodeString CatalogName("CAAV5V6ExtMmrCCDataExtensionCatalog");
    CredentialForDataExt.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId); 
    CredentialForDataExt.RegisterAsCatalogOwner(CatalogName,ClientId);
   
    CATFmFeatureFacade FeatFacadeOnDataExt(CredentialForDataExt, this);

    // Retrieve The Base Feature and Clean its Last UpdateError
    CATFmAttributeValue TheBaseFeatureAsValue ; 
    rc = FeatFacadeOnDataExt.GetBaseFeature(TheBaseFeatureAsValue);
    CATBaseUnknown_var TheBaseFeatureAsFeature = TheBaseFeatureAsValue.GetFeature();
    if (TheBaseFeatureAsFeature != NULL_var)
    {
      rc = TheBaseFeatureAsFeature->QueryInterface(IID_CATIMmiUpdateError , (void**) &pUpdateErrorOnBaseFeature);
      if (SUCCEEDED(rc))
        rc = pUpdateErrorOnBaseFeature->UnsetMmiUpdateError();
    }

    //Start Build Process
    rc = QueryInterface(IID_CAAIV5V6ExtMmrCCDataExtension, (void**) &pCCDataExtension);
    if (SUCCEEDED(rc))
    {
      CATBaseUnknown *pGeomFeature = NULL;

      rc = pCCDataExtension->GetGeomFeature(pGeomFeature);
      if (SUCCEEDED(rc) && pGeomFeature != NULL)
      {
        CATBody_var pBodyOfInputFeature = NULL_var;
        CATIMmiUseGeometricalElement *pGeometricalElementOnInputFeature = NULL;
        rc = pGeomFeature->QueryInterface(IID_CATIMmiUseGeometricalElement, (void**) &pGeometricalElementOnInputFeature);
        if(SUCCEEDED(rc))
        {
          rc = pGeometricalElementOnInputFeature->GetBodyResult(pBodyOfInputFeature);

          pGeometricalElementOnInputFeature->Release();
          pGeometricalElementOnInputFeature = NULL;
        }
        else
        {
          // pGeomFeature is a BRep Feature
          CATIMmiUseMfBRep *pMfBRep = NULL;
          rc = pGeomFeature->QueryInterface(IID_CATIMmiUseMfBRep, (void**) &pMfBRep);
          if (SUCCEEDED(rc))
          {
            rc = pMfBRep->GetBody(pBodyOfInputFeature);
            pMfBRep->Release();
            pMfBRep = NULL;
          }
        }
        if (pBodyOfInputFeature != NULL_var)
        {
          CATLONG32 MaxCellDimension = NULL;
          CATBoolean IsHomogeneous;

          pBodyOfInputFeature->GetCellsHighestDimension(MaxCellDimension , IsHomogeneous);

          if (MaxCellDimension >=1 && IsHomogeneous)
          {
            int IsConfigToStore;

			CATIMmiMechanicalFeature *piGeomFeat = NULL;
			rc = pGeomFeature->QueryInterface(IID_CATIMmiMechanicalFeature,(void **) & piGeomFeat);

            if (SUCCEEDED(rc))
            {
			  // Create CATIMmiAlgoConfigServicesServices component
			  CATIMmiAlgoConfigServices *piAlgoConfigServices = NULL;  
              rc = CATMmiExtendServicesFactory::CreateAlgoConfigServicesAccess(piAlgoConfigServices);
			  if (piAlgoConfigServices)
			  {
                rc = piAlgoConfigServices->GetConfiguration(piGeomFeat, pSoftConfig ,IsConfigToStore);
				piAlgoConfigServices->Release();
				piAlgoConfigServices = NULL;
			  }
            
              if (SUCCEEDED(rc))
              {   
                //Software Configuration Management
                CATTopData TopData;
                TopData.SetSoftwareConfiguration(pSoftConfig) ;

                //Compute of Length of Curves
                CATBody * pBodyOfFeat=NULL;  
                rc = pBodyOfInputFeature->QueryInterface(IID_CATBody, (void**) &pBodyOfFeat);
                if (SUCCEEDED(rc))
                {
                  CATICGMDynMassProperties3D *pDynMasOpe = CATCGMDynCreateMassProperties3D(&TopData, pBodyOfFeat);
                  pBodyOfFeat->Release();
                  pBodyOfFeat=NULL;

                  if (NULL != pDynMasOpe)
                  {
                    double ComputedLength = pDynMasOpe->GetLength();
                    //Storage of ComputedLength in LengthParm

                    CATICkeParm_var spValuatedParm;
                    rc = pCCDataExtension->GetValuatedParam(spValuatedParm);
                    if (FAILED(rc) || spValuatedParm == NULL_var)
                    {
                      // On the First Build of the extension, we need to create a Parameter with the computed value
                      // And aggregate it under "Length" attribute of MmrCCDataExtension.
                      CATCkeGlobalFunctions::InitializeLiteralsEnvironment();

                      CATFmContainerFacade ContFacade(CredentialForDataExt);
                      rc=FeatFacadeOnDataExt.GetContainerFacade(ContFacade);
                      if (SUCCEEDED(rc))
                      {
                        CATICkeParmFactory * pParmFact = NULL;
                        rc = ContFacade.QueryInterfaceOnContainer(IID_CATICkeParmFactory , (void**)& pParmFact);
                        if (SUCCEEDED(rc))
                        {
                          if (pParmFact != NULL)
                          {
                            pParmFact->InitStartUps();
                            spValuatedParm = pParmFact->CreateLength("ComputedLength",0); // /1000. due to units convertion
                            pParmFact->Release();
                            pParmFact=NULL;

                            //Set Out Parameter in ReadOnly Mode...To protect the buid result
                            //Its value will only be modifiable with code
                            if(!!spValuatedParm)
                            {
                              CATIParmAsStored_var spParmStored(spValuatedParm);
                              if (!!spParmStored)
                                spParmStored->ValuateStored(ComputedLength);                 
                      
                              //Now let's Aggregate pValuatedParm under "Length" attribute of MmrCCDataExtension.
                              rc = pCCDataExtension->AggregateParam(spValuatedParm);

                              spValuatedParm->SetUserAccess (CATICkeParm::ReadOnly);
                            }
                          }
                          else
                          {
                            //Raise an Error: Cannot Create Parameter
                            rc = E_FAIL;
                            ErrorDiagnosis = "Cannot Create Parameter";
                            ErrorDiagnosis.Append("\n");

                            RaiseAnError(ErrorDiagnosis, TheBaseFeatureAsFeature);
                          }
                        }
                      }
                    }
                    else
                    {
                      CATIParmAsStored_var spParmStored(spValuatedParm);
                      if(!!spParmStored)
                        spParmStored->ValuateStored(ComputedLength);                 
                    }

                    pDynMasOpe->Release();
                    pDynMasOpe = NULL;
                
                  }
                }
              }
              else
              {
                //Raise an Error: Cannot Retrieve Configuration of Base Feature
                rc = E_FAIL;
                ErrorDiagnosis = "Cannot Retrieve Configuration of Base Feature";

                RaiseAnError(ErrorDiagnosis, TheBaseFeatureAsFeature);
              }
              piGeomFeat->Release();
              piGeomFeat = NULL;
            }
          }
          else
          {
            //Raise an Error: Input Feature is not a Curve
            rc = E_FAIL;
            ErrorDiagnosis = "Input Feature is not a Curve";
            ErrorDiagnosis.Append("\n");
            ErrorDiagnosis.Append("Please select another rep");

            RaiseAnError(ErrorDiagnosis, TheBaseFeatureAsFeature);
          }
        }
        else
        {
          //Raise an Error : Cannot Retrieve the Input Feature's CATBody
          rc = E_FAIL;
          ErrorDiagnosis = "Cannot Retrieve the Input Feature's CATBody";
          ErrorDiagnosis.Append("\n");

          RaiseAnError(ErrorDiagnosis, TheBaseFeatureAsFeature);
        }

        pGeomFeature->Release();
        pGeomFeature = NULL;
      }
      else
      {
        //Raise an Error: ERROR: No Input Feature Valuated
        rc = E_FAIL;
        ErrorDiagnosis = "ERROR: No Input Feature Valuated";
        ErrorDiagnosis.Append("\n");
        RaiseAnError(ErrorDiagnosis, TheBaseFeatureAsFeature);
      }

      pCCDataExtension->Release();
      pCCDataExtension = NULL;
    }
    else
    {
      //Raise an Error
      rc = E_FAIL;

      RaiseAnError(ErrorDiagnosis, TheBaseFeatureAsFeature);
    }
  }

  CATCatch(CATError ,pError)
  {
	CATError * pErrorToThrow = NULL;

    // Create access to Update Error
    CATIMmiErrUpdate *piErrorAccess = NULL;
    rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);
    
    if (NULL != piErrorAccess)
    {
      // Builds a new update error.
      piErrorAccess->CreateNewError(pErrorToThrow);

	  // Check if error is already an update error
	  if(S_OK == piErrorAccess->IsAnUpdateError(pError))
	  {
        // Add the diagnostic coming from the update error.
        CATUnicodeString ErrorDiagnostic;
        rc = piErrorAccess->GetMmiDiagnostic(pError, ErrorDiagnostic);
        rc = piErrorAccess->SetMmiDiagnostic(pErrorToThrow, ErrorDiagnostic);		
	  }
	  else
	  {
		piErrorAccess->SetMmiDiagnostic(pErrorToThrow,pError->GetNLSMessage());
	  }

	  // Destroys the previous error.
      ::Flush(pError);

	  // Associates the error with the feature.
      if(NULL != piUpdateErrorOnThis) 
      {
        rc = piUpdateErrorOnThis->SetMmiUpdateError(pErrorToThrow);

        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
      }

	  // Associates the error with the base feature.
      if(NULL != pUpdateErrorOnBaseFeature) 
      {
        rc = pUpdateErrorOnBaseFeature->SetMmiUpdateError(pErrorToThrow);

        pUpdateErrorOnBaseFeature->Release();
        pUpdateErrorOnBaseFeature = NULL ;
      }

    }
   
    // Releases the software configuration
    if ( pSoftConfig!= NULL)
    {
      pSoftConfig->Release();
      pSoftConfig = NULL ;
    }

		CATThrow(pErrorToThrow);
  }

 
  CATEndTry

  return rc;

}            


//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CanBeRemoved(CATBoolean &) const
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::BeforeRemove()
{
  return E_NOTIMPL;
}

//
HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CcpRegisterAdditionalObjectsForCopy(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const

{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CcpUpdate(const CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}
HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CcpUpdate(CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CcpPaste(const CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}
HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CcpPaste(CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrCCDataExtensionBehavior::CcpRegisterAdditionalObjectsForRemove(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const

{
	return E_NOTIMPL; 
}

void CAAEV5V6ExtMmrCCDataExtensionBehavior::RaiseAnError(CATUnicodeString& iErrorLabel, CATBaseUnknown *iAssociatedFeature)
{ 
  CATIMmiErrUpdate *piErrorAccess = NULL;
  HRESULT rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

  if (NULL != piErrorAccess)
  {
    CATError * pError = NULL;
    piErrorAccess->CreateNewError(pError);

    CATIMmiMechanicalFeature_var hAssociatedMechanicalFeature = iAssociatedFeature;
    piErrorAccess->SetMmiAssociatedFeature(pError ,hAssociatedMechanicalFeature);
    piErrorAccess->AddMmiSickFeature(pError, hAssociatedMechanicalFeature);
    piErrorAccess->SetMmiDiagnostic(pError, iErrorLabel);

    CATThrow(pError);
  }
}
