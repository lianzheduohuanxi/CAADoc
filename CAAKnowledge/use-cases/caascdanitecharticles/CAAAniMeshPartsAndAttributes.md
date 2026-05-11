---
title: "The Mesh Parts and their Attributes"
category: "use-case"
module: "CAAScdAniTechArticles"
tags: []
source_file: "Doc/online/CAAScdAniTechArticles/CAAAniMeshPartsAndAttributes.md"
converted: "2026-05-11T17:31:51.914774"
---
# Analysis Solution

| 
## Analysis Modeler

| 
### The Mesh Parts and their Attributes

_All the mesh parts you can use_  
---|---|---  
Technical Article  
  
* * *
### Abstract

This article describes the Mesh Parts and their Attributes available in Advanced Meshing Tools Workbench.  Names of the Mesh parts and their attributes are listed. These names are required to create the mesh part and also to assign values to its attributes. The type of attributes their legal values and their meaning is also explained. Following is the list of Mesh Parts

  * **Octree Tetrahedron Mesh**
  * **Tetrahedron Filler Mesh**
  * **Sweep 3D Mesh**
  * **Advanced Surface Mesh**
  * **Surface Mesh**
  * **Octree Triangle Mesh**
  * **Beam Mesh**
  * **Translation Mesh**
  * **Rotation Mesh**
  * **Symmetry Mesh**
  * **Extrude with Translation Mesh**
  * **Extrude with Rotation Mesh**
  * **Extrude with Symmetry Mesh**
  * **Extrude along a Spine Mesh**
  * **Coating 1D Mesh**
  * **Coating 2D Mesh**
  * **Spot Welding Connection Mesh**
  * **Seam Welding Connection Mesh**
  * **Surface Welding Connection Mesh**
  * **Nodes to Nodes Connection Mesh**
  * **Node Interface Mesh**

     
---  
  
* * *

Top]
####  ![](images/I_MshTetP2.gif)Octree Tetrahedron Mesh                                    [_use case_   ](../CAAScdAniUseCases/CAAAniMeshOctTetra.md) 

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartOctree3D | SizeValue        | Double |   | The required size of the mesh, it is an objective, the octree mesher will try to reach the nearest possible value  
  | AbsoluteSagValue | Double |   | Specifies the maximum absolute sag accepted this is active when the AbsoluteSag attribute is valuated to 2  
  | ElementOrder | Integer | 1,2 | Specifies the degree of the element 1 for linear 2 for parabolic  
  | MaxInteriorSize | Double |   | Specifies the value of the imposed interior size for 3D mesh when the InteriorSize attribute is active  
  | MinSizeForSags  | Double |   | Specifies the minimum size of the mesh. The Octree mesher tries to achieve the value specified in "SizeValue" but constrain sag may require decrease of the mesh size. This attributes imposes the condition on mesher that mesh size should not be less than the specified value.  
  | MinGeometrySize  | Double |   | The geometry having size below the specified size is not taken into account  
  |  AbsoluteSag | Integer | 1,2 | Attribute specifies whether the mesh is to be created with an imposed absolute sag value. Impose absolute sag (2), (1) otherwise.  
  | MaxWarpAngle  | Double |   | Specifies the maximum warp angle accepted for a quadratic triangle element  
  | Criteria  | Integer | 1,2,3 | Factor that user wants to respect for the elements of the mesh Skewness(1), Stretch(2), Shape(3)  
  | MeshGeometryViolation  | Integer | 1,2 | Specifies whether the user wants to suppress the edges of the mesh  
  | InteriorSize | Integer | 1,2 | Whether the user wants to apply the imposed maximum size for the interior size of the 3D mesh  
  | MinJacobian | Double |   | Minimum Jacobian accepted for each element of the mesh.  
  | MaxAttempts | Integer |   | Number of attempts for launching Octree algorithm if the meshing of the solid fails  
  | ProportionalSag | Integer | 1,2 | Specifies whether the mesh is created with imposed proportional minimum sag. Mesh is created with proportional sag(2), (1) otherwise  
  | ProportionalSagValue  | Double |   | Attribute which specifies the size of the maximum relative sag accepted this attribute is active when the "ProportionalSag" attribute is valuated to (2)  
