---
```vbscript
title: "CAASchDelete.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIAProduct", "CAASCH_Delete01", "CAAScdSchUseCases", "CAASchDelete", "CATIA", "CATIASchRoute", "CATIASchComponent", "CATIASchAppConnector", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchDeleteSource.htm"
converted: "2026-05-11T17:31:51.365141"
```

---
tags: ["CATIAProduct", "CAASCH_Delete01", "CAAScdSchUseCases", "CAASchDelete", "CATIA", "CATIASchRoute", "CATIASchComponent", "CATIASchAppConnector", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchDeleteSource.htm"
converted: "2026-05-11T17:31:51.365141"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Delete objects.
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

                "online\CAAScdSchUseCases\samples\CAASCH_Delete01.CATProduct")

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

          "Output traces from CAASchDelete.CATScript" & vbCrLf
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

        Dim objSchBaseFact As SchBaseFactory

```

```

```

```vbscript
```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then

           Set objSchBaseFact = objSchRoot.GetSchBaseFactory

           Dim objSchComp As SchComponent
```

```vbscript
```vbscript
           Dim objLRoutes As SchListOfObjects
           Dim intNbRouteBefore As Integer
           Dim intNbRouteAfter As Integer
```

```

```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           '  In this specific input model, we expects to find a component
           '  instance that has been inserted into a route.
           '
           '  After this component instance is deleted, the two routes on
           '  each side of the deleted component will be concatenated by the
           '  system to become one.
           '-----------------------------------------------------------------------
           Set objLRoutes = objSchRoot.GetRoutes
           If ( Not ( objLRoutes Is Nothing ) ) Then
```

```

              intNbRouteBefore = objLRoutes.Count
              strMessage = strMessage & "Number of routes in the model "
              strMessage = strMessage & "before deleting an inserted component "
              strMessage = strMessage & " = " & intNbRouteBefore & vbCr
           End If
```

```vbscript
```vbscript
           If ( Not ( objSchBaseFact Is Nothing ) ) Then

              Set objSchComp = FindComponentInst (objSchRoot)

```

```

```vbscript
```vbscript
              If ( Not ( objSchComp Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchComp Is Nothing ) ) Then
                 objSchBaseFact.DeleteObject objSchComp

```

                 strMessage = strMessage & "Component instance deleted from the model " & vbCr

```vbscript
```vbscript
              End If

```

```

```vbscript
           End If '--- If ( Not ( objSchBaseFact Is Nothing ...
```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           '  Concatenate the 2 members
           '  The first member will be extended and the 2 member will be
           '  deleted
           '-----------------------------------------------------------------------
           Set objLRoutes = objSchRoot.GetRoutes
           If ( Not ( objLRoutes Is Nothing ) ) Then
```

```

              intNbRouteAfter = objLRoutes.Count
              strMessage = strMessage & "Number of routes in the model "
              strMessage = strMessage & "after deleting an inserted component "
              strMessage = strMessage & " = " & intNbRouteAfter & vbCr

              Dim objRoute1 As SchRoute
```vbscript
```vbscript
              Dim objRoute2 As SchRoute

              Dim objRCntbl1 As SchConnectable
              Dim objRCntbl2 As SchConnectable

              Dim objAppRCntr1 As SchAppConnector
              Dim objAppRCntr2 As SchAppConnector
```

```

```

```vbscript
              If ( intNbRouteAfter > 0 ) Then
```vbscript
```vbscript
                 Set objRoute1 = objLRoutes.Item (1, "CATIASchRoute")

```

```

```

```vbscript
                 If ( Not ( objRoute1 Is Nothing ) ) Then
```vbscript
                    Set objRCntbl1 = objSchRoot.GetInterface ( _
```

```

                      "CATIASchAppConnectable", objRoute1)
```vbscript
If ( Not ( objRoute1 Is Nothing ) ) Then
```vbscript
```vbscript
Set objRCntbl1 = objSchRoot.GetInterface ( _
                    If ( Not ( objRCntbl1 Is Nothing ) ) Then
                       Set objAppRCntr1 = FindOpenConnector (objSchRoot,objRCntbl1)
                       Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                    End If
                 End If
                 If ( Not ( objRoute2 Is Nothing ) ) Then
                    Set objRCntbl2 = objSchRoot.GetInterface ( _
```

```

```

                      "CATIASchAppConnectable", objRoute2)
```vbscript
End If
```

End If
```vbscript
If ( Not ( objRoute2 Is Nothing ) ) Then
```vbscript
```vbscript
Set objRCntbl2 = objSchRoot.GetInterface ( _
                    If ( Not ( objRCntbl2 Is Nothing ) ) Then
                       Set objAppRCntr2 = FindOpenConnector (objSchRoot,objRCntbl2)
                    End If
                 End If

```

```

```

```vbscript
                 If ( Not ( objRoute1 Is Nothing ) And _
```vbscript
                       Not ( objAppRCntr1 Is Nothing ) And _
                       Not ( objAppRCntr2 Is Nothing ) ) Then
```vbscript
                    Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                    If ( Not ( objRoute2 Is Nothing ) ) Then
```

