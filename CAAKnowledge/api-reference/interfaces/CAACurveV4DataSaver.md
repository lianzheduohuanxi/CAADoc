---
title: "CAACurveV4DataSaver"
type: "LocalClass"
module: "CAACATIAV4Interfaces"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAACATIAV4Interfaces.edu/CAAV4iEduSaveAsV4.m/LocalInterfaces/CAACurveV4DataSaver.h"
---

# CAACurveV4DataSaver

**基类**: CATBaseUnknown | **模块**: CAACATIAV4Interfaces | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### GetData

```cpp
HRESULT GetData(int & oV4Type, double * & oV4Block) ;
```

| 参数 | 类型 |
|------|------|
| oV4Type | `int &` |
| oV4Block | `double * &` |


### GetUserIntent

```cpp
HRESULT GetUserIntent(int & oIntent) ;
```

| 参数 | 类型 |
|------|------|
| oIntent | `int &` |


### GetSplineConstraintData

```cpp
HRESULT GetSplineConstraintData(int & oV4SplineType, int & oV4BlockLength, double * & oV4BlockData) ;
```

| 参数 | 类型 |
|------|------|
| oV4SplineType | `int &` |
| oV4BlockLength | `int &` |
| oV4BlockData | `double * &` |


---

**源文件**: `CAACATIAV4Interfaces.edu/CAAV4iEduSaveAsV4.m/LocalInterfaces/CAACurveV4DataSaver.h`
