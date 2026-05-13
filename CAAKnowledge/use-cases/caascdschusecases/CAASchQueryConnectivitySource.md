---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIASchGRR", "CATIA", "CAAScdSchUseCases", "CATIASchRouteGraphic", "CAASchQueryConnectivity", "CATIASchCompGraphic", "CAASCH_CompRoute01", "CATIASchAppConnectable", "CATIASchCntrLocation", "CATIAProduct"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryConnectivitySource.htmmd"
converted: "2026-05-11T11:27:02.639314"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Query the connectivity of components and routes in a network.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************

'--- strMessage_g is a global variable visible to all private Sub/Function
```vbscript
Dim strMessage_g As String

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
            "online/CAAScdSchUseCases/samples/CAASCH_CompRoute01.CATProduct")
```

```vbscript
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

```

    strMessage_g = _
      "--------------------------------------------------------------------" & vbCr
    strMessage_g = strMessage_g & _
      "Output traces from CAASchQueryConnectivity.CATScript" & vbCrLf

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
    Dim objSchLComps As SchListOfObjects
    Dim objSchLRoutes As SchListOfObjects

```

    ' ------------------------------------------------------------------------- 
    ' |  Get a list of all component instances and
    ' |  a list of all route instances in the model.
    ' ------------------------------------------------------------------------- 
    If ( Not ( objSchRoot Is Nothing ) ) Then
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

    ' ------------------------------------------------------------------------- 
    ' |  For each component instance in the list, find connected objects
    ' ------------------------------------------------------------------------- 
    If ( Not ( objSchLComps Is Nothing ) And _
         Not ( objSchRoot Is Nothing ) ) Then

       intNb = objSchLComps.Count
       strMessage_g = strMessage_g &  "Number of schematic component instances = " & intNb & vbCrLf
       If (intNb > 0) Then
          strMessage_g = strMessage_g &  "-----------Component Connectivity report ------------------- " _
            & vbCrLf

          For intIndex = 1 To intNb
```vbscript
            Set objPrd = Nothing
            strName = ""
```
```vbscript
            Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
            If ( Not ( objPrd Is Nothing ) ) Then
```
               strName = objPrd.Name
               strMessage_g = strMessage_g &  " member " & intIndex & _
                 "= " & strName & vbCr
            End If  
            
```vbscript
            Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

            If ( Not ( objAppCntbl Is Nothing ) ) Then
```

 
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

```vbscript
               Set objLFilter = Nothing

```

               objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
                 objLCntrThis, objLCntrOther

               GenerateALine objSchRoot, objLCntblOther, objLCntrOther

```vbscript
               Set objLCntblOther = Nothing
               Set objLCntrThis = Nothing
               Set objLCntrOther = Nothing

            End If
```
                      
         Next '--- For intIndex = 1 To intNb

       End If ' --- If (intNb > 0) Then

    End If '--- If ( Not ( objSchLComps Is Nothing ) And ...

    ' ------------------------------------------------------------------------- 
    ' |  For each route instance in the list, find connected objects
    ' ------------------------------------------------------------------------- 
    If ( Not ( objSchLRoutes Is Nothing ) And _
         Not ( objSchRoot Is Nothing ) ) Then

       intNb = objSchLRoutes.Count
       strMessage_g = strMessage_g &  "Number of schematic route instances = " & intNb & vbCrLf
       If (intNb > 0) Then
          strMessage_g = strMessage_g &  "---------------- Route Connectivity report ------------------- " _
            & vbCrLf

          For intIndex = 1 To intNb
```vbscript
            Set objPrd = Nothing
            strName = ""
```
```vbscript
            Set objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")
            If ( Not ( objPrd Is Nothing ) ) Then
```
               strName = objPrd.Name
               strMessage_g = strMessage_g &  " member " & intIndex & _
                 "= " & strName & vbCr
            End If  
            
```vbscript
            Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

            If ( Not ( objAppCntbl Is Nothing ) ) Then
```

```vbscript
               Set objLFilter = Nothing

```

               objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
                 objLCntrThis, objLCntrOther

               GenerateALine objSchRoot, objLCntblOther, objLCntrOther

```vbscript
               Set objLCntblOther = Nothing
               Set objLCntrThis = Nothing
               Set objLCntrOther = Nothing

            End If
