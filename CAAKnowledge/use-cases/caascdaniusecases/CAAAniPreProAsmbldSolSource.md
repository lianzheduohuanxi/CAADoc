---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniPreProAsmbldSol"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProAsmbldSolSource.htmmd"
converted: "2026-05-11T11:27:02.493420"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose: Creates Assembled Solution sets
'            add one V4 imported solution to one of the assembled solution
'            and one static case solution to another assembled solution
'	     Update the solutions
'   Assumptions: one solution case already exist in the document
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```cpp
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
sDocPath=CATIA.SystemService.Environ("CATDocView")
sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
Set analysisDocument1 = CATIA.Documents.Open(sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "Assembled_Loads_Slutions.CATAnalysis")

'Retrieve the Analysis Manager from the analysis document
```
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

'Retrieve the analysis cases from analysis model
```
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases

'Retrieve the second object that is Solution Case.1 
```
'from the list of analysis cases
```vbscript
Set analysisCase1 = analysisCases1.Item(2)

'Retrieve the analysis case
```
```vbscript
Set analysisSets1 = analysisCase1.AnalysisSets

'Add two Assembled solution sets
```
```vbscript
Set analysisSet1 = analysisSets1.Add("ElfAssembledSet", catAnalysisSetOut)
Set analysisSet2 = analysisSets1.Add("ElfAssembledSet", catAnalysisSetOut)

'Retrieve the basic component from the analysis set
```
```vbscript
Set basicComponents1 = analysisSet1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem("ElfAssemblyPtr.1")

'Retrieve the basic component from the analysis set
```
```vbscript
Set basicComponents2 = analysisSet2.BasicComponents
Set basicComponent2 = basicComponents2.GetItem("ElfAssemblyPtr.1")

'Search and select
```
```vbscript
Set selection1 = analysisDocument1.Selection
selection1.Search "Name=*DISP*,all"
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

```vbscript
End Sub

```

```vbscript
' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose: Creates Assembled Solution sets
'            add one V4 imported solution to one of the assembled solution
'            and one static case solution to another assembled solution
'	     Update the solutions
'   Assumptions: one solution case already exist in the document
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```cpp
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
sDocPath=CATIA.SystemService.Environ("CATDocView")
sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
Set analysisDocument1 = CATIA.Documents.Open(sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "Assembled_Loads_Slutions.CATAnalysis")

'Retrieve the Analysis Manager from the analysis document
```
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

'Retrieve the analysis cases from analysis model
```
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases

'Retrieve the second object that is Solution Case.1 
```
'from the list of analysis cases
```vbscript
Set analysisCase1 = analysisCases1.Item(2)

'Retrieve the analysis case
```
```vbscript
Set analysisSets1 = analysisCase1.AnalysisSets

'Add two Assembled solution sets
```
```vbscript
Set analysisSet1 = analysisSets1.Add("ElfAssembledSet", catAnalysisSetOut)
Set analysisSet2 = analysisSets1.Add("ElfAssembledSet", catAnalysisSetOut)

'Retrieve the basic component from the analysis set
```
```vbscript
Set basicComponents1 = analysisSet1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem("ElfAssemblyPtr.1")

'Retrieve the basic component from the analysis set
```
```vbscript
Set basicComponents2 = analysisSet2.BasicComponents
Set basicComponent2 = basicComponents2.GetItem("ElfAssemblyPtr.1")

'Search and select
```
```vbscript
Set selection1 = analysisDocument1.Selection
selection1.Search "Name=*DISP*,all"
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

```vbscript
End Sub
```
```