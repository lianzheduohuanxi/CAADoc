// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
// CAAESchAppCntrFlow:
//

// This framework
#include "CAAESchAppCntrFlow.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppErrors.h"


// CATSchPlatformInterfaces
#include "CATISchAppRoute.h"
#include "CATISchAppComponent.h"
#include "CATISchAppConnector.h"
#include "CATISchAppConnectable.h"
#include "CATISchAppConnection.h"
#include "CATISchCompFlow.h"
#include "CATISchInternalFlow.h"
#include "CATSchListServices.h"

// ObjectSpecsModeler
#include "CATISpecAttrKey.h"
#include "CATISpecAttrAccess.h"


CATImplementClass(CAAESchAppCntrFlow,DataExtension,CATBaseUnknown,CAASCHEDUConnector);

#include "TIE_CATISchAppCntrFlow.h"
TIEchain_CATISchAppCntrFlow(CAAESchAppCntrFlow);         


//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppCntrFlow::CAAESchAppCntrFlow()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppCntrFlow::~CAAESchAppCntrFlow()
{
}

//  ===========================================================================
//  | AppGetFlowCapability
//  ===========================================================================
//
HRESULT CAAESchAppCntrFlow::AppGetFlowCapability (
    CATSchCntrFlowCapability *oEFlowCapability)
{
  HRESULT rc = S_OK;
  *oEFlowCapability = SchCntrFlowCapability_Undefined;
  CATTry 
	{
    CATISpecAttrAccess_var spAccessThis(GetImpl());
    if ( NULL_var != spAccessThis )
    {      
      CATISpecAttrKey *piKey = spAccessThis->GetAttrKey(SCHEDUATTR_Connector_FlowCapacity);
      if ( (NULL != piKey) && spAccessThis->TestAttributeValue(piKey) )
      {
        *oEFlowCapability = CATSchCntrFlowCapability(spAccessThis->GetInteger (piKey));
      }
      if ( NULL != piKey ) { piKey->Release(); piKey = NULL; }
    }
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
//  | AppSetFlowCapability
//  ===========================================================================
//
HRESULT CAAESchAppCntrFlow::AppSetFlowCapability (
    CATSchCntrFlowCapability iEFlowCapability)
{
  HRESULT rc = E_FAIL;
  CATTry 
	{
    CATISpecAttrAccess_var spAccessThis(GetImpl());    
    if ( NULL_var != spAccessThis )
    {      
      CATISpecAttrKey *piKey = spAccessThis->GetAttrKey(SCHEDUATTR_Connector_FlowCapacity);
      if ( NULL != piKey )
      {
        spAccessThis->SetInteger (piKey, (int) iEFlowCapability);
        piKey->Release(); piKey = NULL;
        rc = S_OK;
      }
    }
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
//  | AppGetFlowReality
//  ===========================================================================
//
HRESULT CAAESchAppCntrFlow::AppGetFlowReality (
    CATSchCntrFlowReality *oEFlowReality)
{
  HRESULT rc = S_OK;
  CATISchAppConnector *piCntr = NULL;
  CATISchAppConnectable *piConnectable = NULL;
  CATISchAppComponent *piComp = NULL;

  *oEFlowReality = SchCntrFlowReality_Undefined;

  CATTry 
	 {
    CATISpecAttrAccess_var spAccessThis(GetImpl());
    if ( NULL_var != spAccessThis )
    {
      CATISpecAttrKey *piKey = spAccessThis->GetAttrKey(SCHEDUATTR_Connector_FlowCapacity);
      if ( (NULL != piKey) && spAccessThis->TestAttributeValue(piKey) )
      {
        *oEFlowReality = CATSchCntrFlowReality(spAccessThis->GetInteger (piKey));
      }
      if ( NULL != piKey ) { piKey->Release(); piKey = NULL; }
    }

    // If flow reality is undefined and the cntr belongs to a component,
    // get the cntr flow capability.
    if ( *oEFlowReality == SchCntrFlowReality_Undefined && 
          SUCCEEDED (QueryInterface(IID_CATISchAppConnector,(void**) &piCntr)) )
    {
      if ( SUCCEEDED(piCntr->AppGetAssociatedConnectable(&piConnectable)) )
      {
        if ( SUCCEEDED(piConnectable->QueryInterface(IID_CATISchAppComponent,
             (void**)&piComp)) )
        {
          CATSchCntrFlowCapability eFlowCapability = SchCntrFlowCapability_Undefined;
          rc = AppGetFlowCapability (&eFlowCapability);
          *oEFlowReality = CATSchCntrFlowReality((int)eFlowCapability);

          // if the flow capability is Undefined or INOUT, derive the flow reality
          // from a connected route.
          if ( eFlowCapability == SchCntrFlowCapability_Undefined || 
               eFlowCapability == SchCntrFlowCapability_InOutDirection )
          {
             CATSchCntrFlowReality eFReality;
             int CnxAndFlow = 0;
             int ioCntrCount = 0;
             boolean bRouteFound = DeriveFlowReality (piCntr, piConnectable,
                                   CnxAndFlow, &ioCntrCount, &eFReality);
             if ( bRouteFound )
             {
                // if the number of cntrs is odd, the component cntr flow reality
                // is the opposite of the route cntr's.
                if ( (ioCntrCount%2) != 0 )
                {
                   if ( eFReality == SchCntrFlowReality_InDirection )
                      eFReality = SchCntrFlowReality_OutDirection;
                   else if ( eFReality == SchCntrFlowReality_OutDirection )
                      eFReality = SchCntrFlowReality_InDirection;
                }
                *oEFlowReality = eFReality;
                rc = S_OK;
             }
          } 
        }
      } // end get associated connectable
    }
  }
  if ( NULL != piCntr ) { piCntr->Release(); piCntr = NULL; }
  if ( NULL != piConnectable ) { piConnectable->Release(); piConnectable = NULL; }
  if ( NULL != piComp ) { piComp->Release(); piComp = NULL; }

  CATCatch (CATError, error)
	 {
    if ( NULL != piCntr ) { piCntr->Release(); piCntr = NULL; }
    if ( NULL != piConnectable ) { piConnectable->Release(); piConnectable = NULL; }
    if ( NULL != piComp ) { piComp->Release(); piComp = NULL; }
    rc = E_FAIL;
    CATRethrow;
	 }	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppSetFlowReality
//  ===========================================================================
//
HRESULT CAAESchAppCntrFlow::AppSetFlowReality (
    CATSchCntrFlowReality iEFlowReality)
{
  HRESULT rc = E_FAIL;
  CATTry 
	{
    CATISpecAttrAccess_var spAccessThis(GetImpl());
    if ( NULL_var != spAccessThis )
    {
      CATISpecAttrKey *piKey = spAccessThis->GetAttrKey(SCHEDUATTR_Connector_FlowCapacity);
      if ( NULL != piKey )
      {
        spAccessThis->SetInteger (piKey, (int) iEFlowReality);
        piKey->Release(); piKey = NULL;
        rc = S_OK;
      }
    }
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
//  | DeriveFlowReality (private method)
//  | Derive the flow reality for the component connector by searching for
//  | a route that is connected (directly or indirectly) to the component and
//  | using the route cntr flow reality to derive the component cntr flow
//  | reality.  Return true if connected route cntr found.
//  | Input:
//  |      CnxOrFlow = 0: Check connected cntr and internal flow cntr
//  |                  1: Only check for connected cntr
//  |                  2: Only check for internal flow cntr
//  ===========================================================================
//
boolean CAAESchAppCntrFlow::DeriveFlowReality (CATISchAppConnector *iAppCntr,
    CATISchAppConnectable *iConnectable, int CnxOrFlow, int *ioCntrCount,
    CATSchCntrFlowReality *oEFlowReality)
{

  boolean bFoundCntr = FALSE;
  *oEFlowReality = SchCntrFlowReality_Undefined;

  if ( (NULL == iAppCntr) || (NULL == iConnectable) || (ioCntrCount == 0) ) return bFoundCntr;

  HRESULT rc = E_FAIL;
  CATISchAppConnector *piConnectedCntr = NULL;
  CATISchAppConnectable *piConnectable = NULL;
  CATISchAppCntrFlow *piCntrFlow = NULL;
  CATISchAppRoute *piRoute = NULL;
  CATIUnknownList *piLSchCntrs = NULL;
  IUnknown *piUK = NULL;

  CATTry 
	 {
    // Look for the connector that is connected to this cntr
    if ( CnxOrFlow == 0 || CnxOrFlow == 1 )
    {
      if ( SUCCEEDED(FindConnectedCntr(iAppCntr,&piConnectedCntr)) && (NULL != piConnectedCntr) )
      {
         if ( SUCCEEDED(piConnectedCntr->AppGetAssociatedConnectable(&piConnectable)) )
         {
            *ioCntrCount = *ioCntrCount + 1;
            // Found route cntr, get its flow reality
            if ( SUCCEEDED(piConnectable->QueryInterface(IID_CATISchAppRoute,
                 (void**)&piRoute)) && (NULL != piRoute) )
            {
               if ( SUCCEEDED(piConnectedCntr->QueryInterface(IID_CATISchAppCntrFlow,
                    (void**)&piCntrFlow)) && (NULL != piCntrFlow) )
               {
                  bFoundCntr = TRUE;
                  rc = piCntrFlow->AppGetFlowReality (oEFlowReality);
               }
            }
            // Connected cntr belongs to a component, check its internal flow cntrs
            else 
            {
               int iChkFlow = 2;
               bFoundCntr = DeriveFlowReality (piConnectedCntr, piConnectable,
                            iChkFlow, ioCntrCount, oEFlowReality);
               if ( !bFoundCntr ) *ioCntrCount = *ioCntrCount - 1;
            }
            piConnectable->Release(); piConnectable = NULL;
         } // get connectable
         piConnectedCntr->Release(); piConnectedCntr = NULL;
      } // find connected cntr
    }

    // If there is no connected cntr, look for the internal flow connectors
    if ( (CnxOrFlow == 0 || CnxOrFlow == 2) && !bFoundCntr )
    {
       if ( SUCCEEDED(FindInternalFlowCntrs (iAppCntr,iConnectable,&piLSchCntrs)) )
       {
          int NumOfCntrs = 0;
          unsigned int uSize;
          if ( SUCCEEDED(piLSchCntrs->Count(&uSize)) ) NumOfCntrs = uSize;
               
          for ( int i = 1; i <= NumOfCntrs; i++ )
          {                  
            if ( SUCCEEDED(piLSchCntrs->Item(i-1, &piUK)) ) 
            {
              if ( SUCCEEDED(piUK->QueryInterface(IID_CATISchAppConnector,
                   (void **)&piConnectedCntr)) )
              {
                *ioCntrCount = *ioCntrCount + 1;
                int iChkCnx = 1;
                bFoundCntr = DeriveFlowReality (piConnectedCntr, iConnectable,
                            iChkCnx, ioCntrCount, oEFlowReality);
                if ( bFoundCntr ) break;
                else *ioCntrCount = *ioCntrCount - 1;
              }
            }
            if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
            if ( NULL != piConnectedCntr ) { piConnectedCntr->Release(); piConnectedCntr = NULL; }
          } // end loop
       } // find internal flow cntrs
    }
  }

  if ( NULL != piConnectedCntr ) { piConnectedCntr->Release(); piConnectedCntr = NULL; }
  if ( NULL != piConnectable ) { piConnectable->Release(); piConnectable = NULL; }
  if ( NULL != piCntrFlow ) { piCntrFlow->Release(); piCntrFlow = NULL; }
  if ( NULL != piRoute ) { piRoute->Release(); piRoute = NULL; }
  if ( NULL != piLSchCntrs ) { piLSchCntrs->Release(); piLSchCntrs = NULL; }
  if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }

  CATCatch (CATError, error)
	 {
    if ( NULL != piConnectedCntr ) { piConnectedCntr->Release(); piConnectedCntr = NULL; }
    if ( NULL != piConnectable ) { piConnectable->Release(); piConnectable = NULL; }
    if ( NULL != piCntrFlow ) { piCntrFlow->Release(); piCntrFlow = NULL; }
    if ( NULL != piRoute ) { piRoute->Release(); piRoute = NULL; }
    if ( NULL != piLSchCntrs ) { piLSchCntrs->Release(); piLSchCntrs = NULL; }
    if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
    bFoundCntr = FALSE;
    rc = E_FAIL;
    CATRethrow;
	 }	
  CATEndTry;
  return bFoundCntr;
}

//=============================================================================
//  Find connected connector (private)
//=============================================================================
HRESULT CAAESchAppCntrFlow::FindConnectedCntr (
  CATISchAppConnector *iAppCntr, CATISchAppConnector **oAppCntr)
{

  HRESULT RC = E_FAIL;
  *oAppCntr = NULL;

  if ( NULL == iAppCntr ) return RC;

  CATISchAppConnector  *piCntr = NULL;
  CATISchAppConnection *piAppCnx = NULL;
  CATIUnknownList *pLCnxs = NULL;  
  CATIUnknownList *pLCntrs = NULL;
  IUnknown *piUK = NULL;

  CATTry 
	 {
     int NumOfCnxs = 0;
     if ( SUCCEEDED(iAppCntr->AppListConnections (NULL,&pLCnxs))
          && (NULL != pLCnxs) )
     {
        unsigned int LCnxsSize = 0;
        if ( SUCCEEDED(pLCnxs->Count (&LCnxsSize)) )
           NumOfCnxs = LCnxsSize;
     }
     if ( NumOfCnxs != 0 && (NULL != pLCnxs) )
     {
        if ( SUCCEEDED(pLCnxs->Item (0,&piUK)) && (NULL != piUK) )
        {
           if ( SUCCEEDED (piUK->QueryInterface (
                IID_CATISchAppConnection, (void **)&piAppCnx)) )
           {    
              piUK->Release(); piUK = NULL;
              int NumOfCntrs = 0;
              if ( SUCCEEDED (piAppCnx->AppListConnectors (NULL,
                   &pLCntrs)) && (NULL != pLCntrs) )
              {
                 unsigned int LCntrsSize = 0;
                 if ( SUCCEEDED(pLCntrs->Count (&LCntrsSize)) )
                    NumOfCntrs = LCntrsSize;
              }
              if ( NumOfCntrs != 0 && (NULL != pLCntrs) )
              {
                 for ( int indx = 1; indx <= NumOfCntrs; indx++ )
                 {
                     if ( SUCCEEDED(pLCntrs->Item (indx-1,&piUK)) && (NULL != piUK) )
                     { 
                        if ( SUCCEEDED (piUK->QueryInterface (
                             IID_CATISchAppConnector, (void **)&piCntr))
                             && (piCntr != iAppCntr) )
                        {
                           *oAppCntr = piCntr;
                           RC = S_OK;
                           break;
                        }
                        if ( NULL != piCntr ) { piCntr->Release(); piCntr = NULL; }
                     }
                     if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
                 }
              }
           }
        }
     }
  }// end CATTry

  if ( NULL != pLCnxs ) { pLCnxs->Release(); pLCnxs = NULL; }
  if ( NULL != pLCntrs ) { pLCntrs->Release(); pLCntrs = NULL; }
  if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
  if ( NULL != piAppCnx ) { piAppCnx->Release(); piAppCnx = NULL; }

  CATCatch (CATError, error)
	 {
     if ( NULL != pLCnxs ) { pLCnxs->Release(); pLCnxs = NULL; }
     if ( NULL != pLCntrs ) { pLCntrs->Release(); pLCntrs = NULL; }
     if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
     if ( NULL != piAppCnx ) { piAppCnx->Release(); piAppCnx = NULL; }
     if ( NULL != piCntr ) { piCntr->Release(); piCntr = NULL; }
     *oAppCntr = NULL;
     RC = E_FAIL;
	    CATRethrow;
  }
  CATEndTry;
  return RC;
}

//=============================================================================
//  Find internal flow connectors associated to the given connector (private)
//=============================================================================
HRESULT CAAESchAppCntrFlow::FindInternalFlowCntrs (CATISchAppConnector *iAppCntr,
  CATISchAppConnectable *iAppCntbl, CATIUnknownList **oLSchCntrs)
{

  HRESULT RC = E_FAIL;
  *oLSchCntrs = NULL;

  if ( (NULL == iAppCntr) || (NULL == iAppCntbl) ) return RC;

  CATISchCompFlow *piCompFlow = NULL;
  CATISchInternalFlow *piFlow = NULL;
  CATISchAppConnector *piCntr1 = NULL;
  CATISchAppConnector *piCntr2 = NULL;
  CATIUnknownList *piLUKFlows = NULL;
  CATIUnknownList *piLUKFlowCntrs = NULL;
  IUnknown *piUK = NULL;
  IUnknown *piUKCntr1 = NULL;
  IUnknown *piUKCntr2 = NULL;

  CATTry 
	 {
     if ( SUCCEEDED(iAppCntbl->QueryInterface(IID_CATISchCompFlow,
                   (void**) &piCompFlow)) && (NULL != piCompFlow) )
     {
        if ( SUCCEEDED(piCompFlow->ListInternalFlows ( &piLUKFlows )) )
        {
           // Allocate output list
           if ( NULL == *oLSchCntrs )
           {
              CATSchListServices List;
              List.CreateCATIUnknownList (oLSchCntrs);
           }

           int NumOfFlows = 0;
           int NumOfCntrs = 0;
           unsigned int uSize;
           if ( SUCCEEDED(piLUKFlows->Count(&uSize)) ) NumOfFlows = uSize;
               
           for ( int i = 1; i <= NumOfFlows; i++ )
           {                  
             if ( SUCCEEDED(piLUKFlows->Item(i-1, &piUK)) )
             {
               if ( SUCCEEDED(piUK->QueryInterface(IID_CATISchInternalFlow,
                    (void **)&piFlow)) )
               {
                 if ( SUCCEEDED(piFlow->ListSchConnectors (&piLUKFlowCntrs)) &&
                      piLUKFlowCntrs )
                 {
                   if ( SUCCEEDED(piLUKFlowCntrs->Item(0,&piUKCntr1)) && 
                        SUCCEEDED(piLUKFlowCntrs->Item(1,&piUKCntr2)) )
                   {
                     if ( SUCCEEDED(piUKCntr1->QueryInterface(IID_CATISchAppConnector,
                          (void**) &piCntr1)) &&
                          SUCCEEDED(piUKCntr2->QueryInterface(IID_CATISchAppConnector,
                          (void**) &piCntr2)) ) 
                     {
                       if ( piCntr1 == iAppCntr )
                       {
                          RC = (*oLSchCntrs)->Add(NumOfCntrs,piUKCntr2);
                          NumOfCntrs++;
                       }
                       else if ( piCntr2 == iAppCntr )
                       {
                          RC = (*oLSchCntrs)->Add(NumOfCntrs,piUKCntr1);
                          NumOfCntrs++;
                       }
                     }
                   }
                   if ( NULL != piUKCntr1 ) { piUKCntr1->Release(); piUKCntr1 = NULL; }
                   if ( NULL != piUKCntr2 ) { piUKCntr2->Release(); piUKCntr2 = NULL; }
                   if ( NULL != piCntr1 ) { piCntr1->Release(); piCntr1 = NULL; }
                   if ( NULL != piCntr2 ) { piCntr2->Release(); piCntr2 = NULL; }
                 }
                 if ( NULL != piLUKFlowCntrs ) { piLUKFlowCntrs->Release(); piLUKFlowCntrs = NULL; }
               }
             }
             if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
             if ( NULL != piFlow ) { piFlow->Release(); piFlow = NULL; }
           } // end loop
        } // end list internal flows
     } // QI CATISchCompFlow
  }

  if ( NULL != piLUKFlows ) { piLUKFlows->Release(); piLUKFlows = NULL; }
  if ( NULL != piCompFlow ) { piCompFlow->Release(); piCompFlow = NULL; }

  CATCatch (CATError, error)
	 {
     if ( NULL != piCompFlow ) { piCompFlow->Release(); piCompFlow = NULL; }
     if ( NULL != piFlow ) { piFlow->Release(); piFlow = NULL; }
     if ( NULL != piCntr1 ) { piCntr1->Release(); piCntr1 = NULL; }
     if ( NULL != piCntr2 ) { piCntr2->Release(); piCntr2 = NULL; }
     if ( NULL != piUK ) { piUK->Release(); piUK = NULL; }
     if ( NULL != piUKCntr1 ) { piUKCntr1->Release(); piUKCntr1 = NULL; }
     if ( NULL != piUKCntr2 ) { piUKCntr2->Release(); piUKCntr2 = NULL; }
     if ( NULL != piLUKFlows ) { piLUKFlows->Release(); piLUKFlows = NULL; }
     if ( NULL != piLUKFlowCntrs ) { piLUKFlowCntrs->Release(); piLUKFlowCntrs = NULL; }
     RC = E_FAIL;
	    CATRethrow;
  }
  CATEndTry;
  return RC;
}
