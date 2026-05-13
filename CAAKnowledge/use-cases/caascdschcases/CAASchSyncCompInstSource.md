---
```vbscript
title: "CAASchSyncCompInst.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASchSyncCompInst", "CATIASchComponent", "CAASCH_SyncCompInst", "CAAScdSchUseCases", "CATIA", "CATIASchUpdateInstances"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchSyncCompInstSource.htmmd"
converted: "2026-05-11T17:31:51.504791"
```

---
tags: ["CAASchSyncCompInst", "CATIASchComponent", "CAASCH_SyncCompInst", "CAAScdSchUseCases", "CATIA", "CATIASchUpdateInstances"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchSyncCompInstSource.htmmd"
converted: "2026-05-11T17:31:51.504791"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2007
    ' *****************************************************************************
    '   Purpose:      Update component instances when the catalog ref was modiifed.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R18
    ' *****************************************************************************
```

```

```

```vbscript
```vbscript
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```vbscript
        sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```

```

```vbscript
```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
```vbscript
```
        End If
```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Open the schematic document
```vbscript
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdSchUseCases/samples/CAASCH_SyncCompInst.CATProduct")

```vbscript
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```vbscript
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)

        Dim strMessageAs String

```
```

```

```

```vbscript
```vbscript
Dim strMessageAs String
        strMessage = _
```
```

          "--------------------------------------------------------------------" & vbCr
strMessage = _
        strMessage = strMessage & _

          "Output traces from CAASchSyncCompInst.CATScript" & vbCrLf
strMessage = _
strMessage = strMessage & _
```vbscript
```vbscript
        ' Find the top node of the schematic object tree - schematic root.

```

```

```vbscript
```vbscript
        Dim objPrdRoot As Product
```vbscript
```
```vbscript
```vbscript
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

```
```

```

```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
           Set objUpdateInstances = objSchRoot.GetInterface ("CATIASchUpdateInstances",objSchRoot)
        End If
```
```

```

```

```vbscript
```vbscript
```vbscript
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
```vbscript
              Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")
           End If
```
        End If
        ' Synchronize component instances of the first reference component
        If ( Not ( objCompRef Is Nothing ) And _
```

```

```

```vbscript
End If
```vbscript
' Synchronize component instances of the first reference component
```

```

If ( Not ( objCompRef Is Nothing ) And _
```vbscript
             Not ( objUpdateInstances Is Nothing ) )Then

```

           strMessage = strMessage & _
             "Synchronizing instances for the first reference component" & vbCr

           objUpdateInstances.UpdateAllInstancesFromReference objCompRef

```vbscript
```vbscript
        End If '--- If ( Not ( objCompRef Is Nothing )...

```

```

```vbscript
End If '--- If ( Not ( objCompRef Is Nothing )...
        strMessage = strMessage & _
```

          "--------------------------------------------------------------------" & vbCr
```vbscript
        MsgBox strMessage

```vbscript
```
```vbscript
    End Sub

```
```
