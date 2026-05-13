---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAADriSheet", "CAADriSheetSource", "CAAScdPriUseCases", "CAAInfLauchMacro", "CAAPriPad", "CAAlink"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSheet.htmmd"
converted: "2026-05-11T11:27:02.764801"
---

---

      

Once the drawing document has been loaded, the `odrawingSheets`
      is declared to receive the instance of the sheets.
      

#### Creating the Sheet
      
      

The *oDrawingSheet* object is added to the *oDrawingSheets *collection
      with the `Add` method and a default name: New Sheet. 
      

The *oDrawingSheet* is then displayed with the following result
      but not activated.
      

![](images/img002.jpg)
      

#### Activating the Sheet
      
      

The `Activate` property of the *DrawingSheet *object is
      used to activate it.
      

![](images/img003.jpg)
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create and activate a sheet using macros.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
' ------------
' Get the sheets collection of the drawing
' ------------
```vbscript
Dim oDrawingSheets As DrawingSheets
Set oDrawingSheets = oDoc.Sheets
...
```
```

```vbscript
...
' ------------
' Add the sheet with a default name to the sheets collection of the drawing
' ------------
```vbscript
MsgBox &quot;Click OK to create the new sheet.&quot;
Dim oDrawingSheet As DrawingSheet
Set oDrawingSheet = oDrawingSheets.Add(&quot;New Sheet&quot;) 
...
```
```

```vbscript
...
' ------------
' Activate the sheet
' ------------
```vbscript
MsgBox &quot;Click OK to activate the new sheet.&quot;
oDrawingSheet.Activate 
```
...
```