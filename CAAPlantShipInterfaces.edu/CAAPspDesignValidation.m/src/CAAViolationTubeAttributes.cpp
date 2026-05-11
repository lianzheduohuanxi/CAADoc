/**
 * @quickreview eml 07:04:25 Replace tabs with spaces.
 * @fullreview eml svo 07:04:24 Creation
 */
//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CAAViolationTubeAttributes.cpp
//
//=============================================================================
//
// Implementation notes:  Violation object
//
//=============================================================================
//
// Creation:  2007 April 23                                    Eric Miller
//
//=============================================================================

#include "CAAViolationTubeAttributes.h"

#include "CATError.h"
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//-----------------------------------------------------------------------------
// CAAViolationTubeAttributes : constructor
//-----------------------------------------------------------------------------
CAAViolationTubeAttributes::CAAViolationTubeAttributes(const CATUnicodeString& iType,
                                                       const CATUnicodeString& iCheck,
                                                       const CATUnicodeString& iResource)
  :CATPspCheckViolation( iType, iCheck, iResource )
{ 
  _uPressure = "";
  _uNominalSize = "";
  _uMaterial = "";
  _uAuthorizedValues = "";
}

//-----------------------------------------------------------------------------
// CAAViolationTubeAttributes : destructor
//-----------------------------------------------------------------------------
CAAViolationTubeAttributes::~CAAViolationTubeAttributes()
{}

//-----------------------------------------------------------------------------
void CAAViolationTubeAttributes::SetInfo(CATUnicodeString &iuPressure, 
                                         CATUnicodeString &iuNominalSize, 
                                         CATUnicodeString &iuMaterial, 
                                         CATUnicodeString &iuAuthorizedValues)
{
  _uPressure = iuPressure;
  _uNominalSize = iuNominalSize;
  _uMaterial = iuMaterial;
  _uAuthorizedValues = iuAuthorizedValues;
}

//-----------------------------------------------------------------------------
HRESULT CAAViolationTubeAttributes::GetCheckViolationData(int& oRow, 
                                                          CATListValCATUnicodeString** oLValues)
{
  HRESULT returnCode = CATReturnFailure;

  oRow = 1;

  *oLValues = new CATListValCATUnicodeString[oRow];

  if ( *oLValues )
  {
    (*oLValues)[0].Append(_uPressure);
    (*oLValues)[0].Append(_uNominalSize);
    (*oLValues)[0].Append(_uMaterial);
    (*oLValues)[0].Append(_uAuthorizedValues);

    returnCode = CATReturnSuccess;
  }

  return returnCode;
}
