---
title: "CAAEV5V6ExtMmrCombineCurveReplace"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATMmrReplaceAdapter"
method_count: 3
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCombinedCurveReplace.m/LocalInterfaces/CAAEV5V6ExtMmrCombineCurveReplace.h"
---

# CAAEV5V6ExtMmrCombineCurveReplace

> Data extension implementing the CATIReplace interface which  manages the replacement of a Feature by another one for a given Role. This extension extends the V5V6ExtCombinedCurve Feature. Note : CAAEV5V6ExtMmrCombinedCurveReplace is the same use case as CAAEMmrCombinedCurveReplace. The objective is to have the same source delivered in V5 and V6. Any specific code to either V5 or V6 is flagged.

**基类**: CATMmrReplaceAdapter | **模块**: CAAV5V6MechanicalModeler | **方法数**: 3

## 依赖

- `CATMmrReplaceAdapter.h`

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

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCombinedCurveReplace.m/LocalInterfaces/CAAEV5V6ExtMmrCombineCurveReplace.h`
