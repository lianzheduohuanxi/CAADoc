---
title: "CAAISysCircleCenterProperties"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/PublicInterfaces/CAAISysCircleCenterProperties.h"
---

# CAAISysCircleCenterProperties

> Interface to modify the CircleCenter properties. Inheritance: CATBaseUnknown (System Framework). Main Methods: GetMarkerType SetMarkerType

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### GetMarkerType

```cpp
virtual HRESULT GetMarkerType(CAAISysCircleCenterProperties::MarkerType & oMarkerType) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oMarkerType | `CAAISysCircleCenterProperties::MarkerType &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetMarkerType

```cpp
virtual HRESULT SetMarkerType(const CAAISysCircleCenterProperties::MarkerType iMarkerType) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iMarkerType | `const CAAISysCircleCenterProperties::MarkerType` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysCircleCenterProperties.h`
