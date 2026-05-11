---
```vbscript
title: "Using the Topological Objects"
category: "use case"
module: "CAACgmModel"
tags: ["CATICGMIntersectionCrvCrv", "CAADoc", "CAATobTetra", "CATICGMObject", "CATICGMProjectionPtSur", "CAAGMModelGemBrowser", "CAAGMModelCreation", "CATIntersectionSurSur", "CAAGMModelInterfaces", "CAAGMModelTetra", "CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTobTetra.htm"
converted: "2026-05-11T17:33:48.580181"
```

---
tags: ["CATICGMIntersectionCrvCrv", "CAADoc", "CAATobTetra", "CATICGMObject", "CATICGMProjectionPtSur", "CAAGMModelGemBrowser", "CAAGMModelCreation", "CATIntersectionSurSur", "CAAGMModelInterfaces", "CAAGMModelTetra", "CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTobTetra.htm"
converted: "2026-05-11T17:33:48.580181"
Using the Topological Objects

---
converted: "2026-05-11T17:33:48.580181"
Using the Topological Objects
Use Case
Abstract The goal of this use case is to understand the topological model of the geometric modeler, by creating a tetrahedron only with the GMModelInterfaces resources. Topological objects can also be directly created by topological operators, and the use of topological operators (mostly defined in the GMOperatorsInterfaces framework) is the recommended way rather than using the basic tools of the GMModelInterfaces framework. The navigation in a topological structure is also discussed.

    * What You Will Learn With This Use Case
    * The Principle
    * The CAAGMModelTetra Use Case
      * What Does CAAGMModelTetra Do
      * How to Launch CAAGMModelTetra
      * Where to Find the CAAGMModelTetra Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case The topological model is fully described in technical articles [1] [2]. The use case shows how to use the GMModelInterfaces to create and explore topological objects. The Principle The intent of this section is to recall some important notions about the topological model. The topology manages the Boundary Representation of an object: what it bounds and how. A _cell_ is the lowest level of topological objects. There are four types of cells:
    * A _volume_ is a part of the space bounded by faces.
    * A _face_ is a part of a surface bounded by edges.
    * An _edge_ is a part of curve bounded by vertices.
    * A _vertex_ is the topology of the point.
Connected cells of same dimension are grouped into _domains_ to define the boundary of another cell. We can now detail the above definitions:
    * A set of connected volumes is called a _lump_.
    * A volume is a part of the space bounded by shells (sets of connected faces).
    * A face is a part of a surface bounded by loops (sets of connected edges).
    * An edge is a part of a curve bounded by vertices (no domain associated in this case).
    * A shell that does not bound a volume defines a skin.
    * A set of connected edges that does not bound a face is called a _wire_.
    * A vertex alone in the space is a _vertex in volume_.
The _body_ is the highest level of topological object: it is a set of lumps, shells, wires, and vertices in volume. The topological operators operate on bodies,... and it is often much more simpler to use a topological operator than to create the topology from scratch! The CAAGMModelTetra Use Case CAAGMModelTetra is a use case of the CAAGMModelInterfaces.edu framework that illustrates the GMModelInterfaces framework capabilities. What Does CAAGMModelTetra Do The use case details the creation of the geometry and of the topology of the tetrahedron. Moreover, it scans the created topology. Fig. 1: The Topological Structure of the Tetrahedron ![Tetrahedron Topological Structure](images/CAACgmTobCAATobTetra1.gif) | The tetrahedron is a volume bounded by a shell containing 4 faces. Each face is bounded by a loop containing 3 edges, and two adjacent faces have a common edge: the edge makes the connection between the faces. Hence, there are 6 edges in the whole body. In the same way, edges are bounded (and connected) by vertices: there are four vertices.
---|---
The topology bounds the geometry. Hence, the geometry of a vertex is a point, the geometry of a curve and the geometry of a face is a surface. In the CATIA geometric model, any kind of CATSurface can be the geometry of a CATFace. But the geometry of a CATEdge can only be a special type of curve called CATEdgeCurve, and the geometry of a CATVertex can only be a special type of point called CATMacroPoint.
    * A CATEdgeCurve represents several curves. Take the common edge of two faces, each face having its own surface. The CATEdgeCurve represents the CATPCurve on the first surface and the CATPCurve on the second surface. Then, a gap can exist between the two CATPCurve, if they are not exactly identical: this gap might be not greater than the factory resolution [4], except for imported models, when the initial gap was greater.
    * A CATMacroPoint represents several points, the points on each curve of the edges bounded by a vertex.
The _body_ is the highest level of topological object: it is a set of lumps, shells, wires, and vertices in volume. The topological operators operate on bodies,... and it is often much more simpler to use a topological operator than to create the topology from scratch! The CAAGMModelTetra Use Case CAAGMModelTetra is a use case of the CAAGMModelInterfaces.edu framework that illustrates the GMModelInterfaces framework capabilities. What Does CAAGMModelTetra Do The use case details the creation of the geometry and of the topology of the tetrahedron. Moreover, it scans the created topology. Fig. 1: The Topological Structure of the Tetrahedron ![Tetrahedron Topological Structure](images/CAACgmTobCAATobTetra1.gif) | The tetrahedron is a volume bounded by a shell containing 4 faces. Each face is bounded by a loop containing 3 edges, and two adjacent faces have a common edge: the edge makes the connection between the faces. Hence, there are 6 edges in the whole body. In the same way, edges are bounded (and connected) by vertices: there are four vertices.
The topology bounds the geometry. Hence, the geometry of a vertex is a point, the geometry of a curve and the geometry of a face is a surface. In the CATIA geometric model, any kind of CATSurface can be the geometry of a CATFace. But the geometry of a CATEdge can only be a special type of curve called CATEdgeCurve, and the geometry of a CATVertex can only be a special type of point called CATMacroPoint.
Fig. 2: The Edge Curve ![Edge Curve](images/CAACgmTobCAATobTetra2.gif) | The CATEdgeCurve is the geometric representation of a curve, that internally has several facets. In the case of Fig. 2, the CATEdgeCurve represents the geometry of the intersection between two surfaces, that is to say the CATPCurves lying on the two surfaces. The CATPCurve is able to map a parameter (`P(w1)`) on one curve to its equivalent on the other curve (`P(w2)`): the evaluation of `P(w1)` on CATPCurve1 and the evaluation of `P(w2)` on CATPCurve2 give the same 3D location.

The topology bounds the geometry. Hence, the geometry of a vertex is a point, the geometry of a curve and the geometry of a face is a surface. In the CATIA geometric model, any kind of CATSurface can be the geometry of a CATFace. But the geometry of a CATEdge can only be a special type of curve called CATEdgeCurve, and the geometry of a CATVertex can only be a special type of point called CATMacroPoint.
Fig. 2: The Edge Curve ![Edge Curve](images/CAACgmTobCAATobTetra2.gif) | The CATEdgeCurve is the geometric representation of a curve, that internally has several facets. In the case of Fig. 2, the CATEdgeCurve represents the geometry of the intersection between two surfaces, that is to say the CATPCurves lying on the two surfaces. The CATPCurve is able to map a parameter (`P(w1)`) on one curve to its equivalent on the other curve (`P(w2)`): the evaluation of `P(w1)` on CATPCurve1 and the evaluation of `P(w2)` on CATPCurve2 give the same 3D location.
The description of the geometry and of the cells is not sufficient to describe the topology: there is still to define the inside and outside of the objects. Several orientation properties must be set, that will be described when needed in the use case:

    * The relative orientation between the geometry and the topology.
    * The relative orientation of a cell inside its domain.
    * The location of a domain: does it represent an internal or external boundary?
How to Launch CAAGMModelTetra To launch CAAGMModelTetra, you will need to set up the build time environment, then compile CAAGMModelTetra.m along with its prerequisites, set up the run time environment, and then execute the use case [5]. If you simply type CAAGMModelTetra with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMModelTetra e/TetraCreation.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMModelTetra Code The CAAGMModelTetra use case is made of a main named CAATobTetra.cpp located in the CAAGMModelTetra.m module of the `CAAGMModelInterfaces`.edu framework: `InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAAGMModelTetra.m\` where `InstallRootFolder` [5] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following steps:
    * Creating the Geometry Factory
    * Creating the Geometry
    * Creating the Vertices
    * Creating the Edges
    * Creating the Loops and Faces
    * Creating the Shell
    * Creating the Volume
    * Creating the Lump
    * Completing and Freezing the Body
    * Scanning the Topological Structure
    * Writing the Model and Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the `CATICGMObject` (and the curves and surfaces in particular) [4]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the `CATICGMObject` (and the curves and surfaces in particular) [4]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

Creating the Geometry The topology is a logical information describing the boundary of geometric objects: so, first create the geometry! To create planes, directly use the `CreatePlane` method of the `CATGeoFactory`. If NULL pointers are returned, close the factory and return an error.

    CATPlane * piPlanexy = piGeomFactory->**CreatePlane**(CATMathPoint(),
                                                        CATMathPoint(1,0,0),
```vbscript
                                                        CATMathPoint(0,1,0));