```
                      
         Next '--- For intIndex = 1 To intNb

       End If ' --- If (intNb > 0) Then

    End If '--- If ( Not ( objSchLComps Is Nothing ) And ...

    strMessage_g = strMessage_g & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage_g

End Sub

Private Sub GenerateALine (objSchRootArg As SchematicRoot, _
  objLCntblArg As SchListOfObjects, objLCntrArg As SchListOfObjects)
```

```vbscript
  Dim intNbCntbl As Integer
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

  If ( Not ( objLCntblArg Is Nothing ) And _
       Not ( objLCntrArg Is Nothing ) ) Then

     intNbCntbl = objLCntblArg.Count
     intNbCntr = objLCntrArg.Count

     If ( intNbCntbl = intNbCntr ) Then

        For intIndex = 1 To intNbCntbl
```vbscript
          Set objPrd = Nothing
          strName = ""
```

```vbscript
          Set objPrd = objLCntblArg.Item (intIndex,"CATIAProduct")
    
          Set objCntbl = objSchRootArg.GetInterface ("CATIASchAppConnectable",objPrd)

```

          '--------------------------------------------------------------------
          '  Report the name of the object connected 
          '--------------------------------------------------------------------
          If ( Not ( objPrd Is Nothing ) ) Then
             strName = objPrd.Name
             strMessage_g = strMessage_g &  "    connected to  " & intIndex  _
                & strName 
          End If  

          '--------------------------------------------------------------------
          '  Report the location of the connection through the connector 
          '  position
          '--------------------------------------------------------------------
```vbscript
          Set objGRR = Nothing
          Set objGRR = GetImage (objSchRootArg, objCntbl)

          If ( Not ( objGRR Is Nothing ) ) Then
```
             
```vbscript
             Set objCntr = objLCntrArg.Item (intIndex,"CATIASchCntrLocation")

             If ( Not ( objCntr Is Nothing ) ) Then
```

```vbscript
                Set objLDb = Nothing
                objCntr.GetPosition objGRR, objLDb
```

                If ( Not ( objLDb Is Nothing ) ) Then
                   intNbCoord = objLDb.Count
                   If ( intNbCoord > 1 ) Then
                      dbX = objLDb.Item(1)
                      dbY = objLDb.Item(2)
                      strMessage_g = strMessage_g &  " at " & dbX & "," & dbY & vbCr
                   End If
                End If 

             End If

          End If '--- If ( Not ( objGRR Is Nothing ) ) Then ...

 
        Next '--- For intIndex = 1 To intNb

     End If '--- If ( intNbCntbl = intNbCntr ) Then ...

  End If '--- If ( Not ( objLCntblArg Is Nothing ) And ...

```vbscript
End Sub

```

' -----------------------------------------------------------------------------
' | Find the first symbol used for the input schematic component.
' | Input: objSchCompGraph:  the schematic component 
' |        (a CATIASchCompGraphic interface handle).
' | Returns: the component image (the symbol instance)
' -----------------------------------------------------------------------------
```vbscript
Private Function GetImage (objSchRootArg As SchematicRoot, _
  objSchCntblArg As SchAppConnectable) As SchGRR
```

```vbscript
  Dim objSchLImages As SchListOfObjects
  Dim objSchCompGraph As SchCompGraphic
  Dim objSchRouteGraph As SchRouteGraphic
  Dim ErrorCode As Integer

  Set objSchCompGraph = Nothing
  Set objSchRouteGraph = Nothing

```

  If ( Not ( objSchRootArg Is Nothing ) And _
       Not ( objSchCntblArg Is Nothing ) ) Then

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
```vbscript
     On Error Resume Next

     Set objSchRouteGraph = objSchRootArg.GetInterface ( _
       "CATIASchRouteGraphic",objSchCntblArg)
```

     ErrorCode = Err.Number
     If (ErrorCode <> 0) Then
```vbscript
        On Error Goto 0
        If ( objSchRouteGraph Is Nothing ) Then
```

```vbscript
           Set objSchCompGraph = objSchRootArg.GetInterface ( _
             "CATIASchCompGraphic",objSchCntblArg)
```

        End If
     End If
```vbscript
     On Error Goto 0

  End If
```

  If ( Not ( objSchCompGraph Is Nothing ) ) Then
```vbscript
      Set objSchLImages = objSchCompGraph.ListGraphicalImages
  Else 
```
     If ( Not ( objSchRouteGraph Is Nothing ) ) Then
```vbscript
       Set objSchLImages = objSchRouteGraph.ListGraphicalPrimitives
     End If 
