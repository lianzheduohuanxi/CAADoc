// COPYRIGHT Dassault Systemes 2003
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAECircleSweepTgFactory.cpp
// Provide implementation to interface
//    CAAIGSMFeaturesSplFactory
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================


// ObjectSpecsModeler Framework
// MINC 
#include "CATUnicodeString.h"

#include "CATISpecObject.h"      // needed to manage features
#include "CATIDescendants.h"     // needed to agregate the Sew Skinunder its gsm tool 

// ObjectModelerBase Framework
#include "CATIContainer.h"       
#include "CATISpecObject.h"      // needed to manage features
#include "CATIDescendants.h"     // needed to agregate the Combined Curve under its gsm tool 

// Catalog 
#include "CATOsmSUHandler.h"

// Migration OpenCatalog 
#include "CAAEGSMFeaturesSplFactory.h"
#include "CAAIGSMCircleSweepTg.h"
#include "CAAIGSMSewSkinBasic.h"

// Other Framework
#include "CATGSMOrientation.h"
#include "CATMmrFeatureAttributes.h"
#include "CATMmrAlgoConfigServices.h" 

//#define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 


// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIGSMFeaturesSplFactory.h"
TIE_CAAIGSMFeaturesSplFactory( CAAEGSMFeaturesSplFactory);
CATImplementClass(CAAEGSMFeaturesSplFactory,CodeExtension,CATBaseUnknown,CATFeatCont);

//-----------------------------------------------------------------------------
// CAAEGSMFeaturesSplFactory : constructor
//-----------------------------------------------------------------------------
CAAEGSMFeaturesSplFactory::CAAEGSMFeaturesSplFactory():
    CATBaseUnknown()
{
#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMFeaturesSplFactory::CAAEGSMFeaturesSplFactory) Constructor " <<endl ;
#endif 
}

//-----------------------------------------------------------------------------
// CAAEGSMFeaturesSplFactory : destructor
//-----------------------------------------------------------------------------
CAAEGSMFeaturesSplFactory::~CAAEGSMFeaturesSplFactory()
{
#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMFeaturesSplFactory::~CAAEGSMFeaturesSplFactory) Destructor " <<endl ;
#endif 
}
 
//-----------------------------------------------------------------------------
// Implements CAAIGSMFeaturesSplFactory::CreateSewSkinBasic
//-----------------------------------------------------------------------------
CAAIGSMSewSkinBasic  * CAAEGSMFeaturesSplFactory::CreateSewSkinBasic (CATISpecObject * ipSurfaceToSew  , CATISpecObject * ipSurfaceSupport )
{
#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMFeaturesSplFactory::CreateSewSkinBasic ) Create CAA Feature GSMFeaturesSpl Destructor " <<endl ;
#endif 
 
   //===============================================================================================
    //
    //  What does the factory do ?
    //
    //     o -1- Getting a pointer on  CATIContainer
    //     o -2- Opening the Sew Skincatalog
    //     o -3- Retrieving Sew Skin's startup
    //     o -4- Creating a Sew Skininstance
    //     o -5- Setting default values for the attributes of the instance
    //     o -6- Agregating the instance under the GSMTool used as factory
    //
    //===============================================================================================
    
    
    HRESULT rc = E_FAIL; 
    CAAIGSMSewSkinBasic *poSewSkinBasic = NULL;
    
    //===============================================================================================
    //
    // -1- Getting a pointer on  CATIContainer
    //
    //===============================================================================================
    
    CATIContainer_var spiContainer(this);
    if (NULL_var == spiContainer) { 
        return NULL;
    }

    //===============================================================================================
    //
    // -1- SU , Catalog 
    //
    //===============================================================================================
    CATUnicodeString StorageName = "CAAGSMFeaturesSplCatalog.CATfct";
    CATUnicodeString ClientId    = "SAMPLES";
    CATUnicodeString StartupType = "CAASewSkinBasic";
    CATOsmSUHandler SewSkinBasicSUHandler ( StartupType ,ClientId,StorageName); 
    
    //===============================================================================================
    //
    // -2- Instanciate 
    //
    //===============================================================================================
    CATISpecObject_var spSew ; 
    rc = SewSkinBasicSUHandler.Instanciate(spSew, spiContainer, NULL);  
    if( FAILED(rc) )  return NULL ;

    if (NULL_var != spSew ) { 
        //===============================================================================================
        //
        // -##- Setting attribute default / type for BS 
        //
        //===============================================================================================

        // Type Of Feature 	
        // rCode = CATMmrFeatureAttributes::SetFeatureType(hFeature, CATIInputDescription::FeatureType_Modification);
        rc = CATMmrFeatureAttributes::SetFeatureType(spSew, CATIInputDescription::FeatureType_Creation);


        // Configuration Data
        rc = CATMmrAlgoConfigServices::CreateConfigurationData(spSew);

        //===============================================================================================
        //
        // -5- Setting default values for the attributes of the instance
        //
        //===============================================================================================

        rc = spSew->QueryInterface( IID_CAAIGSMSewSkinBasic, (void**) &poSewSkinBasic );

        if ( SUCCEEDED(rc) && NULL != poSewSkinBasic ) { 
            poSewSkinBasic->SetSurfaceToSew    (  ipSurfaceToSew     );
            poSewSkinBasic->SetSurfaceSupport  (  ipSurfaceSupport   );
            poSewSkinBasic->SetOrientation(CATGSMSameOrientation);


        }
    } 

#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMFeaturesSplBasicFactory::CreateSewSkinBasic ) Exit "<<endl ; 
#endif 

    //===============================================================================================
    //
    // -6- Return 
	//
    //===============================================================================================

    return poSewSkinBasic ;
}

 

