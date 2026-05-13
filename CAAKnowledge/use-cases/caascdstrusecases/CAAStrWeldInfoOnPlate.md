---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAStrWeldInfoOnPlateSource", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAStrWeldInfoOnPlate", "CAAScdStrWeldInfo03", "CAAScdStrUseCases", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnPlate.htmmd"
converted: "2026-05-11T11:27:02.591198"
---

---

![End Task Icon](./assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to get weld information set on SDD Split Plate.

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
'Retrieving Super Plates
```vbscript
Dim SuperPlates As References
Set SuperPlates = ManagerObj.GetSuperPlates

'Retrieving Operating Super Plate
```
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

```vbscript
'Retrieving the SplitPlates of SuperPlate1
```vbscript
Dim OperatingSplitPlateRefs As References
Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates

'Retrieving the SplitPlates of SuperPlate2
```
```vbscript
Dim OperatedSplitPlateRefs As SfmSplitPlates
Set OperatedSplitPlateRefs = SuperPlate2.SplitPlatesObjects

Dim OperatingSplitPlate As Reference
Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)

Dim OperatedSplitPlate As SfmSplitPlate
Set OperatedSplitPlate = OperatedSplitPlateRefs.Item(1)
```
```

```vbscript
'Weld Use Case 1 features.
```vbscript
Dim ListWeldsUC1 As SfmWelds
Set ListWeldsUC1 = OperatedSplitPlate.GetWelds(OperatingSplitPlate)

Dim WeldUC1Feature As SfmWeld
Set WeldUC1Feature = ListWeldsUC1.Item(1)
```
```

```vbscript
ustrWeldTypeUC1 = WeldUC1Feature.WeldType
ustrAddedMaterialUC1 = WeldUC1Feature.AddedMaterial
ustrFitUpUC1 = WeldUC1Feature.FitUp
ustrEdgePrepUC1 = WeldUC1Feature.EdgePreparation
```

```vbscript
'Weld Use Case 2 features.
```vbscript
Dim ListWeldsUC2 As SfmWelds
Set ListWeldsUC2 = OperatedSplitPlate.GetWelds(Nothing)

Dim WeldUC2Feature As SfmWeld
Set WeldUC2Feature = ListWeldsUC2.Item(1)
```
```

```vbscript
ustrWeldTypeUC2 = WeldUC2Feature.WeldType
ustrAddedMaterialUC2 = WeldUC2Feature.AddedMaterial
ustrFitUpUC2 = WeldUC2Feature.FitUp
ustrEdgePrepUC2 = WeldUC2Feature.EdgePreparation

```vbscript
End Sub
```
```