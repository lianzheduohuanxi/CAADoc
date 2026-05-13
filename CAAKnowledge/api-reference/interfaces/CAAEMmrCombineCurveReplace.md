---
title: "CAAEMmrCombineCurveReplace"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATSpecReplaceExt"
method_count: 3
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurveReplace.m/LocalInterfaces/CAAEMmrCombineCurveReplace.h"
---

# CAAEMmrCombineCurveReplace

> Data extension implementing the CATIReplace interface which  manages the replacement of a Feature by another one for a given Role. This extension extends the CombineCurve Feature.

**基类**: CATSpecReplaceExt | **模块**: CAAMechanicalModeler | **方法数**: 3

## 依赖

- `CATSpecReplaceExt.h`

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


### GetRequestedBehavior

```cpp
HRESULT GetRequestedBehavior(const CATUnicodeString & iAttributeName, CATListPtrIID ** oBehaviorArray, int * oBehaviorSize) ;
```

| 参数 | 类型 |
|------|------|
| iAttributeName | `const CATUnicodeString &` |
| oBehaviorArray | `CATListPtrIID **` |
| oBehaviorSize | `int *` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurveReplace.m/LocalInterfaces/CAAEMmrCombineCurveReplace.h`
