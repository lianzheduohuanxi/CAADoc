---
title: "CAAEPstINFCSORoot"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/CAAPstINFCommands.m/LocalInterfaces/CAAEPstINFCSORoot.h"
---

# CAAEPstINFCSORoot

> Data extension of the CAAPstINFRoot component, implementing the CATICSOFilter interface to enable the selection of the contextual menu commands. Illustrates programming the CSO Filter on an object by implementing the CATICSOFilter interface of the ApplicationFrame framework. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATLISTV_CATBaseUnknown.h`

## 公共方法

### CommandIsAvailable

```cpp
HRESULT CommandIsAvailable(const char *ipHeaderID, const CATCSO *ipCSO) ;
```

Defines what commands are available in the contextual menu for the Root object.

| 参数 | 类型 |
|------|------|
| *ipHeaderID | `const char` |
| *ipCSO | `const CATCSO` |


### AvailableElements

```cpp
HRESULT AvailableElements(const char *ipHeaderID, const CATCSO *ipCSO, CATListValCATBaseUnknown_var **iospAvailableElements) ;
```

Returns the available objects from the current selection.

| 参数 | 类型 |
|------|------|
| *ipHeaderID | `const char` |
| *ipCSO | `const CATCSO` |
| **iospAvailableElements | `CATListValCATBaseUnknown_var` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFCommands.m/LocalInterfaces/CAAEPstINFCSORoot.h`
