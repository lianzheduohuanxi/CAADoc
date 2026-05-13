---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdSchUseCases", "CAASCH_Delete01", "CATIASchAppConnector", "CATIASchAppConnectable", "CAASchDelete", "CATIASchRoute", "CATIAProduct", "CATIASchComponent"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchDeleteSource.htmmd"
converted: "2026-05-11T11:27:02.621659"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Delete objects.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************

```cpp
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
            "online/CAAScdSchUseCases/samples/CAASCH_Delete01.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessage As String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchDelete.CATScript" & vbCrLf

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
    Dim objSchBaseFact As SchBaseFactory

    If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
       Set objSchBaseFact = objSchRoot.GetSchBaseFactory 

       Dim objSchComp As SchComponent
       Dim objLRoutes As SchListOfObjects
       Dim intNbRouteBefore As Integer
       Dim intNbRouteAfter As Integer

```

       '-----------------------------------------------------------------------
       '  In this specific input model, we expects to find a component
       '  instance that has been inserted into a route.
       '
       '  After this component instance is deleted, the two routes on 
       '  each side of the deleted component will be concatenated by the
       '  system to become one. 
       '-----------------------------------------------------------------------
```vbscript
       Set objLRoutes = objSchRoot.GetRoutes
       If ( Not ( objLRoutes Is Nothing ) ) Then
```
          intNbRouteBefore = objLRoutes.Count
          strMessage = strMessage & "Number of routes in the model "
          strMessage = strMessage & "before deleting an inserted component " 
          strMessage = strMessage & " = " & intNbRouteBefore & vbCr
       End If 

       If ( Not ( objSchBaseFact Is Nothing ) ) Then

```vbscript
          Set objSchComp = FindComponentInst (objSchRoot)

          If ( Not ( objSchComp Is Nothing ) ) Then
```

             objSchBaseFact.DeleteObject objSchComp

             strMessage = strMessage & "Component instance deleted from the model " & vbCr

          End If 

       End If '--- If ( Not ( objSchBaseFact Is Nothing ...

       '-----------------------------------------------------------------------
       '  Concatenate the 2 members
       '  The first member will be extended and the 2 member will be
       '  deleted
       '-----------------------------------------------------------------------
```vbscript
       Set objLRoutes = objSchRoot.GetRoutes
       If ( Not ( objLRoutes Is Nothing ) ) Then
```
          intNbRouteAfter = objLRoutes.Count
          strMessage = strMessage & "Number of routes in the model "
          strMessage = strMessage & "after deleting an inserted component " 
          strMessage = strMessage & " = " & intNbRouteAfter & vbCr

```vbscript
          Dim objRoute1 As SchRoute
          Dim objRoute2 As SchRoute

          Dim objRCntbl1 As SchConnectable
          Dim objRCntbl2 As SchConnectable

          Dim objAppRCntr1 As SchAppConnector
          Dim objAppRCntr2 As SchAppConnector

          If ( intNbRouteAfter > 0 ) Then
```
```cpp
             Set objRoute1 = objLRoutes.Item (1, "CATIASchRoute")

             If ( Not ( objRoute1 Is Nothing ) ) Then
```
```cpp
                Set objRCntbl1 = objSchRoot.GetInterface ( _
                  "CATIASchAppConnectable", objRoute1)
```
                If ( Not ( objRCntbl1 Is Nothing ) ) Then
```cpp
                   Set objAppRCntr1 = FindOpenConnector (objSchRoot,objRCntbl1)
                   Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                End If
```
             End If
             If ( Not ( objRoute2 Is Nothing ) ) Then
```cpp
                Set objRCntbl2 = objSchRoot.GetInterface ( _
                  "CATIASchAppConnectable", objRoute2)
```
                If ( Not ( objRCntbl2 Is Nothing ) ) Then
```vbscript
                   Set objAppRCntr2 = FindOpenConnector (objSchRoot,objRCntbl2)
                End If
```
             End If

             If ( Not ( objRoute1 Is Nothing ) And _
                   Not ( objAppRCntr1 Is Nothing ) And _
                   Not ( objAppRCntr2 Is Nothing ) ) Then
