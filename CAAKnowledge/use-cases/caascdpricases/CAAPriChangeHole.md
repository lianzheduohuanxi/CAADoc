---
```vbscript
title: "Changing the Hole Parameters"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CATIAHole", "CAAPriChangeHole"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHole.htm"
converted: "2026-05-11T17:31:51.189551"
```

---
| 
## Part Design

| 
## Changing the Hole Parameters  

* * *

 This macro shows you how to change the parameters of selected holes (diameter, type, thread definition, etc) from data contained in a text file. Data unit is take into account: Millimeter or Inches.  
This macro allows you to define:

  * T**he limit type: "Up to next" or "Offset" onl**y.
  * **Maximum and minimum** tolerances of the hole diameter.
  * "Simple" or "Counterbored" as hole type only, m**aximum and minimum** tolerances for the spot facing diameter for counterbored holes.
  * Whether the hole is threaded or not, and its ** thread depth** if threaded.
  * A parameter named "Hole_Description" where its value is a letter corresponding to the applied parameters.

It modifies the  _Hole_ object from its methods and properties, and updates the part.  
---|---  

  * Open the [ CAAPriChangeHole.CATPart](samples/CAAPriChangeHole.CATPart) document.
  * Reference the catscript file [CAAPriChangeHole.CATScript](macros/CAAPriChangeHole.CATScript) in the application 
  * The text file [ CAAPriChangeHole.txt](macros/CAAPriChangeHole.txt) located in the CAAScdPriUseCases module.

 CAAPriChangeHole includes the following steps:

CAAPriChangeHole includes the following steps:
  1. Prolog
  2. Reading the Hole Parameters
  3. Looking for the Hole Object in the Selection
  4. Applying the Hole Parameters

#### Prolog

3. Looking for the Hole Object in the Selection
4. Applying the Hole Parameters
Load the CAAPriChangeHole.CATPart document that contains three holes. ![](images/CAAPriChangeHole01.gif) Select one or several holes as shown. Selection is allowed from the specification tree or from the geometry. ![](images/CAAPriChangeHole02.gif) Run the macro. 

      ...
```vbscript
    ' ------------
    ' The string as delimiter between input in the text file
    ' ------------
    iDelimiter = "\\"
    ' ------------
    ' Get the CATIA file system
    ' ------------
```

```vbscript
    Set oCATIAFileSys = CATIA.FileSystem
```

```vbscript
    ' ------------
    ' Get the file containing the hole parameters
    ' ------------
    Set oFile = oCATIAFileSys.GetFile(sDocPath & "\online\CAAScdPriUseCases\macros\CAAPriChangeHole.txt")
    ' ------------
    ' Get the text stream
    ' ------------
    Set oTextSteam = oFile.OpenAsTextStream("ForReading")
    ' ------------
    ' Get the part document
    ' ------------
    Set oPartDocument = CATIA.ActiveDocument
```

       ...  

---  

Once the macro has been started, the `oCATIAFileSys`, ` oFile`, `oTextSteam` and `oPartDocument ` variables are declared to receive the instance of the CATIA file system, the file, the text stream and the CATPart document.
#### Reading the Hole Parameters

    ...
Once the macro has been started, the `oCATIAFileSys`, ` oFile`, `oTextSteam` and `oPartDocument ` variables are declared to receive the instance of the CATIA file system, the file, the text stream and the CATPart document.
    If oPartDocument.Selection.Count = 0 Then

```vbscript
        ' ------------
        ' The selection content is empty, the macro ends
        ' ------------
```

```vbscript
' ------------
' The selection content is empty, the macro ends
' ------------
        MsgBox "Select the holes you wish to transform before running the macro.", vbOKOnly, "Warning"
```

    ...

---  

The selection content is tested, if empty a warning message appears and the macro ends:

![](images/CAAPriChangeHole06.gif)

    ...
    Else
```vbscript
        ' ------------
        ' The selection content is not empty
        ' Read the text file data unit
        ' ------------
        oLine = oTextSteam.ReadLine
        Select Case oLine
```

```vbscript
' ------------
oLine = oTextSteam.ReadLine
Select Case oLine
            Case "Millimeter"
                oUnit = 1
            Case "Inch"
                oUnit = 25.4
        End Select
        oRow = 0
```

```vbscript
        ' ------------
        ' Read the hole parameters
        ' ------------
```

        Do While oTextSteam.AtEndOfStream = False
            oLine = oTextSteam.ReadLine
            For i = 0 To 12
                If InStr(oLine, iDelimiter) > 0 Then
                    iArray(oRow, i) = Left(oLine, InStr(oLine, iDelimiter) - 1)
                    oLine = Mid(oLine, InStr(oLine, iDelimiter) + 2)
                Else
                    iArray(oRow, i) = oLine
                End If
            Next
            iMessage = iMessage & Chr(10) & iArray(oRow, 0) & " " & iArray(oRow, 1)
            oRow = oRow + 1
        Loop
        oTextSteam.Close

    ...  

---  

Otherwise, the macro reads the hole parameters contained in the CAAPriChangeHole.txt file:

  * The first line contains the unit name
  * The second line contains the name of each field.
  * Next lines contain a set of hole parameters per line.

The unit ratio is stored in `oUnit` (macro unit is always millimeter!). The file is read until its end, the field names and all set of hole parameters are stored in an array `iArray`.

    ...
```vbscript
        ' ------------
        ' Get the description you wish, by default pre-select the first description
        ' ------------
        iMessage = "Please select the hole decription you wish to apply:" & iMessage
        oReturn = InputBox(iMessage, "Hole Parameter", iArray(1, 0))
        If oReturn = "" Then
            ' ------------
            ' No selection, the macro ends
            ' ------------
```

