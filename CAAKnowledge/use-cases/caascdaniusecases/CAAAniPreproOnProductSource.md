---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIAParameter", "CATIA", "CAAScdAniUseCases", "CATIAConstraints", "CAAAniPreproOnProduct", "CATISamImportDefine"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnProductSource.htmmd"
converted: "2026-05-11T11:27:02.534730"
---

Language="VBSCRIPT"
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

```cpp
Sub CATMain(#)
'_____________________________________________________________________________________
```
' Optional: allows to find the sample wherever it's installed

```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")
  sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
'_____________________________________________________________________________________
' Get the collection of documents in session
```cpp
  Set documents1 = CATIA.Documents

' Create the CATAnalysis Document 
```
```vbscript
  Set TheAnalysisDoc = documents1.Add("Analysis")

' Only one Analysis Document is required
```
' if WB name already is "GPSCfg", not to use StartWorkbench
```cpp
  WBName = CATIA.GetWorkbenchId
  if (WBName <> "GPSCfg") Then
```
```cpp
     CATIA.StartWorkbench("GPSCfg")
  End If
```

'_____________________________________________________________________________________
' Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
' We call the Import on CATAnalysisImport which implements CATISamImportDefine

 

```cpp
  Set analysisManager1 = TheAnalysisDoc.Analysis

 

  Dim arrayOfVariantOfShort1(0)
  analysisManager1.ImportDefineFile (sDocPath & sSep  & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "basic_assembly.CATProduct"),				     "
```

 

  				     "CATAnalysisImport", arrayOfVariantOfShort1

' _____________________________________________________________________________________
' Reframe All.
```cpp
  Set specsAndGeomWindow2 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow2.ActiveViewer
  viewer3D1.Reframe 
```

' _____________________________________________________________________________________
' Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing
```cpp
  Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
  CATIA.SystemService.Print analysisLinkedDocuments1.Name
  If (analysisLinkedDocuments1.Count <> 1 ) Then
```
```vbscript
    Err.Raise 9999,,"NbDoc Li NE 1"
  End If
```

' _____________________________________________________________________________________
' Retrieve the CATProduct Document and associated publications and constraints collection.

```cpp
  Set productDocument1 = analysisLinkedDocuments1.Item(1)

  Set product1 = productDocument1.Product
  Set products1 = product1.Products

  Set publications1 = product1.Publications
  Set constraints1 = product1.Connections("CATIAConstraints")

' _____________________________________________________________________________________
```
' Create a Virtual Part in the analysis model to transmit the load.
```vbscript
Set analysisModels1 = analysisManager1.AnalysisModels
Set analysisModel1 = analysisModels1.Item(1)

Set analysisSets1 = analysisModel1.AnalysisSets
Set analysisSet1 = analysisSets1.ItemByType("PropertySet")

Set analysisEntities1 = analysisSet1.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Add("SAMVirPartRigid")
Set publication1 = publications1.Item("FaceCylinderTop")
analysisEntity1.AddSupportFromPublication product1, publication1
```
```vbscript
Set basicComponents1 = analysisEntity1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem("SAMRigSlavePoint.1")
Set publication4 = publications1.Item("ForceHandler")
basicComponent1.AddSupportFromPublication product1, publication4
```

' _____________________________________________________________________________________
' Create a Fastened connection in the analysis model to complete the constraints 
' definition
```vbscript
Set analysisEntity2 = analysisEntities1.Add("SAMFaceFaceFastened")
Set constraint1 = constraints1.Item("Surface contact.2")
analysisEntity2.AddSupportFromConstraint product1, constraint1
```

' _____________________________________________________________________________________
' Create a Static Case in the current analysis model.
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases
Set analysisCase1 = analysisCases1.Add(#)

Set analysisSets2 = analysisCase1.AnalysisSets
Set analysisSet2 = analysisSets2.Add("RestraintSet", catAnalysisSetIn)
Set analysisSet3 = analysisSets2.Add("LoadSet", catAnalysisSetIn)
Set analysisSet5 = analysisCase1.AddSolution("StaticSet")

' _____________________________________________________________________________________
```
' Create clamp boundary. Associated to a publication
```vbscript
Set analysisEntities2 = analysisSet2.AnalysisEntities
Set analysisEntity3 = analysisEntities2.Add("SAMClamp")
Set publication2 = publications1.Item("FaceToClamp")
analysisEntity3.AddSupportFromPublication product1, publication2
```

