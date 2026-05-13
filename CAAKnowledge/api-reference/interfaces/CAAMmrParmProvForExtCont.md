---
title: "CAAMmrParmProvForExtCont"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATIParmProvider"
method_count: 1
source_file: "CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAMmrParmProvForExtCont.h"
---

# CAAMmrParmProvForExtCont

> CAAMmrParmProvForExtCont : CATIParmProvider Extension for MmrDataExtensionCont Extends ParmPublisher to FeatureExtensions Contained in MmrDataExtensionCont

**基类**: CATIParmProvider | **模块**: CAAMechanicalModeler | **方法数**: 1

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

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAMmrParmProvForExtCont.h`
