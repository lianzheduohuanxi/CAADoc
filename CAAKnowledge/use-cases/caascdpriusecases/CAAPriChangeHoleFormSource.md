---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CATIAHole", "CATIA", "CAAPriChangeHoleForm", "CAAPriChangeHole", "CAAScdPriUseCases", "CAAPriChangeHoleVBA"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleFormSource.htm"
converted: "2026-05-11T11:27:02.719353"
---

Option Explicit

' COPYRIGHT DASSAULT SYSTEMES 2004

' ***********************************************************************
'   Purpose:      Changes hole description
'   Assumtions:   Looks for CAAPriChangeHoleVBA.htm in the DocView
'   Author:
'   Languages:    MS VBA
'   Locales:      English
'   CATIA Level:  V5R13
' ***********************************************************************

Private oUnit As Double
 
Private Sub cmdOk_Click()

Dim oHole As Hole
Dim iRow As Long
Dim iHoleInSelection As Boolean
Dim oParameters As Parameters

' ------------
' Get the description you wish, by default pre-select the first description
' ------------
iRow = mfgDescription.RowSel
frmCAAPriChangeHole.Hide
iHoleInSelection = True
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
            Case "UpToNext"
                oHole.BottomLimit.LimitMode = catUpThruNextLimit
                ' ------------
                ' Update the part when set the hole limit to "UpToNext"
                ' ------------
                oPartDocument.Part.Update
            Case Else
                oHole.BottomLimit.LimitMode = catOffsetLimit
                oHole.BottomLimit.Dimension.Value = CDbl(mfgDescription.TextMatrix(iRow, 5)) * oUnit
        End Select
        ' ------------
        ' Get the hole diameter and its tolerances
        ' ------------
        oHole.Diameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 2))
        oHole.Diameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 3)) - CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
        oHole.Diameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 4)) - CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
        Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
        ' ------------
        ' Set the hole description parameter
        ' ------------
        If ParameterExists("Hole_Description", oParameters) = True Then
            oParameters.Item("Hole_Description").ValuateFromString (mfgDescription.TextMatrix(iRow, 0))
        Else
            oParameters.CreateString "Hole_Description", mfgDescription.TextMatrix(iRow, 0)
        End If
        ' ------------
        ' Get the hole type
        ' ------------
        Select Case mfgDescription.TextMatrix(iRow, 1)
            Case "Simple"
                oHole.Type = catSimpleHole
            Case "Counterbored"
                oHole.Type = catCounterboredHole
                oHole.HeadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 9)) * oUnit
                oHole.HeadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 12)) * oUnit
                oHole.HeadDiameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 10)) - CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
                oHole.HeadDiameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 11)) - CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
        End Select
        ' ------------
        ' Get the hole thread definition
        ' ------------
        Select Case mfgDescription.TextMatrix(iRow, 6)
            Case "Yes"
                If oHole.Diameter.Value < oHole.ThreadDiameter.Value And oHole.BottomLimit.Dimension.Value > oHole.ThreadDepth.Value Then
                    ' ------------
                    ' Update the part when hole diameter is smaller than tread diameter
                    ' and hole limit is greater than thread depth, before apply new values
                    ' -----------
                    oPartDocument.Part.Update
                End If
                oHole.ThreadingMode = catThreadedHoleThreading
                oHole.ThreadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 7)) * oUnit
                oHole.ThreadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 8)) * oUnit
            Case "No"
                oHole.ThreadingMode = catSmoothHoleThreading
        End Select
        ' ------------
        ' Update the part
        ' ------------
        oPartDocument.Part.Update
    End If
Loop

Unload Me
    
End Sub

Private Sub cmdCancel_Click()

' ------------
' Unload the form
' ------------
Unload Me

End Sub

Private Sub UserForm_Initialize()

Dim oCATIAFileSys
Dim oFile As File
Dim oTextSteam As TextStream
Dim oUnit As Double
Dim oLine As String
Dim iArray() As String
Dim oRow As Long
Dim iDelimiter As String

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
    Case "Millimeter"
        oUnit = 1
    Case "Inch"
        oUnit = 25.4
End Select
oRow = 0
' ------------
' Read the hole parameters
' ------------
Do While oTextSteam.AtEndOfStream = False
    oLine = oTextSteam.ReadLine
    iArray = Split(oLine, iDelimiter)
    For i = 0 To 12
        mfgDescription.TextMatrix(oRow, i) = iArray(i)
    Next i
    oRow = oRow + 1
Loop
oTextSteam.Close
cmdOk.Enabled = True

End Sub



