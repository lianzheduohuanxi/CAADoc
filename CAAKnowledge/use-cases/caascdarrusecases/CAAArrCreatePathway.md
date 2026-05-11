---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAArrCreatePathwaySource", "CAAArrCreatePathway", "CAAScdInfUseCases", "CAAlink", "CAAScdArrUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreatePathway.htm"
converted: "2026-05-11T11:06:32.746181"
---

## Arrangement
 
 
## []Creating an ArrangementPathway Object
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create an *ArrangementPathway*
 under a product.
 

This macro opens a new product document and retrieves the [*ArrangementPathways*]
 collection from the root [*Product*]
 via the [*ArrangementProduct*]
 object. It then adds an [*ArrangementPathway*]
 object. Once the *ArrangementPathway* object is created, the
 individual [*ArrangementNode*]'s
 that make up the object are retrieved and the bend radius is applied on
 them.
 

![](images/CAAArrCreatePathway.jpg)
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAArrCreatePathway is launched in CATIA [[1]].
 No open document is needed.
 

[CAAArrCreatePathway.CATScript ]is
 located in the CAAScdArrUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAArrCreatePathway includes the following steps:
 

 
- [Prolog]
 
- [Obtaining the ArrangementProduct Object and the
 Associated Movable Object from the Root Product]
 
- [Creating the ArrangementPathway Object under the
 ArrangementPathways Collection Object]
 
- [Modifying Properties (Defining a Round Section,
 Changing the Visualization Mode and Bend Radii of the Nodes) of the
 Newly Created ArrangementPathway Object]
 
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

 
 
 
 

The *ArrangementPathways* object is a collection object that
 manages *ArrangementPathway* object's under a given *ArrangementProduct*.
 The movable object serves as the relative axis for the new *ArrangementPathway*
 object to be created.
 
#### []Creating the ArrangementPathway Object under
 the ArrangementPathways Collection Object
 
 
 
```
...
 
' Create ArrangementPathway under the Root Product

 Dim 
dblPathwayPoints(75) 
 As 
Double

 Dim 
dblMathDirection(3) 
 As 
Double

 Dim 
objArrPathway 
 As 
ArrangementPathway

 dblPathwayPoints(0) = 300.0
 dblPathwayPoints(1) = 100.0
 dblPathwayPoints(2) = 0.0

 dblPathwayPoints(3) = 441.42
 dblPathwayPoints(4) = 158.58
 dblPathwayPoints(5) = 1.25

...

 dblPathwayPoints(72) = 300.0
 dblPathwayPoints(73) = 100.0
 dblPathwayPoints(74) = 30

 dblMathDirection(0) = 1.0
 dblMathDirection(1) = 0.0
 dblMathDirection(2) = 0.0

 Set 
objArrPathway = objArrProd.ArrangementPathways.AddPathway(objMove, _
 dblPathwayPoints, _
 dblMathDirection)
 ...
```

 
 
 
 

The newly created *ArrangementPathway* object is visualized as a
 curve and does not have any section definition. In addition the nodes do
 not have any bend radius. 
 
#### []Modifying Properties (Defining a Round Section,
 Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly
 Created ArrangementPathway Object
 
 
 
```
...
 
'----------------------------------------------
 

 ' Change Properties of ArrangementPathway
 
objArrPathway.SectionType = CatArrangementRouteSectionRound
 objArrPathway.SectionDiameter = 10.0
 objArrPathway.VisuMode = CatArrangementRouteVisuModeSolid

 
' Define Bend Radius of Nodes

 
'----------------------------------------------
 

 
 Dim 
intK
 As 
Integer 

 For 
intK = 1
 To 
objArrPathway.Nodes.Count
 objArrPathway.Nodes.Item(intK).BendRadius = 10.0

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

This use case has shown how to create an *ArrangementPathway* object
within a product document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[ArrangementPathways],
 [Product],
 [ArrangementProduct],
 [ArrangementPathway],
 [ArrangementNode]*
 
 
 |[[Top]]

---

*Copyright 2000, Dassault Systmes. All rights reserved.*