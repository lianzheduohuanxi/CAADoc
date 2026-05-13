---
title: "CAAEMaiToolEditionCustomizationDrillTool"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAManufacturingItf.edu/CAAMaiToolEditionCustomization.m/LocalInterfaces/CAAEMaiToolEditionCustomizationDrillTool.h"
---

# CAAEMaiToolEditionCustomizationDrillTool

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 5

## 依赖

- `CATDlgInclude.h`
- `CATBooleanDef.h`
- `CATListOfCATUnicodeString.h`
- `CATISpecObject.h`

## 虚方法

### GetPanelEditor

```cpp
virtual CATDlgFrame* GetPanelEditor(CATDialog *iParent, CATDlgStyle iStyle=CATDlgFraNoFrame, const CATBoolean iEditMode=TRUE) ;
```

This method allows to get the Tool editor view that will be displayed when editing the tool through ResourceList access (simple view)

| 参数 | 类型 |
|------|------|
| *iParent | `CATDialog` |
| iStyle=CATDlgFraNoFrame | `CATDlgStyle` |
| iEditMode=TRUE | `const CATBoolean` |


### GetMorePanelEditor

```cpp
virtual CATDlgFrame* GetMorePanelEditor(CATDialog *iParent, CATDlgStyle iStyle=CATDlgFraNoFrame, const CATBoolean iEditMode=TRUE) ;
```

This method allows to get the Tool editor view that will be displayed when editing the tool through ResourceList access with selection of the button "more" (advanced view)

| 参数 | 类型 |
|------|------|
| *iParent | `CATDialog` |
| iStyle=CATDlgFraNoFrame | `CATDlgStyle` |
| iEditMode=TRUE | `const CATBoolean` |


### GetActivityEditor

```cpp
virtual CATDlgFrame* GetActivityEditor(CATDialog *iParent, CATDlgStyle iStyle=CATDlgFraNoFrame, const CATBoolean iEditMode=FALSE, const CATISpecObject_var &ihSpecAct=NULL_var) ;
```

This method allows to get the Tool editor view that will be displayed when editing the tool with access through the Activity editor (tool tab page)

| 参数 | 类型 |
|------|------|
| *iParent | `CATDialog` |
| iStyle=CATDlgFraNoFrame | `CATDlgStyle` |
| iEditMode=FALSE | `const CATBoolean` |
| &ihSpecAct=NULL_var | `const CATISpecObject_var` |


### GetGraphicEditor

```cpp
virtual CATDlgFrame* GetGraphicEditor(CATDialog *iParent, CATDlgStyle iStyle=CATDlgFraNoFrame, const CATBoolean iEditMode=FALSE) ;
```

This method allows to get the Tool graphic view That can be an icon (at least displayed during Tool selection)

| 参数 | 类型 |
|------|------|
| *iParent | `CATDialog` |
| iStyle=CATDlgFraNoFrame | `CATDlgStyle` |
| iEditMode=FALSE | `const CATBoolean` |


### GenerateJPEGImageFromGraphicEditor

```cpp
virtual void GenerateJPEGImageFromGraphicEditor(CATDialog *iParent, const CATUnicodeString &iImagePathName="") ;
```

Not used (for future use)

| 参数 | 类型 |
|------|------|
| *iParent | `CATDialog` |
| &iImagePathName="" | `const CATUnicodeString` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiToolEditionCustomization.m/LocalInterfaces/CAAEMaiToolEditionCustomizationDrillTool.h`
