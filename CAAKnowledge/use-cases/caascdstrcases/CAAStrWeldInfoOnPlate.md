---
```vbscript
title: "Retrieving Weld Information on Plate Objects"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrWeldInfoOnPlate", "CAAScdStrUseCases"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnPlate.htmmd"
converted: "2026-05-11T17:31:50.915079"
```

---
## Structure Design

|
## Retrieving Weld Information on Plate Objects

* * *

  This macro shows you how to retrieve Weld information already set on SDD Plate Objects. ![Starting Product](images/CAAScdStrWeldInfo03.png)
---|---
  CAAStrWeldInfoOnPlate is launched in CATIA [1]. Some documents are needed.

  * [ CAAStrWeldInfoOnPlate.CATScript](CAAStrWeldInfoOnPlateSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrWeldInfoOnPlate.CATScript) (Windows only).
  * The CAAStrWeldInfoOnPlate.CATPart containing the stiffener is located in the samples directory.

  CAAStrWeldInfoOnPlate includes the following steps:

CAAStrWeldInfoOnPlate includes the following steps:
  1. Prolog
  2. Retrieving Factory Object from Part Document
  3. Getting the Manager from Factory
  4. Retrieving the Super Plates
  5. Retrieving Split Plates of Super Plates
  6. Retrieving Weld Features on the OperatedSplitPlate with Operating Element (Weld Use Case 1)
  7. Retrieving Weld Attributes of Weld Use Case 1 Features
  8. Retrieving Weld Features on the OperatedSplitPlate with No Operating Element (Weld Use Case 2)
  9. Retrieving Weld Attributes of Weld Use Case 2 Features

#### Prolog

8. Retrieving Weld Features on the OperatedSplitPlate with No Operating Element (Weld Use Case 2)
9. Retrieving Weld Attributes of Weld Use Case 2 Features
```vbscript
Opens the CAAStrWeldInfoOnPlate.CATPart in CATIA.

```vbscript
```
```vbscript
    Sub CATMain(#)

```
```

```vbscript
```vbscript
    Dim ObjPart As Part
```vbscript
```
```vbscript
```vbscript
    Set ObjPart = CATIA.ActiveDocument.Part

```
```

```

```

#### Retrieving Factory Object from Part Document

```vbscript
```vbscript
Set ObjPart = CATIA.ActiveDocument.Part
```
```

This step describes how to get Structure Feature Factory. The Factory object is retrieved by adding object to nibble to the selection list.

```vbscript
```vbscript
    'Get the Factory Object

```

```

```vbscript
```vbscript
    Dim FactoryObj As SfmFactory
```vbscript
```
```vbscript
```vbscript
    Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")

```
```

```

```

#### Getting the Manager from Factory

```vbscript
```vbscript
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
```
```

The Manager Object is obtained by GetManager.

```vbscript
```vbscript
    'Get the Manager Object

```

```

```vbscript
```vbscript
    Dim ManagerObj As SfmManager
```vbscript
```
```vbscript
```vbscript
    Set ManagerObj = FactoryObj.GetManager

```
```

```

```

#### Retrieving the Super Plates

```vbscript
```vbscript
Set ManagerObj = FactoryObj.GetManager
```
```

This step describes how to get the collection of Super Plates and how to get one specific element in it.

```vbscript
```vbscript
    'Retrieving Super Plates

```

```

```vbscript
```vbscript
    Dim SuperPlates As References
```vbscript
```
```vbscript
    Set SuperPlates = ManagerObj.GetSuperPlates
```
```

```

```vbscript
```vbscript
```vbscript
    'Retrieving Operating Super Plate
```vbscript
    Dim SuperPlate1 As SfmSuperPlate
    Set SuperPlate1 = SuperPlates.Item(1)
    'Retrieving Operated Super Plate
```
```vbscript
    Dim SuperPlate2 As SfmSuperPlate
    Set SuperPlate2 = SuperPlates.Item(2)
```
```

```

```

#### Retrieving Split Plates of Super Plates

This step describes how to get the collection of Split Plates and how to get one specific element in it.

This step describes how to get the collection of Split Plates and how to get one specific element in it.
```vbscript
```vbscript
    'Retrieving the SplitPlates of SuperPlate1

```

```

```vbscript
```vbscript
    Dim OperatingSplitPlateRefs As References
```vbscript
```
```vbscript
    Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates
```
```

```

```vbscript
```vbscript
```vbscript
    'Retrieving the SplitPlates of SuperPlate2
```vbscript
    Dim OperatedSplitPlateRefs As SfmSplitPlates
    Set OperatedSplitPlateRefs = SuperPlate2.SplitPlatesObjects

    Dim OperatingSplitPlate As Reference
    Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)

    Dim OperatedSplitPlate As SfmSplitPlate
    Set OperatedSplitPlate = OperatedSplitPlateRefs.Item(1)
