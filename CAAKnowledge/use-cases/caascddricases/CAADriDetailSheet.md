---
title: "Creating a Detail Sheet"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriDetailSheet", "CAAScdPriUseCases", "CAAPriPad", "CATIA", "CAADriSheet"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDetailSheet.htm"
converted: "2026-05-11T17:31:51.047373"
---

| 
## Drafting

| 
## Creating a Detail Sheet  
  
  
* * *

  This macro shows you how to create a sheet in a drawing. This macro opens the CAADriSheet.CATDrawing document that contains a sheet only.   
It creates _DrawingSheet_ object from the _DrawingSheets_ __ collection with the AddDetail method and a activate it.  
---|---  
  CAADriSheet is launched in CATIA [1]. No open document is needed. [CAADriDetailSheet.CATScript](CAADriDetailSheetSource.md) is located in the CAAScdPriUseCases module. [Execute macro](macros/CAADriDetailSheet.CATScript) (Windows only).    
  CAAPriPad includes the following steps:

  1. Prolog
  2. Creating the Detail Sheet
  3. Activating the Detail Sheet

#### Prolog

The macro first loads CAADriDetailSheet.CATDrawing that contains a sheet: Sheet.1  ![](images/img004.jpg) 
    
    
    ...
```vbscript
    ' ------------
    ' Get the sheets collection of the drawing
    ' ------------
```

```vbscript
    Dim oDrawingSheets As DrawingSheets
    Set oDrawingSheets = oDoc.Sheets
    ...  
  
```

```

---  
  
Once the drawing document has been loaded, the `odrawingSheets` is declared to receive the instance of the sheets.
#### Creating the Detail Sheet
    
    
    ...
```vbscript
    ' ------------
    ' Add the detail sheet with a default name to the sheets collection of the drawing
    ' ------------
```

    MsgBox "Click OK to create the new sheet."
```vbscript
    Dim oDrawingSheet As DrawingSheet
    Set oDrawingSheet = oDrawingSheets.AddDetail("New Detail Sheet") 
    ...  
  
```

```

---  
  
The _oDrawingSheet_ object is added to the _oDrawingSheets_ collection with the `AddDetail` method and a default name: New Detail Sheet. 

The _oDrawingSheet_ is then displayed with the following result but not activated.

![](images/img005.jpg)
#### Activating the Detail Sheet
    
    
    ...
```vbscript
    ' ------------
    ' Activate the detail sheet
    ' ------------
```

    MsgBox "Click OK to activate the new detail sheet."
    oDrawingSheet.Activate 
    ...  
  
---  
  
The `Activate` property of the _DrawingSheet_ object is used to activate it.

![](images/img006.jpg)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create and activate a sheet using macros.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
