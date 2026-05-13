---
title: "About Numbers, Literals, and Units"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: "[]"
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfLiteralUnits.htm"
converted: "2026-05-11T17:31:52.422043"
---
## Infrastructure

 |
 ## About Numbers, Literals, and Units

 * * *

 Except when explicitly documented, numerical values stored and internally handled for computations are expressed using the MKSA unit system except for two dimensions:

     * Length are expressed in mm
     * Angles are expressed in decimal degrees

Except when explicitly documented, numerical values stored and internally handled for computations are expressed using the MKSA unit system except for two dimensions:
 This means that dimensions returned **may not be homogeneous** : surfaces are not returned in mm2 (by homogeneity with length in mm) but in m2 (MKSA).

 The user interface can be set to display and get values from the end user according to another unit system which better match your needs or habits.

 The parameter values you can set using macros must be expressed using the same unit system, since the user interface filter does not exist when you run macros. This also ensures your macros portability. There is one exception: the literals.

 Literals are specific objects that represent a parameter with a given type. For example, the **Length** object is dedicated to store a length, but its state of object brings more that the simple value storage. The **Length** object derives from the **Dimension** object, and thus inherits from it the **ValuateFromString** method. This method allows the value stored in the **Length** object to be valuated using a figure and a unit. For example, valuate the radius of a face fillet using the **Radius** property of the **FaceFillet** object which aggregates a **Length** object to store this radius:

     MyFaceFillet.Radius.ValuateFromString("5.08mm")

 The character string is interpreted as a value of 5.08 expressed in mm. You can enter a decimal value since the **Dimension** object derives from the **RealParam** object which allows for real values to be set. You may want to enter inches instead. Simply write:

     MyHole.Diameter.ValuateFromString("2in")

> ![image](../../assets/images/ainfo.gif) | ** ** To be compatible with formulas syntax, if you don't specify a Unit for the argument of **ValuateFromString** , the MKSA units are used:  length are expressed in meters and angles in radians.
The character string is interpreted as a value of 5.08 expressed in mm. You can enter a decimal value since the **Dimension** object derives from the **RealParam** object which allows for real values to be set. You may want to enter inches instead. Simply write:
MyHole.Diameter.ValuateFromString("2in")
As a thumb rule, always specify the unit when using **ValuateFromString** or formulas.

 The available unit symbols you can use are those listed in the Units tab-page of the **Tools- >Options** menu. The **RealParam** and the **IntParam** objects provide to their derived objects the **Value** method which sets or returns the value expressed in the MKSA unit system, except for length expressed in millimeters and angles expressed in decimal degrees.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
