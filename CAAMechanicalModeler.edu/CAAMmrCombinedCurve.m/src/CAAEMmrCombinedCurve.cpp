// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================
//
// CAAEMmrCombinedCurve.cpp
// Provide implementation to interface
//      CAAIMmrCombinedCurve
//======================================================================================

// Local Framework
#include "CAAEMmrCombinedCurve.h"

// ObjectSpecsModeler
#include "CATIDescendants.h"

// MecModInterfaces Framework
#include "CATIMfBRep.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"     // needed to manage/query features
#include "CATISpecAttrAccess.h" // needed to access feature attributes
#include "CATISpecAttrKey.h"    // needed to access to the feature attribute values

CATImplementClass ( CAAEMmrCombinedCurve ,
                   DataExtension       ,    
                   CATBaseUnknown      ,
                   CombinedCurve        );

//-------------------------------------------------------------------------------------
// CAAEMmrCombinedCurve : constructor
//-------------------------------------------------------------------------------------
CAAEMmrCombinedCurve::CAAEMmrCombinedCurve():
CATBaseUnknown()
{
    
}

//-------------------------------------------------------------------------------------
// CAAEMmrCombinedCurve : destructor
//-------------------------------------------------------------------------------------
CAAEMmrCombinedCurve::~CAAEMmrCombinedCurve()
{
    
}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_CAAIMmrCombinedCurve.h" // needed to tie the implementation to its interface
TIE_CAAIMmrCombinedCurve( CAAEMmrCombinedCurve);

// To declare that CombinedCurve implements CAAIMmrCombinedCurve, insert 
// the following line in the interface dictionary:
//
// CombinedCurve  CAAIMmrCombinedCurve  libCAAMmrCombinedCurve


