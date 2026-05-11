---
title: "Creating a Combo Command Header"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrMRUHeader", "CAAGeometry", "CAAAfrComboColorNotification", "CAAAfrComboColorHeader", "CAAAfrComboColorRep", "CAAAfrComboColorHdr", "CAAIAfrTemporaryObjectColor", "CAAAfrComboRep", "CAAAfrComboRepId", "CATIAfrCommandHeaderRep", "CAAIAfrGeometryWksAddin", "CAAAfrGeoChartWindowAdn", "CAASysGeomRootObj", "CAASysGeoRootObj", "CATImplementHeaderResources", "CAAAfrEduCombo", "CAAApplicationFrame", "CAAAfrCustomizedCommandHeader", "CAAAfrGeoWksAddin2"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleComboHdr.htm"
converted: "2026-05-11T17:17:55.651120"
---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Creating a Combo Command Header

How to create a command header class whose the representation is a combo in a toolbar?  
---|---|---  
Use Case  
  
* * *
### Abstract

This use case explains how to create a specialized command header. This command header has a customized graphic representation. In place of a check button into a toolbar, the graphic representation is a combo. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrComboColorHeader Use Case**
    * What Does CAAAfrComboColorHeader Do
    * How to Launch CAAAfrComboColorHeader
    * Where to Find the CAAAfrComboColorHeader Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case illustrates the creation of a customized command header. In a toolbar, its graphic representation is a combo in place of a check button, the default representation. You will learn how to:

  * Create the component representing the command header 

> It is a component which must derive from the _CATAfrDialogCommandHeader_ class. 

  * Create the component instantiating the graphic representation

> It is a component which must derive from the _CATAfrCommandHeaderRep_ class and which instantiates a _CATDlgCombo_ instance. 

  * Create the component controlling the data used by the graphic representation

> The data used by the the graphic representation is the value of the current color in the combo. This data is dependent of the instance of a V5 document. 

You can also read the CAAAfrMRUHeader use case [1] which presents another customized command header. In this case, the graphic representation is a dynamic list of push items in a menu of the menu bar. Contrarily to the current use case, the data (a list of string) is independent of the document.  To take full advantage of this article, you can first read "The Command Headers" technical article [2], and precisely the "Creating Customized Command Headers" section.   [Top]
### The CAAAfrComboColorHeader Use Case

CAAAfrComboColorHeader is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities. [Top]
#### What Does CAAAfrComboColorHeader Do

CAAAfrComboColorHeader creates a command header whose the graphic representation is a combo color in a toolbar. The following picture shows the header in the Customized Command Header toolbar: Fig.1 The combo header 
---  
  
If you drop down the combo, you have the choice between ten colors:

Fig.2 Ten values of the combo ![](images/CAAAfrComboHdrDeplie.jpg) |  The combo needs two information: 

  * The available colors in the combo. These ten color are "hard" coded.  
  * The current selected color. This information is kept by a component linked to the CAAGeometry document. This component is the CAASysGeomRootObj component. Refer to the referenced article for complete details on the CAAGeometry document and the CAASysGeomRootObj component [3].

  
  
The **CAASysGeomRootObj component** is the component controlling the data used by the graphic representation. It manages the current value of the color through the _CAAIAfrTemporaryObjectColor_ interface. This interface enables us to get and set the current color. However the color is not persistent (not streamed) because the CAAGeometry document is not "streamable".

Fig.3 Component Controlling the Data Used by the Graphic Representation - UML Diagram ![](images/CAAAfrComboColorHdrUMLModel.jpg)  
---  
  
The CAASysGeomRootObj component plays the role of controller [2], when the current color value is modified using the _CAAIAfrTemporaryObjectColor_ interface, the _CAAEAfrTemporaryObjectColor_ implementation class sends a notification, a _CAAAfrComboColorNotification_ class instance. 

The **combo header class** is an instance of a class deriving from the _CATAfrDialogCommandHeader_ class _,_ like any command header whose the graphic representation is customized. The following UML diagram describes in details the schema of classes:

Fig.4 Combo Header - UML Diagram ![](images/CAAAfrComboColorHdrUMLHdr.jpg)  
---  
  
