// COPYRIGHT DASSAULT SYSTEMES 2000

// Local FrameWork
#include "CAAEMmrCatalogEnableForCombCrv.h"
#include "iostream.h"

CATImplementClass ( CAAEMmrCatalogEnableForCombCrv ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CombinedCurve            );

//-----------------------------------------------------------------------------
// CAAEMmrCatalogEnableForCombCrv : constructor
//-----------------------------------------------------------------------------
CAAEMmrCatalogEnableForCombCrv::CAAEMmrCatalogEnableForCombCrv()
{
   cout <<"CAAEMmrCatalogEnableForCombCrv::CAAEMmrCatalogEnableForCombCrv" << endl;
}

//-----------------------------------------------------------------------------
// CAAEMmrCatalogEnableForCombCrv : destructor
//-----------------------------------------------------------------------------
CAAEMmrCatalogEnableForCombCrv::~CAAEMmrCatalogEnableForCombCrv()
{
   cout <<"CAAEMmrCatalogEnableForCombCrv::~CAAEMmrCatalogEnableForCombCrv" << endl;
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICatalogEnable.h" // needed to tie the implementation to its interface
TIE_CATICatalogEnable( CAAEMmrCatalogEnableForCombCrv);

// 
// To declare that CombinedCurve implements CATICatalogEnable , insert 
// the following line in the interface dictionary :
//
// CombinedCurve      CATICatalogEnable    libCAAMmrCatalogCombCrv

