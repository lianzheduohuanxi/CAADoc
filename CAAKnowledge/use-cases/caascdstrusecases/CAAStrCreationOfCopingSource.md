---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIAStrFeatureFactory", "CATIA", "CAAStrCreateCoping"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfCopingSource.htmmd"
converted: "2026-05-11T11:27:02.582889"
---

```vbscript
Sub CATMain(#)
Dim StrWorkbench As StrWorkbench
Dim strFactory As StrObjectFactory

Set doc = CATIA.ActiveDocument
Dim rootProduct As Product
Set rootProduct = doc.Product
   
Set StrWorkbench = doc.GetWorkbench("StrWorkbench")
    
Dim strPlates As strPlates
Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
   
Dim strMembers As strMembers
Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")

'Case1: When Plate is limited by other Plate and Surface
```
'Get The Factory from Selection Method
```vbscript
Dim PlateToNibble As StrPlate
Set PlateToNibble = strPlates.Item("Deck_014.2")

Dim PlateSelection As Selection
Set PlateSelection = CATIA.ActiveDocument.Selection
PlateSelection.Add PlateToNibble
```
  
```vbscript
Dim FactoryForPlate As StrFeatureFactory
Set FactoryForPlate = PlateSelection.FindObject("CATIAStrFeatureFactory")

'Define the Limits for PlateToNibble
```
```vbscript
Dim Limitplate1 As StrPlate
Set Limitplate1 = strPlates.Item("Shell_002.1")

Dim LimitSurface1 As Reference
Set LimitSurface1 = rootProduct.CreateReferenceFromName("Product1/Part1.1/!Extrude.1")

Dim Listoflimits1(0) As Variant
Dim Listoflimits2(0) As Variant

Set Listoflimits1(0) = Limitplate1
Set Listoflimits2(0) = LimitSurface1

'Create Nibbling by defining Type and SubType
```
```vbscript
Dim NibblingFeature1, NibblingFeature2 As StrNibblingFeature

Set NibblingFeature1 = FactoryForPlate.AddNibbling(Listoflimits1, "Remove")
NibblingFeature1.SubType = "ButtButt"
```

```vbscript
Set NibblingFeature2 = FactoryForPlate.AddNibbling(Listoflimits2, "Remove")
NibblingFeature2.SubType = "CurrCurr"
```

'*******************************************************************
'Case2: When Member is limited by 2 Members and One Plate
'Get The Factory from Selection Method
```vbscript
Dim MembertoNibble1 As StrMember
Set MembertoNibble1 = strMembers.Item("BottShell_LStf_003.1")

Dim MemberSelection As Selection
Set MemberSelection = CATIA.ActiveDocument.Selection
MemberSelection.Add MembertoNibble1
```

```vbscript
Dim FactoryForMember As StrFeatureFactory
Set FactoryForMember = MemberSelection.FindObject("CATIAStrFeatureFactory")

'Define the Limits for  MembertoNibble1
```
```vbscript
Dim L1 As StrMember
Set L1 = strMembers.Item("Shell_VStf_006.1")

Dim L2 As StrMember
Set L2 = strMembers.Item("Shell_VStf_005.1")

Dim L3 As StrPlate
Set L3 = strPlates.Item("Shell_002.1")

Dim Listoflimits3(0) As Variant
Dim Listoflimits4(0) As Variant
Dim Listoflimits5(0) As Variant

Set Listoflimits5(0) = L3
Set Listoflimits3(0) = L1
Set Listoflimits4(0) = L2

'Create Nibbling by defining Type and SubType
```
```vbscript
Dim NibblingFeature3, NibblingFeature4, NibblingFeature5 As StrNibblingFeature

Set NibblingFeature3 = FactoryForMember.AddNibbling(Listoflimits3, "WeldCut")
Set NibblingFeature4 = FactoryForMember.AddNibbling(Listoflimits4, "LongPoint")
NibblingFeature4.Type = "ShortPoint"
```
```vbscript
Set NibblingFeature5 = FactoryForMember.AddNibbling(Listoflimits5, "Remove")

```

'*******************************************************************
'Case3: When Member is limited by Lateral Face of of Plate
'Get The Factory from Selection Method
```vbscript
Dim MembertoNibble2 As StrMember
Set MembertoNibble2 = strMembers.Item("Deck_TStf_005.1")

Dim Member2Sel As Selection
Set Member2Sel = CATIA.ActiveDocument.Selection
Member2Sel.Add MembertoNibble2
```

```vbscript
Dim FactoryForMember2 As StrFeatureFactory
Set FactoryForMember2 = Member2Sel.FindObject("CATIAStrFeatureFactory")

'Define the Limits for  MembertoNibble2
```
```vbscript
Dim L4 As StrPlate
Set L4 = strPlates.Item("Deck_014.2")

Dim ListofLimits6(0) As Variant
Set ListofLimits6(0) = L4

'Create Nibbling by defining the Extrapolation Offset
```
```vbscript
Dim NibblingFeature6 As StrNibblingFeature
Set NibblingFeature6 = FactoryForMember2.AddNibbling(ListofLimits6, "Remove")
NibblingFeature6.GetOffsetForExtrapolate ("25mm")
```

