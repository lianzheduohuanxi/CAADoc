//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// CAAEMaiUserOppositeHandMachiningOptions.h
// Provides implementation to interface CATIMfgUserOppositeHandMachiningOptions
//=============================================================================

#include "CAAEMaiUserOppositeHandMachiningOptions.h"

#include "CATBaseUnknown.h"

//-----------------------------------------------------------------------------
// Supported Interface
//-----------------------------------------------------------------------------
CATImplementBOA (CATIMfgUserOppositeHandMachiningOptions, CAAEMaiUserOppositeHandMachiningOptions);

CATImplementClass(CAAEMaiUserOppositeHandMachiningOptions, Implementation, CATIMfgUserOppositeHandMachiningOptions, CATNull);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEMaiUserOppositeHandMachiningOptions::CAAEMaiUserOppositeHandMachiningOptions(): CATIMfgUserOppositeHandMachiningOptions() {}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEMaiUserOppositeHandMachiningOptions::~CAAEMaiUserOppositeHandMachiningOptions() {}

//-----------------------------------------------------------------------------
// GetNames
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserOppositeHandMachiningOptions::GetNames(CATUnicodeString & oOperationName, CATUnicodeString & oSettingName, CATUnicodeString & oRepositoryName)
{
  HRESULT RC=S_OK;
  {
    oOperationName  = "CAA Profile Contouring";
    oSettingName    = "ReverseMO_CAAProfileContouring";
    oRepositoryName = "NCMfgOperation";
  }
  return RC;
}
