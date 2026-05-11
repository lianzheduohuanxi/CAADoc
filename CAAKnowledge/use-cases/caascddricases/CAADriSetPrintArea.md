---
title: "Setting the Print Area of a Drawing Sheet"
category: "general"
module: "CAAScdDriUseCases"
tags: ["CAADriISetPrintArea", "CATIA", "CAADriSetPrintArea", "CAADriUseCases", "CATIADrawingView"]
source_file: "Doc\online\CAAScdDriUseCases\CAADriSetPrintArea.htm"
converted: "2026-05-11T17:31:51.099755"
---

## Interactive Drafting

| 

## Setting the Print Area of a Drawing Sheet  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to set the print area of the current sheet using the mouse selection. You select a couple of drawing points to define the print area rectangle. You can can select any drawing point into the sheet, including those into a view.  
This macro is based on an active drawing document.  
---|---  
![](../CAAScrBase/images/ainfo.gif) | Open the drawing document: [CAADriSetPrintArea.CATDrawing](samples/CAADriSetPrintArea.CATDrawing) Run CAADriISetPrintArea in CATIA [1]. [CAADriISetPrintArea](CAADriSetPrintAreaSource.htm) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriSetPrintArea.CATScript) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) | CAADriISetPrintArea includes seven steps: 

  1. Prolog
  2. Retrieving the Active Sheet
  3. Retrieving the Selection of the Drawing Document
  4. Defining the Selection
  5. Retrieving the Location of the First Point
  6. Defining the Print Area
  7. Visualizing the Print Area
  8. InShort



#### Prolog

| 
    
    
    ...
    ' Retrieve the active document
    Dim oDocument As Document
    Set oDocument = CATIA.ActiveDocument
    
    ' Test the document's type, if it is not a drawing document the macro stops
    If TypeName(oDocument) = "DrawingDocument" Then
        Dim oDrawingDocument As DrawingDocument
        Set oDrawingDocument = oDocument
    Else
        MsgBox "This macro can be run with a drawing document only."
        Exit Sub
    End If
    ...  
  
---  
  
The active document type is tested. If it is a `DrawingDocument`, the `oDrawingDocument` is retrieved from the `oDocument`. Otherwise the macro stops and prompts a warning message.

#### Retrieving the Active Sheet
    
    
    ...
    ' Retrieve the active sheet of the document
    Dim oSheet As DrawingSheet
    Set oSheet = oDrawingDocument.Sheets.ActiveSheet  
    ...  
  
---  
  
The active sheet object is retrieved from the `Sheets` collection of the `oDrawingDocument` object, using the `ActiveSheet` method.

#### Retrieving the Selection of the Drawing Document
    
    
    ...
    ' Retrieve the selection of the document
    Dim oSelection 'As Selection
    Set oSelection = oDrawingDocument.Selection
    ' Clear the selection
    oSelection.Clear
    ...  
  
---  
  
The selection object is retrieved from the `oDrawingDocument` object using the `Selection` method.  
The selection is cleared.

#### Defining the Selection
    
    
    ...
    ' Define the object type allowed to be selected, here a drawing point
    Dim InputObjectType(0)
    InputObjectType(0) = "Point2D"
    ...
    ' Retrieve the first point location to set the print area from the mouse selection
    ReturnStatus = oSelection.IndicateOrSelectElement2D("Select the first point", _
    InputObjectType, True, True, False, ObjectSelected, oFirstPointAbsolute)
    ...  
  
---  
  
The `Point2D` filtering string is defined in the `InputObjectType` array.  
The first point location is retrieved from  the `oSelection` object using the `IndicateOrSelectElement2D` method.  
According to the `ObjectSelected` boolean value retrieved:

  * `True`: the selection contains a drawing point.
  * `False`: any drawing point has been selected, but a virtual point has been indicated. The coordinates of this location are contained in the `oFirstPointAbsolute` array.



#### Retrieving the Location of the First Point
    
    
    ...
    ' Test of the selection content from the ObjectSelected value
    If ObjectSelected = True Then
        ...
        Set iFirstPoint = oSelection.Item(1).Value
        ...
        Set oView = oSelection.FindObject("CATIADrawingView")
        ...
        iFirstPoint.GetCoordinates oFirstPointRelative
        ...
        CatAbsoluteCoordinates oView, oFirstPointAbsolute, oFirstPointRelative
    End If
    ...  
  
