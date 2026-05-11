---
```vbscript
title: "CAASchNetwork.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIAProduct", "CATIASchNetworkAnalysis", "CAAScdSchUseCases", "CATIA", "CATIASchGRR", "CAASchNetwork", "CATIASchCompGraphic", "CAASCH_Network01", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchNetworkSource.htm"
converted: "2026-05-11T17:31:51.409527"
```

---
tags: ["CATIAProduct", "CATIASchNetworkAnalysis", "CAAScdSchUseCases", "CATIA", "CATIASchGRR", "CAASchNetwork", "CATIASchCompGraphic", "CAASCH_Network01", "CATIASchAppConnectable"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchNetworkSource.htm"
converted: "2026-05-11T17:31:51.409527"
    Option Explicit

```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Network analysis.
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R15 
    ' *****************************************************************************
    '------------------------------------------------------------------------------
    ' These variables are visible to private Sub and CATMain
    '------------------------------------------------------------------------------
```

```vbscript
    Dim objLGRR_g As SchListOfObjects
    Dim objLCntbl_g As SchListOfObjects

```

    Sub CATMain()

```vbscript
        ' ------------------------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```

        strMessage = strMessage &  "sDocPath = " & sDocPath

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,sDocPath,"No Doc Path Defined"
        End If
```

```vbscript
        ' ------------------------------------------------------------------------- 
        ' Open the schematic document 
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                "online\CAAScdSchUseCases\samples\CAASCH_Network01.CATProduct")

```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)

        Dim strMessage As String

```

```vbscript
Dim strMessage As String
        strMessage = _
```

          "--------------------------------------------------------------------" & vbCr
strMessage = _
        strMessage = strMessage & _

          "Output traces from CAASchNetwork.CATScript" & vbCrLf
strMessage = _
strMessage = strMessage & _
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

        Dim objSchBaseFact As SchBaseFactory
        Dim objSchTempListFact As SchTempListFactory
        Dim objLNetWork As SchListOfObjects

```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
           '-----------------------------------------------------------------------
           ' Get all the necessary factories.
           '-----------------------------------------------------------------------
           Set objSchBaseFact = objSchRoot.GetSchBaseFactory 
           Set objSchTempListFact = objSchRoot.GetTemporaryListFactory
```

```vbscript
           If ( Not ( objSchBaseFact Is Nothing )  And _
                Not ( objSchTempListFact Is Nothing ) ) Then
              Set objLCntbl_g = objSchTempListFact.CreateListOfObjects
              Set objLGRR_g = objSchTempListFact.CreateListOfObjects

```

```vbscript
              If ( Not ( objLCntbl_g Is Nothing )  And _
                   Not ( objLGRR_g Is Nothing ) ) Then
```

```vbscript
                 '-----------------------------------------------------------------
                 ' The following "Sub" will populate objLCntbl_g and objLGRR_g
                 '-----------------------------------------------------------------
```

```vbscript
'-----------------------------------------------------------------
' The following "Sub" will populate objLCntbl_g and objLGRR_g
'-----------------------------------------------------------------
                 Find2ComponentInst objSchRoot

                 Set objLNetWork = objSchBaseFact.CreateNetwork (objLCntbl_g, _
                   objLGRR_g) 

```

```vbscript
              End If
           End If '--- If ( Not ( objSchBaseFact Is Nothing )...
        End If '--- If ( Not ( objSchRoot Is Nothing )...

```

```vbscript
        If (  Not ( objLNetWork Is Nothing ) ) Then

           Dim intNbNet As Integer
           Dim intNetIndex As Integer
           Dim intNbMember As Integer
           Dim intMemIndex As Integer
           Dim objSchNet As SchNetworkAnalysis
           Dim objLNetMember As SchListOfObjects
           Dim objMemPrd As Product
           Dim strName As String

```

```vbscript
Dim objMemPrd As Product
Dim strName As String
           intNbNet = objLNetWork.Count
           strMessage = strMessage & "number of network found = " & intNbNet & vbCr
```

```vbscript
           '-----------------------------------------------------------------------
           ' Query the network members
           '-----------------------------------------------------------------------
```

```vbscript
           For intNetIndex = 1 To intNbNet 

```

```vbscript
For intNetIndex = 1 To intNbNet
             intNbMember = 0
```

```vbscript
             Set objLNetMember = Nothing

             Set objSchNet = objLNetWork.Item (intNetIndex,"CATIASchNetworkAnalysis")
```

```vbscript
             '---------------------------------------------------------------------
             '  Get the members of the list of connectables.
             '---------------------------------------------------------------------
             If ( Not ( objSchNet Is Nothing ) ) Then

                Set objLNetMember = objSchNet.ListNetworkObjects
```

```vbscript
             End If 

```

```vbscript
             If ( Not ( objLNetMember Is Nothing ) ) Then

```

```vbscript
If ( Not ( objLNetMember Is Nothing ) ) Then
                intNbMember = objLNetMember.Count

                strMessage = strMessage & "Network component list " & intNetIndex _
```

                  & " has " & intNbMember & " members" & vbCr

```vbscript
                For intMemIndex = 1 To intNbMember

                  Set objMemPrd = objLNetMember.Item (intMemIndex,"CATIAProduct")
                  strName = ""
                  If ( Not ( objMemPrd Is Nothing ) ) Then
                     strName = objMemPrd.Name
                     strMessage = strMessage & "...member " & intMemIndex _
```

                       & " = " & strName & vbCr  
strName = ""
If ( Not ( objMemPrd Is Nothing ) ) Then
strName = objMemPrd.Name
strMessage = strMessage & "...member " & intMemIndex _
                  End If 

                Next '--- For intMemIndex

