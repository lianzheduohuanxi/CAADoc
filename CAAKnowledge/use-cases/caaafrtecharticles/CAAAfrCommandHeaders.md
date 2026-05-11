---
```vbscript
title: "The Command Headers"
category: "use-case"
module: "CAAAfrTechArticles"
tags: ["CAAAfrNormalZHdr", "CATIAfrPaletteOptions", "CAAAfrMRUHeader", "CATIA", "CAAAfrNormalXHdr", "CAAAfrCommandHeader", "CAADegGeoCommands", "CATIAfrCommandHeaderRep", "CATINT32ToPtr", "CAAAfrMyCommandHdr", "CAAAfrGeometryWks", "CATImplementHeaderResources", "CAAAfrGeoCommands", "CAAAfrCommandClass", "CATIAfrCmdPaletteOptions", "CAAAfrPointHdr", "CAA2", "CAAAfrChangeViewNormalCmd", "CAAAfrGeometryWksHeader"]
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrCommandHeaders.htm"
converted: "2026-05-11T17:17:55.868797"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### The Command Headers

_Objects which stand for your dialog commands_
---|---|---
Technical Article

* * *
### Abstract

Command headers stand for commands in workshops and workbenches, and are loaded instead of the commands when the workshop or workbench itself is loaded. A given command is actually loaded when the end user clicks on its representation to execute it. This article explains how and where to create command headers, and how to use them. Reading the "Application Frame Overview" article [1] can be useful to take full benefit from this technical article. You will find a first approach of the command header concept, and how command header are involved in the frame architecture.

  * **Introduction**
  * **Command Header Management**
    * **Life Cycle**
    * **Workbench Loading Order**
    * **The Customize Command**
  * **Creating Standard Command Headers**
  * **Creating Customized Command Headers**
    * **Customized Command Header Class Structure**
    * **Managing Command Availability**
    * **Creating a  Customized Representation **
    * **Managing Contextual Help  **
  * **Re-Using Existing Command Headers**
    * **The Workshop Exposition Command **
    * **Reusability Rules**
  * **General Command Headers**
  * **References**
  * **In Short**

---

* * *
### Introduction

Each command you want to make available in your workshop or workbench must have a command header. The command header plays the role of your business card, which holds information such as your name, your company, your function within the company, the address where your company is located, your phone and fax numbers, and your e-mail id. This card is very useful to contact you when you are out the office, and requires a very small space. Like a business card, the **command header holds the necessary information** to load the command, such as the name of the shared library in which the command's executable code is located, the name of the command class, and the data to pass to the command code when this command becomes the current one.

Each command you want to make available in your workshop or workbench must have a command header. The command header plays the role of your business card, which holds information such as your name, your company, your function within the company, the address where your company is located, your phone and fax numbers, and your e-mail id. This card is very useful to contact you when you are out the office, and requires a very small space. Like a business card, the **command header holds the necessary information** to load the command, such as the name of the shared library in which the command's executable code is located, the name of the command class, and the data to pass to the command code when this command becomes the current one.
The **command header has resources** for each command to display, such as the command name shown to the end user, its ToolTip displayed in a balloon, its help message, and its icon. This enables the workshop or workbench to be displayed, that is loaded in memory, without any of its commands being itself loaded, except the default one, spares memory space, and improves performance. The end user can see the icons in the toolbars, the items in the menu bar, can ask for help on a given command, without loading any of its commands. It's only when the user clicks on the menu item or on the icon that the command code is actually loaded. The "Creating Resources for Command Headers" article [2] explains in details what are the command header resources and how to assign them to command headers.

Before taking up the sections detailing how to create a command header class, it is important to understand how the command header instances are **managed by the frame**. This is the main goal of the "Command Header's Management" section.

A command header instance is always an instance of a class deriving from the _CATCommandHeader_ class. In most cases, you can create this class in a  standard way using a macro. However, you can also explicitly create your class in order to manage the command availability, or to create a command header whose representation is customized. This is the topic of the Creating Customized Command Headers section.

Sometimes you would like to reuse commands in your workbench, but either you have no information about them, or you do not want to create a new command header instance to avoid losing resources. The Re-Using Existing Command Headers section first explains how to retrieve the command header instance associated with a command, and then draws your attention on how to reuse correctly an header instance.

At last, from R12 onwards, you can create command header instances available whatever the type of the opened document, or even if there is no opened document. There are further named **general** headers. You create them in implementations of the _CATIAfrGeneralWksAddin_ interface. Each implementation of this interface is an Add-in of the _CATAfrGeneralWks_ workshop, also named General workshop [2]. The General Command Headers section explains the specificities of these general headers, and how to create the command that they launch.

[Top]
### Command Headers Management

The goal of this paragraph is to explain the life cycle of a command header instance: who creates an instance and who deletes it. These explanations are illustrated by a schema Fig.1 ____ showing that all command header instances associated with a workshop are grouped together in a list. The Workbenches Loading Order paragraph explains how this list is filled up. In an interactive session, this list is displayed in the Command tab page of the Tools/Customize command. The Customize command paragraph gives you some information about the Command tab page and its contents.
#### Life Cycle

The goal of this paragraph is to explain the life cycle of a command header instance: who creates an instance and who deletes it. These explanations are illustrated by a schema Fig.1 ____ showing that all command header instances associated with a workshop are grouped together in a list. The Workbenches Loading Order paragraph explains how this list is filled up. In an interactive session, this list is displayed in the Command tab page of the Tools/Customize command. The Customize command paragraph gives you some information about the Command tab page and its contents.
A V5 document is controlled by an editor [3]. Each editor, a _CATFrmEditor_ class instance, keeps a list of command header instances. To be exact, the editor keeps a list of command header instances for each workshop [1] it can manage. This is illustrated by the picture hereunder.

_Fig.1 Command Header Instances Lists_ ![](images/CAAAfrCmdHdrLifeCycle.jpg)

---

  * When you open a Product document, the editor, named `Editor1`, has at first a list of command headers for the Product workshop (the first yellow list). If you edit a Part of the Product, in the same window, the Part workshop is loaded, and the editor manages a second list (the first dotted-green list).
  * When you open a second Product document, the editor, named `Editor2`, has at first a list of command headers for the Product workshop (the second yellow list). If you edit a Part of the Product, in the same window, the Part workshop is loaded, and the editor manages a second list (the second dotted-green list). If you edit a Sketch of the Part, always in the same window, the Sketcher workshop is loaded, and `Editor2 `manages a third list (the dashed-pink list)

Each list is filled at the _CATCommandHeader_ class **instantiation**. The new instance is inserted in the current list of the current editor. The _CATFrmEditor_ class manages the **destruction** of the _CATCommandHeader_ instances. When a document is closed, all its lists are deleted, and their content is also deleted.

To avoid filling up uselessly the list of _CATCommandHeader_ instances, it is recommended to make the command header instantiation only in the following methods because these methods are called once for each editor instance:

  * `CreateCommands` of the workbench implementations [4]
  * `CreateCommands` of the add-in implementations (*) [5]

(*) There is an exception for Add-ins of the CATAfrGeneralWks workshop. In this specific case, the `CreateCommands` method is called once during the life time of the session. Refer to the General Command Headers **** section which goes deeper for this specific case.

```vbscript
```vbscript
For commands implementing _CATIAfrCmdPaletteOptions_ [6] or workbenches implementing _CATIAfrPaletteOptions  _[7], the code creating command header instances should first verify that the header instance does not already exist into the list of the current editor. A call to the _CATAfrGetCommandHeader_ ` `global function, which retrieves a command header instance from its identifier, enables you check this. Keep in mind that these two interfaces enables you to set command header instances into the "Tools Palette" toolbar. But even if these headers are not created in a workbench or an add-in implementation, once created, they are kept, like the others, in the current list of the current editor.

```

