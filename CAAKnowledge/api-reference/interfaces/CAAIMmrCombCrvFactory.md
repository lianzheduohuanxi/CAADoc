---
title: "CAAIMmrCombCrvFactory"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
verified: true
---

# CAAIMmrCombCrvFactory

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**方法数**: 1

## 方法列表

### CreateCombinedCurve
```cpp
HRESULT CreateCombinedCurve(CATISpecObject *ipCurve1 ,
                                            CATISpecObject *ipDirection1 ,
                                            CATISpecObject *ipCurve2 ,
                                            CATISpecObject *ipDirection2 ,
                                            CATISpecObject **opCombinedCurve);
```

