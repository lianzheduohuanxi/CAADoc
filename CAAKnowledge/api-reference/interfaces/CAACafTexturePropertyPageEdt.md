---
title: "CAACafTexturePropertyPageEdt"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATEditor"
method_count: 4
source_file: "CAACATIAApplicationFrm.edu/CAACafEditTextureProp.m/LocalInterfaces/CAACafTexturePropertyPageEdt.h"
---

# CAACafTexturePropertyPageEdt

> Class representing an Edit Properties Page Editor, and implementing the CATIEditProperties interface. Usage: Launch CATIA V5, click File/New, select CAAGeometry in the New dialog box. Create some elements (point, line, circle, ellipse, plane,...) Launch the Edit/Properties command and select any element: . The circle and the ellipse implement the Texture properties. . The line, the circle implement the Color properties. Inheritance: CATEditor          ( CATIAApplicationFrame Framework) CATImplementationAdapter ( ObjectModelerBase Framework) CATEventSubscriber      ( System Framework ) CATBaseUnknown          (System Framework). Main Methods : BuildEditor           -> Creates the property page ExtractFromSelection  -> Extracts from the CSO involved object in this page. GetEditorTitle        -> NLS title SetEditorSize         -> 1 (small) ,2(medium), 3(large) SetPropertyValue      -> Initializes the property page CommitModification    -> After OK/Apply, modifies extracted object CancelModification    -> After Cancel push button CloseWindowFromEditor -> When you leave this page for another

**基类**: CATEditor | **模块**: CAACATIAApplicationFrm | **方法数**: 4

## 依赖

- `CATEditor.h`
- `CATLISTV_CATBaseUnknown.h`

## 虚方法

### GetEditorTitle

```cpp
virtual CATUnicodeString GetEditorTitle() ;
```

GetEditorTitle --------------- Returns the NLS title of the page. In the NLS file associated with the CAACafTexturePropertyPageDlg class you can customize it. This method is called if the extraction is not empty.


### SetEditorSize

```cpp
virtual void SetEditorSize(int & oSize) ;
```

SetEditorSize --------------- Returns the size of the page. This method is called if the extraction is not empty. oSize can take the following values: 1 : small size 2 : medium size 3 : large size The Properties command analyzes the size returned by all Property pages and creates a box from the largest one.

| 参数 | 类型 |
|------|------|
| oSize | `int &` |


### BuildEditor

```cpp
virtual void BuildEditor(CATEditorPage * iEditor) ;
```

BuildEditor ------------ Creates the page Dialog (_pTextureFrame). This method is called at the first selection of the page. When the end user swaps between pages, this method is not called. iEditor is the parent of _pTextureFrame. It kills _pTextureFrame when the dialog box is closed.

| 参数 | 类型 |
|------|------|
| iEditor | `CATEditorPage *` |


### CloseWindowFromEditor

```cpp
virtual void CloseWindowFromEditor() ;
```

CloseWindowFromEditor() ----------------------- This method is called when the end user swaps between pages, but not when the Edit Properties Dialog box is closed.


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafEditTextureProp.m/LocalInterfaces/CAACafTexturePropertyPageEdt.h`
