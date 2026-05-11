---
```vbscript
title: "CAAAniPostProImageCreation.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProImageCreation", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProImageCreationSource.htm"
converted: "2026-05-11T17:31:51.755530"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      To create demonstrate how images are created
    '                 under analysis sets and restraints.
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
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

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

```

```

```vbscript
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
    ' Retrieve the Analysis Manager
```

```

```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

```

```

```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
    ' Retrieve the analysis model from the list of models
```

```

```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```vbscript
    Set oAnalysisModel = oAnalysisModels.Item(1)

```

```

```

```vbscript
Set oAnalysisModel = oAnalysisModels.Item(1)
```vbscript
    ' Retrieve the analysis cases and the first analysis case
```

```

```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
```vbscript
```vbscript
    Set oAnalysisCase = oAnalysisCases.Item(1)

```

```

```

```vbscript
Set oAnalysisCase = oAnalysisCases.Item(1)
```vbscript
    ' Retrieve the analysis sets and analysis set by its name
```

```

```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
```vbscript
```vbscript
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)

    Set oAnalysisImages = oAnalysisSet.AnalysisImages
    'Image creation  under Frequency Case Solution.1 imagename=Disp_Symbol,  hide existing image=no, showmesh = no, duplicate=yes
    '=================================================================================

    Set analysisImage1 = oAnalysisImages.Add("Disp_Symbol", False, False, True)
    'Image creation  under Frequency Case Solution.1 imagename=Mesh_Deformed,  hide existing image=yes, showmesh = no, duplicate=yes
    '====================================================================================

    Set analysisImage2 = oAnalysisImages.Add("Mesh_Deformed", True, False, True)

    Set analysisSet2 = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)
```

```

```

```vbscript
```vbscript
```vbscript
    ' Retrieve list of Analysis Images from Restraint set
    Set analysisEntities1 = analysisSet2.AnalysisEntities
    Set analysisEntity1 = analysisEntities1.Item(1)
    Set analysisImages2 = analysisEntity1.AnalysisImages
    'Image creation  under Clamp imagename=Restraint,  hide existing image=yes, showmesh = yes, duplicate=no
    '=================================================================================

    Set analysisImage3 = analysisImages2.Add("Restraint", True, True, False)
```

```

```

```vbscript
    End Sub

```
