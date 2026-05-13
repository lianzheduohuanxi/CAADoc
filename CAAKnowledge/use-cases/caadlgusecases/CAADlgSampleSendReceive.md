---
title: "Untitled"
category: "use-case"
module: "CAADlgUseCases"
tags: ["CATIA", "CAADlgAddNotification", "CAASysTechArticles", "CAADocStyleSheets", "CAADlgNotifRemove", "CAADlgContainer", "CAADialog", "CAADlgRemoveNotification", "CAADlgErrorNotification", "CAADocUseCases", "CAADlgModel", "CAADlgNotifAdd", "CATImplementClass", "CAASysSendReceive", "CAADlgNotifError", "CAASysCallbackversusSendReceive", "CAADlgViewScreen", "CAADlgSendReceive", "CAADocRunSample", "CAADlgElement"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleSendReceive.htmmd"
converted: "2026-05-11T11:27:02.790993"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to show you how the Send/Receive mechanism [1]
works and how to use it in your own applications.

[Top]

### The CAADlgSendReceive Case

CAADlgSendReceive is a use case of the CAADialog.edu framework that
illustrates CATIA System and Dialog frameworks capabilities.

[Top]

#### What Does CAADlgSendReceive Do

This use case creates commands that build a command tree structure, create
and send notifications, analyze them, and process them or ask the sending
command to resend the notification above in the tree, possibly up to the command
selector that resends the notification to the active command. The commands that
send notifications are made of a model that has elements, such as points, lines,
and so on. This model has a container as parent, and the container has the
command selector as parent. The possibly active commands are a screen view and a
plot view of the model and of its elements.

The screen and plot views are instantiated without parent. Their default
parent is then the command selector. The container is also instantiated with the
command selector as parent. The model is instantiated with the container as
parent.

When an element is added to the model, the model notifies this event to its
parent by sending a *CAADlgNotifAdd* notification instance. When an element
is removed from the model, it sends a *CAADlgNotifRemove* notification
instance. These two notifications are unknown by the container which is
transparent for them. The container reacts only if the model sends a *CAADlgNotifError*
notification instance.

The notifications for which the container is transparent are resent by the
model to the container's parent, that is the command selector. It is the higher
object in the command tree structure and it receives all the unprocessed
notifications. The command selector has no ability to process notifications, and
it only resend the notification to the active command, that is, the command that
has requested the focus, and that is the last chance for the notification to be
processed. The screen view and the plot view are the two commands that may have
the focus and that request it in turn.

[Top]

#### How to Launch CAADlgSendReceive

To launch CAADlgSendReceive, you will need to set up the build time
environment, then compile CAADlgSendReceive along with its prerequisites, set up
the run time environment, and then execute the use case [2].

[Top]

#### Where to Find the CAADlgSendReceive Code

The CAADlgSendReceive use case is made of a several classes located in the
CAADlgSendReceive.m module of the CAADialog.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

[Top]

### Step-by-Step

To create an event publisher, an event subscriber or listener, and a scenario
to make them play together, there are four steps:

[Top]

#### Creating a Notification Class

The *CAADlgAddNotification* class is taken as example.

A notification is a CAA V5 component. Its class C++-derives from the
notification base class *CATNotification*. The `CATDeclareClass`
macro makes *CAADlgAddNotification** *part of a component. The copy constructor
and the assignment operator are set as private and are not implemented to prevent the compiler to create one as
public, and thus prevent from illegal copies of the notification instances.

The `CATImplementClass` macro declares that *CAADlgAddNotification**
*
is an `Implementation`, that is, a component main class, that
OM-derives from *CATBaseUnknown*. The last argument must always be set to `CATNull`
if the second one is set to `Implementation`.

The *CAADlgAddNotification** *class constructor use `CATNotificationDeleteOn
`as argument for the *CATNotification* class constructor.` `It
means that the notification will be automatically deleted by the system. [3] 

[Top]

#### Sending a Notification

The model sends notifications whenever an element is added to it, or removed
from it. Let's take the adding example.

When an element is successfully added, a *CAADlgAddNotification* class
instance is sent
to the command parent thanks to the `SendNotification` method. The
command parent is retrieved using the `GetFather` method of *CATCommand*.
Otherwise, an error notification is sent. This is an instance of the *CAADlgErrorNotification*
class. Each instance is deleted as soon as it is sent, and its pointer is set to
`NULL`.

[Top]

#### Filtering Notifications

The container traps only the notifications that are instances of *CAADlgNotifError*
thanks to redefining the `AnalyseNotification` method of *CATCommand*.
To do this, it simply returns `CATNotifDontTransmitToFather`, that
stops the notification propagation above in the command tree structure. It
processes the notification by simply printing out an error message. All other
notifications are of no interest for the container, and returning `CATNotifTransmitToFather`
requests the sending command to resend the notification to the container parent,
namely the command selector.

[Top]

#### Taking the Focus

The screen view command is taken as an example.

The `WantedFocus` method requests that the *CAADlgViewScreen*
instance be set as the active command using the `RequestStatusChange`
method. `CATCommandMsgRequestSharedMode` means that the command runs
in shared mode, that is it pushes on the command stack the previous active
command without deleting it. This previous command will then take the focus
again when the *CAADlgViewScreen* instance will be deleted.

[Top]

#### Making the Active Command React to Notifications

The active command also redefines the `AnalyseNotification`
method. Here is the one of the screen view class.

If the notification is of one of the expected types, the `SendObject`
method is called to request the object that sends the notification to provide a
pointer to the object that was either added or removed. `SendObject`
calls the `SendCommandSpecificObject` that must be redefined by the
sending command.

[Top]

#### Returning the Added or Removed Object

Any command that sends notifications to state a model change can be asked to
send a pointer to the object that changes the model. This is the role of `SendCommandSpecificObject`.

`SendCommandSpecificObject` is called using a class name and the
pointer to the notification received. After testing if the notification is one
of those that are sent by the model, a pointer to the last object manipulated,
that is the last added or removed object, is returned. Otherwise `NULL`
is returned.

`SendCommandSpecificObject`  addrefs the sent object, and after a `SendObject`
 call the method releases the pointer.

[Top]

---

### In Short

The Send/Receive communication protocol enables commands to communicate using
notifications that progress from one command to its parent in the command tree
structure. A command can send notifications, and can analyze notifications to
decide whether to be transparent for, or to receive them, depending on their
types. If a notification reaches the command selector at the top of the command
tree structure, it is sent to the active command, that is, the one that has the
focus. This command in turn analyzes the notification, and can ask the sending
command to send the model object for which the notification was sent.

[Top]

---

### References

---

### History

---

*Copyright  2000, Dassault Systmes. All rights reserved.*

```vbscript
#include &quot;CATNotification.h&quot;
class CAADlgAddNotification: public CATNotification
{
  CATDeclareClass;
  public:
    CAADlgAddNotification(#);
    virtual CAADlgAddNotification(#);
  private:
    CAADlgAddNotification(const CAADlgAddNotification&amp;iObjectToCopy);
    CAADlgAddNotification &amp; operator = (const CAADlgAddNotification &amp;iObjectToCopy);
};
```

```vbscript
#include &quot;CAADlgAddNotification.h&quot;

CATImplementClass(CAADlgAddNotification, Implementation, CATBaseUnknown,CATNull);

CAADlgAddNotification::CAADlgAddNotification(#): CATNotification(CATNotificationDeleteOn)
{}
CAADlgAddNotification::CAADlgAddNotification(#)
{}
```

```vbscript
void CAADlgModel::Add(CAADlgElement * iNewElement) 
{
  if ( NULL != iNewElement )
  {
    ... // The element is successfully added

     CAADlgAddNotification * pAddNotification = new CAADlgAddNotification(#);
     SendNotification(GetFather(#), pAddNotification);
     pAddNotification = NULL;
  }
  else
  {
     CAADlgErrorNotification * pErrorNotification = new CAADlgErrorNotification(#);     
     SendNotification(GetFather(#), pErrorNotification);
     pErrorNotification = NULL;
  }
}
```

```vbscript
CATNotifPropagationMode CAADlgContainer::AnalyseNotification(CATCommand      *iSending, 
                                                             CATNotification *iReceive) 
{
  if (iReceive-&gt;IsAKindOf(&quot;CAADlgNotifError&quot;))
  {
      printf(&quot;The Command Container catches an error /n&quot;);
      return(CATNotifDontTransmitToFather);
  }
  else
  {
    return(CATNotifTransmitToFather);
  };
}
```

```vbscript
void CAADlgViewScreen::WantedFocus(#) 
{
  RequestStatusChange(CATCommandMsgRequestSharedMode);
}
```

```vbscript
CATNotifPropagationMode CAADlgViewScreen::AnalyseNotification(CATCommand      *iSending, 
                                                              CATNotification *iReceive) 
{
  if ( iReceive-&gt;IsAKindOf(&quot;CAADlgAddNotification&quot;) ||
       iReceive-&gt;IsAKindOf(&quot;CAADlgRemoveNotification&quot;) )
  {
    CAADlgElement *pElement= NULL;
    pElement = (CAADlgElement *)iSending-&gt;SendObject(CAADlgElement::ClassName(#), iReceive);

    if ( NULL != pElement) 
    {
      pElement-&gt;Release(#); 
      pElement = NULL ;
      return(CATNotifDontTransmitToFather);
      }
    else 
      return(CATNotifTransmitToFather);
  }
  else 
    return(CATNotifTransmitToFather);
}
```

```vbscript
void *CAADlgModel::SendCommandSpecificObject(const char      *iObjectClassNeeded, 
                                             CATNotification *iReceived) 
{
  void * pObjectToReturn = NULL;

  if ( iReceived-&gt;IsAKindOf(&quot;CAADlgAddNotification&quot;) || 
       iReceived-&gt;IsAKindOf(&quot;CAADlgRemoveNotification&quot;) ) 
  {
    if ( _pTheLastElementManipulated-&gt;IsAKindOf(iObjectClassNeeded) )
    {
      pObjectToReturn = _pTheLastElementManipulated;
      pObjectToReturn-&gt;AddRef(#);
    }
  } 
  return pObjectToReturn ;
}
```