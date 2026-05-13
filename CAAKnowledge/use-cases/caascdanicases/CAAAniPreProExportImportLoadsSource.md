---
title: "CAAAniPreProExportImportLoads.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CAAAniPreProExportImportLoads", "CATIA", "CAAScdAniUseCases", "CATIAAnalysisManager"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProExportImportLoadsSource.htm"
converted: "2026-05-11T17:31:51.802920"
---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '   Purpose:  Update the static case solution in AA
    '             Export the loads
    '	      Add a new solution case and import
    '   Assumptions:
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R17
    ' ***********************************************************************

```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    sOut = CATIA.SystemService.Environ("CATTemp")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```

```

```vbscript
```vbscript
    Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
    End If
```

```

```vbscript
```vbscript
```cpp
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
```
```

```

```

```vbscript
    'Search for the Analysis Manager in the document
```

```vbscript
```vbscript
    Set selection1 = analysisDocument1.Selection
    selection1.Search "Name=*Analysis Manager*,all"
```
```vbscript
```vbscript
    'Remove the first Analysis Manager that is the manager of
    'analysis assembly document
```

```

    selection1.Remove(1)
```vbscript
```vbscript
    'Get the AnalysisExport interface from analysis set
```vbscript
    Set analysisExport =  analysisSet1.GetItem("AnalysisExport")
```
```

```

    analysisSet1.Update
```

```vbscript
```vbscript
```vbscript
    'Define Array
    safeArray = Array(#)
    'Here we create as many export files as the number of sub-analysis
    'The exported loads are transferred to their respective
    'sub-analysis with AnalysisImport interface
    For i =1 To selection1.Count
```cpp
              Set manager = selection1.FindObject("CATIAAnalysisManager")
             'Export the computed loads
```
              fullPath = sout + sSep + "ComputedLoads"+ CStr(i) + ".CATAnalysisExport"
```

```

```

```vbscript
```cpp
Set manager = selection1.FindObject("CATIAAnalysisManager")
```vbscript
```
'Export the computed loads
```

```

fullPath = sout + sSep + "ComputedLoads"+ CStr(i) + ".CATAnalysisExport"
              analysisExport.Export  fullPath, "ComputedLoads", array, manager

```vbscript
```vbscript
              Set analysisModel = manager.AnalysisModels.Item(1)
```vbscript
```
```vbscript
              Set analysisCases = analysisModel.AnalysisCases
```
```

```

```vbscript
```vbscript
```vbscript
              'Import Loads
```vbscript
              Set preProCase = analysisCases.Item("Preprocessing Case.1")
              Set importCase =  preProCase.GetItem("AnalysisImport")
```
```

```

```

```vbscript
```vbscript
```vbscript
'Import Loads
```vbscript
Set preProCase = analysisCases.Item("Preprocessing Case.1")
Set importCase =  preProCase.GetItem("AnalysisImport")
```
```

```

              importCase.ImportForce preProCase, fullPath, manager, NOTHING

```

```vbscript
    Next

```vbscript
    End Sub

```
```
