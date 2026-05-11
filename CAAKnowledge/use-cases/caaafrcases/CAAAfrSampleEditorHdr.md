---
title: "Creating Editors in Toolbar"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrEltCountRep", "CAAAfrEltCountRepId", "CAAAfrMRUHeader", "CAAGeometry", "CAAAfrComboColorHeader", "CAAAfrGeoModel", "CAAAfrEdtLine", "CAAISysPoint", "CAAAfrPaletteOptions", "CATIAfrCommandHeaderRep", "CAASysCollectionModifNotif", "CATImplementClass", "CAAAfrEltCountHeader", "CAAAfrEdtPoint", "CAAISysLine", "CAASysGeoModelInf", "CAAEAfrCommandHeaderRepForEltCount", "CAASysSampCont", "CATImplementHeaderResources", "CAASysGeomCont"]
source_file: "Doc\online\CAAAfrUseCases\CAAAfrSampleEditorHdr.htm"
converted: "2026-05-11T17:17:55.729034"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Frame

| 

### Creating Editors in Toolbar

How to create a command header class whose the representation is an editor in a toolbar?  
---|---|---  
Use Case  
  
* * *

### Abstract

This use case explains how to create a specialized command header. This command header has a customized graphic representation. In place of a check button into a toolbar, the graphic representation is two editors. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrEltCountHeader Use Case**
    * What Does CAAAfrEltCountHeader Do
    * How to Launch CAAAfrEltCountHeader
    * Where to Find the CAAAfrEltCountHeader Code
  * **Step-by-Step**
  * **In Short**
  * **References**



* * *

### What You Will Learn With This Use Case

This use case illustrates the creation of a customized command header. In a toolbar, its graphic representation is two editors in place of a check button, the default representation. You will learn how to:

  * Create the component representing the command header 



> It is a component which must derive from the _CATAfrDialogCommandHeader_ class. 

  * Create the component instantiating the graphic representation



> It is a component which must derive from the _CATAfrCommandHeaderRep_ class and which instantiates two _CATDlgEditor_ instances.

  * Create the component controlling the data used by the graphic representation



> The data used by the the graphic representation is the count of lines and points in the document. This data is dependent of the instance of a V5 document. 

You can also read 

  * CAAAfrComboColorHeader use case [1] which presents another customized command header. In this case, the graphic representation is a combo in a toolbar. It is similar to the current one. 
  * CAAAfrMRUHeader use case [2] which presents another customized command header. In this case, the graphic representation is a dynamic list of push items in a menu of the menu bar. Contrarily to the current use case, the data (a list of strings) is independent of the document. 

To take full advantage of this article, you can first read "The Command Headers" technical article [3], and precisely the "Creating Customized Command Headers" section.   [Top]

### The CAAAfrEltCountHeader Use Case

CAAAfrEltCountHeader is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities. [Top]

#### What Does CAAAfrEltCountHeader Do

CAAAfrEltCountHeader creates a command header whose the graphic representation is two editors in a toolbar. The following picture shows the header in the "Tools Palette" toolbar [4]: Fig.1 The EltCount header | ![](images/CAAAfrSamplePaletteWkb.jpg)  
---  
  
There is a command header displaying the count of points and lines created in the CAAGeometry document [5]

The **CAASysGeomCont****** component is the component controlling the data used by the graphic representation. It manages the list of elements in the CAAGeometry document through the _CAAISysCollection_ interface.  

Fig.2 Component Controlling the Data Used by the Graphic Representation - UML Diagram ![](images/CAAAfrEltCountHdrUMLModel.jpg)  
---  
  
The CAASysGeomCont component plays the role of controller [3], when a line or a point is created (or deleted), the _CAAISysCollection_ interface is used, and the _CAAEAfrCollection_ class sends a notification, a _CAASysCollectionModifNotif_ class instance. 

The **EltCount header** is an instance of a class, _CAAAfrEltCountHeader_ ,deriving from the _CATAfrDialogCommandHeader_ class _,_ like any command header whose the graphic representation is customized. The following UML diagram describes in details the schema of classes:

