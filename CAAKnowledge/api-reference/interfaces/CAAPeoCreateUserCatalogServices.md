---
title: "CAAPeoCreateUserCatalogServices"
type: "ProtectedInterface"
module: "CAAOptimizationInterfaces"
base: ""
method_count: 3
source_file: "CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoCreateUserCatalogServices.h"
---

# CAAPeoCreateUserCatalogServices

> Provide services : to create a catalog of features to create your own algorithm start up in the catalog WARNING: NO USAGE HERE This code is given in order to show you how the user catalog containing the user algo start up has been created. =============================================================

**基类**: 无 | **模块**: CAAOptimizationInterfaces | **方法数**: 3

## 依赖

- `CAAPeoBasis.h`
- `CAAPeoReturnCodes.h`
- `CATIContainer.h`
- `CATIOptAlgorithm.h`

## 静态方法

### CAAPeoCreateFillAndSaveUserCatalog

```cpp
static HRESULT CAAPeoCreateFillAndSaveUserCatalog(const CATUnicodeString& iStoragePathWithoutName) ;
```

| 参数 | 类型 |
|------|------|
| iStoragePathWithoutName | `const CATUnicodeString&` |


### CAAPeoCreateUserCatalog

```cpp
static CAAPeoReturnCodes CAAPeoCreateUserCatalog(CATICatalog** opCatalog, const char* iStorageName) ;
```

| 参数 | 类型 |
|------|------|
| opCatalog | `CATICatalog**` |
| iStorageName | `const char*` |


### CAAPeoCreateUserAlgoStartUpInCatalog

```cpp
static CAAPeoReturnCodes CAAPeoCreateUserAlgoStartUpInCatalog(CATICatalog* piCatalog) ;
```

| 参数 | 类型 |
|------|------|
| piCatalog | `CATICatalog*` |


---

**源文件**: `CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoCreateUserCatalogServices.h`
