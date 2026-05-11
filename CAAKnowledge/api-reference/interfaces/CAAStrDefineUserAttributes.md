---
title: "CAAStrDefineUserAttributes"
type: "interface"
module: "CAAStructureInterfaces"
base: "CATPspKweUserAttrAdapter"
method_count: 2
visibility: "local"
verified: true
---

# CAAStrDefineUserAttributes

**基类**: CATPspKweUserAttrAdapter  
**模块**: CAAStructureInterfaces  
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

