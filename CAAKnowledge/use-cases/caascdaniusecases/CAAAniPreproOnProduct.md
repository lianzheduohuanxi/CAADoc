---
title: "Creating Connection Properties on a Product"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIAParameter", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CATIAConstraints", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAAniPreproOnProduct", "CAAScdAniTechArticles", "CAAAniPreprocessingFeatures", "CATISamImportDefine", "CAAInfLauchMacro", "CAAAniPreproOnProductSource"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnProduct.htmmd"
converted: "2026-05-11T11:27:02.495592"
---

---

		

Create the Analysis document. The use of StartWorkbench will customize 
		the analysis document as a generative one. This means that meshparts and 
		properties will be automatically created as in the Generative workbench.
		

#### Importing the Product Document and Extracting 
		the Publications
		

In order to import the document you have to give the path of this document, 
		the late type which implements CATISamImportDefine and an array of CATVariant 
		if you want to customize the import.

 
		
		

The product document is fetched in the documentation installation path, 
		this path has already been stored in the `sDocPath` variable. 
		In the collection of documents analysisLinkedDocuments1, two documents can 
		be retrieved: the Analysis document and the Product document. The extraction 
		of pre-defined geometrical arena is done by using the Publication interface. 
		Each publication is identified by a logical name. This is equivalent as 
		the selection of a Publication element inside the interactive applications. 
		Other used support is the assembly constraints. For this we also extract 
		from the product the constraints collection.
		

[Top]
		

#### Creating a Virtual Part and a Property Connection
		

**Virtual Parts** are structures created without a geometric support. 
		They represent bodies for which no geometry model is available, but which 
		play a role in the structural analysis of single part or assembly systems. 
		Virtual Parts are used to transmit actions at a distance. Therefore they 
		can be thought of as rigid bodies, except for the case where a lumped flexibility 
		is explicitly introduced by the means of a spring element. For each hole 
		we will create a Rigid virtual part in order to distribute a global force 
		to a linked face.
		
		

**Connections properties** are assembly connections used to specify 
		the boundary interactions between bodies in an assembled system. Once the 
		geometric assembly positioning constraints are defined at the Product level, 
		the user can specify the physical nature of the constraints. We will use 
		in this scenario a **Fastened Connection** that represents the link between 
		two bodies which are fastened together at their common boundary, and will 
		behave as if they were a single body. From a finite element model viewpoint, 
		this is equivalent to the situation where the corresponding nodes of two 
		compatible meshes are merged together. However, since bodies can be meshed 
		independently, the Fastened Connection is designed to handle incompatible 
		meshes.
		
		

[Top]
		

#### Creating an Analysis Case for Static Analysis
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **document**, 
		we find the **Analysis manager Object**, the **Analysis models** and 
		the **Analysis cases Objects**. From both last object (Analysis Model 
		and Analysis case), you can get access to **Analysis Sets** and **Analysis 
		entities** that defines the preprocessing actions. This step create a 
```vbscript
		new case and create two input sets (Restraint Set and Load Set) and a solution 
		set (StaticSet).
```
		

[Top]
		

#### Defining the Boundaries
		
		

From the restraint set defined on the analysis case, we retrieve the 
		collection of  analysis entities. We add to this collection a fix (clamp) 
		boundary condition and apply it on the geometry extracted from the Product 
		document.
		

[Top]
		

#### Defining the Loads
		
		

The load is defined as the boundaries. In this case the support is the 
		virtual part created before. To use the method with a Reference use AnalysisManager.CreateReferenceFromObject 
		that will transform the analysis entity into a reference.
		

[Top]
		

#### Extracting Data from a Basic Component
		
		

[Top]
		

#### Computing the Case
		
		

This method will launch the mesher, generate the finite element model 
		for preprocessing.
		

[Top]
		

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
&#39;_____________________________________________________________________________________
&#39; Optional: allows to find the sample wherever it&#39;s installed

```vbscript
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
  sSep=CATIA.SystemService.Environ(&quot;ADL_ODT_SLASH&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39;_____________________________________________________________________________________
&#39; Get the collection of documents in session
```vbscript
  Set documents1 = CATIA.Documents
&#39; ----------------------------------------------------------- 
```
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
&#39; Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
```vbscript
  Set analysisManager1 = TheAnalysisDoc.Analysis
```
```

