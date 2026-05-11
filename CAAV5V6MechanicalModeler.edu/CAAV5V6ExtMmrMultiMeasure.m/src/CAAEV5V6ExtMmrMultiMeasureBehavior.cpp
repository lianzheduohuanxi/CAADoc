// COPYRIGHT DASSAULT SYSTEMES 2012
//=========================================================================================
//
//  CAAEV5V6ExtMmrMultiMeasureBehavior
//    Implementation of interface CATIFmFeatureBehaviorCustomization for CAAMmrMultiMeasure 
//
// Note : CAAEV5V6ExtMmrMultiMeasure is the same use case as CAAEMmrMultiMeasure. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//=========================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6ExtMechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrMultiMeasureBehavior.h"
#include "CAAIV5V6ExtMmrMultiMeasure.h"

// FeatureModelerExt Framework
#include "CATIFmFeatureBehaviorCustomization.h" 

// CATMecModUseItf Framework
#include "CATIMmiUseGeometricalElement.h" // Needed for GetBodyResult
#include "CATIMmiUseMfBRep.h"             

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// CATMecModExtendItf Framework
#include "CATIMmiAlgoConfigServices.h"
#include "CATMmiExtendServicesFactory.h"
#include "CATIMmiErrUpdate.h"
#include "CATIMmiUpdateError.h"

// GMOperatorsInterfaces Framework 
#include "CATICGMDynMassProperties3D.h"

// GMModelInterfaces Framework
#include "CATBody.h"
#include "CATTopData.h"

// CATMathStream Framework
#include "CATSoftwareConfiguration.h"     // Needed to create topological data

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"
#include "CATIParmAsStored.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"

// SpecialAPI Framework
#include "CATDataType.h"
#include "CATError.h"
#include "CATErrorMacros.h"

// VisualizationInterfaces Framework for V6
// Visualization Framework for V6
#include "CATIModelEvents.h"
#include "CATModify.h"

// C++ Standard library
#include "iostream.h"


CATImplementClass(CAAEV5V6ExtMmrMultiMeasureBehavior, DataExtension, CATIFmFeatureBehaviorCustomization, CAAV5V6ExtMmrMultiMeasure);
CATImplementBOA(CATIFmFeatureBehaviorCustomization,CAAEV5V6ExtMmrMultiMeasureBehavior);


// To declare that CAAMmrMultiMeasure implements CATIFmFeatureBehaviorCustomization, insert 
// the following line in the interface dictionary:
//
// CAAV5V6ExtMmrMultiMeasure  CATIFmFeatureBehaviorCustomization  libCAAV5V6ExtMmrMultiMeasure

//-------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureBehavior : constructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureBehavior::CAAEV5V6ExtMmrMultiMeasureBehavior():
    CATIFmFeatureBehaviorCustomization()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureBehavior : destructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureBehavior::~CAAEV5V6ExtMmrMultiMeasureBehavior()
{}

