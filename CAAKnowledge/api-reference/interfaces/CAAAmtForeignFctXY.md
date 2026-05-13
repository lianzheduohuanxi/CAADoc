---
title: "CAAAmtForeignFctXY"
type: "PublicInterface"
module: "CAAAdvancedMathematics"
base: "CATMathFunctionXY"
method_count: 4
source_file: "CAAAdvancedMathematics.edu/PublicInterfaces/CAAAmtForeignFctXY.h"
---

# CAAAmtForeignFctXY

**基类**: CATMathFunctionXY | **模块**: CAAAdvancedMathematics | **方法数**: 4

## 依赖

- `CAAAmtForeignFct.h`
- `CATMathFunctionXY.h`

## 公共方法

### IsAKindOf

```cpp
CATBoolean IsAKindOf(const CATMathClassId iClassId) const ;
```

| 参数 | 类型 |
|------|------|
| iClassId | `const CATMathClassId` |


### IsOption

```cpp
CATBoolean IsOption(const CATMathOption iOption) const ;
```

| 参数 | 类型 |
|------|------|
| iOption | `const CATMathOption` |


### Eval

```cpp
void Eval(const double iX, const double iY, const CATMathOption iOptions, double * ioF, double * ioFx =NULL, double * ioFy=NULL, double * ioFx2=NULL, double * ioFxy=NULL, double *ioFy2=NULL) const ;
```

| 参数 | 类型 |
|------|------|
| iX | `const double` |
| iY | `const double` |
| iOptions | `const CATMathOption` |
| ioF | `double *` |
| =NULL | `double * ioFx` |
| ioFy=NULL | `double *` |
| ioFx2=NULL | `double *` |
| ioFxy=NULL | `double *` |
| *ioFy2=NULL | `double` |


### Eval

```cpp
void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * iNbPoints, const CATMathOption iOptions, double * ioF, double * ioFx =NULL, double * ioFy=NULL, double * ioFx2=NULL, double * ioFxy=NULL, double *ioFy2=NULL) const ;
```

| 参数 | 类型 |
|------|------|
| iDomain | `const CATMathIntervalND &` |
| iNbPoints | `const CATLONG32 *` |
| iOptions | `const CATMathOption` |
| ioF | `double *` |
| =NULL | `double * ioFx` |
| ioFy=NULL | `double *` |
| ioFx2=NULL | `double *` |
| ioFxy=NULL | `double *` |
| *ioFy2=NULL | `double` |


---

**源文件**: `CAAAdvancedMathematics.edu/PublicInterfaces/CAAAmtForeignFctXY.h`