Fig.3 EltCount Header - UML Diagram ![](images/CAAAfrEltCountHdrUMLHdr.jpg)  
---  
  
CAAAfrEltCountHeader is a component which must implement the _CATIAfrCommandHeaderRep_ interface to provide the customized graphic representation _._ This interface contains three methods:

  * `CreateCtxMenuRep`: it returns nothing
  * `CreateMenuRep`: it returns nothing
  * `CreateToolbarRep`: it instantiates an instance of the _CAAAfrEltCountRep_ class. This class is described by the following UML diagram:

Fig.4 Class Instantiating the Graphic Representation \- UML Diagram ![](images/CAAAfrEltCountHdrUMLRep.jpg)  
---  
  
The _CAAAfrEltCountRep_ class creates _CATDlgEditor_ [6] class instances and sets a callback to be inform when lines or points are created or deleted. 

The EltCount header is instantiated in the Tools Palette for a workbench of the CAAGeometry document [4]. 

[Top]

#### How to Launch CAAAfrEltCountHeader

See the section entitled "How to Launch CAAAfrPaletteOptions" in the use case [4] for a detailed description of how this use case should be launched.

[Top]

#### Where to Find the CAAAfrEltCountHeader Code

The CAAAfrEltCountHeader use case is made of several classes mainly located in modules of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\`  
---|---  
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

  * The `CAAAfrCustomizedCommandHeader``.m` module contains classes to define the EltCount header and its graphic representation. 
    * CAAAfrEltCountRep.h (LocalInterfaces) and CAAAfrEltCountRep.cpp (src)
    * CAAEAfrCommandHeaderRepForEltCount.h (LocalInterfaces) and CAAEAfrCommandHeaderRepForEltCount.cpp (src)
    * CAAAfrEltCountHeader.cpp (src),  CAAAfrEltCountHeader.h (PrivateInterfaces)  

  * The `CAAAfrGeoModel.m` module contains 
    * CAAEAfrCollection.h (LocalInterfaces) and CAAEAfrCollection.cpp (src)

It is the data extension of the _CAAISysCollection_ interface implemented on the CAASysGeomCont component. Both ( component+interface) are defined in the CAASystem.edu framework. [5]




[Top]

### Step-by-Step

There are three logical steps in CAAAfrEltCountHeader:

  1. Creating the Component Providing Data
  2. Creating the Component Representing the Command Header 
  3. Creating the Class Instantiating the Graphic Representation



[Top]

#### Creating Component Providing Data

Count of lines and points are kept by the CAASysGeomCont component which implements the _CAAISysCollection_ interface (Fig.2). When a point/Line is created/deleted in the current CAAGeometry document, a _CAASysCollectionModifNotif_ notification is sent by the callback mechanism [7]. 

Here the _CAAISysCollection_ interface such as you can see it in the PublicInterfaces directory of the CAASystem.edu framework. Refer to the Creating an Interface use case [8] for more details on its creation. 
    
    
    ...
    class ExportedByCAASysGeoModelInf CAAISysCollection : public CATBaseUnknown
    {
      CATDeclareInterface;
    
      public:
        virtual HRESULT GetNumberOfObjects(int * oCount) = 0;
        virtual HRESULT GetObject    (int iRank,
                                      CATBaseUnknown ** oObject) = 0;
        virtual HRESULT **AddObject**    (CATBaseUnknown * iObject) = 0;
        virtual HRESULT RemoveObject (CATBaseUnknown * iObject) = 0;
        virtual HRESULT Empty  () =0 ;
    };
    ...  
  
---  
  
This interface is implemented by the CAASysGeomCont component thanks to the _CAAEAfrCollection_ class extension. 
    
    
    ...
    #include "**TIE_CAAISysCollection**.h"
    TIE_CAAISysCollection(CAAEAfrCollection);
    
    CATBeginImplementClass(CAAEAfrCollection,**DataExtension** ,CATBaseUnknown,**CAASysGeomCont**);
    CATAddClassExtension(CAASysSampCont) ;
    CATEndImplementClass(CAAEAfrCollection);
    ...  
  
---  
  
The _CAAEAfrCollection_ class states that it implements the _CAAISysCollection_ interface thanks to the `TIE_``CAAISysCollection` __ macro. This extension class is dedicated to this component, and the `CATBeginImplementClass` macro declares that the _CAAEAfrCollection_   class is data extension class, thanks to the `DataExtension` keyword, and that it extends the component whose main class is CAASysGeomCont. The third parameter must always be set to _CATBaseUnknown_ , makes no sense, and is unused for extensions. 

The `AddObject` adds an element in the CAAGeometry document. `_pListe` is a data member of the _CAAEAfrCollection_ class.
    
    
    ...
    HRESULT CAAEAfrCollection::AddObject (CATBaseUnknown * iObject)
    {
    ...
       _pListe->Append(iObject);
    ...  
  
---  
  
and sends a notification:
    
    
    ...
        CAASysCollectionModifNotif * pNotifModif = new **CAASysCollectionModifNotif**();
    
        ::GetDefaultCallbackManager(this)->DispatchCallbacks(pNotifModif,this);
          
        pNotifModif->Release() ;
        pNotifModif = NULL ;
    ...  
  
---  
  
The `AddObject`  method publishes the notification that states the list of element in the document is modifying. To do this, the global function `GetDefaultCallbackManager` retrieves the callback manager associated by default with the _CAAEAfrCollection_ class instance, and this callback uses its `DispatchCallbacks` method to inform its subscribers or listeners that liste is modifying by means of the _CAASysCollectionModifNotif_**** notification created.

Refer to the callback use case [9] which explains in detail the callback mechanism, and how the _CAASysCollectionModifNotif_**** must be created. You will learn why the _CAASysCollectionModifNotif_**** class instance is deleted just after the `DispatchCallbacks` call. 

[Top]

#### Creating the Component Representing the Command Header 

The EltCount header is a component which must Object Modeler and C++ derive from _CATAfrDialogCommandHeader_ and must implement the _CATIAfrCommandHeaderRep_ interface (Fig.3). This paragraph is divided in two parts:

  * Component Creation
  * CATIAfrCommandHeaderRep implementation



##### **Component Creation**

Here the CAAAfrEltCountHeader header file:
    
    
    //ApplicationFrame framework
    #include "CATAfrDialogCommandHeader.h"
    
    class ExportedByCAAAfrCustomizedCommandHeader CAAAfrEltCountHeader : 
                                    public **CATAfrDialogCommandHeader**
    {
      CATDeclareHeaderResources;
      CATDeclareClass ;
    
      public:
        CAAAfrEltCountHeader(const CATString & iHeaderName);
    
        virtual ~CAAAfrEltCountHeader();
        CATCommandHeader * **Clone**() ;
          
      private:
        **CAAAfrEltCountHeader****(CATCommandHeader *iHeaderToCopy);**
        CAAAfrEltCountHeader(const CAAAfrEltCountHeader &iObjectToCopy);
        CAAAfrEltCountHeader & operator = (const CAAAfrEltCountHeader &iObjectToCopy);
    };  
  
---  
  
_CAAAfrEltCountHeader_ derives from _CATAfrDialogCommandHeader_. It is mandatory for a command header whose the graphic representation is customized. The `CATDeclareClass` macro declares that it belongs to a CAA component. The `CATDeclareHeaderResources` macro inserts the methods to manage the command header resources. 

About the mandatory public methods:

  * A `constructor` with a reference to a `const CATString` as parameter, 
  * A `destructor`, 
  * The `Clone` method inherited from _CATCommandHeader_ and used to duplicate the command header instance. Refer to the "Customized Command Header Class Structure" section of the technical article about the command headers [2]. You will have all the details about the `Clone` method. 



About the mandatory private methods:

  * A `constructor` taking a pointer to a _CATCommandHeader_ is dedicated to the `Clone` method. 
  * Two other `constructor` are declared in the private part, and are not implemented in the source file. This prevents the compiler from creating them as public without you know.



Here the CAAAfrEltCountHeader header file:
    
    
    #include "CAAAfrEltCountHeader.h"
    
    CATImplementClass(CAAAfrEltCountHeader, 
                      Implementation,
                      **CATAfrDialogCommandHeader** , 
                      CATNull);
    
    CATImplementHeaderResources(CAAAfrEltCountHeader,  
    			 CATAfrDialogCommandHeader,          
    			 CAAAfrEltCountHeader);            
    
    CAAAfrEltCountHeader::CAAAfrEltCountHeader(const CATString & iHeaderName) : 
        **CATAfrDialogCommandHeader**(iHeaderName){}
    
    CAAAfrEltCountHeader::~CAAAfrEltCountHeader(){}
    
    CATCommandHeader * CAAAfrEltCountHeader::**Clone** ()                                  
    { 
        return new **CAAAfrEltCountHeader**(this); 
    }   
    
    CAAAfrEltCountHeader::CAAAfrEltCountHeader(CATCommandHeader * iHeaderToCopy):
                              **CATAfrDialogCommandHeader**(iHeaderToCopy)
    {}	                    
  
---  
  
  * A customized command header is a CAA component. The `CATImplementClass` macro makes the class _CAAAfrEltCountHeader_ a component main class (`Implementation`) that OM-derives [10] from _CATAfrDialogCommandHeader_. 
  * The `CATImplementHeaderResources` macro is used in conjunction with the `CATDeclareHeaderResources` macro in the header file. It states that the _CAAAfrEltCountHeader_ class derives from _CATAfrDialogCommandHeader_ , and that its associated resource file names use the class name: CAAAfrEltCountHeader.CATNls and CAAAfrEltCountHeader.CATRsc respectively. The base class name set as second argument helps to use resource concatenation. The third argument could be set to the name of another class that is associated with resource files that use its class name, or to the name, without suffix, of an already existing resource file pair.
  * The `Clone` method returns a copy construction instance of this.



**_CATIAfrCommandHeaderRep_ implementation**

This interface of the ApplicationFrame framework must be implemented by all command header whose the graphic representation is customized. On Fig.3, you see that the _CAAEAfrCommandHeaderRepForEltCount_ class is the implementation of this interface for the CAAAfrEltCountHeader component. 

Here the CAAEAfrCommandHeaderRepForEltCount header file
    
    
    ...
    class CAAEAfrCommandHeaderRepForEltCount: public CATBaseUnknown
    {
      CATDeclareClass;
    public:
      
      CAAEAfrCommandHeaderRepForEltCount();
      virtual CAAEAfrCommandHeaderRepForEltCount();
      
      virtual HRESULT  **CreateToolbarRep** (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      virtual HRESULT  **CreateMenuRep**    (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      virtual HRESULT  **CreateCtxMenuRep** (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      
    private:
      CAAEAfrCommandHeaderRepForEltCount(const CAAEAfrCommandHeaderRepForEltCount&iObjectToCopy);
      CAAEAfrCommandHeaderRepForEltCount& operator = (const CAAEAfrCommandHeaderRepForEltCount&iObjectToCopy);
    };        
  
---  
  
The `CATDeclareClass` macro declares that _CAAEAfrCommandHeaderRepForEltCount_ belongs to a component. `CreateToolbarRep`, `CreateMenuRep`, and `CreateCtxMenuRep` are methods of the _CATIAfrCommandHeaderRep_ interface.

Here the CAAEAfrCommandHeaderRepForEltCount source file
    
    
    ...
    #include <TIE_CATIAfrCommandHeaderRep.h>
    TIE_**CATIAfrCommandHeaderRep**(CAAEAfrCommandHeaderRepForEltCount);
    
    CATImplementClass(CAAEAfrCommandHeaderRepForEltCount, 
                      DataExtension,
                      CATBaseUnknown, 
                      **CAAAfrEltCountHeader**);
    };
    CAAEAfrCommandHeaderRepForEltCount::
               CAAEAfrCommandHeaderRepForEltCount():CATBaseUnknown(){}
    
    CAAEAfrCommandHeaderRepForEltCount::~CAAEAfrCommandHeaderRepForEltCount(){}
    ...        
  
---  
  
The _CAAEAfrCommandHeaderRepForEltCount_ class states that it implements the _CATIAfrCommandHeaderRep_ __ interface thanks to the `TIE_CATIAfrCommandHeaderRep `macro. The `CATImplementClass` macro declares that the _CAAEAfrCommandHeaderRepForEltCount_ class is a data extension, thanks to the `DataExtension` keyword, that extends CAAAfrEltCountHeader. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.  The class constructor and the class destructor are empty.
    
    
    ...
    HRESULT CAAEAfrCommandHeaderRepForEltCount::**CreateToolbarRep**
             (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
       HRESULT rc = E_FAIL ;
    
       if ( oHdrRep != NULL )
       {
          CATString Name = "CAAAfrEltCountRepId" ;
          CAAAfrEltCountRep * pEltCountRep = new **CAAAfrEltCountRep**(iParent,Name);
    
          *oHdrRep = (CATAfrCommandHeaderRep *) pEltCountRep ;
          rc = S_OK ;
       }
    
       return rc ;
    }
    ...        
  
---  
  
The `CreateToolbarRep` method provides the class instantiating the graphic representation of the EltCount header. This method is called each time the header command must be represented in a toolbar.

The _CAAAfrEltCountRep_ class is a _CATCommand_ class (Fig.4) which instantiates the graphic representation of the EltCount header (two _CATDlgEditor_ instances). It is detailed in the Creating the Component Instantiating the Graphic Representation section, just below.  

`iParent` is a _CATDialog_ component. It will be the dialog parent of the _CATDlgEditor_ instances. `Name` is the command name of the _CAAAfrEltCountRep_ class. You can set the same identifier for all _CAAAfrEltCountRep_ class instances. 

You do not have to take care of the _CAAAfrEltCountRep_ class instance, the returned value, `oHdrRep` is kept by the frame application, and the deletion of this pointer is automatically done.  
    
    
    ...
    HRESULT CAAEAfrCommandHeaderRepForEltCount::
                 **CreateMenuRep**(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
      return  **E_FAIL** ;
    }
    
    HRESULT CAAEAfrCommandHeaderRepForEltCount::
              **CreateCtxMenuRep**(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
      return **E_FAIL** ;
    }  
  
---  
  
The EltCount header has no representation in the menu bar or in a contextual menu, so `CreateMenuRep` and `CreateCtxMenuRep` return E_FAIL.

[Top]

#### Creating the Class Instantiating the Graphic Representation

This class is the _CAAAfrEltCountRep_ class. Its main roles are:

  * Set a callback to be informed when a modification occurs in the list of elements controlled by the CAASysGeomCont component
  * Create two _CATDlgEditor_ instances
  * Change the contents of  the _CATDlgEditor_ instances when a notification is sent by the CAASysGeomCont component



Here the CAAAfrEltCountRep header file:
    
    
    ...
    class CAAAfrEltCountRep : public CATAfrCommandHeaderRep
    {
    public:
      CAAAfrEltCountRep(const CATDialog * iParent, CATString & iCommandName);
      virtual ~CAAAfrEltCountRep();
      
      HRESULT **Build**();
    
    private:
      void **ModifiedCB**(CATCallback       iEvent, 
                      void            *       , 
                      CATNotification * iNotification, 
                      CATCallbackEvent  iData,
    		          CATSubscriberData iCallBack);
      HRESULT **ValuateEditors**() ;
    
      CAAAfrEltCountRep(const CAAAfrEltCountRep &iObjectToCopy);
      CAAAfrEltCountRep & operator = (const CAAAfrEltCountRep &iObjectToCopy);
    
    private:
    
         CATDlgEditor      * _pEdtPoint;
         CATDlgEditor      * _pEdtLine;
         CAAISysCollection * _piSysCollection ;
    };
      
  
---  
  
  * The _CAAAfrEltCountRep_ class derives from the _CATAfrCommandHeaderRep_ class (Fig.4)
  * The `Build` method is a method of the _CATAfrCommandHeaderRep_ class. You must overwrite this method. In the _CATAfrCommandHeaderRep_ class it is a pure virtual method. This method is called by the frame application just after the _CAAAfrEltCountRep_ class instantiation, in other words just after the `CreateToolbarRep` method call.  
  * In private methods 
    * The `ModifiedCB` method is a callback method called when the CAASysGeomCont component sends a _CAASysCollectionModifNotif_ notification. 
    * The `ValuateEditors` is called by `Build `and `ModifiedCB `methods to modify the current value of _`pEdtPoint` and `_pEdtLine`, the data members
  * In data member 
    * _`pEdtPoint` and `_pEdtLine, `two _CATDlgEditor_ class instance created in the `Build `method 
    * `_piSysCollection` a _CAAISysCollection_ interface pointer on the CAASysGeomCont component of the current CAAGeometry document.



Here the CAAAfrEltCountRep source file:

  * The **constructor** class 

The First  step consists in to retrieve the CAASysGeomCont component. Refer to the code file for details about `pContainer`. It is useless for the use case to detail this part of code. 
    
    ...
    CAAAfrEltCountRep::CAAAfrEltCountRep(const CATDialog * iParent,CATString & iCommandName): 
                     CATAfrCommandHeaderRep(iParent,iCommandName),
                     _piSysCollection(NULL),_pEdtPoint(NULL),_pEdtLine(NULL)
    {
       ...
       rc = pContainer->QueryInterface(IID_CAAISysCollection, (void**)&**_piSysCollection**);
    
    ...  
  
---  
  
The second and last step consists in to set a callback method to be informed when the CAASysGeomCont component will send a _CAASysCollectionModifNotif_ notification.
    
    ...
       if ( NULL != _piSysCollection )
       {
          ::AddCallback(this,
                   _piSysCollection,
    	           "CAASysCollectionModifNotif",
    	            (CATSubscriberMethod)&CAAAfrEltCountRep::ModifiedCB,
    	            NULL);
       }
    }  
  
---  
  
`AddCallback` is a static global function whose the parameters are:

    * `this:` The subscriber
    * `_piSysCollection`: The publisher 
    * `CAASysCollectionModifNotif``:`The notification class sent by the publisher
    * `ModifiedCB:`The method of this which is called when a _CAASysCollectionModifNotif_ notification is sent
    * `NULL**:**`No parameters for the callback method  

  * The **Destructor** class
    
    ...
    CAAAfrEltCountRep::~CAAAfrEltCountRep()
    {
        if ( NULL != _piSysCollection )
        {
           ::**RemoveSubscriberCallbacks**(this, _piSysCollection);
    
            _piSysCollection->Release();
            _piSysCollection = NULL ;
        }
        if ( NULL != _pEdtPoint )
        {
           _pEdtPoint->**RequestDelayedDestruction**();
           _pEdtPoint = NULL ;
        }
        if ( NULL != _pEdtLine )
        {
           _pEdtLine->**RequestDelayedDestruction**();
           _pEdtLine = NULL ;
        }
    
    }...  
  
---  
  
At the end, the callback set in the constructor must be removed from the callback manager [9], and the _CATDlgEditor_ instances must be released. 

  * The **Build** method

You must overwrite this method. The goal of this method is to create the graphic representation and to initialize it.
    
    ...
    HRESULT  CAAAfrEltCountRep::Build()
    {
       // Creation of the dialog object
       const CATDialog * pParent = NULL ;
       **GetDialogParent**(&pParent);
    
       _pEdtPoint = new CATDlgEditor((CATDialog *)pParent, "CAAAfrEdtPoint", 
                                     CATDlgEdtReadOnly);
       _pEdtLine  = new CATDlgEditor((CATDialog *)pParent, "CAAAfrEdtLine", 
                                     CATDlgEdtReadOnly);
       
       // Sets the value in the editors
       ValuateEditors();
    
       return S_OK ;
    }
    ...  
  
---  
  
The first step consists in to retrieve the Dialog parent of the graphic representation to create. This information is kept by the _CATAfrCommandHeaderRep_ class, and retrieved by its `GetDialogParent` method. Then you can create _CATDlgEditor_ class instance using, `pParent`, the Dialog parent. The second argument of the _CATDlgEditor_ class is the identifier of the dialog object, and the last one is the type of editor (`CATDlgEdtReadOnly`). Then, you call `ValuateEditors `to initialize the contents of the editors.

  * The **ModifyCB** method

The `ModifyCB` method is called when the CAASysGeomCont component sends the _CAASysCollectionModifNotif_   notification. It informs the _CAAAfrEltCountRep_ class instance, that the count of lines/points on the CAASysGeomCont component has been changed by someone. It is done thanks to the `ValuateEditors` method.
    
    ...
    void CAAAfrEltCountRep::ModifiedCB(CATCallback, 
                                  void *, 
                                  CATNotification * iNotification,
    			                  CATCallbackEvent, 
                                  CATSubscriberData)
    {
       ValuateEditors();
    }
    ...  
  
---  
  * The **ValuateEditors** method

This method consists in to retrieve the list of elements into the CAAGeometry document, and modify, thanks to the `SetText` method, the current value on `_pEdtPoint` and `_pEdtLine`, the two data members of the _CAAAfrEltCountRep_ class. 
    
    ...
    HRESULT CAAAfrEltCountRep::ValuateEditors()
    {
     ...
           int nbeltcont = 0 ;
           _piSysCollection->**GetNumberOfObjects**(&nbeltcont);
       
           int NbPoint = 0 ;
           int NbLine  = 0 ;
    
           for (int i=1 ; i <=  nbeltcont ; i++)
           { 
              CATBaseUnknown * pObject = NULL ;
              rc = _piSysCollection->**GetObject**(i,&pObject);
              if (SUCCEEDED(rc))
              {
                  **CAAISysPoint** * piSysPoint  = NULL;                
                  rc = pObject ->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
                  if (SUCCEEDED(rc))
                  {
                     // it's a point
                     NbPoint ++ ;
                     piSysPoint -> Release();
                     piSysPoint = NULL ;
                  } 
                  **CAAISysLine** * piSysLine  = NULL;                
                  rc = pObject ->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
                  if (SUCCEEDED(rc))
                  {
                        // it's a line
                        NbLine ++ ;
     ...
           CATUnicodeString stNbPoint ;
           stNbPoint.**BuildFromNum**(NbPoint) ;
           CATUnicodeString stNbLine ;
           stNbLine.BuildFromNum(NbLine) ;
    
           _pEdtPoint->**SetText**(stNbPoint);
           _pEdtLine ->SetText(stNbLine);
    ...  
  
---  



[Top]

* * *

### In Short

This use case has explained how to create a command header whose the graphic representation is customized:

  * The command header is a component which OM and C++ derives from CATAfrDialogCommandHeader and implements CATIAfrCommandHeaderRep
  * The customized graphic representation is created by a class which must derive from CATAfrCommandHeaderRep



The component controlling the data used by the graphic representation is dependent of the document. 

[Top]

* * *

### References

[1] | [Creating a Combo Command Header](CAAAfrSampleComboHdr.htm)  
---|---  
[2] | [Creating a Most Recent Used Command Header](../CAADocUseCases/CAADocRunSample.htm)  
[3] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.htm)  
[4] | [Using the "Tools Palette" Toolbar for a Workbench](CAAAfrSamplePaletteWkb.htm)  
[5] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.htm)  
[6] | [CATDlgEditor](../CAADlgQuickRefs/CAADlgCATDlgCombo.htm)  
[7] | [The Callback Mechanism](../CAASysTechArticles/CAASysCallbacks.htm)  
[8] | [Creating an Interface](../CAASysUseCases/CAASysSampleOMCreatingInt.htm)  
[9] | [The Callback Mechanism](../CAASysUseCases/CAASysSampleCallbacks.htm)  
[10] | [Object Modeler Inheritances](../CAASysTechArticles/CAASysOMInheritance.htm)  
[Top]  
  
* * *

### History

Version: **1** [Fev 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
