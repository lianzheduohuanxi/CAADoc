// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#include "CAALifCreateExt.h"

// Implementation to be extended
#include "CAALifDicoLibrary.h"

// ===========================================================================
// ABSTRACT:
//
// The CATICreateInstance interface (System) is used to create an implementation instance
// It is implemeted in this code extension which extends the CAALifDicoDictionary
// which is the instance to be created.
// For further explanation see CAALifDicoLibrary.h.
// ===========================================================================

CATImplementClass(CAALifCreateExt, CodeExtension, CATBaseUnknown, CAALifDicoLibrary);

#include <TIE_CATICreateInstance.h>
TIE_CATICreateInstance(CAALifCreateExt); 

HRESULT __stdcall CAALifCreateExt::CreateInstance (void **ppv)
{
  *ppv = new CAALifDicoLibrary ();
  return S_OK;
}

