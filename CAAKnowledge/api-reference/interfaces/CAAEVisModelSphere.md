---
title: "CAAEVisModelSphere"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelSphere.h"
---

# CAAEVisModelSphere

> Data extension of the CAAVisModelSphere component, implementing the CAAIVisModelSphere interface.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATMathPointf.h`

## 虚方法

### GetCenter

```cpp
virtual HRESULT GetCenter(CATMathPointf & iCenter) const ;
```

CAAIVisModelSphere interface

| 参数 | 类型 |
|------|------|
| iCenter | `CATMathPointf &` |


### SetCenter

```cpp
virtual HRESULT SetCenter(const CATMathPointf & oCenter) ;
```

| 参数 | 类型 |
|------|------|
| oCenter | `const CATMathPointf &` |


### GetRadius

```cpp
virtual HRESULT GetRadius(float & oRadius) const ;
```

| 参数 | 类型 |
|------|------|
| oRadius | `float &` |


### SetRadius

```cpp
virtual HRESULT SetRadius(const float iRadius) ;
```

| 参数 | 类型 |
|------|------|
| iRadius | `const float` |


---

**源文件**: `CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelSphere.h`
