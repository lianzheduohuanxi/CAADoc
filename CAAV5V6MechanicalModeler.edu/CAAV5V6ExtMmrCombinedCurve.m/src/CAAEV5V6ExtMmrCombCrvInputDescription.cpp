// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombCrvInputDescription
//    Implementation of interface CATIInputDescription for V5V6ExtCombinedCurve 
//
// Note : CAAEV5V6ExtMmrCombCrvInputDescription is the same use case as CAAEMmrCombCrvInputDescription. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//====================================================================================

// Local CAAV5V6MechanicalModeler.edu framework 
#include "CAAEV5V6ExtMmrCombCrvInputDescription.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass (CAAEV5V6ExtMmrCombCrvInputDescription, DataExtension, CATIInputDescription, V5V6ExtCombinedCurve);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIInputDescription, CAAEV5V6ExtMmrCombCrvInputDescription);

// To declare that V5V6ExtCombinedCurve implements CAAIV5V6ExtMmrCombinedCurve, insert 
// the following line in the interface dictionary:
//
// V5V6ExtCombinedCurve  CATIInputDescription  libCAAV5V6MmrCombinedCurve


//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombCrvInputDescription::CAAEV5V6ExtMmrCombCrvInputDescription():CATIniInputDescriptionAdaptor()
{
	cout <<" CAAEV5V6ExtMmrCombCrvInputDescription::CAAEV5V6ExtMmrCombCrvInputDescription" << endl;
}

//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombCrvInputDescription::~CAAEV5V6ExtMmrCombCrvInputDescription()
{
	cout <<" CAAEV5V6ExtMmrCombCrvInputDescription::~CAAEV5V6ExtMmrCombCrvInputDescription" << endl;
}

//-------------------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCombCrvInputDescription::GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& ListOfModifiedFeatures) 
{    
	return E_FAIL;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombCrvInputDescription::GetMainInput(CATBaseUnknown_var& oMainInput) 
{
	return E_FAIL;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombCrvInputDescription::GetFeatureType(CATIInputDescription::FeatureType& oFeature_type)
{
	cout <<" CAAEV5V6ExtMmrCombCrvInputDescription::GetFeatureType" << endl;

  oFeature_type = CATIInputDescription::FeatureType_Creation ;
  return S_OK;
}


