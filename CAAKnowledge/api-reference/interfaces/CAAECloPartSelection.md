---
title: "CAAECloPartSelection"
type: "LocalClass"
module: "CAACommonLayoutItf"
base: "CATECloPartSelectionAdapter"
method_count: 3
source_file: "CAACommonLayoutItf.edu/CAACloPartSelection.m/LocalInterfaces/CAAECloPartSelection.h"
---

# CAAECloPartSelection

**基类**: CATECloPartSelectionAdapter | **模块**: CAACommonLayoutItf | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`
- `CATECloPartSelectionAdapter.h`

## 虚方法

### FilterPartSelection

```cpp
virtual HRESULT FilterPartSelection(const CATUnicodeString& iuStandard, const CATUnicodeString& iuSpec, const CATUnicodeString& iuPartType, const CATIUnknownList *iLFilterParameters, const CATIUnknownList *iLSortParameters, const CATIUnknownList *iListDescription, CATIUnknownList*& oListDescription) ;
```

| 参数 | 类型 |
|------|------|
| iuStandard | `const CATUnicodeString&` |
| iuSpec | `const CATUnicodeString&` |
| iuPartType | `const CATUnicodeString&` |
| *iLFilterParameters | `const CATIUnknownList` |
| *iLSortParameters | `const CATIUnknownList` |
| *iListDescription | `const CATIUnknownList` |
| oListDescription | `CATIUnknownList*&` |


### IsExternalProgramNeeded

```cpp
virtual HRESULT IsExternalProgramNeeded(const CATUnicodeString &iuApplicationContext, const CATUnicodeString &iuStandard, const CATUnicodeString &iuSpec, const CATUnicodeString &iuPartType, int &oiActivate) ;
```

| 参数 | 类型 |
|------|------|
| &iuApplicationContext | `const CATUnicodeString` |
| &iuStandard | `const CATUnicodeString` |
| &iuSpec | `const CATUnicodeString` |
| &iuPartType | `const CATUnicodeString` |
| &oiActivate | `int` |


### RefinePartSelection

```cpp
virtual HRESULT RefinePartSelection(const CATUnicodeString &iuApplicationContext, const CATUnicodeString &iuStandard, const CATUnicodeString &iuSpec, const CATUnicodeString &iuPartType, const CATIUnknownList *iLEnvironmentParameters, const CATIUnknownList *iLFilterParameters, const CATIUnknownList *iLSortParameters, const IUnknown *ipiCatalogObjectToBeSearched, CATListValCATUnicodeString &opListPartNumbersFound) ;
```

| 参数 | 类型 |
|------|------|
| &iuApplicationContext | `const CATUnicodeString` |
| &iuStandard | `const CATUnicodeString` |
| &iuSpec | `const CATUnicodeString` |
| &iuPartType | `const CATUnicodeString` |
| *iLEnvironmentParameters | `const CATIUnknownList` |
| *iLFilterParameters | `const CATIUnknownList` |
| *iLSortParameters | `const CATIUnknownList` |
| *ipiCatalogObjectToBeSearched | `const IUnknown` |
| &opListPartNumbersFound | `CATListValCATUnicodeString` |


---

**源文件**: `CAACommonLayoutItf.edu/CAACloPartSelection.m/LocalInterfaces/CAAECloPartSelection.h`
