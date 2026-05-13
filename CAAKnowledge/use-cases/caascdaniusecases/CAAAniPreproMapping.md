---
title: "Mapping Loads"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniPreproMappingSource", "CAAScrJavaScript", "CAAScdAniUseCases", "CAAAniPreproOnPublish", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPreproMapping", "CAAAniPreprocessingFeatures", "CATISamImportDefine", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproMapping.htmmd"
converted: "2026-05-11T11:27:02.531523"
---

---

		

Create the Analysis document. The use of StartWorkbench  will customize 
		the Analysis document as a generative one. This means that meshparts and 
		properties will be automatically created as in the Generative workbench.
		

#### Importing the Part Document and Extracting the 
		Publications
		

In order to import the document you have to give the path of this document, 
		the late type which implements CATISamImportDefine and an array of CATVariant 
		if you want to customize the import.
		
		

The Part document is fetched in the documentation installation path, 
		this path has already been stored in the `sDocPath` variable. 
		In the collection of documents analysisLinkedDocuments1, two documents can 
		be retrieved: the Analysis document and the Part document. The extraction 
		of pre-defined geometrical arena is done by using the Publication interface. 
		Each publication is identified by a logical name. This is equivalent as 
		the selection of a Publication element inside the interactive applications.
		

[Top]
		

#### Creating an Analysis Case for Static Analysis
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **document**, 
		we find the **Analysis manager Object**, the **Analysis models** and 
		the **Analysis cases Objects**. From both last object (Analysis Model 
		and Analysis case), you can get access to **Analysis Sets** and **Analysis 
		entities** that defines the pre-processing actions. This step create a 
```vbscript
		new case and create two input sets (Restraint Set and Load Set) and a solution 
		set (StaticSet).
```
		

[Top]
		

#### Defining the Boundaries
		
		

From the restraint set defined on the analysis case, we retrieve the 
		collection of  analysis entities. We add to this collection a fix (clamp) 
		boundary condition and apply it on the geometry extracted from the Part 
		document. Then, same is done for the sliding conditions.
		

[Top]
		

#### Defining the Loads
		
		

The load is defined as the boundaries. For the mapping file, we will 
		use the DesignTable object. This object is created with the collection of 
		Relations. This collection is available on the **AnalysisManager** object 
		by using analysisManager1.Relations method.
		

For more information about the physical types included inside analysis 
		entities and the way to valuate them, refer to the reference [2]
		

[Top]
		

#### Computing the Case
		
		

This method will launch the mesher, generate the finite element model 
		for pre-processing and launch the solver to generate the finite element 
		results.
		

[Top]
		

#### Defining a Sensor and Printing it's 
		Value
		
		

#### Epilog
		
		

