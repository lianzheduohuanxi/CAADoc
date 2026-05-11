---
title: "Viewers Object"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfObjViewer3D.md"
converted: "2026-05-11T17:31:52.429128"
---
# Viewers Object
 
  
 
 See Also | Use Cases | Properties | Methods  
 ---|---|---|---  
   
  
 
 ![](../CAAScrAutomationImages/images/viewers.gif)  
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/viewer.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parderiv.gif)![](../CAAScrAutomationImages/images/viewer3d.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/viewpt3d.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/lightsos.gif)  
 ---  
   
 **_A collection of Viewer objects._**
 
 A **Viewer** is used to display a document according to a given viewpoint and display options. Depending on the document type, the following viewers can be found in a window:
 
     * PartDocument: a **Viewer3D** for the part 3D objects and/or a **SpecsViewer** for the part specification tree
     * ProductDocument: a **Viewer3D** for the assembly 3D objects and/or a **SpecsViewer** for the assembly specification tree
     * DrawingDocument: a **Viewer2D** for the drawing sheets and/or a **SpecsViewer** for the drawing specification tree.
 
 When the window displays both a **Viewer3D** and a **SpecsViewer** , or one or several **Viewer2D** s and a **SpecsViewer** , it is a **SpecsAndGeomWindow** . You can activate a given viewer in a multi-viewer window, fit all the scene in the viewer, update the display, zoom in and out, and capture the contents of the viewer as an image file.
 
 Display options depend on the viewer type. All viewers share display options such as the background color and the display on the whole screen or in a smaller window. In addition, **Viewer3D** s allow for different lighting modes and for modifying lighting intensity, and for depth effects, navigation styles, rendering modes, and clipping modes.
 ## Viewpoints
 
 A viewpoint holds complementary data for viewers. A **Viewpoint2D** defines the origin of the scene to display, expressed in model units, and a zoom factor to apply for display. A **Viewpoint3D** holds in addition the sight and up directions, the target, the field of view, and projection modes.
 
  
 
 ![](images/baspp1-8.gif)
 ## Cameras
 
 A **Camera** is the persistent form of a viewpoint. You can create a camera from the current viewpoint using the **NewCamera** method of the **Viewer** object. The camera name is assigned by CATIA: **Camera00** , **Camera01** , and so forth, and the created camera is placed at the end of the camera collection of the active document and is displayed in the Named Views dialog box of the View menu. You can rename the cameras you create with your own names using the **Name** property. A created camera can then be assigned to a viewer to make its own viewpoint change to this of the camera. Two kinds of cameras exist: the **Camera2D** for 2D viewpoints, that is for DrawingDocument objects, and the **Camera3D** for 3D viewpoints representing the real world, that is for PartDocument and ProductDocument objects. A **Camera2D** stores a **Viewpoint2D** object and a **Camera3D** stores a **Viewpoint3D** object
 
 [Top]
 
 * * *
 
 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
