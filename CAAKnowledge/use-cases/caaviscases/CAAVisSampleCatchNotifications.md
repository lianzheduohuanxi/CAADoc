---
title: "Catching the Visualization Notifications"
category: "use case"
module: "CAAVisUseCases"
tags: ["CAAVisManager", "CAAVisManagerDefaultDocument", "CAAVisManagerAppli", "CATI3DGeoVisu", "CAAVisManagerInt", "CAAVisManagerCxtMenu", "CAAVisManagerCmdSelector", "CAAVisManagerComp", "CAAIVisManagerCmdSelector", "CAAVisManagerImp", "CAAVisualization"]
source_file: "Doc\online\CAAVisUseCases\CAAVisSampleCatchNotifications.htm"
converted: "2026-05-11T17:31:52.051717"
---

# 3D PLM Enterprise Architecture

| 

## 3D Visualization

| 

### Catching the Visualization Notifications

_Redefining the AnalyseNotification method of a document editor selector_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article discusses the CAAVisManager use case. This use case explains how to create and implement a specific visualization interface for geometric components, how to make the visualization manager aware of this interface to display these components, and how to catch the visualization notifications to manage the PSO and HSO contents. This article focuses on catching the visualization notifications. 

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

When a document is displayed in one or several windows and when the end user works in one of these windows, visualization notifications [1] that indicate the end user intents or actions are sent to a selector object attached to the document's editor. This selector must catch the notifications to process, take appropriate actions, and must be transparent for other notifications. With this use case, you will learn how a selector object can catch and process the visualization notifications. Companion articles of this use case deal with the implementation of a visualization interface of your own [2], and with the use of the visualization manager [3].

[Top]

### The CAAVisManager Use Case

CAAVisManager is a set of use cases of the CAAVisualization.edu framework that illustrates Visualization framework capabilities.

[Top]

#### What Does CAAVisManager Do

CAAVisManager contains a series of modules that make up a small application. This article focuses on catching the visualization notifications to manage the PSO and HSO contents, how to decode a path element, and how to set a contextual menu on component representations. To do this, a selector class [3] deriving from the _CATCommand_ class [4] is created. It is instantiated for each document by the document's editor, and passed to the visualization manager when attaching it to the document root object. Thus, the visualization notifications are sent to the selector that can decide to process them. The selector recognizes the notifications in the redefined `AnalyseNotification` method inherited from _CATCommand_.

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
  
This use case details the `AnalyseNotification` method of the _CAAVisManagerCmdSelector_ class in the CAAVisManagerAppli.m module.

[Top]

### Step-by-Step

To redefine the `AnalyseNotification` method of the _CAAVisManagerCmdSelector_ class to catch the visualization notifications, there are nine main steps:

  1. Catching Notifications
  2. Catching CATPreactivate Notifications
  3. Catching CATEndPreactivate Notifications
  4. Catching CATActivate Notifications
  5. Catching CATEndActivate Notifications
  6. Catching CATMove Notifications
  7. Catching CATBeginManipulate, CATManipulate, and CATEndManipulate Notifications
  8. Catching CATContext Notifications
  9. Catching CATEndContext Notifications



[Top]

#### Catching Notifications
    
    
    CATNotifPropagationMode CAAVisManagerCmdSelector::**AnalyseNotification**(
                                                       CATCommand * iFromClient,
                                                       CATNotification * iNotification)
    {
      CATNotifPropagationMode propMode = **CATNotifTransmitToFather** ;
    
      if ( iNotification->IsAKindOf(**CATManipulatorNotification::ClassName**()) )
      {
        ...  // see coming steps
        propMode = **CATNotifDontTransmitToFather** ;
      }
      else  if ( iNotification->IsAKindOf(**CATMultiSel::ClassName**()) )
      {
        propMode = **CATNotifDontTransmitToFather** ;
        CATSO * pSetOfObjects = (CATSO *) iFromClient->**SendCommandSpecificObject**(
                                             CATPathElement::ClassName(), iNotification);
        if  (NULL != pSetOfObjects)
        {
          CATBaseUnknown *pComp = NULL;
          for (int ii=0; pComp=(*pSetOfObjects)[ii]; ii++)
          {
            _Hso.**AddElements**(pComp);
          }
          _Hso.**EndAddElements**();
        }
        pSetOfObjects->Release();
        pSetOfObjects = NULL;
      }
      return propMode;
    }  
  
