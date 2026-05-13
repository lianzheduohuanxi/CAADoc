---
title: "CAAPspDefineUserAttributes"
type: "LocalClass"
module: "CAAPlantShipInterfaces"
base: "CATPspKweUserAttrAdapter"
method_count: 2
source_file: "CAAPlantShipInterfaces.edu/CAAPspDefineUserProperties.m/LocalInterfaces/CAAPspDefineUserAttributes.h"
---

# CAAPspDefineUserAttributes

**基类**: CATPspKweUserAttrAdapter | **模块**: CAAPlantShipInterfaces | **方法数**: 2

## 依赖

- `CATPspKweUserAttrAdapter.h`
- `CATICkeParmFactory.h`
- `CATICkeParm.h`
- `CATIProduct.h`

## 虚方法

### DefineKweUserAttr

```cpp
virtual HRESULT DefineKweUserAttr(const CATString &isTypeName, CATListValCATAttributeInfos &olAttrInfos) ;
```

| 参数 | 类型 |
|------|------|
| &isTypeName | `const CATString` |
| &olAttrInfos | `CATListValCATAttributeInfos` |


### GetValue

```cpp
virtual CATIValue* GetValue(CATIInstance* ipiObject, const CATUnicodeString& iKey) ;
```

| 参数 | 类型 |
|------|------|
| ipiObject | `CATIInstance*` |
| iKey | `const CATUnicodeString&` |


---

**源文件**: `CAAPlantShipInterfaces.edu/CAAPspDefineUserProperties.m/LocalInterfaces/CAAPspDefineUserAttributes.h`
