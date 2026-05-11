/**
 * @quickreview vso bcy 04:11:29
 */
// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
// CAAESchAppCompCompat
//=============================================================================


// This framework
#include "CAAESchAppCompCompat.h"
#include "CAASchDeletionMacro.h"


// CATSchPlatformInterfaces
#include "CATSchListServices.h"
#include "CATISchAppConnector.h"
#include "CATISchAppConnectable.h"


// ObjectSpecsModeler
#include "CATISpecObject.h"


// System
#include "CATErrorMacros.h"
#include "CATIUnknownList.h"
#include "CATICStringList.h"


CATImplementClass(CAAESchAppCompCompat,DataExtension,CATBaseUnknown,CAASCHEDUFunctionalPart);


#include "TIE_CATISchAppCompatible.h"
TIEchain_CATISchAppCompatible(CAAESchAppCompCompat);         


//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppCompCompat::CAAESchAppCompCompat()
{
}


//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppCompCompat::~CAAESchAppCompCompat()
{
}


//  ===========================================================================
//  | AppIsTargetOKForRoute
//  ===========================================================================
//
HRESULT CAAESchAppCompCompat::AppIsTargetOKForRoute (
  const char *iRouteCntrClassType,
  CATIUnknownList **oLOKCntrs, boolean *oBYes)
{
  HRESULT RC = E_FAIL;
  if ( !iRouteCntrClassType || !oLOKCntrs || !oBYes ) return RC;
  *oLOKCntrs = NULL;
  *oBYes = FALSE;


  CATISpecObject_var spSpecTgt (GetImpl());
  if (!spSpecTgt) return RC;


  CATISchAppConnectable *piAppCntble = NULL;
  CATISchAppConnector *piAppCntrTgt = NULL;
  CATIUnknownList *piLUKTgtCntrs = NULL;
  CATICStringList *piCStrTgtCompatTypes = NULL;
  IUnknown *piUKTgt = NULL;


  int NbOut = 0;
  CATSchListServices ListService;


  CATTry 
	{
     HRESULT rc1 = E_FAIL;
     unsigned int uSizeLTgt = 0;
     int NbSizeLTgt = 0;


     //------------------------------------------------------------------------
     // Retrieve all the connectors of this component.
     //------------------------------------------------------------------------
     if (SUCCEEDED (QueryInterface (IID_CATISchAppConnectable,
         (void **) &piAppCntble)))
     {
        if (SUCCEEDED (piAppCntble->AppListConnectors (NULL,&piLUKTgtCntrs))
					  && piLUKTgtCntrs)
        {
           if (SUCCEEDED (piLUKTgtCntrs->Count (&uSizeLTgt)))
           {
              NbSizeLTgt = uSizeLTgt;
           }
        }
     }
     //------------------------------------------------------------------------
     // For each connector of this component, check whether it is 
     // compatible with the input route connector type.
     // To be compatible the following conditions must be satisfied:
     // 1- the connector is not connected to other connector
     // 2- the route connector type is compatible with the allowable types of
     // the connector (determined by call AppListCompatibleTypes).
     //------------------------------------------------------------------------
     if (NbSizeLTgt && piLUKTgtCntrs)
     {
        boolean BYesConnected;
        for (int iTgt=1; iTgt<=NbSizeLTgt; iTgt++)
        {
           BYesConnected = FALSE;
           HRESULT rc = E_FAIL;
           if (SUCCEEDED (piLUKTgtCntrs->Item(iTgt-1,&piUKTgt)))
           {
             if (SUCCEEDED (piUKTgt->QueryInterface (
                 IID_CATISchAppConnector,(void **) &piAppCntrTgt)))                 
             {
               if (SUCCEEDED (piAppCntrTgt->AppIsCntrConnected (
                   &BYesConnected)))
               {
                  if (!BYesConnected)
                  {
                     rc = piAppCntrTgt->AppListCompatibleTypes (
                          &piCStrTgtCompatTypes);
                  }
               }
                   
               if (SUCCEEDED (rc))
               {
                  if (ListService.Locate(piCStrTgtCompatTypes, iRouteCntrClassType) >= 0)
                  {
                     if (!(*oLOKCntrs))
                     {
                        if (!SUCCEEDED (
                          ListService.CreateCATIUnknownList (
                          oLOKCntrs)))
                        {
                           *oLOKCntrs = NULL;
                        }
                     }
                     if (*oLOKCntrs)
                     {
                        RC = (*oLOKCntrs)->Add (NbOut,piUKTgt);
                        NbOut++;
                     }
                  }
               } // if SUCCEEDED
               if (piUKTgt) {piUKTgt->Release(); piUKTgt=NULL;}
               if (piAppCntrTgt) {piAppCntrTgt->Release(); piAppCntrTgt=NULL;}
             } // if OK get piAppCntrTgt
             if (piCStrTgtCompatTypes) {piCStrTgtCompatTypes->Release(); piCStrTgtCompatTypes=NULL;}
           } // if OK piLUKTgtCntrs->Item
        } // for iTgt
     } // if NbSizeLTgt




     if (SUCCEEDED(RC) && NbOut) *oBYes = TRUE;


  } // end CATTry
  CATCatch (CATError, pError)
	{
    if (pError) Flush(pError);
    RC = CATReturnFailure;
 	}	
  CATEndTry;
  if (FAILED(RC))
  {
    if ((*oLOKCntrs)) {(*oLOKCntrs)->Release(); (*oLOKCntrs)=NULL;}
    *oBYes = FALSE;
  }
  if (piAppCntble) {piAppCntble->Release(); piAppCntble=NULL;} 
  if (piAppCntrTgt) {piAppCntrTgt->Release(); piAppCntrTgt=NULL;} 
  if (piLUKTgtCntrs) {piLUKTgtCntrs->Release(); piLUKTgtCntrs=NULL;} 
  if (piUKTgt) {piUKTgt->Release(); piUKTgt=NULL;} 
  if (piCStrTgtCompatTypes) {piCStrTgtCompatTypes->Release(); piCStrTgtCompatTypes=NULL;} 
  return RC;
}


