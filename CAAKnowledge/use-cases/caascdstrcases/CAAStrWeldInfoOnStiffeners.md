---
```vbscript
title: "Retrieving Weld Information on Stiffener Objects"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CATIASfmStiffener", "CAAScdStrUseCases", "CAAStrWeldInfoOnStiffeners"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnStiffeners.htm"
converted: "2026-05-11T17:31:50.922064"
```

---
## Structure Design

|
## Retrieving Weld Information on Stiffener Objects

* * *

  This macro shows you how to retrieve Weld information already set on SDD Stiffener Objects. ![Starting Part](images/CAAScdStrWeldInfo01.png)
---|---
  CAAStrWeldInfoOnStiffeners is launched in CATIA [1]. Some documents are needed.

  * [ CAAStrWeldInfoOnStiffeners.CATScript](CAAStrWeldInfoOnStiffenersSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrWeldInfoOnStiffeners.CATScript) (Windows only).
  * The document CAAStrWeldInfoOnStiffeners.CATPart is located in the CAAScdStrUseCases module in the samples directory.

  CAAStrWeldInfoOnStiffeners includes the following steps:

CAAStrWeldInfoOnStiffeners includes the following steps:
  1. Prolog
  2. Retrieving Factory Object from Part Document
  3. Getting the Manager from Factory
  4. Retrieving the Super Stiffeners
  5. Retrieving Split Stiffeners of Super Stiffener
  6. Retrieving SfmStiffener object from the reference of Split Stiffener
  7. Retrieving Super Plate which is used as Support for Stiffener
  8. Retrieving Weld Features on the Stiffener with Operating Element (Weld Use Case 1)
  9. Retrieving Weld Attributes of Weld Use Case 1 Features
  10. Retrieving Weld Features on the Stiffener with No Operating Element (Weld Use Case 2)
  11. Retrieving Weld Attributes of Weld Use Case 2 Features

#### Prolog

10. Retrieving Weld Features on the Stiffener with No Operating Element (Weld Use Case 2)
11. Retrieving Weld Attributes of Weld Use Case 2 Features
Opens the CAAStrWeldInfoOnStiffeners.CATPart in CATIA.

```vbscript
    Sub CATMain()

```

```vbscript
    Dim ObjPart As Part
```vbscript
```vbscript
    Set ObjPart = CATIA.ActiveDocument.Part

```

```

```

#### Retrieving Factory Object from Part Document

```vbscript
Set ObjPart = CATIA.ActiveDocument.Part
```

This step describes how to get the Structure Functional Modeler Factory. The Factory Object will be used for creating Structure Functional Modeler Objects.

```vbscript
```vbscript
    'Get the Factory Object

```

```

```vbscript
    Dim FactoryObj As SfmFactory
```vbscript
```vbscript
    Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")

```

```

```

#### Getting the Manager from Factory

```vbscript
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
```

The Manager Object is obtained by GetManager.

```vbscript
```vbscript
    'Get the Manager Object

```

```

```vbscript
    Dim ManagerObj As SfmManager
```vbscript
```vbscript
    Set ManagerObj = FactoryObj.GetManager

```

```

```

#### Retrieving the Super Stiffeners

```vbscript
Set ManagerObj = FactoryObj.GetManager
```

This step describes how to get the collection of Super Stiffeners and how to get one specific element in it.

```vbscript
```vbscript
    'RETRIEVING THE SUPERSTIFFENERS

```

```

```vbscript
    Dim SuperStiffeners As References
```vbscript
```vbscript
    Set SuperStiffeners = ManagerObj.GetSuperStiffeners

    Dim SuperStiffener1 As SfmStiffener
    Set SuperStiffener1 = SuperStiffeners.Item(1)

```

```

```

#### Retrieving Split Stiffeners of Super Stiffener

```vbscript
Set SuperStiffener1 = SuperStiffeners.Item(1)
```

This step describes how to get the collection of Split Stiffeners and how to get one specific element in it.

