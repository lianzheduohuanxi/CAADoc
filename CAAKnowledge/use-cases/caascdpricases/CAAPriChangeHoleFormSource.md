---
title: "CAAPriChangeHoleForm.frm"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriChangeHole", "CATIAHole", "CAAPriChangeHoleForm", "CAAPriChangeHoleVBA"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleFormSource.md"
converted: "2026-05-11T17:31:51.192048"
---

    Option Explicit
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' ***********************************************************************
    '   Purpose:      Changes hole description
    '   Assumtions:   Looks for CAAPriChangeHoleVBA.md in the DocView
    '   Author:
    '   Languages:    MS VBA
    '   Locales:      English
    '   CATIA Level:  V5R13
    ' ***********************************************************************
    
    Private oUnit As Double
     
    Private Sub cmdOk_Click()
```

    
```vbscript
    Dim oHole As Hole
    Dim iRow As Long
    Dim iHoleInSelection As Boolean
    Dim oParameters As Parameters
```vbscript
    ' ------------
    ' Get the description you wish, by default pre-select the first description
    ' ------------
    iRow = mfgDescription.RowSel
```

    frmCAAPriChangeHole.Hide
    iHoleInSelection = True
```vbscript
    ' ------------
    ' Loop on the selection content, we expect to find a hole
    ' ------------
    Do While iHoleInSelection = True
        iHoleInSelection = CatObjectExistsInSelection(oPartDocument.Selection, "CATIAHole", oHole)
        If iHoleInSelection = True Then
            ' ------------
            ' There is a hole object in the selection
            ' ------------
            ' Get the hole limit
            ' ------------
            Select Case mfgDescription.TextMatrix(iRow, 5)
```

                Case "UpToNext"
                    oHole.BottomLimit.LimitMode = catUpThruNextLimit
```vbscript
                    ' ------------
                    ' Update the part when set the hole limit to "UpToNext"
                    ' ------------
```

                    oPartDocument.Part.Update
                Case Else
                    oHole.BottomLimit.LimitMode = catOffsetLimit
                    oHole.BottomLimit.Dimension.Value = CDbl(mfgDescription.TextMatrix(iRow, 5)) * oUnit
            End Select
```vbscript
            ' ------------
            ' Get the hole diameter and its tolerances
            ' ------------
```

            oHole.Diameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 2))
            oHole.Diameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 3)) - CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
            oHole.Diameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 4)) - CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
            Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
```vbscript
            ' ------------
            ' Set the hole description parameter
            ' ------------
            If ParameterExists("Hole_Description", oParameters) = True Then
```

                oParameters.Item("Hole_Description").ValuateFromString (mfgDescription.TextMatrix(iRow, 0))
            Else
                oParameters.CreateString "Hole_Description", mfgDescription.TextMatrix(iRow, 0)
            End If
```vbscript
            ' ------------
            ' Get the hole type
            ' ------------
            Select Case mfgDescription.TextMatrix(iRow, 1)
```

                Case "Simple"
                    oHole.Type = catSimpleHole
                Case "Counterbored"
                    oHole.Type = catCounterboredHole
                    oHole.HeadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 9)) * oUnit
                    oHole.HeadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 12)) * oUnit
                    oHole.HeadDiameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 10)) - CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
                    oHole.HeadDiameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 11)) - CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
            End Select
```vbscript
            ' ------------
            ' Get the hole thread definition
            ' ------------
            Select Case mfgDescription.TextMatrix(iRow, 6)
```

                Case "Yes"
                    If oHole.Diameter.Value < oHole.ThreadDiameter.Value And oHole.BottomLimit.Dimension.Value > oHole.ThreadDepth.Value Then
```vbscript
                        ' ------------
                        ' Update the part when hole diameter is smaller than tread diameter
                        ' and hole limit is greater than thread depth, before apply new values
                        ' -----------
```

                        oPartDocument.Part.Update
                    End If
                    oHole.ThreadingMode = catThreadedHoleThreading
                    oHole.ThreadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 7)) * oUnit
                    oHole.ThreadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 8)) * oUnit
                Case "No"
                    oHole.ThreadingMode = catSmoothHoleThreading
            End Select
```vbscript
            ' ------------
            ' Update the part
            ' ------------
```

            oPartDocument.Part.Update
        End If
    Loop
    
```

    Unload Me
        
```vbscript
    End Sub
    
```

    Private Sub cmdCancel_Click()
```vbscript
    ' ------------
    ' Unload the form
    ' ------------
```

    Unload Me
    
```vbscript
    End Sub
    
```

    Private Sub UserForm_Initialize()
    
```vbscript
    Dim oCATIAFileSys
    Dim oFile As File
    Dim oTextSteam As TextStream
    Dim oUnit As Double
    Dim oLine As String
    Dim iArray() As String
    Dim oRow As Long
    Dim iDelimiter As String
```vbscript
    ' ------------
    ' The string as delimiter between input in the text file
    ' ------------
    iDelimiter = "\\"
    ' ------------
    ' Get the CATIA file system
    ' ------------
    Set oCATIAFileSys = CATIA.FileSystem
    ' ------------
    ' Get the file containing the hole parameters
    ' ------------
    Set oFile = oCATIAFileSys.GetFile(sDocPath & "\online\CAAScdPriUseCases\macros\CAAPriChangeHole.txt")
    ' ------------
    ' Get the text stream
    ' ------------
    Set oTextSteam = oFile.OpenAsTextStream("ForReading")
    oLine = oTextSteam.ReadLine
    Select Case oLine
```

        Case "Millimeter"
            oUnit = 1
        Case "Inch"
            oUnit = 25.4
    End Select
    oRow = 0
```vbscript
    ' ------------
    ' Read the hole parameters
    ' ------------
    Do While oTextSteam.AtEndOfStream = False
        oLine = oTextSteam.ReadLine
        iArray = Split(oLine, iDelimiter)
        For i = 0 To 12
```

            mfgDescription.TextMatrix(oRow, i) = iArray(i)
        Next i
        oRow = oRow + 1
    Loop
    oTextSteam.Close
    cmdOk.Enabled = True
    
```

```vbscript
    End Sub
    
```

```