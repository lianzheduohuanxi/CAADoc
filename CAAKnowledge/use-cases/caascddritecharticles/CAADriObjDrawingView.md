---
```vbscript
title: "DrawingView Object"
category: "use-case"
module: "CAAScdDriTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdDriTechArticles/CAADriObjDrawingView.htm"
converted: "2026-05-11T17:31:51.127693"
```

---
# DrawingView Object

See Also | UseCases | Properties | Methods
---|---|---|---

[![](../CAAScrAutomationImages/images/drviews.gif)](CAADriObjDrawingViews.md)
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/dractview.gif)![](../CAAScrAutomationImages/images/drview.gif)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/drview.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drrefview.gif)![](../CAAScrAutomationImages/images/drview.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drviewgb.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drtexts.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/fact2d.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/geoelts.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drwelds.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drviewgl.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drcomps.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drtables.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/drthreads.gif)
---

Represents a drawing view of a drawing sheet in a drawing document.

The drawing view is placed in the drawing sheet using the following properties:

![](images/baspp4-4.gif)

The drawing view is placed in the drawing sheet using the following properties:
The **x** , **y** , and **Angle** properties are used to place the drawing view in the drawing sheet. The drawing view has also a **Scale** property which determines its size in the drawing sheet with respect to the 3D document represented. The **GenerativeBehavior** property retrieves the **DrawingViewGenerativeBehavior** object associated with the drawing view, and you can get or set the reference view thanks to the **ReferenceView** property.

Using the **Activate** method, you can make the drawing view the active one. The **AlignedWithReferenceView** and **UnAlignedWithReferenceView** methods enable you to align and deactivates the alignment with respect to the reference view. The **IsGenerative** methods returns whether the drawing view is generated from a document.

The **DrawingViewGenerativeBehavior** object includes additional parameters to fully define the drawing view. First, it includes a link to the represented document using its **Document** property. Then it includes a link to the parent view, if any, thanks to the **ParentView** property. It also includes the **DefinexxxView** methods to define views according to the different available types. The **SetProjectionPlane** , **GetProjectionPlane** , and **GetProjectionPlaneNormal** methods manage the drawing view projection plane. The drawing view projection plane is usually defined when the drawing view is created, either by setting it explicitly for a front view or an isometric view, or by deducing it from the one of the parent view for the other views.

Let's now detail the different type of views.

A drawing view can be used as a parent view for other drawing views. When you create a drawing view, for example from a part, you first create a front view, and then you can create a left, right, top, or bottom drawing view from this front view. The left, right, top, or bottom view is called a projection view. The front view is used as a parent view to determine how the document is projected in the projection view. For example, left means projecting the part on a vertical plane which is perpendicular to the front view projection plane, and which is seen from the left.

A drawing view is strongly linked to its parent view. If the parent view is updated because the document it displays has changed, or if you change its scale, all the drawing views which have this view as parent view are changed accordingly.

![](images/baspp4-5.gif)

A drawing view is strongly linked to its parent view. If the parent view is updated because the document it displays has changed, or if you change its scale, all the drawing views which have this view as parent view are changed accordingly.
The front view is also used as a reference by the left view for positioning. If you want to move the left view, it is constrained to move horizontally to remain a left view of the front view. The left view can access its reference view by means of the **ReferenceView** property.

The following table summarizes the different view types along with their ability to have a parent view and if this parent view can also be a reference view.

View Types | Parent View | Reference View | Creation Method

The following table summarizes the different view types along with their ability to have a parent view and if this parent view can also be a reference view.
View Types | Parent View | Reference View | Creation Method
Front View | No | No | **DefineFrontView**
Isometric View | No | No | **DefineIsometricView**
Projection View | Yes | Yes | **DefineProjectionView**
Section View | Yes | Yes | **DefineSectionView**
Detail View | Yes | No | **DefineCircularDetailView**
Auxiliary View | Yes | Yes | **DefineAuxiliaryView**

A front view or an isometric view are defined using the components of the two vectors defining its projection plane in the 3D space.

The other views are all defined by giving the **DrawingViewGenerativeBehavior** object of their parent view, and additional information:

  * a projection view is defined using a view type which can be left, right, top, or bottom using the **CatProjViewType** enumeration.
  * a section view or section cut is defined using a section profile in the parent view and passed as an array of point coordinates expressed with respect to the parent view axis system. Other information is required, namely the section type, that is whether the section is a section cut or a section view, the profile type, that is whether the section is aligned or offset, and the drawn side of the section. This drawn side is determined as follows: the parent view is rotated clockwise or counterclockwise around the first segment of the section profile oriented from its start point to its end point.

![](images/baspp4-6.gif)

  * a detail view is defined from a parent view and using a clipping circle
  * an auxiliary view is defined from a parent view and using a line which defines the trace of the auxiliary view projection plane in the parent view.

## Using the DrawingView Object

Use x and y properties to set or retrieve the x and y coordinates of the view coordinate system. The following example sets these coordinates to 260mm and 120mm respectively.

```vbscript
    Dim myView As Object
```vbscript
```vbscript
    Set myView = CATIA.Documents(2).ActiveSheet.ActiveView
    myView.x = 260
    myView.y = 120

```

```

```

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
