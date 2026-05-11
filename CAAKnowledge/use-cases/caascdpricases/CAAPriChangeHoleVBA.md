---
```vbscript
title: "Changing the Hole Parameters (catvba Version)"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriChangeHole", "CAAPriChangeHoleModule", "CATIAHole", "CAAPriChangeHoleForm"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleVBA.htm"
converted: "2026-05-11T17:31:51.207011"
```

---
## Part Design

|
## Changing the Hole Parameters (catvba Version)

* * *

 This macro is dedicated for Windows only, and it is the catvba version of [Changing the Hole Parameters](CAAPriChangeHole.md).
The macro is made of two files [CAAPriChangeHoleModule.bas](CAAPriChangeHoleModuleSource.md) which contains the starting procedure CATMain and [CAAPriChangeHoleForm.frm](CAAPriChangeHoleFormSource.md) which contains the dialog box and the procedure applying the new parameters.
This macro shows you how to change the parameters of selected holes (diameter, type, thread definition, etc) from data contained in a text file. Data unit is take into account: Millimeter or Inches.
This macro allows you to define:

  * T**he limit type: "Up to next" or "Offset" onl**y.
  * **Maximum and minimum** tolerances of the hole diameter.
  * "Simple" or "Counterbored" as hole type only, m**aximum and minimum** tolerances for the spot facing diameter for counterbored holes.
  * Whether the hole is threaded or not, and its **thread depth** if threaded.
  * A parameter named "Hole_Description" where its value is a letter corresponding to the applied parameters.

It modifies the _Hole_ object from its methods and properties, and updates the part.
---|---

  * Open the [CAAPriChangeHole.CATPart](samples/CAAPriChangeHole.CATPart) document.
  * Reference in the application the catvba project: [CAAPriChangeHole.catvba](macros/CAAPriChangeHole.catvba).
  * The text file [CAAPriChangeHole.txt](macros/CAAPriChangeHole.txt) is located in the CAAScdPriUseCases module.

 CAAPriChangeHole includes the following steps:

CAAPriChangeHole includes the following steps:
  1. Prolog
  2. Reading the Hole Parameters
  3. Looking for the Hole Object in the Selection
  4. Applying the Hole Parameters

#### Prolog

3. Looking for the Hole Object in the Selection
4. Applying the Hole Parameters
Load the CAAPriChangeHole.CATPart that contains three holes. ![](images/CAAPriChangeHole01.gif) Select one or several holes as shown. Selection is allowed from the specification tree or from the geometry. ![](images/CAAPriChangeHole02.gif) Run the macro.

    ...
```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the part document
    ' ------------
```

```

```

```vbscript
    Set oPartDocument = CATIA.ActiveDocument
```

    ...

---

Once the macro has been started, the `oCATIAFileSys`, `oFile`, `oTextSteam` and `oPartDocument `variables are declared to receive the instance of the CATIA file system, the file, the text stream and the part document.
#### Reading the Hole Parameters

    ...
Once the macro has been started, the `oCATIAFileSys`, `oFile`, `oTextSteam` and `oPartDocument `variables are declared to receive the instance of the CATIA file system, the file, the text stream and the part document.
```vbscript
    If oPartDocument.Selection.Count = 0 Then

```

```vbscript
```vbscript
```vbscript
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

        MsgBox "Select the holes you wish to transform before running the macro.", vbOKOnly, "Warning"
```

    ...

---

The selection content is tested, if empty a warning message appears and the macro ends:

![](images/CAAPriChangeHole06.gif)

    ...
    Else
```vbscript
```vbscript
```vbscript
        ' ------------
        ' The selection content is not empty
        ' Show the dialog box
        ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' The selection content is not empty
' Show the dialog box
' ------------
```

```

        frmCAAPriChangeHole.Show
    End If
```

    ...

---

Otherwise, the macro shows the dialog box.

    ...
```vbscript
```vbscript
```vbscript
    ' ------------
    ' The string as delimiter between input in the text file
    ' ------------
```

```

    iDelimiter = "\\"
```vbscript
```vbscript
    ' ------------
    ' Get the CATIA file system
    ' ------------
```

```

```

```vbscript
    Set oCATIAFileSys = CATIA.FileSystem
```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the file containing the hole parameters
    ' ------------
    Set oFile = oCATIAFileSys.GetFile(sDocPath & "\online\CAAScdPriUseCases\macros\CAAPriChangeHole.txt")
    ' ------------
    ' Get the text stream
    ' ------------
    Set oTextSteam = oFile.OpenAsTextStream("ForReading")
```

```

    oLine = oTextSteam.ReadLine
    Select Case oLine
```

```vbscript
Set oTextSteam = oFile.OpenAsTextStream("ForReading")
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
        iArray = Split(oLine, iDelimiter)
```vbscript
        For i = 0 To 12
```

```

```vbscript
oLine = oTextSteam.ReadLine
iArray = Split(oLine, iDelimiter)
```vbscript
For i = 0 To 12
```

            mfgDescription.TextMatrix(oRow, i) = iArray(i)
        Next i
        oRow = oRow + 1
    Loop
    oTextSteam.Close
    cmdOk.Enabled = True
```

    ...

---

The macro reads the hole parameters contained in the CAAPriChangeHole.txt file:

  * The first line contains the unit name
  * The second line contains the name of each field.
  * Next lines contain a set of hole parameters per line.

The unit ratio is stored in `oUnit` (macro unit is always millimeter!). The file is read until its end, the field names and all set hole parameters are stored in a MSFlexGrid object: `mfgDescription`. Then, the OK button is enabled.

A dialog box appears and asks you to select the desired hole parameters (field names and full hole parameters are displayed).
"A" description is selected by default. select the desired parameters line.

![](images/CAAPriChangeHole07.gif)
#### Looking for the Hole Object in the Selection

    ...
```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the description you wish, by default pre-select the first description
    ' ------------
