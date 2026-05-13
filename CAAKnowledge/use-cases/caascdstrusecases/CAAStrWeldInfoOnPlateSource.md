---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAStrWeldInfoOnPlate"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnPlateSource.htmmd"
converted: "2026-05-11T11:27:02.599942"
---

'//============================================================================
'// COPYRIGHT DASSAULT SYSTEMES 2013
'//============================================================================
'// Language="VBSCRIPT"
'// Sample of macro for getting weld information on SDD Plates.
'//============================================================================
'// Mar  Creation                                               Bhupendra Mithe
'//============================================================================

```cpp
Sub CATMain(#)

Dim ObjPart As Part
Set ObjPart = CATIA.ActiveDocument.Part

'Get the Factory Object
```
```vbscript
Dim FactoryObj As SfmFactory
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")

'Get the Manager Object
```
```vbscript
Dim ManagerObj As SfmManager
Set ManagerObj = FactoryObj.GetManager

'Retrieving Super Plates
```
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

'Retrieving the SplitPlates of SuperPlate1
```
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

'Weld Use Case 1 features.
```
```vbscript
Dim ListWeldsUC1 As SfmWelds
Set ListWeldsUC1 = OperatedSplitPlate.GetWelds(OperatingSplitPlate)

Dim WeldUC1Feature As SfmWeld
Set WeldUC1Feature = ListWeldsUC1.Item(1)

```

ustrWeldTypeUC1 = WeldUC1Feature.WeldType
ustrAddedMaterialUC1 = WeldUC1Feature.AddedMaterial
ustrFitUpUC1 = WeldUC1Feature.FitUp
ustrEdgePrepUC1 = WeldUC1Feature.EdgePreparation

'Weld Use Case 2 features.
```vbscript
Dim ListWeldsUC2 As SfmWelds
Set ListWeldsUC2 = OperatedSplitPlate.GetWelds(Nothing)

Dim WeldUC2Feature As SfmWeld
Set WeldUC2Feature = ListWeldsUC2.Item(1)

```

ustrWeldTypeUC2 = WeldUC2Feature.WeldType
ustrAddedMaterialUC2 = WeldUC2Feature.AddedMaterial
ustrFitUpUC2 = WeldUC2Feature.FitUp
ustrEdgePrepUC2 = WeldUC2Feature.EdgePreparation

```vbscript
End Sub

```

```vbscript
'//============================================================================
'// COPYRIGHT DASSAULT SYSTEMES 2013
'//============================================================================
'// Language="VBSCRIPT"
'// Sample of macro for getting weld information on SDD Plates.
'//============================================================================
'// Mar  Creation                                               Bhupendra Mithe
'//============================================================================

```cpp
Sub CATMain(#)

Dim ObjPart As Part
Set ObjPart = CATIA.ActiveDocument.Part

'Get the Factory Object
```
```vbscript
Dim FactoryObj As SfmFactory
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")

'Get the Manager Object
```
```vbscript
Dim ManagerObj As SfmManager
Set ManagerObj = FactoryObj.GetManager

'Retrieving Super Plates
```
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

'Retrieving the SplitPlates of SuperPlate1
```
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

'Weld Use Case 1 features.
```
```vbscript
Dim ListWeldsUC1 As SfmWelds
Set ListWeldsUC1 = OperatedSplitPlate.GetWelds(OperatingSplitPlate)

Dim WeldUC1Feature As SfmWeld
Set WeldUC1Feature = ListWeldsUC1.Item(1)

```

ustrWeldTypeUC1 = WeldUC1Feature.WeldType
ustrAddedMaterialUC1 = WeldUC1Feature.AddedMaterial
ustrFitUpUC1 = WeldUC1Feature.FitUp
ustrEdgePrepUC1 = WeldUC1Feature.EdgePreparation

'Weld Use Case 2 features.
```vbscript
Dim ListWeldsUC2 As SfmWelds
Set ListWeldsUC2 = OperatedSplitPlate.GetWelds(Nothing)

Dim WeldUC2Feature As SfmWeld
Set WeldUC2Feature = ListWeldsUC2.Item(1)

```

ustrWeldTypeUC2 = WeldUC2Feature.WeldType
ustrAddedMaterialUC2 = WeldUC2Feature.AddedMaterial
ustrFitUpUC2 = WeldUC2Feature.FitUp
ustrEdgePrepUC2 = WeldUC2Feature.EdgePreparation

```vbscript
End Sub
```
```