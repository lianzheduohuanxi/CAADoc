---
title: "CAAPeoUserAlgorithm"
type: "LocalClass"
module: "CAAOptimizationInterfaces"
base: "CATOptAlgorithmAdapter"
method_count: 4
source_file: "CAAOptimizationInterfaces.edu/CAAPeoCreateUserAlgorithm.m/LocalInterfaces/CAAPeoUserAlgorithm.h"
---

# CAAPeoUserAlgorithm

**基类**: CATOptAlgorithmAdapter | **模块**: CAAOptimizationInterfaces | **方法数**: 4

## 依赖

- `CATOptAlgorithmAdapter.h`
- `CATIOptGoal.h`
- `CATIOptimizationLog.h`
- `CATListOfInt.h`
- `CATICkeType.h`
- `CATICkeParm.h`
- `CATICkeRelationExp.h`
- `CATIParmPublisher.h`
- `CATICkeParameterSet.h`

## 虚方法

### Run

```cpp
virtual HRESULT Run(CATIOptOptimization_var & spiOptim) ;
```

| 参数 | 类型 |
|------|------|
| spiOptim | `CATIOptOptimization_var &` |


### CheckCompatibility

```cpp
virtual HRESULT CheckCompatibility(CATIOptOptimization_var &iOptim) ;
```

| 参数 | 类型 |
|------|------|
| &iOptim | `CATIOptOptimization_var` |


### SetSetting

```cpp
virtual HRESULT SetSetting(const char* attrName, double content) ;
```

| 参数 | 类型 |
|------|------|
| attrName | `const char*` |
| content | `double` |


### GetSetting

```cpp
virtual HRESULT GetSetting(const char* attrName, double &content) ;
```

| 参数 | 类型 |
|------|------|
| attrName | `const char*` |
| &content | `double` |


---

**源文件**: `CAAOptimizationInterfaces.edu/CAAPeoCreateUserAlgorithm.m/LocalInterfaces/CAAPeoUserAlgorithm.h`
