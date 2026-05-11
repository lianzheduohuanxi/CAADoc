---
```vbscript
title: "CAAAniPostProBasicReport.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProBasicReport", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProBasicReportSource.htm"
converted: "2026-05-11T17:31:51.743555"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      To generate basic report
    '   Assumptions:   displacement symbol image exists in the document
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R16
    ' ***********************************************************************

```

```

```

    Sub CATMain()
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed

      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sOut = CATIA.SystemService.Environ("CATTemp")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```

```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
```

```

```

```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

    Set fileSystem1 = CATIA.FileSystem
```

```vbscript
```vbscript
    Set folder1 = fileSystem1.GetFolder(sOut)

```

```

```

```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```

```vbscript
```vbscript
    Set oAnalysisModel = oAnalysisModels.Item(1)
    Set oAnalysisPostManager = oAnalysisModel.PostManager

    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)

```

```

```

```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
```vbscript
Set oAnalysisCase = oAnalysisCases.Item(1)
```

    oAnalysisPostManager.AddExistingCaseForReport oAnalysisCase

```vbscript
```vbscript
    'basic report on frequency case saved in folder1, title=test1, no image added
    '===============================================
```

```

    oAnalysisPostManager.BuildReport folder1, "Test1", False

```vbscript
```vbscript
    'basic report on frequency case saved in folder1, title=test2, add created images
    '=================================================
```

```

    oAnalysisPostManager.BuildReport folder1, "test2", True

```vbscript
```vbscript
    'basic report on frequency case saved in folder1, title=test3, no image added (old method)
    '======================================================
```

```

    oAnalysisPostManager.ExtractHTMLReport folder1, "test3"

```

```vbscript
    End Sub

```
