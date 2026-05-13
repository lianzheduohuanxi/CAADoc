---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAStrCreationOfCutoutSource", "CAAScdInfUseCases", "CAAScdStrCutout01", "CAAScdStrCutout02", "CAAStrCreateCutout", "CAAScdStrUseCases", "CAAInfLauchMacro", "CATIAStrFeatureFactory"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfCutout.htmmd"
converted: "2026-05-11T11:27:02.602438"
---

---

![End Task Icon](./assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create cutout on structure objects.

[Top]

---

#### References

---

*Copyright  1999-2010, Dassault Systmes. All rights reserved.*

```vbscript
```vbscript
Dim doc As Document

Dim StrWorkbench As StrWorkbench
Dim strFactory As StrObjectFactory

Set doc = CATIA.ActiveDocument

Dim rootProduct As Product
Set rootProduct = doc.Product
   
Set StrWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
    
Dim strPlates As strPlates
Set strPlates = rootProduct.GetTechnologicalObject(&quot;StructurePlates&quot;)
```
```

```vbscript
&#39;Get the Factory from Selection Method
```vbscript
Dim PlateToCut1 As StrPlate
Set PlateToCut1 = strPlates.Item(&quot;Plate_052&quot;)

Dim Selection1 As Selection
Set Selection1 = CATIA.ActiveDocument.Selection
Selection1.Add PlateToCut1
```
  
```vbscript
Dim Factory1 As StrFeatureFactory
Set Factory1 = Selection1.FindObject(&quot;CATIAStrFeatureFactory&quot;)
```
```

```vbscript
&#39;Define the Sketch
```vbscript
Dim sketch As Reference
Set sketch1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Sketch.1&quot;)

&#39;Define the Direction by selecting sketch containing line
```
```vbscript
Dim dir1 As Reference
Set dir1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Sketch.3&quot;)

'Create the Cutout
```
```vbscript
Dim Cutout1 As StrCutoutFeature
Set Cutout1 = Factory1.AddCutoutWithAfterFormingMode(sketch1, dir1)
```
```

```vbscript
&#39;Define the Sketch
```vbscript
Dim sketch As Reference
Set sketch1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Sketch.1&quot;)

&#39;Define the Surface 
```
```vbscript
Dim Sur1 As Reference
Set Sur1 = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Extrude.1&quot;)

'Create the Cutout
```
```vbscript
Dim Cutout2 As StrCutoutFeature
Set Cutout2 = Factory2.AddCutoutWithBeforeFormingMode(sketch1, Sur1)
```
```