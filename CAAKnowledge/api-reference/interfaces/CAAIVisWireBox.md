---
title: "CAAIVisWireBox"
type: "PublicInterface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAVisualization.edu/PublicInterfaces/CAAIVisWireBox.h"
---

# CAAIVisWireBox

> Interface which characterizes a wire box. This interface and the wire box is used in the CAADegClippingByBoxCmd class in the CAADialogEngine.edu framework. System Framework

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAAVisWireBoxComp.h`

## 纯虚方法 (接口契约)

### SetDimBox

```cpp
virtual HRESULT SetDimBox(const float iDimBox) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iDimBox | `const float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetDimBox

```cpp
virtual HRESULT GetDimBox(float * oDimBox) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oDimBox | `float *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetCenterBox

```cpp
virtual HRESULT SetCenterBox(const CATMathPoint & iCenter) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iCenter | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCenterBox

```cpp
virtual HRESULT GetCenterBox(CATMathPoint & oCenter) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oCenter | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAVisualization.edu/PublicInterfaces/CAAIVisWireBox.h`
