---
```vbscript
title: "CAASchQueryCompRoute.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_CompRoute01", "CATIAProduct", "CAASchQueryCompRoute", "CATIASchGRRRoute", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIASchGRRComp", "CATIA", "CATIASchCntrLocation", "CATIASchGRR", "CATIASchCompGraphic", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryCompRouteSource.htmmd"
converted: "2026-05-11T17:31:51.455417"
```

---
tags: ["CAASCH_CompRoute01", "CATIAProduct", "CAASchQueryCompRoute", "CATIASchGRRRoute", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIASchGRRComp", "CATIA", "CATIASchCntrLocation", "CATIASchGRR", "CATIASchCompGraphic", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryCompRouteSource.htmmd"
converted: "2026-05-11T17:31:51.455417"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Provides a list of component and route from a schematic
    '                 document. List all the defining points of the component
    '                 route instances. For each component instance, also lists
    '                 the defining points of its connectors.
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

                "online/CAAScdSchUseCases/samples/CAASCH_CompRoute01.CATProduct")

```vbscript
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```vbscript
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

          "Output traces from CAASchQueryCompRoute.CATScript" & vbCrLf
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
        Dim objSchLComps As SchListOfObjects
        Dim objSchLCompRefs As SchListOfObjects
        Dim objSchLRoutes As SchListOfObjects
        Dim objSchSession As SchSession
        Dim objCurDoc As Document
        Dim strCurDocName As String

```
```

```

```

```vbscript
```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then

```vbscript
           Set objSchSession = objSchRoot.GetSchematicSession
```
```

```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           '| Query the name of the current document
           '-----------------------------------------------------------------------
           If ( Not ( objSchSession Is Nothing ) ) Then
```vbscript
              Set objCurDoc = objSchSession.GetCurrentDocument
              If ( Not ( objCurDoc Is Nothing ) ) Then
```
```

```

                 strCurDocName = objCurDoc.Name
                 strMessage = strMessage &  "Current Document = " & strCurDocName & vbCr
              End If
```vbscript
```vbscript
           End If
        End If

```vbscript
        Dim intNbComp As Integer
        Dim intNbRoute As Integer
        Dim intIndex As Integer
        Dim objPrd As Product
        Dim strName As String
        ' -------------------------------------------------------------------------
```
        ' |  List schematic component references in the model
        ' -------------------------------------------------------------------------

```vbscript
        Set objSchLCompRefs = objSchRoot.GetRefComponents
```
```

```

```

```vbscript
        If ( Not ( objSchLCompRefs Is Nothing ) ) Then
           intNbComp = objSchLCompRefs.Count
           strMessage = strMessage &  "Number of schematic component REFERENCES = " _
```

             & intNbComp & vbCr
```vbscript
If ( Not ( objSchLCompRefs Is Nothing ) ) Then
```

intNbComp = objSchLCompRefs.Count
strMessage = strMessage &  "Number of schematic component REFERENCES = " _
```vbscript
           If (intNbComp > 0) Then
```vbscript
```vbscript
             For intIndex = 1 To intNbComp
```vbscript
                Set objPrd = Nothing
```
```

```

                strName = ""
```vbscript
                Set objPrd = objSchLCompRefs.Item (intIndex,"CATIAProduct")
```vbscript
```
                If ( Not ( objPrd Is Nothing ) ) Then
```

                   strName = objPrd.Name
                   strMessage = strMessage &  "  member " & intIndex _
```

                     & "= " & strName & vbCr
```vbscript
```vbscript
Set objPrd = objSchLCompRefs.Item (intIndex,"CATIAProduct")
```
```

If ( Not ( objPrd Is Nothing ) ) Then
strName = objPrd.Name
strMessage = strMessage &  "  member " & intIndex _
```vbscript
                End If
```vbscript
```vbscript
             Next
           End If
        End If
```

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' |  List schematic component instances in the model
        ' -------------------------------------------------------------------------

```vbscript
        Set objSchLComps = objSchRoot.GetComponents

        Dim objGRRCompInst As SchGRRComp
        Dim objCompGraphInst As SchCompGraphic
        Dim objCntbl As SchAppConnectable
        Dim objLCntrs As SchListOfObjects
        Dim objSchLDbComp As SchListOfDoubles
        Dim objLFilter As SchListOfBSTRs
        Dim db6Matrix(6) As Double
        Dim intNb As Integer

        Set objLFilter = Nothing
```
```

```

```