```

      CATPlane * piPlaneyz = piGeomFactory->CreatePlane(CATMathPoint(),
                                                        CATMathPoint(0,1,0),
```vbscript
                                                        CATMathPoint(0,0,1));
```

      CATPlane * piPlanexz = piGeomFactory->CreatePlane(CATMathPoint(),
                                                        CATMathPoint(1,0,0),
```vbscript
                                                        CATMathPoint(0,0,1));
```

      CATPlane * piPlanec  = piGeomFactory->CreatePlane(CATMathPoint(10,0,0),
                                                        CATMathPoint(0,10,0),
```vbscript
                                                        CATMathPoint(0,0,10));
```

     _// is all right?_
      if (NULL==piPlanexy || NULL==piPlaneyz || NULL==piPlanexz || NULL==piPlanec)

      {
        ::CATCloseCGMContainer(piGeomFactory);
```vbscript
CATMathPoint(0,0,10));
_// is all right?_
if (NULL==piPlanexy || NULL==piPlaneyz || NULL==piPlanexz || NULL==piPlanec)
```vbscript
        return (1);
```

```

      }

Now, create `CATPLine` on the planes. A `CATPLine` is a line defined in the parameter space of a surface: it is natively on the surface. To define it, two parameters are needed: the parameters of the start and end limits of the line. But the parameterization of the CGM surfaces is not public: the way to map a parameter into a 3D point is not published. The ways to define a ` CATSurParameter` are:
    * To project a 3D point on the surface with the geometric operator `CATICGMProjectionPtSur`.
    * To use the `CATSurface::GetParam` method (only for canonical surfaces and a point that is known to be on the surface): It is the way used in the use case.
    * To use the barycentric constructor, after retrieving the limits (`CATSurface::GetLimits`) of the surface: this way is illustrated in the `CAAGMModelCreation` use case [6].
The following code creates the `CATPLine`.

    // PLines on Planexy
      CATSurParam Pxy0,Pxy1,Pxy2;
      // Gets the curve parameter corresponding to the Mathematical point
      // This is only possible here, because we know that the Point is on the plane
      // If the surface were not canonical, or if the point were not on the surface,
      // we might use a projection operator.
CATSurParam Pxy0,Pxy1,Pxy2;
      piPlanexy->GetParam(CATMathPoint(0 , 0,0),Pxy0);
      piPlanexy->GetParam(CATMathPoint(10, 0,0),Pxy1);
      piPlanexy->GetParam(CATMathPoint(0 ,10,0),Pxy2);

      // Creates the plines from the parameters
piPlanexy->GetParam(CATMathPoint(0 , 0,0),Pxy0);
piPlanexy->GetParam(CATMathPoint(10, 0,0),Pxy1);
piPlanexy->GetParam(CATMathPoint(0 ,10,0),Pxy2);
      CATPLine * piPLinexy01 = piGeomFactory->CreatePLine( Pxy0, Pxy1, piPlanexy );
      CATPLine * piPLinexy12 = piGeomFactory->CreatePLine( Pxy1, Pxy2, piPlanexy );
      CATPLine * piPLinexy20 = piGeomFactory->CreatePLine( Pxy2, Pxy0, piPlanexy );

      // PLines on Planeyz
CATPLine * piPLinexy01 = piGeomFactory->CreatePLine( Pxy0, Pxy1, piPlanexy );
CATPLine * piPLinexy12 = piGeomFactory->CreatePLine( Pxy1, Pxy2, piPlanexy );
CATPLine * piPLinexy20 = piGeomFactory->CreatePLine( Pxy2, Pxy0, piPlanexy );
      CATSurParam Pyz0,Pyz1,Pyz2;
      piPlaneyz->GetParam(CATMathPoint(0 , 0, 0),Pyz0);
      piPlaneyz->GetParam(CATMathPoint(0 ,10, 0),Pyz1);
      piPlaneyz->GetParam(CATMathPoint(0 , 0,10),Pyz2);
      CATPLine * piPLineyz01 = piGeomFactory->CreatePLine( Pyz0, Pyz1, piPlaneyz );
      CATPLine * piPLineyz12 = piGeomFactory->CreatePLine( Pyz1, Pyz2, piPlaneyz );
      CATPLine * piPLineyz20 = piGeomFactory->CreatePLine( Pyz2, Pyz0, piPlaneyz );

      // PLines on Planexz
CATPLine * piPLineyz01 = piGeomFactory->CreatePLine( Pyz0, Pyz1, piPlaneyz );
CATPLine * piPLineyz12 = piGeomFactory->CreatePLine( Pyz1, Pyz2, piPlaneyz );
CATPLine * piPLineyz20 = piGeomFactory->CreatePLine( Pyz2, Pyz0, piPlaneyz );
      CATSurParam Pxz0,Pxz1,Pxz2;
      piPlanexz->GetParam(CATMathPoint(0 , 0, 0),Pxz0);
      piPlanexz->GetParam(CATMathPoint(10, 0, 0),Pxz1);
      piPlanexz->GetParam(CATMathPoint(0 , 0,10),Pxz2);
      CATPLine * piPLinexz01 = piGeomFactory->CreatePLine( Pxz0, Pxz1, piPlanexz );
      CATPLine * piPLinexz12 = piGeomFactory->CreatePLine( Pxz1, Pxz2, piPlanexz );
      CATPLine * piPLinexz20 = piGeomFactory->CreatePLine( Pxz2, Pxz0, piPlanexz );

      // PLines on Planec
CATPLine * piPLinexz01 = piGeomFactory->CreatePLine( Pxz0, Pxz1, piPlanexz );
CATPLine * piPLinexz12 = piGeomFactory->CreatePLine( Pxz1, Pxz2, piPlanexz );
CATPLine * piPLinexz20 = piGeomFactory->CreatePLine( Pxz2, Pxz0, piPlanexz );
      CATSurParam Pc0,Pc1,Pc2;
      piPlanec->GetParam(CATMathPoint(10,0,0),Pc0);
      piPlanec->GetParam(CATMathPoint(0,10,0),Pc1);
      piPlanec->GetParam(CATMathPoint(0,0,10),Pc2);
      CATPLine * piPLinec01 = piGeomFactory->CreatePLine( Pc0, Pc1, piPlanec );
      CATPLine * piPLinec12 = piGeomFactory->CreatePLine( Pc1, Pc2, piPlanec );
      CATPLine * piPLinec20 = piGeomFactory->CreatePLine( Pc2, Pc0, piPlanec );

      // is all right?
CATPLine * piPLinec01 = piGeomFactory->CreatePLine( Pc0, Pc1, piPlanec );
CATPLine * piPLinec12 = piGeomFactory->CreatePLine( Pc1, Pc2, piPlanec );
CATPLine * piPLinec20 = piGeomFactory->CreatePLine( Pc2, Pc0, piPlanec );
      if (NULL==piPLineyz01 || NULL==piPLineyz12 || NULL==piPLineyz20 ||
          NULL==piPLinexy01 || NULL==piPLinexy12 || NULL==piPLinexy20 ||
          NULL==piPLinexz01 || NULL==piPLinexz12 || NULL==piPLinexz20 ||
          NULL==piPLinec01  || NULL==piPLinec12  || NULL==piPLinec20 )

      {
          ::CATCloseCGMContainer(piGeomFactory);
NULL==piPLinexy01 || NULL==piPLinexy12 || NULL==piPLinexy20 ||
NULL==piPLinexz01 || NULL==piPLinexz12 || NULL==piPLinexz20 ||
NULL==piPLinec01  || NULL==piPLinec12  || NULL==piPLinec20 )
          return (1);

      }

The `CATPCurve` must be used to create the real geometry of the edge: the `CATEdgeCurve`. In the use case case, as the geometry are planes, we know that the two `CATPCurve` of an edge curve have no gap: we can directly create the edge curve using the `CreateSimCurve` method of the `CATGeoFactory`. Another way is to use the geometric intersection operator `CATIntersectionSurSur`, that can output the intersection of two surface as an edge curve. Fig. 3: The Geometry of the Tetrahedron ![Tetrahedron Geometry](images/CAACgmTobCAATobTetra3.gif) | `EC01` is the edge curve that is the geometry of edge` E01`. It represents `PLxy01` on the plane `Pxy` and `PLxz01` on the plane `Pxz`. These two CATPCurve have the same orientation (1 value) as the orientation of their edge curve. The edge is bounded by two vertices whose geometry are the macro point` MP0` and `MP1`. These macro points are created by concatenation of points on the edge curves (CATPointOnEdgeCurve or Poec): for example `MP1` represents `Poec13s` (start of edge curve `EC13`), `Poec01e` (end of edge curve `EC01`) and `Poec12s` (start of edge curve` EC12` ). `EC20` is the edge curve that is the geometry of edge` E20`. It represents `PLxy20` on the plane `Pxy` and `PLyz01` on the plane `Pyz`. `PLxy20` has the same orientation as the orientation of its edge curve whereas `PLyz01` has the opposite orientation (-1 value).
---|---

    // ----------- Creates the Edge Curves, representing several PLines
      //
The `CATPCurve` must be used to create the real geometry of the edge: the `CATEdgeCurve`. In the use case case, as the geometry are planes, we know that the two `CATPCurve` of an edge curve have no gap: we can directly create the edge curve using the `CreateSimCurve` method of the `CATGeoFactory`. Another way is to use the geometric intersection operator `CATIntersectionSurSur`, that can output the intersection of two surface as an edge curve. Fig. 3: The Geometry of the Tetrahedron ![Tetrahedron Geometry](images/CAACgmTobCAATobTetra3.gif) | `EC01` is the edge curve that is the geometry of edge` E01`. It represents `PLxy01` on the plane `Pxy` and `PLxz01` on the plane `Pxz`. These two CATPCurve have the same orientation (1 value) as the orientation of their edge curve. The edge is bounded by two vertices whose geometry are the macro point` MP0` and `MP1`. These macro points are created by concatenation of points on the edge curves (CATPointOnEdgeCurve or Poec): for example `MP1` represents `Poec13s` (start of edge curve `EC13`), `Poec01e` (end of edge curve `EC01`) and `Poec12s` (start of edge curve` EC12` ). `EC20` is the edge curve that is the geometry of edge` E20`. It represents `PLxy20` on the plane `Pxy` and `PLyz01` on the plane `Pyz`. `PLxy20` has the same orientation as the orientation of its edge curve whereas `PLyz01` has the opposite orientation (-1 value).
      CATLISTP(CATCurve)     curves;
```vbscript
      CATLISTP(CATCrvLimits) limits;