CAAAfrComboColorHeader is a component which must implement the _CATIAfrCommandHeaderRep_ interface to provide the customized graphic representation _._ This interface contains three methods:

  * `CreateCtxMenuRep`: it returns nothing
  * `CreateMenuRep`: it returns nothing
  * `CreateToolbarRep`: it instantiates an instance of the _CAAAfrComboRep_ class. This class is described by the following UML diagram:

Fig.5 Class Instantiating the Graphic Representation \- UML Diagram ![](images/CAAAfrComboColorHdrUMLRep.jpg)  
---  
  
The _CAAAfrComboRep_ class creates a _CATDlgCombo_ [4] class instance and sets a callback to be inform when the current color is changed. Therefore, if there are several instances of the _CAAAfrComboColorHeader_ class in the same document, see the How to Launch CAAAfrComboColorHeader section, all the representations will be automatically updated. 

The combo header is instantiated in an Add-in of the workshop of the CAAGeometry document. The last step of the Step by Step section explains this instantiation.

[Top]
#### How to Launch CAAAfrComboColorHeader

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched.

```vbscript
Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 

```

  * On the **File** menu, click **New**
  * **New** Dialog box click **CAAGeometry** and click **OK**
  * If the **Customized Command Header** toolbar is not displayed, right click on any toolbar and select it in the contextual menu to make it appear. (the default current color is red) 
  * Select the first **blue** color in the combo color
  * Click **Point** and creates some points
  * Click **Clipping By Box**  
    * Select the ISO Selection text
    * Select a point (A blue trihedral is displayed)
    * move the mouse and click left to define the clipping box size
  * Select a **purple** color in the combo color
  * Click **Clipping By Box**  
    * Select the ISO Selection text
    * Select a point (A purple trihedral is displayed)
    * move the mouse and click left to define the clipping box size
  * On the **File** menu, click **New**
  * **New** Dialog box click **CAAGeometry** and click **OK**(The current color in the combo color is red.)
  * Select the **blue** color in the combo color
  * Click **Clipping By Box**  
    * Select the ISO Selection text
    * Select a point (A blue trihedral is displayed)
    * move the mouse and click left to define the clipping box size
  * Select the first **CAAGeometry** document (The current color in the combo color is always purple)
  * On the **Tools** menu, click **Customize**
    * Select **Command** tab page
    * Select **CAAAfrComboColorHdr** in **All Commands** categories
    * Drag and Drop the command header in the **Chart Window** toolbar
    * click **OK**
  * Select the **red** color in one combo color instance (the other instance is red too)

[Top]
#### Where to Find the CAAAfrComboColorHeader Code

