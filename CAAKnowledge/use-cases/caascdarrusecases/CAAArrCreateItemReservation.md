---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAArrCreateItemReservationSource", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAArrCreateItemReservation", "CAAScdArrUseCases", "CAAInfLauchMacro", "CAAlink"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservation.htm"
converted: "2026-05-11T11:27:02.677615"
---

---

      

Once the new product document has been created, fetch the *ArrangementProduct*
      and the associated movable object from the Root product of the new product
      document.
      

#### Obtaining the ArrangementProduct Object and
      the Associated Movable Object from the Root Product
      
      

The *ArrangementItemReservations* object is a collection object
      that manages *ArrangementItemReservation* object's under a given *ArrangementProduct*.
      The movable object serves as the relative axis for the new *ArrangementItemReservation*
      object to be created.
      

#### Creating the ArrangementItemReservation Object
      under the ArrangementItemReservations Collection Object
      
      

The newly created *ArrangementItemReservation* object is displayed
      by default in the "Solid" mode as a box.
      

#### Modifying the Visualization Mode of the New
      ArrangementItemReservation Object
      
      

#### Epilog
      
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create an *ArrangementItemReservation*
object within a product document.

[Top]

---

#### References

---

*Copyright  2000, Dassault Systmes. All rights reserved.*



```vbscript
...
   '----------------------------------------------
   'Create a new product document
   Dim objProdDoc        As ProductDocument
   Dim objRootProd       As Product
   Set objProdDoc      = CATIA.Documents.Add(&quot;Product&quot;)
   Set objRootProd     = objProdDoc.Product
   ...
```

```vbscript
...
   '----------------------------------------------
   'Retrieving Root Product's Relative Axis and Position Information
   Dim objMove           As Move
   Dim objPosition       As Position
   Set objMove      = objRootProd.Move
   Set objPosition  = objRootProd.Position

   '----------------------------------------------
   ' Get ArrangementProduct
   Dim objArrProd        As ArrangementProduct
   Set objArrProd   = objRootProd.GetTechnologicalObject(&quot;ArrangementProduct&quot;)
...
```

```vbscript
...
   '----------------------------------------------
   ' Create Item Reservation under the Root Product
   Dim dblItemResPos(11)  As Double
   Dim objItemRes     As ArrangementItemReservation

   objPosition.GetComponents dblItemResPos
   Set objItemRes      = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, _
dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)
...
```

```vbscript
...
  '---------------------------------------------- 
  ' Change Properties of ArrangementItemReservation
   objItemRes.VisuMode = CatArrangementItemReservationVisuModeVisuFlat
...
```

```vbscript
...
 End Sub
```