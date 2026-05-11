//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//=======================================================================
//
// Class  CAAEMmrMultiMeasureBuild:
// Implements CATIBuild for MmrMultiMeasure
//
//========================================================================
// CATIBuild Implementation 
//========================================================================

// Local Framework
#include "CAAIMmrMultiMeasure.h"
#include "CAAEMmrMultiMeasureBuild.h"

// MechanicalModeler Framework
#include "CATMmrAlgoConfigServices.h"  // Needed to subscribe to repository for AlgorithmConfiguration
#include "CATIGeometricalElement.h"
#include "CATIMfBRep.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"            // To query the Combined Curve feature about its inputs
#include "CATLISTV_CATISpecObject.h"

// NewTopologicalObjects Framework
#include "CATBody.h"
#include "CATTopData.h"
#include "CATSoftwareConfiguration.h"

// TopologicalOperators Framework
#include "CATDynMassProperties3D.h"

// Knowledge Framework
#include "CATICkeParm.h"
#include "CATIParmAsStored.h"

// Error Report
#include "CATMfErrUpdate.h"              // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"             // needed to associate an error to a feature

// Raise of VisuEvent
#include "CATIModelEvents.h"
#include "CATNotification.h"
#include "CATModify.h"

// Include System
#include "CATBoolean.h"
#include "CATUnicodeString.h"

// Include SpecialAPI
#include "CATDataType.h"

#include "iostream.h"

// Implementation BOA
CATImplementBOA(CATIBuild, CAAEMmrMultiMeasureBuild);

// Implementation de la Classe CATMmrEulerAngleBuild
CATBeginImplementClass(CAAEMmrMultiMeasureBuild,DataExtension,CATIBuild,CAAMmrMultiMeasure);
CATEndImplementClass(CAAEMmrMultiMeasureBuild);

// Don't forget this line in Dictionary:
// CAAMmrMultiMeasure   CATIBuild  libCAAMmrMultiMeasureAndMeasureSet

//////////////////////////////
// Constructor - Destructor //
//////////////////////////////
CAAEMmrMultiMeasureBuild::CAAEMmrMultiMeasureBuild()
{
}
CAAEMmrMultiMeasureBuild::~CAAEMmrMultiMeasureBuild()
{
}

