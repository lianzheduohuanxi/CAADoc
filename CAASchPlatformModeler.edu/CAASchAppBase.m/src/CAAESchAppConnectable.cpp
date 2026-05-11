// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//

// This framework
#include "CAAESchAppConnectable.h"
#include "CAASchAppInternalError.h"
#include "CAASchAppBaseServices.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppFeatureSUServices.h"

// CATSchPlatformInterfaces
#include "CATSchListServices.h"
#include "CATSchGeneralEnum.h"
#include "CATISchAppConnector.h"
#include "CATISchAppConnection.h"
#include "CATISchAppCntrFlow.h"

// Product Structure
#include "CATIProduct.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATILinkableObject.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecAttribute.h"
#include "CATIConnector.h"
#include "CATIConnectable.h"

// System
#include "CATIUnknownList.h"
#include "CATICStringList.h"
#include "CATLISTV_CATBaseUnknown.h"

CATBeginImplementClass(CAAESchAppConnectable,DataExtension,CATBaseUnknown,CAASCHEDUPart);
CATAddExtendedImplementation(CAASCHEDUString);
CATEndImplementClass(CAAESchAppConnectable);

#include "TIE_CATISchAppConnectable.h"
TIEchain_CATISchAppConnectable(CAAESchAppConnectable);         


//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppConnectable::CAAESchAppConnectable()
{
}

//  ===========================================================================
//  | Copy Constructor
//  ===========================================================================
//
CAAESchAppConnectable::CAAESchAppConnectable (
   const CAAESchAppConnectable &Copy)
{
}

