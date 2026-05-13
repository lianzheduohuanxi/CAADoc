---
title: "Overview of the Topological Operators"
category: "use-case case"
module: "CAATopUseCases"
tags: "["CAAGemBrowser", "CATICGMObject", "CAATopJournal", "CAATopSpline", "CAATopOverview", "CATIA", "CATIntersectionCrvCrv", "CAATopologicalOperators", "CATICGMContainer"]"
source_file: "Doc/online/CAATopUseCases/CAATopOverview.htm"
converted: "2026-05-11T17:31:50.750855"
---
# Geometric Modeler

|
## Topology

|
### Overview of the Topological Operators

_How to use them to create bodies_
---|---|---
Use Case

* * *
### Abstract

Build on a common scheme, the topological operators are transient objects used to create bodies. The use case illustrates their use in chaining them to create bodies: primitive creation (`CATSolidCylinder`, `CATSolidCuboid`), skin body creation (`CATTopSkin`), prism (`CATTopPrism`), Boolean operation (`CATDynBoolean`), filleting (`CATDynFillet`) and shelling (`CATDynShell`). The volume of the resulting body is also computed (`CATDynMassProperties3D`). The use of the journal, describing the topological modifications from the input bodies to the resulting body, is not described here. See the dedicated use case "Managing the Journal" [1] to have more information on this point.

  * **What You Will Learn With This Use Case**
  * **The General Scheme**
  * **The CAATopOverview Use Case**
    * What Does CAATopOverview Do
    * How to Launch CAATopOverview
    * Where to Find theCATopOverview Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

In this use case, the general scheme of the topological operators is explained.

Using topological operators is an easy way to create new consistent topological objects. There are two types of operators:

  * The operators building topology from geometry. They derive from the `CATGeoToTopOperator` class ( to create wire bodies or skin bodies) or from `CATSolidPrimitive` (to create basic primitives such as cylinder, box, sphere).
  * The operators only operating on topological objects. They derive from the `CATTopOperator` class. Some of them allows you to create simple bodies (point, line and spline bodies), see the `CAATopSpline` use case [9].

Using topological operators is an easy way to create new consistent topological objects. There are two types of operators:
All these operators follow the smart concept [3]: they never modify the input bodies. They always create new topological objects, which share topological cells to reduce the model size.

The operators can log, under request, the follow-up of the faces and free edges from the input bodies to the resulting body. This data is written, under request, on a topological journal [4] attached to each operator. Hence, the topological journal offers the developer the means to develop procedural applications, such as feature based modeling, but this point in not detailed here. See the dedicated use case [1] to have more information on the use of the journal.

The topological operators are transient objects used to define topological operations, and cannot be streamed.

The AdvancedTopologicalOpe framework provides advanced topological operators in surface design. They follow the general scheme of the topological operators, but are not described here.

[Top]
### The General Scheme

The AdvancedTopologicalOpe framework provides advanced topological operators in surface design. They follow the general scheme of the topological operators, but are not described here.
All the operators are based on the same scheme as follow that:

  1. Creates an operator

     * by calling a global method for the operators deriving from `CATTopOperator`
     * during this step, the operation is not run
All the operators are based on the same scheme as follow that:
1. Creates an operator
  2. If needed, specifies or modifies additional information such as the definition of a ribbon of a draft or a fillet, the type of trim

     * during this step, the operation is not run
1. Creates an operator
2. If needed, specifies or modifies additional information such as the definition of a ribbon of a draft or a fillet, the type of trim
  3. Runs the operator: `Run`

     * the operation is run
2. If needed, specifies or modifies additional information such as the definition of a ribbon of a draft or a fillet, the type of trim
3. Runs the operator: `Run`
  4. Gets the result: `GetResult`

     * the topological result is always retrieved as a `CATBody`
3. Runs the operator: `Run`
4. Gets the result: `GetResult`
  5. Deletes the operator instance.

Unlike the geometric operators, the topological operators do not provide a BASIC and an ADVANCED modes. The topological operators are always set in ADVANCED mode: the run is always mandatory.

[Top]
### The CAATopOverview Use Case

CAATopOverview is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopOverview Do

CAATopOverview is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.
The use case creates the body of Fig.1 by chaining topological operators.

Fig. 1: The Resulting Body ![](images/CAATopOverview1.gif)

  * A skin is created from a profile and extruded to produce a prism
  * A box primitive is added and a cylinder subtracted
  * The edges of the external loop of the upper face of the prism are filleted. This face is characterized by two holes: one for the path of the cylinder, on for the path of the box
  * A shelling operation is applied with one opening face, the bottom face of the prism.

[Top]
#### How to Launch CAATopOverview

To launch CAATopOverview, you will need to set up the build time environment, then compile CAATopOverview.m along with its prerequisites, set up the run time environment, and then execute the use case [8].

```vbscript
If you simply type CAATopOverview with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

```

With Windows `CAATopOverview e/Overview.NCGM`

With UNIX `CAATopOverview /u/Overview.NCGM`

