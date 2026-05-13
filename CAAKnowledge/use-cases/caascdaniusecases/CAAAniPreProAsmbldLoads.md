---
title: "Creating Assembled Loads"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CATIAAnalysisSet", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAAniPreProAsmbldLoadsSource", "CAAScdAniTechArticles", "CAAAniPreProAsmbldLoads", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProAsmbldLoads.htmmd"
converted: "2026-05-11T11:27:02.509271"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document.
		

#### **Extracting the analysis documents and 
		analysis models**
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, and  **Analysis Models**. 
		From analysis models we retrieve the **Analysis Cases.**
		

#### Adding the assembled load set
		
		

#### Here we 
		retrieve the static case, in which we want to add the assembled load. 
		First the list of cases is retrieved from analysis model. From the first 
		object of the list we obtain the analysis case by its index. The index 
		of the analysis case is same as that of the position in which it appears 
		in specification tree. Once we get the desired static case we retrieve 
		the load set and analysis entities. To this list of analysis entities we 
		add the assembled load.
		

#### Searching through the selection and applying the selected objects
		
		

#### The selection 
		interface allows the user to search objects by providing a search 
		string.  
		This is equivalent of selecting objects interactively through edit 
		search. Here it is important to understand that all the objects which match the search 
		criterion will be selected, this may include objects which do not 
		qualify to be set as reference to assembled loads. These objects should 
		be removed from the selection. Also since the search string is "load" 
		the assembled load will also be selected but it should be added to 
		itself hence this is prevented by explicit comparison with the name of 
		set.
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variable must be defined.
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create assembled loads and how to select 
object using the selection interface.

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
```cpp
sDocPath=CATIA.SystemService.Environ("CATDocView")

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 
' Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Assembled_Loads_Solutions.CATAnalysis&quot;)
Set analysisDocument1 = CATIA.Documents.Open(sFilePath)
```
```

```vbscript
...
```

```vbscript
...
```

```vbscript
'Retrieve the Analysis Manager from the analysis document
```vbscript
Set analysisManager1 = analysisDocument1.Analysis

'Retrieve the product document from the linked document
```
```vbscript
Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
Set productDocument1 = analysisLinkedDocuments1.Item(1)

'From product document retrieve products
```
```vbscript
Set product1 = productDocument1.Product
Set products1 = product1.Products
Set product2 = products1.Item("Analysis1.1")

'Retrieve the analysis models and the first model
```
```vbscript
Set analysisModels1 = analysisManager1.AnalysisModels
Set analysisModel1 = analysisModels1.Item(1)

```

...
```

```vbscript
...
```

```vbscript
'Retrieve the analysis cases from analysis model
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases
```
```

```vbscript
'Retrieve the first object that is Static Case.1
'from the list of analysis cases
```vbscript
Set analysisCase1 = analysisCases1.Item(1)
```
```

```vbscript
'Retrieve the analysis sets and load set
```vbscript
Set analysisSets1 = analysisCase1.AnalysisSets
Set analysisSet1 = analysisSets1.Item("Loads.1", catAnalysisSetSearchAll)

'Retrieve the analysis entities from the load set
```
```vbscript
Set analysisEntities1 = analysisSet1.AnalysisEntities

'Add assembled loads to the list
```
```vbscript
Set analysisEntity1 = analysisEntities1.Add("SAMLoadAssembly")

'Retrieve the basic component from analysis entity
```
```vbscript
Set basicComponents1 = analysisEntity1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem("SAMLoadP.1")
...
```
```

```vbscript
...
```

```vbscript
'Search and select
```vbscript
Set selection1 = analysisDocument1.Selection
selection1.Search "Name=*Load*,all"
```

'Retrieve the analysis manager object from the analysis document
```cpp
Set documents1 = CATIA.Documents
Set analysisDocument2 = documents1.Item("Analysis1.CATAnalysis")
Set analysisManager2 = analysisDocument2.Analysis

```

'Go through the selections and find out the the analysis set
'create a reference from the analysis set and add it to the basic component
For i =1 To selection1.Count
```cpp
Set analysisSet = selection1.FindObject("CATIAAnalysisSet")
Set entity =   analysisSet.AnalysisEntities.Item(1)
          IF ( entity.Type = "SAMLoadAssembly") Then 'DO NOTHING
```
          ELSE 
```vbscript
              Set Reference =analysisManager2.CreateReferenceFromObject(analysisSet)
              basicComponent1.AddSupportFromProduct product2, Reference
```
          END IF       
Next

'Update the analysis set
analysisSet1.Update
```

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```