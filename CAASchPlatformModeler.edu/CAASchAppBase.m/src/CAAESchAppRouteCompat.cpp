/**
 * @quickreview vso bcy 04:11:29
 */
// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAESchAppRouteCompat
//=============================================================================


// This framework
#include "CAAESchAppRouteCompat.h"
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


CATImplementClass(CAAESchAppRouteCompat,DataExtension,CATBaseUnknown,CAASCHEDUString);


#include "TIE_CATISchAppCompatible.h"
TIEchain_CATISchAppCompatible(CAAESchAppRouteCompat);         




//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppRouteCompat::CAAESchAppRouteCompat()
{
}


//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppRouteCompat::~CAAESchAppRouteCompat()
{
}


//  ===========================================================================
//  | AppIsTargetOKForRoute
//  ===========================================================================
//
HRESULT CAAESchAppRouteCompat::AppIsTargetOKForRoute (
  const char *iRouteCntrClassType,
  CATIUnknownList **oLOKCntrs, boolean *oBYes)
{
  HRESULT RC = CATReturnFailure;
  if (!oLOKCntrs) return RC;
  *oLOKCntrs = NULL;
  if (!oBYes) return RC;
  *oBYes = FALSE;
  if ( !iRouteCntrClassType ) return RC;


  CATISchAppConnectable *piAppCntble = NULL;
  CATISchAppConnector *piAppCntrTgt = NULL;
  CATIUnknownList *piLUKTgtCntrs = NULL;
  CATICStringList *piCStrTgtCompatTypes = NULL;
  IUnknown *piUKTgt = NULL;


  int NbOut = 0;
  CATSchListServices ListService;


  CATTry 
	{
     unsigned int uSizeLTgt = 0;
     int NbSizeLTgt = 0;


     if (SUCCEEDED (QueryInterface (IID_CATISchAppConnectable,
         (void **) &piAppCntble)))
     {
        if (SUCCEEDED (piAppCntble->AppListConnectors (NULL,&piLUKTgtCntrs)) &&
            piLUKTgtCntrs)
        {
           if (SUCCEEDED (piLUKTgtCntrs->Count (&uSizeLTgt)))
           {
              NbSizeLTgt = uSizeLTgt;
           }
        }
     }


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
     if (pError) Flush (pError);
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
HRESULT CAAESchAppRouteCompat::AppIsTargetOKForPlace (
  CATIUnknownList *iLCompSourceCntrs,
  CATIUnknownList **oLTargetCntrs, boolean *oBYes)
{
  HRESULT RC = E_FAIL;  
  if (!oLTargetCntrs) return RC;
  *oLTargetCntrs = NULL;
  if (!oBYes) return RC;
  *oBYes = FALSE;
  return RC;
}


//  ===========================================================================
//  | AppIsTargetOKForInsert
//  ===========================================================================
//
HRESULT CAAESchAppRouteCompat::AppIsTargetOKForInsert (
  CATIUnknownList *iLCompSourceCntrs,
  CATIUnknownList **oLSourceCntrs, boolean *oBYes)
{
  HRESULT RC = CATReturnFailure;  
  if (!oLSourceCntrs) return RC;
  *oLSourceCntrs = NULL;
  if (!oBYes) return RC;
  *oBYes = FALSE;
  if (!iLCompSourceCntrs) return RC;


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
     unsigned int uSizeLSrc = 0;
     unsigned int uSizeLTgt = 0;
     int NbSizeLSrc = 0;
     int NbSizeLTgt = 0;


     if (SUCCEEDED (iLCompSourceCntrs->Count (&uSizeLSrc)))
       NbSizeLSrc = uSizeLSrc;


     if (SUCCEEDED (QueryInterface (IID_CATISchAppConnectable,
         (void **) &piAppCntble)))
     {
        if (SUCCEEDED (piAppCntble->AppListConnectors (NULL,&piLUKTgtCntrs)))
        {
           if (SUCCEEDED (piLUKTgtCntrs->Count (&uSizeLTgt)))
           {
              NbSizeLTgt = uSizeLTgt;
           }
        }
     }


     boolean BFound = FALSE;
     boolean BYesConnected;
     boolean BSrcConnected = FALSE;
     if (NbSizeLTgt && NbSizeLSrc && piLUKTgtCntrs)
     {
        for (int iTgt=1; iTgt<=NbSizeLTgt  && !BFound; iTgt++)
        {
           BYesConnected = FALSE;
           HRESULT rc = E_FAIL;
           if (SUCCEEDED (piLUKTgtCntrs->Item(iTgt-1,&piUKTgt)))
           {
             if (SUCCEEDED (piUKTgt->QueryInterface (
                 IID_CATISchAppConnector,(void **) &piAppCntrTgt)))                 
             {
               rc = piAppCntrTgt->AppListCompatibleTypes (&piCStrTgtCompatTypes);


               if (SUCCEEDED (rc))
               {
                 for (int iSrc=1; iSrc<=NbSizeLSrc; iSrc++)
                 {
                   if (SUCCEEDED (iLCompSourceCntrs->Item(iSrc-1,&piUKSrc)))
                   {
                     if (SUCCEEDED (piUKSrc->QueryInterface (
                         IID_CATISchAppConnector,(void **) &piAppCntrSrc)))                       
                     {
                        rc = piAppCntrSrc->AppIsCntrConnected (
                             &BSrcConnected);
                        if (IsConnectorsCompatible (piAppCntrSrc, 
                            piCStrTgtCompatTypes) && !BSrcConnected)
                        {
                           if (!(*oLSourceCntrs))
                           {
                              if (!SUCCEEDED (
                                ListService.CreateCATIUnknownList (
                                oLSourceCntrs)))
                              {
                                 *oLSourceCntrs = NULL;
                              }
                           }
                           if (*oLSourceCntrs)
                           {
                              RC = (*oLSourceCntrs)->Add (NbOut,piUKSrc);
                              NbOut++;
                           }
                           BFound = TRUE;
                        }
                     } // end if OK iLCompSourceCntrs->Item
                     if (piUKSrc) {piUKSrc->Release(); piUKSrc=NULL;}
                     if (piAppCntrSrc) {piAppCntrSrc->Release(); piAppCntrSrc=NULL;}
                   }
                   if (piUKSrc) {piUKSrc->Release(); piUKSrc=NULL;}
                   if (piAppCntrSrc) {piAppCntrSrc->Release(); piAppCntrSrc=NULL;}
                 } // end for iSrc


                 if (BFound) break;


               } // if SUCCEEDED
               if (piUKTgt) {piUKTgt->Release(); piUKTgt=NULL;}
               if (piAppCntrTgt) {piAppCntrTgt->Release(); piAppCntrTgt=NULL;}
             } // if OK get piAppCntrTgt
             if (piCStrTgtCompatTypes) {piCStrTgtCompatTypes->Release(); piCStrTgtCompatTypes=NULL;}
           } // if OK piLUKTgtCntrs->Item
        } // end for iTgt
     } // if NbSizeLTgt && NbSizeLSrc


     if (SUCCEEDED(RC) && NbOut) *oBYes = TRUE;


  } // end CATTry


  CATCatch (CATError, pError)
	{
     if (pError) Flush (pError);
     RC = CATReturnFailure;
	}	
  CATEndTry;


  if (FAILED(RC))
  {
     if ((*oLSourceCntrs)) {(*oLSourceCntrs)->Release(); (*oLSourceCntrs)=NULL;}
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
//  | Private 
//  ===========================================================================
//
boolean CAAESchAppRouteCompat::IsConnectorsCompatible (
  CATISchAppConnector *iAppCntrSrc, CATICStringList *iCStrTgtCompatTypes)                            
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
