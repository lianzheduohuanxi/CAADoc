---
```vbscript
title: "Duplicating a Drawing View"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriDuplicateAView", "CATIA", "CAADriUseCases", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDuplicateAView.htm"
converted: "2026-05-11T17:31:51.071818"
```

---
|
## Interactive Drafting

|
## Duplicating a Drawing View

* * *

 This macro shows you how to copy a view in drawing document and paste it into another drawing document. The copied view has been generated from a part document but isolated, so the pasted view is also isolated. This macro open the drawing document containing the view to be copied and create a new drawing document containing the view to be pasted.
---|---
This macro shows you how to copy a view in drawing document and paste it into another drawing document. The copied view has been generated from a part document but isolated, so the pasted view is also isolated. This macro open the drawing document containing the view to be copied and create a new drawing document containing the view to be pasted.
 CAADriDuplicateAView is launched in CATIA [1]. No open document is needed. [CAADriDuplicateAView](CAADriDuplicateAViewSource.md) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriDuplicateAView.CATScript) (Wndows only).
 CAADriDuplicateAView includes seven steps:

  1. Prolog
  2. Opening and Reframing an Existing Drawing Document
  3. Retrieving and Defining the Sheet
  4. Retrieving and Defining the View
  5. Copying the View
  6. Creating the New Drawing Document
  7. Pasting the View

#### Prolog

|

      ...
```vbscript
        ' Set the CATIA popup file alerts to False
```

```vbscript
```vbscript
```vbscript
' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
```

```

```

```vbscript
        CATIA.DisplayFileAlerts = False
```

      ...

---

The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
#### Opening and Reframing an Existing Drawing Document

      ...
The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
```vbscript
```vbscript
        ' Open the Drawing document

```

```

```vbscript
        Dim oDrawingSource As DrawingDocument
```vbscript
        Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
```

```

                 "\online\CAAScdDriUseCases\samples\CAADriDuplicateAView.CATDrawing")
```vbscript
```vbscript
```vbscript
' Open the Drawing document
Dim oDrawingSource As DrawingDocument
Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
        ' Fit in window the opened document
        CATIA.ActiveWindow.ActiveViewer.Reframe
```

```

```

      ...

---

A drawing document is opened, its window is reframed according to the size of the sheet.
#### Retrieving and Defining the Sheet

      ...
A drawing document is opened, its window is reframed according to the size of the sheet.
```vbscript
```vbscript
        ' Retrieve the sheet containing the view to be duplicated

```

```

```vbscript
        Dim oSheetSource As DrawingSheet
```vbscript
        Set oSheetSource = oDrawingSource.Sheets.Item("Sheet.1")
```

```

      ...

---

The sheets collection is retrieved from the `oDrawingSource` object using the `Sheets` method.
The sheet object is retrieved from the collection using the `Item` method from its name.
#### Retrieving and Defining the View

      ...
The sheet object is retrieved from the collection using the `Item` method from its name.
```vbscript
```vbscript
        ' Retrieve the view to be duplicated

```

```

```vbscript
        Dim oViewSource As DrawingView
```vbscript
        Set oViewSource = oSheetSource.Views.Item("Front view")
```

```

      ...

---

The views collection is retrieved from the `oSheetSource` object using the `Views` method.
The view object is retrieved from the collection using the `Item` method from its name.
#### Copying the View

      ...
The view object is retrieved from the collection using the `Item` method from its name.
```vbscript
```vbscript
        ' Create an object of selection for the source document

```

```

```vbscript
        Dim oSelectionSource As Selection
```vbscript
```vbscript
        Set oSelectionSource = oDrawingSource.Selection
        ' Clear the selection
```

```

        oSelectionSource.Clear
```vbscript
        ' Add the view to be duplicated in the selection
```

        oSelectionSource.Add oViewSource
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
The view object is added to the selection object using the `Add` method.
The view object is copied to the clipboard from the selection object using the `Copy` method.
The selection object is cleared using the `Clear` method another time.

#### Creating the New Drawing Document

      ...
The selection object is cleared using the `Clear` method another time.
```vbscript
```vbscript
        ' Create the Drawing document where the view will be pasted

```

```

```vbscript
        Dim oDrawingTarget As DrawingDocument
```vbscript
        Set oDrawingTarget = CATIA.Documents.Add("Drawing")
```

```

```vbscript
```vbscript
```vbscript
        ' Retrieve the where the view will be pasted
        Dim oSheetTarget As DrawingSheet
        Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
        ' Set the sheet paper size
```

```

```

```vbscript
Dim oSheetTarget As DrawingSheet
```vbscript
```vbscript
Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
' Set the sheet paper size
        oSheetTarget.PaperSize = catPaperA0
```

```

```

      ...

---

A new drawing document is created and the sheet object is retrieved, the size of its sheet is set to A0.
#### Pasting the View

      ...
A new drawing document is created and the sheet object is retrieved, the size of its sheet is set to A0.
```vbscript
```vbscript
        ' Create an object of selection for the source document

```

```

```vbscript
        Dim oSelectionTarget As Selection
```vbscript
```vbscript
        Set oSelectionTarget = oDrawingTarget.Selection
        ' Clear the selection
```

```

        oSelectionTarget.Clear
```vbscript
        ' Add the sheet where the view will be pasted in the selection
```

        oSelectionTarget.Add oSheetTarget
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

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to copy/paste a Drawing view using the _Copy_ and _Paste_ methods of the _Selection_ object.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md) _,_[_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md)
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
