---
title: "Creating an ArrangementItemReservation Object"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAArrCreateItemReservation", "CATIA", "CAAScdArrUseCases"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservation.md"
converted: "2026-05-11T17:31:51.550095"
---

| 
## Arrangement

| 
## Creating an ArrangementItemReservation Object  
  
  
* * *

  This macro shows you how to create an _ArrangementItemReservation_ object in a product document. This macro opens a new Product document and retrieves the _ArrangementItemReservations_ collection from the Root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementItemReservation_ object. The visualization mode of the newly created _ArrangementItemReservation_ object is then changed to "Flat" mode. ![](images/CAAArrCreateItemReservation.jpg)    
---|---  
  CAAArrCreateItemReservation is launched in CATIA [1]. No open document is needed. [CAAArrCreateItemReservation.CATScript](CAAArrCreateItemReservationSource.md) is located in the CAAScdArrUseCases module. [Execute macro](macros/CAAArrCreateItemReservation.CATScript) (Wndows only).    
  CAAArrCreateItemReservation includes the following steps:

  1. Prolog
  2. Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
  3. Creating the ArrangementItemReservation Object under the ArrangementItemReservations Collection Object
  4. Modifying the Visualization Mode of the New ArrangementItemReservation Object
  5. Epilog

#### Prolog

| 
    
    
      ...
       '----------------------------------------------
       'Create a new product document
```vbscript
       Dim objProdDoc        As ProductDocument
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
       ...  
  
```

```

---  
  
Once the new product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the Root product of the new product document.
#### Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
    
    
    ...
       '----------------------------------------------
       'Retrieving Root Product's Relative Axis and Position Information
```vbscript
       Dim objMove           As Move
       Dim objPosition       As Position
       Set objMove      = objRootProd.Move
       Set objPosition  = objRootProd.Position
```vbscript
       '----------------------------------------------
       ' Get ArrangementProduct
       Dim objArrProd        As ArrangementProduct
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
```

    ...  
  
```

```

---  
  
The _ArrangementItemReservations_ object is a collection object that manages _ArrangementItemReservation_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementItemReservation_ object to be created.
#### Creating the ArrangementItemReservation Object under the ArrangementItemReservations Collection Object
    
    
    ...
       '----------------------------------------------
       ' Create Item Reservation under the Root Product
```vbscript
       Dim dblItemResPos(11)  As Double
       Dim objItemRes     As ArrangementItemReservation
    
```

       objPosition.GetComponents dblItemResPos
```vbscript
       Set objItemRes      = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, _
    dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)
    ...  
  
```

```

---  
  
The newly created _ArrangementItemReservation_ object is displayed by default in the "Solid" mode as a box.
#### Modifying the Visualization Mode of the New ArrangementItemReservation Object
    
    
    ...
      '---------------------------------------------- 
      ' Change Properties of ArrangementItemReservation
       objItemRes.VisuMode = CatArrangementItemReservationVisuModeVisuFlat
    ...  
  
---  
#### Epilog
    
    
    ...
     End Sub  
  
```

---  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create an _ArrangementItemReservation_ object within a product document.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2] | _ArrangementItemReservations, Product, ArrangementProduct, ArrangementItemReservation_  
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
