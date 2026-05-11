// COPYRIGHT DASSAULT SYSTEMES 2000

// Local FrameWork
#include "CAAEMmrCatalogSynchronizeForCombCrv.h"

// ObjectModelerBase Framework
#include "CATIAlias.h"

// System Framework
#include "CATUnicodeString.h"

// Standard C++ library
#include "iostream.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICatalogSynchronize.h" // needed to tie the implementation to its interface
TIE_CATICatalogSynchronize( CAAEMmrCatalogSynchronizeForCombCrv);

// 
// To declare that CombinedCurve implements CATICatalogSynchronize , insert 
// the following line in the interface dictionary :
//
// CombinedCurve      CATICatalogSynchronize    libCAAMmrCatalogCombCrv

CATImplementClass ( CAAEMmrCatalogSynchronizeForCombCrv ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CombinedCurve            );

//-----------------------------------------------------------------------------
// CAAEMmrCatalogSynchronizeForCombCrv : constructor
//-----------------------------------------------------------------------------
CAAEMmrCatalogSynchronizeForCombCrv::CAAEMmrCatalogSynchronizeForCombCrv()
{
}

//-----------------------------------------------------------------------------
// CAAEMmrCatalogSynchronizeForCombCrv : destructor
//-----------------------------------------------------------------------------
CAAEMmrCatalogSynchronizeForCombCrv::~CAAEMmrCatalogSynchronizeForCombCrv()
{
}

//-----------------------------------------------------------------------------

HRESULT CAAEMmrCatalogSynchronizeForCombCrv::GetAlias(CATUnicodeString& oAlias) 
{
  HRESULT rc = E_FAIL ;
  CATIAlias_var alias(this);
  if (alias!=NULL_var)
  {
      oAlias  = "CAA" ;
      oAlias += alias->GetAlias();
      rc = S_OK ;
  }
  return rc;
}

//-----------------------------------------------------------------------------

HRESULT CAAEMmrCatalogSynchronizeForCombCrv::GetEmbeddedPreview(CATPixelImage** oImage) 
{
    cout <<" CAAEMmrCatalogSynchronizeForCombCrv::GetEmbeddedPreview" << endl;

    return E_FAIL ;
}

//-----------------------------------------------------------------------------

HRESULT CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   int& oKeyWordValue) 
{
    cout <<" CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue int" << endl;

    HRESULT rc = S_OK ;
    CATUnicodeString Key = "Inputs number" ;
    if ( Key == iKeywordName )
    {
        // The combined curve is built with 4 objects: 
        // 2 lines and 2 curves
        //
        oKeyWordValue = 4 ;
    }else rc = E_FAIL ;

    return rc ;
}
 
//-----------------------------------------------------------------------------

HRESULT CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   const CATICkeType* iKeywordType,
                                   double& oKeyWordValue)
{
    cout <<" CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue CATICkeType*" << endl;
    return E_FAIL ;
}

//-----------------------------------------------------------------------------

HRESULT CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   CATCke::Boolean & oKeyWordValue) 
{
    cout <<" CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue CATCke::Boolean" << endl;
    return E_FAIL ;
}
 
//-----------------------------------------------------------------------------

HRESULT CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   CATUnicodeString& oKeyWordValue) 
{
   cout <<" CAAEMmrCatalogSynchronizeForCombCrv::GetKeywordValue CATUnicodeString" << endl;
   
   HRESULT rc = E_FAIL ;

   return rc ;
}
//-----------------------------------------------------------------------------

