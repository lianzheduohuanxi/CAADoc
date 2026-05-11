---
title: "Sending a Data Message to an Interactive Application"
category: "use case"
module: "CAADlgUseCases"
tags: ["CAADlgBBSender", "CAAIDlgDataRequest", "CATICommunicator", "CAADlgBBMessage", "CATIMessageReceiver", "CAADlgBBMessageNotification", "CATICommMsg", "CAADlgBBMessageManager", "CAADlgBBEditorMessageHandler", "CAADlgBBEditorMessage", "CATImplementClass", "CAADlgBBReceiver", "CAADlgBBReceiverWindow", "CAADlgBBSenderWindow", "CAASystem", "CATInstantiateComponent", "CATInteractiveApplication", "CAADlgBBMessageInt", "CAADialog"]
source_file: "Doc\online\CAADlgUseCases\CAADlgSampleBBMsg.htm"
converted: "2026-05-11T17:17:55.971235"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Dialogs

| 

### Sending a Data Message to an Interactive Application

_Using the backbone to send a message with data_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to make two interactive applications communicate, and how one of them can send a data message that conveys a text, and how the other can receive the message. 

  * **What You Will Learn With This Use Case**
  * **The CAADlgBBSender and CAADlgBBReceiver Use Cases**
    * What Do CAADlgBBSender and CAADlgBBReceiver Do
    * How to Launch CAADlgBBSender and CAADlgBBReceiver
    * Where to Find the CAADlgBBSender and CAADlgBBReceiver Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

### What You Will Learn With This Use Case

This use case is intended to show you how an interactive application can declare that it will send or receive messages, how to filter the messages to receive, and how to send and receive messages using the backbone objects of the System framework. The message taken as an example conveys a text.

[Top]

### The CAADlgBBSender and CAADlgBBReceiver Use Cases

CAADlgBBSender and CAADlgBBReceiver are use cases of the CAADialog.edu framework that illustrates the Dialog and System frameworks capabilities.

[Top]

#### What Do CAADlgBBSender and CAADlgBBReceiver Do

This use case illustrates two interactive applications. One behaves as a message sender, and the other as a message receiver. The message is a data message that conveys a text. The message sender displays an entry field in which the end user types the message text and clicks the Send button to send the message. The message receiver displays a field in which the text of the received message is printed.

![](images/CAADlgBBSender.jpg) | ![](images/CAADlgBBReceiver.jpg)  
---|---  
  
Both the message sender and the message receiver are interactive applications launched by instantiating a class that derives from _CATInteractiveApplication_. To send the message, the message sender connects to the backbone bus, declares itself, instantiates the message component using the text entered in the text field of its window, and sends it.

The message receiver needs to instantiate a message handler to receive the message. Such a message handler is a component that implements the _CATIMessageReceiver_ interface. In addition, the message receiver subscribes to a notification that the message handler will request a message manager to dispatch along with the message text. To receive the message, the message receiver connects to the backbone bus, declares itself, declares the message to receive, instantiates the message handler, associates itself with the message to receive and with the message handler. As soon as the message is sent, it is retrieved by the message handler that requests the message manager to dispatch a notification that carries the message text, and to which the message receiver has subscribed. The message receiver called back method extract the message text from the notification and prints it in the window text field.

Compared to batch applications that intend to receive messages [1] [2], there is no need to create and enter a waiting loop, since the interactive application includes one already. The message conveys data [5] made of a text. It is not described.

[Top]

#### How to Launch CAADlgBBSender and CAADlgBBReceiver

To launch CAADlgBBSender and CAADlgBBReceiver, you will need to set up the build time environment, then compile CAADlgBBSender and CAADlgBBReceiver along with its prerequisites, set up the run time environment [3] in two different windows, and then execute the use case.

To execute the use case: 

  * With Windows, successively type in the DOS window command line the two module names: 
        
        CAADlgBBSender
        CAADlgBBReceiver

  * With UNIX, successively type in the shell window command line the two module names with "&" to launch them in background mode: 
        
        CAADlgBBSender &
        CAADlgBBReceiver &




Type a text in the Backbone Sender window text field, and click Send. The text is printed in the Backbone Receiver window text field.

[Top]

#### Where to Find the CAADlgBBSender and CAADlgBBReceiver Code