**LocalSpecifications** |   |   |   |    
MSHLocalMeshSize |   |   |   | This specification is used in order to specify a local mesh size to faces or edges of geometry  
MSHMeshSizeMag | Double |   | Defines the required mesh size  
ConnectorList |   |   | Defines the support of the local specification  
MSHLocalMeshSag |   |   |   | To specify the local mesh sag to faces and edges of geometry  
MSHMeshSagMag | Double |   | Defines the required mesh sag  
ConnectorList |   |   | Defines the support of the local specification  
MSHLocalMeshImposedPoints |   |   |   | To impose mesh on the points on the geometry  
ConnectorList |   |   | Defines the support of the local specification  
MSHLocalMeshDistribution |   |   |   | This specification is used in order to impose a mesh distribution on edges of geometry  
MSHNumberOdEdges | Double |   | Defines the number of mesh edges  
ConnectorList |   |   | Defines the support of the local specification  
  
[Top]
####  ![](images/I_MshGHS3DP2.gif)Tetrahedron Filler Mesh                                    _[_use case_](../CAAScdAniUseCases/CAAAniMeshTetraFiller.md)_

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MHSPartGHS3D | ElementOrder  | Integer | 1,2 | Specifies the type of element linear(1) or parabolic(2)  
  | Propagation | Double | >1 | Factor which lets you dilute mesh elements inside solid   
  
 
####  ![](images/I_MshSweep3DP2.gif)**Sweep 3D Mesh                                     [_use case_](../CAAScdAniUseCases/CAAAniMeshSweep3D.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartSweep3D |  ElementOrder   | Integer | 1,2 | Specifies the type of element linear or parabolic  
  | GuideAngle | Double |   | Specifies the tolerance angle to compute the guides  
  | CaptureTol | Double |   | Lets you define maximum distance for mesh capture  
  |  DsitributionType | String | Uniform, Arithmetic, Geometric | Based on the distance between distributed nodes  
  | NbElements | Integer |   | Number of layers you want to insert between two supports  
  | Symmetric | Integer | 1,2 | Specifies the distribution to be symmetric(2) or not(1)  
  | Ratio | Double |   | Specifies the common difference value for the AP or common ratio value for GP.  
  | Reverse | Integer |   | Reverse the direction linked to the DistributionType  
  | Smoothing | Integer |   |    
  | Top |   |   | This geometrical support specifies the top face  
  | Bottom |   |   | This geometrical support specifies the bottom face  
  
