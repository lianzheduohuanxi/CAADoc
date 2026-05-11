---
title: "CAAECloPartSelection"
type: "interface"
module: "CAACommonLayoutItf"
base: "CATECloPartSelectionAdapter"
method_count: 3
visibility: "local"
verified: true
---

# CAAECloPartSelection

**基类**: CATECloPartSelectionAdapter  
**模块**: CAACommonLayoutItf  
**可见性**: local  
**方法数**: 3

> -----------------------------------------------------------------------

## 方法列表

### FilterPartSelection
```cpp
HRESULT FilterPartSelection(const CATUnicodeString& iuStandard,
                                            const CATUnicodeString& iuSpec,
                                            const CATUnicodeString& iuPartType,
                                            const CATIUnknownList *iLFilterParameters,
                                            const CATIUnknownList *iLSortParameters,
                                            const CATIUnknownList *iListDescription,
                                            CATIUnknownList*& oListDescription);
```

### IsExternalProgramNeeded
```cpp
HRESULT IsExternalProgramNeeded(const CATUnicodeString &iuApplicationContext,
                                          const CATUnicodeString &iuStandard,
                                          const CATUnicodeString &iuSpec,
                                          const CATUnicodeString &iuPartType,
                                          int &oiActivate);
```

### RefinePartSelection
```cpp
HRESULT RefinePartSelection(const CATUnicodeString &iuApplicationContext,
                                          const CATUnicodeString &iuStandard,
                                          const CATUnicodeString &iuSpec,
                                          const CATUnicodeString &iuPartType,
                                          const CATIUnknownList *iLEnvironmentParameters,
                                          const CATIUnknownList *iLFilterParameters,
                                          const CATIUnknownList *iLSortParameters,
                                          const IUnknown *ipiCatalogObjectToBeSearched,
                                          CATListValCATUnicodeString &opListPartNumbersFound);
```

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`
- `CATECloPartSelectionAdapter.h`

