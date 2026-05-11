---
title: "CAAAniPreproOnPublish.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniPreproOnPublish", "CATISamImportDefine"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnPublishSource.htm"
converted: "2026-05-11T11:27:02.548675"
---

Language="VBSCRIPT"
' COPYRIGTH DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Create a New Analysis document.
'                 Import on a CATPart document with some publication defined 
'                 Define all pre-processing data based on publications
'                 Launch the Computation.
'                 Create a AnalysisSensor and display its values
'                 Create an Image and export data, then deactivate and update it
'   Assumptions:   Looks for AnalysisMechfeat.CATPart stored in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R10
' ***********************************************************************

Sub CATMain()
' ----------------------------------------------------------- 
' Optional: allows to find the sample wherever it's installed
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If(Not CATIA.FileSystem.FolderExists(sDocPath)) Then
    Err.Raise 9999,,"No Doc Path Defined"
    End If
' ----------------------------------------------------------- 
' Get the collection of documents in session
    Set documents1 = CATIA.Documents

' Create the CATAnalysis Document 
    Set TheAnalysisDocument = documents1.Add("Analysis")

' Only one Analysis Document is required
' if WB name already is "GPSCfg", not to use StartWorkbench
    WBName = CATIA.GetWorkbenchId
    if (WBName <> "GPSCfg") Then
	CATIA.StartWorkbench("GPSCfg")
    End If
 
'_____________________________________________________________________________________
' Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
' We call the Import on CATAnalysisImport which implements CATISamImportDefine

    Set analysisManager1 = TheAnalysisDocument.Analysis

    Dim arrayOfVariantOfShort1(0)
    analysisManager1.ImportDefineFile (sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "AnalysisMechfeat.CATPart"),

				       "CATAnalysisImport", arrayOfVariantOfShort1

' _____________________________________________________________________________________
' Reframe All.
  Set specsAndGeomWindow1 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow1.ActiveViewer
  viewer3D1.Reframe 

' _____________________________________________________________________________________
' Scan the analysis document:  Retrieve the Pointed documents to extract the reference for pre-processing
    Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
    CATIA.SystemService.Print analysisLinkedDocuments1.Name

   If (analysisLinkedDocuments1.Count <> 1 ) Then
      Err.Raise 9999,,"NbDoc Li NE 1"
   End If

' _____________________________________________________________________________________
' Retrieve the CATPart Document and associated publications for pre-processing.
   Set TheDoc = analysisLinkedDocuments1.Item(1)
   CATIA.SystemService.Print TheDoc.FullName

  Set product1 = TheDoc.Product
  Set publications1 = product1.Publications
  Set publication1 = publications1.Item("Bottomface")
  Set publication2 = publications1.Item("Sliding1")
  Set publication3 = publications1.Item("Sliding2")
  Set publication4 = publications1.Item("ResizeBody")

' _____________________________________________________________________________________
' Create a Static Case in the current analysis model.
  Set analysisModels1 = analysisManager1.AnalysisModels
  Set analysisModel1 = analysisModels1.Item(1)

  Set analysisCases1 = analysisModel1.AnalysisCases
  Set analysisCase1 = analysisCases1.Add()
  Set analysisSets1 = analysisCase1.AnalysisSets

  Set analysisSet1 = analysisSets1.Add("RestraintSet", catAnalysisSetIn)
  Set analysisSet2 = analysisSets1.Add("LoadSet", catAnalysisSetIn)
  Set analysisSet3 = analysisCase1.AddSolution("StaticSet")

' _____________________________________________________________________________________
' Create clamp boundary.
  Set analysisEntities1 = analysisSet1.AnalysisEntities
  Set analysisEntity1 = analysisEntities1.Add("SAMClamp")
  analysisEntity1.AddSupportFromPublication product1, publication1

' _____________________________________________________________________________________
' Create Slider boundary.
  Set analysisEntity2 = analysisEntities1.Add("SAMSurfaceSlider")
  analysisEntity2.AddSupportFromPublication product1, publication2
  analysisEntity2.AddSupportFromPublication product1, publication3

' _____________________________________________________________________________________
' Create Pressure.
  Set analysisEntities2 = analysisSet2.AnalysisEntities
  Set analysisEntity3 = analysisEntities2.Add("SAMPressure")

  analysisEntity3.AddSupportFromPublication product1, publication4
  analysisEntity3.SetValue "SAMPressureMag","", 0, 0, 0, 500.

