---
title: "CAAAniSelectNodeCmd"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATStateCommand"
method_count: 3
source_file: "CAAAnalysisInterfaces.edu/CAAAniWB.m/LocalInterfaces/CAAAniSelectNodeCmd.h"
---

# CAAAniSelectNodeCmd

**基类**: CATStateCommand | **模块**: CAAAnalysisInterfaces | **方法数**: 3

## 依赖

- `CATStateCommand.h`
- `CATUnicodeString.h`
- `CATBoolean.h`

## 静态方法

### HighlightCustoNode

```cpp
static HRESULT HighlightCustoNode(CAT3DCustomRep *, CATBaseUnknown *, void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `CAT3DCustomRep` |
| * | `CATBaseUnknown` |
| * | `void` |


## 公共方法

### BuildGraph

```cpp
void BuildGraph() ;
```


### SelectNode

```cpp
CATBoolean SelectNode(void *data) ;
```

| 参数 | 类型 |
|------|------|
| *data | `void` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniWB.m/LocalInterfaces/CAAAniSelectNodeCmd.h`
