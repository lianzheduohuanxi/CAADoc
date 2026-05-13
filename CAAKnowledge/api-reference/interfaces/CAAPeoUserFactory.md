---
title: "CAAPeoUserFactory"
type: "ProtectedInterface"
module: "CAAOptimizationInterfaces"
base: ""
method_count: 1
source_file: "CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoUserFactory.h"
---

# CAAPeoUserFactory

> Provide services : to create the user algorithm by instanciating the user algo start up stored in the user catalog located in CAAOptimizationInterfaces.edu\CNext\ressources\graphic\ and named CAAPeoUserCatalog.CATfct.

**基类**: 无 | **模块**: CAAOptimizationInterfaces | **方法数**: 1

## 依赖

- `CAAPeoCreateUserAlgorithm.h`
- `CAAPeoReturnCodes.h`
- `CATIContainer.h`
- `CATIOptAlgorithm.h`

## 静态方法

### CreateUserAlgorithm

```cpp
static CATIOptAlgorithm_var CreateUserAlgorithm(CATIContainer *iContainer) ;
```

| 参数 | 类型 |
|------|------|
| *iContainer | `CATIContainer` |


---

**源文件**: `CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoUserFactory.h`
