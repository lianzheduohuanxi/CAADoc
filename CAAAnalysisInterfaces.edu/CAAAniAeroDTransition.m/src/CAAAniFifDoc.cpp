// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniFifDoc.cpp
// Provide implementation to interface CATIPersistent
// Sample of code for managing Analysis data for Aero Dynamic.
// This file is created in order to be able to consider the input file as a CATDocument.
//===================================================================
#include "CAAAniFifDoc.h"                 // Local Include
#include "CATSamDocumentTools.h"
#include "CATDocument.h"
#include "CATILinkableObject.h"
#include "CATUnicodeString.h"

CATBeginImplementClass(CAAAniFifDoc,DataExtension,CATBaseUnknown,fif); 
CATAddClassExtension   (print);  
CATEndImplementClass   (CAAAniFifDoc);  

//-----------------------------------------------------------------------------
// CAAAniFifDoc : constructor
//-----------------------------------------------------------------------------
CAAAniFifDoc::CAAAniFifDoc():
    CATBaseUnknown()
{}
//-----------------------------------------------------------------------------
// CAAAniFifDoc : destructor
//-----------------------------------------------------------------------------
CAAAniFifDoc::~CAAAniFifDoc()
{}
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIPersistent.h"  
TIE_CATIPersistent(CAAAniFifDoc);  
//=====================================================================
CATBoolean CAAAniFifDoc::Dirty ()
{   return FALSE ; }
//=====================================================================
void CAAAniFifDoc::Save()
{}
//=====================================================================
void CAAAniFifDoc::SaveAs (char * storagePrintableName,CATBoolean becameCurrent) 
{
// Retreive this as CATDocument
  CATDocument* pDoc = NULL;
  CATILinkableObject *piLinka = NULL;
  QueryInterface(IID_CATILinkableObject,(void **)&piLinka);
  if (NULL != piLinka)  {
    pDoc = piLinka -> GetDocument();
    piLinka -> Release(); piLinka = NULL;
  }

  //CALL  CATSamDocumentTools
  CATUnicodeString CopyTarget (storagePrintableName);
  CATSamDocumentTools::SupportFileSaveMgt(pDoc,CopyTarget);
}  
//=====================================================================
void CAAAniFifDoc::SaveAs_B (SEQUENCE(octet) storageName,CATBoolean becameCurrent)
{}
//=====================================================================
void CAAAniFifDoc::Load( char *  storagePrintableName , CATBoolean readOnlyFlag ) 
{}
//=====================================================================
void CAAAniFifDoc::Load_B (SEQUENCE(octet) storageName,CATBoolean readOnly)
{}
//=====================================================================

