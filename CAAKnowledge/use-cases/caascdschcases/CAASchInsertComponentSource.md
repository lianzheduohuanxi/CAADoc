---
```vbscript
title: "CAASchInsertComponent.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_Sample", "CATIASchGRRRoute", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CAASCH_RouteForPlacement", "CATIA", "CAASacInsertComponent", "CATIASchCompatible", "CATIASchComponent", "CATIASchCompGraphic", "CATIASchRoute", "CATIASchAppConnectable", "CAASchInsertComponent"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInsertComponentSource.htmmd"
converted: "2026-05-11T17:31:51.378605"
```

---
tags: ["CAASCH_Sample", "CATIASchGRRRoute", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CAASCH_RouteForPlacement", "CATIA", "CAASacInsertComponent", "CATIASchCompatible", "CATIASchComponent", "CATIASchCompGraphic", "CATIASchRoute", "CATIASchAppConnectable", "CAASchInsertComponent"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInsertComponentSource.htmmd"
converted: "2026-05-11T17:31:51.378605"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Insert a schematic component into a route.
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
        ' Open the catalog document
```vbscript
        Dim sCtlgFilePath
        sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdSchUseCases/samples/CAASCH_Sample.catalog")

```vbscript
```vbscript
sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```vbscript
        Dim objSchCtlgDoc As Document
        Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)
```
```

```

```

```vbscript
```vbscript
```vbscript
        ' Open main schematic design document (for new component instances created here)
```vbscript
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdSchUseCases/samples/CAASCH_RouteForPlacement.CATProduct")

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

          "Output traces from CAASacInsertComponent.CATScript" & vbCrLf
strMessage = _
strMessage = strMessage & _
        '
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
        If ( Not ( IsEmpty(objSchDoc)) ) Then
```
```vbscript
          Set objPrdRoot = objSchDoc.Product
          If ( Not ( IsEmpty(objPrdRoot)) ) Then
```
```vbscript
            Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
          End If
```
        End If

```vbscript
        Dim objSchGRRCVCtlg As SchGRR
        Dim objSchCntblCVRef As SchAppConnectable
        Dim objSchCompCVRef As SchComponent
        Dim objSchCompatRoute As SchCompatible
        Dim objSchCompInst As SchComponent
        Dim objSchCompInst2 As SchComponent
        Dim objSchRouteInst As SchRoute
        Dim objSchCntblRouteInst As SchAppConnectable
        Dim objSchRouteGraph As SchRouteGraphic

```
```

```

```

```vbscript
        If ( Not ( IsEmpty(objSchRoot ) ) ) Then
```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Get the symbol of a component from the component catalog.
           '-----------------------------------------------------------------------
```vbscript
           Set objSchGRRCVCtlg = objSchRoot.GetCompSymbolFromCatalog ("Control Valve",objSchCtlgDoc)
           If ( Not ( IsEmpty(objSchGRRCVCtlg) ) ) Then
```
```

```

             strMessage = strMessage &  "Got the catalog symbol" & vbCr
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Get the owner of the symbol. That is, a reference component,
             ' in the catalog.
             '---------------------------------------------------------------------
```vbscript
             Set objSchCntblCVRef = objSchGRRCVCtlg.GetSchObjOwner
             If ( Not ( IsEmpty (objSchCntblCVRef ) ) ) Then
```
```

```

               strMessage = strMessage &  "Got catalog connectable of the symbol" & vbCr

```vbscript
               Dim objCompRefPlaceInfo As AnyObject
```vbscript
```
```vbscript
```vbscript
               Dim objCompatInfo As AnyObject
               Dim objFinalInsertInfo As AnyObject
               Dim bYesCompat As Boolean
               Dim bFindAllSolutions As Boolean

               Set objSchCompCVRef = objSchRoot.GetInterface ("CATIASchComponent",objSchCntblCVRef)
               If ( Not ( IsEmpty (objSchCompCVRef ) ) ) Then
```
```

```

                  strMessage = strMessage &  "Got catalog component reference of the symbol" & vbCr
