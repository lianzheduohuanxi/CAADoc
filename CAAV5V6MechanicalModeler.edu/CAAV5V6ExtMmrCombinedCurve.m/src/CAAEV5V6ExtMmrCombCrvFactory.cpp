// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrCombCrvFactory.cpp 
//  Provide implementation to interface CAAIV5V6ExtMmrCombCrvFactory
//
// Note : CAAEV5V6ExtMmrCombCrvFactory is the same use case as CAAEMmrCombCrvFactory. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CATIAV5Level.h"

// local CAAV5V6MechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrCombCrvFactory.h"
#include "CAAIV5V6ExtMmrCombinedCurve.h" 

// FeatureModelerExt Framework 
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"

// CATMecModExtendItf Framework
#include "CATIMmiAlgoConfigServices.h"
#include "CATIMmiFeatureAttributes.h"
#include "CATMmiExtendServicesFactory.h" 

// CATMecModUseItf Framework in V6
// InteractiveInterfaces Framework in V5
#include "CATIInputDescription.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// System Framework
#include "CATUnicodeString.h"


CATImplementClass(CAAEV5V6ExtMmrCombCrvFactory, DataExtension, CATBaseUnknown, CATPrtCont);

//---------------------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombCrvFactory : constructor
//---------------------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombCrvFactory::CAAEV5V6ExtMmrCombCrvFactory():
CATBaseUnknown()
{}

//---------------------------------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombCrvFactory : destructor
//---------------------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombCrvFactory::~CAAEV5V6ExtMmrCombCrvFactory()
{}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIV5V6ExtMmrCombCrvFactory.h" // needed to tie the implementation to its interface
TIE_CAAIV5V6ExtMmrCombCrvFactory(CAAEV5V6ExtMmrCombCrvFactory);

// 
// To declare that GSMTool implements CAAIV5V6ExtMmrCombCrvFactory, 
// insert the following line in the interface dictionary:
//
// GSMTool  CAAIV5V6ExtMmrCombCrvFactory    libCAAV5V6ExtMmrCombinedCurve



//---------------------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrCombCrvFactory::CreateCombinedCurve
//---------------------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombCrvFactory::CreateCombinedCurve(CATBaseUnknown *ipCurve1,
                                                   CATBaseUnknown *ipDirection1,
                                                   CATBaseUnknown *ipCurve2,
                                                   CATBaseUnknown *ipDirection2,
                                                   CAAIV5V6ExtMmrCombinedCurve *& opCombinedCurve)  
{
    
  //===============================================================================================
  //
  //  What does the factory do ?
  //
  //     1- Creates a Combined Curve instance
  //     2- Subscribes to repository for Configuration Data Storage
  //     3- Gets Feature Type Information for BackUp / StartUp management  
  //     4- Sets values for the attributes of the instance
  //
  //===============================================================================================
    
  HRESULT rc = E_FAIL;

  //===============================================================================================
  //
  // 1- Creates a Combined Curve instance
  //
  //===============================================================================================
   
  // Get credential for Combined Curve application
  CATUnicodeString ClientId("SAMPLES");
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCombinedCurveCatalog");
  CATFmCredentials CredentialForCC;
  rc = CredentialForCC.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId); 
  if (SUCCEEDED(rc))
    rc = CredentialForCC.RegisterAsCatalogOwner(CatalogName,ClientId);
  
  if (FAILED(rc))
	return rc;

  // Get container facade  
  CATFmContainerFacade CombinedCurveContainerFacade(CredentialForCC, this);

  // Get startup facade
  CATUnicodeString StartupName = "`V5V6ExtCombinedCurve`@`CAAV5V6ExtMmrCombinedCurveCatalog.CATfct`";
  CATFmStartUpFacade CombinedCurveStartUpFacade(CredentialForCC, StartupName);
  
  // Instanciate a Combined Curve
  CATFmFeatureFacade CombinedCurveFeatFacade;
  rc = CombinedCurveStartUpFacade.InstantiateIn(CombinedCurveContainerFacade,CombinedCurveFeatFacade);

  if (FAILED(rc))
    return rc;

  //===============================================================================================
  //
  // 2- Subscribes to repository for Configuration Data Storage
  //
  //===============================================================================================

  // Get CATIMmiMechanicalFeature pointer on the CombinedCurve object
  CATIMmiMechanicalFeature *piMechFeat = NULL;
  rc = CombinedCurveFeatFacade.QueryInterfaceOnFeature(IID_CATIMmiMechanicalFeature,(void**)&piMechFeat);

  if (SUCCEEDED(rc) && piMechFeat)
  {
    // Create CATIMmiAlgoConfigServices component
	CATIMmiAlgoConfigServices *piAlgoConfigServices = NULL;  
    rc = CATMmiExtendServicesFactory::CreateAlgoConfigServicesAccess(piAlgoConfigServices);
	
	// Create configuration data
	if (SUCCEEDED(rc) && piAlgoConfigServices)
	{
	  rc = piAlgoConfigServices->CreateConfigurationData(piMechFeat);

	  piAlgoConfigServices->Release();
	  piAlgoConfigServices = NULL;
	}
	
	piMechFeat->Release();
	piMechFeat = NULL;
  }
	
  if (FAILED(rc))
	return rc;
	
  //===============================================================================================
  //
  // 3- Gets Feature Type Information for BackUp / StartUp management
  //
  //===============================================================================================

  // Get Combined Curve object
  CATBaseUnknown_var spCombinedCurve = CombinedCurveFeatFacade.GetFeature();

  CATIInputDescription_var spInputDescriptionOnCombinedCurve = spCombinedCurve;
	
  if (spInputDescriptionOnCombinedCurve != NULL_var)
  {
	CATIInputDescription::FeatureType Feature_type = CATIInputDescription::FeatureType_Unset;
    rc = spInputDescriptionOnCombinedCurve->GetFeatureType(Feature_type);
 
	if (SUCCEEDED(rc))
	{
	  // Create CATIMmiFeatureAttributes component
	  CATIMmiFeatureAttributes *piFeatureAttributes = NULL;  
      rc = CATMmiExtendServicesFactory::CreateFeatureAttributesAccess(piFeatureAttributes);

	  if (SUCCEEDED(rc) && piFeatureAttributes)
	  {
		// Set the feature type
	    rc = piFeatureAttributes->SetFeatureType(spCombinedCurve, Feature_type);

	    piFeatureAttributes->Release();
		piFeatureAttributes = NULL;
	  }
	}
  }
	
  if (FAILED(rc))
	return rc;

  //===============================================================================================
  //
  // 4- Sets values for the attributes of the combined curve
  //
  //===============================================================================================
    
  // Get CAAIMmrCombinedCurve pointer on the CombinedCurve object
  rc = CombinedCurveFeatFacade.QueryInterfaceOnFeature(IID_CAAIV5V6ExtMmrCombinedCurve,(void**)&opCombinedCurve);
	
  // Set the 2 curves and 2 directions
  if (SUCCEEDED(rc) && opCombinedCurve) 
  {  
    rc = opCombinedCurve->SetCurve(1, ipCurve1);
	if (SUCCEEDED(rc))
	{
      rc = opCombinedCurve->SetCurve(2, ipCurve2);
	  if (SUCCEEDED(rc))
	  {
        rc = opCombinedCurve->SetDirection(1, ipDirection1);
	    if (SUCCEEDED(rc))
          rc = opCombinedCurve->SetDirection(2, ipDirection2);
	  }
	}
  }
	
  if (FAILED(rc) && opCombinedCurve)
  {
    opCombinedCurve->Release();
    opCombinedCurve = NULL;
  }

  return rc;
    
}
