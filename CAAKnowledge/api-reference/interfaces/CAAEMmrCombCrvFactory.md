---
title: "CAAEMmrCombCrvFactory"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurve.m/LocalInterfaces/CAAEMmrCombCrvFactory.h"
---

# CAAEMmrCombCrvFactory

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### CreateCombinedCurve

```cpp
HRESULT CreateCombinedCurve(CATISpecObject *ipiSpecOnCurve1, CATISpecObject *ipiSpecOnDirection1, CATISpecObject *ipiSpecOnCurve2, CATISpecObject *ipiSpecOnDirection2, CATISpecObject **opiSpecOnCombinedCurve) ;
```

| 参数 | 类型 |
|------|------|
| *ipiSpecOnCurve1 | `CATISpecObject` |
| *ipiSpecOnDirection1 | `CATISpecObject` |
| *ipiSpecOnCurve2 | `CATISpecObject` |
| *ipiSpecOnDirection2 | `CATISpecObject` |
| **opiSpecOnCombinedCurve | `CATISpecObject` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurve.m/LocalInterfaces/CAAEMmrCombCrvFactory.h`
