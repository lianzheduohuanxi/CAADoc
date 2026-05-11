---
title: "CAASchQueryConnectivity.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_CompRoute01", "CATIAProduct", "CATIASchRouteGraphic", "CAAScdSchUseCases", "CATIA", "CATIASchCntrLocation", "CATIASchGRR", "CAASchQueryConnectivity", "CATIASchCompGraphic", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryConnectivitySource.md"
converted: "2026-05-11T17:31:51.471879"
---

    Option Explicit
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

```vbscript
    Dim strMessage_g As String
    
```

```vbscript
    Sub CATMain()
```vbscript
        ' ------------------------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
        End If
        ' ------------------------------------------------------------------------- 
        ' Open the schematic document 
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                "online\CAAScdSchUseCases\samples\CAASCH_CompRoute01.CATProduct")
    
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
          Set objPrdRoot = objSchDoc.Product 
          If ( Not ( objPrdRoot Is Nothing ) ) Then
            Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
          End If
        End If
    
        Dim objSchLComps As SchListOfObjects
        Dim objSchLRoutes As SchListOfObjects
    
```

```vbscript
        ' ------------------------------------------------------------------------- 
        ' |  Get a list of all component instances and
        ' |  a list of all route instances in the model.
        ' ------------------------------------------------------------------------- 
```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
           Set objSchLComps = objSchRoot.GetComponents
           Set objSchLRoutes = objSchRoot.GetRoutes
        End If
    
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
```vbscript
        ' ------------------------------------------------------------------------- 
        ' |  For each component instance in the list, find connected objects
        ' ------------------------------------------------------------------------- 
        If ( Not ( objSchLComps Is Nothing ) And _
```

             Not ( objSchRoot Is Nothing ) ) Then
    
```

           intNb = objSchLComps.Count
           strMessage_g = strMessage_g &  "Number of schematic component instances = " & intNb & vbCrLf
```vbscript
           If (intNb > 0) Then
              strMessage_g = strMessage_g &  "-----------Component Connectivity report ------------------- " _
                & vbCrLf
    
```

```vbscript
              For intIndex = 1 To intNb
                Set objPrd = Nothing
                strName = ""
                Set objPrd = objSchLComps.Item (intIndex,"CATIAProduct")
                If ( Not ( objPrd Is Nothing ) ) Then
                   strName = objPrd.Name
                   strMessage_g = strMessage_g &  " member " & intIndex & _
                     "= " & strName & vbCr
                End If  
                
                Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)
    
```

```vbscript
                If ( Not ( objAppCntbl Is Nothing ) ) Then
    
```

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
    
```

```vbscript
                End If
                          
```

```vbscript
             Next '--- For intIndex = 1 To intNb
    
```

```vbscript
           End If ' --- If (intNb > 0) Then
    
```

```vbscript
        End If '--- If ( Not ( objSchLComps Is Nothing ) And ...
    
```

```vbscript
        ' ------------------------------------------------------------------------- 
        ' |  For each route instance in the list, find connected objects
        ' ------------------------------------------------------------------------- 
```

```vbscript
        If ( Not ( objSchLRoutes Is Nothing ) And _
             Not ( objSchRoot Is Nothing ) ) Then
    
```

           intNb = objSchLRoutes.Count
           strMessage_g = strMessage_g &  "Number of schematic route instances = " & intNb & vbCrLf
```vbscript
           If (intNb > 0) Then
              strMessage_g = strMessage_g &  "---------------- Route Connectivity report ------------------- " _
                & vbCrLf
    
```

```vbscript
              For intIndex = 1 To intNb
                Set objPrd = Nothing
                strName = ""
                Set objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")
                If ( Not ( objPrd Is Nothing ) ) Then
                   strName = objPrd.Name
                   strMessage_g = strMessage_g &  " member " & intIndex & _
                     "= " & strName & vbCr
                End If  
                
                Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)
    
```

```vbscript
                If ( Not ( objAppCntbl Is Nothing ) ) Then
    
                   Set objLFilter = Nothing
    
```

                   objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
                     objLCntrThis, objLCntrOther
    
                   GenerateALine objSchRoot, objLCntblOther, objLCntrOther
    
```vbscript
                   Set objLCntblOther = Nothing
                   Set objLCntrThis = Nothing
                   Set objLCntrOther = Nothing
    
```

```vbscript
                End If
                          
```

```vbscript
             Next '--- For intIndex = 1 To intNb
    
```

```vbscript
           End If ' --- If (intNb > 0) Then
    
```

```vbscript
        End If '--- If ( Not ( objSchLComps Is Nothing ) And ...
    
```

    
    
    
        strMessage_g = strMessage_g & _
          "--------------------------------------------------------------------" & vbCr
        MsgBox strMessage_g
    
```vbscript
    End Sub
    
```

    Private Sub GenerateALine (objSchRootArg As SchematicRoot, _
      objLCntblArg As SchListOfObjects, objLCntrArg As SchListOfObjects)
    
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

```vbscript
      If ( Not ( objLCntblArg Is Nothing ) And _
           Not ( objLCntrArg Is Nothing ) ) Then
    
