---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAlink", "CAAArrCreateNoContourArea", "CAAScdArrUseCases", "CAAArrCreateNoContourAreaSource", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateNoContourArea.htm"
converted: "2026-05-11T11:06:32.755440"
---

## Arrangement
 
 
## []Creating an ArrangementArea without a Contour
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create an *ArrangementArea*
 object that has no contour associated with it.
 

This macro opens a new Product document and retrieves the [*ArrangementAreas*]
 collection from the Root [*Product*]
 via the [*ArrangementProduct*]
 object. It then adds an [*ArrangementArea*]
 object. The *ArrangementArea* created without a contour will not have
 any visualization in the 3D viewer as shown in the image below.
 

![](images/CAAArrCreateNoContourArea.jpg)
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAArrCreateNoContourArea is launched in CATIA [[1]].
 No open document is needed.
 

[CAAArrCreateNoContourArea.CATScript]
 is located in the CAAScdArrUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAArrCreateNoContourArea includes the following
 steps:
 

 
- [Prolog]
 
- [Obtaining the ArrangementProduct Object and the
 Associated Movable Object from the Root Product]
 
- [Creating the ArrangementArea Object under the
 ArrangementAreas Collection Object]
 
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
dblAreaPosition(11) 
 As 
Double

 Dim 
objArea 
 As 
ArrangementArea

 objPosition.GetComponents dblAreaPosition
 dblAreaPosition(9) = 300.0
 dblAreaPosition(10) = 400.0
 dblAreaPosition(11) = 300.0

 Set 
objArea = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPosition, 50.0)
 ...
```

 
 
 
 

The newly created *ArrangementArea* object does not have a contour
 and in addition does not display in the 3D viewer. Note that the leaf in
 the specifications tree for this *ArrangementArea* object is
 displayed with a yellow background to distinguish it from an *ArrangementArea*
 object that has a contour.
 
#### []Epilog
 
 
 
```
...
 End Sub
```

 
 
 
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create an *ArrangementArea* object within
a product document.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[ArrangementAreas],
 [Product],
 [ArrangementProduct],
 [ArrangementArea]*
 
 
 |[[Top]]

---

*Copyright 2000, Dassault Systmes. All rights reserved.*