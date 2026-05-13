---
title: "CAAAniPreproMapping.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniPreproMapping", "CATISamImportDefine", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproMappingSource.htm"
converted: "2026-05-11T17:31:51.813397"
---
tags: ["CATIA", "CAAAniPreproMapping", "CATISamImportDefine", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproMappingSource.htmmd"
converted: "2026-05-11T17:31:51.813397"
    Language="VBSCRIPT"

```vbscript
```vbscript
```cpp
    ' COPYRIGTH DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Create a New Analysis document.
    '                 Import on a CATPart document with some publication defined
    '                 Define all preprocessing data based on publications
    '                 Define a surfacique force with variable data (use mapping capability)
    '                 Launch the Computation.
    '                 Create a AnalysisSensor and display its values
    '   Assumtions:   Looks for SimpleChrank.CATPart stored in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R13
    ' ***********************************************************************
```

```

```

```cpp
    Sub CATMain(#)
```vbscript
```
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed

```cpp
      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```
```

```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
        End If
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Get the collection of documents in session
```cpp
        Set documents1 = CATIA.Documents
    ' Only one Analysis Document is required
```
    ' Create the CATAnalysis Document
```vbscript
        Set TheAnalysisDocument = documents1.Add("Analysis")
    ' if WB name already is "GPSCfg", not to use StartWorkbench
```
```

```

```cpp
        WBName = CATIA.GetWorkbenchId
        if (WBName <> "GPSCfg") Then
```
```vbscript
```vbscript
```cpp
    	CATIA.StartWorkbench("GPSCfg")
        End If
```
    '_____________________________________________________________________________________
    ' Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
    ' and link the analysis to a Part Document
```

```

```

```vbscript
```cpp
    ' We call the Import on CATAnalysisImport which implements CATISamImportDefine

```

```

```vbscript
```vbscript
```vbscript
        Set analysisManager1 = TheAnalysisDocument.Analysis

```
```

```

```vbscript
```cpp
        Dim arrayOfVariantOfShort1(0)
        analysisManager1.ImportDefineFile (sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "SimpleChrank.CATPart"),
```

```

    				       "CATAnalysisImport", arrayOfVariantOfShort1
```vbscript
    ' _____________________________________________________________________________________
```

```vbscript
```vbscript
```vbscript
' _____________________________________________________________________________________
    ' Reframe All.
```

```

```

```vbscript
```cpp
      Set specsAndGeomWindow1 = CATIA.ActiveWindow
```vbscript
```
```vbscript
      Set viewer3D1 = specsAndGeomWindow1.ActiveViewer
```
```

      viewer3D1.Reframe
```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing
```cpp
        Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
        CATIA.SystemService.Print analysisLinkedDocuments1.Name
```
```

```

```

```vbscript
       If (analysisLinkedDocuments1.Count <> 1 ) Then
```vbscript
```vbscript
```vbscript
          Err.Raise 9999,,"NbDoc Li NE 1"
       End If
```
```

```

```

```vbscript
```vbscript
```cpp
    ' _____________________________________________________________________________________
    ' Retrieve the CATPart Document and associated publications for preprocessing.
```cpp
       Set TheDoc = analysisLinkedDocuments1.Item(1)
       CATIA.SystemService.Print TheDoc.FullName

       Set product1 = TheDoc.Product
       Set publications1 = product1.Publications
       Set publication1 = publications1.Item("ClampFace")
       Set publication2 = publications1.Item("MappingFace")
    ' _____________________________________________________________________________________
```
    ' Create a Static Case in the current analysis model.
```vbscript
       Set analysisModels1 = analysisManager1.AnalysisModels
       Set analysisModel1 = analysisModels1.Item(1)

       Set analysisCases1 = analysisModel1.AnalysisCases
       Set analysisCase1 = analysisCases1.Add(#)
       Set analysisSets1 = analysisCase1.AnalysisSets

       Set analysisSet1 = analysisSets1.Add("RestraintSet", catAnalysisSetIn)
       Set analysisSet2 = analysisSets1.Add("LoadSet", catAnalysisSetIn)
       Set analysisSet3 = analysisCase1.AddSolution("StaticSet")
    ' _____________________________________________________________________________________
```
    ' Create clamp boundary and apply to the publication called ClampFace

```vbscript
       Set analysisEntities1 = analysisSet1.AnalysisEntities
       Set analysisEntity1 = analysisEntities1.Add("SAMClamp")
```
```

```

```

```vbscript
```vbscript
Set analysisEntities1 = analysisSet1.AnalysisEntities
```vbscript
```
```vbscript
Set analysisEntity1 = analysisEntities1.Add("SAMClamp")
```
```

       analysisEntity1.AddSupportFromPublication product1, publication1
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create Surfacic Force and apply to the publication called MappingFace

```vbscript
       Set analysisEntities2 = analysisSet2.AnalysisEntities
       Set analysisEntity3 = analysisEntities2.Add("SAMSurfacicForce")

```
```

```

```

```vbscript
```vbscript
Set analysisEntities2 = analysisSet2.AnalysisEntities
```vbscript
```
```vbscript
Set analysisEntity3 = analysisEntities2.Add("SAMSurfacicForce")
```
```

       analysisEntity3.AddSupportFromPublication product1, publication2

```

```vbscript
```vbscript
       Set basicComponents1 = analysisEntity3.BasicComponents
```vbscript
```
```vbscript
    ' No Local Axis is defined
```vbscript
       Set basicComponent1 = basicComponents1.GetItem("SAMSurfacicForceAxis.1")
```
```

```

       basicComponent1.SetValue "", 0, 0, 0, 1
```vbscript
```vbscript
    ' Valuate the vector.
```vbscript
       Set basicComponent2 = basicComponents1.GetItem("SAMSurfacicForceVector.1")
```
```

```

       basicComponent2.SetValue "Values", 1, 1, 1, 0.000000
       basicComponent2.SetValue "Values", 2, 1, 1, -1000000.000000
       basicComponent2.SetValue "Values", 3, 1, 1, 0.000000
```

```vbscript
```vbscript
```vbscript
    ' Create a Design Table for the mapping file and valuate the basic component
```vbscript
       Set basicComponent3 = basicComponents1.GetItem("SAMDTPtrSurfForce")
       Set designTable1 = analysisManager1.Relations.CreateDesignTable("", "", False, sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "MappingForCrank.txt")
```
```

```

```

```vbscript
```vbscript
```vbscript
' Create a Design Table for the mapping file and valuate the basic component
```vbscript
Set basicComponent3 = basicComponents1.GetItem("SAMDTPtrSurfForce")
Set designTable1 = analysisManager1.Relations.CreateDesignTable("", "", False, sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "MappingForCrank.txt")
```
```

```

       basicComponent3.SetValue "", 0, 0, 0, designTable1
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Launch Computation.
```

```

      analysisCase1.Compute
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Define a global sensor measuring the maximum value of VonMises criterion.

```cpp
      Set dimension1 = analysisManager1.Parameters.CreateDimension("Maximum value of VonMises criterion", "PRESSURE", 0.000000)
      Set formula1 = analysisManager1.Relations.CreateFormula("Maximum value of VonMises criterion","",dimension1,"misesmax(`Finite Element Model.1/Static Case Solution.1` ) ")
      CATIA.SystemService.Print " Mises Max Computed " & dimension1.ValueAsString
    ' _____________________________________________________________________________________
```
```

```

      viewer3D1.Reframe
```

```vbscript
```vbscript
```vbscript
    '------------------------------- END   END   END   ----------------------------
```cpp
      CATIA.DisplayFileAlerts = False
    '  TheAnalysisDocument.Close
```
```

```

```

```vbscript
```vbscript
    End Sub

```
```
