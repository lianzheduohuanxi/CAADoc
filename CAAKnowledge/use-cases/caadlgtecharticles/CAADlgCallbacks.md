---
```vbscript
title: "Using Callbacks to Trigger Actions"
category: tech-article
module: "CAADlgTechArticles"
tags: []
source_file: "Doc/online/CAADlgTechArticles/CAADlgCallbacks.htmmd"
converted: "2026-05-11T17:17:56.024159"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Dialogs

|
### Using Callbacks to Trigger Actions

_How to associate actions with controls_
---|---|---
Technical Article

* * *
### Abstract

The controls of your windows are merely designed to support user interactions and choices. The end user can select an item in a list, such as a file, push on to a push button, select a quantity using a slider or a spinner, and so forth. To convey the user choice to your application, you will use callbacks. When a given control is activated by the end user, it sends a notification which reflects its modification or state. If you have asked to react to this control for this notification using the callback mechanism and if you have coded a method to execute when such a notification is sent, this method will be executed each time the given notification is emitted by the control.

  * **Overview**
  * **Using Callbacks**
  * **Creating and Deleting a Transient Dialog Window**
  * **In Short**
  * **References**

---

* * *
### Overview

The dialog window class usually aggregates by reference the different controls it contains. When the dialog window Build method instantiates the controls, it sets the parent of this control. This parent must be the control container. This parent has a dual meaning. It is the containment parent, but also the command parent. The containment parent is the object that physically contains the control on the display [1]. The command parent is the object to which the control will send the notifications that correspond to the events happening to it. Since all dialog objects are instances of classes that derive from CATDialog which itself derive from CATCommand, each of these instances occupies a node in the command tree structure [2]. This enables you to use the Send/Receive communication protocol between commands to convey the notifications sent by your controls to the appropriate class that holds the corresponding method to execute. These methods can't be hold by the control itself, because it is just instantiated from a supplied class.

```vbscript
```vbscript
For example, consider the part of a dialog window shown below:

```

```

![CATDlgParent.jpg /(7407 bytes/)](images/CATDlgParent.jpg)

It contains two frames named Axis and Bottom. Assume that these two frames have the dialog window as parent. The Axis frame contains three controls: the Reverse push button, the Normal to Surface check button, and the disabled editor displaying No selection. These three controls have the Axis frame as parent because they are contained in this frame. A pointer to the Axis frame were passed as the first argument of their constructor. Consequently they also have the Axis frame as command parent.

Containment Tree Structure | Command Tree Structure
---|---

It contains two frames named Axis and Bottom. Assume that these two frames have the dialog window as parent. The Axis frame contains three controls: the Reverse push button, the Normal to Surface check button, and the disabled editor displaying No selection. These three controls have the Axis frame as parent because they are contained in this frame. A pointer to the Axis frame were passed as the first argument of their constructor. Consequently they also have the Axis frame as command parent.
Containment Tree Structure | Command Tree Structure
Nevertheless, this command parent can be changed afterwards. For example, the dialog window could be set as their command parent to shorten the sent notification path across the command tree structure. This is possible thanks to the SetFather method of CATCommand. Conversely, the containment parent cannot be changed. This is shown below.

Containment Tree Structure | Command Tree Structure

[Top]

* * *
### Using Callbacks

As an example, let's take one of the push buttons of the Burger window. It is instantiated using the following statements:

As an example, let's take one of the push buttons of the Burger window. It is instantiated using the following statements:
    CATDlgPushButton * pApply;                    // Instantiate the push button
```vbscript
    pApply = new CATDlgPushButton(this, "Apply_Push_Button");

```

```vbscript
    ...                                          // Set a callback on it
