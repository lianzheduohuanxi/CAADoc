---
```vbscript
title: "The Send/Receive Mechanism"
category: "use case"
module: "CAADlgUseCases"
tags: ["CAADlgErrorNotification", "CAADlgViewScreen", "CAADlgElement", "CAADlgNotifError", "CAADlgAddNotification", "CAADlgNotifRemove", "CAADlgModel", "CATIA", "CAADlgNotifAdd", "CAADlgRemoveNotification", "CAADlgSendReceive", "CAADialog", "CAADlgContainer"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleSendReceive.htm"
converted: "2026-05-11T17:17:55.987209"
```

---
# 3D PLM Enterprise Architecture

|
## Middleware Abstraction

|
### The Send/Receive Mechanism

_Making commands collaborate_
---|---|---
Use Case

* * *
### Abstract

This article shows how to create and instantiate commands, and how notifications can be sent and received by commands.

  * **What You Will Learn With This Use Case**
  * **The CAADlgSendReceive Use Case**
    * What Does CAADlgSendReceive Do
    * How to Launch CAADlgSendReceive
    * Where to Find the CAADlgSendReceive Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how the Send/Receive mechanism [1] works and how to use it in your own applications.

[Top]
### The CAADlgSendReceive Case

CAADlgSendReceive is a use case of the CAADialog.edu framework that illustrates CATIA System and Dialog frameworks capabilities.

[Top]
#### What Does CAADlgSendReceive Do

CAADlgSendReceive is a use case of the CAADialog.edu framework that illustrates CATIA System and Dialog frameworks capabilities.
This use case creates commands that build a command tree structure, create and send notifications, analyze them, and process them or ask the sending command to resend the notification above in the tree, possibly up to the command selector that resends the notification to the active command. The commands that send notifications are made of a model that has elements, such as points, lines, and so on. This model has a container as parent, and the container has the command selector as parent. The possibly active commands are a screen view and a plot view of the model and of its elements.

Fig. 1: Command Diagram ![](images/CAADlgSendReceive.gif)

---

This use case creates commands that build a command tree structure, create and send notifications, analyze them, and process them or ask the sending command to resend the notification above in the tree, possibly up to the command selector that resends the notification to the active command. The commands that send notifications are made of a model that has elements, such as points, lines, and so on. This model has a container as parent, and the container has the command selector as parent. The possibly active commands are a screen view and a plot view of the model and of its elements.
Fig. 1: Command Diagram ![](images/CAADlgSendReceive.gif)
The screen and plot views are instantiated without parent. Their default parent is then the command selector. The container is also instantiated with the command selector as parent. The model is instantiated with the container as parent.

When an element is added to the model, the model notifies this event to its parent by sending a _CAADlgNotifAdd_ notification instance. When an element is removed from the model, it sends a _CAADlgNotifRemove_ notification instance. These two notifications are unknown by the container which is transparent for them. The container reacts only if the model sends a _CAADlgNotifError_ notification instance.

The notifications for which the container is transparent are resent by the model to the container's parent, that is the command selector. It is the higher object in the command tree structure and it receives all the unprocessed notifications. The command selector has no ability to process notifications, and it only resend the notification to the active command, that is, the command that has requested the focus, and that is the last chance for the notification to be processed. The screen view and the plot view are the two commands that may have the focus and that request it in turn.

[Top]
#### How to Launch CAADlgSendReceive

To launch CAADlgSendReceive, you will need to set up the build time environment, then compile CAADlgSendReceive along with its prerequisites, set up the run time environment, and then execute the use case [2].

[Top]
#### Where to Find the CAADlgSendReceive Code

To launch CAADlgSendReceive, you will need to set up the build time environment, then compile CAADlgSendReceive along with its prerequisites, set up the run time environment, and then execute the use case [2].
The CAADlgSendReceive use case is made of a several classes located in the CAADlgSendReceive.m module of the CAADialog.edu framework:

