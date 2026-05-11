// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================================
//
// CAAEMmrMultiMeasureAndMeasureSetFactory.cpp
// Provide implementation to interface
//    CAAIMmrMultiMeasureAndMeasureSetFactory
//
//=================================================================================================

// Local Framework
#include "CAAEMmrMultiMeasureAndMeasureSetFactory.h"

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrMultiMeasure.h" 

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"      // needed to manage features
#include "CATOsmSUHandler.h"     // instantiate StartUp

// ObjectModelerBase Framework
#include "CATBaseUnknown.h"        
#include "CATIContainer.h"

// Knowledge Interface
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATIDescendants.h"

//For Configuration Management
#include "CATMmrAlgoConfigServices.h"

// Include System
#include "LifeCycleObject.h"
#include "CATUnicodeString.h"

CATImplementClass ( CAAEMmrMultiMeasureAndMeasureSetFactory ,
                    DataExtension         ,
                    CATBaseUnknown        ,
                    CATPrtCont            );

//---------------------------------------------------------------------------------------------------
// CAAEMmrMultiMeasureAndMeasureSetFactory : constructor
//---------------------------------------------------------------------------------------------------
CAAEMmrMultiMeasureAndMeasureSetFactory::CAAEMmrMultiMeasureAndMeasureSetFactory():
CATBaseUnknown()
{
    
}

//---------------------------------------------------------------------------------------------------
// CAAEMmrMultiMeasureAndMeasureSetFactory : destructor
//---------------------------------------------------------------------------------------------------
CAAEMmrMultiMeasureAndMeasureSetFactory::~CAAEMmrMultiMeasureAndMeasureSetFactory()
{
    
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIMmrMultiMeasureAndMeasureSetFactory.h" // needed to tie the implementation to its interface
TIE_CAAIMmrMultiMeasureAndMeasureSetFactory( CAAEMmrMultiMeasureAndMeasureSetFactory);

// 
// To declare implementation CAAIMmrMultiMeasureAndMeasureSetFactory, insert 
// the following line in the interface dictionary:
//
// CATPrtCont  CAAIMmrMultiMeasureAndMeasureSetFactory    libCAAMmrMultiMeasureAndMeasureSet

//---------------------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasureAndMeasureSetFactory::CreateDataExtension
//---------------------------------------------------------------------------------------------------

HRESULT CAAEMmrMultiMeasureAndMeasureSetFactory::CreateMmrMultiMeasure (CATBaseUnknown *ipGeometricalElementToMesure ,
                                                              CATISpecObject **opMultiMeasureInstance )
{
  //===============================================================================================
  //
  //  What does the factory do ?
  //
  //     o -1- Retrieves a pointer on this (CATPrtCont)
  //     o -2- Creates a MmrMultiMeasure instance
  //     o -3- Subscribes to repository for Configuration Data Storage
  //     o -4- Sets default values for the attributes of the instance
  //
  //===============================================================================================

  //===============================================================================================
  //
  // -1- Retrieves a pointer on this (CATPrtCont)
  //
  //===============================================================================================

  CATIContainer *piContainerOnThis = NULL;
  HRESULT rc = QueryInterface( IID_CATBaseUnknown , ( void**) &piContainerOnThis );
  if (FAILED(rc))
    return rc;

  //===============================================================================================
  //
  // -2- Creates a MmrMultiMeasure instance
  //
  //===============================================================================================

  CATUnicodeString StartupType = "CAAMmrMultiMeasure";
  CATUnicodeString ClientId = "CAAMmrUseCaseForMechanicalSetsAndElements";
  CATUnicodeString StorageName = "CAAMmrMultiMeasureAndMeasureSetCatalog.CATfct";
  CATOsmSUHandler  MMSUHandler(StartupType, ClientId, StorageName);

  CATISpecObject_var spMMInstance = NULL_var;
  rc = MMSUHandler.Instanciate(spMMInstance, piContainerOnThis);

  if(SUCCEEDED(rc))
  {
    spMMInstance->AddRef();
    *opMultiMeasureInstance = spMMInstance;
    rc = CATMmrAlgoConfigServices::CreateConfigurationData(*opMultiMeasureInstance);
    if (SUCCEEDED(rc))
    {
      //===============================================================================================
      //
      // -3- Sets default values for the attributes of the instance
      //
      //===============================================================================================
      CAAIMmrMultiMeasure *pMultiMeasure = NULL;
      rc = (*opMultiMeasureInstance)->QueryInterface( IID_CAAIMmrMultiMeasure, (void**) &pMultiMeasure);

      if(SUCCEEDED(rc))
      {
	      pMultiMeasure -> SetInputGeomFeature(ipGeometricalElementToMesure);
	      //===============================================================================================
	      //
	      // -4- Initialize Parameters
	      //
	      //===============================================================================================
	      CATCkeGlobalFunctions::InitializeLiteralsEnvironment();

	      CATIDescendants *piDescendantsOnMmrMultiMeasure = NULL;
	      rc = pMultiMeasure -> QueryInterface( IID_CATIDescendants, (void**) &piDescendantsOnMmrMultiMeasure);
	      if(SUCCEEDED(rc) && NULL != piDescendantsOnMmrMultiMeasure)
	      {
	        CATICkeParmFactory_var spParmFact = this;
	        if (!!spParmFact)
	        {
	          spParmFact -> InitStartUps();
	          CATICkeParm_var spValuatedParm;

	          spValuatedParm = spParmFact -> CreateLength  ("Computed Length",0);
	          spValuatedParm -> SetUserAccess (CATICkeParm::ReadOnly);
	          piDescendantsOnMmrMultiMeasure->Append(spValuatedParm);

	          spValuatedParm = spParmFact -> CreateDimension(CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("AREA"),"Computed WetArea",0);
	          spValuatedParm -> SetUserAccess (CATICkeParm::ReadOnly);
	          piDescendantsOnMmrMultiMeasure->Append(spValuatedParm);

	          spValuatedParm = spParmFact -> CreateDimension(CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),"Computed Volume",0);
	          spValuatedParm -> SetUserAccess (CATICkeParm::ReadOnly);
	          piDescendantsOnMmrMultiMeasure->Append(spValuatedParm);
	        }
	        piDescendantsOnMmrMultiMeasure -> Release();
	        piDescendantsOnMmrMultiMeasure = NULL;
	      }
	      pMultiMeasure->Release();
	      pMultiMeasure= NULL ;         
      }
    }

    if (FAILED(rc))
    {
      // Deletes the feature instantiated because it won't be aggregated
      LifeCycleObject_var(*opMultiMeasureInstance)->remove();
    }
  }

  piContainerOnThis->Release();
  piContainerOnThis = NULL ;

  return rc; 
}

