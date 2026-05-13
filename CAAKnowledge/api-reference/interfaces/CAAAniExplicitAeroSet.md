---
title: "CAAAniExplicitAeroSet"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATISamExplicitation"
method_count: 1
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniExplicitAeroSet.h"
---

# CAAAniExplicitAeroSet

**基类**: CATISamExplicitation | **模块**: CAAAnalysisInterfaces | **方法数**: 1

## 依赖

- `CATISamExplicitation.h`

## 公共方法

### TranslateToFieldModel

```cpp
HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, CATISamAnalysisModel* iFEMModel, CATAnalysisExplicitListUsr& iOldExplObjects, CATAnalysisExplicitListUsr& oNewExplObjects) ;
```

| 参数 | 类型 |
|------|------|
| iFeatToTranslate | `CATISpecObject*` |
| iFEMModel | `CATISamAnalysisModel*` |
| iOldExplObjects | `CATAnalysisExplicitListUsr&` |
| oNewExplObjects | `CATAnalysisExplicitListUsr&` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniExplicitAeroSet.h`
