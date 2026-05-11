---
title: "Creating Temporary Components"
category: "use case"
module: "CAAVisUseCases"
tags: ["CATInstantiateComponent", "CATI3DGeoVisu", "CAAVisWireBoxComp", "CAAVisualization", "CAAVisTemporaryObjects", "CAADegGeoCommands", "CAAEVisCreateInstanceForWireBox", "CAAVisModelForRep", "CATIA", "CAAIVisTextModel", "CAAGeometry", "CAAIVisWireBox", "CAAEVisWireBox", "CAAEVisVisuWireBox", "CAAVisWireBox", "CAAVisTextModel", "CAADialogEngine", "CATICreateInstance", "CAADegClippingByBoxCmd"]
source_file: "Doc/online/CAAVisUseCases/CAAVisSampleTempObject.htm"
converted: "2026-05-11T17:31:52.178221"
---
# 3D PLM Enterprise Architecture

| 
## 3D Visualization

| 
### Creating Temporary Components

How to create displayable component   
---|---|---  
Use Case  
  
* * *
### Abstract

A temporary component is a component which is not integrated into the data model of a V5 document. In most cases it is a simple component to help the understanding of an interactive command. This article shows how to create a such object depending on its usage. To take full advantage of this article, you can first read the technical article about the Interactive Set of Objects and the temporary components [1]. 

  * **What You Will Learn With This Use Case**
  * **The CAAVisTemporaryObjects Use Case**
    * What Does CAAVisTemporaryObjects Do
    * How to Launch CAAVisTemporaryObjects
    * Where to Find the CAAVisTemporaryObjects Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how create temporary components depending on their usage:

  * A component which only needs to be visualized but not to be selected

> It is simple instance of the _CATModelForRep3D_ class

  * A component which needs to be visualized and to be selected

> It is a component which derives from the _CATModelForRep3D_ component. Consequently, it already implements _CATI3DGeoVisu._ So you have only to create and implement a specific interface which will be the discriminant interface for the agent of selection.  

  * A component whose the graphic representation can be modified while it is always in the ISO

> The usage of the _CATModelForRep3D_ is not recommended for this last case. Refer you to the referenced article [1] for details about the reason. So, the component is a simple component which implements _CATI3DGeoVisu_ and an interface of type. A such interface sets  and gets the "intrinsic" data of the component, and enables us to build the graphic representation.  

These temporary components are visualized thanks the Interactive Set of Objects. The "Visualizing Temporary Components" article [2] details how to insert, remove, update a component of the ISO.  [Top]
### The CAAVisTemporaryObjects Use Case

CAAVisTemporaryObjects is a use case of the CAADialogEngine.edu and CAAVisualization.edu frameworks that illustrates DialogEngine, ApplicationFrame, and Visualization frameworks capabilities. [Top]
#### What Does CAAVisTemporaryObjects Do

CAAVisTemporaryObjects creates three temporary components. There are used in the **Clipping By Box** command of the CAAGeometry document [3]. The referenced article [2] details the state chart of this command. But to sum up, this command is a state command to remove all the points of the document outside a given box. This clipping box is defined by the end user: first, he/she defines its location by selecting an existing point. Then, from the selected point a first clipping box is displayed, and he/she can move the mouse to increase or decrease the size of the box. Now, let us see how the temporary components are used in this command. At the beginning of the command, the following text is displayed in (0,0,0):  
---  
  
Once the text is selected, the end user must select a point to define the center of the wire box. At this point location, a trihedral is displayed

![](images/CAAVisSampleTempObjectTrihedral.jpg)  
---  
  
and a wire box is drawn in the furtive ISO:

![](images/CAAVisSampleTempObjectWireBox.jpg)  
---  
  
The text, the  trihedral and the wire box are three temporary components. Now, let us explained the internal data:

**The trihedral**

![](images/CAAVisSampleTempObjectOMTTrihedral.jpg)  
---  
  
The trihedral is an instance of the CATModelForRep3D component. This component implements _CATI3DGeoVisu_ , that allows you to set the component instance in the ISO. 

