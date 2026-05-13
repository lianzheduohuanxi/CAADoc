---
title: "CAAPriChangeHole.CATScript"
category: "use-case"
module: "CAAScdPriUseCases"
tags: "["CAAScdPriUseCases", "CATIA", "CATIAHole", "CAAPriChangeHole"]"
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleSource.htm"
converted: "2026-05-11T17:31:51.200028"
---
tags: ["CAAScdPriUseCases", "CATIA", "CATIAHole", "CAAPriChangeHole"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleSource.htmmd"
converted: "2026-05-11T17:31:51.200028"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' ***********************************************************************
    '   Purpose:      Changes hole description
    '   Assumptions:   Looks for CAAPriChangeHole.CATPart in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R13
    ' ***********************************************************************
```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```
```

```vbscript
```vbscript
    Dim oPartDocument As PartDocument
```vbscript
```
```vbscript
```cpp
    Dim oCATIAFileSys
    Dim oFile As File
    Dim oTextSteam As TextStream
    Dim oUnit As String
    Dim oLine As String
    Dim oRow As Long
    Dim iArray(4, 12) As String
    Dim oReturn As String
    Dim iMessage As String
    Dim iRow As Long
    Dim oHole As Hole
    Dim iDelimiter As String
    Dim iHoleInSelection As Boolean
    Dim oParameters As Parameters
    Dim i as Long

```
```

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```cpp
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
```
```vbscript
```vbscript
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
```

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' ------------
    ' The string as delimiter between input in the text file
    ' ------------
```

```

    iDelimiter = "//"
```vbscript
```cpp
    ' ------------
    ' Get the CATIA file system
    ' ------------
```cpp
    Set oCATIAFileSys = CATIA.FileSystem
    ' ------------
```
    ' Get the file containing the hole parameters
    ' ------------
```cpp
    Set oFile = oCATIAFileSys.GetFile(sDocPath & "/online/CAAScdPriUseCases/macros/CAAPriChangeHole.txt")
    ' ------------
```
    ' Get the text stream
    ' ------------
```vbscript
    Set oTextSteam = oFile.OpenAsTextStream("ForReading")
    ' ------------
```
    ' Get the part document
    ' ------------
```cpp
    Set oPartDocument = CATIA.ActiveDocument
    ' ------------
```
    ' Test the selection content
    ' ------------
    If oPartDocument.Selection.Count = 0 Then
        ' ------------
        ' The selection content is empty, the macro ends
        ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' The selection content is empty, the macro ends
' ------------
```

```

```vbscript
        MsgBox "Please select the holes you wish to transform before running the macro.", vbOKOnly, "Warning"
    Else
```
```

```vbscript
```vbscript
```vbscript
        ' ------------
        ' The selection content is not empty
        ' Read the text file data unit
        ' ------------
```

```

        oLine = oTextSteam.ReadLine
        Select Case oLine
```

```vbscript
```vbscript
' ------------
```

oLine = oTextSteam.ReadLine
```vbscript
Select Case oLine
            Case "Millimeter"
```

                oUnit = 1
            Case "Inch"
                oUnit = 25.4
        End Select
        oRow = 0
```

```vbscript
```vbscript
```vbscript
        ' ------------
        ' Read the hole parameters
        ' ------------
        Do While oTextSteam.AtEndOfStream = False
```

```

            oLine = oTextSteam.ReadLine
            For i = 0 To 12
```vbscript
                If InStr(oLine, iDelimiter) > 0 Then
```

```

```vbscript
oLine = oTextSteam.ReadLine
For i = 0 To 12
```

If InStr(oLine, iDelimiter) > 0 Then
```vbscript
                    iArray(oRow, i) = Left(oLine, InStr(oLine, iDelimiter) - 1)
                    oLine = Mid(oLine, InStr(oLine, iDelimiter) + 2)
```

                Else
                    iArray(oRow, i) = oLine
```vbscript
                End If
```vbscript
```vbscript
            Next
            iMessage = iMessage & Chr(10) & iArray(oRow, 0) & " " & iArray(oRow, 1)
```

```

            oRow = oRow + 1
        Loop
        oTextSteam.Close
```

```vbscript
```vbscript
```vbscript
        ' ------------
        ' Get the description you wish, by default pre-select the first description
        ' ------------
```

```

        iMessage = "Please select the hole decription you wish to apply:" & iMessage
        oReturn = InputBox(iMessage, "Hole Description", iArray(1, 0))
```vbscript
```vbscript
        If oReturn = "" Then
            ' ------------
            ' No selection, the macro ends
            ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' No selection, the macro ends
' ------------
```

```

            Exit Sub
        Else
```vbscript
            Select Case oReturn
                Case "A"
```

                    iRow = 1
                Case "B"
                    iRow = 2
                Case "C"
                    iRow = 3
                Case "D"
                    iRow = 4
```

```vbscript
```vbscript
```vbscript
                ' ------------
                ' Invalid selection, the macro ends
                ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Invalid selection, the macro ends
' ------------
```

```

                Case Else
                    Exit Sub
            End Select
```

```vbscript
```vbscript
```vbscript
            ' ------------
            ' Loop on the selection content, we expect to find a hole
            ' ------------
```

```

            iHoleInSelection = True
            Do While iHoleInSelection = True
```vbscript
```cpp
                iHoleInSelection = CatObjectExistsInSelection(oPartDocument.Selection, "CATIAHole", oHole)
                If iHoleInSelection = True Then
                    ' ------------
                    ' There is a hole object in the selection
                    ' ------------
                    ' Get the hole limit
                    ' ------------
```

```

                    Select Case iArray(iRow, 5)
```

```vbscript
```vbscript
```vbscript
' Get the hole limit
' ------------
```

```

```vbscript
Select Case iArray(iRow, 5)
                        Case "UpToNext"
```

                            oHole.BottomLimit.LimitMode = catUpThruNextLimit
```

```vbscript
```vbscript
```vbscript
                            ' ------------
                            ' Update the part when set the hole limit to "UpToNext"
                            ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Update the part when set the hole limit to "UpToNext"
' ------------
```

```

                            oPartDocument.Part.Update
                        Case Else
                            oHole.BottomLimit.LimitMode = catOffsetLimit
                            oHole.BottomLimit.Dimension.Value = CDbl(iArray(iRow, 5)) * oUnit
                    End Select
```

```vbscript
```vbscript
```vbscript
                    ' ------------
                    ' Get the hole diameter and its tolerances
                    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Get the hole diameter and its tolerances
' ------------
```

```

                    oHole.Diameter.Value = CDbl(iArray(iRow, 2))
                    oHole.Diameter.MaximumTolerance = (CDbl(iArray(iRow, 3)) - CDbl(iArray(iRow, 2))) * oUnit
                    oHole.Diameter.MinimumTolerance = (CDbl(iArray(iRow, 4)) - CDbl(iArray(iRow, 2))) * oUnit
```vbscript
                    Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
```
```

```vbscript
```vbscript
```vbscript
                    ' ------------
```vbscript
                    ' Set the hole description parameter
                    ' ------------
```
                    If ParameterExists("Hole_Description", oParameters) = True Then
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
' Set the hole description parameter
' ------------
```
If ParameterExists("Hole_Description", oParameters) = True Then
```

```

                        oParameters.Item("Hole_Description").ValuateFromString (iArray(iRow, 0))
                    Else
                        oParameters.CreateString "Hole_Description", iArray(iRow, 0)
                    End If
```

```vbscript
```vbscript
```vbscript
                    ' ------------
                    ' Get the hole type
                    ' ------------
```

```

                    Select Case iArray(iRow, 1)
```

```vbscript
```vbscript
```vbscript
' Get the hole type
' ------------
```

```

```vbscript
Select Case iArray(iRow, 1)
                        Case "Simple"
                            oHole.Type = catSimpleHole
                        Case "Counterbored"
                            oHole.Type = catCounterboredHole
```

                            oHole.HeadDiameter.Value = CDbl(iArray(iRow, 9)) * oUnit
                            oHole.HeadDepth.Value = CDbl(iArray(iRow, 12)) * oUnit
                            oHole.HeadDiameter.MaximumTolerance = (CDbl(iArray(iRow, 10)) - CDbl(iArray(iRow, 9))) * oUnit
                            oHole.HeadDiameter.MinimumTolerance = (CDbl(iArray(iRow, 11)) - CDbl(iArray(iRow, 9))) * oUnit
                    End Select
```

```vbscript
```vbscript
```vbscript
                    ' ------------
                    ' Get the hole thread definition
                    ' ------------
```

```

                    Select Case iArray(iRow, 6)
```

```vbscript
```vbscript
```vbscript
' Get the hole thread definition
' ------------
```

```

```vbscript
Select Case iArray(iRow, 6)
                        Case "Yes"
                            If oHole.Diameter.Value < oHole.ThreadDiameter.Value And oHole.BottomLimit.Dimension.Value > oHole.ThreadDepth.Value Then
```

```

```vbscript
```vbscript
```vbscript
                                ' ------------
                                ' Update the part when hole diameter is smaller than tread diameter
                                ' and hole limit is greater than thread depth, before apply new values
                                ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' Update the part when hole diameter is smaller than tread diameter
' and hole limit is greater than thread depth, before apply new values
' ------------
```

```

                                oPartDocument.Part.Update
                            End If
```vbscript
                            oHole.ThreadingMode = catThreadedHoleThreading
```

                            oHole.ThreadDiameter.Value = CDbl(iArray(iRow, 7)) * oUnit
                            oHole.ThreadDepth.Value = CDbl(iArray(iRow, 8)) * oUnit
```vbscript
                        Case "No"
                            oHole.ThreadingMode = catSmoothHoleThreading
                    End Select
```

```

```vbscript
```vbscript
```vbscript
                    ' ------------
                    ' Update the part
                    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Update the part
' ------------
```

```

                    oPartDocument.Part.Update
                End If
            Loop
        End If
```vbscript
```vbscript
    End If

```

```

```

```vbscript
```vbscript
    End Sub

End Sub
    Private Function CatObjectExistsInSelection(CatSelection As Selection, CatObjectName As String, CatObject As Object) As Boolean

```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Define wether an specific object exists in the selection or not
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Define wether an specific object exists in the selection or not
' ------------
```

```

```vbscript
    On Error Resume Next
```
```

```vbscript
```vbscript
    Set CatObject = CatSelection.FindObject(CatObjectName)
```vbscript
```
```vbscript
    CatObjectExistsInSelection = (Err.Number = 0)
    Err.Clear

```

```

```

```vbscript
```vbscript
    End Function

End Function
    Private Function ParameterExists(ItemIndex As String, ItemCollection As Object) As Boolean

```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Define wether an parameter exists in a collection or not
    ' ------------
```

```

```

```vbscript
```vbscript
    Dim TmpItem As Variant
    On Error Resume Next
    Set TmpItem = ItemCollection.Item(ItemIndex)
```vbscript
```
```vbscript
    ParameterExists = (Err.Number = 0)
    Err.Clear

```

```

```

```vbscript
```vbscript
    End Function

```
```