```

#### Workbench Loading Order

```vbscript
For commands implementing _CATIAfrCmdPaletteOptions_ [6] or workbenches implementing _CATIAfrPaletteOptions  _[7], the code creating command header instances should first verify that the header instance does not already exist into the list of the current editor. A call to the _CATAfrGetCommandHeader_ ` `global function, which retrieves a command header instance from its identifier, enables you check this. Keep in mind that these two interfaces enables you to set command header instances into the "Tools Palette" toolbar. But even if these headers are not created in a workbench or an add-in implementation, once created, they are kept, like the others, in the current list of the current editor.
```

When an UI-active object is first UI-activated, the new list of command header instances is filled up in this order:

  1. The **general** command header instances. Those of DS ( New, Open), and those created in the `CreateCommands` of each _CATIAfrGeneralWksAddin_ implementation.
  2. The command header instances of the **workshop** implementation (DS code)
  3. All the command header instances created in **Add-ins** of the current **workshop** (mainly CAA code)
  4. The command header instances of the current **workbench** ( DS code or CAA code)
  5. All the command header instances created in **Add-ins** of the current **workbench** (mainly CAA code)

This means that once the document is opened, only a part of the command header instances are inside the list, since only one workbench has been loaded. The other workbenches and their associated add-ins are loaded only when a transition is invoked (Start menu for example).

The loading of all workbenches can be forced for the following reasons:

  * Launching the Customize command in the Tools menu,
  * Launching the Commands List in the View menu,
  * Opening a document which contains toolbars with unknown command header instances (coming from a workbench other than the current one). In the "Re-Using Existing Command Headers" section, you will see that this kind of management implies the respect of some rules when you when re-use command header instances.
  * Launching an unknown command in the power input.

#### The Customize Command

The Customize command enables you to customize the organization of your commands in the frame. The Customize Dialog box contains the Commands tab page, see Fig.2, which displays the available commands for the end user.

_Fig.2 Customize Command_ ![](images/CAAAfrCommandHeaderToolsCusto.jpg)
---

The Customize command enables you to customize the organization of your commands in the frame. The Customize Dialog box contains the Commands tab page, see Fig.2, which displays the available commands for the end user.
_Fig.2 Customize Command_ ![](images/CAAAfrCommandHeaderToolsCusto.jpg)
The command header instances displayed in the Commands tab page are **all** the command header instances associated with the current UI-active object since launching the Customize command invokes the re-loading of all workbenches. However there are two exceptions:

  1. Command header instances that a _CATIAfrCmdPaletteOptions_ or _CATIAfrPaletteOptions_ could have been created if they have been called.
  2. **Invisible** command header instances

Sometimes, it can be useful to hide headers to the end user. These can be internal headers, such as set and unset headers of a check header [17], or headers that you do not want the end user to drag and drop onto a toolbar [6].

However, a hidden header in the Command tab page is not "dead". If the end user knows its name, it can always use the power input to launch it, or you can use the _CATAfrStartCommand_ global function to do the same thing.

You can hide, or show again a header using the `SetVisibility` method of the _CATCommandHeader_ class.

[Top]
### Creating Standard Command Headers

You can hide, or show again a header using the `SetVisibility` method of the _CATCommandHeader_ class.
To create a standard command header class, you can use the `MacDeclareHeader` macro. It creates for you a class which derives from _CATCommandHeader_ which is the base class for command headers and should never be directly instantiated.

Let's assume you want to create a command header class named _CAAAfrCommandHeader_. You simply need to create a file, say CAAAfrCommandHeader.h, with the following code:

    #include "CATCommandHeader.h"

    **MacDeclareHeader**(CAAAfrCommandHeader);

---

This macro creates the _CAAAfrCommandHeader_ class declaration and implementation. To instantiate this command header for a command, you should simply use the following constructor created by the macro.

    #include "CAAAfrCommandHeader.h"

    new CAAAfrCommandHeader("CAAAfrMyCommandHdr",
                            "CAAAfrCommandLibName",
                            "CAAAfrCommandClass",
                            void * ipParameter);

---

where:

  * `CAAAfrMyCommandHdr` is the identifier you need to assign to the command header. It will be used afterwards to associate the command starters you will define to put the command in a menu and in toolbars with the command starter. This identifier is also used to build the variables defining the command header resources, such as the name seen by the end user in his/her own language in the menu, or the icon to display in a toolbar [2]
  * `CAAAfrCommandLibName` is the name of the shared library containing the code of the command, without the prefix lib, and without the suffix depending on the operating system
  * `CAAAfrCommandClass` is the name of the class you used to create the command
  * `ipParameter`, the last argument is the possible pointer to the object to pass to the command when starting it.

Different commands can share the same command header class to create their command headers. Refer to the use case that creates a workbench [4]. The following example shows how to create command header instances with and without an argument to pass to the command:

    void CAAAfrGeometryWks::CreateCommands()
    {
      ...
      // Case without argument
      new CAAAfrGeometryWksHeader("CAAAfrPointHdr",
                                  "CAADegGeoCommands",
                                  "CAADegCreatePointCmd",
                                  (void *) NULL);
      ...
      // Cases with argument
      new CAAAfrGeometryWksHeader("CAAAfrNormalXHdr",
                                  "CAAAfrGeoCommands",
                                  "CAAAfrChangeViewNormalCmd",
new CAAAfrGeometryWksHeader("CAAAfrNormalXHdr",
                                  (void *)CATINT32ToPtr(1));

      new CAAAfrGeometryWksHeader("CAAAfrNormalYHdr",

                                  "CAAAfrGeoCommands",
                                  "CAAAfrChangeViewNormalCmd",
(void *)CATINT32ToPtr(1));
new CAAAfrGeometryWksHeader("CAAAfrNormalYHdr",
                                  (void *)**CATINT32ToPtr**(2));

      new CAAAfrGeometryWksHeader("CAAAfrNormalZHdr",

                                  "CAAAfrGeoCommands",
                                  "CAAAfrChangeViewNormalCmd",
(void *)**CATINT32ToPtr**(2));
new CAAAfrGeometryWksHeader("CAAAfrNormalZHdr",
                                  (void *)CATINT32ToPtr(3));

---

(*) `CATINT32ToPtr` is to be 64 compliant.

[Top]
### Creating Customized Command Headers

There are two reasons to create a customized command header:

  1. When you want your command availability to depend on the context that is on what exists or what happens in the document.

```vbscript
```vbscript
For example, let's assume a command applies to a given object in a document. If one or several instances of this object exist in the document, the command can be used and should be available. On the opposite, if no instance of this object exists, the command cannot execute, and it should be set unavailable. Its representation in menus and toolbars should be grayed out, and nothing should happen when the end user clicks on it. A full example describes such a customized command header [8].

```

