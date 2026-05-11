---
```vbscript
title: "The CGM Topological Model"
category: "use-case"
module: "CAACgmModel"
tags: ["CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmTaTobTopoModel.htm"
converted: "2026-05-11T17:33:48.051276"
```

---
# The CGM Topological Model

---
Technical Article
## Abstract

This article details how CGM implements the concepts of the topology used to bound geometric objects. The topological operations are not handled here. First, the main interfaces (CATBody, CATDomain, CATCell) are presented, followed by their mutual relationships, and their validity range. The smart mechanism allowing to reuse topology from body to body is explained in a second part. The last part is more specific about the objects management.
    * The Topological Objects
      * CATBody
      * CATDomain and CATCell
      * Relative Orientation between a CATCell and its Underlying Geometry
      * Location of a CATDomain Bounding a CATCell
      * Matter Side
      * List of the CATEdges inside a CATLoop
      * Orientation of a CATCell inside a CATDomain
      * Methodology
      * Validity of the Topological Objects
    * The Smart Concept
    * The Object Management
      * CATGeoFactory: the Factory of the CATBody
      * CATBody: the Factory of the CATCells and CATDomains
      * Navigation
    * In Short
    * References
---
## The CGM Topological Objects

The Topological Objects interfaces allow to handle the body and all the types of topological domains and cells described in Topological Concepts. They give means to navigate through the topological graph, but do not operate bodies: the operations are brought by the TopologicalOperators interfaces.
### CATBody

The CATBody interface implements the concept of topological body [2]. A CATBody is a geometric object, which handles a set of non necessarily connected cells and refers, directly or indirectly, all the cells needed for its construction. It offers tools to:

    * Navigate through itself.
    * Create the topological CATCells and CATDomains: in this sense, it is a factory for these topological objects.

The building up of a CATBody takes several steps:

    * Create a void CATBody.
    * Create CATCells and CATDomains with their mutual relationships. A CATCell is bounded by CATDomains which define an inner or an outer frontier. A CATDomain may also be immersed in a CATCell.
    * Associate them with the underlying geometry.
    * Attach the first level of domain(s) defining the CATBody.
    * Declare the completion of the CATBody and freeze it (this will be possible only if it satisfies to all the validity criteria, see Validity of the Topological Objects). It now can be used for topological operations, but cannot be modified anymore. It is necessary to make a copy of a frozen CATBody into a non-frozen one, in order to be able to perform modifications. Hence, topological operators do never modify input bodies, but retrieve the result into a new body.
### CATDomain and CATCell

CATDomain and CATCell interfaces implement the concept of topological domains and cells [2]. They offer navigation methods, and all Get and Set methods on their attributes.

CATDomain and CATCell interfaces implement the concept of topological domains and cells [2]. They offer navigation methods, and all Get and Set methods on their attributes.
The following arrays present the mapping between the concepts and the CGM interfaces.

Space Dimension | Cell (concepts) | CATCell | Associated CATGeometry | Bounded by

The following arrays present the mapping between the concepts and the CGM interfaces.
Space Dimension | Cell (concepts) | CATCell | Associated CATGeometry | Bounded by
0 | Vertex | CATVertex | CATMacroPoint |
1 | Edge | CATEdge | CATEdgeCurve | CATVertex
2 | Face | CATFace | CATSurface | CATLoop, CATVertexInFace
3 | Volume | CATVolume |   | CATShell, CATWire, CATVertexInVolume

  | Domain in 3D body (concepts) | CATDomain | Bounding
---|---|---|---
0 | VertexInVolume | CATVertexInVolume | CATBody, CATVolume
1 | Wire | CATWire | CATBody, CATVolume
2 | Shell | CATShell | CATBody, CATVolume
3 | Lump | CATLump | CATBody

  | Domain in 2D body (concepts) | CATDomain | Bounding
0 | VertexInVolume | CATVertexInVolume | CATBody, CATVolume
1 | Wire | CATWire | CATBody, CATVolume
2 | Shell | CATShell | CATBody, CATVolume
3 | Lump | CATLump | CATBody
0 | VertexInFace | CATVertexInFace | CATFace
1 | Loop | CATLoop | CATFace

The general object diagram is now presented.

Fig. 1: Topological Objects Diagram ![Topological Objects Diagram](images/CAACgmTobTopoDiagram.gif)

---

The general object diagram is now presented.
Fig. 1: Topological Objects Diagram ![Topological Objects Diagram](images/CAACgmTobTopoDiagram.gif)
Notice:

    * There is no domain associated with an edge boundary: a vertex bounds directly an edge.
    * A CATLoop is not necessarily closed. If it corresponds to an immersed domain of a face, it is necessarily open.
    * The CATDomains are manifold objects [2]: hence, it is sometimes necessary to divide a domain to satisfy this criterion.  Fig. 2: Examples of Manifold and Non-manifold Objects ![Manifold and Non-manifold Objects](images/CAACgmTobTopoModelNonManifold.gif)