```cpp
                Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                If ( Not ( objRoute2 Is Nothing ) ) Then
```
                    objRoute1.Concatenate objAppRCntr1, objRoute2, objAppRCntr2
                    strMessage = strMessage & "2 routes concatenated" & vbCr
                End If
             End If 
          End If 
       End If '--- If ( Not ( objLRoutes Is Nothing ) ...
       
    End If '--- If ( Not ( objSchRoot Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub

```

' -----------------------------------------------------------------------------
' | Find a component instance with a specific name 
' | (contains "delete" sub-string)
' | Input: objSchRootArg:  the root of the document.
' | Returns: a list schematic component handle
' -----------------------------------------------------------------------------
```vbscript
Private Function FindComponentInst (objSchRootArg As SchematicRoot) As SchComponent

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
   Dim objSchComp As SchComponent
   Dim objPrd As Product
   Dim strInstName As String
   Dim intFound As Integer

```

   If (Not ( objLCompInst Is Nothing ) ) Then

      '------------------------------------------------------------------------
      '  Loop through the members in the list and find s component that
      '  has"delete" as part of its product instance name
      '------------------------------------------------------------------------

      For intIndex = 1 To intNbComp

        intFound = 0
        strInstName = ""

```cpp
        Set objSchComp = objLCompInst.Item (intIndex,"CATIASchComponent")

        If ( Not ( objSchComp Is Nothing ) ) Then
```

```cpp
           Set objPrd = objSchRootArg.GetInterface ( _
             "CATIAProduct", objSchComp)
```

           If ( Not ( objPrd Is Nothing ) ) Then
              strInstName = objPrd.Name
              intFound  = Instr (1, strInstName, "_Delete", 1)  
           End If 

           If ( intFound > 0 ) Then

```cpp
              Set FindComponentInst = objSchRootArg.GetInterface ( _
                "CATIASchComponent", objSchComp)
```

              Exit For  
           End If          

        End If '--- If ( Not ( objSchComp Is Nothing ) ...

      Next

   End If '--- If (Not ( objLCompInst Is Nothing ) ...
```vbscript
End Function

```

' -----------------------------------------------------------------------------
' | Find a connector in a route that is not connected to another object.
' | Input: objSchRoute:  the route object.
' | Returns: the open connector
' -----------------------------------------------------------------------------
```vbscript
Private Function FindOpenConnector (objSchRootArg As SchematicRootArg, _
  objRCntblArg As SchAppConnectable) As SchAppConnector
```

```vbscript
   Dim objLAppCntr As SchListOfObjects
   Dim intNbCntr As Integer
   Dim objLFilter As SchListOfBSTRs
   Set objLFilter = Nothing

   If ( Not ( objRCntblArg Is Nothing ) ) Then
```
```vbscript
      Set objLAppCntr = objRCntblArg.AppListConnectors (objLFilter)
      If ( Not ( objLAppCntr Is Nothing ) ) Then
```
         intNbCntr = objLAppCntr.Count
      End If
   End If

```vbscript
   Dim intIndex As Integer
   Dim objAppCntr As SchAppConnector
   Dim bIsConnected As Boolean

```

   If (Not ( objLAppCntr Is Nothing ) And ( intNbCntr > 0 ) And _
       Not ( objSchRootArg Is Nothing ) ) Then

      '------------------------------------------------------------------------
      '  Loop through the members in the list and find an unconnected connector
      '------------------------------------------------------------------------

      For intIndex = 1 To intNbCntr

```cpp
        Set objAppCntr = objLAppCntr.Item (intIndex,"CATIASchAppConnector")

        If ( Not ( objAppCntr Is Nothing ) ) Then
```

           objAppCntr.AppIsCntrConnected bIsConnected

           If ( Not ( bIsConnected ) )Then

```cpp
              Set FindOpenConnector = objSchRootArg.GetInterface ( _
                "CATIASchAppConnector", objAppCntr)
```

              Exit For  
           End If          

        End If '--- If ( Not ( objAppCntr Is Nothing ) ...

      Next

   End If '--- If (Not ( objLAppCntr Is Nothing ) ...
```vbscript
End Function

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************
'   Purpose:      Delete objects.
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R15 
' *****************************************************************************

