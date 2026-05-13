---
```vbscript
title: "Creating Customized Command Headers"
category: use-case case"
module: "CAAAfrUseCases"
tags: ["CAAFindP2", "CAAAfrDumpCommandHeader", "CAASysCollectionEmptyNotif", "CAAAfrGeometryWksHeader", "CAAAfrGeometryWks", "CATImplementHeaderResources", "CAAAfrGeometryWshop", "CAAGeometry", "CAAAfrGeoCommands", "CAASysCollectionFilledNotif", "CAAAfrDumpCmd", "CAAAfrDumpHdr", "CAAISysCollection", "CAAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleCustomCommandHeader.htmmd"
converted: "2026-05-11T17:17:55.679598"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Creating Customized Command Headers

_Exposing your commands and managing their availability_
---|---|---
Use Case

* * *
### Abstract

This article shows how to create a customized command header class to expose a command and manage its availability.

  * **What You Will Learn With This Use Case**
  * **The CAAAfrDumpCommandHeader Use Case**
    * What Does CAAAfrDumpCommandHeader Do
    * How to Launch CAAAfrDumpCommandHeader
    * Where to Find the CAAAfrDumpCommandHeader Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to create a customized command header class to expose a command and manage its availability.

[Top]
### The CAAAfrDumpCommandHeader Use Case

CAAAfrDumpCommandHeader is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does CAAAfrDumpCommandHeader Do

 The CAAAfrDumpCommandHeader use case creates command header class to manage the availability of the Element Count command. Element Count scans the active CAAGeometry document and prints in a dialog box a bill of the objects contained in the document. This makes sense only if the document is not empty, otherwise the command is made unavailable. The Element Count command availability is managed by its command header.
---|---

The CAAAfrDumpCommandHeader customized command header class plays the following roles:

  * It is a command header as those created using the `MacDeclareHeader` macro. This is possible by deriving the command header class from _CATCommandHeader_
  * It should in addition make the command available when the document contains at least one object, and unavailable otherwise. This is the role of the `BecomeAvailable` and `BecomeUnavailable` methods of _CATCommandHeader_.

[Top]
#### How to Launch CAAAfrDumpCommandHeader

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

```vbscript
Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

```

  * On the **File** menu, click **New**
  * In the **New** box, select **CAAGeometry** and click **OK**
  * Create several geometric objects such as points, lines, planes, and so on, using commands in the **Basic Elements** toolbar, or using the same commands in the **Insert** menu.
  * On the **Tools** menu, click **Element Count**. A dialog box displays the element count for each element type.
Note that if the document is empty, the **Element Count** command is greyed and cannot be triggerred.

[Top]
#### Where to Find the CAAAfrDumpCommandHeader Code

Note that if the document is empty, the **Element Count** command is greyed and cannot be triggerred.
The CAAAfrDumpCommandHeader use case is made of a single class named _CAAAfrDumpCommandHeader_ located in the CAAAfrGeometryWshop.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/`

The CAAAfrDumpCommandHeader use case is made of a single class named _CAAAfrDumpCommandHeader_ located in the CAAAfrGeometryWshop.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

CAAAfrDumpCommandHeader is part of the CAA Geometry Creation workshop where it is instantiated.

[Top]
### Step-by-Step

To create the command header for the Element Count command of the CAAAfrGeometryWshop workshop, there are six steps:
# | Step | Where
---|---|---
To create the command header for the Element Count command of the CAAAfrGeometryWshop workshop, there are six steps:
1 | Create the command header class header file | LocalInterfaces
2 | Declare the command header class resources | CAAAfrDumpCommandHeader.cpp
```vbscript
3 | Set the callbacks to appropriate events and initialize the command availability | Constructor
4 | Create the copy constructor, the Clone method, and the destructor | CAAAfrDumpCommandHeader.cpp
```
5 | Create the callback methods that manage the command availability | CAAAfrDumpCommandHeader.cpp
6 | Instantiate the command header class | CAAAfrGeometryWshop.m `CreateCommands` method
7 | Assign resources to the command header instance | Resource files

[Top]
#### Creating the Command Header Class

