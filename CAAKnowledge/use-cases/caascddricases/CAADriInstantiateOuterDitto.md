---
title: "Instantiating a Ditto in a Drawing View from Another Drawing Document"
category: "use-case"
module: "CAAScdDriUseCases"
tags: "["CAADriScriptUseCases", "CAADriInstantiateOuterDitto", "CAADriInstantiateDittoTarget", "CAADriInstantiateDittoSource", "CATIA", "CAADriUseCases", "CAAScdDriUseCases"]"
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateOuterDitto.htm"
converted: "2026-05-11T17:31:51.089278"
---
## Interactive Drafting

|
## Instantiating a Ditto in a Drawing View from Another Drawing Document

* * *

 This macro shows you how to instantiate a ditto into a view from an existing ditto in another drawing document, offers to user to define the ditto location and defines the ditto's modifiable text value. This macro open the drawing document source containing the ditto and the drawing document target an the detail view. To instantiate the ditto we use the copy/paste mechanism because it is not possible interactively or using automation to create a ditto from a detail view in another document.
---|---
This macro shows you how to instantiate a ditto into a view from an existing ditto in another drawing document, offers to user to define the ditto location and defines the ditto's modifiable text value. This macro open the drawing document source containing the ditto and the drawing document target an the detail view. To instantiate the ditto we use the copy/paste mechanism because it is not possible interactively or using automation to create a ditto from a detail view in another document.
  CAADriInstantiateOuterDitto is launched in CATIA [1]. No open document is needed. [CAADriInstantiateOuterDitto](CAADriInstantiateOuterDittoSource.md) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriInstantiateOuterDitto.CATScript) (Windows only).
 CAADriInstantiateOuterDitto includes nine steps:

  1. Prolog
  2. Opening the Drawing Document Source
  3. Retrieving and Defining the Ditto
  4. Copying the Ditto
  5. Opening the Drawing Document Target
  6. Retrieving and Defining the View
  7. Defining the Ditto's Location
  8. Pasting the Ditto
  9. Retrieving the Instantiated Ditto and Defining its Location
  10. Retrieving the Ditto's Modifiable Text

#### Prolog

|

      ...
```vbscript
```cpp
        ' Set the CATIA popup file alerts to False
```
```

```vbscript
```vbscript
```vbscript
```cpp
' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
```
```

```

```

```vbscript
```cpp
        CATIA.DisplayFileAlerts = False
```
```

      ...

---

The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
#### Opening the Drawing Document Source

      ...
The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
```vbscript
```vbscript
        ' Open the drawing document containing the existing ditto

```

```

```vbscript
```vbscript
        Dim oDrawingSource As DrawingDocument
```vbscript
```
```cpp
        Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
```
```

```

                 "/online/CAAScdDriUseCases/samples/CAADriInstantiateDittoSource.CATDrawing")
      ...

---

A drawing document is opened.
#### Retrieving and Defining the Ditto

      ...
A drawing document is opened.
```vbscript
```vbscript
        ' Retrieve the sheet containing the ditto to be copied

```

```

```vbscript
```vbscript
        Dim oSheetSource As DrawingSheet
```vbscript
```
```vbscript
        Set oSheetSource = oDrawingSource.Sheets.Item("Sheet.3")
```
```

```

```vbscript
```vbscript
```vbscript
        ' Retrieve the view containing the ditto to be copied
```vbscript
        Dim oViewSource As DrawingView
        Set oViewSource = oSheetSource.Views.Item("View.1")
        ' Retrieve the ditto
```
```vbscript
        Dim oDitto As DrawingComponent
        Set oDitto = oViewSource.Components.Item(1)
```
```

```

```

      ...

---

The sheets collection is retrieved from the `oDrawingSource` object using the `Sheets` method.
The sheet object is retrieved from the collection using the `Item` method from its name.
The views collection is retrieved from the `oSheetSource` object using the `Views` method.
The view object is retrieved from the collection using the `Item` method from its name.
The components collection is retrieved from the `oViewSource` object using the `Components` method.
The component object is retrieved from the collection using the `Item` method from its index.

#### Copying the Ditto

      ...
The component object is retrieved from the collection using the `Item` method from its index.
```vbscript
```vbscript
        ' Create an object of selection for the source document

```

```

```vbscript
```vbscript
        Dim oSelectionSource As Selection
```vbscript
```
```vbscript
```vbscript
        Set oSelectionSource = oDrawingSource.Selection
        ' Clear the selection
```
```

```

        oSelectionSource.Clear
```vbscript
        ' Add the ditto to be duplicated in the selection
```

        oSelectionSource.Add oDitto
```vbscript
        ' Copy the view
```

        oSelectionSource.Copy
```vbscript
        ' Clear the selection
```

        oSelectionSource.Clear
```

      ...

---

The selection object is retrieved from the `oDrawingSource` object using the `Selection` method.
The selection object is cleared using the `Clear` method to remove pre-selecting objects if exist.
The component object is added to the selection object using the `Add` method.
The view object is copied to the clipboard from the selection object using the `Copy` method.
The selection object is cleared using the `Clear` method another time.

#### Opening the Drawing Document Target

      ...
The selection object is cleared using the `Clear` method another time.
```vbscript
```vbscript
        ' Open the drawing document where the ditto will be instantiated

```

```

```vbscript
```vbscript
        Dim oDrawingTarget As DrawingDocument
