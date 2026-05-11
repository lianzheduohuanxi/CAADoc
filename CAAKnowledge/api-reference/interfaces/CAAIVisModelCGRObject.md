---
title: "CAAIVisModelCGRObject"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
visibility: "protected"
verified: true
---

# CAAIVisModelCGRObject

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**可见性**: protected  
**方法数**: 2

> /Visualization FrameWork

## 方法列表

### GetCGRRep
```cpp
HRESULT GetCGRRep(CATRep ** oCGRRep);
```

### ReadCGRFile
```cpp
HRESULT ReadCGRFile(const char * iCGRFileName);
```

## 依赖

- `CATBaseUnknown.h`
- `CAAVisManagerInt.h`

