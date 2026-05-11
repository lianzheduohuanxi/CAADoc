---
```vbscript
title: "CAADriInstantiateInnerDitto.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriInstantiateInnerDitto", "CATIA", "CAADriInstantiateDittoSource", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateInnerDittoSource.htm"
converted: "2026-05-11T17:31:51.082294"
```

---
tags: ["CAADriInstantiateInnerDitto", "CATIA", "CAADriInstantiateDittoSource", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriInstantiateInnerDittoSource.htm"
converted: "2026-05-11T17:31:51.082294"
    Option Explicit

```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2003
    ' ***********************************************************************
    '   Purpose:      This macro allows you to instantiate a ditto in 
    '                      a view from a detail view
    '   Author: 
    '   Languages:   VBScript
    '   Locales:       English 
    '   CATIA Level: V5R11
    ' ***********************************************************************
```

    Sub CATMain()
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution

```vbscript
        CATIA.DisplayFileAlerts = False
```

```vbscript
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
        ' Open the drawing document
        Dim oDrawing As DrawingDocument
        Set oDrawing = CATIA.Documents.Open(sDocPath & _
```

                 "\online\CAAScdDriUseCases\samples\CAADriInstantiateDittoSource.CATDrawing")
```vbscript
        ' Retrieve the sheets collection of the drawing document
        Dim oSheets As DrawingSheets
        Set oSheets = oDrawing.Sheets
        ' Retrieve the sheet where the detail view will be instantiated
        Dim oSheet As DrawingSheet
        Set oSheet = oSheets.Item("Sheet.1")
        ' Retrieve the view where the detail view will be instantiated
        Dim oView As DrawingView
        Set oView = oSheet.Views.Item("View.3")
```

```vbscript
' Retrieve the view where the detail view will be instantiated
Dim oView As DrawingView
Set oView = oSheet.Views.Item("View.3")
        oView.Activate
```

```vbscript
        ' Retrieve the detail sheet containing the detail view to be instantiated
        Dim oDetailSheet As DrawingSheet
        Set oDetailSheet = oSheets.Item("Sheet.2 (Detail)")
        ' Retrieve the detail view to be instantiated
        Dim oDetailView As DrawingView
        Set oDetailView = oDetailSheet.Views.Item("DrwDetail.1")
        ' Indicate the ditto location
        Dim ReturnStatus As String
        Dim iDittoCoordinates(1)
        Dim oDraw
        Set oDraw = oDrawing
        ReturnStatus = oDraw.Indicate2D("Indicate the ditto location", iDittoCoordinates)
        ' Retrieve the drawing components collection of the target drawing view
        Dim o2DComponents As DrawingComponents
        Set o2DComponents = oView.Components
        ' Create the ditto
        Dim o2DComponent As DrawingComponent
        Set o2DComponent = o2DComponents.Add(oDetailView, iDittoCoordinates(0), iDittoCoordinates(1))
        ' Retrieve the modifiable text of the ditto
        Dim oText As DrawingText
        Set oText = o2DComponent.GetModifiableObject(1)
        ' Modify the modifiable text value
        Dim ReturnValue As String
        ReturnValue = InputBox( "Enter a value", "", "New Value For Text" )
```

```vbscript
' Modify the modifiable text value
Dim ReturnValue As String
ReturnValue = InputBox( "Enter a value", "", "New Value For Text" )
        oText.Text = ReturnValue
```

```vbscript
        ' Clear the variables
        Set oText = Nothing
        Set o2DComponent = Nothing
        Set o2DComponents = Nothing
        Set oDraw = Nothing
        Set oDetailView = Nothing
        Set oDetailSheet = Nothing
        Set oView = Nothing
        Set oSheet = Nothing
        Set oSheets = Nothing
        Set oDrawing = Nothing
```

    End Sub