```cpp
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
            "online/CAAScdSchUseCases/samples/CAASCH_Delete01.CATProduct")
```

```cpp
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)

    Dim strMessage As String

```

    strMessage = _
      "--------------------------------------------------------------------" & vbCr
    strMessage = strMessage & _
      "Output traces from CAASchDelete.CATScript" & vbCrLf

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
    Dim objSchBaseFact As SchBaseFactory

    If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
       Set objSchBaseFact = objSchRoot.GetSchBaseFactory 

       Dim objSchComp As SchComponent
       Dim objLRoutes As SchListOfObjects
       Dim intNbRouteBefore As Integer
       Dim intNbRouteAfter As Integer

```

       '-----------------------------------------------------------------------
       '  In this specific input model, we expects to find a component
       '  instance that has been inserted into a route.
       '
       '  After this component instance is deleted, the two routes on 
       '  each side of the deleted component will be concatenated by the
       '  system to become one. 
       '-----------------------------------------------------------------------
```vbscript
       Set objLRoutes = objSchRoot.GetRoutes
       If ( Not ( objLRoutes Is Nothing ) ) Then
```
          intNbRouteBefore = objLRoutes.Count
          strMessage = strMessage & "Number of routes in the model "
          strMessage = strMessage & "before deleting an inserted component " 
          strMessage = strMessage & " = " & intNbRouteBefore & vbCr
       End If 

       If ( Not ( objSchBaseFact Is Nothing ) ) Then

```vbscript
          Set objSchComp = FindComponentInst (objSchRoot)

          If ( Not ( objSchComp Is Nothing ) ) Then
```

             objSchBaseFact.DeleteObject objSchComp

             strMessage = strMessage & "Component instance deleted from the model " & vbCr

          End If 

       End If '--- If ( Not ( objSchBaseFact Is Nothing ...

       '-----------------------------------------------------------------------
       '  Concatenate the 2 members
       '  The first member will be extended and the 2 member will be
       '  deleted
       '-----------------------------------------------------------------------
```vbscript
       Set objLRoutes = objSchRoot.GetRoutes
       If ( Not ( objLRoutes Is Nothing ) ) Then
```
          intNbRouteAfter = objLRoutes.Count
          strMessage = strMessage & "Number of routes in the model "
          strMessage = strMessage & "after deleting an inserted component " 
          strMessage = strMessage & " = " & intNbRouteAfter & vbCr

```vbscript
          Dim objRoute1 As SchRoute
          Dim objRoute2 As SchRoute

          Dim objRCntbl1 As SchConnectable
          Dim objRCntbl2 As SchConnectable

          Dim objAppRCntr1 As SchAppConnector
          Dim objAppRCntr2 As SchAppConnector

          If ( intNbRouteAfter &gt; 0 ) Then
```
```cpp
             Set objRoute1 = objLRoutes.Item (1, "CATIASchRoute")

             If ( Not ( objRoute1 Is Nothing ) ) Then
```
```cpp
                Set objRCntbl1 = objSchRoot.GetInterface ( _
                  "CATIASchAppConnectable", objRoute1)
```
                If ( Not ( objRCntbl1 Is Nothing ) ) Then
```cpp
                   Set objAppRCntr1 = FindOpenConnector (objSchRoot,objRCntbl1)
                   Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                End If
```
             End If
             If ( Not ( objRoute2 Is Nothing ) ) Then
```cpp
                Set objRCntbl2 = objSchRoot.GetInterface ( _
                  "CATIASchAppConnectable", objRoute2)
```
                If ( Not ( objRCntbl2 Is Nothing ) ) Then
```vbscript
                   Set objAppRCntr2 = FindOpenConnector (objSchRoot,objRCntbl2)
                End If
```
             End If

             If ( Not ( objRoute1 Is Nothing ) And _
                   Not ( objAppRCntr1 Is Nothing ) And _
                   Not ( objAppRCntr2 Is Nothing ) ) Then
```cpp
                Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                If ( Not ( objRoute2 Is Nothing ) ) Then
