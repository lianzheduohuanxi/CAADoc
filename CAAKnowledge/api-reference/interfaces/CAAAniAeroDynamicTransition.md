---
title: "CAAAniAeroDynamicTransition"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniAeroDynamicTransition.h"
---

# CAAAniAeroDynamicTransition

**基类**: CATBaseUnknown | **模块**: CAAAnalysisInterfaces | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

## 公共方法

### ExecuteTransition

```cpp
HRESULT ExecuteTransition(const CATDocument* iDocument) ;
```

| 参数 | 类型 |
|------|------|
| iDocument | `const CATDocument*` |


### SetAlias

```cpp
void SetAlias(const CATUnicodeString& iName) ;
```

| 参数 | 类型 |
|------|------|
| iName | `const CATUnicodeString&` |


### GetAlias

```cpp
CATUnicodeString GetAlias() ;
```


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniAeroDynamicTransition.h`
