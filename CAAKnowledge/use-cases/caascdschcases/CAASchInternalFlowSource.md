---
title: "CAASchInternalFlow.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: "["CATIASchCompFlow", "CATIASchAppConnectable", "CAASchInternalFlow", "CAAScdSchUseCases", "CATIA", "CATIASchComponent", "CATIASchAppConnector", "CAASCH_Detail02"]"
source_file: "Doc/online/CAAScdSchUseCases/CAASchInternalFlowSource.htm"
converted: "2026-05-11T17:31:51.394565"
---
tags: ["CATIASchCompFlow", "CATIASchAppConnectable", "CAASchInternalFlow", "CAAScdSchUseCases", "CATIA", "CATIASchComponent", "CATIASchAppConnector", "CAASCH_Detail02"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInternalFlowSource.htmmd"
converted: "2026-05-11T17:31:51.394565"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Add/List/Remove internal flows to reference component.
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R15
    ' *****************************************************************************
```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```cpp
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
```cpp
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdSchUseCases/samples/CAASCH_Detail02.CATProduct")

```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```cpp
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

          "Output traces from CAASchInternalFlow.CATScript" & vbCrLf
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
        Dim objLCompRefs As SchListOfObjects
        Dim objLCntr As SchListOfObjects
        Dim objCompRef As SchComponent
        Dim objCntbl As SchAppConnectable
        Dim objCompFlow As SchCompFlow
        Dim objSchTempListFact As SchTempListFactory

```
```

```

```

```vbscript
```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then

```vbscript
           Set objSchTempListFact = objSchRoot.GetTemporaryListFactory

```
```

```

```vbscript
```vbscript
        End If

```

```

```vbscript
        If ( Not ( objSchRoot Is Nothing )  And _
```vbscript
             Not (objSchTempListFact Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Find a list of reference component in the model
           '-----------------------------------------------------------------------
```vbscript
           Set objLCompRefs = objSchRoot.GetRefComponents
```
```

```

```

```vbscript
```vbscript
           If ( Not ( objLCompRefs Is Nothing ) ) Then

```cpp
              Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")

```
```

```

```vbscript
```vbscript
              If ( Not ( objCompRef Is Nothing ) ) Then

```vbscript
                  Set objCompFlow = objSchRoot.GetInterface ( _
```
```

```

                    "CATIASchCompFlow",objCompRef)

```vbscript
If ( Not ( objCompRef Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
Set objCompFlow = objSchRoot.GetInterface ( _
                  Set objCntbl = objSchRoot.GetInterface ( _
```
```

```

```

                    "CATIASchAppConnectable",objCompRef)
```vbscript
```vbscript
Set objCompFlow = objSchRoot.GetInterface ( _
```vbscript
```
```vbscript
```vbscript
Set objCntbl = objSchRoot.GetInterface ( _
              End If
```

```

```

```

```vbscript
              If ( Not ( objCntbl Is Nothing ) And _
```vbscript
                   Not ( objCompFlow Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
                 '-----------------------------------------------------------------
                 ' Find all the connectors associated with the reference
                 ' component
                 '-----------------------------------------------------------------
```vbscript
                 Dim objLFilter As SchListOfBSTRs
                 Set objLFilter = Nothing
                 Set objLCntr = objCntbl.AppListConnectors (objLFilter)
                 '-----------------------------------------------------------------
```
                 ' Add internal flow to the reference component.
                 ' 2 pairs:
                 ' Flow 1: connector 1 to connector 2
                 ' Flow 2: connector 1 to connector 3
                 '-----------------------------------------------------------------
```vbscript
                 Dim intNbCntr As Integer
                 Dim objFlow1 As SchInternalFlow
                 Dim objFlow2 As SchInternalFlow
                 Dim objCntr1 As SchAppConnector
                 Dim objCntr2 As SchAppConnector
                 Dim objCntr3 As SchAppConnector
                 Dim objLCntr1 As SchListOfObjects
                 Dim objLCntr2 As SchListOfObjects
                 Dim objLFlow As SchListOfObjects
```
```

```

```

                 intNbCntr = objLCntr.Count
```vbscript
```vbscript
                 Set objLCntr1 = objSchTempListFact.CreateListOfObjects
```vbscript
```
```vbscript
```vbscript
                 Set objLCntr2 = objSchTempListFact.CreateListOfObjects

                 Set objCntr1 = Nothing
                 Set objCntr2 = Nothing
                 Set objCntr3 = Nothing

```
```

```

```

```vbscript
```cpp
                 If ( intNbCntr > 0 ) Then Set objCntr1 = objLCntr.Item(1,"CATIASchAppConnector")
```vbscript
```
```vbscript
```cpp
                 If ( intNbCntr > 1 ) Then Set objCntr2 = objLCntr.Item(2,"CATIASchAppConnector")
                 If ( intNbCntr > 2 ) Then Set objCntr3 = objLCntr.Item(3,"CATIASchAppConnector")

                 Set objFlow1 = Nothing
                 If ( Not objLCntr1 Is Nothing ) Then
```
                    If ( Not ( objCntr1 Is Nothing ) And _
```

                         Not ( objCntr2 Is Nothing ) ) Then
```

                       objLCntr1.Append (objCntr1)
                       objLCntr1.Append (objCntr2)
```vbscript
                       Set objFlow1 = objCompFlow.AddInternalFlow (objLCntr1)
```vbscript
```
                       If ( Not ( objFlow1 Is Nothing ) ) Then
```

                          strMessage = strMessage & _
```

                            "Internal flow between connector 1 and 2 created " & vbCr
objLCntr1.Append (objCntr2)
```vbscript
```vbscript
Set objFlow1 = objCompFlow.AddInternalFlow (objLCntr1)
```
```

If ( Not ( objFlow1 Is Nothing ) ) Then
strMessage = strMessage & _
```vbscript
                       End If
```vbscript
```vbscript
                    End If
                 End If '--- If ( Not objLCntr1 Is Nothing...

```vbscript
                 Set objFlow2 = Nothing
                 If ( Not objLCntr2 Is Nothing ) Then
```
                    If ( Not ( objCntr1 Is Nothing ) And _
```

                         Not ( objCntr3 Is Nothing ) ) Then
