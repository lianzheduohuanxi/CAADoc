---
title: "CAAIGSMFeaturesSplFactory"
type: "ProtectedInterface"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAGSMInterfaces.edu/ProtectedInterfaces/CAAIGSMFeaturesSplFactory.h"
---

# CAAIGSMFeaturesSplFactory

**基类**: CATBaseUnknown | **模块**: CAAGSMInterfaces | **方法数**: 2

## 依赖

- `CAAGsiFeaturesSplModel.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### CreateSewSkinBasic

```cpp
virtual CAAIGSMSewSkinBasic * CreateSewSkinBasic(CATISpecObject *ipSurfaceToSew, CATISpecObject *ipSurfaceSupport) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *ipSurfaceToSew | `CATISpecObject` |
| *ipSurfaceSupport | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### CreateCircleSweepTg

```cpp
virtual CAAIGSMCircleSweepTg * CreateCircleSweepTg(CATISpecObject *ipCurveRef, CATISpecObject *ipSurfaceSupport, double radius) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *ipCurveRef | `CATISpecObject` |
| *ipSurfaceSupport | `CATISpecObject` |
| radius | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAGSMInterfaces.edu/ProtectedInterfaces/CAAIGSMFeaturesSplFactory.h`