' _____________________________________________________________________________________
' Create load boundary. Associated to the virtual part
```vbscript
Set analysisEntities3 = analysisSet3.AnalysisEntities

Set analysisEntity4 = analysisEntities3.Add("SAMDistributedForce")
Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity1)
analysisEntity4.AddSupportFromReference reference2, reference2
```
```cpp
CATIA.SystemService.Print "Name of the Reference" & reference2.DisplayName  

Set basicComponents2 = analysisEntity4.BasicComponents
Set basicComponent2 = basicComponents2.GetItem("SAMForceAxis.1")
basicComponent2.SetValue "Values", 0, 0, 0, 1
```
```vbscript
Set basicComponent3 = basicComponents2.GetItem("SAMForceVector.1")
basicComponent3.SetDimensions 3, 1, 1
```
basicComponent3.SetValue "", 1, 1, 1, 100.000000
basicComponent3.SetValue "", 2, 1, 1, 0.000000
basicComponent3.SetValue "", 3, 1, 1, 0.000000

' _____________________________________________________________________________________
' Some examples to read the data on the basic componenent
'In this case, direct read 
```cpp
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

For i = 1 to SubList.Count
```
```cpp
	Set Parameter = SubList.Item(i)
	CATIA.SystemService.Print Parameter.Name  
	CATIA.SystemService.Print Parameter.ValueAsString
Next
```

' _____________________________________________________________________________________
' Launch the MeshOnly update
analysisCase1.ComputeMeshOnly

'------------------------------- END   END   END   ----------------------------
```cpp
  CATIA.DisplayFileAlerts = False

End Sub

 
```
 

