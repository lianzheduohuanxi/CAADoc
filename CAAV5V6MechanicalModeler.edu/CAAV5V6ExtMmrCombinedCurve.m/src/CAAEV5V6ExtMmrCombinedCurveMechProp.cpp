// COPYRIGHT DASSAULT SYSTEMES 2012
//=============================================================================
//
// CAAEV5V6ExtMmrCombinedCurveMechProp
//   Implementation of interface CATIMechanicalProperties for V5V6ExtCombinedCurve 
//
// Note :  CAAEV5V6ExtMmrCombinedCurveMechProp is the same use case as CAAEMmrCombinedCurveMechProp. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//=============================================================================

//local CAAV5V6MechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrCombinedCurveMechProp.h"

// VisualizationInterfaces Framework for V6
// Visualization Framework for V5
#include "CATIModelEvents.h"  // to update the display
#include "CATModify.h"        // to update the display

// ObjectModelerNavigator Framework
#include "CATIRedrawEvent.h"  // to refresh the specification tree

// FeatureModelerExt Framework 
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

//System Framework
#include "CATUnicodeString.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass(CAAEV5V6ExtMmrCombinedCurveMechProp, DataExtension, CATBaseUnknown, V5V6ExtCombinedCurve);

//-----------------------------------------------------------------------------
#include "TIE_CATIMechanicalProperties.h" 
TIE_CATIMechanicalProperties(CAAEV5V6ExtMmrCombinedCurveMechProp);
//-----------------------------------------------------------------------------

// To declare that V5V6ExtCombinedCurve implements CATIMechanicalProperties, insert 
// the following line in the interface dictionary:
//
// V5V6ExtCombinedCurve  CATIMechanicalProperties  libCAAV5V6MmrCombinedCurve


//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurveMechProp::CAAEV5V6ExtMmrCombinedCurveMechProp()
{
  cout <<" CAAEV5V6ExtMmrCombinedCurveMechProp::CAAEV5V6ExtMmrCombinedCurveMechProp" << endl;
  ReadStatus();
}

//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurveMechProp::~CAAEV5V6ExtMmrCombinedCurveMechProp()
{}


//-------------------------------------------------------------------------------------
// Implements CATIMechanicalProperties::IsInactive()
//-------------------------------------------------------------------------------------
int CAAEV5V6ExtMmrCombinedCurveMechProp::IsInactive() const
{
  return _status;
}

//-------------------------------------------------------------------------------------
// Implements CATIMechanicalProperties::Activate()
//-------------------------------------------------------------------------------------
void CAAEV5V6ExtMmrCombinedCurveMechProp::Activate()  
{
  cout <<" CAAEV5V6ExtMmrCombinedCurveMechProp::Activate" << endl;

  _status = 0;
  RefreshCombinedCurve();
}


//-------------------------------------------------------------------------------------
// Implements CATIMechanicalProperties::InActivate()
//-------------------------------------------------------------------------------------
void CAAEV5V6ExtMmrCombinedCurveMechProp::InActivate() 
{
  cout <<" CAAEV5V6ExtMmrCombinedCurveMechProp::InActivate" << endl;

  _status = 1;
  RefreshCombinedCurve();
}

//-------------------------------------------------------------------------------------
// Refresh the combined curve
// Modify the "Desactive" attribute to trigger update of display and tree. 
//-------------------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCombinedCurveMechProp::RefreshCombinedCurve()
{
  HRESULT rc = E_FAIL;

   // Get credentials for Combined Curve application
  CATUnicodeString ClientId("SAMPLES");
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCombinedCurveCatalog");
  CATFmCredentials CredentialForCC;
  rc = CredentialForCC.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId);
  if (SUCCEEDED(rc))
		rc = CredentialForCC.RegisterAsCatalogOwner(CatalogName,ClientId);

  if (FAILED(rc))
    return rc;
  
  // Attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("V5V6Desactive");

  // Get the Combined Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCombinedCurve(CredentialForCC, this);

  // Modify the attribute value
  CATFmAttributeValue FmAttrValue;
  FmAttrValue.SetInteger(_status);
  rc = FeatFacadeOnCombinedCurve.SetValue(AttrKey, FmAttrValue);
  if (FAILED(rc))
    return rc;

  // Refresh the specification tree to update the mask
  CATIRedrawEvent * piRedrawEvent = NULL;                
  rc = QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
  if ( SUCCEEDED(rc) )
  {
    piRedrawEvent->Redraw();
    piRedrawEvent->Release();
    piRedrawEvent = NULL ;
  }
  
  //Update the display
  CATIModelEvents * piModelEvent = NULL;                
  rc = QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
    
  if (SUCCEEDED(rc))
  {       
    CATModify notif = this;
    piModelEvent->Dispatch(notif);
         
    piModelEvent->Release();
    piModelEvent=NULL;
  }	 

  return rc;
}

//-------------------------------------------------------------------------------------
// Read the "Desactive" attribute 
//-------------------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCombinedCurveMechProp::ReadStatus()
{
  HRESULT rc = E_FAIL;
  _status = 0;

  // Get credentials for Combined Curve application
  CATUnicodeString ClientId("SAMPLES");
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCombinedCurveCatalog");
  CATFmCredentials CredentialForCC;
	rc = CredentialForCC.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, ClientId);
  if (FAILED(rc))
    return rc;
  rc = CredentialForCC.RegisterAsCatalogOwner(CatalogName,ClientId);
  if (FAILED(rc))
    return rc;
 
  // Attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("V5V6Desactive");

  // Get the Combined Curve feature facade
  CATFmFeatureFacade FeatFacadeOnCombinedCurve(CredentialForCC, this);

  // Get the attribute value
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnCombinedCurve.GetValue(AttrKey, FmAttrValue);
  
  if (SUCCEEDED(rc))
  {
    int ActiveStatus = 0;
    rc = FmAttrValue.GetInteger(ActiveStatus);
    if (SUCCEEDED(rc))
      _status = ActiveStatus;
  }

  return rc;
}
