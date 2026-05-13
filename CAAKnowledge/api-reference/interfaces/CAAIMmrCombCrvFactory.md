---
title: "CAAIMmrCombCrvFactory"
type: "PublicInterface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCombCrvFactory.h"
---

# CAAIMmrCombCrvFactory

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 1

## 依赖

- `CAAMmrCombinedCurve.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### CreateCombinedCurve

```cpp
virtual HRESULT CreateCombinedCurve(CATISpecObject *ipCurve1, CATISpecObject *ipDirection1, CATISpecObject *ipCurve2, CATISpecObject *ipDirection2, CATISpecObject **opCombinedCurve) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *ipCurve1 | `CATISpecObject` |
| *ipDirection1 | `CATISpecObject` |
| *ipCurve2 | `CATISpecObject` |
| *ipDirection2 | `CATISpecObject` |
| **opCombinedCurve | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCombCrvFactory.h`