```cpp
Language=&quot;VBSCRIPT&quot;
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

```cpp
Sub CATMain(#)
'_____________________________________________________________________________________
```
' Optional: allows to find the sample wherever it's installed

```cpp
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
  sSep=CATIA.SystemService.Environ(&quot;ADL_ODT_SLASH&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
'_____________________________________________________________________________________
' Get the collection of documents in session
```cpp
  Set documents1 = CATIA.Documents

' Create the CATAnalysis Document 
```
```vbscript
  Set TheAnalysisDoc = documents1.Add(&quot;Analysis&quot;)

' Only one Analysis Document is required
```
' if WB name already is &quot;GPSCfg&quot;, not to use StartWorkbench
```cpp
  WBName = CATIA.GetWorkbenchId
  if (WBName &lt;&gt; &quot;GPSCfg&quot;) Then
```
```cpp
     CATIA.StartWorkbench(&quot;GPSCfg&quot;)
  End If
```

'_____________________________________________________________________________________
' Start to scan the existing structure of analysis document:  Retrieve the AnalysisManager
' We call the Import on CATAnalysisImport which implements CATISamImportDefine
```

```vbscript
```vbscript
Set analysisManager1 = TheAnalysisDoc.Analysis
```
```

```vbscript
```cpp
Dim arrayOfVariantOfShort1(0)
  analysisManager1.ImportDefineFile (sDocPath &amp; sSep  &amp; &quot;online&quot; &amp; sSep &amp; &quot;CAAScdAniUseCases&quot; &amp; sSep &amp; &quot;samples&quot; &amp; sSep &amp; &quot;basic_assembly.CATProduct&quot;),				     &quot;
```
```

```cpp
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1

' _____________________________________________________________________________________
' Reframe All.
```cpp
  Set specsAndGeomWindow2 = CATIA.ActiveWindow
  Set viewer3D1 = specsAndGeomWindow2.ActiveViewer
  viewer3D1.Reframe 
```

' _____________________________________________________________________________________
' Scan the analysis document:  Retrieve the Pointed documents to extract the reference for preprocessing
```cpp
  Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
  CATIA.SystemService.Print analysisLinkedDocuments1.Name
  If (analysisLinkedDocuments1.Count &lt;&gt; 1 ) Then
```
```vbscript
    Err.Raise 9999,,&quot;NbDoc Li NE 1&quot;
  End If
```

' _____________________________________________________________________________________
' Retrieve the CATProduct Document and associated publications and constraints collection.

```cpp
  Set productDocument1 = analysisLinkedDocuments1.Item(1)

  Set product1 = productDocument1.Product
  Set products1 = product1.Products

  Set publications1 = product1.Publications
  Set constraints1 = product1.Connections(&quot;CATIAConstraints&quot;)

' _____________________________________________________________________________________
```
' Create a Virtual Part in the analysis model to transmit the load.
```vbscript
Set analysisModels1 = analysisManager1.AnalysisModels
Set analysisModel1 = analysisModels1.Item(1)

Set analysisSets1 = analysisModel1.AnalysisSets
Set analysisSet1 = analysisSets1.ItemByType(&quot;PropertySet&quot;)

Set analysisEntities1 = analysisSet1.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Add(&quot;SAMVirPartRigid&quot;)
Set publication1 = publications1.Item(&quot;FaceCylinderTop&quot;)
analysisEntity1.AddSupportFromPublication product1, publication1
```
```vbscript
Set basicComponents1 = analysisEntity1.BasicComponents
Set basicComponent1 = basicComponents1.GetItem(&quot;SAMRigSlavePoint.1&quot;)
Set publication4 = publications1.Item(&quot;ForceHandler&quot;)
basicComponent1.AddSupportFromPublication product1, publication4
```

' _____________________________________________________________________________________
' Create a Fastened connection in the analysis model to complete the constraints 
' definition
```vbscript
Set analysisEntity2 = analysisEntities1.Add(&quot;SAMFaceFaceFastened&quot;)
Set constraint1 = constraints1.Item(&quot;Surface contact.2&quot;)
analysisEntity2.AddSupportFromConstraint product1, constraint1
```

' _____________________________________________________________________________________
' Create a Static Case in the current analysis model.
```vbscript
Set analysisCases1 = analysisModel1.AnalysisCases
Set analysisCase1 = analysisCases1.Add(#)

Set analysisSets2 = analysisCase1.AnalysisSets
Set analysisSet2 = analysisSets2.Add(&quot;RestraintSet&quot;, catAnalysisSetIn)
Set analysisSet3 = analysisSets2.Add(&quot;LoadSet&quot;, catAnalysisSetIn)
Set analysisSet5 = analysisCase1.AddSolution(&quot;StaticSet&quot;)

' _____________________________________________________________________________________
```
' Create clamp boundary. Associated to a publication
```vbscript
Set analysisEntities2 = analysisSet2.AnalysisEntities
Set analysisEntity3 = analysisEntities2.Add(&quot;SAMClamp&quot;)
Set publication2 = publications1.Item(&quot;FaceToClamp&quot;)
analysisEntity3.AddSupportFromPublication product1, publication2
```

' _____________________________________________________________________________________
' Create load boundary. Associated to the virtual part
```vbscript
Set analysisEntities3 = analysisSet3.AnalysisEntities

Set analysisEntity4 = analysisEntities3.Add(&quot;SAMDistributedForce&quot;)
Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity1)
analysisEntity4.AddSupportFromReference reference2, reference2
```
```cpp
CATIA.SystemService.Print &quot;Name of the Reference&quot; &amp; reference2.DisplayName  

Set basicComponents2 = analysisEntity4.BasicComponents
Set basicComponent2 = basicComponents2.GetItem(&quot;SAMForceAxis.1&quot;)
basicComponent2.SetValue &quot;Values&quot;, 0, 0, 0, 1
```
```vbscript
Set basicComponent3 = basicComponents2.GetItem(&quot;SAMForceVector.1&quot;)
basicComponent3.SetDimensions 3, 1, 1
```
basicComponent3.SetValue &quot;&quot;, 1, 1, 1, 100.000000
basicComponent3.SetValue &quot;&quot;, 2, 1, 1, 0.000000
basicComponent3.SetValue &quot;&quot;, 3, 1, 1, 0.000000

' _____________________________________________________________________________________
' Some examples to read the data on the basic componenent
'In this case, direct read 
```cpp
CATIA.SystemService.Print &quot; ForceVector &quot; &amp; basicComponent3.GetValue(&quot;&quot;, 1, 1, 1) 
CATIA.SystemService.Print &quot; ForceVector &quot; &amp; basicComponent3.GetValue(&quot;&quot;, 2, 1, 1)
CATIA.SystemService.Print &quot; ForceVector &quot; &amp; basicComponent3.GetValue(&quot;&quot;, 3, 1, 1)

CATIA.SystemService.Print &quot; ForceVector Type &quot; &amp; basicComponent3.Type  
CATIA.SystemService.Print &quot; ForceVector Dimension &quot; &amp; basicComponent3.GetLinesNumber  (&quot;&quot;)
CATIA.SystemService.Print &quot; ForceVector Dimension &quot; &amp; basicComponent3.GetColumnsNumber(&quot;&quot;)
CATIA.SystemService.Print &quot; ForceVector Dimension &quot; &amp; basicComponent3.GetLayersNumber (&quot;&quot;)

'In this case, use the Kwe CATIAParameter interface.
```
```vbscript
Set ParametersList = analysisManager1.Parameters
Set SubList = ParametersList.SubList(basicComponent3,FALSE)

For i = 1 to SubList.Count
```
```cpp
	Set Parameter = SubList.Item(i)
	CATIA.SystemService.Print Parameter.Name  
	CATIA.SystemService.Print Parameter.ValueAsString
Next
```

' _____________________________________________________________________________________
' Launch the MeshOnly update
analysisCase1.ComputeMeshOnly

'------------------------------- END   END   END   ----------------------------
```cpp
  CATIA.DisplayFileAlerts = False

End Sub
```
```