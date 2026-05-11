// COPYRIGHT DASSAULT SYSTEMES 2007

// Local Framework
#include "CAAEMmrCCDataExtensionBuild.h"

#include "CATIBuild.h"

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrCCDataExtension.h"    

// MechanicalModeler Framework
#include "CATMmrAlgoConfigServices.h"  // Needed to subscribe to repository for AlgorithmConfiguration
#include "CATIGeometricalElement.h"
#include "CATIMfBRep.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"            // To query the Combined Curve feature about its inputs
#include "CATIOsmExtension.h"
#include "CATIContainer.h"

// NewTopologicalObjects Framework
#include "CATBody.h"
#include "CATTopData.h"
#include "CATSoftwareConfiguration.h"

// TopologicalOperators Framework
#include "CATDynMassProperties3D.h"
// Mathematics Framework

// Knowledge Framework
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATCkeGlobalFunctions.h"
#include "CATIParmAsStored.h"

// Error Report
#include "CATMfErrUpdate.h"              // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"             // needed to associate an error to a feature

// Include System
#include "CATBoolean.h"
#include "CATUnicodeString.h"

// Include SpecialAPI
#include "CATDataType.h"

//-------------------------------------------------------------------------
CATImplementClass ( CAAEMmrCCDataExtensionBuild,
                   DataExtension,
                   CATBaseUnknown,
                   CAAMmrCCDataExtension );

#include "TIE_CATIBuild.h" // needed to tie the implementation to its interface
TIE_CATIBuild(CAAEMmrCCDataExtensionBuild);

CAAEMmrCCDataExtensionBuild::CAAEMmrCCDataExtensionBuild()
{
}
//-------------------------------------------------------------------------
CAAEMmrCCDataExtensionBuild::~CAAEMmrCCDataExtensionBuild()
{
}
//-------------------------------------------------------------------------

