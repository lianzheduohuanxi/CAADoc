---
```vbscript
title: "The CGM Journal"
category: "use-case"
module: "CAATopTechArticles"
tags: ["CAATopJournal"]
source_file: "Doc/online/CAATopTechArticles/TopoJournal.htm"
converted: "2026-05-11T17:31:50.799285"
```

---
# Geometric Modeler

| 
## Topology

| 
### The CGM Journal

_The Record of the Topological Modifications_  
---|---|---  
Technical Article  

* * *
### Abstract

Topological and geometric operators create new objects from existing ones. The modifications of the topological model can be logged into a journal. This article describes the features of the CGM journal and illustrates with examples of use. The way an operator writes items into the journal greatly influences the applications (such as Generic Naming and Part) that read this journal. It the reason why some examples of use are taken into the field of these applications, although these applications do not belong to the CGM offering. 

  * **Definition**
    * Journal Structure
    * Item Structure
    * Copy or No Copy Mode
  * **Examples of Use**
    * Naming
    * Selection
    * Influence of the Creation or Modification Item Type on the Behavior of an Operator
  * **In Short**
  * **References**

---  

* * *
### Definition

A topological operator operates on topological objects to create new ones. Most of the time, these topological objects are bodies (a body is a set of connected (or not) volumes, faces, edges and vertices, see [1]). It never modifies the input bodies: the resulting body is a new one, but it can share cells with the input bodies, if they are not modified by the operation. This is called the smart concept (see [2]). On request, the operator can describe the way to go from the initial objects, to the resulting body. This information is then put by each operator into a CGM journal.

A topological operator operates on topological objects to create new ones. Most of the time, these topological objects are bodies (a body is a set of connected (or not) volumes, faces, edges and vertices, see [1]). It never modifies the input bodies: the resulting body is a new one, but it can share cells with the input bodies, if they are not modified by the operation. This is called the smart concept (see [2]). On request, the operator can describe the way to go from the initial objects, to the resulting body. This information is then put by each operator into a CGM journal.
The CGM journal records the creation, modification and deletion of the faces, free edges and free vertices of topological objects. A free edge is an edge bounding at most one face, and a free vertex is a vertex bounding at most one edge. In fact, it is sufficient to follow the modifications of these cells to know how the whole body has been modified. The journal is attached to any topological or geometric operators that operate on topological objects.

The CGM journal is transient. You have to create it before its use and delete it when you have finished. It is possible to compress it to easy its reading.

In addition to this article, you can find a dedicated use case [3], that illustrates the way to read the journal.

[Top]
#### Journal Structure

The CGM journal is built as a composite pattern: a journal is a hierarchy of 

  * **item** s, that are the leaves, and
  * **list** s of lists and items.

Fig. 1: The composite structure of the journal ![TopoJournal1.gif \(3006 bytes\)](images/TopoJournal1.gif) | A journal is composed of items and lists of items  
---|---  

[Top]
#### Item Structure

An item is an elementary line of a journal, describing what happens for a given cell. 

  * Each item has a type:  

An item is an elementary line of a journal, describing what happens for a given cell.
Creation
    A new cell appears in the resulting body, built from an (optional) set of cells of the input body.
Deletion
    The cell disappears in the resulting body.
Modification
    The cell that is used do not appear in the resulting body, and is replaced by a new one.
Subdivision
    Kind of modification where the cell is cut in several parts that appear in the resulting body.
Absorption
    Kind of modification where several cells are merged in the resulting body.

  * An item points to the topological cells of the input bodies that have been modified, if any: in case of an absorption, several cells can be merged.
  * An item points to the resulting topological cells: in case of a subdivision, several cells can appear.
  * An item offers a field for an optional information, used by each operator to give additional details. This can be, as examples, the ribbon number for a fillet surface or the type of face (bottom, top, lateral) for a prism. Each operator publishes the way it uses the optional information.

Fig. 2: Examples of journal items ![TopoJournal2.gif \(4713 bytes\)](images/TopoJournal2.gif) | The subtraction operator of the pocket from the pad splits the face C1 of the pad into the faces D1 and D5.  
The face C3 of the pad is modified and becomes D3.  
The face F1 of the pocket to be subtracted is modified and becomes the face D6 of the result.  
The face F8 disappears in the result.  

The face C3 of the pad is modified and becomes D3.
The face F1 of the pocket to be subtracted is modified and becomes the face D6 of the result.
The face F8 disappears in the result.
To clearly understand the difference between the creation and modification type, let us take an example.

