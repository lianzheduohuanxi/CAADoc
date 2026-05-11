---
```vbscript
title: "Creating an ArrangementRun Object"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CATIA", "CAAArrCreateRun", "CAAScdArrUseCases"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateRun.htm"
converted: "2026-05-11T17:31:51.569560"
```

---
| 
## Arrangement

| 
## Creating an ArrangementRun Object  

* * *

  This macro shows you how to create an _ArrangementRun_ under a product. This macro opens a new Product document and retrieves the _ArrangementRuns_ collection from the root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementRun_ object. Once the _ArrangementRun_ object is created, the individual _ArrangementNode_'s that make up the object are retrieved and the bend radius is applied on them. ![](images/CAAArrCreateRun.jpg)    
---|---  
This macro shows you how to create an _ArrangementRun_ under a product. This macro opens a new Product document and retrieves the _ArrangementRuns_ collection from the root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementRun_ object. Once the _ArrangementRun_ object is created, the individual _ArrangementNode_'s that make up the object are retrieved and the bend radius is applied on them. ![](images/CAAArrCreateRun.jpg)
  CAAArrCreateRun is launched in CATIA [1]. No open document is needed. [CAAArrCreateRun.CATScript ](CAAArrCreateRunSource.md)is located in the CAAScdArrUseCases module. [Execute macro](macros/CAAArrCreateRun.CATScript) (Windows only).    
  CAAArrCreateRun includes the following steps:

  1. Prolog
  2. Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
  3. Creating the ArrangementRun Object under the ArrangementRuns Collection Object
  4. Modifying Properties (Defining a Rectangular Section, Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly Created ArrangementRun Object
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

Once the new product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.
#### Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product

    ...
Once the new product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.
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

The _ArrangementRuns_ object is a collection object that manages _ArrangementRun_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementRun_ object to be created.
#### Creating the ArrangementRun Object under the ArrangementRuns Collection Object

    ...
The _ArrangementRuns_ object is a collection object that manages _ArrangementRun_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementRun_ object to be created.
       ' Create ArrangementRun under the Root Product

```vbscript
       Dim dblRunPoints(75)      As Double
       Dim dblMathDirection(3)        As Double
       Dim objArrRun             As ArrangementRun

```

```vbscript
Dim objArrRun             As ArrangementRun
       dblRunPoints(0)   =  300.0
       dblRunPoints(1)   =  100.0
       dblRunPoints(2)   =  0.0

       dblRunPoints(3)   =  441.42
       dblRunPoints(4)   =  158.58
       dblRunPoints(5)   =  1.25

```

      ...

```vbscript
dblRunPoints(4)   =  158.58
dblRunPoints(5)   =  1.25
       dblRunPoints(72)  =  300.0
       dblRunPoints(73)  =  100.0
       dblRunPoints(74)  =  30

       dblMathDirection(0) = 1.0
       dblMathDirection(1) = 0.0
       dblMathDirection(2) = 0.0

```

```vbscript
       Set objArrRun             = objArrProd.ArrangementRuns.AddRun(objMove,dblRunPoints, dblMathDirection)
```

      ...  

---  

The newly created _ArrangementRun_ object is visualized as a curve and does not have any section definition. In addition the nodes do not have any bend radius.
#### Modifying Properties (Defining a Rectangular Section, Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly Created ArrangementRun Object

      ...
The newly created _ArrangementRun_ object is visualized as a curve and does not have any section definition. In addition the nodes do not have any bend radius.
       objArrRun.SectionType     = CatArrangementRouteSectionRound
       objArrRun.SectionDiameter = 10.0
       objArrRun.VisuMode        = CatArrangementRouteVisuModeSolid
       '----------------------------------------------
       ' Change Properties of ArrangementRun

```vbscript
       Dim intK As Integer   
       For intK = 1 To objArrRun.Nodes.Count

```

```vbscript
Dim intK As Integer
For intK = 1 To objArrRun.Nodes.Count
       objArrRun.Nodes.Item(intK).BendRadius = 10.0

       Next
       objArrRun.SectionType     = CatArrangementRouteSectionRound
       objArrRun.SectionDiameter = 10.0
       objArrRun.VisuMode        = CatArrangementRouteVisuModeSolid
       '----------------------------------------------
       ' Define Bend Radius of Nodes
```

```vbscript
       Dim intK As Integer   
       For intK = 1 To objArrRun.Nodes.Count
       objArrRun.Nodes.Item(intK).BendRadius = 10.0
       Next
```

      ...  

---  

Here we define a round section and change the visualization mode to `CatArrangementRouteVisuModeSolid`. A bend radius of 10 mm is then applied to each of the _ArrangementNodes_ that makes up the object.
#### Epilog

    ...
     End Sub  

---  

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create an _ArrangementRun_ object within a product document.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2} | _ArrangementRuns, Product, ArrangementProduct, ArrangementRun, ArrangementNode_  
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
