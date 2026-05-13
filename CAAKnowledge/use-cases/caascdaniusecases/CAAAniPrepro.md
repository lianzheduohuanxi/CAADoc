---
title: "Creating Preprocessing Data"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPreprocessingFeatures", "CAAAniPrepro", "CAAAniPreproSource", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPrepro.htmmd"
converted: "2026-05-11T11:27:02.555717"
---

---

		

Open the Analysis document. The Analysis document is fetched in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved: 
		the Analysis document and the Part document.
		

#### Extracting from the Part Document the Reference 
		Object for Preprocessing
		
		

The extraction of pre-defined geometrical arena is done by using the 
		Reference interface. This is equivalent as the selection of a B-Rep element 
		inside the interactive applications.
		

#### Navigating Inside the Analysis Document in Order 
		to Retrieve the Preprocessing Sets
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **document**, 
		we find the **Analysis manager Object**, the **Analysis models** and 
		the **Analysis cases Objects**. From both last object (Analysis Model 
		and Analysis case), you can get access to **Analysis Sets** and **Analysis 
		entities** that defines the preprocessing actions.
		

#### Defining the Boundaries
		
		

From the collection of analysis sets defined on the analysis case, we 
		retrieve the preprocessing set that allows you to define boundary conditions. 
		This set is made of analysis entities. We add to this collection a fix (clamp) 
		boundary condition and apply it on the reference extracted from the Part 
		document.
		

#### Defining the Loads
		
		

From the collection of analysis sets defined on the analysis case, we 
		retrieve the preprocessing set that allows you to define loading conditions. 
		This set is made of analysis entities. We add to this collection a momentum, 
		valuate the vector that defines this loading condition, and apply it on 
		the reference extracted from the part document.
		

For more information about the physical types included inside analysis 
		entities and the way to valuate them, refer to the reference [2]
		

#### Computing the Case
		
		

This method will launch the mesher, generate the finite element model 
		for preprocessing and launch the solver to generate the finite element results.
		

#### Epilog
		
		

 
		
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create preprocessing entities and launch a computation 
inside an Analysis document.

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
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
    &#39; ----------------------------------------------------------- 
    &#39; Open the Analysis document 
```cpp
    Dim oAnalysisDocument As Document
    Set oAnalysisDocument = CATIA.Documents.Open
        (sDocPath &amp; &quot;/CAAScdAniUseCases/samples/AnalysisCrank.CATAnalysis&quot;)
```
   ...
```

```vbscript
...
&#39; Retrieve the Part document in order to compute the references for preprocessing
```vbscript
Dim PartDocument As PartDocument
Set PartDocument = documents1.Item(3)

&#39; Retreive the Part from this document
```
```vbscript
Dim part1 As Part
Set part1 = PartDocument.Part

&#39; Retrieve the References
```
```vbscript
Dim referenceBound As Reference
Set referenceBound = part1.CreateReferenceFromName(&quot;Selection_RSur:(Face:(Brp:(GSRotate.2...));None:(#));...)&quot;)

Dim referenceLoad As Reference
Set referenceLoad = part1.CreateReferenceFromName(&quot;Selection_RSur:(Face:(Brp:(GSMRotate.2...));None:(#));...)&quot;)

&#39; Extract the product as input of preprocessing feature.
```
```vbscript
Dim product1 As Product
Set product1 = PartDocument.Product
...
```
```

```vbscript
...
    &#39;Start to scan the existing structure of the analysis document: Retrieve the Analysis Manager 
    
```vbscript
    Dim AnaManager As AnalysisManager
    Set AnaManager = oAnalysisDocument.Analysis

    &#39; Retrieve the AnalysisModels
```
```vbscript
    Dim AnaModels As AnalysisModels
    Set AnaModels = AnaManager.AnalysisModels

    &#39; To work with the first AnalysisModel of the collection
```
```vbscript
    Dim AnaModel As AnalysisModel
    &gt;Set AnaModel = AnaModels.Item(1)
    
    &#39; Retrieve the AnalysisCases
```
```vbscript
    Dim Cases As AnalysisCases
     Set Cases=AnaModel.AnalysisCases
    
    &#39; To work with the first AnalysisCase of the collection
```
```vbscript
     Dim MyCase  As AnalysisCase
     Set MyCase=Cases.Item(1)
  ...
```
```

```vbscript
...
```vbscript
    &#39; To work with the AnalysisSet of the collection that is typed for Boundary condition
    Dim MySet As AnalysisSet
    Set MySet= ListSets.ItemByType(&quot;RestraintSet&quot;)

    &#39; Retrieve the AnalysisEntities collection defined on the set.
```
```vbscript
    Dim anEntities As AnalysisEntities
    Set anEntities = MySet.AnalysisEntities

    &#39; Define an Analysis Entity on the set in order to Fix the referencebound of the part.
```
```vbscript
    Dim analysisEntity As AnalysisEntity
    Set analysisEntity = anEntities.Add(&quot;SAMClamp&quot;)
    analysisEntity.AddSupportFromProduct product1, referenceBound
```
  ...
```

```vbscript
...
```vbscript
    &#39; To work with the AnalysisSet of the collection that is typed for Loading condition
    Set MySet= ListSets.ItemByType(&quot;LoadSet&quot;)

    &#39; Retrieve the AnalysisEntities collection defined on the set.
```
```vbscript
   Set anEntities = MySet.AnalysisEntities

    &#39; Define an Analysis Entity on the set in order to load the referenceLoad of the part.
```
```vbscript
   Set analysisEntity = anEntities.Add(&quot;SAMMoment&quot;)
   
```
   
   analysisEntity.SetValue &quot;SAMMomentVector&quot;,&quot;&quot;, 1, 1, 1, 100000.
   analysisEntity.SetValue &quot;SAMMomentVector&quot;,&quot;&quot;, 2, 1, 1, 0.
   analysisEntity.SetValue &quot;SAMMomentVector&quot;,&quot;&quot;, 3, 1, 1, 0.
   
    analysisEntity.AddSupportFromProduct product1, referenceLoad
  ...
```

```vbscript
...
    &#39; Launch the computation of the Case 
    MyCase.Compute
  ...
```

```vbscript
...
```

```vbscript
...
```