////////////////////////////
// Methods Implementation //
////////////////////////////
HRESULT CAAEMmrMultiMeasureBuild::Build()
{
  //========================================================================================
  // The build method takes place as follows :
  //
  // CATTry
  //   o -1- Clean last update error
  //   o -3- Compute measures
  //   o -4- Clean useless data
  // CATCatch
  //     o -4-1 Managing CATMfErrUpdate Error
  //     o -4-2 Managing other Error's types
  //========================================================================================
  cout <<" CAAEMmrMultiMeasureBuild::Build() " << endl; 
  cout << endl;

  HRESULT rc = E_FAIL;

  //========================================================================================
  // - [-1] - Declaring Useful Handler
  //========================================================================================

  CAAIMmrMultiMeasure             * pMmrMultiMeasure			        = NULL;

  CATISpecObject_var              hSOOnMmrMultiMeasure            = this;      

  CATSoftwareConfiguration        * pSoftConfig                   = NULL;
  CATIUpdateError                 * piUpdateErrorOnThis           = NULL;
  
  CATICkeParm_var                 spLengthParm                    ;
  CATICkeParm_var                 spAreaParm                      ;
  CATICkeParm_var                 spVolumeParm                    ;
  
  CATUnicodeString                ErrorDiagnosis;


  CATTry
  {	

    if(hSOOnMmrMultiMeasure == NULL_var)
      return E_FAIL;

    //========================================================================================
    // -1- Cleaning last update error
    //========================================================================================

    rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnThis);
    if ( SUCCEEDED(rc) )
    {
      piUpdateErrorOnThis->UnsetUpdateError();
    }
    //========================================================================================
    // -2- Retrieves "OutPut" parameters
    //======================================================================================== 
    CAAIMmrMultiMeasure * pMmrMultiMeasure = NULL;
    HRESULT rc = QueryInterface(IID_CAAIMmrMultiMeasure, (void**) & pMmrMultiMeasure);
    if (SUCCEEDED(rc) && pMmrMultiMeasure != NULL)
      {
	  pMmrMultiMeasure->GetLengthParameter(spLengthParm); 
	  pMmrMultiMeasure->GetWetAreaParameter(spAreaParm);
	  pMmrMultiMeasure->GetVolumeParameter(spVolumeParm);
    }

    if(FAILED(rc) || !spLengthParm ||!spAreaParm||!spVolumeParm)
    {
      //Raise an Error: Input Feature is not a Curve
      rc = E_FAIL;
      ErrorDiagnosis = "INTERNAL ERROR - Cannot Retrieve Output Parameter";
      
      RaiseAnError(ErrorDiagnosis, hSOOnMmrMultiMeasure);
    }
    
    //========================================================================================
    // -2- Compute Measure
    //========================================================================================
    rc = QueryInterface( IID_CAAIMmrMultiMeasure, (void**) &pMmrMultiMeasure);
    if(SUCCEEDED(rc) && pMmrMultiMeasure != NULL)
    {
      CATISpecObject* pGeomFeature = NULL;
      rc = pMmrMultiMeasure -> GetGeomFeature (&pGeomFeature);

      if(SUCCEEDED(rc) && pGeomFeature!= NULL)
      {
        CATBody *pBodyOfInputFeature = NULL;

        CATIGeometricalElement *pGeometricalElementOnInputFeature = NULL;
        rc = pGeomFeature -> QueryInterface(IID_CATIGeometricalElement, (void**) &pGeometricalElementOnInputFeature);
        if(SUCCEEDED(rc) && pGeometricalElementOnInputFeature != NULL)
        {
          pBodyOfInputFeature = pGeometricalElementOnInputFeature -> GetBodyResult();

          pGeometricalElementOnInputFeature -> Release();
          pGeometricalElementOnInputFeature = NULL;
        }
        else
        {
          // pGeomFeature is a BRep Feature
          CATIMfBRep *pMfBRep = NULL;
          rc = pGeomFeature -> QueryInterface(IID_CATIMfBRep, (void**) &pMfBRep);
          if ( SUCCEEDED(rc) && pMfBRep != NULL)
          {
            pBodyOfInputFeature = pMfBRep -> CreateBody(MfWithTemporaryBody);

            pMfBRep -> Release();
            pMfBRep = NULL;
          }
        }

        if (pBodyOfInputFeature != NULL)
        {
          CATLONG32 MaxCellDimension = NULL;
          CATBoolean IsHomogeneous;

          pBodyOfInputFeature -> GetCellsHighestDimension(MaxCellDimension , IsHomogeneous);

          if (MaxCellDimension >= 1 && IsHomogeneous)
          {
            int IsConfigToStore;

            rc = CATMmrAlgoConfigServices::GetConfiguration(pGeomFeature, pSoftConfig ,IsConfigToStore);
            if(FAILED(rc))
            {
              pSoftConfig = new CATSoftwareConfiguration();
              rc = S_OK;
            }
            if(SUCCEEDED(rc))
            { 
              //Software Configuration Management
              CATTopData TopData;
              TopData.SetSoftwareConfiguration(pSoftConfig) ;

              //Compute of Length, Area and Volume of Input feature
              CATDynMassProperties3D *pDynMasOpe = CATDynCreateMassProperties3D (&TopData, pBodyOfInputFeature); 
              if(NULL != pDynMasOpe)
              {
                if (MaxCellDimension == 1)
                {
                  double ComputedLength = pDynMasOpe -> GetLength();
                   //Storage of ComputedLength in LengthParm
                  if(!!spLengthParm && !!spAreaParm && !!spVolumeParm )
                  {
                    CATIParmAsStored_var spParmStored(spLengthParm);
                    if(!!spParmStored)
                      spParmStored -> ValuateStored(ComputedLength);

                    spAreaParm   -> Valuate (0.);
                    spVolumeParm -> Valuate (0.);
                  }
                }
                else
                {
                  double ComputedWetArea = pDynMasOpe -> GetWetArea();
                  double ComputedVolume = pDynMasOpe -> GetVolume();
                   
                  if(!!spLengthParm && !!spAreaParm && !!spVolumeParm )
                  {
                    spAreaParm -> Valuate(ComputedWetArea / 1000000.); // /1000000 due to MKS Unit conversion
                    spVolumeParm -> Valuate(ComputedVolume / 1000000000.); //  / 1000000000 due to MKS Unit conversion                  
                    spLengthParm -> Valuate (0.);
                  }
                }
                delete pDynMasOpe;
                pDynMasOpe = NULL;
              }
              //Send an Event for Visu Notification
              CATIModelEvents_var hModelEventOnThis = this;
              CATModify BuiltInfo(this);

              hModelEventOnThis -> Dispatch(BuiltInfo);            
            }
            else
            {
              //Raise an Error: Cannot Retrieve Configuration
              rc = E_FAIL;
              ErrorDiagnosis = "Cannot Retrieve Configuration";

              RaiseAnError(ErrorDiagnosis, hSOOnMmrMultiMeasure);
            }
          }
          else
          {
            //Raise an Error: Input Feature is not a Curve
            rc = E_FAIL;
            ErrorDiagnosis = "Input Feature is not a good geometrical feature - Please Choose another input";

            RaiseAnError(ErrorDiagnosis, hSOOnMmrMultiMeasure );
          }
        }
        else
        {
          //Raise an Error : Cannot Retrieve the Input Feature's CATBody
          rc = E_FAIL;
          ErrorDiagnosis = "Cannot Retrieve the Input Feature's CATBody - Please Choose another input";

          RaiseAnError(ErrorDiagnosis, hSOOnMmrMultiMeasure);
        }
        pGeomFeature -> Release();
        pGeomFeature = NULL;
      }
      else
      {
        //Raise an Error: ERROR: No Input Feature Valuated
        rc = E_FAIL;
        ErrorDiagnosis = "ERROR: No Input Feature Valuated";

        RaiseAnError(ErrorDiagnosis, hSOOnMmrMultiMeasure);
      }

      pMmrMultiMeasure -> Release();
      pMmrMultiMeasure = NULL;
    }
    else
    {
      rc = E_FAIL;
    }
  }

  CATCatch( CATMfErrUpdate , pUpdateError)
  {
    //------------------------------------------------------------------
    // Catches CATMfErrUpdate errors
    //------------------------------------------------------------------
    if(NULL != piUpdateErrorOnThis) 
    {
      piUpdateErrorOnThis->SetUpdateError(pUpdateError);
      piUpdateErrorOnThis->Release();
      piUpdateErrorOnThis = NULL ;
    }

    // Releases the software configuration
    if ( pSoftConfig!= NULL)
    {
      pSoftConfig->Release();
      pSoftConfig = NULL ;
    }
    CATRethrow;
  }

  CATCatch ( CATError , pError) 
  {
    //-------------------------------------------------------------------
    // Catches other CATError errors
    //-------------------------------------------------------------------

    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    pErrorToThrow-> SetDiagnostic(1, pError->GetNLSMessage());

    if(NULL != piUpdateErrorOnThis) 
    {
      piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);

      piUpdateErrorOnThis->Release();
      piUpdateErrorOnThis = NULL ;
    }

    // Releases the software configuration
    if ( pSoftConfig!= NULL)
    {
      pSoftConfig->Release();
      pSoftConfig = NULL ;
    }

    ::Flush(pError);
    
    CATThrow(pErrorToThrow);
  }  

  CATEndTry
    return rc;
}

void CAAEMmrMultiMeasureBuild::RaiseAnError(const CATUnicodeString& iErrorLabel, CATISpecObject_var &iAssociatedFeature)
{    
  CATMfErrUpdate *pError = new CATMfErrUpdate();
  CATUnicodeString Diagnostic(iErrorLabel);
  
  pError -> SetDiagnostic(Diagnostic);

  CATThrow(pError);
}