HRESULT CAAEMmrMultiMeasureAndMeasureSetFactory::CreateMmrMeasureSet(CATISpecObject **opMeasureSetInstance)
{
  //===============================================================================================
  //
  //  What does the factory do ?
  //
  //     o -1- Retrieves a pointer on this (CATPrtCont)
  //     o -2- Creates a MmrMeasureSet instance
  //
  //===============================================================================================

  //===============================================================================================
  //
  // -1- Retrieves a pointer on this (CATPrtCont)
  //
  //===============================================================================================
	 
	CATIContainer *piContainerOnThis = NULL;
  HRESULT rc = QueryInterface( IID_CATBaseUnknown , ( void**) &piContainerOnThis );
  if (FAILED(rc))
    return rc;


  //===============================================================================================
  //
  // -2- Creates a MmrMeasureSet instance
  //
  //===============================================================================================

  CATUnicodeString StartupType = "CAAMmrMeasureSet";
  CATUnicodeString ClientId = "CAAMmrUseCaseForMechanicalSetsAndElements";
  CATUnicodeString StorageName = "CAAMmrMultiMeasureAndMeasureSetCatalog.CATfct";
  CATOsmSUHandler  MSSUHandler(StartupType, ClientId, StorageName);

  CATISpecObject_var spMSInstance = NULL_var;
  rc = MSSUHandler.Instanciate(spMSInstance, piContainerOnThis);
  if (SUCCEEDED(rc))
  {
    spMSInstance->AddRef();
    *opMeasureSetInstance = spMSInstance;
  }
  piContainerOnThis->Release();
  piContainerOnThis = NULL ;

  return rc; 
}
