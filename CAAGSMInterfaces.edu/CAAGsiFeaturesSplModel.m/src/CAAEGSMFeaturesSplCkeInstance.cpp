// COPYRIGHT Dassault Systemes 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMFeaturesSplCkeInstance.cpp
// Provide implementation to interface
//    CATIInstance and CATICkeFeature
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// MINC 
#include "CATIType.h"
#include "CATUnicodeString.h"

#include "CAAEGSMFeaturesSplCkeInstance.h"
 
CATBeginImplementClass(CAAEGSMFeaturesSplCkeInstance,DataExtension,CATKweInstanceAdapter,CAASewSkinBasic);
CATAddExtendedImplementation(CAACircleSweepTg);
CATEndImplementClass(CAAEGSMFeaturesSplCkeInstance);

//Spec Modeler 
#include "CATISpecObject.h"

// LiteralFeatures
#include "CATGlobalFunctions.h"
#include "CATITypeDictionary.h"
#include "CATListOfCATUnicodeString.h"

// #define CAA_DEBUG
#ifdef CAA_DEBUG
#include "iostream.h"
#endif 

//-----------------------------------------------------------------------------
// CAAEGSMFeaturesSplCkeInstance : constructor
//-----------------------------------------------------------------------------
CAAEGSMFeaturesSplCkeInstance::CAAEGSMFeaturesSplCkeInstance():
    CATKweInstanceAdapter()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMFeaturesSplCkeInstance : destructor
//-----------------------------------------------------------------------------
CAAEGSMFeaturesSplCkeInstance::~CAAEGSMFeaturesSplCkeInstance()
{
}
 
// Link the implementation to its interface
// ---------------------------------------

//TIE or TIEchain definitions
#include "TIE_CATICkeFeature.h"
TIE_CATICkeFeature(CAAEGSMFeaturesSplCkeInstance);


//Methods implementation
CATICkeType_var CAAEGSMFeaturesSplCkeInstance::GetType() const
{

	

	CATITypeDictionary_var TypeDic =  CATGlobalFunctions::GetTypeDictionary();

#ifdef CAA_DEBUG
	CATListOfCATUnicodeString olListOfPackages; 
	TypeDic ->ListPackages(olListOfPackages ) ;
	cout << "(CAAEGSMFeaturesSplCkeInstance::GetType)"<<endl; 
	for (int i=1; i<= olListOfPackages.Size();i++){
		cout << "Package ["<<i<<"]="<<olListOfPackages[i]<<endl;
	}
#endif 

	CATIType_var oType;  

	HRESULT rc = S_OK; 
	CATISpecObject_var Spec ( (CAAEGSMFeaturesSplCkeInstance *)this );
	CATUnicodeString TypeLate = Spec -> GetType();

	// Types in "BasicWireframePackage" = Point/Line/Plane/Circle/Surface/VolumeGeo 
	if(TypeLate=="CAASewSkinBasic" ||
	   TypeLate=="CAACircleSweepTg"	)
	{ 
#ifdef CAA_DEBUG
		cout << "(CAAEGSMFeaturesSplCkeInstance::GetType) Late feature Type = "<<TypeLate<<endl; 
#endif 
		// SewSkinBasic = Result is of "Surface" Type 
		// CircleSweep  = Result is of "Surface" Type 
		 rc = TypeDic ->FindTypeSafe("Surface","BasicWireframePackage",oType );
		 if (SUCCEEDED(rc)){
			return oType; 
		 }
	}
	return NULL_var ;
}


