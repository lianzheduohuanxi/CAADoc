---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CATIAAnalysisManager", "CAAAniPreProExportImportDisp"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProExportImportDispSource.htmmd"
converted: "2026-05-11T11:27:02.502848"
---

' COPYRIGHT DASSAULT SYSTEMES 2000
'***********************************************************************
'   Purpose:  Update the static case solution in AA
'             Export the displacements
'	      Add a new solution case and import
'   Assumptions: 
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R17
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
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Assembled_Loads_Solutions.CATAnalysis")
Set analysisDocument1 = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Manager from the analysis document
```
```vbscript
Set analysisManager1 = analysisDocument1.Analysis

'Retrieve the analysis models and the first model
```
```vbscript
Set analysisModels1 = analysisManager1.AnalysisModels
Set analysisModel1 = analysisModels1.Item(1)

'Retrieve the list of analysis cases from analysis model and the first case
```
'from the list of cases
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases
Set analysisCase1 = analysisCases1.Item(1)

'Retrieve the list of solution case and the static case solution
```
```vbscript
Set analysisSets1 = analysisCase1.AnalysisSets
Set analysisSet1 = analysisSets1.Item("Static Case Solution.1", catAnalysisSetSearchAll)

'Search for the Analysis Manager in the document
```
```vbscript
Set selection1 = analysisDocument1.Selection
selection1.Search "Name=*Analysis Manager*,all"
```

'Remove the first Analysis Manager that is the manager of
'analysis assembly document
selection1.Remove(1)

'Get the AnalysisExport interface from analysis set
```vbscript
Set analysisExport =  analysisSet1.GetItem("AnalysisExport")
analysisSet1.Update
```

'Define Array
safeArray = Array(#)

'Here we create as many export files as the number of su-banalysis
'The exported displacements are transferred to their respective
'sub-analysis with AnalysisImport interface

For i =1 To selection1.Count
```cpp
          Set manager = selection1.FindObject("CATIAAnalysisManager")
   
```
   
          'Export the displacements
          fullPath = sOut + sSep +"Displacements" +CStr(i) + ".CATAnalysisExport"
          analysisExport.Export  fullPath, "Displacements", array, manager

```vbscript
          Set analysisModel = manager.AnalysisModels.Item(1)
          Set analysisCases = analysisModel.AnalysisCases     
 
          'Import Displacements  
```
```vbscript
          Set solCase = analysisCases.NewCase("AnalysisSolutionCase")
          Set importCase =  solCase.GetItem("AnalysisImport")
          importCase.ImportDisp solCase, fullPath, manager, NOTHING
```
Next

```vbscript
End Sub

```

```vbscript
' COPYRIGHT DASSAULT SYSTEMES 2000
'***********************************************************************
'   Purpose:  Update the static case solution in AA
'             Export the displacements
'	      Add a new solution case and import
'   Assumptions: 
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R17
' ***********************************************************************

```cpp
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
sDocPath=CATIA.SystemService.Environ("CATDocView")
sOut = CATIA.SystemService.Environ(&quot;CATTemp&quot;)

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Assembled_Loads_Solutions.CATAnalysis&quot;)
Set analysisDocument1 = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Manager from the analysis document
```
```vbscript
Set analysisManager1 = analysisDocument1.Analysis

'Retrieve the analysis models and the first model
```
```vbscript
Set analysisModels1 = analysisManager1.AnalysisModels
Set analysisModel1 = analysisModels1.Item(1)

'Retrieve the list of analysis cases from analysis model and the first case
```
'from the list of cases
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases
Set analysisCase1 = analysisCases1.Item(1)

'Retrieve the list of solution case and the static case solution
```
```vbscript
Set analysisSets1 = analysisCase1.AnalysisSets
Set analysisSet1 = analysisSets1.Item("Static Case Solution.1", catAnalysisSetSearchAll)

'Search for the Analysis Manager in the document
```
```vbscript
Set selection1 = analysisDocument1.Selection
selection1.Search "Name=*Analysis Manager*,all"
```

'Remove the first Analysis Manager that is the manager of
'analysis assembly document
selection1.Remove(1)

'Get the AnalysisExport interface from analysis set
```vbscript
Set analysisExport =  analysisSet1.GetItem("AnalysisExport")
analysisSet1.Update
```

'Define Array
safeArray = Array(#)

'Here we create as many export files as the number of su-banalysis
'The exported displacements are transferred to their respective
'sub-analysis with AnalysisImport interface

For i =1 To selection1.Count
```cpp
          Set manager = selection1.FindObject("CATIAAnalysisManager")
   
```
   
          'Export the displacements
          fullPath = sOut + sSep +"Displacements" +CStr(i) + ".CATAnalysisExport"
          analysisExport.Export  fullPath, "Displacements", array, manager

```vbscript
          Set analysisModel = manager.AnalysisModels.Item(1)
          Set analysisCases = analysisModel.AnalysisCases     
 
          'Import Displacements  
```
```vbscript
          Set solCase = analysisCases.NewCase("AnalysisSolutionCase")
          Set importCase =  solCase.GetItem("AnalysisImport")
          importCase.ImportDisp solCase, fullPath, manager, NOTHING
```
Next

```vbscript
End Sub
```
```