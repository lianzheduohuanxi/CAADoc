---
```vbscript
title: "About NURBS"
category: "use-case"
module: "CAACgmModel"
tags: ["CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmTaGobSurfaces.htm"
converted: "2026-05-11T17:33:47.967121"
```

---
# The Surfaces of CATIA Geometric Modeler  

---  
Technical Article  

* * *
### Abstract

CGM offers a great variety of surfaces. This paper describes their common properties as well as their particular features. 
    * **Introduction**
    * **Properties**
      * General Validity Criteria
      * Surface Parameters
      * Limits and Bounding Box
      * Evaluation
      * Equations
    * **Various Types of Surfaces**
      * Resolved Surfaces
      * Sampled Surfaces
      * Multi-represented Surfaces
      * Procedural Surfaces
    * **In Short**
    * **References**  
---  

* * *
### Introduction

A surface is a function from a closed interval of R^2 to R^3. Hence, it is defined by three scalar functions of two variables. The variables are usually called **parameters** of a point on the surface and denoted through **U** and **V** , while the scalar functions represent the mapping, for each point of the surface, between the Cartesian coordinates, usually called X, Y, Z, and the corresponding parameters U and V.

Fig. 1: The mapping between the parameters and the Cartesian coordinates ![Surfaces1.gif \(3848 bytes\)](images/CAACgmGobSurfaces1.gif) | Three scalar functions FX, FY and FZ map the (U,V) parameters into the Cartesian coordinates (X, Y, Z) for each point P of the surface.  
---|---  

A surface is a function from a closed interval of R^2 to R^3. Hence, it is defined by three scalar functions of two variables. The variables are usually called **parameters** of a point on the surface and denoted through **U** and **V** , while the scalar functions represent the mapping, for each point of the surface, between the Cartesian coordinates, usually called X, Y, Z, and the corresponding parameters U and V.
Fig. 1: The mapping between the parameters and the Cartesian coordinates ![Surfaces1.gif \(3848 bytes\)](images/CAACgmGobSurfaces1.gif) | Three scalar functions FX, FY and FZ map the (U,V) parameters into the Cartesian coordinates (X, Y, Z) for each point P of the surface.
Multi-patches surfaces are defined as a set of (n_u*n_v) connected pieces, each piece, called patch, having its own parameterization. Hence, a point belonging to the surface can be expressed in terms of: 

    * Local parameters: (u,v) parameters on a given patch, independently of the other patches
    * Global parameters: (U,V) parameters taking into account the preceding patches parameterization.
Fig. 1b: Local and global parameters on a 3*2 patches surface ![Surfaces1b.gif \(5335 bytes\)](images/CAACgmGobSurfaces1b.gif) | The Cartesian coordinates of the point P can be evaluated using the global parameter (U,V), or the local parameter (u_3,v_2) on the (3,2)th patch.  
---|---  

[Top]
### Properties of the CGM Surfaces

The CGM surfaces implement the CATSurface interface, which behavior is now described. The CATSurface interface inherits all the behavior of the CATGeometry interface. Therefore, the factory of the CGM objects (CATGeoFactory) handles the creation, stream, unstream and remove of the CGM surfaces. The geometric transformation and/or duplication of CGM surfaces is managed by specific processes through CATTransfoManager and CATCloneManager instances [3]. For more details about the CGM objects general properties, see [1].

[Top]
#### General Validity Criteria

The CGM surfaces implement the CATSurface interface, which behavior is now described. The CATSurface interface inherits all the behavior of the CATGeometry interface. Therefore, the factory of the CGM objects (CATGeoFactory) handles the creation, stream, unstream and remove of the CGM surfaces. The geometric transformation and/or duplication of CGM surfaces is managed by specific processes through CATTransfoManager and CATCloneManager instances [3]. For more details about the CGM objects general properties, see [1].
    1. CGM surfaces **must be C2 continuous**. Hence, the surfaces are many infinitely differentiable with respect to the (U,V) parameters on each patch, and only twice continuously differentiable between two patches. CGM directly generates objects satisfying this criterion. If you want to introduce foreign surfaces, you have to insure that they satisfy it. If they do not satisfy it, you can cut them where they are not C2 continuous, and use topological objects to assemble the parts.  Fig. 2: Validity criteria for surfaces   
 In addition, the surfaces must not be self intersecting, except if they are closed (as for a cylinder for example). On the other hand, they can be degenerated, but only on one or two boundaries that are not adjacent.  

