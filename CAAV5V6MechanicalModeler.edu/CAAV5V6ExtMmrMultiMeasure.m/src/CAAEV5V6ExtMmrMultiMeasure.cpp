// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrMultiMeasure.cpp
// Provide implementation to interface
//      CAAIMmrMultiMeasure
//
// Note : CAAEV5V6ExtMmrMultiMeasure is the same use case as CAAEMmrMultiMeasure. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//======================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrMultiMeasure.h"

// CATMecModUseItf Framework
#include "CATIMmiUseGeometricalElement.h"
#include "CATI3DGeometricalElement.h"
#include "CATIMmiUseBRepAccess.h"
#include "CATIMmiUseFeaturize.h"
#include "CATIMmiUseMfBRep.h"

// FeatureModelerExt framework 
#include "CATFmContainerFacade.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"

// System Framework
#include "CATBaseUnknown.h"     

// KnowledgeIneterfaces
#include "CATICkeParm.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass(CAAEV5V6ExtMmrMultiMeasure, DataExtension, CATBaseUnknown, CAAV5V6ExtMmrMultiMeasure);

//-------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasure : constructor
//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasure::CAAEV5V6ExtMmrMultiMeasure(): CATBaseUnknown()
{
  // Declare credentials for Combined Curve Application
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  CATUnicodeString ClientId("CAAMmrUseCaseForMechanicalSetsAndElements");
  CATUnicodeString CatalogName("CAAV5V6ExtMmrMultiMeasureCatalog");
  _CredentialForMultiMeasure.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId);
  _CredentialForMultiMeasure.RegisterAsCatalogOwner(CatalogName,ClientId);
}

//-------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasure : destructor
//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasure::~CAAEV5V6ExtMmrMultiMeasure()
{}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_CAAIV5V6ExtMmrMultiMeasure.h" // needed to tie the implementation to its interface
TIE_CAAIV5V6ExtMmrMultiMeasure(CAAEV5V6ExtMmrMultiMeasure);

// To declare that CombinedCurve implements CAAIMmrMultiMeasure, insert 
// the following line in the interface dictionary:
//
// CAAV5V6ExtMmrMultiMeasure  CAAIV5V6ExtMmrMultiMeasure  libCAAV5V6ExtMmrMultiMeasure


//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrMultiMeasure::SetGeomFeature
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrMultiMeasure::SetInputGeomFeature (CATBaseUnknown * ipGeomFeature )
{ 
  // Sets the geom feature - The Feature to measure.
  // This geom feature will be the input for computing the length, area and volum, if it is possible.

  HRESULT rc = E_FAIL;

  if (ipGeomFeature == NULL)
    return rc;
  
  // Get feature facade on MultiMeasure
  CATFmFeatureFacade FeatFacadeOnMultiMeasure(_CredentialForMultiMeasure, this);

  // Valuate attribute keys
  CATFmAttributeName AttrKey("V5V6FeatureToMeasure");;
  CATFmAttributeName BRepAttrKey("V5V6BRepFeatureToMeasure");

  // Unset old values
  rc = FeatFacadeOnMultiMeasure.UnsetValue(AttrKey);
  rc = FeatFacadeOnMultiMeasure.UnsetValue(BRepAttrKey);

  // Is the input a geometrical element?
  CATI3DGeometricalElement_var spGeom = ipGeomFeature; 
  //CATIMmiUseGeometricalElement_var spGeom = ipGeomFeature;
  if (spGeom != NULL_var)
  {	
	// Get feature facade on input geometry
    CATFmFeatureFacade FeatFacadeOnGeom;
	FeatFacadeOnGeom = ipGeomFeature;
		
	// Set attribut value for the geometry
    CATFmAttributeValue FmAttrValue;
    FmAttrValue.SetFeature(FeatFacadeOnGeom);

	// Set the feature attribute
    rc = FeatFacadeOnMultiMeasure.SetValue(AttrKey, FmAttrValue);
  }
  else
  {
	// Is the input a BRepAccess? 
    CATIMmiUseBRepAccess_var spBRepAccess = ipGeomFeature;
	if (spBRepAccess != NULL_var)
	{
	  // Featurize BRepAccess
      //    Don't forget : BRepAccess are not persistant 
      //    ---> Featurize it to keep it in the model  
      CATIMmiUseFeaturize_var spFeaturize = ipGeomFeature;
	  if (spFeaturize != NULL_var)
	  {
		// Featurize(R) to keep (R)elimited surface in order to compute the real measure
		CATIMmiUseMfBRep_var spBRepFeature = NULL_var;
		rc = spFeaturize->Featurize(spBRepFeature, MfSelectingFeatureSupport, CATMmrRelimited);
		if (SUCCEEDED(rc) && spBRepFeature != NULL_var)
		{
 		  // Get feature facade on featurized object
		  CATFmFeatureFacade FeatFacadeOnBRep;
          FeatFacadeOnBRep = spBRepFeature;

		  // Set value for BRep
          CATFmAttributeValue BRepFmAttrValue;
          BRepFmAttrValue.SetFeature(FeatFacadeOnBRep);
					 
		  // Set the feature attribute
          rc = FeatFacadeOnMultiMeasure.SetValue(BRepAttrKey, BRepFmAttrValue);
            
		  if (SUCCEEDED(rc))
		  {
			// Set value for MultiMeasure 
			CATFmAttributeValue MultiMeasureFmAttrValue;
            MultiMeasureFmAttrValue.SetFeature(FeatFacadeOnMultiMeasure);

		    // Set redirection
			rc = FeatFacadeOnMultiMeasure.SetRedirectedValuation(AttrKey, MultiMeasureFmAttrValue, BRepAttrKey); 
		  }
		}     
	  }
	}
  }	
  return rc;
}