---

We discuss now on the relationships and relative orientations between these objects.
### Relative Orientation Between a CATCell and its Underlying Geometry

A CATCell is a topological limitation of an underlying geometry (see also [3]).

    * The geometry of a vertex is a CATMacroPoint.
    * The geometry of an edge is a CATEdgeCurve.
    * The geometry of a face is a CATSurface.

The CATCell is oriented with regards to its underlying geometry.

`CATOrientationNegative`
The CATCell is oriented with regards to its underlying geometry.
    The cell orientation is reversed with regards to the geometry orientation.

`CATOrientationPositive`
The CATCell is oriented with regards to its underlying geometry.
The cell orientation is reversed with regards to the geometry orientation.
    The cell orientation is the geometry orientation.

`CATOrientationUnknown`
The cell orientation is reversed with regards to the geometry orientation.
The cell orientation is the geometry orientation.
    The cell orientation is not defined.
Fig. 3: Orientation of the Cell with Regards to its Geometry ![Cell Orientation](images/CAACgmTobTopoModelOrientation1.gif) | The edge V1-V2 is oriented from V2 to V1. Its orientation with regards to the geometry is inverted (`CATOrientationNegative`) Face has the same orientation as the orientation of the underlying surface. (`CATOrientationPositive`).

### Location of a CATDomain Bounding a CATCell

    * A CATDomain is a set of connected CATCells of same dimension that bound a cell of higher dimension. If it bounds a CATCell of dimension n, the CATDomain contains cells of dimension n-1. If immersed in a cell of dimension n, it contains cells of dimension less or equal to n-1.
    * A CATDomain bounds directly an unique CATCell of higher dimension or by a CATBody (for CATLump, CATShell, CATWire and CATVertexInVolume domains).
    * It is located with regards to this bounded CATCell (or CATBody) thanks to an attribute:

`CATLocationInner`
```vbscript
    For internal boundaries (holes into a faces or cavities into a volumes).
```

`CATLocationOuter`
```vbscript
    For external boundaries.
```

`CATLocationFull`
    All cells of the domain to create are immersed into the containing cell , but does not cut the cell in parts (non-manifold topology).
`CATLocationIn3DSpace`
```vbscript
    For creation into a body.
```

Fig. 4: Location of a Cell ![Cell Location](images/CAACgmTobTopoModelOrientation2.gif) | Face is bounded by 3 loop domains: L1 is its external boundary: `CATLocationOuter` L2 is an internal loop: `CATLocationInner` L3 is an immersed loop: `CATLocationFull`
---|---
### Matter Side

Fig. 4: Location of a Cell ![Cell Location](images/CAACgmTobTopoModelOrientation2.gif) | Face is bounded by 3 loop domains: L1 is its external boundary: `CATLocationOuter` L2 is an internal loop: `CATLocationInner` L3 is an immersed loop: `CATLocationFull`
The relative orientation between the cell and its underlying geometry and the type of location of the boundaries are not sufficient to precisely defined the relationships between the cells. It remains to be declared on which side is the matter, when a bounding cell is run along.

The CATSide attribute defines the matter side on a bounding cell of a cell. This attribute is independent of the geometric orientation (CATOrientation), but must be consistent with the location (CATLocation).

  |   | CATFace | CATEdge | CATVertex
---|---|---|---|---
**CATVolume** | `CATSideLeft` | The face normal points inside the volume | Impossible | Impossible
`CATSideRight` | The face normal points outside the volume | Impossible | Impossible
`CATSideFull` | The face is immersed into the volume | The edge is immersed into the volume | The vertex is immersed into the volume
**CATFace** | `CATSideLeft` |   | Standing along the face direction and watching in the direction of the edge leads to have the matter to your left.  | Impossible
`CATSideRight` |   | Standing along the face direction and watching in the direction of the edge leads to have the matter to your right. | Impossible
`CATSideFull` |   | The edge is immersed into the face | The vertex is immersed into the face
**CATEdge** | `CATSideLeft` |   |   | The vertex is at the edge beginning
`CATSideRight` |   |   | The vertex is at the edge end
`CATSideFull` |   |   | Impossible
### List of the CATEdges inside a CATLoop

The CATEdges must always be appended inside an inner or outer CATLoop in the order found by letting the matter on the left side, when the you stand along the normal of the face. This is independent on the orientation of the CATEdge itself.

