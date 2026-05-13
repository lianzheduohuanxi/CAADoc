---
title: "Selecting Groups for Visualization of Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPostProSelectionSource", "CAAInfLauchMacro", "CAAAniPostProSelection"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProSelection.htmmd"
converted: "2026-05-11T11:27:02.513447"
---

---

      

Open the Analysis document. The Analysis document is fetched in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved; 
		the Analysis document and the Part document. 
		

#### **Retrieve Analysis Cases and Analysis Sets 
		from Analysis Document**
      
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, and the **Analysis Model**.
		
		

The Analysis case is retrieved from list of cases by its index. The model 
		contains only one analysis case hence we pass 1 to the method *Item.
		*Otherwise we pass the appropriate index of the frequency case if there 
		are more Analysis cases. The Analysis Case is retrieved from the list of 
		image by its name. The name is same as that appears in the interactive 
		application.
      

#### Create References from 
		different Groups and set them as Selection
      
		

Creating reference from objects and setting them is achieved by Reference 
		interface. This is equivalent to selecting objects in the view using mouse. 
		The type of entities contained in the selection may be different from a 
		specification to another. For example a *Clamp *symbolizes a set of 
		nodes, a *Lineic Force *symbolizes a set of edges and a *Pressure
		*symbolizes a set of faces.
		

#### Epilog
		

To run the macro interactively CATDocView 
		environment variable must be defined.
  
    
    
       

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to assign groups to images for visualization.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

 

 

 

 

```vbscript
...
```

```vbscript
&#39; ----------------------------------------------------------- 
&#39; Optional: allows to find the sample wherever it&#39;s installed
```cpp
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 
' Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
...
```
```

```vbscript
...
```

```vbscript
' Retrieve the Analysis Manager
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
			
' Retrieve the analysis model from the list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```vbscript
' Retrieve the analysis cases and the first analysis case
```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```
```

```vbscript
' Retrieve the analysis sets and analysis set by its name
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set analysisSet2 = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
```
```

```vbscript
' Retrieve the analysis Entity and create a reference
```vbscript
Set analysisEntities1 = oAnalysisSet.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Item(1)
Set reference1 = oAnalysisManager.CreateReferenceFromObject(analysisEntity1)

```

...
```

```vbscript
...
```

```vbscript
' Retrieve the image from Frequency Case Solution and set selection 
```vbscript
Set analysisImages1 = analysisSet2.AnalysisImages
Set analysisImage1 = analysisImages1.Item("Von Mises Stress (nodal values).1")
analysisImage1.SetSelection reference1, True
```
analysisImage1.Update
```

```vbscript
' Get the list of groups and create reference from first group
```vbscript
Set oAnalysisSet = oAnalysisModel.AnalysisSets
Set analysisSet3 = analysisSets2.ItemByType("GroupSet")
Set analysisEntities2 = analysisSet3.AnalysisEntities
Set analysisEntity2 = analysisEntities2.Item(1)
Set reference2 = oAnalysisManager.CreateReferenceFromObject(analysisEntity2)

' Set the created reference for Selection in Von Mises Stress Image
analysisImage1.SetSelection reference2, False
```
analysisImage1.Update
```

```vbscript
' Remove all the selections and update
analysisImage1.ResetSelection 
analysisImage1.Update
```

```vbscript
' Retrieve the mesh part OCTREE Tetrahedron Filler
```vbscript
Set analysisSets3 = oAnalysisModel.AnalysisSets
Set oAnalysisMeshManager = analysisSets3.ItemByType("MSHMeshSet")
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set analysisMeshPart1 = oAnalysisMeshParts.Item("OCTREE Tetrahedron Mesh.1 : Part1")

'Create reference from the mesh part and set the selection
```
```vbscript
Set reference3 = oAnalysisManager.CreateReferenceFromObject(analysisMeshPart1)
analysisImage1.SetSelection reference3, True
```
analysisImage1.Update 

...
```

```vbscript
...
```vbscript
End Sub
...
```
```