```

                       objLCntr2.Append (objCntr1)
                       objLCntr2.Append (objCntr3)
```vbscript
                       Set objFlow2 = objCompFlow.AddInternalFlow (objLCntr2)
```vbscript
```
                       If ( Not ( objFlow2 Is Nothing ) ) Then
```

                          strMessage = strMessage & _

```

                            "Internal flow between connector 1 and 3 created " & vbCr
objLCntr2.Append (objCntr3)
```vbscript
```vbscript
Set objFlow2 = objCompFlow.AddInternalFlow (objLCntr2)
```
```

If ( Not ( objFlow2 Is Nothing ) ) Then
strMessage = strMessage & _
```vbscript
                       End If
```vbscript
```vbscript
                    End If
                 End If '--- If ( Not objLCntr1 Is Nothing...

```

```

```

```vbscript
```vbscript
```vbscript
                 '-----------------------------------------------------------------
                 ' Return a list of all the internal flows
                 ' associated to the reference component. There should be 2.
                 '-----------------------------------------------------------------

```vbscript
                 Set objLFlow = objCompFlow.ListInternalFlows

                 Dim intNbFlow As Integer
                 If ( Not ( objLFlow Is Nothing ) ) Then
```
```

```

                    intNbFlow = objLFlow.Count
                    strMessage = strMessage & "Number of internal flows = " & intNbFlow & vbCr
```

```vbscript
                    If ( Not ( objFlow2 Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
                       '-----------------------------------------------------------------
                       ' Remove "Flow 2" from the reference component
                       '-----------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'-----------------------------------------------------------------
' Remove "Flow 2" from the reference component
'-----------------------------------------------------------------
```

```

                       objCompFlow.RemoveInternalFlow objFlow2
                    End If
```vbscript
                 End If
```

```

```vbscript
```vbscript
```vbscript
                 '-----------------------------------------------------------------
                 ' Return a list of all the internal flows
                 ' associated to the reference component. There should be 1.
                 '-----------------------------------------------------------------
```vbscript
                 Set objLFlow = Nothing
                 Set objLFlow = objCompFlow.ListInternalFlows
                 If ( Not ( objLFlow Is Nothing ) ) Then
```
```

```

                    intNbFlow = objLFlow.Count
                    strMessage = strMessage & "Number of internal flows after calling RemoveInternalFlow"
                    strMessage = strMessage & "  = " & intNbFlow & vbCr
                 End If
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
        End If '--- If ( Not ( objSchRoot Is Nothing )...

```

```

```vbscript
End If '--- If ( Not ( objSchRoot Is Nothing )...
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