//  ===========================================================================
//  | AppIsTargetOKForPlace
//  ===========================================================================
//
HRESULT CAAESchAppCompCompat::AppIsTargetOKForPlace (
  CATIUnknownList *iLCompSourceCntrs,
  CATIUnknownList **oLTargetCntrs, boolean *oBYes)
{
  HRESULT RC = E_FAIL;  
  if (!iLCompSourceCntrs || !oLTargetCntrs || !oBYes) return RC;
  *oLTargetCntrs = NULL;
  *oBYes = FALSE;


  CATISpecObject_var spSpecTgt (GetImpl());
  if (!spSpecTgt) return RC;


  CATISchAppConnectable *piAppCntble = NULL;
  CATISchAppConnector *piAppCntrTgt = NULL;
  CATISchAppConnector *piAppCntrSrc = NULL;
  CATIUnknownList *piLUKTgtCntrs = NULL;
  CATICStringList *piCStrTgtCompatTypes = NULL;
  IUnknown *piUKSrc = NULL;
  IUnknown *piUKTgt = NULL;


  int NbOut = 0;
  CATSchListServices ListService;
  CATTry 
	{
     HRESULT rc1 = E_FAIL;
     unsigned int uSizeLSrc = 0;
     unsigned int uSizeLTgt = 0;
     int NbSizeLSrc = 0;
     int NbSizeLTgt = 0;


     if (SUCCEEDED (iLCompSourceCntrs->Count (&uSizeLSrc)))
       NbSizeLSrc = uSizeLSrc;


     //------------------------------------------------------------------------
     // Retrieve all the connectors of this component.
     //------------------------------------------------------------------------
     if (SUCCEEDED (QueryInterface (IID_CATISchAppConnectable,
         (void **) &piAppCntble)))
     {
        if (SUCCEEDED (piAppCntble->AppListConnectors (NULL,&piLUKTgtCntrs))
					  && piLUKTgtCntrs)
        {
           if (SUCCEEDED (piLUKTgtCntrs->Count (&uSizeLTgt)))
           {
              NbSizeLTgt = uSizeLTgt;
           }
        }
     }


     //------------------------------------------------------------------------
     // For each of the input connector (in the input list: iLCompSourcCntrs)
     // check whether the connector of this component is compatible with the
     // input. To be compatible, the following conditions must be met.
     // 1- the connector of this component must not be connected.
     // 2- the connector type of this component matches that of the input.
     //------------------------------------------------------------------------


     if (NbSizeLTgt && NbSizeLSrc && piLUKTgtCntrs)
     {
        boolean BYesConnected;
        for (int iTgt=1; iTgt<=NbSizeLTgt; iTgt++)
        {
           BYesConnected = FALSE;
           HRESULT rc = E_FAIL;
           if (SUCCEEDED (piLUKTgtCntrs->Item(iTgt-1,&piUKTgt)))
           {
             if (SUCCEEDED (piUKTgt->QueryInterface (
                 IID_CATISchAppConnector,(void **) &piAppCntrTgt)))                 
             {
               if (SUCCEEDED (piAppCntrTgt->AppIsCntrConnected (
                   &BYesConnected)))
               {
                  if (!BYesConnected)
                  {
                     rc = piAppCntrTgt->AppListCompatibleTypes (
                          &piCStrTgtCompatTypes);
                  }
               }
                   
               if (SUCCEEDED (rc))
               {
                 for (int iSrc=1; iSrc<=NbSizeLSrc; iSrc++)
                 {
                   if (SUCCEEDED (iLCompSourceCntrs->Item(iSrc-1,&piUKSrc)))
                   {
                     if (SUCCEEDED (piUKSrc->QueryInterface (
                         IID_CATISchAppConnector,(void **) &piAppCntrSrc)))                       
                     {
                        if (IsConnectorsCompatible (piAppCntrSrc, 
                            piCStrTgtCompatTypes))
                        {
                           if (!(*oLTargetCntrs))
                           {
                              if (!SUCCEEDED (
                                ListService.CreateCATIUnknownList (
                                oLTargetCntrs)))
                              {
                                 *oLTargetCntrs = NULL;
                              }
                           }
                           if (*oLTargetCntrs)
                           {
                              RC = (*oLTargetCntrs)->Add (NbOut,piUKTgt);
                              NbOut++;
                           }
                           break;
                        }
                     } // end if OK iLCompSourceCntrs->Item
                     if (piUKSrc) {piUKSrc->Release(); piUKSrc=NULL;}
                     if (piAppCntrSrc) {piAppCntrSrc->Release(); piAppCntrSrc=NULL;}
                   }
                   if (piUKSrc) {piUKSrc->Release(); piUKSrc=NULL;}
                   if (piAppCntrSrc) {piAppCntrSrc->Release(); piAppCntrSrc=NULL;}
                 } // end for iSrc


               } // if SUCCEEDED
               if (piAppCntrSrc) {piAppCntrSrc->Release(); piAppCntrSrc=NULL;}
               if (piUKTgt) {piUKTgt->Release(); piUKTgt=NULL;}
               if (piAppCntrTgt) {piAppCntrTgt->Release(); piAppCntrTgt=NULL;}
             } // if OK get piAppCntrTgt
             if (piCStrTgtCompatTypes) {piCStrTgtCompatTypes->Release(); piCStrTgtCompatTypes=NULL;}
           } // if OK piLUKTgtCntrs->Item
        } // for iTgt
     } // if NbSizeLTgt && NbSizeLSrc


     if (SUCCEEDED(RC) && NbOut) *oBYes = TRUE;


  } // end CATTry


  CATCatch (CATError, pError)
	{
    if (pError) Flush(pError);
    RC = CATReturnFailure;
 	}	
  CATEndTry;


  if (FAILED(RC))
  {
    if ((*oLTargetCntrs)) {(*oLTargetCntrs)->Release(); (*oLTargetCntrs)=NULL;}
    *oBYes = FALSE;
  }


  if (piAppCntble) {piAppCntble->Release(); piAppCntble=NULL;}
  if (piAppCntrSrc) {piAppCntrSrc->Release(); piAppCntrSrc=NULL;}
  if (piAppCntrTgt) {piAppCntrTgt->Release(); piAppCntrTgt=NULL;}
  if (piLUKTgtCntrs) {piLUKTgtCntrs->Release(); piLUKTgtCntrs=NULL;}
  if (piUKSrc) {piUKSrc->Release(); piUKSrc=NULL;}
  if (piUKTgt) {piUKTgt->Release(); piUKTgt=NULL;}
  if (piCStrTgtCompatTypes) {piCStrTgtCompatTypes->Release(); piCStrTgtCompatTypes=NULL;}


  return RC;
}


