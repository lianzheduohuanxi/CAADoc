#ifndef CAASTMINPUTDATA_H
#define CAASTMINPUTDATA_H

//============================================================================================
// COPYRIGHT Dassault Systemes 2004
//============================================================================================
/**
 * class CAAStmInputData.
 *
 * <b>Role</b>: store the input data of Aerospace Sheet Metal Features in CAA context.
 */
#include "CAAStmExportedBy.h"

#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATTopDefine.h"

class ExportedByCAAStmServices CAAStmInputData
  {
  public:
    
    CAAStmInputData();
    virtual ~CAAStmInputData();
    
    /**
     * <b>Role</b>: Methods to get the Input Data.
     *
     */
    
    // General Data :
    // --------------

    CATUnicodeString          GetInputPartPath  ();
    CATUnicodeString          GetOutputPartPath ();
    CATUnicodeString          GetLengthUnit     ();
    
    CATBoolean                GetDisplay ();

    CATBoolean                GetSupportGeomToSet ();
    CATUnicodeString          GetSupportGeomName  ();
      
    CATBoolean                GetMaterialOrientToSet ();
    CATOrientation            GetMaterialOrient      ();
    
    // Web :
    // -----
    
    CATBoolean                GetBoundaryToSet      ();
    CATListOfCATUnicodeString GetLimitsGeomNameList ();

    // Surfacic Flange :
    // -----------------

    CATBoolean                GetModifFlange     ();
    CATUnicodeString          GetModifFlangeName ();

    CATBoolean                GetBaseFeatureToSet     ();
    CATUnicodeString          GetBaseFeatureName      ();
    CATBoolean                GetBaseRadiusTypeToSet  ();
    CATUnicodeString          GetBaseRadiusTypeName   ();
    CATBoolean                GetBaseRadiusValueToSet ();
    double                    GetBaseRadiusValue      ();

    CATBoolean                GetSupportTypeToSet   ();
    CATUnicodeString          GetSupportTypeName    ();
    CATBoolean                GetSupportLengthToSet ();
    double                    GetSupportLengthValue ();
    CATBoolean                GetSupportApproxToSet ();
    double                    GetSupportApproxValue ();
  
    CATBoolean                GetEOPTypeToSet   ();
    CATUnicodeString          GetEOPTypeName    ();
    CATBoolean                GetEOPGeomToSet   ();
    CATUnicodeString          GetEOPGeomName    ();
    CATBoolean                GetEOPLengthToSet ();
    double                    GetEOPLengthValue ();

    CATBoolean                GetBaseFeatureOrientToSet ();
    CATOrientation            GetBaseFeatureOrient      ();
    CATBoolean                GetFlangeSurfOrientToSet  ();
    CATOrientation            GetFlangeSurfOrient       ();
  
    CATBoolean                GetSide1TypeToSet     ();
    CATUnicodeString          GetSide1TypeName      ();
    CATBoolean                GetSide1GeomToSet     ();
    CATUnicodeString          GetSide1GeomName      ();
    CATBoolean                GetCorner1TypeToSet   ();
    CATUnicodeString          GetCorner1TypeName    ();
    CATBoolean                GetCorner1RadiusToSet ();
    double                    GetCorner1RadiusValue ();

    CATBoolean                GetSide2TypeToSet     ();
    CATUnicodeString          GetSide2TypeName      ();
    CATBoolean                GetSide2GeomToSet     ();
    CATUnicodeString          GetSide2GeomName      ();
    CATBoolean                GetCorner2TypeToSet   ();
    CATUnicodeString          GetCorner2TypeName    ();
    CATBoolean                GetCorner2RadiusToSet ();
    double                    GetCorner2RadiusValue ();

    CATBoolean                GetProcessTypeToSet   ();
    CATUnicodeString          GetProcessTypeName    ();
    CATBoolean                GetK_FactorToSet      ();
    double                    GetK_FactorValue      ();

    CATBoolean                GetCompensJoggleTypeToSet ();
    CATUnicodeString          GetCompensJoggleTypeName  ();
    CATBoolean                GetCompensSide1TypeToSet  ();
    CATUnicodeString          GetCompensSide1TypeName   ();
    CATBoolean                GetCompensSide1ValueToSet ();
    double                    GetCompensSide1Value      ();
    CATBoolean                GetCompensSide2TypeToSet  ();
    CATUnicodeString          GetCompensSide2TypeName   ();
    CATBoolean                GetCompensSide2ValueToSet ();
    double                    GetCompensSide2Value      ();

    // Joggle :
    // --------

    CATBoolean                GetModifJoggle     ();
    CATUnicodeString          GetModifJoggleName ();
      
    CATBoolean                GetPlaneGeomToSet ();
    CATUnicodeString          GetPlaneGeomName  ();
  
    CATBoolean                GetDepthValueToSet   ();
    double                    GetDepthValue        ();
    CATBoolean                GetDepthOrientToSet  ();
    CATOrientation            GetDepthOrient       ();

    CATBoolean                GetRunoutValueToSet  ();
    double                    GetRunoutValue       ();
    CATBoolean                GetRunoutOrientToSet ();
    CATOrientation            GetRunoutOrient      ();
  
    CATBoolean                GetClearanceValueToSet ();
    double                    GetClearanceValue      ();

    CATBoolean                GetStartRadiusValueToSet ();
    double                    GetStartRadiusValue      ();
    CATBoolean                GetEndRadiusValueToSet   ();
    double                    GetEndRadiusValue        ();
    
    /**
     * <b>Role</b>: Methods to set the Input Data.
     *
     */
    
    // General Data :
    // --------------

    void SetInputPartPath  (CATUnicodeString & Val);
    void SetOutputPartPath (CATUnicodeString & Val);
    void SetLengthUnit     (CATUnicodeString & Val);
    
    void SetDisplay        (CATBoolean & Val);

    void SetSupportGeomToSet (CATBoolean & Val);
    void SetSupportGeomName  (CATUnicodeString & Val);
     
    void SetMaterialOrientToSet (CATBoolean & Val);
    void SetMaterialOrient      (CATOrientation & Val);
    
    // Web :
    // -----
    
    void SetBoundaryToSet      (CATBoolean & Val);
    void SetLimitsGeomNameList (CATListOfCATUnicodeString & Val);

    // Surfacic Flange :
    // -----------------

    void SetModifFlange     (CATBoolean & Val);
    void SetModifFlangeName (CATUnicodeString & Val);

    void SetBaseFeatureToSet     (CATBoolean & Val);
    void SetBaseFeatureName      (CATUnicodeString & Val);
    void SetBaseRadiusTypeToSet  (CATBoolean & Val);
    void SetBaseRadiusTypeName   (CATUnicodeString & Val);
    void SetBaseRadiusValueToSet (CATBoolean & Val);
    void SetBaseRadiusValue      (double & Val);

    void SetSupportTypeToSet   (CATBoolean & Val);
    void SetSupportTypeName    (CATUnicodeString & Val);
    void SetSupportLengthToSet (CATBoolean & Val);
    void SetSupportLengthValue (double & Val);
    void SetSupportApproxToSet (CATBoolean & Val);
    void SetSupportApproxValue (double & Val);
  
    void SetEOPTypeToSet   (CATBoolean & Val);
    void SetEOPTypeName    (CATUnicodeString & Val);
    void SetEOPGeomToSet   (CATBoolean & Val);
    void SetEOPGeomName    (CATUnicodeString & Val);
    void SetEOPLengthToSet (CATBoolean & Val);
    void SetEOPLengthValue (double & Val);

    void SetBaseFeatureOrientToSet (CATBoolean & Val);
    void SetBaseFeatureOrient      (CATOrientation & Val);
    void SetFlangeSurfOrientToSet  (CATBoolean & Val);
    void SetFlangeSurfOrient       (CATOrientation & Val);
  
    void SetSide1TypeToSet     (CATBoolean & Val);
    void SetSide1TypeName      (CATUnicodeString & Val);
    void SetSide1GeomToSet     (CATBoolean & Val);
    void SetSide1GeomName      (CATUnicodeString & Val);
    void SetCorner1TypeToSet   (CATBoolean & Val);
    void SetCorner1TypeName    (CATUnicodeString & Val);
    void SetCorner1RadiusToSet (CATBoolean & Val);
    void SetCorner1RadiusValue (double & Val);

    void SetSide2TypeToSet     (CATBoolean & Val);
    void SetSide2TypeName      (CATUnicodeString & Val);
    void SetSide2GeomToSet     (CATBoolean & Val);
    void SetSide2GeomName      (CATUnicodeString & Val);
    void SetCorner2TypeToSet   (CATBoolean & Val);
    void SetCorner2TypeName    (CATUnicodeString & Val);
    void SetCorner2RadiusToSet (CATBoolean & Val);
    void SetCorner2RadiusValue (double & Val);

    void SetProcessTypeToSet   (CATBoolean & Val);
    void SetProcessTypeName    (CATUnicodeString & Val);
    void SetK_FactorToSet      (CATBoolean & Val);
    void SetK_FactorValue      (double & Val);

    void SetCompensJoggleTypeToSet (CATBoolean & Val);
    void SetCompensJoggleTypeName  (CATUnicodeString & Val);
    void SetCompensSide1TypeToSet  (CATBoolean & Val);
    void SetCompensSide1TypeName   (CATUnicodeString & Val);
    void SetCompensSide1ValueToSet (CATBoolean & Val);
    void SetCompensSide1Value      (double & Val);
    void SetCompensSide2TypeToSet  (CATBoolean & Val);
    void SetCompensSide2TypeName   (CATUnicodeString & Val);
    void SetCompensSide2ValueToSet (CATBoolean & Val);
    void SetCompensSide2Value      (double & Val);

    // Joggle :
    // --------

    void SetModifJoggle       (CATBoolean & Val);
    void SetModifJoggleName   (CATUnicodeString & Val);
      
    void SetPlaneGeomToSet    (CATBoolean & Val);
    void SetPlaneGeomName     (CATUnicodeString & Val);
  
    void SetDepthValueToSet   (CATBoolean & Val);
    void SetDepthValue        (double & Val);
    void SetDepthOrientToSet  (CATBoolean & Val);
    void SetDepthOrient       (CATOrientation & Val);

    void SetRunoutValueToSet  (CATBoolean & Val);
    void SetRunoutValue       (double & Val);
    void SetRunoutOrientToSet (CATBoolean & Val);
    void SetRunoutOrient      (CATOrientation & Val);
  
    void SetClearanceValueToSet (CATBoolean & Val);
    void SetClearanceValue      (double & Val);

    void SetStartRadiusValueToSet (CATBoolean & Val);
    void SetStartRadiusValue      (double & Val);
    void SetEndRadiusValueToSet   (CATBoolean & Val);
    void SetEndRadiusValue        (double & Val);

  private:
  
    // General Data :
    // --------------

    CATUnicodeString          _InputPartPath;
    CATUnicodeString          _OutputPartPath;
    CATUnicodeString          _LengthUnit;
    
    CATBoolean                _Display;

    CATBoolean                _SupportGeomToSet;
    CATUnicodeString          _SupportGeomName;
      
    CATBoolean                _MaterialOrientToSet;
    CATOrientation            _MaterialOrient;
    
    // Web :
    // -----
    
    CATBoolean                _BoundaryToSet;
    CATListOfCATUnicodeString _LimitsGeomNameList;

    // Surfacic Flange :
    // -----------------

    CATBoolean                _ModifFlange;
    CATUnicodeString          _ModifFlangeName;

    CATBoolean                _BaseFeatureToSet;
    CATUnicodeString          _BaseFeatureName;
    CATBoolean                _BaseRadiusTypeToSet;
    CATUnicodeString          _BaseRadiusTypeName;
    CATBoolean                _BaseRadiusValueToSet;
    double                    _BaseRadiusValue;

    CATBoolean                _SupportTypeToSet;
    CATUnicodeString          _SupportTypeName;
    CATBoolean                _SupportLengthToSet;
    double                    _SupportLengthValue;
    CATBoolean                _SupportApproxToSet;
    double                    _SupportApproxValue;
  
    CATBoolean                _EOPTypeToSet;
    CATUnicodeString          _EOPTypeName;
    CATBoolean                _EOPGeomToSet;
    CATUnicodeString          _EOPGeomName;
    CATBoolean                _EOPLengthToSet;
    double                    _EOPLengthValue;

    CATBoolean                _BaseFeatureOrientToSet;
    CATOrientation            _BaseFeatureOrient;
    CATBoolean                _FlangeSurfOrientToSet;
    CATOrientation            _FlangeSurfOrient;
 
    CATBoolean                _Side1TypeToSet;
    CATUnicodeString          _Side1TypeName;
    CATBoolean                _Side1GeomToSet;
    CATUnicodeString          _Side1GeomName;
    CATBoolean                _Corner1TypeToSet;
    CATUnicodeString          _Corner1TypeName;
    CATBoolean                _Corner1RadiusToSet;
    double                    _Corner1RadiusValue;

    CATBoolean                _Side2TypeToSet;
    CATUnicodeString          _Side2TypeName;
    CATBoolean                _Side2GeomToSet;
    CATUnicodeString          _Side2GeomName;
    CATBoolean                _Corner2TypeToSet;
    CATUnicodeString          _Corner2TypeName;
    CATBoolean                _Corner2RadiusToSet;
    double                    _Corner2RadiusValue;

    CATBoolean                _ProcessTypeToSet;
    CATUnicodeString          _ProcessTypeName;
    CATBoolean                _K_FactorToSet;
    double                    _K_FactorValue;

    CATBoolean                _CompensJoggleTypeToSet;
    CATUnicodeString          _CompensJoggleTypeName;
    CATBoolean                _CompensSide1TypeToSet;
    CATUnicodeString          _CompensSide1TypeName;
    CATBoolean                _CompensSide1ValueToSet;
    double                    _CompensSide1Value;
    CATBoolean                _CompensSide2TypeToSet;
    CATUnicodeString          _CompensSide2TypeName;
    CATBoolean                _CompensSide2ValueToSet;
    double                    _CompensSide2Value;

    // Joggle :
    // --------

    CATBoolean                _ModifJoggle;
    CATUnicodeString          _ModifJoggleName;
      
    CATBoolean                _PlaneGeomToSet;
    CATUnicodeString          _PlaneGeomName;
  
    CATBoolean                _DepthValueToSet;
    double                    _DepthValue;
    CATBoolean                _DepthOrientToSet;
    CATOrientation            _DepthOrient;

    CATBoolean                _RunoutValueToSet;
    double                    _RunoutValue;
    CATBoolean                _RunoutOrientToSet;
    CATOrientation            _RunoutOrient;
  
    CATBoolean                _ClearanceValueToSet;
    double                    _ClearanceValue;

    CATBoolean                _StartRadiusValueToSet;
    double                    _StartRadiusValue;
    CATBoolean                _EndRadiusValueToSet;
    double                    _EndRadiusValue;
  };

#endif











