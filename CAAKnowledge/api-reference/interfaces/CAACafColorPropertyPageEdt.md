---
title: "CAACafColorPropertyPageEdt"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATEditor"
method_count: 4
source_file: "CAACATIAApplicationFrm.edu/CAACafEditColorProp.m/LocalInterfaces/CAACafColorPropertyPageEdt.h"
---

# CAACafColorPropertyPageEdt

> Class representing an Edit Properties Page Editor, and implementing the CATIEditProperties interface. See CATCafTexturePropertyPageEdt in CAACafEditTextureProp.m to have more detail about this class. Usage: Launch CATIA V5, click File/New, select CAAGeometry in the New dialog box. Create some elements (point, line, circle, ellipse, plane,...) Launch the Edit/Properties command and select any element: . The circle and the ellipse implement the Texture properties. . The line, the circle implement the Color properties. Inheritance: CATEditor          ( CATIAApplicationFrame Framework) CATImplementationAdapter ( ObjectModelerBase Framework) CATEventSubscriber      ( System Framework ) CATBaseUnknown          (System Framework). Main Methods : BuildEditor           -> Creates the property page ExtractFromSelection  -> Extracts from the CSO involved object in this page. GetEditorTitle        -> NLS title SetEditorSize         -> 1 (small) ,2(medium), 3(large) SetPropertyValue      -> Initializes the property page CommitModification    -> After OK/Apply, modifies extracted object CancelModification    -> After Cancel push button CloseWindowFromEditor -> When you leave this page for another

**基类**: CATEditor | **模块**: CAACATIAApplicationFrm | **方法数**: 4

## 依赖

- `CATEditor.h`
- `CATLISTV_CATBaseUnknown.h`

## 虚方法

### GetEditorTitle

```cpp
virtual CATUnicodeString GetEditorTitle() ;
```


### SetEditorSize

```cpp
virtual void SetEditorSize(int & oSize) ;
```

| 参数 | 类型 |
|------|------|
| oSize | `int &` |


### BuildEditor

```cpp
virtual void BuildEditor(CATEditorPage * iEditor) ;
```

| 参数 | 类型 |
|------|------|
| iEditor | `CATEditorPage *` |


### CloseWindowFromEditor

```cpp
virtual void CloseWindowFromEditor() ;
```


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafEditColorProp.m/LocalInterfaces/CAACafColorPropertyPageEdt.h`