Fig. 2bis: Modification and creation items ![TopoJournal7.gif \(5699 bytes\)](images/TopoJournal7.gif) |  Imagine you first put a color attribute (red for exemple) on the face C1 of the initial Pad. After the pocket subtraction, you want that the faces D1 and D5 still have this red color. That is the meaning of the modification type.   Imagine now you have put a color on the curve C1 of the profile. You do not want that the faces F1, F5 and F6 still keeps this color: in fact, what could be the color of the face F5 and F6 if C1 were red and C2 were blue? That is the meaning of the creation item.  

```vbscript
For each operator, the choice of the creation or modification type has been designed according to the needs of the applications.

```

[Top]
#### Copy or No Copy Mode

The copy or no copy mode is a default that the operator takes about the writing of its journal. Take an empty journal as an input of an operator for which you have asked to fill it. 

  * With the copy mode, the operator supposes that all the cells of the input bodies are in the resulting body. Let us consider the boolean union of two bodies, such that their intersection is empty. After such an union, if the union operator is in copy mode (and it fact, it is the way it does), nothing is written into the journal: according to the copy mode, all the cells are renewed by default, and none of them are modified. because the particular position of the two bodies.
  * With the no copy mode, the operator supposes that none of the cells of the input bodies are in the resulting body. If you take the same union of the two non intersecting bodies and if the union operator worked in no copy mode, there would be as many creation item as there are faces, free vertices and edges in the two initial bodies.

This mode also has an influence on the item types that an operator uses to write its items. In fact, in case of copy mode, the operator writes, in general, more modification item type than it does in case of no copy mode. In case of no copy mode, on the contrary, it uses more creation items. The copy and no-copy mode as well as the detailed items is published by each operator.

[Top]
### Examples of Use

We first describe the use of the topological journal for the object naming. Then, we illustrate its use for the selection. The last part discusses on the behavior differences between the creation and modification types. The journal is written for the applications. It is the reason why these exemples are taken in the field of applications to do not belong to the CGM offering.

[Top]
#### Naming

We first describe the use of the topological journal for the object naming. Then, we illustrate its use for the selection. The last part discusses on the behavior differences between the creation and modification types. The journal is written for the applications. It is the reason why these exemples are taken in the field of applications to do not belong to the CGM offering.
The CGM journal makes it possible to build a logical identifier on the generated cells.

Imagine that each curve of a profile has a logical name such as `Curve1`, ..., `CurveN`. Now, extrude the profile along a direction to build a pad. The resulting face of the extrusion of the i-th curve of the profile can be named, using the information of the corresponding topological operation, as `Pad1_Lateral_From_CurveI`.

Now, the user changes the definition of `Curve_I` (a circle radius, or replaces the curve), but keeps it attached to the same label `Curve_I`. If the prism operation is replayed, the result changes but all the logical names remain the same. All information attached to a logical name is still available on the new resulting body.

This principle is used by the Generic Naming to label the objects. In turn, the object names are used by the feature applications to record the order of the different topological operations. This is a main difference between the CGM modeler and the Feature modeler: the Feature modeler records the history of the operations, whereas the CGM modeler gives a transient information at the run of the operator.

Fig. 3: Use of the journal for the naming ![TopoJournal3.gif \(5047 bytes\)](images/TopoJournal3.gif) | Following the items of the topological journal, the generic naming is able to propose logical names, such that a modification of a physical object (C2) attach to a logical name (`Curve_2`) does not modify the logical names of the derived objects (`Pad1_lateral_From_Curve_2`). Information attached to the logical objects are then stable if the operations are replayed in the same order.  

[Top]
#### Selection

Take the pad of Fig. 3 and split it by a plane as on Fig. 4. It is possible to explore the CGM journal and go back from the last created face G2 to the initial face of the Pad that has been modified. It is then possible to have a way of selection which leads to the selection of the initial Pad, by selecting a face of another topological object that has been build from this Pad, which is useful when you want to modify a parameter of the initial prism.

Fig. 4: Use of the journal for the selection ![TopoJournal4.gif \(4415 bytes\)](images/TopoJournal4.gif) | Exploring the CGM journal makes it possible to go back from G2 to F2, and then select the initial Pad (and not the resulting body)  
---|---  

[Top]
#### Influence of the Creation or Modification Item Type on the Behavior of an Operator

On the CGM point on view, the choice of the creation or modification type could have been arbitrary done. Now, this type acts on the behavior of the operator, when it is replayed in a context of an application using the naming, such as the mechanical modeler. So, the type has been chosen to lead to a behavior as close as possible to the expectations of the applications.

