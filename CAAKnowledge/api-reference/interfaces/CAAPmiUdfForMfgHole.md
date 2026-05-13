---
title: "CAAPmiUdfForMfgHole"
type: "LocalClass"
module: "CAAPrismaticMachiningItf"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfForMfgHole.h"
---

# CAAPmiUdfForMfgHole

**基类**: CATBaseUnknown | **模块**: CAAPrismaticMachiningItf | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CATICkeParm.h`
- `CATString.h`

## 虚方法

### GetDiameter

```cpp
virtual HRESULT GetDiameter(CATICkeParm_var &oDiameter) ;
```

| 参数 | 类型 |
|------|------|
| &oDiameter | `CATICkeParm_var` |


### GetDepth

```cpp
virtual HRESULT GetDepth(CATICkeParm_var &oDepth) ;
```

| 参数 | 类型 |
|------|------|
| &oDepth | `CATICkeParm_var` |


### GetOrigin

```cpp
virtual HRESULT GetOrigin(double& oX, double& oY, double& oZ) ;
```

| 参数 | 类型 |
|------|------|
| oX | `double&` |
| oY | `double&` |
| oZ | `double&` |


### GetDirection

```cpp
virtual HRESULT GetDirection(double& oX, double& oY, double& oZ) ;
```

| 参数 | 类型 |
|------|------|
| oX | `double&` |
| oY | `double&` |
| oZ | `double&` |


### get_Parameter

```cpp
virtual HRESULT get_Parameter(const CATString &iParameterName, double &oParameter) ;
```

| 参数 | 类型 |
|------|------|
| &iParameterName | `const CATString` |
| &oParameter | `double` |


### get_Parameter

```cpp
virtual HRESULT get_Parameter(const CATString &iParameterName, int &oParameter) ;
```

| 参数 | 类型 |
|------|------|
| &iParameterName | `const CATString` |
| &oParameter | `int` |


---

**源文件**: `CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfForMfgHole.h`
