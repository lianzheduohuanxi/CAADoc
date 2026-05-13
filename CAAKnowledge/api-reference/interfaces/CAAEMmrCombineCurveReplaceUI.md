---
title: "CAAEMmrCombineCurveReplaceUI"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurveReplace.m/LocalInterfaces/CAAEMmrCombineCurveReplaceUI.h"
---

# CAAEMmrCombineCurveReplaceUI

> Data extension implementing the CATIReplaceUI interface which manages the depth of a given Selection Path.

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### FindValidElementForReplace

```cpp
HRESULT FindValidElementForReplace(const CATUnicodeString& iRole, const CATPathElement* ipSelection, const CATBaseUnknown* ipOldValue, CATBaseUnknown*& opFoundElement) ;
```

| 参数 | 类型 |
|------|------|
| iRole | `const CATUnicodeString&` |
| ipSelection | `const CATPathElement*` |
| ipOldValue | `const CATBaseUnknown*` |
| opFoundElement | `CATBaseUnknown*&` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurveReplace.m/LocalInterfaces/CAAEMmrCombineCurveReplaceUI.h`
