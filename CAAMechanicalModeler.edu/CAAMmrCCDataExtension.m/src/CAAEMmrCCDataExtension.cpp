// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrCCDataExtension.cpp
// Provide implementation to interface
//      CAAIMmrCCDataExtension
//======================================================================================

// Local Framework
#include "CAAEMmrCCDataExtension.h"

// MecModInterfaces Framework
#include "CATIBRepAccess.h"
#include "CATIFeaturize.h"
#include "CATIMfBRep.h"

#include "CATICkeParm.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"     // needed to manage/query features
#include "CATISpecAttrAccess.h" // needed to access feature attributes
#include "CATISpecAttrKey.h"    // needed to access to the feature attribute values

CATImplementClass (CAAEMmrCCDataExtension ,
                   DataExtension       ,    
                   CATBaseUnknown      ,
                   CAAMmrCCDataExtension);

//-------------------------------------------------------------------------------------
// CAAEMmrCCDataExtension : constructor
//-------------------------------------------------------------------------------------
CAAEMmrCCDataExtension::CAAEMmrCCDataExtension():
CATBaseUnknown()
{
    
}

//-------------------------------------------------------------------------------------
// CAAEMmrCCDataExtension : destructor
//-------------------------------------------------------------------------------------
CAAEMmrCCDataExtension::~CAAEMmrCCDataExtension()
{
    
}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_CAAIMmrCCDataExtension.h" // needed to tie the implementation to its interface
TIE_CAAIMmrCCDataExtension( CAAEMmrCCDataExtension);

// To declare that CombinedCurve implements CAAIMmrCCDataExtension, insert 
// the following line in the interface dictionary:
//
// MmrCCDataExtension  CAAIMmrCCDataExtension  libCAAMmrCCDataExtension


//-------------------------------------------------------------------------------------
// Implements CAAIMmrCCDataExtension::SetGeomFeature
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCCDataExtension::SetGeomFeature (const CATBaseUnknown * ipGeomFeature )
{ 
  // Sets the geom feature - parts or integer of the Base Feature on the attribute "".
  // This geom feature will be the input for computing the length of the curve.

  if(ipGeomFeature ==NULL)
    return E_FAIL;

  CATISpecObject *pSpecOnThis = NULL;
  HRESULT rc = QueryInterface(IID_CATISpecObject, (void**) & pSpecOnThis);

  if(SUCCEEDED(rc) && pSpecOnThis!= NULL)
  {
    // Gets a pointer on CATISpecAttrAccess 
    CATISpecAttrAccess *piSpecAttrAccessOnDataExtension = NULL; 
    rc = QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnDataExtension);
    if (SUCCEEDED(rc) && piSpecAttrAccessOnDataExtension != NULL) 
    { 
      // Gets a pointer on the geom feature attributes... curve attribute
      CATISpecAttrKey *piKeyOnInputGeomFeature = NULL;

      piKeyOnInputGeomFeature = piSpecAttrAccessOnDataExtension -> GetAttrKey("GeomFeature");

      if(piKeyOnInputGeomFeature != NULL)
      {
        CATISpecObject *pSpecGeomFeature = NULL;
        rc = ((CATBaseUnknown*)(ipGeomFeature)) -> QueryInterface(IID_CATISpecObject, (void**) & pSpecGeomFeature);

        if(SUCCEEDED(rc) && pSpecGeomFeature!= NULL)
        {
          //We only need to value the "SpecObject Attribute"
          piSpecAttrAccessOnDataExtension  -> SetSpecObject(piKeyOnInputGeomFeature, pSpecGeomFeature);

          pSpecGeomFeature -> Release();
          pSpecGeomFeature = NULL;

          rc = S_OK;
        }
        else
        {
          // ipGeomFeature is a Feature BRep 
          // However, actually, BRep are not compliant with Extension
          rc = E_NOTIMPL;
        }
        piKeyOnInputGeomFeature -> Release(); //Release piKeyOnInputGeomFeature 
        piKeyOnInputGeomFeature = NULL;
      }
      piSpecAttrAccessOnDataExtension -> Release();
      piSpecAttrAccessOnDataExtension = NULL ;
    }
    else
      rc = E_FAIL;

    pSpecOnThis -> Release();
    pSpecOnThis = NULL;
  }
  return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrCCDataExtension::GetGeomFeature 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCCDataExtension::GetGeomFeature (CATISpecObject **ioGeomFeature )
{
  HRESULT rc = E_FAIL;

  // Gets a pointer on CATISpecAttrAccess
  CATISpecAttrAccess *piSpecAttrAccessOnDataExtension = NULL;
  rc = QueryInterface( IID_CATISpecAttrAccess , (void**) &piSpecAttrAccessOnDataExtension );
  if ( SUCCEEDED(rc) && piSpecAttrAccessOnDataExtension != NULL)
  {
    CATISpecAttrKey *piKeyOnGeomFeature = NULL;    
    piKeyOnGeomFeature = piSpecAttrAccessOnDataExtension -> GetAttrKey("GeomFeature");

    rc = E_FAIL;
    
    if(piKeyOnGeomFeature!= NULL)
    {
      //Get The GeomFeature associated to the CCDataExtension.
      *ioGeomFeature = piSpecAttrAccessOnDataExtension -> GetSpecObject(piKeyOnGeomFeature);
      if ( NULL != *ioGeomFeature )
      {
        rc = S_OK ;
      } 
      piKeyOnGeomFeature -> Release();
      piKeyOnGeomFeature = NULL;
    }
    piSpecAttrAccessOnDataExtension ->Release();
    piSpecAttrAccessOnDataExtension = NULL ;
  }
  
  return rc ;
}


