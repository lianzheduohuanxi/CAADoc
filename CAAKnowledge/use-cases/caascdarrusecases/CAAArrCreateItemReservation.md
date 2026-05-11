---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAScrJavaScript", "CAAlink", "CAAArrCreateItemReservationSource", "CAAScdArrUseCases", "CATIA", "CAAArrCreateItemReservation"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservation.htm"
converted: "2026-05-11T11:06:32.742590"
---

## Arrangement
 
 
## []Creating an ArrangementItemReservation Object
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create an *ArrangementItemReservation*
 object in a product document.
 

This macro opens a new Product document and retrieves the [*ArrangementItemReservations*]
 collection from the Root [*Product*]
 via the [*ArrangementProduct*]
 object. It then adds an [*ArrangementItemReservation*]
 object. The visualization mode of the newly created *ArrangementItemReservation*
 object is then changed to "Flat" mode.
 

![](images/CAAArrCreateItemReservation.jpg)
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAArrCreateItemReservation is launched in CATIA [[1]].
 No open document is needed.
 

[CAAArrCreateItemReservation.CATScript]
 is located in the CAAScdArrUseCases module. [Execute
 macro] (Wndows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAArrCreateItemReservation includes the following
 steps:
 

 
- [Prolog]
 
- [Obtaining the ArrangementProduct Object and the
 Associated Movable Object from the Root Product]
 
- [Creating the ArrangementItemReservation Object
 under the ArrangementItemReservations Collection Object]
 
- [Modifying the Visualization Mode of the New
 ArrangementItemReservation Object]
 
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
 and the associated movable object from the Root product of the new product
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

 
 
 
 

The *ArrangementItemReservations* object is a collection object
 that manages *ArrangementItemReservation* object's under a given *ArrangementProduct*.
 The movable object serves as the relative axis for the new *ArrangementItemReservation*
 object to be created.
 
#### []Creating the ArrangementItemReservation Object
 under the ArrangementItemReservations Collection Object
 
 
 
```
...
 
'----------------------------------------------

 
' Create Item Reservation under the Root Product

 Dim 
dblItemResPos(11) 
 As 
Double

 Dim 
objItemRes 
 As 
ArrangementItemReservation

 objPosition.GetComponents dblItemResPos

 Set 
objItemRes = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, _
dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)
...
```

 
 
 
 

The newly created *ArrangementItemReservation* object is displayed
 by default in the "Solid" mode as a box.
 
#### []Modifying the Visualization Mode of the New
 ArrangementItemReservation Object
 
 
 
```
...
 
'----------------------------------------------
 

 ' Change Properties of ArrangementItemReservation

 objItemRes.VisuMode = CatArrangementItemReservationVisuModeVisuFlat
...
```

 
 
 
 
#### []Epilog
 
 
 
```
...
 End Sub
```

 
 
 
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create an *ArrangementItemReservation*
object within a product document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[ArrangementItemReservations],
 [Product],
 [ArrangementProduct],
 [ArrangementItemReservation]*
 
 
 |[[Top]]

---

*Copyright 2000, Dassault Systmes. All rights reserved.*