Fig. 5: Order of the Edges Inside the Loop ![Edge Order](images/CAACgmTobTopoModelOrientation4.gif) | Top: The order for defining the outer loop is E1, E2, E3 (or E2, E3, E1; or E3, E1, E2). All other order is wrong. The order for defining the inner loop is I1, I2, I3 (or I2, I3, I1; or I3, I1, I2). All other order is wrong. Bottom: The order for defining the outer loop is E3, E2, E1 (or E2, E1, E3; or E1, E3, E2). All other order is wrong. The order for defining the inner loop is I3, I2, I1 (or I2, I1, I3; or I1, I3, I2). All other order is wrong.
---|---

The CATEdges must always be appended inside an inner or outer CATLoop in the order found by letting the matter on the left side, when the you stand along the normal of the face. This is independent on the orientation of the CATEdge itself.
Fig. 5: Order of the Edges Inside the Loop ![Edge Order](images/CAACgmTobTopoModelOrientation4.gif) | Top: The order for defining the outer loop is E1, E2, E3 (or E2, E3, E1; or E3, E1, E2). All other order is wrong. The order for defining the inner loop is I1, I2, I3 (or I2, I3, I1; or I3, I1, I2). All other order is wrong. Bottom: The order for defining the outer loop is E3, E2, E1 (or E2, E1, E3; or E1, E3, E2). All other order is wrong. The order for defining the inner loop is I3, I2, I1 (or I2, I1, I3; or I1, I3, I2). All other order is wrong.
Notice the CATSide attributes associated with the CATEdges.

A boundary cell operator always returns the CATCells in the order they have been defined inside the CATLoop. When a cell bounds a domain twice, the boundary cell operator returns the cell twice: once with the `CATSideLeft` attribute, once with the `CATSideRight` attribute. This configuration, allowed by the CGM topological model, is however to avoid: some topological operators does not hold it in a first version.

### Orientation of a CATCell inside a CATDomain

Notice the CATSide attributes associated with the CATEdges.
A boundary cell operator always returns the CATCells in the order they have been defined inside the CATLoop. When a cell bounds a domain twice, the boundary cell operator returns the cell twice: once with the `CATSideLeft` attribute, once with the `CATSideRight` attribute. This configuration, allowed by the CGM topological model, is however to avoid: some topological operators does not hold it in a first version.
A CATDomain is globally oriented. Each CATCell also owns its own orientation. It is the reason why it is necessary to set the `CATOrientation` of a CATCell with regards to the CATDomain that contends it. If this CATDomain is itself a boundary, it is equivalent to give the `CATOrientation` of the CATCell with regards to the CATDomain, or to define the `CATSide` of the CATCell (see the example of the cube below).

Fig. 6: Orientation of a Cell Inside a Domain ![Cell Orientation](images/CAACgmTobTopoModelOrientation3.gif) | The global orientation of the shells are represented by the black arrows. The orientation of each face is drawn in light blue. The faces S2, C2, C4 must have the attribute `CATOrientationNegative` to keep the consistency of the shell domain. The matter side is then `CATSideRight` for the faces C2 and C4, and `CATSideLeft` for the faces C1 and C3 (no matter side for S1, S2, S3, that do not bound a CATDomain).

### Methodology

```vbscript
Do the following steps for managing the different orientations:

```

    * Define the `CATOrientation` of the CATCell with regards to the geometry orientation (choose the orientation of the underlying geometry as much as possible).
    * Define the CATDomain that bounds the CATCell: set the type of boundary (`CATLocation`). For a CATFace, give the list of the CATEdges by letting the matter on the left when you stand along the face direction.
    * Set the matter side `CATSide` for each CATCell, with regards to its own orientation or define the `CATOrientation` of the CATCell with regards to the CATDomain it belongs to.
### Validity of the Topological Objects

The validity of the objects is checked at the CATBody completion. The CATBody cannot be frozen if one of the following rules is not fulfilled:

The validity of the objects is checked at the CATBody completion. The CATBody cannot be frozen if one of the following rules is not fulfilled:
    1. The geometry of a CATVertex is a CATMacroPoint and the geometry of the CATEdge is a CATEdgeCurve.
    2. The geometry of the points of the CATMacroPoint and the geometry of the bounded cells must be consistent. Hence:

       * A CATVertex bounding a CATEdge is related to a CATMacroPoint containing a CATPointOnEdgeCurve.
       * A CATVertex immersed into a CATFace is related to a CATMacroPoint containing a CATPointOnSurface.
       * A CATVertex immersed into the space is related to a CATMacroPoint representing any type of CATPoint.