---  
  
_CAAIVisManagerCmdSelector_ derives from the _CATCommand_ class and redefines the `AnalyseNotification` method. Any received notification is analyzed and, if the notification is an instance of a class that is, or derives from, _CATManipulatorNotification_ or _CATMultiSel_ notification classes, the notification is caught and processed, appropriate actions are undertaken, and the notification propagation is stopped because `AnalyseNotification` returns `CATNotifDontTransmitToFather`. Otherwise, the notification goes on up the command tree structure since `AnalyseNotification` returns `CATNotifTransmitToFather`. The case of _CATManipulatorNotification_ is detailed in the coming steps. Let see what's happen if a _CATMultiSel_ notification class instance is received.

In this case, a multiselection occurred. Several components are selected, and can be retrieved by calling the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector. `SendCommandSpecificObject` returns these components in a _CATSO_ instance, that is, a set of objects. Each component found in this set is added to the HSO to highlight it thanks to the `AddElements` method. The highlight takes place when the set of objects scan is completed thanks to the `EndAddElements` method.

[Top]

#### Catching CATPreactivate Notifications
    
    
        ...
        if  ( iNotification->IsAKindOf(CATManipulator::**GetCATPreactivate**()) )
        {
          CATPathElement * pPath =
           (CATPathElement *)iFromClient->**SendCommandSpecificObject**(
                                              CATPathElement::ClassName(),
                                              iNotification);
          if ( NULL != pPath )
          {
            _Pso.**AddElement**(pPath);
            pPath->Release();
          }
        }
        ...  
  
---  
  
A _CATPreactivate_ notification is sent whenever the mouse moves above a representation with no button pressed. In this case, the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector, retrieves the path element of the representation under the mouse, and if a valid path is retrieved, adds it to the PSO to prehighlight the associated representation.

[Top]

#### Catching CATEndPreactivate Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::GetCATEndPreactivate()) )
        {
          CATPathElement * pPath =
           (CATPathElement *)iFromClient->**SendCommandSpecificObject**(
                                              CATPathElement::ClassName(),
                                              iNotification);
          if ( NULL != pPath )
          {
            _Pso.**RemoveElement**(pPath);
            pPath->Release();
          }
        }
        ...  
  
---  
  
A _CATEndPreactivate_ notification is sent whenever the mouse leaves a representation with no button pressed. In this case, the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector, retrieves the path element of the representation leaved by the mouse, and if a valid path is retrieved, removes it from the PSO to dehighlight the associated representation.

[Top]

#### Catching CATActivate Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATActivate**()) )
        {
          CATPathElement * pPath =
           (CATPathElement *)iFromClient->**SendCommandSpecificObject**(
                                              CATPathElement::ClassName(),
                                              iNotification);
          _Hso.**Empty**();
    
          if ( NULL != pPath )
          {
            _Hso.**AddElement**(pPath);
            pPath->Release();
          }
          else
          {
            _Pso.**Empty**();
          }
        }
        ...  
  
---  
  
A _CATActivate_ notification is sent whenever the mouse left button is pressed above a representation. In this case, the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector, retrieves the path element of the representation under the mouse, empties the HSO to leave it for the newly activated representation, and if a valid path is retrieved, adds it to the HSO to highlight the associated representation. If no valid path is retrieved, the PSO is also emptied because it could contain the path element of the activated component, added when it was preactivated. This path could have become invalid between the preactivation and the activation.

[Top]

#### Catching CATEndActivate Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATEndActivate**()) )
        {
          CATPathElement * pPath =
           (CATPathElement *)iFromClient->**SendCommandSpecificObject**(
                                              CATPathElement::ClassName(),
                                              iNotification);
    
          if ( NULL != pPath )
          {
            _Hso.**RemoveElement**(pPath);
            pPath->Release();
          }
        }
        ...  
  
---  
  
A _CATEndActivate_ notification is sent whenever the mouse left button is pressed above another representation not controlled by the manipulator or above the background. In this case, the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector, retrieves the path element of the representation that was activated and removes it from the HSO.

