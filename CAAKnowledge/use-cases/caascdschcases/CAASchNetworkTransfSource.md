---
title: "CAASchNetworkTransf.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: "["CATIAProduct", "CAAScdSchUseCases", "CATIA", "CATIASchGRR", "CATIASchCompGraphic", "CATIASchMovable", "CAASCH_Network01", "CAASchNetworkTransf", "CATIASchAppConnectable"]"
source_file: "Doc/online/CAAScdSchUseCases/CAASchNetworkTransfSource.htm"
converted: "2026-05-11T17:31:51.422498"
---
tags: ["CATIAProduct", "CAAScdSchUseCases", "CATIA", "CATIASchGRR", "CATIASchCompGraphic", "CATIASchMovable", "CAASCH_Network01", "CAASchNetworkTransf", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchNetworkTransfSource.htmmd"
converted: "2026-05-11T17:31:51.422498"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Scale and move component instances in a network.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
    '------------------------------------------------------------------------------
```cpp
    ' These variables are visible to private Sub and CATMain
    '------------------------------------------------------------------------------
```
```

```

```

```vbscript
```vbscript
    Dim objLGRR_g As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
    Dim objLCntbl_g As SchListOfObjects
    Dim objLSelected_g As SchListOfObjects

```
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
```
```

```

```

        strMessage = strMessage &  "sDocPath = " & sDocPath

```vbscript
```cpp
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
```
```vbscript
```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
        End If
```
```

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

                "online/CAAScdSchUseCases/samples/CAASCH_Network01.CATProduct")

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

          "Output traces from CAASchNetworkTransf.CATScript" & vbCrLf
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
        Dim objSchBaseFact As SchBaseFactory
        Dim objSchTempListFact As SchTempListFactory
        Dim objLNetWork As SchListOfObjects

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
           ' Get all the necessary factories.
           '-----------------------------------------------------------------------
```vbscript
           Set objSchBaseFact = objSchRoot.GetSchBaseFactory
           Set objSchTempListFact = objSchRoot.GetTemporaryListFactory
```
```

```

```

```vbscript
           If ( Not ( objSchBaseFact Is Nothing )  And _
```vbscript
                Not ( objSchTempListFact Is Nothing ) ) Then
```vbscript
```vbscript
              Set objLCntbl_g = objSchTempListFact.CreateListOfObjects
              Set objLGRR_g = objSchTempListFact.CreateListOfObjects
              Set objLSelected_g = objSchTempListFact.CreateListOfObjects

```
```

```

```