```

      CATListOfInt           orients;
      CATCrvLimits           crvLim1,crvLim2;
      double resolution = piGeomFactory ->**GetResolution**();

      // Appends the first curve in of the sim curve
CATListOfInt           orients;
CATCrvLimits           crvLim1,crvLim2;
double resolution = piGeomFactory ->**GetResolution**();
      curves.Append(piPLinexy01);
      piPLinexy01->GetLimits(crvLim1);

      // Defines its limits
curves.Append(piPLinexy01);
piPLinexy01->GetLimits(crvLim1);
      limits.Append(&crvLim1);

      // Defines its relative orientation in the edge curve
curves.Append(piPLinexy01);
piPLinexy01->GetLimits(crvLim1);
limits.Append(&crvLim1);
      orients.Append(**1**);   // 1 == same orientation

      // The same for the second pline
limits.Append(&crvLim1);
orients.Append(**1**);   // 1 == same orientation
      curves.Append(piPLinexz01);
      piPLinexy01->GetLimits(crvLim2);
      limits.Append(&crvLim2);
      orients.Append(1);  // 1 == same orientation

      // Now creates the sim curve
piPLinexy01->GetLimits(crvLim2);
limits.Append(&crvLim2);
orients.Append(1);  // 1 == same orientation
      CATSimCurve * piSimCurve01= piGeomFactory-> **CreateSimCurve**(curves,
                                                                 limits,
                                                                 orients,
                                                                 resolution);

      // The second sim curve
limits,
orients,
resolution);
      curves[1] = piPLinexy12;
      curves[1] ->GetLimits(*(limits[1]));
      curves[2] = piPLinec01;
      curves[2] ->GetLimits(*(limits[2]));
      CATSimCurve * piSimCurve12= piGeomFactory-> CreateSimCurve(curves,
                                                                 limits,
                                                                 orients,
                                                                 resolution);;

      // The third sim curve
limits,
orients,
resolution);;
      curves[1] = piPLinexz20;
      curves[1] ->GetLimits(*(limits[1]));
      curves[2] = piPLineyz20;
      curves[2] ->GetLimits(*(limits[2]));
      CATSimCurve * piSimCurve30= piGeomFactory-> CreateSimCurve(curves,
                                                                 limits,
                                                                 orients,
                                                                 resolution);

      // The fourth sim curve
limits,
orients,
resolution);
      curves[1] = piPLineyz12;
      curves[1] ->GetLimits(*(limits[1]));
      curves[2] = piPLinec12;
      curves[2] ->GetLimits(*(limits[2]));
      CATSimCurve * piSimCurve23= piGeomFactory-> CreateSimCurve(curves,
                                                                 limits,
                                                                 orients,
                                                                 resolution);

      // The fiveth sim curve
limits,
orients,
resolution);
      curves[1] = piPLinexy20;
      curves[1] ->GetLimits(*(limits[1]));
      curves[2] = piPLineyz01;
      curves[2] ->GetLimits(*(limits[2]));
      orients[2] = **-1** ;  // -1 == opposite orientation
      CATSimCurve * piSimCurve20= piGeomFactory-> CreateSimCurve(curves,
                                                                 limits,
                                                                 orients,
                                                                 resolution);

      // The sixth sim curve
CATSimCurve * piSimCurve20= piGeomFactory-> CreateSimCurve(curves,
limits,
orients,
resolution);
      curves[1] = piPLinexz12;
      curves[1] ->GetLimits(*(limits[1]));
      curves[2] = piPLinec20;
      curves[2] ->GetLimits(*(limits[2]));
      CATSimCurve * piSimCurve13= piGeomFactory-> CreateSimCurve(curves,
                                                                 limits,
                                                                 orients,
                                                                 resolution);

      // is all right?
CATSimCurve * piSimCurve13= piGeomFactory-> CreateSimCurve(curves,
limits,
orients,
resolution);
      if (NULL==piSimCurve01 || NULL==piSimCurve12 || NULL==piSimCurve20 ||
          NULL==piSimCurve23 || NULL==piSimCurve30 || NULL==piSimCurve13 )

      {
         ::CATCloseCGMContainer(piGeomFactory);
```vbscript
if (NULL==piSimCurve01 || NULL==piSimCurve12 || NULL==piSimCurve20 ||
NULL==piSimCurve23 || NULL==piSimCurve30 || NULL==piSimCurve13 )
         return (1);
