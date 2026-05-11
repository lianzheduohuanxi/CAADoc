---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAStrWeldInfoOnStiffeners", "CAAScdStrWeldInfo01", "CATIASfmStiffener", "CAAScdStrUseCases", "CAAInfLauchMacro", "CAAStrWeldInfoOnStiffenersSource"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnStiffeners.htm"
converted: "2026-05-11T11:27:02.601544"
---

---

![End Task Icon](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to get weld information set on SDD Split Stiffener.

[Top]

---

#### References

---

*Copyright  1999-2013, Dassault Syst&#232;mes. All rights reserved.*



```vbscript
Sub CATMain()

Dim ObjPart As Part
Set ObjPart = CATIA.ActiveDocument.Part
```

```vbscript
'Get the Factory Object
Dim FactoryObj As SfmFactory
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
```

```vbscript
'Get the Manager Object
Dim ManagerObj As SfmManager
Set ManagerObj = FactoryObj.GetManager
```

```vbscript
'RETRIEVING THE SUPERSTIFFENERS
Dim SuperStiffeners As References
Set SuperStiffeners = ManagerObj.GetSuperStiffeners

Dim SuperStiffener1 As SfmStiffener
Set SuperStiffener1 = SuperStiffeners.Item(1)
```

```vbscript
'Retrieving The Seamed Stiffeners on Deck
Dim SplitStiffeners As References
Set SplitStiffeners = SuperStiffener1.SplitProfiles

Dim SplitStiffener1 As Reference
Set SplitStiffener1 = SplitStiffeners.Item(1)
```

```vbscript
Set SelctionObj = CATIA.ActiveDocument.Selection
'DECK STIFFENER
SelctionObj.Add SplitStiffener1
Dim DeckStiffener1 As SfmStiffener
Set DeckStiffener1 = SelctionObj.FindObject("CATIASfmStiffener")
```

```vbscript
'Retrieving Super Plates
Dim SuperPlates As References
Set SuperPlates = ManagerObj.GetSuperPlates

'Retrieving Operating Super Plate
Dim SuperPlate1 As SfmSuperPlate
Set SuperPlate1 = SuperPlates.Item(1)

'Retrieving the SplitPlates of SuperPlate1
Dim OperatingSplitPlateRefs As References
Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates

Dim OperatingSplitPlate As Reference
Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)
```

```vbscript
Dim WeldsUC1 As SfmWelds
Set WeldsUC1 = DeckStiffener1.GetWelds(OperatingSplitPlate)

Dim WeldUC1 As SfmWeld
Set WeldUC1 = WeldsUC1.Item(1)
```

```vbscript
ustrWeldTypeUC1 = WeldUC1.WeldType
ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
ustrFitUpUC1 = WeldUC1.FitUp
ustrEdgePrepUC1 = WeldUC1.EdgePreparation
```

```vbscript
Dim WeldsUC2 As SfmWelds
Set WeldsUC2 = DeckStiffener1.GetWelds(Nothing)

Dim WeldUC2 As SfmWeld
Set WeldUC2 = WeldsUC2.Item(1)
```

```vbscript
ustrWeldTypeUC2 = WeldUC2.WeldType
ustrAddedMaterialUC2 = WeldUC2.AddedMaterial
ustrFitUpUC2 = WeldUC2.FitUp
ustrEdgePrepUC2 = WeldUC2.EdgePreparation

End Sub
```