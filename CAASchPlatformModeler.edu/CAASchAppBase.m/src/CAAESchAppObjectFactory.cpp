// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================

// This framework
#include "CAAESchAppObjectFactory.h"
#include "CAASchAppBaseServices.h"

// CATSchPlatformInterfaces
#include "CATISchAppRoute.h"
#include "CATISchComponent.h"
#include "CATISchRoute.h"

// ObjectModelerBase
#include "CATDocument.h"

// Product Structure
#include "CATIProduct.h"

// System
#include "CATBoolean.h"
#include "CATError.h"
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

CATImplementClass(CAAESchAppObjectFactory,DataExtension,CATBaseUnknown,CAASCHEDU_SamplePID);
#include "TIE_CATISchAppObjectFactory2.h"
TIEchain_CATISchAppObjectFactory2(CAAESchAppObjectFactory);         


//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppObjectFactory::CAAESchAppObjectFactory()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppObjectFactory::~CAAESchAppObjectFactory()
{
}

//  ===========================================================================
//  | Create application component reference
//  | Application provides the implementation code to create a reference 
//  | component. This is independent and transparent to the Schematic Platform.
//  | The latter has no knowledge of how this is done. 
//  | 
//  | To illustrate the concept, this sample application simply searches for
//  | an object of the same requested class type in the input document.
//  | The input document is a specific document that contains only 
//  | one matching object.
//  ===========================================================================
//
HRESULT CAAESchAppObjectFactory::AppCreateCompRef (
  const char *iAppCompClassType, const CATDocument *iDoc, IUnknown **oAppComp)
{
  HRESULT RC = CATReturnFailure;
  if (!oAppComp || !iAppCompClassType) return RC;
  *oAppComp = NULL;

  CATISchComponent *piSchComp = NULL;

  CATISpecObject_var spSpecRef;
  CATIContainer_var spAppCont;
  CATIProduct_var spPrdRef;
  CATTry 
	{
     CATDocument *pDoc = NULL;
     if ( iDoc )
     {
       pDoc = (CATDocument*) iDoc;
     }
     else 
     {
       pDoc = CAASchAppBaseServices::GetDocInSession();
     }
     if (pDoc) spAppCont = CAASchAppBaseServices::GetAppObjContainer(pDoc);
     if (!!spAppCont)
     {
        spSpecRef = CAASchAppBaseServices::FindAppObjByClass (
                    iAppCompClassType,spAppCont);
        if (!!spSpecRef)
        {
           // make sure this object has not been associated with any 
           // schematic component extension.
           //if (FAILED(spSpecRef->QueryInterface (IID_CATISchComponent,
               //(void **) &piSchComp)))
           //{
              // make sure this is a reference product
              spPrdRef = spSpecRef;
              if (!!spPrdRef) 
              {
                 if (SUCCEEDED(spPrdRef->IsReference()))
                 {
                    RC = spSpecRef->QueryInterface (IID_IUnknown,
                         (void **) oAppComp);
                 }
              }
           //} // if (FAILED(spSpecRef->QueryInterface (IID_CATISchComponent,
        } // if (!!spSpecRef)
     } // if (!!spAppCont)
  }
  CATCatch (CATError, pError)
	{
     if (pError) Flush(pError);
     RC = CATReturnFailure;
	}	
  CATEndTry;
  if (FAILED(RC)) {if (*oAppComp) {(*oAppComp)->Release(); (*oAppComp)=NULL;}}
  if (piSchComp) {piSchComp->Release(); piSchComp=NULL;}
  return RC;
}

//  ===========================================================================
//  | Create application route instance (from existing application reference)
//  | Application provides the implementation code to create a reference 
//  | route. This is independent and transparent to the Schematic Platform.
//  | The latter has no knowledge of how this is done. 
//  | 
//  | To illustrate the concept, this sample application simply searches for
//  | an object of the same requested class type in the input document.
//  | The input document is a specific document that contains only 
//  | one matching object.
//  ===========================================================================
HRESULT CAAESchAppObjectFactory::AppCreateRoute2 (const char *iAppRouteClassType,
  const CATDocument *iDoc, const CATUnicodeString *iLogLineID, IUnknown **oAppRoute)
{
  HRESULT RC = CATReturnFailure;
  if (!oAppRoute || !iAppRouteClassType) return RC;
  *oAppRoute = NULL;

  CATISchRoute *piSchRoute = NULL;

  CATISpecObject_var spSpecRef;
  CATIContainer_var spAppCont;
  CATIProduct_var spPrdRef;
  CATTry 
	{
     CATDocument *pDoc = NULL;
     if ( iDoc )
     {
       pDoc = (CATDocument*) iDoc;
     }
     else 
     {
       pDoc = CAASchAppBaseServices::GetDocInSession();
     }
     if (pDoc) spAppCont = CAASchAppBaseServices::GetAppObjContainer(pDoc);
     if (!!spAppCont)
     {
        spSpecRef = CAASchAppBaseServices::FindAppObjByClass (
                    iAppRouteClassType,spAppCont);
        if (!!spSpecRef)
        {
           // make sure this object has not been associated with any 
           // schematic route extension.
           if (FAILED(spSpecRef->QueryInterface (IID_CATISchRoute,
               (void **) &piSchRoute)))
           {
              // make sure this is a reference product
              spPrdRef = spSpecRef;
              if (!!spPrdRef) 
              {
                 if (SUCCEEDED(spPrdRef->IsReference()))
                 {
                    CATIProduct_var spPrdRoot = CAASchAppBaseServices::
                                                 GetProductRootObject(pDoc);
                    // create the route instance 
                    if (!!spPrdRef && !!spPrdRoot)
                    { 
                       CATISpecObject_var spSpecInst = spPrdRoot->AddProduct(spPrdRef);
                       if (!!spSpecInst)
                       { 
                          RC = spSpecInst->QueryInterface (IID_IUnknown,
                                (void **) oAppRoute);
                       }
                    } // if (!!spPrdRef && !!spPrdRoot)
                 } // if (SUCCEEDED(spPrdRef->IsReference()))
              } // if (!!spPrdRef) 
           } // if (FAILED(spSpecRef->QueryInterface (IID_CATISchRoute,
        } // if (!!spSpecRef)
     } // if (!!spAppCont)
  }
  CATCatch (CATError, pError)
	{
     if (pError) Flush(pError);
     RC = CATReturnFailure;
	}	
  CATEndTry;
  if (FAILED(RC)) {if (*oAppRoute) {(*oAppRoute)->Release(); (*oAppRoute)=NULL;}}
  if (piSchRoute) {piSchRoute->Release(); piSchRoute=NULL;}
  return RC;
}


