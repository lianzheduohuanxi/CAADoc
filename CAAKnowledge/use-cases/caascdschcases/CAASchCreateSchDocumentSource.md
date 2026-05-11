---
title: "CAASchCreateSchDocument.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASCH_Detail01", "CAASchCreateSchDocument", "CAAScdSchUseCases"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocumentSource.htm"
converted: "2026-05-11T17:31:51.349674"
---

    Option Explicit
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Create a schematic document.
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R15 
    ' *****************************************************************************
```

    
```vbscript
    Sub CATMain()
        ' ------------------------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
    
```

        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
    
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
        End If
    
```

        dim sSavePath As String 
        sSavePath=CATIA.SystemService.Environ("CATSavePath")
    
```vbscript
        CATIA.SystemService.Print "CATSavePath = " & sSavePath
    
        If (Not CATIA.FileSystem.FolderExists(sSavePath)) Then
          Err.Raise 9999,sSavePath,"No Path for saving document"
        End If
```vbscript
        ' Open main schematic P&ID; design document 
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                "online\CAAScdSchUseCases\samples\CAASCH_Detail01.CATProduct")
    
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
          Set objPrdRoot = objSchDoc.Product 
          If ( Not ( objPrdRoot Is Nothing ) ) Then
            Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
          End If
        End If
    
        Dim objSchSession As SchSession
        Dim objSchDocNew As Document
        Dim bInteractive As boolean
    
```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```vbscript
           '-----------------------------------------------------------------------
           ' Get the schematic session.
           '-----------------------------------------------------------------------
    
           Set objSchSession = objSchRoot.GetSchematicSession
           If ( Not ( objSchSession Is Nothing ) ) Then
             strMessage = strMessage &  "Got schematic session" & vbCr
             '---------------------------------------------------------------------
             ' Create another schematic document.
             '---------------------------------------------------------------------
             'bInteractive = true
             bInteractive = false
```

             objSchSession.CreateDocument "CATProduct",bInteractive,objSchDocNew
    
```

```vbscript
             If ( Not ( objSchDocNew Is Nothing ) ) Then
    
                Set objPrdRoot = Nothing
                Set objSchRoot = Nothing
    
                Set objPrdRoot = objSchDocNew.Product 
                If ( Not ( objPrdRoot Is Nothing ) ) Then
                   Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
                End If
    
```

```vbscript
                If ( Not ( objSchRoot Is Nothing ) ) Then
                   objSchRoot.SetDrawingStandard catISO
                   strMessage = strMessage & "drawing standard set to catISO" & vbCr
                   Dim std As CatDrawingStandard
                   std = objSchRoot.GetDrawingStandard
                   strMessage = strMessage & "drawing standard = " & std & vbCr
                End If
    
                Dim strDocName As String
    
```

                strDocName = objSchDocNew.FullName
    
                strMessage = strMessage & "document created" & vbCr
                strMessage = strMessage & "default name = " & strDocName & vbCr
    
                strDocName = CATIA.FileSystem.ConcatenatePaths(sSavePath, _
    			              "SampleOutput_SchDoc01.CATProduct")
    
                objSchDocNew.SaveAs strDocName
    
                strMessage = strMessage &  "document created" & vbCr
                strMessage = strMessage &  "document saved as " & strDocName & vbCr
             End If
    
```

```vbscript
           End If '--- If ( Not ( objSchDocNew ...
    
```

```vbscript
        End If  '----If ( Not ( objSchRoot Is Nothing )...
    
```

        strMessage = strMessage & _
          "--------------------------------------------------------------------" & vbCr
        MsgBox strMessage
    
```vbscript
    End Sub
    
```

    
    
    
    
    
    
    

```