' _____________________________________________________________________________________
' Define a global sensor measuring the maximum value of VonMises criterion.
  Set dimension1 = analysisManager1.Parameters.CreateDimension("Maximum value of VonMises criterion", "PRESSURE", 0.000000)
  Set formula1 = analysisManager1.Relations.CreateFormula("Maximum value of VonMises criterion","",dimension1,"misesmax(`Finite Element Model.1\Static Case Solution.1` ) ")

' _____________________________________________________________________________________
' Launch Computation.
  analysisCase1.Compute

  CATIA.SystemService.Print " Mises Max Computed " & dimension1.ValueAsString

' _____________________________________________________________________________________
' Create corresponding image.
  Set analysisImages1 = analysisSet3.AnalysisImages
  Set analysisImage1 = analysisImages1.Add("StressVonMises_Iso_Smooth", False, False, True)

' _____________________________________________________________________________________
' Export data from image.
  outputPath=CATIA.SystemService.Environ("CATTemp")
    If(Not CATIA.FileSystem.FolderExists(outputPath)) Then
    Err.Raise 9999,,"No Output Path Defined"
    End If
  Set fileSystem1 = CATIA.FileSystem
  Set folder1 = fileSystem1.GetFolder(outputPath)
  analysisImage1.ExportData folder1, "VonMises", "txt"

' _____________________________________________________________________________________
' Reframe All.
  viewer3D1.Reframe 
  
' _____________________________________________________________________________________
' Deactivate and Update image.
  analysisImage1.SetActivationStatus false
  analysisImage1.Update

'------------------------------- END   END   END   ----------------------------
  CATIA.DisplayFileAlerts = False

End Sub



```vbscript
Language=&quot;VBSCRIPT&quot;
&#39; COPYRIGTH DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      Create a New Analysis document.
&#39;                 Import on a CATPart document with some publication defined 
&#39;                 Define all pre-processing data based on publications
&#39;                 Launch the Computation.
&#39;                 Create a AnalysisSensor and display its values
&#39;                 Create an Image and export data, then deactivate and update it
&#39;   Assumptions:   Looks for AnalysisMechfeat.CATPart stored in the DocView   
&#39;   Author: 
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R10
&#39; ***********************************************************************

Sub CATMain()
&#39; ----------------------------------------------------------- 
&#39; Optional: allows to find the sample wherever it&#39;s installed
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If(Not CATIA.FileSystem.FolderExists(sDocPath)) Then
    Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
&#39; ----------------------------------------------------------- 
&#39; Get the collection of documents in session
    Set documents1 = CATIA.Documents

&#39; Create the CATAnalysis Document 
    Set TheAnalysisDocument = documents1.Add(&quot;Analysis&quot;)

&#39; Only one Analysis Document is required
&#39; if WB name already is &quot;GPSCfg&quot;, not to use StartWorkbench
    WBName = CATIA.GetWorkbenchId
    if (WBName &lt;&gt; &quot;GPSCfg&quot;) Then
	CATIA.StartWorkbench(&quot;GPSCfg&quot;)
    End If
 
&#39;_____________________________________________________________________________________
&#39; Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
&#39; We call the Import on CATAnalysisImport which implements CATISamImportDefine
```

```vbscript
Set analysisManager1 = TheAnalysisDocument.Analysis
```

```vbscript
Dim arrayOfVariantOfShort1(0)
    analysisManager1.ImportDefineFile (sDocPath &amp; sSep &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep &amp; &quot;AnalysisMechfeat.CATPart&quot;),
```

