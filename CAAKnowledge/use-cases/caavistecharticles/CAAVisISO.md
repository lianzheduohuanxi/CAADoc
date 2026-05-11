---
```vbscript
title: "Interactive Set of Objects"
category: "use-case"
module: "CAAVisTechArticles"
tags: ["CATI3DGeoVisu", "CATIModelEvents", "CAAAfrBoundingElementCmd", "CATISO", "CATI2DGeoVisu", "CATICreateInstance", "CAADegClippingByBoxCmd"]
source_file: "Doc/online/CAAVisTechArticles/CAAVisISO.htm"
converted: "2026-05-11T17:31:52.295366"
```

---
# 3D PLM Enterprise Architecture

| 
## 3D Visualization

| 
### Interactive Set of Objects

What is the ISO and how use it?  
---|---|---  
Technical Article  

* * *
### Abstract

The Interactive Set of Objects is an interactive object used to visualize temporary components, those not kept by a V5 document. This article describes it in detail, and explains how to use it. The last section is dedicated to the temporary component creation. 

  * **A CATISO Class Instance **
  * **A Bag of Components**
  * **Managed by  V5 Document Editors**
  * **Like a Root Model**
  * **How Does it Work?**
  * **Creating Temporary Components**
  * **In Short**
  * **References**

---  

* * *
### A CATISO Class Instance

The Interactive Set of Objects is a component [1] whose main class is the _CATISO_ class _._ It implements _CATI3DGeoVisu_ , _CATI2DGeoVisu_ , and _CATIModelEvents_ interfaces, as represented by the following UML diagram:

![](images/CAAVisISOUML.jpg)  
---  

The implementation of the _CATI3DGeoVisu_ (or _CATI2DGeoVisu)_ interface builds a _CAT3DBagRep_ (or _CAT2DBagRep)_ class instance. This set (bag) of graphic representations contains the graphic representations of all components set in the ISO. The next section, A Bag of Components, details this notion of bag.

```vbscript
For the _CATIModelEvents_ interface, the How Does it Work ? section gives you explanations on the role of this interface.

```

[Top]
### A Bag of Components 

The _CATISO_ class contains methods to:

  * **Add** elements in the ISO: the `AddElement `method,
  * **Remove** elements from the ISO: `RemoveElement` method.

The _CATISO_ class contains methods to:
Before adding or removing an element, it is useless to test if the element already exists, because these two method do it. However, you can always need to know if a component is included in the ISO, for that there is the `IsMember` method. 

The introspection methods are: 

  * The `InitElementList``` method.

> It locates an internal "cursor" just before the first element of the ISO. To retrieve the first element of the list, call `InitElementList` and then, `GetNextElement` .

  * The `GetNextElement` method.

> It returns the element just after the current position of the cursor, and then increases the position of the cursor. If the returned value is NULL, the end of the list is reached.

The elements of the ISO are components which must at least implement the _CATI3DGeoVisu_ or the _CATI2DGeoVisu_ interface. The Creating Temporary Components section describes three kind of components that you can use or create. 

[Top]
### Managed by  V5 Document Editors

Each V5 document is interactively controlled by one _CATFrmEditor_ class instance called an **editor**[2] for short. When this object is instantiated, it creates three kinds of  ISO:

  * **Normal** :

Each V5 document is interactively controlled by one _CATFrmEditor_ class instance called an **editor**[2] for short. When this object is instantiated, it creates three kinds of  ISO:
Elements contained in the normal ISO are drawn in taken their graphic attributes into account . The `GetISO` method the _CATFrmEditor_ class retrieves this specific ISO.

 A component with three red axes.  

  * **Furtive** : 

A component with three red axes.
Elements contained in the furtive ISO are drawn in XOR. It is useful for rubber-bending, clipping box,... for a component does not need graphic attributes, but performance. The `GetFurtiveISO` method of the _CATFrmEditor_ class retrieves this specific ISO.

 A clipping box drawn in XOR  

  * **Background** :

A clipping box drawn in XOR
Elements contained in the background ISO are drawn the first. So they are in the background. The `GetBackgrdISO` method of the _CATFrmEditor_ class retrieves this specific ISO.

In the C _ATFrmEditor_ class destructor, these three interactive sets of objects are first emptied and then released. Consequently, in your command, while the editor is alive you must ensure the contents of the ISO. Refer you to the CAAAfrBoundingElementCmd use case [3] for an example.

[Top]
### Like A Root Model

In a V5 document, Part features and the top Product are root components. You can you refer to the referenced article [9] for a brief notion of root object.You will also learn the main role of the unique _CATVisManager_ class instance. 

The _CATISO_ instance class plays the same role. It means that when you want create a new window class [2] for a V5 document, if you want the elements of the ISO to be also drawn in this new window, you must do the relation between each viewer of the window and each Interactive Set of Objects. You can you refer to the use cases [4] [5] which detail the creation of a new window. In the new window class constructor you can have the following lines:

    ...
