---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIADrawingView", "CATIA", "CAADriUseCases", "CAAScrJavaScript", "CAAScdDriTechArticles", "CAADriObjDrawingSheets", "CAAScdInfUseCases", "CAADriObjDrawingView", "CAADriObjDrawingSheet", "CAADriSetPrintAreaSource", "CAADriObjDrawingDocument", "CAAInfLauchMacro", "CAADriISetPrintArea", "CAADriSetPrintArea", "CAAlink"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSetPrintArea.htm"
converted: "2026-05-11T11:27:02.759629"
---

---

      

The active document type is tested. If it is a `DrawingDocument`,
      the `oDrawingDocument` is retrieved from the `oDocument`.
      Otherwise the macro stops and prompts a warning message.
      

#### Retrieving the Active Sheet
      
      

The active sheet object is retrieved from the `Sheets`
      collection of the `oDrawingDocument` object, using the `ActiveSheet`
      method.
      

#### Retrieving the Selection of the Drawing Document
      
      

The selection object is retrieved from the `oDrawingDocument`
      object using the `Selection` method.

      The selection is cleared.
      

#### Defining the Selection
      
      

The `Point2D` filtering string is defined in the `InputObjectType`
      array.

      The first point location is retrieved from  the `oSelection`
      object using the `IndicateOrSelectElement2D` method.

      According to the `ObjectSelected` boolean value retrieved:
      

        
- `True`: the selection contains a drawing point.
        
- `False`: any drawing point has been selected, but a
          virtual point has been indicated. The coordinates of this location are
          contained in the `oFirstPointAbsolute` array.
      
      

#### Retrieving the Location of the First Point
      
      

According to the `ObjectSelected` boolean value retrieved as
      `True`:
      

        
- The `iFirstPoint` object is retrieved from the `oSelection`
          object using the value of the first item. There is only one item,
          because the `IndicateOrSelectElement2D` method allows you
          to select only one element.
        
- The `oView` object is retrieved from the `oSelection`
          object using the `Find Object` method and specifying the
          object DrawingView  type to be found: `CATIADrawingView`.
          A drawing point is already contained into a drawing view, even for
          those which are in the drawing sheet and not in any drawing views. In
          fact, there is a hidden drawing view corresponding to the drawing
          sheet, because you cannot create 2D geometry directly in the drawing
          sheet.
        
- The `oFirstPointRelative` array is retrieved from the `iFirstPoint`
          object using the `GetCoordinates` method. This array
          contains the coordinates of the selected point according to the
          reference axis of its drawing view.
        
- The `oFirstPointAbsolute` array is computed from the `oFirstPointRelative`
          array using the `CatAbsoluteCoordinates` procedure. In this
          procedure the drawing view location, angle and scale factor are
          retrieved from the `oView` object.
      
      

Otherwise, the `oFirstPointAbsolute` array already contains
      the location of the virtual point.
      

        
- Select the first point. This point is located in the hidden view of
          the sheet and not in the `Front view`.

          ![](images/img021.gif)
        
- Select the second point. This point is located in the hidden view of
          the sheet and not in the `Isometric view`.

          ![](images/img022.gif)
      
      

#### Defining the Print Area
      
      

The print area is defined from a starting point and from its width and
      height. As this starting point must be in the left-bottom corner of the
      print area, to ensure this rule, two tests are performed to find the
      smallest abscissa and ordinate: `XPrintArea` and `YPrintArea`.

      The width and height are computed form the coordinates of the selected
      points: `WidthPrintArea` and `HeightPrintArea`.

      The print area object is retrieved from the `oSheet` object
      using the `PrintArea` method.

      The `oPrintArea` object is defined using the `SetArea`
      method.

      The `oPrintArea` object is activated using the `ActivationState`
      property set to `True`.
      

#### Visualizing the Print Area
      
      

To visualize the print area we have to run the specific command, but as
      this command can be run only with a selected sheet, we have to select it
      before: `oSelection.Add oSheet`

      To run the command you can use its id or its alias. In English context,
      the alias is the name of the command `"Visualize Print
      Area"`, but to ensure the macro works in a non-language
      context, we use its id `"CATDrwVisualizePrintAreaHdr".`
      

![](images/img023.gif)
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to define the print area using the new method `IndicateOrSelectElement2D`
of the `Selection` object

[Top]

---

#### References

---

*Copyright  2004, Dassault Systmes. All rights reserved.*



```vbscript
...
' Retrieve the active document
Dim oDocument As Document
Set oDocument = CATIA.ActiveDocument

' Test the document's type, if it is not a drawing document the macro stops
If TypeName(oDocument) = &quot;DrawingDocument&quot; Then
    Dim oDrawingDocument As DrawingDocument
    Set oDrawingDocument = oDocument
Else
    MsgBox &quot;This macro can be run with a drawing document only.&quot;
    Exit Sub
End If
...
```

```vbscript
...
' Retrieve the active sheet of the document
Dim oSheet As DrawingSheet
Set oSheet = oDrawingDocument.Sheets.ActiveSheet  
...
```

```vbscript
...
' Retrieve the selection of the document
Dim oSelection 'As Selection
Set oSelection = oDrawingDocument.Selection
' Clear the selection
oSelection.Clear
...
```

```vbscript
...
' Define the object type allowed to be selected, here a drawing point
Dim InputObjectType(0)
InputObjectType(0) = &quot;Point2D&quot;
...
' Retrieve the first point location to set the print area from the mouse selection
ReturnStatus = oSelection.IndicateOrSelectElement2D(&quot;Select the first point&quot;, _
InputObjectType, True, True, False, ObjectSelected, oFirstPointAbsolute)
...
```

```vbscript
...
' Test of the selection content from the ObjectSelected value
If ObjectSelected = True Then
    ...
    Set iFirstPoint = oSelection.Item(1).Value
    ...
    Set oView = oSelection.FindObject(&quot;CATIADrawingView&quot;)
    ...
    iFirstPoint.GetCoordinates oFirstPointRelative
    ...
    CatAbsoluteCoordinates oView, oFirstPointAbsolute, oFirstPointRelative
End If
...
```

```vbscript
...
' Define the coordinates of the print area's point
Dim XPrintArea As Double
Dim YPrintArea As Double

If oFirstPointAbsolute(0) &gt; oSecondPointAbsolute(0) Then
    XPrintArea = oSecondPointAbsolute(0)
Else
    XPrintArea = oFirstPointAbsolute(0)
End If

If oFirstPointAbsolute(1) &gt; oSecondPointAbsolute(1) Then
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
```

```vbscript
...
oSelection.Add oSheet
CATIA.StartCommand &quot;CATDrwVisualizePrintAreaHdr&quot;
oSelection.Clear
 ...
```