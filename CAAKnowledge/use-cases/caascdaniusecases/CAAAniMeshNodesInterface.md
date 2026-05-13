---
title: "Creating Nodes Interface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniMeshNodesInterfaceSource", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshNodesInterface", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshNodesInterface.htmmd"
converted: "2026-05-11T11:27:02.549818"
---

---

      

Open the Analysis document. The Analysis document is retrieved in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved; 
		the Analysis document and the Part document. 
		

#### Extracting the List of Mesh Parts and 
		Publications
      

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done by using the Reference interface. This is equivalent to the 
		selection of a B-Rep element inside the interactive application. In this 
		macro reference is created from the analysis connection.

#### Creating the Mesh Part and 
		Assigning Values to its Attributes.
		

#### Epilog
		

To run the macro interactively CATDocView 
		environment variable must be defined.

 

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create nodes interface mesh parts and how to 
assign values to its global specifications.

 

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights 
reserved.*

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
' Open the Analysis document 
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis&quot;)
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
' Retrieve the analysis Manager 
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

' Retreive the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

'Retrieve the connection design manager and connection
```
```vbscript
Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
Set connSet = connection.AnalysisSets
Set conn = connSet.ItemByType("ConnectionDesignSet")
Set entity = conn.AnalysisEntities
Set surfConn  = entity.Item(1)

'Create reference from the surface analysis connection
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
```
```

```vbscript
...
```

```vbscript
...

'Add nodes interface mesh part to the list of mesh  parts
```vbscript
Set nodeMesh = oAnalysisMeshParts.Add ("MSHPartConnHalfPoint") 

```

'Assign previously create reference as support
nodeMesh.AddSupportFromReference NOTHING, reference1

'Assign values to its global specifications
nodeMesh.SetGlobalSpecification "Tolerance", "6 mm"
nodeMesh.SetGlobalSpecification "StopUpdateOnError", 2
nodeMesh.SetGlobalSpecification &quot;MiddleCombination&quot;, 1

nodeMesh.Update

...
```

```vbscript
...
```vbscript
 End Sub
...
```
```