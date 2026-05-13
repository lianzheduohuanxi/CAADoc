---
title: "Creating Copings"
category: "use-case"
module: "CAAScdStrUseCases"
tags: "["CATIA", "CATIAStrFeatureFactory", "CAAScdStrUseCases", "CAAStrCreateCoping"]"
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfCoping.htm"
converted: "2026-05-11T17:31:50.865138"
---
## Structure Design

|
## Creating Copings

* * *

  This macro shows you how to apply coping between structure objects. Here we will see three Cases.

  1. Creating Coping on Plate, when it is limited by another plate and surface.
  2. Creating Coping on Stiffener, when it is limited by stiffeners and Plate.
  3. Creating Coping on Stiffener, when it is limited by lateral face of a Plate.

![Starting Product](images/CAAScdStrCoping01.png)
---|---
2. Creating Coping on Stiffener, when it is limited by stiffeners and Plate.
3. Creating Coping on Stiffener, when it is limited by lateral face of a Plate.
  CAAStrCreateCoping is launched in CATIA [1]. Some documents are needed.

  * [CAAStrCreateCoping.CATScript](CAAStrCreationOfCopingSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrCreateCoping.CATScript) (Windows only).
  * The document Product1.CATProduct is located in the CAAScdStrUseCases module in the samples directory. Part1.CATPart is linked to the previous document and it contains the grid used by the macro.
  * The CATPart containing the section is located in the samples directory.

  CAAStrCreateCoping includes five steps:

  1. Prolog
  2. Retrieving the Factory from Object on which Coping Is to Be Done
  3. Defining the Limits
  4. Creating Coping
  5. Creating Coping for Case2 and Case3

#### Prolog

