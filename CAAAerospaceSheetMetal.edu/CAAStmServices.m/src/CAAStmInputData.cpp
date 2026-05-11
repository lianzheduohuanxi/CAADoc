//============================================================================================
// COPYRIGHT Dassault Systemes 2004
//============================================================================================
// CAAStmInputData.h
// Header definition of CAAStmInputData
//============================================================================================
//
// Usage notes:
//
//  This class exposes services to get or set Input Data in Aerospace Sheet Metal samples .
//
//============================================================================================
//
#include "CAAStmInputData.h"

// ---------------------------------------------------------------------------------------------
CAAStmInputData::CAAStmInputData()
  {
  _InputPartPath  = "";
  _OutputPartPath = "";
  _LengthUnit     = "";
    
  _Display        = FALSE;

  _SupportGeomToSet = FALSE;
  _SupportGeomName  = "";
      
  _MaterialOrientToSet = FALSE;
  _MaterialOrient      = CATOrientationUnknown;
    
  _BoundaryToSet = FALSE;
  _LimitsGeomNameList.RemoveAll();

  _ModifFlange     = FALSE;
  _ModifFlangeName = "";

  _BaseFeatureToSet     = FALSE;
  _BaseFeatureName      = "";
  _BaseRadiusTypeToSet  = FALSE;
  _BaseRadiusTypeName   = "";
  _BaseRadiusValueToSet = FALSE;
  _BaseRadiusValue      = 0.;

  _SupportTypeToSet   = FALSE;
  _SupportTypeName    = "";
  _SupportLengthToSet = FALSE;
  _SupportLengthValue = 0.;
  _SupportApproxToSet = FALSE;
  _SupportApproxValue = 0.;
  
  _EOPTypeToSet   = FALSE;
  _EOPTypeName    = "";
  _EOPGeomToSet   = FALSE;
  _EOPGeomName    = "";
  _EOPLengthToSet = FALSE;
  _EOPLengthValue = 0.;

  _BaseFeatureOrientToSet = FALSE;
  _BaseFeatureOrient      = CATOrientationUnknown;
  _FlangeSurfOrientToSet  = FALSE;
  _FlangeSurfOrient       = CATOrientationUnknown;
 
  _Side1TypeToSet     = FALSE;
  _Side1TypeName      = "";
  _Side1GeomToSet     = FALSE;
  _Side1GeomName      = "";
  _Corner1TypeToSet   = FALSE;
  _Corner1TypeName    = "";
  _Corner1RadiusToSet = FALSE;
  _Corner1RadiusValue = 0.;

  _Side2TypeToSet     = FALSE;
  _Side2TypeName      = "";
  _Side2GeomToSet     = FALSE;
  _Side2GeomName      = "";
  _Corner2TypeToSet   = FALSE;
  _Corner2TypeName    = "";
  _Corner2RadiusToSet = FALSE;
  _Corner2RadiusValue = 0.;

  _ProcessTypeToSet = FALSE;
  _ProcessTypeName  = "";
  _K_FactorToSet    = FALSE;
  _K_FactorValue    = 0.;

  _CompensJoggleTypeToSet = FALSE;
  _CompensJoggleTypeName  = "";
  _CompensSide1TypeToSet  = FALSE;
  _CompensSide1TypeName   = "";
  _CompensSide1ValueToSet = FALSE;
  _CompensSide1Value      = 0.;
  _CompensSide2TypeToSet  = FALSE;
  _CompensSide2TypeName   = "";
  _CompensSide2ValueToSet = FALSE;
  _CompensSide2Value      = 0.;

  _ModifJoggle       = FALSE;
  _ModifJoggleName   = "";
      
  _PlaneGeomToSet    = FALSE;
  _PlaneGeomName     = "";
  
  _DepthValueToSet   = FALSE;
  _DepthValue        = 0.;
  _DepthOrientToSet  = FALSE;
  _DepthOrient       = CATOrientationUnknown;

  _RunoutValueToSet  = FALSE;
  _RunoutValue       = 0.;
  _RunoutOrientToSet = FALSE;
  _RunoutOrient      = CATOrientationUnknown;
  
  _ClearanceValueToSet = FALSE;
  _ClearanceValue      = 0.;

  _StartRadiusValueToSet = FALSE;
  _StartRadiusValue      = 0.;
  _EndRadiusValueToSet   = FALSE;
  _EndRadiusValue        = 0.;
  }
 
