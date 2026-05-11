---
title: "CAAECloAppWeldOffset"
type: "interface"
module: "CAACommonLayoutItf"
base: "CATBaseUnknown"
method_count: 1
visibility: "local"
verified: true
---

# CAAECloAppWeldOffset

**基类**: CATBaseUnknown  
**模块**: CAACommonLayoutItf  
**可见性**: local  
**方法数**: 1

> -----------------------------------------------------------------------

## 方法列表

### GetWeldOffset
```cpp
HRESULT GetWeldOffset(const wchar_t* iaWeldEndStyle,
                                  const double idRunInsideRadius,
                                  const double idRunOutsideRadius,
                                  const double idBranchInsideRadius,
                                  const double idBranchOutsideRadius,
                                  const double idWeldGap,
                                  double* odWeldOffset);
```

## 依赖

- `CATBaseUnknown.h`