```
```

```

```

OperatedSplitPlate is the split plate on which weld features are created. Weld information resides on this plate. OperatingSplitPlate is the split plate which is used as one of the limit of the OperatedSplitPlate.
#### Retrieving Weld Features on the OperatedSplitPlate with Operating Element (Weld Use Case 1)

OperatedSplitPlate is the split plate on which weld features are created. Weld information resides on this plate. OperatingSplitPlate is the split plate which is used as one of the limit of the OperatedSplitPlate.
This step describes how to get the collection of Weld features with operating element and how to get one specific element in it.

```vbscript
```vbscript
    'Weld Use Case 1 features.

```

```

```vbscript
```vbscript
    Dim ListWeldsUC1 As SfmWelds
```vbscript
```
```vbscript
```vbscript
    Set ListWeldsUC1 = OperatedSplitPlate.GetWelds(OperatingSplitPlate)

    Dim WeldUC1Feature As SfmWeld
    Set WeldUC1Feature = ListWeldsUC1.Item(1)

```
```

```

```

#### Retrieving Weld Attributes of Weld Use Case 1 Features

This step describes how to get the weld information set on the Operated split plate.

This step describes how to get the weld information set on the Operated split plate.
    ustrWeldTypeUC1 = WeldUC1Feature.WeldType
    ustrAddedMaterialUC1 = WeldUC1Feature.AddedMaterial
    ustrFitUpUC1 = WeldUC1Feature.FitUp
    ustrEdgePrepUC1 = WeldUC1Feature.EdgePreparation

#### Retrieving Weld Features on the OperatedSplitPlate with No Operating Element (Weld Use Case 2)

```vbscript
ustrAddedMaterialUC1 = WeldUC1Feature.AddedMaterial
ustrFitUpUC1 = WeldUC1Feature.FitUp
ustrEdgePrepUC1 = WeldUC1Feature.EdgePreparation
This step describes how to get the collection of Weld features with operating element and how to get one specific element in it.

```vbscript
    'Weld Use Case 2 features.
```

```

```vbscript
```vbscript
    Dim ListWeldsUC2 As SfmWelds
```vbscript
```
```vbscript
```vbscript
    Set ListWeldsUC2 = OperatedSplitPlate.GetWelds(Nothing)

    Dim WeldUC2Feature As SfmWeld
    Set WeldUC2Feature = ListWeldsUC2.Item(1)

```
```

```

```

#### Retrieving Weld Attributes of Weld Use Case 2 Features

This step describes how to get the weld information set on the Operated split plate with no operating element.

This step describes how to get the weld information set on the Operated split plate with no operating element.
    ustrWeldTypeUC2 = WeldUC2Feature.WeldType
    ustrAddedMaterialUC2 = WeldUC2Feature.AddedMaterial
    ustrFitUpUC2 = WeldUC2Feature.FitUp
    ustrEdgePrepUC2 = WeldUC2Feature.EdgePreparation

```vbscript
```vbscript
    End Sub

```
```

![End Task Icon](./assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to get weld information set on SDD Split Plate.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

[Top]

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
