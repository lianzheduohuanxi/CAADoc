---
title: "CAAICafGeometryViewSettingAtt"
type: "ProtectedInterface"
module: "CAACATIAApplicationFrm"
base: "IUnknown"
method_count: 4
source_file: "CAACATIAApplicationFrm.edu/ProtectedInterfaces/CAAICafGeometryViewSettingAtt.h"
---

# CAAICafGeometryViewSettingAtt

**基类**: IUnknown | **模块**: CAACATIAApplicationFrm | **方法数**: 4

## 依赖

- `IUnknown.h`
- `CAACafCtrlToolsOptions.h`

## 纯虚方法 (接口契约)

### Initialize

```cpp
virtual HRESULT Initialize() = 0 ;
```

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### Get3DRepresentationMode

```cpp
virtual HRESULT Get3DRepresentationMode(CATString & oIdMode) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oIdMode | `CATString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### Set3DRepresentationMode

```cpp
virtual HRESULT Set3DRepresentationMode(const CATString & iIdMode) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iIdMode | `const CATString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetInfo3DRepresentationMode

```cpp
virtual HRESULT GetInfo3DRepresentationMode(CATSettingInfo * oInfo) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oInfo | `CATSettingInfo *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAACATIAApplicationFrm.edu/ProtectedInterfaces/CAAICafGeometryViewSettingAtt.h`
