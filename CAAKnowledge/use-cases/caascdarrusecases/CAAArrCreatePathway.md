---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAArrCreatePathway", "CAAArrCreatePathwaySource", "CAAScdArrUseCases", "CAAInfLauchMacro", "CAAlink"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreatePathway.htmmd"
converted: "2026-05-11T11:27:02.678902"
---

---

      

Once the new product document has been created, fetch the *ArrangementProduct*
      and the associated movable object from the root product of the new product
      document.
      

#### Obtaining the ArrangementProduct Object and
      the Associated Movable Object from the Root Product
      
      

The *ArrangementPathways* object is a collection object that
      manages *ArrangementPathway* object's under a given *ArrangementProduct*.
      The movable object serves as the relative axis for the new *ArrangementPathway*
      object to be created.
      

#### Creating the ArrangementPathway Object under
      the ArrangementPathways Collection Object
      
      

The newly created *ArrangementPathway* object is visualized as a
      curve and does not have any section definition. In addition the nodes do
      not have any bend radius. 
      

#### Modifying Properties (Defining a Round Section,
      Changing the Visualization Mode and Bend Radii of the Nodes) of the Newly
      Created ArrangementPathway Object
      
      

Here we define a round section and change the visualization mode to `CatArrangementRouteVisuModeSolid`.
      A bend radius of 10 mm is then applied to each of the *ArrangementNodes*
      that makes up the object.
      

#### Epilog
      
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create an *ArrangementPathway* object
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
```vbscript
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
   ' Create ArrangementPathway under the Root Product
```vbscript
   Dim dblPathwayPoints(75)      As Double
   Dim dblMathDirection(3)        As Double
   Dim objArrPathway             As ArrangementPathway

```

   dblPathwayPoints(0)   =  300.0
   dblPathwayPoints(1)   =  100.0
   dblPathwayPoints(2)   =  0.0

   dblPathwayPoints(3)   =  441.42
   dblPathwayPoints(4)   =  158.58
   dblPathwayPoints(5)   =  1.25

...

   dblPathwayPoints(72)  =  300.0
   dblPathwayPoints(73)  =  100.0
   dblPathwayPoints(74)  =  30

   dblMathDirection(0) = 1.0
   dblMathDirection(1) = 0.0
   dblMathDirection(2) = 0.0

```vbscript
   Set objArrPathway        = objArrProd.ArrangementPathways.AddPathway(objMove, _
                                                                        dblPathwayPoints, _
```
                                                                        dblMathDirection)
  ...
```

```vbscript
...
   '---------------------------------------------- 
   ' Change Properties of ArrangementPathway
   objArrPathway.SectionType     = CatArrangementRouteSectionRound
   objArrPathway.SectionDiameter = 10.0
   objArrPathway.VisuMode        = CatArrangementRouteVisuModeSolid

   ' Define Bend Radius of Nodes
   '---------------------------------------------- 
```vbscript
   Dim intK As Integer   
   For intK = 1 To objArrPathway.Nodes.Count
```
   objArrPathway.Nodes.Item(intK).BendRadius = 10.0
   Next
  ...
```

```vbscript
...
```vbscript
 End Sub
```
```