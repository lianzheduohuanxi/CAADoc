// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// ===================================================================
//
// CAAMaiUserActivityComputeTP:
// ===================================================================
//
#include "CAAMaiUserActivityComputeTP.h"

//-----------------------------------------------------------------------------
// Interfaces supportees
//-----------------------------------------------------------------------------

#include "TIE_CATIMfgComputeToolPathCustom.h"
TIEchain_CATIMfgComputeToolPathCustom(CAAMaiUserActivityComputeTP);

CATImplementClass (CAAMaiUserActivityComputeTP,DataExtension,CATBaseUnknown,UserActivity);

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------

CAAMaiUserActivityComputeTP::CAAMaiUserActivityComputeTP()
{
}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------

CAAMaiUserActivityComputeTP::~CAAMaiUserActivityComputeTP()
{
}

//-----------------------------------------------------------------------------
// ComputeToolPath
//-----------------------------------------------------------------------------

HRESULT CAAMaiUserActivityComputeTP::ComputeToolPath(const CATIContainer_var& container,CATIMfgToolPath_var& TP)
{
	return E_FAIL;
}

