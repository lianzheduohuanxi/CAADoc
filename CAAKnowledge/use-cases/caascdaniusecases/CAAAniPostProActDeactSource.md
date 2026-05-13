---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniPostProAcDesact", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProActDeactSource.htmmd"
converted: "2026-05-11T11:27:02.512148"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      To demonstrate activation and deactivation of image
'   Assumptions:   displacement symbol image exists in the document
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```vbscript
Sub CATMain(#)
' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```vbscript
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

' Retrieve the analysis cases and the first analysis case
```
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
Set analysisImages1 = oAnalysisSet.AnalysisImages

```

'activation of an  image
'==============
'we search image Disp_Symbol
```vbscript
Set oAnalysisImage = analysisImages1.Item("Disp_Symbol")

```

'we Activate the image
oAnalysisImage.SetActivationStatus true

'we update the  image
oAnalysisImage.Update

'deactivation of an  image
'===============
'we deactivate the image
oAnalysisImage.SetActivationStatus false

'we update the  image
oAnalysisImage.Update

```vbscript
End Sub

```

```vbscript
&#39; COPYRIGHT DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      To demonstrate activation and deactivation of image
&#39;   Assumptions:   displacement symbol image exists in the document
&#39;   Author:       bmw
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R16
&#39; ***********************************************************************

```vbscript
Sub CATMain(#)
&#39; ----------------------------------------------------------- 
```
&#39; Optional: allows to find the sample wherever it&#39;s installed
```vbscript
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 

&#39; Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

&#39; Retrieve the Analysis Manager
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

&#39; Retrieve the analysis model from the list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39; Retrieve the analysis cases and the first analysis case
```
```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)

&#39; Retrieve the analysis cases and the first analysis case
```
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item(&quot;Frequency Case Solution.1&quot;, catAnalysisSetSearchAll)
Set analysisImages1 = oAnalysisSet.AnalysisImages

```

&#39;activation of an  image
&#39;==============
&#39;we search image Disp_Symbol
```vbscript
Set oAnalysisImage = analysisImages1.Item(&quot;Disp_Symbol&quot;)

```

&#39;we Activate the image
oAnalysisImage.SetActivationStatus true

&#39;we update the  image
oAnalysisImage.Update

&#39;deactivation of an  image
&#39;===============
&#39;we deactivate the image
oAnalysisImage.SetActivationStatus false

&#39;we update the  image
oAnalysisImage.Update

```vbscript
End Sub
```
```