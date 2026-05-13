---
title: "CAAMaiMachiningProcessLog"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATIMfgMachiningProcessLog"
method_count: 3
source_file: "CAAManufacturingItf.edu/CAAMaiMachiningProcessInstantiationLog.m/LocalInterfaces/CAAMaiMachiningProcessLog.h"
---

# CAAMaiMachiningProcessLog

**基类**: CATIMfgMachiningProcessLog | **模块**: CAAManufacturingItf | **方法数**: 3

## 依赖

- `CATIMfgMachiningProcessLog.h`

## 公共方法

### Activate

```cpp
HRESULT Activate(CATBoolean iActive) ;
```

| 参数 | 类型 |
|------|------|
| iActive | `CATBoolean` |


### IsActive

```cpp
HRESULT IsActive(CATBoolean& oActive) ;
```

| 参数 | 类型 |
|------|------|
| oActive | `CATBoolean&` |


### Trace

```cpp
HRESULT Trace(int iContext, const CATListOfCATUnicodeString& iTraces) ;
```

| 参数 | 类型 |
|------|------|
| iContext | `int` |
| iTraces | `const CATListOfCATUnicodeString&` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiMachiningProcessInstantiationLog.m/LocalInterfaces/CAAMaiMachiningProcessLog.h`
