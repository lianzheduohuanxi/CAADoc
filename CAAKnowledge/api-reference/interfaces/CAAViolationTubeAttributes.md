---
title: "CAAViolationTubeAttributes"
type: "LocalClass"
module: "CAAPlantShipInterfaces"
base: "CATPspCheckViolation"
method_count: 2
source_file: "CAAPlantShipInterfaces.edu/CAAPspDesignValidation.m/LocalInterfaces/CAAViolationTubeAttributes.h"
---

# CAAViolationTubeAttributes

**基类**: CATPspCheckViolation | **模块**: CAAPlantShipInterfaces | **方法数**: 2

## 依赖

- `CATPspCheckViolation.h`
- `CATUnicodeString.h`
- `CATListOfCATUnicodeString.h`

## 公共方法

### SetInfo

```cpp
void SetInfo(CATUnicodeString &iuPressure, CATUnicodeString &iuNominalSize, CATUnicodeString &iuMaterial, CATUnicodeString &iuAuthorizedValues) ;
```

| 参数 | 类型 |
|------|------|
| &iuPressure | `CATUnicodeString` |
| &iuNominalSize | `CATUnicodeString` |
| &iuMaterial | `CATUnicodeString` |
| &iuAuthorizedValues | `CATUnicodeString` |


### GetCheckViolationData

```cpp
HRESULT GetCheckViolationData(int& oRow, CATListValCATUnicodeString** oLValues) ;
```

| 参数 | 类型 |
|------|------|
| oRow | `int&` |
| oLValues | `CATListValCATUnicodeString**` |


---

**源文件**: `CAAPlantShipInterfaces.edu/CAAPspDesignValidation.m/LocalInterfaces/CAAViolationTubeAttributes.h`
