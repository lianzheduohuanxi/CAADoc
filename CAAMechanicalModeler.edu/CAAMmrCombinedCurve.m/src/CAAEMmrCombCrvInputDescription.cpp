// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================

// Local Framework
#include "CAAEMmrCombCrvInputDescription.h"

#include "iostream.h"

CATImplementClass ( CAAEMmrCombCrvInputDescription ,
                   DataExtension       ,    
                   CATIInputDescription      ,
                   CombinedCurve        );

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIInputDescription, CAAEMmrCombCrvInputDescription);

// To declare that CombinedCurve implements CAAIMmrCombinedCurve, insert 
// the following line in the interface dictionary:
//
// CombinedCurve  CATIInputDescription  libCAAMmrCombinedCurve


//-------------------------------------------------------------------------------------
CAAEMmrCombCrvInputDescription::CAAEMmrCombCrvInputDescription():CATIniInputDescriptionAdaptor()
{
    cout <<" CAAEMmrCombCrvInputDescription::CAAEMmrCombCrvInputDescription" << endl;
}

//-------------------------------------------------------------------------------------
CAAEMmrCombCrvInputDescription::~CAAEMmrCombCrvInputDescription()
{
    cout <<" CAAEMmrCombCrvInputDescription::~CAAEMmrCombCrvInputDescription" << endl;
}

//-------------------------------------------------------------------------------------
HRESULT CAAEMmrCombCrvInputDescription::GetListOfModifiedFeatures
                             (CATListValCATBaseUnknown_var& ListOfModifiedFeatures ) 
{    
    return E_FAIL ;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombCrvInputDescription::GetMainInput(CATBaseUnknown_var& oMainInput) 
{
    return E_FAIL ;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombCrvInputDescription::GetFeatureType
                         (CATIInputDescription::FeatureType& oFeature_type)
{
    cout <<" CAAEMmrCombCrvInputDescription::GetFeatureType" << endl;

    oFeature_type = CATIInputDescription::FeatureType_Creation ;
    return S_OK ;
}