Windows | `InstallRootDirectory\CAADialog.edu\CAADlgSendReceive.m\`

The CAADlgSendReceive use case is made of a several classes located in the CAADlgSendReceive.m module of the CAADialog.edu framework:
Windows | `InstallRootDirectory\CAADialog.edu\CAADlgSendReceive.m\`
Unix | `InstallRootDirectory/CAADialog.edu/CAADlgSendReceive.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To create an event publisher, an event subscriber or listener, and a scenario to make them play together, there are four steps:
# | Step | Where
---|---|---
To create an event publisher, an event subscriber or listener, and a scenario to make them play together, there are four steps:
1 | Creating a Notification Class | _CAADlgNotifAdd_ class
2 | Sending a Notification | _CAADlgModel_ class
3 | Filtering Notifications | _CAADlgContainer_ class
4 | Taking the Focus | _CAADlgViewScreen_ class
5 | Making the Active Command React to Notifications | _CAADlgViewScreen_ class
6 | Returning the Added or Removed Object | _CAADlgModel_ class

[Top]
#### Creating a Notification Class

The _CAADlgAddNotification_ class is taken as example.

    #include "CATNotification.h"
    class CAADlgAddNotification: public **CATNotification**
    {
      **CATDeclareClass** ;
class CAADlgAddNotification: public **CATNotification**
      public:
        CAADlgAddNotification();
        virtual CAADlgAddNotification();
      private:
        CAADlgAddNotification(const CAADlgAddNotification&iObjectToCopy);
        CAADlgAddNotification & operator = (const CAADlgAddNotification &iObjectToCopy);

    };

---

A notification is a CAA V5 component. Its class C++-derives from the notification base class _CATNotification_. The `CATDeclareClass` macro makes _CAADlgAddNotification_ __ part of a component. The copy constructor and the assignment operator are set as private and are not implemented to prevent the compiler to create one as public, and thus prevent from illegal copies of the notification instances.

    #include "CAADlgAddNotification.h"

A notification is a CAA V5 component. Its class C++-derives from the notification base class _CATNotification_. The `CATDeclareClass` macro makes _CAADlgAddNotification_ __ part of a component. The copy constructor and the assignment operator are set as private and are not implemented to prevent the compiler to create one as public, and thus prevent from illegal copies of the notification instances.
    CATImplementClass(CAADlgAddNotification, **Implementation** , CATBaseUnknown,CATNull);

    CAADlgAddNotification::CAADlgAddNotification(): CATNotification(**CATNotificationDeleteOn**)

    {}
```vbscript
CATImplementClass(CAADlgAddNotification, **Implementation** , CATBaseUnknown,CATNull);
CAADlgAddNotification::CAADlgAddNotification(): CATNotification(**CATNotificationDeleteOn**)
    CAADlgAddNotification::CAADlgAddNotification()
```

    {}

---

CAADlgAddNotification::CAADlgAddNotification()
The `CATImplementClass` macro declares that _CAADlgAddNotification_ __ is an `Implementation`, that is, a component main class, that OM-derives from _CATBaseUnknown_. The last argument must always be set to `CATNull` if the second one is set to `Implementation`.

The _CAADlgAddNotification_ __ class constructor use `CATNotificationDeleteOn `as argument for the _CATNotification_ class constructor.` `It means that the notification will be automatically deleted by the system. [3]

[Top]
#### Sending a Notification

The model sends notifications whenever an element is added to it, or removed from it. Let's take the adding example.

The model sends notifications whenever an element is added to it, or removed from it. Let's take the adding example.
    void CAADlgModel::Add(CAADlgElement * iNewElement)

    {
The model sends notifications whenever an element is added to it, or removed from it. Let's take the adding example.
void CAADlgModel::Add(CAADlgElement * iNewElement)
```vbscript
      if ( NULL != iNewElement )

```

      {
        ... // The element is successfully added

```vbscript
if ( NULL != iNewElement )
         CAADlgAddNotification * pAddNotification = new CAADlgAddNotification();
```

         **SendNotification**(GetFather(), pAddNotification);
CAADlgAddNotification * pAddNotification = new CAADlgAddNotification();
         pAddNotification = NULL;

      }
CAADlgAddNotification * pAddNotification = new CAADlgAddNotification();
pAddNotification = NULL;
      else

      {
pAddNotification = NULL;
else
         CAADlgErrorNotification * pErrorNotification = new CAADlgErrorNotification();

         **SendNotification**(GetFather(), pErrorNotification);
else
CAADlgErrorNotification * pErrorNotification = new CAADlgErrorNotification();
         pErrorNotification = NULL;

      }
    }