//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTgFactory::CreateCircleSweepTg
//-----------------------------------------------------------------------------
CAAIGSMCircleSweepTg *  CAAEGSMFeaturesSplFactory::CreateCircleSweepTg (  CATISpecObject *ipCurveRef  , CATISpecObject *ipSurfaceSupport , double radius )
{
#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAEGSMFeaturesSplFactory::CreateCircleSweepTg ) Create CAA Feature GSMFeaturesSpl Destructor " <<endl ;
#endif 
 
   //===============================================================================================
    //
    //  What does the factory do ?
    //
    //     o -1- Getting a pointer on  CATIContainer
    //     o -2- Opening the Sew Skincatalog
    //     o -3- Retrieving Sew Skin's startup
    //     o -4- Creating a Sew Skininstance
    //     o -5- Setting default values for the attributes of the instance
    //     o -6- Agregating the instance under the GSMTool used as factory
    //
    //===============================================================================================
    
    
    HRESULT rc = E_FAIL; 
    CAAIGSMCircleSweepTg *poCircleSweepTg = NULL;

    //===============================================================================================
    //
    // -1- Getting a pointer on  CATIContainer
    //
    //===============================================================================================
    
    CATIContainer_var spiContainer(this);
    if (NULL_var == spiContainer) { 
        return NULL;
    }
    
    //===============================================================================================
    //
    // -1- SU , Catalog 
    //
    //===============================================================================================
    CATUnicodeString StorageName = "CAAGSMFeaturesSplCatalog.CATfct";
    CATUnicodeString ClientId    = "SAMPLES";
    CATUnicodeString StartupType = "CAACircleSweepTg";
    CATOsmSUHandler CircleSweepBasicSUHandler ( StartupType ,ClientId,StorageName); 
    
    //===============================================================================================
    //
    // -2- Instanciate 
    //
    //===============================================================================================
    CATISpecObject_var spCircleSweep ; 
    rc = CircleSweepBasicSUHandler.Instanciate(spCircleSweep, spiContainer, NULL);  
    if( FAILED(rc) )  return NULL ;

    if (NULL_var != spCircleSweep ) { 
        //===============================================================================================
        //
        // -##- Setting attribute default / type for BS 
        //
        //===============================================================================================

        // Type Of Feature 	
        // rCode = CATMmrFeatureAttributes::SetFeatureType(hFeature, CATIInputDescription::FeatureType_Modification);
        rc = CATMmrFeatureAttributes::SetFeatureType(spCircleSweep, CATIInputDescription::FeatureType_Creation);


        // Configuration Data
        rc = CATMmrAlgoConfigServices::CreateConfigurationData(spCircleSweep);

        //===============================================================================================
        //
        // -5- Setting default values for the attributes of the instance
        //
        //===============================================================================================

        rc = spCircleSweep->QueryInterface( IID_CAAIGSMCircleSweepTg, (void**) &poCircleSweepTg );
        
        if ( SUCCEEDED(rc) && NULL != poCircleSweepTg ) { 
            poCircleSweepTg->SetCurveRef        (ipCurveRef      );
            poCircleSweepTg->SetSurfaceSupport  (ipSurfaceSupport);
            poCircleSweepTg->SetTrimMode(0);
            poCircleSweepTg->SetSolution(1);
            poCircleSweepTg->SetRadius (radius);
        }
    } 

#ifdef DEBUG_GSD_CAASAMPLE 
    cout <<" (CAAECircleSweepTgFactory::CreateCircleSweepTg ) Exit " <<endl ; 
#endif 
    
    return poCircleSweepTg ;
}
