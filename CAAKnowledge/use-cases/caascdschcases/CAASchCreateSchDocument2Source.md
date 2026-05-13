---
```vbscript
title: "CAASchCreateSchDocument2.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASchCreateSchDocument2"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocument2Source.htmmd"
converted: "2026-05-11T17:31:51.347682"
```

---
tags: ["CATIA", "CAASchCreateSchDocument2"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocument2Source.htmmd"
converted: "2026-05-11T17:31:51.347682"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Create a schematic document (2).
    '   Assumtions:   Product level: Schematic Platform (SDI).
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
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
        dim sSavePath As String
```vbscript
        sSavePath=CATIA.SystemService.Environ("CATSavePath")

        If (Not CATIA.FileSystem.FolderExists(sSavePath)) Then
```
```

```

```

```vbscript
```vbscript
          Err.Raise 9999,sSavePath,"No Path for saving document"
```vbscript
```
```vbscript
        End If
        ' -------------------------------------------------------------------------

```vbscript
        Dim strMessage As String

```
```

```

```

```vbscript
```vbscript
Dim strMessage As String
        strMessage = _
```
```

          "--------------------------------------------------------------------" & vbCr
        strMessage = strMessage & _
          "Output traces from CAASchCreateSchDocument2.CATScript" & vbCrLf
```vbscript
```vbscript
```vbscript
        '--------------------------------------------------------------------------
        ' Create a CATProduct document
        '--------------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
        Dim objSchDoc As Document
```vbscript
```
```vbscript
```vbscript
        Set objSchDoc = CATIA.Documents.Add ("CATProduct")
        '
```
```

```

```

```vbscript
```vbscript
```vbscript
        ' Find the top node of the schematic object tree - schematic root.
```vbscript
        Dim objPrdRoot As Product
        Dim objSchRoot As SchematicRoot
        '--------------------------------------------------------------------------
```
        ' Associate schematic behavior to the CATProduct document through
        ' the method GetTechnologicalObject.
        '--------------------------------------------------------------------------
```vbscript
        Dim strRootName As String
        Dim strDocName As String
```
```

```

        strRootName = "Sample_SchematicRoot"
```vbscript
        strDocName = CATIA.FileSystem.ConcatenatePaths(sSavePath, _
```
```

    	             "SampleOutput_SchDoc02.CATProduct")

```vbscript
        If ( Not ( objSchDoc Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
          Set objPrdRoot = objSchDoc.Product
          If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
            Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
            objPrdRoot.PartNumber = strRootName
```
          End If

```

```

```

```vbscript
          If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Regular CATProduct is a 3D document and is associated with a 3D
             ' editor and a 3D viewer. On the other hand a schematic document
             ' is a special CATProduct document that is associated with a special
             ' 2D viewer and 2D editor. Therefore, we need to trigger the
             ' documentation initialization (which has already been done in
             ' CATDocuments.Add) again after associating schematic
             ' behavior to the document,
             ' by saving the document and re-opening it again.
             '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' behavior to the document,
' by saving the document and re-opening it again.
'---------------------------------------------------------------------
```

```

             objSchDoc.SaveAs strDocName

```

             objSchDoc.Close

```vbscript
```vbscript
```vbscript
             Set objSchDoc = CATIA.Documents.Open (strDocName)

             Set objPrdRoot = Nothing
```
```

```vbscript
```vbscript
```vbscript
             Set objSchRoot = Nothing
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
```

```

```

```vbscript
```vbscript
```vbscript
             '---------------------------------------------------------------------
```vbscript
             ' Set the drawing standard if needed
             '---------------------------------------------------------------------
```
             If ( Not ( objSchRoot Is Nothing ) ) Then
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
' Set the drawing standard if needed
'---------------------------------------------------------------------
```
If ( Not ( objSchRoot Is Nothing ) ) Then
```

```

                objSchRoot.SetDrawingStandard catISO
                strMessage = strMessage & "drawing standard set to catISO" & vbCr
```vbscript
                Dim std As CatDrawingStandard
                std = objSchRoot.GetDrawingStandard
```
                strMessage = strMessage & "drawing standard = " & std & vbCr
             End If
```vbscript
```vbscript
             'objSchDoc.SaveAs strDocName

```

```

```

```vbscript
```vbscript
           End If  '----If ( Not ( objSchRoot Is Nothing )...

```

```

```vbscript
```vbscript
        End If

```

```

```vbscript
End If
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