//-----------------------------------------------------------------------------
// Update MultiMeasure
// This is called whenever one of the combined curve attributes is modified  
//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::Build()
{
  //========================================================================================
  // The build method takes place as follows :
  //
  // CATTry
  //   o -1- Clean last update error
  //   o -3- Compute measures
  //   o -4- Clean useless data
  // CATCatch
  //     o -4-1 Managing Update Error
  //     o -4-2 Managing other Error's types
  //========================================================================================
  cout <<" CAAEV5V6ExtMmrMultiMeasureBehavior::Build() " << endl; 
  cout << endl;

  HRESULT rc = E_FAIL;

  //========================================================================================
  // - [-1] - Declaring Useful Handler
  //========================================================================================

  CATSoftwareConfiguration *pSoftConfig = NULL;
  CATIMmiUpdateError *piUpdateErrorOnThis = NULL;
  CATUnicodeString ErrorDiagnosis;
  CATICkeParm_var spLengthParm;
  CATICkeParm_var spAreaParm;
  CATICkeParm_var spVolumeParm;
  CAAIV5V6ExtMmrMultiMeasure_var spMmrMultiMeasure;

  CATTry
  {	
    // Clean last update error
    rc = QueryInterface(IID_CATIMmiUpdateError , (void**) &piUpdateErrorOnThis);
    if (SUCCEEDED(rc))
      piUpdateErrorOnThis->UnsetMmiUpdateError();
   
    // Retrieve the MultiMeasure parameters
    spMmrMultiMeasure = this;
	if (spMmrMultiMeasure != NULL_var)
	{
	  rc = spMmrMultiMeasure->GetLengthParameter(spLengthParm); 
	  if (SUCCEEDED(rc))
	  {
	    rc = spMmrMultiMeasure->GetWetAreaParameter(spAreaParm);
	    if (SUCCEEDED(rc))
	      spMmrMultiMeasure->GetVolumeParameter(spVolumeParm);
	  }
    }

    if (FAILED(rc) || !spLengthParm ||!spAreaParm ||!spVolumeParm)
    {
      //Raise an Error
      rc = E_FAIL;
      ErrorDiagnosis = "INTERNAL ERROR - Cannot Retrieve Output Parameter";
      
      RaiseAnError(ErrorDiagnosis, spMmrMultiMeasure);
    }
    

    // Compute Measure
    if (SUCCEEDED(rc) && spMmrMultiMeasure != NULL_var)
    {
      CATBaseUnknown* pGeomFeature = NULL;
      rc = spMmrMultiMeasure->GetGeomFeature(pGeomFeature);

      if (SUCCEEDED(rc) && pGeomFeature)
      {
        CATBody_var spBodyOfInputFeature = NULL_var;

        CATIMmiUseGeometricalElement_var spGeometricalElementOnInputFeature = pGeomFeature;
        if (spGeometricalElementOnInputFeature != NULL_var)
          rc = spGeometricalElementOnInputFeature->GetBodyResult(spBodyOfInputFeature);
        else
        {
          // pGeomFeature is a BRep Feature
          CATIMmiUseMfBRep_var spMfBRep = pGeomFeature;
          if (spMfBRep != NULL_var)
            rc = spMfBRep->GetBody(spBodyOfInputFeature);
        }

        if (spBodyOfInputFeature != NULL_var)
        {
          CATLONG32 MaxCellDimension = NULL;
          CATBoolean IsHomogeneous;

          spBodyOfInputFeature->GetCellsHighestDimension(MaxCellDimension , IsHomogeneous);

          if (MaxCellDimension >= 1 && IsHomogeneous)
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

              if (FAILED(rc))
              {
                pSoftConfig = new CATSoftwareConfiguration();
                rc = S_OK;
			  }

              if (SUCCEEDED(rc))
              { 
                //Software Configuration Management
                CATTopData TopData;
                TopData.SetSoftwareConfiguration(pSoftConfig) ;

                //Compute of Length, Area and Volume of Input feature
                CATICGMDynMassProperties3D *pDynMasOpe = CATCGMDynCreateMassProperties3D(&TopData, spBodyOfInputFeature); 
                if (NULL != pDynMasOpe)
                {
                  if (MaxCellDimension == 1)
                  {
                    double ComputedLength = pDynMasOpe->GetLength();
                    //Storage of ComputedLength in LengthParm
                    if (!!spLengthParm && !!spAreaParm && !!spVolumeParm )
                    {
                      CATIParmAsStored_var spParmStored(spLengthParm);
                      if (!!spParmStored)
                        spParmStored->ValuateStored(ComputedLength);

                      spAreaParm->Valuate(0.);
                      spVolumeParm->Valuate(0.);
                    }
                  }
                  else
                  {
                    double ComputedWetArea = pDynMasOpe->GetWetArea();
                    double ComputedVolume = pDynMasOpe->GetVolume();
                   
                    if (!!spLengthParm && !!spAreaParm && !!spVolumeParm )
                    {
                      spAreaParm->Valuate(ComputedWetArea / 1000000.); // /1000000 due to MKS Unit conversion
                      spVolumeParm->Valuate(ComputedVolume / 1000000000.); //  / 1000000000 due to MKS Unit conversion                  
                      spLengthParm->Valuate (0.);
                    }
                  }
                  pDynMasOpe->Release();
                  pDynMasOpe = NULL;
                }

                //Send an Event for Visu Notification
                CATIModelEvents_var hModelEventOnThis = this;
                CATModify BuiltInfo(this);
                hModelEventOnThis->Dispatch(BuiltInfo);            
              }
              else
              {
                //Raise an Error: Cannot Retrieve Configuration
                rc = E_FAIL;
                ErrorDiagnosis = "Cannot Retrieve Configuration";

                RaiseAnError(ErrorDiagnosis, spMmrMultiMeasure);
              }
			  piGeomFeat->Release();
              piGeomFeat = NULL;
		   }
					}
          else
          {
            //Raise an Error: Input Feature is not a Curve
            rc = E_FAIL;
            ErrorDiagnosis = "Input Feature is not a good geometrical feature - Please Choose another input";

            RaiseAnError(ErrorDiagnosis, spMmrMultiMeasure);
          }
        }
        else
        {
          //Raise an Error : Cannot Retrieve the Input Feature's CATBody
          rc = E_FAIL;
          ErrorDiagnosis = "Cannot Retrieve the Input Feature's CATBody - Please Choose another input";

          RaiseAnError(ErrorDiagnosis, spMmrMultiMeasure);
        }
        pGeomFeature->Release();
        pGeomFeature = NULL;
      }
      else
      {
        //Raise an Error: ERROR: No Input Feature Valuated
        rc = E_FAIL;
        ErrorDiagnosis = "ERROR: No Input Feature Valuated";

        RaiseAnError(ErrorDiagnosis, spMmrMultiMeasure);
      }
    }
    else
    {
      rc = E_FAIL;
    }
  }
  
  // Releases the software configuration
  if ( pSoftConfig!= NULL)
  {
    pSoftConfig->Release();
    pSoftConfig = NULL ;
  }

  CATCatch( CATError , pError)
  {
    CATError * pErrorToThrow = NULL;

    // Create access to Update Error
    CATIMmiErrUpdate *piErrorAccess = NULL;
    rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

    if (NULL != piErrorAccess)
    {
	  // Check if the error is already an update error or not
	  if (S_OK == piErrorAccess->IsAnUpdateError(pError))
	  {
		// Associates the error with the MultiMeasure
		if (NULL != piUpdateErrorOnThis)
		{
		  piUpdateErrorOnThis->SetMmiUpdateError(pError);
      
		  piUpdateErrorOnThis->Release();
		  piUpdateErrorOnThis = NULL ;
		}
	  }
	  else
	  {
        // Builds a new update error.
        piErrorAccess->CreateNewError(pErrorToThrow);
		piErrorAccess->SetMmiDiagnostic(pErrorToThrow,pError->GetNLSMessage());

		// Clean-up
		::Flush(pError);

        // Associates the error with the MultiMeasure
		if (NULL != piUpdateErrorOnThis)
		{
		  piUpdateErrorOnThis->SetMmiUpdateError(pErrorToThrow);
      
		  piUpdateErrorOnThis->Release();
		  piUpdateErrorOnThis = NULL ;
		}
	  }
    }

    // Releases the software configuration
    if ( pSoftConfig!= NULL)
    {
      pSoftConfig->Release();
      pSoftConfig = NULL ;
    }
		
    spLengthParm = NULL_var;
    spAreaParm = NULL_var;
    spVolumeParm = NULL_var;
	spMmrMultiMeasure = NULL_var;

	if (pErrorToThrow)
      CATThrow(pErrorToThrow);
	else
	 CATRethrow;

  }

  CATEndTry

  return rc;

}            


