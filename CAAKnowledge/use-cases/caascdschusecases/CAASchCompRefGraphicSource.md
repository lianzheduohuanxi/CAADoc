---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIASchGRR", "CATIA", "CAASchCompRefGraphic", "CAAScdSchUseCases", "CAASCH_Detail03", "CATIASchCompGraphic"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCompRefGraphicSource.htmmd"
converted: "2026-05-11T11:27:02.650296"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Add/List graphical representations to a reference component. 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************

```vbscript
Sub CATMain(#)

```

    ' ------------------------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,sDocPath,"No Doc Path Defined"
    End If
```
    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```vbscript
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_Detail03.CATProduct")
```

```vbscript
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessage As String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchCompRefGraphic.CATScript" & vbCrLf

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
    Dim objLCompRefs As SchListOfObjects
    Dim objCompRefGraphic As SchCompGraphic

```

    If ( Not ( objSchRoot Is Nothing ) ) Then

       '-----------------------------------------------------------------------
       ' Find a list of reference component in the model
       '-----------------------------------------------------------------------
```vbscript
       Set objLCompRefs = objSchRoot.GetRefComponents

```

       If ( Not ( objLCompRefs Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Get a SchCompGraphic interface handle from a reference
          ' component
          '--------------------------------------------------------------------
```vbscript
          Set objCompRefGraphic = objLCompRefs.Item (1,"CATIASchCompGraphic")

          If ( Not ( objCompRefGraphic Is Nothing ) ) Then
```

```vbscript
              Dim objUnassocSymbol As AnyObject

```

              '----------------------------------------------------------------
              ' Find a symbol that is not associated with any reference in
              ' the model
              '----------------------------------------------------------------
```vbscript
              Set objUnassocSymbol = GetComponentSymbol (objSchRoot)

```

              If ( Not ( objUnassocSymbol Is Nothing ) ) Then

                '--------------------------------------------------------------
                '  Add the second graphical representation to the reference
                '  component using the symbol just found
                '--------------------------------------------------------------
                objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

                strMessage = strMessage & "Successfully add the second graphical representation" & vbCr

              End If

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
                objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

                strMessage = strMessage & "Successfully add the third graphical representation" & vbCr

              End If

```vbscript
              Dim intNbGraphic As Integer
              Dim objGRR As SchGRR
              Dim objLGraphic As SchListOfObjects
              Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
             
```
             
              If ( Not ( objLGraphic Is Nothing ) ) Then
                 intNbGraphic = objLGraphic.Count
                 strMessage = strMessage & "Number of graphical representations"
                 strMessage = strMessage & "= " & intNbGraphic & vbCr

```vbscript
                 Set objGRR = Nothing
                 If (intNbGraphic > 1) Then
```
```vbscript
                    Set objGRR = objLGraphic.Item(intNbGraphic,"CATIASchGRR")
                    If ( Not (objGRR Is Nothing ) ) Then
```
                       objCompRefGraphic.RemoveGraphicalRepresentation objGRR
```vbscript
                       Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
                       If ( Not ( objLGraphic Is Nothing ) ) Then
```
                          intNbGraphic = objLGraphic.Count
                          strMessage = strMessage & "Number of graphical representations"
                          strMessage = strMessage & "after calling "
                          strMessage = strMessage & " RemoveGraphicalRepresentation = " & intNbGraphic & vbCr
                       End If 
                    End If
                 End If ' --- If (intNbGraphic > 1)
              End If '--- If ( Not ( objLGraphic Is Nothing ) ) Then

          End If '--- If ( Not ( objCompRefGraphic Is Nothing )...

       End If '--- If ( Not ( objLCompRefs Is Nothing ) ...

    End If '--- If ( Not ( objSchRoot Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub

```

' -----------------------------------------------------------------------------
' | Find a component symbol that has not been associated with a schematic
' | component from a document root.
' | Input: objSchRootArg:  the root of the document.
' | Returns: component symbol object.
' -----------------------------------------------------------------------------
```vbscript
Private Function GetComponentSymbol (objSchRootArg As SchematicRoot) As AnyObject
   Dim objSchLSymbols As SchListOfObjects
   If ( Not ( objSchRootArg Is Nothing ) ) Then
```
```vbscript
      Set objSchLSymbols = objSchRootArg.GetUnassociatedSymbols
      If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```vbscript
         Set GetComponentSymbol = objSchLSymbols.Item (1,"CATIASchGRR")
      End If