```

      }

Before defining the CATMacroPoint, just create the points on the edge curves. These points on edge curve define the geometry of the start and end of each edge curve. As there are 4 edge curves, 8 points on edge curves are needed (see Fig. 3). To compute a point on edge curve, the use case proposes to retrieve the current limits of the curve. Another way is to use a `CATICGMIntersectionCrvCrv` operator. The `CreatePointOnEdgeCurve` method of the CATGeoFactory creates the poec, by using a curve of the edge curve. Notice that you can retrieve the corresponding parameter on the other curves of the edge curve by the `GetEquivalentParam` method of the CATEdgeCurve.

    // ----------- Creates the point on Edge Curves, limiting the Plines
     //
     // Poecs on edge curve 01
Before defining the CATMacroPoint, just create the points on the edge curves. These points on edge curve define the geometry of the start and end of each edge curve. As there are 4 edge curves, 8 points on edge curves are needed (see Fig. 3). To compute a point on edge curve, the use case proposes to retrieve the current limits of the curve. Another way is to use a `CATICGMIntersectionCrvCrv` operator. The `CreatePointOnEdgeCurve` method of the CATGeoFactory creates the poec, by using a curve of the edge curve. Notice that you can retrieve the corresponding parameter on the other curves of the edge curve by the `GetEquivalentParam` method of the CATEdgeCurve.
      CATCrvParam  crvParam;
      CATCrvLimits crvLimit;
      CATPointOnEdgeCurve *piPoec01Start=NULL,*piPoec01End=NULL;

      // Gets the limits of the first Pline
CATCrvParam  crvParam;
CATCrvLimits crvLimit;
CATPointOnEdgeCurve *piPoec01Start=NULL,*piPoec01End=NULL;
      piPLinexy01->**GetLimits**(crvLimit);

      // Defines the point on edge curve corresponding to the low limit
CATCrvLimits crvLimit;
CATPointOnEdgeCurve *piPoec01Start=NULL,*piPoec01End=NULL;
piPLinexy01->**GetLimits**(crvLimit);
      crvLimit.GetLow(crvParam);
      piPoec01Start = piGeomFactory->**CreatePointOnEdgeCurve**( piPLinexy01,
                                                             crvParam,
                                                             piSimCurve01);

      // Defines the point on edge curve corresponding to the high limit
crvLimit.GetLow(crvParam);
piPoec01Start = piGeomFactory->**CreatePointOnEdgeCurve**( piPLinexy01,
crvParam,
piSimCurve01);
      crvLimit.GetHigh(crvParam);
      piPoec01End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy01,
                                                             crvParam,
                                                             piSimCurve01);

    // Poecs on edge curve 12
piPoec01End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy01,
crvParam,
piSimCurve01);
      CATPointOnEdgeCurve *piPoec12Start=NULL,*piPoec12End=NULL;
      piPLinexy12->GetLimits(crvLimit);
      crvLimit.GetLow(crvParam);
      piPoec12Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy12,
                                                             crvParam,
                                                             piSimCurve12);
      crvLimit.GetHigh(crvParam);
      piPoec12End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy12,
                                                             crvParam,
                                                             piSimCurve12);

    // Poecs on edge curve 20
piPoec12End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy12,
crvParam,
piSimCurve12);
      CATPointOnEdgeCurve *piPoec20Start=NULL,*piPoec20End=NULL;
      piPLinexy20->GetLimits(crvLimit);
      crvLimit.GetLow(crvParam);
      piPoec20Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy20,
                                                             crvParam,
                                                             piSimCurve20);
      crvLimit.GetHigh(crvParam);
      piPoec20End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy20,
                                                             crvParam,
                                                             piSimCurve20);

    // Poecs on edge curve 23
piPoec20End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy20,
crvParam,
piSimCurve20);
      CATPointOnEdgeCurve *piPoec23Start=NULL,*piPoec23End=NULL;
      piPLineyz12->GetLimits(crvLimit);
      crvLimit.GetLow(crvParam);
      piPoec23Start = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz12,
                                                             crvParam,piSimCurve23);
      crvLimit.GetHigh(crvParam);
      piPoec23End   = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz12,
                                                             crvParam,
                                                             piSimCurve23);

    // Poecs on edge curve 30
piPoec23End   = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz12,
crvParam,
piSimCurve23);
      CATPointOnEdgeCurve *piPoec30Start=NULL,*piPoec30End=NULL;
      piPLineyz20->GetLimits(crvLimit);
      crvLimit.GetLow(crvParam);
      piPoec30Start = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz20,
                                                             crvParam,
                                                             piSimCurve30);
      crvLimit.GetHigh(crvParam);
      piPoec30End   = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz20,
                                                             crvParam,
                                                             piSimCurve30);

    // Poecs on edge curve 13
piPoec30End   = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz20,
crvParam,
piSimCurve30);
      CATPointOnEdgeCurve *piPoec13Start=NULL,*piPoec13End=NULL;
      piPLinexz12->GetLimits(crvLimit);
      crvLimit.GetLow(crvParam);
      piPoec13Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexz12,
                                                             crvParam,
                                                             piSimCurve13);
      crvLimit.GetHigh(crvParam);
      piPoec13End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexz12,
                                                             crvParam,
                                                             piSimCurve13);

     // Is all right?
crvLimit.GetHigh(crvParam);
piPoec13End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexz12,
crvParam,
piSimCurve13);
      if (NULL==piPoec01Start || NULL==piPoec01End ||
          NULL==piPoec12Start || NULL==piPoec12End ||
          NULL==piPoec20Start || NULL==piPoec20End ||
          NULL==piPoec23Start || NULL==piPoec23End ||
          NULL==piPoec30Start || NULL==piPoec30End ||
          NULL==piPoec13Start || NULL==piPoec13End)

      {
    	 ::CATCloseCGMContainer(piGeomFactory);
NULL==piPoec23Start || NULL==piPoec23End ||
NULL==piPoec30Start || NULL==piPoec30End ||
NULL==piPoec13Start || NULL==piPoec13End)
    	 return (1);

      }

Appending the points on the edge curves in the corresponding macro points, and the geometry is completed.

    // ----------- Creates the MacroPoints, representing several points
      //
Appending the points on the edge curves in the corresponding macro points, and the geometry is completed.
      CATMacroPoint *piMacro0=NULL, *piMacro1=NULL, *piMacro2=NULL, *piMacro3=NULL;
      CATLISTP(CATPoint) points;

      // Adds 3 points in edge curve per macro point, because there are 3 incident edges
      // at each vertex
CATMacroPoint *piMacro0=NULL, *piMacro1=NULL, *piMacro2=NULL, *piMacro3=NULL;
CATLISTP(CATPoint) points;
      points.Append(piPoec01Start);
      points.Append(piPoec20End);
      points.Append(piPoec30End);
```vbscript
      piMacro0 = piGeomFactory->**CreateMacroPoint**(points);

