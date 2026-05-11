---
title: "Drafting Modeler Overview"
category: "general"
module: "CAADriTechArticles"
tags: ["CATISketchEditor", "CATIDftDrawing", "CATIABase", "CATIADrawingComponent", "CATIDrwAnnotationFactory", "CATI2DWFFactory", "CATIGenerSpec", "CATIDrwAnnotation", "CATIDrwAddIn", "CATI2Dxxx", "CATIDrwFactory", "CATIView", "CATIDftMultiSheet", "CATIDrwAnnotationComponent", "CATIDftGenViewFactory", "CATI2DConstraintFactory", "CAADraftingInterfaces", "CATISketch", "CATIDftSheet"]
source_file: "Doc\online\CAADriTechArticles\CAADriDraftingOverView.htm"
converted: "2026-05-11T17:31:51.038395"
---

# Mechanical Design

| 

## Drafting

| 

### Drafting Modeler Overview

_Describing the foundations of the Drafting Modeler_  
---|---|---  
Technical Article  
  
* * *

### Abstract

This article discusses the Drafting modeler foundations.  

  * **Drafting Modeler Overview**
  * **Drafting Product Prerequisites**
  * **Drafting Structuring Objects**
  * **Drafting 2D Geometry Objects**
  * **Drafting 2D Constraint Objects**
  * **Drafting Annotation Objects**
  * **Drafting Dress-up Objects**
  * **Drafting Generative Views**
  * **Drafting Generated Objects**
  * **Additional Notions**
  * **References**
  * **In Short**

  
---  
  
* * *

### Drafting Modeler Overview

The Drafting application is in relation with several domains. The Drafting modeler enables you to automate tasks linked to these domains. See below the added value of the Drafting modeler.

![](images/DraftingEcosystem.gif)  
---  
Main domains linked to the Drafting application    
![](images/DraftingAddedValue.gif)  
Added value of the Drafting modeler    
  
The Drafting modeler manages geometry, constraint, annotation, dress-up and structuring objects (Sheet, View, Detail Sheet, Ditto). All elements created by the Drafting modeler are fully integrated in the Drawing document. That means, they will recognized by internal mechanism such as sketcher picking assistant, dimensioning, associative orientation and positioning and  constraints.

![](images/DraftingWorkBench.gif) |  The Drafting workbench is loaded and the current drawing sheet (Sheet.1) opens. The drawing specification tree is displayed to the left of the sheet. This tree shows aggregations between structuring objects. "Front View" view  of "Sheet.1" sheet is the active view of the active sheet: That means all elements created by indication will be aggregated on this view. At the top of the document, a tab page manages the active sheet.      
---|---  
  
A drawing document is a collection of sheets, along with information on the drafting standard (ISO, ANSI, ASME and JIS).

The sheet corresponds to the paper space, where the following elements are positioned:

  1. One main view: this view supports the geometries directly created in the sheet
  2. One background view: this view is dedicated to frame,  title block, revision blocks and bill of materials
  3. Any number of interactive and generative views.



The view may contain:

  * **2D geometry** : Geometry created by using the drafting interactive commands. The CAA Sketcher modeler is used to create 2D geometry.
  * **Generative results** : Non modifiable geometry created from 3D documents and linked to them.
  * **Constraints** : Sketcher modeler is used to create constraints.
  * **Annotations** : All elements containing text information: dimensions, texts, roughness symbols, welding symbols.
  * **Dress up** : Area fill axis lines, center lines, arrows, threads.



 

[Top]

### Drafting Product Prerequisites

The drafting application is managed by two products: 

  * Interactive drafting product that addresses 2D design and drawing production requirements.
  * Generative drafting product that provides functionalities to generate drawings from 3D parts and assembly definitions.



These two products are prerequisite to develop an application based on Drafting modeler.

Two frameworks contain the drafting modeler API:

  * DraftingInterfaces: This framework contains all drafting API except Detail, 2D geometry and constraint objects.
  * SketcherInterfaces: This framework is dedicated to manage sketcher component: detail, 2D geometry and constraint objects.



[Top]

### Drafting Structuring objects 