---

When an element is successfully added, a _CAADlgAddNotification_ class instance is sent to the command parent thanks to the `SendNotification` method. The command parent is retrieved using the `GetFather` method of _CATCommand_. Otherwise, an error notification is sent. This is an instance of the _CAADlgErrorNotification_ class. Each instance is deleted as soon as it is sent, and its pointer is set to `NULL`.

[Top]
#### Filtering Notifications

    CATNotifPropagationMode CAADlgContainer::**AnalyseNotification**(CATCommand      *iSending,
CATNotifPropagationMode CAADlgContainer::**AnalyseNotification**(CATCommand      *iSending,
                                                                 CATNotification *iReceive)

    {
CATNotifPropagationMode CAADlgContainer::**AnalyseNotification**(CATCommand      *iSending,
CATNotification *iReceive)
```vbscript
      if (iReceive->IsAKindOf("CAADlgNotifError"))

```

      {
CATNotifPropagationMode CAADlgContainer::**AnalyseNotification**(CATCommand      *iSending,
CATNotification *iReceive)
if (iReceive->IsAKindOf("CAADlgNotifError"))
```vbscript
          printf("The Command Container catches an error \n");
          return(**CATNotifDontTransmitToFather**);

```

      }
```vbscript
if (iReceive->IsAKindOf("CAADlgNotifError"))
```vbscript
printf("The Command Container catches an error \n");
return(**CATNotifDontTransmitToFather**);
```

      else
```

      {
```vbscript
printf("The Command Container catches an error \n");
```vbscript
return(**CATNotifDontTransmitToFather**);
```

else
        return(**CATNotifTransmitToFather**);
```

      };
    }

---

The container traps only the notifications that are instances of _CAADlgNotifError_ thanks to redefining the `AnalyseNotification` method of _CATCommand_. To do this, it simply returns `CATNotifDontTransmitToFather`, that stops the notification propagation above in the command tree structure. It processes the notification by simply printing out an error message. All other notifications are of no interest for the container, and returning `CATNotifTransmitToFather` requests the sending command to resend the notification to the container parent, namely the command selector.

[Top]
#### Taking the Focus

The screen view command is taken as an example.

The screen view command is taken as an example.
    void CAADlgViewScreen::WantedFocus()

    {
The screen view command is taken as an example.
void CAADlgViewScreen::WantedFocus()
      RequestStatusChange(CATCommandMsgRequestSharedMode);

    }

---

The `WantedFocus` method requests that the _CAADlgViewScreen_ instance be set as the active command using the `RequestStatusChange` method. `CATCommandMsgRequestSharedMode` means that the command runs in shared mode, that is it pushes on the command stack the previous active command without deleting it. This previous command will then take the focus again when the _CAADlgViewScreen_ instance will be deleted.

[Top]
#### Making the Active Command React to Notifications

The active command also redefines the `AnalyseNotification` method. Here is the one of the screen view class.

The active command also redefines the `AnalyseNotification` method. Here is the one of the screen view class.
    CATNotifPropagationMode CAADlgViewScreen::**AnalyseNotification**(CATCommand      *iSending,
                                                                  CATNotification *iReceive)

    {
CATNotifPropagationMode CAADlgViewScreen::**AnalyseNotification**(CATCommand      *iSending,
CATNotification *iReceive)
      if ( iReceive->IsAKindOf("CAADlgAddNotification") ||
           iReceive->IsAKindOf("CAADlgRemoveNotification") )

      {
CATNotification *iReceive)
if ( iReceive->IsAKindOf("CAADlgAddNotification") ||
iReceive->IsAKindOf("CAADlgRemoveNotification") )
        CAADlgElement *pElement= NULL;
```vbscript
        pElement = (CAADlgElement *)iSending->**SendObject**(CAADlgElement::ClassName(), iReceive);

        if ( NULL != pElement)

```

        {
CAADlgElement *pElement= NULL;
pElement = (CAADlgElement *)iSending->**SendObject**(CAADlgElement::ClassName(), iReceive);
```vbscript
if ( NULL != pElement)
```

          pElement->Release();
          pElement = NULL ;
          return(CATNotifDontTransmitToFather);

          }
pElement->Release();
pElement = NULL ;
return(CATNotifDontTransmitToFather);
        else
          return(CATNotifTransmitToFather);

      }
```vbscript
return(CATNotifDontTransmitToFather);
else
return(CATNotifTransmitToFather);
      else
        return(CATNotifTransmitToFather);
```

    }

