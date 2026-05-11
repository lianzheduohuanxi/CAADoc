// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEMmrCombCrvCkeFeature.cpp
// Provide implementation to interface
//    CATKweInstanceAdapter
//
//===================================================================
//
// Usage notes:
//
//===================================================================

#include "CAAEMmrCombCrvCkeFeature.h"
 
CATImplementClass(CAAEMmrCombCrvCkeFeature,DataExtension,CATBaseUnknown,CombinedCurve );


#include "TIE_CATICkeFeature.h"
TIEchain_CATICkeFeature(CAAEMmrCombCrvCkeFeature);
 
// LiteralFeatures
#include "CATGlobalFunctions.h"
#include "CATITypeDictionary.h"

#include "iostream.h"


#include "CATIType.h"
//-----------------------------------------------------------------------------
// CAAEMmrCombCrvCkeFeature : constructor
//-----------------------------------------------------------------------------
CAAEMmrCombCrvCkeFeature::CAAEMmrCombCrvCkeFeature(): CATKweInstanceAdapter()
{
}
CAAEMmrCombCrvCkeFeature::~CAAEMmrCombCrvCkeFeature()
{
}
//-----------------------------------------------------------------------------
// Implements CATKweInstanceAdapter::GetType
//-----------------------------------------------------------------------------
CATICkeType_var CAAEMmrCombCrvCkeFeature::GetType () const
{
    cout <<" CAAEMmrCombCrvCkeFeature" << endl;
	CATITypeDictionary_var TypeDic =  CATGlobalFunctions::GetTypeDictionary();
	if (TypeDic != NULL_var ) { 
		CATIType_var oType;  
		HRESULT rc = TypeDic ->FindTypeSafe("Curve","",oType );
		if (SUCCEEDED(rc))  { 
			return  oType ;
		}
	}
	return NULL_var ;
}

