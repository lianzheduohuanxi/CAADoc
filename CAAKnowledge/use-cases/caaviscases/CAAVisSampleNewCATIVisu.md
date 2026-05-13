---
```vbscript
title: "Making a Component Displayable With Your Own Interface"
category: use-case case"
module: "CAAVisUseCases"
tags: ["CAAVisManagerDefaultDocument", "CATI3DGeoVisu", "CAAVisManagerAppli", "CAAVisModelEventsForObject", "CAAIVis2DGraphVisu", "CAAEVis2DGraphVisuForObject", "CAAVisualization", "CATI2GeoVisu", "CAAVisManager", "CATIA", "CAAVisModelObject", "CAAEVisModelEventsuForObject", "CAAVisManagerImpl", "CAAVisManagerComp", "CATIVisu", "CATIModelEvents", "CAAVisManagerInt", "CAAVis2DGraphBoxRep"]
source_file: "Doc/online/CAAVisUseCases/CAAVisSampleNewCATIVisu.htmmd"
converted: "2026-05-11T17:31:52.156240"
```

---
# 3D PLM Enterprise Architecture

|
## 3D Visualization

|
### Making a Component Displayable With Your Own Interface

_Creating and implementing your own visualization interface, and implementing CATIModelEvents_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAVisManager use case. This use case explains how to create and implement a specific visualization interface for geometric components, how to make the visualization manager aware of this interface to display these components, and how to catch the visualization notification to manage the PSO and HSO contents. This article focuses on the specific visualization interface implementation.

  * **What You Will Learn With This Use Case**
  * **The CAAVisManager Use Case**
    * What Does CAAVisManager Do
    * How to Launch CAAVisManager
    * Where to Find the CAAVisManager Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

Geometric components usually implement the visualization interfaces supplied by the Visualization framework, namely _CATI3DGeoVisu_ and _CATI2DGeoVisu_ [1]. This use case is intended to show how to create and implement a visualization interface of your own to make a geometric component displayable in a 3D viewer, and how to make the visualization manager aware of this interface to display this component. Companion articles of this use case deal with the use of the visualization manager [2], and with catching visualization notifications [3].

[Top]
### The CAAVisManager Use Case

CAAVisManager is a set of use cases of the CAAVisualization.edu framework that illustrates CATIA Visualization framework capabilities.

[Top]
#### What Does CAAVisManager Do

CAAVisManager is a set of use cases of the CAAVisualization.edu framework that illustrates CATIA Visualization framework capabilities.
CAAVisManager contains a series of modules that make up a small application. This article focuses on the _CAAIVis2DGraphVisu_ interface, and shows how to create it, and how to implement it for a base geometric component from which derived geometric components, such as a sphere, a cuboid, and a component set, will inherit. It also shows how to implement _CATIModelEvents_ for this base component.

_CAAIVis2DGraphVisu_ provides methods for 3D components that already implement _CATI3DGeoVisu_ to also have a 2D graphic representation used to display each object as a labeled box to build a 2D graph in the 3D window. (_CATI2GeoVisu_ could be used instead of creating a new interface.) _CAAIVis2DGraphVisu_ derives from the _CATIVisu_ interface. This is to make the visualization manager aware of your own interface in addition to _CATI3DGeoVisu_ or _CATI2DGeoVisu_. For this reason, never derive your visualization interfaces from _CATI3DGeoVisu_ or _CATI2DGeoVisu._

[Top]
#### How to Launch the CAAVisManager

To launch CAAVisManager, you will need to set up the build time environment, then compile the four CAAVisManager modules along with their prerequisites, set up the run time environment, and then execute the use case [4]. You cannot launch CAAVisManager itself. CAAVisManager is simply used by the CAAVisManagerAppli use case. Type CAAVisManagerAppli instead of CAAVisManager to display the interactive application along with a viewer that displays the CAAVisManagerDefaultDocument.

[Top]
#### Where to Find the CAAVisManager Code

To launch CAAVisManager, you will need to set up the build time environment, then compile the four CAAVisManager modules along with their prerequisites, set up the run time environment, and then execute the use case [4]. You cannot launch CAAVisManager itself. CAAVisManager is simply used by the CAAVisManagerAppli use case. Type CAAVisManagerAppli instead of CAAVisManager to display the interactive application along with a viewer that displays the CAAVisManagerDefaultDocument.
CAAVisManager code is located in the CAAVisualization.edu framework:

Windows | `InstallRootDirectory/CAAVisualization.edu/`

CAAVisManager code is located in the CAAVisualization.edu framework:
Windows | `InstallRootDirectory/CAAVisualization.edu/`
Unix | `InstallRootDirectory/CAAVisualization.edu/`

where `InstallRootDirectory` is the root directory of your CAA V5 installation.

CAAVisManager includes the following modules:

