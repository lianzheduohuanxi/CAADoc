---
title: "Export/Import of Loads"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniPreProExportImportLoads", "CATIA", "CAAScdAniUseCases", "CATIAAnalysisManager"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProExportImportLoads.htm"
converted: "2026-05-11T17:31:51.800927"
---
## Analysis Modeler

| 
## Export/Import of Loads  
  
  
* * *

  This use case shows how to export computed loads from analysis assembly to the specified sub-analysis. This macro opens an analysis assembly document and exports the loads. With the use of Edit/Search..., all of the sub-analysis are selected, and computed loads are exported for each one of them. We create a new Preprocessing Case in each of the sub-analysis, and import the loads. This scenario is available only with the Generative Assembly Structural Analysis (GAS) product.   ![](images/ExportImportLoads.jpg)    
---|---  
  CAAAniPreProExportImportLoads is launched in CATIA [1]. No open document is needed. [ CAAAniPreProExportImportLoads.catvbs](CAAAniPreProExportImportLoadsSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPreProExportImportLoads.catvbs) (Windows only).    
  CAAAniPreProExportImportLoads includes the following steps:

  1. Prolog
  2. Extracting the analysis documents, models and cases
  3. Selecting using Edit/Search...
  4. Exporting and importing loads
  5. Epilog

#### Prolog

| 
    
    
    ...
    
```vbscript
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    sOut = CATIA.SystemService.Environ("CATTemp")
```

    
```vbscript
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
    Err.Raise 9999,,"No Doc Path Defined"
    End If
```vbscript
    ' ----------------------------------------------------------- 
    ' Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Assembled_Loads_Solutions.CATAnalysis")
    Set analysisDocument1 = CATIA.Documents.Open(sFilePath)
```

    
```

    
    ...  
  
```

---  
  
Open the Analysis document. The Analysis document is retrieved from the documentation installation path, this path is stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. The CATTemp environment variable stores temporary data. On windows it points to C/Documents and Settings\user\Local Settings\Application Data\DassaultSystemes\CATTemp and on unix it points to /CATSettings/CATTemp.
#### **Extracting the analysis documents and analysis models and cases**
    
    
    ...
    
    'Retrieve the Analysis Manager from the analysis document
```vbscript
    Set analysisManager1 = analysisDocument1.Analysis
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

    'Retrieve the list of solution case and the static case solution
```vbscript
    Set analysisSets1 = analysisCase1.AnalysisSets
    Set analysisSet1 = analysisSets1.Item("Static Case Solution.1", catAnalysisSetSearchAll)
    
```

    ...  
  
```

---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses standard procedures to navigate/retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , and then **Analysis Models** , from analysis models we retrieve the analysis cases.
#### Selecting using edit search
    
    
    ...  
    
    'Search for the Analysis Manager in the document
```vbscript
    Set selection1 = analysisDocument1.Selection
    selection1.Search "Name=*Analysis Manager*,all"
    'Remove the first Analysis Manager that is the manager of
    'analysis assembly document
    selection1.Remove(1)
    'Get the AnalysisExport interface from analysis set
    Set analysisExport =  analysisSet1.GetItem("AnalysisExport")
    analysisSet1.Update
    
```

    ...  
  
```

---  
#### Using the Edit/Search... we select all the analysis managers in the document. There will be one analysis manager corresponding to each sub-analysis, and an addition one that corresponds to the analysis assembly. It is important that we remove the analysis manager corresponding to analysis assembly from the selected objects as we need analysis managers of sub-analysis only. We take AnalysisExport interface from the analysis set which is inside the analysis assembly. We also update the analysis set before exporting.
#### Exporting and importing loads
    
    
    ...  
    
```vbscript
    'Here we create as many export files as the number of subanalysis
    'The exported loads are transferred to their respective
    'sub analysis with AnalysisImport interface
```

```vbscript
    For i =1 To selection1.Count
```vbscript
              Set manager = selection1.FindObject("CATIAAnalysisManager")
             'Export the computed loads
              fullPath = sout + sSep + "ComputedLoads"+ CStr(i) + ".CATAnalysisExport" 
              analysisExport.Export  fullPath, "ComputedLoads", array, manager
    
              Set analysisModel = manager.AnalysisModels.Item(1)
              Set analysisCases = analysisModel.AnalysisCases         
```vbscript
              'Import Loads  
              'Set preProCase = analysisCases.NewCase("AnalysisPreproCase")
              Set preProCase = analysisCases.Item("Preprocessing Case.1")  
              Set importCase =  preProCase.GetItem("AnalysisImport")
```

              importCase.ImportForce preProCase, fullPath, manager, NOTHING
     
```

    
    Next
    ...  
  
```

---  
#### Here we run a loop over the selected sub-analyses and export the loads. The export method requires the full path of the output file, including the file name and extension. Hence we append the file name and extension.  We create a new solution case in the sub-analysis and import the loads.
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

This use case has shown how to export and import the loads.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._

 

 

 

 
