---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdArrUseCases", "CAAArrCreateItemReservation", "CAAArrCreateContourArea", "CAAArrCreateContourAreaSource", "CAAInfLauchMacro", "CAAlink"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateContourArea.htmmd"
converted: "2026-05-11T11:27:02.674206"
---

---

      

Once the new product document has been created, fetch the *ArrangementProduct*
      and the associated movable object from the root product of the new product
      document.
      

#### Obtaining the ArrangementProduct Object and
      the Associated Movable Object from the Root Product
      
      

The *ArrangementAreas* object is a collection object that manages *ArrangementArea*
      object's under a given *ArrangementProduct*. The movable object
      serves as the relative axis for the new *ArrangementArea* object to
      be created.
      

#### Creating the ArrangementArea Object under the
      ArrangementAreas Collection Object
      
      

The newly created *ArrangementArea* object is displayed without a
      contour at this point.
      

#### Creating the ArrangementRectangle Object
      
      

Note that the *ArrangementRectangle* object is created using the *ArrangementArea*
      as the movable object.
      

#### Adding a Rectangular Contour to the
      ArrangementArea Object
      
      

The *ArrangementArea* object is now displayed with its boundary as
      shown in the image above.
      

#### Epilog
      
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create an *ArrangementArea* object with a
rectangular contour within a product document.

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
   Dim objPosition       As Position
   Set objMove      = objRootProd.Move
   Set objPosition  = objRootProd.Position

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
   '----------------------------------------------
   ' Create Area without a contour under the Root Product
```vbscript
   Dim objArea     As ArrangementArea
   Dim dblAreaPos(11)  As Double

   objPosition.GetComponents dblAreaPos
```
```vbscript
   Set objArea     = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPos, 50.0)
...
```
```

```vbscript
...
   '----------------------------------------------
   ' Create Rectangle
```vbscript
   Dim objRectangle      As ArrangementRectangle
   Dim objArrProd1       As ArrangementProduct
   Dim objAreaProd1      As Product
   Dim objMove1          As Move
   Dim objPosition1      As Position
   Dim dblRectPos(11)    As Double

   Set objAreaProd1  = objArea.GetTechnologicalObject(&quot;Product&quot;)
   Set objArrProd1   = objArea.GetTechnologicalObject(&quot;ArrangementProduct&quot;)
   Set objMove1      = objAreaProd1.Move
   Set objPosition1  = objAreaProd1.Position
 
```
 
   objPosition1.GetComponents dblRectPos
   dblRectPos(9)  = 100.0
   dblRectPos(10) = 100.0
   dblRectPos(11) = 0.0
```vbscript
   Set objRectangle = objArrProd1.ArrangementRectangles.AddRectangle (objMove1,dblRectPos, 50.0, 50.0)
...
```
```

```vbscript
...
   '---------------------------------------------
   ' Add Rectangular contour to Area                    
   objArea.ArrangementContours.AddRectangularContour(objRectangle)
...
```

```vbscript
...
```vbscript
 End Sub
```
```