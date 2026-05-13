---
title: "CAAEVisWireBox"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAVisualization.edu/CAAVisWireBoxComp.m/LocalInterfaces/CAAEVisWireBox.h"
---

# CAAEVisWireBox

> Data extension ofd the CAAVisWireBox component and implementing the CAAIVisWireBox interface.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`

## 虚方法

### SetDimBox

```cpp
virtual HRESULT SetDimBox(const float iDimBox) ;
```

| 参数 | 类型 |
|------|------|
| iDimBox | `const float` |


### GetDimBox

```cpp
virtual HRESULT GetDimBox(float * oDimBox) ;
```

| 参数 | 类型 |
|------|------|
| oDimBox | `float *` |


### SetCenterBox

```cpp
virtual HRESULT SetCenterBox(const CATMathPoint & iCenter) ;
```

| 参数 | 类型 |
|------|------|
| iCenter | `const CATMathPoint &` |


### GetCenterBox

```cpp
virtual HRESULT GetCenterBox(CATMathPoint & oCenter) const ;
```

| 参数 | 类型 |
|------|------|
| oCenter | `CATMathPoint &` |


---

**源文件**: `CAAVisualization.edu/CAAVisWireBoxComp.m/LocalInterfaces/CAAEVisWireBox.h`
