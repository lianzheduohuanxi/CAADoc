---
```vbscript
title: "Creating a Document's Window - Part 2"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CATI2DGeoVisu", "CAAGeometry", "CATISO", "CATI3DGeoVisu", "CAASample", "CAAAfrCustomWindow", "CAAApplicationFrame", "CAAAfrGeoWindows"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleCustomWindow2.htm"
converted: "2026-05-11T17:17:55.703896"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Creating a Document's Window - Part 2

_How to create a multi-viewers window_  
---|---|---  
Use Case  

* * *
### Abstract

This article shows how to create a window to display a document. It explains more precisely the specificity of a multi-viewers window. In the other hand, the use case described in the "Creating a Document's Window - Part 1" article [1] enables you to understand how to launch a document's window from a command. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrCustomWindow Use Case**
    * What Does CAAAfrCustomWindow Do
    * How to Launch CAAAfrCustomWindow
    * Where to Find the CAAAfrCustomWindow Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to create a window with several viewers for document of a given type [2].

[Top]
### The CAAAfrCustomWindow Use Case

CAAAfrCustomWindow is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does CAAAfrCustomWindow Do

The CAAAfrCustomWindow use case creates a document window for CAASample documents.

![CAAAfrCustomWindow.jpg \(42069 bytes\)](images/CAAAfrCustomWindow.jpg)

[Top]
#### How to Launch CAAAfrCustomWindow

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 

  * Select **File** ->**New**
  * In the New box, select **CAASample** and click **OK**

[Top]
#### Where to Find the CAAAfrCustomWindow Code

The CAAAfrCustomWindow use case is made up of a single class named CAAAfrCustomWindow located in the CAAAfrGeoWindows.m module of the CAAApplicationFrame.edu framework:

The CAAAfrCustomWindow use case is made up of a single class named CAAAfrCustomWindow located in the CAAAfrGeoWindows.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoWindows.m\`  

The CAAAfrCustomWindow use case is made up of a single class named CAAAfrCustomWindow located in the CAAAfrGeoWindows.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoWindows.m\`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoWindows.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. It includes the CAAAfrCustomWindow.h  header file in the PrivateInterfaces directory of the CAAApplicationFrame.edu framework and the CAAAfrCustomWindow.cpp source file in the src directory.

[Top]
### Step-by-Step

To create the custom window, there are five steps:
# | Step | Where  
---|---|---  
To create the custom window, there are five steps:
1 | Create the custom window class | LocalInterfaces and src  
2 | Provide the dialog object behavior | `Build` method  
3 | Provide the MDI document window behavior | `Build` method  
4 | Duplicate the window | `Duplicate` method  
5 | Delete the window | `DeleteWindow` and Destructor  

[Top]
#### Creating the Custom Window Class

This document window includes two 3D viewers of different sizes located in the upper part of the window, and a 2D viewer located in the lower part of the window. The class for this window is _CAAAfrCustomWindow_ , whose header file is as follows.

This document window includes two 3D viewers of different sizes located in the upper part of the window, and a 2D viewer located in the lower part of the window. The class for this window is _CAAAfrCustomWindow_ , whose header file is as follows.
    class CAAAfrCustomWindow: public CATFrmWindow

    {
This document window includes two 3D viewers of different sizes located in the upper part of the window, and a 2D viewer located in the lower part of the window. The class for this window is _CAAAfrCustomWindow_ , whose header file is as follows.
class CAAAfrCustomWindow: public CATFrmWindow
      public:
        CAAAfrCustomWindow(const CATString & iName, CATFrmEditor * iEditor=NULL);
        virtual ~CAAAfrCustomWindow();

        virtual CATFrmWindow * **DuplicateWindow**();
        virtual void **DeleteWindow**();

        void **Build**();

        void **GetViewers**(CATNavigation3DViewer ** oV1,
                           CATNavigation3DViewer ** oV2, 
                           CATNavigation2DViewer ** oV3);

       ...
void **GetViewers**(CATNavigation3DViewer ** oV1,
CATNavigation3DViewer ** oV2,
CATNavigation2DViewer ** oV3);
      private:
        CATNavigation3DViewer * _pViewer1;
        CATNavigation3DViewer * _pViewer2;
        CATNavigation2DViewer * _pViewer3;
        CATPathElement        * _pRootObjectPath;

    };  

---  

_CAAAfrCustomWindow_ has 

  * a constructor and a destructor.
  * a `DuplicateWindow` method used by the New Window command of the Window menu.
  * a `DeleteWindow` method called when the end user closes the window or closes the document.
  * a `Build` method as all the Dialog boxes.
  * a `GetViewers` method to retrieve pointers to its three viewers. 
  * Its data members are the three navigation viewers and the root model to display.

The constructor class is simple.

The constructor class is simple.
    CAAAfrCustomWindow::CAAAfrCustomWindow(const CATString & iName,
                                           CATFrmEditor    * iEditor)

                      : **CATFrmWindow**(iName, iEditor),
CAAAfrCustomWindow::CAAAfrCustomWindow(const CATString & iName,
CATFrmEditor    * iEditor)
                        _pViewer1(NULL), _pViewer2(NULL), _pViewer3(NULL),
                        _pRootObjectPath(NULL),

    {
    }   

---  

[Top]
#### Providing the Dialog Object Behavior

The dialog object behavior consists in: 

  * Instantiating the different viewers to display
  * Arranging these viewers in the document window
  * Setting the current viewer

The constructor creates the viewers, arranges them in the window and sets one of them the current viewer. 

The constructor creates the viewers, arranges them in the window and sets one of them the current viewer.
  1. Instantiating the different viewers to display 

         void CAAAfrCustomWindow::Build()

         {
1. Instantiating the different viewers to display
void CAAAfrCustomWindow::Build()
           int width, height;
           CATString  ViewerName; 

           CATDlgFrame * FrameWindow = **GetViewerFrame**() ;
           CATString FrameName = "FrameName";
           CATDlgFrame * Frame = new CATDlgFrame(FrameWindow, FrameName,
                                                 CATDlgGridLayout|CATDlgFraNoFrame);

           ViewerName = "Viewer3Dnum1";
           width = 200 ; height = 200;
           _pViewer1 = new CATNavigation3DViewer(Frame, ViewerName, width, height);

           ViewerName = "Viewer3Dnum2" ;
           width = 200 ; height = 300 ;
           _pViewer2 = new CATNavigation3DViewer(Frame, ViewerName, width, height);

           ViewerName = "Viewer2D" ;
           width = 200 ; height = 500 ;
           _pViewer3 = new CATNavigation2DViewer(Frame, ViewerName, width, height);

         ...     

---  

_pViewer3 = new CATNavigation2DViewer(Frame, ViewerName, width, height);
The viewer sizes are given in pixels. The MDI application window, here named Frame, is the parent of the viewers. This frame has been created to be inserted between the frame created by the _CATFrmWindow_ ( `FrameWindow` ) and the viewers. It allows us to arrange the viewers with the grid layout and not with the tabulation layout [3] which is a little bit more complex. The `FrameWindow` frame has not been created with the `CATDlgGridLayout` style [1]. 

  2. Arranging these viewers in the document window 

         ...
The viewer sizes are given in pixels. The MDI application window, here named Frame, is the parent of the viewers. This frame has been created to be inserted between the frame created by the _CATFrmWindow_ ( `FrameWindow` ) and the viewers. It allows us to arrange the viewers with the grid layout and not with the tabulation layout [3] which is a little bit more complex. The `FrameWindow` frame has not been created with the `CATDlgGridLayout` style [1].
2. Arranging these viewers in the document window
           FrameWindow->Attach4Sides(Frame);
           _pViewer1->SetGridConstraints(0,0,1,1,CATGRID_4SIDES);
           _pViewer2->SetGridConstraints(0,1,1,1,CATGRID_4SIDES);
           _pViewer3->SetGridConstraints(1,0,2,1,CATGRID_4SIDES);
           Frame->SetGridRowResizable(0,1);
           Frame->SetGridRowResizable(1,1);
           Frame->SetGridColumnResizable(0,1);
           Frame->SetGridColumnResizable(1,1);

         ...        

---  

Frame->SetGridColumnResizable(1,1);
The `Attach4Sides` method attaches the `Frame` object to the four sides of the `FrameWindow` object. It is a method used by the tabulation layout. 

Then the `SetGridConstraints` method applied to `_Viewer1` is located on grid cells beginning with the cell at the intersection of the row 0 and column 0, and expands from left to right on 1 row, and from top to bottom on 1 column. `CATGRID_4SIDES` means that the viewer occupies the whole cell space. Row 0 and 1, as well as columns 0 and 1, as first argument of the `SetGridxxResizable` methods, are declared to be resizable since the second argument is 1 (on the opposite, 0 means non resizable.)

![CAAAfrCustomWindow.gif \(2992 bytes\)](images/CAAAfrCustomWindow.gif)

  3. Setting the current viewer 

         ...
3. Setting the current viewer
           _pViewer1->Reframe();
           SetViewer(_pViewer1);

         ...        

---  

```vbscript
SetViewer(_pViewer1);
The `Reframe` method ensures that the whole contents of `_pViewer1` is displayed, while the `SetViewer` method sets `_pViewer1` as the current viewer. You will retrieve this viewer with the `GetViewer` method of the _CATFrmWindow_ class. 