//  ===========================================================================
//  | Assignment "=" operator
//  ===========================================================================
//
CAAESchAppConnectable &
CAAESchAppConnectable::operator= (const CAAESchAppConnectable& base)
{
  return *this;
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppConnectable::~CAAESchAppConnectable()
{
}

//  ===========================================================================
//  | AppListConnectors
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppListConnectors (
  CATICStringList *iLCntrClassFilter,
  CATIUnknownList **oLCntrs)
{ 
  HRESULT rc = E_FAIL;  
  *oLCntrs = NULL;
  CATTry 
	{
    CATIConnectable_var spCtblThis(GetImpl());
    if ( NULL_var != spCtblThis )
    {
      CATListValCATBaseUnknown_var *pLCtrs = spCtblThis->GiveRequestedConnectors(NULL);
      if ( NULL != pLCtrs ) 
      {
        if ( pLCtrs->Size() > 0 )
        {
          for ( int iCtr=1; iCtr <= pLCtrs->Size(); iCtr++)
          {
            CATISpecObject_var spCtrSpec((*pLCtrs)[iCtr]);

            // Filter Connector Class if necessary
            boolean ToOutput = TRUE;
            if ( NULL != iLCntrClassFilter )
            {
              ToOutput = FALSE;
              unsigned int LCStrSize = 0;
              int NbpiLCStr = 0;
              rc = iLCntrClassFilter->Count (&LCStrSize);
              NbpiLCStr = LCStrSize;
              if (NbpiLCStr != 0)
              {
                for (int iCStr=1; !ToOutput && iCStr <= NbpiLCStr; iCStr++)
                {
                  char *piCStrMember = NULL;
                  if ( SUCCEEDED(iLCntrClassFilter->Item (iCStr-1,&piCStrMember) ) &&
                        (NULL != piCStrMember) )
                  {
                    CATUnicodeString CtrClass = piCStrMember;
                    //cerr << iCStr << " FilterCtrClass=" << CtrClass <<endl;                  
                    if ( spCtrSpec->IsSubTypeOf(CtrClass) )
                      ToOutput = TRUE;
                    delete [] piCStrMember; piCStrMember=NULL;
                  }
                }
              }
            }
            if ( ToOutput && (NULL_var != spCtrSpec) )
            {
              // Allocate output list if not yet done
              if ( NULL == *oLCntrs )
              {
                CATSchListServices List;
                rc = List.CreateCATIUnknownList (oLCntrs);
              }
              if ( SUCCEEDED(rc) && (NULL != *oLCntrs) )
              {
                IUnknown *piUnknown = NULL;
                rc = spCtrSpec->QueryInterface (IID_IUnknown, (void **) &piUnknown);
                if (SUCCEEDED(rc) && (NULL != piUnknown))
                {
                  rc = (*oLCntrs)->Add(iCtr-1,piUnknown);
                  if ( NULL != piUnknown )
                  {
                    piUnknown->Release(); piUnknown = NULL;
                  }
                }
              }
            }
          } // end for()
        } // end if (Size > 0)
        delete pLCtrs; pLCtrs = NULL;
      } // end if ( NULL != pLCtrs )
      if (NULL == *oLCntrs ) rc = E_FAIL;
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
//  | AppListConnectables
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppListConnectables (
  CATICStringList *iLCntbleClassFilter,
  CATIUnknownList **oLCntbles,
  CATIUnknownList **oLCntrsOnThisObj,
  CATIUnknownList **oLCntrsOnConnected)
{
  HRESULT rc = E_FAIL;
  *oLCntbles = NULL;
  *oLCntrsOnThisObj = NULL;
  *oLCntrsOnConnected = NULL;
  CATTry 
	{
    CATIProduct_var spThisPrd(GetImpl());
    CATIConnectable_var spCtblThis(spThisPrd);
    CATSchListServices aList;
    int NumOutput = 0;
    
    // Find connection of each connector on the connectable
    CATIUnknownList *piLCtrs = NULL;
    if ( SUCCEEDED(AppListConnectors(NULL,&piLCtrs) ) && (NULL != piLCtrs) )
    {
      unsigned int LUnknownSize = 0;
      int NumOfCtrs = 0;
      HRESULT rcLCtrs = piLCtrs->Count (&LUnknownSize);
      NumOfCtrs = LUnknownSize;
      for (int iCtr=1; iCtr <= NumOfCtrs; iCtr++)
      {        
        IUnknown *piUnknownCtr = NULL; 
        if ( SUCCEEDED(piLCtrs->Item (iCtr-1,&piUnknownCtr)) && (NULL != piUnknownCtr) )
        {
          CATISchAppConnector *piCtr = NULL;    
          if( SUCCEEDED(piUnknownCtr->QueryInterface (IID_CATISchAppConnector,(void **) &piCtr)) && 
            (NULL != piCtr) )
          {
            CATIUnknownList *piLCnxs = NULL;
            if ( SUCCEEDED(piCtr->AppListConnections(NULL, &piLCnxs)) && (NULL != piLCnxs) )
            {
              unsigned int LUnknownSize = 0;
              int NumOfCnxs = 0;
              HRESULT rcLCnxs = piLCnxs->Count (&LUnknownSize);
              NumOfCnxs = LUnknownSize;              
              for (int iCnx=1; iCnx <= NumOfCnxs; iCnx++)
              {
                IUnknown *piUnknownCnx = NULL;
                if (SUCCEEDED(piLCnxs->Item (iCnx-1,&piUnknownCnx)) && (NULL != piUnknownCnx))
                {
                  CATISchAppConnection *piCnx = NULL;
                  if (SUCCEEDED(piUnknownCnx->QueryInterface (IID_CATISchAppConnection, (void **)&piCnx))
                      && (NULL != piCnx))
                  {
                    CATIUnknownList *piLCtbls = NULL;
                    CATIUnknownList *piLCtblCtrs = NULL;
                    if ( SUCCEEDED(piCnx->AppListConnectables(iLCntbleClassFilter, &piLCtbls, &piLCtblCtrs )) &&
                      (NULL != piLCtbls) && (NULL != piLCtblCtrs) )
                    {
                      int ThisCtrPosition = aList.Locate( piLCtblCtrs, piUnknownCtr );
                      if ( ThisCtrPosition >= 0 )
                      {
                        unsigned int LUnknownSize = 0;
                        int NumOfCtblCtrs = 0;
                        HRESULT rcLCtblCtrs = piLCtblCtrs->Count (&LUnknownSize);
                        NumOfCtblCtrs = LUnknownSize;              
                        for (int iCtblCtr=1; iCtblCtr <= NumOfCtblCtrs; iCtblCtr++)
                        {
                          if ( (iCtblCtr-1) != ThisCtrPosition )
                          {
                            if ( !*oLCntbles ) aList.CreateCATIUnknownList(oLCntbles);
                            if ( !*oLCntrsOnThisObj ) aList.CreateCATIUnknownList(oLCntrsOnThisObj);
                            if ( !*oLCntrsOnConnected ) aList.CreateCATIUnknownList(oLCntrsOnConnected);
                            
                            IUnknown *piUnknownCtbl = NULL;
                            IUnknown *piUnknownCtblCtr = NULL;
                            if (SUCCEEDED(piLCtbls->Item (iCtblCtr-1,&piUnknownCtbl)) && (NULL != piUnknownCtbl) &&
                                SUCCEEDED(piLCtblCtrs->Item (iCtblCtr-1,&piUnknownCtblCtr)) && (NULL != piUnknownCtblCtr) )
                            {                              
                              rc = (*oLCntbles)->Add(NumOutput, piUnknownCtbl);
                              rc = (*oLCntrsOnThisObj)->Add(NumOutput, piUnknownCtr);
                              rc = (*oLCntrsOnConnected)->Add(NumOutput, piUnknownCtblCtr);
                              NumOutput++;
                              
                              if ( NULL != piUnknownCtbl )
                              {
                                piUnknownCtbl->Release(); piUnknownCtbl = NULL;
                              }
                              if ( NULL != piUnknownCtblCtr )
                              {
                                piUnknownCtblCtr->Release(); piUnknownCtblCtr = NULL;
                              }
                            }
                          }
                        } //endfor iCtblCtr
                      }
                      if ( NULL != piLCtbls ) { piLCtbls->Release(); piLCtbls = NULL; }
                      if ( NULL != piLCtblCtrs ) { piLCtblCtrs->Release(); piLCtblCtrs = NULL; }
                    }
                    if ( NULL != piCnx ) { piCnx->Release(); piCnx = NULL; }
                  }
                  if ( NULL != piUnknownCnx ) { piUnknownCnx->Release(); piUnknownCnx = NULL; }
                }
              } //endfor iCnx
              if ( NULL != piLCnxs ) { piLCnxs->Release(); piLCnxs = NULL; }
            }
            if ( NULL != piCtr ) { piCtr->Release(); piCtr = NULL; }
          }
          if ( NULL != piUnknownCtr ) { piUnknownCtr->Release(); piUnknownCtr = NULL; }
        }
      } //endfor iCtr
      if ( NULL != piLCtrs ) { piLCtrs->Release(); piLCtrs = NULL; }
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
//  | AppAddConnector
//  |   if iClasstype is NULL, use default cntr type.
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppAddConnector (
  const char *iClassType,
  CATISchAppConnector **oNewAppCntr)
{
  HRESULT rc = E_FAIL;
  *oNewAppCntr = NULL;
  CATTry 
	{
    CATIProduct_var spPrd(GetImpl());
    if ( NULL_var != spPrd )
    {
      // Get a list of valid connector types to validate input
      CATUnicodeString iConnectorType (iClassType);
      CATICStringList *pLConnectorType=NULL;
      boolean IsValidConnectorType = FALSE;      
      if ( SUCCEEDED(AppListValidCntrTypes(&pLConnectorType)) && pLConnectorType )
      {
        if ( iConnectorType.IsNull() )
        {          
          char *piCStr = NULL;
          pLConnectorType->Item (0,&piCStr);
          iConnectorType = piCStr;
          delete []piCStr; piCStr = NULL;
          IsValidConnectorType = TRUE;
        }
        else
        {
          CATSchListServices aList;
          IsValidConnectorType = aList.Locate(pLConnectorType,iClassType) >= 0;
        }
        pLConnectorType->Release(); pLConnectorType = NULL;
      }
      else
      {
        CAASchAppInternalError *pErr = new CAASchAppInternalError (
          CAASchAppInternalError::Internal_NoValidConnectorType, 
          "Internal_NoValidConnectorType",               
          CAASchAppInternalErrorFile);
        CATThrow(pErr);   
      }

      if ( IsValidConnectorType )
      {
        // Get this product container
        CATISpecObject_var spPrdSpec = spPrd;
        CATIContainer_var spCont = spPrdSpec->GetFeatContainer();

				// Find connector startup
        CATISpecObject* piSpecObjectOnCtr = NULL;
        CATISpecObject_var spCtrSUSpec = NULL_var;

        CAASchAppFeatureSUServices SUServices;
        if ( SUCCEEDED(SUServices.FindStartUpClass (iConnectorType,(CATIContainer*)spCont,&piSpecObjectOnCtr) ) )
        {
          spCtrSUSpec = piSpecObjectOnCtr;
          if ( NULL != piSpecObjectOnCtr ) { piSpecObjectOnCtr->Release(); piSpecObjectOnCtr = NULL; }
        }

        if ( NULL_var != spCtrSUSpec )
        {
	        // Add a new connector to the Product
          CATILinkableObject_var spLinkableNULL ( NULL_var );
          CATIConnector_var spCtr = spPrd->AddConnector (spLinkableNULL, spCtrSUSpec);
          if (NULL_var != spCtr)
          {        
            rc = spCtr->QueryInterface (IID_CATISchAppConnector,(void **) oNewAppCntr);

            // Set CntrFlow default SchCntrFlowCapability_InOutDirection
            CATISchAppCntrFlow *piAppCntrFlow = NULL;
            if ( SUCCEEDED(spCtr->QueryInterface
              (IID_CATISchAppCntrFlow,(void **) &piAppCntrFlow)) && (NULL != piAppCntrFlow) )
            {
              piAppCntrFlow->AppSetFlowCapability(SchCntrFlowCapability_InOutDirection);              
              piAppCntrFlow->Release(); piAppCntrFlow = NULL;
            }
          }
          else
          {
            CAASchAppInternalError *pErr = new CAASchAppInternalError (
              CAASchAppInternalError::Internal_FailToCreateConnector, 
              "Internal_FailToCreateConnector",               
              CAASchAppInternalErrorFile);
            pErr -> SetNLSParameters (1, &iConnectorType);
            CATThrow(pErr);   
          }
        }
      }
      else
      {
        CAASchAppInternalError *pErr = new CAASchAppInternalError (
          CAASchAppInternalError::Internal_InvalidConnectorType, 
          "Internal_InvalidConnectorType",               
          CAASchAppInternalErrorFile);
        pErr -> SetNLSParameters (1, &iConnectorType);
        CATThrow(pErr);
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
//  | AppRemoveConnector
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppRemoveConnector (
  CATISchAppConnector *iCntrToRemove)
{
  HRESULT rc = E_FAIL;
  CATTry 
	{
    // To Do:
    // Validate input connector
    // Unlink from its connections
    // Remove connector from its product
    // Synchronize attribute
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
//  | AppListValidCntrTypes
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppListValidCntrTypes (
  CATICStringList **oLValidCntrTypes)
{
  HRESULT rc = E_FAIL;
  *oLValidCntrTypes = NULL;
  CATTry 
	{
    // return default for now
    CATUnicodeString DefaultCtrType = SCHEDUClass_Connector;
    CATSchListServices List;
    if (SUCCEEDED (List.CreateCATICStringList (oLValidCntrTypes)) &&
        (NULL != *oLValidCntrTypes))
    {
      rc = (*oLValidCntrTypes)->Add(0, DefaultCtrType );
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
//  | AppGetReferenceName
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppGetReferenceName (
  char **oReferenceName)
{
  HRESULT rc = E_FAIL;
  *oReferenceName = NULL;

  CATIProduct *piPrd = NULL;
  CATTry 
  {
    if (SUCCEEDED (QueryInterface (IID_CATIProduct,
        (void **) &piPrd)))
    {
       CATUnicodeString URefName = piPrd->GetPartNumber();
       int CharSize = URefName.GetLengthInChar();
       if (CharSize != 0)
       {
          *oReferenceName = new char [CharSize + 1];
          strcpy(*oReferenceName, URefName.ConvertToChar());
          rc = S_OK;          
       }
    }
  }
  if ( NULL != piPrd ) { piPrd->Release(); piPrd = NULL; }

  CATCatch (CATError, error)
  {
    if ( NULL != piPrd ) { piPrd->Release(); piPrd = NULL; }
    rc = E_FAIL;
    CATRethrow;
  }	
  CATEndTry;
  return rc;
}

//  ===========================================================================
//  | AppSetReferenceName
//  ===========================================================================
//
HRESULT CAAESchAppConnectable::AppSetReferenceName (
  const char *iReferenceName)
{
  HRESULT rc = E_FAIL;
  if (NULL == iReferenceName) return rc;

  CATIProduct *piPrd = NULL;
  CATTry 
  {
    if (SUCCEEDED (QueryInterface (IID_CATIProduct,
        (void **) &piPrd)))
    {
       piPrd->SetPartNumber(iReferenceName);
       rc = S_OK; 
    }
  }
  if ( NULL != piPrd ) { piPrd->Release(); piPrd = NULL; }

  CATCatch (CATError, error)
  {
    if ( NULL != piPrd ) { piPrd->Release(); piPrd = NULL; }
    rc = E_FAIL;
    CATRethrow;
  }	
  CATEndTry;
  return rc;
}
