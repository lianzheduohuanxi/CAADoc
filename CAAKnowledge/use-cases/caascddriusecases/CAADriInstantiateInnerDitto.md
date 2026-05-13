---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAAScdDriUseCases", "CATIA", "CAADriUseCases", "CAAScrJavaScript", "CAADriInstantiateDittoSource", "CAAScdDriTechArticles", "CAADriInstantiateInnerDittoSource", "CAADriObjDrawingSheets", "CAAScdInfUseCases", "CAADriObjDrawingView", "CAADriObjDrawingSheet", "CAADriObjDrawingDocument", "CAADriInstantiateInnerDitto", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateInnerDitto.htmmd"
converted: "2026-05-11T11:27:02.744954"
---

---

 

      

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
      property of the *Application* object set to `False`.
      

#### Opening the Drawing Document
      
      

A drawing document is opened, its window is reframed according to the
      size of the sheet.
      

#### Retrieving and Defining the View
      
      

The sheets collection is retrieved from the `oDrawing`
      object using the `Sheets` method.

      The sheet object is retrieved from the collection using the `Item`
      method from its name.

      The views collection is retrieved from the `oSheet` object
      using the `Views` method.

      The view object is retrieved from the collection using the `Item`
      method from its name.

      The view is activated.
      

#### Retrieving and Defining the Detail View
      
      

The detail sheet object is retrieved from the collection using the `Item`
      method from its name.

      The detail view object is retrieved from the collection using the `Item`
      method from its name.
      

#### Defining the Ditto's Location
      
      

The ditto's location is retrieved using the `Indicate2D`
      method which allow user to retrieve the `x` and `y`
      coordinates when clicking the mouse. Coordinates are stored  in an
      array `iDittoCoordinates`. An unspecified object `oDraw`
      is used to prevent a signature's method restriction usage.
      

![](images/img014.gif)
      

#### Instantiating the Ditto
      
      

The components collection is retrieved from the `oView`
      object using the `Components` method.

      The component object is created in the collection using the `Add`
      method from the `oDetailView` view.
      

![](images/img015.gif)
      

#### Retrieving the Ditto's Modifiable Text
      
      

The text object is retrieved from the `o2DComponent` object
      using the `GetModifiableObject` method.

      The text of the text object is returned using the `InputBox`
      procedure. Enter 10 and click OK.
      

![](images/img016.gif)
      

![](images/img017.gif)
    
  

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
```vbscript
    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```vbscript
    CATIA.DisplayFileAlerts = False
  ...
```
```

```vbscript
...
    ' Open the drawing document
```vbscript
    Dim oDrawing As DrawingDocument
    Set oDrawing = CATIA.Documents.Open(sDocPath &amp; _
             &quot;/online/CAAScdDriUseCases/samples/CAADriInstantiateDittoSource.CATDrawing&quot;)    
```
  ...
```

```vbscript
...
    ' Retrieve the sheets collection of the drawing document
```vbscript
    Dim oSheets As DrawingSheets
    Set oSheets = oDrawing.Sheets
    
    ' Retrieve the sheet where the detail view will be instantiated
```
```vbscript
    Dim oSheet As DrawingSheet
    Set oSheet = oSheets.Item(&quot;Sheet.1&quot;)
    
    ' Retrieve the view where the detail view will be instantiated
```
```vbscript
    Dim oView As DrawingView
    Set oView = oSheet.Views.Item(&quot;View.3&quot;)
    oView.Activate
```
  ...
```

```vbscript
...
    ' Retrieve the detail sheet containing the detail view to be instantiated
```vbscript
    Dim oDetailSheet As DrawingSheet
    Set oDetailSheet = oSheets.Item(&quot;Sheet.2 (Detail)&quot;)
    
    ' Retrieve the detail view to be instantiated
```
```vbscript
    Dim oDetailView As DrawingView
    Set oDetailView = oDetailSheet.Views.Item(&quot;DrwDetail.1&quot;)
  ...
```
```

```vbscript
...
    ' Indicate the ditto location
```vbscript
    Dim ReturnStatus As String
    Dim iDittoCoordinates(1)
    Dim oDraw
    Set oDraw = oDrawing
    ReturnStatus = oDraw.Indicate2D(&quot;Indicate the ditto location&quot;, iDittoCoordinates)
```
  ...
```

```vbscript
...
    ' Retrieve the drawing components collection of the target drawing view
```vbscript
    Dim o2DComponents As DrawingComponents
    Set o2DComponents = oView.Components
    
    ' Create the ditto
```
```vbscript
    Dim o2DComponent As DrawingComponent
    Set o2DComponent = o2DComponents.Add(oDetailView, iDittoCoordinates(0), iDittoCoordinates(1))
  ...
```
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