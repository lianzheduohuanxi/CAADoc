---
```vbscript
title: "Retrieving Weld Information on Member Objects"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CATIASfmMember", "CAAScdStrUseCases", "CAAStrWeldInfoOnMembers"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnMembers.htmmd"
converted: "2026-05-11T17:31:50.908610"
```

---
|
## Structure Design

|
## Retrieving Weld Information on Member Objects

* * *

  This macro shows you how to retrieve Weld information already set on SDD Member Objects. ![Starting Part](images/CAAScdStrWeldInfo02.png)
---|---
  CAAStrWeldInfoOnMembers is launched in CATIA [1]. Some documents are needed.

  * [ CAAStrWeldInfoOnMembers.CATScript](CAAStrWeldInfoOnMembersSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrWeldInfoOnMembers.CATScript) (Windows only).
  * The CAAStrWeldInfoOnMembers.CATPart is located in the samples directory.

  CAAStrWeldInfoOnMembers includes the following steps:

CAAStrWeldInfoOnMembers includes the following steps:
  1. Prolog
  2. Retrieving Factory Object from Part Document
  3. Getting the Manager from Factory
  4. Retrieving the Super Members
  5. Retrieving Split Members of Super Member
  6. Retrieving SfmMember object from the reference of Split Member
  7. Retrieving Super Plate which is used as Support for Member
  8. Retrieving Weld Features on the Member with Operating Element (Weld Use Case 1)
  9. Retrieving Weld Attributes of Weld Use Case 1 Features
  10. Retrieving Weld Features on the Member with No Operating Element (Weld Use Case 2)
  11. Retrieving Weld Attributes of Weld Use Case 2 Features

#### Prolog

10. Retrieving Weld Features on the Member with No Operating Element (Weld Use Case 2)
11. Retrieving Weld Attributes of Weld Use Case 2 Features
```vbscript
Opens the CAAStrWeldInfoOnMembers.CATPart in CATIA.

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

This Step describes how to get Structure Functional Modeler Factory .The Factory Object will be used for creating Structure Functional Modeler Objects.

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

#### Retrieving the Super Members

```vbscript
```vbscript
Set ManagerObj = FactoryObj.GetManager
```
```

This step describes how to get the collection of Super Members and how to get one specific element in it.

```vbscript
```vbscript
    'RETRIEVING THE SUPERMembers

```

```

```vbscript
```vbscript
    Dim SuperMembers As References
```vbscript
```
```vbscript
```vbscript
    Set SuperMembers = ManagerObj.GetSuperMembers

    Dim SuperMember1 As SfmMember
    Set SuperMember1 = SuperMembers.Item(1)

```
```

```

```

#### Retrieving Split Members of Super Member

```vbscript
```vbscript
Set SuperMember1 = SuperMembers.Item(1)
```
```

This step describes how to get the collection of Split Members and how to get one specific element in it.

```vbscript
```vbscript
    'Retrieving The Split Members

```

```

```vbscript
```vbscript
    Dim SplitMembers As References
```vbscript
```
```vbscript
```vbscript
    Set SplitMembers = SuperMember1.SplitProfiles

    Dim SplitMember1 As Reference
    Set SplitMember1 = SplitMembers.Item(1)

```
```

```

```

#### Retrieving SfmMember Object from the Reference of Split Member

This step describes how to get the SfmStiffener object from Reference of split stiffener.****

```vbscript
```vbscript
     Set SelctionObj = CATIA.ActiveDocument.Selection
```vbscript
```
    'DECK Member
```

    SelctionObj.Add SplitMember1
```vbscript
    Dim DeckMember1 As SfmMember
```vbscript
```
```vbscript
```vbscript
    Set DeckMember1 = SelctionObj.FindObject("CATIASfmMember")

```
```

```

```

#### Retrieving Super Plate which is Used as Support for Member

```vbscript
```vbscript
Set DeckMember1 = SelctionObj.FindObject("CATIASfmMember")
```
```

This step describes how to get the Plate used as one of the limit for Member and accessing each element in it.

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
    'Retrieving the SplitPlates of SuperPlate1
```
```vbscript
    Dim OperatingSplitPlateRefs As References
    Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates

    Dim OperatingSplitPlate As Reference
    Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)
```
```

```

```

#### Retrieving Weld Features on the Member with Operating Element (Weld Use Case 1)

This step describes how to get the collection of Weld features with operating element and how to get one specific element in it.

```vbscript
```vbscript
    Dim WeldsUC1 As SfmWelds
```vbscript
```
```vbscript
```vbscript
    Set WeldsUC1 = DeckMember1.GetWelds(OperatingSplitPlate)

    Dim WeldUC1 As SfmWeld
    Set WeldUC1 = WeldsUC1.Item(1)

```
```

```

```

#### Retrieving Weld Attributes of Weld Use Case 1 Features

This step describes how to get the weld information set on the Operated split Member with operating element.

This step describes how to get the weld information set on the Operated split Member with operating element.
    ustrWeldTypeUC1 = WeldUC1.WeldType
    ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
    ustrFitUpUC1 = WeldUC1.FitUp
    ustrEdgePrepUC1 = WeldUC1.EdgePreparation

#### Retrieving Weld Features on the Member with No Operating Element (Weld Use Case 2)

```vbscript
ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
ustrFitUpUC1 = WeldUC1.FitUp
ustrEdgePrepUC1 = WeldUC1.EdgePreparation
This step describes how to get the collection of Weld features with no operating element and how to get one specific element in it.

```

```vbscript
```vbscript
    Dim WeldsUC2 As SfmWelds
```vbscript
```
```vbscript
```vbscript
    Set WeldsUC2 = DeckMember1.GetWelds(Nothing)

    Dim WeldUC2 As SfmWeld
    Set WeldUC2 = WeldsUC2.Item(1)

```
```

```

```

#### Retrieving Weld Attributes of Weld Use Case 2 Features

This step describes how to get the weld information set on the Operated split Member with no operating element.

This step describes how to get the weld information set on the Operated split Member with no operating element.
    ustrWeldTypeUC2 = WeldUC2.WeldType
    ustrAddedMaterialUC2 = WeldUC2.AddedMaterial
    ustrFitUpUC2 = WeldUC2.FitUp
    ustrEdgePrepUC2 = WeldUC2.EdgePreparation

```vbscript
```vbscript
    End Sub

```
```

![End Task Icon](./assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to get weld information set on SDD Split Member.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

[Top]

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
