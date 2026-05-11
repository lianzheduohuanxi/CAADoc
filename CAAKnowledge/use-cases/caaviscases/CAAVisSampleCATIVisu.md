---
title: "Making a Component Displayable With CATI3DGeoVisu"
category: "use case"
module: "CAAVisUseCases"
tags: ["CATI3DGeoVisu", "CAASysLine", "CAASysPolyline", "CAAEVisVisuCircle", "CAAVisualization", "CAAVisGeoModel", "CAASysEllipse", "CATIA", "CAAEVisModelEvents", "CAAIModelEvents", "CAAGeometry", "CAAISysCircle", "CAAVisModelEvents", "CAASysPoint", "CAASysCircle", "CAASysSampRootObj", "CATIModelEvents", "CAASysPlane", "CAASysGeomRootObj"]
source_file: "Doc/online/CAAVisUseCases/CAAVisSampleCATIVisu.md"
converted: "2026-05-11T17:31:52.066701"
---
# 3D PLM Enterprise Architecture

| 
## 3D Visualization

| 
### Making a Component Displayable With CATI3DGeoVisu

_Implementing CATI3DGeoVisu and CATIModelEvents to enable a geometric component to be displayed in a viewer_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article discusses the CAAVisGeoModel use case. This use case explains how geometric components can provide a representation to be displayed in a viewer.

  * **What You Will Learn With This Use Case**
  * **The CAAVisGeoModel Use Case**
    * What Does CAAVisGeoModel Do
    * How to Launch CAAVisGeoModel
    * Where to Find the CAAVisGeoModel Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to show how to implement the _CATI3DGeoVisu_ interface to make a geometric component displayable in a 3D viewer, and how to implement the _CATIModelEvents_ interface to refresh the representation according to model updates.

[Top]
### The CAAVisGeoModel Use Case

CAAVisGeoModel is a set of use cases of the CAAVisualization.edu framework that illustrates Vizualization framework capabilities.

[Top]
#### What Does CAAVisGeoModel Do

CAAVisGeoModel contains a series of C++ classes, each of them being an extension of a component representing a geometric component, such as a point, a line, a circle, or an ellipse. Each extension implements the _CATI3DGeoVisu_ interface to make the corresponding component displayable in a 3D viewer. This article focuses on the way the circle component implements _CATI3DGeoVisu_. In addition, a single extension class implements the _CATIModelEvents_ interface for all the geometric components. It is also described.

[Top]
#### How to Launch the CAAVisGeoModel

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

Launch CATIA. When the application is ready, follow scenarios described below:

  * In the **Start** menu choose **Infrastructure** and click **CAA V5: Geometrical Creation**.
  * In the **Insert** menu choose **Point**.
  * Create three points.
  * In the **Insert** menu choose **Plane**.
  * Select the three points.
  * In the **Insert** menu choose **Circle**.
  * Select the plane, select or indicate the center point, move the mouse to obtain the wanted radius and click to end.

[Top]
#### Where to Find the CAAVisGeoModel Code

CAAVisGeoModel code is located in the CAAVisGeoModel.m use case module of the CAAVisualization.edu framework:

Windows | `InstallRootDirectory\CAAVisualization.edu\CAAVisGeoModel.m`  
---|---  
Unix | `InstallRootDirectory/CAAVisualization.edu/CAAVisGeoModel.m`  
  
where `InstallRootDirectory` is the root directory of your CAA V5 installation. 

CAAVisGeoModel includes the following files for the circle component:

**LocalInterfaces directory**  
---  
CAAEVisVisuCircle.h | Header file for the circle component extension class that implements _CATI3DGeoVisu_  
CAAEVisModelEvents.h | Header file for the common component extension class that implements _CATIModelEvents_  
**src directory**  
CAAEVisVisuCircle.cpp | Source file for the circle component extension class that implements _CATI3DGeoVisu_  
CAAEVisModelEvents.cpp | Source file for the common component extension class that implements _CATIModelEvents_  
  
[Top]
### Step-by-Step

To implement _CATI3DGeoVisu_ and _CATIModelEvents_ , there are four main steps:

  1. Creating the Header File of CAAEVisVisuCircle
  2. Creating the Source File of CAAEVisVisuCircle
  3. Implementing the BuildRep Method of CATI3DGeoVisu
  4. Implementing the CATIModelEvents Interface

[Top]
#### Creating the Header File of CAAEVisVisuCircle