Fig. 5: Influence of the creation or modification type: case of a pocket operation ![TopoJournal5.gif \(8379 bytes\)](images/TopoJournal5.gif) | Take first a pad, and fillet one of its edge. The faces H1 and H2 come from the modification of F1 and F2. Now, insert a pocket operation just before the fillet operation, and replay the operations: pad, pocket, fillet * If the faces G1, G2 and G3 were stamped as created, it were not possible to go back to the initial faces, and the edges are not filleted. This behavior is not desired by the application, it is the reason why this choice is not taken for a Boolean operation. * On the contrary, if the faces G1, G2 and G3 are stamped as modified, it is possible to go back to the initial faces F1 and F2, and then filleting all the edges having F1 and F2 as ancestors.  
---|---  

On the CGM point on view, the choice of the creation or modification type could have been arbitrary done. Now, this type acts on the behavior of the operator, when it is replayed in a context of an application using the naming, such as the mechanical modeler. So, the type has been chosen to lead to a behavior as close as possible to the expectations of the applications.
Fig. 5: Influence of the creation or modification type: case of a pocket operation ![TopoJournal5.gif \(8379 bytes\)](images/TopoJournal5.gif) | Take first a pad, and fillet one of its edge. The faces H1 and H2 come from the modification of F1 and F2. Now, insert a pocket operation just before the fillet operation, and replay the operations: pad, pocket, fillet * If the faces G1, G2 and G3 were stamped as created, it were not possible to go back to the initial faces, and the edges are not filleted. This behavior is not desired by the application, it is the reason why this choice is not taken for a Boolean operation. * On the contrary, if the faces G1, G2 and G3 are stamped as modified, it is possible to go back to the initial faces F1 and F2, and then filleting all the edges having F1 and F2 as ancestors.
In this case, the application wants to keep the filleting of the resulting edges, so that the pocket operation (a Boolean subtraction) stamped the faces as modified. On the contrary, a shell operation is an example of creation mode.

Fig. 6: Influence of the creation or modification type: case of a shell operation ![TopoJournal6.gif \(4372 bytes\)](images/TopoJournal6.gif) | Take the filleted Pad of the preceeding example, and insert a shell operation instead of a pocket operation. The balloon shows how the shell operator operates: it blows the initial faces (such as F2) with a distance e1, leading to new faces (such as J2), and also shrinks the initial faces with a distance e2, leading to new faces (such as K2) * If the faces J2 and K2 were stamped as modified from the face F2, the fillet operator would fillet them both, leading to potential impossible configurations. Moreover, it is not what is expected by the applications in this case. * So, the operator stamps them as created. The fillet operation is not replayed. If the user wants to have the face J2 filleted, it has to run a new fillet operation.  

In this case, the application wants to keep the filleting of the resulting edges, so that the pocket operation (a Boolean subtraction) stamped the faces as modified. On the contrary, a shell operation is an example of creation mode.
Fig. 6: Influence of the creation or modification type: case of a shell operation ![TopoJournal6.gif \(4372 bytes\)](images/TopoJournal6.gif) | Take the filleted Pad of the preceeding example, and insert a shell operation instead of a pocket operation. The balloon shows how the shell operator operates: it blows the initial faces (such as F2) with a distance e1, leading to new faces (such as J2), and also shrinks the initial faces with a distance e2, leading to new faces (such as K2) * If the faces J2 and K2 were stamped as modified from the face F2, the fillet operator would fillet them both, leading to potential impossible configurations. Moreover, it is not what is expected by the applications in this case. * So, the operator stamps them as created. The fillet operation is not replayed. If the user wants to have the face J2 filleted, it has to run a new fillet operation.
The creation or modification type modifies the behavior of the operator when it is replayed on a slightly different configuration.

[Top]

* * *
### In Short

  * The CGM journal allows applications to record the topological modifications of faces and free edges and vertices during geometric or topological operations.
  * The CGM journal is built as a composite pattern, whose leaves are the items. Each item has a type, detailing if the cell has been created, modified or deleted.
  * Each operator publishes the way it writes items.

[Top]

* * *
### References

[1] | [Topology Concepts](../CAATobTechArticles/TopoConcepts.md)  
---|---  
[2] | [The CGM Topological Model](../CAATobTechArticles/TopoModel.md)  
[3] | [The CAATopJournal Use Case](../CAATopUseCases/CAATopJournal.md)  
[Top]  

* * *
### History

Version: **1** [Mar 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