[Top]
####  ![](images/I_MshAdvancedSurfMesherP2.gif)**Advanced Surface Mesh                         [_use case_](../CAAScdAniUseCases/CAAAniMeshAdvSurf.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartSmartSurface | GlobalMethod | String | "Frontal triangle", "Frontal quadrangle" | Specifies the type of the mesh wanted by the user.   
  | GlobalSize | Double |   | The required size of the mesh, it is an objective the surface mesher will try to reach the nearest possible value  
  | MinimumSize | Double |   | Attribute which specifies the minimum size accepted for the length of topological edges, under this size edges must be merged with others (if it's possible)  
  | ElementOrder | Integer | 1,2 | Attribute which specifies the type of the element the user wants to create linear(1), parabolic(2)  
  | FaceAngle | Double |   | Attribute which specifies the minimum angle under which two faces from geometry are grouped in a single topological domain  
  | CurveAngle | Double |   | Attribute which specifies the minimum angle under which two edges from the geometry are grouped in a single topological edge  
  | DetailsElimination | Integer | 1,2 | To activate the the merge of the edges during simplification of topology, linked to "MinimumSize". 1(Don`t activate the merge), 2(activate the merge)  
  | StripOptimization | Integer | 1,2 | Attribute which specifies if mesh in strips must be optimized in order to have a more regular mesh. Activate optimization(2), (1) otherwise  
  | CleanSize | Double |   | Minimum diameter under which a hole is ignored.  
  | Offset | Double |   | Distance between mesh and geometry  
  | OffsetFromThickness | Integer | 1,2 | Attribute which activates the calculation of better offset between mesh and geometry when thickness is defined. activate the calculation(2), (1) otherwise  
  | MinimizeTriangles | Integer |   | whether the number of triangles in the created mesh is minimized ( Useful when global method is "Frontal quadrangle"). Minimize(2), don't minimize(1)  
  | MinSizeForSag | Double |   | Minimum size for the mesh. Useful when the global method is "Frontal triangle"  
  | CurveCaptureTol | Double |   | Maximum distance for curve capture  
  | OptmtimizeRegularity | Integer | 1,2 | Activate(2) or not(1) the parameter which favor a mesh direction for elements.  
  | MeshRelSagValue | Double |   | Attribute which specifies the maximum relative sag accepted. Useful when the global method is "Frontal triangle".  
  | MeshRelSag | Integer | 1,2 | Specifies if the mesh is created with an imposed relative minimum sag ( Useful if the global method is "Frontal triangle")  
  | ConstraintSagValue | Double |   | Specifies the geometric sag for topology build  
  | CurveCapture | Integer | 1,2 | Attributes which specifies if the external curves must be captured.  
  | MeshCapture | Integer | 1,2 | Attribute which specifies if the external mesh must be captured.  
  | MeshCaptureTol | Double |   | Specifies the maximum distance for mesh capture linked to the attribute "MeshCapture" parameter.  
  | MeshAbsSag | Integer | 1,2 | Attribute which specifies if the mesh is created with an imposed minimum sag  
  | MeshAbsSagValue | Double |   | The size of the maximum sag accepted, if the "MeshAbsSag" attribute is activated only  
**Local Specifications** |   |   |   |    
MSHSuppressHole |   |   |   | This attribute is used in order to specify hole which must be ignored for mesh generation.  
Status | Boolean |   | Specifies if the hole must be suppressed (1) or not (0)  
Supports |   |   | It must represent the edge of the hole to suppress and only one.  
MSHSuppressCrack |   |   |   | This specification is used in order to ignore cracks of the geometry for mesh generation  
Status | Boolean |   | This specifies if the crack must be ignored (1) or not (0)  
Supports |   |   | It must represe the crack to suppress.  
MSHSuppressFace |   |   |   | This specification is used in order to ignore faces of the geometry for mesh generation  
Status | Boolean |   | Defines if the faces must be filled (1) or not (0) after being removed.  
Supports |   |   | It must represent one or more faces (a convex set) to inactivate. Supports could be added more than one time.  
MSHConstrainEdge |   |   |   | Used in order to constrain/unconstraint edge(s) of the geometry associated to the current mesh part  
Status | Boolean |   | Specifies if the supports must be constrained(1) or unconstrained(0)  
Supports |   |   | It could represent one or more edges to inactivate or a set of faces from which edges to constrain will be extracted  
MSHConstrainVertex |   |   |   | Used in order to constrain/unconstraint vertex from the geometry linked to the current mesh part  
Status | Boolean |   | This specifies if the supports must be constrained (1) or unconstrained (0)  
Supports |   |   | It must represent a vertex to constraint  
MSHConstrainCurve |   |   |   | This specification is used in order to constrain/unconstraint curves from geometry which is not linked to the current mesh part.  
Supports |   |   | It could represent one or more edges to inactivate or a set of faces from which edges to constrain will be extracted.  
MSHConstrainPoint |   |   |   | This specification is used in order to constrain/unconstraint points from geometry which is not linked to the current mesh part.  
Supports |   |   | It must represent a point to constraint  
MSHDistributionElement |   |   |   | This specification is used in order to define distribution on edge(s)  
Symmetric | Boolean |   | Specifies the distribution must be symmetric(1) or not(0)  
Type | String | "Isometric", "Geometric", "Arithmetic", "Law" | Type of wanted distribution.  
Reverse |   |   | Linked to the "Law" type this attribute allow to apply the law on the reverse side of the edge than default one  
Option | Integer | 1-8 | Specifies the set of attributes to apply depending on the distribution type.  
NbElements | Integer |   | Number of element wanted for the distribution  
Size1 | Double |   | It represents the distance from the first extremity ( respectively the second ) of the edge to the first internal node  
Size2 | Double |    
Ratio21 | Double |   | It is a ratio between size1 and size2   
Supports |   |   | It must represent a set of edges (continuous). Supports could be added more than one time  
MSHCaptureElement |   |   |   | This specification is used in order to define mesh capture coming from others mesh parts. In order to use it, others associated attributes must be defined:  
Tolerence | Double |   | This is a length (double) which define the tolerance of the capture;   
Coincidence | Boolean |   | Which define if the capture must be done with (1) or without (0) coincidence  
Condensation | Boolean |   | Defines if the capture must be done with (1) or without (0) condensation;   
Sources |   |   | To this component you must set the capture source if no tolerance have been set  
Supports |   |   | It must represent a set of edges. Note that supports could be added more than one time in this case.   
MSHMeshAroundHole |   |   |   | This specification is used in order to apply a mesh distribution around a set of holes  
NbElements | Integer |   | Defines the number of elements (mesh edges) to create around each hole of the set specified  
NbRows | Integer | 1,2,3 | Defines the number of rows of mesh elements to create around the hole;   
Height1 | Double |   | These attributes depends from the NbRows attribute. You must define these ones to specify the height of each row elements  
Height2 | Double |    
Height3 | Double |    
Supports |   |   | It must represent only one edge around hole  
MSHMeshDomain |   |   |   | This specification is used in order to specify a mesh method to a topological domain  
Method | String | FrontalTria,  FrontalQuad, HalfBead, MappedFree, Mapped, MappedTria, Bead | Type of the mesh to be created  
Size | Double |   | Defines the required mesh size  
Supports |   |   | Must represent the connex set of faces  
  
[Top]
####  ![](images/I_MshBasicSurfMesherP2.gif)**Surface Mesh                                            [_use case_](../CAAScdAniUseCases/CAAAniMeshBasicSurf.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartBasicSurf | GlobalMethod | Integer | 1,2 | triangle(2), quadrangle(1)  
  | ElementOrder | Integer | 1,2 | Attribute which specifies the type of the element the user wants to create linear(1), parabolic(2)  
  | QuadsOnly | Integer | 1,2 | Set(2) and unset(2) the quads only option  
  | DedicatedMesh | Integer | 1,2 | Whether the user wants to specify dedicated meshing method Useful only when frontal quadrangle method is selected  
  | DedicatedMethod | Integer | 1,2 | This option specifies the dedicated method  
  | GlobalSize | Double |   | Size of the mesh  
  | Offset | Double |   | Value according to which both the geometrical simplification and meshing will be offset  
  | CleanSize | Double |   | Minimum diameter under which a hole is ignored.  
  | TopologySize | Double |   | Global size assigned to the mesh  
  | TopoloySag | Double |   | constraint is created along the edge of a face to avoid creating elements across this edge. Lower the value more the constraints and vice versa  
  | SharpEdges | Integer | 1,2 | Whether the user wants to add sharp edges   
  | FaceAngle | Double |   | Attribute which specifies the minimum angle under which two faces from geometry are grouped in a single topological domain  
  | OffsetFromThickness | Integer | 1,2 | Attribute which activates the calculation of better offset between mesh and geometry when thickness is defined  
  | MeshRelSag | Integer | 1,2 | Specifies if the mesh is created with an imposed relative minimum sag ( Useful if the global method is "triangle")  
  | MeshRelSagValue | Double |   | Attribute which specifies the maximum relative sag accepted. Useful when the global method is "triangle"  
  | CurveCapture | Integer | 1,2 | Attributes which specifies if the external curves must be captured(2) or not(1)  
  | CurveCaptureTol | Double |   | Maximum distance for curve capture  
  |  MeshCapture | Integer | 1,2 | Attribute which specifies if the external mesh must be captured.  
  | MeshCaptureTol | Double |   | Specifies the maximum distance for mesh capture linked to the attribute MeshCapture parameter  
  |  MeshAbsSag | Integer | 1,2 | Attribute which specifies if the mesh is created with an imposed minimum sag.  
  | MeshAbsSagValue | Double |   | The size of the maximum sag accepted, only the MeshAbsSag attribute is is valuated to 2  
**Local Specifications** |   |   |   |    
MSHTopProjectCurve | ConnectorList |   |   | Specify the curve which is to be projected  
Tolerance | Double |   | The approximate distance of the curve from specified geometry  
MSHTopProjectPoint | ConnectorList |   |   | Specify the point which is to be projected  
Tolerance | Double |   | The approximate distance of the point from the specified geometry  
Project | Boolean | 0,1 | Specifies whether the point is to be projected on the geometry(1) or not (0)  
  
[Top]
#### ![](images/I_MshTr3P2.gif)**Octree Triangle Mesh                                     [_use case_](../CAAScdAniUseCases/CAAAniMeshOctTriangle.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartOctree2D | SizeValue | Double |   | The required size of the mesh, it is an objective the octree mesher will try to reach the neares possible value  
  | AbsoluteSagValue | Double |   | Specifies the maximum absolute sag accepted this is active when the AbsoluteSag attribute is active  
  | ElementOrder | Integer | 1,2 | Specifies the degree of the element 1 for linear 2 for parabolic  
  | MaxInteriorSize | Double |   | Specifies the value of the imposed interior size for 2D mesh when the InteriorSize attribute is active  
  | MinSizeForSags | Double |   | Specifies the minimum size of the mesh.  
  | MinGeometrySize | Double |   | The geometry having size below the specified size is not taken into account  
  | AbsoluteSag | Integer | 1,2 | Attribute specifies whether the mesh is to be created with an imposed absolute sag value(2) or not (1)   
  | ProportionalSag | Integer | 1,2 | Specifies whether the mesh is created with imposed proportional minimum sag.  
  | ProportionalSagValue | Double |   | Attribute which specifies the size of the maximum relative sag accepted this attribute is active when the ProportionalSag attribute is active  
  | MaxWarpAngle | Double |   | Specifies the maximum warp angle accepted for a quadratic triangle element  
  | Criteria | Integer | 1,2,3 | Factor that user wants to respect for the elements of the mesh Skewness(1), Stretch(2), Shape(3).  
  | MeshGeometryViolation | Integer | 1,2 | Specifies whether the user wants to suppress the edges of the mesh(2) or not  
  | InteriorSize | Integer | 1,2 | Whether the user wants to apply the imposed maximum size for the interior size of the 3D mesh.  
  | MinJacobian | Double |   | Minimum Jacobian accepted for each element of the mesh.  
  | MaxAttempts | Integer |   | Number of attempts for launching Octree algorithm if the meshing of the surface fails  
  | MeshViolationValue | Double |   | Specifies the value for which edges will be suppressed  
**LocalSpecifications** |   |   |   |    
MSHLocalMeshSize |   |   |   | This specification is used in order to specify a local mesh size to faces or edges of geometry  
MSHMeshSizeMag | Double |   | Defines the required mesh size  
ConnectorList |   |   | Defines the support of the local specification  
MSHLocalMeshSag |   |   |   | To specify the local mesh sag to faces and edges of geometry  
MSHMeshSagMag | Double |   | Defines the required mesh sag  
ConnectorList |   |   | Defines the support of the local specification  
MSHLocalMeshImposedPoints |   |   |   | To impose mesh on the points on the geometry  
ConnectorList |   |   | Defines the support of the local specification  
MSHLocalMeshDistribution |   |   |   | This specification is used in order to impose a mesh distribution on edges of geometry  
MSHNumberOdEdges | Double |   | Defines the number of mesh edges  
ConnectorList |   |   | Defines the support of the local specification  
  
[Top]
#### ![](images/I_MshBarP2.gif)**Beam Mesh                                                 [_use case_](../CAAScdAniUseCases/CAAAniMesh1D.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPart1D | SizeValue | Double |   | Sets the global mesh size  
  | AbsoluteSag | Integer | 1,2 | Sets the element sag  
  | AbsoluteSagValue | Double |   | Minimum distance between the mesh elements and the geometry. Useful for curve-type geometry  
  | MinimumSizeValue | Double |   | Minimum size of the element  
  | ElementOrder | Integer | 1,2 | Elements with intermediate nodes (2; specify "Parabolic") or without linear intermediate nodes(1; specify "Linear").  
  | MeshCapture | Integer | 1,2 | Specifies the option to capture external mesh with given tolerance. External mesh must be a 2D mesh  
  | MeshCaptureTol | Double |   | Specifies the tolerance value to capture mesh  
  | CurveAngle | Double |   | Defines the vertices to be taken into account.  
LocalSpecification |   |   |   |    
MSHTopProjectPoint | ConnectorList |   |   | Specify the point which is to be projected  
Tolerance | Double |   | The approximate distance of the point from the specified geometry  
Project | Boolean | 0,1 | Specifies whether the point is to be projected on the geometry(1) or not (0)  
  
 

[Top]
#### ![](images/I_MshTranslateP2.gif)**Translation Mesh                                         [_use case_](../CAAScdAniUseCases/CAAAniMeshTranslation.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartTranslation | Direction | ConnectorList |   | Specifies the direction of translation, it must be a line created in GSD workbench  
  | TranslationValue | Double |   | Specifies distance and orientation of translation ( negative value for reverse )  
  | Condensation | Integer | 0 | Decides to not condense the nodes of the transformed and parent mesh part  
  | 1 | Condense the nodes of the transformed and parent mesh part.  
  | 2 | Condense the nodes of transformed mesh part and all the neighboring mesh parts  
  | Tolerance | Double |   | Specifies the tolerance of condensation  
  | NbCopies | Integer |   | Specifies the number of copies  
  
[Top]

![](images/I_MshRotateP2.gif)**Rotation Mesh                                             [_use case_](../CAAScdAniUseCases/CAAAniMeshRotation.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartRotation | Direction | ConnectorList |   | Specifies the direction of translation  
  | RotationValue | Double |   | Lets you select angle of rotation  
  | Condensation | Integer | 0 | Decides to not condense the ndoes of the transformed and parent mesh part  
  | 1 | Condense the nodes of the transformed and parent mesh part.  
  | 2 | Condense the nodes of transformed mesh part and all the neighboring mesh parts  
  | Tolerance | Double |   | Specifies the tolerance of condensation  
  | NbCopies | Integer |   | Specifies the number of copies  
  
[Top]

 

![](images/I_MshSymmetryP2.gif)**Symmetry Mesh                                         [_use case_](../CAAScdAniUseCases/CAAAniMeshSymmetry.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartSymmetry | Direction | ConnectorList |   | Lets you select the plane of symmetry  
  | Condensation | Integer | 0 | Decides to not condense the ndoes of the transformed and parent mesh part  
  | 1 | Condense the nodes of the transformed and parent mesh part.  
  | 2 | Condense the nodes of transformed mesh part and all the neighboring mesh parts  
  | NbCopies | Integer |   | Specifies the number of copies  
  
[Top]

 

![](images/I_MshExtrTranslationP2.gif)**Extrude with Translation                                 [_use case_](../CAAScdAniUseCases/CAAAniMeshExtrudeTrans.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartExtrTranslation | Direction |   |   | Selects the direction of extrusion an axis or a line is specified  
  | Condensation | Integer | 1,2 | If activated, this option lets you condense nodes of the extruded mesh part and other mesh parts with a user-defined tolerance.   
  | Tolerance | Double |   | The user defined tolerance for condensation  
  | Length | Double |   | Minimum distance between the mesh elements and the geometry. Useful for curve-type geometry  
  | Length1 | Double |   | The distance up to which you want to extrude  
Distribution | Type | Integer |   | Type of distribution Uniform Arithmetic Geometric  
NbNodes | Integer |   | Number of layers you want to insert  
Symmetric | Integer |   | Whether the extruded mesh is symmetric(2) or not(1)  
Size1 | Double |   | The sizes of the distribution Arithmetic/Geometric  
Size2 | Double |    
Ratio | Real |   | The ratio of size 1 and size2  
AbsoluteSag | Double |   | Absolute sag value  
RelativeSag | Double |   | Relative sag value  
  
[Top]

![](images/I_MshExtrRotationP2.gif)**Extrude with Rotation                                       [_use case_](../CAAScdAniUseCases/CAAAniMeshExtrudeRot.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartExtrTranslation | Direction |   |   | Specifies the axis of extrusion by rotation.  
  | Angle | Double |   | The starting angle from which you want to extrude. Useful curved geometry  
  | Angle1 | Double |   | The angle up to which you want to extrude  
  | Condensation | Integer | 1,2 | If activated(2), this option lets you condense nodes of the extruded mesh part and other mesh parts with a user-defined tolerance. (1) will deactivate the option  
  | Tolerance | Double |   | The user defined tolerance for condensation  
Distribution | Type | Integer |   | Type of distribution Uniform Arithmetic Geometric  
NbNodes | Integer |   | Number of layers you want to insert  
Symmetric | Integer |   | Whether the extruded mesh is symmetric or not  
Size1 | Double |   | The sizes of the distribution Arithmetic/Geometric  
Size2 | Double |    
Ratio | Real |   | The ratio of size 1 and size2  
AbsoluteSag | Double |   | Absolute sag value  
RelativeSag | Double |   | Relative sag value  
  
 

[Top]

 

![](images/I_MshExtrSymmetryP2.gif)**Extrude with Symmetry                                 [_use case_](../CAAScdAniUseCases/CAAAniMeshExtrudeSymm.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartExtrTranslation | Direction |   |   | Specifies the plane of symmetry.  
  | Condensation | Integer |   | If activated, this option lets you condense nodes of the extruded mesh part and other mesh parts with a user-defined tolerance.   
  | Tolerance | Double |   | The user defined tolerance for condensation  
Distribution | Type | Integer |   | Type of distribution Uniform Arithmetic Geometric  
NbNodes | Integer |   | Number of layers you want to insert  
Symmetric | Integer |   | Whether the extruded mesh is symmetric or not  
Size1 | Double |   | The sizes of the distribution Arithmetic/Geometric  
Size2 | Double |    
Ratio | Real |   | The ratio of size 1 and size2  
AbsoluteSag | Double |   | Absolute sag value  
RelativeSag | Double |   | Relative sag value  
  
[Top]

 

![](images/I_MshExtrSpineP2.gif)**Extrude along a Spine                                 [_use case_](../CAAScdAniUseCases/CAAAniMeshExtrudeSpine.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartExtrSpine | Direction |   |   | Lets you select the direction of extrusion ( spine)  
  | Condensation | Integer | 1,2 | If activated, this option lets you condense nodes of the extruded mesh part and other mesh parts with a user-defined tolerance.   
  | Tolerance | Double |   | The user defined tolerance for condensation  
  | Length | Double |   | Specifies the start value of the extrusion  
  | Length1 | Double |   | Specifies the end value of the extrusion  
  | Point |   |   | Specifies the reference point on the spine for the extrusion.  
By default, the anchor point is the projection on the spine of the center of gravity of the mesh to be extruded  
Distribution | Type | Integer |   | Type of distribution Uniform Arithmetic Geometric  
NbNodes | Integer |   | Number of layers you want to insert  
Symmetric | Integer |   | Whether the extruded mesh is symmetric or not  
Size1 | Double |   | The sizes of the distribution Arithmetic/Geometric  
Size2 | Double |    
Ratio | Real |   | The ratio of size 1 and size2  
AbsoluteSag | Double |   | Absolute sag value  
RelativeSag | Double |   | Relative sag value  
  
[Top]

 

![](images/I_MshCoatingP2.gif)**Coating 1D Mesh                                                             [_use case_](../CAAScdAniUseCases/CAAAniMeshCoating1D.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPart1DCoating | ExtractionType | Integer | 1-6 | Specifies the Type of extraction. All Edges(1), Boundary Edges(2), Internal Edges(3), Constrained Edges(4), Non Constrained Edges(5), None(6)  
**LocalSpecifications** |   |   |   |    
MSHCoatingLocalSpecification | ConnectorList |   |   | Specifies the edges you want to include or exclude  
  | LocalExtractionType | Integer | 1,2 | Specifies whether you want to include (1) or exclude (2) the edge  
  
[Top]

 

![](images/I_MshCoating2DP2.gif)**Coating 2D Mesh                                                             [_use case_](../CAAScdAniUseCases/CAAAniMeshCoating2D.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPart2DCoating | ExtractionType | Integer | 1,2 | Specifies the Type of extraction. Boundary Faces(1), None(2)  
**LocalSpecifications** |   |   |   |    
MSHCoatingLocalSpecification | ConnectorList |   |   | Specifies the faces you want to include or exclude  
  | LocalExtractionType | Integer | 1,2 | Specifies whether you want to include (1) or exclude (2) the edge  
  
[Top]

 

![](images/I_MshWeldSpotP2.gif)**Spot Welding Connection Mesh                             [_use case_](../CAAScdAniUseCases/CAAAniMeshSpotWelding.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartConnWeldSpot | MiddleCombination | Integer |   | Decides how the connection is modeled Rigid(3), Beam(4), rigid-spring-rigid(196867), spring-rigid-spring(66305), Hexahedron(10)  
  | CompatibleMesh | Integer | 1,2 | Decides whether the nodes are created by orthogonally projecting welding points on the mesh parts(2) or not  
  | MaximalGap | Double |   | Specifies the radius value of a sphere which has the welding spot as center. It must be an intersection between each face and the solid thus defined  
  | SpotDiameter | Double |   | Specifies the sport diameter for the hexahedron  
  | StopUpdateOnError | Integer | 1,2 | Stop the update mesh process (2), do not stop(1)  
  
[Top]

 

![](images/I_MshWeldSeamP2.gif)**Seam Welding Connection Mesh                                 [_use case_](../CAAScdAniUseCases/CAAAniMeshSeamWelding.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartConnWeldSeam | MiddleCombination | Integer  |   | Decides how the connection is modeled Contact(2), Rigid, Beam(4), Rigid-Spring-Rigid(196867), Spring-Rigid-Spring(66305), Shell(9), Hexahedron(10)  
  | CompatibleMesh | Integer |   | Decides whether the nodes are created by orthogonally projecting welding points on the mesh parts(2) or not(1)  
  | MaximalGap | Double |   | Specifies the radius value of a sphere which has the welding spot as center. It must be an intersection between each face and the solid thus defined.  
  | MeshStep | Double |   | Specifies the mesh progression along the welding seam  
  | Width | Double |   | Specifies the width of the hexahedron  
  | StopUpdateOnError | Integer | 1,2 | Stop the update mesh process (2), do not stop(1)  
  
[Top]

![](images/I_MshWeldSurfP2.gif)**Surface Welding Connection Mesh                             [_use case_](../CAAScdAniUseCases/CAAAniMeshSurfaceWelding.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartConnWeldSurf | MaximalGap | Double |   | Specifies the radius value of a sphere which has the welding spot as center. It must be an intersection between each face and the solid thus defined.  
  | MeshStep | Double |   | Specifies the mesh progression along the welding seam  
  | StopUpdateOnError | Integer | 1,2 | Stop the update mesh process (2), do not stop(1)  
  | MiddleCombination | Integer | 10 | Decides how the connection is modeled Hexahedron  
  
[Top]

 

![](images/I_MshPointPointP2.gif)**Nodes to Nodes Connection Mesh                             _[ _use case_](../CAAScdAniUseCases/CAAAniMeshNodesToNodesConnection.md)_**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
MSHPartConnPointPoint | MiddleCombination | Integer | 13, 12 | How the connection mesh is modeled Rigid(13), DOF Equal(12)  
  | Tolerance | Double |   | Specifies the distance between nodes to be connected  
  | StopUpdateOnError | Integer |   | Stop the update mesh process (2), do not stop(1)  
  
[Top]

 

![](images/I_MshHalfPointP2.gif)**Node Interface Mesh                                                 [_use case_](../CAAScdAniUseCases/CAAAniMeshNodesInterface.md)**

Mesh Part Name | Attributes Name | Value Type | Legal Values | Meaning  
---|---|---|---|---  
  | MiddleCombination | Integer | 1 | How the mesh is modeled Spring(1)  
  | Tolerance | Double |   | Specifies the distance between nodes to be connected  
  | StopUpdateOnError | Integer | 1, 2 | Stop the update mesh process (2), do not stop(1)  
  
[Top]

 

 

 

[Top]

* * *
### History

Version: **1** [Mar 2001] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
