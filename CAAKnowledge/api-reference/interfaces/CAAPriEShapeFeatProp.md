---
title: "CAAPriEShapeFeatProp"
type: "LocalClass"
module: "CAAPartInterfaces"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAPartInterfaces.edu/CAAPriPattern.m/LocalInterfaces/CAAPriEShapeFeatProp.h"
---

# CAAPriEShapeFeatProp

> In this sample we have implemented the mandatory methods to define the properties of the PatternPad feature: Return code of IsAFreeFormFeature   : 1 Return code of IsAContextualFeature : 0 Return code of CanBePatterned       : 1

**基类**: CATBaseUnknown | **模块**: CAAPartInterfaces | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`
- `CATMathPlane.h`

## 公共方法

### IsAFreeFormFeature

```cpp
int IsAFreeFormFeature() ;
```


### IsAContextualFeature

```cpp
int IsAContextualFeature() ;
```


### GetPolarity

```cpp
CATUnicodeString GetPolarity() ;
```


### HasAnAxis

```cpp
int HasAnAxis() ;
```


### HasAnAxis

```cpp
int HasAnAxis(CATBaseUnknown_var Elt) ;
```

| 参数 | 类型 |
|------|------|
| Elt | `CATBaseUnknown_var` |


### CanBePatterned

```cpp
int CanBePatterned() ;
```


---

**源文件**: `CAAPartInterfaces.edu/CAAPriPattern.m/LocalInterfaces/CAAPriEShapeFeatProp.h`
