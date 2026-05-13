---
```vbscript
title: "CAAAniPostProExportData.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProExportData", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProExportDataSource.htmmd"
converted: "2026-05-11T17:31:51.749542"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Export data on image
    '   Assumptions:
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R16
    ' ***********************************************************************
```

```

```

```vbscript
    Sub CATMain(#)
```vbscript
```
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed

```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sOut = CATIA.SystemService.Environ("CATTemp")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```
```

```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
```vbscript
        End If
    ' -----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```vbscript
' -----------------------------------------------------------
    ' Open the CATAnalysis Document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```vbscript
```vbscript
```vbscript
    ' Retrieve the Analysis Manager
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
    ' Retrieve the analysis model from the list of models
```
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    ' Retrieve the analysis cases and the first analysis case
```
```vbscript
    Set oAnalysisSets = oAnalysisModel.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.ItemByType("PropertySet")

    Set oAnalysisImages = oAnalysisSet.AnalysisImages
    Set oAnalysisImage = oAnalysisImages.Add("Material_Fringe", False, False, True)
    ' Retrieve the folder stored in sOut
```
```vbscript
    Set fileSystem1 = CATIA.FileSystem
    Set folder1 = fileSystem1.GetFolder(sout)
```
```

```

```

```vbscript
```vbscript
```vbscript
    'export data in exportfile1.txt (format txt)
    '==============================
```

```

    oAnalysisImage.ExportData folder1, "exportfile1", "txt"

```vbscript
```vbscript
    'export data in exportfile2.xls (format xls)
    '==============================
```

```

    oAnalysisImage.ExportData folder1, "exportfile2", "xls"

```vbscript
```vbscript
    'export data (with mesh part id) in exportfile3.txt (format txt)
    '==================================================
```

```

    oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile3", "txt"

```vbscript
```vbscript
    'export data (with mesh part id) in exportfile4.xls (format xls)
    '==================================================
```

```

    oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile4", "xls"

```

```vbscript
```vbscript
    End Sub

```
```
