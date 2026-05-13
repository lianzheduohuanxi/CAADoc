---
```vbscript
title: "Arranging Dialog Objects"
category: tech-article
module: "CAADlgTechArticles"
tags: []
source_file: "Doc/online/CAADlgTechArticles/CAADlgObjectLayout.htmmd"
converted: "2026-05-11T17:17:56.052020"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Dialogs

|
### Arranging Dialog Objects

How to manage the dialog object layout in dialog windows and boxes
---|---|---
Technical Article

* * *
### Abstract

Arranging dialog objects in a dialog window, a dialog box, a frame or a tab page, that is a container, consists in positionning each object at a given place with respect to the others. The container layout will then not changed when the dialog window is resized.

  * **Dialog Object Layout**
  * **Object and Container Sizes**
  * **Dynamic Resizing and Modification**
  * **Grid Layout**
  * **Tabulation Layout**
  * **References**
  * **In Short**

---

* * *
### Dialog Object Layout

The main parameters for object layout are the dimensions and the assigned position of each object. Objects are automatically sized using their contents when they are instantiated. For example, a label size is computed using the number of characters that the label title includes, and a multilist size is computed using the number of rows and columns. You can arrange the dialog objects inside their container. In addition, you can allow some objects to be resizable when the whole window is resized.

Arranging dialog objects within a container applies to the following containers, which are instances of the CATDlgDocument, CATDlgDialog, CATDlgFrame, and CATDlgTabPage classes. For other container classes, the layout is predetermined and cannot be customized, because:

  * They can't have any child: CATDlgNotify and CATDlgFile
  * They can have a single child: CATDlgContainer
  * The layout is imposed: CATDlgSplitter, CATDlgBar
  * The layout is specific to the object's representation: CATDlgMenu, CATDlgTabContainer, and CATDlgIconBox.

```vbscript
If you have complex windows with containers which include many objects, you need to arrange your containers and their contents. It is advisable to arrange your window container by container, beginning with the main container. You can refer to the "The Burger Order Dialog Box" use case [1] to see how the frames as well as their labels, separators and the bottom push buttons were first arranged, and then how the contents of each of the three frames were arranged afterwards.

```

There are two ways of arranging dialog objects within a container: the grid layout and the tabulation layout. The grid layout is based on a grid that defines cells in which dialog object can take place. The tabulation layout is based on tabulations to which dialog objects are attached by one ore several sides. The grid layout is a bit easier to understand and implement than the tabulation layout, but provides less capabilities. It match most of the situations and is the recommended way of arranging dialog objects.

[Top]
### Object and Container Sizes

There are two ways of arranging dialog objects within a container: the grid layout and the tabulation layout. The grid layout is based on a grid that defines cells in which dialog object can take place. The tabulation layout is based on tabulations to which dialog objects are attached by one ore several sides. The grid layout is a bit easier to understand and implement than the tabulation layout, but provides less capabilities. It match most of the situations and is the recommended way of arranging dialog objects.
The size of each object is determined by its contents. For example, a label, that is a CATDlgLabel instance, size is determined at instantiation time using the text it contains and the character font used to display the text. If your change the text or the character font or both, when reinstantiating the label, its size changes accordingly. But if you dynamically change the text by means of the method `SetTitle` without reinstantiating the label, the size does not change and maybe a part of the text is not displayed.

The size of a container is also determined by its contents. The size of a CATDlgTabContainer instance is the size of the biggest CATDlgTab instance it contains.

The CATDlgContainer is an exception. Since it is dedicated to contain many controls, but usually to display only a part of them, you need to assign it a size using absolute values expressed in pixels by means of the `SetRectDimensions` method. For example, the following statement

    pContainer->SetRectDimensions(1, 1, 200, 300);

---

pContainer->SetRectDimensions(1, 1, 200, 300);
sets the size of `pWindow1` to 200 pixels width and 300 pixels height. The two first coordinates are unused, but must be positive (>0).

You can also set its size in order to show all its content, as follows:

    pContainer->SetRectDimensions(1, 1, -1, -1);

---

[Top]
### Dynamic Resizing or Modification

When resizing a dialog window, the containers it contains are resized accordingly, and part of  their contents can be modified or hidden. For example, containers or subcontainers whose sizes decrease can hide controls and scrollbars can appear to help display hidden controls. On the opposite, when increasing the dialog window size, the scrollbars can disappear as soon as all the existing controls are displayed.

When resizing a dialog window, the containers it contains are resized accordingly, and part of  their contents can be modified or hidden. For example, containers or subcontainers whose sizes decrease can hide controls and scrollbars can appear to help display hidden controls. On the opposite, when increasing the dialog window size, the scrollbars can disappear as soon as all the existing controls are displayed.
But when the dialog window is displayed, it is expected to keep the same contents, whether this contents being fully displayed or partly hidden, in order to display consistently to the end user. Nevertheless, two exceptions exist:

  1. Two or several objects can be designed to be displayed at the same location, depending on the context. In this case, all these objects must be created when building the dialog window. The appropriate one is then displayed and attached to the tabulation line when necessary, the one previously displayed is concurrently detached and hidden. This is possible using tabulations only with the ReplaceKeepAttachments method
  2. A dialog box can have a hidden part that can be displayed using a More push button. This is possible with CATDlgDialog derived classes that feature the CATDlgWndAutoResize style, and that contains only CATDlgFrame instances.

[Top]
### Grid Layout

**This is the recommended way of arranging dialog objects**. It uses a grid made of cells. Each cell is located at the intersection of a row and a column. A given container or dialog object is contained in one or more cells, and can be attached to cell sides for resizing management. Each container has its own grid used for the layout of the objects it contains. This is described in "Arranging Dialog Objects Using Grid" [2]

[Top]
### Tabulation Layout

This is not the recommended way of arranging dialog objects but it is sometimes necessary to create dynamic layout. It uses a set of horizontal and vertical tabulation lines along which you can attach the sides of the containers and objects. You can have a set of horizontal and vertical tabulation line set for each container to manage the layout of the objects it contains. This is described in "Arranging Dialog Objects Using Tabulations" [3]

[Top]
### In Short

Dialog object container sizes are determined using their contents. Containers can be resized without modifying their contents, that can be partially hidden if necessary. Containers and controls can be arranged either using a grid (recommended), or using tabulations (Not recommended).

[Top]

* * *
### References

[1] | [The Burger Order Dialog Box](../CAADlgUseCases/CAADlgBurger.md)
---|---
[2] | [Arranging Dialog Objects Using Grid](CAADlgGridLayout.md)
[3] | [Arranging Dialog Objects Using Tabulations](CAADlgTabLayout.md)
[Top]

* * *
### History

Version: **1** [Fev 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