1. CGM surfaces **must be C2 continuous**. Hence, the surfaces are many infinitely differentiable with respect to the (U,V) parameters on each patch, and only twice continuously differentiable between two patches. CGM directly generates objects satisfying this criterion. If you want to introduce foreign surfaces, you have to insure that they satisfy it. If they do not satisfy it, you can cut them where they are not C2 continuous, and use topological objects to assemble the parts.  Fig. 2: Validity criteria for surfaces
In addition, the surfaces must not be self intersecting, except if they are closed (as for a cylinder for example). On the other hand, they can be degenerated, but only on one or two boundaries that are not adjacent.
    2. In each direction, (U and V), the curvilinear length must be greater than the resolution of the factory. The resolution defines the minimum length of a valid object, see [1].
    3. The normal to the surface must not be null (except possibly at a point on the surface boundary). This applies to degenerate isoparametric curves.
    4. The normal can only be null on a degenerate boundary (of a sliver face for example).
    5. The surface curvature radius must be greater than the resolution.
    6. Each patch must have a 3D length greater than the resolution  along U and V.
    7. The parameterization must be close to the curvilinear abscissa  (the norm of the partial derivatives must be around 1 and always in the 0.1-10 range).

Specific objects

    1. Nurbs Surfaces: control points should be in the geometric infinite 
    2. Nurbs Surfaces: control points should be distant from more than the resolution
    3. Nurbs Surfaces: degree must be less than 15

[Top]
#### Class for Handling Surface Parameters

The surface parameters only have sense if they are associated with the surface they parameterize. These parameters are handled through the CATSurParam instances, which are transient objects containing the parameters in each directions and a reference to the surface. In peculiar, they transform global parameters into local parameters and patches, and vice versa. The CATSurParamReference transient instance can not directly be created; the surface is responsible for retrieving a CATSurParam instance under your request.

[Top]
#### Limits and Bounding Box of a Surface

The surface parameters only have sense if they are associated with the surface they parameterize. These parameters are handled through the CATSurParam instances, which are transient objects containing the parameters in each directions and a reference to the surface. In peculiar, they transform global parameters into local parameters and patches, and vice versa. The CATSurParamReference transient instance can not directly be created; the surface is responsible for retrieving a CATSurParam instance under your request.
A surface has a maximal limit, outside which it is not defined, or cannot be extrapolated. This limit is expressed in terms of a CATSurLimits transient instance, containing two CATSurParam instances.

Geometric operators can be run on a part of the whole surface, therefore defining a current limit. This current limit is also handled by the CATSurLimit class.

Each surface is able to retrieve the definition of a space that surrounds it: the bounding box. This information is very useful, especially if you want to have a first diagnostic of intersection for example.  
The bounding box contains two points, and can be a CATMathBox instance, if expressed with Cartesian coordinates, or a a CATSurParam instance, if expressed with parameters.

[Top]
#### Evaluation

The main behavior of a surface, for a point lying on this surface, is to evaluate the Cartesian coordinates from its parameters and, conversely, the parameters from Cartesian coordinates: 
    * From parameters to Cartesian coordinates. This is called evaluation, and can be done to obtain the Cartesian coordinates of the point, or the vector of the surface derivatives at a given point. Multiple evaluation can be used to save CPU by the means of a CATSurEvalCommand instance.
    * From Cartesian coordinates to parameters. The CATSurface::GetParam method computes (if possible) the surface parameters of a given Cartesian point, and details if the point really is on the surface or not, and if there are several solutions.

The surface is responsible for the mapping between the (X, Y, Z) Cartesian coordinates and the (U, V) parameters, so that no assumptions must be maid about this mapping, except for a few objects that have published their own parameterization.

