---
title: "Creating 1D Mesh"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAScdAniUseCases", "CAAAniMesh1D", "CAAAniUserMaterial"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniApplyUserMaterial.htm"
converted: "2026-05-11T17:31:51.596555"
---
## Analysis Modeler

|
## Creating and applying user material

* * *

  This use case shows how to create a user material and how to apply analysis material property to it. This macro opens an Analysis document. It opens a material catalog retrieves a material. Then it creates an analysis material valuating all its parameters and apply the analysis material to the user material. ![](images/UserMaterial.gif)
---|---
This use case shows how to create a user material and how to apply analysis material property to it. This macro opens an Analysis document. It opens a material catalog retrieves a material. Then it creates an analysis material valuating all its parameters and apply the analysis material to the user material. ![](images/UserMaterial.gif)
  CAAAniMesh1D is launched in CATIA [1]. No open document is needed. [CAAAniUserMaterial.CATScript](CAAAniApplyUserMaterialSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniUserMaterial.CATScript) (Windows only).
  CAAAniMesh1D includes the following steps:

  1. Prolog
  2. Adding a New User Material
  3. Loading the Material Catalog and retrieving a Material
  4. Creating an Analysis Material and Valuating its properties
  5. Epilog

#### Prolog

|

    ...

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
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
```vbscript
    End If
    '-----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```vbscript
'-----------------------------------------------------------
    'Open the Analysis document
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Beam.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
```cpp
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```
```

```

    ...

---

Open the Analysis document. The Analysis document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved: the Analysis document and the Part document.
#### Adding a new user material

    ...

```vbscript
    'Retrieve the Analysis Manager and Analysis Model
```

```vbscript
```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
```
    'Retrieve the analysis model from the list of models
```

```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisModel = oAnalysisManager.Item(1)

```
```

```

```

```vbscript
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
```vbscript
Set oAnalysisModel = oAnalysisManager.Item(1)
    'Retrieve the material set from list of analysis sets
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisSets = oAnalysisModel.AnalysisSets
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisSet = oAnalysisSets.ItemByType("MaterialSet")

```
```

```

```

```vbscript
```vbscript
Set oAnalysisSets = oAnalysisModel.AnalysisSets
```vbscript
```
```vbscript
```vbscript
Set oAnalysisSet = oAnalysisSets.ItemByType("MaterialSet")
    'Add an new user material
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisEntities = oAnalysisSet.AnalysisEntities
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisEntity1 = oAnalysisEntities.Add("SAMUserMaterial")

```
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and **Analysis Set.** We retrieve material set from the list of analysis sets. A new user material is added to this list.
#### Loading a Material Catalog and Applying Analysis Properties

    ...
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and **Analysis Set.** We retrieve material set from the list of analysis sets. A new user material is added to this list.
```vbscript
```vbscript
    'Load the catalog of materials
```cpp
    MaterialFile = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/CatalogForAutomation.CATMaterial")

```
```

```

```vbscript
```cpp
    Set oMaterial_document = CATIA.Documents.Open(MaterialFile)
```
```

```vbscript
```vbscript
```vbscript
    'Load the catalog of materials
```vbscript
    Set cFamilies_list = oMaterial_document.Families
    'Retrieve the first family of the library
```
```vbscript
    Dim ifamily_no As Integer
```
```

```

    ifamily_no = 1
```vbscript
    Set oFirst_family = cFamilies_list.Item(iFamily_no)
```vbscript
```
```vbscript
    'Retrieve the list of materials from the family
```vbscript
    Set cMaterials_list = oFirst_family.Materials

    Dim imaterial_no As Integer
```
```

```

    imaterial_no = 1

```vbscript
    Set oMaterial1 = cMaterials_list.Item(imaterial_no)
```
```

    ...

---

Here we load the material catalog specifying its full path. Inside the material catalog the materials are arranged as families and lists. We retrieve the first family and first list.
#### Creating an Analysis Material and Valuating its Properties

    ...
Here we load the material catalog specifying its full path. Inside the material catalog the materials are arranged as families and lists. We retrieve the first family and first list.
```vbscript
    'Retrieve a material from the list and create analysis material
```

    imaterial_no = 1

```vbscript
```vbscript
    Set oMaterial1 = cMaterials_list.Item(imaterial_no)
```vbscript
```
```vbscript
```vbscript
    Set anlysisMaterial = oMaterial1.CreateAnalysisData("SAMAnisotropicMaterial")

```
```

```

```

```vbscript
```vbscript
Set oMaterial1 = cMaterials_list.Item(imaterial_no)
```vbscript
```
```vbscript
Set anlysisMaterial = oMaterial1.CreateAnalysisData("SAMAnisotropicMaterial")
```
```

    anlysisMaterial.PutValue "SAMShearModulus_11", "1e+10"
    anlysisMaterial.PutValue "SAMShearModulus_12", "1e+10"
    anlysisMaterial.PutValue "SAMShearModulus_1Z", "1e+10"
    anlysisMaterial.PutValue "SAMShearModulus_22", "1e+10"
    anlysisMaterial.PutValue "SAMShearModulus_2Z", "1e+10"
    anlysisMaterial.PutValue "SAMShearModulus_33", "1e+10"
    anlysisMaterial.PutValue "SAMDensity", "7860"
    anlysisMaterial.PutValue "SAMThermalExpansion_X", "1-e5"
    anlysisMaterial.PutValue "SAMThermalExpansion_Y", "1-e5"
    anlysisMaterial.PutValue "SAMThermalExpansion_Z", "1-e5"
    anlysisMaterial.PutValue "SAMTensileStressLimit", "1e+11"
    anlysisMaterial.PutValue "SAMCompressiveStressLimit", "2e+11"
    anlysisMaterial.PutValue "SAMShearStressLimit", "1e+10"
```vbscript
    'Apply the material on the User Material
```

    linkMode = 0
```

```vbscript
```cpp
    Set oManager = oAnalysisManager.GetItem("CATMatManagerVBExt")
    oManager.ApplyMaterialOnUserMaterial oAnalysisEntity1, oMaterial1, linkMode
```

```

    ...

---

We retrieve a material from the list and we can create an analysis material of any of the supported types thanks to the method CreateAnalysisData. We can call PutValue method on analysis material to set appropriate values to its parameters. Finally we apply this analysis material on the user material thanks to the method ApplyMaterialOnUserMaterial.
#### Epilog

    ...
```vbscript
     End Sub
```
    ...

---

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case shows how to add a new user material into the model. It also shows how to retrieve a material from the catalog and create and valuate the analysis material.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
