---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CATIAHole", "CAAPriChangeHole", "CATIA", "CAAScrJavaScript", "CAAPriChangeHole06", "CAAPriChangeHole04", "CAAPriChangeHole03", "CAAScdInfUseCases", "CAAPriChangeHole05", "CAAScdPriUseCases", "CAAPriChangeHole01", "CAAPriChangeHole02", "CAAInfLauchMacro", "CAAlink"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHole.htm"
converted: "2026-05-11T11:27:02.730957"
---

---

    

Once the macro has been started, the `oCATIAFileSys`, `
    oFile`, `oTextSteam` and `oPartDocument `
    variables are declared to receive the instance of the CATIA file system, the 
    file, the text stream and the CATPart document.
    

#### Reading the Hole Parameters
    
    

The selection content is tested, if empty a warning message appears and 
    the macro ends:
    

![](images/CAAPriChangeHole06.gif)
    
    

Otherwise, the macro reads the hole parameters contained in the 
    CAAPriChangeHole.txt file:
    

      
- The first line contains the unit name
      
- The second line contains the name of each field.
      
- Next lines contain a set of hole parameters per line.
    
    

The unit ratio is stored in `oUnit` (macro unit is always 
    millimeter!). The file is read until its end, the field names and all set of 
    hole parameters are stored in an array `iArray`.
    
    

An input box asks you to select the desired hole parameters (letter 
    description and hole type are displayed).

    "A" description is selected by default. If a wrong letter is typed (case 
    sensitive), the macro ends.
    

![](images/CAAPriChangeHole05.gif)
    

#### Looking for the Hole Object in the Selection
    
    

For each hole object found in the selection, the desired parameters are 
    applied.
    

#### Applying the Hole Parameters
    
    

The hole limit is applied.
    
    

The hole diameter and its tolerances are applied.
    
    

The hole parameter is created if needed, otherwise updated.
    
    

The hole type is applied. In case of counterbored, tolerances are applied 
    on the spot facing diameter.
    
    

The hole thread definition is applied.
    
    

The part is updated, the parameter is displayed.
    

![](images/CAAPriChangeHole03.gif)
    

![](images/CAAPriChangeHole04.gif)
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown you how to read data from a file text, find the 
desired object in a selection, modify hole specifications and add a parameter to 
an object.

[Top]

---

#### References

---

*Copyright  2004, Dassault Systmes. All rights reserved.*



```vbscript
...
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
' ------------
' Get the part document
' ------------
Set oPartDocument = CATIA.ActiveDocument
   ...
```

```vbscript
...
If oPartDocument.Selection.Count = 0 Then
    ' ------------
    ' The selection content is empty, the macro ends
    ' ------------
    MsgBox &quot;Select the holes you wish to transform before running the macro.&quot;, vbOKOnly, &quot;Warning&quot;
...
```

```vbscript
...
Else
    ' ------------
    ' The selection content is not empty
    ' Read the text file data unit
    ' ------------
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
        For i = 0 To 12
            If InStr(oLine, iDelimiter) &gt; 0 Then
                iArray(oRow, i) = Left(oLine, InStr(oLine, iDelimiter) - 1)
                oLine = Mid(oLine, InStr(oLine, iDelimiter) + 2)
            Else
                iArray(oRow, i) = oLine
            End If
        Next
        iMessage = iMessage &amp; Chr(10) &amp; iArray(oRow, 0) &amp; &quot; &quot; &amp; iArray(oRow, 1)
        oRow = oRow + 1
    Loop
    oTextSteam.Close
...
```

```vbscript
...
    ' ------------
    ' Get the description you wish, by default pre-select the first description
    ' ------------
    iMessage = &quot;Please select the hole decription you wish to apply:&quot; &amp; iMessage
    oReturn = InputBox(iMessage, &quot;Hole Parameter&quot;, iArray(1, 0))
    If oReturn = &quot;&quot; Then
        ' ------------
        ' No selection, the macro ends
        ' ------------
        Exit Sub
    Else
        Select Case oReturn
            Case &quot;A&quot;
                iRow = 1
            Case &quot;B&quot;
                iRow = 2
            Case &quot;C&quot;
                iRow = 3
            Case &quot;D&quot;
                iRow = 4
            ' ------------
            ' Invalid selection, the macro ends
            ' ------------
            Case Else
                Exit Sub
        End Select
...
```