//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CanBeRemoved(CATBoolean &) const
{
	return E_NOTIMPL;
}


HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::BeforeRemove()
{
  return E_NOTIMPL;
}

//
HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CcpRegisterAdditionalObjectsForCopy(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const

{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CcpUpdate(const CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}
HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CcpUpdate(CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CcpPaste(const CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}
HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CcpPaste(CATFmCCPContext & iContext)
{
	return E_NOTIMPL;
}

HRESULT CAAEV5V6ExtMmrMultiMeasureBehavior::CcpRegisterAdditionalObjectsForRemove(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const

{
	return E_NOTIMPL; 
}

void CAAEV5V6ExtMmrMultiMeasureBehavior::RaiseAnError(CATUnicodeString& iErrorLabel, CATBaseUnknown_var &iAssociatedFeature)
{ 
  CATIMmiErrUpdate *piErrorAccess = NULL;
  HRESULT rc = CATMmiExtendServicesFactory::CreateUpdateErrorAccess(piErrorAccess);

  if (NULL != piErrorAccess)
  {
    CATError * pError = NULL;
    piErrorAccess->CreateNewError(pError);

    CATUnicodeString Diagnostic(iErrorLabel);
    piErrorAccess->SetMmiDiagnostic(pError,Diagnostic);

		piErrorAccess->Release();
    piErrorAccess = NULL;

    CATThrow(pError);
  }  
}

