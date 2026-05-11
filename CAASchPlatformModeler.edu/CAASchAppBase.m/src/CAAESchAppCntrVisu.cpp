// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
// CAAESchAppCntrVisu:
//

// This framework
#include "CAAESchAppCntrVisu.h"

// CATSchPlatformInterfaces
#include "CATISchRoute.h"
#include "CATISchDisplay.h"

// System
#include "CAASchAppErrors.h"

CATImplementClass(CAAESchAppCntrVisu,DataExtension,CATBaseUnknown,CAASCHEDUConnector);

#include "TIE_CATI2DGeoVisu.h"
TIEchain_CATI2DGeoVisu(CAAESchAppCntrVisu);      

//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppCntrVisu::CAAESchAppCntrVisu()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppCntrVisu::~CAAESchAppCntrVisu()
{
}

//  ===========================================================================
//  | BuildRep
//  ===========================================================================
//
CATRep * CAAESchAppCntrVisu::BuildRep()
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
