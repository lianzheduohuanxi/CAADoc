---
title: "CAAECafGeometryEltSettingAtt"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATBaseUnknown"
method_count: 10
source_file: "CAACATIAApplicationFrm.edu/CAACafCtrlToolsOptions.m/LocalInterfaces/CAAECafGeometryEltSettingAtt.h"
---

# CAAECafGeometryEltSettingAtt

> Data Extension of  CAACafGeometryEltSettingCtrl to implement the CAAICafGeometryEltSettingAtt. This interface enables to handle each attribut of the setting repository CAACafGeometryElt

**基类**: CATBaseUnknown | **模块**: CAACATIAApplicationFrm | **方法数**: 10

## 依赖

- `CATBaseUnknown.h`
- `CAAICafGeometryEltSettingAtt.h`

## 虚方法

### Initialize

```cpp
virtual HRESULT Initialize() ;
```

This method calls all Getxxx methods.


### GetIdentifierVisibility

```cpp
virtual HRESULT GetIdentifierVisibility(CATString & oIdVisibility) ;
```

| 参数 | 类型 |
|------|------|
| oIdVisibility | `CATString &` |


### SetIdentifierVisibility

```cpp
virtual HRESULT SetIdentifierVisibility(const CATString & iIdVisibility) ;
```

| 参数 | 类型 |
|------|------|
| iIdVisibility | `const CATString &` |


### GetInfoIdentifierVisibility

```cpp
virtual HRESULT GetInfoIdentifierVisibility(CATSettingInfo * oInfo) ;
```

| 参数 | 类型 |
|------|------|
| oInfo | `CATSettingInfo *` |


### GetMaxPointCurve

```cpp
virtual HRESULT GetMaxPointCurve(int & oMaxPoint) ;
```

| 参数 | 类型 |
|------|------|
| oMaxPoint | `int &` |


### SetMaxPointCurve

```cpp
virtual HRESULT SetMaxPointCurve(const int iMaxPoint) ;
```

| 参数 | 类型 |
|------|------|
| iMaxPoint | `const int` |


### GetInfoMaxPointCurve

```cpp
virtual HRESULT GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray, int * oNbInfo) ;
```

| 参数 | 类型 |
|------|------|
| oInfoArray | `CATSettingInfo **` |
| oNbInfo | `int *` |


### GetImplPointVisibility

```cpp
virtual HRESULT GetImplPointVisibility(CATString & oImplPointVisibility) ;
```

| 参数 | 类型 |
|------|------|
| oImplPointVisibility | `CATString &` |


### SetImplPointVisibility

```cpp
virtual HRESULT SetImplPointVisibility(const CATString & iImplPointVisibility) ;
```

| 参数 | 类型 |
|------|------|
| iImplPointVisibility | `const CATString &` |


### GetInfoImplPointVisibility

```cpp
virtual HRESULT GetInfoImplPointVisibility(CATSettingInfo * oInfo) ;
```

| 参数 | 类型 |
|------|------|
| oInfo | `CATSettingInfo *` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafCtrlToolsOptions.m/LocalInterfaces/CAAECafGeometryEltSettingAtt.h`