CAAVisManagerAppli.m | Contains the interactive application, the windows and the documents

CAAVisManager includes the following modules:
CAAVisManagerAppli.m | Contains the interactive application, the windows and the documents
CAAVisManagerComp.m | Contains the geometric components to display
CAAVisManagerImpl.m | Contains the extension classes required to make the geometric components displayable
CAAVisManagerInt.m | Contains the interfaces implemented by the geometric components, especially the visualization interface. Their header files are located in the PrivateInterfaces directory

CAAVisManager includes the following files to create and implement a customized visualization interface:

**PrivateInterfaces directory**
---
CAAVisManager includes the following files to create and implement a customized visualization interface:
CAAIVis2DGraphVisu.h | Header file for the customized visualization interface _CAAIVis2DGraphVisu_

In CAAVisManagerInt.m

**src directory**
---
In CAAVisManagerInt.m
CAAIVis2DGraphVisu.cpp | Source file for the customized visualization interface _CAAIVis2DGraphVisu_

In CAAVisManagerImpl.m

**LocalInterfaces directory**
---
In CAAVisManagerImpl.m
CAAEVis2DGraphVisuForObject.h | Header file for the extension class that implements _CAAIVis2DGraphVisu_
CAAEVisModelEventsuForObject.h | Header file for the extension class that implements _CATIModelEvents_

**CAAVisManagerImpl.m/src directory**
CAAEVis2DGraphVisuForObject.h | Header file for the extension class that implements _CAAIVis2DGraphVisu_
CAAEVisModelEventsuForObject.h | Header file for the extension class that implements _CATIModelEvents_
CAAEVis2DGraphVisuForObject.cpp | Source file for the extension class that implements _CAAIVis2DGraphVisu_
CAAEVisModelEventsuForObject.cpp | Source file for the extension class that implements _CATIModelEvents_

[Top]
### Step-by-Step

CAAEVisModelEventsuForObject.cpp | Source file for the extension class that implements _CATIModelEvents_
To implement _CATI3DGeoVisu_ and _CATIModelEvents_ , there are four main steps:

  1. Creating the CAAIVis2DGraphVisu Interface
  2. Implementing the CAAIVis2DGraphVisu Interface
  3. Implementing the BuildRep Method of CAAIVis2DGraphVisu
  4. Implementing the CATIModelEvents Interface

[Top]
#### Creating the CAAIVis2DGraphVisu Interface

4. Implementing the CATIModelEvents Interface
The _CAAIVis2DGraphVisu_ interface is intended to display the set, cuboid, and sphere components in a tree showing the document tree structure. Each component is displayed as a colored box with its type written in the box.

  1. The _CAAIVis2DGraphVisu_ header file is located in the PrivateInterfaces directory.

         #include "CATIVisu.h"
         #include "CAT3x3Matrix.h"
         #include "CAAVisManagerInt.h"