HRESULT CAAEMmrCCDataExtensionBuild::Build()
{
  HRESULT rc = E_FAIL ;

  /*-----------------------------
  Build Steps:
  1 - Retrieve the GeomFeature
  2 - Verify GeomFeature is a Geometrical Element
  3 - 2 cases :
  3 - a]It's not a Geometrical Feature => Set Area Parameter as NULL and Rise Information Window
  b - b]It's a Geometrical Feature => Compute Area Value and store it in the Area Parameter
  -----------------------------*/
  CATSoftwareConfiguration        * pSoftConfig                   = NULL ;

  CAAIMmrCCDataExtension          * pCCDataExtension              = NULL ;

  CATIUpdateError                 * pUpdateErrorOnBaseFeature     = NULL ;
  CATIUpdateError                 * piUpdateErrorOnThis           = NULL ;

  CATIOsmExtension                * pExtension                    = NULL ;

  CATISpecObject                  * pBaseFeature                  = NULL ;
  CATISpecObject                  * pBase                         = NULL ;

  CATUnicodeString                ErrorDiagnosis;

  CATTry
  {           
    rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnThis);
    if ( SUCCEEDED(rc) )
    {
      piUpdateErrorOnThis->UnsetUpdateError();
    }

    // Retrieve The Base Feature and Clean its Last UpdateError
    rc = QueryInterface( IID_CATIOsmExtension, (void**) &pExtension);
    if (SUCCEEDED(rc) && pExtension != NULL)
    {
      pExtension -> QueryBaseObject( IID_CATISpecObject, (void**)& pBase);
      if(pBase != NULL)
      {
        rc = pBase -> QueryInterface( IID_CATIUpdateError , (void**) &pUpdateErrorOnBaseFeature);
        if ( SUCCEEDED(rc) && pUpdateErrorOnBaseFeature)
        {
          pUpdateErrorOnBaseFeature->UnsetUpdateError();
        }
        pBaseFeature = pBase;
        pBase -> Release();
        pBase = NULL;
      }
      pExtension -> Release();
      pExtension = NULL;
    }

    //Start Build Process
    rc = QueryInterface( IID_CAAIMmrCCDataExtension, (void**) &pCCDataExtension);
    if (SUCCEEDED(rc) && pCCDataExtension != NULL)
    {
      CATISpecObject *pGeomFeature = NULL;

      rc = pCCDataExtension -> GetGeomFeature(&pGeomFeature);
      if (SUCCEEDED(rc) && pGeomFeature != NULL)
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

          if (MaxCellDimension >=1 && IsHomogeneous)
          {
            int IsConfigToStore;

            rc = CATMmrAlgoConfigServices::GetConfiguration(pGeomFeature, pSoftConfig ,IsConfigToStore);
            if(SUCCEEDED(rc))
            { 
              //Software Configuration Management
              CATTopData TopData;
              TopData.SetSoftwareConfiguration(pSoftConfig) ;

              //Compute of Length of Curves
              CATDynMassProperties3D *pDynMasOpe = CATDynCreateMassProperties3D (&TopData, pBodyOfInputFeature); 
              if(NULL != pDynMasOpe)
              {
                double ComputedLength = pDynMasOpe -> GetLength();
                //Storage of ComputedLength in LengthParm

                CATICkeParm_var spValuatedParm;
                rc = pCCDataExtension -> GetValuatedParam(spValuatedParm);
                if(FAILED(rc) || spValuatedParm == NULL_var)
                {
                  // On the First Build of the extension, we need to create a Parameter with the computed value
                  // And aggregate it under "Length" attribute of MmrCCDataExtension.

                  CATCkeGlobalFunctions::InitializeLiteralsEnvironment();

                  CATIContainer_var Cont;
                  
                  CATISpecObject_var spSOonDataExtension = pCCDataExtension;
                  if (!!spSOonDataExtension ) 
                    Cont = spSOonDataExtension -> GetFeatContainer();

                  CATICkeParmFactory_var spParmFact = Cont;
                  if(spParmFact != NULL_var)
                  {
                    spParmFact -> InitStartUps();
                    spValuatedParm = spParmFact -> CreateLength  ("ComputedLength",0); // /1000. due to units convertion
                    
                    //Set Out Parameter in ReadOnly Mode...To protect the buid result
                    //Its value will only be modifiable with code
                    if(!!spValuatedParm)
                    {
                      CATIParmAsStored_var spParmStored(spValuatedParm);
                      if (!!spParmStored)
                        spParmStored -> ValuateStored(ComputedLength);                 
                      
                      //Now let's Aggregate pValuatedParm under "Length" attribute of MmrCCDataExtension.
                      rc = pCCDataExtension -> AggregateParam(spValuatedParm);

                      spValuatedParm -> SetUserAccess (CATICkeParm::ReadOnly);
                    }
                  }
                  else
                  {
                    //Raise an Error: Cannot Create Parameter
                    rc = E_FAIL;
                    ErrorDiagnosis = "Cannot Create Parameter";
                    ErrorDiagnosis.Append("\n");

                    RaiseAnError(ErrorDiagnosis, pBaseFeature);
                  }
                }
                else
                {
                  CATIParmAsStored_var spParmStored(spValuatedParm);
                  if(!!spParmStored)
                    spParmStored -> ValuateStored(ComputedLength);                 
                }

                delete pDynMasOpe;
                pDynMasOpe = NULL;
                
              }
            }
            else
            {
              //Raise an Error: Cannot Retrieve Configuration of Base Feature
              rc = E_FAIL;
              ErrorDiagnosis = "Cannot Retrieve Configuration of Base Feature";

              RaiseAnError(ErrorDiagnosis, pBaseFeature);
            }
          }
          else
          {
            //Raise an Error: Input Feature is not a Curve
            rc = E_FAIL;
            ErrorDiagnosis = "Input Feature is not a Curve";
            ErrorDiagnosis.Append("\n");
            ErrorDiagnosis.Append("Please select another rep");

            RaiseAnError(ErrorDiagnosis, pBaseFeature);
          }
        }
        else
        {
          //Raise an Error : Cannot Retrieve the Input Feature's CATBody
          rc = E_FAIL;
          ErrorDiagnosis = "Cannot Retrieve the Input Feature's CATBody";
          ErrorDiagnosis.Append("\n");

          RaiseAnError(ErrorDiagnosis, pBaseFeature);
        }

        pGeomFeature -> Release();
        pGeomFeature = NULL;
      }
      else
      {
        //Raise an Error: ERROR: No Input Feature Valuated
        rc = E_FAIL;
        ErrorDiagnosis = "ERROR: No Input Feature Valuated";
        ErrorDiagnosis.Append("\n");

        RaiseAnError(ErrorDiagnosis, pBaseFeature);
      }

      pCCDataExtension -> Release();
      pCCDataExtension = NULL;
    }
    else
    {
      //Raise an Error
      rc = E_FAIL;

      RaiseAnError(ErrorDiagnosis, pBaseFeature);
    }
  }

  CATCatch( CATMfErrUpdate , pUpdateError)
  {
    //------------------------------------------------------------------
    // Catches CATMfErrUpdate errors
    //------------------------------------------------------------------

    // Builds a new update error.
    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    // Add it the diagnostic coming from the error previously caugth.
    pErrorToThrow->SetDiagnostic(pUpdateError->GetDiagnostic());
    // Destroys the previous error.
    ::Flush(pUpdateError);
    // Associates the error with the UserPad.

    if(NULL != piUpdateErrorOnThis) 
    {
      piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);

      piUpdateErrorOnThis->Release();
      piUpdateErrorOnThis = NULL ;
    }

    if(NULL != pUpdateErrorOnBaseFeature) 
    {
      pUpdateErrorOnBaseFeature->SetUpdateError(pErrorToThrow);

      pUpdateErrorOnBaseFeature->Release();
      pUpdateErrorOnBaseFeature = NULL ;
    }

    // Releases the software configuration
    if ( pSoftConfig!= NULL)
    {
      pSoftConfig->Release();
      pSoftConfig = NULL ;
    }
    CATThrow(pErrorToThrow);
  }

  CATCatch ( CATError , pError) 
  {
    //-------------------------------------------------------------------
    // Catches other CATError errors
    //-------------------------------------------------------------------

    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    pErrorToThrow->SetDiagnostic(pError->GetNLSMessage());

    ::Flush(pError);

    if(NULL != piUpdateErrorOnThis) 
    {
      piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);

      piUpdateErrorOnThis->Release();
      piUpdateErrorOnThis = NULL ;
    }

    if(NULL != pUpdateErrorOnBaseFeature) 
    {
      pUpdateErrorOnBaseFeature->SetUpdateError(pErrorToThrow);

      pUpdateErrorOnBaseFeature->Release();
      pUpdateErrorOnBaseFeature = NULL ;
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

void CAAEMmrCCDataExtensionBuild::RaiseAnError(CATUnicodeString& iErrorLabel, CATISpecObject *iAssociatedFeature)
{    
  CATMfErrUpdate *pError = new CATMfErrUpdate();

  pError -> SetAssociatedFeature(iAssociatedFeature);
  pError -> AddSickFeature(iAssociatedFeature);
  pError -> SetDiagnostic(iErrorLabel);

  CATThrow(pError);
}
