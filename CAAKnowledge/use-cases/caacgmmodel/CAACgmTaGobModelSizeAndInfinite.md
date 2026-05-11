---
```vbscript
title: "About the Model Size and Infinite"
category: "use-case"
module: "CAACgmModel"
tags: ["CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmTaGobModelSizeAndInfinite.htm"
converted: "2026-05-11T17:33:47.947121"
```

---
# About the Model Size and Infinite  

---  
Technical Article  
## Abstract

Models must conform to validity criteria related to their size. Two parameters drive the model validity in terms of dimensions: the model size and the "infinite". These two parameters are explained below.
    * The Model Size and Infinite Values
    * The Rules  
---  
## The Model Size and Infinite Values

Here are the values of the model size and infinite:

  | Until V5R13 | From V5R14  
---|---|---  
Here are the values of the model size and infinite:
Model Size | [-100 meters, + 100 meters]  
on each coordinate  | [-1000 meters, + 1000 meters]  
on each coordinate  
Model infinite (10 x model size) | [-1000 meters, + 1000 meters]  
on each coordinate | [-10000 meters, + 10000 meters]  
on each coordinate  

The validity of geometric objects depend on their location within the limits defined by the model size and infinite. The validity rules are explained below.

## The Rules
### Rule 1

Except authorized infinite objects (see Rule 2), any relimited objects should be included in the model size. Objects that are not included in the model size are called infinite .
### Rule 2

The authorized infinite objects the user can create are: the planes, lines, half-lines and points. The visualization of such objects is always reframed at most to the model size. The parts of the infinite object that are not in the model size are not seen by the user.

![Rule 2](images/CAACgmGobinfinite0.gif)

The authorized infinite objects the user can create are: the planes, lines, half-lines and points. The visualization of such objects is always reframed at most to the model size. The parts of the infinite object that are not in the model size are not seen by the user.
_Should an infinite object necessarily fit in the "infinite"?_

No. An infinite object does not necessarily exactly fit in the model infinite. Usually, its larger coordinates are between half and twice the model infinite. 

When a plane is not parallel to canonical planes, it is usually not possible to relimit it exactly in the model infinite. When such an infinite plane is created, its half-dimension with the model infinite is determined. Thus a part of it is in the infinite, while a part of it is outside the infinite.

**Note** : at creation, infinite lines fit in the model infinite.

When a plane is not parallel to canonical planes, it is usually not possible to relimit it exactly in the model infinite. When such an infinite plane is created, its half-dimension with the model infinite is determined. Thus a part of it is in the infinite, while a part of it is outside the infinite.
_Are transformations of infinite objects valid?  
_Transformation of infinite objects are valid provided their origins remain within the model size.

![Rule 2 Examples](images/CAACgmGobinfinite1.gif)
### Rule 3

_Transformation of infinite objects are valid provided their origins remain within the model size.
The mathematical definition of an object should be in the model infinite.

_An example: the circle arc_

![Rule 3](images/CAACgmGobinfinite2.gif)

_An example: the circle arc_
The mathematical definition of the circle consists of a radius which must be smaller than the infinite and a center which must be in the infinite.

On the left-hand side figure, the created arc circle (in blue) is in the model size, the mathematical circle (in dashed green) is in the infinite (Rule 4). This model is valid.

The figures below are examples of unauthorized geometries. On the first figure, the model itself (the full circle in blue) sticks out from the model size.

![Rule 3 Example](images/CAACgmGobinfinite2bis.gif)

On the second figure, the model (the circle arc in blue) is in the model size but the mathematical definition does not fit in the infinite.

![Rule 3 Example](images/CAACgmGobinfinite3.gif)
### Rule 4

On the second figure, the model (the circle arc in blue) is in the model size but the mathematical definition does not fit in the infinite.
The origin of planes and lines should be in the model size.

_An example: the infinite line_

On the figure below, the infinite line and semi infinite line (in green) have their origin (green point) in the model size. The origin (orange point) of infinite plane has its origin in the model size.

![Rule 4](images/CAACgmGobinfinite5.gif)

On the first figure below, the relimited line (in non dashed-green) is in the model size, but its origin (green point on its support in dashed green) is not. The plane origin (orange point) is not in the model size. On the second figure, the origins of the line and the planes are not in the model size. 

![Rule 4 Examples](images/CAACgmGobinfinite4.gif)
## References

[1] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)  
---|---  
## History

Version: **1** [Jul 2005] | Document created  
---|---