[Top]
#### Equations

The surface is responsible for the mapping between the (X, Y, Z) Cartesian coordinates and the (U, V) parameters, so that no assumptions must be maid about this mapping, except for a few objects that have published their own parameterization.
It is useful to retrieve the equations representing the surface, especially when you want to operate the geometry. You can retrieve these equations as CATMathFunctionXY instances, that are transient and created under request.

All surface modification changes the equations. Thus, it is necessary to precisely define the use of the geometry equations. There are 3 main methods for using equations. 

    * `CATSurface::Lock()`: _Locks the geometric object before asking for its equation._ This operation:
      * Declares a reference on the object, so that it cannot be deleted anymore.
      * Increments the number of customers that wants to prevent the object from future modifications, except the relimitation.
      * Does not compute anything.
    * `CATSurface::GetEquation()`: _Asks for the equation._ This operation:
      * Throws an exception if the object is not locked.
      * Allocate the memory (if needed).
      * Computes the equations (if needed).
      * Returns a constant pointer to the required equation.
    * `CATSurface::Unlock()`: _Unlocks the geometric object when you do not need to use its equation no more_. This operation:
      * Releases the reference
      * Decrements the number of customers which want to prevent the object from future modifications, except the relimitation.
      * Keeps the allocated memory and computed equations as long as the object is not modified.

In case of a modification of a surface, 
    * If there remains at least one lock on the surface, an error is thrown
    * Otherwise, the memory is freed.

[Top]
### Various Types of Surfaces

You find four major surface types in the CGM offering: the resolved surfaces, the sampled surfaces, the multi-represented surfaces and the procedural surfaces.You can also introduce your own class of surface, and use it as any CGM surface in all the CGM operators or as the underlying geometry of a topological object. For a detailed description of this mechanism, see [2].

[Top]
#### Resolved Surfaces

You find four major surface types in the CGM offering: the resolved surfaces, the sampled surfaces, the multi-represented surfaces and the procedural surfaces.You can also introduce your own class of surface, and use it as any CGM surface in all the CGM operators or as the underlying geometry of a topological object. For a detailed description of this mechanism, see [2].
These surfaces are only available on a mathematical form: NURBS, canonical surface (plane, cone, sphere, cylinder, torus) belongs to this type. Evaluations are made directly from the mathematical equations. The following array describes, for each resolved surface, its definition parameters, and the validity range of the definition parameters which come in addition to general validity criteria that have already been described.

CATCylinder | obtained by parallel displacement of a circle, or a part of a circle, along an axis.  
The definition parameters are:  

| CATMathAxis | `Axis` | The axis whose third direction is the cylinder axis  
---|---|---  
CATCylinder | obtained by parallel displacement of a circle, or a part of a circle, along an axis.
The definition parameters are:
double | `Radius` | The cylinder radius  
CATAngle | `StartAngle` | The low limit counted from the first direction of the cylinder axis. Positive angles according to the right-hand rule.  
CATAngle | `EndAngle` | The high limit counted from the first direction of the cylinder axis. Positive angles according to the right-hand rule.  
double | `StartLength` | The low limit in the third direction of the cylinder axis.  
double | `EndLength` | The high limit in the third direction of the cylinder axis.  

Validity range of the definition parameters: 

    * 0 <= StartAngle <= 2*Pi, StartAngle <=EndAngle <= StartAngle +2*Pi
    * StartLength < EndLength  
double | `EndLength` | The high limit in the third direction of the cylinder axis.
Validity range of the definition parameters:
CATCone | The definition parameters are:  

| CATMathAxis | `Axis` | The axis, whose third direction is the cone direction  
---|---|---  
CATCone | The definition parameters are:
double | `StartRadius` | The circle radius on the plane defined by the first and second directions of the cone axis.   
CATAngle | `ConeAngle` | The external cone angle. The angle is counted from the plane defined from the first and second directions of the axis.  
CATAngle | `StartAngle` | The low limit of the circle arc, measured from the axis first direction. Positive angles follow the right-hand rule.  
CATAngle | `EndAngle` | The high limit of the circle arc, measured from the axis first direction. Positive angles follow the right-hand rule.  
double | `StartRuleLength` | The start limit of the cone length. This start limit is a slant height (the length is not counted along the third direction of the cone axis but along the cone surface).  
double | `EndRuleLength` | The end limit of the cone length. This end limit is a slant height (the length is not counted along the third direction of the cone axis but along the cone surface).  

