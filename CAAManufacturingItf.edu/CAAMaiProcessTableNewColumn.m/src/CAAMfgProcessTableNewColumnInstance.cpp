/**
 * @fullreview OLC XMN 04:11:22
 */
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CAAMfgProcessTableNewColumnInstance.cpp
// Provide implementation to interface
//    CATICreateInstance
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Nov 2004  Creation
//===================================================================
#include "CAAMfgProcessTableNewColumnInstance.h"

#include "CAAMfgProcessTableNewColumn.h"
 
CATImplementClass( CAAMfgProcessTableNewColumnInstance,
                   CodeExtension,
                   CATNull,
                   CAAMfgProcessTableNewColumn );
 
//-----------------------------------------------------------------------------
// CAAMfgProcessTableNewColumnInstance : constructor
//-----------------------------------------------------------------------------
CAAMfgProcessTableNewColumnInstance::CAAMfgProcessTableNewColumnInstance():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAMfgProcessTableNewColumnInstance : destructor
//-----------------------------------------------------------------------------
CAAMfgProcessTableNewColumnInstance::~CAAMfgProcessTableNewColumnInstance()
{
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance( CAAMfgProcessTableNewColumnInstance);
//-----------------------------------------------------------------------------
// Implements CATICreateInstance::CreateInstance
//-----------------------------------------------------------------------------
HRESULT __stdcall CAAMfgProcessTableNewColumnInstance::CreateInstance (void ** oPPV)
{
    CAAMfgProcessTableNewColumn * pt = new CAAMfgProcessTableNewColumn();
    
    *oPPV = (void*) pt;
    
    if (NULL != pt)
        return S_OK;
    else
        return E_FAIL;
}

