---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAAScdDriUseCases", "CATIA", "CAADriUseCases", "CAAScrJavaScript", "CAADriDuplicateAViewSource", "CAAScdDriTechArticles", "CAADriObjDrawingSheets", "CAAScdInfUseCases", "CAADriObjDrawingView", "CAADriObjDrawingSheet", "CAADriObjDrawingDocument", "CAAInfLauchMacro", "CAADriDuplicateAView"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDuplicateAView.htmmd"
converted: "2026-05-11T11:27:02.748721"
---

---

 

      

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
      property of the *Application* object set to `False`.
      

#### Opening and Reframing an Existing Drawing Document
      
      

A drawing document is opened, its window is reframed according to the
      size of the sheet.
      

#### Retrieving and Defining the Sheet
      
      

The sheets collection is retrieved from the `oDrawingSource`
      object using the `Sheets` method.

      The sheet object is retrieved from the collection using the `Item`
      method from its name.
      

#### Retrieving and Defining the View
      
      

The views collection is retrieved from the `oSheetSource`
      object using the `Views` method.

      The view object is retrieved from the collection using the `Item`
      method from its name.
      

#### Copying the View
      
      

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
      

#### Creating the New Drawing Document
      
      

A new drawing document is created and the sheet object is retrieved,
      the size of its sheet is set to A0.
      

#### Pasting the View
      
      

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
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to copy/paste a Drawing view using the *Copy *and*
Paste* methods of the *Selection* object.

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
    ' Open the Drawing document
```vbscript
    Dim oDrawingSource As DrawingDocument
    Set oDrawingSource = CATIA.Documents.Open(sDocPath &amp; _
             &quot;/online/CAAScdDriUseCases/samples/CAADriDuplicateAView.CATDrawing&quot;)
```
    
    ' Fit in window the opened document
```vbscript
    CATIA.ActiveWindow.ActiveViewer.Reframe
  ...
```
```

```vbscript
...
    ' Retrieve the sheet containing the view to be duplicated
```vbscript
    Dim oSheetSource As DrawingSheet
    Set oSheetSource = oDrawingSource.Sheets.Item(&quot;Sheet.1&quot;)
  ...
```
```

```vbscript
...
    ' Retrieve the view to be duplicated
```vbscript
    Dim oViewSource As DrawingView
    Set oViewSource = oSheetSource.Views.Item(&quot;Front view&quot;)
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
    ' Add the view to be duplicated in the selection
    oSelectionSource.Add oViewSource
    ' Copy the view
    oSelectionSource.Copy
    ' Clear the selection
    oSelectionSource.Clear
  ...
```

```vbscript
...
    ' Create the Drawing document where the view will be pasted
```vbscript
    Dim oDrawingTarget As DrawingDocument
    Set oDrawingTarget = CATIA.Documents.Add(&quot;Drawing&quot;)
    
    ' Retrieve the where the view will be pasted
```
```vbscript
    Dim oSheetTarget As DrawingSheet
    Set oSheetTarget = oDrawingTarget.Sheets.Item(&quot;Sheet.1&quot;)
    
    ' Set the sheet paper size
    oSheetTarget.PaperSize = catPaperA0
```
  ...
```

```vbscript
...
    ' Create an object of selection for the source document
```vbscript
    Dim oSelectionTarget As Selection
    Set oSelectionTarget = oDrawingTarget.Selection
    
```
    
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