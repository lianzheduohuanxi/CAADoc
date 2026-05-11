---
title: "Topological Journal Methodology"
category: "use-case"
module: "CAATopTechArticles"
tags: ["CAACheckForPart", "CAATopCheckGnOK", "CATIBRepAccess", "CAATopJournal", "CAATopCheckForPart", "CATIA", "CAATopCheckGnKO", "CAATopDumpJournal", "CATIMfProcReport", "CAACheck", "CAATopologicalOperators"]
source_file: "Doc/online/CAATopTechArticles/JournalMethodology.md"
converted: "2026-05-11T17:31:50.785311"
---
# Geometric Modeler

| 
## Topology

| 
### Topological Journal Methodology

_Tips and tricks to create a journal_  
---|---|---  
Technical Article  
  
* * *
### Abstract

This article is intended for those of you who have to create a topological journal. A journal must comply with a set of rules otherwise it is invalid. The usual symptom revealing an invalid journal is a non appropriate selectability of cells. This problem is related to the naming mechanism of BRep features which relies on the topological journal. This article explains why in some cases a journal can be invalid and what you have to do to fix it.

  * **Topology and Generic Naming**
  * **The Topological Journal Description**
    * The Type of Events
      * Creation
      * Modification
      * Deletion
      * Subdivision
      * Absorption
      * Keep
    * The Cells Referred to in the Report
      * The Types of Cells
      * The Backtracked Cells
    * The Additional Information
    * The Journal Operands
      * The Copy/No Copy Mode
  * **An Example from the CAA Forum**
    * The Code Steps
    * The Default Journal
    * The Selectability Problems
    * The Preliminary Diagnosis
    * The Solution
    * Tips to Create a New Journal
  * **Checking Your Journal**
    * Preliminary Operations
      * The Tass Operation
      * Dumping your Journal
    * The CAACheck Operation
      * The Rules to be Checked
      * The Generated Files
      * The ERRORS and WARNINGS

  
---  
  
* * *
### Topology and Generic Naming

In CATIA Version 5, a feature cannot refer directly to the topology that is used to specify it. The reason for this, is that the topology as well as the geometry can be deleted and rebuilt during the Update operation. Suppose you create a prism by extruding a simple spline. The spline is assigned a tag as well as the resulting cells of the prism. Modify the spline and update the prism, the tags will all be modified. To sort out this problem, a stable way to refer to parent objects was to be found. The generic naming is a description of the history of a cell that gets rid of tags and is stable when a feature is updated. 

When you move the mouse cursor over a geometric object or select it interactively, CATIA creates a selection object (CATIBRepAccess). These CATIBRepAccess objects are not persistent, they are deleted whenever the document is updated. To keep trace of these objects, CATIA uses specific features called BRep features that store stable labels describing the topology. The generic name of a cell is constructed by reading the a "graph" that describes the Parent-Children links between the cells of different bodies. Building this graph requires information which is provided in the topological journal and is under the responsibility of CGM operators. For more information, take a look at the "Generic Naming Overview" article (Mechanical Modeler).

In brief, a cell name looks something like this: "Cell dimension + Parent feature + Additional information". Keeping this in mind will help you understand the journal naming rules. 

[Top]
### The CGM Journal Description
#### The Types of Events

The only valid types of orders that can appear in a journal are the:

  * Creation
  * Modification
  * Deletion
  * Subdivision
  * Absorption
  * and Keep orders.

##### The Creation Order (CATCGMEvent::Creation)

This order notifies that a new cell has been created. A new cell can be created from scratch or from one or several cells. An additional information intended to differentiate the cells can be added to a Creation order. In the example below, "info 0" is used to differentiate the side faces, "info 1" is used to specify a bottom face and "info 2" characterizes a top face. 

**_Input body_** | **_Resulting body (After CATTopPrism)_**  
---|---  

**_Report_**  
`[Edge_1]->Creation[Face_C] info = 0  
[Edge_2]->Creation[Face_D] info = 0  
[Edge_3]->Creation[Face_E] info = 0  
[Edge_4]->Creation[Face_F] info = 0  
[Face_1]->Creation[Face_A] info = 1  
[Face_1]->Creation[Face_B] info = 2`  
##### The Modification Order (CATCGMJournal::Modification)

This order notifies that a given cell is the result of a modification of an input cell. The Modification order is to be used whenever the geometry is re-used with different limitations. Except in very few cases, a Modification order should have no additional information.

