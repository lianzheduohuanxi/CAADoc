---
title: "CAAEMaiUserPostProcessorIntegrationExtPPProviders"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAManufacturingItf.edu/CAAMaiUserPostProcessorIntegration.m/LocalInterfaces/CAAEMaiUserPostProcessorIntegrationExtPPProviders.h"
---

# CAAEMaiUserPostProcessorIntegrationExtPPProviders

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CATListPV.h`

## 虚方法

### GetListOfExternalPostProcessorProviders

```cpp
virtual HRESULT GetListOfExternalPostProcessorProviders(CATListPV& oListOfPostProcessorProviders) ;
```

Gives the list of Post Processor provides oListOfPostProcessorProviders : list of IID of interfaces of Post Processor providers

| 参数 | 类型 |
|------|------|
| oListOfPostProcessorProviders | `CATListPV&` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiUserPostProcessorIntegration.m/LocalInterfaces/CAAEMaiUserPostProcessorIntegrationExtPPProviders.h`
