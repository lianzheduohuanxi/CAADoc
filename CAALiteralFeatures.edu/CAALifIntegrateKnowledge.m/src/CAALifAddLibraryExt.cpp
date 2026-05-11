// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAALifAddLibraryExt.cpp
// Provide implementation to interface CATICreateInstance
//
//===================================================================

#include "CAALifAddLibrary.h"
#include "CAALifAddLibraryExt.h"

CATImplementClass( CAALifAddLibraryExt,CodeExtension,CATBaseUnknown,CAALifAddLibrary );

//-----------------------------------------------------------------------------
// CAALifAddLibraryExt : constructor
//-----------------------------------------------------------------------------
CAALifAddLibraryExt::CAALifAddLibraryExt():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAALifAddLibraryExt : destructor
//-----------------------------------------------------------------------------
CAALifAddLibraryExt::~CAALifAddLibraryExt()
{
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance( CAALifAddLibraryExt);

//-----------------------------------------------------------------------------
// Implements CATICreateInstance::CreateInstance
//-----------------------------------------------------------------------------
HRESULT __stdcall CAALifAddLibraryExt::CreateInstance (void ** ppv)
{
	*ppv = new CAALifAddLibrary;
	return S_OK;
}

