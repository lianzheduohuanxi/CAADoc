// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAE5iUEDocumentName.h
// Header definition of CAAE5iUEDocumentName
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Nov 2005  Creation: DRT
//===================================================================
#ifndef CAAE5iUEDocumentName_H
#define CAAE5iUEDocumentName_H

#include "CATBaseUnknown.h"
class CATUnicodeString;
class CATDocument;

//=================================================================================
class CAAE5iUEDocumentName: public CATBaseUnknown
{
  CATDeclareClass;
  HRESULT ComputeDocumentName (
     CATUnicodeString &iDocumentDomain,
     CATUnicodeString &iDocumentV_ID,
     CATUnicodeString &iDocumentV_version,
     CATUnicodeString &iDocumentV_extension,
     CATUnicodeString &iPartV_ID,
     CATUnicodeString &iPartV_version,
     CATUnicodeString &oDocumentName);

  HRESULT ComputeDocumentName (CATDocument *iDocument, CATUnicodeString & oDocumentName);
};
//===================================================================

#endif
