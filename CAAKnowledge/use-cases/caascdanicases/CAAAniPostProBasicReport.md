---
```vbscript
title: "Creating Basic Report"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProBasicReport", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProBasicReport.htmmd"
converted: "2026-05-11T17:31:51.741561"
```

---
## Analysis Modeler

|
## Creating Basic Report

* * *

  This use case shows you how to generate basic report using VB. The macro opens an Analysis document which already contains a computed Frequency case and images. Report is generated on Frequency case solution.   ![](images/ActivateDeactivate.gif)
---|---
This use case shows you how to generate basic report using VB. The macro opens an Analysis document which already contains a computed Frequency case and images. Report is generated on Frequency case solution.   ![](images/ActivateDeactivate.gif)
  CAAAniPostProBasicReport is launched in CATIA [1]. No open document is needed. [ CAAAniPostProBasicReport](CAAAniPostProBasicReportSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPostProBasicReport.catvbs) (Windows only).
  CAAAniPostProBasicReport includes the following steps:

  1. Prolog
  2. Retrieve Analysis Cases and Analysis Sets from the Analysis Document
  3. Generate the report
  4. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sOut = CATIA.SystemService.Environ("CATTemp")
```
```

```

```

```vbscript
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
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
```vbscript
    ' -----------------------------------------------------------
    ' Open the Analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved: the Analysis document and the Part document. The CATTemp environment variable stores temporary data. On windows it points to C/Documents and Settings/user/Local Settings/Application Data/DassaultSystemes/CATTemp and on unix it points to /CATSettings/CATTemp.
#### **Retrieve Analysis Cases and Analysis Sets from Analysis Document**

    ...

```vbscript
    ' Retrieve the folder stored in sOut
```

```vbscript
```vbscript
    Set fileSystem1 = CATIA.FileSystem
```vbscript
```
```vbscript
```vbscript
    Set folder1 = fileSystem1.GetFolder(sOut)

```
```

```

```

```vbscript
```vbscript
Set folder1 = fileSystem1.GetFolder(sOut)
```vbscript
```
    ' Retrieve the Analysis Manager
```

```

```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
```vbscript
```vbscript
    ' Retrieve the analysis model from the list of models
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    Set oAnalysisPostManager = oAnalysisModel.PostManager
```
```

```

```

```vbscript
    ' Retrieve the analysis cases and the first analysis case
```

```vbscript
```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisCase = oAnalysisCases.Item(1)

```
```

```

```

```vbscript
```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
```vbscript
```
```vbscript
```vbscript
Set oAnalysisCase = oAnalysisCases.Item(1)
    ' Retrieve the analysis cases and the Frequency case solution
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)

```
```

```

```

    ...

---

The sOut variable stores the path of the folder in which the report is generated. The Analysis post manager interface manages report creation.

The sOut variable stores the path of the folder in which the report is generated. The Analysis post manager interface manages report creation.
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Model**.

The Analysis case is retrieved from list of cases by its index. The model contains only one analysis case hence we pass 1 to the method _Item._ Otherwise we pass the appropriate index of the desired case, if there are more Analysis cases. The analysis case is retrieved from the list of image by its name. The name is same as that appears in the tree in the interactive environment.

#### Generate the Report

    ...

    oAnalysisPostManager.AddExistingCaseForReport oAnalysisCase

oAnalysisPostManager.AddExistingCaseForReport oAnalysisCase
```vbscript
    'basic report on frequency case saved in folder1, title=test1, no image added
```

    oAnalysisPostManager.BuildReport folder1, "Test1", False

```vbscript
    'basic report on frequency case saved in folder1, title=test2, add created images
```

    oAnalysisPostManager.BuildReport folder1, "test2", True

```vbscript
    'basic report on frequency case saved in folder1, title=test3, no image added (old method)
```

    oAnalysisPostManager.ExtractHTMLReport folder1, "test3"

    ...

---
#### Epilog

    ...
```vbscript
    End Sub
    ...
```

---

To run the macro interactively CATDocView environment variable must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to generate the report with different options.

[Top]

* * *
#### References

[1]| [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
