---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAArrCreateBoundary", "CAAScdInfUseCases", "CAAlink", "CAAArrCreateBoundarySource", "CAAScdArrUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateBoundary.htm"
converted: "2026-05-11T11:06:32.728658"
---

## Arrangement
 
 
## []Creating an ArrangementBoundary Object
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create an
 ArrangementBoundary object under a Product.
 

This macro opens a new Product document and retrieves the [*ArrangementBoundaries*]
 collection from the Root [*Product*]
 via the [*ArrangementProduct*]
 object. It then adds an [*ArrangementBoundary*]
 object. Once the *ArrangementBoundary* object is created, the
 individual [*ArrangementNode*]'s
 that make up the object are retrieved and the bend radius is applied on
 them.
 

![](images/CAAArrCreateBoundary.jpg)
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAArrCreateBoundary is launched in CATIA [[1]].
 No open document is needed.
 

[CAAArrCreateBoundary.CATScript
 ]is located in the CAAScdArrUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAArrCreateBoundary includes the following steps:
 

 
- [Prolog]
 
- [Obtaining the ArrangementProduct Object and the
 Associated Movable Object from the Root Product]
 
- [Creating the ArrangementBoundary Object under
 the ArrangementBoundaries Collection Object]
 
- [Modifying Properties (Defining a Rectangular
 Section, Changing the Visualization Mode and Bend Radii of the Nodes)
 of the Newly Created ArrangementBoundary object]
 
- [Epilog]
 
 
#### []Prolog
 
 
 
```
...
 
'----------------------------------------------

 
'Create a new product document

 Dim 
objProdDoc 
 As 
ProductDocument

 Dim 
objRootProd 
 As 
Product

 Set 
objProdDoc = CATIA.Documents.Add("Product")

 Set 
objRootProd = objProdDoc.Product
 ...
```

 
 
 
 

Once the new Product document has been created, fetch the *ArrangementProduct*
 and the associated movable object from the root product of the new product
 document.
 
#### []Obtaining the ArrangementProduct Object and
 the Associated Movable Object from the Root Product
 
 
 
```
...
 
'----------------------------------------------

 
'Retrieving Root Product's Relative Axis and Position Information

 Dim 
objMove 
 As 
Move

 Set 
objMove = objRootProd.Move

 
'----------------------------------------------

 
' Get ArrangementProduct

 Dim 
objArrProd 
 As 
ArrangementProduct

 Set 
objArrProd = objRootProd.GetTechnologicalObject("ArrangementProduct")
...
```

 
 
 
 

The *ArrangementBoundaries* object is a collection object that
 manages *ArrangementBoundary* object's under a given *ArrangementProduct*.
 The movable object serves as the relative axis for the new *ArrangementBoundary*
 object to be created.
 
#### []Creating the ArrangementBoundary Object under
 the ArrangementBoundaries Collection Object
 
 
 
```
...
 
' Create ArrangementBoundary under the Root Product

 Dim 
dblBoundaryPoints(75) 
 As 
Double

 Dim 
dblMathDirection(3) 
 As 
Double

 Dim 
objArrBoundary 
 As 
ArrangementBoundary

 dblBoundaryPoints(0) = 300.0
 dblBoundaryPoints(1) = 100.0
 dblBoundaryPoints(2) = 0.0

 dblBoundaryPoints(3) = 441.42
 dblBoundaryPoints(4) = 158.58
 dblBoundaryPoints(5) = 1.25

 ... 

 dblBoundaryPoints(69) = 158.58
 dblBoundaryPoints(70) = 158.58
 dblBoundaryPoints(71) = 28.75

 dblBoundaryPoints(72) = 300.0
 dblBoundaryPoints(73) = 100.0
 dblBoundaryPoints(74) = 30

 dblMathDirection(0) = 1.0
 dblMathDirection(1) = 0.0
 dblMathDirection(2) = 0.0

 Set 
objArrBoundary = objArrProd.ArrangementBoundaries.AddBoundary(objMove, _
 dblBoundaryPoints, _
 dblMathDirection)
 ...
```

 
 
 
 

The newly created *ArrangementBoundary* object is visualized as a
 curve and does not have any section definition. In addition the nodes do
 not have any bend radius. We therefore define a rectangular section and
 change the visualization mode to solid.
 
#### []Modifying Properties (Defining a Rectangular
 Section, Changing the Visualization Mode and Bend Radii of the Nodes) of
 the Newly Created ArrangementBoundary Object
 
 
 
```
...
 objArrBoundary.SectionType = CatArrangementRouteSectionRectangular
 objArrBoundary.SectionWidth = 10.0
 objArrBoundary.SectionHeight = 10.0 
 objArrBoundary.VisuMode = CatArrangementRouteVisuModeSolid

 
' Define Bend Radius of Nodes

 Dim 
intK 
 As 
Integer

 For 
intK = 1
 To 
objArrBoundary.Nodes.Count
 objArrBoundary.Nodes.Item(intK).BendRadius = 10.0

 Next

 ...
```

 
 
 
 

Here we define a rectangular section and change the visualization mode
 to `CatArrangementRouteVisuModeSolid`. A bend radius of 10 mm
 is then applied to each of the *ArrangementNodes* that makes up the
 object.
 
#### []Epilog
 
 
 
```
...
 End Sub
```

 
 
 
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create an *ArrangementBoundary* object
within a product document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[ArrangementBoundaries],
 [Product],
 [ArrangementProduct],
 [ArrangementBoundary],
 [ArrangementNode].*
 
 
 |[[Top]]
 

---

*Copyright 2000, Dassault Systmes. All rights reserved.*