**The text**

![](images/CAAVisSampleTempObjectOMTText.jpg)  
---  
  
The trihedral is an instance of the CAAVisTextModel component. This component Object Modeler and C++ derives from the CATModelForRep3D component. Consequently, implementing the _CATI3DGeoVisu_ interface, any instance of the CAAVisTextModel component can be visualized in the ISO. 

The CAAVisTextModel component implements the _CAAIVisTextModel_ interface to enable us selecting without ambiguity an instance of this component. This interface will be the filter of the agent of selection, a _CATPathElementAgent_ class [4]. However, without this interface, the trihedral is nevertheless selectable, but the only one interface you can use is _CATI3DGeoVisu_. This interface being implemented by all visualized components, it is not a discriminant interface. 

At last, the CAAVisTextModel component implements the _CATICreateInstance_ interface to avoid to export the component implementation class. 

**The wire box**

![](images/CAAVisSampleTempObjectOMTWireBox.jpg)  
---  
  
The wire box is an instance of the CAAVisWireBox component. Unlike the first two components, the CAAVisWireBox is not a CATModelForRep3D component. The reason comes from that the graphic representation will change during the life time of the state command. To sump up, once a component is into the ISO, you should not use/modify its graphic representation. The construction must be controlled by the _CATVisManager_. Refer to the technical article [1] for details about the life cycle of the graphic representation.

The CAAVisWireBox component implements the _CAAIVisWireBox_ to set and retrieve the size and location of the wire box.

The CAAVisWireBox component implements the _CATI3DGeoVisu_ to build the graphic representation in taken into account the values returned by the _CAAIVisWireBox_ interface.

At last, the CAAVisWireBox component implements the _CATICreateInstance_ interface to avoid to export the component implementation class. 

[Top]
#### How to Launch CAAVisTemporaryObjects

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario:

Launch CATIA. When the application is ready:

  * On the **Start** menu, point to **Infrastructure** , and then click **CAA V5: Geometrical Creation**
  * Launch the **Point** (![](../CAAAfrUseCases/images/CAAAfrPointIconNormal.jpg))command to create some points 
    * In the **Basic Elements** toolbar 
    * In the**Insert** menu, click **Point**  

  * Launch the **Clipping By Box** (![](images/CAAVisClippingByBoxIcon.jpg))command in the **Clipping** toolbar
  * Select the **ISO Selection** text located at the origin of the model (0,0,0)

> After the selection, the text diseappears

  * Select a **Point** as clipping box center

> After the selection, the trihedral is displayed. 

  * **Move** the mouse, and click **left** to stop the command

All points outside the clipping box are removed from the current CAAGeometry document.

[Top]
#### Where to Find the CAAVisTemporaryObjects Code

The CAAVisTemporaryObjects use case is made of several classes located:

  * In the CAADegGeoCommands.m module of the CAADialogEngine.edu framework:
Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  
---|---  
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
  
The _CAADegClippingByBoxCmd_ class contains the creation of the trihedral component.

  * In the CAAVisModelForRep.m module of the CAAVisualization.edu framework:
Windows | `InstallRootDirectory\CAAVisualization.edu\CAAVisModelForRep.m\`  
---|---  
Unix | `InstallRootDirectory/CAAVisualization.edu/CAAVisModelForRep.m/`  
  
This module contains the creation of the text component. The _CAADegClippingByBoxCmd_ class contains the code which creates its graphic representation.

  * In the CAAVisWireBoxComp.m module of the CAAVisualization.edu framework:
Windows | `InstallRootDirectory\CAAVisualization.edu\CAAVisWireBoxComp.m\`  
---|---  
Unix | `InstallRootDirectory/CAAVisualization.edu/CAAVisWireBoxComp.m/`  
  
This module contains the creation of the  "wire box" component. 

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are three logical steps in CAAVisTemporaryObjects:

  1. Creating the Trihedral Component
  2. Creating the Text Component
  3. Creating the Wire Box Component

[Top]
#### Creating the Trihedral Component

The Trihedral component is a simple _CATModelForRep3D_ class instance. In the _CAADegClippingByBoxCmd_ class constructor you have the following instruction:
    
    
    ...
    _pCenterBoxModel     = new CATModelForRep3D(); 
    ...  
  
---  
  
Where `_pCenterBoxModel` is a data member of the _CAADegClippingByBoxCmd_ class. 

Once a Point is selected, the trihedral is set in the ISO. Its graphic representation must be first defined according to the position of the selected point. Here it is the code to build the graphic representation, and associate it with the trihedral component. 
    
    
    ...
    HRESULT CAADegClippingByBoxCmd::CreateRepForCenterBox()
    {
    ...
       CAT3DCustomRep * pRepForCenter = new **CAT3DCustomRep**();
    
       **CATGraphicAttributeSet**  CenterGa ;
    
       float coord[3] ;
       coord[0] = _CenterBox.GetX() ;
       coord[1] = _CenterBox.GetY() ;
       coord[2] = _CenterBox.GetZ();
    
       CATMathPointf StartPoint = _CenterBox ;
       CATMathDirectionf DirX (1.f,0.f,0.f);
       CATMathDirectionf DirY (0.f,1.f,0.f);
       CATMathDirectionf DirZ (0.f,0.f,1.f);
    
       int LengthIn_mm      = 5;
       int ArrowHeadHeight  = 1;
       int BaseLength       = 0 ;
    
       CAT3DFixedArrowGP * pCenterGpX = new **CAT3DFixedArrowGP**(StartPoint,
                                                           DirX,LengthIn_mm,ArrowHeadHeight,
                                                           BaseLength);
       CAT3DFixedArrowGP * pCenterGpY = new CAT3DFixedArrowGP(StartPoint,
                                                           DirY,LengthIn_mm,ArrowHeadHeight,
                                                           BaseLength);
       CAT3DFixedArrowGP * pCenterGpZ = new CAT3DFixedArrowGP(StartPoint,
                                                           DirZ,LengthIn_mm,ArrowHeadHeight,
                                                           BaseLength);
       
       pRepForCenter->**AddGP**(pCenterGpX,CenterGa);
       pRepForCenter->AddGP(pCenterGpY,CenterGa);
       pRepForCenter->AddGP(pCenterGpZ,CenterGa);
    
       CAT3DBoundingSphere be(coord,0.f,1.f) ;
       pRepForCenter->**SetBoundingElement**(be) ;
       
       _pCenterBoxModel->**SetRep**(pRepForCenter) ;
    ...  
  
---  
  
The graphic representation, `pRepForCenter`, of the trihedral is composed of three _CAT3DFixedArrowGP class_ instances _._ Each one is fixed at the center of the clipping box. `_CenterBox` is a data member of the _CAADegClippingByBoxCmd_ class initialized from the value of the agent of selection. Refer to the _CAADegClippingByBoxCmd_ class code for more details.

The `SetRep` method of the _CATModelForRep3D_ class enables you to associate with the component the graphic representation. You do not have to release the `pRepForCenter` pointer. 

[Top]
#### Creating the Text Component

The text (ISO Selection) component, named CAAVisTextModel, is a component which derives from the _CATModelForRep3D_ component. There are six sub-steps:

  1. Creating the CAAIVisTextModel Interface
  2. Creating the CAAVisTextModel Component and Implementing the CAAIVisTextModel Interface
  3. Implementing the CATICreateInstance Interface
  4. Updating the Interface Dictionary
  5. Instantiating the Component 
  6. Creating the Graphic Representation

 

  1. **Creating the CAAIVisTextModel interface**

Here it is the CAAIVisTextModel.h file that you retrieve in the PublicInterfaces of the CAAVisualization.edu framework 
    
    ...
    class ExportedByCAAVisModelForRep **CAAIVisTextModel** : public CATBaseUnknown
    {
      CATDeclareInterface;
    
      public:
          virtual HRESULT **SetGraphicRepresentation**(CATRep * iRep) = 0;
    };
    ...  
  
---  
  
This interface will be used in the _CAADegClippingByBoxCmd_   state command as filter for an agent of selection. Refer to the "Defining the State Chart Diagram" step of the referenced article [2].

This interface contains the `SetGraphicRepresentation` method to associate the graphic representation with the component. The next section, Creating the CAAVisTextModel Component and Implementing the CAAIVisTextModel Interface details the reason of this method.

  2. **Creating the CAAVisTextModel Component and Implementing the CAAIVisTextModel Interface**

Here it is the CAAVisTextModel.h ` `file. 
    
    ... 
    class CAAVisTextModel : public **CATModelForRep3D**
          
    {
             CATDeclareClass;
    
     public:
             CAAVisTextModel() ;
             virtual ~CAAVisTextModel();
    
             virtual HRESULT **SetGraphicRepresentation**(CATRep *iRep) ;
    
     private:
             CAAVisTextModel(const CAAVisTextModel &iObjectToCopy);
             CAAVisTextModel & operator = (const CAAVisTextModel &iObjectToCopy);
    };  
  
---  
  
The _CAAVisTextModel_ class derives from the _CATModelForRep3D_ class. The `CATDeclareClass` macro declares that the _CAAVisTextModel_ class belongs to a component. Note that the copy constructor and the assignment operator are set as private, and are not implemented in the source file. This prevents the compiler from creating them as public without you know. The `SetGraphicRepresentation` method is the only one method of the _CAAIVisTextModel_ interface. 

Here it is now the source file, CAAVisTextModel.cpp 
    #include "CAAVisTextModel.h"
    #include "TIE_CAAIVisTextModel.h"
    TIE_**CAAIVisTextModel**(CAAVisTextModel);
    
    **CATImplementClass**(CAAVisTextModel,Implementation ,**CATModelForRep3D** , CATNull);
    
    CAAVisTextModel::CAAVisTextModel():CATModelForRep3D()  {}
    
    CAAVisTextModel::~CAAVisTextModel() {}  
  
---  
  
The _CAAVisTextModel_ class states that it implements the _CAAIVisTextModel_ __ interface thanks to the `TIE_CAAIVisTextModel` macro. 

The `CATImplementClass` macro declares that the _CAAVisTextModel_ class is a component main class thanks the `Implementation` keyword, and OM-derives [5] from _CATModelForRep3D._ The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension. 

The implementation of the `SetGraphicRepresentation` method is as follows:
    
    HRESULT CAAVisTextModel::**SetGraphicRepresentation**(CATRep *iRep)
    {
        **SetRep**(iRep);
    
        return S_OK ;
    }  
  
---  
  
This method uses the `SetRep` method of the _CATModelForRep3D_ class.  Refer to the Creating the Graphic Representation step for its usage.

Note: If you do not instantiate the CAAVisTextModel component with the _CATICreateInstance_ interface, the `SetGraphicRepresentation` method is useless, since you have a direct access to a _CATModelForRep3D_ class instance. 

  3. **Implementing the CATICreateInstance  interface**

Refer to "Creating a Component" article [6] for details about the creation of the _CAAEVisCreateInstanceForTextModel_ class.

  4. **Updating the Interface Dictionary**

```vbscript
Do not forget to update the interface dictionary, here it is an extract of the CAAVisualization.edu.dico file located in the CAAVisualization.edu/CNext/code/dictionary directory.
    