```

```vbscript
For example, let's assume a command applies to a given object in a document. If one or several instances of this object exist in the document, the command can be used and should be available. On the opposite, if no instance of this object exists, the command cannot execute, and it should be set unavailable. Its representation in menus and toolbars should be grayed out, and nothing should happen when the end user clicks on it. A full example describes such a customized command header [8].
  2. When you want to customize the representation of a command header.

```

Here are three examples:

_Fig.3 Examples of Customized Representations_ ![](images/CAAAfrCommandHeaderComboHdr.jpg) | It is a combo header. In place of the push button, the command header instance is represented by a combo. A full example describes its creation [9].

Here are three examples:
_Fig.3 Examples of Customized Representations_ ![](images/CAAAfrCommandHeaderComboHdr.jpg) | It is a combo header. In place of the push button, the command header instance is represented by a combo. A full example describes its creation [9].
 It is a "Most Recent Used" header. In place of a push item, the command header instance is represented by a dynamic list of push items (Item 1 and Item 2). When end users select one of them, a command is launched to display the selected item. Refer to the referenced use case for a complete description of such a command header. [10]
 Two editors in a toolbar. Refer to the referenced use case for more details [19].

#### Customized Command Header Class Structure

It is a "Most Recent Used" header. In place of a push item, the command header instance is represented by a dynamic list of push items (Item 1 and Item 2). When end users select one of them, a command is launched to display the selected item. Refer to the referenced use case for a complete description of such a command header. [10]
Two editors in a toolbar. Refer to the referenced use case for more details [19].
A customized command header class cannot be created using macros. The example below is a minimum customized command header class.

    #include <CATCommandHeader.h>

    class MyCustomizedCommandHeader : public **HdrBaseClass**
    {
      **CATDeclareClass;**
      **CATDeclareHeaderResources;**

class MyCustomizedCommandHeader : public **HdrBaseClass**
      public :
        MyCustomizedCommandHeader (const CATString & iHeaderName);
        virtual MyCustomizedCommandHeader ();
        CATCommandHeader * **Clone**();

      private :
        MyCustomizedCommandHeader (CATCommandHeader *ipHeaderToCopy);

        MyCustomizedCommandHeader ();
```vbscript
        MyCustomizedCommandHeader (const MyCustomizedCommandHeader &iObjectToCopy);

