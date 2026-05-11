---
```vbscript
title: "Creating an ArrangementPathway Object"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CATIA", "CAAArrCreatePathway", "CAAScdArrUseCases"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreatePathway.htm"
converted: "2026-05-11T17:31:51.563057"
```

---
|
## Arrangement

|
## Creating an ArrangementPathway Object

* * *

  This macro shows you how to create an _ArrangementPathway_ under a product. This macro opens a new product document and retrieves the _ArrangementPathways_ collection from the root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementPathway_ object. Once the _ArrangementPathway_ object is created, the individual _ArrangementNode_'s that make up the object are retrieved and the bend radius is applied on them. ![](images/CAAArrCreatePathway.jpg)
---|---
This macro shows you how to create an _ArrangementPathway_ under a product. This macro opens a new product document and retrieves the _ArrangementPathways_ collection from the root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementPathway_ object. Once the _ArrangementPathway_ object is created, the individual _ArrangementNode_'s that make up the object are retrieved and the bend radius is applied on them. ![](images/CAAArrCreatePathway.jpg)
  CAAArrCreatePathway is launched in CATIA [1]. No open document is needed. [CAAArrCreatePathway.CATScript ](CAAArrCreatePathwaySource.md)is located in the CAAScdArrUseCases module. [Execute macro](macros/CAAArrCreatePathway.CATScript) (Windows only).
  CAAArrCreatePathway includes the following steps:

  1. Prolog
  2. Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
  3. Creating the ArrangementPathway Object under the ArrangementPathways Collection Object
  4. Modifying Properties (Defining a Round Section, Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly Created ArrangementPathway Object
  5. Epilog

#### Prolog

|

      ...
```vbscript
       '----------------------------------------------
```

```vbscript
```vbscript
```vbscript
'----------------------------------------------
       'Create a new product document
```

```

```

```vbscript
       Dim objProdDoc        As ProductDocument
```vbscript
```vbscript
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
```

```

```

       ...

---

Once the new product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.
#### Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product

    ...
Once the new product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.
```vbscript
```vbscript
       '----------------------------------------------
       'Retrieving Root Product's Relative Axis and Position Information

```

```

```vbscript
       Dim objMove           As Move
```vbscript
       Set objMove      = objRootProd.Move
```

```

```vbscript
```vbscript
```vbscript
       '----------------------------------------------
       ' Get ArrangementProduct
       Dim objArrProd        As ArrangementProduct
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
```

```

```

    ...

---

The _ArrangementPathways_ object is a collection object that manages _ArrangementPathway_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementPathway_ object to be created.
#### Creating the ArrangementPathway Object under the ArrangementPathways Collection Object

    ...
The _ArrangementPathways_ object is a collection object that manages _ArrangementPathway_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementPathway_ object to be created.
```vbscript
```vbscript
       ' Create ArrangementPathway under the Root Product

```

```

```vbscript
       Dim dblPathwayPoints(75)      As Double
```vbscript
```vbscript
       Dim dblMathDirection(3)        As Double
       Dim objArrPathway             As ArrangementPathway

```

```

```

```vbscript
Dim objArrPathway             As ArrangementPathway
```vbscript
       dblPathwayPoints(0)   =  300.0
       dblPathwayPoints(1)   =  100.0
       dblPathwayPoints(2)   =  0.0

```

```

       dblPathwayPoints(3)   =  441.42
```vbscript
       dblPathwayPoints(4)   =  158.58
       dblPathwayPoints(5)   =  1.25

```

    ...

```vbscript
dblPathwayPoints(4)   =  158.58
```vbscript
dblPathwayPoints(5)   =  1.25
       dblPathwayPoints(72)  =  300.0
       dblPathwayPoints(73)  =  100.0
       dblPathwayPoints(74)  =  30

       dblMathDirection(0) = 1.0
       dblMathDirection(1) = 0.0
       dblMathDirection(2) = 0.0

```

```

```vbscript
       Set objArrPathway        = objArrProd.ArrangementPathways.AddPathway(objMove, _
                                                                            dblPathwayPoints, _
                                                                            dblMathDirection)
```

      ...

---

The newly created _ArrangementPathway_ object is visualized as a curve and does not have any section definition. In addition the nodes do not have any bend radius.
#### Modifying Properties (Defining a Round Section, Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly Created ArrangementPathway Object

      ...
The newly created _ArrangementPathway_ object is visualized as a curve and does not have any section definition. In addition the nodes do not have any bend radius.
```vbscript
```vbscript
       '----------------------------------------------
       ' Change Properties of ArrangementPathway
       objArrPathway.SectionType     = CatArrangementRouteSectionRound
       objArrPathway.SectionDiameter = 10.0
       objArrPathway.VisuMode        = CatArrangementRouteVisuModeSolid
       ' Define Bend Radius of Nodes
       '----------------------------------------------

```

```

```vbscript
       Dim intK As Integer
```vbscript
       For intK = 1 To objArrPathway.Nodes.Count
```

       objArrPathway.Nodes.Item(intK).BendRadius = 10.0
       Next
```

      ...

---

Here we define a round section and change the visualization mode to `CatArrangementRouteVisuModeSolid`. A bend radius of 10 mm is then applied to each of the _ArrangementNodes_ that makes up the object.
#### Epilog

    ...
```vbscript
     End Sub

```

---

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create an _ArrangementPathway_ object within a product document.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _ArrangementPathways, Product, ArrangementProduct, ArrangementPathway, ArrangementNode_
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
