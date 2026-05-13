---
title: "Creating Constraints on Published Elements"
category: "use-case"
module: "CAAScdAsmUseCases"
tags: "["CAAScdAsmUseCases", "CAAAsmCstOnPublish", "CATIA"]"
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCstOnPublish.htm"
converted: "2026-05-11T17:31:50.852164"
---
|
## Assembly

|
## Creating Constraints on Published Elements

* * *

  This macro shows you how to create constraints on published elements. This macro opens the [CAAAsmCstOnPublish.CATProduct](samples/CstOnPublish.CATProduct) document that contains two parts: a plate, Plate.CATPart, and two instances of a screw, Screw.CATPart. It retrieves on each _Product_ object the _Publication_ objects corresponding to published elements identifying for example the position of the holes in the plate and the axis of the screws. It creates _Constraint_ objects to position those elements regarding one another. It then uses the `ReplaceComponent` method of the _Products_ collection to replace Screw.CATPart with NewScrew.CATPart, automatically reconnecting the constraints on the published elements of the new part.
---|---
This macro shows you how to create constraints on published elements. This macro opens the [CAAAsmCstOnPublish.CATProduct](samples/CstOnPublish.CATProduct) document that contains two parts: a plate, Plate.CATPart, and two instances of a screw, Screw.CATPart. It retrieves on each _Product_ object the _Publication_ objects corresponding to published elements identifying for example the position of the holes in the plate and the axis of the screws. It creates _Constraint_ objects to position those elements regarding one another. It then uses the `ReplaceComponent` method of the _Products_ collection to replace Screw.CATPart with NewScrew.CATPart, automatically reconnecting the constraints on the published elements of the new part.
  CAAAsmCstOnPublish is launched in CATIA [1]. No open document is needed. [CAAAsmCstOnPublish.CATScript](CAAAsmCstOnPublishSource.md) is located in the CAAScdAsmUseCases module. [Execute macro](macros/CAAAsmCstOnPublish.CATScript) (Windows only).
  CAAAsmCstOnPublish includes the following steps:

  1. Prolog
  2. Creating Constraints
  3. Replacing the Screw by Another Screw

#### Prolog

2. Creating Constraints
3. Replacing the Screw by Another Screw
The macro first loads CAAAsmCstOnPublish.CATProduct that contains two Part: Plate.CATPart and Screw.CATPart for which two instances have been created: Screw.1 and Screw.2. Those objects use the Publication capability of CATIA V5 to expose some of their elements using a stable name. The plate published as "Top" its top face and as "Hole1" and "Hole2" the center points of the two holes. The screw publishes as "HeadBottom" the bottom face of its head and as "Axis" its axis. ![](images/CstOnPubBefore.jpg)

      ...
```vbscript
```vbscript
```vbscript
    ' --------------------------
    ' Get the different products
    ' --------------------------
```

```

```

```vbscript
```vbscript
    Dim oRootProduct As Product
```vbscript
```
```vbscript
```cpp
    Set oRootProduct=CATIA.ActiveDocument.Product

    Dim oPlate As Product
    Set oPlate = CATIA.ActiveDocument.Product.Products.Item  ( "Plate.1" )

    Dim oScrew1 As Product
    Set oScrew1 = CATIA.ActiveDocument.Product.Products.Item  ( "Screw.1" )

    Dim oScrew2 As Product
    Set oScrew2 = CATIA.ActiveDocument.Product.Products.Item  ( "Screw.2" )
```
```

```

```

       ...

---

Once the new product document has been loaded, the `oPlate`, `oScrew1` and `oScrew2` variables are declared to receive the instance of the plate and the two instances of the screw. Those instances are fetched in the _Products_ collection of the Root _Product_ using their names.

Other variables, `oPlatePub`, `PlateRef`, `oScrewPub` and `oScrewRef` are declared and will be used in the following to receive plate and screws publications and the underlying published elements. Those published elements will be manipulated as _Reference_ objects.
#### Creating Constraints

    ...
```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Create offset constraint between plate
    ' top face and screws heads bottom faces
    ' --------------------------------------
    set oPlatePub = oPlate.Publications.Item("Top")
```

```

```

```vbscript
```vbscript
    Set oPlateRef = oPlatePub.Valuation
```vbscript
```
```vbscript
    '  ---> Plate/Top Screw1/HeadBottom

```vbscript
    Set oScrewPub = oScrew1.Publications.Item("HeadBottom")
    Set oScrewRef = oScrewPub.Valuation

    Dim oConstraint1 As Constraint
    Set oConstraint1 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef )

```
```

```

```

```vbscript
```vbscript
Dim oConstraint1 As Constraint
```vbscript
```
```vbscript
Set oConstraint1 = oConstraints0.AddBiEltCst  ( catCstTypeDistance, oPlateRef, oScrewRef )
```
```

    oConstraint1.Dimension.Value = 2.000000
    oConstraint1.Orientation = catCstOrientOpposite
```

    ...

---

The _Publication_ object corresponding to the top surface of the plate is fetched in the _Publications_ collection of tthe `oPlate` _Product_ object using its name: "Top". A reference on the underlying published object is then obtained using the `Valuation` method of the _Publication_ object. We proceed the same way for the bottom face of the head of the screw.

Using those 2 references an offset constraint is created using the `AddBiEltCst` method of the _Constraints_ collection. `AddBiEltSct` is used to create constraints involving two elements, valuating the first argument to catCstTypeDistance creates a distance (or offset) constraint between the two objects passed as second and third arguments. Constraint types are defined in the _CatConstraintType_ enum.

The `Dimension` method is used on the resulting _Constraint_ object to specify the value of the distance (here 2 mm) and the `Orientation` method allows to specify the orientation for the second geometric element with regard to the first one. Constraint orientations are defined in the _CatConstraintOrientation_ enum.

Three other constraints are created the same way: offset between the top face of the plate and the bottom face of the second screw and coincidence between the axis of each screw and the center of the corresponding home of the plate.

    ...
```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Update the Product ..
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' --------------------------------------
' Update the Product ..
' --------------------------------------
```

```

    oRootProduct.Update
```

    ...

---

The Root _Product_ is then updated to move the parts in a position respecting the contraints to newly created constraint giving the following result.

![](images/CstOnPubAfter.jpg)

    ...
```vbscript
    MsgBox "Click OK to replace the screw by another standard screw ..."
    ...
```

---

A message box is displayed allowing to see the intermediary result before going on. On Unix the result will only be visible at the end of the macro.
#### Replacing the Screw by Another Screw

    ...
```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Replace the screw by another one: constraints on
    ' published elements are autoatically reconnected ...
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
    Set oScrew1 = oRootProduct.Products.ReplaceComponent ( _
          oScrew1,                                                         _
```
          sDocPath & "/online/CAAScdAsmUseCases/samples/NewScrew.CATPart", _
          True)
```

```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Update the Product with the new Parts
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' --------------------------------------
' Update the Product with the new Parts
' --------------------------------------
```

```

    oRootProduct.Update
```

      ...

---

The `ReplaceComponent` method of the _Products_ collection of the Root Product allows to replace all instances of the reference product of `oScrew1 `(Screw.CATPart) by instances of a new reference product whose full Path is passed as second argument (here NewScrew.CATPart).

All constraints on published elements are automatically reconnected and updating the Root Product automatically positions the new instances in the assembly:

![](images/CstOnPubReplaced.jpg)

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create and use constraints on published elements using macros.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _Product_, _Publication_ _,_ _Constraint_ _,_ _Products_, _CatConstraintType_, _CatConstraintOrientation_
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
