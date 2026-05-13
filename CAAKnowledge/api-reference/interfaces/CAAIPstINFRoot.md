---
title: "CAAIPstINFRoot"
type: "ProtectedInterface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFRoot.h"
---

# CAAIPstINFRoot

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CAAPstINFInterfaces.h`
- `CATLISTV_CATBaseUnknown.h`
- `CATBaseUnknown.h`
- `CATISpecObject.h`

## 纯虚方法 (接口契约)

### AddChild

```cpp
virtual HRESULT AddChild(CATISpecObject *ipiFeature) = 0 ;
```

Aggregates a new feature under the root.

| 参数 | 类型 |
|------|------|
| *ipiFeature | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetChildren

```cpp
virtual HRESULT GetChildren(CATListValCATBaseUnknown_var **opList) = 0 ;
```

Returns a list of the direct children of the root node.

| 参数 | 类型 |
|------|------|
| **opList | `CATListValCATBaseUnknown_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFRoot.h`
