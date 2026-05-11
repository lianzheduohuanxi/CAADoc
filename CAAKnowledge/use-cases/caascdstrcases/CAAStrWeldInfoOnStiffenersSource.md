---
title: "CAAStrWeldInfoOnStiffener.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrWeldInfoOnStiffener", "CATIASfmStiffener"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnStiffenersSource.htm"
converted: "2026-05-11T17:31:50.924560"
---

```vbscript
    '//============================================================================
    '// COPYRIGHT DASSAULT SYSTEMES 2013
    '//============================================================================
    '// Language="VBSCRIPT"
    '// Sample of macro for getting weld information on SDD Stiffeners.
    '//============================================================================
    '// Mar  Creation                                               Bhupendra Mithe
    '//============================================================================
```

    
```vbscript
    Sub CATMain()
    
```vbscript
    Dim ObjPart As Part
    Set ObjPart = CATIA.ActiveDocument.Part
       
    Dim FactoryObj As SfmFactory
    Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
      
    Dim ManagerObj As SfmManager
    Set ManagerObj = FactoryObj.GetManager
```vbscript
    'RETRIEVING THE SUPERSTIFFENERS
    Dim SuperStiffeners As References
    Set SuperStiffeners = ManagerObj.GetSuperStiffeners
    
    Dim SuperStiffener1 As SfmStiffener
    Set SuperStiffener1 = SuperStiffeners.Item(1)
    'Retrieving The Seamed Stiffeners on Deck
    Dim SplitStiffeners As References
    Set SplitStiffeners = SuperStiffener1.SplitProfiles
    
    Dim SplitStiffener1 As Reference
    Set SplitStiffener1 = SplitStiffeners.Item(1)
    
    Set SelctionObj = CATIA.ActiveDocument.Selection
    'DECK STIFFENER
```

    SelctionObj.Add SplitStiffener1
    Dim DeckStiffener1 As SfmStiffener
    Set DeckStiffener1 = SelctionObj.FindObject("CATIASfmStiffener")
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
    
    Dim WeldsUC1 As SfmWelds
    Set WeldsUC1 = DeckStiffener1.GetWelds(OperatingSplitPlate)
    
    Dim WeldUC1 As SfmWeld
    Set WeldUC1 = WeldsUC1.Item(1)
```

    
```

    ustrWeldTypeUC1 = WeldUC1.WeldType
    ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
    ustrFitUpUC1 = WeldUC1.FitUp
    ustrEdgePrepUC1 = WeldUC1.EdgePreparation
    
```vbscript
    Dim WeldsUC2 As SfmWelds
    Set WeldsUC2 = DeckStiffener1.GetWelds(Nothing)
    
    Dim WeldUC2 As SfmWeld
    Set WeldUC2 = WeldsUC2.Item(1)
    
```

    ustrWeldTypeUC2 = WeldUC2.WeldType
    ustrAddedMaterialUC2 = WeldUC2.AddedMaterial
    ustrFitUpUC2 = WeldUC2.FitUp
    ustrEdgePrepUC2 = WeldUC2.EdgePreparation
    
    
```vbscript
    End Sub

```
```