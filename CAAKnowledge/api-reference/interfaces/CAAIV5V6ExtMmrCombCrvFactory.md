---
title: "CAAIV5V6ExtMmrCombCrvFactory"
type: "PublicInterface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrCombCrvFactory.h"
---

# CAAIV5V6ExtMmrCombCrvFactory

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 1

## 依赖

- `CAAV5V6ExtMmrCombinedCurve.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### CreateCombinedCurve

```cpp
virtual HRESULT CreateCombinedCurve(CATBaseUnknown *ipCurve1, CATBaseUnknown *ipDirection1, CATBaseUnknown *ipCurve2, CATBaseUnknown *ipDirection2, CAAIV5V6ExtMmrCombinedCurve *& opCombinedCurve) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *ipCurve1 | `CATBaseUnknown` |
| *ipDirection1 | `CATBaseUnknown` |
| *ipCurve2 | `CATBaseUnknown` |
| *ipDirection2 | `CATBaseUnknown` |
| opCombinedCurve | `CAAIV5V6ExtMmrCombinedCurve *&` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrCombCrvFactory.h`