The CAAAfrComboColorHeader use case is made of several classes located in three modules of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\`  
---|---  
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

The `CAAAfrCustCommandHdrModel.m` module contains classes to define (update) the component controlling the current color.

  * CAAIAfrTemporaryObjectColor.cpp , CAAIAfrTemporaryObjectColor.h (PublicInterfaces), TIE_CAAIAfrTemporaryObjectColor.tsrc (src)

It is the interface managing the current color. 

  * CAAEAfrTemporaryObjectColor.h (LocalInterfaces) and CAAEAfrTemporaryObjectColor.cpp (src)

It is the implementation of the _CAAIAfrTemporaryObjectColor_ interface on the CAASysGeomRootObj component.

  * CAAAfrComboColorNotification.h (LocalInterfaces) and CAAAfrComboColorNotification.cpp (src)

It is the notification sent by the _CAAEAfrTemporaryObjectColor_ class when the current color is modified.

The `CAAAfrCustomizedCommandHeader``.m` module contains classes to define the combo color header:

  * CAAAfrComboRep.h (LocalInterfaces) and CAAAfrComboRep.cpp (src)
  * CAAEAfrCommandHeaderRepForComboColor.h (LocalInterfaces) and CAAEAfrCommandHeaderRepForComboColor.cpp (src)
  * CAAAfrComboColorHeader.cpp (src),  CAAAfrComboColorHeader.h (PrivateInterfaces)

The `CAAAfrGeoWksAddin2.``m` module contains an Add-in of the CAAGeometry workshop 

  * CAAAfrGeoChartWindowAdn.h (LocalInterfaces) and CAAAfrGeoChartWindowAdn.cpp (src)

[Top]
### Step-by-Step

There are four logical steps in CAAAfrComboColorHeader:

  1. Creating the Component Representing the Current Color in the Combo
  2. Creating the Component Representing the Command Header 
  3. Creating the Class Instantiating the Graphic Representation
  4. Instantiating the Combo Header Class

[Top]
#### Creating the Data Model Representing the Current Color in the Combo

The current color is kept by the CAASysGeomRootObj component which implements the _CAAIAfrTemporaryObjectColor_ interface to set and retrieve the current color (Fig.3). When the color is modified on the component (Set method) a _CAAAfrComboColorNotification_ notification is sent by the callback mechanism [5]. 

Here the _CAAIAfrTemporaryObjectColor_ interface such as you can see it in the PublicInterfaces directory of the CAAApplicationFrame.edu framework. Refer to the Creating an Interface use case [6] for more details on its creation. 
    
    
    ...
    #include <CATBaseUnknown.h>      
    
    class ExportedByCAAAfrCustCommandHdrModel CAAIAfrTemporaryObjectColor: public CATBaseUnknown
    {
      CATDeclareInterface;
    
      public:
          virtual HRESULT **GetCurrentColor**(int & oRed, int & oGreen, int & oBlue) const = 0 ;
          virtual HRESULT **SetCurrentColor**(int & iRed, int & iGreen, int & iBlue) = 0 ;
    };
    ...  
  
---  
  
This interface is implemented by the CAASysGeomRootObj component thanks to the _CAAEAfrTemporaryObjectColor_ class extension. 
    
    
    ...
    #include "**TIE_CAAIAfrTemporaryObjectColor.h** "              
    TIE_CAAIAfrTemporaryObjectColor(CAAEAfrTemporaryObjectColor); 
    
    **CATImplementClass** (CAAEAfrTemporaryObjectColor,**DataExtension** , 
                              CATBaseUnknown, **CAASysGeomRootObj**);
    ...  
  
---  
  
The _CAAEAfrTemporaryObjectColor_ class states that it implements the _CAAIAfrTemporaryObjectColor_ interface thanks to the `TIE_``CAAIAfrTemporaryObjectColor` __ macro. This extension class is dedicated to this component, and the `CATImplementClass` macro declares that the _CAAEAfrTemporaryObjectColor_ class is data extension class, thanks to the `DataExtension` keyword, and that it extends the component whose main class is CAASysGeomRootObj. The third parameter must always be set to _CATBaseUnknown_ , makes no sense, and is unused for extensions. 

In the constructor class, you can see that the default value is red ( 255,0,0). 
    
    
    ...
    CAAEAfrTemporaryObjectColor::CAAEAfrTemporaryObjectColor(): CATBaseUnknown()
                                
    {    
       **_RedComp**   = 255   ;
       _GreenComp = 10    ;
       _BlueComp  = 0     ; 
    }
    
    CAAEAfrTemporaryObjectColor::~CAAEAfrTemporaryObjectColor(){}
    ...  
  
---  
  
The `GetCurrentColor` returns the three data members representing the red, blue and green components of the current color. 
    
    
    ...
    HRESULT CAAEAfrTemporaryObjectColor::GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const
    {
       oRed   = _RedComp ;
       oGreen = _GreenComp ;
       oBlue  = _BlueComp ; 
    
       return (S_OK) ;
    }
    ...  
  
---  
  
The `SetCurrentColor` valuates the three data members using the input argument:
    
    
    ...
    HRESULT CAAEAfrTemporaryObjectColor::SetCurrentColor(int & iRed, int & iGreen, int & iBlue) 
    {
       _RedComp   = iRed   ;
       _GreenComp = iGreen;
       _BlueComp  = iBlue; 
    ...  
  
---  
  
and sends a notification:
    
    
    ...
        CATCallbackManager * pCBManager = ::**GetDefaultCallbackManager**(this) ;
        if ( NULL != pCBManager )
        {
             CAAAfrComboColorNotification * pNotification = new CAAAfrComboColorNotification();
             pCBManager->**DispatchCallbacks**(pNotification,this);
             pNotification->Release(); pNotification = NULL ;
        }
       return (S_OK) ;
    }
    ...  
  
---  
  
The `SetCurrentColor` method publishes the notification that states the current color is modifying. To do this, the global function `GetDefaultCallbackManager` retrieves the callback manager associated by default with the _CAAEAfrTemporaryObjectColor_ class instance, and this callback uses its `DispatchCallbacks` method to inform its subscribers or listeners that the current color is modifying by means of the _CAAAfrComboColorNotification_ notification created.

Refer to the callback use case [7] which explains in details the callback mechanism, and how the _CAAAfrComboColorNotification_ must be created. You will learn why the _CAAAfrComboColorNotification_ class instance is deleted just after the `DispatchCallbacks` call. See the constructor of the CAAAfrComboColorRep class. 

[Top]
#### Creating the Component Representing the Command Header 

The combo header is a component which must Object Modeler and C++ derive from _CATAfrDialogCommandHeader_ and must implement the _CATIAfrCommandHeaderRep_ interface (Fig.4). This paragraph is divided in two parts:

  * Component Creation
  * CATIAfrCommandHeaderRep implementation

##### **Component Creation**

Here the CAAAfrComboColorHeader header file:
    
    
    //ApplicationFrame framework
    #include "CATAfrDialogCommandHeader.h"
    
    class ExportedByCAAAfrCustomizedCommandHeader CAAAfrComboColorHeader : public **CATAfrDialogCommandHeader**
    {
      CATDeclareHeaderResources;
      CATDeclareClass ;
    
      public:
        CAAAfrComboColorHeader(const CATString & iHeaderName);
    
        virtual ~CAAAfrComboColorHeader();
        CATCommandHeader * **Clone**() ;
          
      private:
        **CAAAfrComboColorHeader(CATCommandHeader *iHeaderToCopy);**
        CAAAfrComboColorHeader(const CAAAfrComboColorHeader &iObjectToCopy);
        CAAAfrComboColorHeader & operator = (const CAAAfrComboColorHeader &iObjectToCopy);
    };  
  
---  
  
_CAAAfrComboColorHeader_ derives from _CATAfrDialogCommandHeader_. It is mandatory for a command header whose the graphic representation is customized. The `CATDeclareClass` macro declares that it belongs to a CAA component. The `CATDeclareHeaderResources` macro inserts the methods to manage the command header resources. 

About the mandatory public methods:

  * A `constructor` with a reference to a `const CATString` as parameter, 
  * A `destructor`, 
  * The `Clone` method inherited from _CATCommandHeader_ and used to duplicate the command header instance. Refer to the "Customized Command Header Class Structure" section of the technical article about the command headers [2]. You will have all the details about the `Clone` method. 

About the mandatory private methods:

  * A `constructor` taking a pointer to a _CATCommandHeader_ is dedicated to the `Clone` method. 
  * Two other `constructor` are declared in the private part, and are not implemented in the source file. This prevents the compiler from creating them as public without you know.

Here the CAAAfrComboColorHeader header file:
    
    #include "CAAAfrComboColorHeader.h"
    
    CATImplementClass(CAAAfrComboColorHeader, 
                      Implementation,
                      **CATAfrDialogCommandHeader** , 
                      CATNull);
    
    CATImplementHeaderResources(CAAAfrComboColorHeader,  
    			 CATAfrDialogCommandHeader,          
    			 CAAAfrComboColorHeader);            
    
    CAAAfrComboColorHeader::CAAAfrComboColorHeader(const CATString & iHeaderName) : 
        **CATAfrDialogCommandHeader**(iHeaderName){}
    
    CAAAfrComboColorHeader::~CAAAfrComboColorHeader(){}
    
    CATCommandHeader * CAAAfrComboColorHeader::**Clone** ()                                  
    { 
        return new **CAAAfrComboColorHeader**(this); 
    }   
    
    CAAAfrComboColorHeader::CAAAfrComboColorHeader(CATCommandHeader * iHeaderToCopy):
                              **CATAfrDialogCommandHeader**(iHeaderToCopy)
    {}	                    
  
---  
  
  * A customized command header is a CAA component. The `CATImplementClass` macro makes the class _CAAAfrComboColorHeader_ a component main class (`Implementation`) that OM-derives [9] from _CATAfrDialogCommandHeader_. 
  * The `CATImplementHeaderResources` macro is used in conjunction with the `CATDeclareHeaderResources` macro in the header file. It states that the _CAAAfrComboColorHeader_ class derives from _CATAfrDialogCommandHeader_ , and that its associated resource file names use the class name: CAAAfrComboColorHeader.CATNls and CAAAfrComboColorHeader.CATRsc respectively. The base class name set as second argument helps to use resource concatenation. The third argument could be set to the name of another class that is associated with resource files that use its class name, or to the name, without suffix, of an already existing resource file pair.
  * The `Clone` method returns a copy construction instance of this.

**_CATIAfrCommandHeaderRep_ implementation**

This interface of the ApplicationFrame framework must be implemented by all command header whose the graphic representation is customized. On Fig.4, you see that the _CAAEAfrCommandHeaderRepForComboColor_ class is the implementation of this interface for the CAAAfrComboColorHeader component. 

Here the CAAEAfrCommandHeaderRepForComboColor header file
    
    
    ...
    class CAAEAfrCommandHeaderRepForComboColor : public CATBaseUnknown
    {
      CATDeclareClass;
    public:
      
      CAAEAfrCommandHeaderRepForComboColor();
      virtual ~CAAEAfrCommandHeaderRepForComboColor();
      
      virtual HRESULT  **CreateToolbarRep** (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      virtual HRESULT  **CreateMenuRep**    (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      virtual HRESULT  **CreateCtxMenuRep** (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      
    private:
      CAAEAfrCommandHeaderRepForComboColor(const CAAEAfrCommandHeaderRepForComboColor &iObjectToCopy);
      CAAEAfrCommandHeaderRepForComboColor & operator = (const CAAEAfrCommandHeaderRepForComboColor &iObjectToCopy);
    };        
  
---  
  
The `CATDeclareClass` macro declares that _CAAEAfrCommandHeaderRepForComboColor_ belongs to a component. `CreateToolbarRep`, `CreateMenuRep`, and `CreateCtxMenuRep` are methods of the _CATIAfrCommandHeaderRep_ interface.

Here the CAAEAfrCommandHeaderRepForComboColor source file
    
    
    ...
    #include <TIE_CATIAfrCommandHeaderRep.h>
    TIE_**CATIAfrCommandHeaderRep**(CAAEAfrCommandHeaderRepForComboColor);
    
    CATImplementClass(CAAEAfrCommandHeaderRepForComboColor, 
                      DataExtension,
                      CATBaseUnknown, 
                      **CAAAfrComboColorHeader**);
    };
    CAAEAfrCommandHeaderRepForComboColor::
               CAAEAfrCommandHeaderRepForComboColor():CATBaseUnknown(){}
    
    CAAEAfrCommandHeaderRepForComboColor::~CAAEAfrCommandHeaderRepForComboColor(){}
    ...        
  
---  
  
The _CAAEAfrCommandHeaderRepForComboColor_ class states that it implements the _CATIAfrCommandHeaderRep_ __ interface thanks to the `TIE_CATIAfrCommandHeaderRep `macro. The `CATImplementClass` macro declares that the _CAAEAfrCommandHeaderRepForComboColor_ class is a data extension, thanks to the `DataExtension` keyword, that extends CAAAfrComboColorHeader. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.  The class constructor and the class destructor are empty.
    
    
    ...
    HRESULT CAAEAfrCommandHeaderRepForComboColor::**CreateToolbarRep**
             (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
       HRESULT rc = E_FAIL ;
    
       if ( oHdrRep != NULL )
       {
          CATString Name = "CAAAfrComboRepId" ;
          CAAAfrComboRep * pComboRep = new **CAAAfrComboRep**(iParent,Name);
    
          *oHdrRep = (CATAfrCommandHeaderRep *) pComboRep ;
          rc = S_OK ;
       }
    
       return rc ;
    }
    ...        
  
---  
  
The `CreateToolbarRep` method provides the class instantiating the graphic representation of the combo header. This method is called each time the header command must be represented in a toolbar.

The _CAAAfrComboRep_ class is a _CATCommand_ class (Fig.5) which instantiates the graphic representation of the combo header (a _CATDlgCombo_ instance). It is detailed in the Creating the Component Instantiating the Graphic Representation section, just below.  

`iParent` is a _CATDialog_ component. It will be the dialog parent of the _CATDlgCombo_ instance. `Name` is the command name of the _CAAAfrComboRep_ class. You can set the same identifier for all _CAAAfrComboRep_ class instances. 

You do not have to take care of the _CAAAfrComboRep_ class instance, the returned value, `oHdrRep` is kept by the frame application, and the deletion of this pointer is automatically done.  
    
    
    ...
    HRESULT CAAEAfrCommandHeaderRepForComboColor::
                 **CreateMenuRep**(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
      return  **E_FAIL** ;
    }
    
    HRESULT CAAEAfrCommandHeaderRepForComboColor::
              **CreateCtxMenuRep**(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
      return **E_FAIL** ;
    }  
  
---  
  
The combo header has no representation in the menu bar or in a contextual menu, so `CreateMenuRep` and `CreateCtxMenuRep` return E_FAIL.

[Top]
#### Creating the Class Instantiating the Graphic Representation

This class is the _CAAAfrComboRep_ class. Its main roles are:

  * Set a callback to be informed when the current color on the CAASysGeomRootObj component changes, see Creating the Data Model Representing the Current Color in the Combo step 
  * Create a _CATDlgCombo_ instance
  * Change the current value of the _CATDlgCombo_ instance when a notification is sent by the CAASysGeomRootObj component

Here the CAAAfrComboRep header file:
    
    
    ...
    class CAAAfrComboRep : public **CATAfrCommandHeaderRep**
    {
    public:
      CAAAfrComboRep(const CATDialog * iParent, CATString & iCommandName);
      virtual ~CAAAfrComboRep();
    
      HRESULT **Build**();
    
    private:
      void **SelectCB**(CATCommand * iPublishingCommand, 
                    CATNotification * iNotification, 
                    CATCommandClientData iData);
    
      void **ModifiedCB**(CATCallback       iEvent, 
                      void            *       , 
                      CATNotification * iNotification, 
                      CATCallbackEvent  iData,
    		          CATSubscriberData iCallBack);
      HRESULT **SetCurrentColor**() ;
    
      CAAAfrComboRep(const CAAAfrComboRep &iObjectToCopy);
      CAAAfrComboRep & operator = (const CAAAfrComboRep &iObjectToCopy);
    
    private:
         CATDlgCombo    * _pCombo;
         CATBaseUnknown * _pUIActiveObject ;
         int              _ColorTable[30] ;
    };  
  
---  
  
  * The _CAAAfrComboRep_ class derives from the _CATAfrCommandHeaderRep_ class ( Fig.5)
  * The `Build` method is a method of the _CATAfrCommandHeaderRep_ class. You must overwrite this method. In the _CATAfrCommandHeaderRep_ class it is a pure virtual method. This method is called by the frame application just after the _CAAAfrComboRep_ class instantiation, in other words just after the `CreateToolbarRep` method call.  
  * In private methods 
    * The `SelectCB` method is a callback method when the end user selects a color in the combo.
    * The `ModifiedCB` method is a callback method called when the CAASysGeomRootObj component sends a _CAAAfrComboColorNotification_ notification. 
    * The `SetCurrentColor` is called by `SelectCB` and `ModifiedCB` methods to modify the current selected value of `_pCombo`, the data member 
  * In data member 
    * `_pCombo` the _CATDlgCombo_ class instance created in the `Build` method 
    * `_pUIActiveObject` the UI active object of the CAAGeometry document. It is those which sends _CAAAfrComboColorNotification_ notification and keeps the current color. In your modelization, it can another component than the UI active object.  
    * `_ColorTable` is the array defining the ten colors - See Fig.2.  

Here the CAAAfrComboRep source file:

  * The **constructor** class 

First the ten values of the combo are initialized. To simplify the use case, there are always ten values, and there are "hard" coded. 
    
    ...
    CAAAfrComboRep::CAAAfrComboRep(const CATDialog * iParent,CATString & iCommandName): 
                     CATAfrCommandHeaderRep(iParent,iCommandName)
                    ,_pUIActiveObject(NULL),_pCombo(NULL)
    {
       float val ;
       for ( int i= 0 ; i < 10 ; i++)
       {
          // red
          val = (255 * i / 9 ); 
          _ColorTable[i*3]   = (int)val;
    
          // green
          _ColorTable[i*3+1] = 10 ;
    
          // blue
          val = (255 * (9-i) / 9); 
          _ColorTable[i*3+2] = (int)val;
       }
    ...  
  
---  
  
The second step consists in to retrieve the CAASysGeomRootObj component. it is also the UI active object of the CAAGeometry document. 
    
    ...
       CATFrmEditor * pEditor   = **CATFrmEditor** ::**GetCurrentEditor**();
       if ( NULL != pEditor )
       {
    
           CATPathElement path = pEditor->**GetUIActiveObject**();
           if ( 0 != path.GetSize() ) 
           {
              _pUIActiveObject=path[path.GetSize()-1];
    
             _pUIActiveObject->**AddRef**();
           }
       }
    ...  
  
---  
  
The last step consists in to set a callback method to be informed when the CAASysGeomRootObj component will sent a _CAAAfrComboColorNotification_ notification, in other words when the current color kept by the CAASysGeomRootObj component, will be modified. 
    
    ...
       if ( NULL != _pUIActiveObject )
       {
          ::**AddCallback**(this,
                       _pUIActiveObject,
    	          "CAAAfrComboColorNotification",
    	          (CATSubscriberMethod)&CAAAfrComboRep::**ModifiedCB** ,
    	          NULL);
       }
    }  
  
---  
  
`AddCallback` is a static global function whose the parameters are:

    * `this:` The subscriber
    * `_pUIActiveObject`: The publisher 
    * `CAAAfrComboColorNotification:`The notification class sent by the publisher
    * `ModifiedCB:`The method of this which is called when a _CAAAfrComboColorNotification notification is sent_
    * `NULL**:**`No parameters for the callback method  

  * The **Destructor** class
    
    ...
    CAAAfrComboRep::~CAAAfrComboRep()
    {
        if ( NULL != _pUIActiveObject )
        {
           ::**RemoveSubscriberCallbacks**(this, _pUIActiveObject);
    
            _pUIActiveObject->Release();
            _pUIActiveObject = NULL ;
        }
        if ( NULL != _pCombo )
        {
           _pCombo->**RequestDelayedDestruction**();
           _pCombo = NULL ;
        }
    
    }...  
  
---  
  
At the end, the callback set in the constructor must be removed from the callback manager [7], and the _CATDlgCombo_ instance must be released. 

  * The **Build** method

You must overwrite this method. The goal of this method is to create the graphic representation and to initialize it.

The first step consists in to retrieve the Dialog parent of the graphic representation to create. This information is kept by the _CATAfrCommandHeaderRep_ class, and retrieved by its `GetDialogParent` method. Then you can create a _CATDlgCombo_ class instance using, `pParent`, the Dialog parent. The second argument of the _CATDlgCombo_ class is the identifier of the dialog object, and the last one is the type of combo (`CATDlgCmbColor`: a combo of colors). Once the creation is done, you can set a callback to be informed when the end user selects a color among the ten values. 
    
    ...
    HRESULT  CAAAfrComboRep::Build()
    {
       const CATDialog * pParent = NULL ;
       **GetDialogParent**(&pParent);
    
       _pCombo = new **CATDlgCombo**((CATDialog *)pParent, "CAAAfrEduCombo", CATDlgCmbColor);
    
       **AddAnalyseNotificationCB**(_pCombo,
    			   _pCombo->GetComboSelectNotification(),
    			   (CATCommandMethod)&CAAAfrComboRep::**SelectCB** ,
    			   (CATCommandClientData)NULL);
    ...  
  
---  
  
Then, you can initialize the combo with the ten values using `_ColorTable`, the data member, initialized in the constructor class. Once the initialization is done, you can set current value calling `SetCurrentColor`. 
    
    ...
       for ( int i=0 ; i < 10 ; i++)
       {
         _pCombo->**SetLine**(CATUnicodeString(),
    			(unsigned char)_ColorTable[i*3 ], 
    			(unsigned char)_ColorTable[i*3+1], 
    			(unsigned char)_ColorTable[i*3+2], 
    			i);
       }
       **SetCurrentColor**();
    ...  
  
---  
  
Finally, the _CATCommand_ parent of the combo is changed. By default, the command parent is the Dialog parent, so it is `pParent`, the container in which the combo will be inserted. If you do not change the command parent, this, the current _CAAAfrComboRep_ instance, will do not receive the `GetComboSelectNotification` notification. Refer to the referenced article about the command tree [8].
    
    ...
       _pCombo->**SetFather**(this);
    
       return S_OK ;
    }
    ...  
  
---  
  * The **SelectCB** method

The `SelectCB` method is called when the end user has selected a color in the combo. When `_pCombo` sends a notification, this callback method is called. The goal of this method, is first to retrieve the current color, using `GetSelect`, and then to modify the current color on the CAASysGeomRootObj component. `_pUIActiveObject,` is the CAASysGeoRootObj component which implements the _CAAIAfrTemporaryObjectColor_ interface. 
    
    ...
    void CAAAfrComboRep::SelectCB(CATCommand * iPublishingCommand, 
    			      CATNotification * iNotification, 
    			      CATCommandClientData iData)
    {
      **CAAIAfrTemporaryObjectColor** * pITemporaryObjectColor = NULL ;
      HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAIAfrTemporaryObjectColor,
                                                    (void**) & pITemporaryObjectColor);
      ...
         int val = _pCombo->**GetSelect**();
    
         pITemporaryObjectColor->**SetCurrentColor**(_ColorTable[val*3 ],
                                                    _ColorTable[val*3+1],
                                                    _ColorTable[val*3+2]);
    ...  
  
---  
  * The **ModifyCB** method

The `ModifyCB` method is called when the CAASysGeomRootObj component sends the _CAAAfrComboColorNotification_ notification. It informs the _CAAAfrComboRep_ class instance, that the current color on the CAASysGeoRootObj component has been changed by someone. 
    
    ...
    void CAAAfrComboRep::ModifiedCB(CATCallback, 
                                  void *, 
                                  CATNotification * iNotification,
    			                  CATCallbackEvent, 
                                  CATSubscriberData)
    {
       **SetCurrentColor**();
    }
    ...  
  
---  
  * The **SetCurrentColor** method

This method consists in to read the current color on the CAASysGeoRootObj component, and modify, thanks to the `SetSelect` method, the current value on `_pCombo`, the _CATDlgCombo_ data member of the _CAAAfrComboRep_ class. 
    
    ...
    HRESULT CAAAfrComboRep::SetCurrentColor()
    {
       **CAAIAfrTemporaryObjectColor** * pITemporaryObjectColor = NULL ;
       HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAIAfrTemporaryObjectColor,
                                                    (void**) & pITemporaryObjectColor);
       ...
          int r,g,b ;
          pITemporaryObjectColor->**GetCurrentColor**(r,g,b);
    
          int position = 0 ;
          CATBoolean FOUND = FALSE ;
          while ( ( FALSE == FOUND) && ( position < 10 ))
          {
             if ( (r == _ColorTable[position*3 ]) &&
                  (g == _ColorTable[position*3+1 ]) &&
                  (b == _ColorTable[position*3+2 ]) )
             {
                 FOUND = TRUE ;
             }else position ++ ;
          }
    
          if ( TRUE == FOUND) 
          {
             _pCombo->**SetSelect**(position,0);
          }
    ...  
  
---  

[Top]
#### Instantiating the Combo Header Class

The combo header is used in the CAAGeometry document. An instance of this header has been created in an Add-in of the workshop of the document. Here is an extract of the _CAAAfrGeoChartWindowAdn_ class which is an implementation of the _CAAIAfrGeometryWksAddin_ interface. 
    
    
    ...
    void CAAAfrGeoChartWindowAdn::CreateCommands()
    {
    ...
       new **CAAAfrComboColorHeader**("CAAAfrComboColorHdr");
    }
      
  
---  
  
The combo command header is created using its constructor class. 

* * *
### In Short

This use case has explained how to create a command header whose the graphic representation is customized:

  * The command header is a component which OM and C++ derives from CATAfrDialogCommandHeader and implements CATIAfrCommandHeaderRep
  * The customized graphic representation is created by a class which must derive from CATAfrCommandHeaderRep

The component controlling the data used by the graphic representation is dependent of the document. 

[Top]

* * *
### References

[1] | [Creating a Most Recent Used Command Header](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)  
[3] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)  
[4] | [CATDlgCombo](../CAADlgQuickRefs/CAADlgCATDlgCombo.md)  
[5] | [The Callback Mechanism](../CAASysTechArticles/CAASysCallbacks.md)  
[6] | [Creating an Interface](../CAASysUseCases/CAASysSampleOMCreatingInt.md)  
[7] | [The Callback Mechanism](../CAASysUseCases/CAASysSampleCallbacks.md)  
[8] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)  
[9] | [Object Modeler Inheritances](../CAASysTechArticles/CAASysOMInheritance.md)  
[Top]  
  
* * *
### History

Version: **1** [Fev 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
