// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrCombinedCurve.cpp
// Provide implementation to interface
//      CAAIV5V6ExtMmrCombinedCurve : Enables to set/get feature attributes of V5V6ExtCombinedCurve.
//
// Note : CAAEV5V6ExtMmrCombinedCurve is the same use case as CAAEMmrCombinedCurve. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//======================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrCombinedCurve.h"

// CATMecModUseItf Framework 
#include "CATIMmiUseMfBRep.h"
#include "CATIMmiUseBasicInsertion.h"

// CATMecModLiveUseItf Framework 
#include "CATIMmiMechanicalFeature.h"

// FeatureModelerExt Framework  
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

//System Framework 
#include "CATUnicodeString.h"


CATImplementClass (CAAEV5V6ExtMmrCombinedCurve, DataExtension, CATBaseUnknown, V5V6ExtCombinedCurve);

//-------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurve : constructor
//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurve::CAAEV5V6ExtMmrCombinedCurve():
CATBaseUnknown()
{
  // Declare credentials for Combined Curve Application
  CATUnicodeString ClientId("SAMPLES");
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCombinedCurveCatalog");
  _CredentialForCC.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId);
  _CredentialForCC.RegisterAsCatalogOwner(CatalogName,ClientId);
  
}

//-------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurve : destructor
//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurve::~CAAEV5V6ExtMmrCombinedCurve()
{}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_CAAIV5V6ExtMmrCombinedCurve.h" // needed to tie the implementation to its interface
TIE_CAAIV5V6ExtMmrCombinedCurve( CAAEV5V6ExtMmrCombinedCurve);

// To declare that V5V6ExtCombinedCurve implements CAAIV5V6ExtMmrCombinedCurve, 
// insert the following line in the interface dictionary:
//
// V5V6ExtCombinedCurve  CAAIV5V6ExtMmrCombinedCurve  libCAAV5V6MmrCombinedCurve


//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCombinedCurve::SetCurve
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombinedCurve::SetCurve(int iNum , CATBaseUnknown *ipCurve) 
{    
  HRESULT rc = S_OK;

  //Check input
  if (ipCurve == NULL)
    return E_FAIL;
   
  // Get Combined Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCombinedCurve(_CredentialForCC, this);

  // Get input Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCurve;
  FeatFacadeOnCurve = ipCurve;
	
  // Valuate attribute key
  CATFmAttributeName AttrKey;
  if (1 == iNum)
    AttrKey = CATFmAttributeName("V5V6Curve1");
  else
    AttrKey = CATFmAttributeName("V5V6Curve2");

  // Create an attribute value for the Curve
  CATFmAttributeValue FmAttrValue;
  FmAttrValue.SetFeature(FeatFacadeOnCurve);

  // If the feature is a BRep feature it needs to be aggregated by the V5V6ExtCombinedCurve
  CATIMmiUseMfBRep_var spMfBRep = ipCurve; 
  if (NULL_var != spMfBRep)
  {
    CATIMmiUseBasicInsertion_var spBasicInsertion = ipCurve; 
    CATIMmiMechanicalFeature_var spTarget = this;
	     
    if (spBasicInsertion != NULL_var && spTarget != NULL_var)
      rc = spBasicInsertion->InsertInside(spTarget);
    else
      rc = E_FAIL;
  }
 
  // Set the feature attribute
  if (SUCCEEDED(rc))
    rc = FeatFacadeOnCombinedCurve.SetValue(AttrKey, FmAttrValue);
 
  return rc;
}

//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCombinedCurve::GetCurve
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombinedCurve::GetCurve(int iNum ,CATBaseUnknown *&opCurve) 
{
  HRESULT rc = E_FAIL;

  // Get Combined Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCombinedCurve(_CredentialForCC, this);

  // Valuate attribute key
  CATFmAttributeName AttrKey;
  if ( 1 == iNum )
    AttrKey = CATFmAttributeName("V5V6Curve1");
  else
    AttrKey = CATFmAttributeName("V5V6Curve2");

  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnCombinedCurve.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
  {
    // Get the Curve feature facade
	CATFmFeatureFacade FeatFacadeOnCurve; 
    rc = FmAttrValue.GetFeature(FeatFacadeOnCurve);

	// Get the Curve object
    if (SUCCEEDED(rc))
      rc = FeatFacadeOnCurve.QueryInterfaceOnFeature(IID_CATBaseUnknown,(void**)& opCurve);	   
  }
  return rc; 
}

//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCombinedCurve::SetDirection
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombinedCurve::SetDirection(int iNum, CATBaseUnknown *ipDirection) 
{
	HRESULT rc = S_OK;

  //Check input
  if (ipDirection == NULL)
    return E_FAIL;

  // Get Combined Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCombinedCurve(_CredentialForCC, this);

  // Get input Direction feature facade
  CATFmFeatureFacade FeatFacadeOnDirection;
  FeatFacadeOnDirection = ipDirection;

  // Valuate attribute key
  CATFmAttributeName AttrKey;
  if (1 == iNum)
    AttrKey = CATFmAttributeName("V5V6Dir1");
  else
    AttrKey = CATFmAttributeName("V5V6Dir2");

  // Create an attribute value for the Line
  CATFmAttributeValue FmAttrValue;
  FmAttrValue.SetFeature(FeatFacadeOnDirection);

  // If the feature is a Feature BRep it must be aggregated by the V5V6ExtCombinedCurve
  CATIMmiUseMfBRep_var spMfBRep = ipDirection;
  if (NULL_var != spMfBRep)
  {
    CATIMmiUseBasicInsertion_var spBasicInsertion = ipDirection; 
    CATIMmiMechanicalFeature_var spTarget = this;
    if (spBasicInsertion != NULL_var && spTarget != NULL_var)
      rc = spBasicInsertion->InsertInside(spTarget);
    else
	  rc = E_FAIL;   
  }
 
  // Set the feature attribute
  if (SUCCEEDED(rc))
    rc = FeatFacadeOnCombinedCurve.SetValue(AttrKey, FmAttrValue);
  
  return rc;
}

//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCombinedCurve::GetDirection
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombinedCurve::GetDirection(int iNum, CATBaseUnknown *&opDirection)
{
  HRESULT rc = E_FAIL;

  // Get Combined Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCombinedCurve(_CredentialForCC, this);

  // Valuate attribute key
  CATFmAttributeName AttrKey;
  if ( 1 == iNum )
    AttrKey = CATFmAttributeName("V5V6Dir1");
  else
    AttrKey = CATFmAttributeName("V5V6Dir2");

  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnCombinedCurve.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
  {
	// Get Direction feature facade
	CATFmFeatureFacade FeatFacadeOnDirection; 
    rc = FmAttrValue.GetFeature(FeatFacadeOnDirection);

	// Get Direction object
    if (SUCCEEDED(rc))
      rc = FeatFacadeOnDirection.QueryInterfaceOnFeature(IID_CATBaseUnknown,(void**)& opDirection);  
  }

  return rc;
}
                              
