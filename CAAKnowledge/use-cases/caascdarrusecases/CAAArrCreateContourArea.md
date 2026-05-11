---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAArrCreateItemReservation", "CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAlink", "CAAArrCreateContourArea", "CAAArrCreateContourAreaSource", "CAAScdArrUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateContourArea.htm"
converted: "2026-05-11T11:06:32.734018"
---

## Arrangement
 
 
## []Creating an ArrangementArea Object with a
 Rectangular Contour
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create an [*ArrangementArea*]
 object with a rectangular contour in a product document.
 

This macro opens a new product document and retrieves the [*ArrangementItemAreas*]
 collection from the root [*Product*]
 via the [*ArrangementProduct*]
 object. It then adds an [*ArrangementArea*]
 object. The Arrangement object so created does not have a contour. To add
 a contour, the [*ArrangementRectangles*]
 collection oject is then retrieved from the newly created *ArrangementArea*
 and a new [*ArrangementRectangle*]
 object is created and then added to the *ArrangementArea* as a
 rectangular contour.
 

![](images/CAAArrCreateContourArea.jpg)
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAArrCreateContourArea is launched in CATIA [[1]].
 No open document is needed.
 

[CAAArrCreateContourArea.CATScript]
 is located in the CAAScdArrUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAArrCreateItemReservation includes the following
 steps:
 

 
- [Prolog]
 
- [Obtaining the ArrangementProduct Object and the
 Associated Movable Object from the Root Product]
 
- [Creating the ArrangementArea Object under the
 ArrangementAreas Collection Object]
 
- [Creating the ArrangementRectangle Object]
 
- [Adding a Rectangular Contour to the
 ArrangementArea Object]
 
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

 Dim 
objPosition 
 As 
Position

 Set 
objMove = objRootProd.Move

 Set 
objPosition = objRootProd.Position

 
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

 
 
 
 

The *ArrangementAreas* object is a collection object that manages *ArrangementArea*
 object's under a given *ArrangementProduct*. The movable object
 serves as the relative axis for the new *ArrangementArea* object to
 be created.
 
#### []Creating the ArrangementArea Object under the
 ArrangementAreas Collection Object
 
 
 
```
...
 
'----------------------------------------------

 
' Create Area without a contour under the Root Product

 Dim 
objArea 
 As 
ArrangementArea
 
Dim 
dblAreaPos(11) 
 As 
Double

 objPosition.GetComponents dblAreaPos

 Set 
objArea = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPos, 50.0)
...
```

 
 
 
 

The newly created *ArrangementArea* object is displayed without a
 contour at this point.
 
#### []Creating the ArrangementRectangle Object
 
 
 
```
...
 
'----------------------------------------------

 
' Create Rectangle

 Dim 
objRectangle 
 As 
ArrangementRectangle
 
Dim 
objArrProd1 
 As 
ArrangementProduct

 Dim 
objAreaProd1 
 As 
Product

 Dim 
objMove1 
 As 
Move

 Dim 
objPosition1 
 As 
Position
 
 Dim 
dblRectPos(11) 
 As 
Double

 Set 
objAreaProd1 = objArea.GetTechnologicalObject("Product")
 
Set 
objArrProd1 = objArea.GetTechnologicalObject("ArrangementProduct")

 Set 
objMove1 = objAreaProd1.Move

 Set 
objPosition1 = objAreaProd1.Position

 

 objPosition1.GetComponents dblRectPos
 dblRectPos(9) = 100.0
 dblRectPos(10) = 100.0
 dblRectPos(11) = 0.0

 Set 
objRectangle = objArrProd1.ArrangementRectangles.AddRectangle (objMove1,dblRectPos, 50.0, 50.0)
...
```

 
 
 
 

Note that the *ArrangementRectangle* object is created using the *ArrangementArea*
 as the movable object.
 
#### []Adding a Rectangular Contour to the
 ArrangementArea Object
 
 
 
```
...
 
'---------------------------------------------

 
' Add Rectangular contour to Area 

 objArea.ArrangementContours.AddRectangularContour(objRectangle)
...
```

 
 
 
 

The *ArrangementArea* object is now displayed with its boundary as
 shown in the image above.
 
#### []Epilog
 
 
 
```
...
 End Sub
```

 
 
 
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create an *ArrangementArea* object with a
rectangular contour within a product document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[ArrangementItemAreas],
 [Product],
 [ArrangementProduct],
 [ArrangementArea],
 [ArrangementRectangles],
 [ArrangementRectangle]*
 
 
 |[[Top]]

---

*Copyright 2000, Dassault Systmes. All rights reserved.*