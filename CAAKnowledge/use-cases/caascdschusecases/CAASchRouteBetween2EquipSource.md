---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIASchGRR", "CAASCH_RouteBetween2Equip", "CATIA", "CAAScdSchUseCases", "CAASCHEDUFuncString", "CATIASchRouteGraphic", "CAASCHEDUConnector", "CATIASchListOfBSTRs", "CATIASchCompatible", "CATIASchAppConnector", "CATIASchCompGraphic", "CAASCHEDU_SamplePID", "CATIASchAppConnectable", "CATIASchCntrLocation", "CATIASchGRRComp", "CATIAProduct", "CAASchRouteBetween2Equip"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchRouteBetween2EquipSource.htmmd"
converted: "2026-05-11T11:27:02.636363"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Route a piping line function between two equipments.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************
'------------------------------------------------------------------------------
```cpp
' These variables are visible to private Sub and CATMain
'------------------------------------------------------------------------------
```
```cpp
Dim objLGRRComp_g As SchListOfObjects
Dim objLCompat_g As SchListOfObjects
Dim strMessage_g As String

Sub CATMain(#)

```

    ' ------------------------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,sDocPath,"No Doc Path Defined"
    End If
```

    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_RouteBetween2Equip.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

```

    strMessage_g = _
      "--------------------------------------------------------------------" & vbCr
    strMessage_g = strMessage_g & _
      "Output traces from CAASchRouteBetween2Equip.CATScript" & vbCrLf

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

    If ( Not ( objSchRoot Is Nothing ) ) Then

```vbscript
       Dim objSchTempListFact As SchTempListFactory

       Dim objSchCompCompatA As SchCompatible
       Dim objSchGRRCompA As SchGRRComp

       Dim objSchCompCompatB As SchCompatible
       Dim objSchGRRCompB As SchGRRComp

       Set objSchTempListFact = objSchRoot.GetTemporaryListFactory

       If ( Not ( objSchTempListFact Is Nothing )) Then
```
```vbscript
          Set objLCompat_g = objSchTempListFact.CreateListOfObjects
          Set objLGRRComp_g = objSchTempListFact.CreateListOfObjects
       End If
```

       If ( Not ( objLCompat_g Is Nothing )  And _
            Not ( objLGRRComp_g Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Find 2 component instances in the model
          '--------------------------------------------------------------------
          Find2ComponentInst objSchRoot

          '--------------------------------------------------------------------
          ' Route a line connecting its ends to each component
          '--------------------------------------------------------------------
          RouteLineBetween2Component objSchRoot

       End If

    End If '--- If ( Not ( objSchRoot Is Nothing )...

    strMessage_g = strMessage_g & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage_g

End Sub

```

' -----------------------------------------------------------------------------
' | Find the first symbol used for the input schematic component.
' | Input: objSchCompGraph:  the schematic component 
' |        (a CATIASchCompGraphic interface handle).
' | Returns: the component image (the symbol instance)
' -----------------------------------------------------------------------------
```vbscript
Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRRComp
   Dim objSchLSymbols As SchListOfObjects
   If ( Not ( objSchCompGraphArg Is Nothing ) ) Then
```
```vbscript
      Set objSchLSymbols = objSchCompGraphArg.ListGraphicalImages
      If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```cpp
         Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRRComp")
      End If
```
   End If
```vbscript
End Function

```

' -----------------------------------------------------------------------------
' | Find the first graphical primitives of an input route.
' | Input: objSchRouteGraph:  the schematic route
' |        (a CATIASchRouteGraphic interface handle).
' | Returns: the route graphic primitives
' -----------------------------------------------------------------------------
```vbscript
Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic) _
  As SchGRR
```

```vbscript
   Dim objSchLGRR As SchListOfObjects
   If ( Not ( objSchRouteGraphArg Is Nothing ) ) Then
```
```vbscript
      Set objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives
      If ( Not ( objSchLGRR Is Nothing ) ) Then
```
```cpp
         Set GetRoutePrimitives = objSchLGRR.Item (1,"CATIASchGRR")
      End If
```
   End If
```vbscript
End Function

```

' -----------------------------------------------------------------------------
' | Find a connector that matches the input x-y coordinates.
' | Input: dbXArg,dbYArg:  the x-y coordinates of the matching point
' |        objSchGRR: the graphic primitives of the route.
' |        objSchCntbl: the connectable to search for the connectors
' | Returns: the connector handle
' -----------------------------------------------------------------------------
```vbscript
Private Function FindConnectorAtPosition ( dbXArg As Double, dbYArg As Double, _
  objSchCntblArg As SchAppConnectable, _
```
  objSchRootArg As SchematicRoot ) As SchAppConnector

```cpp
   Dim objLCntr As SchListOfObjects
   Dim objLFilter As CATIASchListOfBSTRs
   Dim objSchRouteGraphic As SchRouteGraphic
   Dim objGRR As SchGRR

   If ( Not ( objSchCntblArg Is Nothing ) And _
```
        Not ( objSchRootArg Is Nothing ) ) Then
