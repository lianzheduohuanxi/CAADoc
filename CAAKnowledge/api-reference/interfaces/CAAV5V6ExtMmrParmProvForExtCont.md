---
title: "CAAV5V6ExtMmrParmProvForExtCont"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATIParmProvider"
method_count: 1
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAV5V6ExtMmrParmProvForExtCont.h"
---

# CAAV5V6ExtMmrParmProvForExtCont

> CAAV5V6ExtMmrNavigateProvForExtCont: Implements CATIParmProvider interface. Extends CATIParmPublisher Mechanism to Extension Features contained in the applicative container V5V6ExtMmrDataExtensionCont (type = CAAV5V6ExtMmrNavigateProvForExtCont)

**基类**: CATIParmProvider | **模块**: CAAV5V6MechanicalModeler | **方法数**: 1

## 依赖

- `CATIParmProvider.h`

## 公共方法

### GetDirectChildren

```cpp
HRESULT GetDirectChildren(CATClassId intfName, CATListValCATBaseUnknown_var* oList, CATBaseUnknown* iObj) ;
```

| 参数 | 类型 |
|------|------|
| intfName | `CATClassId` |
| oList | `CATListValCATBaseUnknown_var*` |
| iObj | `CATBaseUnknown*` |


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAV5V6ExtMmrParmProvForExtCont.h`