We have now a nice document window, but few interactive mechanisms are available. Let's assign them now.

```

[Top]
#### Providing the MDI Document Window Behavior

The MDI document window behavior consists in: 

  * Retrieving the visualization manager and the document root object
  * Requesting the document to create its graphics representation(s) and attaching them to the visualization manager
  * Managing the links between these objects and all the other objects enabling interactivity.

  1. Retrieving the visualization manager and the document root object 

Still in the `Build` method, let's now the unique visualization manager be aware of the document to display, under which viewpoints. The `GetEditor` method of the _CATFrmWindow_ enables you to retrieve the editor of the constructor class.

         ...
1. Retrieving the visualization manager and the document root object
Still in the `Build` method, let's now the unique visualization manager be aware of the document to display, under which viewpoints. The `GetEditor` method of the _CATFrmWindow_ enables you to retrieve the editor of the constructor class.
           CATFrmEditor * pEditor = **GetEditor**();
           CATVisManager * pVisuManager = CATVisManager::**GetVisManager**();

           // Here is the code to retrieve the root model, pRootObject
         ...  

---  

In this article the code to retrieve the model to display is not explained once it is not useful for a real V5 document. 

  2. Requesting the document to create its graphics representation(s) and attaching them to the visualization manager 

         ...
In this article the code to retrieve the model to display is not explained once it is not useful for a real V5 document.
2. Requesting the document to create its graphics representation(s) and attaching them to the visualization manager
           if ( (NULL != pEditor  ) && (NULL != pRootObject ) && (NULL != pVisuManager) )

             { 
2. Requesting the document to create its graphics representation(s) and attaching them to the visualization manager
if ( (NULL != pEditor  ) && (NULL != pRootObject ) && (NULL != pVisuManager) )
               _pRootObjectPath = new CATPathElement(pRootObject);

               CATCommand * CommandSelector = (CATCommand*) pEditor->**GetCommandSelector**();

               list<IID> ListIVisu3d, ListIVisu2d;
               IID visu3d = IID_CATI3DGeoVisu;
               IID visu2d = IID_CATI2DGeoVisu;
               ListIVisu3d.fastadd(&visu3d);
               ListIVisu2d.fastadd(&visu2d);

               CATViewpoint * pViewPoint1 = NULL;
               CATViewpoint * pViewPoint2 = NULL;
               CATViewpoint * pViewPoint3 = NULL;

               pViewPoint1 = (CATViewpoint*) &(_pViewer1->GetMain3DViewpoint());
               pVisuManager->**AttachTo**(_pRootObjectPath,pViewPoint1,ListIVisu3d,CommandSelector);

               pViewPoint2 = (CATViewpoint*) &(_pViewer2->GetMain3DViewpoint());
               pVisuManager->AttachTo(_pRootObjectPath,pViewPoint2,ListIVisu3d,CommandSelector);

               pViewPoint3 = (CATViewpoint*) &(_pViewer3->GetMain2DViewpoint());
               pVisuManager->AttachTo(_pRootObjectPath,pViewPoint3,ListIVisu2d,CommandSelector);

         ...  

---  

pVisuManager->AttachTo(_pRootObjectPath,pViewPoint3,ListIVisu2d,CommandSelector);
If the editor, the visualization manager, and the root object are successfully retrieved, this root object is then turned to a _CATPathElement_ , the command selector, that is, the command that stands at the top of the command tree [4], is retrieved, and the lists of 2D and 3D interfaces implemented by the objects of the documents are set up. Then for each viewer, its main viewpoint is retrieved and attached to the visualization manager along with the document's root object, the list of interfaces to use, and the command selector.

  3. Managing the links between these objects and all the other objects enabling interactivity 

         ...
```vbscript
If the editor, the visualization manager, and the root object are successfully retrieved, this root object is then turned to a _CATPathElement_ , the command selector, that is, the command that stands at the top of the command tree [4], is retrieved, and the lists of 2D and 3D interfaces implemented by the objects of the documents are set up. Then for each viewer, its main viewpoint is retrieved and attached to the visualization manager along with the document's root object, the list of interfaces to use, and the command selector.
3. Managing the links between these objects and all the other objects enabling interactivity
               CATPSO * pPSO = pEditor->**GetPSO**() ;  // Preselected Set Objects 
               CATHSO * pHSO = pEditor->**GetHSO**() ;  // Highlighted Set Objects 

               pVisuManager->**AttachPSOTo**(pPSO, pViewPoint1);
               pVisuManager->AttachPSOTo(pPSO, pViewPoint2);
               pVisuManager->AttachPSOTo(pPSO, pViewPoint3);
               pVisuManager->**AttachHSOTo**(pHSO, pViewPoint1);
               pVisuManager->AttachHSOTo(pHSO, pViewPoint2);
               pVisuManager->AttachHSOTo(pHSO, pViewPoint3);

               CATISO * pISO = pEditor->**GetISO**(); 
               pISO->**AddViewer**(_pViewer1);
               pISO->AddViewer(_pViewer2);
               pISO->AddViewer(_pViewer3);
