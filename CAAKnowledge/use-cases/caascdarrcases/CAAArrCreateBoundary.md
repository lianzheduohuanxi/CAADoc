---
```vbscript
title: "Creating an ArrangementBoundary Object"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAArrCreateBoundary", "CATIA", "CAAScdArrUseCases"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateBoundary.htm"
converted: "2026-05-11T17:31:51.537121"
```

---
## Arrangement

| 
## Creating an ArrangementBoundary Object  

* * *

  This macro shows you how to create an ArrangementBoundary object under a Product. This macro opens a new Product document and retrieves the _ArrangementBoundaries_ collection from the Root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementBoundary_ object. Once the _ArrangementBoundary_ object is created, the individual _ArrangementNode_'s that make up the object are retrieved and the bend radius is applied on them. ![](images/CAAArrCreateBoundary.jpg)    
---|---  
This macro shows you how to create an ArrangementBoundary object under a Product. This macro opens a new Product document and retrieves the _ArrangementBoundaries_ collection from the Root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementBoundary_ object. Once the _ArrangementBoundary_ object is created, the individual _ArrangementNode_'s that make up the object are retrieved and the bend radius is applied on them. ![](images/CAAArrCreateBoundary.jpg)
  CAAArrCreateBoundary is launched in CATIA [1]. No open document is needed. [CAAArrCreateBoundary.CATScript ](CAAArrCreateBoundarySource.md)is located in the CAAScdArrUseCases module. [Execute macro](macros/CAAArrCreateBoundary.CATScript) (Windows only).    
  CAAArrCreateBoundary includes the following steps:

  1. Prolog
  2. Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
  3. Creating the ArrangementBoundary Object under the ArrangementBoundaries Collection Object
  4. Modifying Properties (Defining a Rectangular Section, Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly Created ArrangementBoundary object
  5. Epilog

#### Prolog

| 

      ...
       '----------------------------------------------
```vbscript
'----------------------------------------------
       'Create a new product document
```

```vbscript
       Dim objProdDoc        As ProductDocument
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
```

       ...  

---  

Once the new Product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.
#### Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product

    ...
Once the new Product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.
       '----------------------------------------------
       'Retrieving Root Product's Relative Axis and Position Information

```vbscript
       Dim objMove           As Move
       Set objMove      = objRootProd.Move
```

```vbscript
       '----------------------------------------------
       ' Get ArrangementProduct
       Dim objArrProd        As ArrangementProduct
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
```

    ...  

---  

The _ArrangementBoundaries_ object is a collection object that manages _ArrangementBoundary_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementBoundary_ object to be created.
#### Creating the ArrangementBoundary Object under the ArrangementBoundaries Collection Object

    ...
The _ArrangementBoundaries_ object is a collection object that manages _ArrangementBoundary_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementBoundary_ object to be created.
       ' Create ArrangementBoundary under the Root Product

```vbscript
       Dim dblBoundaryPoints(75)      As Double
       Dim dblMathDirection(3)        As Double
       Dim objArrBoundary             As ArrangementBoundary

```

```vbscript
Dim objArrBoundary             As ArrangementBoundary
       dblBoundaryPoints(0)   =  300.0
       dblBoundaryPoints(1)   =  100.0
       dblBoundaryPoints(2)   =  0.0

       dblBoundaryPoints(3)   =  441.42
       dblBoundaryPoints(4)   =  158.58
       dblBoundaryPoints(5)   =  1.25

```

     ... 

```vbscript
dblBoundaryPoints(4)   =  158.58
dblBoundaryPoints(5)   =  1.25
       dblBoundaryPoints(69)  =  158.58
       dblBoundaryPoints(70)  =  158.58
       dblBoundaryPoints(71)  =  28.75

       dblBoundaryPoints(72)  =  300.0
       dblBoundaryPoints(73)  =  100.0
       dblBoundaryPoints(74)  =  30

       dblMathDirection(0) = 1.0
       dblMathDirection(1) = 0.0
       dblMathDirection(2) = 0.0

```

```vbscript
       Set objArrBoundary             = objArrProd.ArrangementBoundaries.AddBoundary(objMove, _
                                                                                     dblBoundaryPoints, _
                                                                                     dblMathDirection)
```

      ...  

---  

The newly created _ArrangementBoundary_ object is visualized as a curve and does not have any section definition. In addition the nodes do not have any bend radius. We therefore define a rectangular section and change the visualization mode to solid.
#### Modifying Properties (Defining a Rectangular Section, Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly Created ArrangementBoundary Object

      ...
The newly created _ArrangementBoundary_ object is visualized as a curve and does not have any section definition. In addition the nodes do not have any bend radius. We therefore define a rectangular section and change the visualization mode to solid.
       objArrBoundary.SectionType     = CatArrangementRouteSectionRectangular
       objArrBoundary.SectionWidth    = 10.0
       objArrBoundary.SectionHeight   = 10.0 
       objArrBoundary.VisuMode        = CatArrangementRouteVisuModeSolid
       ' Define Bend Radius of Nodes

```vbscript
       Dim intK  As Integer
       For intK = 1 To objArrBoundary.Nodes.Count
       objArrBoundary.Nodes.Item(intK).BendRadius = 10.0
       Next
```

      ...  

---  

Here we define a rectangular section and change the visualization mode to `CatArrangementRouteVisuModeSolid`. A bend radius of 10 mm is then applied to each of the _ArrangementNodes_ that makes up the object.
#### Epilog

    ...
     End Sub  

---  

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create an _ArrangementBoundary_ object within a product document.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2] | _ArrangementBoundaries, Product, ArrangementProduct, ArrangementBoundary, ArrangementNode._  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
