// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================

// Local Framework
#include "CAAEMmrCombCrvMf3DBehavior.h"

#include "iostream.h"

CATImplementClass ( CAAEMmrCombCrvMf3DBehavior ,
                   DataExtension       ,    
                   CATBaseUnknown      ,
                   CombinedCurve        );

//-----------------------------------------------------------------------------
#include "TIE_CATIMf3DBehavior.h" // needed to tie the implementation to its interface
TIE_CATIMf3DBehavior( CAAEMmrCombCrvMf3DBehavior);
//-----------------------------------------------------------------------------

// To declare that CombinedCurve implements CATIMf3DBehavior, insert 
// the following line in the interface dictionary:
//
// CombinedCurve  CATIMf3DBehavior  libCAAMmrCombinedCurve


//-------------------------------------------------------------------------------------
CAAEMmrCombCrvMf3DBehavior::CAAEMmrCombCrvMf3DBehavior()
{
    cout <<" CAAEMmrCombCrvMf3DBehavior::CAAEMmrCombCrvMf3DBehavior" << endl;
}

//-------------------------------------------------------------------------------------
CAAEMmrCombCrvMf3DBehavior::~CAAEMmrCombCrvMf3DBehavior()
{
    cout <<" CAAEMmrCombCrvMf3DBehavior::~CAAEMmrCombCrvMf3DBehavior" << endl;
}

//-------------------------------------------------------------------------------------
HRESULT CAAEMmrCombCrvMf3DBehavior::IsASolid() const
{    
    return E_FAIL ;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombCrvMf3DBehavior::IsAShape()  const
{
    return S_OK ;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEMmrCombCrvMf3DBehavior::IsADatum() const
                         
{
    return E_FAIL ;
}


