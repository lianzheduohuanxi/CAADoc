---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAStrWeldInfoOnMembers", "CAAScrJavaScript", "CATIASfmMember", "CAAScdInfUseCases", "CAAScdStrWeldInfo02", "CAAScdStrUseCases", "CAAInfLauchMacro", "CAAStrWeldInfoOnMembersSource"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnMembers.htmmd"
converted: "2026-05-11T11:27:02.592507"
---

---

![End Task Icon](./assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to get weld information set on SDD Split Member.

[Top]

---

#### References

---

*Copyright  1999-2013, Dassault Syst&#232;mes. All rights reserved.*

```vbscript
```vbscript
Sub CATMain(#)

Dim ObjPart As Part
Set ObjPart = CATIA.ActiveDocument.Part
```
```

```vbscript
'Get the Factory Object
```vbscript
Dim FactoryObj As SfmFactory
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
```
```

```vbscript
'Get the Manager Object
```vbscript
Dim ManagerObj As SfmManager
Set ManagerObj = FactoryObj.GetManager
```
```

```vbscript
'RETRIEVING THE SUPERMembers
```vbscript
Dim SuperMembers As References
Set SuperMembers = ManagerObj.GetSuperMembers

Dim SuperMember1 As SfmMember
Set SuperMember1 = SuperMembers.Item(1)
```
```

```vbscript
'Retrieving The Split Members
```vbscript
Dim SplitMembers As References
Set SplitMembers = SuperMember1.SplitProfiles

Dim SplitMember1 As Reference
Set SplitMember1 = SplitMembers.Item(1)
```
```

```vbscript
```vbscript
Set SelctionObj = CATIA.ActiveDocument.Selection
'DECK Member
```
SelctionObj.Add SplitMember1
```vbscript
Dim DeckMember1 As SfmMember
Set DeckMember1 = SelctionObj.FindObject("CATIASfmMember")
```
```

```vbscript
'Retrieving Super Plates
```vbscript
Dim SuperPlates As References
Set SuperPlates = ManagerObj.GetSuperPlates

'Retrieving Operating Super Plate
```
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

```vbscript
```vbscript
Dim WeldsUC1 As SfmWelds
Set WeldsUC1 = DeckMember1.GetWelds(OperatingSplitPlate)

Dim WeldUC1 As SfmWeld
Set WeldUC1 = WeldsUC1.Item(1)
```
```

```vbscript
ustrWeldTypeUC1 = WeldUC1.WeldType
ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
ustrFitUpUC1 = WeldUC1.FitUp
ustrEdgePrepUC1 = WeldUC1.EdgePreparation
```

```vbscript
```vbscript
Dim WeldsUC2 As SfmWelds
Set WeldsUC2 = DeckMember1.GetWelds(Nothing)

Dim WeldUC2 As SfmWeld
Set WeldUC2 = WeldsUC2.Item(1)
```
```

```vbscript
ustrWeldTypeUC2 = WeldUC2.WeldType
ustrAddedMaterialUC2 = WeldUC2.AddedMaterial
ustrFitUpUC2 = WeldUC2.FitUp
ustrEdgePrepUC2 = WeldUC2.EdgePreparation

```vbscript
End Sub
```
```