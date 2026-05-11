---
```vbscript
title: "CAAAniMesh1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMesh1D"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniApplyUserMaterialSource.htm"
converted: "2026-05-11T17:31:51.598559"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:  	Create User Material
    '               Retrieve the material from material catalog
    '               Apply analysis properties to the material.
    '  Assumptions:  The material catalog is not empty
    '  Author:       bmw
    '  Languages:    CATScript
    '  Locales:      English
    '  CATIA Level:  V5R18
    '***********************************************************************

```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```

```

```vbscript
    Err.Raise 9999,,"No Doc Path Defined"
```vbscript
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
    'Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Beam.CATAnalysis")
```

```

```

```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```

```

```vbscript
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
    'Retrieve the Analysis Managar and Analysis Model
```

```

```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```

```vbscript
```vbscript
```vbscript
    'Retrieve the analysis model from list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```

```

```

```vbscript
    'Retrieve the material set from list of analysis sets
```

```vbscript
    Set oAnalysisSets = oAnalysisModel.AnalysisSets
```vbscript
```vbscript
    Set oAnalysisSet = oAnalysisSets.ItemByType("MaterialSet")

```

```

```

```vbscript
Set oAnalysisSets = oAnalysisModel.AnalysisSets
```vbscript
```vbscript
Set oAnalysisSet = oAnalysisSets.ItemByType("MaterialSet")
    'Add an new user material
```

```

```

```vbscript
    Set oAnalysisEntities = oAnalysisSet.AnalysisEntities
```vbscript
    Set oAnalysisEntity1 = oAnalysisEntities.Add("SAMUserMaterial")
```

```

```vbscript
```vbscript
```vbscript
    'Load the catalog of materials
    MaterialFile = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\CatalogForAutomation.CATMaterial")
    Set oMaterial_document = CATIA.Documents.Open(MaterialFile)
    'Load the catalog of materials
    Set cFamilies_list = oMaterial_document.Families
    'Retrieve the first family of the library
    Dim ifamily_no As Integer
```

```

    ifamily_no = 1
    Set oFirst_family = cFamilies_list.Item(iFamily_no)
```vbscript
```vbscript
    'Retrieve the list of materials from the family
    Set cMaterials_list = oFirst_family.Materials

    Dim imaterial_no As Integer
```

```

    imaterial_no = 1

    Set oMaterial1 = cMaterials_list.Item(imaterial_no)
```vbscript
    'Retrieve a material from the list and create analysis material
```

    imaterial_no = 1
    Set oMaterial1 = cMaterials_list.Item(imaterial_no)
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

```vbscript
    Set oManager = oAnalysisManager.GetItem("CATMatManagerVBExt")
    oManager.ApplyMaterialOnUserMaterial oAnalysisEntity1, oMaterial1, linkMode

```

```vbscript
    End Sub

```