To run the macro interactively CATDocView and ADL_ODT_SLASH 
		environment variables must be defined.
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to produce in VB a complete analysis document with 
a generative way.

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
  sSep=CATIA.SystemService.Environ(&quot;ADL_ODT_SLASH&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; -----------------------------------------------------------
```

```vbscript
&#39; Get the collection of documents in session
```cpp
    Set documents1 = CATIA.Documents

```

&#39; ----------------------------------------------------------- 
&#39; Get the collection of documents in session 
&#39; Create the CATAnalysis Document 
```vbscript
   Set TheAnalysisDocument = documents1.Add(&quot;Analysis&quot;) 
   
&#39; if WB name already is &quot;GPSCfg&quot;, not to use StartWorkbench 
```
```cpp
   WBName = CATIA.GetWorkbenchId 
   if (WBName &lt;&gt; &quot;GPSCfg&quot;) Then 
```
```cpp
      CATIA.StartWorkbench(&quot;GPSCfg&quot;)
   End If
```
 ...
```

```vbscript
...
&#39;_____________________________________________________________________________________ 
&#39; Start to scan the existing structure of analysis document: Retrieve the AnalysisManager 
```vbscript
   Set analysisManager1 = TheAnalysisDocument.Analysis
```
```

```vbscript
```cpp
Dim arrayOfVariantOfShort1(0)
   analysisManager1.ImportDefineFile (sDocPath &amp; sSep &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep &amp; &quot;SimpleCrank.CATPart&quot;),
```
```

```cpp
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1
 
&#39; _____________________________________________________________________________________ 
&#39; Reframe All. 
```cpp
   Set specsAndGeomWindow1 = CATIA.ActiveWindow 
   Set viewer3D1 = specsAndGeomWindow1.ActiveViewer 
   viewer3D1.Reframe 
```
&#39; _____________________________________________________________________________________ 
&#39; Scan the analysis document: Retrieve the Pointed documents to extract the reference for pre-processing 
```cpp
   Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments 
   CATIA.SystemService.Print analysisLinkedDocuments1.Name 
   If (analysisLinkedDocuments1.Count &lt;&gt; 1 ) Then 
```
```vbscript
      Err.Raise 9999,,&quot;NbDoc Li NE 1&quot; 
   End If 
```
&#39; _____________________________________________________________________________________ 
&#39; Retrieve the CATPart Document and associated publications for pre-processing. 
```cpp
   Set TheDoc = analysisLinkedDocuments1.Item(1) 
   CATIA.SystemService.Print TheDoc.FullName 
   Set product1 = TheDoc.Product 
   Set publications1 = product1.Publications 
   Set publication1 = publications1.Item(&quot;ClampFace&quot;) 
   Set publication2 = publications1.Item(&quot;MappingFace&quot;) 
...
```
```

```vbscript
...
&#39; _____________________________________________________________________________________ 
&#39; Create a Static Case in the current analysis model. 
```vbscript
   Set analysisModels1 = analysisManager1.AnalysisModels 
   Set analysisModel1 = analysisModels1.Item(1) 
   Set analysisCases1 = analysisModel1.AnalysisCases
   
   Set analysisCase1 = analysisCases1.Add(#)
   Set analysisSets1 = analysisCase1.AnalysisSets
   Set analysisSet1 = analysisSets1.Add(&quot;RestraintSet&quot;, catAnalysisSetIn)
   Set analysisSet2 = analysisSets1.Add(&quot;LoadSet&quot;, catAnalysisSetIn)
   Set analysisSet3 = analysisCase1.AddSolution(&quot;StaticSet&quot;)
  ...
```
```

```vbscript
...
&#39; To work with the collection of entities that defines the Boundary condition.
&#39; _____________________________________________________________________________________ 
```vbscript
   Set analysisEntities1 = analysisSet1.AnalysisEntities
   Set analysisEntity1 = analysisEntities1.Add(&quot;SAMClamp&quot;)
   analysisEntity1.AddSupportFromPublication product1, publication1 
```
...
```

```vbscript
...
&#39; _____________________________________________________________________________________ 
&#39; Create Surfacic Force and apply to the publication called MappingFace

```vbscript
   Set analysisEntities2 = analysisSet2.AnalysisEntities
   Set analysisEntity3 = analysisEntities2.Add(&quot;SAMSurfacicForce&quot;)

   analysisEntity3.AddSupportFromPublication product1, publication2
```

```vbscript
   Set basicComponents1 = analysisEntity3.BasicComponents

&#39; No Local Axis is defined
```
```vbscript
   Set basicComponent1 = basicComponents1.GetItem(&quot;SAMSurfacicForceAxis.1&quot;)
   basicComponent1.SetValue &quot;&quot;, 0, 0, 0, 1
```

&#39; Valuate the vector.
```vbscript
   Set basicComponent2 = basicComponents1.GetItem(&quot;SAMSurfacicForceVector.1&quot;)
   basicComponent2.SetValue &quot;Values&quot;, 1, 1, 1, 0.000000
```
   basicComponent2.SetValue &quot;Values&quot;, 2, 1, 1, -1000000.000000
   basicComponent2.SetValue &quot;Values&quot;, 3, 1, 1, 0.000000

&#39; Create a Design Table for the mapping file and valuate the basic component
```vbscript
   Set basicComponent3 = basicComponents1.GetItem(&quot;SAMDTPtrSurfForce&quot;)
   Set designTable1 = analysisManager1.Relations.CreateDesignTable(&quot;&quot;, &quot;&quot;, False, sDocPath &amp; sSep  &amp; &quot;online&quot; &amp;
                                 sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep  &amp; &quot;MappingForCrank.txt&quot;)
```
   basicComponent3.SetValue &quot;&quot;, 0, 0, 0, designTable1

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
&#39; _____________________________________________________________________________________ 
&#39; Define a global sensor measuring the maximum value of VonMises criterion. 
```vbscript
   Set dimension1 = analysisManager1.Parameters.CreateDimension(&quot;Maximum value of VonMises criterion&quot;, &quot;PRESSURE&quot;, 0.000000)
   Set formula1 = analysisManager1.Relations.CreateFormula(&quot;Maximum value of VonMises criterion&quot;,&quot;&quot;,dimension1,
                                                 &quot;misesmax(`Finite Element Model.1/Static Case Solution.1` ) &quot;)
```
&#39; Extract the computed value of the sensor
```cpp
   CATIA.SystemService.Print &quot; Mises Max Computed &quot; &amp; dimension1. ValueAsString
...
```
```

```vbscript
...
```

```vbscript
...
```