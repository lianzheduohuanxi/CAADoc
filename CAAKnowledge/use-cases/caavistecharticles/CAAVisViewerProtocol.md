---
title: "Conveying End User Intent from Mouse to Controller"
category: "use-case"
module: "CAAVisTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAVisTechArticles/CAAVisViewerProtocol.htm"
converted: "2026-05-11T17:31:52.306819"
---
# 3D PLM Enterprise Architecture

| 
## 3D Visualization

| 
### Conveying End User Intent from Mouse to Controller

_How the end user actions on the mouse become object modifications_  
---|---|---  
Technical Article  
  
* * *
### Abstract

The mouse is the main device used to interact with CATIA. The end user should be able to perform many kinds of actions with only three buttons and mouse moves. The mouse quickly delegates the end user intended actions to manipulators set onto the representations of the model objects. Here we present the notification protocol used to standardize the end user intents. 

  * **What Happens when the End User Plays with the Mouse?**
  * **The Manipulator States Reflecting the End User Interactions**
  * **In Short**

  
---  
  
* * *
### What Happens when the End User Plays with the Mouse

When the end user moves the mouse above, drags, clicks or double-clicks on an object, this is to do something on this object. Manipulators allows for mapping behaviors on objects, as if they could propose themselves the available tools to manipulate objects. In addition, manipulators provide consistent user interface guidelines through the reactivity of the model objects when the mouse is located or moves on the representations which stand for them.

A representation is then controlled by the manipulator. It's the way to define what happens when: 

  * The mouse is located or moves above a representation controlled by a manipulator: the representation is preactivated, ready to be manipulated. It can be highlighted, and handles can appear to allow for manipulating it
  * The left button of the mouse is pressed on this representation: the representation is activated
  * The mouse drags the representation with the left button pressed to move it or drags a handle of the representation to deform it: the representation is being manipulated
  * The left button of the mouse is double clicked on a representation: the represented model object is asked to edit itself by providing an editing dialog window
  * The right button of the mouse is pressed on this representation: the model object is asked to show the contextual actions that can be performed against it. A contextual menu is displayed
  * The mouse is located or moves on a representation while the the help key or the F1 key is pressed: help is asked on the represented model object.

The different end user actions introduced above set the manipulator in different states that we can define using a finite state machine.

The state of a manipulator is composite and made of three parts: 

  1. The _interactive_ part describes the action of the end user on the manipulator at a given time. It is encoded using the MState member data of the class CATManipulator
  2. The device part describes if a manipulator is current for dragging, that is can be used from now on by non-pointing devices (devices which cannot choose objects on the screen such as key arrow or space ball). It is encoded using the MDeviceState member data of the CATManipulator class
  3. The _edit_ part describes if the popup containing the dialog for editing parameters to move or deform the object is there or not. It is encoded using the MEditState member data of the CATManipulator class.

This figure shows the states of a manipulator (in boxes) and the notifications sent when shifting from one state to another (along the arrows) due to end-user interactions represented by the mouse, here with the first manipulator style used (left button pressed):

![CAAVisViewerProtocol.gif \(11027 bytes\)](images/CAAVisViewerProtocol.gif)

[Top]
### The Manipulator States Reflecting the End User Interactions

The following table describes the notifications received by a manipulator that controls a representation and the states it takes depending on the events due to the user interactions.

**What happens when** | **Notification sent** | **State is or becomes**  
---|---|---  
**MState** | **MDeviceState** | **MEditState**  
The mouse is not located above the representation | None | InNormal | UnPlugged | NotRunning  
The mouse intersects the representation | Preactivate | InPreactivate | UnPlugged | NotRunning  
The mouse moves above the representation | Move | InPreactivate | UnPlugged | NotRunning  
The left button is pressed above the representation | Activate followed by BeginManipulate | InActivate followed by InManipulate | Plugged | NotRunning  
The representation is dragged with the left button down | Manipulate | InManipulate | Plugged | NotRunning  
The left button is released | EndManipulate | InNormal | Plugged | NotRunning  
The left button is pressed above another representation not controlled by the manipulator or above the background | EndActivate | InNormal | UnPlugged | NotRunning  
The right button is pressed above the representation | Context | InContext | Remains as is | NotRunning  
The contextual task ends | EndContext | InNormal | Remains as is | NotRunning  
The left button is double clicked above a representation | Edit | InPreactivate | Plugged | Running  
The editing task ends | EndEdit | InPreactivate | Plugged | NotRunning  
  
The viewer reacts to the user interactions by publishing update notifications. The object, father of the manipulator in the command tree structure, needs to subscribe to these notifications by means of the callback on send/receive mechanism through the `AddAnalyseNotificationCB` method. This object, which is often the current interactive command, triggers then the appropriate method to assign an edit window if MEditState is set to Running, or a contextual menu if MState is set to InContext, or let the manipulator do its job if MState is set to Manipulate.

The manipulator states are fully described below. 

**MState InNormal**
    The mouse is not yet located above the representation controlled by the manipulator
