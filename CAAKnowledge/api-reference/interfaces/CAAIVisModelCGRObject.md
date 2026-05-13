---
title: "CAAIVisModelCGRObject"
type: "ProtectedInterface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelCGRObject.h"
---

# CAAIVisModelCGRObject

> Interface which characterizes a CAAVisModelCGRObject object.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAAVisManagerInt.h`

## 纯虚方法 (接口契约)

### GetCGRRep

```cpp
virtual HRESULT GetCGRRep(CATRep ** oCGRRep) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oCGRRep | `CATRep **` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### ReadCGRFile

```cpp
virtual HRESULT ReadCGRFile(const char * iCGRFileName) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iCGRFileName | `const char *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelCGRObject.h`