---

```vbscript
If the notification is of one of the expected types, the `SendObject` method is called to request the object that sends the notification to provide a pointer to the object that was either added or removed. `SendObject` calls the `SendCommandSpecificObject` that must be redefined by the sending command.

```

[Top]
#### Returning the Added or Removed Object

Any command that sends notifications to state a model change can be asked to send a pointer to the object that changes the model. This is the role of `SendCommandSpecificObject`.

Any command that sends notifications to state a model change can be asked to send a pointer to the object that changes the model. This is the role of `SendCommandSpecificObject`.
    void *CAADlgModel::**SendCommandSpecificObject**(const char      *iObjectClassNeeded,
                                                 CATNotification *iReceived)

    {
void *CAADlgModel::**SendCommandSpecificObject**(const char      *iObjectClassNeeded,
CATNotification *iReceived)
      void * pObjectToReturn = NULL;

      if ( iReceived->IsAKindOf("CAADlgAddNotification") ||
           iReceived->IsAKindOf("CAADlgRemoveNotification") )

      {
void * pObjectToReturn = NULL;
if ( iReceived->IsAKindOf("CAADlgAddNotification") ||
iReceived->IsAKindOf("CAADlgRemoveNotification") )
```vbscript
        if ( _pTheLastElementManipulated->IsAKindOf(iObjectClassNeeded) )

```

        {
```vbscript
if ( iReceived->IsAKindOf("CAADlgAddNotification") ||
iReceived->IsAKindOf("CAADlgRemoveNotification") )
if ( _pTheLastElementManipulated->IsAKindOf(iObjectClassNeeded) )
          pObjectToReturn = _pTheLastElementManipulated;
          pObjectToReturn->AddRef();
```

        }
      }
pObjectToReturn = _pTheLastElementManipulated;
pObjectToReturn->AddRef();
      return pObjectToReturn ;

    }

---

`SendCommandSpecificObject` is called using a class name and the pointer to the notification received. After testing if the notification is one of those that are sent by the model, a pointer to the last object manipulated, that is the last added or removed object, is returned. Otherwise `NULL` is returned.

`SendCommandSpecificObject` addrefs the sent object, and after a `SendObject` call the method releases the pointer.

[Top]

* * *
### In Short

The Send/Receive communication protocol enables commands to communicate using notifications that progress from one command to its parent in the command tree structure. A command can send notifications, and can analyze notifications to decide whether to be transparent for, or to receive them, depending on their types. If a notification reaches the command selector at the top of the command tree structure, it is sent to the active command, that is, the one that has the focus. This command in turn analyzes the notification, and can ask the sending command to send the model object for which the notification was sent.

[Top]

* * *
### References

[1] | [The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [Callback versus Send/Receive Mechanism](../CAASysTechArticles/CAASysCallbackversusSendReceive.md)
[Top]

* * *
### History

Version: **1** [May 2000] | Document created
---|---
Version: **2** [Feb 2004] | Document updated
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
