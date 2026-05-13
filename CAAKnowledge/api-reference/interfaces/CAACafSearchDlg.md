---
title: "CAACafSearchDlg"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATDlgDialog"
method_count: 4
source_file: "CAACATIAApplicationFrm.edu/CAACafSearch.m/LocalInterfaces/CAACafSearchDlg.h"
---

# CAACafSearchDlg

> It is the dialog box associated with the CAACafSearchCmd class. It displays a list of query and a list of context. local Framework

**基类**: CATDlgDialog | **模块**: CAACATIAApplicationFrm | **方法数**: 4

## 依赖

- `CATDlgDialog.h`
- `CATIIniSearchContext.h`
- `CATListOfCATUnicodeString.h`
- `CATUnicodeString.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### SetResultQueryEditorText

```cpp
void SetResultQueryEditorText(CATUnicodeString iText) ;
```

| 参数 | 类型 |
|------|------|
| iText | `CATUnicodeString` |


### GetCurrentContext

```cpp
void GetCurrentContext(CATIIniSearchContext::Scope &oCurrentContext) ;
```

| 参数 | 类型 |
|------|------|
| &oCurrentContext | `CATIIniSearchContext::Scope` |


### GetCurrentCriterion

```cpp
void GetCurrentCriterion(int & oCurrentCriterion) ;
```

| 参数 | 类型 |
|------|------|
| oCurrentCriterion | `int &` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafSearch.m/LocalInterfaces/CAACafSearchDlg.h`
