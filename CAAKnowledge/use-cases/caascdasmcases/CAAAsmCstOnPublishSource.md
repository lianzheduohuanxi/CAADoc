---
```vbscript
title: "CAAAsmCstOnPublish.CATScript"
category: "use-case"
module: "CAAScdAsmUseCases"
tags: ["CAAScdAsmUseCases", "CAAAsmCstOnPublish", "CATIA", "CATIAConstraints"]
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCstOnPublishSource.htmmd"
converted: "2026-05-11T17:31:50.854661"
```

---
tags: ["CAAScdAsmUseCases", "CAAAsmCstOnPublish", "CATIA", "CATIAConstraints"]
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCstOnPublishSource.htmmd"
converted: "2026-05-11T17:31:50.854661"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2001
    ' ***********************************************************************
    '   Purpose:      Creates constraints between assembly Parts using Publications
    '   Assumtions:   Looks for CstOnProduct.CATProduct in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R6
    ' ***********************************************************************

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
        ' -----------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```vbscript
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
        End If
```

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Open the Product document
```vbscript
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                     "online/CAAScdAsmUseCases/samples/CstOnPublish.CATProduct")

```vbscript
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```vbscript
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sFilePath)
    '
```
```

```

```

```vbscript
```vbscript
```vbscript
    ' --------------------------
    ' Get the different products
    ' --------------------------
```vbscript
    Dim oRootProduct As Product
    Set oRootProduct=CATIA.ActiveDocument.Product

    Dim oPlate As Product
    Set oPlate = CATIA.ActiveDocument.Product.Products.Item  ( "Plate.1" )

    Dim oScrew1 As Product
    Set oScrew1 = CATIA.ActiveDocument.Product.Products.Item  ( "Screw.1" )

    Dim oScrew2 As Product
    Set oScrew2 = CATIA.ActiveDocument.Product.Products.Item  ( "Screw.2" )
    ' --------------------------------------
```
    ' Declare variables to handle publications
    ' --------------------------------------
```vbscript
    Dim oPlatePub As Publication
    Dim oPlateRef As Reference

    Dim oScrewPub As Publication
    Dim oScrewRef As Reference
    ' --------------------------------------
```
    ' Get the Constraints collection
    ' --------------------------------------
```vbscript
    Dim oConstraints0 As Collection
    Set oConstraints0 = oRootProduct.Connections  ( "CATIAConstraints" )
    ' --------------------------------------
```
    ' Create offset constraint between plate
    ' top face and screws heads bottom faces
    ' --------------------------------------
    set oPlatePub = oPlate.Publications.Item("Top")
```vbscript
    Set oPlateRef = oPlatePub.Valuation
    '  ---> Plate/Top Screw1/HeadBottom
```

```vbscript
    Set oScrewPub = oScrew1.Publications.Item("HeadBottom")
    Set oScrewRef = oScrewPub.Valuation

    Dim oConstraint1 As Constraint
    Set oConstraint1 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef )
```
```

```

```

    oConstraint1.Dimension.Value = 2.000000
    oConstraint1.Orientation = CATCstOrientOpposite
```vbscript
```vbscript
    '  ---> Plate/Top Screw2/HeadBottom

```

```

```vbscript
```vbscript
    Set oScrewPub = oScrew2.Publications.Item("HeadBottom")
```vbscript
```
```vbscript
```vbscript
    Set oScrewRef = oScrewPub.Valuation

    Dim oConstraint2 As Constraint
    Set oConstraint2 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef )

```
```

```

```

```vbscript
```vbscript
Dim oConstraint2 As Constraint
```vbscript
```
```vbscript
Set oConstraint2 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef )
```
```

    oConstraint2.Dimension.Value = 2.000000
    oConstraint2.Orientation = CATCstOrientOpposite
```

```vbscript
```vbscript
```vbscript
    ' --------------------------------------------
    ' Create offset constraint between plate
    ' holes positioning points and screws axis
    ' --------------------------------------------
    '  ---> Plate/Hole1 Screw1/Axis

    set oPlatePub = oPlate.Publications.Item("Hole1")
```

```

```

```vbscript
```vbscript
```vbscript
    Set oPlateRef = oPlatePub.Valuation

    Set oScrewPub = oScrew1.Publications.Item("Axis")
```
```

```vbscript
```vbscript
```vbscript
    Set oScrewRef = oScrewPub.Valuation

    Dim oConstraint3 As Constraint
    Set oConstraint3 = oConstraints0.AddBiEltCst(catCstTypeOn, oPlateRef, oScrewRef )
    '  ---> Plate/Hole2 Screw2/Axis
```

```

```

```

```vbscript
```vbscript
Set oConstraint3 = oConstraints0.AddBiEltCst(catCstTypeOn, oPlateRef, oScrewRef )
```vbscript
```
```vbscript
'  ---> Plate/Hole2 Screw2/Axis
    set oPlatePub = oPlate.Publications.Item("Hole2")
```

```

```

```vbscript
```vbscript
```vbscript
    Set oPlateRef = oPlatePub.Valuation

    Set oScrewPub = oScrew2.Publications.Item("Axis")
```
```

```vbscript
```vbscript
```vbscript
    Set oScrewRef = oScrewPub.Valuation

    Dim oConstraint4 As Constraint
    Set oConstraint4 = oConstraints0.AddBiEltCst(catCstTypeOn, oPlateRef, oScrewRef )

```
```

```

```

```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Update the Product ..
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' --------------------------------------
' Update the Product ..
' --------------------------------------
```

```

    oRootProduct.Update

```vbscript
    MsgBox "Click OK to replace the screw by another standard screw ..."
```
```

```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Replace the screw by another one: constraints on
    ' published elements are autoatically reconnected ...
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
    Set oScrew1 = CATIA.ActiveDocument.Product.Products.ReplaceComponent ( _
          oScrew1,                                                         _
```
          sDocPath & "/online/CAAScdAsmUseCases/samples/NewScrew.CATPart", _
          True)
```

```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Update the Product with the new Parts
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' --------------------------------------
' Update the Product with the new Parts
' --------------------------------------
```

```

    oRootProduct.Update

```

```vbscript
```vbscript
    End Sub

```
```