The CAADlgBBSender and CAADlgBBReceiver use case are made of several classes located in the CAADlgBBSender.m and CAADlgBBReceiver.m module of the CAADialog.edu framework:

Windows | `InstallRootDirectory\CAADialog.edu\CAADlgBBSender.m\  
InstallRootDirectory\CAADialog.edu\CAADlgBBReceiver.m\`  
---|---  
Unix | `InstallRootDirectory/CAADialog.edu/CAADlgBBSender.m/  
InstallRootDirectory/CAADialog.edu/CAADlgBBReceiver.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

The message component is made of several classes located in the CAADlgBBMessage.m module of the CAADialog.edu framework, and in addition implements the CAAIDlgDataRequest interface located in the PrivateInterfaces directory and in the CAADlgBBMessageInt.m module of the CAADialog.edu framework. They are not described in this article. Refer to the messages described in the CAASystem.edu framework [4] [5].

[Top]

### Step-by-Step

To create interactive applications that send and receive a data message, there are seven main steps:

  1. Creating the Message Sender
  2. Sending the Message
  3. Creating the Message Handler
  4. Creating the Message Manager
  5. Creating the Message Receiver
  6. Receiving the Message
  7. Removing the Message Handler



[Top]

#### Creating the Message Sender

The message sender is an interactive application whose class is _CAADlgBBSender_. Its main method is `BeginApplication` where the application window is instantiated. The window class is _CAADlgBBSenderWindow_ whose `Build` method connects to the backbone bus by calling its `BackboneInit` method before creating the controls and setting a callback to react when the Send button is clicked. Below is the `BackboneInit `method
    
    
    ...
    HRESULT CAADlgBBSenderWindow::BackboneInit()
    {
      HRESULT  rc = E_FAIL;
      // Retrieves an instance of a backbone bus (default bus)
      _pICommunicator = ::**CATGetBackboneConnection**();
      if ( NULL != _pICommunicator )
      {
         CATApplicationClass ApplicationSenderId = "CAADlgBBSender";
         rc =_pICommunicator->**Declare**(ApplicationSenderId);
         ... //Process failing declaration
      }
      return rc;
    }
    ...  
  
---  
  
First, a connection to the backbone bus must be established. This is possible thanks to the global function `CATGetBackboneConnection` that returns a pointer to the _CATICommunicator_ interface stored in the `_pICommunicator` data member. Then, the message sender creates its application class identifier and declares it to the backbone bus using the method `Declare`.

[Top]

#### Sending the Message

The message is sent by the callback set to the push button activation.
    
    
    ...
    void CAADlgBBSenderWindow::PushSend(CATCommand         * iSendingCommand, 
                                        CATNotification    * iSentNotification, 
                                        CATCommandClientData iUsefulData)
    {
      CATUnicodeString Line;
      _pEditor->**GetLine**(Line);
      CAAIDlgDataRequest * pIDataRequest = NULL;
      HRESULT rc = ::**CATInstantiateComponent**("CAADlgBBEditorMessage",
                                             IID_CAAIDlgDataRequest,
                                             (void **)&pIDataRequest);
      if ( SUCCEEDED(rc) )
      {
        pIDataRequest->**SetData**(Line.CastToCharPtr());
    
        CATICommMsg * pICommMsg =NULL;
        rc = pIDataRequest->QueryInterface(**IID_CATICommMsg** ,(void**)&pICommMsg);
                                                     
        if ( SUCCEEDED(rcb) )
        {
          CATApplicationClass ReceiverApplicationId = "CAADlgBBReceiver";
          rc = _pICommunicator->**SendRequest**(ReceiverApplicationId, pICommMsg);
          pICommMsg->Release();
          pICommMsg = NULL;
        }
        pIDataRequest->Release();
        pIDataRequest = NULL;
      }
    }
    ...  
  
---  
  
When you click Send, this method is called, and the message sender can send the message. It first retrieves the text entered in the text field, a _CATDlgEditor_ instance, thanks to the `GetLine` method. Then it instantiates the message component _CAADlgBBEditorMessage_ using the `CATInstantiateComponent` global function, which returns a pointer to _CAAIDlgDataRequest_ interface. This interface is created for this message to enable it to set and get its data, that is, the message text. The message text is passed to the message component thanks to the `SetData` method of _CAAIDlgDataRequest_ , and then the message is sent using the `SendRequest` method of _CATICommunicator_ , specifying the target message receiver identifier and the message to send as a pointer to _CATICommMsg_. This message receiver identifier must be the same than the one declared by the message receiver itself in its own `BackboneInit` method.

