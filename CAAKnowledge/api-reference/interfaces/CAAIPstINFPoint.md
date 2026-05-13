---
title: "CAAIPstINFPoint"
type: "ProtectedInterface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFPoint.h"
---

# CAAIPstINFPoint

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 6

## 依赖

- `CAAPstINFInterfaces.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### GetX

```cpp
virtual HRESULT GetX(double *opX) = 0 ;
```

Retrieve the point's X coordinate value.

| 参数 | 类型 |
|------|------|
| *opX | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetY

```cpp
virtual HRESULT GetY(double *opY) = 0 ;
```

Retrieve the point's Y coordinate value.

| 参数 | 类型 |
|------|------|
| *opY | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetZ

```cpp
virtual HRESULT GetZ(double *opZ) = 0 ;
```

Retrieve the point's Z coordinate value.

| 参数 | 类型 |
|------|------|
| *opZ | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetX

```cpp
virtual HRESULT SetX(double iX) = 0 ;
```

Valuate the point's X coordinate.

| 参数 | 类型 |
|------|------|
| iX | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetY

```cpp
virtual HRESULT SetY(double iY) = 0 ;
```

Valuate the point's Y coordinate.

| 参数 | 类型 |
|------|------|
| iY | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetZ

```cpp
virtual HRESULT SetZ(double iZ) = 0 ;
```

Valuate the point's Z coordinate.

| 参数 | 类型 |
|------|------|
| iZ | `double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFPoint.h`
