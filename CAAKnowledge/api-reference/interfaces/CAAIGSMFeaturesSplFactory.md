---
title: "CAAIGSMFeaturesSplFactory"
type: "interface"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 2
visibility: "protected"
verified: true
---

# CAAIGSMFeaturesSplFactory

**基类**: CATBaseUnknown  
**模块**: CAAGSMInterfaces  
**可见性**: protected  
**方法数**: 2

## 方法列表

### CreateSewSkinBasic
```cpp
CAAIGSMSewSkinBasic  * CreateSewSkinBasic(CATISpecObject *ipSurfaceToSew , CATISpecObject *ipSurfaceSupport);
```

### CreateCircleSweepTg
```cpp
CAAIGSMCircleSweepTg * CreateCircleSweepTg(CATISpecObject *ipCurveRef  , CATISpecObject *ipSurfaceSupport , double radius);
```

## 依赖

- `CAAGsiFeaturesSplModel.h`
- `CATBaseUnknown.h`