```

             }
           }
         }
         ...  

---  

This piece of code retrieves the Preselected Set of Objects (PSO) and the Highlighted Set of Objects (HSO) from the editor, and requests the visualization controller to attach the appropriate viewpoints to the PSO and to the HSO. Now, when the end user moves the mouse above a representation in a viewer, the path element corresponding to this representation is put in the PSO, is highlighted and put in the HSO. 

This piece of code retrieves the Preselected Set of Objects (PSO) and the Highlighted Set of Objects (HSO) from the editor, and requests the visualization controller to attach the appropriate viewpoints to the PSO and to the HSO. Now, when the end user moves the mouse above a representation in a viewer, the path element corresponding to this representation is put in the PSO, is highlighted and put in the HSO.
The Interactive Set of Objects (ISO) is also retrieved. These objects are those which don't belong to the document, but that are so handy to manipulate representations in viewers, such as handles to move or deform them. The ISO now knows the three viewers.

The document window `Build` method is now complete.

[Top]
#### Duplicating a Document Window

This is done thanks to the Duplicate method.

    ...
This is done thanks to the Duplicate method.
    CATFrmWindow * CAAAfrCustomWindow :: DuplicateWindow()

    {
CATFrmWindow * CAAAfrCustomWindow :: DuplicateWindow()
      CATString NameOfThis = GetBaseName().CastToCharPtr();
      CAAAfrCustomWindow * pWindowToReturn = NULL;
      pWindowToReturn = new **CAAAfrCustomWindow**(NameOfThis,GetEditor());
      pWindowToReturn->**Build**();

      pWindowToReturn->**SetBaseName**(GetBaseName());

      float r,v,b ;
      if (NULL != _pViewer1) _pViewer1->**GetBackgroundColor**(&r, &v, &b);

      CATNavigation3DViewer * pV1 = NULL;
      CATNavigation3DViewer * pV2 = NULL;
      CATNavigation2DViewer * pV3 = NULL;

      pWindowToReturn->**GetViewers**(&pV1, &pV2, &pV3);
      if (NULL != pV1) pV1->**SetBackgroundColor**(r, v, b);

      return  pWindowToReturn;

    }
    ...  

---  

The `Duplicate` method is now complete. It performs the following: 

  * Creates a window of the same type than the current one
  * Sets the same name than the current one. The `SetBaseName` method modifies the name of the first window if only one exists. At the base name, an index is added [2].
  * Retrieves the background color of the first viewer as a RGB triplet
  * Retrieves the created window viewers
  * Sets the retrieved background color to the first viewer of the created window

This method uses the `GetViewers` method below:

This method uses the `GetViewers` method below:
    void CAAAfrCustomWindow :: GetViewers(CATNavigation3DViewer ** oV1,
                                          CATNavigation3DViewer ** oV2, 
                                          CATNavigation2DViewer ** oV3)

    {
      *oV1 = _pViewer1;
      *oV2 = _pViewer2;
      *oV3 = _pViewer3;
    }  

---  

[Top]
#### Deleting the Window

    ...
    void CAAAfrCustomWindow::DeleteWindow()
    {
void CAAAfrCustomWindow::DeleteWindow()
      if ( (NULL != GetEditor()) && (NULL != pViewer1) &&
           (NULL != pViewer2)    && (NULL != pViewer3) )

      {
        // Detaches Viewers from the ISO 
```vbscript
if ( (NULL != GetEditor()) && (NULL != pViewer1) &&
(NULL != pViewer2)    && (NULL != pViewer3) )
        CATISO *pISO = NULL;
        pISO = **GetEditor**()->GetISO();
        if (NULL != pISO) pISO->**RemoveViewer**(_pViewer1);
        if (NULL != pISO) pISO->RemoveViewer(_pViewer2);
        if (NULL != pISO) pISO->RemoveViewer(_pViewer3);

