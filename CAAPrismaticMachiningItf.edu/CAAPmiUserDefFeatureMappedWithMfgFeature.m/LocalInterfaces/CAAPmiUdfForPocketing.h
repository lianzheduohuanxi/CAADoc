/* -*-c++-*- */
#ifndef CAAPmiUdfForPocketing_h
#define CAAPmiUdfForPocketing_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfForPocketing: implementation of the 
// CATIMfgMappingForPocketing CAA interface for a type of User Defined Features
//
// ===================================================================

#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

class CAAPmiUdfForPocketing : public CATBaseUnknown
{
  CATDeclareClass;

  public:
 
    CAAPmiUdfForPocketing();
    virtual ~CAAPmiUdfForPocketing();

    HRESULT GetPart (CATBaseUnknown_var & oPartElement);

    HRESULT GetRelimitingPlane (CATBaseUnknown_var & oRelimitingPlane);

    HRESULT GetGuidingCurves (CATListValCATBaseUnknown_var & oGuidingElements);

    HRESULT GetIslands (CATListValCATBaseUnknown_var& oListOfIslands, CATListOfInt& oNbOfCurvesByIsland);

};
#endif

