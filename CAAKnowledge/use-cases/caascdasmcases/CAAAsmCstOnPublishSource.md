---
title: "CAAAsmCstOnPublish.CATScript"
category: "use-case"
module: "CAAScdAsmUseCases"
tags: ["CAAScdAsmUseCases", "CAAAsmCstOnPublish", "CATIA", "CATIAConstraints"]
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCstOnPublishSource.md"
converted: "2026-05-11T17:31:50.854661"
---

    Option Explicit
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

    
```vbscript
    Sub CATMain()
    
```

```vbscript
        ' ----------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```vbscript
        ' ----------------------------------------------------------- 
        ' Open the Product document 
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                     "online\CAAScdAsmUseCases\samples\CstOnPublish.CATProduct")
    
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sFilePath)
    '
```vbscript
    ' --------------------------
    ' Get the different products
    ' --------------------------
    Dim oRootProduct As Product
    Set oRootProduct=CATIA.ActiveDocument.Product
    
    Dim oPlate As Product
    Set oPlate = CATIA.ActiveDocument.Product.Products.Item  ( "Plate.1" ) 
    
    Dim oScrew1 As Product
    Set oScrew1 = CATIA.ActiveDocument.Product.Products.Item  ( "Screw.1" ) 
    
    Dim oScrew2 As Product
    Set oScrew2 = CATIA.ActiveDocument.Product.Products.Item  ( "Screw.2" ) 
    ' --------------------------------------
    ' Declare variables to handle publications
    ' --------------------------------------
    Dim oPlatePub As Publication
    Dim oPlateRef As Reference
    
    Dim oScrewPub As Publication
    Dim oScrewRef As Reference
    ' --------------------------------------
    ' Get the Constraints collection 
    ' --------------------------------------
    Dim oConstraints0 As Collection
    Set oConstraints0 = oRootProduct.Connections  ( "CATIAConstraints" ) 
    ' --------------------------------------
    ' Create offset constraint between plate  
    ' top face and screws heads bottom faces
    ' --------------------------------------
    set oPlatePub = oPlate.Publications.Item("Top")
    Set oPlateRef = oPlatePub.Valuation
    '  ---> Plate\Top Screw1\HeadBottom 
    
    Set oScrewPub = oScrew1.Publications.Item("HeadBottom")
    Set oScrewRef = oScrewPub.Valuation
    
    Dim oConstraint1 As Constraint
    Set oConstraint1 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef ) 
```

    
```

    oConstraint1.Dimension.Value = 2.000000
    oConstraint1.Orientation = CATCstOrientOpposite
    '  ---> Plate\Top Screw2\HeadBottom 
    
```vbscript
    Set oScrewPub = oScrew2.Publications.Item("HeadBottom")
    Set oScrewRef = oScrewPub.Valuation
    
    Dim oConstraint2 As Constraint
    Set oConstraint2 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef ) 
    
```

    oConstraint2.Dimension.Value = 2.000000
    oConstraint2.Orientation = CATCstOrientOpposite
```vbscript
    ' --------------------------------------------
    ' Create offset constraint between plate  
    ' holes positioning points and screws axis
    ' --------------------------------------------
    '  ---> Plate\Hole1 Screw1\Axis 
    
    set oPlatePub = oPlate.Publications.Item("Hole1")
```

```vbscript
    Set oPlateRef = oPlatePub.Valuation
    
    Set oScrewPub = oScrew1.Publications.Item("Axis")
    Set oScrewRef = oScrewPub.Valuation
    
    Dim oConstraint3 As Constraint
    Set oConstraint3 = oConstraints0.AddBiEltCst(catCstTypeOn, oPlateRef, oScrewRef )
    '  ---> Plate\Hole2 Screw2\Axis 
    
```

    set oPlatePub = oPlate.Publications.Item("Hole2")
```vbscript
    Set oPlateRef = oPlatePub.Valuation
    
    Set oScrewPub = oScrew2.Publications.Item("Axis")
    Set oScrewRef = oScrewPub.Valuation
    
    Dim oConstraint4 As Constraint
    Set oConstraint4 = oConstraints0.AddBiEltCst(catCstTypeOn, oPlateRef, oScrewRef )
    
```

```vbscript
    ' --------------------------------------
    ' Update the Product ..
    ' --------------------------------------
```

    oRootProduct.Update 
    
    MsgBox "Click OK to replace the screw by another standard screw ..."
```vbscript
    ' --------------------------------------
    ' Replace the screw by another one: constraints on 
    ' published elements are autoatically reconnected ...
    ' --------------------------------------
```

```vbscript
    Set oScrew1 = CATIA.ActiveDocument.Product.Products.ReplaceComponent ( _
          oScrew1,                                                         _
          sDocPath & "\online\CAAScdAsmUseCases\samples\NewScrew.CATPart", _
          True)
```vbscript
    ' --------------------------------------
    ' Update the Product with the new Parts
    ' --------------------------------------
```

    oRootProduct.Update 
    
```

```vbscript
    End Sub
    
```

```