//  ===========================================================================
//  | AppIsTargetOKForInsert
//  ===========================================================================
//
HRESULT CAAESchAppCompCompat::AppIsTargetOKForInsert (
  CATIUnknownList *iLCompSourceCntrs,
  CATIUnknownList **oLSourceCntrs, boolean *oBYes)
{
  HRESULT RC = E_FAIL;  
  *oLSourceCntrs = NULL;
  *oBYes = FALSE;
  return RC;
}


//  ===========================================================================
//  | Private 
//  ===========================================================================
//
boolean CAAESchAppCompCompat::IsConnectorsCompatible (
  CATISchAppConnector *iAppCntrSrc, CATICStringList *iCStrTgtCompatTypes,
  int *iMatch)                            
{
  boolean BYes = FALSE;
  if (!iCStrTgtCompatTypes || !iAppCntrSrc) return BYes;


  char *pCStrType = NULL;
  unsigned int uSizeTypes = 0;
  unsigned int uSizeCntns = 0;
  int NbSizeTypes = 0;
  CATISpecObject *piSpecAppCntr = NULL;


  if (!SUCCEEDED (iAppCntrSrc->QueryInterface (IID_CATISpecObject,
      (void **) &piSpecAppCntr))) return BYes;
 
  if (SUCCEEDED (iCStrTgtCompatTypes->Count (&uSizeTypes)))
  {
     NbSizeTypes = uSizeTypes;
  }


  if (NbSizeTypes)
  {
     for (int iCStr=1; iCStr<=NbSizeTypes; iCStr++)
     {
        if (SUCCEEDED (iCStrTgtCompatTypes->Item(iCStr-1,&pCStrType)))
        {
           if (piSpecAppCntr->IsSubTypeOf(pCStrType))
           {
              if (iMatch) *iMatch = iCStr;
              BYes = TRUE;
              break;
           }
        }
        if (pCStrType) {delete [] pCStrType; pCStrType = NULL;}
     }
  }
  if (pCStrType) {delete [] pCStrType; pCStrType = NULL;}
  if (piSpecAppCntr) {piSpecAppCntr->Release(); piSpecAppCntr=NULL;}
  return BYes;
}
