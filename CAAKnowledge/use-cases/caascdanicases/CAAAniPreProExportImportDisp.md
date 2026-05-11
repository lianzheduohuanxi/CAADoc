---
```vbscript
title: "Export/Import of Displacements"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniPreProExportImportDisp", "CATIA", "CAAScdAniUseCases", "CATIAAnalysisManager"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProExportImportDisp.htm"
converted: "2026-05-11T17:31:51.793943"
```

---
## Analysis Modeler

|
## Export/Import of Displacements

* * *

  This use case shows you how to export displacements from analysis assembly to the specified sub-analysis. This macro opens an analysis assembly document and exports the displacement. With the use of Edit/Search..., all of the sub-analyses are selected and displacements are exported for each one of them. This scenario is available only with the Generative Assembly Structural Analysis (GAS) product.   ![](images/ExportImportDisp.jpg)
---|---
This use case shows you how to export displacements from analysis assembly to the specified sub-analysis. This macro opens an analysis assembly document and exports the displacement. With the use of Edit/Search..., all of the sub-analyses are selected and displacements are exported for each one of them. This scenario is available only with the Generative Assembly Structural Analysis (GAS) product.   ![](images/ExportImportDisp.jpg)
  CAAAniPreProExportImportDisp is launched in CATIA [1]. No open document is needed. [ CAAAniPreProExportImportDisp.catvbs](CAAAniPreProExportImportDispSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPreProExportImportDisp.catvbs) (Windows only).
  CAAAniPreProExportImportDisp includes the following steps:

  1. Prolog
  2. Extracting the analysis documents, models and cases
  3. Selecting sub-analyses using Edit/Search...
  4. Exporting and importing displacements
  5. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
```vbscript
    ' Optional: allows to find the sample wherever it's installed
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    sOut = CATIA.SystemService.Environ("CATTemp")
```

```

```

```vbscript
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
    Err.Raise 9999,,"No Doc Path Defined"
```vbscript
    End If
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Open the Analysis document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Assembled_Loads_Solutions.CATAnalysis")
    Set analysisDocument1 = CATIA.Documents.Open(sFilePath)
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved from the documentation installation path, this path is stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. The CATTemp environment variable stores temporary data. On windows it points to C/Documents and Settings\user\Local Settings\Application Data\DassaultSystemes\CATTemp and on unix it points to /CATSettings/CATTemp.
#### **Extracting the analysis documents and analysis models and cases**

    ...

```vbscript
    'Retrieve the Analysis Manager from the analysis document
```

```vbscript
    Set analysisManager1 = analysisDocument1.Analysis
```

```vbscript
```vbscript
```vbscript
    'Retrieve the analysis models and the first model
    Set analysisModels1 = analysisManager1.AnalysisModels
    Set analysisModel1 = analysisModels1.Item(1)
    'Retrieve the list of analysis cases from analysis model and the first case
    'from the list of cases
    Set analysisCases1 = analysisModel1.AnalysisCases
    Set analysisCase1 = analysisCases1.Item(1)
```

```

```

```vbscript
    'Retrieve the list of solution case and the static case solution
```

```vbscript
    Set analysisSets1 = analysisCase1.AnalysisSets
```vbscript
```vbscript
    Set analysisSet1 = analysisSets1.Item("Static Case Solution.1", catAnalysisSetSearchAll)

```

```

```

    ...

---

According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses standard procedures to navigate/retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , and then **Analysis Models** , from analysis models we retrieve the analysis cases.
#### Selecting using edit search

    ...

```vbscript
    'Search for the Analysis Manager in the document
```

```vbscript
    Set selection1 = analysisDocument1.Selection
    selection1.Search "Name=*Analysis Manager*,all"
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
    Set analysisExport =  analysisSet1.GetItem("AnalysisExport")
```

```

    analysisSet1.Update

```

    ...

---
#### Using the edit search we select all the analysis managers in the document. There will be one analysis manager corresponding to each sub-analysis, and an additional one that corresponds to the analysis assembly document. It is important that we remove the analysis manager corresponding to analysis assembly from the selected objects as we need analysis managers of sub-analysis only. We take AnalysisExport interface from the analysis set which is inside the analysis assembly. We also update the analysis set before exporting.
#### Exporting and importing displacements

    ...

```vbscript
```vbscript
```vbscript
    'Here we create as many export files as the number of sub-analysis
    'The exported displacements are transferred to their respective
    'sub-analysis with AnalysisImport interface
```

```

```

```vbscript
    For i =1 To selection1.Count
```

```vbscript
              Set manager = selection1.FindObject("CATIAAnalysisManager")
```vbscript
```vbscript
              'Export the displacements
              fullPath = sOut + sSep +"Displacements" +CStr(i) + ".CATAnalysisExport"
```

```

              analysisExport.Export  fullPath, "Displacements", array, manager

              Set analysisModel = manager.AnalysisModels.Item(1)
```vbscript
              Set analysisCases = analysisModel.AnalysisCases
```

```

```vbscript
```vbscript
```vbscript
              'Import Displacements
              Set solCase = analysisCases.NewCase("AnalysisSolutionCase")
              Set importCase =  solCase.GetItem("AnalysisImport")
```

```

```

```vbscript
```vbscript
```vbscript
'Import Displacements
Set solCase = analysisCases.NewCase("AnalysisSolutionCase")
Set importCase =  solCase.GetItem("AnalysisImport")
```

```

              importCase.ImportDisp solCase, fullPath, manager, NOTHING
```vbscript
    Next

```

```

    ...

---
#### Here we run a loop over the selected sub-analyses and export the displacements. The export method requires the full path of the output file, including the file name and extension. Hence we append the file name and extension. We create a new solution case in the sub-analysis and import the displacements
#### Epilog

    ...

```vbscript
End Sub

```

    ...

---

To run the macro interactively CATDocView environment variable must be defined.

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to export and import the displacements.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
