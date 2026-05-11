---
title: "Creating Dialog Objects"
category: "use-case"
module: "CAADlgTechArticles"
tags: ["CATInteractiveApplication"]
source_file: "Doc/online/CAADlgTechArticles/CAADlgCreatingDialogs.htm"
converted: "2026-05-11T17:17:56.030157"
---
# 3D PLM Enterprise Architecture

| 
## User Interface - Dialogs

| 
### Creating Dialog Objects

_How to create and manage dialog objects_  
---|---|---  
Technical Article  
  
* * *
### Abstract

All the Dialog framework classes share the way to get their behavior, and attributes. The behavior is set in the object constructor using by assigning a parent object and a style. Attributes are the visibility, and the sensitivity to the end user interactions. Dialog windows and objects can be dynamically created and modified with respect to their changing environment, and dialog objects can thus be deleted or created in an existing dialog window. 

  * **Constructing Dialog Objects**
  * **Managing Visibility and Sensitivity**
    * Managing Visibility
    * Managing Sensitivity
  * **Deleting Dialog Objects**
  * **In Short**
  * **References**

  
---  
  
* * *
### Constructing Dialog Objects

Most of the dialog classes can be used as is, that is instantiated, such as the controls, or the containers. Some others must be derived to create specialized objects, such as the dialog windows. Each class has a constructor which requires at least two parameters, and sometimes three: 

  1. **The parent** [1]. It is altogether: 
     * The parent in the dialog object containment structure. It is the container object. Some rules exist on the parent object. For example, a control cannot be a parent object, since it cannot contain other dialog objects. A [ CATDlgTabContainer](../CAADlgQuickRefs/CAADlgCATDlgTabContainer.md) instance can contain only [ CATDlgTabPage](../CAADlgQuickRefs/CAADlgCATDlgTabPage.md) instances, and conversely, a [ CATDlgTabPage](../CAADlgQuickRefs/CAADlgCATDlgTabPage.md) instance can only be contained by [ CATDlgTabContainer](../CAADlgQuickRefs/CAADlgCATDlgTabContainer.md), but can contain in turn other containers, such as [CATDlgFrame](../CAADlgQuickRefs/CAADlgCATDlgFrame.md) instances, and controls.
     * The parent in the command tree structure. Since [CATDialog](../CAADlgQuickRefs/CAADlgCATDialog.md) derives from _CATCommand_ , each dialog object instance is seen as a command for the event management mechanisms, such as the send/receive [2] and the callback [3] mechanisms.

This parent must of course be an instance of a class that derives from _CATCommand_ , but in addition, it must be either another dialog object instance: its container, or a _CATInteractiveApplication_ instance [4]. Then you can set the parent object for the command tree structure and event transmission to another object that derives from _CATCommand_ using the `CATCommand::SetFather` method. This modifies only the command tree structure, but the parent in containment tree structure doesn't change. The method `GetFatherWindow` allows you to retrieve a pointer to the parent window, usually the dialog object that sits at the top of the containment tree structure
  2. **The instance identifier** : this is an internal character string, instance of the _CATString_ class, which can be used for your internal management, but which is never shown to the end user and thus does not require to be translated. It is generally used to retrieve resources set to the dialog object, such as the title displayed on a push button, a menu item, or a label, or the icon displayed for a push item in a toolbar [5]. Blank characters are not allowed. The `GetName` method allows you to retrieve this identifier.
  3. **The style** : always defaulted to NULL, the style available values depend on the dialog object type, and cannot be modified afterwards. For example, it can set the option style for a combo or request that the text keyed in in an editor should be an integer. The method `GetStyle` allows to retrieve the style of a dialog object.

As an example, the construction of a _[CATDlgCombo](../CAADlgQuickRefs/CAADlgCATDlgCombo.md)_ instance could be as follows:
    
    
    CATDlgCombo * pMyCombo;
    pMyCombo = new CATDlgCombo(this,                  // parent
                               "MyNiceCombo",         // identifier
                               CATDlgCmbOptionStyle); // style  
  
---  
  
When the style can be composite, use the pipe | to concatenate the style attributes. For example, if you want to create a combo with the drop down style and with an editable field, construct it as follows:
    
    
    CATDlgCombo * pMyCombo;
    pMyCombo = new CATDlgCombo(this,
                               "MyNiceCombo",
                               CATDlgCmbDropDown | CATDlgCmbEntry);  
  
---  
  
[Top]
### Managing Visibility and Sensitivity

The other generic attributes of a dialog object are the ability to be seen or hidden, and to be sensitive to user interaction or not, that is the user can select or click it or not.

[Top]
#### Managing Visibility

A given dialog object can be set visible or invisible by means of its visibility attribute which takes the values `CATDlgShow` and ` CATDlgHide`. When creating a main container, such as a _[CATDlgDocument](../CAADlgQuickRefs/CAADlgCATDlgDocument.md)_ or a _[CATDlgDialog](../CAADlgQuickRefs/CAADlgCATDlgDialog.md)_ instance, you need to set it visible using the following method:
    
    
    SetVisibility(CATDlgShow);  
  
---  
  
By default, all the dialog objects contained in this main container are also shown.

The `GetVisibility` method allows you to know whether a given object is visible:
    
    
    if (pObject->GetVisibility() == CATDlgShow)
      ... //Do what is required if the object is visible
    else
      ... //Do what is required if the object is not visible  
  
---  
  
To hide a part of a window, set the visibility attribute of the container(s) making up this part to `CATDlgHide `rather than deleting the involved dialog objects. This avoids to recreate them if you need them again. Just set their visibility attribute to `CATDlgShow`.

[Top]
#### Managing Sensitivity

Another key attribute is the sensitivity of the dialog object to the user interactions. This is usually dedicated usually to controls. You can request a control to be sensitive to user interactions by assigning it the state ` CATDlgEnable`, or the reverse using the state `CATDlgDisable`, by means of the `SetSensitivity` method, as follows:
    
    
    Control->SetSensitivity(CATDlgEnable);  
  
---  
  
A disabled control is displayed dimmed and cannot be selected. Below are some examples of controls shown as disabled and enabled.

| CATDlgDisable | CATDlgEnable  
---|---|---  
Radio buttons 
Combo 
Menu items 
Push items 
  
The ThickSurface and CloseSurface menu items are enabled in both cases.

[Top]
### Deleting Dialog Objects

To delete a dialog object in a dialog window while the dialog window remains active, you can use the RequestDelayedDestruction method, especially in a callback method. Using RequestDelayedDestruction, you can delete the dialog object from a callback method set onto this dialog object. The delete operation is delayed, and executed after the callback end.

When you delete a dialog window, you just need to delete the upper container. The contained dialog objects are then recursively and automatically deleted. If you want to delete a contained container, use RequestDelayedDestruction on this container. Its contained dialog objects are then also recursively and automatically deleted.

[Top]

* * *
### In Short

The behavior of a dialog object is set using its parent to anchor it in the command tree structure, and using its style, possibly composite. Its visibility and its sensitivity to end user interactions can be managed.

[Top]

* * *
### References

[1] | [Dialog Class Usage and Link Reference](../CAADlgQuickRefs/CAADlgDialogSummary.md)  
---|---  
[2] |  [ The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.md)  
[3] |  [ The Callback Mechanism](../CAASysTechArticles/CAASysCallbacks.md)  
[4] | [Designing Your Interactive Application](CAADlgInteractiveApplication.md)  
[5] | [Assigning Resources](CAADlgResources.md)  
[Top]  
  
* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
