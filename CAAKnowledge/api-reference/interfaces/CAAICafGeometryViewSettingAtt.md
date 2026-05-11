---
title: "CAAICafGeometryViewSettingAtt"
type: "interface"
module: "CAACATIAApplicationFrm"
base: "IUnknown"
method_count: 4
visibility: "protected"
verified: true
---

# CAAICafGeometryViewSettingAtt

**基类**: IUnknown  
**模块**: CAACATIAApplicationFrm  
**可见性**: protected  
**方法数**: 4

> Global Unique IDentifier defined in .cpp

## 方法列表

### Initialize
```cpp
HRESULT Initialize();
```

### Get3DRepresentationMode
```cpp
HRESULT Get3DRepresentationMode(CATString & oIdMode);
```

### Set3DRepresentationMode
```cpp
HRESULT Set3DRepresentationMode(const CATString & iIdMode);
```

### GetInfo3DRepresentationMode
```cpp
HRESULT GetInfo3DRepresentationMode(CATSettingInfo * oInfo);
```

## 依赖

- `CAACafCtrlToolsOptions.h`