```

      points[1] = piPoec01End;
      points[2] = piPoec12Start;
      points[3] = piPoec13Start;
```vbscript
      piMacro1 = piGeomFactory->CreateMacroPoint(points);

```

      points[1] = piPoec12End;
      points[2] = piPoec20Start;
      points[3] = piPoec23Start;
```vbscript
      piMacro2 = piGeomFactory->CreateMacroPoint(points);

```

      points[1] = piPoec23End;
      points[2] = piPoec30Start;
      points[3] = piPoec13End;
```vbscript
      piMacro3 = piGeomFactory->CreateMacroPoint(points);

```

      // all is right?
points[1] = piPoec23End;
points[2] = piPoec30Start;
points[3] = piPoec13End;
piMacro3 = piGeomFactory->CreateMacroPoint(points);
```vbscript
      if (NULL==piMacro0 || NULL==piMacro1 || NULL==piMacro2 || NULL==piMacro3 )

```

      {
        ::CATCloseCGMContainer(piGeomFactory);
piMacro3 = piGeomFactory->CreateMacroPoint(points);
```vbscript
if (NULL==piMacro0 || NULL==piMacro1 || NULL==piMacro2 || NULL==piMacro3 )
        return (1);

```

      }

Creating the Vertices Before creating any topological entity, you first must create the factory of these entity: this factory is a CATBody, and not the CATGeoFactory. The factory of the CATBody, however, still is the CATGeoFactory.

    // ----------- Creates the factory of the cells
      //
Creating the Vertices Before creating any topological entity, you first must create the factory of these entity: this factory is a CATBody, and not the CATGeoFactory. The factory of the CATBody, however, still is the CATGeoFactory.
      CATBody * piTetra = piGeomFactory->**CreateBody**();

      // is all right?
      if (NULL==piTetra)
      {
    	::CATCloseCGMContainer(piGeomFactory);
CATBody * piTetra = piGeomFactory->**CreateBody**();
if (NULL==piTetra)
```vbscript
    	return (1);

```

      }

return (1);
Using `Tetra` as the cell factory, we can now create the vertices, and associate them with their geometry (macro point).

    CATVertex *piVertex0=NULL, *piVertex1=NULL, *piVertex2=NULL, *piVertex3=NULL;
      piVertex0 = pi**Tetra** ->**CreateVertex**();
```vbscript
```vbscript
      piVertex1 = piTetra->CreateVertex();
      piVertex2 = piTetra->CreateVertex();
      piVertex3 = piTetra->CreateVertex();

```

```

      // is all right?
piVertex0 = pi**Tetra** ->**CreateVertex**();
```vbscript
```vbscript
piVertex1 = piTetra->CreateVertex();
piVertex2 = piTetra->CreateVertex();
piVertex3 = piTetra->CreateVertex();
```

      if (NULL==piVertex0 || NULL==piVertex1 ||NULL==piVertex2 ||NULL==piVertex3)

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
piVertex3 = piTetra->CreateVertex();
```vbscript
if (NULL==piVertex0 || NULL==piVertex1 ||NULL==piVertex2 ||NULL==piVertex3)
    	return (1);

```

      }
      // Associates with their geometry
return (1);
      piVertex0->**SetPoint**(piMacro0);
      piVertex1->SetPoint(piMacro1);
      piVertex2->SetPoint(piMacro2);
      piVertex3->SetPoint(piMacro3);

Creating the Edges First create them void.

    CATEdge *piEdge01=NULL, *piEdge12=NULL, *piEdge20=NULL,

    	      *piEdge23=NULL, *piEdge30=NULL, *piEdge13=NULL;
Creating the Edges First create them void.
CATEdge *piEdge01=NULL, *piEdge12=NULL, *piEdge20=NULL,
      piEdge01 = piTetra->**CreateEdge**();
```vbscript
```vbscript
      piEdge12 = piTetra->CreateEdge();
      piEdge20 = piTetra->CreateEdge();
      piEdge23 = piTetra->CreateEdge();
      piEdge30 = piTetra->CreateEdge();
      piEdge13 = piTetra->CreateEdge();

```

```

      // Is all right?
piEdge20 = piTetra->CreateEdge();
```vbscript
```vbscript
piEdge23 = piTetra->CreateEdge();
piEdge30 = piTetra->CreateEdge();
piEdge13 = piTetra->CreateEdge();
```

      if (NULL==piEdge01 || NULL==piEdge12 ||NULL==piEdge20 ||
```

    	  NULL==piEdge23 || NULL==piEdge30 || NULL==piEdge13)

      {
    	::CATCloseCGMContainer(piGeomFactory);
```vbscript
if (NULL==piEdge01 || NULL==piEdge12 ||NULL==piEdge20 ||
NULL==piEdge23 || NULL==piEdge30 || NULL==piEdge13)
    	return (1);
```

      }

