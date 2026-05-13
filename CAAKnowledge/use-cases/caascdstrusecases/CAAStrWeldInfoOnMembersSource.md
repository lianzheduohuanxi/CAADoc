---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAStrWeldInfoOnMembers", "CATIASfmMember"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrWeldInfoOnMembersSource.htmmd"
converted: "2026-05-11T11:27:02.585366"
---

'//============================================================================
'// COPYRIGHT DASSAULT SYSTEMES 2013
'//============================================================================
'// Language="VBSCRIPT"
'// Sample of macro for getting weld information on structural objects.
'//============================================================================
'// 03/21/2013  Creation                                                    BE9
'//============================================================================

```cpp
Sub CATMain(#)

Dim ObjPart As Part
Set ObjPart = CATIA.ActiveDocument.Part
   
Dim FactoryObj As SfmFactory
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
  
Dim ManagerObj As SfmManager
Set ManagerObj = FactoryObj.GetManager

'RETRIEVING THE SUPERMembers
```
```vbscript
Dim SuperMembers As References
Set SuperMembers = ManagerObj.GetSuperMembers

Dim SuperMember1 As SfmMember
Set SuperMember1 = SuperMembers.Item(1)

'Retrieving The Split Members
```
```cpp
Dim SplitMembers As References
Set SplitMembers = SuperMember1.SplitProfiles

Dim SplitMember1 As Reference
Set SplitMember1 = SplitMembers.Item(1)

Set SelctionObj = CATIA.ActiveDocument.Selection
'DECK Member
```
SelctionObj.Add SplitMember1
```cpp
Dim DeckMember1 As SfmMember
Set DeckMember1 = SelctionObj.FindObject("CATIASfmMember")

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

'Retrieving the SplitPlates of SuperPlate1
```
```vbscript
Dim OperatingSplitPlateRefs As References
Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates

Dim OperatingSplitPlate As Reference
Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)

Dim WeldsUC1 As SfmWelds
Set WeldsUC1 = DeckMember1.GetWelds(OperatingSplitPlate)

Dim WeldUC1 As SfmWeld
Set WeldUC1 = WeldsUC1.Item(1)

```

ustrWeldTypeUC1 = WeldUC1.WeldType
ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
ustrFitUpUC1 = WeldUC1.FitUp
ustrEdgePrepUC1 = WeldUC1.EdgePreparation

```vbscript
Dim WeldsUC2 As SfmWelds
Set WeldsUC2 = DeckMember1.GetWelds(Nothing)

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

```vbscript
'//============================================================================
'// COPYRIGHT DASSAULT SYSTEMES 2013
'//============================================================================
'// Language="VBSCRIPT"
'// Sample of macro for getting weld information on structural objects.
'//============================================================================
'// 03/21/2013  Creation                                                    BE9
'//============================================================================

```cpp
Sub CATMain(#)

Dim ObjPart As Part
Set ObjPart = CATIA.ActiveDocument.Part
   
Dim FactoryObj As SfmFactory
Set FactoryObj = ObjPart.GetCustomerFactory("SfmFactory")
  
Dim ManagerObj As SfmManager
Set ManagerObj = FactoryObj.GetManager

'RETRIEVING THE SUPERMembers
```
```vbscript
Dim SuperMembers As References
Set SuperMembers = ManagerObj.GetSuperMembers

Dim SuperMember1 As SfmMember
Set SuperMember1 = SuperMembers.Item(1)

'Retrieving The Split Members
```
```cpp
Dim SplitMembers As References
Set SplitMembers = SuperMember1.SplitProfiles

Dim SplitMember1 As Reference
Set SplitMember1 = SplitMembers.Item(1)

Set SelctionObj = CATIA.ActiveDocument.Selection
'DECK Member
```
SelctionObj.Add SplitMember1
```cpp
Dim DeckMember1 As SfmMember
Set DeckMember1 = SelctionObj.FindObject("CATIASfmMember")

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

'Retrieving the SplitPlates of SuperPlate1
```
```vbscript
Dim OperatingSplitPlateRefs As References
Set OperatingSplitPlateRefs = SuperPlate1.SplitPlates

Dim OperatingSplitPlate As Reference
Set OperatingSplitPlate = OperatingSplitPlateRefs.Item(1)

Dim WeldsUC1 As SfmWelds
Set WeldsUC1 = DeckMember1.GetWelds(OperatingSplitPlate)

Dim WeldUC1 As SfmWeld
Set WeldUC1 = WeldsUC1.Item(1)

```

ustrWeldTypeUC1 = WeldUC1.WeldType
ustrAddedMaterialUC1 = WeldUC1.AddedMaterial
ustrFitUpUC1 = WeldUC1.FitUp
ustrEdgePrepUC1 = WeldUC1.EdgePreparation

```vbscript
Dim WeldsUC2 As SfmWelds
Set WeldsUC2 = DeckMember1.GetWelds(Nothing)

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