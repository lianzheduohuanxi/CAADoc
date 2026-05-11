// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombCrvCkeFeature
//    Implementation of interface CATICkeFeature for V5V6ExtCombinedCurve 
//
// Note : CAAEV5V6ExtMmrCombCrvCkeFeature is the same use case as CAAEMmrCombCrvCkeFeature. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//====================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework 
#include "CAAEV5V6ExtMmrCombCrvCkeFeature.h"
 
// KnowledgeInterfaces Framework
#include "CATGlobalFunctions.h"
#include "CATITypeDictionary.h"
#include "CATIType.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass(CAAEV5V6ExtMmrCombCrvCkeFeature,DataExtension,CATBaseUnknown, V5V6ExtCombinedCurve);

#include "TIE_CATICkeFeature.h"
TIEchain_CATICkeFeature(CAAEV5V6ExtMmrCombCrvCkeFeature);
 
// To declare that V5V6ExtCombinedCurve implements CATICkeFeature, insert 
// the following line in the interface dictionary:
//
// V5V6ExtCombinedCurve	        CATICkeFeature         libCAAV5V6MmrCombinedCurve

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombCrvCkeFeature : constructor
//-----------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
CAAEV5V6ExtMmrCombCrvCkeFeature::CAAEV5V6ExtMmrCombCrvCkeFeature(): CATKweObjectAdapter()
#else
//============================================== 
// V5 only
//============================================== 
CAAEV5V6ExtMmrCombCrvCkeFeature::CAAEV5V6ExtMmrCombCrvCkeFeature(): CATKweInstanceAdapter()
#endif
{}

CAAEV5V6ExtMmrCombCrvCkeFeature::~CAAEV5V6ExtMmrCombCrvCkeFeature()
{}

//-----------------------------------------------------------------------------
// Implements CATKweObjectAdapter::GetType
//-----------------------------------------------------------------------------
CATICkeType_var CAAEV5V6ExtMmrCombCrvCkeFeature::GetType () const
{

  cout <<" CAAEV5V6ExtMmrCombCrvCkeFeature" << endl;
  CATITypeDictionary_var TypeDic = CATGlobalFunctions::GetTypeDictionary();
  if (TypeDic != NULL_var )
  { 
	CATIType_var oType;  
	HRESULT rc = TypeDic->FindTypeSafe("Curve","",oType );
	if (SUCCEEDED(rc))  
		return  oType;

  }
  return NULL_var;
}