Now, for each edge:
    * Set its geometry (`SetCurve`): the edge curve, and the relative orientation of the edge curve and the edge. The orientation of the edge is given by the sense start edge -> end edge.
    * Bound the edge by its start vertex (`AddBoundingCell`):
      * The "start" attribute is given by the matter side set to `CATSideLeft`.
      * The `NULL` argument states the fact that no domain is associated with a vertex.
      * The last argument details which poec of the macro point is the end of the edge curve.
    * Bound the edge by its end vertex (`AddBoundingCell`):
      * The "end" attribute is given by the matter side set to `CATSideRight`.
      * The `NULL` argument states the fact that no domain is associated with a vertex.
      * The last argument states which poec of the macro point is the end of the edge curve.

    // Sets the geometry of Edge01: the sim curve, and the relative orientation
      // between the sim curve and the edge
      piEdge01->SetCurve(piSimCurve01,CATOrientationPositive);
      // Bounds Edge01 by Vertex0,
      //    Vertex0 is the start vertex (CATSideLeft)
      //    Vertex0 does not belong to any domain (NULL)
      //    The corresponding geometry of Vertex0 in the context
      //    of the edge Edge01 is Poec01Start
      piEdge01->**AddBoundingCell**(piVertex0,**CATSideLeft** ,**NULL** ,pi**Poec01Start**);
      // Bounds Edge01 by Vertex1,
      //    Vertex1 is the end vertex (CATSideRight)
      //    Vertex0 does not belong to any domain (NULL)
      //    The corresponding geometry of Vertex1 in the context
      //    of the edge Edge01 is Poec01End
      piEdge01->AddBoundingCell(piVertex1,**CATSideRight** ,NULL,piPoec01End);

piEdge01->AddBoundingCell(piVertex1,**CATSideRight** ,NULL,piPoec01End);
      piEdge12->SetCurve(piSimCurve12,CATOrientationPositive);
      piEdge12->AddBoundingCell(piVertex1,CATSideLeft,NULL,piPoec12Start);
      piEdge12->AddBoundingCell(piVertex2,CATSideRight,NULL,piPoec12End);

      piEdge20->SetCurve(piSimCurve20,CATOrientationPositive);
      piEdge20->AddBoundingCell(piVertex2,CATSideLeft,NULL,piPoec20Start);
      piEdge20->AddBoundingCell(piVertex0,CATSideRight,NULL,piPoec20End);

      piEdge23->SetCurve(piSimCurve23,CATOrientationPositive);
      piEdge23->AddBoundingCell(piVertex2,CATSideLeft,NULL,piPoec23Start);
      piEdge23->AddBoundingCell(piVertex3,CATSideRight,NULL,piPoec23End);

      piEdge30->SetCurve(piSimCurve30,CATOrientationPositive);
      piEdge30->AddBoundingCell(piVertex3,CATSideLeft,NULL,piPoec30Start);
      piEdge30->AddBoundingCell(piVertex0,CATSideRight,NULL,piPoec30End);

      piEdge13->SetCurve(piSimCurve13,CATOrientationPositive);
      piEdge13->AddBoundingCell(piVertex1,CATSideLeft,NULL,piPoec13Start);
      piEdge13->AddBoundingCell(piVertex3,CATSideRight,NULL,piPoec13End);

Creating the Loops and Faces Once again, first create a void topology. For the loop, indicates whether the loop defines an inner (hole) or outer boundary. In the case of the tetrahedron, the faces do not have any holes, all the loops are external.

    CATFace *piFacexy=NULL, *piFaceyz=NULL, *piFacexz=NULL, *piFacec=NULL;
      piFacexy = piTetra->**CreateFace**();
```vbscript
```vbscript
      piFaceyz = piTetra->CreateFace();
      piFacexz = piTetra->CreateFace();
      piFacec  = piTetra->CreateFace();
```

```

      CATLoop *piLoopxy=NULL, *piLoopyz=NULL, *piLoopxz=NULL, *piLoopc=NULL;

      // The loops define external boundary of the faces (CATLocationOuter)
piFaceyz = piTetra->CreateFace();
```vbscript
```vbscript
piFacexz = piTetra->CreateFace();
piFacec  = piTetra->CreateFace();
```

```

CATLoop *piLoopxy=NULL, *piLoopyz=NULL, *piLoopxz=NULL, *piLoopc=NULL;
      piLoopxy = piTetra->**CreateLoop**(CATLocationOuter);
```vbscript
```vbscript
      piLoopyz = piTetra->CreateLoop(CATLocationOuter);
      piLoopxz = piTetra->CreateLoop(CATLocationOuter);
      piLoopc  = piTetra->CreateLoop(CATLocationOuter);

```

```

      // is all right?
piLoopxy = piTetra->**CreateLoop**(CATLocationOuter);
```vbscript
```vbscript
piLoopyz = piTetra->CreateLoop(CATLocationOuter);
piLoopxz = piTetra->CreateLoop(CATLocationOuter);
piLoopc  = piTetra->CreateLoop(CATLocationOuter);
```

      if (NULL==piFacexy || NULL==piFaceyz ||NULL==piFacexz || NULL==piFacec ||
```

          NULL==piLoopxy || NULL==piLoopyz ||NULL==piLoopxz || NULL==piLoopc)

      {
    	::CATCloseCGMContainer(piGeomFactory);
```vbscript
if (NULL==piFacexy || NULL==piFaceyz ||NULL==piFacexz || NULL==piFacec ||
NULL==piLoopxy || NULL==piLoopyz ||NULL==piLoopxz || NULL==piLoopc)
    	return (1);
```

      }

Now, for each face:
    * Declare that the face is bounded by a loop (`AddDomain`): only one loop per face can be external.
    * Associate with the surface (`SetSurface`), and sets the relative orientation of the face and the surface. The orientation of the face is given by the walk along its edges, that must be given continuously. The faces of a volume must point to the _INSIDE_ of the volume. It is the reason why the face and the surface have opposite orientations (`CATOrientationNegative`).
    * Bound the face by the edges (`AddBoundingCell`):
      * The matter side tells on which side is the matter when standing along the face normal and looking in the edge direction: so that it depends on the orientation of the faace and on the orientation of the edge.
      * At the same time, the corresponding loop is updated.
      * The last argument details which PCurve of the edge curve is the geometry of the boundary.
    * Declare the completion of the loop (`Done`).

    // Face xy
      // Defines the external boundary of Facexy
      piFacexy->**AddDomain**(piLoopxy);
      // Associates with the geometry.
      // The orientation of the face and of its geometry are opposite
      // (CATOrientationNegative).
      piFacexy->**SetSurface**(piPlanexy,CATOrientationNegative);
      // The first bounding edge Edge20
      // The matter is at the right side (CATSideRight)
      // The edge must be included in the Loopxy loop
      // The geometry of Edge20 in the context of Facexy is PLinexy20
piFacexy->**SetSurface**(piPlanexy,CATOrientationNegative);
      piFacexy->**AddBoundingCell**(piEdge20,CATSideRight,pi**Loop** xy,piPLinexy20);
      piFacexy->AddBoundingCell(piEdge12,CATSideRight,piLoopxy,piPLinexy12);
      piFacexy->AddBoundingCell(piEdge01,CATSideRight,piLoopxy,piPLinexy01);

      // Declares that the loop is finished
