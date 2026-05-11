// COPYRIGHT DASSAULT SYSTEMES 2003
#include "CAAAniExportVBExt.h"
#include "CATIAAnalysisModel.h"
#include <iostream.h>

#include "TIE_CATIVBExtension.h"
TIE_CATIVBExtension(CAAAniExportVBExt);
CATImplementClass(CAAAniExportVBExt, Implementation, CATBaseObject, CATnull);

#include "TIE_CAAIAniExport.h"
TIE_CAAIAniExport(CAAAniExportVBExt);

//-----------------------------------------------------------------------------
// CAAAniExportVBExt : constructor
//-----------------------------------------------------------------------------
CAAAniExportVBExt::CAAAniExportVBExt():
CATBaseObject()
{}
//-----------------------------------------------------------------------------
// CAAAniExportVBExt : destructor
//-----------------------------------------------------------------------------
CAAAniExportVBExt::~CAAAniExportVBExt()
{}
//-----------------------------------------------------------------------------
// Implements CATIVBExtension::GetObjects
//-----------------------------------------------------------------------------
HRESULT CAAAniExportVBExt::GetObjects(CATBaseUnknown * iFrom , CATBaseDispatch *& oDisp) const
{
  cout << " CAAAniExportVBExt::GetObjects" << endl;
//  if (!iFrom) return E_INVALIDARG;
  ((CATBaseUnknown *) this) -> QueryInterface (IID_CAAIAniExport,(void **) &oDisp);
  if (iFrom){
    CATBaseDispatch* pModel = NULL;                                      
    iFrom -> QueryInterface(IID_CATBaseDispatch,(void **)& pModel);      
    if (pModel) {  
      ((CATBaseObject*) this) -> SetParent(pModel);  
      pModel -> Release(); pModel = NULL;
    }
  }
  return (oDisp ? S_OK : E_FAIL) ;
}
//-----------------------------------------------------------------------------
HRESULT __stdcall CAAAniExportVBExt::Export(CATIAAnalysisCase * ipiCase, const CATBSTR & iFullFileName)
{
  cout << " CAAAniExportVBExt::Export" << endl;
  return S_OK;
}
//=========================================================================================================

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAAniExportCreateExt);

CATImplementClass(CAAAniExportCreateExt, CodeExtension, CATBaseUnknown, CAAAniExportVBExt);
//-----------------------------------------------------------------------------
// CAAAniExportCreateExt : constructor
//-----------------------------------------------------------------------------
CAAAniExportCreateExt::CAAAniExportCreateExt():CATBaseUnknown()
{}
CAAAniExportCreateExt::~CAAAniExportCreateExt()
{}
//-----------------------------------------------------------------------------
// Implements CATICreateInstance::CreateInstance
//-----------------------------------------------------------------------------
HRESULT  __stdcall CAAAniExportCreateExt::CreateInstance (void ** oPPV)
{
  if (!oPPV) 
    return E_UNEXPECTED;

  *oPPV = new CAAAniExportVBExt(); // Implementation of CATIVBExtension
  return (*oPPV ? S_OK : E_FAIL) ;
}

















