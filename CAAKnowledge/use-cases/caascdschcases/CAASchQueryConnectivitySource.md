---
```vbscript
title: "CAASchQueryConnectivity.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_CompRoute01", "CATIAProduct", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIA", "CATIASchCntrLocation", "CATIASchGRR", "CAASchQueryConnectivity", "CATIASchCompGraphic", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryConnectivitySource.htmmd"
converted: "2026-05-11T17:31:51.471879"
```

---
tags: ["CAASCH_CompRoute01", "CATIAProduct", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIA", "CATIASchCntrLocation", "CATIASchGRR", "CAASchQueryConnectivity", "CATIASchCompGraphic", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryConnectivitySource.htmmd"
converted: "2026-05-11T17:31:51.471879"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Query the connectivity of components and routes in a network.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
    '--- strMessage_g is a global variable visible to all private Sub/Function
```

```

```

```vbscript
```vbscript
```vbscript
    Dim strMessage_g As String

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
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
        End If
```
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

```
```

```

```

```vbscript
```vbscript
Dim objSchDoc As Document
```vbscript
```
```vbscript
Set objSchDoc = CATIA.Documents.Open(sFilePath)
```
```

        strMessage_g = _
```

          "--------------------------------------------------------------------" & vbCr
strMessage_g = _
        strMessage_g = strMessage_g & _

          "Output traces from CAASchQueryConnectivity.CATScript" & vbCrLf
strMessage_g = _
strMessage_g = strMessage_g & _
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
        Dim objSchLRoutes As SchListOfObjects

```
```

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' |  Get a list of all component instances and
        ' |  a list of all route instances in the model.
        ' -------------------------------------------------------------------------
```

```

```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
           Set objSchLComps = objSchRoot.GetComponents
           Set objSchLRoutes = objSchRoot.GetRoutes
        End If
```

```vbscript
        Dim intNb As Integer
        Dim intNbRoute As Integer
        Dim intIndex As Integer
        Dim objPrd As Product
        Dim strName As String
        Dim objAppCntbl As SchAppConnectable
        Dim objLCntblOther As SchListOfObjects
        Dim objLCntrThis As SchListOfObjects
        Dim objLCntrOther As SchListOfObjects
        Dim objSchTempListFact As SchTempListFactory
        Dim objLFilter As SchListOfBSTRs
```
```

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' |  For each component instance in the list, find connected objects
        ' -------------------------------------------------------------------------
        If ( Not ( objSchLComps Is Nothing ) And _
```

```

```

```vbscript
```vbscript
```vbscript
' |  For each component instance in the list, find connected objects
' -------------------------------------------------------------------------
If ( Not ( objSchLComps Is Nothing ) And _
```

             Not ( objSchRoot Is Nothing ) ) Then

```

```

Not ( objSchRoot Is Nothing ) ) Then
           intNb = objSchLComps.Count
           strMessage_g = strMessage_g &  "Number of schematic component instances = " & intNb & vbCrLf

```vbscript
           If (intNb > 0) Then
              strMessage_g = strMessage_g &  "-----------Component Connectivity report ------------------- " _
```

                & vbCrLf

```vbscript
              For intIndex = 1 To intNb
```vbscript
```vbscript
                Set objPrd = Nothing
```
```

                strName = ""
```vbscript
                Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
```vbscript
```
                If ( Not ( objPrd Is Nothing ) ) Then
```

                   strName = objPrd.Name
                   strMessage_g = strMessage_g &  " member " & intIndex & _
```

                     "= " & strName & vbCr
```vbscript
```vbscript
Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
```
```

If ( Not ( objPrd Is Nothing ) ) Then
strName = objPrd.Name
strMessage_g = strMessage_g &  " member " & intIndex & _
```vbscript
```vbscript
                End If

```vbscript
                Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

```
```

```

```vbscript
```vbscript
                If ( Not ( objAppCntbl Is Nothing ) ) Then

```

```

```vbscript
```vbscript
```vbscript
                   '---------------------------------------------------------------
                   '  AppListConnectables output 3 lists of objects.
                   '
                   '  If a component A is connected to another component B on
                   '  one side and to a route C on the other side, then the
                   '  output lists of objects will contain the following members.
                   '
                   '         objLCntblOther    objLCntrThis    objLCntrOther
                   '         --------------    --------------  ----------------
                   '           B               connector on A   connector on B
                   '           C               connector on A   connector on C
                   '---------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
                   Set objLFilter = Nothing

```
```

```

```vbscript
```vbscript
Set objLFilter = Nothing
                   objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
```
                     objLCntrThis, objLCntrOther

```

                   GenerateALine objSchRoot, objLCntblOther, objLCntrOther

```vbscript
```vbscript
                   Set objLCntblOther = Nothing
```vbscript
```
```vbscript
```vbscript
                   Set objLCntrThis = Nothing
                   Set objLCntrOther = Nothing

```
```

```

```

```vbscript
```vbscript
                End If

```

```

             Next '--- For intIndex = 1 To intNb

```vbscript
```vbscript
           End If ' --- If (intNb > 0) Then

```

```

```vbscript
```vbscript
        End If '--- If ( Not ( objSchLComps Is Nothing ) And ...

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' |  For each route instance in the list, find connected objects
        ' -------------------------------------------------------------------------
```

```

```

```vbscript
        If ( Not ( objSchLRoutes Is Nothing ) And _
```vbscript
             Not ( objSchRoot Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchLRoutes Is Nothing ) And _
```

Not ( objSchRoot Is Nothing ) ) Then
           intNb = objSchLRoutes.Count
           strMessage_g = strMessage_g &  "Number of schematic route instances = " & intNb & vbCrLf

```vbscript
           If (intNb > 0) Then
              strMessage_g = strMessage_g &  "---------------- Route Connectivity report ------------------- " _
```

                & vbCrLf

```vbscript
              For intIndex = 1 To intNb
```vbscript
```vbscript
                Set objPrd = Nothing
```
```

                strName = ""
```vbscript
                Set objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")
```vbscript
```
                If ( Not ( objPrd Is Nothing ) ) Then
```

                   strName = objPrd.Name
                   strMessage_g = strMessage_g &  " member " & intIndex & _
```

                     "= " & strName & vbCr
```vbscript
```vbscript
Set objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")
```
```

If ( Not ( objPrd Is Nothing ) ) Then
strName = objPrd.Name
strMessage_g = strMessage_g &  " member " & intIndex & _
```vbscript
```vbscript
                End If

```vbscript
                Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

```
```

```

```vbscript
```vbscript
                If ( Not ( objAppCntbl Is Nothing ) ) Then

```vbscript
                   Set objLFilter = Nothing

```
```

```

```vbscript
```vbscript
Set objLFilter = Nothing
                   objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
```
                     objLCntrThis, objLCntrOther

```

                   GenerateALine objSchRoot, objLCntblOther, objLCntrOther

```vbscript
```vbscript
                   Set objLCntblOther = Nothing
```vbscript
```
```vbscript
```vbscript
                   Set objLCntrThis = Nothing
                   Set objLCntrOther = Nothing

```
```

```

```

```vbscript
```vbscript
                End If

```

```

             Next '--- For intIndex = 1 To intNb

```vbscript
```vbscript
           End If ' --- If (intNb > 0) Then

```

```

```vbscript
```vbscript
        End If '--- If ( Not ( objSchLComps Is Nothing ) And ...

```

```

        strMessage_g = strMessage_g & _
          "--------------------------------------------------------------------" & vbCr
```vbscript
        MsgBox strMessage_g

```vbscript
```
```vbscript
    End Sub

End Sub
    Private Sub GenerateALine (objSchRootArg As SchematicRoot, _
```
```

      objLCntblArg As SchListOfObjects, objLCntrArg As SchListOfObjects)

```vbscript
```vbscript
      Dim intNbCntbl As Integer
```vbscript
```
```vbscript
```vbscript
      Dim intNbCntr As Integer
      Dim intIndex As Integer
      Dim intNbCoord As Integer
      Dim dbX As Double
      Dim dbY As Double
      Dim objPrd As Product
      Dim objCntr As SchCntrLocation
      Dim objCntbl As SchAppConnectable
      Dim objGRR As SchGRR
      Dim objLDb As SchListOfDoubles
      Dim strName As String

```
```

```

```

```vbscript
      If ( Not ( objLCntblArg Is Nothing ) And _
```vbscript
           Not ( objLCntrArg Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objLCntblArg Is Nothing ) And _
```

Not ( objLCntrArg Is Nothing ) ) Then
         intNbCntbl = objLCntblArg.Count
         intNbCntr = objLCntrArg.Count

```vbscript
```vbscript
         If ( intNbCntbl = intNbCntr ) Then

```

```

```vbscript
            For intIndex = 1 To intNbCntbl
```vbscript
```vbscript
              Set objPrd = Nothing
```
```

              strName = ""

```vbscript
```vbscript
              Set objPrd = objLCntblArg.Item (intIndex,"CATIAProduct")

              Set objCntbl = objSchRootArg.GetInterface ("CATIASchAppConnectable",objPrd)
```
```

```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              '  Report the name of the object connected
              '--------------------------------------------------------------------
              If ( Not ( objPrd Is Nothing ) ) Then
```

```

                 strName = objPrd.Name
                 strMessage_g = strMessage_g &  "    connected to  " & intIndex  _
```

                    & strName
```vbscript
strName = objPrd.Name
strMessage_g = strMessage_g &  "    connected to  " & intIndex  _
              End If
```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              '  Report the location of the connection through the connector
              '  position
              '--------------------------------------------------------------------
```vbscript
              Set objGRR = Nothing
              Set objGRR = GetImage (objSchRootArg, objCntbl)
```
```

```

```

```vbscript
```vbscript
              If ( Not ( objGRR Is Nothing ) ) Then

```vbscript
                 Set objCntr = objLCntrArg.Item (intIndex,"CATIASchCntrLocation")

```
```

```

```vbscript
```vbscript
                 If ( Not ( objCntr Is Nothing ) ) Then

```vbscript
                    Set objLDb = Nothing
```
```

                    objCntr.GetPosition objGRR, objLDb

```

```vbscript
                    If ( Not ( objLDb Is Nothing ) ) Then
                       intNbCoord = objLDb.Count
                       If ( intNbCoord > 1 ) Then
```vbscript
```vbscript
                          dbX = objLDb.Item(1)
                          dbY = objLDb.Item(2)
```

```

                          strMessage_g = strMessage_g &  " at " & dbX & "," & dbY & vbCr
                       End If
```vbscript
```vbscript
                    End If

```

```

```

```vbscript
```vbscript
                 End If

```

```

```vbscript
```vbscript
              End If '--- If ( Not ( objGRR Is Nothing ) ) Then ...

```

```

            Next '--- For intIndex = 1 To intNb

```vbscript
```vbscript
         End If '--- If ( intNbCntbl = intNbCntr ) Then ...

```

```

```vbscript
```vbscript
      End If '--- If ( Not ( objLCntblArg Is Nothing ) And ...

```

```

```vbscript
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
    Private Function GetImage (objSchRootArg As SchematicRoot, _
```
```

```vbscript
```vbscript
```vbscript
' | Returns: the component image (the symbol instance)
' -----------------------------------------------------------------------------
```

```

```vbscript
Private Function GetImage (objSchRootArg As SchematicRoot, _
      objSchCntblArg As SchAppConnectable) As SchGRR
```

```vbscript
      Dim objSchLImages As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
      Dim objSchCompGraph As SchCompGraphic
      Dim objSchRouteGraph As SchRouteGraphic
      Dim ErrorCode As Integer

      Set objSchCompGraph = Nothing
      Set objSchRouteGraph = Nothing

```
```

```

```

```vbscript
      If ( Not ( objSchRootArg Is Nothing ) And _
```vbscript
           Not ( objSchCntblArg Is Nothing ) ) Then

```

```

```vbscript
```vbscript
```vbscript
         '-------------------------------------------------------------------------
         ' Input objSchCntblArg could be a route or a component.  If
         ' objSchCntblArg is a component, we expect
```vbscript
         ' Set objSchRouteGraph = objSchRootArg.GetInterface ( _
         '  "CATIASchRouteGraphic",objSchCntblArg) to fail
```
         ' Error handling is to call GetInterface again with "CATIASchCompGraphic"
         ' as input argument.
         '-------------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' Error handling is to call GetInterface again with "CATIASchCompGraphic"
' as input argument.
'-------------------------------------------------------------------------
```

```

```vbscript
         On Error Resume Next

```
```

```vbscript
```vbscript
         Set objSchRouteGraph = objSchRootArg.GetInterface ( _
```
```

           "CATIASchRouteGraphic",objSchCntblArg)

```vbscript
```vbscript
Set objSchRouteGraph = objSchRootArg.GetInterface ( _
         ErrorCode = Err.Number
```
         If (ErrorCode <> 0) Then
```vbscript
            On Error Goto 0
```vbscript
```
            If ( objSchRouteGraph Is Nothing ) Then

```vbscript
               Set objSchCompGraph = objSchRootArg.GetInterface ( _
```
```

```

                 "CATIASchCompGraphic",objSchCntblArg)

```vbscript
            End If
```vbscript
         End If
```

```vbscript
         On Error Goto 0

```

```

```vbscript
```vbscript
      End If

```

```

```vbscript
      If ( Not ( objSchCompGraph Is Nothing ) ) Then
```vbscript
```vbscript
          Set objSchLImages = objSchCompGraph.ListGraphicalImages
```
```

      Else
         If ( Not ( objSchRouteGraph Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
           Set objSchLImages = objSchRouteGraph.ListGraphicalPrimitives
         End If
```
      End If

```

```

```

```vbscript
      If ( Not ( objSchLImages Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
         Set GetImage = objSchLImages.Item (1,"CATIASchGRR")
      End If
```

```

```

```

```vbscript
```vbscript
    End Function

```
```