Validity range of the definition parameters:: 

    * 0 < ConeAngle < Pi/2
    * 0 <= StartAngle <= 2*Pi, StartAngle <=EndAngle <= StartAngle +2*Pi
    * StartRuleLength < EndRuleLength . They may be negative, if they do not exceed the Z abscissa of the cone apex.  
CATTorus | The full torus is defined by an axis and two radii. The major ring sweeps a full circle in the plane defined by the first and second directions of the axis. The major ring is centered at the origin of the axis. The minor ring sweeps a full circle of radius MinorRadius, centered at some point on the major ring and lying in the plane containing this center point, the origin O, and the vector defined by the axis third direction. A piece of the full torus is given by limiting the angles through which the major ring sweeps and those through which every minor ring sweeps. The definition parameters are:  
| CATMathAxis | `Axis` | The torus axis, whose third direction is the torus direction.  
---|---|---  
CATTorus | The full torus is defined by an axis and two radii. The major ring sweeps a full circle in the plane defined by the first and second directions of the axis. The major ring is centered at the origin of the axis. The minor ring sweeps a full circle of radius MinorRadius, centered at some point on the major ring and lying in the plane containing this center point, the origin O, and the vector defined by the axis third direction. A piece of the full torus is given by limiting the angles through which the major ring sweeps and those through which every minor ring sweeps. The definition parameters are:
double | `Major`Radius | The major ring radius on the plane defined by the first and second directions of the axis.  
double | `Minor`Radius | The minor ring radius.  
CATAngle | `MajorStartAngle` | The start limit of the major ring in radians, counted from the first direction of the torus axis. Positive angles are defined by the right-hand rule around the torus axis. The major start angle must be less than the major end angle.   
CATAngle | `MajorEndAngle` | The end limit of the major ring in radians, counted from the first direction of the torus axis. Positive angles are defined by the right-hand rule around the torus axis. The major end angle must be greater than the major start angle.  

CATAngle | `MinorStartAngle` | The first limit of the minor circle in radians. Positive angles are in the direction of the torus axis. Angles are counted from the external minor radius in the plane defined by the first and second direction of the torus axis.  
CATAngle | `MinorEndAngle` | The end limit of the minor circle in radians. Positive angles are in the direction of the torus axis. Angles are counted from the external minor radius in the plane defined by the first and second direction of the torus axis.  

Validity range of the definition parameters: 

    * 0 <= MajorStartAngle <= 2*Pi  
CATAngle | `MinorStartAngle` | The first limit of the minor circle in radians. Positive angles are in the direction of the torus axis. Angles are counted from the external minor radius in the plane defined by the first and second direction of the torus axis.
CATAngle | `MinorEndAngle` | The end limit of the minor circle in radians. Positive angles are in the direction of the torus axis. Angles are counted from the external minor radius in the plane defined by the first and second direction of the torus axis.
Validity range of the definition parameters:
MajorStartAngle <=MajorEndAngle <=MajorStartAngle +2*Pi  
CATSphere | The definition parameters are:  

| CATMathAxis | `Axis` | The axis whose center is the sphere center  
---|---|---  
MajorStartAngle <=MajorEndAngle <=MajorStartAngle +2*Pi
CATSphere | The definition parameters are:
double | `Radius` | The sphere radius  
CATAngle | `MeridianStart` | The low limit of the meridians existence.  
CATAngle | `MeridianEnd` | The high limit of the meridians existence.  
CATLength | `ParallelStart` | The low limit of the parallels existence  
CATLength | `ParallelEnd` | The high limit of the parallels existence  