```vbscript
End Sub

```vbscript
```
```vbscript
Sub CATMain(#)
Dim StrWorkbench As StrWorkbench
Dim strFactory As StrObjectFactory

Set doc = CATIA.ActiveDocument
Dim rootProduct As Product
Set rootProduct = doc.Product
   
Set StrWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
    
Dim strPlates As strPlates
Set strPlates = rootProduct.GetTechnologicalObject(&quot;StructurePlates&quot;)
   
Dim strMembers As strMembers
Set strMembers = rootProduct.GetTechnologicalObject(&quot;StructureMembers&quot;)

'Case1: When Plate is limited by other Plate and Surface
```
'Get The Factory from Selection Method
```vbscript
Dim PlateToNibble As StrPlate
Set PlateToNibble = strPlates.Item(&quot;Deck_014.2&quot;)

Dim PlateSelection As Selection
Set PlateSelection = CATIA.ActiveDocument.Selection
PlateSelection.Add PlateToNibble
```
  
```vbscript
Dim FactoryForPlate As StrFeatureFactory
Set FactoryForPlate = PlateSelection.FindObject(&quot;CATIAStrFeatureFactory&quot;)

'Define the Limits for PlateToNibble
```
```vbscript
Dim Limitplate1 As StrPlate
Set Limitplate1 = strPlates.Item(&quot;Shell_002.1&quot;)

Dim LimitSurface1 As Reference
Set LimitSurface1 = rootProduct.CreateReferenceFromName(&quot;Product1/Part1.1/!Extrude.1&quot;)

Dim Listoflimits1(0) As Variant
Dim Listoflimits2(0) As Variant

Set Listoflimits1(0) = Limitplate1
Set Listoflimits2(0) = LimitSurface1

'Create Nibbling by defining Type and SubType
```
```vbscript
Dim NibblingFeature1, NibblingFeature2 As StrNibblingFeature

Set NibblingFeature1 = FactoryForPlate.AddNibbling(Listoflimits1, &quot;Remove&quot;)
NibblingFeature1.SubType = &quot;ButtButt&quot;
```

```vbscript
Set NibblingFeature2 = FactoryForPlate.AddNibbling(Listoflimits2, &quot;Remove&quot;)
NibblingFeature2.SubType = &quot;CurrCurr&quot;
```

'*******************************************************************
'Case2: When Member is limited by 2 Members and One Plate
'Get The Factory from Selection Method
```vbscript
Dim MembertoNibble1 As StrMember
Set MembertoNibble1 = strMembers.Item(&quot;BottShell_LStf_003.1&quot;)

Dim MemberSelection As Selection
Set MemberSelection = CATIA.ActiveDocument.Selection
MemberSelection.Add MembertoNibble1
```

```vbscript
Dim FactoryForMember As StrFeatureFactory
Set FactoryForMember = MemberSelection.FindObject(&quot;CATIAStrFeatureFactory&quot;)

'Define the Limits for  MembertoNibble1
```
```vbscript
Dim L1 As StrMember
Set L1 = strMembers.Item(&quot;Shell_VStf_006.1&quot;)

Dim L2 As StrMember
Set L2 = strMembers.Item(&quot;Shell_VStf_005.1&quot;)

Dim L3 As StrPlate
Set L3 = strPlates.Item(&quot;Shell_002.1&quot;)

Dim Listoflimits3(0) As Variant
Dim Listoflimits4(0) As Variant
Dim Listoflimits5(0) As Variant

Set Listoflimits5(0) = L3
Set Listoflimits3(0) = L1
Set Listoflimits4(0) = L2

'Create Nibbling by defining Type and SubType
```
```vbscript
Dim NibblingFeature3, NibblingFeature4, NibblingFeature5 As StrNibblingFeature

Set NibblingFeature3 = FactoryForMember.AddNibbling(Listoflimits3, &quot;WeldCut&quot;)
Set NibblingFeature4 = FactoryForMember.AddNibbling(Listoflimits4, &quot;LongPoint&quot;)
NibblingFeature4.Type = &quot;ShortPoint&quot;
```
```vbscript
Set NibblingFeature5 = FactoryForMember.AddNibbling(Listoflimits5, &quot;Remove&quot;)

```

'*******************************************************************
'Case3: When Member is limited by Lateral Face of of Plate
'Get The Factory from Selection Method
```vbscript
Dim MembertoNibble2 As StrMember
Set MembertoNibble2 = strMembers.Item(&quot;Deck_TStf_005.1&quot;)

Dim Member2Sel As Selection
Set Member2Sel = CATIA.ActiveDocument.Selection
Member2Sel.Add MembertoNibble2
```

```vbscript
Dim FactoryForMember2 As StrFeatureFactory
Set FactoryForMember2 = Member2Sel.FindObject(&quot;CATIAStrFeatureFactory&quot;)

'Define the Limits for  MembertoNibble2
```
```vbscript
Dim L4 As StrPlate
Set L4 = strPlates.Item(&quot;Deck_014.2&quot;)

Dim ListofLimits6(0) As Variant
Set ListofLimits6(0) = L4

'Create Nibbling by defining the Extrapolation Offset
```
```vbscript
Dim NibblingFeature6 As StrNibblingFeature
Set NibblingFeature6 = FactoryForMember2.AddNibbling(ListofLimits6, &quot;Remove&quot;)
NibblingFeature6.GetOffsetForExtrapolate (&quot;25mm&quot;)
```

```vbscript
End Sub
```
```