```
                    objRoute1.Concatenate objAppRCntr1, objRoute2, objAppRCntr2
                    strMessage = strMessage & "2 routes concatenated" & vbCr
                End If
             End If 
          End If 
       End If '--- If ( Not ( objLRoutes Is Nothing ) ...
       
    End If '--- If ( Not ( objSchRoot Is Nothing )...

    strMessage = strMessage & _
      "--------------------------------------------------------------------" & vbCr
```vbscript
    MsgBox strMessage

End Sub

```

' -----------------------------------------------------------------------------
' | Find a component instance with a specific name 
' | (contains "delete" sub-string)
' | Input: objSchRootArg:  the root of the document.
' | Returns: a list schematic component handle
' -----------------------------------------------------------------------------
```vbscript
Private Function FindComponentInst (objSchRootArg As SchematicRoot) As SchComponent

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
   Dim objSchComp As SchComponent
   Dim objPrd As Product
   Dim strInstName As String
   Dim intFound As Integer

```

   If (Not ( objLCompInst Is Nothing ) ) Then

      '------------------------------------------------------------------------
      '  Loop through the members in the list and find s component that
      '  has"delete" as part of its product instance name
      '------------------------------------------------------------------------

      For intIndex = 1 To intNbComp

        intFound = 0
        strInstName = ""

```cpp
        Set objSchComp = objLCompInst.Item (intIndex,"CATIASchComponent")

        If ( Not ( objSchComp Is Nothing ) ) Then
```

```cpp
           Set objPrd = objSchRootArg.GetInterface ( _
             "CATIAProduct", objSchComp)
```

           If ( Not ( objPrd Is Nothing ) ) Then
              strInstName = objPrd.Name
              intFound  = Instr (1, strInstName, "_Delete", 1)  
           End If 

           If ( intFound &gt; 0 ) Then

```cpp
              Set FindComponentInst = objSchRootArg.GetInterface ( _
                "CATIASchComponent", objSchComp)
```

              Exit For  
           End If          

        End If '--- If ( Not ( objSchComp Is Nothing ) ...

      Next

   End If '--- If (Not ( objLCompInst Is Nothing ) ...
```vbscript
End Function

```

' -----------------------------------------------------------------------------
' | Find a connector in a route that is not connected to another object.
' | Input: objSchRoute:  the route object.
' | Returns: the open connector
' -----------------------------------------------------------------------------
```vbscript
Private Function FindOpenConnector (objSchRootArg As SchematicRootArg, _
  objRCntblArg As SchAppConnectable) As SchAppConnector
```

```vbscript
   Dim objLAppCntr As SchListOfObjects
   Dim intNbCntr As Integer
   Dim objLFilter As SchListOfBSTRs
   Set objLFilter = Nothing

   If ( Not ( objRCntblArg Is Nothing ) ) Then
```
```vbscript
      Set objLAppCntr = objRCntblArg.AppListConnectors (objLFilter)
      If ( Not ( objLAppCntr Is Nothing ) ) Then
```
         intNbCntr = objLAppCntr.Count
      End If
   End If

```vbscript
   Dim intIndex As Integer
   Dim objAppCntr As SchAppConnector
   Dim bIsConnected As Boolean

```

   If (Not ( objLAppCntr Is Nothing ) And ( intNbCntr &gt; 0 ) And _
       Not ( objSchRootArg Is Nothing ) ) Then

      '------------------------------------------------------------------------
      '  Loop through the members in the list and find an unconnected connector
      '------------------------------------------------------------------------

      For intIndex = 1 To intNbCntr

```cpp
        Set objAppCntr = objLAppCntr.Item (intIndex,"CATIASchAppConnector")

        If ( Not ( objAppCntr Is Nothing ) ) Then
```

           objAppCntr.AppIsCntrConnected bIsConnected

           If ( Not ( bIsConnected ) )Then

```cpp
              Set FindOpenConnector = objSchRootArg.GetInterface ( _
                "CATIASchAppConnector", objAppCntr)
```

              Exit For  
           End If          

        End If '--- If ( Not ( objAppCntr Is Nothing ) ...

      Next

   End If '--- If (Not ( objLAppCntr Is Nothing ) ...
```vbscript
End Function
```
```