```
  End If

  If ( Not ( objSchLImages Is Nothing ) ) Then
```vbscript
     Set GetImage = objSchLImages.Item (1,"CATIASchGRR")
  End If
```

```vbscript
End Function

```

```vbscript
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Query the connectivity of components and routes in a network.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************

'--- strMessage_g is a global variable visible to all private Sub/Function
```vbscript
Dim strMessage_g As String

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
            "online/CAAScdSchUseCases/samples/CAASCH_CompRoute01.CATProduct")
```

```vbscript
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

```

    strMessage_g = _
      "--------------------------------------------------------------------" & vbCr
    strMessage_g = strMessage_g & _
      "Output traces from CAASchQueryConnectivity.CATScript" & vbCrLf

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
    Dim objSchLComps As SchListOfObjects
    Dim objSchLRoutes As SchListOfObjects

```

    ' ------------------------------------------------------------------------- 
    ' |  Get a list of all component instances and
    ' |  a list of all route instances in the model.
    ' ------------------------------------------------------------------------- 
    If ( Not ( objSchRoot Is Nothing ) ) Then
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

    ' ------------------------------------------------------------------------- 
    ' |  For each component instance in the list, find connected objects
    ' ------------------------------------------------------------------------- 
    If ( Not ( objSchLComps Is Nothing ) And _
         Not ( objSchRoot Is Nothing ) ) Then

       intNb = objSchLComps.Count
       strMessage_g = strMessage_g &  "Number of schematic component instances = " & intNb & vbCrLf
       If (intNb &gt; 0) Then
          strMessage_g = strMessage_g &  "-----------Component Connectivity report ------------------- " _
            & vbCrLf

          For intIndex = 1 To intNb
```vbscript
            Set objPrd = Nothing
            strName = ""
```
```vbscript
            Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
            If ( Not ( objPrd Is Nothing ) ) Then
```
               strName = objPrd.Name
               strMessage_g = strMessage_g &  " member " & intIndex & _
                 "= " & strName & vbCr
            End If  
            
```vbscript
            Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

            If ( Not ( objAppCntbl Is Nothing ) ) Then
```

 
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

```vbscript
               Set objLFilter = Nothing

```

               objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
                 objLCntrThis, objLCntrOther

               GenerateALine objSchRoot, objLCntblOther, objLCntrOther

```vbscript
               Set objLCntblOther = Nothing
               Set objLCntrThis = Nothing
               Set objLCntrOther = Nothing

            End If
```
                      
         Next '--- For intIndex = 1 To intNb

       End If ' --- If (intNb &gt; 0) Then

    End If '--- If ( Not ( objSchLComps Is Nothing ) And ...

    ' ------------------------------------------------------------------------- 
    ' |  For each route instance in the list, find connected objects
    ' ------------------------------------------------------------------------- 
    If ( Not ( objSchLRoutes Is Nothing ) And _
         Not ( objSchRoot Is Nothing ) ) Then

       intNb = objSchLRoutes.Count
       strMessage_g = strMessage_g &  "Number of schematic route instances = " & intNb & vbCrLf
       If (intNb &gt; 0) Then
          strMessage_g = strMessage_g &  "---------------- Route Connectivity report ------------------- " _
            & vbCrLf

          For intIndex = 1 To intNb
```vbscript
            Set objPrd = Nothing
            strName = ""
```
```vbscript
            Set objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")
            If ( Not ( objPrd Is Nothing ) ) Then
```
               strName = objPrd.Name
               strMessage_g = strMessage_g &  " member " & intIndex & _
                 "= " & strName & vbCr
            End If  
            
```vbscript
            Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

            If ( Not ( objAppCntbl Is Nothing ) ) Then
```

```vbscript
               Set objLFilter = Nothing

```

               objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
                 objLCntrThis, objLCntrOther

               GenerateALine objSchRoot, objLCntblOther, objLCntrOther

```vbscript
               Set objLCntblOther = Nothing
               Set objLCntrThis = Nothing
               Set objLCntrOther = Nothing

            End If
```
                      
         Next '--- For intIndex = 1 To intNb

       End If ' --- If (intNb &gt; 0) Then

    End If '--- If ( Not ( objSchLComps Is Nothing ) And ...

    strMessage_g = strMessage_g & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage_g

End Sub

Private Sub GenerateALine (objSchRootArg As SchematicRoot, _
  objLCntblArg As SchListOfObjects, objLCntrArg As SchListOfObjects)
```

