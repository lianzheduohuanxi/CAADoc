---
title: "CAAMcaUdfLoftDlg"
type: "LocalClass"
module: "CAAMechanicalCommands"
base: "CATDlgDialog"
method_count: 5
source_file: "CAAMechanicalCommands.edu/CAAMcaUdfEdit.m/LocalInterfaces/CAAMcaUdfLoftDlg.h"
---

# CAAMcaUdfLoftDlg

> Dialog box to edit or create a user feature which contains two inputs: two points. This dialog box is used by the CAAMcaUdfLoftEditCreateCmd and contains for each input to valuate: a CATDlgSelectorList with one element It contains the alias name of the input. a CATDlgLabel The title of the label is the role of the input To indicate to the end user the current input to valuate, the linked CATDlgSelectorList is highlighted (selected)

**基类**: CATDlgDialog | **模块**: CAAMechanicalCommands | **方法数**: 5

## 依赖

- `CATDlgDialog.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### InitPointName

```cpp
void InitPointName(CATUnicodeString iName1, CATUnicodeString iName2) ;
```

| 参数 | 类型 |
|------|------|
| iName1 | `CATUnicodeString` |
| iName2 | `CATUnicodeString` |


### SetPointName

```cpp
void SetPointName(int iPointNumber, CATUnicodeString iName) ;
```

| 参数 | 类型 |
|------|------|
| iPointNumber | `int` |
| iName | `CATUnicodeString` |


### SetRole

```cpp
void SetRole(int iPointNumber, CATUnicodeString iName) ;
```

| 参数 | 类型 |
|------|------|
| iPointNumber | `int` |
| iName | `CATUnicodeString` |


### GetActiveEditorNumber

```cpp
int GetActiveEditorNumber() ;
```


---

**源文件**: `CAAMechanicalCommands.edu/CAAMcaUdfEdit.m/LocalInterfaces/CAAMcaUdfLoftDlg.h`
