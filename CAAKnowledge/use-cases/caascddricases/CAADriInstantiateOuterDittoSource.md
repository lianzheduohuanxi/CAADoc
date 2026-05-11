---
```vbscript
title: "CAADriInstantiateOuterDitto.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriInstantiateOuterDitto", "CAADriInstantiateDittoTarget", "CAADriInstantiateDittoSource", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateOuterDittoSource.htm"
converted: "2026-05-11T17:31:51.092771"
```

---
tags: ["CAADriInstantiateOuterDitto", "CAADriInstantiateDittoTarget", "CAADriInstantiateDittoSource", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateOuterDittoSource.htm"
converted: "2026-05-11T17:31:51.092771"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2003
    ' ***********************************************************************
    '   Purpose:      This macro allows you to instantiate a ditto in
    '                 a view from a ditto in another document
    '   Author:
    '   Languages:   VBScript
    '   Locales:     English
    '   CATIA Level: V5R11
    ' ***********************************************************************
```

```

```

    Sub CATMain()
```vbscript
```vbscript
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution

```

```

```vbscript
        CATIA.DisplayFileAlerts = False
```

```vbscript
```vbscript
```vbscript
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
        ' Open the drawing document containing the existing ditto
        Dim oDrawingSource As DrawingDocument
        Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
```

```

```

                 "\online\CAAScdDriUseCases\samples\CAADriInstantiateDittoSource.CATDrawing")
```vbscript
```vbscript
```vbscript
        ' Retrieve the sheet containing the ditto to be copied
        Dim oSheetSource As DrawingSheet
        Set oSheetSource = oDrawingSource.Sheets.Item("Sheet.3")
        ' Retrieve the view containing the ditto to be copied
        Dim oViewSource As DrawingView
        Set oViewSource = oSheetSource.Views.Item("View.1")
        ' Retrieve the ditto
        Dim oDitto As DrawingComponent
        Set oDitto = oViewSource.Components.Item(1)
        ' Create an object of selection for the source document
        Dim oSelectionSource As Selection
        Set oSelectionSource = oDrawingSource.Selection
        ' Clear the selection
```

```

```

```vbscript
Dim oSelectionSource As Selection
```vbscript
```vbscript
Set oSelectionSource = oDrawingSource.Selection
' Clear the selection
```

```

        oSelectionSource.Clear
```vbscript
        ' Add the ditto to be duplicated in the selection
```

        oSelectionSource.Add oDitto
```vbscript
        ' Copy the view
```

        oSelectionSource.Copy
```vbscript
        ' Clear the selection
```

        oSelectionSource.Clear
```

```vbscript
```vbscript
```vbscript
        ' Open the drawing document where the ditto will be instantiated
        Dim oDrawingTarget As DrawingDocument
        Set oDrawingTarget = CATIA.Documents.Open(sDocPath & _
```

```

```

                 "\online\CAAScdDriUseCases\samples\CAADriInstantiateDittoTarget.CATDrawing")
```vbscript
Dim oDrawingTarget As DrawingDocument
```vbscript
```vbscript
Set oDrawingTarget = CATIA.Documents.Open(sDocPath & _
        CATIA.ActiveWindow.ActiveViewer.Reframe
```

```

```

```vbscript
```vbscript
```vbscript
        ' Retrieve the sheet where the ditto will be instantiated
        Dim oSheetTarget As DrawingSheet
        Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
```

```

```

```vbscript
```vbscript
```vbscript
' Retrieve the sheet where the ditto will be instantiated
Dim oSheetTarget As DrawingSheet
Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
```

```

        oSheetTarget.Activate
```

```vbscript
```vbscript
```vbscript
        ' Retrieve the view where the ditto will be instantiated
        Dim oViewTarget As DrawingView
        Set oViewTarget = oSheetTarget.Views.Item("View.3")
        ' Indicate the ditto location
        Dim ReturnStatus As String
        Dim iDittoCoordinates(1)
        Dim oDraw
        Set oDraw = oDrawingTarget
        ReturnStatus = oDraw.Indicate2D("Indicate the ditto location", iDittoCoordinates)
        ' Create an object of selection for the target document
        Dim oSelectionTarget As Selection
        Set oSelectionTarget = oDrawingTarget.Selection
        ' Clear the selection
```

```

```

```vbscript
Dim oSelectionTarget As Selection
```vbscript
```vbscript
Set oSelectionTarget = oDrawingTarget.Selection
' Clear the selection
```

```

        oSelectionTarget.Clear
```vbscript
        ' Add the view in the selection, where the ditto will be instantiated
```

        oSelectionTarget.Add oViewTarget
```vbscript
        ' Paste the clipboard
```

        oSelectionTarget.Paste
```vbscript
        ' Clear the selection
```

        oSelectionTarget.Clear
```

```vbscript
```vbscript
```vbscript
        ' Retrieve the drawing components collection of the target drawing view
        Dim o2DComponents As DrawingComponents
        Set o2DComponents = oViewTarget.Components
        ' Retrieve the ditto and define its location
        Dim o2DComponent As DrawingComponent
        Set o2DComponent = o2DComponents.Item("DrwDetail.1")
```

```

```

```vbscript
```vbscript
```vbscript
' Retrieve the ditto and define its location
Dim o2DComponent As DrawingComponent
Set o2DComponent = o2DComponents.Item("DrwDetail.1")
        o2DComponent.X = iDittoCoordinates(0)
        o2DComponent.Y = iDittoCoordinates(1)
```

```

```

```vbscript
```vbscript
```vbscript
        ' Retrieve the modifiable text of the ditto
        Dim oText As DrawingText
        Set oText = o2DComponent.GetModifiableObject(1)
        ' Modify the modifiable text value
        Dim ReturnValue As String
        ReturnValue = InputBox("Enter a value", "", "New Value For Text")
```

```

```

```vbscript
```vbscript
```vbscript
' Modify the modifiable text value
Dim ReturnValue As String
```

```

```

ReturnValue = InputBox("Enter a value", "", "New Value For Text")
```vbscript
```vbscript
        oText.Text = ReturnValue

```

```

```vbscript
```vbscript
```vbscript
        ' Clear the variables
        Set oText = Nothing
        Set o2DComponent = Nothing
        Set o2DComponents = Nothing
        Set oSelectionTarget = Nothing
        Set oDraw = Nothing
        Set oViewTarget = Nothing
        Set oSheetTarget = Nothing
        Set oDrawingTarget = Nothing
        Set oSelectionSource = Nothing
        Set oViewSource = Nothing
        Set oSheetSource = Nothing
        Set oDrawingSource = Nothing
```

```

```

```vbscript
    End Sub

```