The _CATISO_ instance class plays the same role. It means that when you want create a new window class [2] for a V5 document, if you want the elements of the ISO to be also drawn in this new window, you must do the relation between each viewer of the window and each Interactive Set of Objects. You can you refer to the use cases [4] [5] which detail the creation of a new window. In the new window class constructor you can have the following lines:
      CATISO * pISO = pEditor->**GetISO**()  ;  
      pISO->**AddViewer**(_pViewer);

      CATISO * pfurtiveISO = pEditor->**GetFurtiveISO**()  ;  
      pfurtiveISO->**AddViewer**(_pViewer);

      CATISO * pbgISO = pEditor->**GetBackgrdISO**()  ;  
      pbgISO->**AddViewer**(_pViewer);

    ...  

---  

The `AddViewer`**** method**** calls the `AttachTo` method of the _CATVisManager_ class with the following arguments:

  * The root model is the _CATISO_ class instance itself 
  * The viewpoint is the main 3D  (2D) viewpoint of the viewer given as an argument
  * The list of interfaces contains CATI3DGeoVisu interface (or CATI2DGeoVisu) 
  * The command selector is the one of the editor of the ISO. ( `GetCommandSelector` method of the _CATFrmEditor_ class)

    HRESULT AttachTo ( CATPathElement* iTreeRoot,
                       CATViewpoint*	iViewpoint,
                       list<IID>&	iVisuList,
                       CATCommand* iSelectorFather = NULL,
                       int iFurtive=0,
                       int iLocalMatrix=0,
                       int iLocalGraphicAttributs=0 );  

---  

int iLocalMatrix=0,
int iLocalGraphicAttributs=0 );
The following schema explains the command tree, and the similitude between a V5 root object and the ISO.

![](images/CAAVisISOCommandTree.jpg)  
---  

The following schema explains the command tree, and the similitude between a V5 root object and the ISO.
The manipulator (CAT3DManipulator/CAT2DManipulator) associated with the graphic representation of the root object, and the ISO are inside the command tree. It enables us to receive the information coming from the end user interactions in the viewer. 

This diagram shows that the complete path of an element into the ISO is first the ISO itself and then the component. Here is the code to create this path:

    ...
This diagram shows that the complete path of an element into the ISO is first the ISO itself and then the component. Here is the code to create this path:
    CATFrmEditor * pEdt = CATFrmEditor::GetCurrentEditor();
    CATISO * pISO = pEdt->**GetISO**();

    CATPathElement pPathElement (pISO);

    PathElement.**AddChildElement**(pComponent);

    ...  

---  

Where `pComponent` is a pointer on an element contained in the ISO. 

[Top]
### How Does it Work?

Where `pComponent` is a pointer on an element contained in the ISO.
When an element is **added** in the ISO, the _CATISO_ class instance keeps the new component in a list, and sends a _CATCreate_ notification thanks to its implementation to the _CATIModelEvents_ interface. The _CATVisManager_ receives the notification and asks the reconstruction of the graphic representation of the ISO. The `Build` method of the _CATI3DGeoVisu_ (or 2D) interface, for the _CATISO_ component, browses the internal list of the ISO, and asks the _CATVisManager_ to retrieve or build the graphic representation of each element of the list. 

When an element is **removed** from the ISO, the element is first removed from the internal list. Then, depending on the second argument of the ` RemoveElement` method, two kinds of notifications can be sent: 

  * The value is **0**(default value): a _CATDelete_ notification is sent. The graphic representation associated with the element to remove is**deleted**. To re-visualize the same element, you must first re-create the graphic representation before using the `AddElement` method.
  * The value is **1** : A notification is sent to erase the element, but its graphic representation is **not deleted**. Consequently, to re-visualize the same element, you do not have to re-create the graphic representation before using the `AddElement` method.

When an element is **removed** from the ISO, the element is first removed from the internal list. Then, depending on the second argument of the ` RemoveElement` method, two kinds of notifications can be sent:
When an element of the ISO is **updated** , thanks to the `UpdateElement` method, a _CATModify_ notification is sent. The _CATVisManager_ will ask for the re-construction of the graphic representation associated with the element to update. This reconstruction must be absolutely done by the _CATVisManager_ thanks to the implementation of the _CATI3DGeoVisu_ (or 2D) interface on the component to update. 

Here is a forbidden scenario:

![](images/CAAVisISOScenarioInterdit.gif)  
---  

Here is a forbidden scenario:
You must not modify the graphic representation of a component included into an ISO.

Here is a possible scenario:

![](images/CAAVisISOScenarioOK.gif)  
---  

Here is a possible scenario:
The step 3 consists in using an interface of the component to modify one or more of its characteristic. These characteristics are parameters used to build the graphic representation, and consequently used in the _CATI3DGeoVisu_ (or 2D) interface. 

You can you refer to the CAADegClippingByBoxCmd use case [6] where elements are added into ISO, removed with or without deletion from the ISO, and updated. 

[Top]
### Creating Temporary Components

