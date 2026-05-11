// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAE5iUEDocumentName.cpp
// Header definition of CAAE5iUEDocumentName
//
//===================================================================
//
// Purpose: customize the name displayed in CATIA V5 for ENOVIA V5
//          documents by implementing the CATIPDMUEDocumentName interface
// Usage notes: see CAAE5iUEDocumentName use case in CAA Encyclopedia
//  
//===================================================================
//
//  Dec 2005 creation DRT
//===================================================================
#include "CAAE5iUEDocumentName.h"
#include "CATIPDMUEDocumentName.h"
#include "CATDocument.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLib.h"
#include "CATOmbDocPropertyServices.h"
#include "CATIPDMPersistency.h"
#include <stdio.h>

//missing macro definition... CATCreateClass(CAAE5iUEDocumentName);

#include "TIE_CATIPDMUEDocumentName.h"
TIEchain_CATIPDMUEDocumentName(CAAE5iUEDocumentName);
CATImplementClass( CAAE5iUEDocumentName, DataExtension, CATBaseUnknown, CATUEPDMDocumentName );


HRESULT CAAE5iUEDocumentName::ComputeDocumentName (
     CATUnicodeString &iDocumentDomain,
     CATUnicodeString &iDocumentV_ID,
     CATUnicodeString &iDocumentV_version,
     CATUnicodeString &iDocumentV_extension,
     CATUnicodeString &iPartV_ID,
     CATUnicodeString &iPartV_version,
     CATUnicodeString &oDocumentName)
{ 
  printf(">>> CAAE5iUEDocumentName::ComputeDocumentName V_ID = %s\n", iDocumentV_ID.CastToCharPtr());
  return S_FALSE;
}

HRESULT CAAE5iUEDocumentName::ComputeDocumentName (CATDocument *iDocument, CATUnicodeString & oDocumentName)
{
  HRESULT hr = S_FALSE; // meaning we do not override the default display name

  // I - Extract document name and type from the storage name

  CATUnicodeString docStorageName;   // storage name E.G. ENOVIA5\MyPart.CATPart
  CATUnicodeString docPath;          // path         E.G. ENOVIA5
  CATUnicodeString docName;          // name         E.G. MyPart
  CATUnicodeString docType;          // extension    E.G. CATPart

  if (! iDocument) return E_FAIL;
  docStorageName = iDocument->StorageName();

  printf(">>> CAAE5iUEDocumentName::ComputeDocumentName storage name = %s\n", docStorageName.CastToCharPtr());
  char strDocPath[300], strDocName[300];
  CATSplitPath(docStorageName.CastToCharPtr(),strDocPath,strDocName);
  docPath = strDocPath;
  docName = strDocName;
  
  int dot = docStorageName.SearchSubString(".",0,CATUnicodeString::CATSearchModeBackward);
  if (dot<0)
  {
    printf(">>> CAAE5iUEDocumentName::ComputeDocumentName failed to get document's type\n");
    return E_FAIL;
  }

  docName=docStorageName.SubString(0,dot);
  docType=docStorageName;
  docType.Remove(0,dot+1);
  
  // II - Filter out document that are not kept in ENOVIA V5 (PRC + some intermediate CATProducts)

  CATIPDMPersistency_var hPersistency(iDocument);
  if(!!hPersistency)
  {
    CATIPDMPersistency::VaultMode vaultMode;
    HRESULT persistencyHR = hPersistency->CurrentVaultMode(vaultMode);
    if ( SUCCEEDED(persistencyHR) && (vaultMode == CATIPDMPersistency::VolatileExposed) )
      return S_FALSE;
  }

  // III - Compute document display name based on database attributes and document name + type

  CATIDocId*  docId = NULL;
  CATUnicodeString status;
  CATUnicodeString version;

  HRESULT rc = iDocument->GetDocId(&docId);
  if (SUCCEEDED(rc))
  {
    // Retrieve ENOVIA V5 document revision's V_version attribute E.G. "---", "--A"
    CATOmbDocPropertyServices::GetValue(docId, "ENOVIA5.DocumentVersion.Value", version);

    // Retrieve ENOVIA V5 document revision's V_status attribute E.G. "InWork", "Released"
    CATOmbDocPropertyServices::GetValue(docId, "ENOVIA5.DocumentStatus.Value", status);

    if (version.GetLengthInChar() && status.GetLengthInChar())
    {
      oDocumentName = docName + CATUnicodeString("_rev") + version + CATUnicodeString("(") + status + CATUnicodeString(").") + docType;
      printf(">>> CAAE5iUEDocumentName::ComputeDocumentName display name = %s\n", oDocumentName.CastToCharPtr());
      hr = S_OK;
    }
  }
  else
  {
    printf(">>> CAAE5iUEDocumentName::ComputeDocumentName failed to get document's DocId\n");
    hr = E_FAIL;
  }
  return hr;
}