```

        // Retrieves Viewpoints
```vbscript
if (NULL != pISO) pISO->**RemoveViewer**(_pViewer1);
if (NULL != pISO) pISO->RemoveViewer(_pViewer2);
if (NULL != pISO) pISO->RemoveViewer(_pViewer3);
        CATViewpoint * pViewpoint1 = NULL;
        CATViewpoint * pViewpoint2 = NULL;
        CATViewpoint * pViewpoint3 = NULL;
        pViewpoint1 = (CATViewPoint *) &(_pViewer1->GetMain3DViewpoint());
        pViewpoint2 = (CATViewPoint *) &(_pViewer2->GetMain3DViewpoint());
        pViewpoint3 = (CATViewPoint *) &(_pViewer3->GetMain2DViewpoint());

```

        // Retrieves the unique visu manager
pViewpoint1 = (CATViewPoint *) &(_pViewer1->GetMain3DViewpoint());
pViewpoint2 = (CATViewPoint *) &(_pViewer2->GetMain3DViewpoint());
pViewpoint3 = (CATViewPoint *) &(_pViewer3->GetMain2DViewpoint());
        CATVisManager *pVisuManager = **CATVisManager::GetVisManager**();
        if ( (NULL != pViewpoint1) &&
             (NULL != pViewpoint2) &&
             (NULL != pViewpoint3) && (NULL != pVisuManager) )

        {
          // Detaches Viewpoints from PSO and HSO
```vbscript
if ( (NULL != pViewpoint1) &&
(NULL != pViewpoint2) &&
(NULL != pViewpoint3) && (NULL != pVisuManager) )
          pVisuManager->**DetachPSOFrom**(pViewpoint1);
          pVisuManager->DetachPSOFrom(pViewpoint2);
          pVisuManager->DetachPSOFrom(pViewpoint3);
          pVisuManager->**DetachHSOFrom**(pViewpoint1);
          pVisuManager->DetachHSOFrom(pViewpoint2);
          pVisuManager->DetachHSOFrom(pViewpoint3);

