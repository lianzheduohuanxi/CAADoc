---
title: "CAAISysGeomFactory"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
visibility: "public"
verified: true
---

# CAAISysGeomFactory

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 1

> System Framework

## 方法列表

### Create
```cpp
HRESULT Create(const CAAISysGeomFactory::GeomObject  iObjectType,
                           const IID                            &iRequestInterfaceIID,          
                           CATBaseUnknown **oCreatedObj) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

