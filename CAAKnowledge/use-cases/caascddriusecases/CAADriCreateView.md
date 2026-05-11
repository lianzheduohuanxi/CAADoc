---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScdDriUseCases", "CAAScrBase", "CAAInfLauchMacro", "CAADriObjDrawingView", "CAAScdInfUseCases", "CAAScdDriTechArticles", "CAADriCreateViewSource", "CAADriCreateView", "CAADriObjDrawingSheet", "CAADriObjDrawingDocument", "CAAlink", "CAADriObjDrawingSheets", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriCreateView.htm"
converted: "2026-05-11T11:06:32.908092"
---

## Generative Drafting
 
 
## []Creating a Front View in a new Drawing Document
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create views in Drawing
 documents.
 
 

It retrieves a part document, creates a *DrawingDocument* and a
 front view of the part document.
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAADriCreateView is launched in CATIA [[1]].
 No open document is needed.
 

[CAADriCreateView.CATScript]
 is located in the CAAScdDriUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAADriCreateView includes four steps:
 

 
- [Prolog]
 
- [Creating a New View in the Active Sheet]
 
- [Set its Parameters to Make it a Generative Front
 View]
 
- [Epilog]
 
 
#### []Prolog
 
 
 
```
...
 
' Open the Part document
 
 
Dim
 oPartToDraw 
As
 PartDocument
 
Set
 oPartToDraw = CATIA.Documents.Open(sDocPath & _
 "\online\CAAScdDriUseCases\samples\Cube.CATPart")

 
' Create a drawing document: it becomes the active document.

 
Dim
 oDrawing 
As
 DrawingDocument
 
Set
 oDrawing = CATIA.Documents.Add("Drawing")
 ...
```

 
 
 
 

Open the part document to draw and create a new *[DrawingDocument]*.
 The part document is fetched in the documentation installation path, this
 path has already been stored in the `sDocPath` variable.
 
#### []Creating a New View in the Active Sheet
 
 
 
```
...
 
' Retrieve the active sheet

 
Dim
 oSheet 
As
 DrawingSheet
 
Set
 oSheet = oDrawing.Sheets.ActiveSheet

 
' Create a view called "Front View" in this sheet

 
Dim
 oFrontView 
As
 DrawingView
 
Set
 oFrontView = oSheet.Views.Add("Front View")
 ...
```

 
 
 
 

The new [*DrawingView*]
 is created in the active *[DrawingSheet]*
 that is found on the [*DrawingSheets*]
 collection aggregated by the *DrawingDocument* object.
 
#### []Set its Parameters to Make it a Generative Front
 View
 
 
 
```
...
 
' Retrieve it generative behavior

 
Dim
 oFrontViewGB 
As
 DrawingViewGenerativeBehavior
 
Set
 oFrontViewGB = oFrontView.GenerativeBehavior

 
' Declare the part to draw in this front view

 oFrontViewGB.Document = oPartToDraw

 
' Define this view as a front view, with the XY plane (in oPartToDraw) as projection plane 

 oFrontViewGB.DefineFrontView 1, 0, 0, 0, 1, 0

 
' Position the View in the Sheet

 oFrontView.x = 300
 oFrontView.y = 150
 ...
```

 
 
 
 

The generative behavior is provided by the [*DrawingViewGenerativeBehavior*]
 object aggregated by the *DrawingView*. We need to define the
 document to draw by valuating the `Document` attribute of the
 generative behavior. We then define which projection plane in this
 document will be used to draw the front view (here XY) and then the
 position of this view in its parent *Sheet*.
 
#### []Epilog
 
 
 
```
...
 
' Update the view

 oFrontViewGB.Update
```

 
 
 
 

Update the now completely defined generative behavior.
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create generative views in a drawing document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[DrawingDocument]*,
 [*DrawingView*],
 *[DrawingSheet],*
 [*DrawingSheets*],
 [*DrawingViewGenerativeBehavior*]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*