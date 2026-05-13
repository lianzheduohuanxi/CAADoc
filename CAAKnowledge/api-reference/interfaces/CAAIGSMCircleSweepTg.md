---
title: "CAAIGSMCircleSweepTg"
type: "ProtectedInterface"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 10
source_file: "CAAGSMInterfaces.edu/ProtectedInterfaces/CAAIGSMCircleSweepTg.h"
---

# CAAIGSMCircleSweepTg

**基类**: CATBaseUnknown | **模块**: CAAGSMInterfaces | **方法数**: 10

## 依赖

- `CAAGsiFeaturesSplModel.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetCurveRef

```cpp
virtual HRESULT SetCurveRef(const CATISpecObject_var ipCurveRef) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ipCurveRef | `const CATISpecObject_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCurveRef

```cpp
virtual HRESULT GetCurveRef(CATISpecObject_var &ipCurveRef) = 0 ;
```

| 参数 | 类型 |
|------|------|
| &ipCurveRef | `CATISpecObject_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetSurfaceSupport

```cpp
virtual HRESULT SetSurfaceSupport(const CATISpecObject_var ipSupport) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ipSupport | `const CATISpecObject_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetSurfaceSupport

```cpp
virtual HRESULT GetSurfaceSupport(CATISpecObject_var &ipSupport) = 0 ;
```

| 参数 | 类型 |
|------|------|
| &ipSupport | `CATISpecObject_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetTrimMode

```cpp
virtual HRESULT SetTrimMode(const int iTrimMode) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iTrimMode | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetTrimMode

```cpp
virtual HRESULT GetTrimMode(int & oTrimMode) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oTrimMode | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetRadius

```cpp
virtual HRESULT SetRadius(const double iRadius) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iRadius | `const double` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetRadius

```cpp
virtual HRESULT GetRadius(double & oRadius) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oRadius | `double &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetSolution

```cpp
virtual HRESULT SetSolution(const int iSolution) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iSolution | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetSolution

```cpp
virtual HRESULT GetSolution(int & oSolution) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oSolution | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAGSMInterfaces.edu/ProtectedInterfaces/CAAIGSMCircleSweepTg.h`
