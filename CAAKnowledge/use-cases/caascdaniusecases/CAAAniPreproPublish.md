---
title: "Creating Preprocessing Data from Publications"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniPreproOnPublish", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPreprocessingFeatures", "CATISamImportDefine", "CAAAniPreproOnPublishSource", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproPublish.htmmd"
converted: "2026-05-11T11:27:02.498470"
---

---

		

Create the Analysis document. The use of StartWorkbench  will customize 
		the analysis document as a generative one. it mean's that meshparts and 
		properties will be automatically created as in the Generative workbench.
		

#### Importing the Part Document and Extracting the 
		Publications
		

In order to import the document you have to give the path of this document, 
		the late type which implements CATISamImportDefine and an array of CATVariant 
		if you want to customize the import.
		
		

The part document is fetched in the documentation installation path, 
		this path has already been stored in the `sDocPath` variable. 
		In the collection of documents analysisLinkedDocuments1 , two documents 
		can be retrieved: the Analysis one and the Part document. The extraction 
		of pre defined geometrical arena is done by using the Publication interface. 
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
		

#### Defining the Load
		
		

The load is defined as the boundaries. For more information about the 
		physical type included inside analysis entities and the way to valuate them, 
		refer to the reference [2]
		

[Top]
		

#### Defining a Sensor
		
		

[Top]
		

#### Computing the Case and Printing the Sensor Value
		
		

This method will launch the mesher, generate the finite element model 
		for preprocessing and launch the solver to generate the finite element results.
		

[Top]
		

#### Creating an Image
		
		

The image is created based on the solution of the case. For this use 
		the AnalysisImages collection and create the image according to it's name. 
		Then, reframe will update the display.
		

[Top]
		

#### Exporting Data from the Image
		
		

The image is exported in the specified file. This file is defined by 
		folder, export data filename and filetype.
		

#### Deactivating the Image
		
		

The image is deactivated.
		

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
```vbscript
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If(Not CATIA.FileSystem.FolderExists(sDocPath)) Then
    Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; -----------------------------------------------------------
```

```vbscript
&#39; Get the collection of documents in session
```vbscript
    Set documents1 = CATIA.Documents

```

&#39; ----------------------------------------------------------- 
&#39; Get the collection of documents in session 
&#39; Create the CATAnalysis Document 
```vbscript
   Set TheAnalysisDocument = documents1.Add(&quot;Analysis&quot;) 
   
&#39; if WB name already is &quot;GPSCfg&quot;, not to use StartWorkbench 
```
```vbscript
   WBName = CATIA.GetWorkbenchId if (WBName &lt;&gt; &quot;GPSCfg&quot;) Then 
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
```vbscript
Dim arrayOfVariantOfShort1(0)
   analysisManager1.ImportDefineFile (sDocPath &amp; sSep &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep &amp; &quot;AnalysisMechfeat.CATPart&quot;),
```
```

```vbscript
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1
```

```vbscript
&#39; _____________________________________________________________________________________ 
&#39; Reframe All. 
```vbscript
   Set specsAndGeomWindow1 = CATIA.ActiveWindow 
   Set viewer3D1 = specsAndGeomWindow1.ActiveViewer 
   viewer3D1.Reframe 
```
&#39; _____________________________________________________________________________________ 
&#39; Scan the analysis document: Retrieve the Pointed documents to extract the reference for preprocessing 
```vbscript
   Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments 
   CATIA.SystemService.Print analysisLinkedDocuments1.Name 
   If (analysisLinkedDocuments1.Count &lt;&gt; 1 ) Then 
```
```vbscript
      Err.Raise 9999,,&quot;NbDoc Li NE 1&quot; 
   End If 
```
&#39; _____________________________________________________________________________________ 
&#39; Retrieve the CATPart Document and associated publications for preprocessing. 
```vbscript
   Set TheDoc = analysisLinkedDocuments1.Item(1) 
   CATIA.SystemService.Print TheDoc.FullName 
   Set product1 = TheDoc.Product 
   Set publications1 = product1.Publications 
   Set publication1 = publications1.Item(&quot;Bottomface&quot;) 
   Set publication2 = publications1.Item(&quot;Sliding1&quot;) 
   Set publication3 = publications1.Item(&quot;Sliding2&quot;) 
   Set publication4 = publications1.Item(&quot;ResizeBody&quot;)
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
&#39; _____________________________________________________________________________________ 
&#39; Create Slider boundary.
```vbscript
   Set analysisEntity2 = analysisEntities1.Add(&quot;SAMSurfaceSlider&quot;)
   analysisEntity2.AddSupportFromPublication product1, publication2
```
   analysisEntity2.AddSupportFromPublication product1, publication3
...
```

```vbscript
...
&#39; _____________________________________________________________________________________ 
&#39; Create Pressure.
```vbscript
   Set analysisEntities2 = analysisSet2.AnalysisEntities 
   Set analysisEntity3 = analysisEntities2.Add(&quot;SAMPressure&quot;)
   analysisEntity3.AddSupportFromPublication product1, publication4  
```
   analysisEntity3.SetValue &quot;SAMPressureMag&quot;,&quot;&quot;, 0, 0, 0, 500.
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
...
```

```vbscript
...
&#39; Launch the computation of the Case 
   MyCase.Compute ...
  
&#39; Extract the computed value of the sensor
```vbscript
   CATIA.SystemService.Print &quot; Mises Max Computed &quot; &amp; dimension1.ValueAsString
...
```
```

```vbscript
...
&#39; _____________________________________________________________________________________ 
&#39; Create corresponding image.
```vbscript
   Set analysisImages1 = analysisSet3.AnalysisImages 
   Set analysisImage1 = analysisImages1.Add(&quot;StressVonMises_Iso_Smooth&quot;, False, False, True)
 &#39; _____________________________________________________________________________________ &#39;
```
 Reframe All. 
   viewer3D1.Reframe
...
```

```vbscript
...
&#39; _____________________________________________________________________________________ 
&#39; Export data from the created image.
```vbscript
   Set fileSystem1 = CATIA.FileSystem 
   Set folder1 = fileSystem1.GetFolder(outputPath)
   analysisImage1.ExportData folder1, &quot;VonMises&quot;, &quot;txt&quot;
```
 &#39; _____________________________________________________________________________________ &#39;
 
...
```

```vbscript
...
&#39; _____________________________________________________________________________________ 
&#39; Deactivate and Update the created image.
   analysisImage1.SetActivationStatus false
   analysisImage1.Update
 &#39; _____________________________________________________________________________________ &#39;
 
...
```

```vbscript
...
```

```vbscript
...
```