```

```

    iRow = mfgDescription.RowSel
```

```vbscript
```vbscript
```vbscript
' Get the description you wish, by default pre-select the first description
' ------------
```

```

iRow = mfgDescription.RowSel
    CAAPriChangeHoleForm.Hide
```

    ...

---

When the OK button is clicked, the selected row description is retrieved in `iRow` , and the dialog box is hidden.

    ...
When the OK button is clicked, the selected row description is retrieved in `iRow` , and the dialog box is hidden.
    iHoleInSelection = True

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Loop on the selection content, we expect to find a hole
    ' ------------
```

```

```

    Do While iHoleInSelection = True
```vbscript
```vbscript
        iHoleInSelection = CatObjectExistsInSelection(oPartDocument.Selection, "CATIAHole", oHole)
        If iHoleInSelection = True Then

```

```

    ...

---

On each hole object found in the selection, the desired hole parameters are applied.
#### Applying the Hole Parameters

    ...
```vbscript
```vbscript
```vbscript
            ' ------------
            ' Get the hole limit
            ' ------------
```

```

            Select Case mfgDescription.TextMatrix(iRow, 5)
```

```vbscript
```vbscript
```vbscript
' Get the hole limit
' ------------
```

```

```vbscript
Select Case mfgDescription.TextMatrix(iRow, 5)
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
                    oHole.BottomLimit.Dimension.Value = CDbl(mfgDescription.TextMatrix(iRow, 5)) * oUnit
            End Select
```

    ...

---

The hole limit is applied.

    ...
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

            oHole.Diameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 2))
            oHole.Diameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 3)) - _
                                               CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
            oHole.Diameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 4)) - _
                                               CDbl(mfgDescription.TextMatrix(iRow, 2))) * oUnit
```

    ...

---

The hole diameter and its tolerances are applied.

    ...
```vbscript
            Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
```

```vbscript
```vbscript
```vbscript
            ' ------------
            ' Set the hole parameter
            ' ------------
            If ParameterExists("Hole_Description", oParameters) = True Then
```

```

```

```vbscript
```vbscript
```vbscript
' Set the hole parameter
' ------------
If ParameterExists("Hole_Description", oParameters) = True Then
```

```

                oParameters.Item("Hole_Description").ValuateFromString (mfgDescription.TextMatrix(iRow, 0))
            Else
                oParameters.CreateString "Hole_Description", mfgDescription.TextMatrix(iRow, 0)
            End If
```

    ...

---

The hole parameter is created if needed, else updated.

    ...
```vbscript
```vbscript
```vbscript
            ' ------------
            ' Get the hole type
            ' ------------
```

```

            Select Case mfgDescription.TextMatrix(iRow, 1)
```

```vbscript
```vbscript
```vbscript
' Get the hole type
' ------------
```

```

```vbscript
Select Case mfgDescription.TextMatrix(iRow, 1)
                Case "Simple"
                    oHole.Type = catSimpleHole
                Case "Counterbored"
                    oHole.Type = catCounterboredHole
```

                    oHole.HeadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 9)) * oUnit
                    oHole.HeadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 12)) * oUnit
                    oHole.HeadDiameter.MaximumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 10)) - _
                                                           CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
                    oHole.HeadDiameter.MinimumTolerance = (CDbl(mfgDescription.TextMatrix(iRow, 11)) - _
                                                           CDbl(mfgDescription.TextMatrix(iRow, 9))) * oUnit
            End Select
```

    ...

---

The hole type is applied. In case of counterbored, tolerances are applied on the spot facing diameter.

    ...
```vbscript
```vbscript
```vbscript
            ' ------------
            ' Get the hole thread definition
            ' ------------
```

```

            Select Case mfgDescription.TextMatrix(iRow, 6)
```

```vbscript
```vbscript
```vbscript
' Get the hole thread definition
' ------------
```

```

```vbscript
Select Case mfgDescription.TextMatrix(iRow, 6)
                Case "Yes"
                    If oHole.Diameter.Value < oHole.ThreadDiameter.Value And _
```

                       oHole.BottomLimit.Dimension.Value > oHole.ThreadDepth.Value Then
```

```vbscript
```vbscript
```vbscript
                        ' ------------
                        ' Update the part when hole diameter is smaller than tread diameter
                        ' and hole limit is greater than thread depth, before apply new values
                        ' -----------
```

```

```

```vbscript
```vbscript
```vbscript
' Update the part when hole diameter is smaller than tread diameter
' and hole limit is greater than thread depth, before apply new values
' -----------
```

```

                        oPartDocument.Part.Update
                    End If
```vbscript
                    oHole.ThreadingMode = catThreadedHoleThreading
```

                    oHole.ThreadDiameter.Value = CDbl(mfgDescription.TextMatrix(iRow, 7)) * oUnit
                    oHole.ThreadDepth.Value = CDbl(mfgDescription.TextMatrix(iRow, 8)) * oUnit
```vbscript
                Case "No"
                    oHole.ThreadingMode = catSmoothHoleThreading
            End Select

```

```

    ...

---

The hole thread definition is applied.

    ...
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
```

    ...

---

The part is updated, the parameter is displayed.

![](images/CAAPriChangeHole03.gif)

![](images/CAAPriChangeHole04.gif)

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown you how to read data from a file text, find the desired object in a selection, modify hole specifications and add a parameter to an object.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
