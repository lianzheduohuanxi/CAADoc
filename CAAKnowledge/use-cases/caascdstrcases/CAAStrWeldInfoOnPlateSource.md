---
```vbscript
title: "CAAStrWeldInfoOnPlate.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrWeldInfoOnPlate"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnPlateSource.htm"
converted: "2026-05-11T17:31:50.917575"
```

---
```vbscript
```vbscript
```vbscript
    '//============================================================================
    '// COPYRIGHT DASSAULT SYSTEMES 2013
    '//============================================================================
    '// Language="VBSCRIPT"
    '// Sample of macro for getting weld information on SDD Plates.
    '//============================================================================
    '// Mar  Creation                                               Bhupendra Mithe
    '//============================================================================
```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
    Dim ObjPart As Part
```vbscript
    Set ObjPart = CATIA.ActiveDocument.Part
```

```

```vbscript
```vbscript
```vbscript
    'Get the Factory Object
    Dim FactoryObj As SfmFactory
    Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
    'Get the Manager Object
    Dim ManagerObj As SfmManager
    Set ManagerObj = FactoryObj.GetManager
    'Retrieving Super Plates
    Dim SuperPlates As References
    Set SuperPlates = ManagerObj.GetSuperPlates
    'Retrieving Operating Super Plate
    Dim SuperPlate1 As SfmSuperPlate
    Set SuperPlate1 = SuperPlates.Item(1)
    'Retrieving Operated Super Plate
    Dim SuperPlate2 As SfmSuperPlate
    Set SuperPlate2 = SuperPlates.Item(2)
    'Retrieving the SplitPlates of SuperPlate1
    Dim OperatingSplitPlateRefs As References
    Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates
    'Retrieving the SplitPlates of SuperPlate2
    Dim OperatedSplitPlateRefs As SfmSplitPlates
    Set OperatedSplitPlateRefs = SuperPlate2.SplitPlatesObjects

    Dim OperatingSplitPlate As Reference
    Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)

    Dim OperatedSplitPlate As SfmSplitPlate
    Set OperatedSplitPlate = OperatedSplitPlateRefs.Item(1)
    'Weld Use Case 1 features.
    Dim ListWeldsUC1 As SfmWelds
    Set ListWeldsUC1 = OperatedSplitPlate.GetWelds(OperatingSplitPlate)

    Dim WeldUC1Feature As SfmWeld
    Set WeldUC1Feature = ListWeldsUC1.Item(1)
```

```

```

```vbscript
    ustrWeldTypeUC1 = WeldUC1Feature.WeldType
    ustrAddedMaterialUC1 = WeldUC1Feature.AddedMaterial
    ustrFitUpUC1 = WeldUC1Feature.FitUp
    ustrEdgePrepUC1 = WeldUC1Feature.EdgePreparation
```vbscript
    'Weld Use Case 2 features.
```

```

```vbscript
    Dim ListWeldsUC2 As SfmWelds
```vbscript
```vbscript
    Set ListWeldsUC2 = OperatedSplitPlate.GetWelds(Nothing)

    Dim WeldUC2Feature As SfmWeld
    Set WeldUC2Feature = ListWeldsUC2.Item(1)

```

```

```

```vbscript
Dim WeldUC2Feature As SfmWeld
```vbscript
Set WeldUC2Feature = ListWeldsUC2.Item(1)
```

    ustrWeldTypeUC2 = WeldUC2Feature.WeldType
    ustrAddedMaterialUC2 = WeldUC2Feature.AddedMaterial
    ustrFitUpUC2 = WeldUC2Feature.FitUp
    ustrEdgePrepUC2 = WeldUC2Feature.EdgePreparation

```

```vbscript
    End Sub

```
