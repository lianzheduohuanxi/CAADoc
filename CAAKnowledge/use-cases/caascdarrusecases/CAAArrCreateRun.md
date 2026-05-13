---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdArrUseCases", "CAAInfLauchMacro", "CAAArrCreateRun", "CAAArrCreateRunSource", "CAAlink"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateRun.htmmd"
converted: "2026-05-11T11:27:02.675489"
---

---

      

Once the new product document has been created, fetch the *ArrangementProduct*
      and the associated movable object from the root product of the new product
      document.
      

#### Obtaining the ArrangementProduct Object and
      the Associated Movable Object from the Root Product
      
      

The *ArrangementRuns* object is a collection object that manages *ArrangementRun*
      object's under a given *ArrangementProduct*. The movable object
      serves as the relative axis for the new *ArrangementRun* object to be
      created.
      

#### Creating the ArrangementRun Object under the
      ArrangementRuns Collection Object
      
      

The newly created *ArrangementRun* object is visualized as a curve
      and does not have any section definition. In addition the nodes do not
      have any bend radius.
      

#### Modifying Properties (Defining a Rectangular
      Section, Changing the Visualization Mode and Bend Radii of the Nodes) of
      the Newly Created ArrangementRun Object
      
      

Here we define a round section and change the visualization mode to `CatArrangementRouteVisuModeSolid`.
      A bend radius of 10 mm is then applied to each of the *ArrangementNodes*
      that makes up the object.
      

#### Epilog
      
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create an *ArrangementRun* object within
a product document.

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
   ' Create ArrangementRun under the Root Product
```vbscript
   Dim dblRunPoints(75)      As Double
   Dim dblMathDirection(3)        As Double
   Dim objArrRun             As ArrangementRun

```

   dblRunPoints(0)   =  300.0
   dblRunPoints(1)   =  100.0
   dblRunPoints(2)   =  0.0

   dblRunPoints(3)   =  441.42
   dblRunPoints(4)   =  158.58
   dblRunPoints(5)   =  1.25

  ...

   dblRunPoints(72)  =  300.0
   dblRunPoints(73)  =  100.0
   dblRunPoints(74)  =  30

   dblMathDirection(0) = 1.0
   dblMathDirection(1) = 0.0
   dblMathDirection(2) = 0.0

```vbscript
   Set objArrRun             = objArrProd.ArrangementRuns.AddRun(objMove,dblRunPoints, dblMathDirection)
  ...
```
```

```vbscript
...
   objArrRun.SectionType     = CatArrangementRouteSectionRound
   objArrRun.SectionDiameter = 10.0
   objArrRun.VisuMode        = CatArrangementRouteVisuModeSolid

   '----------------------------------------------
   ' Change Properties of ArrangementRun
```vbscript
   Dim intK As Integer   
   For intK = 1 To objArrRun.Nodes.Count
```
  
   objArrRun.Nodes.Item(intK).BendRadius = 10.0
 
   Next
   objArrRun.SectionType     = CatArrangementRouteSectionRound
   objArrRun.SectionDiameter = 10.0
   objArrRun.VisuMode        = CatArrangementRouteVisuModeSolid

   '----------------------------------------------
   ' Define Bend Radius of Nodes
```vbscript
   Dim intK As Integer   
   For intK = 1 To objArrRun.Nodes.Count
```
   objArrRun.Nodes.Item(intK).BendRadius = 10.0
   Next
  ...
```

```vbscript
...
```vbscript
 End Sub
```
```