This NCGM file can be displayed using the CAAGemBrowser use case.

[Top]
#### Where to Find the CAATopOverview Code

The CAATopOverview use case is made of a main named CAATopOverview.cpp located in the CAATopOverview.m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopOverview.m/`

The CAATopOverview use case is made of a main named CAATopOverview.cpp located in the CAATopOverview.m module of the CAATopologicalOperators.edu framework:
Windows | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopOverview.m/`
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopOverview.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
The main program:

  1. Creates the Geometry Factory
  2. Creates a Skin Body (CATTopSkin)
  3. Creates a Prism (CATTopPrism)
  4. Creates a Box Primitive (CATDynSolidCuboid) and a Cylinder Primitive (CATDynSolidCylinder)
  5. Adds and Subtracts (CATDynBoolean)
  6. Fillets (CATDynFillet)
  7. Shells (CATDynShell)
  8. Computes the Volume (CATDynMassProperties3D)
  9. Writes the Model and Closes the Container

[Top]
#### Creating the Geometry Factory

9. Writes the Model and Closes the Container
The geometry factory (CATGeoFactory) creates and manages all the `CATICGMObject` : it creates the points, curves, surfaces and bodies and remove them [7].

The CATGeoFactory creation itself is done by the global function `::CATCreateCGMContainer`.

Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#) ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

---

[Top]
#### Creating a Skin Body

This section illustrates the use of the type of topological operators that derive from `CATGeoToTopOperator`. There are two ways to create a skin body:

  * Define it on the boundary of a surface
  * Define it with a list of ordered curves defining the boundary of the face on the surface. This second way is illustrated here. Hence the following steps are needed:
    * Creating the surface, here the xy plane
    * Creating the curves on the surface (`CATPLine` and `CATPCircle`)
    * Defining the orientation of each curve: in fact, the `CreatePCircle` method always creates circles in the direct sense, even if the limits are given clockwise while `CATTpoSkin` requires to have curves such that the end of one curve (after orientation) is the end of the next curve
    * Using `CATTopSkin`.

  1. _Creating the Surface_

         CATPlane * piPlane = piGeomFactory->CreatePlane(**CATMathOIJ**);  _// xy plane_
```vbscript
             if (NULL == piPlane)

```

             {
               ::CATCloseCGMContainer(piGeomFactory);
CATPlane * piPlane = piGeomFactory->CreatePlane(**CATMathOIJ**);  _// xy plane_
if (NULL == piPlane)
```vbscript
               return (1);

```

             }

---
return (1);
  2. _Creating the Curves On the Surface_

Now, using the characteristics of the plane (`CATPlane::GetAxis`), the `CATPLine` and `CATPCircle` of the contour are created.

Fig. 2: The Skin Body ![](images/CAATopOverview2.gif)

---

Now, using the characteristics of the plane (`CATPlane::GetAxis`), the `CATPLine` and `CATPCircle` of the contour are created.
Fig. 2: The Skin Body ![](images/CAATopOverview2.gif)
The lines and circles are created with the corresponding `CATGeoFactory::CreatePLine` and `CATGeoFactory::CreatePCircle` methods. As these lines and circles are defining on the surface, they can only be created from surface parameters. However, no assumption can be done on the parameterization of the geometric objects. The parameters on the plane are evaluated with the `CATSurface::GetParam` method, from 3D points that are known to be on the plane. This method can be called because the plane is a canonical object, and the points are already on it. If one of these conditions were not filled, it would be mandatory to call the `CATProjectionPtSur` geometric operator.

         _// ----------- Retrieves the mathematical definition of the geometrical plane_
         CATMathPoint mathOrigin;
         CATMathDirection mathU, mathV;
         piPlane->**GetAxis**(mathOrigin,mathU,mathV);

         _// -----------Defines points on the plane

         // Notice that we do not make any assumption on the plane parameterization.
         // The use of GetParam is allowed here, because the 3D points belong to the plane
         // by construction_
_// -----------Defines points on the plane
         CATSurParam p1, p2, p3, p4, c1, c2;
         piPlane->**GetParam**(mathOrigin, p1);
         piPlane->**GetParam**(mathOrigin - 20*mathU                      , p2);
         piPlane->**GetParam**(mathOrigin - 10*mathU +    10*sqrt(3)  *mathV, p3);
         piPlane->**GetParam**(mathOrigin            +    10*sqrt(3)  *mathV, p4);
         piPlane->**GetParam**(mathOrigin - 20*mathU +    10          *mathV, c1);
         piPlane->**GetParam**(mathOrigin - 10*mathU + (10+10*sqrt(3))*mathV, c2);

         _// -----------Defines the curves of the profile_
         const int nbPCurves = 5;
         CATPCurve *  aPCurves[nbPCurves];
         CATCrvLimits aLimits[nbPCurves];

         aPCurves[0]=  piGeomFactory->**CreatePLine**   (p1, p2, piPlane );
         aPCurves[0] ->GetLimits(aLimits[0]);
         aPCurves[1]=  piGeomFactory->**CreatePCircle** (10,        _// radius_
                                                     c1,        _// center_
                                                     CATPI/3,   _// first limit  (may be reordered)_
                                                     3*CATPI/2, _// second limit (may be reordered)_
                                                     piPlane);  _// surface_
         aPCurves[1] ->GetLimits(aLimits[1]);
         aPCurves[2]=  piGeomFactory->CreatePCircle (10, c2, 4*CATPI/3, 3*CATPI/2, piPlane);
         aPCurves[2] ->GetLimits(aLimits[2]);

         aPCurves[3]=  piGeomFactory->CreatePLine   (p3, p4, piPlane );
         aPCurves[3] ->GetLimits(aLimits[3]);

         aPCurves[4]=  piGeomFactory->CreatePLine   (p4, p1, piPlane );
         aPCurves[4] ->GetLimits(aLimits[4]);
