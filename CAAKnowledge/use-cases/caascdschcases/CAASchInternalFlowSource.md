---
title: "CAASchInternalFlow.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIASchCompFlow", "CATIASchAppConnectable", "CAASchInternalFlow", "CAAScdSchUseCases", "CATIA", "CATIASchComponent", "CATIASchAppConnector", "CAASCH_Detail02"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInternalFlowSource.htm"
converted: "2026-05-11T17:31:51.394565"
---

    Option Explicit
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Add/List/Remove internal flows to reference component. 
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R15 
    ' *****************************************************************************
```

    
```vbscript
    Sub CATMain()
```vbscript
        ' ------------------------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
        End If
```vbscript
        ' ------------------------------------------------------------------------- 
        ' Open the schematic document 
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                "online\CAAScdSchUseCases\samples\CAASCH_Detail02.CATProduct")
    
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)
    
        Dim strMessage As String
    
```

        strMessage = _
          "--------------------------------------------------------------------" & vbCr
        strMessage = strMessage & _
          "Output traces from CAASchInternalFlow.CATScript" & vbCrLf
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
    
        Dim objLCompRefs As SchListOfObjects
        Dim objLCntr As SchListOfObjects
        Dim objCompRef As SchComponent
        Dim objCntbl As SchAppConnectable
        Dim objCompFlow As SchCompFlow
        Dim objSchTempListFact As SchTempListFactory
    
```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
    
           Set objSchTempListFact = objSchRoot.GetTemporaryListFactory
    
```

```vbscript
        End If
    
```

```vbscript
        If ( Not ( objSchRoot Is Nothing )  And _
             Not (objSchTempListFact Is Nothing ) ) Then
```vbscript
           '-----------------------------------------------------------------------
           ' Find a list of reference component in the model
           '-----------------------------------------------------------------------
           Set objLCompRefs = objSchRoot.GetRefComponents
```

    
```

```vbscript
           If ( Not ( objLCompRefs Is Nothing ) ) Then
    
              Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")
    
```

```vbscript
              If ( Not ( objCompRef Is Nothing ) ) Then
    
                  Set objCompFlow = objSchRoot.GetInterface ( _
                    "CATIASchCompFlow",objCompRef)
    
                  Set objCntbl = objSchRoot.GetInterface ( _
                    "CATIASchAppConnectable",objCompRef)
              End If 
    
```

```vbscript
              If ( Not ( objCntbl Is Nothing ) And _             
                   Not ( objCompFlow Is Nothing ) ) Then
```vbscript
                 '-----------------------------------------------------------------
                 ' Find all the connectors associated with the reference 
                 ' component
                 '----------------------------------------------------------------- 
                 Dim objLFilter As SchListOfBSTRs
                 Set objLFilter = Nothing
                 Set objLCntr = objCntbl.AppListConnectors (objLFilter)
                 '-----------------------------------------------------------------
                 ' Add internal flow to the reference component.
                 ' 2 pairs:
                 ' Flow 1: connector 1 to connector 2
                 ' Flow 2: connector 1 to connector 3
                 '-----------------------------------------------------------------
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

                 intNbCntr = objLCntr.Count
```vbscript
                 Set objLCntr1 = objSchTempListFact.CreateListOfObjects
                 Set objLCntr2 = objSchTempListFact.CreateListOfObjects
    
                 Set objCntr1 = Nothing
                 Set objCntr2 = Nothing
                 Set objCntr3 = Nothing
    
```

```vbscript
                 If ( intNbCntr > 0 ) Then Set objCntr1 = objLCntr.Item(1,"CATIASchAppConnector")
                 If ( intNbCntr > 1 ) Then Set objCntr2 = objLCntr.Item(2,"CATIASchAppConnector")
                 If ( intNbCntr > 2 ) Then Set objCntr3 = objLCntr.Item(3,"CATIASchAppConnector")
    
                 Set objFlow1 = Nothing
                 If ( Not objLCntr1 Is Nothing ) Then
                    If ( Not ( objCntr1 Is Nothing ) And _
                         Not ( objCntr2 Is Nothing ) ) Then
                       objLCntr1.Append (objCntr1)
                       objLCntr1.Append (objCntr2)
                       Set objFlow1 = objCompFlow.AddInternalFlow (objLCntr1)
                       If ( Not ( objFlow1 Is Nothing ) ) Then
                          strMessage = strMessage & _
                            "Internal flow between connector 1 and 2 created " & vbCr
                       End If 
                    End If 
                 End If '--- If ( Not objLCntr1 Is Nothing...
    
                 Set objFlow2 = Nothing
                 If ( Not objLCntr2 Is Nothing ) Then
                    If ( Not ( objCntr1 Is Nothing ) And _
                         Not ( objCntr3 Is Nothing ) ) Then
                       objLCntr2.Append (objCntr1)
                       objLCntr2.Append (objCntr3)
                       Set objFlow2 = objCompFlow.AddInternalFlow (objLCntr2)
                       If ( Not ( objFlow2 Is Nothing ) ) Then
                          strMessage = strMessage & _
                            "Internal flow between connector 1 and 3 created " & vbCr
                       End If 
                    End If 
                 End If '--- If ( Not objLCntr1 Is Nothing...
```vbscript
                 '-----------------------------------------------------------------
                 ' Return a list of all the internal flows 
                 ' associated to the reference component. There should be 2.
                 '-----------------------------------------------------------------
    
                 Set objLFlow = objCompFlow.ListInternalFlows 
    
                 Dim intNbFlow As Integer
                 If ( Not ( objLFlow Is Nothing ) ) Then
                    intNbFlow = objLFlow.Count
                    strMessage = strMessage & "Number of internal flows = " & intNbFlow & vbCr
```

    
```

```vbscript
                    If ( Not ( objFlow2 Is Nothing ) ) Then
```vbscript
                       '-----------------------------------------------------------------
                       ' Remove "Flow 2" from the reference component
                       '-----------------------------------------------------------------
```

                       objCompFlow.RemoveInternalFlow objFlow2
                    End If
                 End If 
```vbscript
                 '-----------------------------------------------------------------
                 ' Return a list of all the internal flows 
                 ' associated to the reference component. There should be 1.
                 '-----------------------------------------------------------------
                 Set objLFlow = Nothing
                 Set objLFlow = objCompFlow.ListInternalFlows 
                 If ( Not ( objLFlow Is Nothing ) ) Then
                    intNbFlow = objLFlow.Count
                    strMessage = strMessage & "Number of internal flows after calling RemoveInternalFlow" 
                    strMessage = strMessage & "  = " & intNbFlow & vbCr
                 End If
```

    
```

```vbscript
              End If
           End If 
    
```

```vbscript
        End If '--- If ( Not ( objSchRoot Is Nothing )...
    
```

        strMessage = strMessage & _
          "--------------------------------------------------------------------" & vbCr
        MsgBox strMessage
    
    
```vbscript
    End Sub
    
```

    
    

```