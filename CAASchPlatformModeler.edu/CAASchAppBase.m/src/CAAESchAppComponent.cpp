/**
 * @quickreview bcy 05:01:28
 * @quickreview vso bcy 04:11:29
 */
// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//


// This framework
#include "CAASchApp.h"
#include "CAAESchAppComponent.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppBaseServices.h"
#include "CAASchAppInternalError.h"


// CATSchPlatformInterfaces
#include "CATISchRoute.h"
#include "CATISchComponent.h"
#include "CATISchAppConnectable.h"
#include "CATISchGRR.h"
#include "CATISchAppObjectFactory2.h"
#include "CATSchListServices.h"

// Product Structure
#include "CATIProduct.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATInit.h"
#include "CATIContainer.h"
#include "CATObject.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// System 
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATICStringList.h"
#include "CATErrorMacros.h"

CATImplementClass(CAAESchAppComponent,DataExtension,CATBaseUnknown,CAASCHEDUPart);

#include "TIE_CATISchAppComponent.h"
TIEchain_CATISchAppComponent(CAAESchAppComponent);

//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppComponent::CAAESchAppComponent()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppComponent::~CAAESchAppComponent()
{
}

//  ===========================================================================
//  | AppCreateComponentInst
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppCreateComponentInst (IUnknown **oNewAppCompInst)
  
