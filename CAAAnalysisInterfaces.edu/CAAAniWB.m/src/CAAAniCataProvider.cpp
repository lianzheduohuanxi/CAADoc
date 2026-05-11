// COPYRIGHT Dassault Systemes 2000
//===================================================================
// CAAAniCataProvider.h
// Provide implementation to interface CATISamCatalogProvider.
// Associate an Applicative feature catalog to the late type.
//===================================================================
#include "CAAAniCataProvider.h"               // this class definition.

#include "CATIContainer.h"                    // Input Argument
#include "CATOsmSUHandler.h"				  // To load Catalog

CATImplementClass(CAAAniCataProvider,Implementation,CATBaseUnknown,CATnull);

//-----------------------------------------------------------------------------
// CAAAniCataProvider : constructor
//-----------------------------------------------------------------------------
CAAAniCataProvider::CAAAniCataProvider():
CATBaseUnknown()
{}
//-----------------------------------------------------------------------------
// CAAAniCataProvider : destructor
//-----------------------------------------------------------------------------
CAAAniCataProvider::~CAAAniCataProvider()
{}
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATISamCatalogProvider.h"
TIE_CATISamCatalogProvider( CAAAniCataProvider);
//-----------------------------------------------------------------------------
// Implements CAAAniCataProvider::GetContextualMenu
//-----------------------------------------------------------------------------
HRESULT CAAAniCataProvider::AssociateCatalog(CATUnicodeString iName,
                                             const CATIContainer* ipiContainer)
{
  if (NULL == ipiContainer) return E_FAIL;
  if (iName == CATUnicodeString("AeroDynamicSet") || iName == CATUnicodeString("AeroMeshPart") ||
      iName == CATUnicodeString("ANIVirtualMeshPart") || iName == CATUnicodeString("ANIVirtualProperty") ||
      iName == CATUnicodeString("ANIVariableLoad") || iName == CATUnicodeString("ANIVariableLoadWithAxis") || iName == CATUnicodeString("ANIVariableLoadForDoc") ||
      iName == CATUnicodeString("CAAANIBushingMeshPart") || iName == CATUnicodeString("CAAANIBushingProperty"))
  {
// Load the Feature Catalog for Startup On the CATIContainer
    CATUnicodeString CataName ("CAAAniCatalog.CATfct");
    CATUnicodeString CataId   ("CAAAniCatalog");
	CATOsmSUHandler  novelSUHandler(iName, CataId, CataName);
	if (SUCCEEDED(novelSUHandler.IsValid()))
      return S_OK;
  }
  return S_FALSE;
}
//===========================================================================================