//-------------------------------------------------------------------------------------
// Implements CAAIMmrCCDataExtension::AggregateParam 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCCDataExtension::AggregateParam (CATICkeParm_var ispParmToAggregate)
{
  HRESULT rc = E_FAIL;

  if(ispParmToAggregate == NULL_var)
    return rc;

  // Gets a pointer on CATISpecAttrAccess
  CATISpecAttrAccess *piSpecAttrAccessOnDataExtension = NULL;
  rc = QueryInterface( IID_CATISpecAttrAccess , (void**) &piSpecAttrAccessOnDataExtension );
  if ( SUCCEEDED(rc) && piSpecAttrAccessOnDataExtension != NULL)
  {
    CATISpecAttrKey *piKeyOnAggregatedParm = NULL;    
    piKeyOnAggregatedParm = piSpecAttrAccessOnDataExtension -> GetAttrKey("Length");

    rc = E_FAIL;
    
    if(piKeyOnAggregatedParm!= NULL)
    {
      if(piSpecAttrAccessOnDataExtension -> TestAttributeValue(piKeyOnAggregatedParm)!=TRUE)
      {
        CATISpecObject_var spSpecOnParam = ispParmToAggregate;
        if(!!spSpecOnParam)
        {
          piSpecAttrAccessOnDataExtension -> SetSpecObject(piKeyOnAggregatedParm, spSpecOnParam);
          rc = S_OK;
        }
      }
      piKeyOnAggregatedParm -> Release();
      piKeyOnAggregatedParm = NULL;
    }
    piSpecAttrAccessOnDataExtension ->Release();
    piSpecAttrAccessOnDataExtension = NULL ;
  }
  return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrCCDataExtension::GetValuatedParam 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCCDataExtension::GetValuatedParam (CATICkeParm_var& iospValuatedParm)
{
  HRESULT rc = E_FAIL;

  // Gets a pointer on CATISpecAttrAccess
  CATISpecAttrAccess *piSpecAttrAccessOnDataExtension = NULL;
  rc = QueryInterface( IID_CATISpecAttrAccess , (void**) &piSpecAttrAccessOnDataExtension );
  if ( SUCCEEDED(rc) && piSpecAttrAccessOnDataExtension != NULL)
  {
    CATISpecAttrKey *piKeyOnAggregatedParm = NULL;    
    piKeyOnAggregatedParm = piSpecAttrAccessOnDataExtension -> GetAttrKey("Length");

    rc = E_FAIL;
    
    if(piKeyOnAggregatedParm!= NULL)
    {
      if(piSpecAttrAccessOnDataExtension -> TestAttributeValue(piKeyOnAggregatedParm)==TRUE)
      {
        CATISpecObject_var spSpecOnParam;
        spSpecOnParam = piSpecAttrAccessOnDataExtension -> GetSpecObject(piKeyOnAggregatedParm);
        
        if(!!spSpecOnParam)
        {
          iospValuatedParm = spSpecOnParam;
          rc = S_OK;
        }
      }
      piKeyOnAggregatedParm -> Release();
      piKeyOnAggregatedParm = NULL;
    }
    piSpecAttrAccessOnDataExtension ->Release();
    piSpecAttrAccessOnDataExtension = NULL ;
  }
  return rc ;
}

