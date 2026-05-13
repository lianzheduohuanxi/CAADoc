---
title: "CAAICafGeometryEltSettingAtt"
type: "ProtectedInterface"
module: "CAACATIAApplicationFrm"
base: "IUnknown"
method_count: 10
source_file: "CAACATIAApplicationFrm.edu/ProtectedInterfaces/CAAICafGeometryEltSettingAtt.h"
---

# CAAICafGeometryEltSettingAtt

**基类**: IUnknown | **模块**: CAACATIAApplicationFrm | **方法数**: 10

## 依赖

- `IUnknown.h`
- `CAACafCtrlToolsOptions.h`

## 纯虚方法 (接口契约)

### Initialize

```cpp
virtual HRESULT Initialize() = 0 ;
```

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetIdentifierVisibility

```cpp
virtual HRESULT GetIdentifierVisibility(CATString & oIdVisibility) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oIdVisibility | `CATString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetIdentifierVisibility

```cpp
virtual HRESULT SetIdentifierVisibility(const CATString & iIdVisibility) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iIdVisibility | `const CATString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetInfoIdentifierVisibility

```cpp
virtual HRESULT GetInfoIdentifierVisibility(CATSettingInfo * oInfo) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oInfo | `CATSettingInfo *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetMaxPointCurve

```cpp
virtual HRESULT GetMaxPointCurve(int & oMaxPoint) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oMaxPoint | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetMaxPointCurve

```cpp
virtual HRESULT SetMaxPointCurve(const int iMaxPoint) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iMaxPoint | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetInfoMaxPointCurve

```cpp
virtual HRESULT GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray, int * iNbInfo) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oInfoArray | `CATSettingInfo **` |
| iNbInfo | `int *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetImplPointVisibility

```cpp
virtual HRESULT GetImplPointVisibility(CATString & oImplPointVisibility) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oImplPointVisibility | `CATString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetImplPointVisibility

```cpp
virtual HRESULT SetImplPointVisibility(const CATString & iImplPointVisibility) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iImplPointVisibility | `const CATString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetInfoImplPointVisibility

```cpp
virtual HRESULT GetInfoImplPointVisibility(CATSettingInfo * oInfo) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oInfo | `CATSettingInfo *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAACATIAApplicationFrm.edu/ProtectedInterfaces/CAAICafGeometryEltSettingAtt.h`
