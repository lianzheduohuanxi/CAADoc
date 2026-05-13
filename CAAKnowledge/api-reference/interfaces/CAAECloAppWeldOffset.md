---
title: "CAAECloAppWeldOffset"
type: "LocalClass"
module: "CAACommonLayoutItf"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAACommonLayoutItf.edu/CAACloSetup.m/LocalInterfaces/CAAECloAppWeldOffset.h"
---

# CAAECloAppWeldOffset

**基类**: CATBaseUnknown | **模块**: CAACommonLayoutItf | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetWeldOffset

```cpp
virtual HRESULT GetWeldOffset(const wchar_t* iaWeldEndStyle, const double idRunInsideRadius, const double idRunOutsideRadius, const double idBranchInsideRadius, const double idBranchOutsideRadius, const double idWeldGap, double* odWeldOffset) ;
```

| 参数 | 类型 |
|------|------|
| iaWeldEndStyle | `const wchar_t*` |
| idRunInsideRadius | `const double` |
| idRunOutsideRadius | `const double` |
| idBranchInsideRadius | `const double` |
| idBranchOutsideRadius | `const double` |
| idWeldGap | `const double` |
| odWeldOffset | `double*` |


---

**源文件**: `CAACommonLayoutItf.edu/CAACloSetup.m/LocalInterfaces/CAAECloAppWeldOffset.h`