The meridian planes are passing through the axis third direction, the parallel planes are orthogonal to the axis third direction. Validity range of the definition parameters: 

    * -Pi/2 <= ParallelStart <=Pi/2, ParallelStart < ParallelEnd<= Pi/2+ParallelStart
    * 0 <= MeridianStart <=2*Pi, MeridianStart < MeridianEnd<= 2*Pi+ MeridianStart  
CATLength | `ParallelEnd` | The high limit of the parallels existence
The meridian planes are passing through the axis third direction, the parallel planes are orthogonal to the axis third direction. Validity range of the definition parameters:
CATPlane | The definition parameters are:  

| CATMathPoint | `Origin` | The plane origin  
---|---|---  
CATPlane | The definition parameters are:
CATMathDirection | `FirstDirection` | The first normalized direction  
CATMathDirection | `secondDirection` | The second normalized direction, orthogonal to the first one  
CATSurLimits | `Limits` | The limits if needed  
CATNurbsSurface | NURBS definition of a curve, see [4]  

[Top]
#### Sampled Surfaces

CATNurbsSurface | NURBS definition of a curve, see [4]
These surfaces result from a computation that does not lead to a canonical form. For example, a fillet with variable radius cannot be expressed in terms of a cylinder or another canonical surface. Moreover, the limiting curves in this case are defined by a Spline interpolation between marching points, obtained by a progressive algorithm. It is the reason why this type of surface is called sampled surface. For example, the CATGenericFilletSurface interface manages the behavior of a fillet surface that is not canonical, while the CATGenericRuledSurface interface manages the behavior of a draft surface that is not canonical.

CATGenericFillet | Surface generated by the smallest circle arcs of `CenterPoints` centers and passing through `Limit1` and `Limit2` sets of points. The definition parameters are:  

| CATMathSetOfPointsND | `CenterPoints` | The center of the circles  
---|---|---  
These surfaces result from a computation that does not lead to a canonical form. For example, a fillet with variable radius cannot be expressed in terms of a cylinder or another canonical surface. Moreover, the limiting curves in this case are defined by a Spline interpolation between marching points, obtained by a progressive algorithm. It is the reason why this type of surface is called sampled surface. For example, the CATGenericFilletSurface interface manages the behavior of a fillet surface that is not canonical, while the CATGenericRuledSurface interface manages the behavior of a draft surface that is not canonical.
CATGenericFillet | Surface generated by the smallest circle arcs of `CenterPoints` centers and passing through `Limit1` and `Limit2` sets of points. The definition parameters are:
CATMathSetOfPointsND | `Limit1` | Corresponding passing points on the first limitation curve  
CATMathSetOfPointsND | `Limit2` | Corresponding passing points on the second limitation curve  
CATGenericRuledSurface | Surface generated by lines passing through and delimited by `Limit1` and `Limit2` sets of points. The definition parameters are:  

| CATMathSetOfPointsND | `Limit1` | Corresponding passing points on the first limitation curve  
---|---|---  
CATMathSetOfPointsND | `Limit1` | Corresponding passing points on the first limitation curve
CATMathSetOfPointsND | `Limit2` | Corresponding passing points on the second limitation curve
CATGenericRuledSurface | Surface generated by lines passing through and delimited by `Limit1` and `Limit2` sets of points. The definition parameters are:
CATMathSetOfPointsND | `Limit2` | Corresponding passing points on the second limitation curve  

[Top]
#### Multi-represented Surfaces

CATMathSetOfPointsND | `Limit2` | Corresponding passing points on the second limitation curve
The multi-represented surface simply delegates, without computation, its evaluation to a pointed surface.This model allows CGM to keep as long as possible the object canonicity: for example, an object implementing the CATFilletSurface interface point to an objet implementing a canonical surface (such as CATCylinder, CATCone) or to an object implementing the CATGenericFillet if the resulting fillet is not canonical. The canonical representation, if it exists, is returned by the `CATSurface::GetGeometricRep` method.

Fig. 3: The multi-represented surfaces ![Surfaces2.gif \(5852 bytes\)](images/CAACgmGobSurfaces2.gif) | CATFilletSurface, CATDraftSurface, CATSweepSurface, CATOffsetSurface are interfaces for various multi-represented surfaces. Each of these surface refers to another one for the evaluation process. The referred surface is preferably a canonical surface. If it is not possible, sampled or procedural surfaces are chosen.  

