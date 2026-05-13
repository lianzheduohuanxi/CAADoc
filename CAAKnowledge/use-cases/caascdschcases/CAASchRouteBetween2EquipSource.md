---
```vbscript
title: "CAASchRouteBetween2Equip.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIASchAppConnectable", "CATIAProduct", "CAASchRouteBetween2Equip", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIASchAppConnector", "CATIASchGRRComp", "CATIA", "CATIASchListOfBSTRs", "CAASCHEDU_SamplePID", "CAASCHEDUConnector", "CATIASchGRR", "CAASCHEDUFuncString", "CATIASchCompatible", "CAASCH_RouteBetween2Equip", "CATIASchCompGraphic", "CATIASchCntrLocation"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchRouteBetween2EquipSource.htmmd"
converted: "2026-05-11T17:31:51.497816"
```

---
tags: ["CATIASchAppConnectable", "CATIAProduct", "CAASchRouteBetween2Equip", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIASchAppConnector", "CATIASchGRRComp", "CATIA", "CATIASchListOfBSTRs", "CAASCHEDU_SamplePID", "CAASCHEDUConnector", "CATIASchGRR", "CAASCHEDUFuncString", "CATIASchCompatible", "CAASCH_RouteBetween2Equip", "CATIASchCompGraphic", "CATIASchCntrLocation"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchRouteBetween2EquipSource.htmmd"
converted: "2026-05-11T17:31:51.497816"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Route a piping line function between two equipments.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
    '------------------------------------------------------------------------------
```vbscript
    ' These variables are visible to private Sub and CATMain
    '------------------------------------------------------------------------------
```
```

```

```

```vbscript
```vbscript
    Dim objLGRRComp_g As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
    Dim objLCompat_g As SchListOfObjects
    Dim strMessage_g As String

```
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

                "online/CAAScdSchUseCases/samples/CAASCH_RouteBetween2Equip.CATProduct")

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

          "Output traces from CAASchRouteBetween2Equip.CATScript" & vbCrLf
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

```

```

```

```vbscript
```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then

```vbscript
           Dim objSchTempListFact As SchTempListFactory

           Dim objSchCompCompatA As SchCompatible
```
```

```vbscript
```vbscript
```vbscript
           Dim objSchGRRCompA As SchGRRComp

           Dim objSchCompCompatB As SchCompatible
           Dim objSchGRRCompB As SchGRRComp

           Set objSchTempListFact = objSchRoot.GetTemporaryListFactory

```
```

```

```

```vbscript
           If ( Not ( objSchTempListFact Is Nothing )) Then
```vbscript
```vbscript
```vbscript
              Set objLCompat_g = objSchTempListFact.CreateListOfObjects
              Set objLGRRComp_g = objSchTempListFact.CreateListOfObjects
           End If
```

```

```

```

```vbscript
           If ( Not ( objLCompat_g Is Nothing )  And _
```vbscript
                Not ( objLGRRComp_g Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              ' Find 2 component instances in the model
              '--------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'--------------------------------------------------------------------
' Find 2 component instances in the model
'--------------------------------------------------------------------
```

```

              Find2ComponentInst objSchRoot
```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              ' Route a line connecting its ends to each component
              '--------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'--------------------------------------------------------------------
' Route a line connecting its ends to each component
'--------------------------------------------------------------------
```

```

              RouteLineBetween2Component objSchRoot

```

```vbscript
```vbscript
           End If

```

```

```vbscript
```vbscript
        End If '--- If ( Not ( objSchRoot Is Nothing )...

```

```

```vbscript
End If '--- If ( Not ( objSchRoot Is Nothing )...
        strMessage_g = strMessage_g & _
```

          "--------------------------------------------------------------------" & vbCr
```vbscript
        MsgBox strMessage_g

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
    Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRRComp
```
```

```vbscript
```vbscript
       Dim objSchLSymbols As SchListOfObjects
```vbscript
```
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
    ' | Input: objSchRouteGraph:  the schematic route
    ' |        (a CATIASchRouteGraphic interface handle).
    ' | Returns: the route graphic primitives
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic) _
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
Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic) _
      As SchGRR