**MState InPreactivate**
    The mouse moves and at a given time intersects a representation controlled by the manipulator without pressing any button. At this moment, the manipulator receives a Preactivate notification, sets MState to InPreactivate and defines the preactivation of the representation. To do this, the manipulator sends a Preactivate notification to its father in the command tree structure, that is to the instance of the CATCommand class or one of its derived class used as one of the manipulator constructor arguments. This notification is an instance of the CATPreactivate class.  
```vbscript
For example, a manipulator used for selection will usually highlight the representation.  
```

When the mouse moves on a representation with a preactivated manipulator, that is a manipulator with MState set to InPreactivate, the viewer publishes a Move notification as long as the mouse moves and remains located above the representation.  
When the mouse leaves the representation, the manipulator receives an EndPreactivate notification. By default, it sends an EndPreactivate notification to its father and sets MState to InNormal.
**MState InActivate**
    A manipulator has MState set to InPreactivate. The end user clicks on the mouse left button. The manipulator receives an Activate notification and sets MState to InActivate. By default, a notification, instance of the CATActivate class, is sent to its father. This notification must be interpreted as "I have taken this element". The manipulator MDeviceState is set to Plugged. If a different manipulator was already plugged, its MDeviceState turns to Unplugged. When a manipulator is plugged, it can receive the notifications of the devices used to manipulate, such as the space ball, the keyboard, the mouse, and so forth.
**MState InManipulate**
    A manipulator has MDeviceState set to Plugged. It has subscribed to the BeginManipulate notification. The left button of the mouse is pressed on the representation. If the manipulator MState was not set to InActivate before the mouse left button is pressed, it is first set to InActivate before then be set to InManipulate until the end user releases the mouse.  
The viewer sends a BeginManipulate notification which includes the x and y pixel coordinates of the mouse location. The manipulator receives it through the publish/subscribe mechanism and sends a notification, instance of the CATBeginManipulate class, to its father. In most cases, a mathematical transformation along with a matrix and a vector are initialized to identity and sent as part of the notification.  
When the object is dragged, that is, for example, when the mouse moves with the left button down, or when the space ball is pressed, or when the arrow down key is pressed, the viewer publishes a Manipulate notification. Depending on the device used to manipulate, the manipulator updates the mathematical transformation between the previous position of the graphical object and the current value resulting from the manipulation. A notification, instance of the class CATGenerateEvent, is sent by the manipulator. The command attached to the manipulator receives this transformation, possibly modifies it to satisfy the applicative constraints, and deforms or moves the appropriate model objects accordingly.  
When the mouse left button is released, a CATEndManipulate notification is sent and the manipulator MState returns to InNormal. If the mouse remains on the representation, a Preactivate notification is sent and the MState is set to InPreactivate.
**MState InContext**
    A manipulator has MState set to InPreactivate. The end user presses the mouse right button. A Context notification is sent to the manipulator which MState is set to InContext. This one creates a contextual menu and sends a notification, instance of the CATContext class, to its father. The father command can then put items in this contextual menu and connect to these items by means of the publish/subscribe mechanism and the `AddAnalyseNotificationCB` method. When an item is chosen, the command which is attached to this item is called back and executes its applicative task. When the callback ends, the manipulator receives the EndContext notification and kills the contextual menu. MState returns to InNormal.  
The contextual menu is specific to each manipulator and is redefined each time a contextual action is asked on a manipulator.
**MStateEdit Running**
    A manipulator is preactivated or activated and the associated representation is double clicked. If the manipulator was only preactivated, it first becomes activated. An Edit notification is published by the viewer. The default behavior of the manipulator consists in sending a notification, instance of the CATEdit class to its father. The command connected to the manipulator can decide to value the MEditState of the manipulator to Running to associate dialog with it. The command must create a popup and assign it to the manipulator. This popup is supposed to contain dialog components, such as alphanumeric fields, slider, other specific representations with new manipulators, and so forth, for changing the values exported by the manipulator. The destruction of these elements occurs when the command receives the CATEndEdit notification, that is when the manipulator leaves the edit state. The manipulator MEditState returns to NotRunning when the edit popup is destroyed when the end-user presses ok, cancel or close). In most cases, the command will not define the contents of the edit popup. A specific manipulator, such as a translation or a rotation manipulator, will have its own edition window to define the value of the event exported by the manipulator.  
A non trivial use of the edit state can be to have a manipulator for selection connected to a set of objects. Its behavior when MEditState is turned to Running can consist in displaying the controlled representations in the edit window and assigning them specific manipulators to deform the model object geometry. Leaving the edit window turns MEditState to NotRunning and destroys the manipulators used for the deformation.

[Top]

* * *
### In Short

When the end user uses the mouse, the different actions are transformed into notifications the system sends to the viewer. Each notification sent reflects the mouse state and movement which themselves reflect the end user intent.

Providing manipulators which subscribe to these notifications bring to the objects manipulated the behavior you wish to match the end user's expected actions.

[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
