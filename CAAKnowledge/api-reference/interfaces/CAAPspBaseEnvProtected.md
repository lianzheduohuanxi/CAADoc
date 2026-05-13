---
title: "CAAPspBaseEnvProtected"
type: "ProtectedInterface"
module: "CAAPlantShipInterfaces"
base: ""
method_count: 10
source_file: "CAAPlantShipInterfaces.edu/ProtectedInterfaces/CAAPspBaseEnvProtected.h"
---

# CAAPspBaseEnvProtected

**基类**: 无 | **模块**: CAAPlantShipInterfaces | **方法数**: 10

## 依赖

- `CAAPspUtilitiesProtected.h`
- `CATIContainer.h`
- `CATUnicodeString.h`
- `IUnknown.h`
- `CATBaseUnknown.h`
- `CAAPspUtilityMacros.h`

## 虚方法

### SaveDocument

```cpp
virtual void SaveDocument(const CATUnicodeString &iFileName) ;
```

Save document

| 参数 | 类型 |
|------|------|
| &iFileName | `const CATUnicodeString` |


### CreateCATProductEnv

```cpp
virtual void CreateCATProductEnv(const CATUnicodeString &iFileNameToBeLoaded) ;
```

Save document virtual void SaveDocument (const CATUnicodeString &iFileName); Create environment

| 参数 | 类型 |
|------|------|
| &iFileNameToBeLoaded | `const CATUnicodeString` |


### ApplicationInit

```cpp
virtual void ApplicationInit(const CATUnicodeString &iuApplicationContext = "CATPiping") ;
```

Initialize application

| 参数 | 类型 |
|------|------|
| "CATPiping" | `const CATUnicodeString &iuApplicationContext =` |


### GetRootProduct

```cpp
virtual CATIProduct * GetRootProduct() ;
```

Get root product in the document


### GetChildObject

```cpp
virtual IUnknown * GetChildObject(const IID &iIID, const CATUnicodeString &iuObjectName = "", const CATIProduct *ipiParentProduct = NULL) ;
```

Get a child object of a product iObjectTestMethod tests if child object meets criteria. ipiParentProduct is the product whose children will be searched. if NULL, the root product will be searched.

| 参数 | 类型 |
|------|------|
| &iIID | `const IID` |
| "" | `const CATUnicodeString &iuObjectName =` |
| NULL | `const CATIProduct *ipiParentProduct =` |


### GetAPhysicalObject

```cpp
virtual CATIPspPhysical * GetAPhysicalObject(const CATIProduct *ipiParentProduct = NULL) ;
```

Get the first physical object found under a parent product. NULL uses root product.

| 参数 | 类型 |
|------|------|
| NULL | `const CATIProduct *ipiParentProduct =` |


### GetALightObject

```cpp
virtual CATIPspLightPart * GetALightObject(const CATIProduct *ipiParentProduct = NULL) ;
```

Get the first physical light object found under a parent product. NULL uses root product.

| 参数 | 类型 |
|------|------|
| NULL | `const CATIProduct *ipiParentProduct =` |


### GetABendablePipeObject

```cpp
virtual CATIPspPhysical * GetABendablePipeObject(const CATIProduct *ipiParentProduct = NULL) ;
```

Get the first bendable pipe found under a parent product. NULL uses root product.

| 参数 | 类型 |
|------|------|
| NULL | `const CATIProduct *ipiParentProduct =` |


### GetALogicalLine

```cpp
virtual CATIPspLogicalLine * GetALogicalLine(const CATIProduct *ipiParentProduct = NULL) ;
```

Get the first logical line found under a parent product. NULL uses root product.

| 参数 | 类型 |
|------|------|
| NULL | `const CATIProduct *ipiParentProduct =` |


### CleanupSession

```cpp
virtual void CleanupSession() ;
```

Cleanup


---

**源文件**: `CAAPlantShipInterfaces.edu/ProtectedInterfaces/CAAPspBaseEnvProtected.h`
