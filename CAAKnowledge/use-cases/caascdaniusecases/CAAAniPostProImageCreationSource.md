---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniPostProImageCreation", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProImageCreationSource.htmmd"
converted: "2026-05-11T11:27:02.506805"
---

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

```cpp
Sub CATMain(#)
' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the Analysis Manager
```
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
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)

' Retrieve the analysis sets and analysis set by its name
```
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)

Set oAnalysisImages = oAnalysisSet.AnalysisImages

'Image creation  under Frequency Case Solution.1 imagename=Disp_Symbol,  hide existing image=no, showmesh = no, duplicate=yes 
```
'=================================================================================

```vbscript
Set analysisImage1 = oAnalysisImages.Add("Disp_Symbol", False, False, True)

'Image creation  under Frequency Case Solution.1 imagename=Mesh_Deformed,  hide existing image=yes, showmesh = no, duplicate=yes 
```
'====================================================================================

```vbscript
Set analysisImage2 = oAnalysisImages.Add("Mesh_Deformed", True, False, True)

Set analysisSet2 = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)

' Retrieve list of Analysis Images from Restraint set
```
```vbscript
Set analysisEntities1 = analysisSet2.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Item(1)
Set analysisImages2 = analysisEntity1.AnalysisImages

'Image creation  under Clamp imagename=Restraint,  hide existing image=yes, showmesh = yes, duplicate=no 
```
'=================================================================================

```vbscript
Set analysisImage3 = analysisImages2.Add("Restraint", True, True, False)

End Sub

```

```vbscript
&#39; COPYRIGHT DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      To create demonstrate how images are created
&#39;                 under analysis sets and restraints.
&#39;   Assumptions:   
&#39;   Author:       bmw
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R16
&#39; ***********************************************************************

```cpp
Sub CATMain(#)
&#39; ----------------------------------------------------------- 
```
&#39; Optional: allows to find the sample wherever it&#39;s installed
```cpp
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 

&#39; Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

&#39; Retrieve the Analysis Manager
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
&#39; Retrieve the analysis model from the list of models
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```vbscript
&#39; Retrieve the analysis cases and the first analysis case
```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```
```

```vbscript
&#39; Retrieve the analysis sets and analysis set by its name
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item(&quot;Frequency Case Solution.1&quot;, catAnalysisSetSearchAll)

Set oAnalysisImages = oAnalysisSet.AnalysisImages

&#39;Image creation  under Frequency Case Solution.1 imagename=Disp_Symbol,  hide existing image=no, showmesh = no, duplicate=yes 
```
&#39;=================================================================================

```vbscript
Set analysisImage1 = oAnalysisImages.Add(&quot;Disp_Symbol&quot;, False, False, True)

&#39;Image creation  under Frequency Case Solution.1 imagename=Mesh_Deformed,  hide existing image=yes, showmesh = no, duplicate=yes 
```
&#39;====================================================================================

```vbscript
Set analysisImage2 = oAnalysisImages.Add(&quot;Mesh_Deformed&quot;, True, False, True)

Set analysisSet2 = oAnalysisSets.Item(&quot;Restraints.1&quot;, catAnalysisSetSearchAll)

&#39; Retrieve list of Analysis Images from Restraint set
```
```vbscript
Set analysisEntities1 = analysisSet2.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Item(1)
Set analysisImages2 = analysisEntity1.AnalysisImages

&#39;Image creation  under Clamp imagename=Restraint,  hide existing image=yes, showmesh = yes, duplicate=no 
```
&#39;=================================================================================

```vbscript
Set analysisImage3 = analysisImages2.Add(&quot;Restraint&quot;, True, True, False)

End Sub
```
```