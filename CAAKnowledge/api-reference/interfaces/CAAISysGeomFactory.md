---
title: "CAAISysGeomFactory"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASystem.edu/PublicInterfaces/CAAISysGeomFactory.h"
---

# CAAISysGeomFactory

> Interface representing a factory which creates model objects. Inheritance: CATBaseUnknown (System Framework) Main Method: Create: instantiates model objects

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### Create

```cpp
virtual HRESULT Create(const CAAISysGeomFactory::GeomObject iObjectType, const IID &iRequestInterfaceIID, CATBaseUnknown **oCreatedObj) const = 0 ;
```

Create ------ Instanciates an object and returns its asked interface pointer .

| 参数 | 类型 |
|------|------|
| iObjectType | `const CAAISysGeomFactory::GeomObject` |
| &iRequestInterfaceIID | `const IID` |
| **oCreatedObj | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysGeomFactory.h`
