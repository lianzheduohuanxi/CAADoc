---
title: "CAASchCompRefGraphic.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: "["CAAScdSchUseCases", "CAASchCompRefGraphic", "CATIA", "CATIASchGRR", "CATIASchCompGraphic", "CAASCH_Detail03"]"
source_file: "Doc/online/CAAScdSchUseCases/CAASchCompRefGraphicSource.htm"
converted: "2026-05-11T17:31:51.333715"
---
tags: ["CAAScdSchUseCases", "CAASchCompRefGraphic", "CATIA", "CATIASchGRR", "CATIASchCompGraphic", "CAASCH_Detail03"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCompRefGraphicSource.htmmd"
converted: "2026-05-11T17:31:51.333715"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Add/List graphical representations to a reference component.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```cpp
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
```cpp
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdSchUseCases/samples/CAASCH_Detail03.CATProduct")

```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```cpp
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)

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
strMessage = _
        strMessage = strMessage & _

          "Output traces from CAASchCompRefGraphic.CATScript" & vbCrLf
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

```vbscript
        Dim objLCompRefs As SchListOfObjects
        Dim objCompRefGraphic As SchCompGraphic

```
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
           ' Find a list of reference component in the model
           '-----------------------------------------------------------------------
```vbscript
           Set objLCompRefs = objSchRoot.GetRefComponents
```
```

```

```

```vbscript
           If ( Not ( objLCompRefs Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              ' Get a SchCompGraphic interface handle from a reference
              ' component
              '--------------------------------------------------------------------
```cpp
              Set objCompRefGraphic = objLCompRefs.Item (1,"CATIASchCompGraphic")
```
```

```

```

```vbscript
```vbscript
              If ( Not ( objCompRefGraphic Is Nothing ) ) Then

```vbscript
                  Dim objUnassocSymbol As AnyObject
```
```

```

```vbscript
```vbscript
```vbscript
                  '----------------------------------------------------------------
                  ' Find a symbol that is not associated with any reference in
                  ' the model
                  '----------------------------------------------------------------
```vbscript
                  Set objUnassocSymbol = GetComponentSymbol (objSchRoot)
```
```

```

```

```vbscript
                  If ( Not ( objUnassocSymbol Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
                    '--------------------------------------------------------------
                    '  Add the second graphical representation to the reference
                    '  component using the symbol just found
                    '--------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'  Add the second graphical representation to the reference
'  component using the symbol just found
'--------------------------------------------------------------
```

```

                    objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

```

                    strMessage = strMessage & "Successfully add the second graphical representation" & vbCr

```vbscript
                  End If
```

```vbscript
```vbscript
```vbscript
                  '----------------------------------------------------------------
                  ' Find another symbol that is not associated with
                  ' any reference in the model
                  '----------------------------------------------------------------
```vbscript
                  Set objUnassocSymbol = GetComponentSymbol (objSchRoot)
                  If ( Not ( objUnassocSymbol Is Nothing ) ) Then
```
                    '--------------------------------------------------------------
                    '  Add the third graphical representation to the reference
                    '  component using the symbol just found
                    '--------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'  Add the third graphical representation to the reference
'  component using the symbol just found
'--------------------------------------------------------------
```

```

                    objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

```

                    strMessage = strMessage & "Successfully add the third graphical representation" & vbCr

```vbscript
```vbscript
                  End If

```vbscript
                  Dim intNbGraphic As Integer
```
```

```vbscript
```vbscript
```vbscript
                  Dim objGRR As SchGRR
                  Dim objLGraphic As SchListOfObjects
                  Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations

```
```

```

```

```vbscript
                  If ( Not ( objLGraphic Is Nothing ) ) Then
                     intNbGraphic = objLGraphic.Count
                     strMessage = strMessage & "Number of graphical representations"
                     strMessage = strMessage & "= " & intNbGraphic & vbCr

```vbscript
                     Set objGRR = Nothing
```vbscript
```
```vbscript
                     If (intNbGraphic > 1) Then
```cpp
                        Set objGRR = objLGraphic.Item(intNbGraphic,"CATIASchGRR")
                        If ( Not (objGRR Is Nothing ) ) Then
```
```

```

                           objCompRefGraphic.RemoveGraphicalRepresentation objGRR
```vbscript
                           Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
```vbscript
```
                           If ( Not ( objLGraphic Is Nothing ) ) Then
```

                              intNbGraphic = objLGraphic.Count
                              strMessage = strMessage & "Number of graphical representations"
                              strMessage = strMessage & "after calling "
                              strMessage = strMessage & " RemoveGraphicalRepresentation = " & intNbGraphic & vbCr
                           End If
```vbscript
```vbscript
                        End If
                     End If ' --- If (intNbGraphic > 1)
                  End If '--- If ( Not ( objLGraphic Is Nothing ) ) Then

```

```

```

```vbscript
```vbscript
              End If '--- If ( Not ( objCompRefGraphic Is Nothing )...

```

```

```vbscript
```vbscript
           End If '--- If ( Not ( objLCompRefs Is Nothing ) ...

```

```

```vbscript
```vbscript
        End If '--- If ( Not ( objSchRoot Is Nothing )...

```

```

```vbscript
End If '--- If ( Not ( objSchRoot Is Nothing )...
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

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find a component symbol that has not been associated with a schematic
    ' | component from a document root.
    ' | Input: objSchRootArg:  the root of the document.
    ' | Returns: component symbol object.
    ' -----------------------------------------------------------------------------
```

```

```vbscript
```vbscript
    Private Function GetComponentSymbol (objSchRootArg As SchematicRoot) As AnyObject
       Dim objSchLSymbols As SchListOfObjects
```
```

```vbscript
```vbscript
       If ( Not ( objSchRootArg Is Nothing ) ) Then
```vbscript
          Set objSchLSymbols = objSchRootArg.GetUnassociatedSymbols
          If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```cpp
             Set GetComponentSymbol = objSchLSymbols.Item (1,"CATIASchGRR")
          End If
```
       End If
```

```

```vbscript
    End Function
```
```