**_Input Body_** | **_Resulting Body (After CATDynFillet)_**  
---|---  

**_Report_**  
`[Face_1]->Modification[Face_A]  
[Face_1],[Face_2]->Creation[Face_C]  
[Face_2]->Modification[Face_B]  
[Face_3]->Modification[Face_D]  
[Face_4]->Modification[Face_E]`  
##### The Deletion Order (CATCGMJournal::Deletion)

This order notifies that a given cell belonging to an input body in Copy Mode is to be deleted in the result body.

**_Input bodies_** | **_Resulting body (After CATHybSplit)_**  
---|---  

**_Report_**  
`[Face_1, Edge_1] -Creation -> [Vertex_A]  
[Vertex_1] -Deletion  
[Edge_1] -Modification -> [Edge_A]`  
##### The Subdivision Order (CATCGMJournal::Subdivision)

This order is a particular type of Modification that notifies that one cell of an input body in Copy Mode is modified into two or more cells into the resulting body.

**_Input bodies_** | **_Resulting body (After CATHybSplit)_**  
---|---  

**_Report_**  
`[Edge_1, Edge_2] -Creation -> [Vertex_B]  
[Edge_1, Edge_3] -Creation -> [Vertex_A]  
[Edge_1] -Subdivision -> [Edge_A, Edge_B]`  
##### 
##### The Absorption Order (CATCGMJournal::Absorption)

This order is a particular type of Modification that notifies that two or more cells of an input body in Copy Mode are merged into one cell into the resulting body.

**_Input bodies_** | **_Resulting body (After CATDynBoolean Add)_**  
---|---  

**_Report_**  
`[Face_5] -Modification -> [Face_B]  
[Face_6] -Deletion  
[Face_8] -Modification -> [Face_F]  
[Face_2] -Modification -> [Face_E]  
[Face_3] -Modification -> [Face_D]  
[Face_4] -Modification -> [Face_C]  
[Face_1, Face_7] -Absorption -> [Face_A]`  
  
Note: In the figure above, Face_6 relies on Face_8. Face_8 is modified and becomes Face_F after the split operation while Face_6 is deleted.
##### The Keep Order (CATCGMJournal::Keep)

This order specifies that a cell belonging to an input body in No Copy mode is reused in the resulting body. The CAACheck operation issues a warning whenever a cell belonging to an input body in Copy mode is declared as kept in the journal.

In the example below, the CATHybBoundary operator generates a body that shares the bording edges with the input body which is in No Copy mode.

**_Input Body_** | **_Resulting Body (After CATHybBoundary)_**  
---|---  

**_Report_**  
`[Edge_1]->Keep  
[Edge_2]->Keep  
[Edge_3]->Keep  
[Edge_4]->Keep`  
#### The Cells Referred to in the Report
##### The Types of Cells

Only CATFace, CATEdge and CATVertex objects should be referred to in the journal. To date, operators taking geometry as an argument generate journals with geometry as parent objects in orders. These operators should be considered as exceptions. It is recommended that CAA developers should not build journals reporting geometry.
##### The Backtracked Cells

Only bording cells are backtracked in a journal. In summary:

  * if the result is a solid, the journal should report only events that affect the faces of the result
  * if the result is a shell, the journal should report only events that affect the faces of the result as well as the bording edges of the shell.
  * if the result is a wire, the journal should report only events that affect the edges and the end vertices.
  * if the result is a vertex, the journal should report only events affecting the vertex.

#### The Information
##### The purpose of an information

An information is a means to differentiate cells that have different dimensions and same parent features. A simple example is the circular cylinder. You cannot select the semi-cylindrical faces one-by-one because they carry the same name.

**_Input body: two edges  
_**![](images/sketchinit.jpg) 
---|---  
![](images/cylinderFace1.jpg)  
**_Sketch Report (closed conic) Both edges carry the same name_**  
---  
`[] -Creation -> [Edge_1]  
[] -Creation -> [Edge_2]`  
**_Prism report - Face_C and Face_D cannot be differentiated_**  
`[] -Creation -> [Face_B] Info=2  
[] -Creation -> [Face_A] Info=1  
[Edge_1] -Creation -> [Face_D] Info=0  
[Edge_2] -Creation -> [Face_C] Info=0`  
##### Information in standard operators

In standard operators, the value assigned to an "information" generally complies with the rule below:

  * _**Info = 1**_  
