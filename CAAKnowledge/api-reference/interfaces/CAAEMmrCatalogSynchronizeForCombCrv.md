---
title: "CAAEMmrCatalogSynchronizeForCombCrv"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAMechanicalModeler.edu/CAAMmrCatalogCombCrv.m/LocalInterfaces/CAAEMmrCatalogSynchronizeForCombCrv.h"
---

# CAAEMmrCatalogSynchronizeForCombCrv

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CATICkeType.h`

## 虚方法

### GetAlias

```cpp
virtual HRESULT GetAlias(CATUnicodeString& oAlias) ;
```

| 参数 | 类型 |
|------|------|
| oAlias | `CATUnicodeString&` |


### GetEmbeddedPreview

```cpp
virtual HRESULT GetEmbeddedPreview(CATPixelImage** oImage) ;
```

| 参数 | 类型 |
|------|------|
| oImage | `CATPixelImage**` |


### GetKeywordValue

```cpp
virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName, int& oKeyWordValue) ;
```

| 参数 | 类型 |
|------|------|
| iKeywordName | `const CATUnicodeString&` |
| oKeyWordValue | `int&` |


### GetKeywordValue

```cpp
virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName, const CATICkeType* iKeywordType, double& oKeyWordValue) ;
```

| 参数 | 类型 |
|------|------|
| iKeywordName | `const CATUnicodeString&` |
| iKeywordType | `const CATICkeType*` |
| oKeyWordValue | `double&` |


### GetKeywordValue

```cpp
virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName, CATCke::Boolean & oKeyWordValue) ;
```

| 参数 | 类型 |
|------|------|
| iKeywordName | `const CATUnicodeString&` |
| oKeyWordValue | `CATCke::Boolean &` |


### GetKeywordValue

```cpp
virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName, CATUnicodeString& oKeyWordValue) ;
```

| 参数 | 类型 |
|------|------|
| iKeywordName | `const CATUnicodeString&` |
| oKeyWordValue | `CATUnicodeString&` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCatalogCombCrv.m/LocalInterfaces/CAAEMmrCatalogSynchronizeForCombCrv.h`