1. The _CAAIVis2DGraphVisu_ header file is located in the PrivateInterfaces directory.
         extern  ExportedByCAAVisManagerInt IID IID_CAAIVis2DGraphVisu;

         class  ExportedByCAAVisManagerInt CAAIVis2DGraphVisu : public CATIVisu

         {
extern  ExportedByCAAVisManagerInt IID IID_CAAIVis2DGraphVisu;
class  ExportedByCAAVisManagerInt CAAIVis2DGraphVisu : public CATIVisu
           CATDeclareInterface;
           public:
             virtual CAT3x3Matrix & GetPositioningMatrix(#)=0;
             virtual void IncrementPositioningMatrix(#)=0;

         };

---

_CAAIVis2DGraphVisu_ derives from the _CATIVisu_ interface. As for any interface, its header file includes the `CATDeclareInterface` macro. Its methods are:

`BuildRep` | Inherited from _CATIVisu_ , it builds and returns the representation associated with the geometric component to display in a viewer
---|---
`GetPositioningMatrix` | Returns the representation positioning matrix
`IncrementPositioningMatrix` | Computes the representation positioning matrix
  2. The _CAAIVis2DGraphVisu_ source file is located in CAAVisManagerInt.m.
         #include "CAAIVis2DGraphVisu.h"

2. The _CAAIVis2DGraphVisu_ source file is located in CAAVisManagerInt.m.
         IID IID_CAAIVis2DGraphVisu =  {
            0x2ccd5540,
            0xd884,
            0x11d3,

            {0x9e, 0xd6, 0x00, 0x50, 0x8b, 0x12, 0x96, 0xfa}
         };

0xd884,
0x11d3,
         CATImplementInterface(CAAIVis2DGraphVisu, **CATBaseUnknown**);

---

```vbscript
CATImplementInterface(CAAIVis2DGraphVisu, **CATBaseUnknown**);
The source file contains the interface IID [5], and the `CATImplementInterface` macro to state that _CAAIVis2DGraphVisu_ OM-derives [6] from _CATBaseUnknown_.

 Note that even if _CAAIVis2DGraphVisu_ C++-derives from _CATIVisu_ , it's useless to make it also OM-derive from _CATIVisu_ , and much safer to OM-derive it from _CATBaseUnknown_. This satisfies the Determinism principle in case of your component OM-derives from another one, or if your component implements several visualization interfaces that all must C++-derive from CATIVisu.
```

[Top]
#### Implementing the CAAIVis2DGraphVisu Interface

The _CAAEVis2DGraphVisuForObject_ header file is as follows.

    #include "CAAVis2DGraphVisuAdapter.h"

    class CAAEVis2DGraphVisuForObject : public CAAVis2DGraphVisuAdapter
    {
      **CATDeclareClass** ;
class CAAEVis2DGraphVisuForObject : public CAAVis2DGraphVisuAdapter
```vbscript
      public :

```

        CAAEVis2DGraphVisuForObject(#);
        virtual ~CAAEVis2DGraphVisuForObject(#);

        **CATRep * BuildRep(#);**

```vbscript
CAAEVis2DGraphVisuForObject(#);
virtual ~CAAEVis2DGraphVisuForObject(#);
      private:
        CAAEVis2DGraphVisuForObject(const CAAEVis2DGraphVisuForObject &iObjectToCopy);

```

    };

---

_CAAEVis2DGraphVisuForObject_ derives from _CAAVis2DGraphVisuAdapter_ , that provides the code for the non described `GetPositioningMatrix` and `IncrementPositioningMatrix` methods. _CAAVis2DGraphVisuAdapter_ derives from the _CATExtIVisu_ class that provides the methods of _CATIVisu_ that don't need to be redefined. The `BuildRep` method is the method for making object displayable. As any class that makes up a component, its header file includes the `CATDeclareClass` macro. Note that the copy constructor is declared as private, and is not implemented. This prevents the compiler from creating a public one without you know. This is to prevent clients from creating instances from an existing one, that they normally should not handle, except using interface pointers.

The _CAAEVis2DGraphVisuForObject_ source file is as follows.

    ...
    #include "TIE_CAAIVis2DGraphVisu.h"
    **TIE_CAAIVis2DGraphVisu(CAAEVis2DGraphVisuForObject);**

    **CATImplementClass**(CAAEVis2DGraphVisuForObject,
                      **DataExtension** ,
                      CATBaseUnknown,
                      **CAAVisModelObject**);

CATBaseUnknown,
    CAAEVis2DGraphVisuForObject::CAAEVis2DGraphVisuForObject(#) {}

    CAAEVis2DGraphVisuForObject::~CAAEVis2DGraphVisuForObject(#) {}

    **CATRep *** CAAEVis2DGraphVisuForObject::**BuildRep**(#)
    {
      ...
    }

---

The main points of this source file are:

  * _CAAEVis2DGraphVisuForObject_ implements the _CAAIVis2DGraphVisu_ interface: this is expressed thanks to the `TIE_CAAIVis2DGraphVisu` macro
  * _CAAEVis2DGraphVisuForObject_ implements the _CAAIVis2DGraphVisu_ interface for the _CAAVisModelObject_ component as a data extension. This is expressed using the `CATImplementClass` macro
  * The `BuildRep` method is the only redefined method of _CATIVisu_. It should return a pointer to the component representation, that is, a pointer to a _CAT2DRep_ in this case.

[Top]
#### Implementing the BuildRep Method of CAAIVis2DGraphVisu

The `BuildRep` method is implemented using three sub steps.

The `BuildRep` method is implemented using three sub steps.
  1. Declaring the representation to return

         CATRep * CAAEVis2DGraphVisuForObject::**BuildRep**(#)

         {
           **CAT2DBagRep** * pCurrentObjectBagRep = NULL;
           ...

---

The _CAT2DBagRep_ class can contain any kind of 2D representation.

  2. Creating the box representation

         ...
The _CAT2DBagRep_ class can contain any kind of 2D representation.
2. Creating the box representation
           CAAIVisModelObject *PtrVMO=NULL;
           HRESULT rc = QueryInterface(IID_CAAIVisModelObject,(void **)&PtrVMO);
```vbscript
           if ( SUCCEEDED(rc) )

```

           {
CAAIVisModelObject *PtrVMO=NULL;
HRESULT rc = QueryInterface(IID_CAAIVisModelObject,(void **)&PtrVMO);
if ( SUCCEEDED(rc) )
             char * Type = NULL;
             PtrVMO->GetType(&Type);

```vbscript
             pCurrentObjectBagRep = new CAAVis2DGraphBoxRep(Type);

```

             delete [] Type;

             ...

---

delete [] Type;
The box displays the component type. To retrieve this type, a pointer to the _CAAIVisModelObject_ interface is needed, with which we can call the `GetType` method that returns this type as a character string. A specific representation, the _CAAVis2DGraphBoxRep_ , is instantiated.

  3. Positioning the representation box in the tree

This code is specific to the example. It is not described here and uses the methods of the adapter.

[Top]
#### Implementing the CATIModelEvents Interface

This code is specific to the example. It is not described here and uses the methods of the adapter.
_CAAVisModelEventsForObject_ implements the _CATIModelEvents_ interface by deriving from the _CATExtIModelEvents_ adapter.

  1. Create the header file.

         #include "CATExtIModelEvents.h"

_CAAVisModelEventsForObject_ implements the _CATIModelEvents_ interface by deriving from the _CATExtIModelEvents_ adapter.
1. Create the header file.
         class CAAEVisModelEventsForObject : public **CATExtIModelEvents**

         {
           **CATDeclareClass** ;
class CAAEVisModelEventsForObject : public **CATExtIModelEvents**
           public :
             CAAEVisModelEventsForObject(#);
             virtual ~CAAEVisModelEventsForObject(#);
           private :
           CAAEVisModelEventsForObject(const CAAEVisModelEventsForObject &iObjectToCopy);

         };

---

```vbscript
CAAEVisModelEventsForObject(const CAAEVisModelEventsForObject &iObjectToCopy);
As any class that makes up a component, its header file includes the `CATDeclareClass` macro. None of the _CATIModelEvents_ methods needs to be redefined. Note that the copy constructor is declared as private, and is not implemented. This prevents the compiler from creating a public one without you know. This is to prevent clients from creating instances from an existing one, that they normally should not handle, except using interface pointers.

  2. Create the source file.
```

         #include "CAAEVisModelEventsForObject.h"
         #include "TIE_CATIModelEvents.h"
As any class that makes up a component, its header file includes the `CATDeclareClass` macro. None of the _CATIModelEvents_ methods needs to be redefined. Note that the copy constructor is declared as private, and is not implemented. This prevents the compiler from creating a public one without you know. This is to prevent clients from creating instances from an existing one, that they normally should not handle, except using interface pointers.
2. Create the source file.
         TIE_CATIModelEvents(CAAEVisModelEventsForObject);

         CATImplementClass(CAAEVisModelEventsForObject,

                           **DataExtension** ,
```vbscript
TIE_CATIModelEvents(CAAEVisModelEventsForObject);
```vbscript
CATImplementClass(CAAEVisModelEventsForObject,
```

                           CATBaseUnknown,
```

                           **CAAVisModelObject**);

```vbscript
CATImplementClass(CAAEVisModelEventsForObject,
CATBaseUnknown,
         CAAEVisModelEventsForObject::CAAEVisModelEventsForObject(#) {}

         CAAEVisModelEventsForObject::~CAAEVisModelEventsForObject(#) {}

```

---

The main points of this source file are:

     * _CAAEVisModelEventsForObject_ implements the _CATIModelEvents_ interface: this is expressed thanks to the `TIE_CATIModelEvents` macro
     * _CAAEVisModelEventsForObject_ implements the _CATIModelEvents_ interface for the _CAAVisModelObject_ component as a data extension. This is expressed using the `CATImplementClass` macro
     * The adapter provide the code for the _CATIModelEvents_ methods.

[Top]

* * *
### In Short

This use case shows how to implement an visualization interface of your own, named _CAAIVis2DGraphVisu_. It is intended to display a geometric component as a labeled box in an object tree.___CAAIVis2DGraphVisu_ is implemented by an extension class of the base graphic component and so applies to all derived graphic component, since the representations differ only by the type printed in the box. The `BuildRep` method creates and returns the 2D representation that stands for the geometric component in the component tree. The geometric component also implements _CATI3DGeoVisu_ to display in the 3D viewer.

To enable the representation of the geometric component to be refreshed when the component is modified, the component should implement the _CATIModelEvents_ interface. This is done also using an extension class of the base geometric component, and any derived geometric component inherits the implementation of this interfaces. Usually, deriving from the _CATExtIModelEvents_ adapter is enough, and no method needs to be redefined.

[Top]

* * *
### References

[1] | [Making a Component Displayable With CATI3DGeoVisu](CAAVisSampleCATIVisu.md)
---|---
[2] | [Using the Visualization Manager](CAAVisSampleVisManager.md)
[3] | [Catching the Visualization Notifications](CAAVisSampleCatchNotifications.md)
[4] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[5] | [About Globally Unique IDentifiers](../CAASysQuickRefs/CAASysGUID.md)
[6] | [Object Modeler Component and Implementation Inheritances](../CAASysTechArticles/CAASysOMInheritance.md)
[Top]

* * *
### History

Version: **1** [May 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