Denotes a starting cell.  
Examples:  
      Starting/initial vertex of the helix created by CATCreateTopHelix.  
      Starting edge of an extruded surface (CATTopExtrude).  
      Starting/Bottom face of a pad.

  * **_Info = 2_**  
Denotes an ending cell.  
Examples:  
      Ending vertex of the helix created by CATCreateTopHelix.  
      Ending edge of an extruded surface (CATTopExtrude).  
      Top face of a pad.

  * **_Info = 0_**  
Denotes a lateral cell.  
Examples:  
       Lateral edges for a sweep.  
       Lateral faces for a pad.

Rules related to additional information:

  * The same info should not be used to name cells of different dimensions.
  * After an update, an info will not switch to a cell of different dimension.
  * Stick as long as it is possible to the info values already used for standard operators.

[Top]
#### The Journal Operands

The journal operands are the bodies that are used as input data in your operator. You have to declare these operands whenever you carry out a check operation as well as in CATIMfProcReport::StoreProcReport method.
##### The Copy/ No Copy Mode

Stating that an input body is in a Copy/No Copy mode is a strategy to reduce the number of orders in a journal. For a given operator, an input body (the operand of the operator) must be either in Copy or in No Copy Mode.

When an input body is declared as in Copy mode, it is assumed that all its cells are in the resulting body after the operation except those reported as deleted by a Deletion order and those modified. Each unmodified cell is included in the resulting body.

When an input body is declared as in No Copy mode, it is assumed that none of its cells is in the resulting body except those specified as kept by a Keep order. Stating that an operand is in Copy or No Copy mode has an impact on the topological journal and its validity.

When do you have to specify the Copy/No Copy Mode of an Operand ?

  1. when you check your journal, this is done by using the CAACheckForPart::AddInputBody method.
  2. when you store the report (CATIMfProcReport::StoreProcReport).

What are the specification criteria for the Copy/No Copy Mode?

`No Copy` is to be used whenever there are no cell or few cells of the operand in the resulting body. `Copy` is to be used when a large number of cells providing from the operand exist in the resulting body. For example: if you split a shell by a another shell, the cutting shell is in No Copy mode while the split shell is in Copy mode. Note that you may be induced to create operators with operands having a different Copy/No Copy mode depending on the options of the operator. This is the case for the CATTopCorner standard operator.

**_The CATTopCorner Example_**

| **_Resulting Body_**  
---|---  
**_Input bodies: two wires and a support  

![](images/CornerTrimming.jpg)  
**_Report without trimming  
Support: No Copy - Wires: No Copy_**  
`[Edge_1, Edge_2, Face_1] -Creation -> [Edge_A]  
[] -Creation -> [Vertex_A] Info=1  
[] -Creation -> [Vertex_B] Info=2`  
**_Report with trimming  
Support: No Copy - Wires: Copy_**  
`[Vertex_2] -Deletion  
[Vertex_3] -Deletion  
[Edge_1, Edge_2, Face_1] -Creation -> [Edge_A]  
[Edge_1] -Modification -> [Edge_B]  
[Edge_2] -Modification -> [Edge_C]  
[Vertex_1] -Modification -> [Vertex_D]  
[Vertex_4] -Modification -> [Vertex_E]`  
  
[Top]
### An Example from the CAA Forum

Here above is a case that has been submitted through the CAA Forum by a developer creating a prism from an extruded skin.
#### The Code Steps

  * Input specification (sp_IN) attribute: the initial sketch
  * Topological operations carried out in the feature build: CATTopSkin to create the skin to be extruded, CATTopPrism to extrude the skin.

#### The Default Journal for the Topological Operations after the Tass Call

If you dump the journal on the standard output, you obtain something like this:

`[PLine_a, PLine_b, PLine_c, PLine_d] -Creation -> [Face_bottom] Info=1  
[PLine_a, PLine_b, PLine_c, PLine_d] -Creation -> [Face_skin]  
[PLine_d, PLine_c, PLine_b, PLine_a] -Creation -> [Face_top] Info=2  
[PLine_a] -Creation -> [Edge1_skin]  
[PLine_a] -Creation -> [Face1_lateral] Info=0  
[PLine_b] -Creation -> [Edge2_skin]  
[PLine_b] -Creation -> [Face2_lateral] Info=0  
[PLine_c] -Creation -> [Edge3_skin]  
[PLine_c] -Creation -> [Face3_lateral] Info=0  
[PLine_d] -Creation -> [Edge4_skin]  
[PLine_d] -Creation -> [Face4_lateral] Info=0`  
---  
#### The Selectability Problems

