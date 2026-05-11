// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//

// This framework
#include "CAAESchAppRoute.h"
#include "CAASchAppBaseServices.h"
#include "CAASchAppInternalError.h"

// CATSchPlatformInterfaces
#include "CATISchRoute.h"

// ObjectBaseModeler
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATInit.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// System
#include "CAASchAppErrors.h"

CATImplementClass(CAAESchAppRoute,DataExtension,CATBaseUnknown,CAASCHEDUString);

#include "TIE_CATISchAppRoute.h"
TIEchain_CATISchAppRoute(CAAESchAppRoute);         


//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppRoute::CAAESchAppRoute()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppRoute::~CAAESchAppRoute()
{
}

//  ===========================================================================
//  | CreateLocalReference
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppCreateLocalReference (
  CATDocument *iDocToCopyTo, 
  CATISchAppRoute **oSchAppRoute)
{
  HRESULT RC = E_FAIL;
  *oSchAppRoute = NULL;
  return RC;
}

//  ===========================================================================
//  | Break
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppBreak (IUnknown **oNewAppRoute) 
{
  HRESULT RC = E_FAIL;
  *oNewAppRoute = NULL;

  CATTry 
	 {
    // Create a new instance route from this route's reference product and
    // add the new instance route to the same father product.
    CATIProduct *piProduct = NULL;
    if ( SUCCEEDED(QueryInterface(IID_CATIProduct,(void**)&piProduct)) && (NULL != piProduct) )
    {
      CATIProduct_var spRefPrd = piProduct->GetReferenceProduct();
      CATIProduct_var spFatherPrd = piProduct->GetFatherProduct();
      if ( (NULL_var != spRefPrd) && (NULL_var != spFatherPrd) )
      {
        CATIProduct_var spInstPrd = spFatherPrd->AddProduct(spRefPrd);
        if ( NULL_var != spInstPrd )
        {
          RC = spInstPrd->QueryInterface(IID_IUnknown,(void**)oNewAppRoute);
          // CopyDataFrom to copy all attributes from this route
        }
      }
      piProduct->Release(); piProduct = NULL;
    }
  }

  CATCatch (CATError, error)
	 {
    RC = E_FAIL;
	   CATRethrow;
	 }	
  CATEndTry;
  return RC;
}

//  ===========================================================================
//  | AppPostBreakProcess
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppPostBreakProcess (CATISchRoute *iOldAppRoute, 
    CATISchRoute *iNewAppRoute)
{
  HRESULT rc = S_OK;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{
    rc = E_FAIL;
    CATRethrow;
	}	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppPostConcatenateProcess
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppPostConcatenateProcess (CATISchRoute *iNewAppRoute)
{
  HRESULT rc = S_OK;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{
    rc = E_FAIL;
    CATRethrow;
	}	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppOKToModifyPoints
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppOKToModifyPoints (boolean *oBYes)
{
  HRESULT rc = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{
    rc = E_FAIL;
    CATRethrow;
	}	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppOKToBreak
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppOKToBreak (boolean *oBYes)
{
  HRESULT rc = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{
    rc = E_FAIL;
    CATRethrow;
	}	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppOKToConcatenate
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppOKToConcatenate (boolean *oBYes)
{
  HRESULT rc = S_OK;
  *oBYes = TRUE;

  CATTry 
	{
  }
  CATCatch (CATError, error)
	{
    rc = E_FAIL;
    CATRethrow;
	}	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppOKToBranch
//  ===========================================================================
//
HRESULT CAAESchAppRoute::AppOKToBranch (const char* iBranchClassType, boolean *oBYes)
{
  HRESULT rc = S_OK;
  *oBYes = TRUE;

  CATTry 
	 {
  }

  CATCatch (CATError, error)
	 {
    rc = E_FAIL;
    CATRethrow;
	 }	
  CATEndTry;
  return rc;
}
