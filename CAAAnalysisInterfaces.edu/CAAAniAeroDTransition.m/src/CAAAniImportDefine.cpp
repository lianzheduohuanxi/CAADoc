// COPYRIGHT DASSAULT SYSTEMES 2004
//===================================================================
//
// CAAAniImportDefine.cpp
// Provide implementation to interface CATISamImportDefine
//    
//===================================================================
#include "CAAAniImportDefine.h"

// System prereq
#include "CATDocument.h"
#include "CAAIAniAeroImport.h"

CATImplementClass(CAAAniImportDefine,DataExtension,CATBaseUnknown,AeroDynamicImport);

//-----------------------------------------------------------------------------
// CAAAniImportDefine : constructor
//-----------------------------------------------------------------------------
CAAAniImportDefine::CAAAniImportDefine():CATESamImportDefineAdaptor()
{  
}

//-----------------------------------------------------------------------------
// CAAAniImportDefine : destructor
//-----------------------------------------------------------------------------
CAAAniImportDefine::~CAAAniImportDefine()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATISamImportDefine.h"
TIE_CATISamImportDefine(CAAAniImportDefine);

//=================================================================================================
// Implements CATISamImportDefine::GetFileTypes
// Output Argument   
//          oTypes : CATString List defining the suffix of the different allowed files.
//=================================================================================================
HRESULT CAAAniImportDefine::GetFileTypes(CATListValCATString& oTypes)
{
  oTypes.Append("fif");
  return S_OK;
}
//=================================================================================================
// Implements CATISamImportDefine::GetCommentForType
// Input  Argument
//           iType    : CATString defining the suffix of the file.
// Output Argument   
//           oComment : CATUnicodeString as comment for the File selection dialog box.
//=================================================================================================
HRESULT CAAAniImportDefine::GetCommentForType(const CATString iType,CATUnicodeString& oComment)
{
  if(iType == "fif")
	  oComment   = "Aerodynamic Mesh File";
  else
    return E_FAIL;

  return S_OK;
}

//=================================================================================================
// Implements CATISamImportDefine::Import
// Input Arguments
//            oImportedDoc : CATDocument to import
//            idocument    : Current CATAnalysis for import
//=================================================================================================
HRESULT CAAAniImportDefine::Import (CATDocument * iImportedDoc, CATDocument * iAnalysisDoc)
{
  HRESULT HR = E_FAIL;

  if (NULL == iImportedDoc) return E_INVALIDARG;
  if (NULL == iAnalysisDoc) return E_INVALIDARG;

  if (iImportedDoc->GetType() == CATUnicodeString("fif")) 
  {
    CAAIAniAeroImport_var spAeroImport(iImportedDoc);
    if (!!spAeroImport)HR = spAeroImport->Import(iAnalysisDoc);     
  }
  return HR;
}