```

    CAAVisTextModel        CAAIVisTextModel         libCAAVisModelForRep
    CAAVisTextModel        CATICreateInstance       libCAAVisModelForRep  
  
---  
  5. **Instantiating the Component**

It is an extract of the _CAADegClippingByBoxCmd_   state command. The CAAVisTextModel component is created in the constructor class as such that:
    
    ...
    ::**CATInstantiateComponent**("CAAVisTextModel",IID_CAAIVisTextModel,
                                     (void**)&_pITextToSelectModel);
    ...  
  
---  
  
`_pITextToSelectModel` is a data member of the _CAADegClippingByBoxCmd_   class. It will be used to handle the CAAVisTextModel component instance. 

  6. **Creating the Graphic Representation**

Once an instance of the CAAVisTextModel component is created, to visualize it, its graphic representation must be created and associated with the component. 

Here it is an extract of the _CAADegClippingByBoxCmd_   state command. 
    
    ...
    HRESULT CAADegClippingByBoxCmd::**CreateRepForText**()
    {      
       **CAT3DCustomRep** * pRepForText= new **CAT3DCustomRep**();
    
       **CATGraphicAttributeSet**   TextGa ;
       
       CATMathPointf  TextPos(0.f,0.f,0.f);
      
       CATUnicodeString TextValue ="ISO Selection" ;
       CAT3DAnnotationTextGP   *pTextGP = new **CAT3DAnnotationTextGP**(TextPos,TextValue);
     
       pRepForText->AddGP(pTextGP,TextGa);
    
      _pITextToSelectModel->**SetGraphicRepresentation**(pRepForText) ;
    ...  
  
---  
  
The graphic representation of the CAAVisTextModel component, `pRepForText,` is a _CAT3DCustomRep_ class instance with only one graphic primitive, a _CAT3DAnnotationTextGP_ class instance. 

`pRepForText`, is associated with the CAAVisTextModel component thanks the `SetGraphicRepresentation` method of the _CAAIVisTextModel_ interface. Once done, the graphic representation is "hold" by the CATModelForRep3D component (upper component of the CAAVisTextModel component). You do not have to release the `pRepForText` pointer. 

[Top]
#### Creating the Wire Box Component

The "Wire box" component is named CAAVisWireBox. There are six sub-steps to define it:

  1. Creating the CAAVisWireBox Component
  2. Creating CAAIVisWireBox Interface
  3. Implementing CATICreateInstance Interface
  4. Implementing CAAIVisWireBox Interface
  5. Implementing CATI3DGeoVisu Interface
  6. Updating the Interface Dictionary

 
  1. **Creating the CAAVisWireBox Component**

Here it is the CAAVisWireBox.h file 
    #include "CATBaseUnknown.h"
    
    class  **CAAVisWireBox** : public CATBaseUnknown
    {
      CATDeclareClass;
    
      public :
        CAAVisWireBox();
        virtual ~CAAVisWireBox();
    
      private:
        CAAVisWireBox(const CAAVisWireBox &iObjectToCopy);
        CAAVisWireBox & operator = (const CAAVisWireBox &iObjectToCopy);
     
    };  
  
---  
  
The _CAAVisWireBox_ class derives from the _CATBaseUnknown_ class. The `CATDeclareClass` macro declares that the _CAAVisWireBox_ class belongs to a component. Note that the copy constructor and the assignment operator are set as private, and are not implemented in the source file. This prevents the compiler from creating them as public without you know. 

Here it is the CAAVisWireBox.cpp file 
    #include "CAAVisWireBox.h"
    
    **CATImplementClass**(CAAVisWireBox,Implementation,CATBaseUnknown,CATNull);
    
    CAAVisWireBox::CAAVisWireBox(){}
    
    CAAVisWireBox::~CAAVisWireBox(){}  
  
---  
  
The `CATImplementClass` macro declares that the _CAAVisWireBox_ class is a component main class thanks the `Implementation` keyword, and OM-derives from _CATBaseUnknown._ The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension. 

  2. **Creating CAAIVisWireBox interface**

Here it is the CAAIVisWireBox.h file that you retrieve in the PublicInterfaces of the CAAVisualization.edu framework 
    
    ...
    class ExportedByCAAVisWireBoxComp **CAAIVisWireBox** : public CATBaseUnknown
    {
      CATDeclareInterface;
    
      public:
      virtual HRESULT **SetDimBox** ( const float iDimBox ) = 0;
      virtual HRESULT **GetDimBox** (float * oDimBox ) = 0;
    
      virtual  HRESULT  **SetCenterBox**(const CATMathPoint & iCenter)  =0 ;
      virtual  HRESULT  **GetCenterBox**(CATMathPoint & oCenter) const  =0 ;
    };
    ...  
  
---  
  
The CAAIVisWireBox is an interface of "type", it enables you to define or retrieve the characteristics of the wire box:

     * Its **size** : `SetDimBox` and `GetDimBox` are the methods to valuate or retrieve the size of the wire box.
     * Its **location** : `SetCenterBox` and `GetCenterBox` are the methods to valuate or retrieve the position of the wire box in the model.

This interface will be used:

     * In the _CAADegClippingByBoxCmd_ state command to set the values depending on the end user interactions. Refer to the "Managing Wire Box Component" step of the referenced article [2].
     * In the _CATI3DGeoVisu_ implementation, to retrieve the values and build the graphic representation depending on them. Refer to the Implementing CATI3DGeoVisu step. 

  3. **Implementing CATICreateInstance interface**

Refer to "Creating a Component" article [6] for details about the creation of the _CAAEVisCreateInstanceForWireBox_ class. 

  4. **Implementing CAAIVisWireBox interface**

The CAAEVisWireBox class is the implementation of the  CAAIVisWireBox interface for the _CAAVisWireBox_ component. Refer to the code itself. 

  5. **Implementing CATI3DGeoVisu interface**

Since the CAAVisWireBox component does not derive from the CATModelForRep3D component, you must implement the _CATI3DGeoVisu_ interface to set the component into the ISO. 

Here it is the CAAEVisVisuWireBox.h file:
    #include "CATExtIVisu.h"   // Need to derive from
    
    class CAAEVisVisuWireBox : public CATExtIVisu 
    {
      CATDeclareClass;
    
      public:
        CAAEVisVisuWireBox();
        virtual ~CAAEVisVisuWireBox();
    
        virtual  CATRep * **BuildRep**();
    
      private:
      CAAEVisVisuWireBox(const CAAEVisVisuWireBox &iObjectToCopy);
      CAAEVisVisuWireBox & operator = (const CAAEVisVisuWireBox &iObjectToCopy);
    };  
  
---  
  
The _CAAEVisVisuWireBox_ class derives from the _CATExtIVisu_ class. The `CATDeclareClass` macro declares that the _CAAEVisVisuWireBox_ class belongs to a component. Note that the copy constructor and the assignment operator are set as private, and are not implemented in the source file. This prevents the compiler from creating them as public without you know. Only the `BuildRep` method of the _CATI3DGeoVisu_ interface is overwritten. 

Here it is the CAAEVisVisuWireBox.cpp file:
    
    ...
    #include "TIE_CATI3DGeoVisu.h"
    **TIE_CATI3DGeoVisu**(CAAEVisVisuWireBox);
    
    CATImplementClass(CAAEVisVisuWireBox, DataExtension, CATBaseUnknown, **CAAVisWireBox**);
    
    CAAEVisVisuWireBox::CAAEVisVisuWireBox() {}
    
    CAAEVisVisuWireBox::~CAAEVisVisuWireBox() {}  
  
---  
  
The _CAAEVisVisuWireBox_ class states that it implements the _CATI3DGeoVisu_ interface thanks to the `TIE_CATI3DGeoVisu` macro. This extension class is dedicated to this component, and the `CATImplementClass` macro declares that the _CAAEVisVisuWireBox_ class is data extension class, thanks to the `DataExtension` keyword, and that it extends the component whose main class is _CAAVis_ WireBox. The third parameter must always be set to _CATBaseUnknown_ , makes no sense, and is unused for extensions. 

The `BuildRep` method builds the graphic representation of the wire box depending on its size and its location. 
    
    ...
    CATRep * CAAEVisVisuWireBox::**BuildRep**()
    {
       CAT3DCustomRep         * pWireBoxRep = NULL ;
     
       **CAAIVisWireBox** * piVisWireBox = NULL;                
       HRESULT rc = QueryInterface(IID_CAAIVisWireBox, (void**)&piVisWireBox);
       if (SUCCEEDED(rc))
       {
           float DimBox = .2f ;
           piVisWireBox->**GetDimBox**(&DimBox) ;    
    
           CATMathPoint CenterBox ;
           piVisWireBox->**GetCenterBox**(CenterBox) ;
    
           piVisWireBox->Release();
           piVisWireBox = NULL ;
    
           pWireBoxRep = new **CAT3DCustomRep**();
    
           CATGraphicAttributeSet   BoxGa ;
    
           float Cx = CenterBox.GetX() ;
           float Cy = CenterBox.GetY() ;
           float Cz = CenterBox.GetZ() ;
    
           float Tab1[12] ;
           
           Tab1[0] = Cx + DimBox; Tab1[1]  = Cy - DimBox; Tab1[2]  = Cz + DimBox ;
           Tab1[3] = Cx - DimBox; Tab1[4]  = Cy - DimBox; Tab1[5]  = Cz + DimBox ;
           Tab1[6] = Cx - DimBox; Tab1[7]  = Cy + DimBox; Tab1[8]  = Cz + DimBox ;
           Tab1[9] = Cx + DimBox; Tab1[10] = Cy + DimBox; Tab1[11] = Cz + DimBox ;
           ...
           CAT3DLineGP * pPolyline1 = new **CAT3DLineGP** (Tab1, 4,ALLOCATE, LINE_LOOP);
           ...
           CAT3DLineGP * pPolyline2 = new **CAT3DLineGP** (Tab2, 4,ALLOCATE, LINE_LOOP);
           ...
           CAT3DLineGP * pPolyline3 = new **CAT3DLineGP** (Tab3, 8,ALLOCATE, LINE);
    
           pWireBoxRep->**AddGP**(pPolyline1,BoxGa);
           pWireBoxRep->**AddGP**(pPolyline2,BoxGa);
           pWireBoxRep->**AddGP**(pPolyline3,BoxGa);
    
           ...
         
           CAT3DBoundingSphere be(CenterBox,Radius) ;
           pWireBoxRep->**SetBoundingElement**(be);
       }
    
       return pWireBoxRep;
    } 
    ...  
  
---  
  
The CAAIVisWireBox enables us to retrieve the size and the location of the wire box. From these values, three polylines are created. The following schema explains the code:

![](images/CAAVisSampleTempObjectBuildWireBox.jpg)  
---  
  
 

  6. **Updating the Interface Dictionary**

```vbscript
Do not forget to update the interface dictionary, here it is an extract of the CAAVisualization.edu.dico file located in the CAAVisualization.edu/CNext/code/dictionary directory.
    
```

    CAAVisWireBox CAAIVisWireBox         libCAAVisModelForRep
    CAAVisWireBox CATICreateInstance     libCAAVisModelForRep
    CAAVisWireBox CATI3DGeoVisu          libCAAVisModelForRep  
  
---  

[Top]

* * *
### In Short

The use case has detailed how to create three kinds of temporary components depending on their usage:

  * A simple CATModelForRep3D instance, for only displayable component 
  * A component deriving from CATModelForRep3D, for displayable and selectable component 
  * A component deriving from CATBaseUnknown and implementing _CATI3DGeoVisu_ , for a component whose the graphic representation can change while the component is into the ISO.

[Top]

* * *
### References

[1] | [Interactive Set of Objects](../CAAVisTechArticles/CAAVisISO.md)  
---|---  
[2] | [Visualizing Temporary Components](CAAVisSampleISO.md)  
[3] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)  
[4] | [Implementing the Command Statechart Diagram](../CAADegTechArticles/CAADegGraph.md)  
[5] | [Creating Components](../CAASysTechArticles/CAASysCreatingComponent.md)  
[6] | [Creating Components](../CAASysUseCases/CAASysSampleOMCreatingCmp.md)  
[Top]  
  
* * *
### History

Version: **1** [Fev 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
