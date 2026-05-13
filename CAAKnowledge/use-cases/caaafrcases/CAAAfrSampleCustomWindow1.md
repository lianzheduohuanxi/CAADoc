---
```vbscript
title: "Creating a Document's Window - Part 1"
category: use-case case"
module: "CAAAfrUseCases"
tags: ["CATIDocumentEdit", "CAAGeometry", "CAAxx", "CATISO", "CAAIVisHistogramChartVisu", "CAADegGeoCommands", "CAAxxx", "CAADialogEngine", "CAAyyy", "CAADegHistogramChartWindowCmd", "CATIEditor", "CAAAfrHistogramChartWindow", "CAASysGeoModelInf", "CAAVisualization", "CAAISysDocumentChartWindow", "CAAVisGeoModelInt", "CATI3DGeoVisu", "CAASystem", "CAAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleCustomWindow1.htmmd"
converted: "2026-05-11T17:17:55.693605"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Creating a Document's Window - Part 1

_Enabling a document to be displayed in the V5 application frame_
---|---|---
Use Case

* * *
### Abstract

This article shows how to create a new window class to display an existing document and how to instantiate it from a command. In the other hand, the use case described in the "Creating a Document's Window - Part 2" article [1] explains more precisely the specificity of a multi-viewers window.

  * **What You Will Learn With This Use Case**
  * **The CAAAfrHistogramChartWindow Use Case**
    * What Does CAAAfrHistogramChartWindow Do
    * How to Launch CAAAfrHistogramChartWindow
    * Where to Find the CAAAfrHistogramChartWindow Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

A document, visualized in the V5 application frame, implements the _CATIDocumentEdit_ interface. This interface provides the default window to display it. This use case is intended to show how to create a new type of window for an existing document.

A document, visualized in the V5 application frame, implements the _CATIDocumentEdit_ interface. This interface provides the default window to display it. This use case is intended to show how to create a new type of window for an existing document.
You will learn all the steps to visualize a document with a none-standard way:

  1. How to create the window class deriving from the _CATFrmWindow_ ,
  2. How to manage the MVC  paradigm by using the _CATVisManager_ ,
  3. How to create instances of the window.

At last, before getting in this use case, refer to the technical article [2], to have a complete viewpoint of all the objects implicated in the V5 layout.

[Top]
### The CAAAfrHistogramChartWindow Use Case

CAAAfrHistogramChartWindow is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does CAAAfrHistogramChartWindow Do

CAAAfrHistogramChartWindow is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.
The CAAAfrHistogramChartWindow use case creates a document window for CAAGeometry documents. This new window is launched from the "Histogram Chart Window" command. Refer to the use case entitled "Associating a Dialog Box with a Dialog Agent-2" [3].

 The "Histogram Chart Window" command in the Chart Window toolbar

The CAAAfrHistogramChartWindow use case creates a document window for CAAGeometry documents. This new window is launched from the "Histogram Chart Window" command. Refer to the use case entitled "Associating a Dialog Box with a Dialog Agent-2" [3].
The "Histogram Chart Window" command in the Chart Window toolbar
The top window on the picture below is the default window those created by the _CATIDocumentEdit_ interface. The bottom window, named Model Histogram Chart, is those created by the "Histogram Chart Window" command.

Fig.1: The CAAGeometry Document Window's Types ![](images/CAAAfrCreateWindow11.jpg)

---

The top window on the picture below is the default window those created by the _CATIDocumentEdit_ interface. The bottom window, named Model Histogram Chart, is those created by the "Histogram Chart Window" command.
Fig.1: The CAAGeometry Document Window's Types ![](images/CAAAfrCreateWindow11.jpg)
The two windows displayed the same document (six points, one line and one plane) with two kinds of visualization:

  * In the top window, the elements of the model are visualized in 3D with the _CATI3DGeoVisu_ interface.
  * In the bottom window, the elements are visualized in 2D with the _CAAIVisHistogramChartVisu_**** interface.

The CAAGeometry document implements the _CATIDocumentEdit_ to create the default window. To create the _CAAAfrHistogramChartWindow_ window we have chosen to create a new interface for this document. This interface, _CAAISysDocumentChartWindow_ , enables you to have no link between the framework which contains the definition window (CAAApplicationFrame.edu) and those which contains the command to create a window's instance (CAADialogEngine.edu ).

[Top]
#### How to Launch CAAAfrHistogramChartWindow

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

```vbscript
Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