[Top]

#### Creating the Message Handler
    
    
    #include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown
    
    class CATICommMsg;
    
    class  CAADlgBBEditorMessageHandler : public CATBaseUnknown
    {
       CATDeclareClass;
       public:
          CAADlgBBEditorMessageHandler();
          virtual ~CAADlgBBEditorMessageHandler();
    
          // CATIMessageReceiver Interface
          void HandleMessage(CATICommMsg * iMessage);
    
      private:
          CAADlgBBEditorMessageHandler(const CAADlgBBEditorMessageHandler &iObjectToCopy);
    };  
  
---  
  
The _CAADlgBBEditorMessageHandler_ class belongs to a component, thanks to the `CATDeclareClass` macro, C++ derives from _CATBaseUnknown_ , and implements _CATIMessageReceiver_ , whose single method is `HandleMessage`. Note that the copy constructor is set as private, and is not implemented in the source file. This prevents the compiler from creating the copy constructor as public without you know.
    
    
    #include "CAADlgBBEditorMessageHandler.h"
    #include <CATErrorDef.h> // for the SUCCEEDED macro 
    #include "CAAIDlgDataRequest.h"
    #include "CAADlgBBMessageManager.h"
    
    #include "TIE_CATIMessageReceiver.h"
    **TIE_CATIMessageReceiver(CAADlgBBEditorMessageHandler);**
    
    **CATImplementClass(CAADlgBBEditorMessageHandler,
                      Implementation,
                      CATBaseUnknown,
                      CATNull);**
    CAADlgBBEditorMessageHandler::CAADlgBBEditorMessageHandler(){}
    
    CAADlgBBEditorMessageHandler::~CAADlgBBEditorMessageHandler(){}
    
    void CAADlgBBEditorMessageHandler::**HandleMessage**(CATICommMsg* iMessage)
    {
      if ( NULL != iMessage )
      {
        CAAIDlgDataRequest * pIRequest = NULL;
        HRESULT rcb = iMessage->QueryInterface(IID_CAAIDlgDataRequest,(void**) &pIRequest);
        if ( SUCCEEDED(rcb) )
        {
           char * Text = NULL;
           pIRequest->GetData(&Text);
           pIRequest->Release();
           pIRequest= NULL;
    
           CAADlgBBMessageManager * pManager = CAADlgBBMessageManager::**GetManager**();
           pManager->**EventToDispatch**(Text);
            
           delete [] Text;
           Text = NULL;
    
           pManager->Release();
           pManager= NULL;
        }
      } 
    }  
  
---  
  
The _CAADlgBBEditorMessageHandler_ class states that it implements the _CATIMessageReceiver_ interface thanks to the `TIE_CATIMessageReceiver` macro. The `CATImplementClass` macro declares that the _CAADlgBBEditorMessageHandler_ class is a component main class thanks the `Implementation` keyword, and that the component OM-derives [6] from _CATBaseUnknown_. Any component main class declared as an `Implementation` must C++-derive and OM-derive from the same class. The _CATIMessageReceiver_ interface `HandleMessage` method is called by the backbone bus and a pointer to the message is passed. A pointer to _CAAIDlgDataRequest_ is retrieved from the message to get the message text. Then, the message manager of the message receiver application is retrieved. The message text is passed to the message manager thanks to the `EventToDispatch` method.

The framework interface dictionary is updated to declare that _CAADlgBBEditorMessageHandler_ implements the _CATIMessageReceiver_   interface in the libCAADlgBBReceiver shared library or DLL. This interface dictionary is a file located in the CNext\code\dictionary directory, and is named CAADialog.edu.dico. There is one and only one interface dictionary per framework, named using the framework name suffixed by dico.
    
    
    ...
    CAADlgBBEditorMessageHandler CATIMessageReceiver  libCAADlgBBReceiver
    ...  
  
---  
  
[Top]

#### Creating the Message Manager