CATDlgPushButton * pApply;                    // Instantiate the push button
```
pApply = new CATDlgPushButton(this, "Apply_Push_Button");
```vbscript
    AddAnalyseNotificationCB(pApply,                                 // push button
```

                             pApply->GetPushBActivateNotification(#), // notification
                             (CATCommandMethod)&Burger::labelApply,  // method to trigger
                             NULL);                                  // no data to pass to labelApply

---

(CATCommandMethod)&Burger::labelApply,  // method to trigger
NULL);                                  // no data to pass to labelApply
where:

  * `pApply` is a pointer to push button
  * `pApply->GetPushBActivateNotification(#)` retireves the notification to which the window must react
  * `(CATCommandMethod)&Burger::labelApply` is the method to trigger when the notification is emitted. The method l`abelApply` of the Burger object is casted to a `CATCommandMethod` method.

Each time the user pushes on the Apply push button, a activation notification of the Apply push button, instance of the CATDlgPushBActivateNotification class, is emitted, and the callback mechanism is used to trigger the method labelApply. This method has the following signature:

Each time the user pushes on the Apply push button, a activation notification of the Apply push button, instance of the CATDlgPushBActivateNotification class, is emitted, and the callback mechanism is used to trigger the method labelApply. This method has the following signature:
    void Burger::labelApply(
            CATCommand           * ipControl,          // push button
            CATNotification      * ipNotification,     // notification
            CATCommandClientData   iUsefulData=NULL);  // no data here

---

CATNotification      * ipNotification,     // notification
CATCommandClientData   iUsefulData=NULL);  // no data here
The parameters are those you put as parameters of the method `AddAnalyseNotificationCB`:

`ipControl` | The pointer to the push button which sets the callback, seen here as a CATCommand (all classes of the Dialog framework derive from the class CATCommand of the System framework)
---|---
`ipNotification` | The pointer to the notification emitted by the push button
`iUsefulData` | Data that you can request to pass using this parameter which can be useful to the method to execute. For example, if the control is an editor, you can pass the character string selected.

When the user closes the window into which the control was located, you need to remove all the callbacks set on this control. To do this, in the window destructor, use the method `RemoveAnalyseNotificationCB` as follows:

When the user closes the window into which the control was located, you need to remove all the callbacks set on this control. To do this, in the window destructor, use the method `RemoveAnalyseNotificationCB` as follows:
    RemoveAnalyseNotificationCB(pApply,
                                pApply->GetPushBActivateNotification(#),
                                NULL)

---

[Top]

* * *
### Creating and Deleting a Transient Dialog Window

You will often need to create a transient window from your main window or from another transient window. Usually, the transient window is the result of a user action on a push button, or a selection in a list displayed in an editor, or whatever scenario which uses a control you can imagine to request from the user the data your application is expecting.

You will often need to create a transient window from your main window or from another transient window. Usually, the transient window is the result of a user action on a push button, or a selection in a list displayed in an editor, or whatever scenario which uses a control you can imagine to request from the user the data your application is expecting.
To create and display a transient window, you need to use a callback set on the control you propose to the user. The method called from this callback should then include the instantiation of the transient window. In addition to the different dialog object you will put in this transient window, some of them, when activated, will close the window, whether the data input is complete or the user cancels the data input.

To do this, you need to set callbacks on the controls in the transient window to be able to perform the task appropriate to the user action.

```vbscript
```vbscript
For example, suppose you create a transient window to key in a character string in an editor when the end user has pressed on a push button. Proceed as follows:

```

```

    ...
```vbscript
    AddAnalyseNotificationCB(          // set callback on the control to
           pPushButton,                // create the transient window
           pPushButton->GetPushBActivateNotification(#),
           (CATCommandMethod)&MyDocument::CreateTransWindow,
           UsefulData);
```

    ...
pPushButton,                // create the transient window
pPushButton->GetPushBActivateNotification(#),
(CATCommandMethod)&MyDocument::CreateTransWindow,
UsefulData);
    void MyDocument::CreateTransWindow(
                      CATCommand * pCommand,
                      CATNotification * pNotification
                      CATCommandClientData UsefulData) {
      MyTransientWindow * _Window;
      _pWindow = new MyTransientWindow(         // create the transient
                     this,                      // window

                     "Transient_Window_Name",
CATCommandClientData UsefulData) {
MyTransientWindow * _Window;
_pWindow = new MyTransientWindow(         // create the transient
this,                      // window
                     CATDlgWndOK);

      ...
_pWindow = new MyTransientWindow(         // create the transient
this,                      // window
CATDlgWndOK);
      AddAnalyseNotificationCB(                 // set callback on the
              _pWindow,                         // window when the
              _pWindow->GetDiaOKNotification(#), // text is keyed in
              (CATCommandMethod)&MyDocument::MethodOK,
              (void *) _pWindow);

    }
    ...
_pWindow->GetDiaOKNotification(#), // text is keyed in
(CATCommandMethod)&MyDocument::MethodOK,
(void *) _pWindow);
    void MyDocument::MethodOK(                // do what is needed
                      CATCommand * pCommand,  // to retrieve the text
                      CATNotification * pNotification
                      CATCommandClientData UsefulData) {

      ...
      *Text = ((MyTransientWindow *) UsefulData)->
CATCommand * pCommand,  // to retrieve the text
CATNotification * pNotification
CATCommandClientData UsefulData) {
                   TransWindowEditor->GetText(#) ;

      ...
CATCommandClientData UsefulData) {
TransWindowEditor->GetText(#) ;
      delete ((MyTransientWindow *) UsefulData); // delete transient window

    }

---

You normally set a callback, for example on a push button of your main window. The method called back when the user presses on this push button creates the transient window with all its stuff. To react to user actions in this window, you set callbacks wherever you need, and especially to react to completion and closing request, that is in these cases:

  * when the text is keyed in and the end user has pressed Enter or the OK button: this is shown in the example. The transient window pointer is passed to the method MethodOK as a CATCommandClientData (void *) and allows to retrieve the text input. Before exiting, the transient window is deleted. This window is handled through the pointer passed to the method, casted to a MyTransientWindow pointer.
  * when the end user cancels its input by pressing the Cancel button. To do this, set a callback for the CATDlgDiaCANCELNotification using `GetDiaCANCELNotification` as follows:

You normally set a callback, for example on a push button of your main window. The method called back when the user presses on this push button creates the transient window with all its stuff. To react to user actions in this window, you set callbacks wherever you need, and especially to react to completion and closing request, that is in these cases:
        AddAnalyseNotificationCB(
                  _pWindow,
                  _pWindow->GetDiaCANCELNotification(#),
                  (CATCommandMethod)&MyDocument::MethodCANCEL,
                  (void *) _Window)

---
  * when the end user closes the window by means of the close item, or using ALT F4. To do this, set a callback for the CATDlgWindCloseNotification using `GetWindCloseNotification` as follows:

(void *) _Window)
        AddAnalyseNotificationCB(
                  _pWindow,
                  _pWindow->GetWindCloseNotification(#),
                  (CATCommandMethod)&MyDocument::MethodClose,
                  (void *) _Window);

---

(CATCommandMethod)&MyDocument::MethodClose,
(void *) _Window);
Note that a single method could be used for cancelling or closing.

[Top]

* * *
### In Short

Callbacks are used to associate an action to a control activation. When activated the control sends a notification that goes upwards in the command tree structure, that usually matches the dialog containment tree structure. A transient window can be created from a callback method that itself can set callbacks to manage control activation in the transient window.

[Top]

* * *
### References

[1] | [Creating Dialog Objects](CAADlgCreatingDialogs.md)
---|---
[2] | [The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.md)
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
