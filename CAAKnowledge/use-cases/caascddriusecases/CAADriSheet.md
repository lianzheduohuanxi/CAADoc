---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAADriSheet", "CAAInfLauchMacro", "CAAPriPad", "CAAScdInfUseCases", "CAADriSheetSource", "CAAlink", "CAAScdPriUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSheet.htm"
converted: "2026-05-11T11:06:32.937620"
---

## Drafting
 
 
## []Creating a Sheet
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create a sheet in a
 drawing.
 

This macro opens the CAADriSheet.CATDrawing document that contains a
 sheet only.

 It creates [*DrawingSheet*]
 object from the [*DrawingSheets*]*
 *collection with the Add method and a activate it.
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAADriSheet is launched in CATIA [[1]].
 No open document is needed.
 

[CAADriSheet.CATScript] is located in
 the CAAScdPriUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAPriPad includes the following steps:
 

 
- [Prolog]
 
- [Creating the Sheet]
 
- [Activating the Sheet]
 
 
#### []Prolog
 

The macro first loads CAADriSheet.CATDrawing that contains a sheet:
 Sheet.1
 

![](images/img001.jpg)
 
 
 
```
...

' ------------

' Get the sheets collection of the drawing

' ------------

Dim 
oDrawingSheets
 As 
DrawingSheets

Set 
oDrawingSheets = oDoc.Sheets
...
```

 
 
 
 

Once the drawing document has been loaded, the `odrawingSheets`
 is declared to receive the instance of the sheets.
 
#### []Creating the Sheet
 
 
 
```
...

' ------------

' Add the sheet with a default name to the sheets collection of the drawing

' ------------

MsgBox "Click OK to create the new sheet."

Dim 
oDrawingSheet
 As 
DrawingSheet

Set 
oDrawingSheet = oDrawingSheets.Add("New Sheet") 
...
```

 
 
 
 

The *oDrawingSheet* object is added to the *oDrawingSheets *collection
 with the `Add` method and a default name: New Sheet. 
 

The *oDrawingSheet* is then displayed with the following result
 but not activated.
 

![](images/img002.jpg)
 
#### []Activating the Sheet
 
 
 
```
...

' ------------

' Activate the sheet

' ------------

MsgBox "Click OK to activate the new sheet."
oDrawingSheet.Activate 
...
```

 
 
 
 

The `Activate` property of the *DrawingSheet *object is
 used to activate it.
 

![](images/img003.jpg)
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create and activate a sheet using macros.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*