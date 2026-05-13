---
title: "CAAMmrNavigateProvForExtCont"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATINavigateProvider"
method_count: 1
source_file: "CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAMmrNavigateProvForExtCont.h"
---

# CAAMmrNavigateProvForExtCont

> CAAMmrNavigateProvForExtCont: CATIUpdateProviderExtension Extends CATINavigateObject Mechanism to FeatureExtensions Contained in MmrDataExtensionCont

**基类**: CATINavigateProvider | **模块**: CAAMechanicalModeler | **方法数**: 1

## 依赖

- `CATINavigateProvider.h`

## 公共方法

### GetChildren

```cpp
HRESULT GetChildren(CATBaseUnknown * iObj, CATListPtrCATBaseUnknown ** oListChildren) ;
```

| 参数 | 类型 |
|------|------|
| iObj | `CATBaseUnknown *` |
| oListChildren | `CATListPtrCATBaseUnknown **` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAMmrNavigateProvForExtCont.h`
