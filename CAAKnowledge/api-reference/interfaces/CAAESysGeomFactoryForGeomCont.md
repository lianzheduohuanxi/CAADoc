---
title: "CAAESysGeomFactoryForGeomCont"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
visibility: "local"
verified: true
---

# CAAESysGeomFactoryForGeomCont

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 1

> Create   -> Constructs a new CATObject

## 方法列表

### Create
```cpp
HRESULT Create(const CAAISysGeomFactory::GeomObject iObjectType, 
                            const IID        & iRequestInterfaceIID,          
                            CATBaseUnknown  ** oCreatedObj) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CAAISysGeomFactory.h`

