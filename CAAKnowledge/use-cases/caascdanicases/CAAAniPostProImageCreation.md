---
title: "Generating Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniPostProImageCreation", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProImageCreation.htm"
converted: "2026-05-11T17:31:51.754031"
---
## Analysis Modeler

|
## Generating Images

* * *

  This use case shows you how to generate image under different Analysis Sets. The macro opens an Analysis document which already contains a computed frequency case and images. Images are created under Restraints.1 and Frequency Case Solution.1.   ![](images/ImageCreation.gif)
---|---
This use case shows you how to generate image under different Analysis Sets. The macro opens an Analysis document which already contains a computed frequency case and images. Images are created under Restraints.1 and Frequency Case Solution.1.   ![](images/ImageCreation.gif)
  CAAAniPostProImageCreation is launched in CATIA [1]. No open document is needed. [ CAAAniPostProImageCreation.catvbs](CAAAniPostProImageCreationSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPostProImageCreation.catvbs) (Windows only).
  CAAAniPostProImageCreation includes the following steps:

  1. Prolog
  2. Retrieve Analysis Cases and Analysis Sets from the Analysis Document
  3. Create Image under different Analysis Sets
  4. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```cpp
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```cpp
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
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### **Retrieve Analysis Cases and Analysis Sets from Analysis Document**

    ...

```vbscript
    ' Retrieve the Analysis Manager
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
    ' Retrieve the analysis sets and analysis set by its name
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

```vbscript
```vbscript
Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
```vbscript
```
    ' Get the list of images from analysis set
```

```

```vbscript
```vbscript
```vbscript
    Set oAnalysisImages = oAnalysisSet.AnalysisImages

```
```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , and the **Analysis Model**.

The Analysis case is retrieved from list of cases by its index. The model contains only one analysis case hence we pass 1 to the method _Item._ Otherwise we pass the appropriate index of the desired case if there are more Analysis cases. The Analysis  set is retrieved from the list of Analysis sets by its name. The name is same as that appears in the interactive application.
#### Create Image under different Analysis Sets

    ...

```vbscript
    ' Create image under Frequency Case Solution.1
```

```vbscript
```vbscript
    Set analysisImage1 = oAnalysisImages.Add("Disp_Symbol", False, False, True)
```vbscript
```
```vbscript
```vbscript
    Set analysisImage2 = oAnalysisImages.Add("Mesh_Deformed", True, False, True)

```
```

```

```

```vbscript
```vbscript
Set analysisImage1 = oAnalysisImages.Add("Disp_Symbol", False, False, True)
```vbscript
```
```vbscript
```vbscript
Set analysisImage2 = oAnalysisImages.Add("Mesh_Deformed", True, False, True)
    ' Retrieve the Restraint set from the list of analysis sets
```
```

```

```

```vbscript
```vbscript
```vbscript
    Set analysisSet2 = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)

```
```

```

```vbscript
```vbscript
Set analysisSet2 = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)
```vbscript
```
    ' Retrieve list of Analysis Images from Restraint set
```

```

```vbscript
```vbscript
    Set analysisEntities1 = analysisSet2.AnalysisEntities
```vbscript
```
```vbscript
```vbscript
    Set analysisEntity1 = analysisEntities1.Item(1)
    Set analysisImages2 = analysisEntity1.AnalysisImages

```
```

```

```

```vbscript
```vbscript
Set analysisImages2 = analysisEntity1.AnalysisImages
```vbscript
```
    ' Add new image under the Restraint set
```

```

```vbscript
```vbscript
```vbscript
    Set analysisImage3 = analysisImages2.Add("Restraint", True, True, False)

```
```

```

    ...

---

Images can be created under different Analysis sets, for example Analysis Case solution, Loads, Masses, Restraints, Properties, Nodes and Elements, Computed Loads and Computed Masses. The Add method creates a new image. It requires four parameters name of the image, to hide the existing images or not (Boolean), to show the mesh or not (Boolean), duplicate (Boolean).
#### Epilog

    ...
```vbscript
    End Sub
    ...
```

---

To run the macro interactively CATDocView environment variable must be defined.
  |

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to generate images under different Analysis sets.

[Top]

* * *
#### References

[1]| [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
