---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScdDriUseCases", "CAAScrBase", "CAAInfLauchMacro", "CAADriScriptUseCases", "CAADriObjDrawingView", "CAADriInstantiateDittoTarget", "CAAScdInfUseCases", "CAAScdDriTechArticles", "CAADriObjDrawingSheet", "CAADriInstantiateOuterDittoSource", "CAADriObjDrawingDocument", "CAADriInstantiateOuterDitto", "CAADriInstantiateDittoSource", "CAADriUseCases", "CAADriObjDrawingSheets", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateOuterDitto.htm"
converted: "2026-05-11T11:06:32.935108"
---

## Interactive Drafting
 
 
## []Instantiating a Ditto in a Drawing View from Another
 Drawing Document
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 |This macro shows you how to instantiate a ditto into a view
 from an existing ditto in another drawing document, offers to user to
 define the ditto location and defines the ditto's modifiable text value.
 This macro open the drawing document source containing the ditto and the
 drawing document target an the detail view. To instantiate the ditto we
 use the copy/paste mechanism because it is not possible interactively or
 using automation to create a ditto from a detail view in another document.
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 |[] CAADriInstantiateOuterDitto is
 launched in CATIA [[1]]. No open document is
 needed.
 

[CAADriInstantiateOuterDitto]
 is located in the CAADriUseCases module.  [Execute
 macro] (Windows only).
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 |[]CAADriInstantiateOuterDitto includes nine
 steps:
 

 
- [Prolog]
 
- [Opening the Drawing Document Source]
 
- [Retrieving and Defining the Ditto]
 
- [Copying the Ditto]
 
- [Opening the Drawing Document Target]
 
- [Retrieving and Defining the View]
 
- [Defining the Ditto's Location]
 
- [Pasting the Ditto]
 
- [Retrieving the Instantiated Ditto and Defining its
 Location]
 
- [Retrieving the Ditto's Modifiable Text]
 
 
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
 
#### []Opening the Drawing Document Source
 
 
 
```
...
 
' Open the drawing document containing the existing ditto

 Dim 
oDrawingSource
 As 
DrawingDocument

 Set 
oDrawingSource = CATIA.Documents.Open(sDocPath & _
 "\online\CAAScdDriUseCases\samples\CAADriInstantiateDittoSource.CATDrawing")
 ...
```

 
 
 
 

A drawing document is opened.
 
#### []Retrieving and Defining the Ditto
 
 
 
```
...
 
' Retrieve the sheet containing the ditto to be copied

 Dim 
oSheetSource
 As 
DrawingSheet

 Set 
oSheetSource = oDrawingSource.Sheets.Item("Sheet.3")
 
 
' Retrieve the view containing the ditto to be copied

 Dim 
oViewSource
 As 
DrawingView

 Set 
oViewSource = oSheetSource.Views.Item("View.1")
 
 
' Retrieve the ditto

 Dim 
oDitto
 As 
DrawingComponent

 Set 
oDi
tto 
= oViewSource.Components.Item(1)
 ...
```

 
 
 
 

The sheets collection is retrieved from the `oDrawingSource`
 object using the `Sheets` method.

 The sheet object is retrieved from the collection using the `Item`
 method from its name.

 The views collection is retrieved from the `oSheetSource`
 object using the `Views` method.

 The view object is retrieved from the collection using the `Item`
 method from its name.

 The components collection is retrieved from the `oViewSource`
 object using the `Components` method.

 The component object is retrieved from the collection using the `Item`
 method from its index.
 
#### []Copying the Ditto
 
 
 
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
 
' Add the ditto to be duplicated in the selection

 oSelectionSource.Add oDitto
 
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

 The component object is added to the selection object using the `Add`
 method.

 The view object is copied to the clipboard from the selection object using
 the `Copy` method.

 The selection object is cleared using the `Clear` method
 another time.
 
#### []Opening the Drawing Document Target
 
 
 
```
...
 
' Open the drawing document where the ditto will be instantiated

 Dim 
oDrawingTarget
 As 
DrawingDocument

 Set 
oDrawingTarget
 
= CATIA.Documents.Open(sDocPath & _
 "\online\CAADriScriptUseCases\samples\CAADriInstantiateDittoTarget.CATDrawing")
 CATIA.ActiveWindow.ActiveViewer.Reframe
 ...
```

 
 
 
 

A drawing document is opened, its window is reframed according to the
 size of the sheet.
 
#### []Retrieving and Defining the View
 
 
 
```
...
 
' Retrieve the sheet where the ditto will be instantiated

 Dim 
oSheetTarget
 As 
DrawingSheet

 Set 
oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
 oSheetTarget.Activate

 
' Retrieve the view where the ditto will be instantiated

 Dim 
oViewTarget
 As 
DrawingView

 Set 
oViewTarget = oSheetTarget.Views.Item("View.3")
 ...
```

 
 
 
 

The sheets collection is retrieved from the `oDrawingTarget`
 object using the `Sheets` method.

 The sheet object is retrieved from the collection using the `Item`
 method from its name.

 The views collection is retrieved from the `oSheetTarget`
 object using the `Views` method.

 The view object is retrieved from the collection using the `Item`
 method from its name.

 The sheet is activated.
 
#### []Defining the Ditto's Location
 

The ditto's location is retrieved using the `Indicate2D`
 method which allow user to retrieve the `x` and `y`
 coordinates when clicking the mouse. Coordinates are stored  in an
 array `iDittoCoordinates`. An unspecified object `oDraw`
 is used to prevent a signature's method restriction usage.
 

![](images/img018.gif)
 
#### []Pasting the Ditto
 
 
 
```
...
 
' Create an object of selection for the target document

 Dim 
oSelectionTarget
 As 
Selection

 Set 
oSelectionTarget = oDrawingTarget.Selection
 
 
' Clear the selection

 oSelectionTarget.Clear
 
' Add the view in the selection, where the ditto will be instantiated

 oSelectionTarget.Add oViewTarget
 
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
 
#### []Retrieving the Instantiated Ditto and Defining its
 Location
 
 
 
```
...
 
' Retrieve the drawing components collection of the target drawing view

 Dim 
o2DComponents
 As 
DrawingComponents

 Set 
o2DComponents = oViewTarget.Components
 
 
' Retrieve the ditto and define its location

 Dim 
o2DComponent
 As 
DrawingComponent

 Set 
o2DComponent = o2DComponents.Item("DrwDetail.1")
 o2DComponent.X = iDittoCoordinates(0)
 o2DComponent.Y = iDittoCoordinates(1)
 ...
```

 
 
 
 

![](images/img019.gif)
 
#### []Retrieving the Ditto's Modifiable Text
 
 
 
```
...
 
' Retrieve the modifiable text of the ditto

 Dim 
oText
 As 
DrawingText

 Set 
oText = o2DComponent.GetModifiableObject(1)
 
 
' Modify the modifiable text value

 Dim 
ReturnValue
 As 
String
 ReturnValue = InputBox("Enter a value", "", "New Value For Text")
 oText.Text = ReturnValue
 ...
```

 
 
 
 

The text object is retrieved from the `o2DComponent` object
 using the `GetModifiableObject` method.

 The text of the text object is returned using the `InputBox`
 procedure. Enter 10 and click OK.
 

![](images/img016.gif)
 

![](images/img020.gif)
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to instantiate a drawing detail view as a ditto
in a view using the *Add *method of the *Components* object.

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