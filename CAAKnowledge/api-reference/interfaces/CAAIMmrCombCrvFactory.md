---
title: "CAAIMmrCombCrvFactory"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
visibility: "public"
verified: true
---

# CAAIMmrCombCrvFactory

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**可见性**: public  
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

## 依赖

- `CAAMmrCombinedCurve.h`
- `CATBaseUnknown.h`