```vbscript
' ------------
' No selection, the macro ends
' ------------
            Exit Sub
        Else
            Select Case oReturn
                Case "A"
                    iRow = 1
                Case "B"
                    iRow = 2
                Case "C"
                    iRow = 3
                Case "D"
                    iRow = 4
```

```vbscript
                ' ------------
                ' Invalid selection, the macro ends
                ' ------------
```

```vbscript
' ------------
' Invalid selection, the macro ends
' ------------
                Case Else
                    Exit Sub
            End Select
```

    ...

---  

An input box asks you to select the desired hole parameters (letter description and hole type are displayed).  
"A" description is selected by default. If a wrong letter is typed (case sensitive), the macro ends.

![](images/CAAPriChangeHole05.gif)
#### Looking for the Hole Object in the Selection

    ...
            iHoleInSelection = True
            Do While iHoleInSelection = True
                iHoleInSelection = CatObjectExistsInSelection(oPartDocument.Selection, "CATIAHole", oHole)
                If iHoleInSelection = True Then

    ...  

---  

```vbscript
For each hole object found in the selection, the desired parameters are applied.

```

#### Applying the Hole Parameters

    ...
```vbscript
                    ' ------------
                    ' Get the hole limit
                    ' ------------
                    Select Case iArray(iRow, 5)
```

```vbscript
' Get the hole limit
' ------------
Select Case iArray(iRow, 5)
                        Case "UpToNext"
                            oHole.BottomLimit.LimitMode = catUpThruNextLimit
```

```vbscript
                            ' ------------
                            ' Update the part when set the hole limit to "UpToNext"
                            ' ------------
```

```vbscript
' ------------
' Update the part when set the hole limit to "UpToNext"
' ------------
                            oPartDocument.Part.Update
                        Case Else
                            oHole.BottomLimit.LimitMode = catOffsetLimit
                            oHole.BottomLimit.Dimension.Value = CDbl(iArray(iRow, 5)) * oUnit
                    End Select
```

    ...  

---  

The hole limit is applied.

    ...
```vbscript
                    ' ------------
                    ' Get the hole diameter and its tolerances
                    ' ------------
```

```vbscript
' ------------
' Get the hole diameter and its tolerances
' ------------
                    oHole.Diameter.Value = CDbl(iArray(iRow, 2))
                    oHole.Diameter.MaximumTolerance = (CDbl(iArray(iRow, 3)) - CDbl(iArray(iRow, 2))) * oUnit
                    oHole.Diameter.MinimumTolerance = (CDbl(iArray(iRow, 4)) - CDbl(iArray(iRow, 2))) * oUnit
```

    ...  

---  

The hole diameter and its tolerances are applied.

    ...
```vbscript
                    Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
```

```vbscript
                    ' ------------
                    ' Set the hole parameter
                    ' ------------
                    If ParameterExists("Hole_Description", oParameters) = True Then
```

```vbscript
' Set the hole parameter
' ------------
If ParameterExists("Hole_Description", oParameters) = True Then
                        oParameters.Item("Hole_Description").ValuateFromString (iArray(iRow, 0))
                    Else
                        oParameters.CreateString "Hole_Description", iArray(iRow, 0)
                    End If
```

    ...  

---  

The hole parameter is created if needed, otherwise updated.

    ...
```vbscript
                    ' ------------
                    ' Get the hole type
                    ' ------------
                    Select Case iArray(iRow, 1)
```

```vbscript
' Get the hole type
' ------------
Select Case iArray(iRow, 1)
                        Case "Simple"
                            oHole.Type = catSimpleHole
                        Case "Counterbored"
                            oHole.Type = catCounterboredHole
                            oHole.HeadDiameter.Value = CDbl(iArray(iRow, 9)) * oUnit
                            oHole.HeadDepth.Value = CDbl(iArray(iRow, 12)) * oUnit
                            oHole.HeadDiameter.MaximumTolerance = (CDbl(iArray(iRow, 10)) - CDbl(iArray(iRow, 9))) * oUnit
                            oHole.HeadDiameter.MinimumTolerance = (CDbl(iArray(iRow, 11)) - CDbl(iArray(iRow, 9))) * oUnit
                    End Select
```

    ...  

---  

The hole type is applied. In case of counterbored, tolerances are applied on the spot facing diameter.

    ...
```vbscript
                    ' ------------
                    ' Get the hole thread definition
                    ' ------------
                    Select Case iArray(iRow, 6)
```

```vbscript
' Get the hole thread definition
' ------------
Select Case iArray(iRow, 6)
                        Case "Yes"
                            If oHole.Diameter.Value < oHole.ThreadDiameter.Value And _
                               oHole.BottomLimit.Dimension.Value > oHole.ThreadDepth.Value Then
```

```vbscript
                                ' ------------
                                ' Update the part when hole diameter is smaller than tread diameter 
                                ' and hole limit is greater than thread depth, before apply new values 
                                ' ------------
```

```vbscript
' Update the part when hole diameter is smaller than tread diameter
' and hole limit is greater than thread depth, before apply new values
' ------------
                                oPartDocument.Part.Update
                            End If
                            oHole.ThreadingMode = catThreadedHoleThreading
                            oHole.ThreadDiameter.Value = CDbl(iArray(iRow, 7)) * oUnit
                            oHole.ThreadDepth.Value = CDbl(iArray(iRow, 8)) * oUnit
                        Case "No"
                            oHole.ThreadingMode = catSmoothHoleThreading
                    End Select
```

    ...  

---  

The hole thread definition is applied.

    ...
```vbscript
                    ' ------------
                    ' Update the part
                    ' ------------
```

```vbscript
' ------------
' Update the part
' ------------
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
