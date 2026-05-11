---
title: "Creating EdgeFillets on a Rectangular Pad"
category: "general"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriUseCases", "CAAPriCreateEdgeFillet"]
source_file: "Doc\online\CAAScdPriUseCases\CAAPriCreateEdgeFillet.htm"
converted: "2026-05-11T17:31:51.218485"
---

## Part Interfaces

| 

## Creating EdgeFillets on a Rectangular Pad  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This macro shows you how to create fillets on a rectangular Pad. This macro retrieves a rectangular pad from a Part document and creates fillets from the selection of all vertical edges and top and bottom faces.  
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAPriCreateEdgeFillet is launched in CATIA [1]. No open document is needed. ![](images/PartWithFillet.jpg)  
Figure 1: The final result. [CAAPriCreateEdgeFillet.CATScript](CAAPriCreateEdgeFilletSource.htm) is located in the CAAPriUseCases module.  [Execute macro](macros/CAAPriCreateEdgeFillet.CATScript).    
![](../CAAScrBase/images/ascenari.gif) |  CAAPriCreateEdgeFillet includes five steps:

  1. Retrieving the Pad Contained in the Associated Pad.CATPart file
  2. Retrieving All the Vertical Edges from the Rectangular Pad
  3. Creating a First EdgeFillet with the Selected Edges
  4. Retrieving the Top and Bottom Faces of the Pad
  5. Creating a Second EdgeFillet with the Selected Faces



#### Retrieving the Pad Contained in the Associated Pad.CATPart file

| 
    
    
    ...

Dim oPartDocument As PartDocument  
Set oPartDocument = CATIA.Documents.Open("E:\tmp\CAAScdPriUseCases.doc\src\samples\Pad.CATPart Dim oPart As Part  
Set oPart = CATIA.ActiveDocument.Part ' Retrieve the part body of the document containing the pad to be used  
Dim oBody As Body  
Set oBody = oPart.Bodies.Item ( "MechanicalTool.1" ) ' Retrieve the pad of the body  
Dim oPad As Pad  
Set oPad = oBody.Shapes.Item ( "Pad.1" )
    
    
    ...  
  
---  
  
oPad is retrieved by its name "Pad.1" in the PartBody tree.

#### Retrieving All the Vertical Edges of the Rectangular Pad
    
    
      ...
    

' Retrieve the vertical edges of the pad to be filleted  
Dim oEdge1 As Reference  
Set oEdge1 = oPart.CreateReferenceFromBRepName ( "REdge:(Edge:(Face:(Brp:(Pad.1;0:(Brp:(Sketch.1;1))); None:());Face:(Brp:(Pad.1;0:(Brp:(Sketch.1;2)));None:());None:(Limits1:();Limits2:())); WithTemporaryBody;WithoutBuildError;WithSelectingFeatureSupport)", oPad )
    
    
      ...  
  
---  
  
The elements to be filleted are edges. Here these elements are REdge features  
defined by their symbolic addresses.

#### Creating a first EdgeFillet with the selected edges
    
    
    ...
    

' Define the fillet to be created with the first edge  
Dim oEdgeFillet1 As ConstRadEdgeFillet  
Set oEdgeFillet1 = oPart.ShapeFactory.AddNewEdgeFilletWithConstantRadius ( oEdge1, 1, 5.000000 ) ' Add the others edges to be filleted  
oEdgeFillet1.AddObjectToFillet oEdge2  
oEdgeFillet1.AddObjectToFillet oEdge3  
oEdgeFillet1.AddObjectToFillet oEdge4 ' Enable the fillet to be propagated to all the tangent contiguous edges  
oEdgeFillet1.EdgePropagation = 1 ' Define the fillet radius to 5 mm  
oEdgeFillet1.Radius.Value = 5.000000 ' Update the document  
oPart.Update
    
    
      ...  
  
---  
  
The AddNewEdgeFilletWithConstantRadius method from the ShapeFactory allows you to create a constant  
EdgeFillet with the propagation mode (1 for second argument) and a 5 mm radius.  
Update the part to compute the result of the EdgeFillet.

![](images/PartWithVerticalFillets.jpg)  
Figure 2: Rectangular pad with its vertical filleted edges.

#### Retrieving the Top and Bottom Faces of the Rectangular Pad
    
    
    ...  

' Retrieve the top face of the pad to be filleted  
Dim oTopFace As Reference  
Set oTopFace = oPart.CreateReferenceFromBRepName ( "RSur:(Face:(Brp:(Pad.1;2);None:());WithTemporaryBody;WithoutBuildError;WithSelectingFeatureSupport)", oEdgeFillet1 ) ' Retrieve the bottom face of the pad to be filleted  
Dim oBottomFace As Reference  
Set oBottomFace = oPart.CreateReferenceFromBRepName ( "RSur:(Face:(Brp:(Pad.1;1);None:());WithTemporaryBody;WithoutBuildError;WithSelectingFeatureSupport)", oEdgeFillet1 )
    
    
    ...  
  
---  
  
Retrieve the Rsur features representing the top and bottom faces of the pad to use them to create another EdgeFillet.

#### Creating a Second EdgeFillet with the Selected Faces

... ' Define the fillet to be created with the first face  
Dim oEdgeFillet2 As ConstRadEdgeFillet  
Set oEdgeFillet2 = oPart.ShapeFactory.AddNewEdgeFilletWithConstantRadius ( oTopFace, 1, 15.000000 ) ' Define the fillet radius to 5 mm  
oEdgeFillet2.Radius.Value = 5.000000 ' Add the other face  
oEdgeFillet2.AddObjectToFillet oBottomFace ' Update the document  
oPart.Update ...  
---  
  
All the limiting edges of the selected faces will be used to create the second EdgeFillet.  
  
|  ![](../CAAScrBase/images/aendtask.gif)  
  
[Top]

* * *

#### In Short

This use case has shown how to create EdgeFillets retrieving REdge or RSur features from a pad.

[Top]

* * *

#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
  
[Top]

* * *

_Copyright © 2001, Dassault Systèmes. All rights reserved._
