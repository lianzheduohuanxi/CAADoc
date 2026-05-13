---
title: "CAAIV5V6ExtMmrMultiMeasureFactory"
type: "PublicInterface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrMultiMeasureFactory.h"
---

# CAAIV5V6ExtMmrMultiMeasureFactory

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 2

## 依赖

- `CAAV5V6ExtMmrMultiMeasure.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### CreateMmrMultiMeasure

```cpp
virtual HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure, CATBaseUnknown *&opMultiMeasureInstance) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *ipGeometricalElementToMesure | `CATBaseUnknown` |
| *&opMultiMeasureInstance | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### CreateMmrMeasureSet

```cpp
virtual HRESULT CreateMmrMeasureSet(CATBaseUnknown *&opMeasureSetInstance) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *&opMeasureSetInstance | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrMultiMeasureFactory.h`
