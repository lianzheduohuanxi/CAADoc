---
title: "CAAEVisModelCuboid"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelCuboid.h"
---

# CAAEVisModelCuboid

> Data extension of the CAAVisModelCuboid component, implementing the CAAIVisModelCuboid interface.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATMathPointf.h`

## 虚方法

### GetVertices

```cpp
virtual HRESULT GetVertices(float ** oVertices) ;
```

Interface CAAIVisModelCuboid

| 参数 | 类型 |
|------|------|
| oVertices | `float **` |


### SetVertices

```cpp
virtual HRESULT SetVertices(float * iVertices) ;
```

| 参数 | 类型 |
|------|------|
| iVertices | `float *` |


---

**源文件**: `CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelCuboid.h`