{
  HRESULT RC = E_FAIL;
  *oNewAppCompInst = NULL;
  CATTry 
	{
     HRESULT rc;
     CATIProduct_var spPrdThis = (GetImpl());
     CATISpecObject_var spSpecThis (spPrdThis);
     CATUnicodeString UParam1 ("Unknown Type");
     if (NULL_var != spSpecThis) UParam1 = spSpecThis->GetType();

     //------------------------------------------------------------------------
     //  Get Application component reference
     //------------------------------------------------------------------------
     CATIProduct_var spPrdRef = spPrdThis->GetReferenceProduct();
     if (NULL_var == spPrdRef)
     {
        CAASchAppInternalError *pErr = new CAASchAppInternalError 
          (CAASchAppInternalError::Internal_CannotFindAppReference, 
          "Internal_CannotFindAppReference",               
        CAASchAppInternalErrorFile);                                 
        pErr -> SetNLSParameters (1, &UParam1);
        CATThrow(pErr);       
     }
 
     CATISpecObject_var spSpecRef (spPrdRef);
     CATDocument *pDoc = CAASchAppBaseServices::GetDocInSession();

     CATIProduct_var spPrdRoot = CAASchAppBaseServices::GetProductRootObject(pDoc);
     if (NULL_var == spPrdRoot)
     {
        CAASchAppInternalError *pErr = new CAASchAppInternalError 
          (CAASchAppInternalError::Internal_CannotFindProductRoot, 
          "Internal_CannotFindProductRoot",               
        CAASchAppInternalErrorFile);  
        CATThrow(pErr);
     }
     //------------------------------------------------------------------------
     // Create instance
     //------------------------------------------------------------------------
     if ((NULL_var != spPrdRef) && (NULL_var != spPrdRoot))
     {
        CATISpecObject_var spSpecInst = spPrdRoot->AddProduct (spPrdRef); // <- Creates the instance

        CATISpecObject *piSpecInst = NULL;
        if (NULL_var != spSpecInst)
        {
          rc = spSpecInst->QueryInterface (IID_CATISpecObject,
            (void **) &piSpecInst);
          if (SUCCEEDED(rc) && (NULL != piSpecInst))
          {
            // do not release, output to the caller
            *oNewAppCompInst = piSpecInst;
            RC = S_OK;
          }
        }
     }
     
     if (NULL == *oNewAppCompInst)
     {
        CAASchAppInternalError *pErr = new CAASchAppInternalError 
          (CAASchAppInternalError::Internal_FailToCreateCompInst, 
          "Internal_FailToCreateCompInst",               
          CAASchAppInternalErrorFile);  
        CATUnicodeString UParam1 ("Unknown Type");
        if (NULL_var != spSpecRef) UParam1 = spSpecRef->GetType();
        pErr -> SetNLSParameters (1, &UParam1);
        CATThrow(pErr); 
     }

  } // end CATTry

  CATCatch (CATError, error)
	{
     RC = E_FAIL;
     *oNewAppCompInst = NULL;
     CATRethrow;
	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppCreateLocalReference 
//  |
//  | This method should be implementated by the Schematic Platform client
//  | (the schematic application).
//  |
//  | DSA provided schematic applications such as (Piping & Instrumentation
//  | diagram, HVAC diagram..etc). In these applications, the pseudo-code of 
//  | the implementation is highlighted as follows.
//  | 1- The "this" object, is the schematic reference component
//  |    object assciated with a specific graphical representation (detail).
//  |    This graphical representation is linked to a symbol in the catalog,
//  |    which the user has selected.
//  | 2- The graphical representation and the schematic reference 
//  |    component (the "this" object) is in a document 
//  |    different from the input: iDocToCopyTo.
//  | 3- This method makes a copy of the "this" schematic 
//  |    component to the "target" document ("iDocToCopyTo") using a specific
//  |    API provided by the ObjectSpecsModeler framework. This API
//  |    creates a weak link between the source and the target schematic 
//  |    reference component.
//  |    
//  | We cannot illustrates the above pseudo-code in our CAA Sample here, 
//  | because the critical API in step 3 is not CAA exposed. 
//  |
//  | Schematic applications other then those provided by DSA might choose to
//  | implement this method differently, however they see fit. Somehow, the
//  | application has to "import" the reference component from the catalog
//  | referenced document to the "iDocToCopyTo" document,
//  | and the Schematic Platform does not need to know. 
//  |
//  | To provide a simple sample application example, this code simply calls 
//  | the factory to create a schematic reference component of the same type.
//  |   
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppCreateLocalReference (CATDocument *iDocToCopyTo,
  IUnknown **oNewAppCompRef)
{

  HRESULT RC = E_FAIL;
  if (!iDocToCopyTo || !oNewAppCompRef) return RC;
  *oNewAppCompRef = NULL;

  CATISpecObject_var spSpecThis (GetImpl());
  if (!spSpecThis) return RC;

  CATObject *pObj = NULL;
  CATISchAppObjectFactory2 *piAppObjFact = NULL;

  CATTry
  {
     pObj = new CATObject ("CAASCHEDU_SamplePID");
     if (pObj)
     {
        if (SUCCEEDED(pObj->QueryInterface (IID_CATISchAppObjectFactory2,
            (void **) &piAppObjFact)) && piAppObjFact && !!spSpecThis)
        {
           CATUnicodeString UType = spSpecThis->GetType();
           RC = piAppObjFact->AppCreateCompRef (UType.ConvertToChar(),NULL,
             oNewAppCompRef);
        }
     }
  } // end CATTry
  CATCatch (CATError, pError)
	{
     RC = CATReturnFailure;
     if (pError) Flush (pError);
	}	
  CATEndTry;
  if (FAILED(RC)) 
  {
     if (*oNewAppCompRef) 
     {
        (*oNewAppCompRef)->Release(); 
        (*oNewAppCompRef)=NULL;
     } 
  }
  if (piAppObjFact) {piAppObjFact->Release(); piAppObjFact=NULL;}
  if (pObj) {pObj->Release(); pObj=NULL;}
  return RC;
}

//  ===========================================================================
//  | AppListGRRNames
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppListGRRNames (CATICStringList **oLGRRNames)
{
  HRESULT RC = E_FAIL;
  *oLGRRNames = NULL;
  CATTry 
	{
      CATSchListServices List;
      if (SUCCEEDED (List.CreateCATICStringList (oLGRRNames)))
      {
         if (NULL != *oLGRRNames)
         {
            RC = (*oLGRRNames)->Add(0, CAASCHAPP_GRR_REP1 );
            RC = (*oLGRRNames)->Add(1, CAASCHAPP_GRR_REP2 );
            RC = (*oLGRRNames)->Add(2, CAASCHAPP_GRR_REP3 );
            RC = (*oLGRRNames)->Add(3, CAASCHAPP_GRR_REP4 );
            RC = (*oLGRRNames)->Add(4, CAASCHAPP_GRR_REP5 );
            RC = (*oLGRRNames)->Add(5, CAASCHAPP_GRR_REP6 );
            RC = (*oLGRRNames)->Add(6, CAASCHAPP_GRR_REP7 );
         }
      }

  }
  CATCatch (CATError, error)
	{
     RC = E_FAIL;
     *oLGRRNames = NULL;
	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppGetDefaultGRRNames
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppGetDefaultGRRName (char **oGRRDefaultName)
{
  HRESULT RC = E_FAIL;
  *oGRRDefaultName = NULL;
  CATTry 
	{
    char aDefaultName[] = CAASCHAPP_GRR_REP1;
    (*oGRRDefaultName) = new char[strlen(aDefaultName)+1];
    if (NULL != *oGRRDefaultName)
    {
       strcpy(*oGRRDefaultName, aDefaultName);
       RC = S_OK;
    }
  }
  CATCatch (CATError, error)
	{
     RC = E_FAIL;
     *oGRRDefaultName = NULL;
	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppListGRRNames2
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppListGRRNames2 (CATListOfCATUnicodeString &oLGRRNames)
{
  HRESULT RC = E_FAIL;
  CATTry 
  {
    oLGRRNames.Append(CAASCHAPP_GRR_REP1 );
    oLGRRNames.Append(CAASCHAPP_GRR_REP2 );
    oLGRRNames.Append(CAASCHAPP_GRR_REP3 );
    oLGRRNames.Append(CAASCHAPP_GRR_REP4 );
    oLGRRNames.Append(CAASCHAPP_GRR_REP5 );
    oLGRRNames.Append(CAASCHAPP_GRR_REP6 );
    oLGRRNames.Append(CAASCHAPP_GRR_REP7 );
    RC = S_OK;
  }
  CATCatch (CATError, error)
	{
     RC = E_FAIL;
	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppGetDefaultGRRNames2
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppGetDefaultGRRName2 (CATUnicodeString &oGRRDefaultName)
{
  HRESULT RC = E_FAIL;
  CATTry 
	{
    oGRRDefaultName = CAASCHAPP_GRR_REP1;
    RC = S_OK;
  }
  CATCatch (CATError, error)
	{
    RC = E_FAIL;
	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostPlaceProcess 
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostPlaceProcess (
  CATISchComponent *iNewCompInst, CATISchAppConnectable *iCntblConnectedTo)
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}
//  ===========================================================================
//  | AppPostSlideProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostSlideProcess (void) 
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostFlipConnectedProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostFlipConnectedProcess (void) 
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostFlipOnLineProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostFlipOnLineProcess (void) 
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostFlipHorizontalProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostFlipHorizontalProcess (void) 
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostFlipVerticalProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostFlipVerticalProcess (void) 
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}
//  ===========================================================================
//  | AppPostUninsertProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostUninsertProcess (
  CATISchRoute *iOldAppRoute1,CATISchRoute *iOldAppRoute2,
  CATISchRoute *iNewAppRoute)    
{
  HRESULT RC = S_OK;
  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostSwitchGraphicProcess
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppPostSwitchGraphicProcess (CATISchGRR *iGRR)
{
  HRESULT RC = S_OK;
  CATTry 
	 {
  }
  CATCatch (CATError, error)
	 {
 	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToPlaceInSpace
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToPlaceInSpace (boolean *oBYes)
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToSlide
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToSlide (boolean *oBYes)
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToFlipConnected
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToFlipConnected (boolean *oBYes)
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToFlipOnLine
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToFlipOnLine (boolean *oBYes)
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToFlipHorizontal
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToFlipHorizontal (boolean *oBYes)
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToFlipVertical
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToFlipVertical (boolean *oBYes)
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{

	}	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToUninsert
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToUninsert (boolean *oBYes)    
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;

  CATTry 
	 {
  }
  CATCatch (CATError, error)
	 {

	 }	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppOKToScale
//  ===========================================================================
//
HRESULT CAAESchAppComponent::AppOKToScale (boolean *oBYes)    
{
  HRESULT RC = S_OK;
  *oBYes = TRUE;
  CATTry 
	 {
  }
  CATCatch (CATError, error)
	 {

	 }	
  CATEndTry;
  return RC;
}
