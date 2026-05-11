---
title: "The Objects of CATIA Geometric Modeler"
category: "use-case"
module: "CAACgmModel"
tags: ["CATICGMContainer", "CATICGMObject", "CATIContainer", "CATICGMObjects", "CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmTaGobGeoObjects.md"
converted: "2026-05-11T17:33:47.936600"
---
# The Objects of CATIA Geometric Modeler  
  
---  
Technical Article  
## Abstract

CGM mainly offers objects that have a geometric or topological meaning such as curves, surfaces or topological bodies. It also provides objects to manage and operate them. This paper introduces the objects you can use in the CGM offering, and goes in more details through the persistent objects and their environment. 
    * Introduction
    * Container, Factory, and Document
      * Properties of the CGM Container and Factory
        * A CGM Container Is Complete
        * Persistent Tag
        * Implicit and Explicit Factories
      * Use of the CGM Container and Factory
        * Document
        * Viewer and Workshop
        * Integration into CATIA V5
    * Persistent CGM Objects: CATICGMObject
      * Base Interface of the Geometric Objects: CATGeometry
      * C2 Continuity
      * Points: CATPoint
      * Curves: CATCurve
      * Surfaces: CATSurface
      * Topology
    * Units and Tolerance
      * Unit
      * Model Size
      * Resolution
      * Numerical Tolerance
    * In Short
    * References  
---  
## Introduction

CGM offers a large variety of objects, allowing a developer to build its own geometric or topological applications. We find : 

    * _Persistent objects_. Federated by the **CATICGMObject** interface, they group all the objects of the CGM offering that can be streamed. The main part of these objects are the **CATGeometry** objects, which group the usually called geometric objects (such as points, curves, surfaces of all kinds), and the topological objects (such as vertices, edges, faces, volumes and bodies), that also are subtypes of geometric objects.
    * _The managers of the persistent objects_. The **CATICGMContainer** interface manages the membership of the CATICGMObject instances to a given container (a set containing the elements) while the **CATGeoFactory** interface creates the geometric instances inside a container. CATICGMContainer and CATGeoFactory instances can of course be streamed.
    * _Non persistent (or transient) objects_ , that roughly are: 
      * _Mathematical objects_ : used for mathematical computations, they are often employed by the geometric objects. Vectors, matrices, equations, transformations are examples of mathematical objects [1].
      * _Operators_ on CATGeometry objects. Federated by the **CATCGMOperator** class, they build new geometric objects or topological objects from existing one. Examples of geometric operators are the intersection of curves and/or surfaces, the projection on curves or surfaces or the search for geometric coincidence. Examples of topological operators are the Boolean operations, the creation of a topological prism or the filleting of a body. See Operating geometric objects, Operating topological objects.
      * Objects that manages the _parameters_ on curves and surfaces, and the mapping between theses parameters and the global coordinates.
    * _Attributes_ , allowing a programmer to add data on exiting CATICGMObjects, this data may be transient (**CATCGMAttribute**) or persistent (**CATCGMStreamAttribute**). See [2].
Fig. 1: The Main Families of CGM Objects ![CGM Objects](images/CAACgmGobGeoObjects1.gif) | Into the right angle boxes are shown the main permanent objects, as described upper. Inside the round angle boxes are written the transient objects. We only represent the main objects families. For a full detail of the composition of each family, see the References item, which links you to the adequate paper according to the object you want to study.  
---|---  
## Container, Factory and Document

A container is a set containing and managing objects. Hence, the CATICGMContainer interface represents the behavior of the CGM container, that manages the CATICGMObject instances. It gives a persistent tag to each instance it creates and follows the links between the CATICGMObject instances. It allows the developer: 

    * To scan the CATICGMObject instances that it contains.
    * To remove any CATICGMObject instance.
    * To find an instance from its persistent tag.
    * To stream its contents.

The CATGeoFactory gives another view of a CATICGMContainer. It is a kind of CATICGMContainer that manages: 

    * The definition of the unit.
    * The validity range (minimum length, maximum length) of the CATGeometry instances.
    * The creation of the CATGeometry instances.
### Properties of the CGM Container and Factory

As seen previously, the CATICGMContainer contains and the CATGeoFactory creates. We described here some other properties of these objects.
#### A CGM Container Is Complete

All the objects needed for the definition of a topological and geometric instance must be created inside the container of this instance.
#### Persistent Tag

When an instance is created inside a (explicit or implicit) factory, it gets an unique identifier called "persistent tag". This tag remains the same as long as the instance is not removed. Hence, it is not modified even if:

    * Other instances are created or removed from the factory.
    * The factory is streamed or unstreamed.
    * Data of this instance is modified.

But it is canceled with the removal of the instance.
#### Implicit and Explicit Factories

The creation of a CATGeoFactory instance really triggers the creation of two factories (called explicit factory and implicit factory), with the same unit and validity range. All methods we have described are available for both factories, except the `CATICGMContainer::Scan` method, that only scans the explicit factory.
### Use of the CGM Container and Factory

Given the CATGeoFactory, you already can write your own applications, visualize the data by your own viewer and save the data using our own repository. If you do not have such viewer or repository, you can use these offered by CGM.
#### Document

No specific document is required to store the persistent CGM objects. Each application writes the CGM objects in its own document but have to put them consistently inside a geometric container (CATGeoFactory).

Now, if you are not owner of any document, but you want to store your data, CGM puts a .NCGM document to your disposal.

The reference of CGM instances from a document to another one is offered by the ObjectModeler hyperlinks.
#### Viewer and Workshop

Moreover, a viewer and a workshop, associated with the .NCGM document, are provided to illustrate the CGM use. In this implementation, the viewer only displays the objects of the explicit factory, but it is its own choice.
#### Integration into CATIA V5

To let CGM possibly be independent of the CATIA V5 environment, the CATGeoFactory does not require all the properties of a CATIA V5 container. In fact, if you examine the behavior of the CATGeoFactory interface, you can see that is not a CATIA V5 container, because it does not adhere to the CATIContainer interface. In particular, it does not allow an application to include other container in itself.

However, CATIA V5 brings a higher level object, created by the CATIA V5 factory of containers, that is a CATIA container, and also adheres to CATGeoFactory. In this environment, you take advantages of the CATIContainer interface and the CATGeoFactory interface.

Fig. 2: Available Interfaces According to the Offering ![Interfaces](images/CAACgmGobGeoObjects2.gif) | The CATGeoFactory interface is different from the CATIContainer interface. CGM proposes an object adhering to the CATGeoFactory interface, while CATIA V5 offers an object also adhering to the CATIContainer interface.  
---|---  
  
As an example, this object will be seen when you use a Part document, that contains a SpecModeler/Part container, a Generic Naming container, and a geometric container.
## Persistent CGM Objects: CATICGMObjects

CATICGMObject is the basis interface for all the persistent objects of the CGM offering. The CATICGMObject instances are explicit or implicit according to the factory they belong to and are identified through a persistent tag. They offer more behaviors: 

    * They can support attributes. Attributes allow an application programmer to put data on a CATICGMObject. See [2].
    * They can be cloned, (i.e., duplicated with or without the instances that are forward linked) by the use of a `CATCloneManager`. The clone process is detailed in [7].

Most of the CATICGMObject have a geometric meaning. They are grouped under the CATGeometry interface. Up to now, there is only one CATICGMObject that is not a CATGeometry: the CATLaw, that models the variation of a parameter on an interval.
### Base Interface of the Geometric Objects: CATGeometry

The added value of the CATGeometry interface is its geometric meaning. Hence, a CATGeometry object offers: 

    * The ability to return the definition of a portion of the space (called bounding box) that contains it.
    * The ability to be moved.

and many other behaviors, depending on the kind of CATGeometry.

The CATGeometry interface groups 

    * The usually called geometric objects: points (dimension 0), curves (dimension 1) and surfaces (dimension 2).
    * The topological objects (bodies, cells and domains), that are fully documented in [5] for the concepts and [6] for the CGM implementation.
### C2 Continuity

The main assumption made on the geometric objects is that **they must be C2 continuous**. CGM directly generates objects satisfying this criterion. If you want to introduce foreign curves or surfaces, you have to insure they satisfy it. If they do not satisfy it, you can cut them where they are not C2 continuous, and use topological objects to assemble the parts.

Before dealing with the curves (base class CATCurve) and the surfaces (base class CATSurface), we briefly presents the geometric points (CATPoint).
### Points

There mainly are three geometric point interfaces: 

    * CATCartesianPoint, allowing you to modify the Cartesian coordinates.
    * CATPointOnCurve and CATPointOnSurface, representing the behavior of points on a curve and on a surface respectively. Hence, they give the mapping between the Cartesian coordinates and the parameters on the curve or the surface.
    * CATMacroPoint, used to define the geometry of a vertex (the vertex the is topological object of the lowest dimension).
    * CATPointOnEdgeCurve, representing a point on a specific curve called edge curve, used to define the geometry of a topological edge [8].

```vbscript
Do not confuse CATPoint and CATMathPoint!

```

    * CATPoint is a geometric interface. Instances are created with the CATGeoFactory and can be streamed.
    * CATMathPoint is a mathematical class. Instances are created with the class constructor and are transient: they cannot be streamed.
### Parameters on Curves or Surfaces

A point on a curve may be represented with 3 coordinates, as a point in a 3D space, or with 1 parameter (usually called `w`) in the space of the curve.

In the same way, a point on a surface may be represented as a 3D point or with two parameters (usually called `u` and `v`) in the space of the surface.

These parameters have only sense if they are associated with the curve or the surface they parameterize. Hence, the object is responsible for the mapping between the 3D coordinates and the parameter(s), and the user of these objects must never make any assumptions about this mapping.
### Surfaces in CGM

CGM offers several types of surfaces: 

    * Elementary surfaces: canonical (cylinder, cone, sphere, torus, plane) or NURBS surfaces.
    * Sampled surfaces: their limiting curves are computed by Spline interpolation between points from a marching algorithm.
    * Multi-represented surfaces: these surfaces delegate the evaluation to another one, which is as much as possible canonical.
    * Procedural surfaces: the procedural surface use the evaluation of another one to compute its own evaluation (more than a simple delegation).

All the CGM surfaces are precisely described in [4].

If you have specific surfaces that no CGM surface fits, CGM allows you to define your own surface, and use it as if it were a CGM surface. See [2] for a precise description of this capability.
### Curves in CGM

CGM offers several types of curves:

    * Resolved curves: these curves have a mathematical form: line, conic (circle, ellipse, parabola, hyperbola), NURBS, Spline belong to this type. Evaluations are made directly from the mathematical equations.
    * Edge curves: they are geometric curves, that can be seen under several representation. They are in particular used to define the geometry of a topological edge [8].
    * P-curves: they are used to define curves in the parameter space of a surface. For example, a P-line is a curve the mathematical representation of which in the space of the surface is a line, but can be a line, a circle or a much more complex curve in the 3D space.

All the CGM curves are precisely described in [5].

If you have specific curves that no CGM curve fits, CGM allows you to define your own curve, and use it as if it were a CGM curve. See [2] for a precise description of this capability.
### Topology

The topological objects are geometric objects, and managed in the same container. These topological objects are bodies, cells (vertex, edge, face, volume) and domains (loop, shell, wire, lump). See [5] for the topological concepts and [6] for their implementation in CGM.
## Units and Tolerance

This section explains how CGM deals with the units and the tolerances for its objects.
### Unit

The geometric factory is the object that creates any geometric objects. The unit of the geometric factory is the mm.

The angles are defined in radians in the whole CGM offering. Constants (`CATRadianToDegree`, `CATDegreeToRadian`) allows you to convert degrees to radians and the converse.
### Model Size: the Bounding Box of the CGM Model

The factory defines the maximum box inside which the geometric objects must be. This box is defined by the _Model Size_ , fixed to 10^6mm (10^5mm before R14). As the unit is the millimeter, all the objects must be inside the box [-1000m, +1000m] ([-100m, +100 m] before R14).
###  Resolution: the Lower Valid Length of an Object of the CGM Model

The _Resolution_ defines the minimum length of a valid object. It is fixed to `10^-3.unit`. As the unit is mm, lines of length smaller than `1micro-m` are not valid.

The management of confusions ("Do two objects have the same geometry?") is a direct consequence of the resolution: if the distance between two geometric points is less than the resolution, the two points are considered to be geometrically at the same location.

However, the resolution is not a maximum gap (between adjacent surfaces for example). In fact, the topology captures the design intent, and the gap between the geometry of two faces sharing the same edge can be greater than the factory resolution: the modeler is tolerant.
### Numerical Tolerance

All the algorithms use a numerical tolerance, much more precise than the resolution.
## In Short

    * CGM offers persistent objects to model geometry and topology.
    * These objects are created inside a factory called CATGeoFactory.
    * Non persistent objects are used to do mathematical computations or operations on geometric or topological objects.
## References

[1] | Using the Mathematical Classes  
---|---  
[2] | [The Management of Foreign Data](CAACgmTaGobAttribute.md)  
[3] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)  
[4] | [The Surfaces of CATIA Geometric Modeler](CAACgmTaGobSurfaces.md)  
[5] | [Topology Concepts](CAACgmTaTobTopoConcepts.md)  
[6] | [The CGM Topological Model](CAACgmTaTobTopoModel.md)  
[7] | [The Clone and Transformation Managers](CAACgmTaGobClone.md)  
[8] | [Scanning an Edge Curve](CAACgmUcTobEdgeCurve.md)  
## History

Version: **1** [Mar 2000] | Document created  
---|---