```vbscript
        If ( Not ( objSchLComps Is Nothing ) ) Then
           intNbComp = objSchLComps.Count
           strMessage = strMessage &  "Number of schematic component INSTANCES = " _
```

             & intNbComp & vbCr

```vbscript
```vbscript
           If (intNbComp > 0) Then

```vbscript
             Dim iCntr As Integer
```
```

```vbscript
```vbscript
```vbscript
             Dim intNbCntr As Integer
             Dim objLDbCntr As SchListOfDoubles
             Dim objCntr As SchCntrLocation
             Dim objGRR As SchGRR
             Dim intNCoord As Integer
             Dim dbCntrX As Double
             Dim dbCntrY As Double

```
```

```

```

```vbscript
```vbscript
             For intIndex = 1 To intNbComp

```vbscript
                Set objPrd = Nothing
```
```

```vbscript
```vbscript
```vbscript
                Set objCompGraphInst = Nothing
                Set objGRRCompInst = Nothing
                Set objCntbl = Nothing
                Set objLCntrs = Nothing
                Set objGRR = Nothing
                Set objSchLDbComp = Nothing

```
```

```

```

```vbscript
```vbscript
Set objGRR = Nothing
```vbscript
```
```vbscript
Set objSchLDbComp = Nothing
```
```

                strName = ""
```

```vbscript
```vbscript
                Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
```vbscript
```
                If ( Not ( objPrd Is Nothing ) ) Then
```

                   strName = objPrd.Name
                   strMessage = strMessage &  "  member " & intIndex _
```

                     & "= " & strName & vbCr
```vbscript
```vbscript
Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
```
```

If ( Not ( objPrd Is Nothing ) ) Then
strName = objPrd.Name
strMessage = strMessage &  "  member " & intIndex _
```vbscript
```vbscript
                   Set objCompGraphInst = objSchRoot.GetInterface  ("CATIASchCompGraphic", _
                     objPrd)
```
                End If
```

```vbscript
```vbscript
```vbscript
                '------------------------------------------------------------------
                ' Get the orientation matrix of the symbol representing the
                ' component instance.
                '------------------------------------------------------------------
                If ( Not ( objCompGraphInst Is Nothing ) ) Then
```vbscript
                   Set objGRRCompInst = GetComponentImage (objCompGraphInst)
                   If ( Not ( objGRRCompInst Is Nothing ) ) Then
```
```

```

```

```vbscript
If ( Not ( objCompGraphInst Is Nothing ) ) Then
```vbscript
```vbscript
Set objGRRCompInst = GetComponentImage (objCompGraphInst)
```
```

```

If ( Not ( objGRRCompInst Is Nothing ) ) Then
                      objGRRCompInst.GetTransformation2D objSchLDbComp

```vbscript
```vbscript
                      If ( Not ( objSchLDbComp Is Nothing ) ) Then

```

```

                         intNb = objSchLDbComp.Count

```vbscript
```vbscript
                         If ( intNb > 5 ) Then

```

```

```vbscript
If ( intNb > 5 ) Then
```vbscript
                            db6Matrix(0) = objSchLDbComp.Item(1)
                            db6Matrix(1) = objSchLDbComp.Item(2)
                            db6Matrix(2) = objSchLDbComp.Item(3)
                            db6Matrix(3) = objSchLDbComp.Item(4)
                            db6Matrix(4) = objSchLDbComp.Item(5)
                            db6Matrix(5) = objSchLDbComp.Item(6)

```

```

                            strMessage = strMessage & "---- rotation matrix = " & _

                              "(" & db6Matrix(0) & "," & db6Matrix(1) & "," _
                              & db6Matrix(2) & "," & db6Matrix(3) & ")" & vbCr
```vbscript
db6Matrix(5) = objSchLDbComp.Item(6)
strMessage = strMessage & "---- rotation matrix = " & _
                            strMessage = strMessage & "---- instance origin = " & _
```

                              "(" & db6Matrix(4) & "," & db6Matrix(5) & ")" & vbCr

```vbscript
```vbscript
                         End If

```

```

```vbscript
                      End If
```vbscript
```vbscript
                   End If '--- If ( Not ( objGRRComp Is Nothing )...

```vbscript
                   Set objCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",_
```
```

```

                     objCompGraphInst)
```vbscript
```vbscript
                   Set objGRR = objSchRoot.GetInterface ("CATIASchGRR", objGRRCompInst)

```
```

```