piFacexy->**AddBoundingCell**(piEdge20,CATSideRight,pi**Loop** xy,piPLinexy20);
piFacexy->AddBoundingCell(piEdge12,CATSideRight,piLoopxy,piPLinexy12);
piFacexy->AddBoundingCell(piEdge01,CATSideRight,piLoopxy,piPLinexy01);
      piLoopxy->Done();

      // Faceyz
piFacexy->AddBoundingCell(piEdge01,CATSideRight,piLoopxy,piPLinexy01);
piLoopxy->Done();
      piFaceyz->AddDomain(piLoopyz);

      // Associates with the geometry and bounds the face
piLoopxy->Done();
piFaceyz->AddDomain(piLoopyz);
      piFaceyz->SetSurface(piPlaneyz,CATOrientationNegative);
      piFaceyz->AddBoundingCell(piEdge30,CATSideRight,piLoopyz,piPLineyz20);
      piFaceyz->AddBoundingCell(piEdge23,CATSideRight,piLoopyz,piPLineyz12);
      piFaceyz->AddBoundingCell(piEdge20,CATSideLeft,piLoopyz,piPLineyz01);
      piLoopyz->Done();// _The loop is finished!_

      // Facexz
piFaceyz->AddBoundingCell(piEdge23,CATSideRight,piLoopyz,piPLineyz12);
piFaceyz->AddBoundingCell(piEdge20,CATSideLeft,piLoopyz,piPLineyz01);
piLoopyz->Done();// _The loop is finished!_
      piFacexz->AddDomain(piLoopxz);

      // Associates with the geometry and bounds the face
piLoopyz->Done();// _The loop is finished!_
piFacexz->AddDomain(piLoopxz);
      piFacexz->SetSurface(piPlanexz);
      piFacexz->AddBoundingCell(piEdge01,CATSideLeft,piLoopxz,piPLinexz01);
      piFacexz->AddBoundingCell(piEdge13,CATSideLeft,piLoopxz,piPLinexz12);
      piFacexz->AddBoundingCell(piEdge30,CATSideLeft,piLoopxz,piPLinexz20);
      piLoopxz->Done();// The loop is finished!

      // Facec
piFacexz->AddBoundingCell(piEdge13,CATSideLeft,piLoopxz,piPLinexz12);
piFacexz->AddBoundingCell(piEdge30,CATSideLeft,piLoopxz,piPLinexz20);
piLoopxz->Done();// The loop is finished!
      piFacec->AddDomain(piLoopc);

      // Associates with the geometry and bounds the face
piLoopxz->Done();// The loop is finished!
piFacec->AddDomain(piLoopc);
      piFacec->SetSurface(piPlanec);
      piFacec->AddBoundingCell(piEdge12,CATSideLeft,piLoopc,piPLinec01);
      piFacec->AddBoundingCell(piEdge23,CATSideLeft,piLoopc,piPLinec12);
      piFacec->AddBoundingCell(piEdge13,CATSideRight,piLoopc,piPLinec20);
      piLoopc->Done();// The loop is finished!

Creating the Shell In the use case, the shell is aimed to bound a volume, it is an external boundary of a future volume (CATLocationOuter). To create a skin body, use the CATLocationIn3DSpace value instead, and directly attach the shell to the body (i.e.: go to step 9 and attach the shell to the body. But you still have to add the face inside the shell with the `AddCell` method).

    CATShell * piShell = NULL;
```vbscript
      piShell = piTetra->**CreateShell**(**CATLocationOuter**);

```

Creating the Volume After creating a void volume (`CreateVolume`), add it in the already created shell (`AddDomain`). As before, bound the volume by the faces by using the `AddBoundingCell` method:

    * The orientation is right, according to the previously face orientation.
    * The shell is automatically updated.
    * The geometry of the face is detailed.

Creating the Volume After creating a void volume (`CreateVolume`), add it in the already created shell (`AddDomain`). As before, bound the volume by the faces by using the `AddBoundingCell` method:
    CATVolume * piVolume = NULL;
```vbscript
      piVolume = piTetra->**CreateVolume**();

```

      // is all right?
CATVolume * piVolume = NULL;
piVolume = piTetra->**CreateVolume**();
```vbscript
```vbscript
      if (NULL==piShell || NULL==piVolume )

```

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
piVolume = piTetra->**CreateVolume**();
```vbscript
if (NULL==piShell || NULL==piVolume )
    	return (1);

```

      }
      // Adds the shell
      piVolume->**AddDomain**(piShell);

      // Bounds by the faces and add them in the shell at the same time
      // To define a volume, the shell orientation points to the volume inside
piVolume->**AddDomain**(piShell);
      piVolume->**AddBoundingCell**(piFacexy, CATSideRight, piShell, piPlanexy);
      piVolume->AddBoundingCell(piFacexz, CATSideRight, piShell, piPlanexz);
      piVolume->AddBoundingCell(piFaceyz, CATSideRight, piShell, piPlaneyz);
      piVolume->AddBoundingCell(piFacec, CATSideRight, piShell, piPlanec);

Creating the Lump After creating a void lump (`CreateLump`), add it the already created volume (`AddCell`).

    CATLump * piLump = NULL;
      piLump = piTetra->**CreateLump**();
```vbscript
```vbscript
      if (NULL==piShell || NULL==piVolume )

```

```

      {
    	 ::CATCloseCGMContainer(piGeomFactory);
CATLump * piLump = NULL;
piLump = piTetra->**CreateLump**();
```vbscript
if (NULL==piShell || NULL==piVolume )
    		return (1);

```

      }
      // Adds the volume
return (1);
      piLump->**AddCell**(piVolume);

Completing and Freezing the Body Adds the lump to the body (`AddDomain`). The topological structure is finished. It remains to declare this completion with the `Completed` method. As this method can throw errors, these errors are caught and written on the usual output.

    piTetra->**AddDomain**(piLump);
      CATTry    // to catch an error

      {
Completing and Freezing the Body Adds the lump to the body (`AddDomain`). The topological structure is finished. It remains to declare this completion with the `Completed` method. As this method can throw errors, these errors are caught and written on the usual output.
piTetra->**AddDomain**(piLump);
CATTry    // to catch an error
    	piTetra->Completed();
            piTetra->Freeze();

      }
CATTry    // to catch an error
piTetra->Completed();
piTetra->Freeze();
      CATCatch(CATError,error)

      {
piTetra->Completed();
piTetra->Freeze();
CATCatch(CATError,error)
        cout << error->GetMessageText()<<endl;
        cout << (error->GetNLSMessage()).CastToCharPtr()<<endl;
        rc=4;

      }
cout << error->GetMessageText()<<endl;
cout << (error->GetNLSMessage()).CastToCharPtr()<<endl;
rc=4;
      CATEndTry

The `Freeze` method declares that the body cannot be modified anymore. Using a frozen body in a topological operation leads to the duplication in the resulting body of the cells and domains that must be modified. The resulting body shares with the initial body the cells and domains that are not touched by the operation. Scanning the Topological Structure To retrieve the number of domains of a body, use the `CATBody::GetNbDomains` method. In case of the tetrahedron, only one domain is created. To retrieve a given domain, use the `CATBody::GetDomain` method, which argument is the rank (from 1 to `GetNbDomains`) of the domain to retrieve. A body can contain domain of different dimensions.

    long nbDomain = piTetra ->**GetNbDomains**();
```vbscript
      if (1!=nbDomain)

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
long nbDomain = piTetra ->**GetNbDomains**();
if (1!=nbDomain)
```vbscript
    	return (10);

```

      }