```vbscript
             End If '--- If ( Not ( objLNetMember Is Nothing ) ...

```

```vbscript
             '---------------------------------------------------------------------
             '  Get the members of the list of extremities (routes).
             '---------------------------------------------------------------------
```

```vbscript
             If ( Not ( objSchNet Is Nothing ) ) Then

                Set objLNetMember = objSchNet.ListExtremityObjects

```

```vbscript
             End If 

```

```vbscript
             If ( Not ( objLNetMember Is Nothing ) ) Then

```

```vbscript
If ( Not ( objLNetMember Is Nothing ) ) Then
                intNbMember = objLNetMember.Count

                strMessage = strMessage & "Network route list " & intNetIndex _
```

                  & " has " & intNbMember & " members" & vbCr

```vbscript
                For intMemIndex = 1 To intNbMember

                  Set objMemPrd = objLNetMember.Item (intMemIndex,"CATIAProduct")
                  strName = ""
                  If ( Not ( objMemPrd Is Nothing ) ) Then
                     strName = objMemPrd.Name
                     strMessage = strMessage & "...member " & intMemIndex _
```

                       & " = " & strName & vbCr  
strName = ""
If ( Not ( objMemPrd Is Nothing ) ) Then
strName = objMemPrd.Name
strMessage = strMessage & "...member " & intMemIndex _
                  End If 

                Next '--- For intMemIndex

```vbscript
             End If '--- If ( Not ( objLNetMember Is Nothing ) ...

```

           Next '--- For intNetIndex
        End If '--- If ( Not ( objLNetWork Is Nothing ) ...

Next '--- For intNetIndex
End If '--- If ( Not ( objLNetWork Is Nothing ) ...
        strMessage = strMessage & _

          "--------------------------------------------------------------------" & vbCr
        MsgBox strMessage

    End Sub

```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find 2 components and their images.
    ' | Input: objSchRootArg:  the root of the document.
    ' | Returns: objLCntbl_g: a list of component instance objects
    ' |          objLGRR_g: a list of component instance image objects
    ' -----------------------------------------------------------------------------
    Private Sub Find2ComponentInst (objSchRootArg As SchematicRoot)
```

```vbscript
       If ( objLCntbl_g Is Nothing ) Then Exit Sub
       If ( objLGRR_g Is Nothing ) Then Exit Sub

       Dim objLCompInst As SchListOfObjects
       Dim intNbComp As Integer

```

```vbscript
       If ( Not ( objSchRootArg Is Nothing ) ) Then
          Set objLCompInst = objSchRootArg.GetComponents
          If ( Not ( objLCompInst Is Nothing ) ) Then
             intNbComp = objLCompInst.Count
          End If
       End If

       Dim intIndex As Integer
       Dim intNbFlow As Integer
       Dim objCntbl As SchConnectable
       Dim objGRR As SchGRR
       Dim objPrd As Product
       Dim strInstName As String
       Dim intFound As Integer
       Dim intNbFound As Integer

```

```vbscript
       If (Not ( objLCompInst Is Nothing ) ) Then
```

```vbscript
          '------------------------------------------------------------------------
          '  Loop through the members in the list and find 2 components that
          '  have "network" as part of the product instance names
          '------------------------------------------------------------------------
          intNbFound = 0
```

```vbscript
          For intIndex = 1 To intNbComp

```

```vbscript
For intIndex = 1 To intNbComp
            strInstName = ""
            intFound = 0

```

```vbscript
            Set objCntbl = objLCompInst.Item (intIndex,"CATIASchAppConnectable")

```

```vbscript
            If ( Not ( objCntbl Is Nothing ) ) Then

               Set objPrd = objSchRootArg.GetInterface ( _
```

                 "CATIAProduct", objCntbl)

```vbscript
               If ( Not ( objPrd Is Nothing ) ) Then
                  strInstName = objPrd.Name
                  intFound  = Instr (1, strInstName, "_Network", 1)  
               End If 

```

```vbscript
               If ( intFound > 0 ) Then
                 Dim ObjSchCompGraph As SchCompGraphic
                 Set objSchCompGraph = objSchRootArg.GetInterface ( _
```

                   "CATIASchCompGraphic",objCntbl)
```vbscript
If ( intFound > 0 ) Then
Dim ObjSchCompGraph As SchCompGraphic
Set objSchCompGraph = objSchRootArg.GetInterface ( _
                 Set objGRR = GetComponentImage (objSchCompGraph)

```

```vbscript
                 If ( ( Not ObjGRR Is Nothing ) ) Then
                    objLCntbl_g.Append objCntbl
                    objLGRR_g.Append objGRR
                    intNbFound = intNbFound + 1
                 End If 
               End If

```

```vbscript
               If ( intNbFound > 1 ) Then  Exit For           

```

```vbscript
            End If '--- If ( Not ( objCntbl Is Nothing ) ...

```

          Next

```vbscript
       End If '--- If (Not ( objLCompInst Is Nothing ) ...
    End Sub
```

```vbscript
    ' -----------------------------------------------------------------------------
    ' | Find the first symbol used for the input schematic component.
    ' | Input: objSchCompGraph:  the schematic component 
    ' |        (a CATIASchCompGraphic interface handle).
    ' | Returns: the component image (the symbol instance)
    ' -----------------------------------------------------------------------------
    Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRR
       Dim objSchLSymbols As SchListOfObjects
       If ( Not ( objSchCompGraphArg Is Nothing ) ) Then
          Set objSchLSymbols = objSchCompGraphArg.ListGraphicalImages
          If ( Not ( objSchLSymbols Is Nothing ) ) Then
             Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRR")
          End If
       End If
    End Function
```