```vbscript
                End If '---if ( Not ( objCompGraphInst Is Nothing ) ...
```

```vbscript
```vbscript
```vbscript
                '------------------------------------------------------------------
                ' Get the connector locations of all component instances
                '------------------------------------------------------------------
                If ( Not ( objCntbl Is Nothing ) And  Not ( objGRR Is Nothing ) ) Then
```vbscript
                   Set objLCntrs = objCntbl.AppListConnectors (objLFilter)
                   If ( Not ( objLCntrs Is Nothing ) ) Then
```
```

```

                      intNbCntr = objLCntrs.Count
                      If ( intNbCntr > 0) Then
```vbscript
```vbscript
                         For iCntr = 1 To intNbCntr
```vbscript
                            Set objLDbCntr = Nothing
                            Set objCntr = Nothing
                            Set objCntr = objLCntrs.Item (iCntr,"CATIASchCntrLocation")
                            If ( Not ( objCntr Is Nothing )) Then
```
```

```

```

```vbscript
```vbscript
Set objCntr = Nothing
```vbscript
```
```vbscript
Set objCntr = objLCntrs.Item (iCntr,"CATIASchCntrLocation")
```
```

```

If ( Not ( objCntr Is Nothing )) Then
                               objCntr.GetPosition objGRR, objLDbCntr
```vbscript
                               If ( Not ( objLDbCntr Is Nothing ) ) Then
                                  intNCoord = objLDbCntr.Count
                                  If ( intNCoord > 1 ) Then
```vbscript
```vbscript
                                     dbCntrX = objLDbCntr.Item(1)
                                     dbCntrY = objLDbCntr.Item(2)
```

```

                                     strMessage = strMessage & "---- ... connector " & iCntr
                                     strMessage = strMessage & " position = " & dbCntrX & _
```

                                       "," & dbCntrY & vbCr
```vbscript
dbCntrX = objLDbCntr.Item(1)
```vbscript
dbCntrY = objLDbCntr.Item(2)
```

strMessage = strMessage & "---- ... connector " & iCntr
strMessage = strMessage & " position = " & dbCntrX & _
                                  End If
```vbscript
```vbscript
                               End If
                            End If '---If ( Not ( objCntr Is Nothing )) ...
```

```

                         Next '--- For iCntr ...
                      End If '--- If ( NbCntr > 0 ...
```vbscript
```vbscript
                   End If '--- Not ( objLCntr Is Nothing ...
                End If '---if ( Not ( objCntbl Is Nothing )) ...

```

```

```

             Next  '--- For intIndex = 1
           End If '--- If (intNbComp > 0) ...
```vbscript
```vbscript
        End If '--- If ( Not ( objSchLComps Is Nothing ) ...

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' |  List schematic route instances
        ' -------------------------------------------------------------------------

```vbscript
        Set objSchLRoutes = objSchRoot.GetRoutes

        Dim objGRRRoute As SchGRRRoute
        Dim objSchRouteGraph As SchRouteGraphic
        Dim objSchLDbRoute As SchListOfDoubles
        Dim intNbOut As Integer
```
```

```

```

```vbscript
        If ( Not ( objSchLRoutes Is Nothing ) ) Then
           intNbRoute = objSchLRoutes.Count
           strMessage = strMessage &  "Number of schematic route instances = " & _
             intNbRoute & vbCr
```vbscript
           If (intNbRoute > 0) Then

```

```

```vbscript
             For intIndex = 1 To intNbRoute
```vbscript
```vbscript
```vbscript
                Set objPrd = Nothing
                Set objGRRRoute = Nothing
                Set objSchRouteGraph = Nothing

```
```

```

```

```vbscript
```vbscript
Set objGRRRoute = Nothing
```vbscript
```
```vbscript
Set objSchRouteGraph = Nothing
```
```

                strName = ""
```

```vbscript
```vbscript
                Set objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")
```vbscript
```
                If ( Not ( objPrd Is Nothing ) ) Then
```

```

```vbscript
```vbscript
                   'strName = objPrd.Name
```

                   strName = objPrd.PartNumber
                   strMessage = strMessage &  "  member " & _
```

```vbscript
```vbscript
'strName = objPrd.Name
```

strName = objPrd.PartNumber
strMessage = strMessage &  "  member " & _
                     intIndex & "= " & strName & vbCr
```vbscript
                   Set objSchRouteGraph = objSchRoot.GetInterface  ("CATIASchRouteGraphic", _
                     objPrd)
```
                End If