[Top]

#### Catching CATMove Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATMove**()) )
        {
          _Pso.**Empty**();
          CATPathElement * pPath =
           (CATPathElement *)iFromClient->**SendCommandSpecificObject**(
                                              CATPathElement::ClassName(),
                                              iNotification);
          if ( NULL != pPath )
          {
            _Pso.**AddElement**(pPath);
            pPath->Release();
          }
        }
        ...  
  
---  
  
A _CATMove_ notification is sent whenever the mouse moves above a representation. In this case, the PSO is emptied, the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector, retrieves the path element of the representation above which the mouse moves, and adds it to the PSO to prehighlight the associated representation.

[Top]

#### Catching CATBeginManipulate, CATManipulate, and CATEndManipulate Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATBeginManipulate**()) )
        {}
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATManipulate**()) )
        {}
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATEndManipulate**()) )
        {}
        ...  
  
---  
  
A _CATBeginManipulate_ notification is sent whenever the mouse begins to move above an activated representation, that is with the mouse left button pressed. If the mouse goes on moving with the mouse left button pressed, _CATManipulate_ notifications are sent as long as the mouse moves. When the left button is released, A _CATEndManipulate_ notification is sent. These notifications are simply caught with no associated action.

[Top]

#### Catching CATContext Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATContext**()) )
        {
          CATPathElement *pPath = (CATPathElement *) 
            iFromClient->**SendCommandSpecificObject**(CATPathElement::ClassName(),iNotification);
          if (NULL != pPath) 
          {		
            CATBaseUnknown *lastobj_of_path = (*pPath)[pPath->GetSize()-1];
            if (NULL != lastobj_of_path)
            {
              CATViewer * pViewer = (CATViewer *) 
                     iFromClient->**SendCommandSpecificObject**(CATViewer::ClassName(),
                                                            iNotification);
              if ( NULL != pViewer)
              {
                _Pso.Empty();
                _Hso.Empty();
                _Hso.AddElement(pPath);
                _pCxtMenu = new CAAVisManagerCxtMenu(this, "Context", pPath, pViewer);
                _pCxtMenu->Build();
    
                pViewer->Release();
                pViewer = NULL ;
              }
            }
            else
            {
              propMode = **CATNotifTransmitToFather** ;
            }
            pPath->Release();
            pPath = NULL;
          }
        }
        ...  
  
---  
  
A _CATContext_ notification is sent whenever the mouse right button is pressed above a representation. In this case, the `SendCommandSpecificObject` method of the sending command, that is, the child _CATSelector_ instance associated with the current selector, retrieves the path element of the representation under the mouse. The viewer is also retrieved thanks to the `SendCommandSpecificObject` method. If a valid path and a valid viewer are retrieved, the PSO and the HSO are emptied, the retrieved path is added to the HSO to highlight the associated representation, and a contextual menu is created.

[Top]

#### Catching CATEndContext Notifications
    
    
        ...
        else if ( iNotification->IsAKindOf(CATManipulator::**GetCATEndContext**()) )
        {
          if ( NULL != _pCxtMenu )
          {
            _Hso.Empty();
            _pCxtMenu->RequestDelayedDestruction();
            _pCxtMenu = NULL ;
          }
        }
        ...  
  
---  
  
A _CATEndContext_ notification is sent whenever the mouse right button is released. In this case, the HSO is emptied and the contextual menu is deleted.

[Top]

* * *

### In Short

This use case shows how to catch the visualization notifications by redefining the `AnalyseNotification` method of _CATCommand_. Their types can be recognized thanks to the `IsAKindOf` method and appropriate actions can be undertaken.

[Top]

* * *

### References

[1] | [Conveying End User Intent from Mouse to Controller](../CAAVisTechArticles/CAAVisViewerProtocol.htm)  
---|---  
[2] | [Making a Component Displayable With CATI3DGeoVisu](CAAVisSampleCATIVisu.htm)  
[3] | [Using the Visualization Manager](CAAVisSampleVisManager.htm)  
[4] | [The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.htm)  
[5] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
[Top]  
  
* * *

### History

Version: **1** [May 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