```vbscript
                  Set objSchCompatRoute = FindARouteInModel (objSchRoot)
```vbscript
```
               End If 'If ( Not ( IsEmpty (objSchCompCVRef ) ) ...
```

```

```vbscript
               If ( Not ( IsEmpty (objSchCompCVRef ) ) And _
```vbscript
                    Not ( IsEmpty (objSchCompatRoute )) ) Then
```

```

```vbscript
```vbscript
```vbscript
                  '----------------------------------------------------------------
                  '  Insert a component into a route.
                  '
                  '  Approach 1 - with compatibility information.
                  '  1- QueryConnectAbility.
                  '     Ask the reference of the component for information
                  '     to use in compatibility checking. The objCompRefPlaceInfo
                  '     is an output and should be used as a "black box".
                  '     It is the input to the next call.
                  '
                  '  2- IsTargetOKForInsert
                  '     Check whether the route is compatible to the component
                  '     in making connections.
                  '     The route instance is the "target".
                  '     objCompatInfo is an output and should be used as
                  '     a "black box". It is an input to the next call.
                  '
                  '  3- GetBestFitInsertInfo
                  '     Input the placement location, close to middle of the route
                  '     objFinalInsertInfo is an output and should be used as
                  '     a "black box". It is an input to the next call.
                  '
                  '  4- InsertIntoRouteWithInfo
                  '     Place a new component instance with the black box info.
                  '     The route will be broken up into 2 pieces (shorten the
                  '     existing route and create a new route instance).
                  '     The new component instance will be connected to the
                  '     2 routes on each of the 2 sides (left and right).
                  '----------------------------------------------------------------
                  ' -- step 1
```vbscript
                  Set objCompRefPlaceInfo = objSchCompCVRef.QueryConnectAbility _
```
```

```

                    (objSchGRRCVCtlg)
```vbscript
                  ' -- step 2
```

```

```vbscript
```vbscript
Set objCompRefPlaceInfo = objSchCompCVRef.QueryConnectAbility _
```
```

(objSchGRRCVCtlg)
```vbscript
' -- step 2
```

                  objSchCompatRoute.IsTargetOKForInsert objCompRefPlaceInfo, _
                    objCompatInfo, bYesCompat

```vbscript
```vbscript
                  Dim db2Pt(2) As CATSafeArrayVariant
```vbscript
```
                  '-- a point at the middle of the route
                  db2Pt(0) = 80.0
                  db2Pt(1) = 50.0

```

```

```vbscript
                  If ( bYesCompat ) Then
                     strMessage = strMessage &  "Target is compatible" & vbCr
                     bFindAllSolutions = false
```vbscript
                     ' -- step 3
```

                     objSchCompatRoute.GetBestFitInsertInfo db2Pt, objCompatInfo, _
                       objFinalInsertInfo, bFindAllSolutions

```

```vbscript
                     If ( Not ( IsEmpty (objFinalInsertInfo ) ) ) Then
```vbscript
                        ' -- step 4
```

                        objSchCompCVRef.InsertIntoRouteWithInfo objFinalInsertInfo, _
                          objSchCompInst,objSchRouteInst

```

```vbscript
                        If ( Not ( IsEmpty (objSchCompInst ) )  And _
```vbscript
                             Not ( IsEmpty (objSchRouteInst ) ) ) Then
```

                           strMessage = strMessage &  _
```

                             "Insert a new component instance into a route is successful" & vbCr
```vbscript
If ( Not ( IsEmpty (objSchCompInst ) )  And _
```

Not ( IsEmpty (objSchRouteInst ) ) ) Then
strMessage = strMessage &  _
```vbscript
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
End If
                  Else
                     strMessage = strMessage &  "Target is NOT compatible" & vbCr
                  End If
```

```vbscript
```vbscript
```vbscript
                  '----------------------------------------------------------------
                  '  Insert a component into a route.
                  '
                  '  Approach 2 - without compatibility information.
                  '  One step approach.
                  '  Is this specific example, we want to place another
                  '  instance of the control valve on the middle of the first
                  '  segment of the new route we have just created.
                  '
                  '  1- we need the interface handle on the new route we
                  '  have just created
                  '
                  '  2- we need to figure out the placement point location.
                  '  For this we need to extract the x-y coordinates of the route
                  '  points.
                  '----------------------------------------------------------------

```vbscript
                  Dim objLDbPlace As SchListOfDoubles
```
```

```

```

```vbscript
```vbscript
                  If ( Not ( IsEmpty (objSchRouteInst ) ) ) Then

```vbscript
                    Set objSchCntblRouteInst = objSchRoot.GetInterface ( _
```
```

```

                      "CATIASchAppConnectable",objSchRouteInst)

```vbscript
If ( Not ( IsEmpty (objSchRouteInst ) ) ) Then
```vbscript
```vbscript
```vbscript
Set objSchCntblRouteInst = objSchRoot.GetInterface ( _
                    Set objSchRouteGraph = objSchRoot.GetInterface ( _
```
```

```

```

                      "CATIASchRouteGraphic",objSchRouteInst)

```vbscript
```vbscript
```vbscript
                    Set objLDbPlace = FindPlacementPoint (objSchRoot, objSchRouteGraph)

```
```

```

```vbscript
```vbscript
                  End If

```

```

```vbscript
                  If (  Not ( IsEmpty (objSchCntblRouteInst ) ) And _
```vbscript
                        Not ( IsEmpty (objLDbPlace ) )  ) Then

```

```

```vbscript
If (  Not ( IsEmpty (objSchCntblRouteInst ) ) And _
```

Not ( IsEmpty (objLDbPlace ) )  ) Then
```vbscript
                    db2Pt(0) = objLDbPlace.Item(1)
                    db2Pt(1) = objLDbPlace.Item(2)

```

                    strMessage = strMessage &  _

                      "Placement point for PlaceOnObject = (" & db2Pt(0) & "," & db2Pt(1) &")" & vbCr

```vbscript
```vbscript
                     Dim db6Matrix(6) As CATSafeArrayVariant
```vbscript
```
                     db6Matrix(0)=1.0
                     db6Matrix(1)=0.0
                     db6Matrix(2)=0.0
                     db6Matrix(3)=1.0
                     db6Matrix(4)=db2Pt(0)
                     db6Matrix(5)=db2Pt(1)

```

```

```vbscript
db6Matrix(4)=db2Pt(0)
```vbscript
db6Matrix(5)=db2Pt(1)
```

                     objSchCompCVRef.PlaceOnObject objSchGRRCVCtlg, db6Matrix, _
                       objSchCntblRouteInst, objSchCompInst2

```

```vbscript
                     If (  Not ( IsEmpty (objSchCntblRouteInst ) )  ) Then
                        strMessage = strMessage &  _
```

                          "PlaceOnObject is successful" & vbCr
```vbscript
If (  Not ( IsEmpty (objSchCntblRouteInst ) )  ) Then
```

strMessage = strMessage &  _
```vbscript
```vbscript
                     End If

```

```

```vbscript
```vbscript
                  End If '---- If ( ( Not ( IsEmpty (objSchCntblRouteInst ) ) ...

```

```

```vbscript
```vbscript
               End If '----If ( Not ( IsEmpty (objSchCompCVRef ) )...

```

```

```vbscript
```vbscript
             End If '---- If ( Not ( IsEmpty (objSchCntblCVRef ) )...

```

```

```vbscript
```vbscript
           End If '----- If ( Not ( IsEmpty (objSchGRRCVCtlg ) )...

```

```

```vbscript
```vbscript
        End If  '----If ( Not ( IsEmpty (objSchRoot ) )...

```

```

```vbscript
End If  '----If ( Not ( IsEmpty (objSchRoot ) )...
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
    ' | Find a route instance in the model.
    ' | Input: objSchCompGraph:  the schematic component
    ' |        (a CATIASchCompGraphic interface handle).
    ' | Returns: the component image (the symbol instance)
    ' -----------------------------------------------------------------------------
```

```

```vbscript
```vbscript
    Private Function FindARouteInModel (objSchRootArg As SchematicRoot) As SchCompatible
       Dim objSchLSymbols As SchListOfObjects
```
```

```vbscript
```vbscript
       If ( Not ( IsEmpty (objSchRootArg ) ) ) Then
```vbscript
          Set objSchLSymbols = objSchRootArg.GetRoutes
          If ( Not ( IsEmpty (objSchLSymbols ) ) ) Then
```
```vbscript
             Set FindARouteInModel = objSchLSymbols.Item (1,"CATIASchCompatible")
          End If
```
       End If
```

```

```vbscript
    End Function
```vbscript
```
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find a route instance in the model.
    ' | Input: objSchRouteArg:  the route
    ' |        (a CATIASchRoute interface handle).
    ' | Returns: the mid point of the first segment of the route.
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Function FindPlacementPoint (objSchRootArg As SchematicRoot, _
```
```

```vbscript
```vbscript
```vbscript
' | Returns: the mid point of the first segment of the route.
' -----------------------------------------------------------------------------
```

```

```vbscript
Private Function FindPlacementPoint (objSchRootArg As SchematicRoot, _
      objSchRouteGraphArg As SchRouteGraphic) As SchListOfDoubles
```

```vbscript
       Dim objSchLGRR As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
       Dim objSchLDb As SchListOfDoubles
       Dim objSchGRRRoute As SchGRRRoute
       Dim objSchTempListFact As SchTempListFactory
       Dim intSize As Integer
       Dim intCount As Integer
       Dim db2Seg1(4) As CATSafeArrayVariant
       Dim dbXOut As Double
       Dim dbYOut As Double

```
```

```

```

```vbscript
       If ( Not ( IsEmpty (objSchRootArg ) ) ) Then
```vbscript
```vbscript
```vbscript
          Set objSchTempListFact = objSchRootArg.GetTemporaryListFactory
          If ( Not ( IsEmpty (objSchTempListFact ) ) ) Then
```
```vbscript
             Set FindPlacementPoint = objSchTempListFact.CreateListOfDoubles
          End If
```
       End If

```

```

```

```vbscript
       If ( Not ( IsEmpty (objSchRouteGraphArg ) ) And _
```vbscript
            Not ( IsEmpty (FindPlacementPoint ) ) ) Then

```vbscript
```vbscript
          Set objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives

```
```

```

```

```vbscript
```vbscript
          If ( Not ( IsEmpty (objSchLGRR ) ) ) Then

```vbscript
             Set objSchGRRRoute = objSchLGRR.Item (1,"CATIASchGRRRoute")

```
```

```

```vbscript
```vbscript
             If ( Not ( IsEmpty (objSchGRRRoute ) ) ) Then

```

```

                objSchGRRRoute.GetPath objSchLDb

```vbscript
```vbscript
                If ( Not ( IsEmpty (objSchLDb ) ) ) Then

```

```

                   intCount = objSchLDb.Count

```vbscript
```vbscript
                   If ( intCount > 3 ) Then

```

```

```vbscript
If ( intCount > 3 ) Then
```vbscript
                      db2Seg1(0) = objSchLDb.Item(1)
                      db2Seg1(1) = objSchLDb.Item(2)
                      db2Seg1(2) = objSchLDb.Item(3)
                      db2Seg1(3) = objSchLDb.Item(4)

```

```

                      dbXOut = (db2Seg1(0) + db2Seg1(2)) * 0.5
```vbscript
```vbscript
                      dbYOut = (db2Seg1(1) + db2Seg1(3)) * 0.5

```

```

                      FindPlacementPoint.Append (dbXOut)
                      FindPlacementPoint.Append (dbYOut)

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
          End If '--- If ( Not ( IsEmpty (objSchLGRR ) ) ...

```

```

```vbscript
```vbscript
       End If '--- If ( Not ( IsEmpty (objSchRouteGraphArg ) ) ...
```vbscript
    End Function

```
```

```
