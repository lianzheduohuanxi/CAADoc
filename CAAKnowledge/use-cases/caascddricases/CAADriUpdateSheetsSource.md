---
```vbscript
title: "CAADriUpdateSheets.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriUpdateSheets", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriUpdateSheetsSource.htmmd"
converted: "2026-05-11T17:31:51.114720"
```

---
tags: ["CAADriUpdateSheets", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriUpdateSheetsSource.htmmd"
converted: "2026-05-11T17:31:51.114720"
    Option Explicit
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000

```

```

```vbscript
```vbscript
    Dim Language as String
    Language="VBScript"
```
```

```vbscript
```vbscript
```vbscript
    ' ***********************************************************************
    '   Purpose:      This macro allows you to update all the sheets contained
    '                 in all Drawing document of a specified folder
    '   Assumptions:
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English (United States)
    '   CATIA Level:  V5R6
    ' ***********************************************************************
```

```

```

```vbscript
```vbscript
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
```vbscript
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
```
```vbscript
        CATIA.DisplayFileAlerts = False
        ' Set the file system object containig the folder
        Dim oFileSys As FileSystem
        Set oFileSys = CATIA.FileSystem
        ' -----------------------------------------------------------
```
        ' Optional: allows to find the sample wherever it's installed
```vbscript
        Dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")
    '    If (Not oFileSys.FolderExists(sDocPath)) Then
```
```vbscript
    '      Err.Raise 9999,,"No Doc Path Defined"
    '    End If
```
        ' -----------------------------------------------------------
        ' Define the path's folder where we are looking for Drawing documents
```vbscript
        Dim sFolderPath As String
        sFolderPath = InputBox( "Enter a folder path:", "Update All Sheets Of a Folder", _
```
```

```

```

```vbscript
```vbscript
```vbscript
' Define the path's folder where we are looking for Drawing documents
```vbscript
Dim sFolderPath As String
```
```

```

```

sFolderPath = InputBox( "Enter a folder path:", "Update All Sheets Of a Folder", _
                                sDocPath & "/online/CAAScdDriUseCases/samples")
```vbscript
        If (Not oFileSys.FolderExists(sFolderPath)) Then
```vbscript
```vbscript
```vbscript
          Err.Raise 9999,,sFolderPath & ": This Folder does not exist"
        End If
```
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
        ' Set the folder object
        Dim oFolder As Folder
        Set oFolder = oFileSys.GetFolder(sFolderPath)
        ' Loop on the files collection of the folder
```
        ' For Each File In Folder.Files
```vbscript
        Dim iI, iJ
        For iI = 1 To oFolder.Files.Count
```
```vbscript
            Dim oFile As Object
            Set oFile = oFolder.Files.Item(iI)
            '  Retrieve in the files collection only the Drawing documents from its extension
```
            If InStr(oFile.Name, ".CATDrawing") <> 0 Then
```vbscript
                ' Set and open a Drawing document
                Dim oDoc As Document
                Set oDoc = CATIA.Documents.Open(oFile.Path)
```
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
' Set and open a Drawing document
Dim oDoc As Document
Set oDoc = CATIA.Documents.Open(oFile.Path)
```
```

```

```vbscript
                MsgBox "Updating Document " & oFile.Path, 0  ' VBOKOnly
```
```

```vbscript
```vbscript
```vbscript
                ' Loop on the sheets collection of the drawing document
                ' For Each sheet In oDoc.Sheets
                For iJ = 1 To oDoc.Sheets.Count
                    ' Update the sheet even is not necessary
```

```

```

```vbscript
```vbscript
```vbscript
' For Each sheet In oDoc.Sheets
For iJ = 1 To oDoc.Sheets.Count
' Update the sheet even is not necessary
```

```

                    oDoc.Sheets.Item(iJ).ForceUpdate
                Next
```

```vbscript
```vbscript
```vbscript
                ' Save the Drawing document
                ' oDoc.Save
                ' Close the Drawing document
```

```

```

```vbscript
```vbscript
```vbscript
' Save the Drawing document
' oDoc.Save
' Close the Drawing document
```

```

                oDoc.Close
```vbscript
            End If

```

```

oDoc.Close
```vbscript
End If
```vbscript
```vbscript
        Next

```

```

```

```vbscript
```vbscript
    End Sub

```
```
