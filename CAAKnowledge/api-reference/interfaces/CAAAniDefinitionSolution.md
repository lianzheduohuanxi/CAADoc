---
title: "CAAAniDefinitionSolution"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATISamDefineSolution"
method_count: 2
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniDefinitionSolution.h"
---

# CAAAniDefinitionSolution

**基类**: CATISamDefineSolution | **模块**: CAAAnalysisInterfaces | **方法数**: 2

## 依赖

- `CATISamDefineSolution.h`

## 公共方法

### GetSetsForDefinition

```cpp
HRESULT GetSetsForDefinition(int & oNbDefineSets, CATSamDefineSet * & oDefineSets) ;
```

| 参数 | 类型 |
|------|------|
| oNbDefineSets | `int &` |
| oDefineSets | `CATSamDefineSet * &` |


### DefineDefaultSensors

```cpp
int DefineDefaultSensors(const CATBoolean iCreateSensor, const CATISamAnalysisSet* iNewSolution) ;
```

| 参数 | 类型 |
|------|------|
| iCreateSensor | `const CATBoolean` |
| iNewSolution | `const CATISamAnalysisSet*` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniDefinitionSolution.h`