The _CAAEVisVisuCircle_ header file is as follows. 
    
    #include "CATExtIVisu.h"
    
    class CAAEVisVisuCircle : public **CATExtIVisu**
    {
      **CATDeclareClass** ;
      public:
        CAAEVisVisuCircle();
        virtual ~CAAEVisVisuCircle();
        **virtual  CATRep * BuildRep();**
      private :
      CAAEVisVisuCircle(const CAAEVisVisuCircle &iObjectToCopy);
    };  
  
---  
  
_CAAEVisVisuCircle_ derives from the CATExtIVisu adapter that provides code for the _CATI3DGeoVisu_ interface methods. As any class that makes up a component, its header file includes the `CATDeclareClass` macro. The `BuildRep` method is the only one to redefine. Note that the copy constructor is declared as private, and is not implemented. This prevents the compiler from creating a public one without you know. This is to prevent clients from creating instances from an existing one, that they normally should not handle, except using interface pointers.

[Top]
#### Creating the Source File of CAAEVisVisuCircle

The _CAAEVisVisuCircle_ source file is as follows.
    
    #include "CAAEVisVisuCircle.h"
    #include "CAAISysCircle.h"
    #include "CAT3DCustomRep.h"
    #include "CAT3DArcCircleGP.h"
    #include "TIE_CATI3DGeoVisu.h"
    **TIE_CATI3DGeoVisu(CAAEVisVisuCircle);**
    
    **CATImplementClass**(CAAEVisVisuCircle, **DataExtension** , CATBaseUnknown, **CAASysCircle**);
    
    CAAEVisVisuCircle::CAAEVisVisuCircle() {}
    
    CAAEVisVisuCircle::~CAAEVisVisuCircle() {}
    
    **CATRep *** CAAEVisVisuCircle::**BuildRep**()
    {
      ...
    }   
  
---  
  
The main points of this source file are:

  * _CAAEVisVisuCircle_ implements the _CATI3DGeoVisu_ interface: this is expressed thanks to the `TIE_CATI3DGeoVisu` macro
  * _CAAEVisVisuCircle_ implements the _CATI3DGeoVisu_ interface for the _CAASysCircle_ component as a data extension. This is expressed using the `CATImplementClass` macro
  * The BuildRep method is the only redefined method of _CATI3DGeoVisu_. It should return a pointer to the circle representation, that is, a pointer to a _CAT3DRep_

[Top]
#### Implementing the BuildRep Method of CATI3DGeoVisu

There are two possibilities for creating the representation of a circle, that is, using the _CAT3DArcCircleRep_ class, or using a custom representation. This latter is detailed here.

  1. Declaring the representation to return 
         
         CATRep * CAAEVisVisuCircle::**BuildRep**()
         {
           **CAT3DCustomRep** *pCircleRep = NULL;
           ...  
  
---  
  
The _CAT3DCustomRep_ class can accommodate any kind of representation(s).

  2. Retrieving the circle parameters 
         
         ...
           CAAISysCircle * piSysCircle = NULL;                
           HRESULT rc = **QueryInterface**(IID_CAAISysCircle, (void**)&piSysCircle);
           if (SUCCEEDED(rc))
           {
             CATMathPoint center;
             float radius;
             CATMathVector normal, axis;
         
             piSysCircle->GetCenter(center);
             piSysCircle->GetRadius(radius);
             piSysCircle->GetPlane(normal, axis);
         
             piSysCircle->**Release**();
             ...  
  
---  
  
 

 The circle component implements the _CAAISysCircle_ interface [1]. This is a type interface that enables to set and retrieve the parameters that make this component a circle: its center and radius, and the normal and axis vectors of the plane in which it lies. Once the pointer to _CAAISysCircle_ is not any longer needed, it is released.  
---|---  
  3. Creating the graphic primitive for the circle 
         
         ...
             CAT3DArcCircleGP * pCircleGp = new **CAT3DArcCircleGP**(center, normal, radius, axis);
             ...   
  
---  
  
The circle graphic primitive is an instance of _CAT3DArcCircleGP_. Its constructor needs the four parameters retrieved from the circle component.

  4. Creating and filling in the representation 
         
         ...
             pCircleRep = new **CAT3DCustomRep**();
             **CATGraphicAttributeSet** circleGa;
             pCircleRep->**AddGP**(pCircleGp,circleGa);
             ...   
  
---  
  
The circle representation is created as a _CAT3DCustomRep_ instance. Is is filled in thanks to the `AddRep` method with the graphical primitive and a set of graphic attributes featuring their default values.

  5. Creating the circle bounding element and assigning it to the representation 
         
         ...
             **CAT3DBoundingSphere** circleBe(center,radius);
             pCircleRep->**SetBoundingElement**(circleBe);
             ...  
  
---  
  
In order to increase display performance, any representation should have a bounding element that is first asked to determine whether the associated representation should be displayed in the current view port. This bounding element is chosen as a _CAT3DBoundingSphere_ instance defined using the circle center and radius. The `SetBoundingElement` method assigns it to the circle representation.

  6. Returning the created representation 
         
         ... 
           }
           return pCircleRep;
         }   
  
