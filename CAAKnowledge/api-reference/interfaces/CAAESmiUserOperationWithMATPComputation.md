---
title: "CAAESmiUserOperationWithMATPComputation"
type: "LocalClass"
module: "CAASurfaceMachiningItf"
base: "CATIMfgComputeToolPathCustom"
method_count: 1
source_file: "CAASurfaceMachiningItf.edu/CAASmiConnectUserOperationWithMA.m/LocalInterfaces/CAAESmiUserOperationWithMATPComputation.h"
---

# CAAESmiUserOperationWithMATPComputation

**基类**: CATIMfgComputeToolPathCustom | **模块**: CAASurfaceMachiningItf | **方法数**: 1

## 依赖

- `CATIMfgComputeToolPathCustom.h`
- `CATGeometry.h`

## 公共方法

### ComputeToolPath

```cpp
HRESULT ComputeToolPath(const CATIContainer_var& iContainer, CATIMfgToolPath_var& oTP) ;
```

Computes the tool path of the current user operation.

| 参数 | 类型 |
|------|------|
| iContainer | `const CATIContainer_var&` |
| oTP | `CATIMfgToolPath_var&` |


---

**源文件**: `CAASurfaceMachiningItf.edu/CAASmiConnectUserOperationWithMA.m/LocalInterfaces/CAAESmiUserOperationWithMATPComputation.h`
