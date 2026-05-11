/* -*-c++-*- */
#ifndef CAAMaiUdfForGeomMacroMotions_h
#define CAAMaiUdfForGeomMacroMotions_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAMaiUdfForGeomMacroMotions: implementation of the 
// CATIMfgMacroMotionsGeomMapping CAA interface for a type of User Defined Features
//
// ===================================================================

#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

class CATUnicodeString;

class CAAMaiUdfForGeomMacroMotions : public CATBaseUnknown
{
  CATDeclareClass;

  public:
 
    CAAMaiUdfForGeomMacroMotions();
    virtual ~CAAMaiUdfForGeomMacroMotions();

    HRESULT MapGeomOnApproachMacroMotion (CATUnicodeString iActivityType, int iMacroMotionType,
      CATListOfInt iElementaryMotionTypeList, CATListValCATBaseUnknown_var &oGeometryList);

    HRESULT MapGeomOnRetractMacroMotion (CATUnicodeString iActivityType, int iMacroMotionType,
      CATListOfInt iElementaryMotionTypeList, CATListValCATBaseUnknown_var &oGeometryList);
};
#endif

