---
title: "Untitled"
category: "use-case"
module: "CAADlgUseCases"
tags: ["CAADlgBBReceiverWindow", "CAAIDlgDataRequest", "CAASysTechArticles", "CAADocStyleSheets", "CATInstantiateComponent", "CAADialog", "CAASysSampleBBSendRecDataMsg", "CAADlgBBMessageInt", "CAASysOMInheritance", "CAASysUseCases", "CAADlgBBEditorMessage", "CAASysSampleBBSimpleMsg", "CAADlgBBReceiver", "CAADocUseCases", "CAADlgBBMessage", "CAASysSampleBBSendRecSimpleMsg", "CATInteractiveApplication", "CAASystem", "CATImplementClass", "CAADlgBBMessageManager"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleBBMsg.htmmd"
converted: "2026-05-11T11:27:02.785913"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to show you how an interactive application can
declare that it will send or receive messages, how to filter the messages to
receive, and how to send and receive messages using the backbone objects of the
System framework. The message taken as an example conveys a text.

[Top]

### The CAADlgBBSender and CAADlgBBReceiver Use Cases

CAADlgBBSender and CAADlgBBReceiver are use cases of the CAADialog.edu
framework that illustrates the Dialog and System frameworks capabilities.

[Top]

#### What Do CAADlgBBSender and CAADlgBBReceiver Do

This use case illustrates two interactive applications. One behaves as a
message sender, and the other as a message receiver. The message is a data
message that conveys a text. The message sender displays an entry field in which
the end user types the message text and clicks the Send button to send the
message. The message receiver displays a field in which the text of the received
message is printed.

Both the message sender and the message receiver are interactive applications
launched by instantiating a class that derives from *CATInteractiveApplication*.
To send the message, the message sender connects to the backbone bus, declares
itself, instantiates the message component using the text entered in the text
field of its window, and sends it.

The message receiver needs to instantiate a message handler to receive the
message. Such a message handler is a component that implements the *CATIMessageReceiver*
interface. In addition, the message receiver subscribes to a notification that
the message handler will request a message manager to dispatch along with the
message text. To receive the message, the message receiver connects to the
backbone bus, declares itself, declares the message to receive, instantiates the
message handler, associates itself with the message to receive and with the
message handler. As soon as the message is sent, it is retrieved by the message
handler that requests the message manager to dispatch a notification that
carries the message text, and to which the message receiver has subscribed. The
message receiver called back method extract the message text from the
notification and prints it in the window text field.

Compared to batch applications that intend to receive messages [1]
[2], there is no need to create and enter a waiting
loop, since the interactive application includes one already. The message
conveys data [5] made of a text. It is not described.

[Top]

#### How to Launch CAADlgBBSender and CAADlgBBReceiver

To launch CAADlgBBSender and CAADlgBBReceiver, you will need to set up the
build time environment, then compile CAADlgBBSender and CAADlgBBReceiver along
with its prerequisites, set up the run time environment [3]
in two different windows, and then execute the use case.

To execute the use case:

  
- With Windows, successively type in the DOS window command line the two
    module names:
    

CAADlgBBSender
CAADlgBBReceiver
  
  
- With UNIX, successively type in the shell window command line the two
    module names with "&" to launch them in background mode:
    

CAADlgBBSender &
CAADlgBBReceiver &
  

Type a text in the Backbone Sender window text field, and click Send. The
text is printed in the Backbone Receiver window text field.

[Top]

#### Where to Find the CAADlgBBSender and CAADlgBBReceiver
Code

The CAADlgBBSender and CAADlgBBReceiver use case are made of several classes
located in the CAADlgBBSender.m and CAADlgBBReceiver.m module of the
CAADialog.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

The message component is made of several classes located in the
CAADlgBBMessage.m module of the CAADialog.edu framework, and in addition
implements the CAAIDlgDataRequest interface located in the PrivateInterfaces
directory and in the CAADlgBBMessageInt.m module of the CAADialog.edu framework.
They are not described in this article. Refer to the messages described in the
CAASystem.edu framework [4] [5].

[Top]

### Step-by-Step

To create interactive applications that send and receive a data message,
there are seven main steps:

  
- Creating the Message Sender
  
- Sending the Message
  
- Creating the Message Handler
  
- Creating the Message Manager
  
- Creating the Message Receiver
  
- Receiving the Message
  
- Removing the Message Handler

[Top]

#### Creating the Message Sender

The message sender is an interactive application whose class is *CAADlgBBSender*.
Its main method is `BeginApplication` where the application window is
instantiated. The window class is *CAADlgBBSenderWindow* whose `Build`
method connects to the backbone bus by calling its `BackboneInit`
method before creating the controls and setting a callback to react when the
Send button is clicked. Below is the `BackboneInit `method

First, a connection to the backbone bus must be established. This is possible
thanks to the global function `CATGetBackboneConnection` that returns
a pointer to the *CATICommunicator* interface stored in the `_pICommunicator`
data member. Then, the message sender creates its application class identifier
and declares it to the backbone bus using the method `Declare`.

[Top]

#### Sending the Message

The message is sent by the callback set to the push button activation.

When you click Send, this method is called, and the message sender can send
the message. It first retrieves the text entered in the text field, a *CATDlgEditor*
instance, thanks to the `GetLine` method. Then it instantiates the
message component *CAADlgBBEditorMessage* using the `CATInstantiateComponent`
global function, which returns a pointer to *CAAIDlgDataRequest* interface.
This interface is created for this message to enable it to set and get its data,
that is, the message text. The message text is passed to the message component
thanks to the `SetData` method of *CAAIDlgDataRequest*, and then
the message is sent using the `SendRequest` method of *CATICommunicator*,
specifying the target message receiver identifier and the message to send as a
pointer to *CATICommMsg*. This message receiver identifier must be the same
than the one declared by the message receiver itself in its own `BackboneInit`
method.

[Top]

#### Creating the Message Handler

The *CAADlgBBEditorMessageHandler* class belongs to a component, thanks
to the `CATDeclareClass` macro, C++ derives from *CATBaseUnknown*,
and implements *CATIMessageReceiver*, whose single method is `HandleMessage`.
Note that the copy constructor is set as private, and is not implemented in the
source file. This prevents the compiler from creating the copy constructor as
public without you know.

The *CAADlgBBEditorMessageHandler* class states that it implements the *CATIMessageReceiver*
interface thanks to the `TIE_CATIMessageReceiver` macro. The `CATImplementClass`
macro declares that the *CAADlgBBEditorMessageHandler *class is a component
main class thanks the `Implementation` keyword, and that the
component OM-derives [6] from *CATBaseUnknown*.
Any component main class declared as an `Implementation` must
C++-derive and OM-derive from the same class. The *CATIMessageReceiver*
interface `HandleMessage` method is called by the backbone bus and a
pointer to the message is passed. A pointer to *CAAIDlgDataRequest* is
retrieved from the message to get the message text. Then, the message manager of
the message receiver application is retrieved. The message text is passed to the
message manager thanks to the `EventToDispatch` method.

The framework interface dictionary is updated to declare that *CAADlgBBEditorMessageHandler*
implements the *CATIMessageReceiver*  interface in the
libCAADlgBBReceiver shared library or DLL. This interface dictionary is a file
located in the CNext/code/dictionary directory, and is named CAADialog.edu.dico.
There is one and only one interface dictionary per framework, named using the
framework name suffixed by dico.

[Top]

#### Creating the Message Manager

The message manager is a component that dispatches a notification that
carries the message text.

The message manager is created as a component and is unique. It is
instantiated by the `GetManager` static method. The `EventToDispatch`
method retrieves the default callback manager associated with any component,
instantiates a *CAADlgBBMessageNotification* class that takes the message
text as a data member, and request the default callback manager to dispatch this
notification, to which the message receiver application will subscribe.

[Top]

#### Creating the Message Receiver

The message receiver is an interactive application. It has a window, instance
of the class *CAADlgBBReceiverWindow*, that carries out the main tasks of
connecting to the backbone bus and receiving the message. Below is the `Build`
method of  *CAADlgBBReceiverWindow.*

The `Build` method first call the `BackboneInit`
method, and if this method succeeds, creates the controls. Then it retrieves the
message manager thanks to the static method `GetManager` of *CAADlgBBMessageManager*,
and sets a callback, that is, subscribes to an event, using the `AddCallback`
global function whose arguments are:

The `BackboneInit` method is as follows.

First, a connection to the backbone bus must be established. This is possible
thanks to the global function `CATGetBackboneConnection` that returns
a pointer to the *CATICommunicator* interface. Once the connection is
established, the message receiver sets its application identifier and declares
it to the backbone bus using the method `Declare`. Note that this
identifier is used by the message sender when sending the message using the `SendRequest`
method. Then the message receiver instantiates the message handler, asks the
message handler for a pointer to *CATIMessageReceiver*, and declares to the
backbone bus that it will receive the declared messages using the designated
handler, thanks to the `AssociateHandler` method.

[Top]

#### Receiving the Message

The message is received thanks to the message handler that retrieves the
message manager, and requests it to dispatch a notification that carries the
message text. The message receiver has subscribed to this notification, and the
callback method designated is then called. This method is the `ModifyEditor`
method below.

`ModifyEditor` retrieves the message text from the notification,
and assigns it to the editor thanks to the `SetLine` method.

[Top]

#### Removing the Message Handler

The message handler should be removed when no messages are to be received any
longer. This is done here in the message receiver application window destructor.

The data members are released and nullified. The message handler is removed
thanks to the `RemoveHandler` method of *CATICommunicator*. Its
arguments are:

[Top]

---

### In Short

This use case shows how to create interactive applications that send and
receive backbone messages. The receiving application identifier must be known by
the message sender.

[Top]

---

### References

---

### History

---

*Copyright  2000, Dassault Systmes. All rights reserved.*

```vbscript
CAADlgBBSender
CAADlgBBReceiver
```

```vbscript
CAADlgBBSender &amp;
CAADlgBBReceiver &amp;
```

```vbscript
...
HRESULT CAADlgBBSenderWindow::BackboneInit(#)
{
  HRESULT  rc = E_FAIL;
  // Retrieves an instance of a backbone bus (default bus)
  _pICommunicator = ::CATGetBackboneConnection(#);
  if ( NULL != _pICommunicator )
  {
     CATApplicationClass ApplicationSenderId = &quot;CAADlgBBSender&quot;;
     rc =_pICommunicator-&gt;Declare(ApplicationSenderId);
     ... //Process failing declaration
  }
  return rc;
}
...
```

```vbscript
...
void CAADlgBBSenderWindow::PushSend(CATCommand         * iSendingCommand, 
                                    CATNotification    * iSentNotification, 
                                    CATCommandClientData iUsefulData)
{
  CATUnicodeString Line;
  _pEditor-&gt;GetLine(Line);
  CAAIDlgDataRequest * pIDataRequest = NULL;
  HRESULT rc = ::CATInstantiateComponent(&quot;CAADlgBBEditorMessage&quot;,
                                         IID_CAAIDlgDataRequest,
                                         (void **)&amp;pIDataRequest);
  if ( SUCCEEDED(rc) )
  {
    pIDataRequest-&gt;SetData(Line.CastToCharPtr(#));

    CATICommMsg * pICommMsg =NULL;
    rc = pIDataRequest-&gt;QueryInterface(IID_CATICommMsg,(void**)&amp;pICommMsg);
                                                 
    if ( SUCCEEDED(rcb) )
    {
      CATApplicationClass ReceiverApplicationId = &quot;CAADlgBBReceiver&quot;;
      rc = _pICommunicator-&gt;SendRequest(ReceiverApplicationId, pICommMsg);
      pICommMsg-&gt;Release(#);
      pICommMsg = NULL;
    }
    pIDataRequest-&gt;Release(#);
    pIDataRequest = NULL;
  }
}
...
```

```vbscript
#include &quot;CATBaseUnknown.h&quot;   //Needed to derive from CATBaseUnknown

class CATICommMsg;

class  CAADlgBBEditorMessageHandler : public CATBaseUnknown
{
   CATDeclareClass;
   public:
      CAADlgBBEditorMessageHandler(#);
      virtual ~CAADlgBBEditorMessageHandler(#);

      // CATIMessageReceiver Interface
      void HandleMessage(CATICommMsg * iMessage);

  private:
      CAADlgBBEditorMessageHandler(const CAADlgBBEditorMessageHandler &amp;iObjectToCopy);
};
```

```vbscript
#include &quot;CAADlgBBEditorMessageHandler.h&quot;
#include &lt;CATErrorDef.h&gt; // for the SUCCEEDED macro 
#include &quot;CAAIDlgDataRequest.h&quot;
#include &quot;CAADlgBBMessageManager.h&quot;

#include &quot;TIE_CATIMessageReceiver.h&quot;
TIE_CATIMessageReceiver(CAADlgBBEditorMessageHandler);

CATImplementClass(CAADlgBBEditorMessageHandler,
                  Implementation,
                  CATBaseUnknown,
                  CATNull);

CAADlgBBEditorMessageHandler::CAADlgBBEditorMessageHandler(#){}

CAADlgBBEditorMessageHandler::~CAADlgBBEditorMessageHandler(#){}

void CAADlgBBEditorMessageHandler::HandleMessage(CATICommMsg* iMessage)
{
  if ( NULL != iMessage )
  {
    CAAIDlgDataRequest * pIRequest = NULL;
    HRESULT rcb = iMessage-&gt;QueryInterface(IID_CAAIDlgDataRequest,(void**) &amp;pIRequest);
    if ( SUCCEEDED(rcb) )
    {
       char * Text = NULL;
       pIRequest-&gt;GetData(&amp;Text);
       pIRequest-&gt;Release(#);
       pIRequest= NULL;

       CAADlgBBMessageManager * pManager = CAADlgBBMessageManager::GetManager(#);
       pManager-&gt;EventToDispatch(Text);
        
       delete [] Text;
       Text = NULL;

       pManager-&gt;Release(#);
       pManager= NULL;
    }
  } 
}
```

```vbscript
...
CAADlgBBEditorMessageHandler CATIMessageReceiver  libCAADlgBBReceiver
...
```

```vbscript
#include &lt;CAADlgBBMessageManager.h&gt;
#include &lt;CAADlgBBMessageNotification.h&gt;
#include &quot;CATCallbackManager.h&quot;

CATImplementClass(CAADlgBBMessageManager,Implementation,CATBaseUnknown,CATNull);

CAADlgBBMessageManager * CAADlgBBMessageManager::_Manager = NULL;

CAADlgBBMessageManager::CAADlgBBMessageManager(#)
{}

CAADlgBBMessageManager::~CAADlgBBMessageManager(#)
{}

void CAADlgBBMessageManager::EventToDispatch(char * iText)
{
  CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this);
  if ( NULL != pCBManager )
  {
     CAADlgBBMessageNotification * pNotification = new CAADlgBBMessageNotification(iText);

     pCBManager-&gt;DispatchCallbacks(pNotification, this);

     pNotification-&gt;Release(#);
     pNotification = NULL;
  }	
}

CAADlgBBMessageManager * CAADlgBBMessageManager::GetManager(#)
{
  if ( NULL == _Manager )
  {
    _Manager = new CAADlgBBMessageManager(#);
  }
  _Manager-&gt;AddRef(#);
  return _Manager;
}
...
```

```vbscript
void CAADlgBBReceiverWindow::Build(#)
{
  HRESULT Init = BackboneInit(#);

  if ( SUCCEEDED(Init) )
  {
     CATDlgFrame  * pFrame  = new CATDlgFrame(this, &quot;FrameId&quot;, CATDlgFraNoFrame | CATDlgGridLayout );
  
     CATDlgLabel  * pLabel  = new CATDlgLabel (pFrame,&quot;LabelEditorId&quot;);
     pLabel-&gt;SetGridConstraints(0,0,1,1,CATGRID_LEFT);

     _pEditor = new CATDlgEditor(pFrame,&quot;EditorId&quot;,CATDlgEdtReadOnly);
     _pEditor-&gt;SetGridConstraints(0,1,1,1,CATGRID_LEFT); 
  
     _pMessageManager = CAADlgBBMessageManager::GetManager(#);
     ::AddCallback(this,
                   _pMessageManager,
                   &quot;CAADlgBBMessageNotification&quot;,
                   (CATSubscriberMethod)&amp;CAADlgBBReceiverWindow::ModifyEditor,
                   NULL);
  }
  AddAnalyseNotificationCB(this,
                           GetWindCloseNotification(#),
                           (CATCommandMethod)&amp;CAADlgBBReceiverWindow::Exit, NULL);
}
...
```

```vbscript
HRESULT CAADlgBBReceiverWindow::BackboneInit(#)
{
  HRESULT rc = E_FAIL;
  _pICommunicator = ::CATGetBackboneConnection(#);
  if ( NULL == _pICommunicator )
      ... // Process failure
  else
  {
    CATApplicationClass ReceiverApplicationId = &quot;CAADlgBBReceiver&quot;;
    rc= _pICommunicator-&gt;Declare( ReceiverApplicationId );
    if ( FAILED(rc) )
      ... // Process failure
    else
    {
      CATMessageClass MessageClassName = &quot;CAADlgBBEditorMessage&quot;; 
      CAADlgBBEditorMessageHandler * pHandlerForMessage = NULL;
      pHandlerForMessage = new CAADlgBBEditorMessageHandler(#);

      if ( NULL != pHandlerForMessage )
      {
        rc = pHandlerForMessage-&gt;QueryInterface(IID_CATIMessageReceiver,
                                                (void**)&amp; _pIMessageReceiver);
        if ( SUCCEEDED(rc) )
        {
          rc = _pICommunicator-&gt;AssociateHandler(ReceiverApplicationId, 
                                                 MessageClassName,
                                                 _pIMessageReceiver);
          ... // Process failure
        }
        pHandlerForMessage-&gt;Release(#);
        pHandlerForMessage = NULL;
      }
    }
  }
  return rc;
}
...
```

```vbscript
...
void CAADlgBBReceiverWindow::ModifyEditor(CATCallbackEvent  ievent,
                                          void             *ipublisher,
                                          CATNotification  *iNotification,
                                          CATSubscriberData iData,
                                          CATCallback       iCallback)
{
   char * Text = NULL;
   CAADlgBBMessageNotification * iNotif = (CAADlgBBMessageNotification*) iNotification;

   iNotif-&gt;GetText(&amp;Text);
   _pEditor-&gt;SetLine(Text);

   delete [] Text;
}
...
```

```vbscript
...
CAADlgBBReceiverWindow::~CAADlgBBReceiverWindow(#)
{ 
  _pApplication = NULL;
  _pEditor = NULL;

  if ( NULL !=  _pICommunicator )
  {
    if ( NULL != _pIMessageReceiver )
    {
      CATMessageClass MessageClassName = &quot;CAADlgBBEditorMessage&quot;; 
      _pICommunicator-&gt;RemoveHandler(&quot;CAADlgBBReceiver&quot;,
                                     MessageClassName,
                                     _pIMessageReceiver);
      _pIMessageReceiver-&gt;Release(#);
      _pIMessageReceiver = NULL;
    }
    _pICommunicator-&gt;Release(#);
    _pICommunicator = NULL;
  }
  if ( NULL != _pMessageManager )
  {
    _pMessageManager-&gt;Destroy(#);      
    _pMessageManager = NULL;
  }
}
...
```