```

```vbscript
```vbscript
```vbscript
                '------------------------------------------------------------------
                ' Get the route points x-y coordinates of the route.
                '------------------------------------------------------------------
                If ( Not ( objSchRouteGraph Is Nothing ) ) Then

```vbscript
                   Set objGRRRoute = GetRoutePrimitives (objSchRouteGraph,objSchRoot)
```
```

```

```

```vbscript
                   If ( Not ( objGRRRoute Is Nothing ) ) Then
```vbscript
```vbscript
                      Set objSchLDbRoute = Nothing
```
```

                      objGRRRoute.GetPath objSchLDbRoute

```

```vbscript
                      If ( Not ( objSchLDbRoute Is Nothing ) And _
                           intNbOut > 3 ) Then

```

```vbscript
If ( Not ( objSchLDbRoute Is Nothing ) And _
```

intNbOut > 3 ) Then
                         intNb = objSchLDbRoute.Count

```vbscript
```vbscript
                         Dim iIndex As Integer
```vbscript
```
```vbscript
```vbscript
                         Dim jIndex As integer
                         Dim dbX As Double
                         Dim dbY As Double
                         Dim intNbPoint As Integer
```
```

```

                         intNbPoint = intNbOut/2

```

```vbscript
                         If ( (intNbOut = intNb ) And  (intNbPoint > 1) ) Then
                            strMessage = strMessage & "---- route points = ["
                            For iIndex = 1 To intNbPoint
```vbscript
```vbscript
                               jIndex = ((iIndex-1) * 2) + 1
                               dbX = objSchLDbRoute.Item(jIndex)
                               dbY = objSchLDbRoute.Item(jIndex+1)
                               strMessage = strMessage & "(" & dbX & "," & dbY & ")"
                            Next
```

```

                            strMessage = strMessage & "]" & vbCr
```vbscript
                         End If

```

```

```vbscript
                      End If '--- If ( Not ( objSchLDbRoute Is Nothing ...
```vbscript
```vbscript
                   End If '--- If ( Not ( objGRRRoute Is Nothing )...
                End If '---if ( Not ( objSchRouteGraph Is Nothing ) ...

```

```

```

             Next '--- For intIndex = 1 To intNbRoute
           End If '--- If (intNbRoute > 0) ...
```vbscript
```vbscript
        End If '--- If ( Not ( objSchLRoutes Is Nothing ) ...

```

```

```vbscript
End If '--- If (intNbRoute > 0) ...
```

End If '--- If ( Not ( objSchLRoutes Is Nothing ) ...
        strMessage = strMessage & _

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
    ' | Find the first symbol used for the input schematic component.
    ' | Input: objSchCompGraph:  the schematic component
    ' |        (a CATIASchCompGraphic interface handle).
    ' | Returns: the component image (the symbol instance)
    ' -----------------------------------------------------------------------------
```

```

```vbscript
```vbscript
    Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRRComp
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
```vbscript
             Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRRComp")
          End If
```
       End If
```

```

```vbscript
    End Function
```
```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find the first graphical primitives of an input route.
    ' | Input: objSchRouteGraph: the schematic route
    ' |        (a CATIASchRouteGraphic interface handle).
    ' |        objSchRootGraph: the schematic root
    ' | Returns: the route graphic primitives
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic, _
```
```

```vbscript
```vbscript
```vbscript
' | Returns: the route graphic primitives
' -----------------------------------------------------------------------------
```

```

```vbscript
Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic, _
      objSchRootArg As SchematicRoot) As SchGRRRoute
```
```

```vbscript
```vbscript
       Dim objSchLGRR As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
       Dim objSchGRR As SchGRR
       If ( Not ( objSchRouteGraphArg Is Nothing ) And _
```
```

            Not ( objSchRootArg Is Nothing ) ) Then
```vbscript
```vbscript
          Set objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives
          If ( Not ( objSchLGRR Is Nothing ) ) Then
```
```vbscript
             Set objSchGRR = objSchLGRR.Item (1,"CATIASchGRR")
             If ( Not ( objSchGRR Is Nothing ) ) Then
```
```vbscript
                Set GetRoutePrimitives = objSchRootArg.GetInterface ("CATIASchGRRRoute", _
```
```

```

                  objSchGRR)
             End If
```vbscript
```vbscript
          End If
       End If
```

```

```vbscript
```vbscript
    End Function

```
```

```
