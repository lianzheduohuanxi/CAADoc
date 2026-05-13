---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIAStrFeatureFactory", "CATIA", "CAAStrCreateCutout"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfCutoutSource.htmmd"
converted: "2026-05-11T11:27:02.589968"
---

```cpp
Sub CATMain(#)

Dim doc As Document

  Dim StrWorkbench As StrWorkbench
  Dim strFactory As StrObjectFactory

  Set doc = CATIA.ActiveDocument
  Dim rootProduct As Product
  Set rootProduct = doc.Product
   
  Set StrWorkbench = doc.GetWorkbench("StrWorkbench")
    
  Dim strPlates As strPlates
  Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")

  Dim sketch As Reference
  Set sketch1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.1")

  '*************************First Cutout**************************************************
```
```cpp
  Dim PlateToCut1 As StrPlate
  Set PlateToCut1 = strPlates.Item("Plate_052")

  Dim Selection1 As Selection
  Set Selection1 = CATIA.ActiveDocument.Selection
  Selection1.Add PlateToCut1
```
  
```cpp
  Dim Factory1 As StrFeatureFactory
  Set Factory1 = Selection1.FindObject("CATIAStrFeatureFactory")

  Dim dir1 As Reference
  Set dir1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.3")

  Dim Cutout1 As StrCutoutFeature
  Set Cutout1 = Factory1.AddCutoutWithAfterFormingMode(sketch1, dir1)
 
  '*************************Second  Cutout**************************************************
```
```cpp
  Dim PlateToCut2 As StrPlate
  Set PlateToCut2 = strPlates.Item("Plate_053")

  Dim Selection2 As Selection
  Set Selection2 = CATIA.ActiveDocument.Selection
  Selection2.Add PlateToCut2
```

```cpp
  Dim Factory2 As StrFeatureFactory
  Set Factory2 = Selection2.FindObject("CATIAStrFeatureFactory")

  Dim Sur1 As Reference
  Set Sur1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Extrude.1")

  Dim Cutout2 As StrCutoutFeature
  Set Cutout2 = Factory2.AddCutoutWithBeforeFormingMode(sketch1, Sur1)

End Sub

```vbscript
```
```cpp
Sub CATMain(#)

Dim doc As Document

  Dim StrWorkbench As StrWorkbench
  Dim strFactory As StrObjectFactory

  Set doc = CATIA.ActiveDocument
  Dim rootProduct As Product
  Set rootProduct = doc.Product
   
  Set StrWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
    
  Dim strPlates As strPlates
  Set strPlates = rootProduct.GetTechnologicalObject(&quot;StructurePlates&quot;)

  Dim sketch As Reference
  Set sketch1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Sketch.1&quot;)

  '*************************First Cutout**************************************************
```
```cpp
  Dim PlateToCut1 As StrPlate
  Set PlateToCut1 = strPlates.Item(&quot;Plate_052&quot;)

  Dim Selection1 As Selection
  Set Selection1 = CATIA.ActiveDocument.Selection
  Selection1.Add PlateToCut1
```
  
```cpp
  Dim Factory1 As StrFeatureFactory
  Set Factory1 = Selection1.FindObject(&quot;CATIAStrFeatureFactory&quot;)

  Dim dir1 As Reference
  Set dir1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Sketch.3&quot;)

  Dim Cutout1 As StrCutoutFeature
  Set Cutout1 = Factory1.AddCutoutWithAfterFormingMode(sketch1, dir1)
 
  '*************************Second  Cutout**************************************************
```
```cpp
  Dim PlateToCut2 As StrPlate
  Set PlateToCut2 = strPlates.Item(&quot;Plate_053&quot;)

  Dim Selection2 As Selection
  Set Selection2 = CATIA.ActiveDocument.Selection
  Selection2.Add PlateToCut2
```

```cpp
  Dim Factory2 As StrFeatureFactory
  Set Factory2 = Selection2.FindObject(&quot;CATIAStrFeatureFactory&quot;)

  Dim Sur1 As Reference
  Set Sur1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Extrude.1&quot;)

  Dim Cutout2 As StrCutoutFeature
  Set Cutout2 = Factory2.AddCutoutWithBeforeFormingMode(sketch1, Sur1)

End Sub
```
```