```vbscript
...
        iHoleInSelection = True
        Do While iHoleInSelection = True
            iHoleInSelection = CatObjectExistsInSelection(oPartDocument.Selection, &quot;CATIAHole&quot;, oHole)
            If iHoleInSelection = True Then

...
```

```vbscript
...
                ' ------------
                ' Get the hole limit
                ' ------------
                Select Case iArray(iRow, 5)
                    Case &quot;UpToNext&quot;
                        oHole.BottomLimit.LimitMode = catUpThruNextLimit
                        ' ------------
                        ' Update the part when set the hole limit to &quot;UpToNext&quot;
                        ' ------------
                        oPartDocument.Part.Update
                    Case Else
                        oHole.BottomLimit.LimitMode = catOffsetLimit
                        oHole.BottomLimit.Dimension.Value = CDbl(iArray(iRow, 5)) * oUnit
                End Select
...
```

```vbscript
...
                ' ------------
                ' Get the hole diameter and its tolerances
                ' ------------
                oHole.Diameter.Value = CDbl(iArray(iRow, 2))
                oHole.Diameter.MaximumTolerance = (CDbl(iArray(iRow, 3)) - CDbl(iArray(iRow, 2))) * oUnit
                oHole.Diameter.MinimumTolerance = (CDbl(iArray(iRow, 4)) - CDbl(iArray(iRow, 2))) * oUnit
...
```

```vbscript
...
                Set oParameters = oPartDocument.Part.Parameters.SubList(oHole, True)
                ' ------------
                ' Set the hole parameter
                ' ------------
                If ParameterExists(&quot;Hole_Description&quot;, oParameters) = True Then
                    oParameters.Item(&quot;Hole_Description&quot;).ValuateFromString (iArray(iRow, 0))
                Else
                    oParameters.CreateString &quot;Hole_Description&quot;, iArray(iRow, 0)
                End If
...
```

```vbscript
...
                ' ------------
                ' Get the hole type
                ' ------------
                Select Case iArray(iRow, 1)
                    Case &quot;Simple&quot;
                        oHole.Type = catSimpleHole
                    Case &quot;Counterbored&quot;
                        oHole.Type = catCounterboredHole
                        oHole.HeadDiameter.Value = CDbl(iArray(iRow, 9)) * oUnit
                        oHole.HeadDepth.Value = CDbl(iArray(iRow, 12)) * oUnit
                        oHole.HeadDiameter.MaximumTolerance = (CDbl(iArray(iRow, 10)) - CDbl(iArray(iRow, 9))) * oUnit
                        oHole.HeadDiameter.MinimumTolerance = (CDbl(iArray(iRow, 11)) - CDbl(iArray(iRow, 9))) * oUnit
                End Select
...
```

```vbscript
...
                ' ------------
                ' Get the hole thread definition
                ' ------------
                Select Case iArray(iRow, 6)
                    Case &quot;Yes&quot;
                        If oHole.Diameter.Value &lt; oHole.ThreadDiameter.Value And _
                           oHole.BottomLimit.Dimension.Value &gt; oHole.ThreadDepth.Value Then
                            ' ------------
                            ' Update the part when hole diameter is smaller than tread diameter 
                            ' and hole limit is greater than thread depth, before apply new values 
                            ' ------------
                            oPartDocument.Part.Update
                        End If
                        oHole.ThreadingMode = catThreadedHoleThreading
                        oHole.ThreadDiameter.Value = CDbl(iArray(iRow, 7)) * oUnit
                        oHole.ThreadDepth.Value = CDbl(iArray(iRow, 8)) * oUnit
                    Case &quot;No&quot;
                        oHole.ThreadingMode = catSmoothHoleThreading
                End Select
...
```

```vbscript
...
                ' ------------
                ' Update the part
                ' ------------
                oPartDocument.Part.Update
...
```