```vbscript
              If ( Not ( objLCntbl_g Is Nothing )  And _
```vbscript
                   Not ( objLGRR_g Is Nothing ) And _
                   Not ( objLSelected_g Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
                 '-----------------------------------------------------------------
                 ' The following "Sub" will populate objLCntbl_g and objLGRR_g and
                 ' objLSelected_g
                 '-----------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' The following "Sub" will populate objLCntbl_g and objLGRR_g and
' objLSelected_g
'-----------------------------------------------------------------
```

```

                 FindNetworkComponentInst objSchRoot

```vbscript
                 Set objLNetWork = objSchBaseFact.CreateNetwork (objLCntbl_g, _
                   objLGRR_g)
```

```

```vbscript
              End If
```vbscript
```vbscript
           End If '--- If ( Not ( objSchBaseFact Is Nothing )...
        End If '--- If ( Not ( objSchRoot Is Nothing )...

```

```

```

```vbscript
```vbscript
        If (  Not ( objLNetWork Is Nothing ) ) Then

```vbscript
           Dim objSchNet As SchMovable
```
```

```vbscript
```vbscript
```cpp
           Dim Db2Vector (2) As CATSafeArrayVariant
           Dim DbScaleFactor As Double
           Dim intNbNet As Integer

```
```

```

```

```vbscript
```vbscript
Dim DbScaleFactor As Double
```vbscript
```
```vbscript
Dim intNbNet As Integer
           Db2Vector(0) = 50.0
```
           Db2Vector(1) = 0.0
```

           DbScaleFactor = 1.5

```

           intNbNet = objLNetWork.Count
           strMessage = strMessage & "number of network found = " & intNbNet & vbCr

```vbscript
           If ( intNbNet > 0 ) Then
```vbscript
```vbscript
```cpp
              Set objSchNet = objLNetWork.Item (1,"CATIASchMovable")

```
```

```

```

```vbscript
              If ( Not ( objSchNet Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
                 '-----------------------------------------------------------------
                 '  Translate the first network by (50.0, 0.0)
                 '-----------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'-----------------------------------------------------------------
'  Translate the first network by (50.0, 0.0)
'-----------------------------------------------------------------
```

```

                 objSchNet.Translate Db2Vector
                 strMessage = strMessage & "Successfully translate network by " _
```

                   & Db2Vector(0) & "," & Db2Vector(1) & vbCr
```vbscript
```vbscript
```vbscript
                 '-----------------------------------------------------------------
                 '  Scale a component (the one with "_Scale" in its name) that is in
                 '  the network. Objects directly connected to this component will
                 '  be adjusted according until a route is reached. The latter will
                 '  be "reshaped".
                 '  objLSelected_g is set in FindNetworkComponentInst
                 '-----------------------------------------------------------------
```vbscript
                 Dim intSelected As Integer
```
```

```

                 intSelected = objLSelected_g.Count
                 If ( intSelected > 0 ) Then
```

```vbscript
```vbscript
Dim intSelected As Integer
```
```

intSelected = objLSelected_g.Count
```vbscript
If ( intSelected > 0 ) Then
                    objSchNet.ScaleSelectedObjects objLSelected_g, DbScaleFactor
                    strMessage = strMessage & "Successfully scale a connectable in the network by " _
```

                      & DbScaleFactor & vbCr
objSchNet.ScaleSelectedObjects objLSelected_g, DbScaleFactor
strMessage = strMessage & "Successfully scale a connectable in the network by " _
```vbscript
```vbscript
                 End If

```

```

```vbscript
              End If
```vbscript
```vbscript
           End If

```

```

```

```vbscript
```vbscript
        End If '--- If ( Not ( objLNetWork Is Nothing ) ...

```

```

```vbscript
End If '--- If ( Not ( objLNetWork Is Nothing ) ...
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
    ' | Find components and their images to be used to compute a network.
    ' | Input: objSchRootArg:  the root of the document.
    ' | Returns: objLCntbl_g: a list of component instance objects
    ' |          objLGRR_g: a list of component instance image objects
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Sub FindNetworkComponentInst (objSchRootArg As SchematicRoot)
```
```

```vbscript
       If ( objLCntbl_g Is Nothing ) Then Exit Sub
```vbscript
```vbscript
       If ( objLGRR_g Is Nothing ) Then Exit Sub

```vbscript
       Dim objLCompInst As SchListOfObjects
       Dim intNbComp As Integer

```
```

```

```

```vbscript
       If ( Not ( objSchRootArg Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
          Set objLCompInst = objSchRootArg.GetComponents
          If ( Not ( objLCompInst Is Nothing ) ) Then
```
```

```

             intNbComp = objLCompInst.Count
          End If
```vbscript
```vbscript
       End If

```vbscript
       Dim intIndex As Integer
       Dim intNbFlow As Integer
       Dim objCntbl As SchConnectable
       Dim objGRR As SchGRR
       Dim objPrd As Product
       Dim strInstName As String
       Dim intFound As Integer
       Dim intNbFound As Integer
       Dim intSelected As Integer

```
```

```

```

```vbscript
       If (Not ( objLCompInst Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
          '------------------------------------------------------------------------
          '  Loop through the members in the list and find components that
          '  have "network" as part of the product instance names
          '------------------------------------------------------------------------
```

```

          intNbFound = 0
```

```vbscript
```vbscript
          For intIndex = 1 To intNbComp

```

```

```vbscript
For intIndex = 1 To intNbComp
            strInstName = ""
            intFound = 0

```

```vbscript
```vbscript
```cpp
            Set objCntbl = objLCompInst.Item (intIndex,"CATIASchAppConnectable")

```
```

```

```vbscript
```vbscript
            If ( Not ( objCntbl Is Nothing ) ) Then

```vbscript
               Set objPrd = objSchRootArg.GetInterface ( _
```
```

```

                 "CATIAProduct", objCntbl)

```vbscript
               If ( Not ( objPrd Is Nothing ) ) Then
                  strInstName = objPrd.Name
                  intFound  = Instr (1, strInstName, "_network_scale", 1)
```vbscript
```vbscript
               End If

```

```

```

```vbscript
               If ( intFound > 0 ) Then
```vbscript
```vbscript
```vbscript
                 Dim ObjSchCompGraph As SchCompGraphic
                 Set objSchCompGraph = objSchRootArg.GetInterface ( _
```
```

```

```

                   "CATIASchCompGraphic",objCntbl)
```vbscript
If ( intFound > 0 ) Then
```vbscript
```vbscript
```vbscript
Dim ObjSchCompGraph As SchCompGraphic
Set objSchCompGraph = objSchRootArg.GetInterface ( _
                 Set objGRR = GetComponentImage (objSchCompGraph)

```
```

```

```

```vbscript
                 If ( ( Not ObjGRR Is Nothing ) ) Then
                    objLCntbl_g.Append objCntbl
                    objLGRR_g.Append objGRR
                    intSelected = objLSelected_g.Count
                    If (intSelected = 0) Then objLSelected_g.Append objCntbl
                    intNbFound = intNbFound + 1
```vbscript
                 End If

```

```

```vbscript
```vbscript
               End If

```

```

```vbscript
```vbscript
            End If '--- If ( Not ( objCntbl Is Nothing ) ...

```

```

```vbscript
          Next

```

```vbscript
```vbscript
       End If '--- If (Not ( objLCompInst Is Nothing ) ...
```vbscript
    End Sub
```
```

```

```vbscript
```vbscript
```cpp
    ' -----------------------------------------------------------------------------
    ' | Find the first symbol used for the input schematic component.
    ' | Input: objSchCompGraph:  the schematic component
    ' |        (a CATIASchCompGraphic interface handle).
    ' | Returns: the component image (the symbol instance)
    ' -----------------------------------------------------------------------------
```

```

```vbscript
```vbscript
    Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRR
       Dim objSchLSymbols As SchListOfObjects
```
```

```vbscript
```vbscript
       If ( Not ( objSchCompGraphArg Is Nothing ) ) Then
```vbscript
          Set objSchLSymbols = objSchCompGraphArg.ListGraphicalImages
          If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```cpp
             Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRR")
          End If
```
       End If
```

```

```vbscript
    End Function
```
```
