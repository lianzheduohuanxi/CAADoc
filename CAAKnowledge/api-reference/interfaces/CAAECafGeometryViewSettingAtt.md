---
title: "CAAECafGeometryViewSettingAtt"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAACATIAApplicationFrm.edu/CAACafCtrlToolsOptions.m/LocalInterfaces/CAAECafGeometryViewSettingAtt.h"
---

# CAAECafGeometryViewSettingAtt

> Data Extension of CAACafGeometryViewSettingCtrl to implement the CAAICafGeometryViewSettingAtt. This interface enables to handle each attribut of the setting repository CAACafGeometryView

**基类**: CATBaseUnknown | **模块**: CAACATIAApplicationFrm | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAAICafGeometryViewSettingAtt.h`

## 虚方法

### Initialize

```cpp
virtual HRESULT Initialize() ;
```

This method calls all Getxxx methods.


### Get3DRepresentationMode

```cpp
virtual HRESULT Get3DRepresentationMode(CATString & oIdVisibility) ;
```

| 参数 | 类型 |
|------|------|
| oIdVisibility | `CATString &` |


### Set3DRepresentationMode

```cpp
virtual HRESULT Set3DRepresentationMode(const CATString & iIdVisibility) ;
```

| 参数 | 类型 |
|------|------|
| iIdVisibility | `const CATString &` |


### GetInfo3DRepresentationMode

```cpp
virtual HRESULT GetInfo3DRepresentationMode(CATSettingInfo * oInfo) ;
```

| 参数 | 类型 |
|------|------|
| oInfo | `CATSettingInfo *` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafCtrlToolsOptions.m/LocalInterfaces/CAAECafGeometryViewSettingAtt.h`
