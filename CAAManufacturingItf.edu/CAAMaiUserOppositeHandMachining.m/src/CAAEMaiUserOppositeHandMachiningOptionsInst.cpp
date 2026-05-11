//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// CAAEMaiUserOppositeHandMachiningOptionsInst.h
// Provides implementation to interface CATICreateInstance
//=============================================================================

#include "CAAEMaiUserOppositeHandMachiningOptionsInst.h"

#include "CAAEMaiUserOppositeHandMachiningOptions.h"

//-----------------------------------------------------------------------------
// Supported Interface
//-----------------------------------------------------------------------------
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance( CAAEMaiUserOppositeHandMachiningOptionsInst);
CATImplementClass(CAAEMaiUserOppositeHandMachiningOptionsInst,CodeExtension,CATNull,CAAEMaiUserOppositeHandMachiningOptions);
 
//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEMaiUserOppositeHandMachiningOptionsInst::CAAEMaiUserOppositeHandMachiningOptionsInst(): CATBaseUnknown() {}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEMaiUserOppositeHandMachiningOptionsInst::~CAAEMaiUserOppositeHandMachiningOptionsInst() {}

//-----------------------------------------------------------------------------
// CreateInstance
//-----------------------------------------------------------------------------
HRESULT __stdcall CAAEMaiUserOppositeHandMachiningOptionsInst::CreateInstance (void ** oPPV)
{
    CAAEMaiUserOppositeHandMachiningOptions * pt = new CAAEMaiUserOppositeHandMachiningOptions();
    
    *oPPV = (void*) pt;
    
    if (NULL != pt)
        return S_OK;
    else
        return E_FAIL;
}