---  
  
According to the `ObjectSelected` boolean value retrieved as `True`:

  * The `iFirstPoint` object is retrieved from the `oSelection` object using the value of the first item. There is only one item, because the `IndicateOrSelectElement2D` method allows you to select only one element.
  * The `oView` object is retrieved from the `oSelection` object using the `Find Object` method and specifying the object DrawingView  type to be found: `CATIADrawingView`. A drawing point is already contained into a drawing view, even for those which are in the drawing sheet and not in any drawing views. In fact, there is a hidden drawing view corresponding to the drawing sheet, because you cannot create 2D geometry directly in the drawing sheet.
  * The `oFirstPointRelative` array is retrieved from the `iFirstPoint` object using the `GetCoordinates` method. This array contains the coordinates of the selected point according to the reference axis of its drawing view.
  * The `oFirstPointAbsolute` array is computed from the `oFirstPointRelative` array using the `CatAbsoluteCoordinates` procedure. In this procedure the drawing view location, angle and scale factor are retrieved from the `oView` object.



Otherwise, the `oFirstPointAbsolute` array already contains the location of the virtual point.

  1. Select the first point. This point is located in the hidden view of the sheet and not in the `Front view`.  
![](images/img021.gif)
  2. Select the second point. This point is located in the hidden view of the sheet and not in the `Isometric view`.  
![](images/img022.gif)



#### Defining the Print Area
    
    
    ...
    ' Define the coordinates of the print area's point
    Dim XPrintArea As Double
    Dim YPrintArea As Double
    
    If oFirstPointAbsolute(0) > oSecondPointAbsolute(0) Then
        XPrintArea = oSecondPointAbsolute(0)
    Else
        XPrintArea = oFirstPointAbsolute(0)
    End If
    
    If oFirstPointAbsolute(1) > oSecondPointAbsolute(1) Then
        YPrintArea = oSecondPointAbsolute(1)
    Else
        YPrintArea = oFirstPointAbsolute(1)
    End If
    
    Dim WidthPrintArea As Double
    Dim HeightPrintArea As Double
    
    ' Define the width and height of the print area
    WidthPrintArea = Abs(oSecondPointAbsolute(0) - oFirstPointAbsolute(0))
    HeightPrintArea = Abs(oSecondPointAbsolute(1) - oFirstPointAbsolute(1))
    
    ' Define and activate the print area of the drawing document
    Dim oPrintArea As PrintArea
    Set oPrintArea = oSheet.PrintArea
    
    oPrintArea.SetArea XPrintArea, YPrintArea, WidthPrintArea, HeightPrintArea
    oPrintArea.ActivationState = True
    ...  
  
---  
  
The print area is defined from a starting point and from its width and height. As this starting point must be in the left-bottom corner of the print area, to ensure this rule, two tests are performed to find the smallest abscissa and ordinate: `XPrintArea` and `YPrintArea`.  
The width and height are computed form the coordinates of the selected points: `WidthPrintArea` and `HeightPrintArea`.  
The print area object is retrieved from the `oSheet` object using the `PrintArea` method.  
The `oPrintArea` object is defined using the `SetArea` method.  
The `oPrintArea` object is activated using the `ActivationState` property set to `True`.

#### Visualizing the Print Area
    
    
    ...
    oSelection.Add oSheet
    CATIA.StartCommand "CATDrwVisualizePrintAreaHdr"
    oSelection.Clear
     ...  
  
---  
  
To visualize the print area we have to run the specific command, but as this command can be run only with a selected sheet, we have to select it before: `oSelection.Add oSheet`  
To run the command you can use its id or its alias. In English context, the alias is the name of the command `"Visualize Print Area"`, but to ensure the macro works in a non-language context, we use its id `"CATDrwVisualizePrintAreaHdr".`

![](images/img023.gif)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to define the print area using the new method `IndicateOrSelectElement2D` of the `Selection` object

[Top]

* * *

#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.htm)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.htm),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.htm) _,__[DrawingView](../CAAScdDriTechArticles/CAADriObjDrawingView.htm), Selection_  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