```vbscript
if (1!=nbDomain)
```vbscript
return (10);
```

      CATDomain * piDomain = NULL;
      piDomain = piTetra->**GetDomain**(1);
```vbscript
      if (NULL==piDomain)
```

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
CATDomain * piDomain = NULL;
piDomain = piTetra->**GetDomain**(1);
```vbscript
if (NULL==piDomain)
    	return (1);

```

      }

return (1);
Now, to retrieve the number of cells of the lump domain, use `CATDomain::GetAllCells`. This method fills a list with the founded cells. To have the number of cells, just ask the list (`Size`). In the tetrahedron case, there is one volume in the lump domain, and the pointer to the volume must not be NULL.

    CATLISTP(CATCell) listCells;
      piDomain ->**GetAllCells**(listCells, 3 );
      int nbCells = listCells.**Size**();
```vbscript
      if (1 != nbCells)

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
piDomain ->**GetAllCells**(listCells, 3 );
int nbCells = listCells.**Size**();
if (1 != nbCells)
```vbscript
    	return (11);

```

      }

return (11);
      CATCell * piVolumeCell = listCells[1];
```vbscript
      if (NULL==piVolumeCell)

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
CATCell * piVolumeCell = listCells[1];
if (NULL==piVolumeCell)
```vbscript
    	return (1);

```

      }

return (1);
From the volume to the shell: check that the volume is made of faces by retrieving the dimension of the cells of the domain.

    nbDomain = piVolumeCell->GetNbDomains();
```vbscript
```vbscript
      piDomain = piVolumeCell->GetDomain(1);

```

```

      // It is a shell, because it is made of faces (dimension 2).
nbDomain = piVolumeCell->GetNbDomains();
```vbscript
piDomain = piVolumeCell->GetDomain(1);
```

      short dimShell = piDomain->**GetLowDimension**();
```vbscript
      if ( 2 != dimShell )

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
short dimShell = piDomain->**GetLowDimension**();
if ( 2 != dimShell )
```vbscript
    	return (12);

```

      }

return (12);
From the shell to the faces: first clean the list with `RemoveAll` that frees the memory of the list, but does not remove the objects. Then, get all the cells (4 faces for the tetrahedron).

    listCells.**RemoveAll**();

      piDomain ->**GetAllCells**(listCells,dimShell);
      nbCells = listCells.Size();
```vbscript
```vbscript
      if (4!=nbCells)

```

```

      {
    	::CATCloseCGMContainer(piGeomFactory);
piDomain ->**GetAllCells**(listCells,dimShell);
nbCells = listCells.Size();
```vbscript
if (4!=nbCells)
    	return (13);

```

      }

```vbscript
For each face:
```

    * Recover its geometry: `CATCell::GetGeometry`.
    * Test the type of geometry (a `CATPlane` for the tetrahedron).
    * Retrieve the edges of the face: one way is to get the bounding loops (`GetDomain`) and the edges of the loops (`GetAllCells`) as always done, or use a boundary iterator, that is explained here:
      * Create it: `CATCell::CreateBoundaryIterator`.
      * Skip to the `CATBoundaryIterator::Next` cell until the last one.
      * `delete` it.

Using the boundary iterator, the number of edges is computed (4 for the tetrahedron).

Using the boundary iterator, the number of edges is computed (4 for the tetrahedron).
```vbscript
    for (int i=1;i<=nbCells;i++)

```

      {
Using the boundary iterator, the number of edges is computed (4 for the tetrahedron).
for (int i=1;i<=nbCells;i++)
         CATOrientation ori;
```vbscript
         if (NULL==listCells[i])

```

         {
    	   ::CATCloseCGMContainer(piGeomFactory);
CATOrientation ori;
if (NULL==listCells[i])
```vbscript
    	   return (1);

```

         }
        // Recovers the geometry
return (1);
        CATGeometry * piGeom = listCells[i]->**GetGeometry**(&ori);
```vbscript
        if (NULL==piGeom)

```

        {
    	  ::CATCloseCGMContainer(piGeomFactory);
CATGeometry * piGeom = listCells[i]->**GetGeometry**(&ori);
if (NULL==piGeom)
```vbscript
    	  return (1);

```

        }
        // Is the geometry of Plane type?
        if (NULL == (piGeom->IsATypeOf(**CATPlaneType**)) ) // the geometry is a plane!...
        {
    	  ::CATCloseCGMContainer(piGeomFactory);
    	  return (14);
        }
        // Another way to retrieve the cells: use a boundary iterator
return (14);
        CATBoundaryIterator  *  pBoundaryIt =
                                   listCells[i]->**CreateBoundaryIterator**();
```vbscript
        if (NULL==pBoundaryIt)

```

        {
    	  ::CATCloseCGMContainer(piGeomFactory);
CATBoundaryIterator  *  pBoundaryIt =
listCells[i]->**CreateBoundaryIterator**();
if (NULL==pBoundaryIt)
```vbscript
    	  return (1);

```

        }

return (1);
        CATSide side;
        CATCell*  piBcell = NULL;
        int nbEdges=0;
```vbscript
        while ((piBcell=pBoundaryIt->**Next**(&side,&piDomain)) != NULL)

```

        {
CATSide side;
CATCell*  piBcell = NULL;
int nbEdges=0;
while ((piBcell=pBoundaryIt->**Next**(&side,&piDomain)) != NULL)
           nbEdges = nbEdges+1;

        }
        **delete** pBoundaryIt;
while ((piBcell=pBoundaryIt->**Next**(&side,&piDomain)) != NULL)
nbEdges = nbEdges+1;
        pBoundaryIt=NULL;

        // There must be three edges for each face ...
        if (3!=nbEdges)
        {
    	   ::CATCloseCGMContainer(piGeomFactory);
    	   return (15);
        }

      }

Writing the Model and Closing the Factory To save the model on a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global method.

    if(1==toStore)
     {
    #ifdef _WINDOWS_SOURCE
Writing the Model and Closing the Factory To save the model on a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global method.
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;

    #else
```vbscript
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

    #endif

       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }

     //
     // Closes the container
     //

     **::CATCloseCGMContainer**(piGeomFactory);

In Short This use case creates a tetrahedron from scratch in order to expose the topological model of the geometric modeler. This primitive could also be created by using the topological operators in trimming a box primitive by a plane. The topology of the created tetrahedron is investigated to show different means to scan the body. References [1] | [Topology Concepts](CAACgmTaTobTopoConcepts.md)
---|---
[2] | [The CGM Topological Model](CAACgmTaTobTopoModel.md)
[3] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)
[4] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)
[5] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
[6] | [Creating and Transforming Geometry](CAACgmUcGobCreation.md)
History Version: **1** [Apr 2000] | Document created
---|---
