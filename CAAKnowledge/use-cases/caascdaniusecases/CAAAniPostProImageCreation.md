---
title: "Generating Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPostProImageCreationSource", "CAAInfLauchMacro", "CAAAniPostProImageCreation"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProImageCreation.htm"
converted: "2026-05-11T11:27:02.552985"
---

---

      

Open the Analysis document. The Analysis document is retrieved in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved; 
		the Analysis document and the Part document. 
		

#### **Retrieve Analysis Cases and Analysis Sets 
		from Analysis Document**
      
		

According to the general
		[
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard 
		procedures to navigate or retrieve the required objects. First, from the **
		Document**, we find the **Analysis Manager Object**, and the **
		Analysis Model**.
		
		

The Analysis case is retrieved from list of cases by its index. The 
		model contains only one analysis case hence we pass 1 to the method *
		Item.
		*Otherwise we pass the appropriate index of the desired case if there 
		are more Analysis cases. The Analysis  set is retrieved from the 
		list of Analysis sets by its name. The name is same as that appears in 
		the interactive application.
      

#### Create Image under different Analysis Sets
      
		

Images can be created under different Analysis sets, for example Analysis 
		Case solution, Loads, Masses, Restraints, Properties, Nodes and Elements, 
		Computed Loads and Computed Masses. The Add method creates a new image. 
		It requires four parameters name of the image, to hide the existing images 
		or not (Boolean), 
		to show the mesh or not (Boolean), duplicate (Boolean).
		

#### Epilog
		

To run the macro interactively CATDocView 
		environment variable must be defined.
  
    
    
       

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to generate images under different Analysis sets.

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
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
&#39; ----------------------------------------------------------- 
' Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
' Retrieve the Analysis Manager
Set oAnalysisManager = oAnalysisDocument.Analysis
			
' Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```

```vbscript
' Retrieve the analysis cases and the first analysis case
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```

```vbscript
' Retrieve the analysis sets and analysis set by its name
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
```

```vbscript
' Get the list of images from analysis set 
Set oAnalysisImages = oAnalysisSet.AnalysisImages

...
```

```vbscript
...
```

```vbscript
' Create image under Frequency Case Solution.1
Set analysisImage1 = oAnalysisImages.Add("Disp_Symbol", False, False, True)
Set analysisImage2 = oAnalysisImages.Add("Mesh_Deformed", True, False, True)
```

```vbscript
' Retrieve the Restraint set from the list of analysis sets
Set analysisSet2 = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)
```

```vbscript
' Retrieve list of Analysis Images from Restraint set
Set analysisEntities1 = analysisSet2.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Item(1)
Set analysisImages2 = analysisEntity1.AnalysisImages
```

```vbscript
' Add new image under the Restraint set
Set analysisImage3 = analysisImages2.Add("Restraint", True, True, False)
```

```vbscript
...
```

```vbscript
...
End Sub
...
```