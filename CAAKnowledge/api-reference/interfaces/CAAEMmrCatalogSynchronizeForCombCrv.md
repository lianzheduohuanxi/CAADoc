---
title: "CAAEMmrCatalogSynchronizeForCombCrv"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 6
visibility: "local"
verified: true
---

# CAAEMmrCatalogSynchronizeForCombCrv

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**可见性**: local  
**方法数**: 6

## 方法列表

### GetAlias
```cpp
HRESULT GetAlias(CATUnicodeString& oAlias);
```

### GetEmbeddedPreview
```cpp
HRESULT GetEmbeddedPreview(CATPixelImage** oImage);
```

### GetKeywordValue
```cpp
HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   int& oKeyWordValue);
```

### GetKeywordValue
```cpp
HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   const CATICkeType* iKeywordType,
                                   double& oKeyWordValue);
```

### GetKeywordValue
```cpp
HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   CATCke::Boolean & oKeyWordValue);
```

### GetKeywordValue
```cpp
HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   CATUnicodeString& oKeyWordValue);
```

## 依赖

- `CATBaseUnknown.h`
- `CATICkeType.h`

