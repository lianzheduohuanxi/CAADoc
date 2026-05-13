---
title: "CAAEMaiUserPostProcessorIntegrationExtPPClient1"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAManufacturingItf.edu/CAAMaiUserPostProcessorIntegration.m/LocalInterfaces/CAAEMaiUserPostProcessorIntegrationExtPPClient1.h"
---

# CAAEMaiUserPostProcessorIntegrationExtPPClient1

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATString.h`
- `CATListOfCATString.h`
- `CATUnicodeString.h`
- `CATListOfCATUnicodeString.h`

## 虚方法

### GetProviderNames

```cpp
virtual HRESULT GetProviderNames(CATUnicodeString& oNLSName, CATString& oKeywordName) ;
```

Gives the Post Processor provider name oNLSName : in native language : "My Post Processor Provider" oKeywordName : "MYPPPROVIDER"

| 参数 | 类型 |
|------|------|
| oNLSName | `CATUnicodeString&` |
| oKeywordName | `CATString&` |


### GetListOfPPs

```cpp
virtual HRESULT GetListOfPPs(CATListOfCATUnicodeString& oNLSList, CATListOfCATString& oKeywordList) ;
```

Gives the list of PPs managed by the provider oNLSList : in native language oKeywordList : qs keywords

| 参数 | 类型 |
|------|------|
| oNLSList | `CATListOfCATUnicodeString&` |
| oKeywordList | `CATListOfCATString&` |


### RunHelp

```cpp
virtual HRESULT RunHelp(CATString& iPPKeyword) ;
```

Open method to run PP help

| 参数 | 类型 |
|------|------|
| iPPKeyword | `CATString&` |


### RunPP

```cpp
virtual HRESULT RunPP(CATListOfCATUnicodeString& iPPParams) ;
```

Open method to run PP

| 参数 | 类型 |
|------|------|
| iPPParams | `CATListOfCATUnicodeString&` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiUserPostProcessorIntegration.m/LocalInterfaces/CAAEMaiUserPostProcessorIntegrationExtPPClient1.h`
