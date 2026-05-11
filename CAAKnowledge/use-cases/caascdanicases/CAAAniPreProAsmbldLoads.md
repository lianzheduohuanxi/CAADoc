---
```vbscript
title: "Creating Assembled Loads"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniPreProAsmbldLoads", "CATIA", "CATIAAnalysisSet", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProAsmbldLoads.htm"
converted: "2026-05-11T17:31:51.779974"
```

---
## Analysis Modeler

|
## Creating Assembled Loads

* * *

  This use case shows you how to create an assembled load. Here use of Edit/Search... capability through VB is also demonstrated. This macro opens an analysis assembly document and creates an assembled load. With the use of edit search all the objects with name "load" are selected and they are applied to the load set. An assembled load is an entity defined in an assembled analysis and therefore applied on the assembled mesh. This load is the concatenation of several loads defined in the sub analyses. This scenario is available only with the Generative Assembly Structural Analysis (GAS) product.   ![](images/AsmbldLoads.jpg)
---|---
This use case shows you how to create an assembled load. Here use of Edit/Search... capability through VB is also demonstrated. This macro opens an analysis assembly document and creates an assembled load. With the use of edit search all the objects with name "load" are selected and they are applied to the load set. An assembled load is an entity defined in an assembled analysis and therefore applied on the assembled mesh. This load is the concatenation of several loads defined in the sub analyses. This scenario is available only with the Generative Assembly Structural Analysis (GAS) product.   ![](images/AsmbldLoads.jpg)
  CAAAniPreProAsmbldLoads is launched in CATIA [1]. No open document is needed. [CAAAniPreProAsmbldLoads.catvbs](CAAAniPreProAsmbldLoadsSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPreProAsmbldLoads.catvbs) (Windows only).
  CAAAniPreProAsmbldLoads includes the following steps:

  1. Prolog
  2. Extracting the analysis documents and analysis models
  3. Adding the assembled load set
  4. Searching through the selection and applying the selected objects
  5. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
    sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```

```

```vbscript
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
    Err.Raise 9999,,"No Doc Path Defined"
```vbscript
    End If
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Open the Analysis document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Assembled_Loads_Solutions.CATAnalysis")
    Set analysisDocument1 = CATIA.Documents.Open(sFilePath)
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### **Extracting the analysis documents and analysis models**

    ...

```vbscript
    'Retrieve the Analysis Manager from the analysis document
```

```vbscript
    Set analysisManager1 = analysisDocument1.Analysis
```

```vbscript
```vbscript
```vbscript
    'Retrieve the product document from the linked document
    Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
    Set productDocument1 = analysisLinkedDocuments1.Item(1)
    'From product document retrieve products
    Set product1 = productDocument1.Product
    Set products1 = product1.Products
    Set product2 = products1.Item("Analysis1.1")
    'Retrieve the analysis models and the first model
    Set analysisModels1 = analysisManager1.AnalysisModels
    Set analysisModel1 = analysisModels1.Item(1)
```

```

```

    ...

---

According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , and  **Analysis Models**. From analysis models we retrieve the **Analysis Cases.**
#### Adding the assembled load set

    ...

```vbscript
    'Retrieve the analysis cases from analysis model
```

```vbscript
```vbscript
    Set analysisCases1 = analysisModel1.AnalysisCases

```

```

```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases
```vbscript
```vbscript
    'Retrieve the first object that is Static Case.1
    'from the list of analysis cases
```

```

```

```vbscript
```vbscript
    Set analysisCase1 = analysisCases1.Item(1)

```

```

```vbscript
Set analysisCase1 = analysisCases1.Item(1)
```vbscript
    'Retrieve the analysis sets and load set
```

```

```vbscript
    Set analysisSets1 = analysisCase1.AnalysisSets
```vbscript
    Set analysisSet1 = analysisSets1.Item("Loads.1", catAnalysisSetSearchAll)
```

```

```vbscript
```vbscript
```vbscript
    'Retrieve the analysis entities from the load set
    Set analysisEntities1 = analysisSet1.AnalysisEntities
    'Add assembled loads to the list
    Set analysisEntity1 = analysisEntities1.Add("SAMLoadAssembly")
    'Retrieve the basic component from analysis entity
    Set basicComponents1 = analysisEntity1.BasicComponents
    Set basicComponent1 = basicComponents1.GetItem("SAMLoadP.1")
```

```

```

    ...

---
#### Here we retrieve the static case, in which we want to add the assembled load. First the list of cases is retrieved from analysis model. From the first object of the list we obtain the analysis case by its index. The index of the analysis case is same as that of the position in which it appears in specification tree. Once we get the desired static case we retrieve the load set and analysis entities. To this list of analysis entities we add the assembled load.
#### Searching through the selection and applying the selected objects

    ...

```vbscript
    'Search and select
```

```vbscript
    Set selection1 = analysisDocument1.Selection
    selection1.Search "Name=*Load*,all"
```

```vbscript
```vbscript
```vbscript
    'Retrieve the analysis manager object from the analysis document
    Set documents1 = CATIA.Documents
    Set analysisDocument2 = documents1.Item("Analysis1.CATAnalysis")
    Set analysisManager2 = analysisDocument2.Analysis
    'Go through the selections and find out the the analysis set
    'create a reference from the analysis set and add it to the basic component
    For i =1 To selection1.Count
    Set analysisSet = selection1.FindObject("CATIAAnalysisSet")
    Set entity =   analysisSet.AnalysisEntities.Item(1)
              IF ( entity.Type = "SAMLoadAssembly") Then 'DO NOTHING
```

```

```

```vbscript
Set analysisSet = selection1.FindObject("CATIAAnalysisSet")
```vbscript
Set entity =   analysisSet.AnalysisEntities.Item(1)
```

```

IF ( entity.Type = "SAMLoadAssembly") Then 'DO NOTHING
              ELSE
```vbscript
                  Set Reference =analysisManager2.CreateReferenceFromObject(analysisSet)
                  basicComponent1.AddSupportFromProduct product2, Reference
              END IF
```vbscript
```vbscript
    Next
    'Update the analysis set
```

```

    analysisSet1.Update

```

    ...

---
#### The selection interface allows the user to search objects by providing a search string. This is equivalent of selecting objects interactively through edit search. Here it is important to understand that all the objects which match the search criterion will be selected, this may include objects which do not qualify to be set as reference to assembled loads. These objects should be removed from the selection. Also since the search string is "load" the assembled load will also be selected but it should be added to itself hence this is prevented by explicit comparison with the name of set.
#### Epilog

    ...

```vbscript
End Sub

```

    ...

---

To run the macro interactively CATDocView environment variable must be defined.

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create assembled loads and how to select object using the selection interface.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