// ---------------------------------------------------------------------------------------------
CAAStmInputData::~CAAStmInputData()
  {
  _InputPartPath  = "";
  _OutputPartPath = "";
  _LengthUnit     = "";
    
  _Display        = FALSE;

  _SupportGeomToSet = FALSE;
  _SupportGeomName  = "";
      
  _MaterialOrientToSet = FALSE;
  _MaterialOrient      = CATOrientationUnknown;
    
  _BoundaryToSet = FALSE;
  _LimitsGeomNameList.RemoveAll();

  _ModifFlange     = FALSE;
  _ModifFlangeName = "";

  _BaseFeatureToSet     = FALSE;
  _BaseFeatureName      = "";
  _BaseRadiusTypeToSet  = FALSE;
  _BaseRadiusTypeName   = "";
  _BaseRadiusValueToSet = FALSE;
  _BaseRadiusValue      = 0.;

  _SupportTypeToSet   = FALSE;
  _SupportTypeName    = "";
  _SupportLengthToSet = FALSE;
  _SupportLengthValue = 0.;
  _SupportApproxToSet = FALSE;
  _SupportApproxValue = 0.;
  
  _EOPTypeToSet   = FALSE;
  _EOPTypeName    = "";
  _EOPGeomToSet   = FALSE;
  _EOPGeomName    = "";
  _EOPLengthToSet = FALSE;
  _EOPLengthValue = 0.;

  _BaseFeatureOrientToSet = FALSE;
  _BaseFeatureOrient      = CATOrientationUnknown;
  _FlangeSurfOrientToSet  = FALSE;
  _FlangeSurfOrient       = CATOrientationUnknown;
 
  _Side1TypeToSet     = FALSE;
  _Side1TypeName      = "";
  _Side1GeomToSet     = FALSE;
  _Side1GeomName      = "";
  _Corner1TypeToSet   = FALSE;
  _Corner1TypeName    = "";
  _Corner1RadiusToSet = FALSE;
  _Corner1RadiusValue = 0.;

  _Side2TypeToSet     = FALSE;
  _Side2TypeName      = "";
  _Side2GeomToSet     = FALSE;
  _Side2GeomName      = "";
  _Corner2TypeToSet   = FALSE;
  _Corner2TypeName    = "";
  _Corner2RadiusToSet = FALSE;
  _Corner2RadiusValue = 0.;

  _ProcessTypeToSet = FALSE;
  _ProcessTypeName  = "";
  _K_FactorToSet    = FALSE;
  _K_FactorValue    = 0.;

  _CompensJoggleTypeToSet = FALSE;
  _CompensJoggleTypeName  = "";
  _CompensSide1TypeToSet  = FALSE;
  _CompensSide1TypeName   = "";
  _CompensSide1ValueToSet = FALSE;
  _CompensSide1Value      = 0.;
  _CompensSide2TypeToSet  = FALSE;
  _CompensSide2TypeName   = "";
  _CompensSide2ValueToSet = FALSE;
  _CompensSide2Value      = 0.;

  _ModifJoggle       = FALSE;
  _ModifJoggleName   = "";
      
  _PlaneGeomToSet    = FALSE;
  _PlaneGeomName     = "";
  
  _DepthValueToSet   = FALSE;
  _DepthValue        = 0.;
  _DepthOrientToSet  = FALSE;
  _DepthOrient       = CATOrientationUnknown;

  _RunoutValueToSet  = FALSE;
  _RunoutValue       = 0.;
  _RunoutOrientToSet = FALSE;
  _RunoutOrient      = CATOrientationUnknown;
  
  _ClearanceValueToSet = FALSE;
  _ClearanceValue      = 0.;

  _StartRadiusValueToSet = FALSE;
  _StartRadiusValue      = 0.;
  _EndRadiusValueToSet   = FALSE;
  _EndRadiusValue        = 0.;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetInputPartPath ()
  {
  return _InputPartPath;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetOutputPartPath ()
  {
  return _OutputPartPath;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetLengthUnit ()
  {
  return _LengthUnit;
  }
    
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetDisplay ()
  {
  return _Display;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSupportGeomToSet ()
  {
  return _SupportGeomToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetSupportGeomName ()
  {
  return _SupportGeomName;
  }
      
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetMaterialOrientToSet ()
  {
  return _MaterialOrientToSet;
  }

// ---------------------------------------------------------------------------------------------
CATOrientation CAAStmInputData::GetMaterialOrient ()
  {
  return _MaterialOrient;
  }
    
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetBoundaryToSet ()
  {
  return _BoundaryToSet;
  }

// ---------------------------------------------------------------------------------------------
CATListOfCATUnicodeString CAAStmInputData::GetLimitsGeomNameList ()
  {
  return _LimitsGeomNameList;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetModifFlange ()
  {
  return _ModifFlange;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetModifFlangeName ()
  {
  return _ModifFlangeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetBaseFeatureToSet ()
  {
  return _BaseFeatureToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetBaseFeatureName ()
  {
  return _BaseFeatureName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetBaseRadiusTypeToSet ()
  {
  return _BaseRadiusTypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetBaseRadiusTypeName ()
  {
  return _BaseRadiusTypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetBaseRadiusValueToSet ()
  {
  return _BaseRadiusValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetBaseRadiusValue ()
  {
  return _BaseRadiusValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSupportTypeToSet ()
  {
  return _SupportTypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetSupportTypeName ()
  {
  return _SupportTypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSupportLengthToSet ()
  {
  return _SupportLengthToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetSupportLengthValue ()
  {
  return _SupportLengthValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSupportApproxToSet ()
  {
  return _SupportApproxToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetSupportApproxValue ()
  {
  return _SupportApproxValue;
  }
  
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetEOPTypeToSet ()
  {
  return _EOPTypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetEOPTypeName ()
  {
  return _EOPTypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetEOPGeomToSet ()
  {
  return _EOPGeomToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetEOPGeomName ()
  {
  return _EOPGeomName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetEOPLengthToSet ()
  {
  return _EOPLengthToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetEOPLengthValue ()
  {
  return _EOPLengthValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetBaseFeatureOrientToSet ()
  {
  return _BaseFeatureOrientToSet;
  }

// ---------------------------------------------------------------------------------------------
CATOrientation CAAStmInputData::GetBaseFeatureOrient ()
  {
  return _BaseFeatureOrient;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetFlangeSurfOrientToSet ()
  {
  return _FlangeSurfOrientToSet;
  }

// ---------------------------------------------------------------------------------------------
CATOrientation CAAStmInputData::GetFlangeSurfOrient ()
  {
  return _FlangeSurfOrient;
  }
  
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSide1TypeToSet ()
  {
  return _Side1TypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetSide1TypeName ()
  {
  return _Side1TypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSide1GeomToSet ()
  {
  return _Side1GeomToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetSide1GeomName ()
  {
  return _Side1GeomName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCorner1TypeToSet ()
  {
  return _Corner1TypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetCorner1TypeName ()
  {
  return _Corner1TypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCorner1RadiusToSet ()
  {
  return _Corner1RadiusToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetCorner1RadiusValue ()
  {
  return _Corner1RadiusValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSide2TypeToSet ()
  {
  return _Side2TypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetSide2TypeName ()
  {
  return _Side2TypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetSide2GeomToSet ()
  {
  return _Side2GeomToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetSide2GeomName ()
  {
  return _Side2GeomName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCorner2TypeToSet ()
  {
  return _Corner2TypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetCorner2TypeName ()
  {
  return _Corner2TypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCorner2RadiusToSet ()
  {
  return _Corner2RadiusToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetCorner2RadiusValue ()
  {
  return _Corner2RadiusValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetProcessTypeToSet ()
  {
  return _ProcessTypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetProcessTypeName ()
  {
  return _ProcessTypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetK_FactorToSet ()
  {
  return _K_FactorToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetK_FactorValue ()
  {
  return _K_FactorValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCompensJoggleTypeToSet ()
  {
  return _CompensJoggleTypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetCompensJoggleTypeName ()
  {
  return _CompensJoggleTypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCompensSide1TypeToSet ()
  {
  return _CompensSide1TypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetCompensSide1TypeName ()
  {
  return _CompensSide1TypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCompensSide1ValueToSet ()
  {
  return _CompensSide1ValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetCompensSide1Value ()
  {
  return _CompensSide1Value;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCompensSide2TypeToSet ()
  {
  return _CompensSide2TypeToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetCompensSide2TypeName ()
  {
  return _CompensSide2TypeName;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetCompensSide2ValueToSet ()
  {
  return _CompensSide2ValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetCompensSide2Value ()
  {
  return _CompensSide2Value;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetModifJoggle ()
  {
  return _ModifJoggle;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetModifJoggleName ()
  {
  return _ModifJoggleName;
  }
      
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetPlaneGeomToSet ()
  {
  return _PlaneGeomToSet;
  }

// ---------------------------------------------------------------------------------------------
CATUnicodeString CAAStmInputData::GetPlaneGeomName ()
  {
  return _PlaneGeomName;
  }
  
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetDepthValueToSet ()
  {
  return _DepthValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetDepthValue ()
  {
  return _DepthValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetDepthOrientToSet ()
  {
  return _DepthOrientToSet;
  }

// ---------------------------------------------------------------------------------------------
CATOrientation CAAStmInputData::GetDepthOrient ()
  {
  return _DepthOrient;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetRunoutValueToSet ()
  {
  return _RunoutValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetRunoutValue ()
  {
  return _RunoutValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetRunoutOrientToSet ()
  {
  return _RunoutOrientToSet;
  }

// ---------------------------------------------------------------------------------------------
CATOrientation CAAStmInputData::GetRunoutOrient ()
  {
  return _RunoutOrient;
  }
  
// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetClearanceValueToSet ()
  {
  return _ClearanceValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetClearanceValue ()
  {
  return _ClearanceValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetStartRadiusValueToSet ()
  {
  return _StartRadiusValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetStartRadiusValue ()
  {
  return _StartRadiusValue;
  }

// ---------------------------------------------------------------------------------------------
CATBoolean CAAStmInputData::GetEndRadiusValueToSet ()
  {
  return _EndRadiusValueToSet;
  }

// ---------------------------------------------------------------------------------------------
double CAAStmInputData::GetEndRadiusValue ()
  {
  return _EndRadiusValue;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetInputPartPath (CATUnicodeString & Val)
  {
  _InputPartPath = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetOutputPartPath (CATUnicodeString & Val)
  {
  _OutputPartPath = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetLengthUnit (CATUnicodeString & Val)
  {
  _LengthUnit = Val;
  }
    
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetDisplay (CATBoolean & Val)
  {
  _Display = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportGeomToSet (CATBoolean & Val)
  {
  _SupportGeomToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportGeomName (CATUnicodeString & Val)
  {
  _SupportGeomName = Val;
  }
     
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetMaterialOrientToSet (CATBoolean & Val)
  {
  _MaterialOrientToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetMaterialOrient (CATOrientation & Val)
  {
  _MaterialOrient = Val;
  }
    
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBoundaryToSet (CATBoolean & Val)
  {
  _BoundaryToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetLimitsGeomNameList (CATListOfCATUnicodeString & Val)
  {
  _LimitsGeomNameList = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetModifFlange (CATBoolean & Val)
  {
  _ModifFlange = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetModifFlangeName (CATUnicodeString & Val)
  {
  _ModifFlangeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseFeatureToSet (CATBoolean & Val)
  {
  _BaseFeatureToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseFeatureName (CATUnicodeString & Val)
  {
  _BaseFeatureName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseRadiusTypeToSet (CATBoolean & Val)
  {
  _BaseRadiusTypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseRadiusTypeName (CATUnicodeString & Val)
  {
  _BaseRadiusTypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseRadiusValueToSet (CATBoolean & Val)
  {
  _BaseRadiusValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseRadiusValue (double & Val)
  {
  _BaseRadiusValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportTypeToSet (CATBoolean & Val)
  {
  _SupportTypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportTypeName (CATUnicodeString & Val)
  {
  _SupportTypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportLengthToSet (CATBoolean & Val)
  {
  _SupportLengthToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportLengthValue (double & Val)
  {
  _SupportLengthValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportApproxToSet (CATBoolean & Val)
  {
  _SupportApproxToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSupportApproxValue (double & Val)
  {
  _SupportApproxValue = Val;
  }
  
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEOPTypeToSet (CATBoolean & Val)
  {
  _EOPTypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEOPTypeName (CATUnicodeString & Val)
  {
  _EOPTypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEOPGeomToSet (CATBoolean & Val)
  {
  _EOPGeomToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEOPGeomName (CATUnicodeString & Val)
  {
  _EOPGeomName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEOPLengthToSet (CATBoolean & Val)
  {
  _EOPLengthToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEOPLengthValue (double & Val)
  {
  _EOPLengthValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseFeatureOrientToSet (CATBoolean & Val)
  {
  _BaseFeatureOrientToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetBaseFeatureOrient (CATOrientation & Val)
  {
  _BaseFeatureOrient = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetFlangeSurfOrientToSet (CATBoolean & Val)
  {
  _FlangeSurfOrientToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetFlangeSurfOrient (CATOrientation & Val)
  {
  _FlangeSurfOrient = Val;
  }
  
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide1TypeToSet (CATBoolean & Val)
  {
  _Side1TypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide1TypeName (CATUnicodeString & Val)
  {
  _Side1TypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide1GeomToSet (CATBoolean & Val)
  {
  _Side1GeomToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide1GeomName (CATUnicodeString & Val)
  {
  _Side1GeomName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner1TypeToSet (CATBoolean & Val)
  {
  _Corner1TypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner1TypeName (CATUnicodeString & Val)
  {
  _Corner1TypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner1RadiusToSet (CATBoolean & Val)
  {
  _Corner1RadiusToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner1RadiusValue (double & Val)
  {
  _Corner1RadiusValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide2TypeToSet (CATBoolean & Val)
  {
  _Side2TypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide2TypeName (CATUnicodeString & Val)
  {
  _Side2TypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide2GeomToSet (CATBoolean & Val)
  {
  _Side2GeomToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetSide2GeomName (CATUnicodeString & Val)
  {
  _Side2GeomName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner2TypeToSet (CATBoolean & Val)
  {
  _Corner2TypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner2TypeName (CATUnicodeString & Val)
  {
  _Corner2TypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner2RadiusToSet (CATBoolean & Val)
  {
  _Corner2RadiusToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCorner2RadiusValue (double & Val)
  {
  _Corner2RadiusValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetProcessTypeToSet (CATBoolean & Val)
  {
  _ProcessTypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetProcessTypeName (CATUnicodeString & Val)
  {
  _ProcessTypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetK_FactorToSet (CATBoolean & Val)
  {
  _K_FactorToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetK_FactorValue (double & Val)
  {
  _K_FactorValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensJoggleTypeToSet (CATBoolean & Val)
  {
  _CompensJoggleTypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensJoggleTypeName (CATUnicodeString & Val)
  {
  _CompensJoggleTypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide1TypeToSet (CATBoolean & Val)
  {
  _CompensSide1TypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide1TypeName (CATUnicodeString & Val)
  {
  _CompensSide1TypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide1ValueToSet (CATBoolean & Val)
  {
  _CompensSide1ValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide1Value (double & Val)
  {
  _CompensSide1Value = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide2TypeToSet (CATBoolean & Val)
  {
  _CompensSide2TypeToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide2TypeName (CATUnicodeString & Val)
  {
  _CompensSide2TypeName = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide2ValueToSet (CATBoolean & Val)
  {
  _CompensSide2ValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetCompensSide2Value (double & Val)
  {
  _CompensSide2Value = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetModifJoggle (CATBoolean & Val)
  {
  _ModifJoggle = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetModifJoggleName (CATUnicodeString & Val)
  {
  _ModifJoggleName = Val;
  }
      
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetPlaneGeomToSet (CATBoolean & Val)
  {
  _PlaneGeomToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetPlaneGeomName (CATUnicodeString & Val)
  {
  _PlaneGeomName = Val;
  }
  
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetDepthValueToSet (CATBoolean & Val)
  {
  _DepthValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetDepthValue (double & Val)
  {
  _DepthValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetDepthOrientToSet (CATBoolean & Val)
  {
  _DepthOrientToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetDepthOrient (CATOrientation & Val)
  {
  _DepthOrient = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetRunoutValueToSet (CATBoolean & Val)
  {
  _RunoutValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetRunoutValue (double & Val)
  {
  _RunoutValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetRunoutOrientToSet (CATBoolean & Val)
  {
  _RunoutOrientToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetRunoutOrient (CATOrientation & Val)
  {
  _RunoutOrient = Val;
  }
  
// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetClearanceValueToSet (CATBoolean & Val)
  {
  _ClearanceValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetClearanceValue (double & Val)
  {
  _ClearanceValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetStartRadiusValueToSet (CATBoolean & Val)
  {
  _StartRadiusValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetStartRadiusValue (double & Val)
  {
  _StartRadiusValue = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEndRadiusValueToSet (CATBoolean & Val)
  {
  _EndRadiusValueToSet = Val;
  }

// ---------------------------------------------------------------------------------------------
void CAAStmInputData::SetEndRadiusValue (double & Val)
  {
  _EndRadiusValue = Val;
  }







