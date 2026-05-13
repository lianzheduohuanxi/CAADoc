---
title: "CAACafSearchCmd"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATStateCommand"
method_count: 3
source_file: "CAACATIAApplicationFrm.edu/CAACafSearch.m/LocalInterfaces/CAACafSearchCmd.h"
---

# CAACafSearchCmd

> State command which creates some queries and displayes a dialog box to choose a criterion and a context and enables the end user to launch the query. Illustrates: Creation of a State command Use of a Search AI Use of a CATPanelState Usage: Select a criterion and a context in the dialog box and then launch the query.

**基类**: CATStateCommand | **模块**: CAACATIAApplicationFrm | **方法数**: 3

## 依赖

- `CATStateCommand.h`
- `CATListOfCATUnicodeString.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode


## 公共方法

### LaunchQuery

```cpp
CATBoolean LaunchQuery(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


### GetCriteriaText

```cpp
HRESULT GetCriteriaText(CATListOfCATUnicodeString ** oCriteriaTextList) ;
```

GetCriteriaText -------------- This method is called by the dialog box to retrieve the text of each criterion to display in the combo.

| 参数 | 类型 |
|------|------|
| oCriteriaTextList | `CATListOfCATUnicodeString **` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafSearch.m/LocalInterfaces/CAACafSearchCmd.h`
