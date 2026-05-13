---
title: "CAAAniMesh1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMesh1D", "CAAScrBase", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniApplyUserMaterialSource.htmmd"
converted: "2026-05-11T11:27:02.499530"
---

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

```vbscript
Sub CATMain(#)

'----------------------------------------------------------- 
```
'Optional: allows to find the sample wherever it's installed
```vbscript
sDocPath=CATIA.SystemService.Environ("CATDocView")
If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
'----------------------------------------------------------- 

'Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Beam.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Managar and Analysis Model
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

'Retrieve the analysis model from list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the material set from list of analysis sets
```
```vbscript
Set oAnalysisSets = oAnalysisModel.AnalysisSets 
Set oAnalysisSet = oAnalysisSets.ItemByType("MaterialSet")

'Add an new user material
```
```vbscript
Set oAnalysisEntities = oAnalysisSet.AnalysisEntities
Set oAnalysisEntity1 = oAnalysisEntities.Add("SAMUserMaterial")

'Load the catalog of materials
```
```vbscript
MaterialFile = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/CatalogForAutomation.CATMaterial")
Set oMaterial_document = CATIA.Documents.Open(MaterialFile)

'Load the catalog of materials
```
```vbscript
Set cFamilies_list = oMaterial_document.Families

'Retrieve the first family of the library
```
```vbscript
Dim ifamily_no As Integer
ifamily_no = 1
```
```vbscript
Set oFirst_family = cFamilies_list.Item(iFamily_no)

'Retrieve the list of materials from the family
```
```vbscript
Set cMaterials_list = oFirst_family.Materials

Dim imaterial_no As Integer
imaterial_no = 1
```

```vbscript
Set oMaterial1 = cMaterials_list.Item(imaterial_no)

'Retrieve a material from the list and create analysis material 
```
imaterial_no = 1
```vbscript
Set oMaterial1 = cMaterials_list.Item(imaterial_no)
Set anlysisMaterial = oMaterial1.CreateAnalysisData("SAMAnisotropicMaterial")

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

'Apply the material on the User Material
linkMode = 0
```vbscript
Set oManager = oAnalysisManager.GetItem("CATMatManagerVBExt")
oManager.ApplyMaterialOnUserMaterial oAnalysisEntity1, oMaterial1, linkMode 
```

```vbscript
End Sub

```

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

```vbscript
Sub CATMain(#)

'----------------------------------------------------------- 
```
'Optional: allows to find the sample wherever it&#39;s installed
```vbscript
sDocPath=CATIA.SystemService.Environ("CATDocView")
If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
'----------------------------------------------------------- 

'Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Beam.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

&#39;Retrieve the Analysis Managar and Analysis Model
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

&#39;Retrieve the analysis model from list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```vbscript
'Retrieve the material set from list of analysis sets
```vbscript
Set oAnalysisSets = oAnalysisModel.AnalysisSets 
Set oAnalysisSet = oAnalysisSets.ItemByType(&quot;MaterialSet&quot;)

'Add an new user material
```
```vbscript
Set oAnalysisEntities = oAnalysisSet.AnalysisEntities
Set oAnalysisEntity1 = oAnalysisEntities.Add(&quot;SAMUserMaterial&quot;)

'Load the catalog of materials
```
```vbscript
MaterialFile = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/CatalogForAutomation.CATMaterial&quot;)
Set oMaterial_document = CATIA.Documents.Open(MaterialFile)

'Load the catalog of materials
```
```vbscript
Set cFamilies_list = oMaterial_document.Families

'Retrieve the first family of the library
```
```vbscript
Dim ifamily_no As Integer
ifamily_no = 1
```
```vbscript
Set oFirst_family = cFamilies_list.Item(iFamily_no)

'Retrieve the list of materials from the family
```
```vbscript
Set cMaterials_list = oFirst_family.Materials

Dim imaterial_no As Integer
imaterial_no = 1
```

```vbscript
Set oMaterial1 = cMaterials_list.Item(imaterial_no)

'Retrieve a material from the list and create analysis material 
```
imaterial_no = 1
```vbscript
Set oMaterial1 = cMaterials_list.Item(imaterial_no)
Set anlysisMaterial = oMaterial1.CreateAnalysisData(&quot;SAMAnisotropicMaterial&quot;)

```

anlysisMaterial.PutValue &quot;SAMShearModulus_11&quot;, &quot;1e+10&quot;
anlysisMaterial.PutValue &quot;SAMShearModulus_12&quot;, &quot;1e+10&quot;
anlysisMaterial.PutValue &quot;SAMShearModulus_1Z&quot;, &quot;1e+10&quot;
anlysisMaterial.PutValue &quot;SAMShearModulus_22&quot;, &quot;1e+10&quot;
anlysisMaterial.PutValue &quot;SAMShearModulus_2Z&quot;, &quot;1e+10&quot;
anlysisMaterial.PutValue &quot;SAMShearModulus_33&quot;, &quot;1e+10&quot;
anlysisMaterial.PutValue &quot;SAMDensity&quot;, &quot;7860&quot;
anlysisMaterial.PutValue &quot;SAMThermalExpansion_X&quot;, &quot;1-e5&quot;
anlysisMaterial.PutValue &quot;SAMThermalExpansion_Y&quot;, &quot;1-e5&quot;
anlysisMaterial.PutValue &quot;SAMThermalExpansion_Z&quot;, &quot;1-e5&quot;
anlysisMaterial.PutValue &quot;SAMTensileStressLimit&quot;, &quot;1e+11&quot;
anlysisMaterial.PutValue &quot;SAMCompressiveStressLimit&quot;, &quot;2e+11&quot;
anlysisMaterial.PutValue &quot;SAMShearStressLimit&quot;, &quot;1e+10&quot;

'Apply the material on the User Material
linkMode = 0
```vbscript
Set oManager = oAnalysisManager.GetItem(&quot;CATMatManagerVBExt&quot;)
oManager.ApplyMaterialOnUserMaterial oAnalysisEntity1, oMaterial1, linkMode 
```

```vbscript
End Sub
```
```