//-------------------------------------------------------------------------------------
// Implements CAAIMmrCombinedCurve::SetCurve
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombinedCurve::SetCurve ( int iNum , CATISpecObject *ipiSpecOnCurve ) 
{    
    // Gets a pointer on CATISpecAttrAccess 
    CATISpecAttrAccess * piSpecAttrAccessOnCC = NULL; 
    HRESULT rc = QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnCC);
    if ( SUCCEEDED(rc) ) 
    { 
       // Gets a pointer on the curve attribute
       CATISpecAttrKey * piSpecAttrKeyOnInputCurve = NULL;
       if ( 1 == iNum )
       {
          piSpecAttrKeyOnInputCurve = piSpecAttrAccessOnCC->GetAttrKey("Curve1");
       }
       else
       {
          piSpecAttrKeyOnInputCurve = piSpecAttrAccessOnCC->GetAttrKey("Curve2");
       }
    
       if ( NULL == piSpecAttrKeyOnInputCurve )
       {
           rc = E_FAIL ;
       }else
       {
      
          CATISpecObject_var spiSpecOnCurve(ipiSpecOnCurve);
             
          if ( NULL_var != spiSpecOnCurve )
          {
            // If the feature is a Feature BRep it must be aggregated by the CC
            CATIMfBRep *pIMfBRep = NULL ;
            rc = spiSpecOnCurve->QueryInterface(IID_CATIMfBRep, (void**) & pIMfBRep);
            if ( SUCCEEDED(rc) )
            {
               CATISpecObject * pFather = spiSpecOnCurve->GetFather() ;
               if ( NULL == pFather )
               {
                  CATIDescendants * pIDescendantsOnCC = NULL ;
                  rc = QueryInterface( IID_CATIDescendants , (void**) &pIDescendantsOnCC );
                                                
                  if ( SUCCEEDED(rc) )
                  {
                     pIDescendantsOnCC->Append(spiSpecOnCurve) ;

                     pIDescendantsOnCC->Release();
                     pIDescendantsOnCC = NULL ;
                  }
               }else 
               {
                  pFather->Release();
                  pFather = NULL ;
                  rc = E_FAIL ;
               }

               pIMfBRep->Release();
               pIMfBRep = NULL ;
       
            }else rc = S_OK ; // it's not an error 

            // Sets the curve as input of the CC
            if ( SUCCEEDED(rc) )
            {
               piSpecAttrAccessOnCC->SetSpecObject(piSpecAttrKeyOnInputCurve,spiSpecOnCurve);
            }

          }else
          {
              // The input curve pointer is null 
              piSpecAttrAccessOnCC->UnsetAttributeValue (piSpecAttrKeyOnInputCurve);
          }

          piSpecAttrKeyOnInputCurve->Release();
          piSpecAttrKeyOnInputCurve = NULL ;
       }

       piSpecAttrAccessOnCC->Release();
       piSpecAttrAccessOnCC = NULL ;
    }

    return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrCombinedCurve::GetCurve
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombinedCurve::GetCurve ( int iNum , CATISpecObject **opiSpecOnCurve ) 
{
    HRESULT rc = E_FAIL;

    if ( NULL == opiSpecOnCurve )
       return E_FAIL ;

    // Gets a pointer on CATISpecObject
    CATISpecAttrAccess *piSpecAttrAccessOnCC = NULL;
    rc = QueryInterface( IID_CATISpecAttrAccess , (void**) &piSpecAttrAccessOnCC );
    if ( SUCCEEDED(rc) )
    {
       CATISpecAttrKey * piSpecAttrKeyOnInputCurve = NULL;
       if ( 1 == iNum )
       {
          piSpecAttrKeyOnInputCurve = piSpecAttrAccessOnCC->GetAttrKey("Curve1");
       }
       else
       {
          piSpecAttrKeyOnInputCurve = piSpecAttrAccessOnCC->GetAttrKey("Curve2");
       }

       rc = E_FAIL;
       
       if ( NULL != piSpecAttrKeyOnInputCurve )
       {
          // Gets the curve
          *opiSpecOnCurve = piSpecAttrAccessOnCC->GetSpecObject(piSpecAttrKeyOnInputCurve);

          if ( NULL != *opiSpecOnCurve )
          {
              rc = S_OK ;
          } 

          piSpecAttrKeyOnInputCurve->Release();
          piSpecAttrKeyOnInputCurve = NULL ; 
       }
       
       piSpecAttrAccessOnCC->Release();
       piSpecAttrAccessOnCC = NULL ;

    }

    return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrCombinedCurve::SetDirection
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombinedCurve::SetDirection ( int iNum , CATISpecObject *ipiSpecOnDirection ) 
{
    // Gets a pointer on CATISpecAttrAccess 
    CATISpecAttrAccess * piSpecAttrAccessOnCC = NULL; 
    HRESULT rc = QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnCC);
    if ( SUCCEEDED(rc) ) 
    { 
       // Gets a pointer on the curve attribute
       CATISpecAttrKey * piSpecAttrKeyOnInputDirection = NULL;
       if ( 1 == iNum )
       {
          piSpecAttrKeyOnInputDirection = piSpecAttrAccessOnCC->GetAttrKey("Direction1");
       }
       else
       {
          piSpecAttrKeyOnInputDirection = piSpecAttrAccessOnCC->GetAttrKey("Direction2");
       }
    
       if ( NULL == piSpecAttrKeyOnInputDirection )
       {
           rc = E_FAIL ;
       }else
       {
      
          CATISpecObject_var spiSpecOnDirection(ipiSpecOnDirection);
             
          if ( NULL_var != spiSpecOnDirection )
          {
            // If the feature is a Feature BRep it must be aggregated by the CC
            CATIMfBRep *pIMfBRep = NULL ;
            rc = spiSpecOnDirection->QueryInterface(IID_CATIMfBRep, (void**) & pIMfBRep);
            if ( SUCCEEDED(rc) )
            {
               CATISpecObject * pFather = spiSpecOnDirection->GetFather() ;
               if ( NULL == pFather )
               {
                  CATIDescendants * pIDescendantsOnCC = NULL ;
                  rc = QueryInterface( IID_CATIDescendants , (void**) &pIDescendantsOnCC );
                                                
                  if ( SUCCEEDED(rc) )
                  {
                     pIDescendantsOnCC->Append(spiSpecOnDirection) ;

                     pIDescendantsOnCC->Release();
                     pIDescendantsOnCC = NULL ;
                  }
               }else 
               {
                  pFather->Release();
                  pFather = NULL ;
                  rc = E_FAIL ;
               }

               pIMfBRep->Release();
               pIMfBRep = NULL ;
       
            }else rc = S_OK ; // it's not an error 

            // Sets the curve as input of the CC
            if ( SUCCEEDED(rc) )
            {
               piSpecAttrAccessOnCC->SetSpecObject(piSpecAttrKeyOnInputDirection,spiSpecOnDirection);
            }

          }else
          {
              // The input curve pointer is null 
              piSpecAttrAccessOnCC->UnsetAttributeValue (piSpecAttrKeyOnInputDirection);
          }

          piSpecAttrKeyOnInputDirection->Release();
          piSpecAttrKeyOnInputDirection = NULL ;
       }

       piSpecAttrAccessOnCC->Release();
       piSpecAttrAccessOnCC = NULL ;
    }

    return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrCombinedCurve::GetDirection
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombinedCurve::GetDirection ( int iNum , CATISpecObject **opiSpecOnDirection )
{
    
    HRESULT rc = E_FAIL;

    if ( NULL == opiSpecOnDirection )
       return E_FAIL ;

    // Gets a pointer on CATISpecObject
    CATISpecAttrAccess *piSpecAttrAccessOnCC = NULL;
    rc = QueryInterface( IID_CATISpecAttrAccess , (void**) &piSpecAttrAccessOnCC );
    if ( SUCCEEDED(rc) )
    {
       CATISpecAttrKey * piSpecAttrKeyOnInputDirection = NULL;
       if ( 1 == iNum )
       {
          piSpecAttrKeyOnInputDirection = piSpecAttrAccessOnCC->GetAttrKey("Direction1");
       }
       else
       {
          piSpecAttrKeyOnInputDirection = piSpecAttrAccessOnCC->GetAttrKey("Direction2");
       }

       rc = E_FAIL;
       
       if ( NULL != piSpecAttrKeyOnInputDirection )
       {
          // Gets the curve
          *opiSpecOnDirection = piSpecAttrAccessOnCC->GetSpecObject(piSpecAttrKeyOnInputDirection);

          if ( NULL != *opiSpecOnDirection )
          {
              rc = S_OK ;
          } 

          piSpecAttrKeyOnInputDirection->Release();
          piSpecAttrKeyOnInputDirection = NULL ; 
       }
       
       piSpecAttrAccessOnCC->Release();
       piSpecAttrAccessOnCC = NULL ;

    }

    return rc ;
}