```

        ...
    };

---

The customized command header class should derive from a _CATCommandHeader_ class, so `HdrBaseClass`**** can be:

  * _CATCommandHeader_ class for a class only managing the command availability,
  * _CATAfrDialogCommandHeader_ for a class whose graphic representation is customized.

The customized command header class should derive from a _CATCommandHeader_ class, so `HdrBaseClass`**** can be:
It should include the `CATDeclareClass` and `CATDeclareHeaderResources` macros. `CATDeclareClass` declares that the _MyCustomizedCommandHeader_ class belongs to a CAA component, and `CATDeclareHeaderResources` inserts the methods to manage the command header resources. [2]

This class should also include in its **public** part:

  * A ` constructor` with a reference to a `const CATString` as parameter,
  * A `destructor`,
  * The ` clone` method inherited from _CATCommandHeader_ and used to duplicate the command header instance. This method is only used for general headers, those available whatever the document. For other command headers, the Life Cycle section has previously shown that the `CreateCommands` method is called to fill up each editor ists. However, it is strongly recommended to overwrite the ` clone` method for not pre-supposing the use of the command header class.

This class should also include in its **private** part:

  * A ` constructor` with a pointer to a _CATCommandHeader_ is dedicated to the `Clone` method.
  * Two other ` constructor`, declared, but not implemented in the source file. This prevents the compiler from creating them as public without you knowing.

Here is an example of implementation of the _MyCustomizedCommandHeader_ class.

    #include "MyCustomizedCommandHeader .h"
    ...
    **CATImplementClass**(MyCustomizedCommandHeader ,
Here is an example of implementation of the _MyCustomizedCommandHeader_ class.
                      Implementation,

                      **HdrBaseClass** ,
                      CATNull);

    **CATImplementHeaderResources**(MyCustomizedCommandHeader ,
                                **HdrBaseClass** ,
                                MyCustomizedCommandHeader );

    ...

---

The `CATImplementClass` macro states that the _MyCustomizedCommandHeader_ class OM-derives [11] from `HdrBaseClass``,`**** the base class, and is a component main class thanks to the `Implementation` keyword.

The `CATImplementClass` macro states that the _MyCustomizedCommandHeader_ class OM-derives [11] from `HdrBaseClass``,`**** the base class, and is a component main class thanks to the `Implementation` keyword.
The `CATImplementHeaderResources` macro is used in conjunction with the `CATDeclareHeaderResources` macro in the header file. It defines the command header resource file name [2]. The base class name set as second argument helps you use resource concatenation [12]. The third argument could be set to the name of another class associated with resource files using its class name, or to the name, without suffix, of an already existing resource file pair. Here it states that its associated resource file names use the class name: MyCustomizedCommandHeader.CATNls and MyCustomizedCommandHeader.CATRsc, respectively.

The constructor must call one of the constructors of the base class, and the destructor is empty.

    ...
    MyCustomizedCommandHeader ::MyCustomizedCommandHeader (const CATString &iHeaderName)
                                 : **HdrBaseClass**(...)

    {...}

    MyCustomizedCommandHeader ::MyCustomizedCommandHeader ()
    {}
    ...

---

The `Clone` method calls the constructor class with `this` as an argument. The constructor class with a _CATCommandHeader_ pointer is called. This constructor calls the same constructor of the base class.

    ...
The `Clone` method calls the constructor class with `this` as an argument. The constructor class with a _CATCommandHeader_ pointer is called. This constructor calls the same constructor of the base class.
    CATCommandHeader * MyCustomizedCommandHeader ::**Clone**()

    {
      return new MyCustomizedCommandHeader (this);
    }

CATCommandHeader * MyCustomizedCommandHeader ::**Clone**()
return new MyCustomizedCommandHeader (this);
    MyCustomizedCommandHeader ::MyCustomizedCommandHeader (CATCommandHeader * ipHeaderToCopy)

                                 : **HdrBaseClass**(ipHeaderToCopy)
    {}
    ...

---
#### Managing Command Availability

One good reason to create explicitly a command header is the need to manage the availability of the command represented by the header. [8].

    ...
    MyCustomizedCommandHeader ::MyCustomizedCommandHeader (const CATString &iHeaderName)
                                 : **HdrBaseClass**(...)
    {

MyCustomizedCommandHeader ::MyCustomizedCommandHeader (const CATString &iHeaderName)
```vbscript
        if ( condition )

