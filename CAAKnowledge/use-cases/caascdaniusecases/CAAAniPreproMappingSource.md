---
title: "CAAAniPreproMapping.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAScdAniUseCases", "CATIA", "CAAAniPreproMapping", "CATISamImportDefine"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproMappingSource.htm"
converted: "2026-05-11T11:27:02.572460"
---

Language="VBSCRIPT"
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

Sub CATMain()
' ----------------------------------------------------------- 
' Optional: allows to find the sample wherever it's installed

  sDocPath=CATIA.SystemService.Environ("CATDocView")
  sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
' ----------------------------------------------------------- 
' Get the collection of documents in session
    Set documents1 = CATIA.Documents

' Only one Analysis Document is required
' Create the CATAnalysis Document 
    Set TheAnalysisDocument = documents1.Add("Analysis")

' if WB name already is "GPSCfg", not to use StartWorkbench
    WBName = CATIA.GetWorkbenchId
    if (WBName <> "GPSCfg") Then
	CATIA.StartWorkbench("GPSCfg")
    End If
 
'_____________________________________________________________________________________
' Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
' and link the analysis to a Part Document

' We call the Import on CATAnalysisImport which implements CATISamImportDefine
    
    Set analysisManager1 = TheAnalysisDocument.Analysis

    Dim arrayOfVariantOfShort1(0)
    analysisManager1.ImportDefineFile (sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "SimpleChrank.CATPart"),

				       "CATAnalysisImport", arrayOfVariantOfShort1

' _____________________________________________________________________________________
' Reframe All.
  Set specsAndGeomWindow1 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow1.ActiveViewer
  viewer3D1.Reframe 

' _____________________________________________________________________________________
' Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing
    Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
    CATIA.SystemService.Print analysisLinkedDocuments1.Name

   If (analysisLinkedDocuments1.Count <> 1 ) Then
      Err.Raise 9999,,"NbDoc Li NE 1"
   End If

' _____________________________________________________________________________________
' Retrieve the CATPart Document and associated publications for preprocessing.
   Set TheDoc = analysisLinkedDocuments1.Item(1)
   CATIA.SystemService.Print TheDoc.FullName

   Set product1 = TheDoc.Product
   Set publications1 = product1.Publications
   Set publication1 = publications1.Item("ClampFace")
   Set publication2 = publications1.Item("MappingFace")

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
' Create clamp boundary and apply to the publication called ClampFace

   Set analysisEntities1 = analysisSet1.AnalysisEntities
   Set analysisEntity1 = analysisEntities1.Add("SAMClamp")
   analysisEntity1.AddSupportFromPublication product1, publication1

' _____________________________________________________________________________________
' Create Surfacic Force and apply to the publication called MappingFace

   Set analysisEntities2 = analysisSet2.AnalysisEntities
   Set analysisEntity3 = analysisEntities2.Add("SAMSurfacicForce")

   analysisEntity3.AddSupportFromPublication product1, publication2

   Set basicComponents1 = analysisEntity3.BasicComponents

' No Local Axis is defined
   Set basicComponent1 = basicComponents1.GetItem("SAMSurfacicForceAxis.1")
   basicComponent1.SetValue "", 0, 0, 0, 1

' Valuate the vector.
   Set basicComponent2 = basicComponents1.GetItem("SAMSurfacicForceVector.1")
   basicComponent2.SetValue "Values", 1, 1, 1, 0.000000
   basicComponent2.SetValue "Values", 2, 1, 1, -1000000.000000
   basicComponent2.SetValue "Values", 3, 1, 1, 0.000000

' Create a Design Table for the mapping file and valuate the basic component
   Set basicComponent3 = basicComponents1.GetItem("SAMDTPtrSurfForce")
   Set designTable1 = analysisManager1.Relations.CreateDesignTable("", "", False, sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "MappingForCrank.txt")
   basicComponent3.SetValue "", 0, 0, 0, designTable1

' _____________________________________________________________________________________
' Launch Computation.
  analysisCase1.Compute

' _____________________________________________________________________________________
' Define a global sensor measuring the maximum value of VonMises criterion.

  Set dimension1 = analysisManager1.Parameters.CreateDimension("Maximum value of VonMises criterion", "PRESSURE", 0.000000)
  Set formula1 = analysisManager1.Relations.CreateFormula("Maximum value of VonMises criterion","",dimension1,"misesmax(`Finite Element Model.1\Static Case Solution.1` ) ")
  CATIA.SystemService.Print " Mises Max Computed " & dimension1.ValueAsString

' _____________________________________________________________________________________
  viewer3D1.Reframe 

'------------------------------- END   END   END   ----------------------------
  CATIA.DisplayFileAlerts = False
'  TheAnalysisDocument.Close

End Sub



