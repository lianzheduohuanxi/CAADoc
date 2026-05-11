---
title: "CAAPeoUserAlgorithm"
type: "interface"
module: "CAAOptimizationInterfaces"
base: "CATOptAlgorithmAdapter"
method_count: 4
visibility: "local"
verified: true
---

# CAAPeoUserAlgorithm

**基类**: CATOptAlgorithmAdapter  
**模块**: CAAOptimizationInterfaces  
**可见性**: local  
**方法数**: 4

> LiteralFeatures

## 方法列表

### Run
```cpp
HRESULT Run(CATIOptOptimization_var & spiOptim);
```

### CheckCompatibility
```cpp
HRESULT CheckCompatibility(CATIOptOptimization_var &iOptim);
```

### SetSetting
```cpp
HRESULT SetSetting(const char* attrName, double content);
```

### GetSetting
```cpp
HRESULT GetSetting(const char* attrName, double &content);
```

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

