---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScdDriUseCases", "CAAScrBase", "CAADriDuplicateAViewSource", "CAAInfLauchMacro", "CAADriObjDrawingView", "CAAScdInfUseCases", "CAAScdDriTechArticles", "CAADriDuplicateAView", "CAADriObjDrawingSheet", "CAADriObjDrawingDocument", "CAADriUseCases", "CAADriObjDrawingSheets", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDuplicateAView.htm"
converted: "2026-05-11T11:06:32.898822"
---

## Interactive Drafting
 
 
## []Duplicating a Drawing View
 
 

---

 

 
 |![](../CAAScrBase/images/atarget.gif)
 |This macro shows you how to copy a view in drawing document and paste it
 into another drawing document. The copied view has been generated from a
 part document but isolated, so the pasted view is also isolated. This
 macro open the drawing document containing the view to be copied and
 create a new drawing document containing the view to be pasted.
 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 |[]CAADriDuplicateAView is launched in CATIA [[1]].
 No open document is needed.
 

[CAADriDuplicateAView] is
 located in the CAADriUseCases module.  [Execute
 macro] (Wndows only).
 

 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 |[]CAADriDuplicateAView includes seven steps:
 

 
- [Prolog]
 
- [Opening and Reframing an Existing Drawing Document]
 
- [Retrieving and Defining the Sheet]
 
- [Retrieving and Defining the View]
 
- [Copying the View]
 
- [Creating the New Drawing Document]
 
- [Pasting the View]
 
 
#### []Prolog
 
 
 
```
...
 
' Set the CATIA popup file alerts to False

 
' It prevents to stop the macro at each alert during its execution

 CATIA.DisplayFileAlerts = False
 ...
```

 
 
 
 

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
 property of the *Application* object set to `False`.
 
#### []Opening and Reframing an Existing Drawing Document
 
 
 
```
...
 
' Open the Drawing document

 Dim 
oDrawingSource
 As 
DrawingDocument

 Set 
oDrawingSource = CATIA.Documents.Open(sDocPath & _
 "\online\CAAScdDriUseCases\samples\CAADriDuplicateAView.CATDrawing")
 
 
' Fit in window the opened document

 CATIA.ActiveWindow.ActiveViewer.Reframe
 ...
```

 
 
 
 

A drawing document is opened, its window is reframed according to the
 size of the sheet.
 
#### []Retrieving and Defining the Sheet
 
 
 
```
...
 
' Retrieve the sheet containing the view to be duplicated

 Dim 
oSheetSource
 As 
DrawingSheet

 Set 
oSheetSource = oDrawingSource.Sheets.Item("Sheet.1")
 ...
```

 
 
 
 

The sheets collection is retrieved from the `oDrawingSource`
 object using the `Sheets` method.

 The sheet object is retrieved from the collection using the `Item`
 method from its name.
 
#### []Retrieving and Defining the View
 
 
 
```
...
 
' Retrieve the view to be duplicated

 Dim 
oViewSource
 As 
DrawingView

 Set 
oViewSource = oSheetSource.Views.Item("Front view")
 ...
```

 
 
 
 

The views collection is retrieved from the `oSheetSource`
 object using the `Views` method.

 The view object is retrieved from the collection using the `Item`
 method from its name.
 
#### []Copying the View
 
 
 
```
...
 
' Create an object of selection for the source document

 Dim 
oSelectionSource
 As 
Selection

 Set 
oSelectionSource = oDrawingSource.Selection
 
 
' Clear the selection

 oSelectionSource.Clear
 
' Add the view to be duplicated in the selection

 oSelectionSource.Add oViewSource
 
' Copy the view

 oSelectionSource.Copy
 
' Clear the selection

 oSelectionSource.Clear
 ...
```

 
 
 
 

The selection object is retrieved from the `oDrawingSource`
 object using the `Selection` method.

 The selection object is cleared using the `Clear` method to
 remove pre-selecting objects if exist.

 The view object is added to the selection object using the `Add`
 method.

 The view object is copied to the clipboard from the selection object using
 the `Copy` method.

 The selection object is cleared using the `Clear` method
 another time.
 
#### []Creating the New Drawing Document
 
 
 
```
...
 
' Create the Drawing document where the view will be pasted

 Dim 
oDrawingTarget
 As 
DrawingDocument

 Set 
oDrawingTarget = CATIA.Documents.Add("Drawing")
 
 
' Retrieve the where the view will be pasted

 Dim 
oSheetTarget
 As 
DrawingSheet

 Set 
oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
 
 
' Set the sheet paper size

 oSheetTarget.PaperSize = catPaperA0
 ...
```

 
 
 
 

A new drawing document is created and the sheet object is retrieved,
 the size of its sheet is set to A0.
 
#### []Pasting the View
 
 
 
```
...
 
' Create an object of selection for the source document

 Dim 
oSelectionTarget
 As 
Selection

 Set 
oSelectionTarget = oDrawingTarget.Selection
 
 
' Clear the selection

 oSelectionTarget.Clear
 
' Add the sheet where the view will be pasted in the selection

 oSelectionTarget.Add oSheetTarget
 
' Paste the clipboard

 oSelectionTarget.Paste
 
' Clear the selection

 oSelectionTarget.Clear
 ...
```

 
 
 
 

The selection object is retrieved from the `oDrawingTarget`
 object using the `Selection` method.

 The selection object is cleared using the `Clear` method to
 remove pre-selecting objects if exist.

 The sheet object is added to the selection object using the `Add`
 method.

 The view is pasted from the clipboard into the sheet from the selection
 object using the `Paste` method.

 The selection object is cleared using the `Clear` method
 another time.
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to copy/paste a Drawing view using the *Copy *and*
Paste* methods of the *Selection* object.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[DrawingDocument]*,
 *[DrawingSheet],*
 [*DrawingSheets*]*,
 *[*DrawingView*]
 
 
 |[[Top]]
 

---

*Copyright 2003, Dassault Systmes. All rights reserved.*