```vbscript
```
```cpp
        Set oDrawingTarget = CATIA.Documents.Open(sDocPath & _
```
```

```

                 "/online/CAADriScriptUseCases/samples/CAADriInstantiateDittoTarget.CATDrawing")
```vbscript
```vbscript
```vbscript
' Open the drawing document where the ditto will be instantiated
```cpp
Dim oDrawingTarget As DrawingDocument
Set oDrawingTarget = CATIA.Documents.Open(sDocPath & _
        CATIA.ActiveWindow.ActiveViewer.Reframe
```
```

```

```

      ...

---

A drawing document is opened, its window is reframed according to the size of the sheet.
#### Retrieving and Defining the View

      ...
A drawing document is opened, its window is reframed according to the size of the sheet.
```vbscript
```vbscript
        ' Retrieve the sheet where the ditto will be instantiated

```

```

```vbscript
```vbscript
        Dim oSheetTarget As DrawingSheet
```vbscript
```
```vbscript
        Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
```
```

        oSheetTarget.Activate
```

```vbscript
```vbscript
```vbscript
        ' Retrieve the view where the ditto will be instantiated
```vbscript
        Dim oViewTarget As DrawingView
        Set oViewTarget = oSheetTarget.Views.Item("View.3")
```
```

```

```

      ...

---

The sheets collection is retrieved from the `oDrawingTarget` object using the `Sheets` method.
The sheet object is retrieved from the collection using the `Item` method from its name.
The views collection is retrieved from the `oSheetTarget` object using the `Views` method.
The view object is retrieved from the collection using the `Item` method from its name.
The sheet is activated.

#### Defining the Ditto's Location

The views collection is retrieved from the `oSheetTarget` object using the `Views` method.
The view object is retrieved from the collection using the `Item` method from its name.
The sheet is activated.
The ditto's location is retrieved using the `Indicate2D` method which allow user to retrieve the `x` and `y` coordinates when clicking the mouse. Coordinates are stored  in an array `iDittoCoordinates`. An unspecified object `oDraw` is used to prevent a signature's method restriction usage.

![](images/img018.gif)
#### Pasting the Ditto

      ...
```vbscript
        ' Create an object of selection for the target document
```

```vbscript
```vbscript
        Dim oSelectionTarget As Selection
```vbscript
```
```vbscript
```vbscript
        Set oSelectionTarget = oDrawingTarget.Selection
        ' Clear the selection
```
```

```

        oSelectionTarget.Clear
```vbscript
        ' Add the view in the selection, where the ditto will be instantiated
```

        oSelectionTarget.Add oViewTarget
```vbscript
        ' Paste the clipboard
```

        oSelectionTarget.Paste
```vbscript
        ' Clear the selection
```

        oSelectionTarget.Clear
```

      ...

---

The selection object is retrieved from the `oDrawingTarget` object using the `Selection` method.
The selection object is cleared using the `Clear` method to remove pre-selecting objects if exist.
The sheet object is added to the selection object using the `Add` method.
The view is pasted from the clipboard into the sheet from the selection object using the `Paste` method.
The selection object is cleared using the `Clear` method another time.

#### Retrieving the Instantiated Ditto and Defining its Location

      ...
The selection object is cleared using the `Clear` method another time.
```vbscript
```vbscript
        ' Retrieve the drawing components collection of the target drawing view

```

```

```vbscript
```vbscript
        Dim o2DComponents As DrawingComponents
```vbscript
```
```vbscript
        Set o2DComponents = oViewTarget.Components
```
```

```

```vbscript
```vbscript
```vbscript
        ' Retrieve the ditto and define its location
```vbscript
        Dim o2DComponent As DrawingComponent
        Set o2DComponent = o2DComponents.Item("DrwDetail.1")
```
```

```

```

```vbscript
```vbscript
```vbscript
' Retrieve the ditto and define its location
```vbscript
Dim o2DComponent As DrawingComponent
Set o2DComponent = o2DComponents.Item("DrwDetail.1")
        o2DComponent.X = iDittoCoordinates(0)
```
        o2DComponent.Y = iDittoCoordinates(1)
```

```

```

      ...

---

![](images/img019.gif)
#### Retrieving the Ditto's Modifiable Text

      ...
```vbscript
        ' Retrieve the modifiable text of the ditto
```

```vbscript
```vbscript
        Dim oText As DrawingText
```vbscript
```
```vbscript
        Set oText = o2DComponent.GetModifiableObject(1)
```
```

```

```vbscript
```vbscript
```vbscript
        ' Modify the modifiable text value
```vbscript
        Dim ReturnValue As String
        ReturnValue = InputBox("Enter a value", "", "New Value For Text")
```
```

```

```

```vbscript
```vbscript
```vbscript
' Modify the modifiable text value
```vbscript
Dim ReturnValue As String
```
```

```

```

ReturnValue = InputBox("Enter a value", "", "New Value For Text")
```vbscript
```vbscript
        oText.Text = ReturnValue

```

```

      ...

---

The text object is retrieved from the `o2DComponent` object using the `GetModifiableObject` method.
The text of the text object is returned using the `InputBox` procedure. Enter 10 and click OK.

![](images/img016.gif)

![](images/img020.gif)

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to instantiate a drawing detail view as a ditto in a view using the _Add_ method of the _Components_ object.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md) _,_[_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md)
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
