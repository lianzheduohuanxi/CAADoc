---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CAASCH_SyncCompInst", "CATIA", "CAAScdSchUseCases", "CAASchSyncCompInst", "CATIASchComponent", "CATIASchUpdateInstances"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchSyncCompInstSource.htmmd"
converted: "2026-05-11T11:27:02.652678"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2007

' *****************************************************************************
'   Purpose:      Update component instances when the catalog ref was modiifed.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R18 
' *****************************************************************************

```cpp
Sub CATMain(#)

```

    ' ------------------------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,sDocPath,"No Doc Path Defined"
    End If
```

    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_SyncCompInst.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessageAs String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchSyncCompInst.CATScript" & vbCrLf

    ' Find the top node of the schematic object tree - schematic root.
```vbscript
    Dim objPrdRoot As Product
    Dim objSchRoot As SchematicRoot
    If ( Not ( objSchDoc Is Nothing ) ) Then
```
```vbscript
      Set objPrdRoot = objSchDoc.Product 
      If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
      End If
```
    End If

    ' Get SchUpdateInstances interface on the schematic root. 
```vbscript
    Dim objUpdateInstancesAs SchUpdateInstances

    If ( Not ( objSchRoot Is Nothing ) ) Then
```
```cpp
       Set objUpdateInstances = objSchRoot.GetInterface ("CATIASchUpdateInstances",objSchRoot) 
    End If 
```
   
    ' Find a list of reference component in the model
```vbscript
    Dim objLCompRefsAs SchListOfObjects
    Dim objCompRefAs SchComponent
    If ( Not ( objSchRoot Is Nothing ) ) Then
```
```vbscript
       Set objLCompRefs = objSchRoot.GetRefComponents

       ' Get the first reference component 
```
       If ( Not ( objLCompRefs Is Nothing ) )Then
```cpp
          Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")
       End If
```
    End If 
   
    ' Synchronize component instances of the first reference component 
    If ( Not ( objCompRef Is Nothing ) And _
         Not ( objUpdateInstances Is Nothing ) )Then

       strMessage = strMessage & _ 
         "Synchronizing instances for the first reference component" & vbCr 

       objUpdateInstances.UpdateAllInstancesFromReference objCompRef

    End If '--- If ( Not ( objCompRef Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2007

' *****************************************************************************
'   Purpose:      Update component instances when the catalog ref was modiifed.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R18 
' *****************************************************************************

```cpp
Sub CATMain(#)

```

    ' ------------------------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,sDocPath,"No Doc Path Defined"
    End If
```

    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_SyncCompInst.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessageAs String

```

    strMessage = _
      "--------------------------------------------------------------------" &amp; vbCr
    strMessage = strMessage & _
      "Output traces from CAASchSyncCompInst.CATScript" & vbCrLf

    ' Find the top node of the schematic object tree - schematic root.
```vbscript
    Dim objPrdRoot As Product
    Dim objSchRoot As SchematicRoot
    If ( Not ( objSchDoc Is Nothing ) ) Then
```
```vbscript
      Set objPrdRoot = objSchDoc.Product 
      If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
      End If
```
    End If

    ' Get SchUpdateInstances interface on the schematic root. 
```vbscript
    Dim objUpdateInstancesAs SchUpdateInstances

    If ( Not ( objSchRoot Is Nothing ) ) Then
```
```cpp
       Set objUpdateInstances = objSchRoot.GetInterface ("CATIASchUpdateInstances",objSchRoot) 
    End If 
```
   
    ' Find a list of reference component in the model
```vbscript
    Dim objLCompRefsAs SchListOfObjects
    Dim objCompRefAs SchComponent
    If ( Not ( objSchRoot Is Nothing ) ) Then
```
```vbscript
       Set objLCompRefs = objSchRoot.GetRefComponents

       ' Get the first reference component 
```
       If ( Not ( objLCompRefs Is Nothing ) )Then
```cpp
          Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")
       End If
```
    End If 
   
    ' Synchronize component instances of the first reference component 
    If ( Not ( objCompRef Is Nothing ) And _
         Not ( objUpdateInstances Is Nothing ) )Then

       strMessage = strMessage &amp; _ 
         "Synchronizing instances for the first reference component" &amp; vbCr 

       objUpdateInstances.UpdateAllInstancesFromReference objCompRef

    End If '--- If ( Not ( objCompRef Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub
```
```