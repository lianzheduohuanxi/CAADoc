// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrCCDataExtension.cpp
// Provide implementation to interface
//      CAAIV5V6ExtMmrCCDataExtension
//
// Note : CAAEV5V6ExtMmrCCDataExtension is the same use case as CAAEMmrCCDataExtension. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//======================================================================================

#include "CATIAV5Level.h"

// Local Framework
#include "CAAEV5V6ExtMmrCCDataExtension.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// FeatureModelerExt Framework 
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass (CAAEV5V6ExtMmrCCDataExtension ,
                   DataExtension       ,    
                   CATBaseUnknown      ,
                   CAAV5V6ExtMmrCCDataExtension);

//-------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrCCDataExtension : constructor
//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCCDataExtension::CAAEV5V6ExtMmrCCDataExtension():
CATBaseUnknown()
{
  // Declare credentials for Combined Curve Application
  CATUnicodeString ClientId("CAAMmrUseCase");
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCCDataExtensionCatalog");
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  _CredentialForDataExt.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId);
  _CredentialForDataExt.RegisterAsCatalogOwner(CatalogName,ClientId);
   
}

//-------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrCCDataExtension : destructor
//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCCDataExtension::~CAAEV5V6ExtMmrCCDataExtension()
{}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_CAAIV5V6ExtMmrCCDataExtension.h" // needed to tie the implementation to its interface
TIE_CAAIV5V6ExtMmrCCDataExtension(CAAEV5V6ExtMmrCCDataExtension);

// To declare that CombinedCurve implements CAAIMmrCCDataExtension, insert 
// the following line in the interface dictionary:
//
// CAAV5V6ExtMmrCCDataExtension  CAAIV5V6ExtMmrCCDataExtension  libCAAV5V6ExtMmrCCDataExtension


//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCCDataExtension::SetGeomFeature
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCCDataExtension::SetGeomFeature(CATBaseUnknown * ipGeomFeature)
{ 
  // Sets the geom feature - parts or integer of the Base Feature on the attribute "".
  // This geom feature will be the input for computing the length of the curve.
  HRESULT rc = E_FAIL;
  
  if(ipGeomFeature ==NULL)
    return rc;

  // Get Data extension feature facade
  CATFmFeatureFacade FeatFacadeOnDataExtension(_CredentialForDataExt, this);

  // Get input feature facade
  CATFmFeatureFacade FeatFacadeOnInput;
  FeatFacadeOnInput = ipGeomFeature;

  // Valuate attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("V5V6GeomFeature");

  // Create an attribute value for the extension
  CATFmAttributeValue FmAttrValue;
  FmAttrValue.SetFeature(FeatFacadeOnInput);

  // Set the feature attribute
  rc = FeatFacadeOnDataExtension.SetValue(AttrKey, FmAttrValue);
 
  return rc;
}

//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCCDataExtension::GetGeomFeature 
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCCDataExtension::GetGeomFeature(CATBaseUnknown *&opGeomFeature)
{
  HRESULT rc = E_FAIL;

 // Get Data extension feature facade
  CATFmFeatureFacade FeatFacadeOnDataExtension(_CredentialForDataExt, this);

	// Valuate attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("V5V6GeomFeature");
  
  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnDataExtension.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
  {
    // Get the  feature facade
	  CATFmFeatureFacade FeatFacadeOnGeomFeat; 
    rc = FmAttrValue.GetFeature(FeatFacadeOnGeomFeat);

	  // Get the GeomFeature object
    if (SUCCEEDED(rc))
      rc = FeatFacadeOnGeomFeat.QueryInterfaceOnFeature(IID_CATBaseUnknown,(void**)& opGeomFeature);	   
  }
 
  return rc;
}


//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCCDataExtension::AggregateParam 
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCCDataExtension::AggregateParam(CATICkeParm_var ispParmToAggregate)
{
  HRESULT rc = E_FAIL;

  if (ispParmToAggregate == NULL_var)
    return rc;

  // Get Data extension feature facade
  CATFmFeatureFacade FeatFacadeOnDataExtension(_CredentialForDataExt, this);

  // Get input feature facade
  CATFmFeatureFacade FeatFacadeOnInput;
  FeatFacadeOnInput = ispParmToAggregate;

  // Valuate attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("V5V6Length");

  // Create an attribute value for the extension
  CATFmAttributeValue FmAttrValue;
  FmAttrValue.SetFeature(FeatFacadeOnInput);

  // Set the feature attribute
  rc = FeatFacadeOnDataExtension.SetValue(AttrKey, FmAttrValue);
 
  return rc;
}

//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCCDataExtension::GetValuatedParam 
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCCDataExtension::GetValuatedParam (CATICkeParm_var& iospValuatedParm)
{
  HRESULT rc = E_FAIL;

  // Get Data extension feature facade
  CATFmFeatureFacade FeatFacadeOnDataExtension(_CredentialForDataExt, this);

	// Valuate attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("V5V6Length");
  
  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnDataExtension.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
    iospValuatedParm = FmAttrValue.GetFeature();
  
  return rc;
}