```

         intNbCntbl = objLCntblArg.Count
         intNbCntr = objLCntrArg.Count
    
```vbscript
         If ( intNbCntbl = intNbCntr ) Then
    
```

```vbscript
            For intIndex = 1 To intNbCntbl
              Set objPrd = Nothing
              strName = ""
    
              Set objPrd = objLCntblArg.Item (intIndex,"CATIAProduct")
        
              Set objCntbl = objSchRootArg.GetInterface ("CATIASchAppConnectable",objPrd)
```vbscript
              '--------------------------------------------------------------------
              '  Report the name of the object connected 
              '--------------------------------------------------------------------
              If ( Not ( objPrd Is Nothing ) ) Then
                 strName = objPrd.Name
                 strMessage_g = strMessage_g &  "    connected to  " & intIndex  _
```

                    & strName 
              End If  
```vbscript
              '--------------------------------------------------------------------
              '  Report the location of the connection through the connector 
              '  position
              '--------------------------------------------------------------------
              Set objGRR = Nothing
              Set objGRR = GetImage (objSchRootArg, objCntbl)
```

    
```

```vbscript
              If ( Not ( objGRR Is Nothing ) ) Then
                 
                 Set objCntr = objLCntrArg.Item (intIndex,"CATIASchCntrLocation")
    
```

```vbscript
                 If ( Not ( objCntr Is Nothing ) ) Then
    
                    Set objLDb = Nothing
                    objCntr.GetPosition objGRR, objLDb
    
```

```vbscript
                    If ( Not ( objLDb Is Nothing ) ) Then
                       intNbCoord = objLDb.Count
                       If ( intNbCoord > 1 ) Then
                          dbX = objLDb.Item(1)
                          dbY = objLDb.Item(2)
                          strMessage_g = strMessage_g &  " at " & dbX & "," & dbY & vbCr
                       End If
                    End If 
    
```

```vbscript
                 End If
    
```

```vbscript
              End If '--- If ( Not ( objGRR Is Nothing ) ) Then ...
    
```

     
```vbscript
            Next '--- For intIndex = 1 To intNb
    
```

```vbscript
         End If '--- If ( intNbCntbl = intNbCntr ) Then ...
    
```

```vbscript
      End If '--- If ( Not ( objLCntblArg Is Nothing ) And ...
    
```

```vbscript
    End Sub
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find the first symbol used for the input schematic component.
    ' | Input: objSchCompGraph:  the schematic component 
    ' |        (a CATIASchCompGraphic interface handle).
    ' | Returns: the component image (the symbol instance)
    ' -----------------------------------------------------------------------------
    Private Function GetImage (objSchRootArg As SchematicRoot, _
```

      objSchCntblArg As SchAppConnectable) As SchGRR
    
      Dim objSchLImages As SchListOfObjects
      Dim objSchCompGraph As SchCompGraphic
      Dim objSchRouteGraph As SchRouteGraphic
      Dim ErrorCode As Integer
    
      Set objSchCompGraph = Nothing
      Set objSchRouteGraph = Nothing
    
```

```vbscript
      If ( Not ( objSchRootArg Is Nothing ) And _
           Not ( objSchCntblArg Is Nothing ) ) Then
    
```

```vbscript
         '-------------------------------------------------------------------------
         ' Input objSchCntblArg could be a route or a component.  If 
         ' objSchCntblArg is a component, we expect 
         ' Set objSchRouteGraph = objSchRootArg.GetInterface ( _
         '  "CATIASchRouteGraphic",objSchCntblArg) to fail
         ' Error handling is to call GetInterface again with "CATIASchCompGraphic"
         ' as input argument.
         '-------------------------------------------------------------------------
```

         On Error Resume Next
    
```vbscript
         Set objSchRouteGraph = objSchRootArg.GetInterface ( _
           "CATIASchRouteGraphic",objSchCntblArg)
    
         ErrorCode = Err.Number
         If (ErrorCode <> 0) Then
            On Error Goto 0
            If ( objSchRouteGraph Is Nothing ) Then
    
               Set objSchCompGraph = objSchRootArg.GetInterface ( _
                 "CATIASchCompGraphic",objSchCntblArg)
    
```

```vbscript
            End If
         End If
         On Error Goto 0
    
```

```vbscript
      End If
    
```

```vbscript
      If ( Not ( objSchCompGraph Is Nothing ) ) Then
          Set objSchLImages = objSchCompGraph.ListGraphicalImages
      Else 
         If ( Not ( objSchRouteGraph Is Nothing ) ) Then
           Set objSchLImages = objSchRouteGraph.ListGraphicalPrimitives
         End If 
      End If
    
```

```vbscript
      If ( Not ( objSchLImages Is Nothing ) ) Then
         Set GetImage = objSchLImages.Item (1,"CATIASchGRR")
      End If
    
```

```vbscript
    End Function
    
```

    
    

```