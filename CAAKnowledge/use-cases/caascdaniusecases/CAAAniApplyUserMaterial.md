---
title: "Creating 1D Mesh"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro", "CAAAniApplyUserMaterialSource", "CAAAniMesh1D", "CAAAniUserMaterial"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniApplyUserMaterial.htm"
converted: "2026-05-11T11:27:02.560661"
---

---

		

Open the Analysis document. The Analysis document is fetched in the 
		documentation installation path, this path has already been stored in 
		the `sDocPath` 
		variable. In the collection of documents, two documents can be 
		retrieved: the Analysis document and the Part document. 
		

#### Adding a new user material
		
		

According to the general
		[
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard 
		procedures to navigate or retrieve the required objects. First, from the **
		Document**, we find the **Analysis Manager Object**, the **
		Analysis Models** and **Analysis Set. **We retrieve material set 
		from the list of analysis sets. A new user material is added to this 
		list.
		

#### Loading a Material Catalog and 
		Applying Analysis Properties
		
		

Here we load the material catalog specifying its full path. Inside 
		the material catalog the materials are arranged as families and lists. 
		We retrieve the first family and first list.
		

#### Creating an Analysis Material 
		and Valuating its Properties
		
		

We retrieve a material from the list and we can create an analysis 
		material of any of the supported types thanks to the method 
		CreateAnalysisData. We can call PutValue method on analysis material to 
		set appropriate values to its parameters. Finally we apply this analysis 
		material on the user material thanks to the method 
		ApplyMaterialOnUserMaterial.
		

#### Epilog
		
		

 

 
	

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case shows how to add a new user material into the model. It also 
shows how to retrieve a material from the catalog and create and valuate the 
analysis material.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
...
```

```vbscript
Sub CATMain()

'----------------------------------------------------------- 
'Optional: allows to find the sample wherever it&#39;s installed
sDocPath=CATIA.SystemService.Environ("CATDocView")
If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
'-----------------------------------------------------------
```

```vbscript
'Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Beam.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
'Retrieve the Analysis Manager and Analysis Model
Set oAnalysisManager = oAnalysisDocument.Analysis
```

```vbscript
'Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)
```

```vbscript
'Retrieve the material set from list of analysis sets
Set oAnalysisSets = oAnalysisModel.AnalysisSets 
Set oAnalysisSet = oAnalysisSets.ItemByType(&quot;MaterialSet&quot;)
```

```vbscript
'Add an new user material
Set oAnalysisEntities = oAnalysisSet.AnalysisEntities
Set oAnalysisEntity1 = oAnalysisEntities.Add(&quot;SAMUserMaterial&quot;)
```

```vbscript
...
```

```vbscript
...
'Load the catalog of materials
MaterialFile = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\CatalogForAutomation.CATMaterial&quot;)
Set oMaterial_document = CATIA.Documents.Open(MaterialFile)

'Load the catalog of materials
Set cFamilies_list = oMaterial_document.Families

'Retrieve the first family of the library
Dim ifamily_no As Integer
ifamily_no = 1
Set oFirst_family = cFamilies_list.Item(iFamily_no)

'Retrieve the list of materials from the family
Set cMaterials_list = oFirst_family.Materials

Dim imaterial_no As Integer
imaterial_no = 1

Set oMaterial1 = cMaterials_list.Item(imaterial_no)
...
```

```vbscript
...
'Retrieve a material from the list and create analysis material 
imaterial_no = 1
Set oMaterial1 = cMaterials_list.Item(imaterial_no)
Set anlysisMaterial = oMaterial1.CreateAnalysisData(&quot;SAMAnisotropicMaterial&quot;)

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
Set oManager = oAnalysisManager.GetItem(&quot;CATMatManagerVBExt&quot;)
oManager.ApplyMaterialOnUserMaterial oAnalysisEntity1, oMaterial1, linkMode
```

```vbscript
...
```

```vbscript
...
 End Sub
...
```