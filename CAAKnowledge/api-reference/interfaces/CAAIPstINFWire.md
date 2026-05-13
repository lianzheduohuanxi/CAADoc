---
title: "CAAIPstINFWire"
type: "ProtectedInterface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFWire.h"
---

# CAAIPstINFWire

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CAAPstINFInterfaces.h`
- `CATBaseUnknown.h`
- `CATListPtrCATISpecObject.h`

## 纯虚方法 (接口契约)

### GetPoints

```cpp
virtual HRESULT GetPoints(CATListPtrCATISpecObject **pointList) = 0 ;
```

Retrieve the list of points defining the wire.

| 参数 | 类型 |
|------|------|
| **pointList | `CATListPtrCATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetPoints

```cpp
virtual HRESULT SetPoints(CATListPtrCATISpecObject *pointList) = 0 ;
```

Valuate the list of points defining the wire.

| 参数 | 类型 |
|------|------|
| *pointList | `CATListPtrCATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFWire.h`
