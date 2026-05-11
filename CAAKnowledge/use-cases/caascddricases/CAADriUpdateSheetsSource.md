---
title: "CAADriUpdateSheets.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriUpdateSheets", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriUpdateSheetsSource.md"
converted: "2026-05-11T17:31:51.114720"
---

    Option Explicit
    ' COPYRIGHT DASSAULT SYSTEMES 2000
```vbscript
    Dim Language as String
    Language="VBScript"
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

```vbscript
    Sub CATMain()
```vbscript
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
        CATIA.DisplayFileAlerts = False
        ' Set the file system object containig the folder
        Dim oFileSys As FileSystem
        Set oFileSys = CATIA.FileSystem 
        ' ----------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        Dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
    '    If (Not oFileSys.FolderExists(sDocPath)) Then
    '      Err.Raise 9999,,"No Doc Path Defined"
    '    End If
        ' ----------------------------------------------------------- 
        ' Define the path's folder where we are looking for Drawing documents
        Dim sFolderPath As String
        sFolderPath = InputBox( "Enter a folder path:", "Update All Sheets Of a Folder", _
```

                                sDocPath & "\online\CAAScdDriUseCases\samples")
        If (Not oFileSys.FolderExists(sFolderPath)) Then
          Err.Raise 9999,,sFolderPath & ": This Folder does not exist"
        End If
```vbscript
        ' Set the folder object
        Dim oFolder As Folder 
        Set oFolder = oFileSys.GetFolder(sFolderPath) 
        ' Loop on the files collection of the folder
        ' For Each File In Folder.Files
        Dim iI, iJ
        For iI = 1 To oFolder.Files.Count
            Dim oFile As Object
            Set oFile = oFolder.Files.Item(iI)
            '  Retrieve in the files collection only the Drawing documents from its extension
            If InStr(oFile.Name, ".CATDrawing") <> 0 Then
                ' Set and open a Drawing document
                Dim oDoc As Document 
                Set oDoc = CATIA.Documents.Open(oFile.Path)
```

                MsgBox "Updating Document " & oFile.Path, 0  ' VBOKOnly
```vbscript
                ' Loop on the sheets collection of the drawing document
                ' For Each sheet In oDoc.Sheets 
                For iJ = 1 To oDoc.Sheets.Count
                    ' Update the sheet even is not necessary
```

                    oDoc.Sheets.Item(iJ).ForceUpdate 
                Next
```vbscript
                ' Save the Drawing document
                ' oDoc.Save
                ' Close the Drawing document
```

                oDoc.Close
            End If
    
```

        Next
    
```vbscript
    End Sub
    
```

```