```vbscript
```cpp
    Sub CATMain(#)

```
```

```vbscript
```vbscript
    Dim StrWorkbench As StrWorkbench
```vbscript
```
```vbscript
```cpp
    Dim strFactory As StrObjectFactory

    Set doc = CATIA.ActiveDocument
    Dim rootProduct As Product
    Set rootProduct = doc.Product

    Set StrWorkbench = doc.GetWorkbench("StrWorkbench")

    Dim strPlates As strPlates
    Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")

    Dim strMembers As strMembers
    Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")

```
```

```

```

#### Retrieving the Factory from Object on which Coping Is to Be Done

```vbscript
```vbscript
Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
```
```

This step describes how to get Structure Feature Factory. The Factory object is retrieved by adding object to nibble to the selection list.

```vbscript
```vbscript
    'Get The Factory from Selection Method

```

```

```vbscript
```vbscript
    Dim PlateToNibble As StrPlate
```vbscript
```
```vbscript
```cpp
    Set PlateToNibble = strPlates.Item("Deck_014.2")

    Dim PlateSelection As Selection
    Set PlateSelection = CATIA.ActiveDocument.Selection
```
```

```

    PlateSelection.Add PlateToNibble

```vbscript
    Dim FactoryForPlate As StrFeatureFactory
```vbscript
```
```vbscript
```cpp
    Set FactoryForPlate = PlateSelection.FindObject("CATIAStrFeatureFactory")

```
```

```

```

#### Defining the Limits

```vbscript
```cpp
Set FactoryForPlate = PlateSelection.FindObject("CATIAStrFeatureFactory")
```
```

The limits are defined by adding them to list of variant which can contain only one element at a time.

```vbscript
```vbscript
    'Define the Limits for PlateToNibble

```

```

```vbscript
```vbscript
    Dim Limitplate1 As StrPlate
```vbscript
```
```vbscript
```vbscript
    Set Limitplate1 = strPlates.Item("Shell_002.1")

    Dim LimitSurface1 As Reference
    Set LimitSurface1 = rootProduct.CreateReferenceFromName("Product1/Part1.1/!Extrude.1")

    Dim Listoflimits1(0) As Variant
    Dim Listoflimits2(0) As Variant

    Set Listoflimits1(0) = Limitplate1
    Set Listoflimits2(0) = LimitSurface1

```
```

```

```

#### Creating Coping

```vbscript
```vbscript
Set Listoflimits2(0) = LimitSurface1
```
```

Create Coping by passing list of limits containing one element and Type. Coping SubType can also be defined later.

```vbscript
```vbscript
    'Create Nibbling by defining Type and SubType

```

```

```vbscript
```vbscript
```vbscript
    Dim NibblingFeature1, NibblingFeature2 As StrNibblingFeature

    Set NibblingFeature1 = FactoryForPlate.AddNibbling(Listoflimits1, "Remove")
```
```

```vbscript
```vbscript
    NibblingFeature1.SubType = "ButtButt"

```vbscript
    Set NibblingFeature2 = FactoryForPlate.AddNibbling(Listoflimits2, "Remove")
    NibblingFeature2.SubType = "CurrCurr"
```

```

```

```

#### Creating Coping for Case2 and Case3

NibblingFeature2.SubType = "CurrCurr"
In Case2: we will apply coping on Member when it is limited by 2 Members and One Plate.

```vbscript
```vbscript
    'Case2: When Member is limited by 2 Members and One Plate
    'Get the Factory from Selection Method

```

```

```vbscript
```vbscript
    Dim MembertoNibble1 As StrMember
```vbscript
```
```vbscript
```cpp
    Set MembertoNibble1 = strMembers.Item("BottShell_LStf_003.1")

    Dim MemberSelection As Selection
    Set MemberSelection = CATIA.ActiveDocument.Selection
```
```

```

    MemberSelection.Add MembertoNibble1

```vbscript
    Dim FactoryForMember As StrFeatureFactory
```vbscript
```
```cpp
    Set FactoryForMember = MemberSelection.FindObject("CATIAStrFeatureFactory")
```
```

```

```vbscript
```vbscript
```vbscript
    'Define the Limits for MembertoNibble1
```vbscript
    Dim L1 As StrMember
    Set L1 = strMembers.Item("Shell_VStf_006.1")

    Dim L2 As StrMember
    Set L2 = strMembers.Item("Shell_VStf_005.1")

    Dim L3 As StrPlate
    Set L3 = strPlates.Item("Shell_002.1")

    Dim Listoflimits3(0) As Variant
    Dim Listoflimits4(0) As Variant
    Dim Listoflimits5(0) As Variant

    Set Listoflimits5(0) = L3
    Set Listoflimits3(0) = L1
    Set Listoflimits4(0) = L2
    'Create Nibbling by defining Type and SubType
```
```vbscript
    Dim NibblingFeature3, NibblingFeature4, NibblingFeature5 As StrNibblingFeature

    Set NibblingFeature3 = FactoryForMember.AddNibbling(Listoflimits3, "WeldCut")
    Set NibblingFeature4 = FactoryForMember.AddNibbling(Listoflimits4, "LongPoint")
```
```

```

```

```vbscript
```vbscript
Set NibblingFeature3 = FactoryForMember.AddNibbling(Listoflimits3, "WeldCut")
```vbscript
```
```vbscript
```vbscript
Set NibblingFeature4 = FactoryForMember.AddNibbling(Listoflimits4, "LongPoint")
    NibblingFeature4.Type = "ShortPoint"
```
```vbscript
    Set NibblingFeature5 = FactoryForMember.AddNibbling(Listoflimits5, "Remove")

```
```

```

```

NibblingFeature4.Type = "ShortPoint"
```vbscript
```vbscript
Set NibblingFeature5 = FactoryForMember.AddNibbling(Listoflimits5, "Remove")
```
```

In case3 we will define the extrapolation offset for the lateral face of stiffener.

```vbscript
```vbscript
    'Case3: When Member is limited by Lateral Face of Plate
    'Get the Factory from Selection Method

```

```

```vbscript
```vbscript
    Dim MembertoNibble2 As StrMember
```vbscript
```
```vbscript
```cpp
    Set MembertoNibble2 = strMembers.Item("Deck_TStf_005.1")

    Dim Member2Sel As Selection
    Set Member2Sel = CATIA.ActiveDocument.Selection
```
```

```

    Member2Sel.Add MembertoNibble2

```vbscript
    Dim FactoryForMember2 As StrFeatureFactory
```vbscript
```
```cpp
    Set FactoryForMember2 = Member2Sel.FindObject ("CATIAStrFeatureFactory")
```
```

```

```vbscript
```vbscript
```vbscript
    'Define the Limits for MembertoNibble2
```vbscript
    Dim L4 As StrPlate
    Set L4 = strPlates.Item("Deck_014.2")

    Dim ListofLimits6(0) As Variant
    Set ListofLimits6(0) = L4
    'Create Nibbling by defining the Extrapolation Offset
```
```vbscript
    Dim NibblingFeature6 As StrNibblingFeature
    Set NibblingFeature6 = FactoryForMember2.AddNibbling(ListofLimits6, "Remove")
```
```

```

```

```vbscript
```vbscript
```vbscript
'Create Nibbling by defining the Extrapolation Offset
```vbscript
Dim NibblingFeature6 As StrNibblingFeature
Set NibblingFeature6 = FactoryForMember2.AddNibbling(ListofLimits6, "Remove")
```
```

```

    NibblingFeature6.GetOffsetForExtrapolate ("25mm")

```

![End Task Icon](./assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create coping between structure objects.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

[Top]

* * *

_Copyright 1999-2010, Dassault Systmes. All rights reserved._
