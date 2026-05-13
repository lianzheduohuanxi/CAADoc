---
title: "Creating Surface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshBasicSurfSource", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniMeshBasicSurf", "CAAAniTocAnalysisDocument", "CAAScdAniTechArticles", "CAAScdInfUseCases", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshBasicSurf.htmmd"
converted: "2026-05-11T11:27:02.546029"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path is already stored in the
		`sDocPath` variable. If this cariable is not valuated then error 
		is raised. In the collection of documents, two documents can be retrieved; 
		the Analysis document and the Part document.
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of a B-Rep elements inside the interactive application. In 
		this macro the reference is created from the published face.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

#### Here parameters 
		are set with their respective units, this helps in setting up of the parameters 
		independent of the unit settings. Calling update on the mesh part computes 
		the mesh.
		

#### Epilog
		
		

To run the macro interactively CATDocView environment 
		variables must be defined.
		
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create basic surface mesh parts and how to assign 
values to its global specifications.

 

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
```

```vbscript
&#39;----------------------------------------------------------- 
&#39;Optional: allows to find the sample wherever it&#39;s installed
```vbscript
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39;-----------------------------------------------------------
```

```vbscript
&#39;Open the Analysis document 
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
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
&#39;Retrieve the Analysis Manager and Analysis Model
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
&#39;Retreive the part document from Analysis manager
```vbscript
Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```
```

```vbscript
&#39;Retrieve the analysis model from the list of models
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)
```
```

```vbscript
&#39;Retrieve mesh manager and mesh part 
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```
```

```vbscript
&#39;Retrieve publications from product and retrieve the published surface and edge
```vbscript
Set publications1 = product.Publications
Set pubEdge = publications1.Item(&quot;Edge&quot;)
...
```
```

```vbscript
...
&#39;Add the new basic surface mesh part to the list of mesh parts
```vbscript
Set  surfPart = meshPart.Add (&quot;MSHPartBasicSurf&quot;)
```
```

```vbscript
&#39;Add support from the published surface
surfPart.AddSupportFromPublication product, pubSurf
```

```vbscript
```vbscript
&#39;Set the global Specifications
surfPart.SetGlobalSpecification &quot;GlobalMethod&quot;, 1
```
surfPart.SetGlobalSpecification &quot;QuadsOnly&quot;, 2
surfPart.SetGlobalSpecification &quot;ElementOrder&quot;, &quot;Parabolic&quot;
surfPart.SetGlobalSpecification &quot;DedicatedMesh&quot;, 1
surfPart.SetGlobalSpecification &quot;GlobalSize&quot;, &quot;10.0 mm&quot;
surfPart.SetGlobalSpecification &quot;Offset&quot;, &quot;15.0 mm&quot;
surfPart.SetGlobalSpecification &quot;TopologySize&quot;, &quot;20.0 mm&quot;
surfPart.SetGlobalSpecification &quot;TopologySag&quot;, 2
surfPart.SetGlobalSpecification &quot;SharpEdges&quot;, 1
surfPart.SetGlobalSpecification &quot;FaceAngle&quot;, &quot;0 deg&quot;
surfPart.SetGlobalSpecification &quot;OffsetFromThickness&quot;, 1
surfPart.SetGlobalSpecification &quot;MeshRelSag&quot;, 1
surfPart.SetGlobalSpecification &quot;MeshRelSagValue&quot;, &quot;0.1 mm&quot;
surfPart.SetGlobalSpecification &quot;CurveCapture&quot;, 1
surfPart.SetGlobalSpecification &quot;CurveCaptureTol&quot;, &quot;1.1 mm&quot;
surfPart.SetGlobalSpecification &quot;MeshCapture&quot;, 1
surfPart.SetGlobalSpecification &quot;MeshCaptureTol&quot;, &quot;1.1 mm&quot;
surfPart.SetGlobalSpecification &quot;MeshAbsSag&quot;, 1
surfPart.SetGlobalSpecification &quot;MeshAbsSaglValue&quot;, &quot;1.1 mm&quot;
```

```vbscript
&#39;Create local specification
```vbscript
Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add(&quot;MSHTopProjectCurve&quot;)
spec.AddSupportFromPublication &quot;ConnectorList&quot;, product1, pubCurve
```
spec.SetAttribute &quot;Tolerance&quot;, &quot;500 mm&quot;
```

```vbscript
```vbscript
Set spec = meshSpecs.Add(&quot;MSHTopProjectPoint&quot;)
spec.AddSupportFromPublication &quot;ConnectorList&quot;, product1, pubPoint
```
spec.SetAttribute &quot;Tolerance&quot;, &quot;500 mm&quot;
```

```vbscript
&#39;Update the mesh part
```

```vbscript
...
```

```vbscript
...
```vbscript
 End Sub
...
```
```