```

  * On the **File** menu click **New**
  * In the New box, select CAAGeometry and click **OK**
  * Select **Window** ->**Histogram Chart Window**
  * Click **OK**

[Top]
#### Where to Find the CAAAfrHistogramChartWindow Code

The CAAAfrHistogramChartWindow use case is made up of several classes and interfaces:

  * _CAAAfrHistogramChartWindow_  : The document's window class
  * _CAAISysDocumentChartWindow :_ The interface to create a document's window class instance
  * _CAAIVisHistogramChartVisu_**** : The interface to visualized in 2D the document's elements  (not explained here)
  * _CAADegHistogramChartWindowCmd_ : The state command to create a document's window class instance thanks to the _CAAISysDocumentChartWindow  _

There are respectively located in the CAAAfrGeoWindows.m, CAASysGeoModelInf.m, CAAVisGeoModelInt.m and CAADegGeoCommands.m modules of the CAAApplicationFrame.edu, CAASystem.edu, CAAVisualization.edu and CAADialogEngine.edu frameworks:

There are respectively located in the CAAAfrGeoWindows.m, CAASysGeoModelInf.m, CAAVisGeoModelInt.m and CAADegGeoCommands.m modules of the CAAApplicationFrame.edu, CAASystem.edu, CAAVisualization.edu and CAADialogEngine.edu frameworks:
Windows | `InstallRootDirectory/CAAxxx.edu/CAAyyy.m/`

There are respectively located in the CAAAfrGeoWindows.m, CAASysGeoModelInf.m, CAAVisGeoModelInt.m and CAADegGeoCommands.m modules of the CAAApplicationFrame.edu, CAASystem.edu, CAAVisualization.edu and CAADialogEngine.edu frameworks:
Windows | `InstallRootDirectory/CAAxxx.edu/CAAyyy.m/`
Unix | `InstallRootDirectory/CAAxx.edu/CAAyyy.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
To create the Histogram Chart window, there are two steps which can be divided in sub-steps:

  1. **Creating the Document's Window class**
1 | Creating the Histogram Chart Window class

To create the Histogram Chart window, there are two steps which can be divided in sub-steps:
1. **Creating the Document's Window class**
1 | Creating the Histogram Chart Window class
2 | Providing the dialog object behavior
3 | Providing the MDI document window behavior
4 | Duplicating the window
5 | Deleting the window
  2. **Creating Document's Window class instances**
6 | Creating the _CAAISysDocumentChartWindow_ interface

4 | Duplicating the window
5 | Deleting the window
2. **Creating Document's Window class instances**
6 | Creating the _CAAISysDocumentChartWindow_ interface
7 | Implementing the _CAAISysDocumentChartWindow_ interface
8 | Using the _CAAISysDocumentChartWindow_ interface

[Top]
#### Creating the Histogram Chart Window Class

This document window includes one viewer. The class for this window is _CAAAfrHistogramChartWindow_ , whose header file is as follows.

    ...
