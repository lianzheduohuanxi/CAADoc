---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAAScdDriUseCases", "CAADriCreateView", "CATIA", "CAAScrJavaScript", "CAAScdDriTechArticles", "CAADriObjDrawingSheets", "CAAScdInfUseCases", "CAADriCreateViewSource", "CAAInfLauchMacro", "CAADriObjDrawingSheet", "CAADriObjDrawingDocument", "CAADriObjDrawingView", "CAAlink"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriCreateView.htmmd"
converted: "2026-05-11T11:27:02.752753"
---

---

      

Open the part document to draw and create a new *[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)*.
      The part document is fetched in the documentation installation path, this
      path has already been stored in the `sDocPath` variable.
      

#### Creating a New View in the Active Sheet
      
      

The new *DrawingView*
      is created in the active *[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md)*
      that is found on the *DrawingSheets*
      collection aggregated by the *DrawingDocument* object.
      

```vbscript
#### Set its Parameters to Make it a Generative Front
      View
```
      
      

The generative behavior is provided by the *DrawingViewGenerativeBehavior*
      object aggregated by the *DrawingView*. We need to define the
      document to draw by valuating the `Document` attribute of the
      generative behavior. We then define which projection plane in this
      document will be used to draw the front view (here XY) and then the
      position of this view in its parent *Sheet*.
      

#### Epilog
      
      

Update the now completely defined generative behavior.
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create generative views in a drawing document.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
    ' Open the Part document 
```vbscript
    Dim oPartToDraw As PartDocument
    Set oPartToDraw = CATIA.Documents.Open(sDocPath &amp; _
             &quot;/online/CAAScdDriUseCases/samples/Cube.CATPart&quot;)
```

    ' Create a drawing document: it becomes the active document.
```vbscript
    Dim oDrawing As DrawingDocument
    Set oDrawing = CATIA.Documents.Add(&quot;Drawing&quot;)
  ...
```
```

```vbscript
...
  ' Retrieve the active sheet
```vbscript
    Dim oSheet As DrawingSheet
    Set oSheet = oDrawing.Sheets.ActiveSheet

    ' Create a view called &quot;Front View&quot; in this sheet
```
```vbscript
    Dim oFrontView As DrawingView
    Set oFrontView = oSheet.Views.Add(&quot;Front View&quot;)
  ...
```
```

```vbscript
...
    ' Retrieve it generative behavior
```vbscript
    Dim oFrontViewGB As DrawingViewGenerativeBehavior
    Set oFrontViewGB = oFrontView.GenerativeBehavior

```

    ' Declare the part to draw in this front view
    oFrontViewGB.Document = oPartToDraw

    ' Define this view as a front view, with the XY plane (in oPartToDraw) as projection plane 
    oFrontViewGB.DefineFrontView 1, 0, 0, 0, 1, 0

    ' Position the View in the Sheet
    oFrontView.x = 300
    oFrontView.y = 150
  ...
```

```vbscript
...
   ' Update the view
    oFrontViewGB.Update
```