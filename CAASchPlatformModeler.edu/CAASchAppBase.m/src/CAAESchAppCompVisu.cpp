// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//

// This framework
#include "CAAESchAppCompVisu.h"

// CATSchPlatformInterfaces
#include "CATISchRoute.h"
#include "CATISchDisplay.h"

// System
#include "CAASchAppErrors.h"

CATImplementClass(CAAESchAppCompVisu,DataExtension,CATBaseUnknown,CAASCHEDUPart);

#include "TIE_CATI2DGeoVisu.h"
TIEchain_CATI2DGeoVisu(CAAESchAppCompVisu);      

//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppCompVisu::CAAESchAppCompVisu()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppCompVisu::~CAAESchAppCompVisu()
{
}

//  ===========================================================================
//  | BuildRep
//  ===========================================================================
//
CATRep * CAAESchAppCompVisu::BuildRep()
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