```

```vbscript
       Dim objSchLGRR As SchListOfObjects
```vbscript
```
```vbscript
       If ( Not ( objSchRouteGraphArg Is Nothing ) ) Then
```vbscript
          Set objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives
          If ( Not ( objSchLGRR Is Nothing ) ) Then
```
```vbscript
             Set GetRoutePrimitives = objSchLGRR.Item (1,"CATIASchGRR")
          End If
```
       End If
```

```

```vbscript
```vbscript
    End Function

```
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find a connector that matches the input x-y coordinates.
    ' | Input: dbXArg,dbYArg:  the x-y coordinates of the matching point
    ' |        objSchGRR: the graphic primitives of the route.
    ' |        objSchCntbl: the connectable to search for the connectors
    ' | Returns: the connector handle
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Function FindConnectorAtPosition ( dbXArg As Double, dbYArg As Double, _
```
```

```vbscript
```vbscript
```vbscript
' | Returns: the connector handle
' -----------------------------------------------------------------------------
```

```

```vbscript
Private Function FindConnectorAtPosition ( dbXArg As Double, dbYArg As Double, _
      objSchCntblArg As SchAppConnectable, _
```
      objSchRootArg As SchematicRoot ) As SchAppConnector

```

```vbscript
```vbscript
       Dim objLCntr As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
       Dim objLFilter As CATIASchListOfBSTRs
       Dim objSchRouteGraphic As SchRouteGraphic
       Dim objGRR As SchGRR

```
```

```

```

```vbscript
       If ( Not ( objSchCntblArg Is Nothing ) And _
```vbscript
            Not ( objSchRootArg Is Nothing ) ) Then
```vbscript
```vbscript
          Set objLFilter = Nothing

          Set objLCntr = objSchCntblArg.AppListConnectors (objLFilter)

          Set objSchRouteGraphic = objSchRootArg.GetInterface ( _
```
```

```

```

            "CATIASchRouteGraphic", objSchCntblArg)
```vbscript
```vbscript
Set objLCntr = objSchCntblArg.AppListConnectors (objLFilter)
```vbscript
```
```vbscript
```vbscript
Set objSchRouteGraphic = objSchRootArg.GetInterface ( _
          If ( Not ( objSchRouteGraphic Is Nothing ) ) Then
```
```vbscript
             Set objGRR = GetRoutePrimitives (objSchRouteGraphic)
          End If
```
       End If '--- If ( Not ( objSchRoute Is Nothing ) ...

```

```

```

```vbscript
       If ( Not ( objLCntr Is Nothing )  And _
```vbscript
             Not ( objGRR Is Nothing ) ) Then

```vbscript
```vbscript
          Dim intNbCntr As Integer
          Dim iCntr As Integer
          Dim objLDbOut As SchListOfDoubles
          Dim objCntrLoc As SchCntrLocation
          Dim IntNbCoord As Integer
          Dim dbXOut As Double
          Dim dbYOut As Double

```
```

```

```

```vbscript
```vbscript
Dim dbXOut As Double
```vbscript
```
```vbscript
Dim dbYOut As Double
```
```

          intNbCntr = objLCntr.Count
```

```vbscript
          If (intNbCntr > 0) Then
```vbscript
```vbscript
             For iCntr = 1 To intNbCntr
```vbscript
               Set objCntrLoc = Nothing
               Set objLDbOut = Nothing

               Set objCntrLoc = objLCntr.Item (iCntr,"CATIASchCntrLocation")

```
```

```

```

```vbscript
```vbscript
               If (Not ( objCntrLoc Is Nothing ) ) Then

```

```

                  objCntrLoc.GetPosition objGRR,objLDbOut

```vbscript
                  If ( Not ( objLDbOut Is Nothing ) ) Then
                     IntNbCoord = objLDbOut.Count
                     If (IntNbCoord > 1) Then
```vbscript
```vbscript
                       dbXOut = objLDbOut.Item(1)
                       dbYOut = objLDbOut.Item(2)
                       If ( ( dbXOut = dbXArg ) And _
```

```

```

                            ( dbYOut = dbYArg ) ) Then

