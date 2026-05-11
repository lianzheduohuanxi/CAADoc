/**
 * @quickreview vso bcy 04:11:29
 */
// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAASchAppSampleConnection
//=============================================================================


#include "CAASchAppSampleConnection.h"
#include "CAASchDeletionMacro.h"


// CATSchPlatformInterfaces
#include "CATISchAppConnector.h"
#include "CATSchListServices.h"


// System
#include "CATIUnknownList.h"
#include "CATICStringList.h"
#include "CATErrorMacros.h"


// ObjectSpecsModeler
#include "CATIConnectable.h"


CATImplementClass(CAASchAppSampleConnection,Implementation,CATBaseUnknown,CATNull);


#include "TIE_CATISchAppConnection.h"
TIEchain_CATISchAppConnection(CAASchAppSampleConnection);


//=============================================================================
// Constructors
//=============================================================================
//
CAASchAppSampleConnection::CAASchAppSampleConnection (const IUnknown* iCntr1,
  const IUnknown* iCntr2) 
: CATBaseUnknown()
{
   CATIConnector *piCntr = NULL;
   if (iCntr1)
   {
      if (SUCCEEDED(((IUnknown *)iCntr1)->QueryInterface(IID_CATIConnector,
          (void **) &piCntr)) && piCntr)
      {
         _spCntr1 = piCntr;
         if (piCntr) {piCntr->Release(); piCntr=NULL;}
      }
   }


   if (piCntr) {piCntr->Release(); piCntr=NULL;}
   if (iCntr2)
   {
      if (SUCCEEDED(((IUnknown *)iCntr2)->QueryInterface(IID_CATIConnector,
          (void **) &piCntr)) && piCntr)
      {
         _spCntr2 = piCntr;
         if (piCntr) {piCntr->Release(); piCntr=NULL;}
      }
   }
   if (piCntr) {piCntr->Release(); piCntr=NULL;}
}


//=============================================================================
// Destructor
//=============================================================================
//
CAASchAppSampleConnection::~CAASchAppSampleConnection() 
{
}




//=============================================================================
// CATISchAppConnection interface implementations
//=============================================================================
//
HRESULT CAASchAppSampleConnection::AppListConnectors (
  CATICStringList *iLCntrClassFilter,
  CATIUnknownList **oLCntrs)
{
  HRESULT RC = CATReturnFailure;
  // this sample implementation ignores the iLCntrClassFilter input.
  if (!oLCntrs) return RC;
  *oLCntrs = NULL;


  IUnknown *piUK1 = NULL;
  IUnknown *piUK2 = NULL;


  CATSchListServices SchList;
  CATTry
  {
     if (!!_spCntr1 && !!_spCntr2)
     {
        RC = _spCntr1->QueryInterface(IID_IUnknown,(void **)&piUK1);
        if (SUCCEEDED(RC) && piUK1) RC =  _spCntr2->QueryInterface (
          IID_IUnknown,(void **)&piUK2);


        if (SUCCEEDED (RC) && piUK1 && piUK2)
        {
           if (SUCCEEDED(SchList.CreateCATIUnknownList(oLCntrs)) && 
               (*oLCntrs))
           {
              if (SUCCEEDED((*oLCntrs)->Add(0,piUK1)))
              {
                 RC = (*oLCntrs)->Add(1,piUK2);
              }
           } // if (SUCCEEDED(SchList.CreateCATIUnknownList(oLCntrs)) && 
        } // if (SUCCEEDED (RC) && piUK1 && piUK2)
     } // if (!!_spCntr1 && !!_spCntr2)
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (FAILED(RC)) if ((*oLCntrs)) {(*oLCntrs)->Release(); (*oLCntrs)=NULL;}
  if (piUK1) {piUK1->Release(); piUK1=NULL;}
  if (piUK2) {piUK2->Release(); piUK2=NULL;}
  return RC;
}


//=============================================================================
HRESULT CAASchAppSampleConnection::AppListConnectables (
  CATICStringList *iLCntbleClassFilter,
  CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrs)
{
  HRESULT RC = CATReturnFailure;
  // this sample implementation ignores the iLCntrClassFilter input.
  if (!oLCntbles || !oLCntrs) return RC;
  *oLCntrs = NULL;
  *oLCntbles = NULL;


  IUnknown *piUK1 = NULL;
  IUnknown *piUK2 = NULL;
  CATIConnectable_var spCntbl;
  CATIConnector_var spCntr;
  CATSchListServices SchList;
  CATTry
  {
     if (!!_spCntr1 && !!_spCntr2)
     {
        RC = _spCntr1->QueryInterface(IID_IUnknown,(void **)&piUK1);
        if (SUCCEEDED(RC) && piUK1) RC =  _spCntr2->QueryInterface (
          IID_IUnknown,(void **)&piUK2);


        if (SUCCEEDED (RC) && piUK1 && piUK2)
        {
           if (SUCCEEDED(SchList.CreateCATIUnknownList(oLCntrs)) && 
               (*oLCntrs))
           {
              if (SUCCEEDED((*oLCntrs)->Add(0,piUK1)))
              {
                 RC = (*oLCntrs)->Add(1,piUK2);
              }
           } // if (SUCCEEDED(SchList.CreateCATIUnknownList(oLCntrs)) && 
        } // if (SUCCEEDED (RC) && piUK1 && piUK2)
        if (piUK1) {piUK1->Release(); piUK1=NULL;}
        if (piUK2) {piUK2->Release(); piUK2=NULL;}


        if (SUCCEEDED(RC) && !!_spCntr1 && !!_spCntr2)
        {
           spCntbl = _spCntr1->GiveAssociatedConnectable();
           if (!!spCntbl)
           { 
              RC = spCntbl->QueryInterface(IID_IUnknown,(void **)&piUK1);
              if (SUCCEEDED(RC) && piUK1)
              {
                 spCntbl = _spCntr2->GiveAssociatedConnectable();
                 if (!!spCntbl)
                 {
                    RC = spCntbl->QueryInterface (IID_IUnknown,
                      (void **)&piUK2);
                 }
              }
           }
           if (SUCCEEDED(RC) && piUK1 && piUK2)
           {
              if (SUCCEEDED(SchList.CreateCATIUnknownList(oLCntbles)) && 
                  (*oLCntbles))
              {
                 if (SUCCEEDED((*oLCntbles)->Add(0,piUK1)))
                 {
                    RC = (*oLCntbles)->Add(1,piUK2);
                 }
              } 
           }
        } // if (SUCCEEDED(RC) && !!_spCntr1 && !!_spCntr2)


     } // if (!!_spCntr1 && !!_spCntr2)
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (FAILED(RC)) 
  {
     if ((*oLCntrs)) {(*oLCntrs)->Release(); (*oLCntrs)=NULL;}
     if ((*oLCntbles)) {(*oLCntbles)->Release(); (*oLCntbles)=NULL;}
  }
  if (piUK1) {piUK1->Release(); piUK1=NULL;}
  if (piUK2) {piUK2->Release(); piUK2=NULL;}
  return RC;
}


//=============================================================================
HRESULT CAASchAppSampleConnection::AppAddConnector (
  CATISchAppConnector *iCntrToAdd)
{
  // use CATISchAppConnector->Connect instead
  return CATReturnFailure;
}


//=============================================================================
HRESULT CAASchAppSampleConnection::AppRemoveConnector (
  CATISchAppConnector *iCntrToRemove)
{
  // use CATISchAppConnector->Disconnect instead
  return CATReturnFailure;
}


