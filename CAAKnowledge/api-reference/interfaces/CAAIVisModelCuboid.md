---
title: "CAAIVisModelCuboid"
type: "ProtectedInterface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelCuboid.h"
---

# CAAIVisModelCuboid

> Interface which characterizes a CAAVisModelCuboid object. The Cuboid is represented by 8 vertices, ie 8*3 float. Each vertices is placed like this: X4 --------------X7 /  .                   /  | /     .                 /    | /     X3 .............../........X2 X5 -------------X6      / |    .                 |       / |  .                   |    / X0--------------X1

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAAVisManagerInt.h`

## 纯虚方法 (接口契约)

### GetVertices

```cpp
virtual HRESULT GetVertices(float ** oVertices) = 0 ;
```

Retrieves vertices of the cuboid. The length of the array is 24 = 8 vertices * 3 coordinates (x,y,z) don't delete the array after the call.

| 参数 | 类型 |
|------|------|
| oVertices | `float **` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetVertices

```cpp
virtual HRESULT SetVertices(float * iVertices) = 0 ;
```

Sets vertices of the cuboid.

| 参数 | 类型 |
|------|------|
| iVertices | `float *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelCuboid.h`
