/**
 * @quickreview vso bcy 04:11:29
 */
// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
// This framework
#include "CAAESchAppConnector.h"
#include "CAASchDeletionMacro.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppSampleConnection.h"


// CATSchPlatformInterfaces
#include "CATSchListServices.h"
#include "CATISchAppConnectable.h"
#include "CATISchAppConnector.h"
#include "CATISchAppConnection.h"


// ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATIConnectable.h"
#include "CATIConnector.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"


// System
#include "CATIUnknownList.h"
#include "CATICStringList.h"
#include "CATErrorMacros.h"


CATImplementClass(CAAESchAppConnector,DataExtension,CATBaseUnknown,CAASCHEDUConnector);


#include "TIE_CATISchAppConnector.h"
TIEchain_CATISchAppConnector(CAAESchAppConnector);         




//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppConnector::CAAESchAppConnector()
{
}


//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppConnector::~CAAESchAppConnector()
{
}


//  ===========================================================================
//  | AppGetAssociatedConnectable
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppGetAssociatedConnectable (
  CATISchAppConnectable **oConnectable)
{ 
  HRESULT RC = CATReturnFailure;
  if (!oConnectable) return RC;
  *oConnectable = NULL;
  CATTry 
	{
    CATIConnector_var spCtrThis(GetImpl());
    if ( NULL_var != spCtrThis )
    {
      CATIConnectable_var spConnectable = spCtrThis->GiveAssociatedConnectable();
      if ( NULL_var != spConnectable )
      {
        RC = spConnectable->QueryInterface (IID_CATISchAppConnectable,
          (void **) oConnectable);
      }
    }
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (FAILED(RC)) if ((*oConnectable)) {(*oConnectable)->Release(); (*oConnectable)=NULL;}
  return RC;
}


//  ===========================================================================
//  | AppListCompatibleTypes
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppListCompatibleTypes (
  CATICStringList **oLCntrCompatClass)
{
  HRESULT RC = CATReturnFailure;
  if (!oLCntrCompatClass) return RC;
  *oLCntrCompatClass = NULL;
  CATTry 
	{
    CATIConnector_var spCtrThis(GetImpl());
    if ( NULL_var != spCtrThis )
    {
      // return default type for now.      
      CATSchListServices List;
      if (SUCCEEDED (List.CreateCATICStringList (oLCntrCompatClass)) &&
          (NULL != *oLCntrCompatClass))
      {
        RC = (*oLCntrCompatClass)->Add(0, SCHEDUClass_Connector );
        if ( SUCCEEDED(RC) )
        {
          RC = (*oLCntrCompatClass)->Add(1, SCHEDUClass_String);
        }
      }
    }
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (FAILED(RC)) if ((*oLCntrCompatClass)) {(*oLCntrCompatClass)->Release(); (*oLCntrCompatClass)=NULL;}
  return RC;
}


//  ===========================================================================
//  | AppListConnections
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppListConnections (
  CATICStringList *iLCntnClassFilter,
  CATIUnknownList **oLConnections)
{
  HRESULT RC = CATReturnFailure;
  // this sample implementation ignores the iLCntrClassFilter input.
  if (!oLConnections) return RC;
  *oLConnections = NULL;


  CATISpecAttrAccess_var spAccess (GetImpl());
  if (!spAccess) return RC;


  CATISpecAttrKey *piKey = NULL;
  CATISpecObject *piSpecOtherCntr = NULL;
  CAASchAppSampleConnection *pCntn = NULL;
  IUnknown *piUKCntn = NULL;


  CATSchListServices SchList;
  CATTry 
	{
     piKey = spAccess->GetAttrKey (SCHEDUATTR_Connector_ToOtherCntr);
     if (piKey)
     {
        piSpecOtherCntr = spAccess->GetSpecObject(piKey);
        if (piSpecOtherCntr)
        {
           // constructor of CAASchAppSampleConnection will
           // call QueryInterface for input
           pCntn = new CAASchAppSampleConnection ((IUnknown *)(GetImpl()),
             piSpecOtherCntr);
           if (pCntn) RC = pCntn->QueryInterface (IID_IUnknown,
             (void **) &piUKCntn);
           if (SUCCEEDED(RC) && piUKCntn)
           {
              if (SUCCEEDED(SchList.CreateCATIUnknownList(oLConnections)) &&
                  (*oLConnections))
              {
                 RC = (*oLConnections)->Add (0,piUKCntn);
              }
           } // if (SUCCEEDED(RC) && piAppCntn)
        } // if (piSpecOtherCntr)
     } // if (piKey)
     if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
     if (piUKCntn) {piUKCntn->Release(); piUKCntn=NULL;}
     if (pCntn) {pCntn->Release(); pCntn=NULL;}
     if (piKey) {piKey->Release(); piKey=NULL;}
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (FAILED(RC)) if ((*oLConnections)) {(*oLConnections)->Release(); (*oLConnections)=NULL;}
  if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
  if (piUKCntn) {piUKCntn->Release(); piUKCntn=NULL;}
  if (pCntn) {pCntn->Release(); pCntn=NULL;}
  if (piKey) {piKey->Release(); piKey=NULL;}
  return RC;
}


//  ===========================================================================
//  | AppConnect
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppConnect (
  CATISchAppConnector *iCntrToConnect,
  CATISchAppConnection **oCntn )
{
  HRESULT RC = CATReturnFailure;
  if (!oCntn || !iCntrToConnect) return RC;
  *oCntn = NULL;
 
  CATISpecAttrAccess_var spAccess (GetImpl());
  CATISpecObject_var spSpecThis (GetImpl());
  if (!spAccess || !spSpecThis) return RC;


  CATISpecAttrKey *piKey = NULL;
  CATISpecAttrKey *piKey2 = NULL;
  CATISpecObject *piSpecOtherCntr = NULL;
  CAASchAppSampleConnection *pCntn = NULL;


  CATTry 
	{
     piKey = spAccess->GetAttrKey (SCHEDUATTR_Connector_ToOtherCntr);
     if (piKey)
     {
        RC = iCntrToConnect->QueryInterface (IID_CATISpecObject,
          (void **) &piSpecOtherCntr);
        if (SUCCEEDED(RC) && piSpecOtherCntr)
        {
           spAccess->SetSpecObject(piKey,piSpecOtherCntr);


           spAccess = piSpecOtherCntr;
           if (!!spAccess)
           {
              piKey2 = spAccess->GetAttrKey (SCHEDUATTR_Connector_ToOtherCntr);
              if (piKey2)
              {
                 spAccess->SetSpecObject(piKey,spSpecThis);


                 // constructor of CAASchAppSampleConnection will
                 // call QueryInterface for input
                 pCntn = new CAASchAppSampleConnection (
                   (IUnknown *)(GetImpl()),piSpecOtherCntr);
                 if (pCntn) RC = pCntn->QueryInterface (
                   IID_CATISchAppConnection,(void **) oCntn);
              }
           }
        } // if (piSpecOtherCntr)
     } // if (piKey)
     if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
     if (pCntn) {pCntn->Release(); pCntn=NULL;}
     if (piKey) {piKey->Release(); piKey=NULL;}
     if (piKey2) {piKey2->Release(); piKey2=NULL;}
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (FAILED(RC)) if ((*oCntn)) {(*oCntn)->Release(); (*oCntn)=NULL;}
  if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
  if (pCntn) {pCntn->Release(); pCntn=NULL;}
  if (piKey) {piKey->Release(); piKey=NULL;}
  if (piKey2) {piKey2->Release(); piKey2=NULL;}
  return RC;
}


//  ===========================================================================
//  | AppConnectBranch
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppConnectBranch (
  CATISchAppConnector *iCntrToConnect,
  CATISchAppConnection **oCntn )
{
  if (oCntn) (*oCntn) = NULL;
  return CATReturnFailure;
}


//  ===========================================================================
//  | AppDisconnect
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppDisconnect (
  CATISchAppConnector *iCntrToDisconnect)
{
  HRESULT RC = CATReturnFailure;
  if (!iCntrToDisconnect) return RC;
 
  CATISpecAttrAccess_var spAccess (GetImpl());
  CATISpecObject_var spSpecThis (GetImpl());
  if (!spAccess || !spSpecThis) return RC;


  CATISpecAttrKey *piKey = NULL;
  CATISpecAttrKey *piKey2 = NULL;
  CATISpecObject *piSpecCntrIn = NULL;
  CATISpecObject *piSpecOtherCntr = NULL;


  CATTry 
	{
     HRESULT rc1 = E_FAIL;
     rc1 = iCntrToDisconnect->QueryInterface (IID_CATISpecObject,
       (void **) &piSpecCntrIn);
     
     if (SUCCEEDED(rc1) && piSpecCntrIn)
       piKey = spAccess->GetAttrKey (SCHEDUATTR_Connector_ToOtherCntr);


     if (piKey && piSpecCntrIn)
     {
        piSpecOtherCntr = spAccess->GetSpecObject(piKey);
        if (piSpecOtherCntr)
        {
           if (piSpecOtherCntr->IsEqual(piSpecCntrIn))
           {
              spAccess->UnsetAttributeValue (piKey);


              spAccess = piSpecCntrIn;
              if (!!spAccess)
              {
                 piKey2 = spAccess->GetAttrKey (
                   SCHEDUATTR_Connector_ToOtherCntr);
                 if (piKey2)
                 {
                    spAccess->UnsetAttributeValue (piKey2); 
                    RC = CATReturnSuccess;
                 }
              }
           }
        } // if (piSpecOtherCntr)
     } // if (piKey)
     if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
     if (piSpecCntrIn) {piSpecCntrIn->Release(); piSpecCntrIn=NULL;}
     if (piKey) {piKey->Release(); piKey=NULL;}
     if (piKey2) {piKey2->Release(); piKey2=NULL;}


  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
  if (piSpecCntrIn) {piSpecCntrIn->Release(); piSpecCntrIn=NULL;}
  if (piKey) {piKey->Release(); piKey=NULL;}
  if (piKey2) {piKey2->Release(); piKey2=NULL;}
  return RC;
}


//  ===========================================================================
//  | AppOKToNoShowConnectedCntr
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppOKToNoShowConnectedCntr (boolean *oBYes)
{  
  HRESULT RC = CATReturnSuccess;
  if (!oBYes) return RC;
  *oBYes = TRUE;
  return RC;
}


//  ===========================================================================
//  | AppIsCntrConnected
//  ===========================================================================
//
HRESULT CAAESchAppConnector::AppIsCntrConnected (boolean *oBYes)
{  
  HRESULT RC = CATReturnSuccess;
  if (!oBYes) return RC;
  *oBYes = FALSE;
 
  CATISpecAttrAccess_var spAccess (GetImpl());
  if (!spAccess) return RC;


  CATISpecAttrKey *piKey = NULL;
  CATISpecObject *piSpecOtherCntr = NULL;


  CATTry 
	{
     piKey = spAccess->GetAttrKey (SCHEDUATTR_Connector_ToOtherCntr);
     if (piKey)
     {
        piSpecOtherCntr = spAccess->GetSpecObject(piKey);
        if (piSpecOtherCntr)
        {
           *oBYes = TRUE;
        }
     } // if (piKey)
     if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
     if (piKey) {piKey->Release(); piKey=NULL;}
  }
  CATCatch (CATError, pError)
  {
     if (pError) Flush(pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (piSpecOtherCntr) {piSpecOtherCntr->Release(); piSpecOtherCntr=NULL;}
  if (piKey) {piKey->Release(); piKey=NULL;}
  return RC;
}
