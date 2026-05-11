---
```vbscript
title: "CAASchSyncCompInst.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASchSyncCompInst", "CATIASchComponent", "CAASCH_SyncCompInst", "CAAScdSchUseCases", "CATIA", "CATIASchUpdateInstances"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchSyncCompInstSource.htm"
converted: "2026-05-11T17:31:51.504791"
```

---
tags: ["CAASchSyncCompInst", "CATIASchComponent", "CAASCH_SyncCompInst", "CAAScdSchUseCases", "CATIA", "CATIASchUpdateInstances"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchSyncCompInstSource.htm"
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
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```

```

```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
```vbscript
        End If
```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Open the schematic document
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

```

```

                "online\CAAScdSchUseCases\samples\CAASCH_SyncCompInst.CATProduct")

```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```vbscript
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)

        Dim strMessageAs String

```

```

```

```vbscript
Dim strMessageAs String
        strMessage = _
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
        Dim objPrdRoot As Product
```vbscript
```vbscript
        Dim objSchRoot As SchematicRoot
        If ( Not ( objSchDoc Is Nothing ) ) Then
          Set objPrdRoot = objSchDoc.Product
          If ( Not ( objPrdRoot Is Nothing ) ) Then
            Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
          End If
        End If
        ' Get SchUpdateInstances interface on the schematic root.
        Dim objUpdateInstancesAs SchUpdateInstances

```

```

```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```vbscript
```vbscript
           Set objUpdateInstances = objSchRoot.GetInterface ("CATIASchUpdateInstances",objSchRoot)
        End If
```

```

```

```vbscript
```vbscript
```vbscript
        ' Find a list of reference component in the model
        Dim objLCompRefsAs SchListOfObjects
        Dim objCompRefAs SchComponent
        If ( Not ( objSchRoot Is Nothing ) ) Then
           Set objLCompRefs = objSchRoot.GetRefComponents
           ' Get the first reference component
           If ( Not ( objLCompRefs Is Nothing ) )Then
              Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")
           End If
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
        MsgBox strMessage

```vbscript
    End Sub

```
