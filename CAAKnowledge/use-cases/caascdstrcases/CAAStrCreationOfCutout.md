---
title: "Creating Cutouts"
category: "use-case"
module: "CAAScdStrUseCases"
tags: "["CATIA", "CATIAStrFeatureFactory", "CAAStrCreateCutout", "CAAScdStrUseCases"]"
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfCutout.htm"
converted: "2026-05-11T17:31:50.872122"
---
## Structure Design

|
## Creating Cutouts

* * *

  This macro shows you how to create cutout on structure objects. Here we will place cutout on Plate using After Forming as well as Before Forming modes. ![Starting Product](images/CAAScdStrCutout01.png)
---|---
  CAAStrCreateCutout is launched in CATIA [1]. Some documents are needed.

  * [CAAStrCreateCutout.CATScript](CAAStrCreationOfCutoutSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrCreateCutout.CATScript) (Windows only).
  * The document Product1.CATProduct is located in the CAAScdStrUseCases module in the samples directory. Grid.CATPart is linked to the previous document and it contains the grid, sketches and surfaces used by the macro.
  * The CATPart containing the section is located in the samples directory.

  CAAStrCreateCutout includes four steps:

  1. Prolog
  2. Retrieving the Factory from Object on which Cutout Is to Be Placed
  3. Defining Sketch and Direction (After Forming Mode)
  4. Defining Sketch and Surface (Before Forming Mode)

#### Prolog

```vbscript
```vbscript
```vbscript
    Dim doc As Document

    Dim StrWorkbench As StrWorkbench
```
```

```vbscript
```vbscript
```cpp
    Dim strFactory As StrObjectFactory

    Set doc = CATIA.ActiveDocument

    Dim rootProduct As Product
    Set rootProduct = doc.Product

    Set StrWorkbench = doc.GetWorkbench("StrWorkbench")

    Dim strPlates As strPlates
    Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")

```
```

```

```

#### Retrieving the Factory from Object on which Cutout Is to Be Placed

```vbscript
```vbscript
Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
```
```

This step describes how to get Structure Feature Factory. The Factory object is retrieved by adding object on which cutout is to be placed to the selection list.

```vbscript
```vbscript
    'Get the Factory from Selection Method

```

```

```vbscript
```vbscript
    Dim PlateToCut1 As StrPlate
```vbscript
```
```vbscript
```cpp
    Set PlateToCut1 = strPlates.Item("Plate_052")

    Dim Selection1 As Selection
    Set Selection1 = CATIA.ActiveDocument.Selection
```
```

```

    Selection1.Add PlateToCut1

```vbscript
    Dim Factory1 As StrFeatureFactory
```vbscript
```
```vbscript
```cpp
    Set Factory1 = Selection1.FindObject("CATIAStrFeatureFactory")

```
```

```

```

#### Defining Sketch and Direction (After Forming Mode)

```vbscript
```vbscript
For placing cutout using After Forming Mode you need to select a sketch and a direction.

```

```

```vbscript
For placing cutout using After Forming Mode you need to select a sketch and a direction.
```vbscript
    'Define the Sketch
```

```

```vbscript
```vbscript
    Dim sketch As Reference
```vbscript
```
```vbscript
    Set sketch1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.1")
```
```

```

```vbscript
```vbscript
```vbscript
    'Define the Direction by selecting sketch containing line
```vbscript
    Dim dir1 As Reference
    Set dir1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.3")
    'Create the Cutout
```
```vbscript
    Dim Cutout1 As StrCutoutFeature
    Set Cutout1 = Factory1.AddCutoutWithAfterFormingMode(sketch1, dir1)
```
```

```

```

#### Defining Sketch and Surface (Before Forming Mode)

```vbscript
```vbscript
For placing cutout using Before Forming Mode you need to select a sketch and a Surface.

```

```

```vbscript
For placing cutout using Before Forming Mode you need to select a sketch and a Surface.
```vbscript
    'Define the Sketch
```

```

```vbscript
```vbscript
    Dim sketch As Reference
```vbscript
```
```vbscript
    Set sketch1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.1")
```
```

```

```vbscript
```vbscript
```vbscript
    'Define the Surface
```vbscript
    Dim Sur1 As Reference
    Set Sur1 = rootProduct.CreateReferenceFromName("Product1/Grid/!Extrude.1")
    'Create the Cutout
```
```vbscript
    Dim Cutout2 As StrCutoutFeature
    Set Cutout2 = Factory2.AddCutoutWithBeforeFormingMode(sketch1, Sur1)
```
```

```

```

![Resulting Product](images/CAAScdStrCutout02.png)

![End Task Icon](./assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create cutout on structure objects.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

[Top]

* * *

_Copyright 1999-2010, Dassault Systmes. All rights reserved._