---  
  
The circle is now ready for display.

[Top]
#### Implementing the CATIModelEvents Interface

_CAAVisModelEvents_ implements the _CATIModelEvents_ interface by deriving from the _CATExtIModelEvents_ adapter.

  1. Creating the header file. 
         #include "CATExtIModelEvents.h"
         
         class CAAEVisModelEvents : public **CATExtIModelEvents**
         {
           **CATDeclareClass** ;
           public :
             CAAEVisModelEvents();
             virtual ~CAAEVisModelEvents();
           private :
           CAAEVisModelEvents(const CAAEVisModelEvents &iObjectToCopy);
         };  
  
---  
  
As any class that makes up a component [2], its header file includes the `CATDeclareClass` macro. None of the _CATIModelEvents_ methods needs to be redefined. Note that the copy constructor is declared as private, and is not implemented. This prevents the compiler from creating a public one without you know. This is to prevent clients from creating instances from an existing one, that they normally should not handle, except using interface pointers.

  2. Creating the source file. 
         #include "CAAEVisModelEvents.h"
         #include "TIE_CATIModelEvents.h"
         **TIE_CATIModelEvents**(CAAEVisModelEvents);
         
         **CATBeginImplementClass**(CAAEVisModelEvents, DataExtension, CATBaseUnknown, CAASysPoint);
         CATAddClassExtension(CAASysSampRootObj);
         CATAddClassExtension(CAASysGeomRootObj);
         CATAddClassExtension(CAASysLine);
         CATAddClassExtension(CAASysEllipse);
         CATAddClassExtension(CAASysPlane);
         **CATAddClassExtension**(CAASysCircle);
         CATAddClassExtension(CAASysPolyline);
         **CATEndImplementClass**(CAAEVisModelEvents); 
         
         CAAEVisModelEvents::CAAEVisModelEvents() {}
         
         CAAEVisModelEvents::~CAAEVisModelEvents() {}  
  
---  
  
The main points of this source file are:

     * _CAAEVisModelEvents_ implements the _CATIModelEvents_ interface: this is expressed thanks to the `TIE_CATIModelEvents` macro
     * _CAAEVisModelEvents_ implements the _CATIModelEvents_ interface for several components, among which the _CAASysCircle_ component, as a data extension. Compared to the declaration of a single component extension using `CATImplementClass`, this is expressed using three macros: 
       * `CATBeginImplementClass`, that has the same signature than `CATImplementClass`, and that namely declares that _CAAEVisModelEvents_ is a data extension of the _CAASysPoint_ component, and that OM-derives from _CATBaseUnknown_
       * `CATAddClassExtension` to declare each additional extended component, such as _CAASysCircle_
       * `CATEndImplementClass` to close the extended component declaration
     * Since none of the _CAAIModelEvents_ methods needs to be redefined, the default constructor and the destructor are enough.

[Top]

* * *
### In Short

This use case shows how to implement the _CATI3DGeoVisu_ interface to display a geometric component in a 3D viewer. _CATI3DGeoVisu_ is implemented in an extension class of the geometric component by deriving the extension from the _CATExtI3DVisu_ adapter, and redefining the `BuildRep` method. `BuildRep` creates and returns the 3D representation that stands for the geometric component in the visualization world using the component geometric parameters.

To enable the representation of the geometric component to be refreshed when the component is modified, the component should implement the _CATIModelEvents_ interface. This is done also using an extension, but can be done for a component family in a single extension for the whole family. Usually, deriving from the _CATExtIModelEvents_ adapter is enough, and no method needs to be redefined.

[Top]

* * *
### References

[1] | [Creating Interfaces](../CAASysUseCases/CAASysSampleOMCreatingInt.md)  
---|---  
[2] | [Creating Components](../CAASysUseCases/CAASysSampleOMCreatingCmp.md)  
[Top]  
  
* * *
### History

Version: **1** [Feb 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
