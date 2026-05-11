---
title: "About NURBS"
category: "use-case"
module: "CAACgmModel"
tags: ["CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmTaGobAboutNurbs.md"
converted: "2026-05-11T17:33:47.874094"
---
# About NURBS  
  
---  
Technical Article  
## Abstract

The NURBS model is now widely used in the CAD word to define curves and surfaces. It is the result of a continuous improvement of the curve and surface mathematical models. We first introduce the NURBS model and the objects it manages: knot vector, basis of functions, control points. Then, we describe how the Bzier points and Bernstein basis, uniform B-Splines, non-uniform B-Splines models can be seen as particular cases of the general NURBS model. We finally show how to use NURBS curves and surfaces in CGM. 

  * Introduction
  * The NURBS Model
    * NURBS Curve Definition
    * Knot Vector
    * Properties
    * NURBS Surfaces
  * From the General NURBS Model to Particular Cases
    * Non Uniform Polynomial B-Splines: NUPBS
    * Uniform B-Splines: UPBS
    * Bernstein Basis and Bzier Points
  * The NURBS in CGM
    * CATKnotVector
    * CATNurbsCurve
    * CATNurbsSurface
  * In Short
  * References

  
---  
## Introduction

The mathematical model of a curve is the description of the geometric form that the user wants to design in a way that can be handled by a CAD system. Ideally, a totally free curve in the 3D space has many infinitely degrees of freedom: it is the juxtaposition of an infinite number of points, and this is unusable for a CAD system. The mathematical model allows the CAD system to handle curves with a finite number of data. But it also put constraints on the objects it models: all the curves cannot be expressed with one model. We see here a key point of the mathematical model: it has to be judiciously chosen to be able to model as many types of curve representations as possible, with as less data as possible, in a as simple manner as possible.

A curve is a mono-parameterized element: the three Cartesian coordinates of a point of the curve are functions of one variable called parameter. The mathematical model for a line is simple: the coordinate functions are linear with the parameter. To model more complex curves, mathematical models use polynomial functions basis to expressed the coordinates functions. The way the polynomial function basis is chosen greatly influences the properties of the curves such as their continuity. The NURBS definition results of a continuous improvement of the development of these basis.

What has been described on curves also applies to surfaces. It the reason why, for a matter of simplicity, we present here the case of the curves. A specific discussion on the surfaces is proposed, but the general scheme is not run again for them.
## The NURBS Model

The NURBS (Non Uniform Rational B-Spline) model proposes the definition of a curve as a piecewise rational polynomial function of the **parameter** _u_. See [1] for a complete description of this model.
### NURBS Curve Definition

A NURBS curve is defined by **control points** _Pi, i=0..n_ , which influence is weighted by **rational polynomial functions** _Ri, i=0..n_ (dependent on the parameter) and **weights** _wi, i=0..n_ (independent on the parameter). The rational polynomial functions _Ri_ are defined by the means of a **basis** , called B-Spline basis, set of piecewise polynomial functions _Nik, i=0..n_ , of same **degree** _k_. The degree of the NURBS curve is the degree of the polynomial functions.

![Nurbs Equations](images/CAACgmGobNurbsEquations1.gif)

The definition of the basis _Nik_ is uniquely determined by a **knot vector**. The pieces of the basis polynomial functions are called **arcs**. They represent an interval for the parameter values to calculate a segment of shape.

The control points are not, in general, points of the NURBS curve. By convention however, the first and last control points are the begin and end point of the curve respectively, except for the periodic NURBS curves. These control points can be seen as an attracting zone for the curve, which influence is weighted as seen previously.
### Knot Vector

The knot vector is the way to state the definition of the basis. In particular, it manages the continuity between the different arcs of the basis functions, and, hence, the curves that use it. The knot vector is a set of non decreasing parameter values _(t_0,..,t_m)_ , called **knot values** or **knots**. The B-Spline basis is recursively defined as follows, with _i=0,..,n_ :

![Nurbs Equations](images/CAACgmGobNurbsEquations2.gif)

with the following conventions:

![Nurbs Equations](images/CAACgmGobNurbsEquations6.gif)

The relation between the number of knots (_m+1_), the degree (_k_) of _Nik_ and the number of control points (_n+1_) is given as follows:

_m = (n+1) + k_

Knot values are non-decreasing, so a knot vector can have knots with the same value. In this case, the knot is called **multiple** , and its multiplicity is the number of repetitions of the same value. There are as many arcs as knots of different values plus one. If the increment is always 1, the knot vector is called **uniform**.

The multiplicity is a way to specify the **continuity order** between the arcs. Hence, there is a relation between the multiplicity and this continuity order: 

  1. For an internal knot value (neither the first, nor the last), the continuity order is the degree minus the multiplicity. As a consequence, the multiplicity of a knots cannot be strictly greater then the degree.
  2. By convention, for a non periodic basis (open curve), each extreme knot value has a multiplicity equal to the degree plus one.
  3. For a periodic basis (they are used to model closed curves), the first point applies for all knots. Moreover, the first and last multiplicities are the same.

The following table summarizes these relations:

| Multiplicity (`m`) | Continuity order  
---|---|---  
internal knot values | `1 <= m <= degree` | `Degree-m`  
extreme knot values for a non periodic basis | `degree+1 `(by convention) | `(-1)`  
same first and last multiplicities for a periodic basis | `1 <= m <= degree` | `Degree-m`  
  
**Example 1** :

Knot vector of one arc of degree 3: 0 0 0 0 1 1 1 1  
In this case, there are four control points

Fig. 1: Illustration of Example 1 ![Nurbs](images/CAACgmGobNurbs2.gif) | The green curve has four control points (CP1 to CP4). If you move CP3 to CP3', the curve is attracted by this new points. Notice two important properties of this kind of NURBS, called Bezier arc: 

  * The curve is inside the convex hull of the control points
  * The curve is tangent to the segment joigning the first and second control points at the beginning of the curve, and to the segment joining the last and next to last control points at its end.

  
  
**Example 2** :

Non uniform knot vector, 3 arcs of degree 3, C2 continuity: 0 0 0 0 2 8 9 9 9 9  
In this case, there are six control points

Fig. 2: Illustration of Example 2 ![Nurbs](images/CAACgmGobNurbs1.gif) | The green curve is an example of non uniform polynomial B-Spline curve, having the knot vector of the example 2. The weight of each control point is 1. If you assign (1,1,10,20,5,1) to the control points, it gives the red curve. This curve is attracted by the control points CP3 and CP4, that are more weighted than the others. These curves have three arcs: CP1-K1, K1-K2, K2-CP2.  
---|---  
  
According to the definition, it is possible to create NURBS curves that are only C0 or C1 continuous. Despite of this fact, remember that the CGM geometric operators suppose that the geometry is at least C2 continuous.
### Properties

  * The NURBS provides a unified mathematical model for representing 
    * analytic shapes (such as conics or quadric surfaces, that cannot be handled by the Bzier model, by uniform B-Splines or non uniform B-Splines)
    * free form entities, used to design car bodies for example.
  * Their model easily manages the continuity between the arcs, and their algorithm are fast and numerically stable.
  * Their are invariant under common geometric transformations such as translations and rotations.
  * They generalize the concepts of uniform B-Splines and Bzier curves and surfaces.

### NURBS Surfaces

A NURBS surface is defined in a similar way, by moving from one parameter to two parameters. The arcs become **patches**. The parametric definition of the surface is:

![Nurbs Equations](images/CAACgmGobNurbsEquations3.gif)

As for the curve, the NURBS surface model handles the continuity, through the multiplicity of the knots, but now, two knot vectors are needed, one for each direction of the surface.
## From the General NURBS Model to Particular Cases

The NURBS model is the result of a continuous improvement of the function basis definition. We recall here the evolution of the different models that leads to the generalized concept of NURBS. Only definitions for curves are given, the definitions for surfaces being defined in a similar way.
### Non Uniform Polynomial B-Splines (NUPBS)

A NUPBS curve is defined by **control points** _Pi, i=0..n_ , which influence is directly (and only) weighted by the polynomial functions _Nik, i=0..n_ (dependent on the parameter). These polynomial functions are still defined by the knot vector.

![Nurbs Equations](images/CAACgmGobNurbsEquations4.gif)

As for the NURBS, this gives a flexible way to define arcs and the continuity between them. But now, NUPBS cannot model the conics as for the NURBS.
### Uniform Polynomial B-Spline (UPBS)

This is a particular case of NUPBS: 

  * the internal knots multiplicity is 1
  * the extreme knots multiplicity is the degree plus 1
  * the difference between two internal knots is always 1.

In this case, the basis becomes uniform. The continuity between the arcs cannot be changed: it is always the degree minus 1, and there is now a direct relation between the number of arcs (_l_) and the number of control points (_n+1_)

_l = n - k_
### Bernstein Basis and Bzier Points

NURBS, NUPS, UPBS have a common feature: the continuity between arcs is managed, with more or less flexibility, by the model with the knot vector. The arcs definitions are linked together. Now, the Bernstein-Bzier model defines a basis for one arc. To define a curve with several arcs, you have to connect arcs, each arc being independent on its neighbors. Hence, the continuity is not managed by the model, you have to put constraints between the different arcs to insure it.

The parametric equation of an arc of degree _k_ and the functions of the basis are as follows:

![Nurbs Equations](images/CAACgmGobNurbsEquations5.gif)

The control points _Pi_ are called Bzier points.

The transformation of a NURBS curve into a Bernstein-Bzier curve amounts to increase the multiplicity of the knots until having a C0 continuity. Conversely, the transformation of a Bernstein-Bzier curve into a NURBS curve amounts to build a knot vector for which the knots have a multiplicity equal to the degree.

Fig. 1 displays examples of Bzier arcs.
## The NURBS in CGM

Two interfaces and a class manage the NURBS model in CGM: the CATNurbsCurve and CATNurbsSurface interfaces and the CATKnotVector class.

Note: Periodic NURBS are not supported.
### CATKnotVector

This class handles the knot vector definition. Instances of this class are transient, they cannot be directly stored. However, they are saved as private data of the curve and surface, of which they are the B-Spline basis definition. The knot vector is defined as compressed, that is to say that, for evident numerical reasons, all the knots have different values and their multiplicity is managed by a specific array. Hence, a CATKnotVector has the following definition:

long | Degree | The degree of the B-Spline basis functions  
---|---|---  
CATBoolean | IsPeriodic | 1 for a periodic basis (not supported): the parameter domain is unlimited. If `Delta= LastKnotValue - FirstKnotValue`, the evaluations at `Parameter + Delta` and `Parameter` are the same.  
0 otherwise  
CATBoolean | IsUniform | 1 in case of equally spaced knot values.  
0 otherwise.  
long | NbOfKnots | The size of the compressed knot vector ( `=NbOfArcs + 1)`  
long | Knots | The array of the knots  
long | Multiplicities | The array of the multiplicity of a knot value  
  
In the case of the two previous examples, this leads to:

  * Example 1  
Knot vector of one arc of degree 3: 0 0 0 0 1 1 1 1  Degree | IsPeriodic | IsUniform | NbOfKnots | Knots | Multiplicities  
---|---|---|---|---|---  
3 | 0 | 1 | 2 | 0 1 | 4 4  
  * Example 2  
Non uniform knot vector, 3 arcs of degree 3, C2 continuity: 0 0 0 0 2 8 9 9 9 9  
In this case, there are six control points  Degree | IsPeriodic | IsUniform | NbOfKnots | Knots | Multiplicities  
---|---|---|---|---|---  
3 | 0 | 0 | 4 | 0 2 8 9 | 4 1 1 4  

### CATNurbsCurve

Note: Periodic NURBS are not supported.

This interface manages the NURBS curves in CGM. As a NURBS curve is a kind of curve, it inherits all the properties of the CGM curves (CATCurve, see [2]). It is defined as follows:

CATKnotVector | `KnotVector` | The knot vector for the polynomial basis definition  
---|---|---  
CATMatSetOfPoints | `Vertices` | The set of control points  
CATBoolean | `IsRational` | 1 if the NURBS is rational, else 0  
double[] | `Weigths` | The weigths array if `IsRational`  
  
By default, the CATNurbsCurve constructor adapts the parametrization of the knots, according to the length of the curve. Hence, if you ask for the CATKnotVector of a NURBS curve you have just created, you find different data for the knots. If you want that your curve keeps the initial parameterization, set the `CATParameterizationOption` to `CatKeepParameterization` (optional argument).

To design NURBS curves defined in the space of a surface, use the CATPNurbsCurve interface: in this case, a control point has two coordinates, its parameter values in the space of the surface.
### CATNurbsSurface

Note: Periodic NURBS are not supported.

This interface manages the NURBS surfaces in CGM. As a NURBS surface is a kind of surface, it inherits all the properties of the CGM surfaces (CATSurface, see [3]). It is defined as follows:

CATKnotVector | `UKnotVector` | The knot vector for the polynomial basis definition on the surface first direction  
---|---|---  
CATKnotVector | `VKnotVector` | The knot vector for the polynomial basis definition on the surface second direction  
CATMatSetOfPoints | `Vertices` | The set of control points  
CATBoolean | `IsRational` | 1 if the NURBS is rational, else 0  
double[] | `Weigths` | The weigths array if `IsRational`  
## In Short

  * The NURBS model is an industry standard tool for the representation and design of geometry.
  * They are the result of a continuous improvement of the polynomial function basis definition.
  * CGM handles the NURBS curves through the CATNurbsCurve interface, the NURBS surfaces through the CATNurbsSurface interface and the knot vector definition with the CATKnotVector class.

## References

[1] | The NURBS book- Les Piegl, Wayne Tiller- Springer 1995  
---|---  
[2] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)  
[3] | [The Surfaces of CATIA Geometric Modeler](CAACgmTaGobSurfaces.md)  
## History

Version: **1** [Mar 2000] | Document created  
---|---