```vbscript
dbXOut = objLDbOut.Item(1)
```vbscript
```vbscript
dbYOut = objLDbOut.Item(2)
If ( ( dbXOut = dbXArg ) And _
```vbscript
                          Set FindConnectorAtPosition =  objSchRootArg.GetInterface ( _
```
```

```

```

                             "CATIASchAppConnector", objCntrLoc )

                          Exit For

```vbscript
                       End If
```vbscript
```vbscript
                     End If
                  End If
               End If '--- If (Not ( objCntrLoc Is Nothing ...
```

```

             Next ' --- For iCntr = 1 To intNbCntr ...
          End If '--- If (intNbCntr > 0) ...
```vbscript
```vbscript
       End If '--- If ( Not ( objLCntr Is Nothing ) ...

```

```

```

```vbscript
```vbscript
    End Function

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find 2 components and their images. The user need to designate specific
    ' | specific component instances by naming them specially.
    ' | From - component : should have "_Routefrom" embedded in the name
    ' | To - component : should have "_Routeto" embedded in the name
    ' |
    ' | Input: objSchRootArg:  the root of the document.
    ' | Returns: objLCompat_g: a list of component instance objects
    ' |          objLGRRComp_g: a list of component instance image objects
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Sub Find2ComponentInst (objSchRootArg As SchematicRoot)
```
```

```vbscript
       If ( objLCompat_g Is Nothing ) Then Exit Sub
```vbscript
```vbscript
       If ( objLGRRComp_g Is Nothing ) Then Exit Sub

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
       Dim objCompCompat As SchCompatible
       Dim objGRRComp As SchGRRComp

       Dim objCompCompatFrom As SchCompatible
       Dim objGRRCompFrom As SchGRRComp
       Dim objCompCompatTo As SchCompatible
       Dim objGRRCompTo As SchGRRComp

       Dim objPrd As Product
       Dim strInstName As String
       Dim strTgtTo As String
       Dim strTgtFrom As String
       Dim intFound As Integer
       Dim intNbFound As Integer
       Dim intStoreIndex As Integer

       Set objCompCompatFrom = Nothing
       Set objGRRCompFrom  = Nothing
       Set objCompCompatTo = Nothing
       Set objGRRCompTo  = Nothing
       If (Not ( objLCompInst Is Nothing ) ) Then
```
```

```

```

```vbscript
```vbscript
```vbscript
          '------------------------------------------------------------------------
          '  Loop through the members in the list and find 2 components that
          '  have "network" as part of the product instance names
          '------------------------------------------------------------------------
```

```

          intNbFound = 0
          intStoreIndex = 0
          strTgtFrom = "_Routefrom"
          strTgtTo = "_Routeto"
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
```vbscript
            Set objCompCompat = objLCompInst.Item (intIndex,"CATIASchCompatible")

```
```

```

```vbscript
```vbscript
            If ( Not ( objCompCompat Is Nothing ) ) Then

```vbscript
               Set objPrd = objSchRootArg.GetInterface ( _
```
```

```

                 "CATIAProduct", objCompCompat)

```vbscript
               If ( Not ( objPrd Is Nothing ) ) Then
                  strInstName = objPrd.Name
                  intFound  = Instr (1, strInstName, strTgtFrom, 1)
```vbscript
```vbscript
                  If ( intFound < 1 ) Then
                     intFound  = Instr (1, strInstName, strTgtTo, 1)
```

```

                     intStoreIndex = 2
                  Else
                     intStoreIndex = 1
                  End If
```vbscript
```vbscript
               End If

```

```

```

```vbscript
```vbscript
               If ( intFound > 0 ) Then

