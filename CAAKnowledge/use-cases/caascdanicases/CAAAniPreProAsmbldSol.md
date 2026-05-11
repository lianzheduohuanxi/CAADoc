---
```vbscript
title: "Creating Assembled Solution"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPreProAsmbldSol", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProAsmbldSol.htm"
converted: "2026-05-11T17:31:51.786958"
```

---
## Analysis Modeler

|
## Creating Assembled Solution

* * *

  This use case shows you how to create an assembled solution. Here use of Edit/Search... capability through VB is also demonstrated. This macro opens an analysis assembly document and creates two assembled solutions. In the first assembled solution a V4 imported solution is added and in the second a static case is added. Both of these solutions are selected using the Edit/Search... capability. Assembled solution ( also called displacement assembly) is created in assembled analysis. This solution is concatenation of several solutions computed in the sub-analysis. This scenario is available only in Generative Assembly Structural Analysis (GAS) product.   ![](images/AsmbldSol.jpg)
---|---
This use case shows you how to create an assembled solution. Here use of Edit/Search... capability through VB is also demonstrated. This macro opens an analysis assembly document and creates two assembled solutions. In the first assembled solution a V4 imported solution is added and in the second a static case is added. Both of these solutions are selected using the Edit/Search... capability. Assembled solution ( also called displacement assembly) is created in assembled analysis. This solution is concatenation of several solutions computed in the sub-analysis. This scenario is available only in Generative Assembly Structural Analysis (GAS) product.   ![](images/AsmbldSol.jpg)
  CAAAniPreProAsmbldSol is launched in CATIA [1].No open document is needed. [CAAAniPreProAsmbldSol.catvbs](CAAAniPreProAsmbldSolSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPreProAsmbldSol.catvbs) (Windows only).
  CAAAniPreProAsmbldSol includes the following steps:

  1. Prolog
  2. Extracting the analysis documents and analysis models
  3. Adding the assembled solution set
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
    sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")
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
    Set analysisDocument1 = CATIA.Documents.Open(sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" &
```

```

```

```vbscript
```vbscript
```vbscript
' -----------------------------------------------------------
' Open the Analysis document
Set analysisDocument1 = CATIA.Documents.Open(sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" &
```

```

    						 sSep & "samples" & sSep & "Assembled_Loads_Slutions.CATAnalysis")
```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### **Extracting the analysis documents and analysis models**

    ...

```vbscript
    'Retrieve the Analysis Manageer from tha analysis document
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
     Set analysisCases1 = analysisModel1.AnalysisCases
```

```vbscript
```vbscript
```vbscript
    'Retrieve the second object that is Solution Case.1
    'from the list of analysis cases
    Set analysisCase1 = analysisCases1.Item(2)
    'Retrieve the analysis case
    Set analysisSets1 = analysisCase1.AnalysisSets
    'Add two Assembled solution sets
    Set analysisSet1 = analysisSets1.Add("ElfAssembledSet", catAnalysisSetOut)
    Set analysisSet2 = analysisSets1.Add("ElfAssembledSet", catAnalysisSetOut)
    'Retrieve the basic component from the analysis set
    Set basicComponents1 = analysisSet1.BasicComponents
    Set basicComponent1 = basicComponents1.GetItem("ElfAssemblyPtr.1")
    'Retrieve the basic component from the analysis set
    Set basicComponents2 = analysisSet2.BasicComponents
    Set basicComponent2 = basicComponents2.GetItem("ElfAssemblyPtr.1")
```

```

```

    ...

---
#### Here we retrieve the solution case, in which we want to add the assembled load. First the list of cases is retrieved from analysis model. The index of the analysis case is same as that of the position in which it appears in specification tree. Once we get the desired solution case we retrieve the set and add assembled solution to it. To add analysis sets to assembled solution
#### Searching through the selection and applying the selected objects

    ...

```vbscript
    'Search and select
```

```vbscript
    Set selection1 = analysisDocument1.Selection
    selection1.Search "Name=*DISP*,all"
```

```vbscript
```vbscript
```vbscript
    'Retrieve the analysis manager object from the analysis document
    Set documents1 = CATIA.Documents
    Set analysisDocument2 = documents1.Item("Analysis1.CATAnalysis")
    Set analysisManager2 = analysisDocument2.Analysis
```

```

```

```vbscript
    'Go through the selections and find out the the analysis set
```

```vbscript
```vbscript
```vbscript
'Go through the selections and find out the the analysis set
    'create a reference from the analysis set and add it to the basic component
```

```

```

```vbscript
    For i =1 To selection1.Count
```vbscript
```vbscript
              Set element = selection1.Item(i)
               IF (element.Type = "AnalysisSet" ) Then 'DO NOTHING
                  Set Reference = analysisManager2.CreateReferenceFromObject(element.Value)
```

```

                  basicComponent1.AddSupportFromProduct product2, Reference
```vbscript
             END IF

```

```

basicComponent1.AddSupportFromProduct product2, Reference
END IF
```vbscript
```vbscript
    Next
    'Search and select
```

```

    selection1.Clear
    selection1.Search "Name=*Static Case*,all"
```vbscript
```vbscript
    'Remove the last static case, since this is at the same
    'level in the analysis assembly
```

```

    selection1.Remove2(selection1.Count)
```vbscript
```vbscript
    'Go through the selections and find out the the analysis set
    'create a reference from the analysis set and add it to the basic component

```

```

```vbscript
    For i =1 To selection1.Count
```vbscript
```vbscript
              Set element = selection1.Item(i)
               IF (element.Type = "AnalysisSet" ) Then 'DO NOTHING
                   Set Reference = analysisManager2.CreateReferenceFromObject(element.Value)
```

```

                   basicComponent2.AddSupportFromProduct product2, Reference
```vbscript
             END IF

```

```

basicComponent2.AddSupportFromProduct product2, Reference
END IF
```vbscript
```vbscript
    Next
    'update the two analysis sets
```

```

    analysisSet1.Update
    analysisSet2.Update

    ...

---
#### The selection interface allows the user to search objects by providing a search string. This is equivalent of selecting objects interactively through edit search. Here it is important to understand that all the objects which match the search criterion will be selected, this may include objects which do not qualify to be set as support to assembled solutions. Hence we add only the element of type analysis set. First we search for the V4 imported mesh and set as support to the assembled solution and again we search for the static case solution which is set as support to the second assembled solution.
#### Epilog

    ...

```vbscript
End Sub

```

    ...

---

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create assembled solution and how to select object using the selection interface.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