The multi-represented surface simply delegates, without computation, its evaluation to a pointed surface.This model allows CGM to keep as long as possible the object canonicity: for example, an object implementing the CATFilletSurface interface point to an objet implementing a canonical surface (such as CATCylinder, CATCone) or to an object implementing the CATGenericFillet if the resulting fillet is not canonical. The canonical representation, if it exists, is returned by the `CATSurface::GetGeometricRep` method.
Fig. 3: The multi-represented surfaces ![Surfaces2.gif \(5852 bytes\)](images/CAACgmGobSurfaces2.gif) | CATFilletSurface, CATDraftSurface, CATSweepSurface, CATOffsetSurface are interfaces for various multi-represented surfaces. Each of these surface refers to another one for the evaluation process. The referred surface is preferably a canonical surface. If it is not possible, sampled or procedural surfaces are chosen.
Multi-represented surfaces are often created with geometric operators that are dedicated to this creation. The following array displays the geometric operator or the method of the CATGeoFactory to use for the creation of each type of multi-represented surface:

Surface | Creation | Definition parameters  

Multi-represented surfaces are often created with geometric operators that are dedicated to this creation. The following array displays the geometric operator or the method of the CATGeoFactory to use for the creation of each type of multi-represented surface:
Surface | Creation | Definition parameters
CATFilletSurface | CATConnect  
operator | Connection of two or three surfaces.  

| CATSurface | `Surface1` | The first surface to connect  
---|---|---  
CATFilletSurface | CATConnect
operator | Connection of two or three surfaces.
long | `Orientation1` | The `Surface1 `orientation to take into account  
CATSurface | `Surface2` | The second surface to connect  
long | `Orientation2` | The `Surface2 `orientation to take into account  
CATSurface | `Surface3` | The third surface to connect (optional)  
long | `Orientation3` | The `Surface3 `orientation to take into account (optional)  
CATConnectTool | `RadiusLaw` | The definition of the radius law: constant: CATConstantFilletTool or variable: CATVariableFilletTool  
CATChamfer | CATConnect  
operator | Defines a surface such that the surface normal has a constant angle with a given direction (called draft direction)  

| CATSurface | `Surface1` | The first surface to connect  
---|---|---  
CATConnectTool | `RadiusLaw` | The definition of the radius law: constant: CATConstantFilletTool or variable: CATVariableFilletTool
CATChamfer | CATConnect
operator | Defines a surface such that the surface normal has a constant angle with a given direction (called draft direction)
long | `Orientation1` | The `Surface1 `orientation to take into account  
CATSurface | `Surface2` | The second surface to connect  
long | `Orientation2` | The `Surface2 `orientation to take into account  
CATChamferTool | `ChamferDef` | The chamfer is defined:  
either with a distance on each surface,  
or with a distance and an angle  
CATDraftSurface | CATGeoFactory::  
CreateDraftSurface |    
CATOffsetSurface | CATGeoFactory::  
CreateOffsetSurface |    
CATSweepSurface | CATExtruder  
operator |    

[Top]
#### Procedural Surfaces

operator |
The procedural surface uses the evaluation of another surface, call the reference, for the computation of its own evaluation. The reference can be any type of surface, even a procedural one. But in this last case, this will be more time consuming: two evaluations are done, one for each level. In case of a CATProcOffsetSurface referring another CATProcOffsetSurface however, the offset values are directly cumulated at the surface creation, so that only one evaluation is done.

Fig. 4: The evaluation mechanism and the special case of procedural offset surface ![Surfaces3.gif \(7309 bytes\)](images/CAACgmGobSurfaces3.gif) | When you ask for an evaluation of a procedural surface, the procedural surface uses the evaluation of its reference. This process is recursive if the reference is a procedural surface itself, so that it could be time consuming, because each procedural surface do computations at each level. This is not the case for a procedural offset surface of another procedural offset surface: here, the offset are cumulated, eliminating the recursivity.  