```vbscript
Language=&quot;VBSCRIPT&quot;
&#39; COPYRIGTH DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      Create a New Analysis document.
&#39;                 Import on a CATPart document with some publication defined 
&#39;                 Define all preprocessing data based on publications
&#39;                 Define a surfacique force with variable data (use mapping capability)
&#39;                 Launch the Computation.
&#39;                 Create a AnalysisSensor and display its values
&#39;   Assumtions:   Looks for SimpleChrank.CATPart stored in the DocView   
&#39;   Author: 
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R13
&#39; ***********************************************************************

Sub CATMain()
&#39; ----------------------------------------------------------- 
&#39; Optional: allows to find the sample wherever it&#39;s installed

  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
  sSep=CATIA.SystemService.Environ(&quot;ADL_ODT_SLASH&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
&#39; ----------------------------------------------------------- 
&#39; Get the collection of documents in session
    Set documents1 = CATIA.Documents

&#39; Only one Analysis Document is required
&#39; Create the CATAnalysis Document 
    Set TheAnalysisDocument = documents1.Add(&quot;Analysis&quot;)

&#39; if WB name already is &quot;GPSCfg&quot;, not to use StartWorkbench
    WBName = CATIA.GetWorkbenchId
    if (WBName &lt;&gt; &quot;GPSCfg&quot;) Then
	CATIA.StartWorkbench(&quot;GPSCfg&quot;)
    End If
 
&#39;_____________________________________________________________________________________
&#39; Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
&#39; and link the analysis to a Part Document
```

```vbscript
&#39; We call the Import on CATAnalysisImport which implements CATISamImportDefine
    
    Set analysisManager1 = TheAnalysisDocument.Analysis
```

```vbscript
Dim arrayOfVariantOfShort1(0)
    analysisManager1.ImportDefineFile (sDocPath &amp; sSep  &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep  &amp; &quot;SimpleChrank.CATPart&quot;),
```

```vbscript
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1

&#39; _____________________________________________________________________________________
&#39; Reframe All.
  Set specsAndGeomWindow1 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow1.ActiveViewer
  viewer3D1.Reframe 

&#39; _____________________________________________________________________________________
&#39; Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing
    Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
    CATIA.SystemService.Print analysisLinkedDocuments1.Name

   If (analysisLinkedDocuments1.Count &lt;&gt; 1 ) Then
      Err.Raise 9999,,&quot;NbDoc Li NE 1&quot;
   End If

&#39; _____________________________________________________________________________________
&#39; Retrieve the CATPart Document and associated publications for preprocessing.
   Set TheDoc = analysisLinkedDocuments1.Item(1)
   CATIA.SystemService.Print TheDoc.FullName

   Set product1 = TheDoc.Product
   Set publications1 = product1.Publications
   Set publication1 = publications1.Item(&quot;ClampFace&quot;)
   Set publication2 = publications1.Item(&quot;MappingFace&quot;)

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
&#39; Create clamp boundary and apply to the publication called ClampFace

   Set analysisEntities1 = analysisSet1.AnalysisEntities
   Set analysisEntity1 = analysisEntities1.Add(&quot;SAMClamp&quot;)
   analysisEntity1.AddSupportFromPublication product1, publication1

&#39; _____________________________________________________________________________________
&#39; Create Surfacic Force and apply to the publication called MappingFace

   Set analysisEntities2 = analysisSet2.AnalysisEntities
   Set analysisEntity3 = analysisEntities2.Add(&quot;SAMSurfacicForce&quot;)

   analysisEntity3.AddSupportFromPublication product1, publication2

   Set basicComponents1 = analysisEntity3.BasicComponents

&#39; No Local Axis is defined
   Set basicComponent1 = basicComponents1.GetItem(&quot;SAMSurfacicForceAxis.1&quot;)
   basicComponent1.SetValue &quot;&quot;, 0, 0, 0, 1

&#39; Valuate the vector.
   Set basicComponent2 = basicComponents1.GetItem(&quot;SAMSurfacicForceVector.1&quot;)
   basicComponent2.SetValue &quot;Values&quot;, 1, 1, 1, 0.000000
   basicComponent2.SetValue &quot;Values&quot;, 2, 1, 1, -1000000.000000
   basicComponent2.SetValue &quot;Values&quot;, 3, 1, 1, 0.000000

&#39; Create a Design Table for the mapping file and valuate the basic component
   Set basicComponent3 = basicComponents1.GetItem(&quot;SAMDTPtrSurfForce&quot;)
   Set designTable1 = analysisManager1.Relations.CreateDesignTable(&quot;&quot;, &quot;&quot;, False, sDocPath &amp; sSep  &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep  &amp; &quot;MappingForCrank.txt&quot;)
   basicComponent3.SetValue &quot;&quot;, 0, 0, 0, designTable1

&#39; _____________________________________________________________________________________
&#39; Launch Computation.
  analysisCase1.Compute

&#39; _____________________________________________________________________________________
&#39; Define a global sensor measuring the maximum value of VonMises criterion.

  Set dimension1 = analysisManager1.Parameters.CreateDimension(&quot;Maximum value of VonMises criterion&quot;, &quot;PRESSURE&quot;, 0.000000)
  Set formula1 = analysisManager1.Relations.CreateFormula(&quot;Maximum value of VonMises criterion&quot;,&quot;&quot;,dimension1,&quot;misesmax(`Finite Element Model.1\Static Case Solution.1` ) &quot;)
  CATIA.SystemService.Print &quot; Mises Max Computed &quot; &amp; dimension1.ValueAsString

&#39; _____________________________________________________________________________________
  viewer3D1.Reframe 

&#39;------------------------------- END   END   END   ----------------------------
  CATIA.DisplayFileAlerts = False
&#39;  TheAnalysisDocument.Close

End Sub
```