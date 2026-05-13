---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniPostProExportData", "CAAScrBase", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProExportDataSource.htmmd"
converted: "2026-05-11T11:27:02.524013"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Export data on image
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
  sOut = CATIA.SystemService.Environ("CATTemp")

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
Set oAnalysisSets = oAnalysisModel.AnalysisSets
Set oAnalysisSet = oAnalysisSets.ItemByType("PropertySet")

Set oAnalysisImages = oAnalysisSet.AnalysisImages
Set oAnalysisImage = oAnalysisImages.Add("Material_Fringe", False, False, True)

' Retrieve the folder stored in sOut
```
```cpp
Set fileSystem1 = CATIA.FileSystem
Set folder1 = fileSystem1.GetFolder(sout)

```

'export data in exportfile1.txt (format txt)
'==============================
oAnalysisImage.ExportData folder1, "exportfile1", "txt"

'export data in exportfile2.xls (format xls)
'==============================
oAnalysisImage.ExportData folder1, "exportfile2", "xls"

'export data (with mesh part id) in exportfile3.txt (format txt) 
'==================================================
oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile3", "txt"

'export data (with mesh part id) in exportfile4.xls (format xls) 
'==================================================
oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile4", "xls"

```vbscript
End Sub

```

```cpp
&#39; COPYRIGHT DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      Export data on image
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
  sOut = CATIA.SystemService.Environ(&quot;CATTemp&quot;)

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

&#39; Retrieve the analysis model from the list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39; Retrieve the analysis cases and the first analysis case
```
```vbscript
Set oAnalysisSets = oAnalysisModel.AnalysisSets
Set oAnalysisSet = oAnalysisSets.ItemByType(&quot;PropertySet&quot;)

Set oAnalysisImages = oAnalysisSet.AnalysisImages
Set oAnalysisImage = oAnalysisImages.Add(&quot;Material_Fringe&quot;, False, False, True)

&#39; Retrieve the folder stored in sOut
```
```cpp
Set fileSystem1 = CATIA.FileSystem
Set folder1 = fileSystem1.GetFolder(sout)
```
```

```vbscript
&#39;export data in exportfile1.txt (format txt)
&#39;==============================
oAnalysisImage.ExportData folder1, &quot;exportfile1&quot;, &quot;txt&quot;
```

```vbscript
&#39;export data in exportfile2.xls (format xls)
&#39;==============================
oAnalysisImage.ExportData folder1, &quot;exportfile2&quot;, &quot;xls&quot;
```

```vbscript
&#39;export data (with mesh part id) in exportfile3.txt (format txt) 
&#39;==================================================
oAnalysisImage.ExportDataWithMeshPartId folder1, &quot;exportfile3&quot;, &quot;txt&quot;
```

```vbscript
&#39;export data (with mesh part id) in exportfile4.xls (format xls) 
&#39;==================================================
oAnalysisImage.ExportDataWithMeshPartId folder1, &quot;exportfile4&quot;, &quot;xls&quot;

```vbscript
End Sub
```
```