This document window includes one viewer. The class for this window is _CAAAfrHistogramChartWindow_ , whose header file is as follows.
    class ExportedByCAAAfrGeoWindows CAAAfrHistogramChartWindow: public CATFrmWindow

    {
class ExportedByCAAAfrGeoWindows CAAAfrHistogramChartWindow: public CATFrmWindow
      public:
        CAAAfrHistogramChartWindow(const CATString & iName, CATFrmEditor * iEditor=NULL);
        virtual ~CAAAfrHistogramChartWindow(#);
        void **Build**(#);

        virtual CATFrmWindow * **DuplicateWindow**(#);

        virtual void **DeleteWindow**(#);

        ...
virtual CATFrmWindow * **DuplicateWindow**(#);
virtual void **DeleteWindow**(#);
      private:

        CATNavigation2DViewer * _pViewer ;
        CATPathElement        * _pRootObjectPath ;

    };

---

_CAAAfrHistogramChartWindow_   derives from the _CATFrmWindow_ class. This base class manages the integration of the window in the V5 application layout. The _CAAAfrHistogramChartWindow_   class has:

  * A constructor and a destructor
  * A `DuplicateWindow` method used by the New Window command of the Window menu
  * A `DeleteWindow` to delete or release the specific data of the window.
  * The `Build` method, as usual for a Dialog class, creates and arranges the dialog objects, and for a document's window manages the interactivity.

This class keeps in data member the viewer and the root of the document to display.

The constructor class is simple:

This class keeps in data member the viewer and the root of the document to display.
The constructor class is simple:
    CAAAfrHistogramChartWindow :: CAAAfrHistogramChartWindow

                             ( const CATString &iName, CATFrmEditor * iEditor )
                       : **CATFrmWindow**(iName,iEditor), _pViewer(NULL),_pRootObjectPath(NULL)
    {
    }

---

[Top]
#### Providing the Dialog Object Behavior

The dialog object behavior consists in:

  * Instantiating the viewer to display
  * Arranging the viewer in the document window
  * Setting the current viewer

The `Build` method creates the viewer, arranges it in the window and sets it the current viewer.

The `Build` method creates the viewer, arranges it in the window and sets it the current viewer.
  1. Instantiating the viewer to display

         void CAAAfrHistogramChartWindow :: Build(#)

         {
1. Instantiating the viewer to display
void CAAAfrHistogramChartWindow :: Build(#)
            CATDlgFrame * pFrameWindow = **GetViewerFrame**(#) ;

            CATString ViewerName = "HistogramChar2DViewer" ;
            int width  = 200 ;
            int height = 200 ;
            CATDlgStyle DlgStyle = CATDlgFraNoTitle | CATDlgFraNoFrame ;
            _pViewer = new **CATNavigation2DViewer**(pFrameWindow,ViewerName,
                                                        DlgStyle,width,height) ;
            _pViewer->SetBackgroundColor(0.7f,0.7f,0.7f);
            _pViewer->SetGraduatedBackground(0);

         ...

---

`_pViewer` is a _CATNavigation2DViewer_ class instance:

     * Its parent, `pFrameWindow` , is a _CATDlgFrame_ object created by the _CATFrmWindow_ class [2].
     * Its size (`width` and `height`) is given in pixels.
     * Its background color is white and not gratuaded. (`SetBackgroundColor` and `SetGraduatedBackground` are _CATViewer_ methods)

  2. Arranging the viewer in the document window

         ...
           FrameWindow->**Attach4Sides**(Frame);
         ...

---

FrameWindow->**Attach4Sides**(Frame);
The `Attach4Sides` method attaches `_pViewer` to the four sides of the `pFrameWindow` frame.

  3. Setting the current viewer

         ...
The `Attach4Sides` method attaches `_pViewer` to the four sides of the `pFrameWindow` frame.
3. Setting the current viewer
           _pViewer->**ReframeOn**(0.f,300.f,-20.f,300.f);

           **SetViewer**(_pViewer);
         ...

---

The `Reframe` method ensures that the whole contents of `_pViewer` is displayed, while the `SetViewer` method sets `_pViewer` as the current viewer. We have now a nice document window, but few interactive mechanisms are available. Let's assign them now.

[Top]
#### Providing the MDI Document Window Behavior

The MDI document window behavior consists in:

  * Retrieving the visualization manager and the document root object
  * Requesting the document to create its graphics representation and attaching them to the visualization manager
  * Managing the links between these objects and all the other objects enabling interactivity.

  1. Retrieving the visualization manager and the document root object

Still in the `Build` method, let's now the unique visualization manager be aware of the document to display, under which viewpoints, and with which tools, that is, which interfaces should be queried onto the document objects to make them display.

         ...
1. Retrieving the visualization manager and the document root object
Still in the `Build` method, let's now the unique visualization manager be aware of the document to display, under which viewpoints, and with which tools, that is, which interfaces should be queried onto the document objects to make them display.
           CATFrmEditor * pEditor = **GetEditor**(#);
           CATVisManager * pVisuManager = CATVisManager::**GetVisManager**(#);

```vbscript
           if ( (NULL != pEditor ) && ( NULL != pVisuManager) )

```

            {
CATFrmEditor * pEditor = **GetEditor**(#);
CATVisManager * pVisuManager = CATVisManager::**GetVisManager**(#);
if ( (NULL != pEditor ) && ( NULL != pVisuManager) )
               CATDocument    * pDocument   =  pEditor ->**GetDocument**(#);

               CATBaseUnknown * pRootObject = NULL ;
```vbscript
               if ( NULL != pDocument )

```

               {
CATDocument    * pDocument   =  pEditor ->**GetDocument**(#);
CATBaseUnknown * pRootObject = NULL ;
if ( NULL != pDocument )
                  CATPathElement path = pEditor ->**GetUIActiveObject**(#);
```vbscript
                 _pRootObjectPath = new CATPathElement(path);

```

               }
         ...

---

`pEditor`, a pointer to the editor, is the argument of the window constructor kept by the _CATFrmWindow_ class. Then the visualization manager is retrieved, and the root object. In this use case, the root object is the current UI active object.  A local _CATPathElement ,_ `_pRootObjectPath`, is created to keep "a pointer" on the root object. This path will be released in the destructor.

  2. Requesting the document to create its graphics representation and attaching them to the visualization manager

         ...
2. Requesting the document to create its graphics representation and attaching them to the visualization manager
```vbscript
             if ( NULL != _pRootObjectPath )

```

             {
2. Requesting the document to create its graphics representation and attaching them to the visualization manager
if ( NULL != _pRootObjectPath )
                  CATCommand * pCommandSelector = (CATCommand*) pEditor->**GetCommandSelector**(#);

                  list<IID> ListIVisu;
                  IID visu = IID_**CAAIVisHistogramChartVisu** ;
                  ListIVisu.fastadd(&visu);

                  CATViewpoint  * pViewPoint = NULL ;
```vbscript
                  pViewPoint = (CATViewpoint*) &(_pViewer->**GetMain2DViewpoint**(#));

```

                  pVisuManager->**AttachTo**(_pRootObjectPath,pViewPoint,ListIVisu,pCommandSelector);

         ...

---

pVisuManager->**AttachTo**(_pRootObjectPath,pViewPoint,ListIVisu,pCommandSelector);
The command selector, that is, the command that stands at the top of the command tree, is retrieved. This selector will be the father of a _CATSelector_ class instance created by the `AttachTo` [4]. The manipulators attached to the graphic representation of the model will be linked to this _CATSelector_ enabling the selection and the pre-selection in the viewer.

The list with the interface implemented by the objects of the documents is set up.

The main 2D viewpoint of the viewer is retrieved and attached to the visualization manager along with the document's root object, the list of interfaces to use, and the command selector.

  3. Managing the links between these objects and all the other objects enabling interactivity

         ...
The main 2D viewpoint of the viewer is retrieved and attached to the visualization manager along with the document's root object, the list of interfaces to use, and the command selector.
3. Managing the links between these objects and all the other objects enabling interactivity
                  CATPSO * pPSO = pEditor->**GetPSO**(#) ;
                  pVisuManager->**AttachPSOTo**( pPSO,pViewPoint);

                  CATHSO * pHSO = pEditor->**GetHSO**(#) ;
                  pVisuManager->**AttachHSOTo**( pHSO,pViewPoint);

                  CATISO * pISO = pEditor->**GetISO**(#)  ;
                  pISO->**AddViewer**(_pViewer);

         ...

---

pISO->**AddViewer**(_pViewer);
```vbscript
This piece of code retrieves the Preselected Set of Objects (PSO) and the Highlighted Set of Objects (HSO) from the editor, and requests the visualization controller to attach the  viewpoint to the PSO and to the HSO. Now, when the end user moves the mouse above a representation in a viewer, the path element corresponding to this representation is put in the PSO, is highlighted and put in the HSO.

The Interactive Set of Objects (ISO) is also retrieved. These objects are those which don't belong to the document, but that are so handy to manipulate representations in viewers, such as handles to move or deform them. The ISO now knows the viewer.

```

The document window `Build` method is now complete.

[Top]
#### Duplicating the Window

This is done thanks to the `Duplicate` method.

    ...
This is done thanks to the `Duplicate` method.
    CATFrmWindow * CAAAfrHistogramChartWindow :: DuplicateWindow(#)

    {
CATFrmWindow * CAAAfrHistogramChartWindow :: DuplicateWindow(#)
       CATString NameOfThis = **GetBaseName**(#).CastToCharPtr(#) ;
       CAAAfrHistogramChartWindow * pWindowToReturn = NULL ;
       pWindowToReturn  = new **CAAAfrHistogramChartWindow**(NameOfThis,GetEditor(#) )  ;
       pWindowToReturn ->**Build**(#);
       pWindowToReturn->**SetBaseName**(GetBaseName(#));

       return  pWindowToReturn ;

    }
    ...

---

The `Duplicate` method creates a window of the same type than the current one. This new window is managed by the editor dedicated to the document. This editor is those kept by the current window and retrieved by the `GetEditor` method of the _CATFrmWindow_ base class.

The `SetBaseName` method enables you to manage the window's title. The Fig.1 shows that the name of the window is "Model Histogram Chart". Refer to the "Implementing the _CAAISysDocumentChartWindow_ interface" section.

![](images/CAAAfrCreateWindow13.jpg)
---

The `SetBaseName` method enables to update the title of the first windows if only one exist.

![](images/CAAAfrCreateWindow14.jpg)
---

The title of the first window becomes "Model Histogram Chart:1" and the title of the second window is " Model Histogram Chart:2".

[Top]
#### Deleting the Window

    ...
    void CAAAfrHistogramChartWindow :: DeleteWindow(#)
    {
void CAAAfrHistogramChartWindow :: DeleteWindow(#)
```vbscript
       if ((NULL != GetEditor(#) ) && (NULL != _pViewer) )

```

       {
void CAAAfrHistogramChartWindow :: DeleteWindow(#)
if ((NULL != GetEditor(#) ) && (NULL != _pViewer) )
          CATISO * pISO = NULL ;
```vbscript
          pISO = GetEditor(#)->**GetISO**(#);

          if  (NULL != pISO)   pISO->**RemoveViewer**(_pViewer);

```

          CATViewpoint  * pViewPoint = NULL ;
```vbscript
          pViewPoint = (CATViewpoint*) &(_pViewer->**GetMain2DViewpoint**(#));

```

          CATVisManager * pVisuManager = CATVisManager::**GetVisManager**(#);

```vbscript
          if ( (NULL != pViewPoint) &&  ( NULL != pVisuManager) )

```

          {
CATVisManager * pVisuManager = CATVisManager::**GetVisManager**(#);
if ( (NULL != pViewPoint) &&  ( NULL != pVisuManager) )
             pVisuManager->**DetachPSOFrom**(pViewPoint) ;
             pVisuManager->**DetachHSOFrom**(pViewPoint);

             pVisuManager->**DetachFrom**(_pRootObjectPath,pViewPoint);

          }
       }
pVisuManager->**DetachHSOFrom**(pViewPoint);
pVisuManager->**DetachFrom**(_pRootObjectPath,pViewPoint);
       CATFrmWindow::**DeleteWindow**(#);

    }
    ...

---

The document window is deleted thanks to the `DeleteWindow` method, that removes the viewer from the ISO, then retrieves the viewpoint and detaches it from the PSO and from the HSO, and  that recursively calls the `DeleteWindow` method of the base class. This last line is mandatory to ensure the complete destruction of the window in the V5 layout.

The destructor simply deletes the path to the root object. No need to delete the viewer, since as any dialog object, they will be automatically deleted when the window itself will be deleted.

    ...
The destructor simply deletes the path to the root object. No need to delete the viewer, since as any dialog object, they will be automatically deleted when the window itself will be deleted.
    CAAAfrHistogramChartWindow :: ~CAAAfrHistogramChartWindow (#)

    {
CAAAfrHistogramChartWindow :: ~CAAAfrHistogramChartWindow (#)
       if ( NULL != _pRootObjectPath) _pRootObjectPath->Release(#) ;
       _pRootObjectPath = NULL ;

    }
    ...

---

The document's window class is now complete. You will learn how to create instances.
#### Creating the _CAAISysDocumentChartWindow_ interface

This new interface [6] has only one method, the `CreateHistogramWindow` method.

    ...
This new interface [6] has only one method, the `CreateHistogramWindow` method.
    class ExportedByCAASysGeoModelInf CAAISysDocumentChartWindow : public CATBaseUnknown

    {
class ExportedByCAASysGeoModelInf CAAISysDocumentChartWindow : public CATBaseUnknown
      CATDeclareInterface;

      public :
      virtual HRESULT **CreateHistogramWindow**(#) = 0;

    };
    ...

---
#### Implementing the _CAAISysDocumentChartWindow_ interface

This interface is implemented on the CAAGeometry document. The last argument of the `CATImplementClass` macro is the suffix of the document. It is `CAAGeom` for  the CAAGeometry  and `CATPart` for a Part document.

    ...
    #include "TIE_CAAISysDocumentChartWindow.h"
This interface is implemented on the CAAGeometry document. The last argument of the `CATImplementClass` macro is the suffix of the document. It is `CAAGeom` for  the CAAGeometry  and `CATPart` for a Part document.
    TIE_CAAISysDocumentChartWindow(CAAEAfrDocumentChartWindow);

    CATImplementClass(CAAEAfrDocumentChartWindow, DataExtension, CATBaseUnknown,**CAAGeom**);

    ...

---

The constructor and the destructor are empty.

    ...
The constructor and the destructor are empty.
    CAAEAfrDocumentChartWindow::CAAEAfrDocumentChartWindow(#){}

    CAAEAfrDocumentChartWindow::~CAAEAfrDocumentChartWindow(#){}

    ...

---

The `CreateHistogramWindow` method is similar to the Duplicate method of the _CAAAfrHistogramChartWindow_ class.

    ...
    HRESULT CAAEAfrDocumentChartWindow::CreateHistogramWindow(#)
    {
       // 1- Creating the new instance
HRESULT CAAEAfrDocumentChartWindow::CreateHistogramWindow(#)
       CATUnicodeString **WindowName** = CATMsgCatalog::BuildMessage("CAAAfrHistogramChartWindow",

                                            "BaseName",NULL,0,"Histogram Chart");
HRESULT CAAEAfrDocumentChartWindow::CreateHistogramWindow(#)
CATUnicodeString **WindowName** = CATMsgCatalog::BuildMessage("CAAAfrHistogramChartWindow",
       CATString WindowBaseName = WindowName.ConvertToChar(#);

       CATIEditor * pIEditor = NULL ;
       HRESULT rc = QueryInterface(IID_CATIEditor, (void**)&pIEditor);
```vbscript
       if (SUCCEEDED(rc))

```

       {
CATIEditor * pIEditor = NULL ;
HRESULT rc = QueryInterface(IID_CATIEditor, (void**)&pIEditor);
if (SUCCEEDED(rc))
          CATFrmEditor * pEditor = pIEditor->**GetEditor**(#);
          CAAAfrHistogramChartWindow * pWindow = new **CAAAfrHistogramChartWindow**(WindowBaseName,pEditor);
          pWindow->**Build**(#);

          //2- Managing the Window's Title
CATFrmEditor * pEditor = pIEditor->**GetEditor**(#);
CAAAfrHistogramChartWindow * pWindow = new **CAAAfrHistogramChartWindow**(WindowBaseName,pEditor);
pWindow->**Build**(#);
          CATUnicodeString BaseName = pWindow->**GetBaseName**(#);
          pWindow->**SetBaseName**(BaseName);

          //3- Managing the current window
CATUnicodeString BaseName = pWindow->**GetBaseName**(#);
pWindow->**SetBaseName**(BaseName);
          CATFrmLayout *currentLayout = CATFrmLayout::**GetCurrentLayout**(#);
          currentLayout->**SetCurrentWindow**(pWindow);

          pIEditor->Release(#);
          pIEditor = NULL ;

       }
currentLayout->**SetCurrentWindow**(pWindow);
pIEditor->Release(#);
pIEditor = NULL ;
       return rc ;

    }
    ...

---

This method is divided in three parts:

  * Create a _CAAAfrHistogramChartWindow_ class instance

    * The first identifier is a default name extracted from the CAAAfrHistogramChartWindow.CATNls file. In most cases, this identifier is the complete path of the document. ( the editor knows its document by the `GetDocument` method).

In the CNext/Resources/msgcatalog directory of the CAAApplicationFrame.edu framework you will find the CAAAfrHistogramChartWindow.CATNls file which contains the following line:

    ...
    BaseName = "Model Histogram Chart ";
    ...

---
  * The `GetBaseName` method retrieves the name of the document without its complete path. The `SetBaseName` method enables to modify the title of the already existing windows. Refer to the Duplicate method.

```vbscript
  * Set the current window has current in the V5 application. In other words, the new window has the focus. The windows management is the role of the unique _CATFrmLayout_ class instance [2].

#### Using the _CAAISysDocumentChartWindow_ interface
```

In the _CAADegHistogramChartWindowCmd_ state command [3], there is a transition with the `CreateHistogramChartWindow` action method:

    ...
In the _CAADegHistogramChartWindowCmd_ state command [3], there is a transition with the `CreateHistogramChartWindow` action method:
    CATBoolean CAADegHistogramChartWindowCmd::CreateHistogramChartWindow(void *iDummy)

    {
CATBoolean CAADegHistogramChartWindowCmd::CreateHistogramChartWindow(void *iDummy)
      CATFrmEditor * pEditor = **GetEditor**(#);
```vbscript
      if ( NULL != pEditor )

```

      {
         **CATDocument** * pDocument = pEditor->**GetDocument**(#);
CATFrmEditor * pEditor = **GetEditor**(#);
if ( NULL != pEditor )
```vbscript
```vbscript
         if ( NULL != pDocument )

```

```

         {
            **CAAISysDocumentChartWindow** * pIDocumentChartWnd = NULL ;
```vbscript
if ( NULL != pDocument )
            HRESULT rc = pDocument->QueryInterface(IID_CAAISysDocumentChartWindow,
    			                        (void**)&pIDocumentChartWnd);
            if ( SUCCEEDED(rc) )
```

            {
HRESULT rc = pDocument->QueryInterface(IID_CAAISysDocumentChartWindow,
(void**)&pIDocumentChartWnd);
if ( SUCCEEDED(rc) )
               pIDocumentChartWnd->**CreateHistogramWindow**(#);

              ...
    }
    ...

---

[Top]

* * *
### In Short

Documents of the same type are always displayed in similar windows. You can instantiate the _CATFrmGraphAnd3DWindow_ class and the _CATFrmGraphAnd2DWindow_ class provided by CAA V5, or create your own window which should derive from the _CATFrmWindow_ base class.

Document windows are instantiated in the `CreateDefaultWindow` method of the _CATIDocumentEdit_ interface when the end user clicks File->New or File->Open. For your own window you should provide a new interface which realizes the new window instantiation.

[Top]

* * *
### References

[1] | [Creating a Document's Window - Part 2](CAAAfrSampleCustomWindow1.md)
---|---
[2] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)
[3] | [Associating a Dialog Box with a Dialog Agent - Part 2](../CAADegUseCases/CAADegSampleDialogWithAgent2.md)
[4] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
[Top]

* * *
### History

Version: **1** [Fev 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
