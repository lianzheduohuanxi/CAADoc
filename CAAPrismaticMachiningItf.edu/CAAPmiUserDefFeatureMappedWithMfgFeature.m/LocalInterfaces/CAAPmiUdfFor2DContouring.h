/* -*-c++-*- */
#ifndef CAAPmiUdfFor2DContouring_h
#define CAAPmiUdfFor2DContouring_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfFor2DContouring: implementation of the 
// CATIMfgMappingForProfileContouring CAA interface for a type of User Defined Features
//
// ===================================================================

#include "CATBaseUnknown.h"
#include "CATPoint.h"
#include "CATLISTV_CATBaseUnknown.h"

class CAAPmiUdfFor2DContouring : public CATBaseUnknown
{
  CATDeclareClass;

  public:
 
    CAAPmiUdfFor2DContouring();
    virtual ~CAAPmiUdfFor2DContouring();

    HRESULT GetPart (CATBaseUnknown_var & oPartElement);

    HRESULT GetRelimitingPlane (CATBaseUnknown_var & oRelimitingPlane);

    HRESULT GetGuidingCurves (CATListValCATBaseUnknown_var & oGuidingElements,
                              int & oSide, CATPoint * oExtremity);

    HRESULT GetChecks (CATListValCATBaseUnknown_var & oChecks);

    HRESULT GetRelimitingElements (CATListValCATBaseUnknown_var & oFirstRelimitingElements,
      CATListValCATBaseUnknown_var & oSecondRelimitingElements);

};
#endif

