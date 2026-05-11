---
```vbscript
title: "Understanding the Application Frame Layout"
category: "use-case"
module: "CAAAfrTechArticles"
tags: ["CATIDocumentEdit", "CAAAfrHistogramChartWindow", "CAAEMyInterface", "CATIAfrGeneralWksAddin", "CATISO", "CATIVisu", "CATIAApplicationFrame", "CATIEditor"]
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrLayoutV5.htm"
converted: "2026-05-11T17:17:55.923668"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Understanding the Application Frame Layout

_A description of the objects involved in the V5 interactive application layout_  
---|---|---  
Technical Article  

* * *
### Abstract

This article shows the layout of the V5 application and the objects involved in this layout. To take full advantage of this article, a reading of the "Application Frame Overview" article [1] can be benefit to have a global view of the V5 Application. 

  * **The V5 Interactive Application Layout**
    * **The CATApplicationDocument class**
    * **The CATApplicationFrame Class**
    * **The CATFrmEditor Class**
    * **The****CATFrmLayout Class**
  * **The Document Window**
    * **The Contents of a Window**
    * **The Default Window**
    * **The Window Title**
    * **Defining a New Window Type**
    * **Defining a Window Creation Interface**
  * **In Short**
  * **References**

---  

* * *
### The V5 Interactive Application Layout

The V5 Application is an interactive application [2]. This section presents all the C++ objects which are involved in the layout of this application.
#### The CATApplicationDocument

The V5 Application is an interactive application [2]. This section presents all the C++ objects which are involved in the layout of this application.
The application layout is provided by the non-exposed _CATApplicationDocument_ class _._

Fig.1: The V5 Interactive Application Layout ![](images/CAAAfrUnderstandingLayout1.jpg)  

---  

The application layout is provided by the non-exposed _CATApplicationDocument_ class _._
Fig.1: The V5 Interactive Application Layout ![](images/CAAAfrUnderstandingLayout1.jpg)
The V5 layout contains many objects among which the main ones are:

Menu bar | It is a [_CATDlgMenu_](../CAADlgQuickRefs/CAADlgCATDlgMenu.md) class instance. You customize it through workbenches [3] and Add-ins [4].   

The V5 layout contains many objects among which the main ones are:
Menu bar | It is a [_CATDlgMenu_](../CAADlgQuickRefs/CAADlgCATDlgMenu.md) class instance. You customize it through workbenches [3] and Add-ins [4].
Tool bars | They are _[CATDlgToolbar](../CAADlgQuickRefs/CAADlgCATDlgToolBar.md)_ class instances. You create them also through workbenches [3] and Add-ins [4].   
Status bar | It is a _[CATDlgStatusBar](../CAADlgQuickRefs/CAADlgCATDlgStatusBar.md)_ class instance. The message displayed inside is either the active command name or an information driven by the current command.   
Power input | It is a non-exposed dialog object class included in the status bar. This tool, depending on the configuration level, may be unavailable.  
Document window | Each window is an instance of a class deriving from the _CATFrmWindow_ class. In the picture below, the Part document is visualized with two instances and the Product document with one instance. In the Product and Part document cases, the default window is a _CATFrmGraphAnd3DWindow_(CATIAApplicationFrame Framework)  
Dialog Box | It is a _[CATDlgDialog](../CAADlgQuickRefs/CAADlgCATDlgDialog.md)_ class instance. It can be a simple command [7] or an object driven by a state command [5].   
Decorator | This object is an invisible dialog object which contains all the dialog objects related to the document: all its windows and all its dialog boxes. Thanks to this object, it is possible to hide/deactivate all the dialog objects when the document loses the focus.   

[Top] 
#### The CATApplicationFrame class 

Decorator | This object is an invisible dialog object which contains all the dialog objects related to the document: all its windows and all its dialog boxes. Thanks to this object, it is possible to hide/deactivate all the dialog objects when the document loses the focus.
 This _CATApplicationDocument_ class instance is built by the _**CATApplicationFrame**_ class instance. 

Fig.2: The V5 Interactive Application UML Diagram ![](images/CAAAfrUnderstandingLayout2.jpg)  

---  

This _CATApplicationDocument_ class instance is built by the _**CATApplicationFrame**_ class instance.
Fig.2: The V5 Interactive Application UML Diagram ![](images/CAAAfrUnderstandingLayout2.jpg)
 This UML diagram shows that:

  * The _CATApplicationDocument_ deriving from the _CATDlgDocument_ class is created by the non-exposed _l_CATApplicationFrame_ class. 
  * The _l_CATApplicationFrame_ class instance is a workshop. In fact it is the **General** workshop, the one containing the commands that are always available: File/New, Print .... whether a document is opened or not.  
  * The _CATApplicationFrame_ instance is created in the `BeginApplication` method of the interactive application [2]

The main methods of the _CATApplicationFrame_ class are:

`GetFrame`             | This static method returns the unique instance of this class.  
---|---  
`SetMessage    `   | To set a message in the status bar.   
`GetApplicationDocument` | This method returns the _CATApplicationDocument_ class instance  
`GetMainWindow`    | This method returns: 

  * The _CATApplicationDocument_ class instance if no document is open
  * otherwise, the decorator associated to the current document(editor)

This class is generally used to retrieve the current decorator in order to be set as the dialog parent of a dialog box [6]: 

    ...
This class is generally used to retrieve the current decorator in order to be set as the dialog parent of a dialog box [6]:
    CATApplicationFrame * **pFrame** = CATApplicationFrame::**GetFrame**();
    if ( NULL != pFrame ) 

    {
CATApplicationFrame * **pFrame** = CATApplicationFrame::**GetFrame**();
if ( NULL != pFrame )
       CATDialog * **pParent** = pFrame->**GetMainWindow**();
       CATMyDialogBox * pMyDialogBox = new MyDialogBox(**pParent** ,...);

    }
    ...  

---  

`MyDialogBox` will be automatically hidden when the editor will be deactivated. Therefore if you need a dialog box always visible, and independent of the life of the document, its parent must be the _CATApplicationDocument_ class instance returned by the `GetApplicationDocument` method. You can also read the "Defining Headers in CATIAfrGeneralWksAddin Implementations" section in the technical article about the command headers [5]. 

[Top] 
#### The CATFrmEditor Class

The C++ objects involved in the Model View Controller paradigm are:

  * M = a _CATDocument_(document)
  * V = a _CATFrmWindow_   __(window)
  * C = a _CATFrmEditor_  __(editor)

Fig.3: The MVC Paradigm ![](images/CAAAfrUnderstandingLayout3.jpg)  
---  

Fig.3: The MVC Paradigm ![](images/CAAAfrUnderstandingLayout3.jpg)
This diagram shows several things:

  1. The **document** manages the editor and the window creation through interfaces:

     1. The _**CATIEditor**_ interface is used to create the _CATFrmEditor_ instance, actually a _CATFrmObjectEditor_ class instance. 

     2. The _**CATIDocumentEdit**_ interface is used to create the default window to display the document. This window is a class instance deriving from the _CATFrmWindow_ class. The "Defining a New Window Type" section shows that the document can implement other interfaces to provide other window types. 

  2. The **editor** is a **_CATCommand_**.

     * It creates an invisible object, the **decorator** (See the Fig.1 ). This decorator is the dialog parent of each window which displays the document. It must be also the dialog parent of all dialog boxes which are used as commands or associated with a state command. Refer to the previous section to retrieve it. 

     * It creates a _CATCommandSelector_ instance. Refer to the article about the command for more information on the role of this object [5].

  3. The _CATFrmEditor_ class does not contain the list of the **windows** associated with the document. This list is managed by the _CATFrmLayout_ class. The next section explains the role of this unique class instance and how to retrieve the list of windows created for a document. 

The methods of the _CATFrmEditor_ class, those in relationship with the layout, are:

`GetCurrentEditor ` | This static method returns the current editor. This method must be used only in a command class constructor. In the state command case, you ought to prefer the CATStateCommand#`GetEditor` method. This method is available everywhere in the state command.  
---|---  
`GetDocument`           | Returns the document _which has created the editor_ but which may not be the one displayed in the windows. If you open a Product document, then edit one of its Part instance's, the editor displays the Part, but `GetDocument` always returns the Product document.   
`GetWindowCount`     | Returns the count of _CATFrmWindow_ associated with this editor.  
`GetCommandSelector` | Returns the command selector dedicated to the editor.  

The _CATFrmEditor_ class has other roles mentioned below but not detailed in this documentation:

  * Managing the UI active object,
  * Managing the sets of objects like : PSO,HSO,SDO,CSO [1] 
  * Managing the Interactive Set of Objects [15]
  * Controlling the send/receive command tree through its _CATCommandSelector_ instance [5]
  * Managing the command header list [13]

[Top]
#### The CATFrmLayout Class

This class manages all the windows created. It enables you to:

  * Identify all the windows associated with a document
  * Receive the events sent by the editors
  * Manage the current window

##### This class enables you to find all the windows opened for a document: 

    ...
    CATFrmLayout * **pLayout** = CATFrmLayout::**GetCurrentLayout**();
CATFrmLayout * **pLayout** = CATFrmLayout::**GetCurrentLayout**();
    if ( NULL != pLayout ) 

    {
CATFrmLayout * **pLayout** = CATFrmLayout::**GetCurrentLayout**();
if ( NULL != pLayout )
       CATLISTP(CATFrmWindow) WindowList ;
       WindowList = pLayout ->**GetWindowList**();
       for ( int = i ; i <= WindowList.Size() ; i++ )

       {
            **CATFrmWindow** * pCurrentWind = WindowList[i] ;
```vbscript
CATLISTP(CATFrmWindow) WindowList ;
WindowList = pLayout ->**GetWindowList**();
for ( int = i ; i <= WindowList.Size() ; i++ )
            if ( NULL != pCurrentWind )
