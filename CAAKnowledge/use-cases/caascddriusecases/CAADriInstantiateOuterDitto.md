---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAAScdDriUseCases", "CATIA", "CAADriUseCases", "CAAScrJavaScript", "CAADriInstantiateDittoSource", "CAAScdDriTechArticles", "CAADriObjDrawingSheets", "CAAScdInfUseCases", "CAADriInstantiateOuterDittoSource", "CAADriObjDrawingView", "CAADriObjDrawingSheet", "CAADriInstantiateDittoTarget", "CAADriObjDrawingDocument", "CAADriInstantiateOuterDitto", "CAAInfLauchMacro", "CAADriScriptUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateOuterDitto.htmmd"
converted: "2026-05-11T11:27:02.763860"
---

---

      

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
      property of the *Application* object set to `False`.
      

#### Opening the Drawing Document Source
      
      

A drawing document is opened.
      

#### Retrieving and Defining the Ditto
      
      

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
      

#### Copying the Ditto
      
      

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
      

#### Opening the Drawing Document Target
      
      

A drawing document is opened, its window is reframed according to the
      size of the sheet.
      

#### Retrieving and Defining the View
      
      

The sheets collection is retrieved from the `oDrawingTarget`
      object using the `Sheets` method.

      The sheet object is retrieved from the collection using the `Item`
      method from its name.

      The views collection is retrieved from the `oSheetTarget`
      object using the `Views` method.

      The view object is retrieved from the collection using the `Item`
      method from its name.

      The sheet is activated.
      

#### Defining the Ditto's Location
      

The ditto's location is retrieved using the `Indicate2D`
      method which allow user to retrieve the `x` and `y`
      coordinates when clicking the mouse. Coordinates are stored  in an
      array `iDittoCoordinates`. An unspecified object `oDraw`
      is used to prevent a signature's method restriction usage.
      

![](images/img018.gif)
      

#### Pasting the Ditto
      
      

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
      

#### Retrieving the Instantiated Ditto and Defining its
      Location
      
      

![](images/img019.gif)
      

#### Retrieving the Ditto's Modifiable Text
      
      

The text object is retrieved from the `o2DComponent` object
      using the `GetModifiableObject` method.

      The text of the text object is returned using the `InputBox`
      procedure. Enter 10 and click OK.
      

![](images/img016.gif)
      

![](images/img020.gif)
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to instantiate a drawing detail view as a ditto
in a view using the *Add *method of the *Components* object.

[Top]

---

#### References

---

*Copyright  2003, Dassault Systmes. All rights reserved.*

```vbscript
...
```cpp
    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```cpp
    CATIA.DisplayFileAlerts = False
  ...
```
```

```vbscript
...
    ' Open the drawing document containing the existing ditto
```cpp
    Dim oDrawingSource As DrawingDocument
    Set oDrawingSource = CATIA.Documents.Open(sDocPath &amp; _
             &quot;/online/CAAScdDriUseCases/samples/CAADriInstantiateDittoSource.CATDrawing&quot;)
```
  ...
```

```vbscript
...
    ' Retrieve the sheet containing the ditto to be copied
```vbscript
    Dim oSheetSource As DrawingSheet
    Set oSheetSource = oDrawingSource.Sheets.Item(&quot;Sheet.3&quot;)
    
    ' Retrieve the view containing the ditto to be copied
```
```vbscript
    Dim oViewSource As DrawingView
    Set oViewSource = oSheetSource.Views.Item(&quot;View.1&quot;)
    
    ' Retrieve the ditto
```
```vbscript
    Dim oDitto As DrawingComponent
    Set oDitto = oViewSource.Components.Item(1)
  ...
```
```

```vbscript
...
    ' Create an object of selection for the source document
```vbscript
    Dim oSelectionSource As Selection
    Set oSelectionSource = oDrawingSource.Selection
    
```
    
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

```vbscript
...
    ' Open the drawing document where the ditto will be instantiated
```cpp
    Dim oDrawingTarget As DrawingDocument
    Set oDrawingTarget = CATIA.Documents.Open(sDocPath &amp; _
             &quot;/online/CAADriScriptUseCases/samples/CAADriInstantiateDittoTarget.CATDrawing&quot;)
```
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
  ...
```
```

```vbscript
...
    ' Retrieve the sheet where the ditto will be instantiated
```vbscript
    Dim oSheetTarget As DrawingSheet
    Set oSheetTarget = oDrawingTarget.Sheets.Item(&quot;Sheet.1&quot;)
    oSheetTarget.Activate
```

    ' Retrieve the view where the ditto will be instantiated
```vbscript
    Dim oViewTarget As DrawingView
    Set oViewTarget = oSheetTarget.Views.Item(&quot;View.3&quot;)
  ...
```
```

```vbscript
...
    ' Create an object of selection for the target document
```vbscript
    Dim oSelectionTarget As Selection
    Set oSelectionTarget = oDrawingTarget.Selection
    
```
    
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

```vbscript
...
    ' Retrieve the drawing components collection of the target drawing view
```vbscript
    Dim o2DComponents As DrawingComponents
    Set o2DComponents = oViewTarget.Components
    
    ' Retrieve the ditto and define its location
```
```vbscript
    Dim o2DComponent As DrawingComponent
    Set o2DComponent = o2DComponents.Item(&quot;DrwDetail.1&quot;)
    o2DComponent.X = iDittoCoordinates(0)
```
    o2DComponent.Y = iDittoCoordinates(1)
  ...
```

```vbscript
...
    ' Retrieve the modifiable text of the ditto
```vbscript
    Dim oText As DrawingText
    Set oText = o2DComponent.GetModifiableObject(1)
    
    ' Modify the modifiable text value
```
```vbscript
    Dim ReturnValue As String
    ReturnValue = InputBox(&quot;Enter a value&quot;, &quot;&quot;, &quot;New Value For Text&quot;)
```
    oText.Text = ReturnValue
  ...
```