---
```vbscript
title: "CAAAniPreproOnProduct.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATISamImportDefine", "CATIAParameter", "CATIAConstraints", "CAAScdAniUseCases", "CATIA", "CAAAniPreproOnProduct"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnProductSource.htmmd"
converted: "2026-05-11T17:31:51.826370"
```

---
tags: ["CATISamImportDefine", "CATIAParameter", "CATIAConstraints", "CAAScdAniUseCases", "CATIA", "CAAAniPreproOnProduct"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnProductSource.htmmd"
converted: "2026-05-11T17:31:51.826370"
    Language="VBSCRIPT"

```vbscript
```vbscript
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Create a New Analysis document.
    '                 Import on a CATProduct document with some publication defined
    '                 Define all preprocessing data based on constraints and publications
    '                 Launch the Computation.
    '                 Extract some values stored in the document
    '   Assumptions:   Looks for basic_assembly.CATProduct stored in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R13
    ' ***********************************************************************
```

```

```

```vbscript
    Sub CATMain(#)
```vbscript
```
```vbscript
    '_____________________________________________________________________________________
    ' Optional: allows to find the sample wherever it's installed

```vbscript
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
    '_____________________________________________________________________________________
    ' Get the collection of documents in session
```vbscript
      Set documents1 = CATIA.Documents
    ' Create the CATAnalysis Document
```
```vbscript
      Set TheAnalysisDoc = documents1.Add("Analysis")
    ' Only one Analysis Document is required
```
    ' if WB name already is "GPSCfg", not to use StartWorkbench
```

```

```vbscript
      WBName = CATIA.GetWorkbenchId
      if (WBName <> "GPSCfg") Then
```
```vbscript
```vbscript
```vbscript
         CATIA.StartWorkbench("GPSCfg")
      End If
```
    '_____________________________________________________________________________________
    ' Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
    ' We call the Import on CATAnalysisImport which implements CATISamImportDefine
```

```

```

```vbscript
```vbscript
```vbscript
      Set analysisManager1 = TheAnalysisDoc.Analysis

```
```

```

```vbscript
```vbscript
      Dim arrayOfVariantOfShort1(0)
      analysisManager1.ImportDefineFile (sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "basic_assembly.CATProduct"),				     "
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
```vbscript
      Set specsAndGeomWindow2 = CATIA.ActiveWindow
```vbscript
```
```vbscript
      Set viewer3D1 = specsAndGeomWindow2.ActiveViewer
```
```

      viewer3D1.Reframe

```

```vbscript
```vbscript
Set viewer3D1 = specsAndGeomWindow2.ActiveViewer
```
```

viewer3D1.Reframe
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing

```

```

```vbscript
```vbscript
      Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
```vbscript
```
```vbscript
```vbscript
      CATIA.SystemService.Print analysisLinkedDocuments1.Name
      If (analysisLinkedDocuments1.Count <> 1 ) Then
```
```vbscript
        Err.Raise 9999,,"NbDoc Li NE 1"
      End If
```
    ' _____________________________________________________________________________________
    ' Retrieve the CATProduct Document and associated publications and constraints collection.

```vbscript
      Set productDocument1 = analysisLinkedDocuments1.Item(1)

      Set product1 = productDocument1.Product
      Set products1 = product1.Products

      Set publications1 = product1.Publications
      Set constraints1 = product1.Connections("CATIAConstraints")
```
```

```

```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create a Virtual Part in the analysis model to transmit the load.
```vbscript
    Set analysisModels1 = analysisManager1.AnalysisModels
    Set analysisModel1 = analysisModels1.Item(1)

    Set analysisSets1 = analysisModel1.AnalysisSets
    Set analysisSet1 = analysisSets1.ItemByType("PropertySet")

    Set analysisEntities1 = analysisSet1.AnalysisEntities
    Set analysisEntity1 = analysisEntities1.Add("SAMVirPartRigid")
    Set publication1 = publications1.Item("FaceCylinderTop")
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
```vbscript
Set analysisEntity1 = analysisEntities1.Add("SAMVirPartRigid")
Set publication1 = publications1.Item("FaceCylinderTop")
```
```

```

    analysisEntity1.AddSupportFromPublication product1, publication1
```vbscript
    Set basicComponents1 = analysisEntity1.BasicComponents
```vbscript
```
```vbscript
```vbscript
    Set basicComponent1 = basicComponents1.GetItem("SAMRigSlavePoint.1")
    Set publication4 = publications1.Item("ForceHandler")
```
```

```

    basicComponent1.AddSupportFromPublication product1, publication4
```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create a Fastened connection in the analysis model to complete the constraints
    ' definition
```vbscript
    Set analysisEntity2 = analysisEntities1.Add("SAMFaceFaceFastened")
    Set constraint1 = constraints1.Item("Surface contact.2")
```
```

```

```

```vbscript
```vbscript
```vbscript
' definition
```vbscript
Set analysisEntity2 = analysisEntities1.Add("SAMFaceFaceFastened")
Set constraint1 = constraints1.Item("Surface contact.2")
```
```

```

    analysisEntity2.AddSupportFromConstraint product1, constraint1
```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create a Static Case in the current analysis model.
```vbscript
    Set analysisCases1 = analysisModel1.AnalysisCases
    Set analysisCase1 = analysisCases1.Add(#)

    Set analysisSets2 = analysisCase1.AnalysisSets
    Set analysisSet2 = analysisSets2.Add("RestraintSet", catAnalysisSetIn)
    Set analysisSet3 = analysisSets2.Add("LoadSet", catAnalysisSetIn)
    Set analysisSet5 = analysisCase1.AddSolution("StaticSet")
```
```

```

```

```vbscript
    ' _____________________________________________________________________________________
```

```vbscript
```vbscript
```vbscript
' _____________________________________________________________________________________
    ' Create clamp boundary. Associated to a publication
```

```

```

```vbscript
```vbscript
    Set analysisEntities2 = analysisSet2.AnalysisEntities
```vbscript
```
```vbscript
```vbscript
    Set analysisEntity3 = analysisEntities2.Add("SAMClamp")
    Set publication2 = publications1.Item("FaceToClamp")
```
```

```

    analysisEntity3.AddSupportFromPublication product1, publication2
```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create load boundary. Associated to the virtual part
```vbscript
    Set analysisEntities3 = analysisSet3.AnalysisEntities

    Set analysisEntity4 = analysisEntities3.Add("SAMDistributedForce")
    Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity1)
```
```

```

```

```vbscript
```vbscript
Set analysisEntity4 = analysisEntities3.Add("SAMDistributedForce")
```vbscript
```
```vbscript
Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity1)
```
```

    analysisEntity4.AddSupportFromReference reference2, reference2
```vbscript
```vbscript
    CATIA.SystemService.Print "Name of the Reference" & reference2.DisplayName

```
```

```

```vbscript
```vbscript
    Set basicComponents2 = analysisEntity4.BasicComponents
```vbscript
```
```vbscript
    Set basicComponent2 = basicComponents2.GetItem("SAMForceAxis.1")
```
```

    basicComponent2.SetValue "Values", 0, 0, 0, 1
```vbscript
    Set basicComponent3 = basicComponents2.GetItem("SAMForceVector.1")
    basicComponent3.SetDimensions 3, 1, 1
```
    basicComponent3.SetValue "", 1, 1, 1, 100.000000
    basicComponent3.SetValue "", 2, 1, 1, 0.000000
    basicComponent3.SetValue "", 3, 1, 1, 0.000000
```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Some examples to read the data on the basic componenent
    'In this case, direct read
```vbscript
    CATIA.SystemService.Print " ForceVector " & basicComponent3.GetValue("", 1, 1, 1)
    CATIA.SystemService.Print " ForceVector " & basicComponent3.GetValue("", 2, 1, 1)
    CATIA.SystemService.Print " ForceVector " & basicComponent3.GetValue("", 3, 1, 1)

    CATIA.SystemService.Print " ForceVector Type " & basicComponent3.Type
    CATIA.SystemService.Print " ForceVector Dimension " & basicComponent3.GetLinesNumber  ("")
    CATIA.SystemService.Print " ForceVector Dimension " & basicComponent3.GetColumnsNumber("")
    CATIA.SystemService.Print " ForceVector Dimension " & basicComponent3.GetLayersNumber ("")
    'In this case, use the Kwe CATIAParameter interface.
```
```vbscript
    Set ParametersList = analysisManager1.Parameters
    Set SubList = ParametersList.SubList(basicComponent3,FALSE)
```
```

```

```

```vbscript
    For i = 1 to SubList.Count
```vbscript
```vbscript
```vbscript
    	Set Parameter = SubList.Item(i)
    	CATIA.SystemService.Print Parameter.Name
    	CATIA.SystemService.Print Parameter.ValueAsString
    Next
```
    ' _____________________________________________________________________________________
    ' Launch the MeshOnly update
```

```

    analysisCase1.ComputeMeshOnly

```

```vbscript
```vbscript
' Launch the MeshOnly update
```

analysisCase1.ComputeMeshOnly
```vbscript
    '------------------------------- END   END   END   ----------------------------
```

```

```vbscript
```vbscript
```vbscript
      CATIA.DisplayFileAlerts = False

```
```

```

```vbscript
```vbscript
    End Sub

```
```
