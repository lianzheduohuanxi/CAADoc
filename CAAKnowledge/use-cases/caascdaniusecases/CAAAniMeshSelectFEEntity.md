---
title: "Selecting a mesh entity (node, element)"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniMeshSelectFEEntitySource", "CAAScrJavaScript", "CAAScdAniUseCases", "CAAScdInfUseCases", "CAAAniMeshSelectFEEntity", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSelectFEEntity.htmmd"
converted: "2026-05-11T11:27:02.547047"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path is already stored in the
		`sDocPath` variable. If this variable is not valuated then error 
		is raised. In the collection of documents, two documents can be retrieved; 
		the Analysis document and the Part document.
		The **Selection** object is retrieved from the Analysis document.
		

#### Selecting a mesh element
		
		

User is prompted to select a mesh element. The filter **AnalysisMeshElement** allows to select
		either a mesh element, a mesh edge or a mesh node.
		

#### Selecting a mesh node.
		
		

#### User is prompted to select a mesh node.
		The filter **AnalysisMeshNode** allows to select a mesh node that does not belong to a mesh element.
		

#### Epilog
		
		

To run the macro interactively CATDocView environment 
		variables must be defined.
		
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to use the **Selection** object in order to select mesh entites.

 

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
```cpp
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39;-----------------------------------------------------------
```

```vbscript
&#39;Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/AllElementsAndNode.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```vbscript
&#39;Get the Selection object 
```vbscript
Set oSelection = oAnalysisDocument.Selection
```
```

```vbscript
...
```

```vbscript
...
```

```vbscript
```vbscript
&#39;Set the selection type
InputObjectType(0) = &quot;AnalysisMeshElement&quot;
```

&#39;Get the status
oStatus = oSelection.SelectElement2 ( InputObjectType, &quot;Select a mesh element&quot;, True )

&#39;Get the object in the selection
```vbscript
Set oMeshElement = oSelection.Item(1).Value

```

...
```

```vbscript
...
```

```vbscript
```vbscript
&#39;Set the selection type
InputObjectType(0) = &quot;AnalysisMeshNode&quot;
```

&#39;Get the status
oStatus = oSelection.SelectElement2 ( InputObjectType, &quot;Select a mesh node&quot;, True )

&#39;Get the object in the selection
```vbscript
Set oMeshNode = oSelection.Item(1).Value

```

...
```

```vbscript
...
```vbscript
 End Sub
...
```
```