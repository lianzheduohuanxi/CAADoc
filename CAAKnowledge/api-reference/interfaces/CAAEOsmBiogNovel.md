---
title: "CAAEOsmBiogNovel"
type: "LocalClass"
module: "CAAObjectSpecsModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAObjectSpecsModeler.edu/CAAOsmManageExtensions.m/LocalInterfaces/CAAEOsmBiogNovel.h"
---

# CAAEOsmBiogNovel

> This class is an implementation of the CAAIBiogNovel interface for the "CAAOsmBiographicalNovel" extension late-type. It essentially retrieves and valuates the values of the attributes of this extension.This implementation is included in Use Case CAAOsmMainExtensions.m. Main Methods: GetEpoch:  Returns the value of the "Epoch" attribute. SetEpoch:  Valuates the "Epoch" attribute. GetDomain: Returns the value of the "Domain" attribute. SetDomain: Valuates the "Domain" attribute.

**基类**: CATBaseUnknown | **模块**: CAAObjectSpecsModeler | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

## 公共方法

### GetEpoch

```cpp
HRESULT GetEpoch(CATUnicodeString *opEpoch) ;
```

| 参数 | 类型 |
|------|------|
| *opEpoch | `CATUnicodeString` |


### SetEpoch

```cpp
HRESULT SetEpoch(const CATUnicodeString iEpoch) ;
```

| 参数 | 类型 |
|------|------|
| iEpoch | `const CATUnicodeString` |


### GetDomain

```cpp
HRESULT GetDomain(CATUnicodeString *opDomain) ;
```

| 参数 | 类型 |
|------|------|
| *opDomain | `CATUnicodeString` |


### SetDomain

```cpp
HRESULT SetDomain(const CATUnicodeString iDomain) ;
```

| 参数 | 类型 |
|------|------|
| iDomain | `const CATUnicodeString` |


---

**源文件**: `CAAObjectSpecsModeler.edu/CAAOsmManageExtensions.m/LocalInterfaces/CAAEOsmBiogNovel.h`