//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrMultiMeasure::GetGeomFeature 
//-------------------------------------------------------------------------------------
  
HRESULT CAAEV5V6ExtMmrMultiMeasure::GetGeomFeature (CATBaseUnknown *& opGeomFeature)
{
  cout <<" CAAEV5V6ExtMmrMultiMeasure::GetGeomFeature" << endl ;
   
  HRESULT rc = E_FAIL;
  opGeomFeature = NULL;
  
  // Get Multi Measure feature facade
  CATFmFeatureFacade FeatFacadeOnMultiMeasure(_CredentialForMultiMeasure, this);

  // Valuate attribute key
  CATFmAttributeName AttrKey;
  AttrKey = CATFmAttributeName("V5V6FeatureToMeasure");
	    
  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnMultiMeasure.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
  {
    // Get the geometry feature facade
	CATFmFeatureFacade FeatFacadeOnGeom; 
    rc = FmAttrValue.GetFeature(FeatFacadeOnGeom);

	// Get the geometry object
	if (SUCCEEDED(rc))
	  rc = FeatFacadeOnGeom.QueryInterfaceOnFeature(IID_CATBaseUnknown,(void**)& opGeomFeature);
  }

  return rc;
}


//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::GetLengthParameter 
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrMultiMeasure::GetLengthParameter (CATICkeParm_var &oLengthParm) 
{
  HRESULT rc = E_FAIL;
  oLengthParm = NULL_var;

  // Get Multi Measure feature facade
  CATFmFeatureFacade FeatFacadeOnMultiMeasure(_CredentialForMultiMeasure, this);

  // Valuate attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("ComputedLength");
  
  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnMultiMeasure.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
  oLengthParm = FmAttrValue.GetFeature();

  return rc ;
}
//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::GetWetAreaParameter 
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrMultiMeasure::GetWetAreaParameter (CATICkeParm_var &oWetAreaParm) 
{
  HRESULT rc = E_FAIL;
  oWetAreaParm = NULL_var;
	
  // Get Multi Measure feature facade
  CATFmFeatureFacade FeatFacadeOnMultiMeasure(_CredentialForMultiMeasure, this);

  // Valuate attribute key
  CATFmAttributeName AttrKey = CATFmAttributeName("ComputedWetArea");
  
  // Get the feature attribute
  CATFmAttributeValue FmAttrValue;
  rc = FeatFacadeOnMultiMeasure.GetValue(AttrKey, FmAttrValue);

  if (SUCCEEDED(rc))
  oWetAreaParm = FmAttrValue.GetFeature();
 
  return rc;
}
//-------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrMultiMeasure::GetVolumeParameter 
//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrMultiMeasure::GetVolumeParameter (CATICkeParm_var &oVolumeParm) 
{
   HRESULT rc = E_FAIL;
   oVolumeParm = NULL_var;

	
   // Get Multi Measure feature facade
   CATFmFeatureFacade FeatFacadeOnMultiMeasure(_CredentialForMultiMeasure, this);

   // Valuate attribute key
   CATFmAttributeName AttrKey = CATFmAttributeName("ComputedVolume");
  
   // Get the feature attribute
   CATFmAttributeValue FmAttrValue;
   rc = FeatFacadeOnMultiMeasure.GetValue(AttrKey, FmAttrValue);

   if (SUCCEEDED(rc))
   oVolumeParm = FmAttrValue.GetFeature();

   return rc;
}