```

          // Detaches Viewpoints from the visu manager
pVisuManager->**DetachHSOFrom**(pViewpoint1);
pVisuManager->DetachHSOFrom(pViewpoint2);
pVisuManager->DetachHSOFrom(pViewpoint3);
          pVisuManager->**DetachFrom**(_pRootObjectPath, pViewpoint1);
          pVisuManager->DetachFrom(_pRootObjectPath, pViewpoint2);
          pVisuManager->DetachFrom(_pRootObjectPath, pViewpoint3);

        }
      }
      **CATFrmWindow::DeleteWindow**();
    }

    CAAAfrCustomWindow::~CAAAfrCustomWindow()
    {
CAAAfrCustomWindow::~CAAAfrCustomWindow()
      if (NULL != _pRootObjectPath) delete _pRootObjectPath;
      _pRootObjectPath = NULL;

    }
    ...      

---  

The document window is deleted thanks to the `DeleteWindow` method, that removes the viewers from the ISO, then retrieves their viewpoints and detaches them from the PSO and from the HSO, and  that recursively calls the `DeleteWindow` method of the base class. The destructor simply deletes the path to the root object. No need to delete the viewers, since as any dialog object, they will be automatically deleted when the window itself will be deleted.

[Top]

* * *
### In Short

This use case explains the structure of a document's window class:

  * A `Build` method 
    * To create and arrange the viewers in the window,
    * To attach the root's document and the Interactive Set Objects to the command tree.
  * A `DuplicateWindow` method to create a new instance from an existing one. 
  * A `DeleteWindow` method to detach the root's document and the Interactive Set Objects from the command tree. 

[Top]

* * *
### References

[1] | [Creating a Document's Window - Part 1](CAAAfrSampleCustomWindow1.md)  
---|---  
[2] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)  
[3] | [Arranging Dialog Objects](../CAADlgTechArticles/CAADlgObjectLayout.md)  
[4] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)  
[Top]  

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Mar 2003] | Document updated  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
