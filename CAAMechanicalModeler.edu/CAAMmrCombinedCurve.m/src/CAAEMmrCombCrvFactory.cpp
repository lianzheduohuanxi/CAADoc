// COPYRIGHT DASSAULT SYSTEMES 2000
//=================================================================================================
//
// CAAEMmrCombCrvFactory.cpp
// Provide implementation to interface
//    CAAIMmrCombCrvFactory
//
//=================================================================================================

// Local Framework
#include "CAAEMmrCombCrvFactory.h"

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrCombinedCurve.h" // needed by the factory to return a pointer on this interface

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"      // needed to manage features
#include "CATOsmSUHandler.h"     // needed to retrieve the Combined Curve feature startup

// ObjectModelerBase Framework
#include "CATBaseUnknown.h"  
#include "CATIContainer.h"

// AlgorithmConfiguration Management
#include "CATMmrAlgoConfigServices.h"  //needed to subscribe to repository for AlgorithmConfiguration

//BackUp / StartUp Management
#include "CATIInputDescription.h"
#include "CATMmrFeatureAttributes.h"

//System Framework
#include "CATUnicodeString.h"

CATImplementClass ( CAAEMmrCombCrvFactory ,
                    DataExtension         ,
                    CATBaseUnknown        ,
                    CATPrtCont            );

//---------------------------------------------------------------------------------------------------
// CAAEMmrCombCrvFactory : constructor
//---------------------------------------------------------------------------------------------------
CAAEMmrCombCrvFactory::CAAEMmrCombCrvFactory():
CATBaseUnknown()
{
    
}

//---------------------------------------------------------------------------------------------------
// CAAEMmrCombCrvFactory : destructor
//---------------------------------------------------------------------------------------------------
CAAEMmrCombCrvFactory::~CAAEMmrCombCrvFactory()
{
    
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIMmrCombCrvFactory.h" // needed to tie the implementation to its interface
TIE_CAAIMmrCombCrvFactory( CAAEMmrCombCrvFactory);

// 
// To declare that GSMTool implements CAAIMmrCombCrvFactory, insert 
// the following line in the interface dictionary:
//
// GSMTool  CAAIMmrCombCrvFactory    libCAAMmrCombinedCurve



//---------------------------------------------------------------------------------------------------
// Implements CAAIMmrCombCrvFactory::CreateCombinedCurve
//---------------------------------------------------------------------------------------------------

HRESULT CAAEMmrCombCrvFactory::CreateCombinedCurve ( CATISpecObject *ipiSpecOnCurve1     ,
                                                    CATISpecObject *ipiSpecOnDirection1 ,
                                                    CATISpecObject *ipiSpecOnCurve2     ,
                                                    CATISpecObject *ipiSpecOnDirection2 ,
                                                    CATISpecObject **opiSpecOnCombinedCurve )  
{
    
    //===============================================================================================
    //
    //  What does the factory do ?
    //
    //     o -1- Retrieves a CATBaseUnknown interface pointer on this (CATPrtCont)
    //     o -2- Creates a Combined Curve instance
    //     o -3- Subscribes to repository for Configuration Data Storage
    //     o -4- Gets Feature Type Information for BackUp / StartUp management  
    //     o -5- Sets default values for the attributes of the instance
    //
    //
    //===============================================================================================
    
   

		 //===============================================================================================
    //
    // -1- Retrieves a CATIContainer interface pointer on this (CATPrtCont)
    //
    //===============================================================================================
    
    CATIContainer *piContainerOnThis = NULL;
    HRESULT rc = QueryInterface( IID_CATIContainer , ( void**) &piContainerOnThis );
    if ( FAILED(rc) )
    {
       return E_FAIL;
    }

    //===============================================================================================
    //
    // -2- Creates a Combined Curve instance
    //
    //===============================================================================================
    
    CATUnicodeString StartupType = "CombinedCurve";
    CATUnicodeString ClientId = "SAMPLES";
    CATUnicodeString StorageName = "CAAMmrCombinedCurveCatalog.CATfct";
    CATOsmSUHandler ccSUHandler(StartupType, ClientId, StorageName);
    CATISpecObject_var spCombinedCurveSU = NULL_var;
    
    rc = ccSUHandler.Instanciate(spCombinedCurveSU, piContainerOnThis);
    if ( FAILED(rc) )
    {
	    return E_FAIL;
    }
    *opiSpecOnCombinedCurve = spCombinedCurveSU;
    spCombinedCurveSU->AddRef(); // Add a reference to compensate for our
                                 // smart pointer release
    
		piContainerOnThis->Release();
    piContainerOnThis = NULL ;
		

    //===============================================================================================
    //
    // -3- Subscribes to repository for Configuration Data Storage
    //
    //===============================================================================================

    rc = CATMmrAlgoConfigServices::CreateConfigurationData(*opiSpecOnCombinedCurve);
    if( FAILED(rc) )
      return rc;
    //===============================================================================================
    //
    // -4- Gets Feature Type Information for BackUp / StartUp management
    //
    //===============================================================================================

    CATIInputDescription* pInputDescriptionOnCombinedCurve = NULL;
    rc = (*opiSpecOnCombinedCurve)->QueryInterface( IID_CATIInputDescription, (void**) &pInputDescriptionOnCombinedCurve);
    if(FAILED(rc))
      return E_FAIL;
    
    CATIInputDescription::FeatureType Feature_type = CATIInputDescription::FeatureType_Unset;
    
    rc = pInputDescriptionOnCombinedCurve -> GetFeatureType(Feature_type);
    if(FAILED(rc))
    {
      pInputDescriptionOnCombinedCurve -> Release();
      pInputDescriptionOnCombinedCurve = NULL ;
      return E_FAIL;
    }
  
    rc = CATMmrFeatureAttributes::SetFeatureType(*opiSpecOnCombinedCurve, Feature_type);
    if(FAILED(rc))
    {
      pInputDescriptionOnCombinedCurve -> Release();
      pInputDescriptionOnCombinedCurve = NULL ;
      return E_FAIL;
    }
    
    pInputDescriptionOnCombinedCurve -> Release();
    pInputDescriptionOnCombinedCurve = NULL ;
    
    //===============================================================================================
    //
    // -5- Sets default values for the attributes of the instance
    //
    //===============================================================================================
    
    CAAIMmrCombinedCurve *piCombinedCurve = NULL;
    rc = (*opiSpecOnCombinedCurve)->QueryInterface( IID_CAAIMmrCombinedCurve, (void**) &piCombinedCurve );
    if( FAILED(rc) ) 
        return E_FAIL;
    
    piCombinedCurve->SetCurve    ( 1 , ipiSpecOnCurve1     );
    piCombinedCurve->SetDirection( 1 , ipiSpecOnDirection1 );
    piCombinedCurve->SetCurve    ( 2 , ipiSpecOnCurve2     );
    piCombinedCurve->SetDirection( 2 , ipiSpecOnDirection2 );
    
    piCombinedCurve->Release();
    piCombinedCurve = NULL ;
    
    return S_OK;
    
}
