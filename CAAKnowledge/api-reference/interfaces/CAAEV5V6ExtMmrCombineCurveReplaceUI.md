---
title: "CAAEV5V6ExtMmrCombineCurveReplaceUI"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCombinedCurveReplace.m/LocalInterfaces/CAAEV5V6ExtMmrCombineCurveReplaceUI.h"
---

# CAAEV5V6ExtMmrCombineCurveReplaceUI

> Data extension implementing the CATIReplaceUI interface which manages the depth of a given Selection Path.

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 1

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

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCombinedCurveReplace.m/LocalInterfaces/CAAEV5V6ExtMmrCombineCurveReplaceUI.h`
