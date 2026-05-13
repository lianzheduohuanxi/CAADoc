---
title: "CAAGetFLEXEquivalentModulusExt"
type: "LocalClass"
module: "CAAElecHarnessItf"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAElecHarnessItf.edu/CAAEhiFLEXImpl.m/LocalInterfaces/CAAGetFLEXEquivalentModulusExt.h"
---

# CAAGetFLEXEquivalentModulusExt

**基类**: CATBaseUnknown | **模块**: CAAElecHarnessItf | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CATIEhiFLEX.h`

## 公共方法

### GetFLEXEquivalentModulus

```cpp
HRESULT GetFLEXEquivalentModulus(CATListValCATBaseUnknown_var * ipListOfWireWireGroup, CATListValCATBaseUnknown_var * ipOrderedListOfProtectionReference, CATListValCATBaseUnknown_var * ipInternalSpliceReferenceList, CATEhiProfileType iProfile, double iProfileLength1, double iProfileLength2, int iBundleSegmentFlexibility, double & oYoungModulusEquivalent, double & oEquivalentRatioToBend, double & oEquivalentRatioToTwist) ;
```

| 参数 | 类型 |
|------|------|
| ipListOfWireWireGroup | `CATListValCATBaseUnknown_var *` |
| ipOrderedListOfProtectionReference | `CATListValCATBaseUnknown_var *` |
| ipInternalSpliceReferenceList | `CATListValCATBaseUnknown_var *` |
| iProfile | `CATEhiProfileType` |
| iProfileLength1 | `double` |
| iProfileLength2 | `double` |
| iBundleSegmentFlexibility | `int` |
| oYoungModulusEquivalent | `double &` |
| oEquivalentRatioToBend | `double &` |
| oEquivalentRatioToTwist | `double &` |


---

**源文件**: `CAAElecHarnessItf.edu/CAAEhiFLEXImpl.m/LocalInterfaces/CAAGetFLEXEquivalentModulusExt.h`
