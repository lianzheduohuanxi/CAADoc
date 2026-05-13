---
title: "CAAIPstINFLine"
type: "ProtectedInterface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFLine.h"
---

# CAAIPstINFLine

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CAAPstINFInterfaces.h`
- `CATBaseUnknown.h`
- `CATISpecObject.h`

## 纯虚方法 (接口契约)

### GetPoint

```cpp
virtual HRESULT GetPoint(int iNum, CATISpecObject **opiPoint) = 0 ;
```

Retrieves one of the point features pointed to by the line's attribute definitions.

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| **opiPoint | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetPoint

```cpp
virtual HRESULT SetPoint(int iNum, CATISpecObject *ipiPoint) = 0 ;
```

Valuates one of the line's attribute definitions with a point feature.

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipiPoint | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAProductStructure.edu/ProtectedInterfaces/CAAIPstINFLine.h`