The customer complains because the faces of a prism generated from a sketch are not selectable one-by-one. Actually, the top and the bottom faces are selectable but not the lateral faces. Selecting one of the lateral faces highlights all the lateral faces.
#### The Preliminary Diagnosis

All the report events are ignored by the naming mechanism because there are geometric elements (PLines) in the report. You cannot help this when using the CATTopSkin and CATTopPrism operators as both operators take geometry as their input arguments. The initial geometry re-appears in the report. If you pass this default journal to the CATIMfProcReport, you won't be able to differentiate any face at selection. It is like having an empty journal.

The journal checking results in a KO verdict. The warning file tells you there are cells of the resulting body that cannot be traced back.
#### The Solution

The remedy to this invalid default journal consists in creating a valid journal to be passed to CATIMfProcReport. In the journal below, you specify that the lateral faces of the prism are created from the sketch edges (the input specification). It is not mandatory to specify info=0 for the lateral faces but it is recommended as, further on in your application, you may need a key to distinguish the faces in the extrusion direction from the top/bottom ones. This journal is valid because all the cells of the resulting body can be traced back and they all have a different name.

`[Edge1_sketch] -Creation -> [Face1_lateral] Info=0  
[Edge2_sketch] -Creation -> [Face2_lateral] Info=0  
[Edge3_sketch] -Creation -> [Face3_lateral] Info=0  
[Edge4_sketch] -Creation -> [Face4_lateral] Info=0  
[] -Creation -> [Face_top] Info=2  
[] -Creation -> [Face_bottom] Info=1`  
---  
#### Tips to Create a New Journal

Dump the default one (CAATopDumpJournal if you want to dump the journal on the standard output). Dumping the journal allows you retrieve all pieces of information to be re-injected in the journal to be created. Taking a look at the default journal above (the one invalid), the lateral faces appear in the journal and can be retrieved by scanning all the constructed objects with info=0.

Check the default journal - the verdict and warning file give clues about why your journal is invalid. In the example above, the default journal is obviously invalid for all events. In most cases you have to look for the non-backtracked cells as well as the cells that are not properly named. The data files resulting from the check help you find out the disorders in the journal and fix them if need be.

Suppose you are mistaken and create a new journal with the skin edges as parents of the lateral faces instead of the sketch edges, the created journal will be invalid and the lateral faces will be non backtracked (the operand is the sketch and not the skin). In this case, you won't be able to differentiate the lateral faces at selection.

[Top]
### Checking your Journal
#### Preliminary Operations

Prior to checking a journal, you must tass it. This operation is explained below.
##### The Tass Operation

When you chain operators within the same CATTopData, the resulting journal is made up of several CATCGMJournalList which are nested into each other. In this case, the journal items are arranged according to a hierarchy in which the first journal generated in the application is the one which is at the top of the hierarchy and includes all the others. The journal which is in the heart of the structure contains the events that defines how the cells of the resulting body are constructed.

The Tass operation allows you to concatenate under a single level all the journal items and simplify the journal by removing intermediate cells. This operation is required when you have to check your journal. If things work properly in term of selectability and update, it is not required to tass the journal prior to passing it to the CATIMfProcReport - it is automatically tassed by the naming mechanism. The Tass operation performs a certain number of operations. Some of them are given below to help you understand how things work. Beware that it is not a comprehensive list.

Suppose you are chaining two operators, the first operator produces a journal with the `A-Creation->B `order, while the second operator yields a journal with the `B-Creation` `->`C order. After the Tass operation you will only have A->Creation C in the journal. C must belong to the body resulting from the chaining of operations 1 and 2 and A belongs to one of the input bodies.

_**Examples of rules (to name but a few)**_

The initial set of events | is replaced with  
---|---  
`A-Modification->B  
C-Creation->B` | `C-Creation->B (`the creation order prevails`)`  
`A-Modification->B info 1  
B-Modification->C info 2` | `A-Modification->C info 2`  
`A-Modification->B  
B->Deletion` | `A->Deletion`  
  
`A-Modification->B info1  
C-Creation->D info2  
B, D-Creation->E info3` | `A-Modification->B info1  
C-Creation->D info2  
A, C-Creation->E info1`  
`A-Creation->A  
A-Modification->B` | `[A]-Modification->B`  
`A-Creation->B info 1  
B-Modification->C info 2` | `A->Creation->C info 1 if info 1 not NULL  
A->Creation->C info 2 if info 1 == NULL  
`The info on the creation order prevails as long as it is not NULL.  
  