```cpp
      Set objLFilter = Nothing

      Set objLCntr = objSchCntblArg.AppListConnectors (objLFilter)

      Set objSchRouteGraphic = objSchRootArg.GetInterface ( _
        "CATIASchRouteGraphic", objSchCntblArg)
```
      If ( Not ( objSchRouteGraphic Is Nothing ) ) Then
```vbscript
         Set objGRR = GetRoutePrimitives (objSchRouteGraphic)
      End If
```
   End If '--- If ( Not ( objSchRoute Is Nothing ) ...

   If ( Not ( objLCntr Is Nothing )  And _
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

      intNbCntr = objLCntr.Count
      If (intNbCntr > 0) Then
         For iCntr = 1 To intNbCntr
```cpp
           Set objCntrLoc = Nothing
           Set objLDbOut = Nothing

           Set objCntrLoc = objLCntr.Item (iCntr,"CATIASchCntrLocation")

           If (Not ( objCntrLoc Is Nothing ) ) Then
```

              objCntrLoc.GetPosition objGRR,objLDbOut

              If ( Not ( objLDbOut Is Nothing ) ) Then
                 IntNbCoord = objLDbOut.Count
                 If (IntNbCoord > 1) Then
                   dbXOut = objLDbOut.Item(1)
                   dbYOut = objLDbOut.Item(2)
                   If ( ( dbXOut = dbXArg ) And _ 
                        ( dbYOut = dbYArg ) ) Then

```cpp
                      Set FindConnectorAtPosition =  objSchRootArg.GetInterface ( _
                         "CATIASchAppConnector", objCntrLoc )
```

                      Exit For

                   End If 
                 End If 
              End If
           End If '--- If (Not ( objCntrLoc Is Nothing ...
         Next ' --- For iCntr = 1 To intNbCntr ...
      End If '--- If (intNbCntr > 0) ...
   End If '--- If ( Not ( objLCntr Is Nothing ) ...

```vbscript
End Function

```

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
```vbscript
Private Sub Find2ComponentInst (objSchRootArg As SchematicRoot)

   If ( objLCompat_g Is Nothing ) Then Exit Sub
```
   If ( objLGRRComp_g Is Nothing ) Then Exit Sub

```vbscript
   Dim objLCompInst As SchListOfObjects
   Dim intNbComp As Integer

   If ( Not ( objSchRootArg Is Nothing ) ) Then
```
```vbscript
      Set objLCompInst = objSchRootArg.GetComponents
      If ( Not ( objLCompInst Is Nothing ) ) Then
```
         intNbComp = objLCompInst.Count
      End If
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

      '------------------------------------------------------------------------
      '  Loop through the members in the list and find 2 components that
      '  have "network" as part of the product instance names
      '------------------------------------------------------------------------
      intNbFound = 0
      intStoreIndex = 0
      strTgtFrom = "_Routefrom"
      strTgtTo = "_Routeto"

      For intIndex = 1 To intNbComp

        strInstName = ""
        intFound = 0

```cpp
        Set objCompCompat = objLCompInst.Item (intIndex,"CATIASchCompatible")

        If ( Not ( objCompCompat Is Nothing ) ) Then
```

```cpp
           Set objPrd = objSchRootArg.GetInterface ( _
             "CATIAProduct", objCompCompat)
```

           If ( Not ( objPrd Is Nothing ) ) Then
              strInstName = objPrd.Name
              intFound  = Instr (1, strInstName, strTgtFrom, 1) 
              If ( intFound < 1 ) Then
                 intFound  = Instr (1, strInstName, strTgtTo, 1) 
                 intStoreIndex = 2
              Else
                 intStoreIndex = 1
              End If   
           End If 

           If ( intFound > 0 ) Then

```cpp
             Dim ObjSchCompGraph As SchCompGraphic
             Set objSchCompGraph = objSchRootArg.GetInterface ( _
               "CATIASchCompGraphic",objCompCompat)
```
```vbscript
             Set objGRRComp = GetComponentImage (objSchCompGraph)

             If ( ( Not objGRRComp Is Nothing ) ) Then
```
                If ( intStoreIndex = 1 ) Then
```vbscript
                  Set objCompCompatFrom = objCompCompat
                  Set objGRRCompFrom = objGRRComp
                Else
```
```vbscript
                  Set objCompCompatTo = objCompCompat
                  Set objGRRCompTo = objGRRComp
                End If 
```
                intNbFound  = intNbFound + 1
             End If 
           End If

           If ( intNbFound > 1 ) Then  Exit For           

        End If '--- If ( Not ( objCompCompat Is Nothing ) ...

      Next

      If ( Not ( objCompCompatFrom Is Nothing ) And _
           Not ( objGRRCompFrom Is Nothing ) ) Then

         objLCompat_g.Append objCompCompatFrom
         objLGRRComp_g.Append objGRRCompFrom

      End If 

      If ( Not ( objCompCompatTo Is Nothing ) And _
           Not ( objGRRCompTo Is Nothing ) ) Then

         objLCompat_g.Append objCompCompatTo
         objLGRRComp_g.Append objGRRCompTo

      End If 

   End If '--- If (Not ( objLCompInst Is Nothing ) ...

```vbscript
End Sub

```

' -----------------------------------------------------------------------------
' | Route a line from member 1 in objLCompat_g to member 2 in objLCompat_g. 
' | These members are specific interface handle on 2 component instances.
' |
' | Input: objSchRootArg:  the root of the document.
' | Returns: objLCompat_g: a list of component instance objects
' |          objLGRRComp_g: a list of component instance image objects
' -----------------------------------------------------------------------------
```vbscript
Private Sub RouteLineBetween2Component (objSchRootArg As SchematicRoot)
   If ( objLCompat_g Is Nothing ) Then Exit Sub
```
   If ( objLGRRComp_g Is Nothing ) Then Exit Sub

```vbscript
   Dim intNbComp As Integer
   Dim intNbGRR As Integer
   Dim intIndex As Integer

```

   intNbComp = objLCompat_g.Count
   intNbGRR = objLGRRComp_g.Count

   If ( intNbComp <> 2 ) Then Exit Sub
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

```cpp
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

   For intIndex = 1 To 2
```
```cpp
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
         strName = objPrd.Name
         If ( intIndex = 1 ) Then
            strMessage_g = strMessage_g &  _
              "Routing from " &  strName & vbCr
         Else
            strMessage_g = strMessage_g &  _
              "Routing to " &  strName & vbCr
         End If 
      End If

      If ( Not ( objGRRComp Is Nothing ) And _
           Not ( objCompCompat Is Nothing ) ) Then

         '---------------------------------------------------------------------
         '  IsTargetOKRoute returns a list of compatible connectors
         '  on the target component is the component is compatible to
         '  to connected to the start point of the route.
         '---------------------------------------------------------------------
         objCompCompat.IsTargetOKForRoute "CAASCHEDUConnector", _
           objGRRComp, objLCntrs, bCompatible

```cpp
         Set objSchGRR = objSchRootArg.GetInterface ("CATIASchGRR",objGRRComp) 

```

         If ( Not ( objLCntrs Is Nothing ) And  _
              Not ( objSchGRR Is Nothing ) And bCompatible ) Then

            If ( intIndex = 1 ) Then
               db2SelectPt(0) = 83.75
               db2SelectPt(1) = 81.25
            Else 
               db2SelectPt(0) = 130.0
               db2SelectPt(1) = 100.0
            End If 

            '------------------------------------------------------------------
            '  GetBestCntrForRoute returns a connector from
            '  the output list that is closest 
            '  to a user selection point.
            '------------------------------------------------------------------
```vbscript
            Set objLDbOut = Nothing
            Set objAppCntrBest = Nothing
            objCompCompat.GetBestCntrForRoute db2SelectPt, _
```
              objSchGRR, objLCntrs, objLDbOut, objAppCntrBest
   
            IntNbCoord = objLDbOut.Count
            If (IntNbCoord > 1) Then
              db2CntrPt(0) = objLDbOut.Item(1)
              db2CntrPt(1) = objLDbOut.Item(2)

              If ( intIndex = 1 ) Then
                 db2CntrPt1(0) =  db2CntrPt(0)
                 db2CntrPt1(1) =  db2CntrPt(1)
```vbscript
                 Set objAppCntrCompBest1 = objAppCntrBest
                 strMessage_g = strMessage_g &  _
```
                   "Target is compatible for route " & vbCr
                 strMessage_g = strMessage_g &  "Route point starts at " & _
                   db2CntrPt(0) & " " & db2CntrPt(1) & vbCr
              Else
                 db2CntrPt2(0) =  db2CntrPt(0)
                 db2CntrPt2(1) =  db2CntrPt(1)
                 strMessage_g = strMessage_g &  _
                   "Target is compatible for route " & vbCr
                 strMessage_g = strMessage_g &  "Route point ends at " & _
                   db2CntrPt(0) & " " & db2CntrPt(1) & vbCr
```vbscript
                 Set objAppCntrCompBest2 = objAppCntrBest
              End If 
```
            End If '--- If (IntNbCoord > 1) Then

         End If '--- If ( Not ( objLCntrs Is Nothing ) And  _
      End If '--- If ( Not ( objGRRComp Is Nothing ) ...
   Next '--- For intIndex

```cpp
   Dim objAppRouteRef As AnyObject
   Dim objSchRoute As AnyObject
   Dim strLogLineID As String
   Dim dbPtArray(8) As CATSafeArrayVariant

   Dim objAppCntrRouteBest1 As SchAppConnector
   Dim objAppCntrRouteBest2 As SchAppConnector

   Dim objAppConnection As SchAppConnection
   Dim objRouteCntbl As SchAppConnectable

```

   dbPtArray(0) = db2CntrPt1(0)
   dbPtArray(1) = db2CntrPt1(1)

   dbPtArray(2) = (db2CntrPt1(0) + db2CntrPt2(0)) * 0.5
   dbPtArray(3) = db2CntrPt1(1)

   dbPtArray(4) = dbPtArray(2)
   dbPtArray(5) = db2CntrPt2(1)

   dbPtArray(6) = db2CntrPt2(0)
   dbPtArray(7) = db2CntrPt2(1)

   '---------------------------------------------------------------------------
   ' Ask application to create a route reference
   '---------------------------------------------------------------------------
   'Logical line concept not supported in sample application
   'So just send in a null string.
   'strLogLineID = ""
   objAppObjFact.AppCreateRoute "CAASCHEDUFuncString", _
     objAppRouteRef, strLogLineID      

   If ( Not ( objAppRouteRef Is Nothing ) ) Then
     strMessage_g = strMessage_g &  _
       "application reference route created" & vbCr

     objSchBaseFact.CreateSchRouteByPoints objAppRouteRef, _
       dbPtArray, objSchRoute  

     If ( Not ( objSchRoute Is Nothing ) ) Then
       strMessage_g = strMessage_g &  "schematic route created" & vbCr

```cpp
       Set objRouteCntbl = objSchRootArg.GetInterface ( _
         "CATIASchAppConnectable",objSchRoute)
```

       '-----------------------------------------------------------------------
       ' Find the connector of the route matching the 
       ' component connector position at each end
       '-----------------------------------------------------------------------

```vbscript
       Set objAppCntrRouteBest1 = FindConnectorAtPosition ( _
         db2CntrPt1(0), db2CntrPt1(1), objRouteCntbl, objSchRootArg)
```

```vbscript
       Set objAppCntrRouteBest2 = FindConnectorAtPosition ( _
         db2CntrPt2(0), db2CntrPt2(1), objRouteCntbl, objSchRootArg)
```

       '-----------------------------------------------------------------------
       ' Connect the route to the 2 components
       '-----------------------------------------------------------------------
       If ( Not (objAppCntrRouteBest1 Is Nothing ) And _
            Not (objAppCntrCompBest1 Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Connect start point of route to "*_from" component
          '--------------------------------------------------------------------
```vbscript
          Set objAppConnection = objAppCntrCompBest1.AppConnect _
            (objAppCntrRouteBest1)
```

          If ( Not ( objAppConnection Is Nothing ) ) Then
             strMessage_g = strMessage_g & "route has been connected"
             strMessage_g = strMessage_g & _
               " to _from component successfully" & vbCr
          End If 

       End If '--- If ( Not (objAppCntrRouteBest Is Nothing ) ...

       If ( Not (objAppCntrRouteBest2 Is Nothing ) And _
            Not (objAppCntrCompBest2 Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Connect end point of route to "*_to" component
          '--------------------------------------------------------------------
```vbscript
          Set objAppConnection = objAppCntrCompBest2.AppConnect _
            (objAppCntrRouteBest2)
```

          If ( Not ( objAppConnection Is Nothing ) ) Then
             strMessage_g = strMessage_g & "route has been connected"
             strMessage_g = strMessage_g & _
               " to _to component successfully" & vbCr
          End If 

       End If '--- If ( Not (objAppCntrRouteBest Is Nothing ) ...

     End If '--- If ( Not ( objSchRoute Is Nothing )...

   End If '--- If ( Not ( objAppCompRef Is Nothing ) ...

```vbscript
End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Route a piping line function between two equipments.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************
'------------------------------------------------------------------------------
```cpp
' These variables are visible to private Sub and CATMain
'------------------------------------------------------------------------------
```
```cpp
Dim objLGRRComp_g As SchListOfObjects
Dim objLCompat_g As SchListOfObjects
Dim strMessage_g As String

Sub CATMain(#)

```

    ' ------------------------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,sDocPath,"No Doc Path Defined"
    End If
```

    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_RouteBetween2Equip.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

```

    strMessage_g = _
      "--------------------------------------------------------------------" & vbCr
    strMessage_g = strMessage_g & _
      "Output traces from CAASchRouteBetween2Equip.CATScript" & vbCrLf

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

    If ( Not ( objSchRoot Is Nothing ) ) Then

```vbscript
       Dim objSchTempListFact As SchTempListFactory

       Dim objSchCompCompatA As SchCompatible
       Dim objSchGRRCompA As SchGRRComp

       Dim objSchCompCompatB As SchCompatible
       Dim objSchGRRCompB As SchGRRComp

       Set objSchTempListFact = objSchRoot.GetTemporaryListFactory

       If ( Not ( objSchTempListFact Is Nothing )) Then
```
```vbscript
          Set objLCompat_g = objSchTempListFact.CreateListOfObjects
          Set objLGRRComp_g = objSchTempListFact.CreateListOfObjects
       End If
```

       If ( Not ( objLCompat_g Is Nothing )  And _
            Not ( objLGRRComp_g Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Find 2 component instances in the model
          '--------------------------------------------------------------------
          Find2ComponentInst objSchRoot

          '--------------------------------------------------------------------
          ' Route a line connecting its ends to each component
          '--------------------------------------------------------------------
          RouteLineBetween2Component objSchRoot

       End If

    End If '--- If ( Not ( objSchRoot Is Nothing )...

    strMessage_g = strMessage_g & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage_g

End Sub

```

' -----------------------------------------------------------------------------
' | Find the first symbol used for the input schematic component.
' | Input: objSchCompGraph:  the schematic component 
' |        (a CATIASchCompGraphic interface handle).
' | Returns: the component image (the symbol instance)
' -----------------------------------------------------------------------------
```vbscript
Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRRComp
   Dim objSchLSymbols As SchListOfObjects
   If ( Not ( objSchCompGraphArg Is Nothing ) ) Then
```
```vbscript
      Set objSchLSymbols = objSchCompGraphArg.ListGraphicalImages
      If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```cpp
         Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRRComp")
      End If
```
   End If
```vbscript
End Function

```

' -----------------------------------------------------------------------------
' | Find the first graphical primitives of an input route.
' | Input: objSchRouteGraph:  the schematic route
' |        (a CATIASchRouteGraphic interface handle).
' | Returns: the route graphic primitives
' -----------------------------------------------------------------------------
```vbscript
Private Function GetRoutePrimitives (objSchRouteGraphArg As SchRouteGraphic) _
  As SchGRR
```

```vbscript
   Dim objSchLGRR As SchListOfObjects
   If ( Not ( objSchRouteGraphArg Is Nothing ) ) Then
```
```vbscript
      Set objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives
      If ( Not ( objSchLGRR Is Nothing ) ) Then
```
```cpp
         Set GetRoutePrimitives = objSchLGRR.Item (1,"CATIASchGRR")
      End If
```
   End If
```vbscript
End Function

```

' -----------------------------------------------------------------------------
' | Find a connector that matches the input x-y coordinates.
' | Input: dbXArg,dbYArg:  the x-y coordinates of the matching point
' |        objSchGRR: the graphic primitives of the route.
' |        objSchCntbl: the connectable to search for the connectors
' | Returns: the connector handle
' -----------------------------------------------------------------------------
```vbscript
Private Function FindConnectorAtPosition ( dbXArg As Double, dbYArg As Double, _
  objSchCntblArg As SchAppConnectable, _
```
  objSchRootArg As SchematicRoot ) As SchAppConnector

```cpp
   Dim objLCntr As SchListOfObjects
   Dim objLFilter As CATIASchListOfBSTRs
   Dim objSchRouteGraphic As SchRouteGraphic
   Dim objGRR As SchGRR

   If ( Not ( objSchCntblArg Is Nothing ) And _
```
        Not ( objSchRootArg Is Nothing ) ) Then
```cpp
      Set objLFilter = Nothing

      Set objLCntr = objSchCntblArg.AppListConnectors (objLFilter)

      Set objSchRouteGraphic = objSchRootArg.GetInterface ( _
        "CATIASchRouteGraphic", objSchCntblArg)
```
      If ( Not ( objSchRouteGraphic Is Nothing ) ) Then
```vbscript
         Set objGRR = GetRoutePrimitives (objSchRouteGraphic)
      End If
```
   End If '--- If ( Not ( objSchRoute Is Nothing ) ...

   If ( Not ( objLCntr Is Nothing )  And _
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

      intNbCntr = objLCntr.Count
      If (intNbCntr &gt; 0) Then
         For iCntr = 1 To intNbCntr
```cpp
           Set objCntrLoc = Nothing
           Set objLDbOut = Nothing

           Set objCntrLoc = objLCntr.Item (iCntr,"CATIASchCntrLocation")

           If (Not ( objCntrLoc Is Nothing ) ) Then
```

              objCntrLoc.GetPosition objGRR,objLDbOut

              If ( Not ( objLDbOut Is Nothing ) ) Then
                 IntNbCoord = objLDbOut.Count
                 If (IntNbCoord &gt; 1) Then
                   dbXOut = objLDbOut.Item(1)
                   dbYOut = objLDbOut.Item(2)
                   If ( ( dbXOut = dbXArg ) And _ 
                        ( dbYOut = dbYArg ) ) Then

```cpp
                      Set FindConnectorAtPosition =  objSchRootArg.GetInterface ( _
                         "CATIASchAppConnector", objCntrLoc )
```

                      Exit For

                   End If 
                 End If 
              End If
           End If '--- If (Not ( objCntrLoc Is Nothing ...
         Next ' --- For iCntr = 1 To intNbCntr ...
      End If '--- If (intNbCntr &gt; 0) ...
   End If '--- If ( Not ( objLCntr Is Nothing ) ...

```vbscript
End Function

```

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
```vbscript
Private Sub Find2ComponentInst (objSchRootArg As SchematicRoot)

   If ( objLCompat_g Is Nothing ) Then Exit Sub
```
   If ( objLGRRComp_g Is Nothing ) Then Exit Sub

```vbscript
   Dim objLCompInst As SchListOfObjects
   Dim intNbComp As Integer

   If ( Not ( objSchRootArg Is Nothing ) ) Then
```
```vbscript
      Set objLCompInst = objSchRootArg.GetComponents
      If ( Not ( objLCompInst Is Nothing ) ) Then
```
         intNbComp = objLCompInst.Count
      End If
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

      '------------------------------------------------------------------------
      '  Loop through the members in the list and find 2 components that
      '  have "network" as part of the product instance names
      '------------------------------------------------------------------------
      intNbFound = 0
      intStoreIndex = 0
      strTgtFrom = "_Routefrom"
      strTgtTo = "_Routeto"

      For intIndex = 1 To intNbComp

        strInstName = ""
        intFound = 0

```cpp
        Set objCompCompat = objLCompInst.Item (intIndex,"CATIASchCompatible")

        If ( Not ( objCompCompat Is Nothing ) ) Then
```

```cpp
           Set objPrd = objSchRootArg.GetInterface ( _
             "CATIAProduct", objCompCompat)
```

           If ( Not ( objPrd Is Nothing ) ) Then
              strInstName = objPrd.Name
              intFound  = Instr (1, strInstName, strTgtFrom, 1) 
              If ( intFound &lt; 1 ) Then
                 intFound  = Instr (1, strInstName, strTgtTo, 1) 
                 intStoreIndex = 2
              Else
                 intStoreIndex = 1
              End If   
           End If 

           If ( intFound &gt; 0 ) Then

```cpp
             Dim ObjSchCompGraph As SchCompGraphic
             Set objSchCompGraph = objSchRootArg.GetInterface ( _
               "CATIASchCompGraphic",objCompCompat)
```
```vbscript
             Set objGRRComp = GetComponentImage (objSchCompGraph)

             If ( ( Not objGRRComp Is Nothing ) ) Then
```
                If ( intStoreIndex = 1 ) Then
```vbscript
                  Set objCompCompatFrom = objCompCompat
                  Set objGRRCompFrom = objGRRComp
                Else
```
```vbscript
                  Set objCompCompatTo = objCompCompat
                  Set objGRRCompTo = objGRRComp
                End If 
```
                intNbFound  = intNbFound + 1
             End If 
           End If

           If ( intNbFound &gt; 1 ) Then  Exit For           

        End If '--- If ( Not ( objCompCompat Is Nothing ) ...

      Next

      If ( Not ( objCompCompatFrom Is Nothing ) And _
           Not ( objGRRCompFrom Is Nothing ) ) Then

         objLCompat_g.Append objCompCompatFrom
         objLGRRComp_g.Append objGRRCompFrom

      End If 

      If ( Not ( objCompCompatTo Is Nothing ) And _
           Not ( objGRRCompTo Is Nothing ) ) Then

         objLCompat_g.Append objCompCompatTo
         objLGRRComp_g.Append objGRRCompTo

      End If 

   End If '--- If (Not ( objLCompInst Is Nothing ) ...

```vbscript
End Sub

```

' -----------------------------------------------------------------------------
' | Route a line from member 1 in objLCompat_g to member 2 in objLCompat_g. 
' | These members are specific interface handle on 2 component instances.
' |
' | Input: objSchRootArg:  the root of the document.
' | Returns: objLCompat_g: a list of component instance objects
' |          objLGRRComp_g: a list of component instance image objects
' -----------------------------------------------------------------------------
```vbscript
Private Sub RouteLineBetween2Component (objSchRootArg As SchematicRoot)
   If ( objLCompat_g Is Nothing ) Then Exit Sub
```
   If ( objLGRRComp_g Is Nothing ) Then Exit Sub

```vbscript
   Dim intNbComp As Integer
   Dim intNbGRR As Integer
   Dim intIndex As Integer

```

   intNbComp = objLCompat_g.Count
   intNbGRR = objLGRRComp_g.Count

   If ( intNbComp &lt;&gt; 2 ) Then Exit Sub
   If ( intNbComp &lt;&gt; intNbGRR ) Then Exit Sub
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

```cpp
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

   For intIndex = 1 To 2
```
```cpp
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
         strName = objPrd.Name
         If ( intIndex = 1 ) Then
            strMessage_g = strMessage_g &  _
              "Routing from " &  strName & vbCr
         Else
            strMessage_g = strMessage_g &  _
              "Routing to " &  strName & vbCr
         End If 
      End If

      If ( Not ( objGRRComp Is Nothing ) And _
           Not ( objCompCompat Is Nothing ) ) Then

         '---------------------------------------------------------------------
         '  IsTargetOKRoute returns a list of compatible connectors
         '  on the target component is the component is compatible to
         '  to connected to the start point of the route.
         '---------------------------------------------------------------------
         objCompCompat.IsTargetOKForRoute "CAASCHEDUConnector", _
           objGRRComp, objLCntrs, bCompatible

```cpp
         Set objSchGRR = objSchRootArg.GetInterface ("CATIASchGRR",objGRRComp) 

```

         If ( Not ( objLCntrs Is Nothing ) And  _
              Not ( objSchGRR Is Nothing ) And bCompatible ) Then

            If ( intIndex = 1 ) Then
               db2SelectPt(0) = 83.75
               db2SelectPt(1) = 81.25
            Else 
               db2SelectPt(0) = 130.0
               db2SelectPt(1) = 100.0
            End If 

            '------------------------------------------------------------------
            '  GetBestCntrForRoute returns a connector from
            '  the output list that is closest 
            '  to a user selection point.
            '------------------------------------------------------------------
```vbscript
            Set objLDbOut = Nothing
            Set objAppCntrBest = Nothing
            objCompCompat.GetBestCntrForRoute db2SelectPt, _
```
              objSchGRR, objLCntrs, objLDbOut, objAppCntrBest
   
            IntNbCoord = objLDbOut.Count
            If (IntNbCoord &gt; 1) Then
              db2CntrPt(0) = objLDbOut.Item(1)
              db2CntrPt(1) = objLDbOut.Item(2)

              If ( intIndex = 1 ) Then
                 db2CntrPt1(0) =  db2CntrPt(0)
                 db2CntrPt1(1) =  db2CntrPt(1)
```vbscript
                 Set objAppCntrCompBest1 = objAppCntrBest
                 strMessage_g = strMessage_g &  _
```
                   "Target is compatible for route " & vbCr
                 strMessage_g = strMessage_g &  "Route point starts at " & _
                   db2CntrPt(0) & " " & db2CntrPt(1) & vbCr
              Else
                 db2CntrPt2(0) =  db2CntrPt(0)
                 db2CntrPt2(1) =  db2CntrPt(1)
                 strMessage_g = strMessage_g &  _
                   "Target is compatible for route " & vbCr
                 strMessage_g = strMessage_g &  "Route point ends at " & _
                   db2CntrPt(0) & " " & db2CntrPt(1) & vbCr
```vbscript
                 Set objAppCntrCompBest2 = objAppCntrBest
              End If 
```
            End If '--- If (IntNbCoord &gt; 1) Then

         End If '--- If ( Not ( objLCntrs Is Nothing ) And  _
      End If '--- If ( Not ( objGRRComp Is Nothing ) ...
   Next '--- For intIndex

```cpp
   Dim objAppRouteRef As AnyObject
   Dim objSchRoute As AnyObject
   Dim strLogLineID As String
   Dim dbPtArray(8) As CATSafeArrayVariant

   Dim objAppCntrRouteBest1 As SchAppConnector
   Dim objAppCntrRouteBest2 As SchAppConnector

   Dim objAppConnection As SchAppConnection
   Dim objRouteCntbl As SchAppConnectable

```

   dbPtArray(0) = db2CntrPt1(0)
   dbPtArray(1) = db2CntrPt1(1)

   dbPtArray(2) = (db2CntrPt1(0) + db2CntrPt2(0)) * 0.5
   dbPtArray(3) = db2CntrPt1(1)

   dbPtArray(4) = dbPtArray(2)
   dbPtArray(5) = db2CntrPt2(1)

   dbPtArray(6) = db2CntrPt2(0)
   dbPtArray(7) = db2CntrPt2(1)

   '---------------------------------------------------------------------------
   ' Ask application to create a route reference
   '---------------------------------------------------------------------------
   'Logical line concept not supported in sample application
   'So just send in a null string.
   'strLogLineID = ""
   objAppObjFact.AppCreateRoute "CAASCHEDUFuncString", _
     objAppRouteRef, strLogLineID      

   If ( Not ( objAppRouteRef Is Nothing ) ) Then
     strMessage_g = strMessage_g &  _
       "application reference route created" & vbCr

     objSchBaseFact.CreateSchRouteByPoints objAppRouteRef, _
       dbPtArray, objSchRoute  

     If ( Not ( objSchRoute Is Nothing ) ) Then
       strMessage_g = strMessage_g &  "schematic route created" & vbCr

```cpp
       Set objRouteCntbl = objSchRootArg.GetInterface ( _
         "CATIASchAppConnectable",objSchRoute)
```

       '-----------------------------------------------------------------------
       ' Find the connector of the route matching the 
       ' component connector position at each end
       '-----------------------------------------------------------------------

```vbscript
       Set objAppCntrRouteBest1 = FindConnectorAtPosition ( _
         db2CntrPt1(0), db2CntrPt1(1), objRouteCntbl, objSchRootArg)
```

```vbscript
       Set objAppCntrRouteBest2 = FindConnectorAtPosition ( _
         db2CntrPt2(0), db2CntrPt2(1), objRouteCntbl, objSchRootArg)
```

       '-----------------------------------------------------------------------
       ' Connect the route to the 2 components
       '-----------------------------------------------------------------------
       If ( Not (objAppCntrRouteBest1 Is Nothing ) And _
            Not (objAppCntrCompBest1 Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Connect start point of route to "*_from" component
          '--------------------------------------------------------------------
```vbscript
          Set objAppConnection = objAppCntrCompBest1.AppConnect _
            (objAppCntrRouteBest1)
```

          If ( Not ( objAppConnection Is Nothing ) ) Then
             strMessage_g = strMessage_g & "route has been connected"
             strMessage_g = strMessage_g & _
               " to _from component successfully" & vbCr
          End If 

       End If '--- If ( Not (objAppCntrRouteBest Is Nothing ) ...

       If ( Not (objAppCntrRouteBest2 Is Nothing ) And _
            Not (objAppCntrCompBest2 Is Nothing ) ) Then

          '--------------------------------------------------------------------
          ' Connect end point of route to "*_to" component
          '--------------------------------------------------------------------
```vbscript
          Set objAppConnection = objAppCntrCompBest2.AppConnect _
            (objAppCntrRouteBest2)
```

          If ( Not ( objAppConnection Is Nothing ) ) Then
             strMessage_g = strMessage_g & "route has been connected"
             strMessage_g = strMessage_g & _
               " to _to component successfully" & vbCr
          End If 

       End If '--- If ( Not (objAppCntrRouteBest Is Nothing ) ...

     End If '--- If ( Not ( objSchRoute Is Nothing )...

   End If '--- If ( Not ( objAppCompRef Is Nothing ) ...

```vbscript
End Sub
```
```