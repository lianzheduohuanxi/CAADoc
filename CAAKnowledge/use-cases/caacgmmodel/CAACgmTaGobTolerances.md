---
title: "The Management of Tolerances"
category: "use-case"
module: "CAACgmModel"
tags: ["CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmTaGobTolerances.md"
converted: "2026-05-11T17:33:47.977985"
---
# The Management of Tolerances  
  
---  
Technical Article  
## Abstract

The topology is a way to logically describe connections between objects. And it may happen that the underlying geometry does not exactly join, leading to gaps. This article describes how these gaps are managed, in particular by the Boolean operations.
    * General Principles
    * The Resolution of the Factory
      * Model Size
      * Resolution
      * Modification of the Unit and the Model Size
    * How Gaps Are Taken Into Account by the Boolean Operators
    * In Short
    * References  
---  
## General Principles

The _resolution_ , defined at the level of the geometric factory you are working with, is the _tolerance of creation_ of the geometric objects: it defines the lowest admissible length of a geometric object. Hence, curves or edges of length less than the factory resolution are not created, for example.

But the geometric operators, such as intersection or projection, run until the numerical precision, much more precise than the resolution of the factory.

To stay inside the limits of the relative numerical tolerance, the resolution fixes the maximum size of the model, called _ModelSize_.

In another hand, the topology is a way to logically capture the design intend. Hence, an edge can logically links two faces which underlying surfaces are not contiguous: there is no maximum value on the gap between theses surfaces, although CGM tries to avoid to create situations with large gaps.

In the same manner, the sharpness criterion can be logically put on an edge. The sharpness defines the tangential continuity of two edges, or the continuity of the normals of two faces. This criterion is global on the edge, and influences the behavior of the propagation of some topological operators (such as the filleting operator).

    * If the edge is said smooth, the fillet is always propagated.
    * If the edge is said sharp, this does not say that the fillet is never propagated. In fact, it may be locally smooth, and must be propagated in this case. The locally smoothness is decided if the sharpness angle is less than the _tolerance of sharpness_ ( `CATTopSharpAngle`) at that location.

We first recalled how the resolution is defined, then study the behavior of the Boolean operator when it encounters topologies with underlying geometry that presents gaps.
## The Resolution of the Factory

The geometric factory is the object that creates any geometric objects. The unit of the geometric factory is the mm.
### Model Size: the Bounding Box of the CGM Model

The factory defines the maximum box inside which the geometric objects must be. This box is defined by the _Model Size_ , fixed by default to 1km (100m before R14). All the objects must be inside the box [-1km, +1km] for CATParts created after R14.
###  Resolution: the Lower Valid Length of an Object of the CGM Model

The _Resolution_ defines the mimimum length of a valid object. It is fixed to `10^-3.unit`. As the unit is mm, lines of length smaller than `1micro-m` are not valid.

The management of confusions ("Do two objects have the same geometry?") is a direct consequence of the resolution: if the distance between to geometric points is less than the resolution, the two points are considered to be geometrically at the same location.

An other consequence of the resolution is that edges of length less than the resolution cannot be created. This has a direct impact on Boolean operators for example.

Fig. 1: Influence of the Resolution on the Creation of Topological Objects. ![Resolution Influence on Topological Object Creation](images/CAACgmGobTolerances1.gif) | On top, if D is greater than the resolution, a new face is created, with edges of length greater than the resolution.  
---|---  
On bottom, if D is less than the resolution, the face is gripped to become two faces.  
### Modification of the Unit and the Model Size

Unit and Model Size cannot be changed by the user. When you create a geometric factory, its unit is the mm and the Model Size is 10^6mm=1000m in R14 and after R14 and 100m before R14.

However, when you open an existing geometric factory that you did not create, do not suppose its unit and Model Size: recover them by the `CATGeoFactory::GetUnit`, `CATGeoFactory::GetModelSize` methods.
## How Gaps Are Taken Into Account by the Boolean Operators

The topology is a logical information of connections. This logical information is related to geometry, which can be not exactly contiguous. But CGM does not impose a maximum gap for extremities of curves to be the same vertex, or to curves to be the same edge. In fact, remember that the resolution is not a gap tolerance, but a creation tolerance. So that it allows you to create topologies with gaps (the underlying geometry do not exactly connect together), although it does not create itself gaps larger than the resolution.

Let be a body, that is to say a general topological object. Imagine that this body have gaps larger than the resolution, because it comes from a system that allows them, for example CATIA V4. The question is to know how these gaps are taken into account by the topological operators.

Imagine that in this body, there is an edge that connects two faces F1 and F2 with a gap larger than the resolution. A Boolean operation is asked between these two faces and a third one, F3. The gap that is really important to take into account is the tangential gap along the edge.

Fig. 2: Management of a Gap in a Boolean Operator ![Gap Management in a Boolean Operator](images/CAACgmGobTolerances2.gif) | If T is less than the resolution, no edge is created. The initial gap G has not been widened. If T is greater than the resolution, a New Edge can be (and then is) created, with its corresponding geometry, as a merged curve. This merged curve references two curves, one on the surface of the third intersecting face F3, the other being the Edge Curve of the edge between the two faces F1 and F2. The initial gap has not been widened too.  
---|---  
Fig. 3: Management of an Overlapping in a Boolean Operator ![Overlapping Management in a Boolean Operator](images/CAACgmGobTolerances3.gif) | In case of an overlapping, instead of a gap, the initial treatment is the same. Then, the operator checks that it does not generate a Z configuration. If it does, the Z is eliminated to lead to a correct edge.  
---|---  
## In Short

    * The Model Size is the maximum length of a valid object. The resolution and the unit are defined at the creation of the geometric factory (`CATGeoFactory`).
    * The model size determines the lowest length of a valid object, called the resolution of the factory. The resolution is a tolerance of creation, and then of confusion, but not a tolerance of gaps: You can import bodies with gaps larger than the resolution, although CGM tries to avoid the creation of such bodies.
    * The topological operators take the gaps into account, and create, when necessary and if needed, edges to fill them. They do not create new discontinuities, so that the resulting bodies are compatible with regard to their gap quality: the initial gaps are not widened.
    * The tolerance of sharpness is a way to decide of the local sharpness quality, when it is not globally defined as smooth for a given edge.
## References

[1] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)  
---|---  
## History

Version: **1** [May 2000] | Document created  
---|---