[Top]
##### Dumping the journal

To display a journal on the standard output, you can use the CAATopDumpJournal use case (CAATopologicalOperators.edu). This use case can be customized by those of you who want to modify or re-arrange the format of the orders.
#### The CAACheck Operation

To check the journal, you must use the CAATopCheckForPart use case (CAATopologicalOperators.edu).
##### The Generated Files

The CAATopCheckForPart use case generates two files:

  1. the **_verdict_** file (argument four of the CAATopCheckForPart constructor) 

This verdict file informs you about whether the journal to be checked is valid or invalid.

A - If you ask for a detailed verdict file (argument six set to TRUE), the verdict is given for each category of rules to be checked. The verdict file looks something like this

`Checking MyFeature  
  
(1) - Mandatory  
Checking that all cells in result body can be traced back  
KO  
  
(2)  
Checking that all reported cells are of CATFace/CATEdge/CATVertex type  
OK  
  
(3)  
Checking that all reported cells are bording cells  
OK  
  
(4)  
Checking that cells with same parents & infos are not of different type  
KO  
  
TOPOLOGICAL JOURNAL  
[Edge_27]->Creation[Face_44] Info=1  
[Edge_27]->Creation[Edge_53] Info=1  
[Edge_27]->Creation[Edge_52] Info=2  
[Vertex_25]->Creation[Edge_46] Info=4  
[Vertex_26]->Creation[Edge_49] Info=3``  
  
TOPOLOGICAL JOURNAL FOR FEATURE MyFeature KO`  
---  
  
The journal is displayed at the end of the verdict file only when the verdict is KO.

B - If the argument six is set to FALSE, you will only get a restricted verdict file:

`Checking MyFeature  
  
TOPOLOGICAL JOURNAL FOR FEATURE MyFeature KO`  
---  
  
  2. The detail file provides you with:  

     * more information on the ERRORS and possible WARNINGS.
     * the list of cells in the resulting body as well as in the operands.

You get something like this:

`Checking MyFeature  
  
  
DETAILED LIST OF ERRORS AND WARNINGS  
  
*  
ERROR  
In  
[Edge_27]->Creation[Face_44] Info=1  
and  
[Edge_27]->Creation[Edge_53] Info=1  
Cells with same parents and infos must not be of different type  
*  
  
ERROR  
Cells in Copy mode not in the result body and not deleted  
27 25 26  
  
List of Bodies in Copy Mode  
Body 28 - List of cells: 27 25 26  
  
List of Bodies in No Copy Mode  
  
Body Result  
Body 29 - List of cells: 44 46 52 49 53  
  
TOPOLOGICAL JOURNAL FOR FEATURE MyFeature KO`  
---  

[Top]
##### The ERRORS and WARNINGS

