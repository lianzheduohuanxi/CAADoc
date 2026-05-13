---
title: "CAADVTubeAttributes"
type: "LocalClass"
module: "CAAPlantShipInterfaces"
base: "CATEAPspDesignValidation"
method_count: 12
source_file: "CAAPlantShipInterfaces.edu/CAAPspDesignValidation.m/LocalInterfaces/CAADVTubeAttributes.h"
---

# CAADVTubeAttributes

**基类**: CATEAPspDesignValidation | **模块**: CAAPlantShipInterfaces | **方法数**: 12

## 依赖

- `CATEAPspDesignValidation.h`

## 公共方法

### GetValidationChecks

```cpp
HRESULT GetValidationChecks(CATListValCATUnicodeString& oChecks) ;
```

| 参数 | 类型 |
|------|------|
| oChecks | `CATListValCATUnicodeString&` |


### IsObjectAViolation

```cpp
HRESULT IsObjectAViolation(const CATBaseUnknown* iObject, const CATListValCATUnicodeString& iChecks, CATListPV** oViolation, const unsigned int& iErrorFile) ;
```

| 参数 | 类型 |
|------|------|
| iObject | `const CATBaseUnknown*` |
| iChecks | `const CATListValCATUnicodeString&` |
| oViolation | `CATListPV**` |
| iErrorFile | `const unsigned int&` |


### GetClassification

```cpp
HRESULT GetClassification(CATUnicodeString& oClassification) ;
```

| 参数 | 类型 |
|------|------|
| oClassification | `CATUnicodeString&` |


### GetResource

```cpp
HRESULT GetResource(CATUnicodeString& oName) ;
```

| 参数 | 类型 |
|------|------|
| oName | `CATUnicodeString&` |


### GetColumnTitles

```cpp
HRESULT GetColumnTitles(CATListValCATUnicodeString& oTitles) ;
```

| 参数 | 类型 |
|------|------|
| oTitles | `CATListValCATUnicodeString&` |


### CheckTubeSize

```cpp
HRESULT CheckTubeSize(const CATBaseUnknown* iObject, CATListPV** oViolation, const unsigned int& iErrorFile) ;
```

| 参数 | 类型 |
|------|------|
| iObject | `const CATBaseUnknown*` |
| oViolation | `CATListPV**` |
| iErrorFile | `const unsigned int&` |


### CheckTubeMaterial

```cpp
HRESULT CheckTubeMaterial(const CATBaseUnknown* iObject, CATListPV** oViolation, const unsigned int& iErrorFile) ;
```

| 参数 | 类型 |
|------|------|
| iObject | `const CATBaseUnknown*` |
| oViolation | `CATListPV**` |
| iErrorFile | `const unsigned int&` |


### GetLogicalLine

```cpp
HRESULT GetLogicalLine(const IUnknown *ipiLogicalLineMember, CATIPspLogicalLine *&opiLogicalLine) ;
```

| 参数 | 类型 |
|------|------|
| *ipiLogicalLineMember | `const IUnknown` |
| *&opiLogicalLine | `CATIPspLogicalLine` |


### GetObjectAttribute

```cpp
HRESULT GetObjectAttribute(const IUnknown *ipiObject, CATUnicodeString iuAttributeName, CATICkeParm *&opiAttributeParm) ;
```

| 参数 | 类型 |
|------|------|
| *ipiObject | `const IUnknown` |
| iuAttributeName | `CATUnicodeString` |
| *&opiAttributeParm | `CATICkeParm` |


### GetTestData

```cpp
HRESULT GetTestData(const CATICkeParm *ipiPressureParm, const CATICkeParm *ipiNominalSizeParm, const CATICkeParm *ipiMaterialParm, double &oPressure, CATUnicodeString &ouPressure, CATUnicodeString &ouNominalSize, CATUnicodeString &ouMaterial) ;
```

| 参数 | 类型 |
|------|------|
| *ipiPressureParm | `const CATICkeParm` |
| *ipiNominalSizeParm | `const CATICkeParm` |
| *ipiMaterialParm | `const CATICkeParm` |
| &oPressure | `double` |
| &ouPressure | `CATUnicodeString` |
| &ouNominalSize | `CATUnicodeString` |
| &ouMaterial | `CATUnicodeString` |


### TestTubeSize

```cpp
HRESULT TestTubeSize(const double &iPressure, const CATUnicodeString &iuNominalSize, CATUnicodeString &ouAuthorizedSizes) ;
```

| 参数 | 类型 |
|------|------|
| &iPressure | `const double` |
| &iuNominalSize | `const CATUnicodeString` |
| &ouAuthorizedSizes | `CATUnicodeString` |


### TestTubeMaterial

```cpp
HRESULT TestTubeMaterial(const double &iPressure, const CATUnicodeString &iuNominalSize, const CATUnicodeString &iuMaterial, CATUnicodeString &ouAuthorizedMaterialForSize) ;
```

| 参数 | 类型 |
|------|------|
| &iPressure | `const double` |
| &iuNominalSize | `const CATUnicodeString` |
| &iuMaterial | `const CATUnicodeString` |
| &ouAuthorizedMaterialForSize | `CATUnicodeString` |


---

**源文件**: `CAAPlantShipInterfaces.edu/CAAPspDesignValidation.m/LocalInterfaces/CAADVTubeAttributes.h`
