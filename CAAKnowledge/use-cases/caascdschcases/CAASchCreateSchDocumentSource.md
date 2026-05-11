---
```vbscript
title: "CAASchCreateSchDocument.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASCH_Detail01", "CAASchCreateSchDocument", "CAAScdSchUseCases"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocumentSource.htm"
converted: "2026-05-11T17:31:51.349674"
```

---
tags: ["CATIA", "CAASCH_Detail01", "CAASchCreateSchDocument", "CAAScdSchUseCases"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocumentSource.htm"
converted: "2026-05-11T17:31:51.349674"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Create a schematic document.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
```

```

```

    Sub CATMain()
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed

```

```

```vbscript
```vbscript
```vbscript
' -------------------------------------------------------------------------
' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")

```

```

```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
```vbscript
```vbscript
        End If

```

```

```

```vbscript
Err.Raise 9999,sDocPath,"No Doc Path Defined"
```

End If
```vbscript
```vbscript
        dim sSavePath As String
        sSavePath=CATIA.SystemService.Environ("CATSavePath")

```

```

```vbscript
```vbscript
        CATIA.SystemService.Print "CATSavePath = " & sSavePath

        If (Not CATIA.FileSystem.FolderExists(sSavePath)) Then
```

```vbscript
```vbscript
          Err.Raise 9999,sSavePath,"No Path for saving document"
        End If
```

```

```

```vbscript
```vbscript
```vbscript
        ' Open main schematic P&ID; design document
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

```

```

                "online\CAAScdSchUseCases\samples\CAASCH_Detail01.CATProduct")

```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```vbscript
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)

        Dim strMessage As String

```

```

```

```vbscript
Dim strMessage As String
        strMessage = _
```

          "--------------------------------------------------------------------" & vbCr
strMessage = _
        strMessage = strMessage & _

          "Output traces from CAASchCreateSchDocument.CATScript" & vbCrLf
strMessage = _
strMessage = strMessage & _
        '
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

        Dim objSchSession As SchSession
        Dim objSchDocNew As Document
        Dim bInteractive As boolean

```

```

```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Get the schematic session.
           '-----------------------------------------------------------------------

           Set objSchSession = objSchRoot.GetSchematicSession
           If ( Not ( objSchSession Is Nothing ) ) Then
```

```

             strMessage = strMessage &  "Got schematic session" & vbCr
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Create another schematic document.
             '---------------------------------------------------------------------
             'bInteractive = true
```

```

             bInteractive = false
```

```vbscript
```vbscript
```vbscript
'---------------------------------------------------------------------
'bInteractive = true
```

```

bInteractive = false
             objSchSession.CreateDocument "CATProduct",bInteractive,objSchDocNew

```

```vbscript
```vbscript
             If ( Not ( objSchDocNew Is Nothing ) ) Then

                Set objPrdRoot = Nothing
```

```vbscript
```vbscript
                Set objSchRoot = Nothing

                Set objPrdRoot = objSchDocNew.Product
                If ( Not ( objPrdRoot Is Nothing ) ) Then
                   Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
                End If

```

```

```

```vbscript
                If ( Not ( objSchRoot Is Nothing ) ) Then
                   objSchRoot.SetDrawingStandard catISO
                   strMessage = strMessage & "drawing standard set to catISO" & vbCr
                   Dim std As CatDrawingStandard
                   std = objSchRoot.GetDrawingStandard
                   strMessage = strMessage & "drawing standard = " & std & vbCr
```vbscript
                End If

                Dim strDocName As String

```

```

```vbscript
Dim strDocName As String
                strDocName = objSchDocNew.FullName

```

                strMessage = strMessage & "document created" & vbCr
                strMessage = strMessage & "default name = " & strDocName & vbCr

```vbscript
                strDocName = CATIA.FileSystem.ConcatenatePaths(sSavePath, _

```

    			              "SampleOutput_SchDoc01.CATProduct")

strMessage = strMessage & "default name = " & strDocName & vbCr
strDocName = CATIA.FileSystem.ConcatenatePaths(sSavePath, _
                objSchDocNew.SaveAs strDocName

                strMessage = strMessage &  "document created" & vbCr
                strMessage = strMessage &  "document saved as " & strDocName & vbCr
```vbscript
```vbscript
             End If

```

```

```vbscript
```vbscript
           End If '--- If ( Not ( objSchDocNew ...

```

```

```vbscript
```vbscript
        End If  '----If ( Not ( objSchRoot Is Nothing )...

```

```

```vbscript
End If  '----If ( Not ( objSchRoot Is Nothing )...
        strMessage = strMessage & _
```

          "--------------------------------------------------------------------" & vbCr
        MsgBox strMessage

```vbscript
    End Sub

```
