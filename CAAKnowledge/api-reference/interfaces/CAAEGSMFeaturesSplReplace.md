---
title: "CAAEGSMFeaturesSplReplace"
type: "LocalClass"
module: "CAAGSMInterfaces"
base: "CATSpecReplaceExt"
method_count: 2
source_file: "CAAGSMInterfaces.edu/CAAGsiFeaturesSplModel.m/LocalInterfaces/CAAEGSMFeaturesSplReplace.h"
---

# CAAEGSMFeaturesSplReplace

**基类**: CATSpecReplaceExt | **模块**: CAAGSMInterfaces | **方法数**: 2

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


---

**源文件**: `CAAGSMInterfaces.edu/CAAGsiFeaturesSplModel.m/LocalInterfaces/CAAEGSMFeaturesSplReplace.h`