```vbscript
         for (int i=0; i<nbPCurves; i++)

```

         {
aPCurves[4]=  piGeomFactory->CreatePLine   (p4, p1, piPlane );
aPCurves[4] ->GetLimits(aLimits[4]);
for (int i=0; i<nbPCurves; i++)
```vbscript
```vbscript
           if (NULL==aPCurves[i])

```

```

           {
             ::CATCloseCGMContainer(piGeomFactory);
```vbscript
for (int i=0; i<nbPCurves; i++)
```vbscript
if (NULL==aPCurves[i])
             return (1);
```

```

           }
         }

---
  3. _Defining the Orientations Of the Curves In the Profile_

`CATTopSkin` needs
     * An ordered list of curves: contiguous curves must be contiguous in the list. The limits to take into account for each curve must be detailed. In this use case, the intersection between the lines and circles are easily computed, but if it were not the case, they would be computed with the `CATIntersectionCrvCrv` geometric operator.
     * The orientation of each curve in the profile: the curve must be taken in its natural orientation (increasing parameter, +1 value) or in the opposite orientation (decreasing parameter, -1 value), so that the end (after orientation) of a curve must be linked to the beginning (after orientation) of the next curve. The computation of the orientations gives the opportunity to show how to evaluate a parameter on a curve: this is done by the `CATCurve::Eval` method. Again, do never make any assumption on the parameterization of the geometric objects.

    _// Defines the orientations of the curves_
    short aOrientations[nbPCurves];
    aOrientations[0] = 1;
    aOrientations[1] = 1;
    aOrientations[2] = 1;
    aOrientations[3] = 1;
    aOrientations[4] = 1;

    CATCrvParam low,high;
    CATMathPoint m1start, m1end, aPoints[2];

    _//first checks the first two curves_
    aLimits[0].GetExtremities(low,high);
    aPCurves[0]->**Eval**(low , CATCrvEvalCommand::EvalPoint, &m1start);
    aPCurves[0]->Eval(high, CATCrvEvalCommand::EvalPoint, &m1end);

    aLimits[1].GetExtremities(low,high);
    aPCurves[1]->Eval(low , CATCrvEvalCommand::EvalPoint, &(aPoints[0]));
    aPCurves[1]->Eval(high, CATCrvEvalCommand::EvalPoint, &(aPoints[1]));

    int index1, index2;
    double d1 = m1start.**DistanceTo**(aPoints, _// array of 2 points_
                                   2,       _// count of points of aPoints_
                                   index1); _// index (beginning at 0) of a point of aPoints_
                                            _// closest to this_
    double d2 =   m1end.DistanceTo(aPoints,2,index2);

```vbscript
    if (d1 < d2 )     _// the orientation of the first curve is inverted_

```

    {
_// closest to this_
double d2 =   m1end.DistanceTo(aPoints,2,index2);
if (d1 < d2 )     _// the orientation of the first curve is inverted_
      aOrientations[0] = -1;
```vbscript
      if (1==index1) aOrientations[1] = -1; _// inverts the orientation of the second curve_

```

    }
```vbscript
if (d1 < d2 )     _// the orientation of the first curve is inverted_
aOrientations[0] = -1;
if (1==index1) aOrientations[1] = -1; _// inverts the orientation of the second curve_
    else
```

    {
aOrientations[0] = -1;
if (1==index1) aOrientations[1] = -1; _// inverts the orientation of the second curve_
else
```vbscript
      if (1==index2) aOrientations[1]= -1;  _// inverts the orientation of the second curve_

```

    }

else
if (1==index2) aOrientations[1]= -1;  _// inverts the orientation of the second curve_
    _// Checks now the other curves_
```vbscript
    for (i=2;i<5;i++)

```

    {
_// Checks now the other curves_
for (i=2;i<5;i++)
      m1end   = aPoints [1];
```vbscript
      if (-1==aOrientations[i-1]) m1end   = aPoints [0];

```

      aLimits[i].GetExtremities(low,high);
      aPCurves[i]->Eval(low , CATCrvEvalCommand::EvalPoint, &(aPoints[0]));
      aPCurves[i]->Eval(high, CATCrvEvalCommand::EvalPoint, &(aPoints[1]));

      d2 =   m1end.DistanceTo(aPoints,2,index2);
```vbscript
```vbscript
      if (1==index2) aOrientations[i]= -1;

```

```

    }

