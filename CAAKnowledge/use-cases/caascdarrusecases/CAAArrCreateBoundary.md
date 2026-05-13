---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdArrUseCases", "CAAArrCreateBoundary", "CAAArrCreateBoundarySource", "CAAInfLauchMacro", "CAAlink"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateBoundary.htmmd"
converted: "2026-05-11T11:27:02.672075"
---

---

      

Once the new Product document has been created, fetch the *ArrangementProduct*
      and the associated movable object from the root product of the new product
      document.
      

#### Obtaining the ArrangementProduct Object and
      the Associated Movable Object from the Root Product
      
      

The *ArrangementBoundaries* object is a collection object that
      manages *ArrangementBoundary* object's under a given *ArrangementProduct*.
      The movable object serves as the relative axis for the new *ArrangementBoundary*
      object to be created.
      

#### Creating the ArrangementBoundary Object under
      the ArrangementBoundaries Collection Object
      
      

The newly created *ArrangementBoundary* object is visualized as a
      curve and does not have any section definition. In addition the nodes do
      not have any bend radius. We therefore define a rectangular section and
      change the visualization mode to solid.
      

#### Modifying Properties (Defining a Rectangular
      Section, Changing the Visualization Mode and Bend Radii of the Nodes) of
      the Newly Created ArrangementBoundary Object
      
      

Here we define a rectangular section and change the visualization mode
      to `CatArrangementRouteVisuModeSolid`. A bend radius of 10 mm
      is then applied to each of the *ArrangementNodes* that makes up the
      object.
      

#### Epilog
      
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create an *ArrangementBoundary* object
within a product document.

[Top]

---

#### References

---

*Copyright  2000, Dassault Systmes. All rights reserved.*

```vbscript
...
   '----------------------------------------------
   'Create a new product document
```cpp
   Dim objProdDoc        As ProductDocument
   Dim objRootProd       As Product
   Set objProdDoc      = CATIA.Documents.Add(&quot;Product&quot;)
   Set objRootProd     = objProdDoc.Product
   ...
```
```

```vbscript
...
   '----------------------------------------------
   'Retrieving Root Product's Relative Axis and Position Information
```vbscript
   Dim objMove           As Move
   Set objMove      = objRootProd.Move

   '----------------------------------------------
```
   ' Get ArrangementProduct
```vbscript
   Dim objArrProd        As ArrangementProduct
   Set objArrProd   = objRootProd.GetTechnologicalObject(&quot;ArrangementProduct&quot;)
...
```
```

```vbscript
...
   ' Create ArrangementBoundary under the Root Product
```vbscript
   Dim dblBoundaryPoints(75)      As Double
   Dim dblMathDirection(3)        As Double
   Dim objArrBoundary             As ArrangementBoundary

```

   dblBoundaryPoints(0)   =  300.0
   dblBoundaryPoints(1)   =  100.0
   dblBoundaryPoints(2)   =  0.0

   dblBoundaryPoints(3)   =  441.42
   dblBoundaryPoints(4)   =  158.58
   dblBoundaryPoints(5)   =  1.25

 ... 

   dblBoundaryPoints(69)  =  158.58
   dblBoundaryPoints(70)  =  158.58
   dblBoundaryPoints(71)  =  28.75

   dblBoundaryPoints(72)  =  300.0
   dblBoundaryPoints(73)  =  100.0
   dblBoundaryPoints(74)  =  30

   dblMathDirection(0) = 1.0
   dblMathDirection(1) = 0.0
   dblMathDirection(2) = 0.0

```vbscript
   Set objArrBoundary             = objArrProd.ArrangementBoundaries.AddBoundary(objMove, _
                                                                                 dblBoundaryPoints, _
```
                                                                                 dblMathDirection)
  ...
```

```vbscript
...
   objArrBoundary.SectionType     = CatArrangementRouteSectionRectangular
   objArrBoundary.SectionWidth    = 10.0
   objArrBoundary.SectionHeight   = 10.0 
   objArrBoundary.VisuMode        = CatArrangementRouteVisuModeSolid

   ' Define Bend Radius of Nodes
```vbscript
   Dim intK  As Integer
   For intK = 1 To objArrBoundary.Nodes.Count
```
   objArrBoundary.Nodes.Item(intK).BendRadius = 10.0
   Next
  ...
```

```vbscript
...
```vbscript
 End Sub
```
```