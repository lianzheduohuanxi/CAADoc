---
title: "Creating an ArrangementArea without a Contour"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CATIA", "CAAArrCreateNoContourArea", "CAAScdArrUseCases"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateNoContourArea.md"
converted: "2026-05-11T17:31:51.556574"
---

| 
## Arrangement

| 
## Creating an ArrangementArea without a Contour  
  
  
* * *

  This macro shows you how to create an _ArrangementArea_ object that has no contour associated with it. This macro opens a new Product document and retrieves the _ArrangementAreas_ collection from the Root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementArea_ object. The _ArrangementArea_ created without a contour will not have any visualization in the 3D viewer as shown in the image below. ![](images/CAAArrCreateNoContourArea.jpg)    
---|---  
  CAAArrCreateNoContourArea is launched in CATIA [1]. No open document is needed. [CAAArrCreateNoContourArea.CATScript](CAAArrCreateNoContourAreaSource.md) is located in the CAAScdArrUseCases module. [Execute macro](macros/CAAArrCreateNoContourArea.CATScript) (Windows only).    
  CAAArrCreateNoContourArea includes the following steps:

  1. Prolog
  2. Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
  3. Creating the ArrangementArea Object under the ArrangementAreas Collection Object
  4. Epilog

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
  
The _ArrangementAreas_ object is a collection object that manages _ArrangementArea_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementArea_ object to be created.
#### Creating the ArrangementArea Object under the ArrangementAreas Collection Object
    
    
    ...
       '----------------------------------------------
       ' Create Area without a contour under the Root Product
```vbscript
       Dim dblAreaPosition(11)  As Double
       Dim objArea     As ArrangementArea
    
```

       objPosition.GetComponents dblAreaPosition
       dblAreaPosition(9)    = 300.0
       dblAreaPosition(10)   = 400.0
       dblAreaPosition(11)   = 300.0
```vbscript
       Set objArea     = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPosition, 50.0)
      ...  
  
```

```

---  
  
The newly created _ArrangementArea_ object does not have a contour and in addition does not display in the 3D viewer. Note that the leaf in the specifications tree for this _ArrangementArea_ object is displayed with a yellow background to distinguish it from an _ArrangementArea_ object that has a contour.
#### Epilog
    
    
    ...
     End Sub  
  
```

---  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create an _ArrangementArea_ object within a product document.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2] | _ArrangementAreas, Product, ArrangementProduct, ArrangementArea_  
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
