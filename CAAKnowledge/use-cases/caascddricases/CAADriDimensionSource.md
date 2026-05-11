---
```vbscript
title: "CAADriDimension.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CATIA", "CAADriDimension"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDimensionSource.htm"
converted: "2026-05-11T17:31:51.059350"
```

---
```vbscript
    Dim Language as String
    Language="VBScript"

```

```vbscript
    '---------------------------------------------------------------------------
    'COPYRIGHT DASSAULT SYSTEMES 2002
    ' ****************************************************************************
    '
    ' Purpose:       To analyze a subset of dimensions pointed by text leaders
    '                in the active drafting document.
    '                That macro checks all dimensions pointed by text leader elements.
    '                If dimensions have a wrong display (tolerances or wrong frame)
    '                text leader object is highlighted.
    '
    ' Assumptions:   A Drafting document should be active
    '
    ' Author: 
    ' Languages:     VBScript
    ' Version:       V5R10
    ' Locales:       English 
    ' CATIA Level: V5R10 
    '
    ' ****************************************************************************
    '---------------------------------------------------------------------------
```

    Sub CATMain()

```vbscript
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
        CATIA.DisplayFileAlerts = False
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    '---------------------------------------------------------------------------
    '1/ Read active CATDrawing Document
    '---------------------------------------------------------------------------
    Dim DrwDoc As DrawingDocument
    Set DrwDoc = CATIA.ActiveDocument
    ' Get Selection Object and clear it
    Dim DrwSelect As Selection
    Set DrwSelect = DrwDoc.Selection
    ' Variables declaration
    Dim ElemDispatch As CATBaseDispatch
    Dim NomObj As String
    Dim numsheet As Long
    Dim numview As Long
    Dim numtxt As Long
    Dim numleader As Long
    '---------------------------------------------------------------------------
    '2/ Scan all the sheet of the current drawing (Included detail sheet)
    '---------------------------------------------------------------------------
    Dim DrwSheets As DrawingSheets
    Set DrwSheets = DrwDoc.Sheets
    Dim CurrentSheet As DrawingSheet
    'Read the current sheet to restore it at the end of the macro
    Dim SheetToRestore As DrawingSheet
    Set SheetToRestore = DrwSheets.ActiveSheet
```

```vbscript
    For numsheet = 1 To DrwSheets.Count

       Set CurrentSheet = DrwSheets.Item(numsheet)
       ' Active Currentsheet
       CurrentSheet.Activate
       ' Clear the selection
       DrwSelect.Clear

       Dim DrwViews As DrawingViews
       Set DrwViews = CurrentSheet.Views
```

```vbscript
       'Read the current view to restore it at the end of the macro
       Dim ViewToRestore As DrawingView
       Set ViewToRestore = DrwViews.ActiveView
    '---------------------------------------------------------------------------
    '3/ Scan all the view of the current sheet
    '---------------------------------------------------------------------------
       Dim CurrentView As DrawingView
```

```vbscript
       For numview = 1 To DrwViews.Count

          Set CurrentView = DrwViews.Item(numview)
          'Active the current view
          CurrentView.Activate
```

```vbscript
    '---------------------------------------------------------------------------
    '4/ Scan all the texts of the current view
    '---------------------------------------------------------------------------

          Dim Texts As DrawingTexts
          Set Texts = CurrentView.Texts
```

```vbscript
          For numtxt = 1 To Texts.Count

             Dim CurrentText As DrawingText
             Set CurrentText = Texts.Item(numtxt)
```

```vbscript
    '---------------------------------------------------------------------------
    '5/ Scan all the leaders of the current text
    '---------------------------------------------------------------------------

             Dim Leaders As DrawingLeaders
             Set Leaders = CurrentText.Leaders
```

```vbscript
             For numleader = 1 To Leaders.Count
                Dim CurrentLeader As DrawingLeader
                Set CurrentLeader = Leaders.Item(numleader)
                ' Manage error on HeadTarget method when
                ' no element is pointed by the text leader.
                On Error Resume Next
```

```vbscript
                ' Get object pointed on the leader
                Set ElemDispatch = Nothing
                Set ElemDispatch = CurrentLeader.HeadTarget
                NomObj = TypeName(ElemDispatch)
    '------------------------------------------------------------------------------
    '6/ Check tolerances and the frame type of the dimension pointed by text leader
    '------------------------------------------------------------------------------
                ' A dimension is pointed by text leader
                If NomObj = "DrawingDimension" Then
                   ' Get the dimension object
                   Dim PointedDim As DrawingDimension
                   Set PointedDim = ElemDispatch
                   ' Read dimension tolerances
                   Dim oTolType As Long
                   Dim oDisplayMode As Long
                   Dim oTolName As String
                   Dim oUpTolS As String
                   Dim oLowTolS As String
                   Dim oUpTolD As Double
                   Dim oLowTolD As Double
```

```vbscript
Dim oLowTolS As String
Dim oUpTolD As Double
Dim oLowTolD As Double
                   PointedDim.GetTolerances oTolType, oTolName, oUpTolS, oLowTolS, oUpTolD, oLowTolD, oDisplayMode
```

```vbscript
                   ' Read dimension frame type
                   Dim TypeFrame As CatDimFrame
                   TypeFrame = PointedDim.ValueFrame
    '---------------------------------------------------------------------------
    '7/ Change the visualization of the text leader linked to that dimension
    '---------------------------------------------------------------------------
                   ' If dimension does not respect the criteria text leader object is highlighted
                   If oTolType <> 0 Or TypeFrame <> catFraRectangle Then
```

```vbscript
'---------------------------------------------------------------------------
' If dimension does not respect the criteria text leader object is highlighted
If oTolType <> 0 Or TypeFrame <> catFraRectangle Then
                      DrwSelect.Add CurrentText
                      DrwSelect.VisProperties.SetRealColor 255, 0, 0, 0
                      DrwSelect.VisProperties.SetRealWidth 6, 1
                   End If

```

```vbscript
                End If
             Next

```

```vbscript
End If
Next
          Next
        'Restore the view
        ViewToRestore.Activate

       Next

```

```vbscript
     Next 
    'Restore the Drawing Document sheet
    SheetToRestore.Activate

```

    End Sub
