---
title: "Using the Visualization Manager"
category: "use case"
module: "CAAVisUseCases"
tags: ["CAAVisManager", "CAAVisManagerDefaultDocument", "CAAVisManagerAppli", "CATI3DGeoVisu", "CAAVisManagerInt", "CAAVisManagerDocument", "CAAVisManagerCGRDocument", "CAAIVis2DGraphVisu", "CAAVisManagerCmdSelector", "CATIA", "CAAVisManagerComp", "CAAVisManagerApplicationFrame", "CAAVisManagerImp", "CAAVisManagerApplication", "CAAVisManagerWindow", "CAAVisualization", "CAAVisManagerEditor"]
source_file: "Doc\online\CAAVisUseCases\CAAVisSampleVisManager.htm"
converted: "2026-05-11T17:31:52.224318"
---

# 3D PLM Enterprise Architecture

| 

## 3D Visualization

| 

### Using the Visualization Manager

_Attaching the visualization manager to and detaching it from documents and viewpoints_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article discusses the CAAVisManager use case. This use case explains how to create and implement a specific visualization interface for geometric components, how to make the visualization manager aware of this interface to display these components, and how to catch the visualization notification to manage the PSO and HSO contents. This article focuses on using the visualization manager.

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

The visualization manager is the unique instance of the _CATVisManager_ class that manages the display of all the documents in all their windows. It is a key object in the visualization process that needs information about the documents to display, such as the document root object, the visualization interfaces that the document implements for 3D and 2D viewpoints, the selector to which visualization notifications must be sent, and the PSO (Prehighlighted Set of Objects) and HSO (Highlighted Set of Objects) associated with the document. With this use case, you will learn how to make the visualization manager aware of this information when a document is created or opened, and how to inform it to forget this information when a document is closed. Companion articles of this use case deal with the implementation of a visualization interface of your own [1], and with catching visualization notifications [2].

[Top]

### The CAAVisManager Use Case

CAAVisManager is a set of use cases of the CAAVisualization.edu framework that illustrates Visualization framework capabilities.

[Top]

#### What Does CAAVisManager Do

CAAVisManager contains a series of modules that make up a small MDI (Multiple Document Interface) application dedicated to showing and explaining the role of the visualization manager. The main objects are:

  * The application itself
  * The application frame window (or main window)
  * The documents
  * The document windows: a document can be displayed in several windows
  * The editors: an editor is associated with each document
  * The editor selector
  * The visualization manager
  * The selector



Even if the CATIA application is a bit more complex than this application and involves more objects, those listed here, along with their respective roles and relations, are identical, and are just shown to explain what you should do to work with the unique instance of the visualization manager.

![](images/CAAVisSampleManager.jpg)

Let's briefly describe them. The application manages two lists: one for the documents, and one for the windows that display these documents. At all times, one of the documents, if any, is active, and is known as such. The application is the parent of the application frame window from the command tree structure standpoint [3], that is in turn the parent of all the document windows. An editor is associated with one and only one document, and is known by the document and by all its windows. A selector is associated with the editor and creates a _CATPSO_ and a _CATHSO_ instances to store pointers to the preselected and selected components respectively. The selector is the parent, again from the command tree structure standpoint, of the _CATSelector_ instance created by the visualization manager for each document. Because of this parent-child relation, the editor selector will receive the notifications affecting the document and coming from the viewers [4] in which it is displayed and passed to the _CATSelector_ instance. In the same way, to get notifications affecting the viewer background, that is, that do not impact the document itself, a _CAT3DIndicator_ instance is created by the document window and is assigned the editor as parent to catch these notifications that otherwise would be lost. The selector should redefine the `AnalyseNotification` method to catch these notifications [2].

[Top]

#### How to Launch the CAAVisManager

To launch CAAVisManager, you will need to set up the build time environment, then compile the four CAAVisManager modules along with their prerequisites, set up the run time environment, and then execute the use case [5]. You cannot launch CAAVisManager itself. CAAVisManager is simply used by the CAAVisManagerAppli use case. Type CAAVisManagerAppli instead of CAAVisManager to display the interactive application along with a viewer that displays the CAAVisManagerDefaultDocument.

[Top]

#### Where to Find the CAAVisManager Code

CAAVisManager code is located in the CAAVisualization.edu framework:

Windows | `InstallRootDirectory\CAAVisualization.edu\`  
---|---  
Unix | `InstallRootDirectory/CAAVisualization.edu/`  
  
where `InstallRootDirectory` is the root directory of your CAA V5 installation. 

CAAVisManager includes the following modules:

CAAVisManagerAppli.m | Contains the interactive application, the windows and the documents  
---|---  
CAAVisManagerComp.m | Contains the geometric components to display  
CAAVisManagerImp.m | Contains the extension classes required to make the geometric components displayable  
CAAVisManagerInt.m | Contains the interfaces implemented by the geometric components, especially the visualization interface. Their header files are located in the PrivateInterfaces directory  
  
CAAVisManagerAppli.m includes the following classes:

CAAVisManagerApplication | Interactive application  
---|---  
CAAVisManagerApplicationFrame | Application frame window that hosts the application  
CAAVisManagerDocument | Base document  
CAAVisManagerDefaultDocument | Document displayed when launching the use case  
CAAVisManagerCGRDocument | CGR document  
CAAVisManagerWindow | Document window  
CAAVisManagerEditor | Document editor  
CAAVisManagerCmdSelector | Selector  
  
[Top]

### Step-by-Step

To use the visualization manager, there are four main steps:

  1. Retrieving the Visualization Manager
  2. Attaching the Visualization Manager to the Main 3D Viewpoint, the HSO and the PSO
  3. Attaching the Visualization Manager to the Main 2D Viewpoint, the HSO and the PSO
  4. Detaching the Visualization Manager



[Top]

#### Retrieving the Visualization Manager
    
    
    void CAAVisManagerWindow::Attach()
    {
      CATVisManager            *pVisuMgr  = **CATVisManager::GetVisManager()** ;
      ...  
  
---  
  
The `CATVisManager::GetVisManager` static method retrieves a pointer to the visualization manager.

[Top]

#### Attaching the Visualization Manager to the Main 3D Viewpoint, the HSO and the PSO
    
    
      ...
      CAAVisManagerDocument    *pDocument = _pEditor->GetDocument();
      CAAVisManagerCmdSelector *pSelector = _pEditor->GetSelector();
    
      if ( (NULL != pDocument) && (NULL != pDocument->GetRootContainer()) )
      {
        CATBaseUnknown * pRootObject = pDocument->GetRootContainer();
        _pRootObjectPath = new CATPathElement(pRootObject);
      }
    
      if ( (NULL != _pViewer) && ( NULL!= _pRootObjectPath) )
      {
        CAT3DViewpoint * pMain3DViewpoint = &(_pViewer->**GetMain3DViewpoint**());
    
        list<IID> liste_iid_3D;
        liste_iid_3D += new IID(IID_CATI3DGeoVisu);
        pVisuMgr->**AttachTo**   (_pRootObjectPath,
                              pMain3DViewpoint,
                              liste_iid_3D,
                              pSelector);
        pVisuMgr->**AttachHSOTo**(_pEditor->GetHSO(), pMain3DViewpoint);
        pVisuMgr->**AttachPSOTo**(_pEditor->GetPSO(), pMain3DViewpoint);
        delete liste_iid_3D[0];
        ...  
  
---  
  
The document and the selector associated with the document editor are both retrieved from the editor, and the document root object is retrieved as a CATPathElement instance. Then the main 3D viewpoint of the 3D viewer is retrieved using the `GetMain3DViewPoint` method. A list of 3D visualization interface IIDs is created and the _CATI3DGeoVisu_ interface IID is added to the list. Then the visualization manager can be attached to the document thanks to the `AttachTo` method:

  * Through a unique object: its root object path
  * Seen from a given viewpoint: the main 3D viewpoint of the viewer
  * Using a given list of visualization interfaces, limited here to _CATI3DGeoVisu_ , but that will be used in their appending order if there are several ones
  * The visualization manager will forward the visualization notifications that affect the document to the editor selector



Then the visualization manager is attached for highlighted components to the editor's HSO and to the viewer's main 3D viewpoint using the `AttachHSOTo` method, and attached for prehighlighted components to the editor's PSO and again to the viewer's main 3D viewpoint using the `AttachPSOTo` method.

[Top]

#### Attaching the Visualization Manager to the 2D Main Viewpoint, the HSO and the PSO
    
    
        ...
        CAT2DViewpoint * pMain2DViewpoint = &(_pViewer->GetMain2DViewpoint());
    
        list<IID> liste_iid_2D;
        liste_iid_2D += new IID(IID_CAAIVis2DGraphVisu);
        pVisuMgr->**AttachTo**  (_pRootObjectPath,
                             pMain2DViewpoint,
                             liste_iid_2D,
                             pSelector);
        pVisuMgr->**AttachHSOTo**(_pEditor->GetHSO(), pMain2DViewpoint);
        pVisuMgr->**AttachPSOTo**(_pEditor->GetPSO(), pMain2DViewpoint);
        delete liste_iid_2D[0];
        ...
      }
    }  
  
---  
  
The main 2D viewpoint of the 3D viewer is retrieved using the `GetMain2DViewPoint` method. A list of 2D visualization interface IIDs is created and the _CAAIVis2DGraphVisu_ interface IID is added to the list. Then the visualization manager can be attached to the document thanks to the `AttachTo` method:

  * Through a unique object: its root object path
  * Seen from a given viewpoint: the main 2D viewpoint of the viewer
  * Using a given list of visualization interfaces, limited here to _CAAIVis2DGraphVisu_ , but that will be used in their appending order if there are several ones
  * The visualization manager will forward the visualization notifications that affect the document to the editor selector that should retrieve them [x].



Then the visualization manager is attached for highlighted components to the editor's HSO and to the viewer's main 2D viewpoint using the `AttachHSOTo` method, and attached for prehighlighted components to the editor's PSO and again to the viewer's main 2D viewpoint using the `AttachPSOTo` method.

The main 2D viewpoint zoom and origin are reset.

[Top]

#### Detaching the Visualization Manager
    
    
    void CAAVisManagerWindow::Detach()
    {
      CATVisManager * pVisuManager = **CATVisManager::GetVisManager**();
    
      if ( (NULL != _pViewer) && (NULL != _pRootObjectPath) )
      {
        CAT3DViewpoint * pMain3DViewpoint = &(_pViewer->GetMain3DViewpoint());
    
        pVisuManager->**DetachFrom**(_pRootObjectPath, pMain3DViewpoint);
        pVisuManager->**DetachHSOFrom**(pMain3DViewpoint);
        pVisuManager->**DetachPSOFrom**(pMain3DViewpoint);
    
        CAT2DViewpoint * pMain2DViewpoint = &(_pViewer->GetMain2DViewpoint());
    
        pVisuManager->DetachPSOFrom(pMain2DViewpoint);
        pVisuManager->DetachHSOFrom(pMain2DViewpoint);
        pVisuManager->DetachFrom(_pRootObjectPath, pMain2DViewpoint);
      }
    }  
  
---  
  
The `CATVisManager::GetVisManager` static method retrieves a pointer to the visualization manager. Then the visualization manager is detached from the document and from the viewer's main 3D viewpoint using the `DetachFrom` method. Then the visualization manager is detached for highlighted and prehighlighted components from the viewer's main 3D viewpoint using the `DetachHSOFrom` and `DetachPSOFrom` methods respectively. The same applies to the main 2D viewpoint.

[Top]

* * *

### In Short

This use case shows how to use the visualization manager to make it aware of the visualization interfaces to call for the document to display in both 3D and 2D viewpoints, and how to make sure that visualization notifications that affect the document can be retrieved, using the `AttachTo` method of _CATVisManager_. It shows also how to attach the visualization manager to the document's editor PSO and HSO using the `AttachPSOTo` and `AttachHSOTo` methods of _CATVisManager_ respectively. In addition, it shows how to perform the detachments using the `DetachFrom`, `DetachPSOFrom`, and `DetachHSOFrom` methods.

[Top]

* * *

### References

[1] | [Making a Component Displayable With CATI3DGeoVisu](CAAVisSampleCATIVisu.htm)  
---|---  
[2] | [Catching the Visualization Notifications](CAAVisSampleCatchNotifications.htm)  
[3] | [The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.htm)  
[4] | [Conveying End User Intent from Mouse to Controller](../CAAVisTechArticles/CAAVisViewerProtocol.htm)  
[5] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
[Top]  
  
* * *

### History

Version: **1** [May 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
