---
title: "Creating Assembled Solution"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniPreProAsmbldSolSource", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniPreProAsmbldSol", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProAsmbldSol.htmmd"
converted: "2026-05-11T11:27:02.527850"
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
		retrieve the solution case, in which we want to add the assembled load. 
		First the list of cases is retrieved from analysis model. The index 
		of the analysis case is same as that of the position in which it appears 
		in specification tree. Once we get the desired solution case we retrieve 
		the set and add assembled solution to it. To add analysis sets to 
		assembled solution
		

#### Searching through the selection and applying the selected objects
		
		

#### The selection 
		interface allows the user to search objects by providing a search 
		string. This is equivalent of selecting objects interactively through edit 
		search. Here it is important to understand that all the objects which match the search 
		criterion will be selected, this may include objects which do not 
		qualify to be set as support to assembled solutions. Hence we add only 
		the element of type analysis set. First we search for 
		the V4 imported mesh and set as support to the assembled solution and 
		again we search for the static case solution which is set as support to 
		the second assembled solution. 
		

#### Epilog
		
		
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create assembled solution and how to select 
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
```vbscript
sDocPath=CATIA.SystemService.Environ("CATDocView")
sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 
' Open the Analysis document 
```vbscript
Set analysisDocument1 = CATIA.Documents.Open(sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" &
						 sSep & "samples" & sSep & "Assembled_Loads_Slutions.CATAnalysis")
```
...
```

```vbscript
...
```

```vbscript
'Retrieve the Analysis Manageer from tha analysis document
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
&nbsp;Set analysisCases1 = analysisModel1.AnalysisCases
&nbsp;
```
'Retrieve the second object that is Solution Case.1 
'from the list of analysis cases
```vbscript
Set analysisCase1 = analysisCases1.Item(2)
&nbsp;
```
'Retrieve the analysis case
```vbscript
Set analysisSets1 = analysisCase1.AnalysisSets
&nbsp;
```
'Add two Assembled solution sets
```vbscript
Set analysisSet1 = analysisSets1.Add(&quot;ElfAssembledSet&quot;, catAnalysisSetOut)
Set analysisSet2 = analysisSets1.Add(&quot;ElfAssembledSet&quot;, catAnalysisSetOut)
&nbsp;
```
'Retrieve the basic component from the analysis set
```vbscript
Set basicComponents1 = analysisSet1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem(&quot;ElfAssemblyPtr.1&quot;)
&nbsp;
```
'Retrieve the basic component from the analysis set
```vbscript
Set basicComponents2 = analysisSet2.BasicComponents
Set basicComponent2 = basicComponents2.GetItem(&quot;ElfAssemblyPtr.1&quot;)
```
```

```vbscript
...
```

```vbscript
...
```

```vbscript
'Search and select
```vbscript
Set selection1 = analysisDocument1.Selection
selection1.Search "Name=*DISP*,all"
```

'Retrieve the analysis manager object from the analysis document
```vbscript
Set documents1 = CATIA.Documents
Set analysisDocument2 = documents1.Item("Analysis1.CATAnalysis")
Set analysisManager2 = analysisDocument2.Analysis

```

'Go through the selections and find out the the analysis set
'create a reference from the analysis set and add it to the basic component
For i =1 To selection1.Count
```vbscript
          Set element = selection1.Item(i)
           IF (element.Type = "AnalysisSet" ) Then 'DO NOTHING
```
```vbscript
              Set Reference = analysisManager2.CreateReferenceFromObject(element.Value)
              basicComponent1.AddSupportFromProduct product2, Reference
```
         END IF
       
Next

'Search and select
selection1.Clear
selection1.Search "Name=*Static Case*,all"

'Remove the last static case, since this is at the same
'level in the analysis assembly
selection1.Remove2(selection1.Count)

'Go through the selections and find out the the analysis set
'create a reference from the analysis set and add it to the basic component
For i =1 To selection1.Count
```vbscript
          Set element = selection1.Item(i)
           IF (element.Type = "AnalysisSet" ) Then 'DO NOTHING
```
```vbscript
               Set Reference = analysisManager2.CreateReferenceFromObject(element.Value)
               basicComponent2.AddSupportFromProduct product2, Reference
```
         END IF
       
Next

'update the two analysis sets
analysisSet1.Update
analysisSet2.Update
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