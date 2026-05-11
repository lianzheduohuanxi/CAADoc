// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAV5V6ExtMmrAddCCExtension :
// Manages the instantiation of the data extension
// 
// Note :  CAAV5V6ExtMmrAddCCExtension is the same use case as  CAAMmrAddCCExtension. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//=================================================================================================

// CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrAddCCExtension.h"
#include "CAAIV5V6ExtMmrCCDataExtension.h" // needed by the factory to return a pointer on this interface

// CATMecModUseItf Framework
#include "CATIMmiUseBRepAccess.h"  //For BRepAccess Management

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// ObjectModelerNavigator Framework
#include "CATIRedrawEvent.h"

// Visualization Framework in V5 
// VisualizationInterfaces Framework in V6  
#include "CATIModelEvents.h"
#include "CATCreate.h"   

// System Framework 
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATBaseUnknown.h"

// FeatureModelerExt 
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeValue.h"

// C++ Standard library
#include "iostream.h"


//------------------------------------------------------------------------------------------------

HRESULT CAAV5V6ExtMmrAddCCExtension( const CATBaseUnknown *iBaseFeature,CAAIV5V6ExtMmrCCDataExtension **ioMmrCCDataExtension)
                                                                    
{
	cout <<" CAAV5V6ExtMmrAddCCExtension" << endl;
    
	HRESULT rc = S_OK;

  // Check arguments
	if ((NULL == iBaseFeature) || (NULL==ioMmrCCDataExtension))
		return E_FAIL;
	
  // Initialize
  CATBaseUnknown * pBaseFeatureModifiable = (CATBaseUnknown *) iBaseFeature;
  (*ioMmrCCDataExtension) = NULL;
	
  // Declare credentials 
  CATFmCredentials MyCredential;
  CATUnicodeString ClientId("CAAMmrUseCase");
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCCDataExtensionCatalog");
  rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId); 
  rc = MyCredential.RegisterAsCatalogOwner(CatalogName,ClientId);
  
  // Check base feature
  CATIMmiMechanicalFeature_var spBaseFeature = pBaseFeatureModifiable;
  if (spBaseFeature == NULL_var)
  { 
    // Is it a selecting object?
    CATIMmiUseBRepAccess *pBRepAccess = NULL;
    rc = pBaseFeatureModifiable->QueryInterface(IID_CATIMmiUseBRepAccess, ( void**) &pBRepAccess);
    if (SUCCEEDED(rc))
    {
      rc = pBRepAccess->GetBRepSelectingFeature(spBaseFeature);
      
      pBRepAccess->Release();
      pBRepAccess = NULL;
    }
  }
  if (spBaseFeature == NULL_var)
    return E_FAIL;

  // Create the extension on the base feature
  CATFmFeatureFacade FeatFacadeOnCC(MyCredential, spBaseFeature);
  
  CATString ExtensionName("`CAAV5V6ExtMmrCCDataExtension`@`CAAV5V6ExtMmrCCDataExtensionCatalog.CATfct`");
  CATFmAttributeValue DataExtValue;
  rc = FeatFacadeOnCC.AddExtension(ExtensionName, DataExtValue);
  CATFmFeatureFacade FeatFacadeOnDataExt(MyCredential, DataExtValue);

  // Initialize the new extended feature 
  if (SUCCEEDED(rc))
  {
   	rc = FeatFacadeOnDataExt.QueryInterfaceOnFeature(IID_CAAIV5V6ExtMmrCCDataExtension,(void**) ioMmrCCDataExtension);
    if (SUCCEEDED(rc))
    {
      rc = (*ioMmrCCDataExtension)->SetGeomFeature(spBaseFeature);

      //Update
      if (SUCCEEDED(rc))
      {
        rc = FeatFacadeOnDataExt.IsUpToDate();
        if (rc == S_FALSE)
          rc = FeatFacadeOnDataExt.Update();
      }
    }
  }

  // Connection for visualisation
  if (SUCCEEDED(rc) && (NULL!=(*ioMmrCCDataExtension)))
  {
    CATIModelEvents_var spModelEvtBaseFeature = pBaseFeatureModifiable;
    if (NULL_var != spModelEvtBaseFeature)
    {
      spModelEvtBaseFeature->ConnectTo((*ioMmrCCDataExtension)) ;
    }
  }

  // Retrieve the Part feature
  CATIMmiMechanicalFeature_var spMechFeatOnBase = pBaseFeatureModifiable;
  CATIMmiMechanicalFeature_var PartFeat;
  if (NULL_var != spMechFeatOnBase)
  {
    rc = spMechFeatOnBase->GetMechanicalPart(PartFeat);
  }

  // CATCreate Event to visualize it -> child of Part
  CATIModelEvents_var spModelEvtExtendedFeature = (*ioMmrCCDataExtension) ;
  if ( SUCCEEDED(rc) && (NULL_var != spModelEvtExtendedFeature ) && (NULL_var != PartFeat))
  {
	// The second argument of the method must be the Part since it is the Part 
	// which contains the visu of the extended feature.
	// 
	CATCreate notif((*ioMmrCCDataExtension),PartFeat);
    spModelEvtExtendedFeature->Dispatch(notif);
  }

  // update the Spec tree
  CATIRedrawEvent_var spDrwEvt = PartFeat;
  
  if ( NULL_var != spDrwEvt )
  {
    spDrwEvt->Redraw();
  }

  return rc; 
}

