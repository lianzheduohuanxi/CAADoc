---
title: "CAAEVisModelCGRObject"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelCGRObject.h"
---

# CAAEVisModelCGRObject

> Data extension of the CAAVisModelCGRObject component, implementing the CAAIVisModelCGRObject interface.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetCGRRep

```cpp
virtual HRESULT GetCGRRep(CATRep ** oCGRRep) ;
```

--------------------------------------------------------------- +++  Methods of the CAAIVisModelCGRObject interface ++++++++++++++ ---------------------------------------------------------------

| 参数 | 类型 |
|------|------|
| oCGRRep | `CATRep **` |


### ReadCGRFile

```cpp
virtual HRESULT ReadCGRFile(const char * iCGRFileName) ;
```

| 参数 | 类型 |
|------|------|
| iCGRFileName | `const char *` |


---

**源文件**: `CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelCGRObject.h`