The drawing application data is included in an applicative container: the drawing container may be obtained from drawing root by using ` GetFeatContainer` method [[1](../CAADriUseCases/CAADriStructure.htm#Step2)]. 

When a drawing document is created, the following objects are created at the same time:

  * the Drawing container.
  * the Drawing root
  * The first sheet.
  * A main view aggregated by the first sheet.
  * A background view aggregated by the first sheet.



The following steps are necessary to complete the drawing creation:

  * Import a drawing standard [[1](../CAADriUseCases/CAADriStructure.htm#Step3)].
  * Get the available format from the standard and apply it to the first sheet [[1](../CAADriUseCases/CAADriStructure.htm#Step4)].



The _CATIDrwFactory_ interface implemented on drawing container enables you to create views or sheets and any objects which are not aggregated by a view. for example sheet, view, pattern, detail or relations.

_Note: To create a sheet, it is better to use`the AddSheet` method of the CATIDftDrawing interface to take into account the sheet page manager [[1](../CAADriUseCases/CAADriStructure.htm#Step5)]._

A sheet aggregates views and a view aggregates all objects instantiated in it. There is always an active view in a sheet. To create objects directly in a sheet, the main view of the sheet has to be activated.

![](images/StructuringObjectUML.gif)  
---  
This figure shows the UML diagram of drafting structuring objects.  
  
A view inherits from sketch to manages 2D geometry and 2D constraints. Two kinds of geometry coexist in a view:

  * 2D geometry: geometry managed by the CAA sketcher modeler.
  * Generative geometry: geometry created in a generative view from 3D data.



Two kinds of interfaces allow to get information on geometry:

  * IDMxxx interfaces: these interfaces are implemented by 2D geometry as well as generative geometry.
  * CATI2Dxxx interfaces: these interfaces are only available with 2D geometry.



 

[Top]

 

### Drafting 2D Compoment Objects 

A 2D component is a re-usable set of geometry and annotations. This component is located in a sheet and can be edited like a view. This is why this component is called Detail View. The 2D component can be instantiated several times, each instance providing a component with a specific orientation, position and scale. The detail view can be either in the same drawing as the CATDrawing of the corresponding instances or in a separate CATDrawing.

The Catalog Browser command allows to instantiate a ditto from an external CATDrawing document _CATDrawing1_ in a new Drawing document _CATDrawing2._ To do that, a special copy of _Detail Ref_ is created (_Detail Ref2_) and an instance of this copy (Ditto Inst 1). _Detail Ref2_ Detail is a **_no accessible local reference_** of the Reference Detail (Detail Ref)._See figure 1._

_Figure 1_  
---  
![](images/detailditto.jpg)  
  
Detail Ref 2 can not be directly modified. Only Detail Ref can be modified. When you instantiate for the second time the ditto (from Detail Ref) , in the new CATDrawing _CATDrawing 2_ , a new instance of the “copied” detail (Detail Ref2) is created (Ditto Inst 2).

No object can be modified in Ditto instance except Text modifiable in instance.

**_Text modifiable in instance:_**

A modifiable text in instance is a text with a specific attribute to inform the system to duplicate the text when a ditto is instantiated. See under the way to access to modifiable objects in instance:
    
    
    // GetModifiableObjects method allows to retrieve texts modifiable in ditto piDitto
    
    
    CATIADrawingComponent * piMyDrawComp = NULL;
    HRESULT rc = piMyDitto -> QueryInterface (IID_CATIADrawingComponent,(void**)&piMyDrawComp);
    if ( SUCCEEDED(rc) )
    {
      long Count = 0;
      piMyDrawComp -> GetModifiableObjectsCount (Count);
      for ( int Idx = 1; Idx<=Count; Idx++ )
      {
        CATVariant Variant;
        rc = BuildVariant ((long)Idx, Variant);
        if ( SUCCEEDED(rc) )
        {
          CATIABase * piABase = NULL;
          rc = piMyDrawComp -> GetModifiableObject (Variant, **piABase**);
          if ( SUCCEEDED(rc) )
         {  
  
---  
  
[Top]

 

### Drafting 2D Geometry Objects 

These objects are created by using 2D wire frame factory defined in SketcherInterface framework. A pointer on _CATI2DWFFactory_ interface may be obtained by using a `QueryInterface` on the view [[1](../CAADriUseCases/CAADriStructure.htm#Step7)].

Notes:

  1. The view has to be activated to deal with 2D geometry. When a view is activated, associated sketch is in open edition, so geometry may be created.
  2. If an interactive command deals with geometry, at the end of the 2D geometry creation step, `SaveEdition` method defined on _CATISketchEditor_ interface has to be executed. _CATISketch_ interface inherits from _CATISketchEditor_ , so, `SaveEdtion may be executed from _CATISketch_ interface.`



[Top]

### Drafting 2D Constraint objects 

These objects are created by using 2D constraint factory defined in SketcherInterface framework. A pointer on _CATI2DConstraintFactory_ interface may be obtained by using a `QueryInterface` on the view. In this factory  CreateConstraint method allows to create constraint in the view.

[Top]

### Drafting Annotation objects 

These objects are created by using drawing annotation factory. A pointer on _CATIDrwAnnotationFactory_ interface may be obtained by using a ` QueryInterface` on the view [[2](../CAADriUseCases/CAADriCreateDim.htm#Step5)]. All the annotations inherit from AnnotationComponent object which inherits from Annotation object. _CATIDrwAnnotation_ interface manages associative position and associative orientation between annotations or annotation and geometry. CATIDrwAnnotationComponent is dedicated to manage global informations relative to the annotation text.

When an annotation is modified feature has to be rebuild to get the result [[3](../CAADriUseCases/CAADriDimDressup.htm#References)].

![](images/AnnotationObjectUML.gif)  
---  
                          This figure shows the UML diagram of annotation objects    
  
[Top]

### Drafting Dress-up objects 

These objects are created by using drawing annotation factory. A pointer on _CATIDrwAnnotationFactory_ interface may be obtained by using a ` QueryInterface` on the view. Sometime these elements require geometry to be created. The Center Line Creation sample explains how to create center line from 2D geometry or Generative Geometry [[4](../CAADriUseCases/CAADriCenterLine.htm)].

[Top]

### Drafting Generative Views

These views are created  from 3D data coming from Product or Part type documents. To create a Generative Front View, a view with makeUp first has to be created, then the view typed by using the SetViewType method defined in _CATIView_ interface. The SetDoc method allows to create a link between the Generative View and the 3D document. At last, define a projection plane in the view using the SetProjectionPlane  method of the _CATIGenerSpec_ interface. A pointer to _CATIGenerSpec_ interface may be retrieved from _CATIView_ interface by using GetGenerSpec method. As any view, a Generative View has to be aggregated to a sheet by using AddView method on _CATIDftSheet_ interface. To get the result of a 3D projection in the view, call the Update method on _CATIView_ interface.

Particular Generative views may be easily created by using the following interface: _CATIDftGenViewFactory_ interface. This interface is implemented by the sheet object:

  1. CreateViewFrom3D: To Create a generative Drawing View from TPS view. (TPS view is a 3D view created in Functional, Tolerancing and Annotation workbench) [[5](../CAADriUseCases/CAADriCreateViewFrom3D.htm)].
  2. CreateSectionView: To create a section from a parent view and a profile defined in the parent view.
  3. CreateStandAloneSectionView: To create a section view with a cutting profile associative to 3D element. This 3D element may be a a Planar Face, a 3D Sketch [[6](../CAADriUseCases/CAADriCreateSectionFrom3DSketch.htm)] or Plane[[7](../CAADriUseCases/CAADriCreateSectionFromPlane.htm)]  . The cutting profile is associative to the 3D element.



 

[Top]

### Drafting Generated Objects 

These objects are automatically created when a Generative View is created or updated. Generative Geometry is defined from 3D Document and associated on it. Generative Geometry can not be edited, only graphic properties may be modified  [[8](../CAADriUseCases/CAADriGenGeomAccess.htm#References)].

[Top]

### Additional Notions

The _CATIDrwAddIn_ interface enables you to add a new command in drafting workbench. Interactive commands defined in CAADraftingInterfaces.edu framework have been plugged in a toolbar [[9](../CAAAfrUseCases/CAAAfrSampleAddin.htm)].

The _CATIDftMultiSheet_ interface, implemented by the sheet enables to keep an interactive command active when the active sheet is changing [[10](../CAADriUseCases/CAADriMultiSheetCmd.htm)].

[Top]

 

* * *

### References

[1] |  [Create Sheets and Views in a CATDrawing Document](../CAADriUseCases/CAADriStructure.htm)  
---|---  
[2] |  [Create a Distance Dimension Between on Interactive Geometry](../CAADriUseCases/CAADriCreateDim.htm)  
[3] |  [Editing Dimension Dress-Up](../CAADriUseCases/CAADriDimDressup.htm)  
[4] |  [Creating a Center Line in CATDrawing Document](../CAADriUseCases/CAADriCenterLine.htm)  
[5] |  [Creating _a view from 3D_](../CAADriUseCases/CAADriCreateViewFrom3D.htm)  
[6] |  [ Creating a Section view from a 3D Sketch](../CAADriUseCases/CAADriCreateSectionFrom3DSketch.htm)  
[7] |  [ Creating a Section view from Plane](../CAADriUseCases/CAADriCreateSectionFromPlane.htm)  
[8] |  [Editing Generetated Geometry in a Generative View](../CAADriUseCases/CAADriGenGeomAccess.htm)  
[9] |  [ Creating an Add-in](../CAAAfrUseCases/CAAAfrSampleAddin.htm)  
[10] |  [Create a Multisheet Interactive Command](../CAADriUseCases/CAADriMultiSheetCmd.htm)  
[Top]  
  
* * *

### In Short

This article has explained the foundations of the Drafting Modeler.

[Top]

* * *

### History

Version: **1** [Mar 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
