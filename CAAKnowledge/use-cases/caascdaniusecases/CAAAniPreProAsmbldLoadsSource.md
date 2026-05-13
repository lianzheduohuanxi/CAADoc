---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CATIAAnalysisSet", "CAAAniPreProAsmbldLoads"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreProAsmbldLoadsSource.htmmd"
converted: "2026-05-11T11:27:02.490149"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose: Creates Assembled Loads sets
'            adds one V4 imported Loads and
'            and one static case solution in the AA context
'		 Update the Loads
'   Assumptions: 
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

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Assembled_Loads_Solutions.CATAnalysis")
Set analysisDocument1 = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Manageer from tha analysis document
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

'Retrieve the second object that is Static Case.1
```
'from the list of analysis cases
```vbscript
Set analysisCase1 = analysisCases1.Item(1)

'Retrieve the analysis sets and load set
```
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

'Search and select
```
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

```vbscript
End Sub

```

```vbscript
' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose: Creates Assembled Loads sets
'            adds one V4 imported Loads and
'            and one static case solution in the AA context
'		 Update the Loads
'   Assumptions: 
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

If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Assembled_Loads_Solutions.CATAnalysis&quot;)
Set analysisDocument1 = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Manageer from tha analysis document
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

'Retrieve the second object that is Static Case.1
```
'from the list of analysis cases
```vbscript
Set analysisCase1 = analysisCases1.Item(1)

'Retrieve the analysis sets and load set
```
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

'Search and select
```
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

```vbscript
End Sub
```
```