```

          **BecomeAvailable**();
        else
          **BecomeUnavailable**();

        ::**AddCallback**(this,
else
                     publisher,

                    "NotifClassNameForAvailable",
publisher,
    		(CATSubscriberMethod)&MyCustomizedCommandHeader ::**AvailableCB** ,
                    NULL);

        ::**AddCallback**(this,
(CATSubscriberMethod)&MyCustomizedCommandHeader ::**AvailableCB** ,
NULL);
                     publisher,

                    "NotifClassNameForUnavailable",
NULL);
publisher,
    		(CATSubscriberMethod)&MyCustomizedCommandHeader ::**UnavailableCB** ,
                    NULL);

    }

---

The ` constructor` should initialize the command availability by appropriately calling the `BecomeAvailable` or `BecomeUnavailable` method. If several commands share the same command header class, each command should be examined individually.

In addition, the ` constructor` , and/or methods called by it, can set a callback on objects and events that can change the command availability. Methods called by these callbacks should of course be declared.

    ...
In addition, the ` constructor` , and/or methods called by it, can set a callback on objects and events that can change the command availability. Methods called by these callbacks should of course be declared.
    void MyCustomizedCommandHeader ::**UnavailableCB**(CATCallbackEvent iPublishedEvent ,
    		                          void   * iPublishingObject ,
    		                          CATNotification   * iNotif,
    				          CATSubscriberData   iUsefulData,
    					  CATCallback         iCallbackId)

    {
      **BecomeUnavailable**();
    }
CATSubscriberData   iUsefulData,
CATCallback         iCallbackId)
    void MyCustomizedCommandHeader ::**AvailableCB**(CATCallbackEvent iPublishedEvent ,
    		                          void   * iPublishingObject ,
    		                          CATNotification   * iNotif,
    				          CATSubscriberData   iUsefulData,
    					  CATCallback         iCallbackId)

    {
      **BecomeAvailable**();
    }
    ...

---
#### Creating a Customized Representation** **

Before detailing how to create such a command header, a global explanation is useful. Below is a diagram introducing the main objects.

![](images/CAAAfrCommandHeaderCustoHdrDiagram.jpg)
---

You retrieve the MVC model:

  * **M** : The data used by the graphic representations of the command header.

There are two cases to consider:

    * **Associated with a document instance**

> It means that the value of the data is linked to a document instance. When the end user switches between documents, the displayed values could be different. In the combo color example, the data can be the value of the current color. It could be also the available colors.
>
> If the data is persistent, the best storage file is the document.

    * **Independent of document instances**.

> It means that the data is valid whatever :
>     * The opened document: for example, the most recent opened documents in the File menu. The same list of documents is displayed, if no document is opened, or whatever the opened document.
>     * The type of document: for example, the option defined by the "Create Datum" command of the Part workbench. Whatever the opened Part document, the option is the same.
>
> In this case, the best storage file is a setting file.

  * **V** :**** The command header instance and its graphic representation.

> Each command header instance can be represented one or several times. Each representation is the association of the command header instance with a starter. You do it in a workbench or in an Add-in, but the end user can interactively do it, by dragging and dropping a command (header) onto a toolbar.

  * **C** :  The data controller

It is a component that must control the data in memory. It must:

    * **Provide** the data from the file
    * **Save** the modified data in the file
    * **Inform** all the viewers (headers) when the data is modified
      * From a viewer: if the end user modifies a graphic representation: e.g. changes the state of a check button, changes the selected color of a combo, ....
      * From an application which directly modifies the data

Here is an example with the combo header:

![](images/CAAAfrCommandHeaderComboMAJ.jpg)

The customized command header is a component [17]. Here is its UML diagram:

![](images/CAAAfrCommandHeaderUMLHdr.jpg)
---

`MyHeader`, the component representing the customized command header Object Modeler [11] and C++ derives from the _CATAfrDialogCommandHeader_ component.

This component must implement the _CATIAfrCommandHeaderRep_ interface. This interface has three methods: `CreateToolbarRep`, `CreateMenuRep`, and `CreateCtxMenuRep`. Each method corresponds to the container where the starter associated with the command header instance is included. The invoked method instantiates a class which creates the graphic representation. Below is the UML diagram of the class creating the graphic representation:

![](images/CAAAfrCommandHeaderUMLRep.jpg)
---

_MyRep_ is a class which derives from the _CATAfrCommandHeaderRep_ class. The main roles of this class are:

  * Setting a callback [18] on the component controlling the data
  * Instantiating one or more graphic representations ( Dialog components)
  * Updating the graphic representation (s) when the controller sends a notification when the data is modified.

#### Managing Contextual Help

The “More Info …” shortcut from the LongHelp message is available only if the Dialog (CATDlgxxx) object SetLongHelpId method was called. On Standard command headers SetLongHelpId is automatically called on the button using the LongHelpId resource of the command header. For customized command headers the command header does not know the Dialog objects so no SetLongHelpId is called. SetLongHelpId has to be called explicitely on the Dialog objects created to represent the customized command header.

    ...
    void MyCustomizedCommandHeader ::**Build**()
    {
    **

    ... pDialogItem->SetLongHelpId(pCustomizedCommandHeader->GetContextualHelp());
    **  ...
    }

---
### [Top]
### Re-Using Existing Command Headers

Until now, this article has explained how to create a command header instance to associate it with your own command. But sometimes you would like to re-use an existing command (_CATCommand_ ) without recreating a new command header instance:

  * You do not know the necessary information about this command (its class name, its dll name,...)
  * You do not want to lose the resources associated with an existing header.

Until now, this article has explained how to create a command header instance to associate it with your own command. But sometimes you would like to re-use an existing command (_CATCommand_ ) without recreating a new command header instance:
So you should be able to retrieve the identifier of a command header thanks to its NLS name. It is the one displayed in the Commands page of the Customize Command. The  Workshop Exposition Command resolves this problem.

However, once you have this identifier, before associating it with a starter, you should be aware of the workbench loading management. The rules to respect are detailed in the Reusability Rules paragraph.

#### The Workshop Exposition Command

So you should be able to retrieve the identifier of a command header thanks to its NLS name. It is the one displayed in the Commands page of the Customize Command. The  Workshop Exposition Command resolves this problem.
However, once you have this identifier, before associating it with a starter, you should be aware of the workbench loading management. The rules to respect are detailed in the Reusability Rules paragraph.
The frame application provides the "Workshop Exposition" command to give the command header identifiers. You launch it as explained in the following scenario:

Launch CATIA, then, when the application is ready,

  * enter **c: workshop exposition** in the power input or

  * From the **Tools** menu, click **Customize**
  * The**Customize** Dialog Box appears
    * Click the **Command** page
    * Click the **XCAA2** category
    * Drag and Drop the **Workshop Exposition** command onto a toolbar
    * Click **Close**
  * Launch the **Workshop Exposition** command

In the picture below, the current workshop is the **Part** workshop, and the current workbench is **Part Design**.

_Fig.5 The Workshop Exposition Command_ ![](images/CAAAfrCommandHeaderWshopExpo.jpg)
---

In the picture below, the current workshop is the **Part** workshop, and the current workbench is **Part Design**.
_Fig.5 The Workshop Exposition Command_ ![](images/CAAAfrCommandHeaderWshopExpo.jpg)
This Dialog command contains:

  * The **list** **of** **current entities**. This list is always arranged in the following order:
    * The workshop defined by the frame application (CATAfrGeneralWks)
    * The current workshop (the one of the current UI-active object)
    * The Add-ins of the current workshop
    * The current workbench
    * The Add-ins of the current workbench
  * The "**Directory** " editor to enter the path where the txt files will be generated.
  * The **Print** button enables you to generate the txt files for the selected entities. Each file is named `NameOfTheEntity.txt`, ex: ` CATAfrGeneralWks.txt`
  * The **OK** and **Cancel** Buttons close the Dialog box. Note, that to switch to another workbench, it is not necessary to close the command. The Workshop Exposition Dialog box will be automatically updated if a new workbench or a new workshop is activated.

The generated files contain two types of information, one being the list of the command header identifiers.  Here is an extract of the ` CATAfrGeneralWks.txt ` file:

![](images/CAAAfrCommandHeaderExtract.jpg)
---

where:

**Title** |  The Nls title of the command header instance
---|---
**Id** | The identifier of the command header instance
**DLL** | The library exporting the _CATCommand  _
**Cmd** | The _CATCommand_ to execute
**Arg** | The possible argument of the _CATCommand_

![](../CAAIcons/images/warning.gif)

  * Only the visible identifiers in the Commands tab page of the Customize command are generated in the txt files.
  * If you can safely reuse the identifier of a command header, there is no guaranty of stability with the other three parameters (DLL, Cmd, Arg).

#### Reusability Rules

Before associating any identifier with a starter, you must know that the workbenches (and their add-ins) are loaded when necessary. See the "Workbenches Loading Order" section. It means that, at a given time, all the command header identifiers defined in the workshop and its add-ins exist, but they are not necessary those of a workbench and its add-ins. The consequences are the followings:

  * Inside a workbench [4] (or add-in) [5]

When the entity (workbench/add-in) is loaded, if an identifier associated with a starter comes from a non-loaded workbench, all the workbenches will be loaded. The consequences are important because you lose the benefit of the partial workbench loading. Each time you open a document of this type, you will have the full loading.

  * Inside a contextual menu [13]

When the entity (workbench/add-in) is loaded, if an identifier associated with a starter comes from a non-loaded workbench, all the workbenches will be loaded. The consequences are important because you lose the benefit of the partial workbench loading. Each time you open a document of this type, you will have the full loading.
When the contextual menu is displayed, if an identifier associated with a starter comes from a non-loaded workbench, the starter will be not displayed.

It gives the following advices:

  * **Rule 1:** In a workbench or in an Add-in (workshop/workbench) avoid using an identifier coming from another workbench or from an add-in of another workbench.
  * **Rule 2 :** Into workbenches or contextual menus use identifiers coming from the workshop or one of its Add-ins. You can create, for example, an add-in of the workshop to group together the shared headers. This add-in will only contain command header instantiations, and will have no toolbar.

###  General Command Headers

The _CATIAfrGeneralWksAddin_ interface enables you to define an add-in of the General (CATAfrGeneralWks) workshop [14], in other words to define command headers and starters always available whatever the open document, or even if no document is open.

The _CATIAfrGeneralWksAddin_ interface enables you to define an add-in of the General (CATAfrGeneralWks) workshop [14], in other words to define command headers and starters always available whatever the open document, or even if no document is open.
The `CreateCommands` and `CreateToolbars` methods, the two methods of any Add-in interface, are called once during the session, when it starts. The command header instances created in the `CreateCommands` method are kept in a list (named `GeneralHdrList` on the Fig.6 ). This list is written in each list associated with an editor, and the headers are duplicated thanks to the `Clone` method.

_Fig.6_ ![](images/CAAAfrCommandHeaderGeneralAddin.jpg)

---

The `CreateCommands` and `CreateToolbars` methods, the two methods of any Add-in interface, are called once during the session, when it starts. The command header instances created in the `CreateCommands` method are kept in a list (named `GeneralHdrList` on the Fig.6 ). This list is written in each list associated with an editor, and the headers are duplicated thanks to the `Clone` method.
_Fig.6_ ![](images/CAAAfrCommandHeaderGeneralAddin.jpg)
When no document is open, a command is launched from a command header instance coming from the `GeneralHdrList` list. But if a document is open, the same command is launched from the command header instance coming from the list associated with the document editor. With this architecture, you can understand that even if the end user has the feeling that the icon representing the command is associated with the same object, in fact, swapping between documents or closing all of them, invokes different command header instances. What are the consequences:

  * For command headers launching a **shared** or **exclusive** command [15]

> If the header is started when no document is open, it comes from the GeneralHdrList, the shared or exclusive command will be deleted as soon as a document is opened.
>
> If the header is started when an editor is active, it comes from a list associated with this editor, the shared or exclusive command will be also deleted as soon as another editor is activated.
>
> Consequently, you do not encounter any problem,  the starter of the command header is always normal (not highlighted) in the list associated with the "leaving" editor because the command is always deleted before a swap. So after a swap, you retrieves always the state "normal" in any another list. You can re-launch the same command with another command header instance.
>
> In this situation, you also have the Dialog command with the `CATDlgWndModal` behavior. You have an example with the Add Item in MRU command of the CAAAfrMRUHeader use case [10]. The command is not described, but you will retrieve in this article the location of the code.

  * For command headers launching an **undefined** command [15]

> In most cases, this command is a _CATDlgDialog_ class. An example is the Search command, or the Workshop Exposition command.
>
> It is recommended to create a command header which launches a simple _CATCommand_ class. This class has no method. In the constructor class and in this order:
>
>   1. Create the Dialog box
>
> Take care of the Dialog parent - Refer to the technical article about the frame layout [3], and compare the difference between `GetMainWindow` and `GetApplicationDocument`, the two methods of _CATApplicationFrame_ class.
>
> The Dialog box must manage its life cycle. When the end user clicks the Close button, or the Close/Cancel buttons if they exist, the Dialog box is deleted (by a `RequestDelayedDestruction` on itself)
>
>   2. Call `RequestDelayedDestruction` on itself
>
> The "button" of the command header instance becomes "normal" (not highlighted anymore). The end user can re-launch the command, the Dialog box will appear twice, if the previous one has not been closed.
>
>

>
> This command class remaining undefined (do not use the `RequestStatusChange` method ), the current shared or exclusive command is not deleted.

  * For command headers using _CATAfrCheckHeaderAccessor_ [16]

Before using this class,  you should be aware of this behavior: if the check header is started when no document is open, the instance in GeneralHdrList is modified. When an editor is created, its header list is initialized with the content of GeneralHdrList, Fig.6, so the initial state of the header associated with an editor depends on the current state in GeneralHdrList. It's OK. But as long as an editor is active, if the end user clicks a check button, the header of the list associated with the current editor is modified. So if you change of current document, or if no documents are open anymore, the state of the check can be different: the state is not independent of the document. So if you want a check header be independent of the document instance, you can create a customized command header, which manages the refresh between all command header instances. Refer to the Creating Customized Representation section.

### [Top]

* * *
### In Short

A command header stands for a command and avoids loading the command when the end user does not require it. A command header is an instance of a command header class. This class can be used for several commands, and can be created either using a macro or explicitly if the command header should manage availability information or customize its representation.

A command header stands for a command and avoids loading the command when the end user does not require it. A command header is an instance of a command header class. This class can be used for several commands, and can be created either using a macro or explicitly if the command header should manage availability information or customize its representation.
It is possible to re-use command header identifiers, but there are two rules to respect:

  1. In a workbench or in an add-in (workshop/workbench) avoid using an identifier coming from another workbench or workbench's Add-in.
  2. In a contextual menu do not use an identifier coming from a workbench or a workbench Add-in, but only coming from the workshop or an workshop add-in.

The "Workshop Exposition" command enables you to retrieve the command header identifiers.

[Top]

* * *
### References

[1] | [Application Frame Overview](CAAAfrOverview.md)
---|---
[2] | [Creating Resources for Command Headers](CAAAfrI18NHeader.md)
[3] | [Understanding the Application Frame Layout](CAAAfrLayoutV5.md)
[4] | [Creating a Workbench](../CAAAfrUseCases/CAAAfrSampleWorkbench.md)
[5] | [Creating an Add-in](../CAAAfrUseCases/CAAAfrSampleAddin.md)
[6] | [Creating a Command with Options in the "Tools Palette" Toolbar](../CAAAfrUseCases/CAAAfrCmdPalette.md)
[7] | [Using the "Tools Palette" Toolbar for a Workbench](../CAAAfrUseCases/CAAAfrSamplePaletteWkb.md)
[8] | [Creating Customized Command Headers](../CAAAfrUseCases/CAAAfrSampleCustomCommandHeader.md)
[9] | [Creating a Combo Command Header](../CAAAfrUseCases/CAAAfrSampleComboHdr.md)
10] | [Creating a Most Recent Used Command Header](../CAAAfrUseCases/CAAAfrSampleMRUHdr.md)
[11] | [Object Modeler Inheritances](../CAASysTechArticles/CAASysOMInheritance.md)
[12] | [Assigning Resources to a Dialog Box](../CAADlgTechArticles/CAADlgResources.md)
[13] | [Inserting Commands in Contextual Menus](../CAAAfrUseCases/CAAAfrSampleContextualMenu.md)
[14] | [Making Your Document Independent Command Available in All Workbenches](../CAAAfrUseCases/CAAAfrSampleGeneralWksAddin.md)
[15] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
[16] | [Creating Check Button](../CAAAfrUseCases/CAAAfrCheckHeader.md)
[17] | [Creating a Component](../CAASysTechArticles/CAASysCreatingComponent.md)
[18] | [The Callback Mechanism](../CAASysTechArticles/CAASysCallbacks.md)
[19] | [Creating Editors in Toolbar](../CAAAfrUseCases/CAAAfrSampleEditorHdr.md)
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
Version: **1** [Jan 2000] | Document created
Version: **2** [Feb 2003] | Command header re-usage explanations
Version: **3** [Sep 2003] | Palette and General workshop add-in Integration
Version: **4** [Jan 2004] | Customized command header integration \+ a complete review

[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