```vbscript
                 Dim ObjSchCompGraph As SchCompGraphic
```
```

```vbscript
```vbscript
                 Set objSchCompGraph = objSchRootArg.GetInterface ( _
```
```

```

                   "CATIASchCompGraphic",objCompCompat)
```vbscript
If ( intFound > 0 ) Then
```vbscript
```vbscript
```vbscript
Dim ObjSchCompGraph As SchCompGraphic
Set objSchCompGraph = objSchRootArg.GetInterface ( _
                 Set objGRRComp = GetComponentImage (objSchCompGraph)

```
```

```

```

```vbscript
                 If ( ( Not objGRRComp Is Nothing ) ) Then
```vbscript
```vbscript
                    If ( intStoreIndex = 1 ) Then
```vbscript
                      Set objCompCompatFrom = objCompCompat
                      Set objGRRCompFrom = objGRRComp
```
```

```

                    Else
```vbscript
                      Set objCompCompatTo = objCompCompat
```vbscript
```
```vbscript
```vbscript
                      Set objGRRCompTo = objGRRComp
                    End If
```
```

```

                    intNbFound  = intNbFound + 1
                 End If
```vbscript
```vbscript
               End If

```

```

```

```vbscript
```vbscript
               If ( intNbFound > 1 ) Then  Exit For

```

```

```vbscript
```vbscript
            End If '--- If ( Not ( objCompCompat Is Nothing ) ...

```

```

```vbscript
          Next

```

```vbscript
          If ( Not ( objCompCompatFrom Is Nothing ) And _
```vbscript
               Not ( objGRRCompFrom Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objCompCompatFrom Is Nothing ) And _
```

Not ( objGRRCompFrom Is Nothing ) ) Then
             objLCompat_g.Append objCompCompatFrom
             objLGRRComp_g.Append objGRRCompFrom

```vbscript
```vbscript
          End If

```

```

```vbscript
          If ( Not ( objCompCompatTo Is Nothing ) And _
```vbscript
               Not ( objGRRCompTo Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objCompCompatTo Is Nothing ) And _
```

Not ( objGRRCompTo Is Nothing ) ) Then
             objLCompat_g.Append objCompCompatTo
             objLGRRComp_g.Append objGRRCompTo

```vbscript
```vbscript
          End If

```

```

```vbscript
```vbscript
       End If '--- If (Not ( objLCompInst Is Nothing ) ...

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
    ' | Route a line from member 1 in objLCompat_g to member 2 in objLCompat_g.
    ' | These members are specific interface handle on 2 component instances.
    ' |
    ' | Input: objSchRootArg:  the root of the document.
    ' | Returns: objLCompat_g: a list of component instance objects
    ' |          objLGRRComp_g: a list of component instance image objects
    ' -----------------------------------------------------------------------------
```

```

```vbscript
```vbscript
    Private Sub RouteLineBetween2Component (objSchRootArg As SchematicRoot)
       If ( objLCompat_g Is Nothing ) Then Exit Sub
```
```

```vbscript
```vbscript
       If ( objLGRRComp_g Is Nothing ) Then Exit Sub

```vbscript
       Dim intNbComp As Integer
       Dim intNbGRR As Integer
       Dim intIndex As Integer
```
```

```

```

       intNbComp = objLCompat_g.Count
       intNbGRR = objLGRRComp_g.Count

```vbscript
       If ( intNbComp <> 2 ) Then Exit Sub
```vbscript
```vbscript
       If ( intNbComp <> intNbGRR ) Then Exit Sub
       If ( objSchRootArg Is Nothing ) Then Exit Sub

```vbscript
       Dim objAppObjFact As SchAppObjectFactory
       Set objAppObjFact = objSchRootArg.GetApplObjFactFromVirtualType ("CAASCHEDU_SamplePID")
       If ( objAppObjFact Is Nothing ) Then Exit Sub
```

```vbscript
       Dim objSchBaseFact As SchBaseFactory
       Set objSchBaseFact = objSchRootArg.GetSchBaseFactory
       If ( objSchBaseFact Is Nothing ) Then Exit Sub
```

```vbscript
       Dim objCompCompat As SchCompatible
       Dim objGRRComp As SchCompGRR
       Dim bCompatible As Boolean
       Dim objLCntrs As SchListOfObjects
       Dim objSchGRR As SchGRR
       Dim objAppCntrBest As SchAppConnector
       Dim objLDbOut As SchListOfDoubles
       Dim db2CntrPt(2) As Double
       Dim db2SelectPt(2) As CATSafeArrayVariant
       Dim intNbCoord As Integer
       Dim objAppCntrCompBest1 As SchAppConnector
       Dim objAppCntrCompBest2 As SchAppConnector
       Dim db2CntrPt1(2) As Double
       Dim db2CntrPt2(2) As Double
       Dim objPrd As Product
       Dim strName As String

```
```

```

```

```vbscript
       For intIndex = 1 To 2
```vbscript
```vbscript
```vbscript
          Set objCompCompat = Nothing
          Set objGRRComp = Nothing
          Set objLCntrs = Nothing
          Set objSchGRR = Nothing
          Set objPrd = Nothing

          Set objCompCompat = objLCompat_g.Item (intIndex,"CATIASchCompatible")
          Set objGRRComp = objLGRRComp_g.Item (intIndex,"CATIASchGRRComp")

          Set objPrd = objSchRootArg.GetInterface ("CATIAProduct",objCompCompat)
          If ( Not ( objPrd Is Nothing ) ) Then
```
```

```

             strName = objPrd.Name
             If ( intIndex = 1 ) Then
                strMessage_g = strMessage_g &  _
```

                  "Routing from " &  strName & vbCr
```vbscript
If ( Not ( objPrd Is Nothing ) ) Then
```

strName = objPrd.Name
```vbscript
If ( intIndex = 1 ) Then
```

strMessage_g = strMessage_g &  _
             Else
                strMessage_g = strMessage_g &  _

                  "Routing to " &  strName & vbCr
strMessage_g = strMessage_g &  _
Else
strMessage_g = strMessage_g &  _
```vbscript
             End If
```vbscript
```vbscript
          End If

```

```

```

```vbscript
          If ( Not ( objGRRComp Is Nothing ) And _
```vbscript
               Not ( objCompCompat Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
             '---------------------------------------------------------------------
             '  IsTargetOKRoute returns a list of compatible connectors
             '  on the target component is the component is compatible to
             '  to connected to the start point of the route.
             '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'  on the target component is the component is compatible to
'  to connected to the start point of the route.
'---------------------------------------------------------------------
```

```

             objCompCompat.IsTargetOKForRoute "CAASCHEDUConnector", _
               objGRRComp, objLCntrs, bCompatible

```vbscript
```vbscript
             Set objSchGRR = objSchRootArg.GetInterface ("CATIASchGRR",objGRRComp)

```
```

```

```vbscript
             If ( Not ( objLCntrs Is Nothing ) And  _
```vbscript
                  Not ( objSchGRR Is Nothing ) And bCompatible ) Then

```

```

```vbscript
                If ( intIndex = 1 ) Then
```vbscript
                   db2SelectPt(0) = 83.75
                   db2SelectPt(1) = 81.25
```

                Else
                   db2SelectPt(0) = 130.0
```vbscript
                   db2SelectPt(1) = 100.0
                End If
```

```

```vbscript
```vbscript
```vbscript
                '------------------------------------------------------------------
                '  GetBestCntrForRoute returns a connector from
                '  the output list that is closest
                '  to a user selection point.
                '------------------------------------------------------------------
```vbscript
                Set objLDbOut = Nothing
                Set objAppCntrBest = Nothing
```
```

```

```

```vbscript
```vbscript
```vbscript
'------------------------------------------------------------------
```vbscript
Set objLDbOut = Nothing
Set objAppCntrBest = Nothing
```
```

```

                objCompCompat.GetBestCntrForRoute db2SelectPt, _
                  objSchGRR, objLCntrs, objLDbOut, objAppCntrBest

```

objCompCompat.GetBestCntrForRoute db2SelectPt, _
objSchGRR, objLCntrs, objLDbOut, objAppCntrBest
                IntNbCoord = objLDbOut.Count

```vbscript
                If (IntNbCoord > 1) Then
```vbscript
                  db2CntrPt(0) = objLDbOut.Item(1)
                  db2CntrPt(1) = objLDbOut.Item(2)

```

```

```vbscript
                  If ( intIndex = 1 ) Then
```vbscript
                     db2CntrPt1(0) =  db2CntrPt(0)
                     db2CntrPt1(1) =  db2CntrPt(1)
```vbscript
                     Set objAppCntrCompBest1 = objAppCntrBest
```
```

                     strMessage_g = strMessage_g &  _
```

                       "Target is compatible for route " & vbCr
```vbscript
db2CntrPt1(0) =  db2CntrPt(0)
```vbscript
db2CntrPt1(1) =  db2CntrPt(1)
```vbscript
Set objAppCntrCompBest1 = objAppCntrBest
```
```

```

strMessage_g = strMessage_g &  _
                     strMessage_g = strMessage_g &  "Route point starts at " & _
                       db2CntrPt(0) & " " & db2CntrPt(1) & vbCr
                  Else
                     db2CntrPt2(0) =  db2CntrPt(0)
```vbscript
                     db2CntrPt2(1) =  db2CntrPt(1)
```

                     strMessage_g = strMessage_g &  _

                       "Target is compatible for route " & vbCr
Else
db2CntrPt2(0) =  db2CntrPt(0)
```vbscript
db2CntrPt2(1) =  db2CntrPt(1)
```

strMessage_g = strMessage_g &  _
                     strMessage_g = strMessage_g &  "Route point ends at " & _
                       db2CntrPt(0) & " " & db2CntrPt(1) & vbCr
```vbscript
```vbscript
                     Set objAppCntrCompBest2 = objAppCntrBest
```vbscript
```
```vbscript
                  End If
                End If '--- If (IntNbCoord > 1) Then

```

```

```

```vbscript
             End If '--- If ( Not ( objLCntrs Is Nothing ) And  _
```vbscript
          End If '--- If ( Not ( objGRRComp Is Nothing ) ...
```

       Next '--- For intIndex

```vbscript
       Dim objAppRouteRef As AnyObject
```vbscript
```
```vbscript
```vbscript
       Dim objSchRoute As AnyObject
       Dim strLogLineID As String
       Dim dbPtArray(8) As CATSafeArrayVariant

```
```

```

```

```vbscript
```vbscript
       Dim objAppCntrRouteBest1 As SchAppConnector
```vbscript
```
```vbscript
```vbscript
       Dim objAppCntrRouteBest2 As SchAppConnector

       Dim objAppConnection As SchAppConnection
       Dim objRouteCntbl As SchAppConnectable

```
```

```

```

```vbscript
```vbscript
Dim objAppConnection As SchAppConnection
```vbscript
```
```vbscript
Dim objRouteCntbl As SchAppConnectable
       dbPtArray(0) = db2CntrPt1(0)
```
       dbPtArray(1) = db2CntrPt1(1)

```

```

       dbPtArray(2) = (db2CntrPt1(0) + db2CntrPt2(0)) * 0.5
```vbscript
       dbPtArray(3) = db2CntrPt1(1)

       dbPtArray(4) = dbPtArray(2)
       dbPtArray(5) = db2CntrPt2(1)

       dbPtArray(6) = db2CntrPt2(0)
       dbPtArray(7) = db2CntrPt2(1)

```

```vbscript
```vbscript
```vbscript
       '---------------------------------------------------------------------------
       ' Ask application to create a route reference
       '---------------------------------------------------------------------------
       'Logical line concept not supported in sample application
       'So just send in a null string.
       'strLogLineID = ""
```

```

```

```vbscript
```vbscript
```vbscript
'Logical line concept not supported in sample application
'So just send in a null string.
'strLogLineID = ""
```

```

       objAppObjFact.AppCreateRoute "CAASCHEDUFuncString", _
         objAppRouteRef, strLogLineID

```

```vbscript
       If ( Not ( objAppRouteRef Is Nothing ) ) Then
         strMessage_g = strMessage_g &  _
```

           "application reference route created" & vbCr

strMessage_g = strMessage_g &  _
         objSchBaseFact.CreateSchRouteByPoints objAppRouteRef, _
           dbPtArray, objSchRoute

```vbscript
         If ( Not ( objSchRoute Is Nothing ) ) Then
           strMessage_g = strMessage_g &  "schematic route created" & vbCr

```vbscript
           Set objRouteCntbl = objSchRootArg.GetInterface ( _
```
```

             "CATIASchAppConnectable",objSchRoute)
```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Find the connector of the route matching the
           ' component connector position at each end
           '-----------------------------------------------------------------------

```vbscript
           Set objAppCntrRouteBest1 = FindConnectorAtPosition ( _
```
```

```

```

```vbscript
```vbscript
```vbscript
'-----------------------------------------------------------------------
```vbscript
Set objAppCntrRouteBest1 = FindConnectorAtPosition ( _
```
```

             db2CntrPt1(0), db2CntrPt1(1), objRouteCntbl, objSchRootArg)

```vbscript
           Set objAppCntrRouteBest2 = FindConnectorAtPosition ( _
             db2CntrPt2(0), db2CntrPt2(1), objRouteCntbl, objSchRootArg)
```
```

```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Connect the route to the 2 components
           '-----------------------------------------------------------------------
           If ( Not (objAppCntrRouteBest1 Is Nothing ) And _
```

```

```

```vbscript
```vbscript
```vbscript
' Connect the route to the 2 components
'-----------------------------------------------------------------------
If ( Not (objAppCntrRouteBest1 Is Nothing ) And _
```

                Not (objAppCntrCompBest1 Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              ' Connect start point of route to "*_from" component
              '--------------------------------------------------------------------
```vbscript
              Set objAppConnection = objAppCntrCompBest1.AppConnect _
```
```

```

                (objAppCntrRouteBest1)
```

```vbscript
              If ( Not ( objAppConnection Is Nothing ) ) Then
                 strMessage_g = strMessage_g & "route has been connected"
                 strMessage_g = strMessage_g & _
```

                   " to _from component successfully" & vbCr
```vbscript
If ( Not ( objAppConnection Is Nothing ) ) Then
```

strMessage_g = strMessage_g & "route has been connected"
strMessage_g = strMessage_g & _
```vbscript
```vbscript
              End If

```

```

```vbscript
```vbscript
           End If '--- If ( Not (objAppCntrRouteBest Is Nothing ) ...

```

```

```vbscript
           If ( Not (objAppCntrRouteBest2 Is Nothing ) And _
```vbscript
                Not (objAppCntrCompBest2 Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
              '--------------------------------------------------------------------
              ' Connect end point of route to "*_to" component
              '--------------------------------------------------------------------
```vbscript
              Set objAppConnection = objAppCntrCompBest2.AppConnect _
```
```

```

                (objAppCntrRouteBest2)
```

```vbscript
              If ( Not ( objAppConnection Is Nothing ) ) Then
                 strMessage_g = strMessage_g & "route has been connected"
                 strMessage_g = strMessage_g & _
```

                   " to _to component successfully" & vbCr
```vbscript
If ( Not ( objAppConnection Is Nothing ) ) Then
```

strMessage_g = strMessage_g & "route has been connected"
strMessage_g = strMessage_g & _
```vbscript
```vbscript
              End If

```

```

```vbscript
```vbscript
           End If '--- If ( Not (objAppCntrRouteBest Is Nothing ) ...

```

```

```vbscript
```vbscript
         End If '--- If ( Not ( objSchRoute Is Nothing )...

```

```

```vbscript
```vbscript
       End If '--- If ( Not ( objAppCompRef Is Nothing ) ...

```

```

```vbscript
```vbscript
    End Sub

```
```
