---
title: "Creating Spot Welding Connection Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniMeshSpotWeldingSource", "CAAScrJavaScript", "CAAScdAniUseCases", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro", "CAAAniMeshSpotWelding"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSpotWelding.htm"
converted: "2026-05-11T11:27:02.501885"
---

---

		

Open the Analysis document. The Analysis document is retrieve in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document.  
		

#### **Extracting the Reference Object from the 
		Part Document for  Meshing**
		
		

According to the general
		[
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. 
		

The extraction of pre-defined geometric elements is done with the help 
		of Reference interface. This is equivalent to the selection of a B-Rep elements 
		inside the interactive application.
		

#### Creating Mesh Part and Assigning Values to its 
		Attributes
		
		

#### Epilog
		
		

To run the macro interactively CATDocView environment 
		variable must be defined.
		
	

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create spot welding connection mesh parts and 
how to assign values to its global attributes.

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
&#39;Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
&#39;Retrieve the analysis Manager 
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

&#39;Retrieve the part document and product
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

&#39;Retrieve the analysis model
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39;Retrieve the mesh manager and list of mesh parts
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts


&#39;Retrieve the connection design manager and connection
Set connection = oAnalysisSet.ItemByType(&quot;ConnectionDesignManager&quot;)
Set connSet = connection.AnalysisSets
Set conn = connSet.ItemByType(&quot;ConnectionDesignSet&quot;)
Set entity = conn.AnalysisEntities
Set surfConn  = entity.Item(1)
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

...
```

```vbscript
...
```

```vbscript
&#39;Add new surface analysis connection mesh to the list of mesh parts
Set surfWeld = oAnalysisMeshParts.Add (&quot;MSHPartConnWeldSurf&quot;) 

&#39;Assign previously created reference as support
surfWeld.AddSupportFromReference NOTHING, reference1


&#39;Assign values to its global specifications
spotWeldMesh.SetGlobalSpecification &quot;MaximalGap&quot;, &quot;10.0 mm&quot;
spotWeldMesh.SetGlobalSpecification &quot;MeshStep&quot;, &quot;10.0 mm&quot;
spotWeldMesh.SetGlobalSpecification &quot;StopUpdateOnError&quot;, 1
spotWeldMesh.SetGlobalSpecification &quot;SpotDiameter&quot;, &quot;2.0 mm&quot; 
spotWeldMesh.SetGlobalSpecification &quot;MiddleCombination&quot;, 3

&#39;Update Mesh
spotWeldMesh.Update

...
```

```vbscript
...
```

```vbscript
...
```