The procedural surface uses the evaluation of another surface, call the reference, for the computation of its own evaluation. The reference can be any type of surface, even a procedural one. But in this last case, this will be more time consuming: two evaluations are done, one for each level. In case of a CATProcOffsetSurface referring another CATProcOffsetSurface however, the offset values are directly cumulated at the surface creation, so that only one evaluation is done.
Fig. 4: The evaluation mechanism and the special case of procedural offset surface ![Surfaces3.gif \(7309 bytes\)](images/CAACgmGobSurfaces3.gif) | When you ask for an evaluation of a procedural surface, the procedural surface uses the evaluation of its reference. This process is recursive if the reference is a procedural surface itself, so that it could be time consuming, because each procedural surface do computations at each level. This is not the case for a procedural offset surface of another procedural offset surface: here, the offset are cumulated, eliminating the recursivity.
We detail now the various procedural surfaces.

CATProcOffsetSurface | Generated by offsetting each point of a reference surface in the direction of the reference surface normal and of length a given offset that may be positive or negative.  

| CATSurface | `Reference` | The surface to offset. Is any type of surface. In case of another CATProcOffsetSurface, the offsets are added and the reference surface becomes the reference surface of the CATProcOffsetSurface to offset.  
---|---|---  
We detail now the various procedural surfaces.
CATProcOffsetSurface | Generated by offsetting each point of a reference surface in the direction of the reference surface normal and of length a given offset that may be positive or negative.
CATLength | `Offset` | The value of the offset  
CATTabulatedCylinder | Generated by the translation of a generative curve.  

| CATCurve | `Profile` | The curve to translate  
---|---|---  
CATLength | `Offset` | The value of the offset
CATTabulatedCylinder | Generated by the translation of a generative curve.
CATMathDirection | `Dir` | The translation direction  
CATLength | `Start` | The low limit of the surface on the translation direction  
CATLength | `End` | The high limit of the surface on the translation direction  
CATRevolutionSurface | Generated by the revolution of a generative curve around a direction.  

| CATCurve | `Profile` | The curve to rotate  
---|---|---  
CATLength | `Start` | The low limit of the surface on the translation direction
CATLength | `End` | The high limit of the surface on the translation direction
CATRevolutionSurface | Generated by the revolution of a generative curve around a direction.
CATMathAxis | `Axis` | The axis whose third direction is the rotation direction  
CATAngle | `StartAngle` | The low limit of the rotation  
CATAngle | `EndAngle` | The end limit of the rotation  
CATLinearTransfoSurface | Generated by transforming each point of a reference surface with a given geometric linear transformation.  

| CATSurface | `Reference` | The surface to transform  
---|---|---  
CATAngle | `StartAngle` | The low limit of the rotation
CATAngle | `EndAngle` | The end limit of the rotation
CATLinearTransfoSurface | Generated by transforming each point of a reference surface with a given geometric linear transformation.
CATMathTransformation | `Transformation` | The applied transformation  
CATNonLinearTransfoSurface | Generated by transforming each point of a reference surface with a given non linear transformation.  

| CATSurface | `Reference` | The surface to transform  
---|---|---  
CATMathTransformation | `Transformation` | The applied transformation
CATNonLinearTransfoSurface | Generated by transforming each point of a reference surface with a given non linear transformation.
CATMathNonLinearTransformation | `Transformation` | The applied transformation  

[Top]

* * *
### In Short

    * CGM surfaces are C2 continuous. They offer you evaluators to evaluate point parameters and derivatives, and equations to use in geometric operations for example.
    * Four major types of surfaces are available: resolved surfaces, sampled surfaces, multi-represented surfaces and procedural surfaces. Foreign surfaces can also be introduced in CGM.

[Top]

* * *
### References

[1] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)  
---|---  
[2] | [The Management of Foreign Data](CAACgmTaGobAttribute.md)  
[3] | [The Cloning and Transformation Managers](CAACgmTaGobClone.md)  
[4] | [About NURBS](CAACgmTaGobAboutNurbs.md)  
[Top]  

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
