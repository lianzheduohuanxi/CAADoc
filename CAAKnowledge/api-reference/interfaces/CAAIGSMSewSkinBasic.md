---
title: "CAAIGSMSewSkinBasic"
type: "ProtectedInterface"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 7
source_file: "CAAGSMInterfaces.edu/ProtectedInterfaces/CAAIGSMSewSkinBasic.h"
---

# CAAIGSMSewSkinBasic

**基类**: CATBaseUnknown | **模块**: CAAGSMInterfaces | **方法数**: 7

## 依赖

- `CAAGsiFeaturesSplModel.h`
- `CATGSMOrientation.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetSurfaceToSew

```cpp
virtual HRESULT SetSurfaceToSew(CATISpecObject_var ispSurfaceToSew) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ispSurfaceToSew | `CATISpecObject_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetSurfaceToSew

```cpp
virtual HRESULT GetSurfaceToSew(CATISpecObject_var & ospSurfaceToSew) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ospSurfaceToSew | `CATISpecObject_var &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetSurfaceSupport

```cpp
virtual HRESULT SetSurfaceSupport(CATISpecObject_var ispSupport) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ispSupport | `CATISpecObject_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetSurfaceSupport

```cpp
virtual HRESULT GetSurfaceSupport(CATISpecObject_var & ospSupport) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ospSupport | `CATISpecObject_var &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetOrientation

```cpp
virtual HRESULT SetOrientation(CATGSMOrientation iOrientation) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iOrientation | `CATGSMOrientation` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetOrientation

```cpp
virtual HRESULT GetOrientation(CATGSMOrientation & oOrientation) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oOrientation | `CATGSMOrientation &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### InvertOrientation

```cpp
virtual HRESULT InvertOrientation() = 0 ;
```

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAGSMInterfaces.edu/ProtectedInterfaces/CAAIGSMSewSkinBasic.h`
