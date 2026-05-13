---
title: "Specifying Occurrences for Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAAniPostProOccurrenceSource", "CAAScdAniTechArticles", "CAAAniPostProOccurrence", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProOccurrence.htmmd"
converted: "2026-05-11T11:27:02.569963"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document. 
		

#### **Retrieve Analysis Cases and Analysis Sets 
		from Analysis Document**
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models**.
		
		

The Analysis case is retrieved from list of cases by its index. The model 
		contains only one analysis case hence we pass 1 to the method *Item.
		*Otherwise we pass the appropriate index of the Frequency case if there 
		are more Analysis cases. The analysis image is retrieved from the list of 
		images by its name. The name is same as that appears in the tree, in the 
		interactive environment.
		

#### Setting the Occurrence
		
		

#### Epilog
		
		

To run the macro interactively CATDocView environment 
		variable must be defined.
		
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to specify occurrences for images.

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
```vbscript
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 
&#39; Open the Analysis document 
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
...
```
```

```vbscript
...
```

```vbscript
&#39; Retrieve the Analysis Manager
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
			
&#39; Retrieve the analysis model from the list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```vbscript
&#39; Retrieve the analysis cases and the first analysis case
```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```
```

```vbscript
&#39; Retrieve the analysis cases and the first analysis case
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item(&quot;Frequency Case Solution.1&quot;, catAnalysisSetSearchAll)
```
```

```vbscript
&#39; Get the list of image and retrieve the Von Mises Stress image by its name
```vbscript
Set oAnalysisImages = oAnalysisSet.AnalysisImages
Set oAnalysisImage = oAnalysisImages.Item(&quot;Von Mises Stress (nodal values).1&quot;)

```

...
```

```vbscript
...
```

```vbscript
&#39;Modify current occurrence of Image Von Mises Stress (nodal values)
&#39;==================================================================
oAnalysisImage.SetCurrentOccurrence 4
oAnalysisImage.Update
...
```

```vbscript
...
```

```vbscript
...
```