---

The principle of the algorithm is
     * To compare the limits of the first two curves to know their orientation. This also gives the geometric location of the end of the second curve
     * For each next curve
       * To compare its limits with the end of the preceeding curve, in order to get its orientation.

The principle of the algorithm is
The use of the `CATMathPoint::DistanceTo` method to compute the minimum distance between a point (`this` calling `DistanceTo` ) and an array of points: the method retrieves the index (beginning at 0) in the input array of the point realizing the minimum distance.

  4. _Using` CATTopSkin`_

The geometry being created, the `CATTopSkin` can now be invoked according to the general scheme that:

     * Creates with the global function `CATCreateTopSkin`
     * Runs
     * Gets the resulting skin body. This body is created by `CATTopSkin` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
     * Deletes.

    _// Creates the operator_
    _//_ _first defines an open configuration for the operator_
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(#);
    _// defines the data of the operator: configuration + journal_
    CATTopData topdata(pConfig,NULL);
    _// now creates the operator_
    CATTopSkin * pSkinOp = **::CATCreateTopSkin** (piGeomFactory,

                                               &topdata,
_// defines the data of the operator: configuration + journal_
CATTopData topdata(pConfig,NULL);
_// now creates the operator_
CATTopSkin * pSkinOp = **::CATCreateTopSkin** (piGeomFactory,
                                               piPlane,
    		                           nbPCurves,
    					   aPCurves,
                                               aLimits,
                                               aOrientations);
```vbscript
    if (NULL==pSkinOp)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
aLimits,
aOrientations);
if (NULL==pSkinOp)
```vbscript
          return (1);

```

    }

return (1);
    _// Runs_
    pSkinOp->**Run**(#);

    _// Gets the resulting body_
    CATBody * piSkinBody = pSkinOp->**GetResult**(#);
```vbscript
    if (NULL==piSkinBody)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
_// Gets the resulting body_
CATBody * piSkinBody = pSkinOp->**GetResult**(#);
if (NULL==piSkinBody)
```vbscript
          return (1);

```

    }

return (1);
    _// Deletes the operator_

    **delete** pSkinOp;
return (1);
_// Deletes the operator_
    pSkinOp = NULL;

---

pSkinOp = NULL;
The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled.

The configuration must be released after use. Here, it is released after the call to the last operator.

[Top]
#### Creating a Prism

The created `SkinBody` is now extruded to create a prism with `CATTopPrism`. To use it:

  * Create it with the corresponding `::CATTopCreatePrism` global function, by declaring the body to extrude (`SkinBody`), the direction of the extrusion, the start and end limits of the prism from `SkinBody`
  * Run it
  * Get the resulting body (`MainBody1`). This body is created by `CATTopOperator` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
  * Delete it.

    CATMathDirection   zDir(0., 0., 1.);
    double startOffset = 10.;
    double endOffset   = 30.;
    CATTopPrism       *pPrismOp = **::CATTopCreatePrism** (piGeomFactory,

                                                       &topdata
CATMathDirection   zDir(0., 0., 1.);
double startOffset = 10.;
double endOffset   = 30.;
CATTopPrism       *pPrismOp = **::CATTopCreatePrism** (piGeomFactory,
                                                       piSkinBody,

                                                       &zDir,
double endOffset   = 30.;
CATTopPrism       *pPrismOp = **::CATTopCreatePrism** (piGeomFactory,
piSkinBody,
                                                       startOffset,
                                                       endOffset);

```vbscript
    if (NULL==pPrismOp)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
endOffset);
if (NULL==pPrismOp)
```vbscript
          return (1);

```

    }

    // Runs
    pPrismOp->**Run**(#);

    // Gets the resulting body
pPrismOp->**Run**(#);
    CATBody * piMainBody1=NULL;
    piMainBody1 = pPrismOp->**GetResult**(#);
```vbscript
```vbscript
    if (NULL==piMainBody1)

```

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
CATBody * piMainBody1=NULL;
piMainBody1 = pPrismOp->**GetResult**(#);
```vbscript
if (NULL==piMainBody1)
          return (1);

```

    }

    // Deletes the operator
    **delete** pPrismOp;
    pPrismOp = NULL;

---

As the body to extrude is a skin body, `MainBody1` is a volume body. If the body to extrude were a wire body, the result would be a skin body. Other types of prism operations can be defined, especially "until" operations: the limits of the prism are reached when encountering another body. This case is detailed in the `CAATopJournal` use case [1].

[Top]
#### Creating a Box and a Cylinder Primitives

As the body to extrude is a skin body, `MainBody1` is a volume body. If the body to extrude were a wire body, the result would be a skin body. Other types of prism operations can be defined, especially "until" operations: the limits of the prism are reached when encountering another body. This case is detailed in the `CAATopJournal` use case [1].
This section illustrates the use of `CATSolidPrimitive` operators: no run is called to do the operation, that is done at the operator creation.

To create a box, use `CATSolidCuboid`:

  * Create it with the global function `CATCreateSolidCuboid`. The points that are given are four corners of the box. The operation is automatically run.
  * Get the resulting body (`CuboidBody`). This body is created by `CATSolidCuboid` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
  * Delete it.

    CATMathPoint vO( -2., 2., 28.),  vOI(-2., 15., 28.),
                 vOJ(-15., 2., 28.),  vOK(-2., 2., 35.);

    CATSolidCuboid *pCuboidOp = **::CATCreateSolidCuboid**( piGeomFactory, &topdata, vO, vOI, vOJ, vOK);

```vbscript
    if (NULL==pCuboidOp)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
CATSolidCuboid *pCuboidOp = **::CATCreateSolidCuboid**( piGeomFactory, &topdata, vO, vOI, vOJ, vOK);
if (NULL==pCuboidOp)
```vbscript
          return (1);

```

    }

return (1);
    _// Gets the result (the operator is run at is creation)_
    CATBody *piCuboidBody=NULL;
    piCuboidBody = pCuboidOp->**GetResult**(#);
```vbscript
```vbscript
    if (NULL==piCuboidBody)

```

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
CATBody *piCuboidBody=NULL;
piCuboidBody = pCuboidOp->**GetResult**(#);
```vbscript
if (NULL==piCuboidBody)
          return (1);

```

    }

return (1);
    _// Deletes the operator_

    **delete** pCuboidOp;
return (1);
_// Deletes the operator_
    pCuboidOp = NULL;

---

To create a cylinder, use `CATSolidCylinder` :

  * Create it with the global function `CATCreateSolidCylinder`. The two points defines the axis of the cylinder. The operation is automatically run
  * Get the resulting body (`CylinderBody`). This body is created by `CATSolidCylinder` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
  * Delete it.

    CATMathPoint axisStart ( -20,  10,  20 ),  axisEnd( -20,  10, 32 );
    double       radius = 4.0;

    CATSolidCylinder *pCylinderOp = ::**CATCreateSolidCylinder**(piGeomFactory,

                                                             &topdata
CATMathPoint axisStart ( -20,  10,  20 ),  axisEnd( -20,  10, 32 );
double       radius = 4.0;
CATSolidCylinder *pCylinderOp = ::**CATCreateSolidCylinder**(piGeomFactory,
                                                             axisStart,
                                                             axisEnd,
                                                             radius);
```vbscript
    if (NULL==pCylinderOp)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
axisEnd,
radius);
if (NULL==pCylinderOp)
```vbscript
          return (1);

```

    }

return (1);
    _// Gets the resulting body (the operator is run at its creation)_
    CATBody *piCylinderBody = NULL;
    piCylinderBody = pCylinderOp->**GetResult**(#);
```vbscript
```vbscript
    if (NULL==piCylinderBody)

```

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
CATBody *piCylinderBody = NULL;
piCylinderBody = pCylinderOp->**GetResult**(#);
```vbscript
if (NULL==piCylinderBody)
          return (1);

```

    }

return (1);
    _// Deletes the operator_

    **delete** pCylinderOp;
return (1);
_// Deletes the operator_
    pCylinderOp = NULL;

---

See the `CAATopJournal` use case [1] to see how to create a skin body cylinder.

[Top]
#### Adding and Subtracting

To use CATDynBoolean:

  * Create it with the corresponding `::CATCreateDynBoolean` global function, by declaring the bodies to union (`MainBody1, CuboidBody`)
  * Run it
  * Get the resulting body (`MainBody2`). This body is created by `CATDynBoolean` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
  * Delete it.

This code also shows an example of use the `CATICGMContainer::Remove` method to suppress the no more used bodies: the `RemoveDependancies` option declares that not only the body, but also its domains, cells and geometry are removed, except if they were used by other CGM entities.

    CATDynBoolean* pBoolOp = **::CATCreateDynBoolean** (piGeomFactory,
                                                    &topdata,
                                                    **CATBoolUnion** ,
CATDynBoolean* pBoolOp = **::CATCreateDynBoolean** (piGeomFactory,
                                                    piMainBody1,
                                                    piCuboidBody);
```vbscript
    if (NULL==pBoolOp)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
piMainBody1,
piCuboidBody);
if (NULL==pBoolOp)
```vbscript
          return (1);

```

    }

return (1);
    _// Runs_
    pBoolOp->Run(#);

    _// Gets the resulting body_
    CATBody * piMainBody2 = NULL;
    piMainBody2 = pBoolOp->**GetResult**(#);
```vbscript
```vbscript
    if (NULL==piMainBody2)

```

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
CATBody * piMainBody2 = NULL;
piMainBody2 = pBoolOp->**GetResult**(#);
```vbscript
if (NULL==piMainBody2)
          return (1);

```

    }

return (1);
    _// Deletes the operator_

    **delete** pBoolOp;
return (1);
_// Deletes the operator_
    pBoolOp = NULL;

    _// Asks the factoryto proceed the deletion (CATBody)_
    piGeomFactory->**Remove**(piCuboidBody, **CATICGMContainer::RemoveDependancies**);
    piCuboidBody = NULL;
    piGeomFactory->Remove(piMainBody1, CATICGMContainer::RemoveDependancies);
    piMainBody1 = NULL;

---

piGeomFactory->Remove(piMainBody1, CATICGMContainer::RemoveDependancies);
piMainBody1 = NULL;
The same is done for a Boolean subtract: the option `CATBoolRemoval` is used. `MainBody3` contains the result of all the operations, while the no-more used bodies (`MainBody`2 , `CylinderBody`) are removed.

```cpp
    pBoolOp = **::CATCreateDynBoolean** (piGeomFactory,

```

                                     &topdata,
                                     **CATBoolRemoval** ,
pBoolOp = **::CATCreateDynBoolean** (piGeomFactory,
    			         piMainBody2,
    			         piCylinderBody);
```vbscript
    if (NULL==pBoolOp)

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
piMainBody2,
piCylinderBody);
if (NULL==pBoolOp)
```vbscript
          return (1);

```

    }

return (1);
    _// Runs_
    pBoolOp->**Run**(#);

    _// Gets the resulting body_
    CATBody * piMainBody3 = NULL;
    piMainBody3 = pBoolOp->**GetResult**(#);
```vbscript
```vbscript
    if (NULL==piMainBody3)

```

```

    {
          ::CATCloseCGMContainer(piGeomFactory);
CATBody * piMainBody3 = NULL;
piMainBody3 = pBoolOp->**GetResult**(#);
```vbscript
if (NULL==piMainBody3)
          return (1);

```

    }

return (1);
    _// Deletes the operator_

    **delete** pBoolOp;
return (1);
_// Deletes the operator_
    pBoolOp = NULL;

    piGeomFactory->**Remove**(piCylinderBody);
    piCylinderBody = NULL;
    piGeomFactory->Remove(piMainBody2);
    piMainBody2 = NULL;

---

[Top]
#### Filleting

First define the edges to fillet. These edges are the external boundary of the upper face of the prism after the two Boolean operations, in other words in our case, the face with 2 holes (the paths of the cylinder and the box). To retrieve them:

  * Get all the faces (the dimension of a face is 2, see [2]) of the body `MainBody3` with the` CATBody::GetAllCells` method
  * Select the face with two holes (i.e. three domains) (use of `CATCell::GetNbDomains`)
  * For each domain of the selected face, count the number of edges: the loop with five edges is the external one. One can also ask for the location of the domain to directly have the external domain. Get the edges.

```cpp
    CATLISTP(CATCell) listC;
```cpp
    CATLISTP(CATCell) listFaces;
```

    piMainBody3 ->**GetAllCells**(listFaces,  _// the output list of cells_
```

                              **2** );        _// the dimension of the retrieved cells (2 for faces)_
```cpp
CATLISTP(CATCell) listC;
```cpp
CATLISTP(CATCell) listFaces;
```

piMainBody3 ->**GetAllCells**(listFaces,  _// the output list of cells_
    int nbFaces=listFaces.Size(#);
    CATCell * piFace = NULL;

    _// ----------Recovers the only face with 2 internal loops_
    for ( i=1;i<=nbFaces;i++)
```

    {
CATCell * piFace = NULL;
_// ----------Recovers the only face with 2 internal loops_
for ( i=1;i<=nbFaces;i++)
```vbscript
```vbscript
    	if ( 3== (listFaces[i]->**GetNbDomains**(#)) ) piFace = listFaces[i];

```

```

    }

```vbscript
for ( i=1;i<=nbFaces;i++)
```vbscript
if ( 3== (listFaces[i]->**GetNbDomains**(#)) ) piFace = listFaces[i];
```

    _// ---------- and the loop with 5 edges_
    CATDomain * piLoop = NULL;
    CATLISTP(CATEdge) listEdges;
    int numberOfEdges;

    if (NULL != piFace)
```

    {
```cpp
CATLISTP(CATEdge) listEdges;
int numberOfEdges;
if (NULL != piFace)
```vbscript
       for (i=1;i<=3;i++)
```

```

       {
```vbscript
if (NULL != piFace)
```vbscript
```vbscript
for (i=1;i<=3;i++)
    	piLoop = piFace->**GetDomain**(i);
```

```

            piLoop->**GetAllCells**(listC, 1);
    	numberOfEdges = listC.Size(#);
```vbscript
    	if (5==listC.Size(#))
```

```

    	{
piLoop = piFace->**GetDomain**(i);
piLoop->**GetAllCells**(listC, 1);
numberOfEdges = listC.Size(#);
```vbscript
```vbscript
if (5==listC.Size(#))
              for (int j=1;j<=numberOfEdges;j++)

```

```

    		{listEdges.**Append**((CATEdge *)listC[j]);}
    	}
       }
    }
    else _// problem in the definition of the body_
    {
          ::CATCloseCGMContainer(piGeomFactory);
       return (2);
    }

---

A filleting operation is defined by affecting (possibly variable) radius to edges:

  * The definition of the radius law is contained in the `CATDynFilletRadius` object: in the use case, the radius is chosen constant along the edges
  * The definition of the edges to fillet according to a given radius law is called ribbon and managed by the `CATDynFilletRibbon` object: there can be several ribbons in one fillet operation, but in the use case, only one is defined.
The `CATDynFilletRibbon::SetSegmentationMode` option indicates that the computed ribbon must be delimited on the main part.

    _// for a constant radius, only the first argument is useful_
    CATDynFilletRadius * pRadius = new

                           **CATDynFilletRadius**(1.,    _// radius value_
_// for a constant radius, only the first argument is useful_
CATDynFilletRadius * pRadius = new
                           NULL,  _// the cell on which the radius is defined_
                           NULL,  _// The ratio of the edge length defining the point_
                           NULL); _// must be kept to NULL_
```vbscript
    if (NULL==pRadius)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
NULL,  _// The ratio of the edge length defining the point_
NULL); _// must be kept to NULL_
if (NULL==pRadius)
```vbscript
      return (1);

```

    }

return (1);
```cpp
    CATLISTP(CATDynFilletRadius)	listRadius;
```

    listRadius.Append(pRadius);

    _// ribbon definition_
    CATDynEdgeFilletRibbon * pRibbon = new **CATDynEdgeFilletRibbon**(listEdges, listRadius);
```vbscript
    if (NULL==pRibbon)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
_// ribbon definition_
CATDynEdgeFilletRibbon * pRibbon = new **CATDynEdgeFilletRibbon**(listEdges, listRadius);
if (NULL==pRibbon)
```vbscript
      return (1);

```

    }

    pRibbon ->SetSegmentationMode(CATDynTrim);

---

The fillet operation can now be defined and run. To use it

  * Create it (with the corresponding `::CATCreateDynFillet` global function) by declaring the body to fillet (`MainBody3, CuboidBody`)
  * Append the ribbon
  * Run it
  * Get the resulting body (`MainBody4`). This body is created by `CATDynFillet` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
  * Delete it.

Also deletes the no more used object (radius, ribbon) and removes the old body (`MainBody3`).

    CATDynFillet * pFilletOp = **CATCreateDynFillet**(piGeomFactory,&topdata,piMainBody3);
```vbscript
    if (NULL==pFilletOp)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
CATDynFillet * pFilletOp = **CATCreateDynFillet**(piGeomFactory,&topdata,piMainBody3);
if (NULL==pFilletOp)
```vbscript
      return (1);

```

    }

    // Appends the ribbon
    pFilletOp ->**Append**(pRibbon);

    // Runs
    pFilletOp ->**Run**(#);

    // Gets the resulting body
pFilletOp ->**Run**(#);
    CATBody * piMainBody4 = NULL;
```vbscript
    piMainBody4 = pFilletOp->**GetResult**(#);

    if (NULL==piMainBody4)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
piMainBody4 = pFilletOp->**GetResult**(#);
```vbscript
if (NULL==piMainBody4)
      return (1);

```

    }

    // Deletes the operator
    **delete** pFilletOp;
return (1);
    pFilletOp = NULL;

    if (NULL != pRadius) **delete** pRadius;
    pRadius = NULL;
    if (NULL != pRibbon) **delete** pRibbon;
    pRibbon = NULL;

    piGeomFactory->**Remove**(piMainBody3);
    piMainBody3 = NULL;

---

[Top]
#### Shelling

Take two offset bodies of one initial body. The shelling operation digs a volume by removing one offset body (internal) from the other one (external). Some faces can also be not offset: these faces are called openings. In the use case, the opening face is the bottom face of the prism: it is the unique face with five edges and one domain. The way to retrieve it is similar to the way used in the section Fillets. First void the list (`RemoveAll`), and remember that the list begins at 1!

    listEdges.**RemoveAll**(#);
    piFace = NULL;
```vbscript
    for (i=1;i<=nbFaces;i++)

```

    {
listEdges.**RemoveAll**(#);
piFace = NULL;
for (i=1;i<=nbFaces;i++)
```vbscript
```vbscript
     if ( 1== (listFaces[i]->**GetNbDomains**(#)) )

```

```

     {
piFace = NULL;
for (i=1;i<=nbFaces;i++)
```vbscript
```vbscript
if ( 1== (listFaces[i]->**GetNbDomains**(#)) )
       piLoop = listFaces[i]->**GetDomain**(1);
```

```

       piLoop ->**GetAllCells**(listC, 1);
       numberOfEdges = listC.**Size**(#);
```vbscript
```vbscript
       if (5==listC.Size(#))

```

```

       {
piLoop = listFaces[i]->**GetDomain**(1);
piLoop ->**GetAllCells**(listC, 1);
numberOfEdges = listC.**Size**(#);
```vbscript
if (5==listC.Size(#))
```

         piFace=listFaces[i];

       }
     }
    }

```vbscript
    if (NULL == piFace) return (3);

```

---

The shelling operation can now be defined and run. To use it:

  * Create it (with the corresponding `::CATCreateDynShell` global function) by declaring the body to shell (`MainBody4`) and the offset values defined the factory unit
  * Define the openings (`Append`)
  * Run it
  * Get the resulting body (`MainBody5`). This body is created by `CATDynShell` using `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
  * Delete it.

Also removes the old body (`MainBody4`).

    CATDynShell* pShellOp = **CATCreateDynShell** (piGeomFactory,

                                               &topdata,      _// the configuration and the journal_
Also removes the old body (`MainBody4`).
CATDynShell* pShellOp = **CATCreateDynShell** (piGeomFactory,
                                               piMainBody4,   _// the body to shell_

                                               -1.,   _// first offset value (inside the body)_
CATDynShell* pShellOp = **CATCreateDynShell** (piGeomFactory,
piMainBody4,   _// the body to shell_
                                               0.);   _// second offset value (initial body)_
```vbscript
    if (NULL==pShellOp)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
0.);   _// second offset value (initial body)_
if (NULL==pShellOp)
```vbscript
      return (1);

```

    }
```vbscript
if (NULL==pShellOp)
```vbscript
return (1);
```

    _// Sets the opening faces_
    CATLISTP(CATFace) openings;
    openings.Append((CATFace*)piFace);
    pShellOp-> **Append**(openings);

    _// Runs_
    pShellOp->**Run**(#);

    _// Gets the resulting body_
    CATBody * piMainBody5 = NULL;
    piMainBody5 = pShellOp->**GetResult**(#);
```vbscript
    if (NULL==piMainBody5)
```

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
CATBody * piMainBody5 = NULL;
piMainBody5 = pShellOp->**GetResult**(#);
```vbscript
if (NULL==piMainBody5)
      return (1);

```

    }

return (1);
    _// Deletes the operator_

    **delete** pShellOp;
return (1);
_// Deletes the operator_
    pShellOp = NULL;

    piGeomFactory->**Remove**(piMainBody4,CATICGMContainer::RemoveDependancies);
    piMainBody4 = NULL;

---

[Top]
#### Computing the Volume

`CATDynMassProperties3D` is an operator to analyze a body. Here we ask for the computation of the volume of the body, result of all the operations. To use it:

  * Create it with the `::CATDynCreateMassProperties3D` global function
  * Get the needed characteristics
  * Delete it.

    CATDynMassProperties3D *pPropOp = **CATDynCreateMassProperties3D** (piMainBody5);
```vbscript
    if (NULL != pPropOp)

```

    {
CATDynMassProperties3D *pPropOp = **CATDynCreateMassProperties3D** (piMainBody5);
if (NULL != pPropOp)
       cout << "Volume of the final object" << pPropOp->**GetVolume**(#) << endl;

       **delete** pPropOp;
CATDynMassProperties3D *pPropOp = **CATDynCreateMassProperties3D** (piMainBody5);
if (NULL != pPropOp)
cout << "Volume of the final object" << pPropOp->**GetVolume**(#) << endl;
       pPropOp = NULL;

    }

---

[Top]
#### Writing the Model and Closing the Factory

Before ending, we must first release the software configuration.

    _// Releases the configuration_
        pConfig->Release(#);

---

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.
The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
     if(1==toStore)

     {
    #ifdef _WINDOWS_SOURCE
```cpp
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;
```

    #else
```cpp
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

    #endif

       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close(#);
     }

     _//
     // Closes the container
     //_

     **::CATCloseCGMContainer**(piGeomFactory);

---

[Top]

* * *
### In Short

This use case creates a body by chaining several types of topological operations, such Boolean, Filleting or Shelling, and primitive creation. The journal is not detailed.

[Top]

* * *
### References

[1] | [How to Use the Topological Journal](CAATopJournal.md)
---|---
[2] | [Topology Concepts](../CAATobTechArticles/TopoConcepts.md)
[3] | [The CGM Topological Model](../CAATobTechArticles/TopoModel.md)
[4] | [The CGM Journal](../CAATopTechArticles/TopoJournal.md)
[5] | [The Geometric Operators](../CAAGopUseCases/CAAGopIntersect.md)
[6] | [The Boolean Operators](../CAATopTechArticles/TopoBoolean.md)
[7] | [The Objects of CATIA Geometric Modeler](../CAATopTechArticles/TopoBoolean.md)
[8] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[9] | [Basic Topological Operators](CAATopSpline.md)
[Top]

* * *
### History

Version: **1.1** [Oct 2000] | Operator configuration
---|---
Version: **1** [May 2000] | Document created
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
