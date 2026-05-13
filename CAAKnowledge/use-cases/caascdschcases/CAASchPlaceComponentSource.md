---
```vbscript
title: "CAASchPlaceComponent.CATScript"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIASchCompatibility", "CAASCH_Sample", "CAASCH_RouteForPlacement2", "CAAScdSchUseCases", "CATIASchGRRComp", "CATIA", "CAASchPlaceComponent", "CATIASchCompatible", "CATIASchComponent", "CATIASchCompGraphic", "CATIASchComponent2"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchPlaceComponentSource.htmmd"
converted: "2026-05-11T17:31:51.438458"
```

---
tags: ["CATIASchCompatibility", "CAASCH_Sample", "CAASCH_RouteForPlacement2", "CAAScdSchUseCases", "CATIASchGRRComp", "CATIA", "CAASchPlaceComponent", "CATIASchCompatible", "CATIASchComponent", "CATIASchCompGraphic", "CATIASchComponent2"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchPlaceComponentSource.htmmd"
converted: "2026-05-11T17:31:51.438458"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2004
    ' *****************************************************************************
    '   Purpose:      Schematic component placement in free space and connected to
    '                 existing component.
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
        ' Open the schematic document
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
        ' Open main schematic P&ID; design document (for new component instances created here)
```vbscript
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdSchUseCases/samples/CAASCH_RouteForPlacement2.CATProduct")

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

          "Output traces from CAASchPlaceComponent.CATScript" & vbCrLf
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
        Dim objSchGRRCtlg As SchGRR
        Dim objSchCntblRef As SchAppConnectable
        Dim objSchComp2Ref As SchComponent2
        Dim objSchCompInstA As SchComponent
        Dim objSchGRRCompInstA As SchGRRComp
        Dim objSchCompGraphInstA As SchCompGraphic
        Dim objSchCompatInstA As SchCompatible
        Dim objSchCompInstB As SchComponent
```
```

```

```

```vbscript
```vbscript
```vbscript
        '--------------------------------------------------------------------------
        ' Component instance (to be created below) orientation matrix.
        ' x-axis = (1.0,0.0)
        ' y-axis = (0.0,1.0)
        ' origin = (100.0,300.0)
        '--------------------------------------------------------------------------
```vbscript
        Dim db6Array(6) As CATSafeArrayVariant
```
```

```

```

```vbscript
```vbscript
```vbscript
' origin = (100.0,300.0)
'--------------------------------------------------------------------------
```vbscript
Dim db6Array(6) As CATSafeArrayVariant
```
```

        db6Array(0)=1.0
        db6Array(1)=0.0
        db6Array(2)=0.0
        db6Array(3)=1.0
        db6Array(4)=145.0
        db6Array(5)=130.0

```

```

```vbscript
        If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Get the first symbol from component catalog.
           '-----------------------------------------------------------------------
```vbscript
           Set objSchGRRCtlg = objSchRoot.GetCompSymbolFromCatalog ("Blocking Valve",objSchCtlgDoc)
           If ( Not ( objSchGRRCtlg Is Nothing ) ) Then
```
```

```

             strMessage = strMessage &  "Got the first catalog symbol" & vbCr
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Get the owner of the first symbol. That is a reference component
             ' in the catalog.
             '---------------------------------------------------------------------
```vbscript
             Set objSchCntblRef = objSchGRRCtlg.GetSchObjOwner
             If ( Not ( objSchCntblRef Is Nothing ) ) Then
```
```

```

               strMessage = strMessage &  "Got catalog connectable of the first symbol" & vbCr
```vbscript
```vbscript
               '-------------------------------------------------------------------
               ' Place an instance of the catalog reference in an empty space in
               ' the design document
               ' Note that the target document is an input to PlaceInSpace
               '-------------------------------------------------------------------
```vbscript
               Set objSchComp2Ref = objSchRoot.GetInterface ("CATIASchComponent2",objSchCntblRef)
               If ( Not ( objSchComp2Ref Is Nothing ) ) Then
```
```

```

                  strMessage = strMessage &  "Got catalog component reference of the symbol" & vbCr
```

```vbscript
```vbscript
Set objSchComp2Ref = objSchRoot.GetInterface ("CATIASchComponent2",objSchCntblRef)
```
```

If ( Not ( objSchComp2Ref Is Nothing ) ) Then
strMessage = strMessage &  "Got catalog component reference of the symbol" & vbCr
                  objSchComp2Ref.PlaceInSpace objSchGRRCtlg,db6Array,objSchDoc,objSchCompInstA
```vbscript
                  If ( Not ( objSchCompInstA Is Nothing ) ) Then
                     strMessage = strMessage &  "Place component instance in space is successful" & vbCr
                  End If
```vbscript
```vbscript
               End If
             End If
           End If
```

```

```

```vbscript
```vbscript
```vbscript
           '-----------------------------------------------------------------------
           ' Get another symbol from component catalog.
           '-----------------------------------------------------------------------
```vbscript
           Dim objSchGRRCVCtlg As SchGRR
           Dim objSchCntblCVRef As SchAppConnectable
           Dim objSchCompCVRef As SchComponent

           Set objSchGRRCVCtlg = objSchRoot.GetCompSymbolFromCatalog ("Control Valve",objSchCtlgDoc)
           If ( Not ( objSchGRRCVCtlg Is Nothing ) ) Then
```
```

```

             strMessage = strMessage &  "Got the second catalog symbol" & vbCr
```vbscript
```vbscript
             '---------------------------------------------------------------------
             ' Get the owner of the second symbol. That is a reference component
             ' in the catalog.
             '---------------------------------------------------------------------
```vbscript
             Set objSchCntblCVRef = objSchGRRCVCtlg.GetSchObjOwner
             If ( Not ( objSchCntblCVRef Is Nothing ) ) Then
```
```

```

               strMessage = strMessage &  "Got catalog connectable of the second symbol" & vbCr
```vbscript
```vbscript
               '-------------------------------------------------------------------
               ' Place an instance of the second reference connecting it to the
               ' first one. That is to "place" a new instance B connecting to
               ' the existing instance A.
               '-------------------------------------------------------------------
```vbscript
               Dim objCompRefPlaceInfo As AnyObject
               Dim objCompatInfo As AnyObject
               Dim objFinalPlaceInfo As AnyObject
               Dim bYesCompat As Boolean
               Dim bFindAllSolutions As Boolean

               Set objSchCompCVRef = objSchRoot.GetInterface ("CATIASchComponent",objSchCntblCVRef)
               If ( Not ( objSchCompCVRef Is Nothing ) ) Then
```
```

```

                  strMessage = strMessage &  "Got catalog component reference of the second symbol" & vbCr
               End If
```vbscript
```vbscript
               '-------------------------------------------------------------------
               '  Preparing to place B on A.
               '  1- need to retreive a CATIASchCompatibility interface handle
               '     from the existing instance (objSchCompInstA), the one we have
               '     just placed in empty space.
               '  2- need to retreive the graphical image (symbol instance) of
               '     objSchCompInstA. This is needed for the compatibility
               '     checking.
               '     For this we need another interface handle: CATIASchCompGraphic
               '-------------------------------------------------------------------
```

```

```

```vbscript
               If ( Not ( objSchCompInstA Is Nothing ) ) Then
```vbscript
```vbscript
                  Set objSchCompatInstA = objSchRoot.GetInterface ("CATIASchCompatible", _
```
```

                    objSchCompInstA)
```vbscript
                  Set objSchCompGraphInstA = objSchRoot.GetInterface ("CATIASchCompGraphic", _
                    objSchCompInstA)
```
```vbscript
                  Set objSchGRRCompInstA = GetComponentImage (objSchCompGraphInstA)
```vbscript
```
```vbscript
               End If

```

```

```

```vbscript
               If ( Not ( objSchCompatInstA Is Nothing ) And _
```vbscript
                    Not ( objSchGRRCompInstA Is Nothing ) And _
                    Not ( objSchCompCVRef Is Nothing ) ) Then
```

```

```vbscript
```vbscript
```vbscript
                  '----------------------------------------------------------------
                  '  1- QueryConnectAbility.
                  '     Ask the reference of the new instance B for information
                  '     to use in compatibility checking. The objCompRefPlaceInfo
                  '     is an output and should be used as a "black box".
                  '     It is the input to the next call.
                  '
                  '  2- IsTargetOKForPlace
                  '     Check whether A is compatible to B in making a connection.
                  '     A is the first instance, it is the "target".
                  '     objCompatInfo is an output and should be used as
                  '     a "black box". It is an input to the next call.
                  '
                  '  3- GetBestFitPlaceInfo
                  '     Input the placement location, close to the x-y location of
                  '     the connector of objSchCompInstA (A) that you want to connect
                  '     B to.
                  '     objFinalPlaceInfo is an output and should be used as
                  '     a "black box". It is an input to the next call.
                  '
                  '  4- PlaceOnComponentWithInfo
                  '     Place a new instance with the black box info.
                  '
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

                  objSchCompatInstA.IsTargetOKForPlace objSchGRRCompInstA, _
                    objCompRefPlaceInfo, objCompatInfo, bYesCompat

```vbscript
```vbscript
                  Dim db2Pt(2) As CATSafeArrayVariant
```vbscript
```
```vbscript
                  '-- 6.50 is the relative x coordinate of the right connector
                  '-- from the symbol origin
```

                  db2Pt(0) = 145.0 + 5.00
                  db2Pt(1) = 130.0

```

```

```vbscript
                  If ( bYesCompat ) Then
                     strMessage = strMessage &  "Target is compatible" & vbCr
                     bFindAllSolutions = false
```vbscript
                     ' -- step 3
```

                     objSchCompatInstA.GetBestFitPlaceInfo db2Pt, objCompatInfo, _
                       objFinalPlaceInfo, bFindAllSolutions

```

```vbscript
                     If ( Not ( objFinalPlaceInfo is Nothing ) ) Then
```vbscript
```vbscript
                        ' -- step 4
```vbscript
                        Set objSchCompInstB = objSchCompCVRef.PlaceOnComponentWithInfo _
```
```

```

                          (objFinalPlaceInfo)

```

```vbscript
                        If ( Not ( objSchCompInstB is Nothing ) ) Then
                           strMessage = strMessage &  _
```

                             "Place a new component instance on another existing object is successful" & vbCr
```vbscript
If ( Not ( objSchCompInstB is Nothing ) ) Then
```

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
```vbscript
                  End If

```

```

```vbscript
```vbscript
               End If '----If ( Not ( objSchCompatInstA Is Nothing )...

```

```

```vbscript
             End If '---- If ( Not ( objSchCntblCVRef Is Nothing )...
```vbscript
```vbscript
           End If '---- If ( Not ( objSchGRRCVCtlg Is Nothing )...
        End If  '----If ( Not ( objSchRoot Is Nothing )...

```

```

```

```vbscript
End If '---- If ( Not ( objSchGRRCVCtlg Is Nothing )...
```

End If  '----If ( Not ( objSchRoot Is Nothing )...
        strMessage = strMessage & _

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
    ' | Find the first symbol used for the input schematic component.
    ' | Input: objSchCompGraphArg:  the schematic component
    ' |        (a CATIASchCompGraphic interface handle).
    ' | Returns: the component image (the symbol instance)
    ' -----------------------------------------------------------------------------
```

```

```vbscript
```vbscript
    Private Function GetComponentImage (objSchCompGraphArg As SchCompGraphic) As SchGRRComp
       Dim objSchLSymbols As SchListOfObjects
```
```

```vbscript
```vbscript
       If ( Not ( objSchCompGraphArg Is Nothing ) ) Then
```vbscript
          Set objSchLSymbols = objSchCompGraphArg.ListGraphicalImages
          If ( Not ( objSchLSymbols Is Nothing ) ) Then
```
```vbscript
             Set GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRRComp")
          End If
```
       End If
```

```

```vbscript
    End Function
```
```
