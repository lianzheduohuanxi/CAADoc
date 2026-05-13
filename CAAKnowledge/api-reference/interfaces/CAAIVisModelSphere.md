---
title: "CAAIVisModelSphere"
type: "ProtectedInterface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelSphere.h"
---

# CAAIVisModelSphere

> Interface which characterizes a CAAVisModelSphere object.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAAVisManagerInt.h`

## 纯虚方法 (接口契约)

### SetCenter

```cpp
virtual HRESULT SetCenter(const CATMathPointf & iCenter) = 0 ;
```

The circle is defined by: ------------------------ A point center -------------------

| 参数 | 类型 |
|------|------|
| iCenter | `const CATMathPointf &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCenter

```cpp
virtual HRESULT GetCenter(CATMathPointf & oCenter) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oCenter | `CATMathPointf &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetRadius

```cpp
virtual HRESULT SetRadius(const float iRadius) = 0 ;
```

A radius -------------------

| 参数 | 类型 |
|------|------|
| iRadius | `const float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetRadius

```cpp
virtual HRESULT GetRadius(float & oRadius) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oRadius | `float &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelSphere.h`
