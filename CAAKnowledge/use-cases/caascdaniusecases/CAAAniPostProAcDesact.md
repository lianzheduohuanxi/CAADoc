---
title: "Activating - Deactivating Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPostProActDeactSource", "CAAInfLauchMacro", "CAAAniPostProAcDesact"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProAcDesact.htmmd"
converted: "2026-05-11T11:27:02.504794"
---

---

      

Open the Analysis document. The Analysis document is retrieved in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
		

#### **Retrieve Analysis Cases and Analysis Sets 
		from Analysis Document**
      
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Model**.
		
		

The Analysis case is retrieved from list of cases by its index. The model 
		contains only one analysis case hence we pass 1 to the method *Item.
		*Otherwise we pass the appropriate index of the desired analysis case if there 
		are more Analysis cases. The analysis case is retrieved from the list of 
		image by its name. The name is same as that appears in the tree, in the 
		interactive environment.
      

#### Changing the Activation Status
      

#### Epilog
		

To run the macro interactively CATDocView environment variable must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to change the activation status of an image.

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
```
```

```vbscript
...
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
' Retrieve the analysis cases and the Frequency case solution
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
Set analysisImages1 = oAnalysisSet.AnalysisImages
```
```

```vbscript
...
```

```vbscript
...
```

```vbscript
'activation of an  image
'==============
'we search image Disp_Symbol
```vbscript
Set oAnalysisImage = analysisImages1.Item("Disp_Symbol")

```

'we Activate the image
oAnalysisImage.SetActivationStatus true

'we update the  image
oAnalysisImage.Update

'deactivation of an  image
'===============
'we deactivate the image
oAnalysisImage.SetActivationStatus false

'we update the  image
oAnalysisImage.Update
...
```

```vbscript
...
```vbscript
End Sub
...
```
```