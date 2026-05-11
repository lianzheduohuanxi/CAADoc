---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAArrCreateRunSource", "CAAScdInfUseCases", "CAAScrJavaScript", "CAAlink", "CAAScdArrUseCases", "CATIA", "CAAArrCreateRun"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateRun.htm"
converted: "2026-05-11T11:06:32.737684"
---

## Arrangement
 
 
## []Creating an ArrangementRun Object
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create an *ArrangementRun*
 under a product.
 

This macro opens a new Product document and retrieves the [*ArrangementRuns*]
 collection from the root [*Product*]
 via the [*ArrangementProduct*]
 object. It then adds an [*ArrangementRun*]
 object. Once the *ArrangementRun* object is created, the individual [*ArrangementNode*]'s
 that make up the object are retrieved and the bend radius is applied on
 them.
 

![](images/CAAArrCreateRun.jpg)
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAArrCreateRun is launched in CATIA [[1]].
 No open document is needed.
 

[CAAArrCreateRun.CATScript ]is
 located in the CAAScdArrUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAArrCreateRun includes the following steps:
 

 
- [Prolog]
 
- [Obtaining the ArrangementProduct Object and the
 Associated Movable Object from the Root Product]
 
- [Creating the ArrangementRun Object under the
 ArrangementRuns Collection Object]
 
- [Modifying Properties (Defining a Rectangular
 Section, Changing the Visualization Mode and Bend Radii of the Nodes)
 of the Newly Created ArrangementRun Object]
 
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

 
 
 
 

Once the new product document has been created, fetch the *ArrangementProduct*
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

 
 
 
 

The *ArrangementRuns* object is a collection object that manages *ArrangementRun*
 object's under a given *ArrangementProduct*. The movable object
 serves as the relative axis for the new *ArrangementRun* object to be
 created.
 
#### []Creating the ArrangementRun Object under the
 ArrangementRuns Collection Object
 
 
 
```
...
 
' Create ArrangementRun under the Root Product

 Dim 
dblRunPoints(75) 
 As 
Double

 Dim 
dblMathDirection(3) 
 As 
Double

 Dim 
objArrRun 
 As 
ArrangementRun

 dblRunPoints(0) = 300.0
 dblRunPoints(1) = 100.0
 dblRunPoints(2) = 0.0

 dblRunPoints(3) = 441.42
 dblRunPoints(4) = 158.58
 dblRunPoints(5) = 1.25

 ...

 dblRunPoints(72) = 300.0
 dblRunPoints(73) = 100.0
 dblRunPoints(74) = 30

 dblMathDirection(0) = 1.0
 dblMathDirection(1) = 0.0
 dblMathDirection(2) = 0.0

 Set 
objArrRun = objArrProd.ArrangementRuns.AddRun(objMove,dblRunPoints, dblMathDirection)
 ...
```

 
 
 
 

The newly created *ArrangementRun* object is visualized as a curve
 and does not have any section definition. In addition the nodes do not
 have any bend radius.
 
#### []Modifying Properties (Defining a Rectangular
 Section, Changing the Visualization Mode and Bend Radii of the Nodes) of
 the Newly Created ArrangementRun Object
 
 
 
```
...
 objArrRun.SectionType = CatArrangementRouteSectionRound
 objArrRun.SectionDiameter = 10.0
 objArrRun.VisuMode = CatArrangementRouteVisuModeSolid

 
'----------------------------------------------

 
' Change Properties of ArrangementRun

 Dim 
intK
 As 
Integer 

 For 
intK = 1
 To 
objArrRun.Nodes.Count
 
 objArrRun.Nodes.Item(intK).BendRadius = 10.0
 

 Next

 objArrRun.SectionType = CatArrangementRouteSectionRound
 objArrRun.SectionDiameter = 10.0
 objArrRun.VisuMode = CatArrangementRouteVisuModeSolid

 
'----------------------------------------------

 
' Define Bend Radius of Nodes

 Dim 
intK
 As 
Integer 

 For 
intK = 1
 To 
objArrRun.Nodes.Count
 objArrRun.Nodes.Item(intK).BendRadius = 10.0

 Next

 ...
```

 
 
 
 

Here we define a round section and change the visualization mode to `CatArrangementRouteVisuModeSolid`.
 A bend radius of 10 mm is then applied to each of the *ArrangementNodes*
 that makes up the object.
 
#### []Epilog
 
 
 
```
...
 End Sub
```

 
 
 
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create an *ArrangementRun* object within
a product document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2}
 |*[ArrangementRuns],
 [Product],
 [ArrangementProduct],
 [ArrangementRun],
 [ArrangementNode]*
 
 
 |[[Top]]

---

*Copyright 2000, Dassault Systmes. All rights reserved.*