```

                        objRoute1.Concatenate objAppRCntr1, objRoute2, objAppRCntr2
                        strMessage = strMessage & "2 routes concatenated" & vbCr
                    End If
```vbscript
```vbscript
                 End If
              End If
           End If '--- If ( Not ( objLRoutes Is Nothing ) ...

```

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
    ' | Find a component instance with a specific name
    ' | (contains "delete" sub-string)
    ' | Input: objSchRootArg:  the root of the document.
    ' | Returns: a list schematic component handle
    ' -----------------------------------------------------------------------------
```

```

```vbscript
    Private Function FindComponentInst (objSchRootArg As SchematicRoot) As SchComponent

       Dim objLCompInst As SchListOfObjects
```

```vbscript
       Dim intNbComp As Integer
```

```

```vbscript
       If ( Not ( objSchRootArg Is Nothing ) ) Then
```vbscript
```vbscript
          Set objLCompInst = objSchRootArg.GetComponents
          If ( Not ( objLCompInst Is Nothing ) ) Then
```

```

             intNbComp = objLCompInst.Count
          End If
```vbscript
```vbscript
       End If

       Dim intIndex As Integer
       Dim objSchComp As SchComponent
       Dim objPrd As Product
       Dim strInstName As String
       Dim intFound As Integer

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
          '  Loop through the members in the list and find s component that
          '  has"delete" as part of its product instance name
          '------------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
          For intIndex = 1 To intNbComp

```

```

```vbscript
For intIndex = 1 To intNbComp
            intFound = 0
            strInstName = ""

```

```vbscript
```vbscript
            Set objSchComp = objLCompInst.Item (intIndex,"CATIASchComponent")

```

```

```vbscript
```vbscript
            If ( Not ( objSchComp Is Nothing ) ) Then

               Set objPrd = objSchRootArg.GetInterface ( _
```

```

                 "CATIAProduct", objSchComp)

```vbscript
               If ( Not ( objPrd Is Nothing ) ) Then
                  strInstName = objPrd.Name
                  intFound  = Instr (1, strInstName, "_Delete", 1)
```vbscript
```vbscript
               End If

```

```

```

```vbscript
```vbscript
               If ( intFound > 0 ) Then

                  Set FindComponentInst = objSchRootArg.GetInterface ( _
```

```

                    "CATIASchComponent", objSchComp)

```vbscript
Set FindComponentInst = objSchRootArg.GetInterface ( _
                  Exit For
```vbscript
               End If

```

```

```vbscript
```vbscript
            End If '--- If ( Not ( objSchComp Is Nothing ) ...

```

```

```vbscript
          Next

```

```vbscript
```vbscript
       End If '--- If (Not ( objLCompInst Is Nothing ) ...
    End Function

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find a connector in a route that is not connected to another object.
    ' | Input: objSchRoute:  the route object.
    ' | Returns: the open connector
    ' -----------------------------------------------------------------------------
```

```

    Private Function FindOpenConnector (objSchRootArg As SchematicRootArg, _
```

```vbscript
```vbscript
```vbscript
' | Returns: the open connector
' -----------------------------------------------------------------------------
```

```

Private Function FindOpenConnector (objSchRootArg As SchematicRootArg, _
      objRCntblArg As SchAppConnectable) As SchAppConnector

```

```vbscript
       Dim objLAppCntr As SchListOfObjects
```vbscript
```vbscript
       Dim intNbCntr As Integer
       Dim objLFilter As SchListOfBSTRs
       Set objLFilter = Nothing

```

```

```

```vbscript
       If ( Not ( objRCntblArg Is Nothing ) ) Then
```vbscript
```vbscript
          Set objLAppCntr = objRCntblArg.AppListConnectors (objLFilter)
          If ( Not ( objLAppCntr Is Nothing ) ) Then
```

```

             intNbCntr = objLAppCntr.Count
          End If
```vbscript
```vbscript
       End If

       Dim intIndex As Integer
       Dim objAppCntr As SchAppConnector
       Dim bIsConnected As Boolean

```

```

```

```vbscript
       If (Not ( objLAppCntr Is Nothing ) And ( intNbCntr > 0 ) And _
```vbscript
           Not ( objSchRootArg Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
          '------------------------------------------------------------------------
          '  Loop through the members in the list and find an unconnected connector
          '------------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
          For intIndex = 1 To intNbCntr

            Set objAppCntr = objLAppCntr.Item (intIndex,"CATIASchAppConnector")

```

```

```vbscript
```vbscript
            If ( Not ( objAppCntr Is Nothing ) ) Then

```

```

               objAppCntr.AppIsCntrConnected bIsConnected

```vbscript
```vbscript
               If ( Not ( bIsConnected ) )Then

                  Set FindOpenConnector = objSchRootArg.GetInterface ( _
```

```

                    "CATIASchAppConnector", objAppCntr)

```vbscript
Set FindOpenConnector = objSchRootArg.GetInterface ( _
                  Exit For
```vbscript
               End If

```

```

```vbscript
```vbscript
            End If '--- If ( Not ( objAppCntr Is Nothing ) ...

```

```

```vbscript
          Next

```

```vbscript
```vbscript
       End If '--- If (Not ( objLAppCntr Is Nothing ) ...
    End Function

```

```
