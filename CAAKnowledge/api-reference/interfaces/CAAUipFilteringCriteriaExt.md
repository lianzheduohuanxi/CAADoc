---
title: "CAAUipFilteringCriteriaExt"
type: "LocalClass"
module: "CAAElecRoutingItf"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAAElecRoutingItf.edu/CAAEwrCriteria.m/LocalInterfaces/CAAUipFilteringCriteriaExt.h"
---

# CAAUipFilteringCriteriaExt

**基类**: CATBaseUnknown | **模块**: CAAElecRoutingItf | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### ListCriteria

```cpp
HRESULT ListCriteria(const CATListValCATUnicodeString * iListOfSystems, CATListValCATUnicodeString *& oListOfCriteria) ;
```

| 参数 | 类型 |
|------|------|
| iListOfSystems | `const CATListValCATUnicodeString *` |
| oListOfCriteria | `CATListValCATUnicodeString *&` |


### ListWires

```cpp
HRESULT ListWires(const CATListValCATUnicodeString * iListOfSystems, const CATListValCATUnicodeString * iListOfCriteria, CATListValCATUnicodeString *& oListOfWires) ;
```

| 参数 | 类型 |
|------|------|
| iListOfSystems | `const CATListValCATUnicodeString *` |
| iListOfCriteria | `const CATListValCATUnicodeString *` |
| oListOfWires | `CATListValCATUnicodeString *&` |


### ListSystems

```cpp
HRESULT ListSystems(CATListValCATUnicodeString *& oListOfSystems) ;
```

| 参数 | 类型 |
|------|------|
| oListOfSystems | `CATListValCATUnicodeString *&` |


---

**源文件**: `CAAElecRoutingItf.edu/CAAEwrCriteria.m/LocalInterfaces/CAAUipFilteringCriteriaExt.h`
