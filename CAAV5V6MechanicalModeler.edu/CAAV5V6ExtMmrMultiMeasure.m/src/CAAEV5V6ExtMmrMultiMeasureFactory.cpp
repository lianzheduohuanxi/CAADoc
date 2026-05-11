// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrMultiMeasureFactory.cpp
// Provide implementation to interface
//    CAAIV5V6ExtMmrMultiMeasureFactory
//
// Note : CAAEV5V6ExtMmrMultiMeasureFactory is the same use case as CAAEMmrMultiMeasureAndMeasureSetFactory. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrMultiMeasureFactory.h"
#include "CAAIV5V6ExtMmrMultiMeasure.h" 

// CATMecModUseItf Framework Framework
#include "CATIMmiUseBasicInsertion.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// CATMecModExtendItf Framework
#include "CATIMmiAlgoConfigServices.h"
#include "CATMmiExtendServicesFactory.h"

//FeatureModelerExt framework 
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"

// KnowledgeInterfaces Framework
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"


#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// DataCommonProtocolUse
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

#else
//============================================== 
// V5 only
//==============================================

// ObjectModelerSystem Framework
#include "LifeCycleObject.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#endif

CATImplementClass (CAAEV5V6ExtMmrMultiMeasureFactory, DataExtension, CATBaseUnknown, CATPrtCont);

//---------------------------------------------------------------------------------------------------
// CAAEMmrMultiMeasureAndMeasureSetFactory : constructor
//---------------------------------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureFactory::CAAEV5V6ExtMmrMultiMeasureFactory(): CATBaseUnknown()
{
}

//---------------------------------------------------------------------------------------------------
// CAAEMmrMultiMeasureAndMeasureSetFactory : destructor
//---------------------------------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureFactory::~CAAEV5V6ExtMmrMultiMeasureFactory()
{    
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIV5V6ExtMmrMultiMeasureFactory.h" // needed to tie the implementation to its interface
TIE_CAAIV5V6ExtMmrMultiMeasureFactory(CAAEV5V6ExtMmrMultiMeasureFactory);

// 
// To declare implementation of CAAIV5V6ExtMmrMultiMeasureFactory, insert 
// the following line in the interface dictionary:
//
// CATPrtCont  CAAIV5V6ExtMmrMultiMeasureFactory    libCAAV5V6ExtMmrMultiMeasure

//---------------------------------------------------------------------------------------------------
// Implements CAAIV5V6ExtMmrMultiMeasureAndMeasureSetFactory::CreateDataExtension
//---------------------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrMultiMeasureFactory::CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure,
                                                                 CATBaseUnknown *&opMultiMeasureInstance )
{
   //===============================================================================================
   //
   //  What does the factory do ?
   //
   //     o -1- Creates a MmrMultiMeasure instance
   //     o -2- Subscribes to repository for Configuration Data Storage
   //     o -3- Sets default values for the attributes of the instance
   //
   //===============================================================================================

   HRESULT rc = S_OK;

   //===============================================================================================
   //
   // -1- Creates a MmrMultiMeasure instance
   //
   //===============================================================================================

   // Get credential for MultiMeasure application 
   CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
   CATUnicodeString ClientId = "CAAMmrUseCaseForMechanicalSetsAndElements";
   CATUnicodeString CatalogName = "CAAV5V6ExtMmrMultiMeasureCatalog";
   CATFmCredentials CredentialForMultiMeasure;
   rc = CredentialForMultiMeasure.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId);
   if (FAILED(rc))
      return rc;
   rc = CredentialForMultiMeasure.RegisterAsCatalogOwner(CatalogName,ClientId);
   if (FAILED(rc))
      return rc;

   // Get container facade  
   CATFmContainerFacade MultiMeasureContainerFacade(CredentialForMultiMeasure, this);

   // Get startup facade	
   CATUnicodeString StartupName = "`CAAV5V6ExtMmrMultiMeasure`@`CAAV5V6ExtMmrMultiMeasureCatalog.CATfct`";
   CATFmStartUpFacade MultiMeasureStartUpFacade(CredentialForMultiMeasure, StartupName);

   // Instanciate a MultiMeasure
   CATFmFeatureFacade MultiMeasureFeatFacade(CredentialForMultiMeasure);
   rc = MultiMeasureStartUpFacade.InstantiateIn(MultiMeasureContainerFacade, MultiMeasureFeatFacade);

   if (FAILED(rc))
      return rc;

   //===============================================================================================
   //
   // 2- Subscribes to repository for Configuration Data Storage
   //
   //===============================================================================================

   // Get CATIMmiMechanicalFeature pointer on the MultiMeasure object
   CATIMmiMechanicalFeature *piMechFeat = NULL;
   rc = MultiMeasureFeatFacade.QueryInterfaceOnFeature(IID_CATIMmiMechanicalFeature,(void**)&piMechFeat);

   if (SUCCEEDED(rc) && piMechFeat)
   {
      // Create CATIMmiAlgoConfigServicesServices component
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
   // -3- Sets default values for the attributes of the instance
   //
   //===============================================================================================

   CAAIV5V6ExtMmrMultiMeasure * pMultiMeasure = NULL;
   rc = MultiMeasureFeatFacade.QueryInterfaceOnFeature(IID_CAAIV5V6ExtMmrMultiMeasure, (void**) &pMultiMeasure);

   if (FAILED(rc))
      return rc;

   rc = pMultiMeasure->SetInputGeomFeature(ipGeometricalElementToMesure);

   if (FAILED(rc))
   {
      pMultiMeasure->Release();
      pMultiMeasure=NULL;
      return rc;
   }

   //===============================================================================================
   //
   // -4- Initialize Parameters
   //
   //===============================================================================================

   CATCkeGlobalFunctions::InitializeLiteralsEnvironment();

   CATIMmiMechanicalFeature_var spTarget = pMultiMeasure;
   if (spTarget != NULL_var)
   {
      CATICkeParmFactory_var spParmFact = this;
      if (spParmFact != NULL_var)
      {
         spParmFact->InitStartUps();

         // Initialialize ComputedLength parameter
         CATICkeParm_var spValuatedParm = spParmFact->CreateLength("ComputedLength",0);
         spValuatedParm->SetUserAccess(CATICkeParm::ReadOnly);

         // Create feature facade on parameter
         CATFmFeatureFacade FeatFacadeOnParam;
         FeatFacadeOnParam = spValuatedParm;

         // Valuate attribute key
         CATFmAttributeName AttrKey = CATFmAttributeName("ComputedLength");

         // Create an attribute value 
         CATFmAttributeValue FmAttrValue;
         FmAttrValue.SetFeature(FeatFacadeOnParam);

         // Set the attribute on the feature
         rc = MultiMeasureFeatFacade.SetValue(AttrKey, FmAttrValue);

         // Initialialize ComputedWetArea
         spValuatedParm = spParmFact->CreateDimension(CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("AREA"),
            "ComputedWetArea",0);
         spValuatedParm->SetUserAccess(CATICkeParm::ReadOnly);

         // Feature facade on parameter
         FeatFacadeOnParam = spValuatedParm;

         // Valuate attribute key
         AttrKey = CATFmAttributeName("ComputedWetArea");

         // Attribute value
         FmAttrValue.SetFeature(FeatFacadeOnParam);

         // Set the attribute on the feature
         rc = MultiMeasureFeatFacade.SetValue(AttrKey, FmAttrValue);

         // Initialialize ComputedVolume
         spValuatedParm = spParmFact->CreateDimension(CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),
            "ComputedVolume",0);
         spValuatedParm->SetUserAccess(CATICkeParm::ReadOnly);

         // Feature facade on parameter
         FeatFacadeOnParam = spValuatedParm;

         // Valuate attribute key
         AttrKey = CATFmAttributeName("ComputedVolume");

         // Attribute value
         FmAttrValue.SetFeature(FeatFacadeOnParam);

         // Set the attribute on the feature
         rc = MultiMeasureFeatFacade.SetValue(AttrKey, FmAttrValue);

      }
   }

   if (FAILED(rc))
   {
      // Delete the feature instantiated because it won't be aggregated
#ifdef CATIAR214
      //============================================== 
      // V6 only
      //==============================================
      CATIUseEntity * piEntity = NULL;
      rc = pMultiMeasure->QueryInterface(IID_CATIUseEntity , (void**) &piEntity);

      if (SUCCEEDED(rc))
      { 
         rc = DataCommonProtocolServices::Delete(piEntity);
         piEntity->Release();
         piEntity = NULL;
      }
#else
      //============================================== 
      // V5 only
      //==============================================	

      LifeCycleObject_var spLifeCycle = pMultiMeasure; 

      if (spLifeCycle != NULL_var)
      { 
         spLifeCycle->remove();
      }
#endif
   }
   else
   {
      // Get MultiMeasure instance
      rc = MultiMeasureFeatFacade.QueryInterfaceOnFeature(IID_CATBaseUnknown, (void**) &opMultiMeasureInstance);
   }

   return rc; 
}

