---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdArrUseCases", "CAAArrCreateNoContourAreaSource", "CAAInfLauchMacro", "CAAArrCreateNoContourArea", "CAAlink"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateNoContourArea.htm"
converted: "2026-05-11T11:27:02.683045"
---

---

      

Once the new product document has been created, fetch the *ArrangementProduct*
      and the associated movable object from the Root product of the new product
      document.
      

#### Obtaining the ArrangementProduct Object and
      the Associated Movable Object from the Root Product
      
      

The *ArrangementAreas* object is a collection object that manages *ArrangementArea*
      object's under a given *ArrangementProduct*. The movable object
      serves as the relative axis for the new *ArrangementArea* object to
      be created.
      

#### Creating the ArrangementArea Object under the
      ArrangementAreas Collection Object
      
      

The newly created *ArrangementArea* object does not have a contour
      and in addition does not display in the 3D viewer. Note that the leaf in
      the specifications tree for this *ArrangementArea* object is
      displayed with a yellow background to distinguish it from an *ArrangementArea*
      object that has a contour.
      

#### Epilog
      
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create an *ArrangementArea* object within
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
   ' Create Area without a contour under the Root Product
   Dim dblAreaPosition(11)  As Double
   Dim objArea     As ArrangementArea

   objPosition.GetComponents dblAreaPosition
   dblAreaPosition(9)    = 300.0
   dblAreaPosition(10)   = 400.0
   dblAreaPosition(11)   = 300.0
   Set objArea     = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPosition, 50.0)
  ...
```

```vbscript
...
 End Sub
```