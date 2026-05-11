---
title: "Creating a Sheet"
category: "general"
module: "CAAScdDriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAADriSheet", "CAAPriPad"]
source_file: "Doc\online\CAAScdDriUseCases\CAADriSheet.htm"
converted: "2026-05-11T17:31:51.105743"
---

## Drafting

| 

## Creating a Sheet  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This macro shows you how to create a sheet in a drawing. This macro opens the CAADriSheet.CATDrawing document that contains a sheet only.  
It creates _DrawingSheet_ object from the _DrawingSheets_ __ collection with the Add method and a activate it.  
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAADriSheet is launched in CATIA [1]. No open document is needed. [CAADriSheet.CATScript](CAADriSheetSource.htm) is located in the CAAScdPriUseCases module. [Execute macro](macros/CAADriSheet.CATScript) (Windows only).    
![](../CAAScrBase/images/ascenari.gif) |  CAAPriPad includes the following steps:

  1. Prolog
  2. Creating the Sheet
  3. Activating the Sheet



#### Prolog

The macro first loads CAADriSheet.CATDrawing that contains a sheet: Sheet.1 ![](images/img001.jpg) | 
    
    
    ...
    ' ------------
    ' Get the sheets collection of the drawing
    ' ------------
    Dim oDrawingSheets As DrawingSheets
    Set oDrawingSheets = oDoc.Sheets
    ...  
  
---  
  
Once the drawing document has been loaded, the `odrawingSheets` is declared to receive the instance of the sheets.

#### Creating the Sheet
    
    
    ...
    ' ------------
    ' Add the sheet with a default name to the sheets collection of the drawing
    ' ------------
    MsgBox "Click OK to create the new sheet."
    Dim oDrawingSheet As DrawingSheet
    Set oDrawingSheet = oDrawingSheets.Add("New Sheet") 
    ...  
  
---  
  
The _oDrawingSheet_ object is added to the _oDrawingSheets_ collection with the `Add` method and a default name: New Sheet. 

The _oDrawingSheet_ is then displayed with the following result but not activated.

![](images/img002.jpg)

#### Activating the Sheet
    
    
    ...
    ' ------------
    ' Activate the sheet
    ' ------------
    MsgBox "Click OK to activate the new sheet."
    oDrawingSheet.Activate 
    ...  
  
---  
  
The `Activate` property of the _DrawingSheet_ object is used to activate it.

![](images/img003.jpg)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to create and activate a sheet using macros.

[Top]

* * *

#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
