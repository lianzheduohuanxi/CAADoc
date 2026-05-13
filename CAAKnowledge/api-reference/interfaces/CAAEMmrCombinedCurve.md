---
title: "CAAEMmrCombinedCurve"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurve.m/LocalInterfaces/CAAEMmrCombinedCurve.h"
---

# CAAEMmrCombinedCurve

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### SetCurve

```cpp
HRESULT SetCurve(int iNum, CATISpecObject *ipiSpecOnCurve) ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipiSpecOnCurve | `CATISpecObject` |


### GetCurve

```cpp
HRESULT GetCurve(int iNum, CATISpecObject **opiSpecOnCurve) ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| **opiSpecOnCurve | `CATISpecObject` |


### SetDirection

```cpp
HRESULT SetDirection(int iNum, CATISpecObject *ipiSpecOnDirection) ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipiSpecOnDirection | `CATISpecObject` |


### GetDirection

```cpp
HRESULT GetDirection(int iNum, CATISpecObject **opiSpecOnDirection) ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| **opiSpecOnDirection | `CATISpecObject` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurve.m/LocalInterfaces/CAAEMmrCombinedCurve.h`
