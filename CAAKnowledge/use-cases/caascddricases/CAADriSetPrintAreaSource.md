---
title: "CAADriSetPrintArea.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CATIADrawingView", "CATIA", "CAADriSetPrintArea"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSetPrintAreaSource.htm"
converted: "2026-05-11T17:31:51.102250"
---

```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' ***********************************************************************
    '   Purpose     : This macro allows you to set the drafting print area
    '                 from the mouse selection, then to visualize it.
    '   Author      : TBU
    '   Languages   : VBScript
    '   Locales     : English 
    '   CATIA Level : V5R14
    ' ***********************************************************************
```

    
```vbscript
    Sub CATMain()
    ' Retrieve the active document
```vbscript
    Dim oDocument As Document
    Set oDocument = CATIA.ActiveDocument
```vbscript
    ' Test the document's type, if it is not a drawing document the macro stops
    If TypeName(oDocument) = "DrawingDocument" Then
        Dim oDrawingDocument As DrawingDocument
        Set oDrawingDocument = oDocument
```

    Else
        MsgBox "This macro can be run with a drawing document only."
        Exit Sub
    End If
```vbscript
    ' Retrieve the active sheet of the document
    Dim oSheet As DrawingSheet
    Set oSheet = oDrawingDocument.Sheets.ActiveSheet
    ' Retrieve the selection of the document
    Dim oSelection 'As Selection
    Set oSelection = oDrawingDocument.Selection
    ' Clear the selection
```

    oSelection.Clear
    ' Define the object type allowed to be selected, here a drawing point
    Dim InputObjectType(0)
    InputObjectType(0) = "Point2D"
    Dim ReturnStatus As String
    Dim oView As DrawingView
    Dim ObjectSelected As Boolean
    
    Dim iFirstPoint 'As Point 2D
    Dim oFirstPointRelative(1)
    Dim oFirstPointAbsolute(1)
```vbscript
    ' Retrieve the first point location to set the print area from the mouse selection
    ReturnStatus = oSelection.IndicateOrSelectElement2D("Select the first point", InputObjectType, True, True, False, ObjectSelected, oFirstPointAbsolute)
    ' Test of the selection content from the ObjectSelected value
    If ObjectSelected  Then
        ' A drawing point has been selected
        ' Retrieve the drawing point object
        Set iFirstPoint = oSelection.Item(1).Value
        ' Retrieve the drawing point's view form the FindObject method of the selection
        Set oView = oSelection.FindObject("CATIADrawingView")
        ' Retrieve the drawing point's coordinates,
        ' these coordinates are defined from the view's reference axis
```

        iFirstPoint.GetCoordinates oFirstPointRelative
        ' Compute the drawing point's coordinates according to the sheet's reference axis
        CatAbsoluteCoordinates oView, oFirstPointAbsolute, oFirstPointRelative
    End If
    oSelection.Clear
    
    Dim iSecondPoint 'As Point2D
    Dim oSecondPointRelative(1)
    Dim oSecondPointAbsolute(1)
    ' Retrieve the second point location to set the print area from the mouse selection
    ReturnStatus = oSelection.IndicateOrSelectElement2D("Select the second point", InputObjectType, True, True, False, ObjectSelected, oSecondPointAbsolute)
    
```

    If ObjectSelected  Then
        ' A drawing point has been selected
        ' Retrieve the drawing point object
```vbscript
        Set iSecondPoint = oSelection.Item(1).Value
```vbscript
        ' Retrieve the drawing point's view form the FindObject method of the selection
        Set oView = oSelection.FindObject("CATIADrawingView")
        ' Retrieve the drawing point's coordinates,
        ' these coordinates are defined from the view's reference axis
```

        iSecondPoint.GetCoordinates oSecondPointRelative
        ' Compute the drawing point's coordinates according to the sheet's reference axis
        CatAbsoluteCoordinates oView, oSecondPointAbsolute, oSecondPointRelative
    End If
    oSelection.Clear
```vbscript
    ' Define the coordinates of the print area's point
    Dim XPrintArea As Double
    Dim YPrintArea As Double
```

    
```

    If oFirstPointAbsolute(0) > oSecondPointAbsolute(0) Then
        XPrintArea = oSecondPointAbsolute(0)
    Else
        XPrintArea = oFirstPointAbsolute(0)
    End If
    
```

    If oFirstPointAbsolute(1) > oSecondPointAbsolute(1) Then
        YPrintArea = oSecondPointAbsolute(1)
    Else
        YPrintArea = oFirstPointAbsolute(1)
    End If
    
    Dim WidthPrintArea As Double
    Dim HeightPrintArea As Double
```vbscript
    ' Define the width and height of the print area
    WidthPrintArea = Abs(oSecondPointAbsolute(0) - oFirstPointAbsolute(0))
    HeightPrintArea = Abs(oSecondPointAbsolute(1) - oFirstPointAbsolute(1))
    ' Define and activate the print area of the drawing document
    Dim oPrintArea As PrintArea
    Set oPrintArea = oSheet.PrintArea
```

    
```

    oPrintArea.SetArea XPrintArea, YPrintArea, WidthPrintArea, HeightPrintArea
    oPrintArea.ActivationState = True
    ' Run the "Visualize Print Area" command from its id, the sheet must be selected before !
    oSelection.Add oSheet
```vbscript
    CATIA.StartCommand "CATDrwVisualizePrintAreaHdr"
    oSelection.Clear
    
```

```vbscript
    End Sub
    
```

    Private Sub CatAbsoluteCoordinates(CatDrawingView As Object, AbsoluteCoordinates(), RelativeCoordinates())
    ' Compute the coordinates of a point in a view according to the sheet's reference axis
    ' Location, Angle and Scale factor of the view are take into account
    AbsoluteCoordinates(0) = CatDrawingView.xAxisData + (RelativeCoordinates(0) * Cos(CatDrawingView.Angle) - RelativeCoordinates(1) * Sin(CatDrawingView.Angle)) * CatDrawingView.Scale2
    AbsoluteCoordinates(1) = CatDrawingView.yAxisData + (RelativeCoordinates(0) * Sin(CatDrawingView.Angle) + RelativeCoordinates(1) * Cos(CatDrawingView.Angle)) * CatDrawingView.Scale2
    
```vbscript
    End Sub
    
```

```