```vbscript
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1

&#39; _____________________________________________________________________________________
&#39; Reframe All.
  Set specsAndGeomWindow1 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow1.ActiveViewer
  viewer3D1.Reframe 

&#39; _____________________________________________________________________________________
&#39; Scan the analysis document:  Retrieve the Pointed documents to extract the reference for pre-processing
    Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
    CATIA.SystemService.Print analysisLinkedDocuments1.Name

   If (analysisLinkedDocuments1.Count &lt;&gt; 1 ) Then
      Err.Raise 9999,,&quot;NbDoc Li NE 1&quot;
   End If

&#39; _____________________________________________________________________________________
&#39; Retrieve the CATPart Document and associated publications for pre-processing.
   Set TheDoc = analysisLinkedDocuments1.Item(1)
   CATIA.SystemService.Print TheDoc.FullName

  Set product1 = TheDoc.Product
  Set publications1 = product1.Publications
  Set publication1 = publications1.Item(&quot;Bottomface&quot;)
  Set publication2 = publications1.Item(&quot;Sliding1&quot;)
  Set publication3 = publications1.Item(&quot;Sliding2&quot;)
  Set publication4 = publications1.Item(&quot;ResizeBody&quot;)

&#39; _____________________________________________________________________________________
&#39; Create a Static Case in the current analysis model.
  Set analysisModels1 = analysisManager1.AnalysisModels
  Set analysisModel1 = analysisModels1.Item(1)

  Set analysisCases1 = analysisModel1.AnalysisCases
  Set analysisCase1 = analysisCases1.Add()
  Set analysisSets1 = analysisCase1.AnalysisSets

  Set analysisSet1 = analysisSets1.Add(&quot;RestraintSet&quot;, catAnalysisSetIn)
  Set analysisSet2 = analysisSets1.Add(&quot;LoadSet&quot;, catAnalysisSetIn)
  Set analysisSet3 = analysisCase1.AddSolution(&quot;StaticSet&quot;)

&#39; _____________________________________________________________________________________
&#39; Create clamp boundary.
  Set analysisEntities1 = analysisSet1.AnalysisEntities
  Set analysisEntity1 = analysisEntities1.Add(&quot;SAMClamp&quot;)
  analysisEntity1.AddSupportFromPublication product1, publication1

&#39; _____________________________________________________________________________________
&#39; Create Slider boundary.
  Set analysisEntity2 = analysisEntities1.Add(&quot;SAMSurfaceSlider&quot;)
  analysisEntity2.AddSupportFromPublication product1, publication2
  analysisEntity2.AddSupportFromPublication product1, publication3

&#39; _____________________________________________________________________________________
&#39; Create Pressure.
  Set analysisEntities2 = analysisSet2.AnalysisEntities
  Set analysisEntity3 = analysisEntities2.Add(&quot;SAMPressure&quot;)

  analysisEntity3.AddSupportFromPublication product1, publication4
  analysisEntity3.SetValue &quot;SAMPressureMag&quot;,&quot;&quot;, 0, 0, 0, 500.

&#39; _____________________________________________________________________________________
&#39; Define a global sensor measuring the maximum value of VonMises criterion.
  Set dimension1 = analysisManager1.Parameters.CreateDimension(&quot;Maximum value of VonMises criterion&quot;, &quot;PRESSURE&quot;, 0.000000)
  Set formula1 = analysisManager1.Relations.CreateFormula(&quot;Maximum value of VonMises criterion&quot;,&quot;&quot;,dimension1,&quot;misesmax(`Finite Element Model.1\Static Case Solution.1` ) &quot;)

&#39; _____________________________________________________________________________________
&#39; Launch Computation.
  analysisCase1.Compute

  CATIA.SystemService.Print &quot; Mises Max Computed &quot; &amp; dimension1.ValueAsString

&#39; _____________________________________________________________________________________
&#39; Create corresponding image.
  Set analysisImages1 = analysisSet3.AnalysisImages
  Set analysisImage1 = analysisImages1.Add(&quot;StressVonMises_Iso_Smooth&quot;, False, False, True)

&#39; _____________________________________________________________________________________
&#39; Export data from image.
  outputPath=CATIA.SystemService.Environ(&quot;CATTemp&quot;)
    If(Not CATIA.FileSystem.FolderExists(outputPath)) Then
    Err.Raise 9999,,&quot;No Output Path Defined&quot;
    End If
  Set fileSystem1 = CATIA.FileSystem
  Set folder1 = fileSystem1.GetFolder(outputPath)
  analysisImage1.ExportData folder1, &quot;VonMises&quot;, &quot;txt&quot;

&#39; _____________________________________________________________________________________
&#39; Reframe All.
  viewer3D1.Reframe 
  
&#39; _____________________________________________________________________________________
&#39; Deactivate and Update image.
  analysisImage1.SetActivationStatus false
  analysisImage1.Update

&#39;------------------------------- END   END   END   ----------------------------
  CATIA.DisplayFileAlerts = False

End Sub
```