The message manager is a component that dispatches a notification that carries the message text.
    
    
    #include <CAADlgBBMessageManager.h>
    #include <CAADlgBBMessageNotification.h>
    #include "CATCallbackManager.h"
    
    CATImplementClass(CAADlgBBMessageManager,Implementation,CATBaseUnknown,CATNull);
    
    CAADlgBBMessageManager * CAADlgBBMessageManager::_Manager = NULL;
    
    CAADlgBBMessageManager::CAADlgBBMessageManager()
    {}
    
    CAADlgBBMessageManager::~CAADlgBBMessageManager()
    {}
    
    void CAADlgBBMessageManager::**EventToDispatch**(char * iText)
    {
      CATCallbackManager * pCBManager = ::**GetDefaultCallbackManager**(this);
      if ( NULL != pCBManager )
      {
         CAADlgBBMessageNotification * pNotification = new CAADlgBBMessageNotification(iText);
    
         pCBManager->**DispatchCallbacks**(pNotification, this);
    
         pNotification->Release();
         pNotification = NULL;
      }	
    }
    
    CAADlgBBMessageManager * CAADlgBBMessageManager::**GetManager**()
    {
      if ( NULL == _Manager )
      {
        _Manager = new CAADlgBBMessageManager();
      }
      _Manager->AddRef();
      return _Manager;
    }
    ...  
  
---  
  
The message manager is created as a component and is unique. It is instantiated by the `GetManager` static method. The `EventToDispatch` method retrieves the default callback manager associated with any component, instantiates a _CAADlgBBMessageNotification_ class that takes the message text as a data member, and request the default callback manager to dispatch this notification, to which the message receiver application will subscribe.

[Top]

#### Creating the Message Receiver

The message receiver is an interactive application. It has a window, instance of the class _CAADlgBBReceiverWindow_ , that carries out the main tasks of connecting to the backbone bus and receiving the message. Below is the `Build` method of  _CAADlgBBReceiverWindow._
    
    
    void CAADlgBBReceiverWindow::**Build**()
    {
      HRESULT Init = **BackboneInit**();
    
      if ( SUCCEEDED(Init) )
      {
         CATDlgFrame  * pFrame  = new CATDlgFrame(this, "FrameId", CATDlgFraNoFrame | CATDlgGridLayout );
      
         CATDlgLabel  * pLabel  = new CATDlgLabel (pFrame,"LabelEditorId");
         pLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
    
         _pEditor = new CATDlgEditor(pFrame,"EditorId",CATDlgEdtReadOnly);
         _pEditor->SetGridConstraints(0,1,1,1,CATGRID_LEFT); 
      
         _pMessageManager = CAADlgBBMessageManager::**GetManager**();
         ::**AddCallback**(this,
                       _pMessageManager,
                       "CAADlgBBMessageNotification",
                       (CATSubscriberMethod)&CAADlgBBReceiverWindow::ModifyEditor,
                       NULL);
      }
      AddAnalyseNotificationCB(this,
                               GetWindCloseNotification(),
                               (CATCommandMethod)&CAADlgBBReceiverWindow::Exit, NULL);
    }
    ...  
  
---  
  
The `Build` method first call the `BackboneInit` method, and if this method succeeds, creates the controls. Then it retrieves the message manager thanks to the static method `GetManager` of _CAADlgBBMessageManager_ , and sets a callback, that is, subscribes to an event, using the `AddCallback` global function whose arguments are:

`this` | The event subscriber, that is, the message receiver application window  
---|---  
`_pMessageManager` | The event publisher, which is here the message manager  
`CAADlgBBMessageNotification` | The event to subscribe. It is the class name of the notification that is sent by the message manager  
`(CATSubscriberMethod)&CAADlgBBReceiverWindow::ModifyEditor` | The method to call back when such a notification is received  
`NULL` | Possible useful data that could be sent with the notification  
  
The `BackboneInit` method is as follows.
    
    
    HRESULT CAADlgBBReceiverWindow::**BackboneInit**()
    {
      HRESULT rc = E_FAIL;
      _pICommunicator = ::**CATGetBackboneConnection**();
      if ( NULL == _pICommunicator )
          ... // Process failure
      else
      {
        CATApplicationClass ReceiverApplicationId = "CAADlgBBReceiver";
        rc= _pICommunicator->**Declare**( ReceiverApplicationId );
        if ( FAILED(rc) )
          ... // Process failure
        else
        {
          CATMessageClass MessageClassName = "CAADlgBBEditorMessage"; 
          CAADlgBBEditorMessageHandler * pHandlerForMessage = NULL;
          pHandlerForMessage = new **CAADlgBBEditorMessageHandler**();
    
          if ( NULL != pHandlerForMessage )
          {
            rc = pHandlerForMessage->QueryInterface(**IID_CATIMessageReceiver** ,
                                                    (void**)& _pIMessageReceiver);
            if ( SUCCEEDED(rc) )
            {
              rc = _pICommunicator->**AssociateHandler**(ReceiverApplicationId, 
                                                     MessageClassName,
                                                     _pIMessageReceiver);
              ... // Process failure
            }
            pHandlerForMessage->Release();
            pHandlerForMessage = NULL;
          }
        }
      }
      return rc;
    }
    ...  
  