```

            {
               **CATFrmEditor** * pEditor = pCurrentWind->**GetEditor**(); 
               if ( NULL != pEditor )
               {
                   **CATDocument** * pDocument = pEditor ->**GetDocument**(); 
                   if ( pDocument == pOurDocument)
                   {
                      // pCurrentWind is a window for our document 
                   }
    ...  

---  

There is only one instance of this class during a session. The `GetCurrentLayout` method retrieves this unique instance. The `GetWindowList` methods returns all the windows of the session. To select only those dedicated to a document, you should retrieve the document which has created the window. This information is kept by the editor which is itself kept by the window. Fig.3
##### Receiving the events sent by the editors 

Each editor, a _CATFrmEditor_ class instance, sends an event when it is closing or when its UI-active object is changing. If you are interested by receiving this information, you should be aware that the _CATFrmLayout_ class is the "sender" and not the editor itself. In your code you set the following callback:

    ...
       ::AddCallback(this,
Each editor, a _CATFrmEditor_ class instance, sends an event when it is closing or when its UI-active object is changing. If you are interested by receiving this information, you should be aware that the _CATFrmLayout_ class is the "sender" and not the editor itself. In your code you set the following callback:
                    CATFrmLayout::**GetCurrentLayout**(),
                    CATFrmEditor::EDITOR_CLOSE_ENDED(),
                    (CATSubscriberMethod)&Class::MethodCB,
                    NULL);

    ...  

---  

Where: 

`This` | It is the subscriber.  
---|---  
`CATFrmLayout::GetCurrentLayout` | The unique  _CATFrmLayout_ class instance is the event publisher.  
`CATFrmEditor::EDITOR_CLOSE_ENDED()` | It is the published event. You also have `CATFrmEditor::UIACTIVEOBJECT_CHANGED()`  
`Class::MethodCB` | It is the method called when the event is sent. As usual, the class must be the class name of this.  

When the editor is not the publisher, you should test in the callback method that the editor which sent the event is at the origin of the event.

    ...
When the editor is not the publisher, you should test in the callback method that the editor which sent the event is at the origin of the event.
    void Class::MethodCB(CATCallbackEvent  iEvent, void            * iFrom,
                         CATNotification * iNotification,CATSubscriberData iClientData,
                         CATCallback       iCallBack )     

    {
void Class::MethodCB(CATCallbackEvent  iEvent, void            * iFrom,
CATNotification * iNotification,CATSubscriberData iClientData,
CATCallback       iCallBack )
      if ( _pMyEditor == iFrom )

       {
        ...
       }
    }
    ...  

---  

where:

`_pMyEditor`  | A data member of the class   
---|---  
`iEvent` | It is the published event (`CATFrmEditor::EDITOR_CLOSE_ENDED` or `CATFrmEditor::UIACTIVEOBJECT_CHANGED)`  
`iFrom` | The _CATFrmEditor_ class pointer concerned by the event   
`iNotification` | This pointer is always NULL .  
`iClientData` | The fifth data of the `AddCallback` global function  
`iCallBack ` | The callback identifier  

Refer to use case [7]  for a sample. 
##### Managing the current window

Refer to use case [7]  for a sample.
The _CATFrmLayout_ class enables you to activate a new window. This method is `SetCurrentWindow`. You can use it to display in the foreground the current document window or to change of the current document. However, bear in mind that using this method has the same effect as clicking on the window: a new editor may be activated and your command may be deleted.

Here is an action method of a state command of a Part workbench.

    ...
    CATBoolean MyStateClass::MyActionMethod(void *iPointIndice)
    {
     ...
CATBoolean MyStateClass::MyActionMethod(void *iPointIndice)
     CATFrmWindow * pWindowProduct = ...
     CATFrmLayout *pLayout = CATFrmLayout::**GetCurrentLayout**();
     pLayout->**SetCurrentWindow**(pWindowProduct );

     ...
    }
    ...  

---  

In this action method `pWindowProduct` is a pointer on a Product document window. Thanks to the `SetCurrentWindow `method, this document will be activated. But the current command, `MyStateClass`, will be deleted if it is a shared or exclusive command [5]. Nevertheless, you can interact until the action method is over (`MyActionMethod`). 

To summarize, the methods of the _CATFrmLayout_ class are:

`GetCurrentLayout`             | This static method returns the unique instance of this class.  
---|---  
`SetCurrentWindow`    | This method enables you to give the focus to a window. This method is useful when the window has just been created. See the "The Default Window" section.  
`GetCurrentWindow`    | This method returns the window which has the focus.  
`GetWindowList`    | This method returns all the windows created in the frame.   

[Top]
### The Document Window 

A document window allows you to visualize the document content, either entirely or partly. It must be a class deriving from the _CATFrmWindow_ class. All the windows have the following inheritance tree:

![](images/CAAAfrUnderstandingLayout4.jpg)  
---  

This section explains the contents of a window, how the default window is created, how the window title is managed and how to create your own window. 

[Top]
#### **The Contents of a Window**

A window is a _CATDlgDialog_ class and as such, it can contain any dialog object susceptible to be included by this class [6]. But in most cases it contains _CATViewer_ (Visualization framework) instances. You have to respect only one rule: all the dialog objects must be inside a frame created by the _CATFrmWindow_ class:

![](images/CAAAfrUnderstandingLayout5.jpg)  
---  

A window is a _CATDlgDialog_ class and as such, it can contain any dialog object susceptible to be included by this class [6]. But in most cases it contains _CATViewer_ (Visualization framework) instances. You have to respect only one rule: all the dialog objects must be inside a frame created by the _CATFrmWindow_ class:
This frame is an invisible frame that you retrieve with the `GetViewerFrame` method. Inside this frame the objects must be arranged with the tabulation layout [8]. To take full advantage of the grid layout [9], you can create an intermediary frame with the _CATDlgGridLayout_ style. 

Here is an example :

![](images/CAAAfrUnderstandingLayout6.jpg)  
---  

Refer to the "Creating a Document's Window -2" use case [10].

[Top]
#### **The Default Window**

On  Fig.3 you can note that the default window is created by the _CATIDocumentEdit_ interface. This interface is used when the document is open. 
#### The Window Title

The _CATFrmWindow_ class constructor is:

    CATFrmWindow(const CATString & **iWindowTag** , CATFrmEditor * iEditor = NULL);  

---  

```vbscript
CATFrmWindow(const CATString & **iWindowTag** , CATFrmEditor * iEditor = NULL);
The name of the window will be `iWindowTag.` If it is not a complete file name, otherwise the name will be the one of the file:

  1. CATFrmWindow("**MyWindowName** ", pEditor);

