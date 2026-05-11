---
```vbscript
title: "CAASchAppObjFactory.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCHEDUCompressFunc", "CAAScdSchUseCases", "CAASCH_Detail01", "CATIASchCompGraphic", "CAASCHEDU_SamplePID", "CATIA", "CAASCHEDUFuncString", "CATIASchListOfBSTRs", "CATIASchCompatible", "CATIASchAppConnectable", "CATIASchCntrLocation", "CAASchAppObjFactory", "CATIASchCompConnector", "CATIASchRouteGraphic", "CATIASchGRRComp", "CAASCHEDUConnector", "CATIASchGRR", "CATIASchAppConnector", "CATIASchComponent2"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchAppObjFactorySource.htm"
converted: "2026-05-11T17:31:51.321739"
```

---
tags: ["CAASCHEDUCompressFunc", "CAAScdSchUseCases", "CAASCH_Detail01", "CATIASchCompGraphic", "CAASCHEDU_SamplePID", "CATIA", "CAASCHEDUFuncString", "CATIASchListOfBSTRs", "CATIASchCompatible", "CATIASchAppConnectable", "CATIASchCntrLocation", "CAASchAppObjFactory", "CATIASchCompConnector", "CATIASchRouteGraphic", "CATIASchGRRComp", "CAASCHEDUConnector", "CATIASchGRR", "CATIASchAppConnector", "CATIASchComponent2"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchAppObjFactorySource.htm"
converted: "2026-05-11T17:31:51.321739"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Create an application reference and add connectors. Also
    '                 create an application route connecting to an instance of
    '                 the component.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```

```

```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
```vbscript
        End If
```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Open the schematic document
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

          "Output traces from CAASchAppObjFactory.CATScript" & vbCrLf
strMessage = _
strMessage = strMessage & _
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

        Dim objAppObjFact As SchAppObjectFactory
        Dim objSchBaseFact As SchBaseFactory
        Dim objSchTempListFact As SchTempListFactory

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
           Set objAppObjFact = objSchRoot.GetApplObjFactFromVirtualType ("CAASCHEDU_SamplePID")
           Set objSchBaseFact = objSchRoot.GetSchBaseFactory
           Set objSchTempListFact = objSchRoot.GetTemporaryListFactory
```

```

```

```vbscript
           If ( Not ( objAppObjFact Is Nothing ) And _
```vbscript
                Not ( objSchBaseFact Is Nothing )  And _
                Not ( objSchTempListFact Is Nothing ) ) Then

```

```

Not ( objSchBaseFact Is Nothing )  And _
```vbscript
Not ( objSchTempListFact Is Nothing ) ) Then
```

             strMessage = strMessage &  "Got Application object factory " & vbCr

```vbscript
             Dim objAppCompRef As AnyObject
```vbscript
```vbscript
             Dim objSchSymbol As AnyObject
             Dim objSchCompRef As SchComponent
             Dim objSchListGRR As SchListOfObjects
             Dim objSchComp2Ref As SchComponent2
             Dim objSchCompInst As SchComponent
```

```

```

```vbscript
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Ask application to create a component reference
             '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'---------------------------------------------------------------------
' Ask application to create a component reference
'---------------------------------------------------------------------
```

```

             objAppObjFact.AppCreateCompRef "CAASCHEDUCompressFunc", _
               objAppCompRef

```

```vbscript
             If ( Not ( objAppCompRef Is Nothing ) ) Then
               strMessage = strMessage &  "application reference component created" & vbCr
```

```vbscript
```vbscript
```vbscript
               '---------------------------------------------------------------------
               ' Find a unassociated component symbol in the document
               '---------------------------------------------------------------------
               Set objSchSymbol = GetComponentSymbol (objSchRoot)
               If ( Not ( objSchSymbol Is Nothing ) ) Then
                  Set objSchListGRR = objSchTempListFact.CreateListOfObjects
                  If ( Not ( objSchListGRR Is Nothing ) ) Then
```

```

```

```vbscript
If ( Not ( objSchSymbol Is Nothing ) ) Then
```vbscript
Set objSchListGRR = objSchTempListFact.CreateListOfObjects
```

```

If ( Not ( objSchListGRR Is Nothing ) ) Then
                     objSchListGRR.Append objSchSymbol
```vbscript
                     Set objSchCompRef = objSchBaseFact.CreateSchComponent ( _
                       objAppCompRef, objSchListGRR)
                     If ( Not ( objSchCompRef Is Nothing ) ) Then
                        strMessage = strMessage &  "schematic reference component attached" & vbCr
                     End If
```vbscript
```vbscript
                  End If
               End If
```

```

```

```vbscript
```vbscript
```vbscript
               '---------------------------------------------------------------------
               ' Add two connectors to the reference component
               '---------------------------------------------------------------------
               Dim objSchCntr As SchCompConnector
               Dim objSchAppCntr As SchAppConnector
               Dim objSchCntrLoc As SchCntrLocation

               Set objSchCntr = objSchRoot.GetInterface ("CATIASchCompConnector", _
```

```

```

```vbscript
Dim objSchCntrLoc As SchCntrLocation
```vbscript
Set objSchCntr = objSchRoot.GetInterface ("CATIASchCompConnector", _
```

                 objSchCompRef)

```

```vbscript
```vbscript
               If ( Not ( objSchCntr Is Nothing ) ) Then

                  Dim iCntr As Integer
```

```vbscript
```vbscript
                  Dim db2CntrPos (2) As CATSafeArrayVariant
                  Dim db2CntrVec (2) As CATSafeArrayVariant

```

```

```

```vbscript
                  For iCntr = 1 To 2
```vbscript
```vbscript
                    Set objSchCntrLoc = Nothing
                    Set objSchAppCntr = Nothing
```

```

```

```vbscript
```vbscript
```vbscript
                    '-------------------------------------------------------------
                    ' connector position and alignment vector are in coordinates
                    ' relative the origin of the reference component graphical
                    ' representation (the detail axis).
                    '-------------------------------------------------------------
                    If ( iCntr = 1 ) Then
```

```

```

```vbscript
```vbscript
```vbscript
' representation (the detail axis).
'-------------------------------------------------------------
If ( iCntr = 1 ) Then
```

                       db2CntrPos(0) = 15.0
                       db2CntrPos(1) = -5.0
                       db2CntrVec(0) = 1.0
                       db2CntrVec(1) = 0.0
```

                    Else
                       db2CntrPos(0) = -15.0
```vbscript
                       db2CntrPos(1) = -5.0
                       db2CntrVec(0) = -1.0
                       db2CntrVec(1) = 0.0
```vbscript
                    End If

```

```

```

```vbscript
db2CntrVec(1) = 0.0
```vbscript
End If
```

                    objSchCntr.AddConnector "CAASCHEDUConnector", objSchSymbol, _
                      Db2CntrPos, objSchAppCntr

```

```vbscript
                    If ( Not ( objSchAppCntr Is Nothing ) ) Then
```vbscript
                       Set objSchCntrLoc = objSchRoot.GetInterface ( _
```

```

                         "CATIASchCntrLocation", objSchAppCntr)
```vbscript
If ( Not ( objSchAppCntr Is Nothing ) ) Then
```vbscript
```vbscript
Set objSchCntrLoc = objSchRoot.GetInterface ( _
                       If ( Not ( objSchCntrLoc Is Nothing ) ) Then

```

```

```

```vbscript
If ( Not ( objSchCntrLoc Is Nothing ) ) Then
                          objSchCntrLoc.SetAlignVector objSchSymbol, Db2CntrVec

```

                          strMessage = strMessage &  "  connector " & iCntr & _

                            " created" & vbCr

```vbscript
                       End If
```vbscript
```vbscript
                    End If
                  Next

```

```

```

```vbscript
               End If '--- If ( Not ( objSchCntr Is Nothing ) ...
```

```vbscript
```vbscript
```vbscript
               '-------------------------------------------------------------------
               ' Place an instance of reference just created in an empty space in
               ' the design document
               ' Note that the target document is an input to PlaceInSpace
               '-------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
               '-------------------------------------------------------------------
               ' Component instance (to be created below) orientation matrix.
               ' x-axis = (1.0,0.0)
               ' y-axis = (0.0,1.0)
               ' origin = (100.0,100.0)
               '-------------------------------------------------------------------
```

```

```

```vbscript
               Dim db6Matrix(6) As CATSafeArrayVariant
```vbscript
               db6Matrix(0)=1.0
               db6Matrix(1)=0.0
               db6Matrix(2)=0.0
               db6Matrix(3)=1.0
               db6Matrix(4)=100.0
               db6Matrix(5)=100.0

               Set objSchComp2Ref = objSchRoot.GetInterface ( _
```

```

                 "CATIASchComponent2",objAppCompRef)

```vbscript
```vbscript
               If ( Not ( objSchComp2Ref Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchComp2Ref Is Nothing ) ) Then
                  objSchComp2Ref.PlaceInSpace objSchSymbol,db6Matrix, _
                    objSchDoc,objSchCompInst

```

```vbscript
                  If ( Not ( objSchCompInst Is Nothing ) ) Then
                     strMessage = strMessage &  "Place component instance in space is successful" & vbCr
                  End If
```vbscript
```vbscript
               End If

```

```

```

```vbscript
```vbscript
             End If '--- If ( Not ( objAppCompRef Is Nothing ) ...

```

```

```vbscript
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Find the coordinates of the route point by asking an existing
             ' component instance for a nearest compatible connector (connector A
             ' on the component instance).
             '
             ' The position of connector A will be used to define
             ' the first route point. A extremity connector will be
             ' automatically created for the route
             ' at this start point (connector B).
             '
             ' Connect the route to the component using
             ' connector A and connector B.
             '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
             If ( Not  ( objSchCompInst Is Nothing ) ) Then

                Dim bCompatible As Boolean
```

```vbscript
```vbscript
                Dim objLCntrs As SchListOfObjects
                Dim objSchGRRCompInst As SchGRRComp
                Dim objSchCompGraphic As SchCompGraphic
                Dim objSchCompCompat As SchCompatible

                Set objSchCompGraphic = objSchRoot.GetInterface ( _
```

```

```

                  "CATIASchCompGraphic",objSchCompInst)
```vbscript
```vbscript
```vbscript
                '-------------------------------------------------------------------
                ' Get the image (ditto) of the component instance
                '-------------------------------------------------------------------
                If ( Not ( objSchCompGraphic Is Nothing ) ) Then
                   Set objSchGRRCompInst = GetComponentImage (objSchCompGraphic)
                End If

                Set objSchCompCompat = objSchRoot.GetInterface ( _
```

```

```

                 "CATIASchCompatible",objSchCompInst)

```vbscript
                If ( Not ( objSchCompCompat Is Nothing ) And _
```vbscript
                     Not ( objSchGRRCompInst Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchCompCompat Is Nothing ) And _
```

Not ( objSchGRRCompInst Is Nothing ) ) Then
                   objSchCompCompat.IsTargetOKForRoute "CAASCHEDUConnector", _
                     objSchGRRCompInst, objLCntrs, bCompatible

```vbscript
```vbscript
```vbscript
                   '---------------------------------------------------------------
                   '  IsTargetOKRoute returns a list of compatible connectors
                   '  on the target component if the component is compatible to
                   '  be connected to the start point of the route.
                   '---------------------------------------------------------------
```

```

```

```vbscript
                   Dim objSchGRRInst As SchGRR
```vbscript
```vbscript
                   Dim objAppCntrCompBest As SchAppConnector
                   Dim objLDbOut As SchListOfDoubles
                   Dim db2SelectPt(2) As CATSafeArrayVariant

```

```

```

```vbscript
Dim objLDbOut As SchListOfDoubles
```vbscript
Dim db2SelectPt(2) As CATSafeArrayVariant
                   db2SelectPt(0) = 130.0
                   db2SelectPt(1) = 110.0

```

```

```vbscript
                   Set objSchGRRInst = objSchRoot.GetInterface ( _
```

                     "CATIASchGRR",objSchGRRCompInst)

```vbscript
                   If ( Not ( objLCntrs Is Nothing ) And  _
```vbscript
                        Not ( objSchGRRInst Is Nothing ) And bCompatible ) Then
```

```

```vbscript
```vbscript
```vbscript
                      '------------------------------------------------------------
                      '  GetBestCntrForRoute returns a connector from
                      '  the output list that is closest
                      '  to a user selection point.
                      '------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'  the output list that is closest
'  to a user selection point.
'------------------------------------------------------------
```

```

                      objSchCompCompat.GetBestCntrForRoute db2SelectPt, _
                        objSchGRRInst, objLCntrs, objLDbOut, objAppCntrCompBest

                      Dim objAppRouteRef As AnyObject
```vbscript
```vbscript
                      Dim objSchRoute As AnyObject
                      Dim strLogLineID As String
                      Dim dbPtArray(6) As CATSafeArrayVariant
                      Dim objAppCntrRouteBest As SchAppConnector
                      Dim objAppConnection As SchAppConnection
                      Dim objRouteCntbl As SchAppConnectable
                      Dim IntNbCoord As Integer

```

```

```

```vbscript
Dim objRouteCntbl As SchAppConnectable
```vbscript
Dim IntNbCoord As Integer
                      dbPtArray(0) = 0.0
                      dbPtArray(1) = 0.0

```

```

                      IntNbCoord = objLDbOut.Count

```vbscript
                      If (IntNbCoord > 1) Then
```vbscript
                        dbPtArray(0) = objLDbOut.Item(1)
                        dbPtArray(1) = objLDbOut.Item(2)
```

                        strMessage = strMessage &  _
```

                          "Target is compatible for route " & vbCr
```vbscript
If (IntNbCoord > 1) Then
```

dbPtArray(0) = objLDbOut.Item(1)
```vbscript
dbPtArray(1) = objLDbOut.Item(2)
```

strMessage = strMessage &  _
                        strMessage = strMessage &  "Route point starts at " & _
                          dbPtArray(0) & " " & dbPtArray(1) & vbCr
```vbscript
```vbscript
                      End If

```

```

```vbscript
dbPtArray(0) & " " & dbPtArray(1) & vbCr
```vbscript
End If
                      dbPtArray(2) = dbPtArray(0) + 100.0
                      dbPtArray(3) = dbPtArray(1)
                      dbPtArray(4) = dbPtArray(2)
                      dbPtArray(5) = dbPtArray(1) + 60.0
```

```

```vbscript
```vbscript
```vbscript
                      '-------------------------------------------------------------
                      ' Ask application to create a route reference
                      '-------------------------------------------------------------
                      'strLogLineID = "U1-P101-2in-CS150R-FG"
```

```

                      strLogLineID = ""
```

```vbscript
```vbscript
```vbscript
'-------------------------------------------------------------
'strLogLineID = "U1-P101-2in-CS150R-FG"
```

```

strLogLineID = ""
                      objAppObjFact.AppCreateRoute "CAASCHEDUFuncString", _
                        objAppRouteRef, strLogLineID

```

```vbscript
                      If ( Not ( objAppCompRef Is Nothing ) ) Then
                        strMessage = strMessage &  _
```

                          "application reference route created" & vbCr

strMessage = strMessage &  _
                        objSchBaseFact.CreateSchRouteByPoints objAppRouteRef, _
                          dbPtArray, objSchRoute

```vbscript
                        If ( Not ( objSchRoute Is Nothing ) ) Then
                          strMessage = strMessage &  "schematic route created" & vbCr

                          Set objRouteCntbl = objSchRoot.GetInterface ( _
```

                            "CATIASchAppConnectable",objSchRoute)

strMessage = strMessage &  "schematic route created" & vbCr
```vbscript
Set objRouteCntbl = objSchRoot.GetInterface ( _
```vbscript
                          Set objAppCntrRouteBest = FindConnectorAtPosition ( _
                            dbPtArray(0), dbPtArray(1), objRouteCntbl, objSchRoot)

```

```

```vbscript
                          If ( Not (objAppCntrRouteBest Is Nothing ) And _
```vbscript
                               Not (objAppCntrCompBest Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
                             '-----------------------------------------------------
                             ' Connect "Connector A" to "Connector B"
                             '-----------------------------------------------------
                             Set objAppConnection = objAppCntrCompBest.AppConnect _
```

```

                               (objAppCntrRouteBest)
```

```vbscript
                             If ( Not ( objAppConnection Is Nothing ) ) Then
                                strMessage = strMessage & "route has been connected"
                                strMessage = strMessage & _
```

                                  " to component successfully" & vbCr

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
                   End If '--- If ( Not ( objLCntrs Is Nothing )...

```

```

```vbscript
```vbscript
                End If '--- If ( Not ( objSchCompCompat Is Nothing ) ...

```

```

```vbscript
```vbscript
             End If '--- If ( Not  ( objSchCompInst Is Nothing ) ...

```

```

```vbscript
```vbscript
           End If '--- If ( Not ( objAppObjFact Is Nothing )...

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
        MsgBox strMessage

```vbscript
    End Sub

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
    Private Function GetComponentSymbol (objSchRootArg As SchematicRoot) As AnyObject
       Dim objSchLSymbols As SchListOfObjects
```

```vbscript
```vbscript
       If ( Not ( objSchRootArg Is Nothing ) ) Then
          Set objSchLSymbols = objSchRootArg.GetUnassociatedSymbols
          If ( Not ( objSchLSymbols Is Nothing ) ) Then
             Set GetComponentSymbol = objSchLSymbols.Item (1,"CATIASchGRR")
          End If
       End If
```

```

    End Function
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

    Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRRComp
```

```vbscript
       Dim objSchLSymbols As SchListOfObjects
```vbscript
```vbscript
       If ( Not ( objSchCompGraphArg Is Nothing ) ) Then
          Set objSchLSymbols = objSchCompGraphArg.ListGraphicalImages
          If ( Not ( objSchLSymbols Is Nothing ) ) Then
             Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRRComp")
          End If
       End If
```

```

    End Function
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

    Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic) _
```

```vbscript
```vbscript
```vbscript
' | Returns: the route graphic primitives
' -----------------------------------------------------------------------------
```

```

Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic) _
      As SchGRR

       Dim objSchLGRR As SchListOfObjects
```vbscript
```vbscript
       If ( Not ( objSchRouteGraphArg Is Nothing ) ) Then
          Set objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives
          If ( Not ( objSchLGRR Is Nothing ) ) Then
             Set GetRoutePrimitives = objSchLGRR.Item (1,"CATIASchGRR")
          End If
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
    ' | Find a connector that matches the input x-y coordinates.
    ' | Input: dbXArg,dbYArg:  the x-y coordinates of the matching point
    ' |        objSchGRR: the graphic primitives of the route.
    ' |        objSchCntbl: the connectable to search for the connectors
    ' | Returns: the connector handle
    ' -----------------------------------------------------------------------------
```

```

    Private Function FindConnectorAtPosition ( dbXArg As Double, dbYArg As Double, _
```

```vbscript
```vbscript
```vbscript
' | Returns: the connector handle
' -----------------------------------------------------------------------------
```

```

Private Function FindConnectorAtPosition ( dbXArg As Double, dbYArg As Double, _
      objSchCntblArg As SchAppConnectable, _
      objSchRootArg As SchematicRoot ) As SchAppConnector

```

```vbscript
       Dim objLCntr As SchListOfObjects
```vbscript
```vbscript
       Dim objLFilter As CATIASchListOfBSTRs
       Dim objSchRouteGraphic As SchRouteGraphic
       Dim objGRR As SchGRR

```

```

```

```vbscript
       If ( Not ( objSchCntblArg Is Nothing ) And _
```vbscript
            Not ( objSchRootArg Is Nothing ) ) Then
```vbscript
          Set objLFilter = Nothing

          Set objLCntr = objSchCntblArg.AppListConnectors (objLFilter)

          Set objSchRouteGraphic = objSchRootArg.GetInterface ( _
```

```

```

            "CATIASchRouteGraphic", objSchCntblArg)
```vbscript
Set objLCntr = objSchCntblArg.AppListConnectors (objLFilter)
```vbscript
```vbscript
Set objSchRouteGraphic = objSchRootArg.GetInterface ( _
          If ( Not ( objSchRouteGraphic Is Nothing ) ) Then
             Set objGRR = GetRoutePrimitives (objSchRouteGraphic)
          End If
       End If '--- If ( Not ( objSchCntblArg Is Nothing ) ...

```

```

```

```vbscript
       If ( Not ( objLCntr Is Nothing )  And _
```vbscript
             Not ( objGRR Is Nothing ) ) Then

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

```vbscript
Dim dbXOut As Double
```vbscript
Dim dbYOut As Double
```

          intNbCntr = objLCntr.Count
```

```vbscript
          If (intNbCntr > 0) Then
```vbscript
```vbscript
             For iCntr = 1 To intNbCntr
               Set objCntrLoc = Nothing
               Set objLDbOut = Nothing

               Set objCntrLoc = objLCntr.Item (iCntr,"CATIASchCntrLocation")

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
                          Set FindConnectorAtPosition =  objSchRootArg.GetInterface ( _
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
    End Function

```
