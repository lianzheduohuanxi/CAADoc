#include "CAAAniExplicitMP.h"

#include "CATAnalysisExplicitListUsr.h"
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATSamDocumentTools.h"

#include "CAAIAniAeroImport.h"

CATImplementClass(CAAAniExplicitMP,DataExtension,CATBaseUnknown,STRUCTURAL_AeroMeshPart);

//-----------------------------------------------------------------------------
// CAAAniExplicitMP : constructor
//-----------------------------------------------------------------------------
CAAAniExplicitMP::CAAAniExplicitMP():
CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAAniExplicitMP : destructor
//-----------------------------------------------------------------------------
CAAAniExplicitMP::~CAAAniExplicitMP()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATISamExplicitation.h"
TIEchain_CATISamExplicitation(CAAAniExplicitMP);
//-----------------------------------------------------------------------------
// Implements CATISamExplicit::Explicit
//-----------------------------------------------------------------------------
HRESULT CAAAniExplicitMP::TranslateToFieldModel(CATISpecObject* iFeatToTranslate,
                                                CATISamAnalysisModel* iFEMModel,
                                                CATAnalysisExplicitListUsr& iOldExplObjects,
                                                CATAnalysisExplicitListUsr& oNewExplObjects)
{
  CATDocument *pFifDoc = NULL ;
  HRESULT hr = GetLinkedDoc(iFeatToTranslate, pFifDoc);
  if (NULL == pFifDoc) return E_FAIL;

  CAAIAniAeroImport_var spAeroImport = pFifDoc;
  if ( ! spAeroImport) return E_FAIL;

  return spAeroImport->TranslateToFieldModel(iFeatToTranslate,
                                             iFEMModel,
                                             iOldExplObjects,
                                             oNewExplObjects);
}
//==========================================================================================
HRESULT CAAAniExplicitMP::GetLinkedDoc (CATISpecObject* iFeatToTranslate, CATDocument* &oDoc)
{
  HRESULT hr = S_OK;
  oDoc = NULL;

  if (NULL == iFeatToTranslate) return E_FAIL;
  CATISpecObject* piLink = NULL;

  CATISpecAttrAccess *piMPAc = NULL;
  iFeatToTranslate -> QueryInterface(IID_CATISpecAttrAccess,(void **) &piMPAc);
  if (NULL != piMPAc)
  {
    CATISpecAttrKey * piKey = piMPAc -> GetAttrKey("InputLink");
    if (piKey) {
      piLink = piMPAc -> GetSpecObject(piKey);
      piKey -> Release();piKey = NULL;
    }
    piMPAc -> Release();piMPAc = NULL;
  }

  CATILinkableObject * linkable = NULL;

  if (piLink)
  {
    CATISpecAttrAccess *LinkDoc = NULL;
    piLink -> QueryInterface(IID_CATISpecAttrAccess,(void **) &LinkDoc);
    piLink -> Release (); piLink = NULL;

    if (LinkDoc)
    {
      CATISpecAttrKey * piKey = LinkDoc -> GetAttrKey("ExternDoc");
      if (piKey) {
        linkable = LinkDoc -> GetExternalObject(piKey,ANYWHERE);
        piKey -> Release(); piKey = NULL;
      }
      if (NULL == linkable) return E_FAIL;
      oDoc = linkable->GetDocument();
      linkable->Release();linkable = NULL;
      CATUnicodeString NameDoc;
      if (oDoc) CATSamDocumentTools::GetFileStorage(oDoc,NameDoc);
 
      else
        hr = E_FAIL;
//
      LinkDoc -> Release ();LinkDoc = NULL;
    }
  }
  else 
    hr = E_FAIL;

  return hr;
}
