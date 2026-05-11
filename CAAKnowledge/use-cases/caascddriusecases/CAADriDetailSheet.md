---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAADriSheet", "CAADriDetailSheet", "CAAScdPriUseCases", "CAAInfLauchMacro", "CAAPriPad", "CAADriDetailSheetSource", "CAAlink"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDetailSheet.htm"
converted: "2026-05-11T11:27:02.755106"
---

---

      

Once the drawing document has been loaded, the `odrawingSheets`
      is declared to receive the instance of the sheets.
      

#### Creating the Detail Sheet
      
      

The *oDrawingSheet* object is added to the *oDrawingSheets *collection
      with the `AddDetail` method and a default name: New Detail
      Sheet. 
      

The *oDrawingSheet* is then displayed with the following result
      but not activated.
      

![](images/img005.jpg)
      

#### Activating the Detail Sheet
      
      

The `Activate` property of the *DrawingSheet *object is
      used to activate it.
      

![](images/img006.jpg)
    
  

![](../CAAScrBase/images/aendtask.gif)

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
Dim oDrawingSheets As DrawingSheets
Set oDrawingSheets = oDoc.Sheets
...
```

```vbscript
...
' ------------
' Add the detail sheet with a default name to the sheets collection of the drawing
' ------------
MsgBox &quot;Click OK to create the new sheet.&quot;
Dim oDrawingSheet As DrawingSheet
Set oDrawingSheet = oDrawingSheets.AddDetail(&quot;New Detail Sheet&quot;) 
...
```

```vbscript
...
' ------------
' Activate the detail sheet
' ------------
MsgBox &quot;Click OK to activate the new detail sheet.&quot;
oDrawingSheet.Activate 
...
```