```vbscript
Option Explicit

' COPYRIGHT DASSAULT SYSTEMES 2004

' ***********************************************************************
'   Purpose:      Changes hole description
'   Assumtions:   Looks for CAAPriChangeHoleVBA.htm in the DocView
'   Author:
'   Languages:    MS VBA
'   Locales:      English
'   CATIA Level:  V5R13
' ***********************************************************************

Private oUnit As Double
 
Private Sub cmdOk_Click()

Dim oHole As Hole
Dim iRow As Long
Dim iHoleInSelection As Boolean
Dim oParameters As Parameters

' ------------
' Get the description you wish, by default pre-select the first description
' ------------
iRow = mfgDescription.RowSel
frmCAAPriChangeHole.Hide
iHoleInSelection = True
' ------------
' Loop on the selection content, we expect to find a hole
' ------------
Do While iHoleInSelection = True
    iHoleInSelection = CatObjectExistsInSelection(oPartDocument.Selection, &quot;CATIAHole&quot;, oHole)
    If iHoleInSelection = True Then
        ' ------------
        ' There is a hole object in the selection
        ' ------------
        ' Get the hole limit
        ' ------------
        Select Case mfgDescription.TextMatrix(iRow, 5)
            Case &quot;UpToNext&quot;
                oHole.BottomLimit.LimitMode = catUpThruNextLimit
                ' ------------
                ' Update the part when set the hole limit to &quot;UpToNext&quot;
                ' ------------
                oPartDocument.Part.Update
            Case Else
                oHole.BottomLimit.LimitMode = catOffsetLimit
                oHole.BottomLimit.Dimension.Value = CDbl(mfgDescription.TextMatrix(iRow, 5)) * oUnit
        End Select
        ' ------------
        ' Get the hole diameter and its tolerances
        ' ------------
        oHole.Diameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 2))
        oHole.Diameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 3)) - CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
        oHole.Diameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 4)) - CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
        Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
        ' ------------
        ' Set the hole description parameter
        ' ------------
        If ParameterExists(&quot;Hole_Description&quot;, oParameters) = True Then
            oParameters.Item(&quot;Hole_Description&quot;).ValuateFromString (mfgDescription.TextMatrix(iRow, 0))
        Else
            oParameters.CreateString &quot;Hole_Description&quot;, mfgDescription.TextMatrix(iRow, 0)
        End If
        ' ------------
        ' Get the hole type
        ' ------------
        Select Case mfgDescription.TextMatrix(iRow, 1)
            Case &quot;Simple&quot;
                oHole.Type = catSimpleHole
            Case &quot;Counterbored&quot;
                oHole.Type = catCounterboredHole
                oHole.HeadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 9)) * oUnit
                oHole.HeadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 12)) * oUnit
                oHole.HeadDiameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 10)) - CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
                oHole.HeadDiameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 11)) - CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
        End Select
        ' ------------
        ' Get the hole thread definition
        ' ------------
        Select Case mfgDescription.TextMatrix(iRow, 6)
            Case &quot;Yes&quot;
                If oHole.Diameter.Value &lt; oHole.ThreadDiameter.Value And oHole.BottomLimit.Dimension.Value &gt; oHole.ThreadDepth.Value Then
                    ' ------------
                    ' Update the part when hole diameter is smaller than tread diameter
                    ' and hole limit is greater than thread depth, before apply new values
                    ' -----------
                    oPartDocument.Part.Update
                End If
                oHole.ThreadingMode = catThreadedHoleThreading
                oHole.ThreadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 7)) * oUnit
                oHole.ThreadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 8)) * oUnit
            Case &quot;No&quot;
                oHole.ThreadingMode = catSmoothHoleThreading
        End Select
        ' ------------
        ' Update the part
        ' ------------
        oPartDocument.Part.Update
    End If
Loop

Unload Me
    
End Sub

Private Sub cmdCancel_Click()

' ------------
' Unload the form
' ------------
Unload Me

End Sub

Private Sub UserForm_Initialize()

Dim oCATIAFileSys
Dim oFile As File
Dim oTextSteam As TextStream
Dim oUnit As Double
Dim oLine As String
Dim iArray() As String
Dim oRow As Long
Dim iDelimiter As String

' ------------
' The string as delimiter between input in the text file
' ------------
iDelimiter = &quot;\\&quot;
' ------------
' Get the CATIA file system
' ------------
Set oCATIAFileSys = CATIA.FileSystem
' ------------
' Get the file containing the hole parameters
' ------------
Set oFile = oCATIAFileSys.GetFile(sDocPath &amp; &quot;\online\CAAScdPriUseCases\macros\CAAPriChangeHole.txt&quot;)
' ------------
' Get the text stream
' ------------
Set oTextSteam = oFile.OpenAsTextStream(&quot;ForReading&quot;)
oLine = oTextSteam.ReadLine
Select Case oLine
    Case &quot;Millimeter&quot;
        oUnit = 1
    Case &quot;Inch&quot;
        oUnit = 25.4
End Select
oRow = 0
' ------------
' Read the hole parameters
' ------------
Do While oTextSteam.AtEndOfStream = False
    oLine = oTextSteam.ReadLine
    iArray = Split(oLine, iDelimiter)
    For i = 0 To 12
        mfgDescription.TextMatrix(oRow, i) = iArray(i)
    Next i
    oRow = oRow + 1
Loop
oTextSteam.Close
cmdOk.Enabled = True

End Sub
```