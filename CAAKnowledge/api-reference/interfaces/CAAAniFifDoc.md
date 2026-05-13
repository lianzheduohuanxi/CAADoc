---
title: "CAAAniFifDoc"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniFifDoc.h"
---

# CAAAniFifDoc

**基类**: CATBaseUnknown | **模块**: CAAAnalysisInterfaces | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATIPersistent.h`

## 公共方法

### Dirty

```cpp
CATBoolean Dirty() ;
```


### Save

```cpp
void Save() ;
```


### SaveAs

```cpp
void SaveAs(char * storagePrintableName, CATBoolean readOnly) ;
```

| 参数 | 类型 |
|------|------|
| storagePrintableName | `char *` |
| readOnly | `CATBoolean` |


### Load

```cpp
void Load(char * storagePrintableName, CATBoolean readOnly) ;
```

| 参数 | 类型 |
|------|------|
| storagePrintableName | `char *` |
| readOnly | `CATBoolean` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniFifDoc.h`
