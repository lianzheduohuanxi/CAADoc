---
```vbscript
title: "CAAAniPreproOnVirtual.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPreproOnVirtual", "CATISamImportDefine", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnVirtualSource.htmmd"
converted: "2026-05-11T17:31:51.840341"
```

---
tags: ["CATIA", "CAAAniPreproOnVirtual", "CATISamImportDefine", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnVirtualSource.htmmd"
converted: "2026-05-11T17:31:51.840341"
    Language="VBSCRIPT"

```vbscript
```vbscript
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Create a New Analysis document.
    '                 Import on a CATPart document with some publication defined
    '                 Define all preprocessing data based on publications:
    '                 This sample includes some rigid virtual parts that are clampled.
    '                 Launch the Computation.
    '   Assumtions:   Looks for FlangeForVirtualUsage.CATPart stored in the DocView
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
    ' -----------------------------------------------------------
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
    ' -----------------------------------------------------------
    ' Get the collection of documents in session
```vbscript
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
    ' and link the analysis to a Part Document
```

```

```

```vbscript
```vbscript
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
```vbscript
        Dim arrayOfVariantOfShort1(0)
        analysisManager1.ImportDefineFile (sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "FlangeForVirtualUsage.CATPart"),
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
```vbscript
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
```vbscript
    ' _____________________________________________________________________________________
    ' Retrieve the CATPart Document and associated collection of publications for preprocessing.
```vbscript
       Set TheDoc = analysisLinkedDocuments1.Item(1)
       CATIA.SystemService.Print TheDoc.FullName

       Set product1 = TheDoc.Product
       Set publications1 = product1.Publications
    ' _____________________________________________________________________________________
```
    ' Create a Modal Case in the current analysis model.
```vbscript
       Set analysisModels1 = analysisManager1.AnalysisModels
       Set analysisModel1 = analysisModels1.Item(1)

       Set analysisCases1 = analysisModel1.AnalysisCases
       Set analysisCase1 = analysisCases1.Add(#)
       Set analysisSets1 = analysisCase1.AnalysisSets

       Set analysisSet1 = analysisSets1.Add("RestraintSet", catAnalysisSetIn)
       Set analysisSet2 = analysisSets1.Add("MassSet", catAnalysisSetIn)
       Set analysisSet3 = analysisCase1.AddSolution("FrequencySet")
       Set analysisSet6 = analysisSets1.Add("SensorSet",catAnalysisSetOut)
    ' _____________________________________________________________________________________
```
    ' Create a property set from the Analysis Model to create some Rigid Virtal Parts
```vbscript
       Set analysisSets2 = analysisModel1.AnalysisSets

       Set analysisSet4 = analysisSets2.ItemByType("PropertySet")
       Set analysisEntities1 = analysisSet4.AnalysisEntities

       Set analysisEntity1 = analysisEntities1.Add("SAMVirPartRigid")
       Set publication1 = publications1.Item("SmallHole")
```
```

```

```

```vbscript
```vbscript
Set analysisEntity1 = analysisEntities1.Add("SAMVirPartRigid")
```vbscript
```
```vbscript
Set publication1 = publications1.Item("SmallHole")
```
```

       analysisEntity1.AddSupportFromPublication product1, publication1

```vbscript
       Set analysisEntity2 = analysisEntities1.Add("SAMVirPartRigid")
```vbscript
```
```vbscript
       Set publication2 = publications1.Item("SmallHole1")
```
```

       analysisEntity2.AddSupportFromPublication product1, publication2

```vbscript
       Set analysisEntity3 = analysisEntities1.Add("SAMVirPartRigid")
```vbscript
```
```vbscript
       Set publication3 = publications1.Item("SmallHole3")
```
```

       analysisEntity3.AddSupportFromPublication product1, publication3

```vbscript
       Set analysisEntity4 = analysisEntities1.Add("SAMVirPartRigid")
```vbscript
```
```vbscript
       Set publication4 = publications1.Item("SmallHole2")
```
```

       analysisEntity4.AddSupportFromPublication product1, publication4
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Clamp the Rigid Virtal Parts

```vbscript
       Set analysisEntities2 = analysisSet1.AnalysisEntities
       Set analysisEntity5 = analysisEntities2.Add("SAMClamp")
       Set reference1 = analysisManager1.CreateReferenceFromObject(analysisEntity4)
```
```

```

       analysisEntity5.AddSupportFromReference reference1, reference1

```vbscript
       Set analysisEntity6 = analysisEntities2.Add("SAMClamp")
```vbscript
```
```vbscript
       Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity3)
```
```

       analysisEntity6.AddSupportFromReference reference2, reference2

```vbscript
       Set analysisEntity7 = analysisEntities2.Add("SAMClamp")
```vbscript
```
```vbscript
       Set reference3 = analysisManager1.CreateReferenceFromObject(analysisEntity2)
```
```

       analysisEntity7.AddSupportFromReference reference3, reference3

```vbscript
       Set analysisEntity8 = analysisEntities2.Add("SAMClamp")
```vbscript
```
```vbscript
       Set reference4 = analysisManager1.CreateReferenceFromObject(analysisEntity1)
```
```

       analysisEntity8.AddSupportFromReference reference4, reference4
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Distribute some Masses on top of the Part

```vbscript
       Set analysisEntities3 = analysisSet2.AnalysisEntities
       Set analysisEntity9 = analysisEntities3.Add("SAMDistributedMass")
       Set publication5 = publications1.Item("TopFace")
```
```

```

       analysisEntity9.AddSupportFromPublication product1, publication5

```vbscript
       Set basicComponents1 = analysisEntity9.BasicComponents
```vbscript
```
```vbscript
       Set basicComponent1 = basicComponents1.GetItem("SAMMassMag")
```
```

       basicComponent1.SetValue "", 0, 0, 0, 25.000000

```

```vbscript
```vbscript
Set basicComponent1 = basicComponents1.GetItem("SAMMassMag")
```
```

basicComponent1.SetValue "", 0, 0, 0, 25.000000
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Read the Value of the Mass

```

```

```vbscript
```vbscript
      CATIA.SystemService.Print " Mass Applied of the Part: " & basicComponent1.GetValue ("",0,0,0)
```vbscript
```
```vbscript
    ' _____________________________________________________________________________________
    ' Launch Computation.
```

```

      analysisCase1.Compute
```

```vbscript
```vbscript
```vbscript
    '------------------------------- END   END   END   ----------------------------
```vbscript
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