You can you refer to the CAADegClippingByBoxCmd use case [6] where elements are added into ISO, removed with or without deletion from the ISO, and updated.
There are three ways to create a component which will be displayed thanks to the Interactive Set of Objects:

  1. Create an instance of the _CATModelForRep3D_ class 
  2. Create a component which derives from the _CATModelForRep3D_ component
  3. Create a component which derives from _CATBaseUnknown_ and implements, at least, the _CATI3DGeoVisu_ interface (or 2D)

Each case is in relationship to a specific usage of the component. 

  1. Create an instance of the _CATModelForRep3D_ class 

It is the simplest way to create a temporary component. Here is an example:

    ...
1. Create an instance of the _CATModelForRep3D_ class
It is the simplest way to create a temporary component. Here is an example:
    CATModelForRep3D *pModel = new **CATModelForRep3D**();

    CAT3DCustomRep *pMyRep = new CAT3DCustomRep() ; 

    ...
CATModelForRep3D *pModel = new **CATModelForRep3D**();
CAT3DCustomRep *pMyRep = new CAT3DCustomRep() ;
    pModel->**SetRep**(pMyRep );

    ...  

---  

The graphic representation is built in your code and associated with the component, `pModel`, thanks to the `SetRep` method of the _CATModelForRep3D_ class. Once the graphic representation is associated with the component, it is hold by the component, you do not have to delete the graphic representation (`pMyRep`). 

![](../CAAIcons/images/hand.gif)You use it when your component is just a visual help, not modifiable and not selectable by the end user. 

The graphic representation is built in your code and associated with the component, `pModel`, thanks to the `SetRep` method of the _CATModelForRep3D_ class. Once the graphic representation is associated with the component, it is hold by the component, you do not have to delete the graphic representation (`pMyRep`).
  2. Create a component which derives from the _CATModelForRep3D_ component

You create a component [1] which Object Modeler and C++ derives from  the _CATModelForRep3D_ component, you create a specific interface [8], and you implement it on your component. This interface will be used as filter of an agent of selection. 

    ...
    **CATPathElementAgent** * pAgent = new CATPathElementAgent(...);
    pAgent->**AddElementType**(IID_ISpecificInterface);
    ...  

---  

To create the component, and set it its graphic representation, the method is identical as the one detailed above:

    ...
To create the component, and set it its graphic representation, the method is identical as the one detailed above:
    CATMyModel *pModel = new **CATMyModel**();

    CAT3DCustomRep *pMyRep = new CAT3DCustomRep() ; 

    ...
CATMyModel *pModel = new **CATMyModel**();
CAT3DCustomRep *pMyRep = new CAT3DCustomRep() ;
    pModel->**SetRep**(pMyRep );

    ...  

---  

where _CATMyModel_ is a component main class which OM and C++ derives from CATModelForRep. If the component implements _CATICreateInstance_ , refer to the use case [7] for a complete implementation. 

![](../CAAIcons/images/hand.gif)You create such a component when the end user must select it without ambiguity. 

where _CATMyModel_ is a component main class which OM and C++ derives from CATModelForRep. If the component implements _CATICreateInstance_ , refer to the use case [7] for a complete implementation.
  3. Create a component which derives from _CATBaseUnknown_ and implements, at least, the _CATI3DGeoVisu_ interface (or 2D)

In fact, there are the following steps:

     * Creating a component  which Object Modeler and C++ derives from _CATBaseUnknown_  
     * Creating and implementing an interface of type which retrieves and sets the characteristics of your component 
     * Implementing _CATI3DGeoVisu_ (or 2D) which uses the interface of type to create the graphic representation 

![](../CAAIcons/images/hand.gif)You create such a component when the graphic representation can change during the life cycle of the component. See the  How does it Work section to understand the life cycle of the graphic representation. The interface of type can also be the filter interface. 

You can refer to the CAADegClippingByBoxCmd use case [7] where these three kinds of components have been implemented.  

[Top]

* * *
### In Short

The Interactive Set of Objects (ISO) is an interactive object handled by the _CATISO_ class. It enables you to display components which are not included in a V5 document. These components must only implement the _CATI3DGeoVisu_ (2D) interface. 

[Top]

* * *
### References

[1] | [Creating Components](../CAASysTechArticles/CAASysCreatingComponent.md)  
---|---  
[2] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)  
[3] | [Creating a Command that Consists in a Dialog Window](../CAAAfrUseCases/CAAAfrSampleDialogOnly.md)  
[4] | [Creating a Document's Window-1](../CAAAfrUseCases/CAAAfrSampleCustomWindow1.md)  
[5] | [Creating a Document's Window-2](../CAAAfrUseCases/CAAAfrSampleCustomWindow2.md)  
[6] | [Visualizing Temporary Components](../CAAVisUseCases/CAAVisSampleISO.md)  
[7] | [Creating Temporary Components](../CAAVisUseCases/CAAVisSampleTempObject.md)  
[8] | [Creating Interfaces](../CAASysTechArticles/CAASysCreatingInterfaces.md)   
[9] | [Using the Visualization Manager](../CAAVisUseCases/CAAVisSampleVisManager.md)  
[Top]  

* * *
### History

Version: **1** [Feb 2004] | Document created  
---|---  
[Top]  

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
