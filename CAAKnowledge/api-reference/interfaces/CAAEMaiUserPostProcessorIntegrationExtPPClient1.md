---
title: "CAAEMaiUserPostProcessorIntegrationExtPPClient1"
type: "interface"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAEMaiUserPostProcessorIntegrationExtPPClient1

**基类**: CATBaseUnknown  
**模块**: CAAManufacturingItf  
**可见性**: local  
**方法数**: 4

## 方法列表

### GetProviderNames
```cpp
HRESULT GetProviderNames(CATUnicodeString&        oNLSName     ,
				     CATString&               oKeywordName);
```

### GetListOfPPs
```cpp
HRESULT GetListOfPPs(CATListOfCATUnicodeString& oNLSList     , 
				     CATListOfCATString&        oKeywordList);
```

### RunHelp
```cpp
HRESULT RunHelp(CATString&                 iPPKeyword);
```

### RunPP
```cpp
HRESULT RunPP(CATListOfCATUnicodeString& iPPParams);
```

## 依赖

- `CATBaseUnknown.h`
- `CATString.h`
- `CATListOfCATString.h`
- `CATUnicodeString.h`
- `CATListOfCATUnicodeString.h`