```
   End If
```vbscript
End Function

```

```vbscript
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Add/List graphical representations to a reference component. 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************

```vbscript
Sub CATMain(#)

```

    ' ------------------------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,sDocPath,"No Doc Path Defined"
    End If
```
    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```vbscript
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_Detail03.CATProduct")
```

```vbscript
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessage As String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchCompRefGraphic.CATScript" & vbCrLf

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
    Dim objLCompRefs As SchListOfObjects
    Dim objCompRefGraphic As SchCompGraphic

```

    If ( Not ( objSchRoot Is Nothing ) ) Then

       '-----------------------------------------------------------------------
       ' Find a list of reference component in the model
       '-----------------------------------------------------------------------
```vbscript
       Set objLCompRefs = objSchRoot.GetRefComponents

```

       If ( Not ( objLCompRefs Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Get a SchCompGraphic interface handle from a reference
          ' component
          '--------------------------------------------------------------------
```vbscript
          Set objCompRefGraphic = objLCompRefs.Item (1,"CATIASchCompGraphic")

          If ( Not ( objCompRefGraphic Is Nothing ) ) Then
```

```vbscript
              Dim objUnassocSymbol As AnyObject

```

              '----------------------------------------------------------------
              ' Find a symbol that is not associated with any reference in
              ' the model
              '----------------------------------------------------------------
```vbscript
              Set objUnassocSymbol = GetComponentSymbol (objSchRoot)

```

              If ( Not ( objUnassocSymbol Is Nothing ) ) Then

                '--------------------------------------------------------------
                '  Add the second graphical representation to the reference
                '  component using the symbol just found
                '--------------------------------------------------------------
                objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

                strMessage = strMessage & "Successfully add the second graphical representation" & vbCr

              End If

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
                objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

                strMessage = strMessage & "Successfully add the third graphical representation" & vbCr

              End If

```vbscript
              Dim intNbGraphic As Integer
              Dim objGRR As SchGRR
              Dim objLGraphic As SchListOfObjects
              Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
             
```
             
              If ( Not ( objLGraphic Is Nothing ) ) Then
                 intNbGraphic = objLGraphic.Count
                 strMessage = strMessage & "Number of graphical representations"
                 strMessage = strMessage & "= " & intNbGraphic & vbCr

```vbscript
                 Set objGRR = Nothing
                 If (intNbGraphic &gt; 1) Then
```
```vbscript
                    Set objGRR = objLGraphic.Item(intNbGraphic,"CATIASchGRR")
                    If ( Not (objGRR Is Nothing ) ) Then
```
                       objCompRefGraphic.RemoveGraphicalRepresentation objGRR
```vbscript
                       Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
                       If ( Not ( objLGraphic Is Nothing ) ) Then
```
                          intNbGraphic = objLGraphic.Count
                          strMessage = strMessage & "Number of graphical representations"
                          strMessage = strMessage & "after calling "
                          strMessage = strMessage & " RemoveGraphicalRepresentation = " & intNbGraphic & vbCr
                       End If 
                    End If
                 End If ' --- If (intNbGraphic &gt; 1)
              End If '--- If ( Not ( objLGraphic Is Nothing ) ) Then

          End If '--- If ( Not ( objCompRefGraphic Is Nothing )...

       End If '--- If ( Not ( objLCompRefs Is Nothing ) ...

    End If '--- If ( Not ( objSchRoot Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub

```

' -----------------------------------------------------------------------------
' | Find a component symbol that has not been associated with a schematic
' | component from a document root.
' | Input: objSchRootArg:  the root of the document.
' | Returns: component symbol object.
' -----------------------------------------------------------------------------
```vbscript
Private Function GetComponentSymbol (objSchRootArg As SchematicRoot) As AnyObject
   Dim objSchLSymbols As SchListOfObjects
   If ( Not ( objSchRootArg Is Nothing ) ) Then
```
```vbscript
      Set objSchLSymbols = objSchRootArg.GetUnassociatedSymbols
      If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```vbscript
         Set GetComponentSymbol = objSchLSymbols.Item (1,"CATIASchGRR")
      End If
```
   End If
```vbscript
End Function
```
```