The name of the window is `MyWindowName`

  2. CATFrmWindow("**e/users\Part.CATPart** ", pEditor);

The name of the window is `Part.CATPart`

In fact, this (truncated) name is the**base name.** You can change it using the `SetBaseName` method on the _CATFrmWindow_ class. It is a base name because after the first window creation an index will be added to the window title. Consider this scenario:

```

| 1) The TestFrame Part is opened  
---  
![](images/CAAAfrUnderstandingLayout7.jpg)  
| 2) File/ New Window  
---  
![](images/CAAAfrUnderstandingLayout8.jpg)  

After the creation of the second window, the name of the first window becomes `TestFrame.CATPart:1`. This part is detailed further in the "Managing the base name" section.

[Top]
#### **Defining a New Window Type**

After the creation of the second window, the name of the first window becomes `TestFrame.CATPart:1`. This part is detailed further in the "Managing the base name" section.
A default document window is provided by the V5 application. However, you can visualize it in a different way by creating a new window type for the document. The article [11] gives you a concrete sample.  

The class defining the new window type must have at least five methods:

  * Constructor/Destructor
  * Build 
  * DeleteWindow
  * DuplicateWindow

Depending on your window, other methods may be available. For example, you can have a method which returns the list of viewers if the window is multi-viewer [10].
##### Constructor/Destructor

As usual the constructor of a dialog box is simple:

As usual the constructor of a dialog box is simple:
    MyWindow :: MyWindow ( const CATString &iName, CATFrmEditor * iEditor )

                       : **CATFrmWindow**(iName,iEditor):_pViewer(NULL),
As usual the constructor of a dialog box is simple:
MyWindow :: MyWindow ( const CATString &iName, CATFrmEditor * iEditor )
                                                     _pRootObjectPath(NULL)

    {}  

---  

In the constructor the data members which are pointers are set to NULL. Generally, these data members correspond to the viewer(s) and the path of the objects to be visualized.

In the destructor the data member which are pointers are set to NULL. You do not need to delete the viewers since they are automatically deleted.  
##### Build 

In the constructor the data members which are pointers are set to NULL. Generally, these data members correspond to the viewer(s) and the path of the objects to be visualized.
In the destructor the data member which are pointers are set to NULL. You do not need to delete the viewers since they are automatically deleted.
The `Build` method, as usual for a Dialog class, **creates** and **arranges** the dialog objects (**viewers**). The "Contents of a Window" section can help you to carry out this part. The second role of this method is to **manage the interactivity** for the objects to visualize. 

There are two kinds of objects to visualize:

  * The elements of the document. In this case, the interactivity is managed by the _CATVisManager_ [14]. 
  * The temporary components (objects). Their interactivity is managed by the _CATISO_.

There are two kinds of objects to visualize:
In both cases, the main goal is to attach the objects to be visualized to the _CATCommand_ tree. Actually it is the manipulator attached to the graphic representation of the objects. The following diagram illustrates this: 

Fig.4: The CATCommand tree ![](images/CAAAfrUnderstandingLayout10.jpg)  

---  

In both cases, the main goal is to attach the objects to be visualized to the _CATCommand_ tree. Actually it is the manipulator attached to the graphic representation of the objects. The following diagram illustrates this:
Fig.4: The CATCommand tree ![](images/CAAAfrUnderstandingLayout10.jpg)
The code in the `Build` method is the following:

**For the elements of the document:**

    ...
    list **ListIVisu** ;
    IID visu = IID_CAT3DGeoVisu;
    ListIVisu.fastadd(&visu);

    CATVisManager * pVisuManager = **CATVisManager::GetVisManager**();
    CATCommandSelector *pCommandSelector = pEditor->GetCommandSelector();

    pVisuManager->**AttachTo**(_pRootObjectPath,pViewPoint,ListIVisu,pCommandSelector);

    ...  

---  

where:

`pVisuManager`  | It is a pointer to the unique _CATVisManager_ class instance.  
---|---  
`pEditor` | The _CATFrmEditor_ class instance of the window  
`_pRootObjectPath` | It is a _CATPathElement_ of the root model. It is a data member used to keep a handle on the model.   
`pViewPoint` | One viewpoint of the viewer, the main 3D, the main2D or another viewpoint.  
`ListIVisu` | A list of CATIVisu IID.   

This `AttachTo` method must be called as many times as the root model is in a viewpoint.

**For the temporary elements of the CATISO:**

    ...
    CATISO * pISO = pEditor->**GetISO**()  ;  
    pISO->**AddViewer**(_pViewer);
    ...  

---  

pISO->**AddViewer**(_pViewer);
The  `AddViewer` method must be called as many times as there are viewers in the window.

The last operation in the `Build` method is to declare the PSO [1] and HSO [1] to the _CATVisManager_. 

    ...
The last operation in the `Build` method is to declare the PSO [1] and HSO [1] to the _CATVisManager_.
    CATPSO * pPSO = pEditor->**GetPSO**() ;   
    pVisuManager->**AttachPSOTo**( pPSO,pViewPoint);

    CATHSO * pHSO = pEditor->**GetHSO**() ; 
    pVisuManager->**AttachHSOTo**( pHSO,pViewPoint);

    ...  

---  

pVisuManager->**AttachHSOTo**( pHSO,pViewPoint);
These `AttachPSOTo` and `AttachHSOTo` methods must be called as many time the root model is seen by a viewpoint. 

The `Build` method is now complete. 

##### DeleteWindow

These `AttachPSOTo` and `AttachHSOTo` methods must be called as many time the root model is seen by a viewpoint.
The `Build` method is now complete.
This method is called when the end-user closes the document or when the window is closed. 

    ...
    void NewWindow :: DeleteWindow()
    {     
       // ISO management
void NewWindow :: DeleteWindow()
          CATISO * pISO = NULL ;
          pISO = GetEditor()->**GetISO**();
          if  (NULL != pISO)   pISO->**RemoveViewer**(_pViewer);

       // Root Model management
CATISO * pISO = NULL ;
pISO = GetEditor()->**GetISO**();
if  (NULL != pISO)   pISO->**RemoveViewer**(_pViewer);
          CATVisManager * pVisuManager = CATVisManager::**GetVisManager**();
          CATViewpoint  * pViewPoint = NULL ;

          pViewPoint = (CATViewpoint*) &(_pViewer->**GetMain3DViewpoint**());
          pVisuManager->**DetachFrom**(_pRootObjectPath,pViewPoint);

       // PSO/HSO management
pViewPoint = (CATViewpoint*) &(_pViewer->**GetMain3DViewpoint**());
pVisuManager->**DetachFrom**(_pRootObjectPath,pViewPoint);
          pVisuManager->**DetachPSOFrom**(pViewPoint);
          pVisuManager->**DetachHSOFrom**(pViewPoint);

       // Mandatory call
          **CATFrmWindow::DeleteWindow();**
    }
    ...  

---  
##### This method is the opposite of the `Build` method. The temporary objects of the ISO  and the object of the model are "detached" from the CATCommand tree Fig.4. 

  * The _CATISO_ class, through the `RemoveViewer` method, detaches the main viewpoint. It is the main 2D viewpoint for a 2D Viewer and the main 3D viewpoint for a 3D viewer.
  * The _CATVisManager_ , through the `DetachFrom`**** method, detaches the viewpoint. 

You should also detach the PSO and the HSO from the _CATVisManager_. 

At the end of the `DeleteWindow` method, do not forget to call the parent method. It is important to finish the window deletion.
##### DuplicateWindow

You should also detach the PSO and the HSO from the _CATVisManager_.
At the end of the `DeleteWindow` method, do not forget to call the parent method. It is important to finish the window deletion.
This method is called when the end user selects the Window/New Window command. Its role is to create a new instance of the window. 

    ...
    CATFrmWindow * MyWindow :: DuplicateWindow()
    {
       // Window creation
CATFrmWindow * MyWindow :: DuplicateWindow()
       CATString NameOfThis = **GetBaseName**().CastToCharPtr() ;
       CAAAfrHistogramChartWindow * pWindowToReturn = new **MyWindow**(NameOfThis,GetEditor() )  ;
       pWindowToReturn->**Build**();

       // Assigning the characteristic of the current instance 
CATString NameOfThis = **GetBaseName**().CastToCharPtr() ;
CAAAfrHistogramChartWindow * pWindowToReturn = new **MyWindow**(NameOfThis,GetEditor() )  ;
pWindowToReturn->**Build**();
       float r,v,b ;
       _pViewer->**GetBackgroundColor**(&r,&v,&b);   
       CATViewer *pNewViewer = pWindowToReturn->**GetViewer**()
       pNewViewer->**SetBackgroundColor**(r,v,b);

      // Windows title management
_pViewer->**GetBackgroundColor**(&r,&v,&b);
CATViewer *pNewViewer = pWindowToReturn->**GetViewer**()
pNewViewer->**SetBackgroundColor**(r,v,b);
       pWindowToReturn->**SetBaseName**(NameOfThis);
       return  pWindowToReturn ;

    }
    ...  

---  
This method may assign to the new instance all the visual characteristics of the duplicated window. The last action consists in "recomputing" the name of the first window. 

**Defining a Window Creation Interface**

This method may assign to the new instance all the visual characteristics of the duplicated window. The last action consists in "recomputing" the name of the first window.
To create instances of the new window type, you can use the constructor class (new). But it can be useful to create an interface, implemented by the document, to provide a creation method. This last methodology avoids linking the framework which creates the window to the one which uses it.

The source file of the interface implementation must contain: 

    ...
    #include "TIE_MyInterface.h"              
The source file of the interface implementation must contain:
    TIE_MyInterface(CAAEMyInterface); 

    CATImplementClass(CAAEMyInterface, DataExtension, CATBaseUnknown, **XXX**);

    ...      

---  

where:

`MyInterface` | The name of the new interface [12]  
---|---  
`CAAEMyInterface` | The class which implements `MyInterface`  
**`XXX`** | The suffix of the document ( `CATPart` for a Part document for example)  

This interface must have at least one method  which creates an instance of the new window. In general, this method contains three parts:

    ...
This interface must have at least one method  which creates an instance of the new window. In general, this method contains three parts:
    HRESULT CAAEMyInterface::CreateWindow()  

    {
HRESULT CAAEMyInterface::CreateWindow()
       1/ Creating the new window 
       2/ Managing the base name 
       3/ Declaring the window as current

    }
    ...      

---  

  * Creating the new window

    ...
       **CATIEditor** * pIEditor = NULL ;
       HRESULT rc = QueryInterface(IID_CATIEditor, (void**)&pIEditor);
HRESULT rc = QueryInterface(IID_CATIEditor, (void**)&pIEditor);
       if (SUCCEEDED(rc))

       {
HRESULT rc = QueryInterface(IID_CATIEditor, (void**)&pIEditor);
if (SUCCEEDED(rc))
          CATFrmEditor * pEditor = pIEditor->**GetEditor**();
          CATString WindowBaseName ="xxx";
          MyWindow * pWindow = new **MyWindow**(WindowBaseName,pEditor);
          pWindow ->**Build**()

    ...      

---  

We are inside a data extension of the document. The `QueryInterface` on the _CATIEditor_ enables you to retrieve the editor which manages this document.

  * Managing the base name

This section enables you to modify the name of the first window. At first it is important to retrieve the base name of the window, then apply the `SetBaseName` method with this name.

    ...
This section enables you to modify the name of the first window. At first it is important to retrieve the base name of the window, then apply the `SetBaseName` method with this name.
          CATUnicodeString BaseName = pWindow->**GetBaseName**();
          pWindow->**SetBaseName**(BaseName);

    ...      

---  
  * Declaring the window as current

The `SetCurrentWindow` method enables you to give the focus to the new window.

    ...
The `SetCurrentWindow` method enables you to give the focus to the new window.
          CATFrmLayout *currentLayout = CATFrmLayout::**GetCurrentLayout**();
          currentLayout->**SetCurrentWindow**(pWindow)

    ...      

---  

[Top]

* * *
### In Short

This article enables you to understand the role of the main objects defining or managing the V5 interactive application. 

  * _CATApplicationFrame_

This class has only one instance during the session. You essentially use it to retrieve the dialog parent of your dialog box. 

  * _CATFrmLayout_

This class has only one instance during the session. Its role is to manage all the document windows. You use it to retrieve windows and to define the current one. 

  * _CATFrmEditor_

This class controls the visualization and the interactivity of the document. It is the C, in the MVC paradigm, where M is the document and V the window. 

  * _CATFrmWindow_

It is the base class of all the classes defining a window to display a document. 

[Top]

* * *
### References

[1] | [Application Frame Overview](CAAAfrOverview.md)  
---|---  
[2] | [Designing Your Interactive Application](../CAADlgTechArticles/CAADlgInteractiveApplication.md)  
[3] | [Creating a Workbench](../CAAAfrUseCases/CAAAfrSampleWorkbench.md)  
[4] | [Creating an Add-in](../CAAAfrUseCases/CAAAfrSampleAddin.md)  
[5] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)  
[6] | [Creating Dialog Objects](../CAADlgTechArticles/CAADlgCreatingDialogs.md)  
[7] | [Creating a Command that Consists in a Dialog Window](../CAAAfrUseCases/CAAAfrSampleDialogOnly.md)  
[8] | [Arranging Dialog Objects with Tabulation Layout](../CAADlgTechArticles/CAADlgTabLayout.md)  
[9] | [Arranging Dialog Objects with Grid Layout](../CAADlgTechArticles/CAADlgGridLayout.md)  
[10] | [Creating a Document's Window -2](../CAAAfrUseCases/CAAAfrSampleCustomWindow2.md)  
[11] | [Creating a Document's Window -1](../CAAAfrUseCases/CAAAfrSampleCustomWindow1.md)  
[12] | [Creating Interfaces](../CAASysTechArticles/CAASysCreatingInterfaces.md)  
[13] | [The Command Headers](CAAAfrCommandHeaders.md)  
[14] | [Using the Visualization Manager](../CAAVisUseCases/CAAVisSampleVisManager.md)  
[15] | [Interactive Set of Objects](../CAAVisTechArticles/CAAVisISO.md)  
[Top]  

* * *
### History

Version: **1** [Fev 2003] | Document created  
---|---  
[Top]  

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
