---
title: "CAAIMmrMultiMeasureAndMeasureSetFactory"
type: "ProtectedInterface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAMechanicalModeler.edu/ProtectedInterfaces/CAAIMmrMultiMeasureAndMeasureSetFactory.h"
---

# CAAIMmrMultiMeasureAndMeasureSetFactory

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 2

## 依赖

- `CAAMmrMultiMeasureAndMeasureSet.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### CreateMmrMultiMeasure

```cpp
virtual HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure, CATISpecObject **opMultiMeasureInstance) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *ipGeometricalElementToMesure | `CATBaseUnknown` |
| **opMultiMeasureInstance | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### CreateMmrMeasureSet

```cpp
virtual HRESULT CreateMmrMeasureSet(CATISpecObject **opMeasureSetInstance) = 0 ;
```

| 参数 | 类型 |
|------|------|
| **opMeasureSetInstance | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAMechanicalModeler.edu/ProtectedInterfaces/CAAIMmrMultiMeasureAndMeasureSetFactory.h`
