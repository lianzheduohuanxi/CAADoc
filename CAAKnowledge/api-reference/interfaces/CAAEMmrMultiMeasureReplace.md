---
title: "CAAEMmrMultiMeasureReplace"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATIReplace"
method_count: 2
source_file: "CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSet.m/LocalInterfaces/CAAEMmrMultiMeasureReplace.h"
---

# CAAEMmrMultiMeasureReplace

> Data extension implementing the CATIReplace interface which  manages the replacement of a Feature by another one for a given Role. This extension extends the MmrMultiMeasure Features.

**基类**: CATIReplace | **模块**: CAAMechanicalModeler | **方法数**: 2

## 依赖

- `CATIReplace.h`

## 公共方法

### IsElementValidForReplace

```cpp
HRESULT IsElementValidForReplace(const CATUnicodeString& iNameOfRole, const CATBaseUnknown_var& ispElement, CATUnicodeString& oMessage, int& oElementValidity, const CATBaseUnknown_var& ispOldValue=NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| iNameOfRole | `const CATUnicodeString&` |
| ispElement | `const CATBaseUnknown_var&` |
| oMessage | `CATUnicodeString&` |
| oElementValidity | `int&` |
| ispOldValue=NULL_var | `const CATBaseUnknown_var&` |


### Replace

```cpp
HRESULT Replace(const CATUnicodeString& iNameOfRole, CATBaseUnknown_var& ispNewElement, const CATBaseUnknown_var& ispOldValue=NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| iNameOfRole | `const CATUnicodeString&` |
| ispNewElement | `CATBaseUnknown_var&` |
| ispOldValue=NULL_var | `const CATBaseUnknown_var&` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSet.m/LocalInterfaces/CAAEMmrMultiMeasureReplace.h`
