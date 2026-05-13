---
title: "CAAGobForeignSurfaceData"
type: "ProtectedInterface"
module: "CAAGeometricObjects"
base: "CATForeignSurfaceData"
method_count: 12
source_file: "CAAGeometricObjects.edu/ProtectedInterfaces/CAAGobForeignSurfaceData.h"
---

# CAAGobForeignSurfaceData

**基类**: CATForeignSurfaceData | **模块**: CAAGeometricObjects | **方法数**: 12

## 依赖

- `CAAGobForeign.h`
- `CATForeignSurfaceData.h`

## 公共方法

### Stream

```cpp
void Stream(CATCGMStream & iStr) const ;
```

| 参数 | 类型 |
|------|------|
| iStr | `CATCGMStream &` |


### UnStream

```cpp
void UnStream(CATCGMStream & iStr) ;
```

| 参数 | 类型 |
|------|------|
| iStr | `CATCGMStream &` |


### Move3D

```cpp
void Move3D(CATTransfoManager & iTransfo) ;
```

| 参数 | 类型 |
|------|------|
| iTransfo | `CATTransfoManager &` |


### SetLimits

```cpp
void SetLimits(const CATSurLimits & iNewLimits) ;
```

| 参数 | 类型 |
|------|------|
| iNewLimits | `const CATSurLimits &` |


### GetLimits

```cpp
void GetLimits(CATSurLimits & ioLimits) const ;
```

| 参数 | 类型 |
|------|------|
| ioLimits | `CATSurLimits &` |


### GetMaxLimits

```cpp
void GetMaxLimits(CATSurLimits & ioLimits) const ;
```

| 参数 | 类型 |
|------|------|
| ioLimits | `CATSurLimits &` |


### GetInternalMaxLimits

```cpp
void GetInternalMaxLimits(const CATLONG32 iPatchU, const CATLONG32 iPatchV, CATSurLimits & ioLimits) const ;
```

| 参数 | 类型 |
|------|------|
| iPatchU | `const CATLONG32` |
| iPatchV | `const CATLONG32` |
| ioLimits | `CATSurLimits &` |


### Extrapolate

```cpp
CATBoolean Extrapolate(const CATMathVector2D & iRequiredParamExtension, CATMathVector2D * ioActualExtension = NULL) ;
```

| 参数 | 类型 |
|------|------|
| iRequiredParamExtension | `const CATMathVector2D &` |
| NULL | `CATMathVector2D * ioActualExtension =` |


### CreateLocalEquation

```cpp
void CreateLocalEquation(const CATLONG32 iPatchU, const CATLONG32 iPatchV, const CATMathFunctionXY* & oFx, const CATMathFunctionXY* & oFy, const CATMathFunctionXY* & oFz) ;
```

| 参数 | 类型 |
|------|------|
| iPatchU | `const CATLONG32` |
| iPatchV | `const CATLONG32` |
| oFx | `const CATMathFunctionXY* &` |
| oFy | `const CATMathFunctionXY* &` |
| oFz | `const CATMathFunctionXY* &` |


### IsConfused

```cpp
CATBoolean IsConfused(const CATMathTransformation & iTransfo, const CATSurface * iTSurface, CATMathTransformation2D * ioTransfo2D = NULL) const ;
```

| 参数 | 类型 |
|------|------|
| iTransfo | `const CATMathTransformation &` |
| iTSurface | `const CATSurface *` |
| NULL | `CATMathTransformation2D * ioTransfo2D =` |


### IsPeriodicU

```cpp
CATBoolean IsPeriodicU() const ;
```


### IsPeriodicV

```cpp
CATBoolean IsPeriodicV() const ;
```


---

**源文件**: `CAAGeometricObjects.edu/ProtectedInterfaces/CAAGobForeignSurfaceData.h`