1. The geometry of a CATVertex is a CATMacroPoint and the geometry of the CATEdge is a CATEdgeCurve.
2. The geometry of the points of the CATMacroPoint and the geometry of the bounded cells must be consistent. Hence:
    3. The geometry of the curves of an CATEdgeCurve and the geometry of the bounded cells must be consistent:

       * A CATEdge bounding a CATFace is related to a CATEdgeCurve containing a CATPCurve.
       * A CATEdge immersed into the space is related a CATEdgeCurve representing any type of CATCurves.
3. The geometry of the curves of an CATEdgeCurve and the geometry of the bounded cells must be consistent:
    4. A CATLoop is declared to be done as the loop is defined in terms of topology AND geometry. Inner and outer loops must be closed. Full (immersed) loop must not be closed.
    5. A CATShell (res.CATLoop) does not cut right across a CATVolume (reps. CATFace). This rule is required. However, it is not tested for a matter of performance.
    6. The iterator of the face edges always scans all the edges by letting the matter on the left side, whatever the type of loop (inner or outer) they belong to.
    7. Compatibility between the `CATSide` and `CATLocation` attributes.
    8. Closed topological cells: the CGM topological modeler allows such configurations, but some topological operators do not hold them for the moment. Avoid their use.

       * Closed circle with the same vertex at the beginning and the end of the edge.
       * Cylinder with an unique closed face: the surface cylinder is closed and an edge is laid down on the closure. The loop uses the edge, one way up, the other way down.
       * Cylinder with an unique closed face and two loops on the bottom and up circles.

_Hence, a cell must not be bounded several times by the same cell of lower dimension._ For representing such objects, it will be necessary to use more than one cell.
## The Smart Concept

_Hence, a cell must not be bounded several times by the same cell of lower dimension._ For representing such objects, it will be necessary to use more than one cell.
The topological model allows domains to share cells with other domains (in the same body or in different bodies). This property minimizes the model size. On the other hand, a cell may belong to several domains and bodies. Hence, it is necessary to precise the context of the body or the domain, for getting its parents.

This property is used by the topological operators. A topological operator often has frozen bodies as input operands. These bodies cannot be modified anymore. However, the topological operator exactly knows what it wants to modify. Then, it only duplicates the touched part of the body, and shares the untouched cells. For doing that, it uses a `CATSmartBodyDuplicator`.

The following example shows the Boolean difference between a cuboid and a cylinder that is totally included into the cuboid. In this case, all the faces of each initial body are shared with the resulting body.

Fig. 7: Illustration of the Smart Concept ![Smart Concept](images/CAACgmTobTopoSmart.gif) | This figure illustrates the smart concept: the initial bodies are not modified. A new one is created, sharing existing topology. Notice that the boundaries of the upper and lower faces of the cylinder are made of two edges, for satisfying the validity rules about closed cells.

## The Object Management

The object persistency is realized through the use of a document, that can be any user Document. A geometric container of CATGeoFactory type must be initialized to allow the creation of the geometric and topological objects.
### CATGeoFactory: the Factory of the CATBody

The CATGeoFactory is the factory of all geometric objects in general hence it is the factory of the CATBody, that is a geometric object.
### CATBody: the Factory of the CATCells and CATDomains

In turn, the CATBody allows to create CATCells and CATDomains of all dimensions inside a geometric container. These objects are however not directly attached to the CATBody that created them. Only the first level of domains will be directly related to the CATBody.
### Navigation

Different tools allows to easily navigate though the topology.

    * At the CATBody level: list of all the first level domains, hash table of all the cells of a given dimension, bounding edges list of a set of faces, etc.
    * At the CATDomain level: recursive and non recursive scans of the domain cells, etc.
    * At the CATCell level: iterator of the bounding cells, search of adjacent cells, etc.
## In Short

    * The CATBody, CATDomain and CATCell interfaces implements the concepts of the topological objects: A CATBody is made of CATDomain(s), that contains connected bounding CATCells linked to underlying geometry, etc. Three types of relative orientations precise their relationships:
      * A CATCell owns an orientation with respect to its underlying geometry.
      * A CATDomain is an inner, outer or immersed boundary of a CATCell or of a CATBody.
      * The CATSide defines the matter side of a CATCell when one of its bounding CATCell is run along.
    * Rules are established to insure the validity of a CATBody.
    * CATBodies may share CATCells (smart concept).
    * The CATGeoFactory creates the CATBodies, the CATBody creates the CATCells and CATDomains.
## References

[1] |  [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)
---|---
[2] | [Topology Concepts](CAACgmTaTobTopoConcepts.md)
[3] | [How to Associate Topology with Geometry](CAACgmTaTobTopoCreate.md)
## History

Version: **1** [Mar 2000] | Document created
---|---