`WARNING  
_Cell_x_ is not a bording cell - The order is ignored`  
---  
This message is displayed along with the order which refers to the non bording cell and is issued whenever a reported cell is not a bording cell, no matter it is a parent cell or a created/modified cell. The order containing such a cell is simply ignored. Such a warning may or may not impede the journal validity. If there are other orders that allow a resulting cell to be backtracked, the journal can be valid. This warning is always associated with a KO result in the Step 3 ("`Checking that all reported cells are bording cells")`of the Verdict file.  
`WARNING  
_Cell_x_ is not a CATFace, a CATEdge or a CATVertex - The order is ignored`  
This message is displayed along with the order which refers to the invalid object and issued whenever a reported cell is not a CATFace, a CATEdge or a CATVertex, no matter it is a parent cell or a created/modified cell. The order containing such a cell is simply ignored. Such a warning may or may not impede the journal validity. If there are other orders that allow a resulting cell to be backtracked, the journal can be valid. This warning is always associated with a KO result in the Step 2 ("`Checking that all reported cells are of CATFace/CATEdge/CATVertex type")`of the Verdict file.  
`WARNING  
The following cells are not bording cells`  
Provides you with the **list** of cells that are not bording cells. Orders referring to such objects can potentially be the cause of an invalid journal. Either the order is useless and it is better to remove it from the journal, or it impedes the backtracking of a cell belonging to the resulting body.  
`WARNING  
The following objects are not of CATFace/CATEdge/CATVertex type.`  
Provides you with a **list** of objects that are geometry or not appropriate topological objects. Orders referring to such objects can potentially be the cause of an invalid journal. Either the order is useless and it is better to remove it from the journal, or it impedes the backtracking of a cell belonging to the resulting body.  
`WARNING  
_Cell_x_ does not belong to any input body in No Copy mode`  
This warning applies to Keep orders. This message is displayed along with the order which refers to the kept cell. A cell is to be specified as kept when it is intended to be found in the resulting body while it belongs originally to a body in No Copy mode. If a cell is stated as kept while it does not belong to a body in No Copy mode, the order is meaningless and it is ignored.  
`ERROR  
In  
[Edge_27]->Creation[Face_44] Info=1  
and  
[Edge_27]->Creation[Edge_53] Info=1  
Cells with same parents and infos must not be of different type`  
The error above will not result in an invalid journal (in other words, if there are no other errors, the return value of the CAACheck method will be 0). Nevertheless, you must do your best to avoid such a message. This message is only displayed when related orders are not ignored . For more information, see the CAATopCheckGnKO.m and CAATopCheckGnOK.m use cases (CAATopologicalOperators.edu). They both illustrate how to create a journal in which naming rules are or are not satisfied.  
`ERROR`  
`Cells of the result body that cannot be traced back`  
`48  
52`  
Provides you with the list of all the cells that cannot be traced back. This message is associated with KO in Step1 of the verdict file.  
`ERROR`  
`Cells in Copy mode not in the result body and not deleted.`  
Provides you with the list of all the cells that are in Copy mode but not in the resulting body and not deleted OR not modified. Is associated with KO in Step1 of the verdict file.  
  
[Top]  

##### The rules to be Checked

The rules to be checked are divided into four categories which are summarized below:

1 - Any cell belonging to the resulting body must be backtracked

A cell is backtracked if its parents belong to the input bodies specified as the operator inputs. The check result depends on the Copy/NoCopy mode of the operands. This Copy/NoCopy mode must be specified prior to running the Check operation. For example: if a cell belonging to the resulting body does not appear as created/modified in the journal, it is expected to belong to an input body in Copy mode, otherwise, it is not backtracked and the resulting journal is invalid. If a cell belonging to an input body in Copy mode is not in the result it must be explicitly deleted in the journal.

If this criteria is not fulfilled, the journal is invalid.

2 - Checking that all the reported cells are of CATFace/CATEdge/CATVertex type

Normally, all the cells reported in the journal should be topological cells of CATFace/CATEdge/CATVertex type. If the Check operation detects an invalid cell, the order is ignored. This may or may not result in an invalid journal. If there are other orders in the journal that make possible the backtracking of the resulting cell, the journal will not be invalid.

Whatever the check result, the Check operation warns you about wrong-type objects (unauthorized type).

Note: Standard operators that take geometry as input data (CATTopwire for example) yield journals that exhibit geometry. This is an exception.

3 - Only bording cells are backtracked.

Normally, all the cells appearing either as parents or created/constructed objects should be bording cells. If the Check operation detects a non-bording cell as a parent of a resulting cell, this parent cell will not be used for the backtracking (the order will be ignored). This may or may not result in an invalid journal. If there are other orders in the journal that make possible the backtracking of the resulting cell, the journal will not be invalid. Otherwise it will be invalid, because the order in which the non-bording cell appears is ignored.

4- Cells with same parents and infos must not be of different type

The couple of orders below (not ignored):

`[]->Creation [Edge_1] info=1  
[]->Creation [Face_1] info=1`

will result into an error because the naming mechanism will not be able to differentiate `[Edge_1]`and `[Face_1].`

The couple of orders below is fine with respect to the Check operation because the naming mechanism manages to detect adjacent faces and makes possible the differentiation of the adjacent cells at selection.

`[]->Creation [Face_1] info=1  
[]->Creation [Face_2] info=1`

[Top]

* * *
### In Short

The topological journal is used by the generic naming mechanism. Whenever you create your own operator, you must check your journal. Potential errors left in a journal may result in selectability problem.

[Top]

* * *
### References

[1] | [Topology Concepts](../CAATobTechArticles/TopoConcepts.md)  
---|---  
[2] | [The CGM Topological Model](../CAATobTechArticles/TopoModel.md)  
[3] | [The CGM Journal](TopoJournal.md)  
[4] | [The CAATopJournal Use Case](../CAATopUseCases/CAATopJournal.md)  
[Top]  
  
* * *
### History

Version: **1** [Mar 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