---  
  
First, a connection to the backbone bus must be established. This is possible thanks to the global function `CATGetBackboneConnection` that returns a pointer to the _CATICommunicator_ interface. Once the connection is established, the message receiver sets its application identifier and declares it to the backbone bus using the method `Declare`. Note that this identifier is used by the message sender when sending the message using the `SendRequest` method. Then the message receiver instantiates the message handler, asks the message handler for a pointer to _CATIMessageReceiver_ , and declares to the backbone bus that it will receive the declared messages using the designated handler, thanks to the `AssociateHandler` method.

[Top]

#### Receiving the Message

The message is received thanks to the message handler that retrieves the message manager, and requests it to dispatch a notification that carries the message text. The message receiver has subscribed to this notification, and the callback method designated is then called. This method is the `ModifyEditor` method below.
    
    
    ...
    void CAADlgBBReceiverWindow::ModifyEditor(CATCallbackEvent  ievent,
                                              void             *ipublisher,
                                              CATNotification  *iNotification,
                                              CATSubscriberData iData,
                                              CATCallback       iCallback)
    {
       char * Text = NULL;
       CAADlgBBMessageNotification * iNotif = (CAADlgBBMessageNotification*) iNotification;
    
       iNotif->GetText(&Text);
       _pEditor->SetLine(Text);
    
       delete [] Text;
    }
    ...  
  
---  
  
`ModifyEditor` retrieves the message text from the notification, and assigns it to the editor thanks to the `SetLine` method.

[Top]

#### Removing the Message Handler

The message handler should be removed when no messages are to be received any longer. This is done here in the message receiver application window destructor.
    
    
    ...
    CAADlgBBReceiverWindow::~CAADlgBBReceiverWindow()
    { 
      _pApplication = NULL;
      _pEditor = NULL;
    
      if ( NULL !=  _pICommunicator )
      {
        if ( NULL != _pIMessageReceiver )
        {
          CATMessageClass MessageClassName = "CAADlgBBEditorMessage"; 
          _pICommunicator->**RemoveHandler**("CAADlgBBReceiver",
                                         MessageClassName,
                                         _pIMessageReceiver);
          _pIMessageReceiver->Release();
          _pIMessageReceiver = NULL;
        }
        _pICommunicator->Release();
        _pICommunicator = NULL;
      }
      if ( NULL != _pMessageManager )
      {
        _pMessageManager->Destroy();      
        _pMessageManager = NULL;
      }
    }
    ...  
  
---  
  
The data members are released and nullified. The message handler is removed thanks to the `RemoveHandler` method of _CATICommunicator_. Its arguments are:

`CAADlgBBReceiver` | The message receiver identifier  
---|---  
`MessageClassName` | The message class name to which the message handler is dedicated  
`_pIMessageReceiver` | The message handler  
  
[Top]

* * *

### In Short

This use case shows how to create interactive applications that send and receive backbone messages. The receiving application identifier must be known by the message sender.

[Top]

* * *

### References

[1] | [Sending a Backbone Simple Message to an Application](../CAASysUseCases/CAASysSampleBBSendRecSimpleMsg.htm)  
---|---  
[2] | [Sending a Backbone Data Message to an Application](../CAASysUseCases/CAASysSampleBBSendRecDataMsg.htm)  
[3] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
[4] | [Creating a Backbone Simple Message](../CAASysUseCases/CAASysSampleBBSimpleMsg.htm)  
[5] | [Creating a Backbone Data Message](../CAASysUseCases/CAASysSampleBBDataMsg.htm)  
[6] | [Object Modeler Component and Implementation Inheritances](../CAASysTechArticles/CAASysOMInheritance.htm)  
[Top]  
  
* * *

### History

Version: **1** [Jul 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
