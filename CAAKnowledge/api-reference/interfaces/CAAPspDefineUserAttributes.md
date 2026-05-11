---
title: "CAAPspDefineUserAttributes"
type: "interface"
module: "CAAPlantShipInterfaces"
base: "CATPspKweUserAttrAdapter"
method_count: 2
visibility: "local"
verified: true
---

# CAAPspDefineUserAttributes

**基类**: CATPspKweUserAttrAdapter  
**模块**: CAAPlantShipInterfaces  
**可见性**: local  
**方法数**: 2

## 方法列表

### DefineKweUserAttr
```cpp
HRESULT DefineKweUserAttr(const CATString &isTypeName, 
                                      CATListValCATAttributeInfos &olAttrInfos);
```

### GetValue
```cpp
CATIValue* GetValue(CATIInstance*  ipiObject, 
                           const CATUnicodeString& iKey);
```

## 依赖

- `CATPspKweUserAttrAdapter.h`
- `CATICkeParmFactory.h`
- `CATICkeParm.h`
- `CATIProduct.h`

