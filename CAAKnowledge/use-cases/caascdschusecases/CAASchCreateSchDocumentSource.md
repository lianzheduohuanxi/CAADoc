---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdSchUseCases", "CAASCH_Detail01", "CAASchCreateSchDocument"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocumentSource.htmmd"
converted: "2026-05-11T11:27:02.643369"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Create a schematic document.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
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

    dim sSavePath As String 
```cpp
    sSavePath=CATIA.SystemService.Environ("CATSavePath")

    CATIA.SystemService.Print "CATSavePath = " & sSavePath

    If (Not CATIA.FileSystem.FolderExists(sSavePath)) Then
      Err.Raise 9999,sSavePath,"No Path for saving document"
    End If
```

    ' Open main schematic P&ID design document 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_Detail01.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessage As String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchCreateSchDocument.CATScript" & vbCrLf

    '
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

```vbscript
    Dim objSchSession As SchSession
    Dim objSchDocNew As Document
    Dim bInteractive As boolean

```

    If ( Not ( objSchRoot Is Nothing ) ) Then

       '-----------------------------------------------------------------------
       ' Get the schematic session.
       '-----------------------------------------------------------------------

```vbscript
       Set objSchSession = objSchRoot.GetSchematicSession
       If ( Not ( objSchSession Is Nothing ) ) Then
```
         strMessage = strMessage &  "Got schematic session" & vbCr

         '---------------------------------------------------------------------
         ' Create another schematic document.
         '---------------------------------------------------------------------
         'bInteractive = true
         bInteractive = false
         objSchSession.CreateDocument "CATProduct",bInteractive,objSchDocNew

         If ( Not ( objSchDocNew Is Nothing ) ) Then

```vbscript
            Set objPrdRoot = Nothing
            Set objSchRoot = Nothing

            Set objPrdRoot = objSchDocNew.Product 
            If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
               Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
            End If
```

            If ( Not ( objSchRoot Is Nothing ) ) Then
               objSchRoot.SetDrawingStandard catISO
               strMessage = strMessage & "drawing standard set to catISO" & vbCr
```vbscript
               Dim std As CatDrawingStandard
               std = objSchRoot.GetDrawingStandard
```
               strMessage = strMessage & "drawing standard = " & std & vbCr
            End If

```vbscript
            Dim strDocName As String

```

            strDocName = objSchDocNew.FullName

            strMessage = strMessage & "document created" & vbCr
            strMessage = strMessage & "default name = " & strDocName & vbCr

```cpp
            strDocName = CATIA.FileSystem.ConcatenatePaths(sSavePath, _
			              "SampleOutput_SchDoc01.CATProduct")
```

            objSchDocNew.SaveAs strDocName

            strMessage = strMessage &  "document created" & vbCr
            strMessage = strMessage &  "document saved as " & strDocName & vbCr
         End If

       End If '--- If ( Not ( objSchDocNew ...

    End If  '----If ( Not ( objSchRoot Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Create a schematic document.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
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

    dim sSavePath As String 
```cpp
    sSavePath=CATIA.SystemService.Environ("CATSavePath")

    CATIA.SystemService.Print "CATSavePath = " & sSavePath

    If (Not CATIA.FileSystem.FolderExists(sSavePath)) Then
      Err.Raise 9999,sSavePath,"No Path for saving document"
    End If
```

    ' Open main schematic P&ID design document 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_Detail01.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessage As String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchCreateSchDocument.CATScript" & vbCrLf

    '
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

```vbscript
    Dim objSchSession As SchSession
    Dim objSchDocNew As Document
    Dim bInteractive As boolean

```

    If ( Not ( objSchRoot Is Nothing ) ) Then

       '-----------------------------------------------------------------------
       ' Get the schematic session.
       '-----------------------------------------------------------------------

```vbscript
       Set objSchSession = objSchRoot.GetSchematicSession
       If ( Not ( objSchSession Is Nothing ) ) Then
```
         strMessage = strMessage &  "Got schematic session" & vbCr

         '---------------------------------------------------------------------
         ' Create another schematic document.
         '---------------------------------------------------------------------
         'bInteractive = true
         bInteractive = false
         objSchSession.CreateDocument "CATProduct",bInteractive,objSchDocNew

         If ( Not ( objSchDocNew Is Nothing ) ) Then

```vbscript
            Set objPrdRoot = Nothing
            Set objSchRoot = Nothing

            Set objPrdRoot = objSchDocNew.Product 
            If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
               Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
            End If
```

            If ( Not ( objSchRoot Is Nothing ) ) Then
               objSchRoot.SetDrawingStandard catISO
               strMessage = strMessage & "drawing standard set to catISO" & vbCr
```vbscript
               Dim std As CatDrawingStandard
               std = objSchRoot.GetDrawingStandard
```
               strMessage = strMessage & "drawing standard = " & std & vbCr
            End If

```vbscript
            Dim strDocName As String

```

            strDocName = objSchDocNew.FullName

            strMessage = strMessage & "document created" & vbCr
            strMessage = strMessage & "default name = " & strDocName & vbCr

```cpp
            strDocName = CATIA.FileSystem.ConcatenatePaths(sSavePath, _
			              "SampleOutput_SchDoc01.CATProduct")
```

            objSchDocNew.SaveAs strDocName

            strMessage = strMessage &  "document created" & vbCr
            strMessage = strMessage &  "document saved as " & strDocName & vbCr
         End If

       End If '--- If ( Not ( objSchDocNew ...

    End If  '----If ( Not ( objSchRoot Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub
```
```