```vbscript
```vbscript
Dim arrayOfVariantOfShort1(0)
  analysisManager1.ImportDefineFile (sDocPath &amp; sSep  &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot;
```
                                     &amp; sSep &amp; &quot;samples&quot; &amp; sSep &amp; &quot;basic_assembly.CATProduct&quot;),
```

```vbscript
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1

&#39; _____________________________________________________________________________________
&#39; Reframe All.
```vbscript
  Set specsAndGeomWindow2 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow2.ActiveViewer
  viewer3D1.Reframe 
```

&#39; _____________________________________________________________________________________
&#39; Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing
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
&#39; Retrieve the CATProduct Document and associated publications and constraints collection.

```vbscript
  Set productDocument1 = analysisLinkedDocuments1.Item(1)

  Set product1 = productDocument1.Product
  Set products1 = product1.Products

  Set publications1 = product1.Publications
  Set constraints1 = product1.Connections(&quot;CATIAConstraints&quot;)
...
```
```

```vbscript
...
&#39; _____________________________________________________________________________________
&#39; Create a Virtual Part in the analysis model to transmit the load.
```vbscript
Set analysisSets1 = analysisModel1.AnalysisSets
Set analysisSet1 = analysisSets1.ItemByType(&quot;PropertySet&quot;)

Set analysisEntities1 = analysisSet1.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Add(&quot;SAMVirPartRigid&quot;)
Set publication1 = publications1.Item(&quot;FaceCylinderTop&quot;)
analysisEntity1.AddSupportFromPublication product1, publication1
```
```vbscript
Set basicComponents1 = analysisEntity1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem(&quot;SAMRigSlavePoint.1&quot;)
Set publication4 = publications1.Item(&quot;ForceHandler&quot;)
basicComponent1.AddSupportFromPublication product1, publication4
```

...
```

```vbscript
...
&#39; _____________________________________________________________________________________
&#39; Create a Fastened connection in the analysis model to complete the constraints 
&#39; definition
```vbscript
Set analysisEntity2 = analysisEntities1.Add(&quot;SAMFaceFaceFastened&quot;)
Set constraint1 = constraints1.Item(&quot;Surface contact.2&quot;)
analysisEntity2.AddSupportFromConstraint product1, constraint1
```

...
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
&#39; _____________________________________________________________________________________
&#39; Create clamp boundary. Associated to a publication
```vbscript
Set analysisEntities2 = analysisSet2.AnalysisEntities
Set analysisEntity3 = analysisEntities2.Add(&quot;SAMClamp&quot;)
Set publication2 = publications1.Item(&quot;FaceToClamp&quot;)
analysisEntity3.AddSupportFromPublication product1, publication2
```
...
```

```vbscript
...
&#39; _____________________________________________________________________________________
&#39; Create load boundary. Associated to the virtual part
```vbscript
Set analysisEntities3 = analysisSet3.AnalysisEntities

Set analysisEntity4 = analysisEntities3.Add(&quot;SAMDistributedForce&quot;)
Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity1)
analysisEntity4.AddSupportFromReference reference2, reference2
```

```vbscript
Set basicComponents2 = analysisEntity4.BasicComponents
Set basicComponent2 = basicComponents2.GetItem(&quot;SAMForceAxis.1&quot;)
basicComponent2.SetValue &quot;Values&quot;, 0, 0, 0, 1
```
```vbscript
Set basicComponent3 = basicComponents2.GetItem(&quot;SAMForceVector.1&quot;)
basicComponent3.SetDimensions 3, 1, 1
```
basicComponent3.SetValue &quot;&quot;, 1, 1, 1, 100.000000
basicComponent3.SetValue &quot;&quot;, 2, 1, 1, 0.000000
basicComponent3.SetValue &quot;&quot;, 3, 1, 1, 0.000000
...
```

```vbscript
...
&#39; Some examples to read the data on the basic component
&#39;In this case, direct read 
```vbscript
CATIA.SystemService.Print &quot; ForceVector &quot; &amp; basicComponent3.GetValue(&quot;&quot;, 1, 1, 1) 
CATIA.SystemService.Print &quot; ForceVector &quot; &amp; basicComponent3.GetValue(&quot;&quot;, 2, 1, 1)
CATIA.SystemService.Print &quot; ForceVector &quot; &amp; basicComponent3.GetValue(&quot;&quot;, 3, 1, 1)

CATIA.SystemService.Print &quot; ForceVector Type &quot; &amp; basicComponent3.Type  
CATIA.SystemService.Print &quot; ForceVector Dimension &quot; &amp; basicComponent3.GetLinesNumber  (&quot;&quot;)
CATIA.SystemService.Print &quot; ForceVector Dimension &quot; &amp; basicComponent3.GetColumnsNumber(&quot;&quot;)
CATIA.SystemService.Print &quot; ForceVector Dimension &quot; &amp; basicComponent3.GetLayersNumber (&quot;&quot;)

&#39;In this case, use the Kwe CATIAParameter interface.
```
```vbscript
Set ParametersList = analysisManager1.Parameters
Set SubList = ParametersList.SubList(basicComponent3,FALSE)

For i = 1 to SubList.Count
```
```vbscript
	Set Parameter = SubList.Item(i)
	CATIA.SystemService.Print Parameter.Name  
	CATIA.SystemService.Print Parameter.ValueAsString
Next
```

...
```

```vbscript
...
&#39; Launch the computation of the Case 
   MyCase.ComputeMeshOnly ...
  
...
```

```vbscript
...
```

```vbscript
...
```