```vbscript
```vbscript
    'Retrieving The Seamed Stiffeners on Deck

```

```

```vbscript
    Dim SplitStiffeners As References
```vbscript
```vbscript
    Set SplitStiffeners = SuperStiffener1.SplitProfiles

    Dim SplitStiffener1 As Reference
    Set SplitStiffener1 = SplitStiffeners.Item(1)

```

```

```

#### Retrieving SfmStiffener Object from the Reference of Split Stiffener

This step describes how to get the SfmStiffener object from Reference of split stiffener.

```vbscript
    Set SelctionObj = CATIA.ActiveDocument.Selection
```vbscript
    'DECK STIFFENER
```

    SelctionObj.Add SplitStiffener1
    Dim DeckStiffener1 As SfmStiffener
```vbscript
```vbscript
    Set DeckStiffener1 = SelctionObj.FindObject("CATIASfmStiffener")

```

```

```

#### Retrieving Super Plate which is Used as Support for Stiffener

```vbscript
Set DeckStiffener1 = SelctionObj.FindObject("CATIASfmStiffener")
```

This step describes how to get the Plate used as support for the Stiffener and accessing each element in it.

```vbscript
```vbscript
    'Retrieving Super Plates

```

```

```vbscript
    Dim SuperPlates As References
```vbscript
    Set SuperPlates = ManagerObj.GetSuperPlates
```

```

```vbscript
```vbscript
```vbscript
    'Retrieving Operating Super Plate
    Dim SuperPlate1 As SfmSuperPlate
    Set SuperPlate1 = SuperPlates.Item(1)
    'Retrieving the SplitPlates of SuperPlate1
    Dim OperatingSplitPlateRefs As References
    Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates

    Dim OperatingSplitPlate As Reference
    Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)
```

```

```

#### Retrieving Weld Features on the Stiffener with Operating Element (Weld Use Case 1)

This step describes how to get the collection of Weld features with operating element and how to get one specific element in it.

```vbscript
    Dim WeldsUC1 As SfmWelds
```vbscript
```vbscript
    Set WeldsUC1 = DeckStiffener1.GetWelds(OperatingSplitPlate)

    Dim WeldUC1 As SfmWeld
    Set WeldUC1 = WeldsUC1.Item(1)

```

```

```

#### Retrieving Weld Attributes of Weld Use Case 1 Features

This step describes how to get the weld information set on the Operated split stiffener with operating element.

This step describes how to get the weld information set on the Operated split stiffener with operating element.
    ustrWeldTypeUC1 = WeldUC1.WeldType
    ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
    ustrFitUpUC1 = WeldUC1.FitUp
    ustrEdgePrepUC1 = WeldUC1.EdgePreparation

#### Retrieving Weld Features on the Stiffener with No Operating Element (Weld Use Case 2)

```vbscript
ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
ustrFitUpUC1 = WeldUC1.FitUp
ustrEdgePrepUC1 = WeldUC1.EdgePreparation
This step describes how to get the collection of Weld features with no operating element and how to get one specific element in it.

```

```vbscript
    Dim WeldsUC2 As SfmWelds
```vbscript
```vbscript
    Set WeldsUC2 = DeckStiffener1.GetWelds(Nothing)

    Dim WeldUC2 As SfmWeld
    Set WeldUC2 = WeldsUC2.Item(1)

```

```

```

#### Retrieving Weld Attributes of Weld Use Case 2 Features

This step describes how to get the weld information set on the Operated split Stiffener with no operating element.

This step describes how to get the weld information set on the Operated split Stiffener with no operating element.
    ustrWeldTypeUC2 = WeldUC2.WeldType
    ustrAddedMaterialUC2 = WeldUC2.AddedMaterial
    ustrFitUpUC2 = WeldUC2.FitUp
    ustrEdgePrepUC2 = WeldUC2.EdgePreparation

```vbscript
    End Sub

```

![End Task Icon](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to get weld information set on SDD Split Stiffener.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

[Top]

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
