// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================

// This framework
#include "CAAESchAppRouteVisu.h"

// CATSchPlatformInterfaces
#include "CATISchRoute.h"
#include "CATISchDisplay.h"

// System
#include "CAASchAppErrors.h"

CATImplementClass(CAAESchAppRouteVisu,DataExtension,CATBaseUnknown,CAASCHEDUString);

#include "TIE_CATI2DGeoVisu.h"
TIEchain_CATI2DGeoVisu(CAAESchAppRouteVisu);      

//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppRouteVisu::CAAESchAppRouteVisu()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppRouteVisu::~CAAESchAppRouteVisu()
{
}

//  ===========================================================================
//  | BuildRep
//  ===========================================================================
//
CATRep * CAAESchAppRouteVisu::BuildRep()
{
  CATRep *pRep = NULL;
  CATISchDisplay *piDisplay = NULL;

  if (SUCCEEDED (QueryInterface (IID_CATISchDisplay,
	  (void **) &piDisplay)))
  {
	 HRESULT rc = piDisplay->BuildRep (&pRep);
	 piDisplay->Release();
	 piDisplay = NULL;
  }
  return pRep;
}

//  ===========================================================================
//  | BuildHighlightLook
//  ===========================================================================
HRESULT CAAESchAppRouteVisu::BuildHighlightLook (
  const CATPathElement &modelPath, CATRepPath &repPath)              
{
  HRESULT RC = E_FAIL;
  CATISchDisplay *piDisplay = NULL;
  if (SUCCEEDED (QueryInterface (IID_CATISchDisplay,
	  (void **) &piDisplay)))
  {
	 RC = piDisplay->BuildHighlightLook (modelPath,repPath);
	 piDisplay->Release();
	 piDisplay = NULL;
  }
  return RC;
}
