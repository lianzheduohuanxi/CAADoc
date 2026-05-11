---
title: "Creating Basic Report"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPostProBasicReportSource", "CAAInfLauchMacro", "CAAAniPostProBasicReport"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProBasicReport.htm"
converted: "2026-05-11T11:27:02.526362"
---

---

      

Open the Analysis document. The Analysis document is retrieved in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved: 
		the Analysis document and the Part document. The CATTemp 
		environment variable stores temporary data. On windows it points to
		C:\Documents and Settings\user\Local Settings\Application Data\DassaultSystemes\CATTemp and on unix it points 
		to /CATSettings/CATTemp.
		

#### **Retrieve Analysis Cases and Analysis Sets 
		from Analysis Document**
      
		

The sOut variable stores the path of the folder in which the report is 
		generated. The Analysis post manager interface manages report creation.
		

According to the general
		[
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Model**.
		
		

The Analysis case is retrieved from list of cases by its index. The model 
		contains only one analysis case hence we pass 1 to the method *Item.
		*Otherwise we pass the appropriate index of the desired case, if there 
		are more Analysis cases. The analysis case is retrieved from the list of 
		image by its name. The name is same as that appears in the tree in the 
		interactive environment.
      

#### Generate the Report
      

#### Epilog
		

To run the macro interactively CATDocView 
		environment variable must be defined.

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to generate the report with different options.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

 

 

 

 

```vbscript
...
```

```vbscript
' ----------------------------------------------------------- 
' Optional: allows to find the sample wherever it's installed
  sDocPath=CATIA.SystemService.Environ("CATDocView")
  sOut = CATIA.SystemService.Environ(&quot;CATTemp&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
' ----------------------------------------------------------- 
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
' Retrieve the folder stored in sOut
Set fileSystem1 = CATIA.FileSystem
Set folder1 = fileSystem1.GetFolder(sOut)
```

```vbscript
' Retrieve the Analysis Manager
Set oAnalysisManager = oAnalysisDocument.Analysis
			
' Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
Set oAnalysisPostManager = oAnalysisModel.PostManager
```

```vbscript
' Retrieve the analysis cases and the first analysis case
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```

```vbscript
' Retrieve the analysis cases and the Frequency case solution
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item(&quot;Frequency Case Solution.1&quot;, catAnalysisSetSearchAll)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
oAnalysisPostManager.AddExistingCaseForReport oAnalysisCase
```

```vbscript
'basic report on frequency case saved in folder1, title=test1, no image added
oAnalysisPostManager.BuildReport folder1, "Test1", False
```

```vbscript
'basic report on frequency case saved in folder1, title=test2, add created images
oAnalysisPostManager.BuildReport folder1, "test2", True
```

```vbscript
'basic report on frequency case saved in folder1, title=test3, no image added (old method)
oAnalysisPostManager.ExtractHTMLReport folder1, "test3"
```

```vbscript
...
```

```vbscript
...
End Sub
...
```