```vbscript
  Dim intNbCntbl As Integer
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

  If ( Not ( objLCntblArg Is Nothing ) And _
       Not ( objLCntrArg Is Nothing ) ) Then

     intNbCntbl = objLCntblArg.Count
     intNbCntr = objLCntrArg.Count

     If ( intNbCntbl = intNbCntr ) Then

        For intIndex = 1 To intNbCntbl
```vbscript
          Set objPrd = Nothing
          strName = ""
```

```vbscript
          Set objPrd = objLCntblArg.Item (intIndex,"CATIAProduct")
    
          Set objCntbl = objSchRootArg.GetInterface ("CATIASchAppConnectable",objPrd)

```

          '--------------------------------------------------------------------
          '  Report the name of the object connected 
          '--------------------------------------------------------------------
          If ( Not ( objPrd Is Nothing ) ) Then
             strName = objPrd.Name
             strMessage_g = strMessage_g &  "    connected to  " & intIndex  _
                & strName 
          End If  

          '--------------------------------------------------------------------
          '  Report the location of the connection through the connector 
          '  position
          '--------------------------------------------------------------------
```vbscript
          Set objGRR = Nothing
          Set objGRR = GetImage (objSchRootArg, objCntbl)

          If ( Not ( objGRR Is Nothing ) ) Then
```
             
```vbscript
             Set objCntr = objLCntrArg.Item (intIndex,"CATIASchCntrLocation")

             If ( Not ( objCntr Is Nothing ) ) Then
```

```vbscript
                Set objLDb = Nothing
                objCntr.GetPosition objGRR, objLDb
```

                If ( Not ( objLDb Is Nothing ) ) Then
                   intNbCoord = objLDb.Count
                   If ( intNbCoord &gt; 1 ) Then
                      dbX = objLDb.Item(1)
                      dbY = objLDb.Item(2)
                      strMessage_g = strMessage_g &  " at " & dbX & "," & dbY & vbCr
                   End If
                End If 

             End If

          End If '--- If ( Not ( objGRR Is Nothing ) ) Then ...

 
        Next '--- For intIndex = 1 To intNb

     End If '--- If ( intNbCntbl = intNbCntr ) Then ...

  End If '--- If ( Not ( objLCntblArg Is Nothing ) And ...

```vbscript
End Sub

```

' -----------------------------------------------------------------------------
' | Find the first symbol used for the input schematic component.
' | Input: objSchCompGraph:  the schematic component 
' |        (a CATIASchCompGraphic interface handle).
' | Returns: the component image (the symbol instance)
' -----------------------------------------------------------------------------
```vbscript
Private Function GetImage (objSchRootArg As SchematicRoot, _
  objSchCntblArg As SchAppConnectable) As SchGRR
```

```vbscript
  Dim objSchLImages As SchListOfObjects
  Dim objSchCompGraph As SchCompGraphic
  Dim objSchRouteGraph As SchRouteGraphic
  Dim ErrorCode As Integer

  Set objSchCompGraph = Nothing
  Set objSchRouteGraph = Nothing

```

  If ( Not ( objSchRootArg Is Nothing ) And _
       Not ( objSchCntblArg Is Nothing ) ) Then

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
```vbscript
     On Error Resume Next

     Set objSchRouteGraph = objSchRootArg.GetInterface ( _
       "CATIASchRouteGraphic",objSchCntblArg)
```

     ErrorCode = Err.Number
     If (ErrorCode &lt;&gt; 0) Then
```vbscript
        On Error Goto 0
        If ( objSchRouteGraph Is Nothing ) Then
```

```vbscript
           Set objSchCompGraph = objSchRootArg.GetInterface ( _
             "CATIASchCompGraphic",objSchCntblArg)
```

        End If
     End If
```vbscript
     On Error Goto 0

  End If
```

  If ( Not ( objSchCompGraph Is Nothing ) ) Then
```vbscript
      Set objSchLImages = objSchCompGraph.ListGraphicalImages
  Else 
```
     If ( Not ( objSchRouteGraph Is Nothing ) ) Then
```vbscript
       Set objSchLImages = objSchRouteGraph.ListGraphicalPrimitives
     End If 
```
  End If

  If ( Not ( objSchLImages Is Nothing ) ) Then
```vbscript
     Set GetImage = objSchLImages.Item (1,"CATIASchGRR")
  End If
```

```vbscript
End Function
```
```