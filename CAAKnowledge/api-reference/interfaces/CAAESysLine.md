---
title: "CAAESysLine"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysLine.h"
---

# CAAESysLine

> Data extension ofd the CAASysLine component and implementing the CAAISysLine interface. Main Method: SetStartPoint/GetStartPoint SetEndPoint/GetEndPoint

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`

## 虚方法

### SetStartPoint

```cpp
virtual HRESULT SetStartPoint(const CATMathPoint & iStartPoint) ;
```

Start Point

| 参数 | 类型 |
|------|------|
| iStartPoint | `const CATMathPoint &` |


### GetStartPoint

```cpp
virtual HRESULT GetStartPoint(CATMathPoint & oStartPoint) const ;
```

| 参数 | 类型 |
|------|------|
| oStartPoint | `CATMathPoint &` |


### SetEndPoint

```cpp
virtual HRESULT SetEndPoint(const CATMathPoint & iEndPoint) ;
```

End Point

| 参数 | 类型 |
|------|------|
| iEndPoint | `const CATMathPoint &` |


### GetEndPoint

```cpp
virtual HRESULT GetEndPoint(CATMathPoint & oEndPoint) const ;
```

| 参数 | 类型 |
|------|------|
| oEndPoint | `CATMathPoint &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysLine.h`
