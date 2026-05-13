---
```vbscript
title: "Creating a Front View in a new Drawing Document"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CATIA", "CAADriCreateView", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriCreateView.htmmd"
converted: "2026-05-11T17:31:51.042883"
```

---
## Generative Drafting

|
## Creating a Front View in a new Drawing Document

* * *

  This macro shows you how to create views in Drawing documents. It retrieves a part document, creates a _DrawingDocument_ and a front view of the part document.
---|---
This macro shows you how to create views in Drawing documents. It retrieves a part document, creates a _DrawingDocument_ and a front view of the part document.
  CAADriCreateView is launched in CATIA [1]. No open document is needed. [CAADriCreateView.CATScript](CAADriCreateViewSource.md) is located in the CAAScdDriUseCases module. [Execute macro](macros/CAADriCreateView.CATScript) (Windows only).
  CAADriCreateView includes four steps:

  1. Prolog
  2. Creating a New View in the Active Sheet
```vbscript
  3. Set its Parameters to Make it a Generative Front View
  4. Epilog
```

#### Prolog

|

      ...
```vbscript
        ' Open the Part document
```

```vbscript
```vbscript
        Dim oPartToDraw As PartDocument
```vbscript
```
```vbscript
        Set oPartToDraw = CATIA.Documents.Open(sDocPath & _
```
```

```

                 "/online/CAAScdDriUseCases/samples/Cube.CATPart")
```vbscript
```vbscript
```vbscript
        ' Create a drawing document: it becomes the active document.
```vbscript
        Dim oDrawing As DrawingDocument
        Set oDrawing = CATIA.Documents.Add("Drawing")
```
```

```

```

      ...

---

Open the part document to draw and create a new _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_. The part document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable.
#### Creating a New View in the Active Sheet

      ...
Open the part document to draw and create a new _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_. The part document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable.
```vbscript
```vbscript
      ' Retrieve the active sheet

```

```

```vbscript
```vbscript
        Dim oSheet As DrawingSheet
```vbscript
```
```vbscript
        Set oSheet = oDrawing.Sheets.ActiveSheet
```
```

```

```vbscript
```vbscript
```vbscript
        ' Create a view called "Front View" in this sheet
```vbscript
        Dim oFrontView As DrawingView
        Set oFrontView = oSheet.Views.Add("Front View")
```
```

```

```

      ...

---

The new [_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md) is created in the active _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md)_ that is found on the [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md) collection aggregated by the _DrawingDocument_ object.
```vbscript
#### Set its Parameters to Make it a Generative Front View

```

    ...
The new [_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md) is created in the active _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md)_ that is found on the [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md) collection aggregated by the _DrawingDocument_ object.
```vbscript
```vbscript
        ' Retrieve it generative behavior

```

```

```vbscript
```vbscript
        Dim oFrontViewGB As DrawingViewGenerativeBehavior
```vbscript
```
```vbscript
```vbscript
        Set oFrontViewGB = oFrontView.GenerativeBehavior
        ' Declare the part to draw in this front view
```
        oFrontViewGB.Document = oPartToDraw
        ' Define this view as a front view, with the XY plane (in oPartToDraw) as projection plane
```

```

        oFrontViewGB.DefineFrontView 1, 0, 0, 0, 1, 0
```vbscript
```vbscript
        ' Position the View in the Sheet
        oFrontView.x = 300
        oFrontView.y = 150
```

```

```

      ...

---

The generative behavior is provided by the _DrawingViewGenerativeBehavior_ object aggregated by the _DrawingView_. We need to define the document to draw by valuating the `Document` attribute of the generative behavior. We then define which projection plane in this document will be used to draw the front view (here XY) and then the position of this view in its parent _Sheet_.
#### Epilog

    ...
The generative behavior is provided by the _DrawingViewGenerativeBehavior_ object aggregated by the _DrawingView_. We need to define the document to draw by valuating the `Document` attribute of the generative behavior. We then define which projection plane in this document will be used to draw the front view (here XY) and then the position of this view in its parent _Sheet_.
```vbscript
       ' Update the view
```

        oFrontViewGB.Update

---

```vbscript
```vbscript
' Update the view
```

oFrontViewGB.Update
Update the now completely defined generative behavior.

```

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create generative views in a drawing document.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_ , [_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md), _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md), _DrawingViewGenerativeBehavior_
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
