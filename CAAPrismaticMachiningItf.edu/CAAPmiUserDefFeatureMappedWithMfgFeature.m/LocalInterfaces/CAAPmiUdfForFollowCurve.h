/* -*-c++-*- */
#ifndef CAAPmiUdfForFollowCurve_h
#define CAAPmiUdfForFollowCurve_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfForFollowCurve: implementation of the 
// CATIMfgMappingForFollowCurve CAA interface for a type of User Defined Features
//
// ===================================================================

#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

class CAAPmiUdfForFollowCurve : public CATBaseUnknown
{
  CATDeclareClass;

  public:
 
    CAAPmiUdfForFollowCurve();
    virtual ~CAAPmiUdfForFollowCurve();

    HRESULT GetGuidingCurves (CATListValCATBaseUnknown_var & oAuxGuidingElements);

    HRESULT GetAuxiliaryGuidingCurves (CATListValCATBaseUnknown_var & oAuxGuidingElements);

    HRESULT GetChecks (CATListValCATBaseUnknown_var & oChecks);

    HRESULT GetRelimitingElements (CATListValCATBaseUnknown_var & oFirstRelimitingElements,
      CATListValCATBaseUnknown_var & oSecondRelimitingElements);

};
#endif

