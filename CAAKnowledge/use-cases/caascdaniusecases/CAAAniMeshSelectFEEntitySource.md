---
title: "CAAAniMeshSelectFEEntity.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniMeshSelectFEEntity", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSelectFEEntitySource.htm"
converted: "2026-05-11T11:27:02.528621"
---

'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Select a mesh element  
'                Select a mesh node
'  Assumptions:   Looks for AllElementsAndNode.CATAnalysis in the directory
'  Author:       jgw
'  Languages:    VBScript
'  Locales:      English 
'  CATIA Level:  V5R21
'***********************************************************************

Sub CATMain()
'----------------------------------------------------------- 
'Optional: allows to find the sample wherever it's installed

  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
'----------------------------------------------------------- 

'Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\AllElementsAndNode.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the Selection object
Set oSelection = oAnalysisDocument.Selection

Dim InputObjectType(0)

'Set the selection type
InputObjectType(0) = "AnalysisMeshElement"

'Get the status
oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh element", True )

'Get the object in the selection
Set oMeshElement = oSelection.Item(1).Value

'Display message
MsgBox "Selected element: " & oMeshElement.Name

'Clear selection
oSelection.Clear

'Set the selection type
InputObjectType(0) = "AnalysisMeshNode"

'Get the status
oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh node", True )

'Get the object in the selection
Set oMeshNode = oSelection.Item(1).Value

'Display message
MsgBox "Selected node: " & oMeshNode.Name

'Clear selection
oSelection.Clear 

End Sub



```vbscript
&#39;COPYRIGHT DASSAULT SYSTEMES 2000

&#39;***********************************************************************
&#39;  Purpose:      Open an analysis document
&#39;                Select a mesh element  
&#39;                Select a mesh node
&#39;  Assumptions:   Looks for AllElementsAndNode.CATAnalysis in the directory
&#39;  Author:       jgw
&#39;  Languages:    VBScript
&#39;  Locales:      English 
&#39;  CATIA Level:  V5R21
&#39;***********************************************************************

Sub CATMain()
&#39;----------------------------------------------------------- 
&#39;Optional: allows to find the sample wherever it&#39;s installed

  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
&#39;----------------------------------------------------------- 

&#39;Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\AllElementsAndNode.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

&#39;Retrieve the Selection object
Set oSelection = oAnalysisDocument.Selection

Dim InputObjectType(0)

&#39;Set the selection type
InputObjectType(0) = &quot;AnalysisMeshElement&quot;

&#39;Get the status
oStatus = oSelection.SelectElement2 ( InputObjectType, &quot;Select a mesh element&quot;, True )

&#39;Get the object in the selection
Set oMeshElement = oSelection.Item(1).Value

&#39;Display message
MsgBox "Selected element: " & oMeshElement.Name

&#39;Clear selection
oSelection.Clear

&#39;Set the selection type
InputObjectType(0) = &quot;AnalysisMeshNode&quot;

&#39;Get the status
oStatus = oSelection.SelectElement2 ( InputObjectType, &quot;Select a mesh node&quot;, True )

&#39;Get the object in the selection
Set oMeshNode = oSelection.Item(1).Value

&#39;Display message
MsgBox "Selected node: " & oMeshNode.Name

&#39;Clear selection
oSelection.Clear 

End Sub
```