The CAAAfrDumpCommandHeader header file is as follows:

    #include <CATCommandHeader.h>
    ...
    class CAAAfrDumpCommandHeader : public **CATCommandHeader**
    {
      **CATDeclareClass** ;
      **CATDeclareHeaderResources** ;
class CAAAfrDumpCommandHeader : public **CATCommandHeader**
      public:

        CAAAfrDumpCommandHeader(const CATString & iHeaderName);
        virtual ~CAAAfrDumpCommandHeader(#);
        CATCommandHeader * **Clone**(#);

      private:

        **CAAAfrDumpCommandHeader**(CATCommandHeader *iHeaderToCopy);
virtual ~CAAAfrDumpCommandHeader(#);
CATCommandHeader * **Clone**(#);
private:
        CAAAfrDumpCommandHeader(const CAAAfrDumpCommandHeader &iObjectToCopy);
        void **AnalyzeFilledCB**(CATCallbackEvent     iPublishedEvent,
                             void              *  ipPublishingObject,
                             CATNotification   *  ipPublishNotification,
                             CATSubscriberData    iUsefulData,
                             CATCallback          iCallbackId);
        void **AnalyzeEmptyCB** (CATCallbackEvent     iPublishedEvent,
                             void              *  ipPublishingObject,
                             CATNotification   *  ipPublishNotification,
                             CATSubscriberData    iUsefulData,
                             CATCallback          iCallbackId);
      private:
        CAAISysCollection * _pCollection;

    };

---

CAAISysCollection * _pCollection;
_CAAAfrDumpCommandHeader_ derives from _CATCommandHeader_. The `CATDeclareClass` macro declares that it belongs to a CAA component. The `CATDeclareHeaderResources` macro inserts the methods to manage the command header resources.

About the mandatory public methods:

  * A `constructor` with a reference to a `const CATString` as parameter,
  * A `destructor`,
  * The `Clone` method inherited from _CATCommandHeader_ and used to duplicate the command header instance. Refer to the "Customized Command Header Class Structure" section of the technical article about the command headers [2]. You will have all the details about the `Clone` method.

About the mandatory private methods:

  * A `constructor` taking a pointer to a _CATCommandHeader_ is dedicated to the `Clone` method.
  * Two other `constructor` are declared in the private part, and are not implemented in the source file. This prevents the compiler from creating them as public without you know.

Two callback methods, `AnalyzeFilledCB` and `AnalyzeEmptyCB`, are declared to be called when the document contains objects or when it is empty respectively. `_pCollection` is a pointer to the collection of objects in the document, and is document dependent.

[Top]
#### Declaring the Command Header Class Resources

The CAAAfrDumpCommandHeader source file contains the resource declaration:

    ...
    **CATImplementClass**(CAAAfrDumpCommandHeader,**Implementation** , **CATCommandHeader** , CATNull);
    **CATImplementHeaderResources**(CAAAfrDumpCommandHeader,
                                CATCommandHeader,
                                CAAAfrDumpCommandHeader);
    ...

---

A customized command header is a CAA component. The `CATImplementClass` macro makes the class _CAAAfrDumpCommandHeader_ a component main class (`Implementation`) that OM-derives [1] from _CATCommandHeader_. The `CATImplementHeaderResources` macro is used in conjunction with the `CATDeclareHeaderResources` macro in the header file. It states that the _CAAAfrDumpCommandHeader_ class derives from _CATCommandHeader_ , and that its associated resource file names use the class name: CAAAfrDumpCommandHeader.CATNls and CAAAfrDumpCommandHeader.CATRsc respectively. The base class name set as second argument helps to use resource concatenation. The third argument could be set to the name of another class that is associated with resource files that use its class name, or to the name, without suffix, of an already existing resource file pair.

[Top]
#### Setting the Callbacks to the Appropriate Events and Initializing the Command Availability

This is done in the _CAAAfrDumpCommandHeader_ as follows:

    ...
    CAAAfrDumpCommandHeader::CAAAfrDumpCommandHeader(const CATString &iHeaderName)
                           : CATCommandHeader(iHeaderName,          // Command header id
                                              "CAAAfrGeoCommands",  // Command shared lib or DLL
                                              "CAAAfrDumpCmd",      // Command class
CAAAfrDumpCommandHeader::CAAAfrDumpCommandHeader(const CATString &iHeaderName)
                                              (void*) NULL),         // No parameter to pass to the command
                             _pCollection(NULL)

    {
     ...  // Get _pCollection
(void*) NULL),         // No parameter to pass to the command
_pCollection(NULL)
```vbscript
```vbscript
      if (NULL != _pCollection)

```

```

        ::**AddCallback**(this,
```vbscript
_pCollection(NULL)
```vbscript
if (NULL != _pCollection)
```

                      _pCollection,
```

                      "CAASysCollectionEmptyNotif",
```vbscript
if (NULL != _pCollection)
_pCollection,
                      (CATSubscriberMethod)&CAAAfrDumpCommandHeader::AnalyzeEmptyCB,
                      NULL);
```

        ::**AddCallback**(this,
_pCollection,
(CATSubscriberMethod)&CAAAfrDumpCommandHeader::AnalyzeEmptyCB,
NULL);
                      _pCollection,

                      "CAASysCollectionFilledNotif",
(CATSubscriberMethod)&CAAAfrDumpCommandHeader::AnalyzeEmptyCB,
NULL);
_pCollection,
                      (CATSubscriberMethod)&CAAAfrDumpCommandHeader::AnalyzeFilledCB,
                      NULL);

        int nbobject = 0;
        _pCollection->GetNumberOfObjects(&nbobject);

```vbscript
        if ( nbobject > 1 )

```

          **BecomeAvailable(#);**
int nbobject = 0;
_pCollection->GetNumberOfObjects(&nbobject);
if ( nbobject > 1 )
        else

          **BecomeUnavailable(#);**
      }
```vbscript
if ( nbobject > 1 )
else
      else
```

        **BecomeUnavailable(#);**
    }

else
    CAAAfrDumpCommandHeader::~CAAAfrDumpCommandHeader(#)

    {
      if ( NULL != _pCollection)
      {
         **RemoveSubscriberCallbacks**(_pCollection);
CAAAfrDumpCommandHeader::~CAAAfrDumpCommandHeader(#)
if ( NULL != _pCollection)
         _pCollection->Release(#);
         _pCollection = NULL ;

      }
    ...

---

The constructor first retrieves a pointer to a collection interface that manages the objects in the document. This is document implementation dependent. When the document is created or becomes empty, the collection sends a _CAASysCollectionEmptyNotif_ notification class instance. On the opposite, when the first object is created in the document, the collection sends a _CAASysCollectionFilledNotif_ notification class instance. A callback is set for each of these notifications thanks to the `AddCallback` global function, whose parameters are (for the first function call):

`this` | The object that executes the callback method
---|---
`_pCollection` | The object that sends the notification
`CAASysCollectionEmptyNotif` | The class name of the notification sent
`AnalyzeEmptyCB` | The method to call back
`NULL` | Possible useful data to pass to the method

The constructor finally asks the collection interface pointer to know whether the document is empty (An empty document contains at least one object: the UIactive object.) Depending on the answer, it initializes the command availability using the two methods `BecomeAvailable` and `BecomeUnavailable`. This is valid only at the command header class instantiation, and the callbacks will change this availability afterwards if needed.

Don't forget to remove the subscriptions in the destructor using the `RemoveSubscriberCallbacks` method.

[Top]
#### Creating the Copy Constructor, the Clone Method, and the Destructor

This is done in the _CAAAfrDumpCommandHeader_ as follows:

    ...
This is done in the _CAAAfrDumpCommandHeader_ as follows:
    CAAAfrDumpCommandHeader::CAAAfrDumpCommandHeader(CATCommandHeader * iHeaderToCopy)

                           : CATCommandHeader(iHeaderToCopy),
                             _pCollection(NULL)
    {}

CAAAfrDumpCommandHeader::CAAAfrDumpCommandHeader(CATCommandHeader * iHeaderToCopy)
_pCollection(NULL)
    CATCommandHeader * CAAAfrDumpCommandHeader::Clone(#)

    {
```vbscript
_pCollection(NULL)
CATCommandHeader * CAAAfrDumpCommandHeader::Clone(#)
      return new CAAAfrDumpCommandHeader(this);
```

    }

CATCommandHeader * CAAAfrDumpCommandHeader::Clone(#)
return new CAAAfrDumpCommandHeader(this);
    CAAAfrDumpCommandHeader::~CAAAfrDumpCommandHeader(#)

    {
return new CAAAfrDumpCommandHeader(this);
CAAAfrDumpCommandHeader::~CAAAfrDumpCommandHeader(#)
```vbscript
      if ( NULL != _pCollection)

```

      {
         **RemoveSubscriberCallbacks**(_pCollection);
CAAAfrDumpCommandHeader::~CAAAfrDumpCommandHeader(#)
if ( NULL != _pCollection)
         _pCollection->Release(#);
         _pCollection = NULL;

      }
    ...

---

The `Clone` method uses the copy constructor.

Don't forget to remove the subscriptions in the destructor using the `RemoveSubscriberCallbacks` method.

[Top]
#### Creating the Callback Methods that Manage the Command Availability

This is done in the _CAAAfrDumpCommandHeader_ as follows:

    ...
This is done in the _CAAAfrDumpCommandHeader_ as follows:
    void CAAAfrDumpCommandHeader::AnalyzeFilledCB(CATCallbackEvent    iPublishedEvent,
                                                  void              * ipPublishingObject,
                                                  CATNotification   * ipNotif,
                                                  CATSubscriberData   iUsefulData,
                                                  CATCallback         iCallbackId)

    {
      **BecomeAvailable**(#);
    }

CATCallback         iCallbackId)
    void CAAAfrDumpCommandHeader::AnalyzeEmptyCB (CATCallbackEvent    iPublishedEvent,
                                                  void              * ipPublishingObject,
                                                  CATNotification   * ipNotif,
                                                  CATSubscriberData   iUsefulData,
                                                  CATCallback         iCallbackId)

    {
      **BecomeUnavailable**(#);
    }

---

These two methods have the classical signatures of callback methods. Depending on the notification sent, they simply set the command availability accordingly.

[Top]
#### Instantiating the Command Header Class

To instantiate this command header, the `CreateCommands` method of the _CAAAfrGeometryWks_ workshop class should call its constructor with the command header identifier as parameter.

    void CAAAfrGeometryWks::**CreateCommands**(#)
    {
      ...
      new **CAAAfrDumpCommandHeader**("CAAAfrDumpHdr");
      ...

---

where `CAAAfrDumpHdr` is the identifier assigned to the command header. It will be used afterwards to associate the command starters defined to put the command in a menu and in toolbars with the command header. This identifier is also used to build the variables that define the command header resources, such as the name seen by the end user in his/her own language in the menu, or the icon to display in a toolbar.

[Top]
#### Assigning Resources to the Command Header Instance

The _CAAAfrDumpCommandHeader_ class is automatically associated with two resources files whose names are built using the class name:

  * CAAAfrDumpCommandHeader.CATNls for titles and help message that can be translated
  * CAAAfrDumpCommandHeader.CATRsc for other resources, such as the icons to display in the toolbars

The resources are designated using a key built as a concatenation of the command header class name, the command header instance identifier, and the resource keyword, separated by dots. The CAAAfrDumpCommandHeader.CATNls file includes the following for the Point command:

The resources are designated using a key built as a concatenation of the command header class name, the command header instance identifier, and the resource keyword, separated by dots. The CAAAfrDumpCommandHeader.CATNls file includes the following for the Point command:
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**Title**     = "Element Count...";
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**ShortHelp** = "Element Count";
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**Help**      = "Contents of the document";
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**LongHelp**  = "Element Count (Tools menu)
    This command enables the user to dump document contents";
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**Category**  = "Tools";

---

This command enables the user to dump document contents";
CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**Category**  = "Tools";
These resources are:

Title | Text displayed in the Tools menu for the command

These resources are:
Title | Text displayed in the Tools menu for the command
ShortHelp | Text displayed in a balloon as the command short help message when the mouse moves over the command when this command is in a toolbar. This is not applicable to commands located in the menu bar
Help | Text displayed in the status bar as the command help message when the mouse moves over the command. This is not applicable to commands located only in the menu bar, but is applicable for commands located in both the menu bar and a toolbar
LongHelp | Text displayed in a balloon when the end user clicks ![I_WhatsThisP2.gif /(235 bytes/)](images/I_WhatsThisP2.gif), which turns the mouse cursor as a question mark, and then clicks on the icon representing the command. This is not applicable to commands located in the menu bar
Category | An attribute associated with the command and used to sort the commands in the Commands tab page of the Customize window

The CAAAfrGeometryWksHeader.CATRsc file includes the following for the Point command:

    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**Icon.Normal**  = "I_CAAFindP2";
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**LongHelpId**   = "CAAAfrDumpCommandHeader.CAAAfrDumpHdr";

---

CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**Icon.Normal**  = "I_CAAFindP2";
CAAAfrDumpCommandHeader.CAAAfrDumpHdr.**LongHelpId**   = "CAAAfrDumpCommandHeader.CAAAfrDumpHdr";
These are the file names of the icons used to show the Element Count command in the toolbar:

Icon.Normal | Icon associated with the command and used in toolbars when the command is available. The greyed icon associated with the command when it is unavailable is computed from this one. In a P2 session, the shadowed icon displayed for default state and the Pressed and Focused icons are computed from the Normal one too.

These are the file names of the icons used to show the Element Count command in the toolbar:
Icon.Normal | Icon associated with the command and used in toolbars when the command is available. The greyed icon associated with the command when it is unavailable is computed from this one. In a P2 session, the shadowed icon displayed for default state and the Pressed and Focused icons are computed from the Normal one too.
LongHelpId |  | Identifier associated with the command and that calls the command help when the F1 key is pressed while the command is active

[Top]

* * *
### In Short

A command header stands for a command and avoids to load the command when the end user does not require it. A command header is an instance of a command header class. A customized command header created by deriving the _CATCommandHeader_ class can manage the command availability with respect to the document contents or to any other criterion using the `BecomeAvailable` and `BecomeUnavailable` methods.

[Top]

* * *
### References

[1] | [Object Modeler Component and Implementation Inheritances](../CAASysTechArticles/CAASysOMInheritance.md)
---|---
[2] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
Version: **2** [Feb 2004] | Document updated
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
