---
title: "Creating an ArrangementArea Object with a Rectangular Contour"
category: "general"
module: "CAAScdArrUseCases"
tags: ["CAAArrCreateContourArea", "CAAArrCreateItemReservation", "CATIA", "CAAScdArrUseCases"]
source_file: "Doc\online\CAAScdArrUseCases\CAAArrCreateContourArea.htm"
converted: "2026-05-11T17:31:51.544106"
---

## Arrangement

| 

## Creating an ArrangementArea Object with a Rectangular Contour  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This macro shows you how to create an _ArrangementArea_ object with a rectangular contour in a product document. This macro opens a new product document and retrieves the _ArrangementItemAreas_ collection from the root _Product_ via the _ArrangementProduct_ object. It then adds an _ArrangementArea_ object. The Arrangement object so created does not have a contour. To add a contour, the _ArrangementRectangles_ collection oject is then retrieved from the newly created _ArrangementArea_ and a new _ArrangementRectangle_ object is created and then added to the _ArrangementArea_ as a rectangular contour. ![](images/CAAArrCreateContourArea.jpg)    
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAArrCreateContourArea is launched in CATIA [1]. No open document is needed. [CAAArrCreateContourArea.CATScript](CAAArrCreateContourAreaSource.htm) is located in the CAAScdArrUseCases module. [Execute macro](macros/CAAArrCreateContourArea.CATScript) (Windows only).    
![](../CAAScrBase/images/ascenari.gif) |  CAAArrCreateItemReservation includes the following steps:

  1. Prolog
  2. Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
  3. Creating the ArrangementArea Object under the ArrangementAreas Collection Object
  4. Creating the ArrangementRectangle Object
  5. Adding a Rectangular Contour to the ArrangementArea Object
  6. Epilog



#### Prolog

| 
    
    
      ...
       '----------------------------------------------
       'Create a new product document
       Dim objProdDoc        As ProductDocument
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
       ...  
  
---  
  
Once the new product document has been created, fetch the _ArrangementProduct_ and the associated movable object from the root product of the new product document.

#### Obtaining the ArrangementProduct Object and the Associated Movable Object from the Root Product
    
    
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
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
    ...  
  
---  
  
The _ArrangementAreas_ object is a collection object that manages _ArrangementArea_ object's under a given _ArrangementProduct_. The movable object serves as the relative axis for the new _ArrangementArea_ object to be created.

#### Creating the ArrangementArea Object under the ArrangementAreas Collection Object
    
    
    ...
       '----------------------------------------------
       ' Create Area without a contour under the Root Product
       Dim objArea     As ArrangementArea
       Dim dblAreaPos(11)  As Double
    
       objPosition.GetComponents dblAreaPos
       Set objArea     = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPos, 50.0)
    ...  
  
---  
  
The newly created _ArrangementArea_ object is displayed without a contour at this point.

#### Creating the ArrangementRectangle Object
    
    
    ...
       '----------------------------------------------
       ' Create Rectangle
       Dim objRectangle      As ArrangementRectangle
       Dim objArrProd1       As ArrangementProduct
       Dim objAreaProd1      As Product
       Dim objMove1          As Move
       Dim objPosition1      As Position
       Dim dblRectPos(11)    As Double
    
       Set objAreaProd1  = objArea.GetTechnologicalObject("Product")
       Set objArrProd1   = objArea.GetTechnologicalObject("ArrangementProduct")
       Set objMove1      = objAreaProd1.Move
       Set objPosition1  = objAreaProd1.Position
     
       objPosition1.GetComponents dblRectPos
       dblRectPos(9)  = 100.0
       dblRectPos(10) = 100.0
       dblRectPos(11) = 0.0
       Set objRectangle = objArrProd1.ArrangementRectangles.AddRectangle (objMove1,dblRectPos, 50.0, 50.0)
    ...  
  
---  
  
Note that the _ArrangementRectangle_ object is created using the _ArrangementArea_ as the movable object.

#### Adding a Rectangular Contour to the ArrangementArea Object
    
    
    ...
       '---------------------------------------------
       ' Add Rectangular contour to Area                    
       objArea.ArrangementContours.AddRectangularContour(objRectangle)
    ...  
  
---  
  
The _ArrangementArea_ object is now displayed with its boundary as shown in the image above.

#### Epilog
    
    
    ...
     End Sub  
  
---  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to create an _ArrangementArea_ object with a rectangular contour within a product document.

[Top]

* * *

#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[2] | _ArrangementItemAreas, Product, ArrangementProduct, ArrangementArea, ArrangementRectangles, ArrangementRectangle_  
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
