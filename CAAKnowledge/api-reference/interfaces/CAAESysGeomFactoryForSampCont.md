---
title: "CAAESysGeomFactoryForSampCont"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysGeomFactoryForSampCont.h"
---

# CAAESysGeomFactoryForSampCont

> Data Extension of CAASysSampCont to implement the CAAISysGeomFactory interface which enables to create the objects. Main Methods: Create   -> Constructs a new CATObject

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CAAISysGeomFactory.h`

## 虚方法

### Create

```cpp
virtual HRESULT Create(const CAAISysGeomFactory::GeomObject iObjectType, const IID & iRequestInterfaceIID, CATBaseUnknown ** oCreatedObj) const ;
```

Create ------ iObjectType is point, root, line ...... oCreateObj  is a pointer on the request interface

| 参数 | 类型 |
|------|------|
| iObjectType | `const CAAISysGeomFactory::GeomObject` |
| iRequestInterfaceIID | `const IID &` |
| oCreatedObj | `CATBaseUnknown **` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysGeomFactoryForSampCont.h`
