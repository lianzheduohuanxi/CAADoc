---
title: "CAAIV5V6ExtMmrCombCrvFactory"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
verified: true
---

# CAAIV5V6ExtMmrCombCrvFactory

**基类**: CATBaseUnknown  
**模块**: CAAV5V6MechanicalModeler  
**方法数**: 1

## 方法列表

### CreateCombinedCurve
```cpp
HRESULT CreateCombinedCurve(CATBaseUnknown  *ipCurve1,
                                          CATBaseUnknown  *ipDirection1,
                                          CATBaseUnknown  *ipCurve2,
                                          CATBaseUnknown  *ipDirection2,
                                          CAAIV5V6ExtMmrCombinedCurve *& opCombinedCurve);
```

