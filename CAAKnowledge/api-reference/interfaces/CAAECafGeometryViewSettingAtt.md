---
title: "CAAECafGeometryViewSettingAtt"
type: "interface"
module: "CAACATIAApplicationFrm"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAECafGeometryViewSettingAtt

**基类**: CATBaseUnknown  
**模块**: CAACATIAApplicationFrm  
**可见性**: local  
**方法数**: 4

> ===========================================================================

## 方法列表

### Initialize
```cpp
HRESULT Initialize();
```

### Get3DRepresentationMode
```cpp
HRESULT Get3DRepresentationMode(CATString & oIdVisibility);
```

### Set3DRepresentationMode
```cpp
HRESULT Set3DRepresentationMode(const CATString & iIdVisibility);
```

### GetInfo3DRepresentationMode
```cpp
HRESULT GetInfo3DRepresentationMode(CATSettingInfo * oInfo);
```

## 依赖

- `CATBaseUnknown.h`
- `CAAICafGeometryViewSettingAtt.h`