HRESULT CAAEV5V6ExtMmrMultiMeasureFactory::CreateMmrMeasureSet(CATBaseUnknown *&opMeasureSetInstance)
{
   //===============================================================================================
   //
   //  What does the factory do ?
   //
   //     Creates a CAAV5V6ExtMmrMeasureSet instance
   //
   //===============================================================================================

   HRESULT rc = S_OK;

   //===============================================================================================
   //
   // -1- Creates a MmrMeasureSet instance
   //
   //===============================================================================================

   // Get credential for MeasureSet application
   CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
   CATUnicodeString ClientId = "CAAMmrUseCaseForMechanicalSetsAndElements";
   CATUnicodeString CatalogName = "CAAV5V6ExtMmrMultiMeasureCatalog";
   CATFmCredentials CredentialForMeasureSet;
   rc = CredentialForMeasureSet.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId);
   if (FAILED(rc))
      return rc;
   rc = CredentialForMeasureSet.RegisterAsCatalogOwner(CatalogName,ClientId);
   if (FAILED(rc))
      return rc;

   // Get container facade  
   CATFmContainerFacade MeasureSetContainerFacade(CredentialForMeasureSet, this);

   // Get startup facade	
   
   CATUnicodeString StartupType = "`CAAV5V6ExtMmrMeasureSet`@`CAAV5V6ExtMmrMultiMeasureCatalog.CATfct`";
   CATFmStartUpFacade MeasureSetStartUpFacade(CredentialForMeasureSet, StartupType);

   // Instanciate a MultiMeasure
   CATFmFeatureFacade MeasureSetFeatFacade;
   rc = MeasureSetStartUpFacade.InstantiateIn(MeasureSetContainerFacade, MeasureSetFeatFacade);

   // Get MeasureSet instance
   if (SUCCEEDED(rc))
      rc = MeasureSetFeatFacade.QueryInterfaceOnFeature(IID_CATBaseUnknown, (void**) &opMeasureSetInstance);	


   return rc; 
}

