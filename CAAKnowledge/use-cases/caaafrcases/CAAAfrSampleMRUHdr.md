---
```vbscript
title: "Creating a Most Recent Used Command Header"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrGeneralWksAddinHeader", "CAAAfrMRUHeader", "CAAAfrMRUAddElementCmd", "CAAAfrComboColorHeader", "CAAAfrMRURep", "CAAAfrMRUManager", "CAAAfrGetMRUManager", "CAAEAfrCommandHeaderRepForMRU", "CATIAfrCommandHeaderRep", "CAAAfrMRUHdr", "CATIniCleanerSettingCtrl", "CATINT32ToPtr", "CATIWorkbenchAddin", "CAAAfrMRUSelElementHdr", "CAAAfrMRUNotification", "CATImplementHeaderResources", "CAAAfrGeoCommands", "CAAAfrGeneralWksAddin", "CAAAfrMRUManagerNotification"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleMRUHdr.htm"
converted: "2026-05-11T17:17:55.774532"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Creating a Most Recent Used Command Header

_How to create a command header class whose the representation is a dynamic list of items in a menu_
---|---|---
Use Case

* * *
### Abstract

This use case explains how to create a specialized command header. This command header has a customized graphic representation. In place of a push item into a menu, the graphic representation is a dynamic list of push items.

  * **What You Will Learn With This Use Case**
  * **The CAAAfrMRUHeader Use Case**
    * What Does CAAAfrMRUHeader Do
    * How to Launch CAAAfrMRUHeader
    * Where to Find the CAAAfrMRUHeader Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case illustrates the creation of a customized command header. In a menu, its graphic representation is a dynamic list of push items in place of a push item, the default representation. You will learn how to create a command header such as those which displays the most recent used document in the File menu. There are three steps:

  * Create the component representing the command header

> It is a component which must derive from the _CATAfrDialogCommandHeader_ class.

  * Create the component instantiating the graphic representation

> It is a component which must derive from the _CATAfrCommandHeaderRep_ class and which instantiates one or more _CATDlgPushItem_ class __ instances.

  * Create the component controlling the data used by the graphic representation

> The data is a list of strings. This list is independent of an instance of a V5 document. It means that whatever the current document, or even if any document is opened, the list of strings is the same.

You can also read the CAAAfrComboColorHeader use case [1] which presents another customized command header. In this case, the graphic representation is a combo in a toolbar. Contrarily to the current use case, the data (the current color) is dependent of the document.  To take full advantage of this article, you can first read "The Command Headers" technical article [2], and precisely the "Creating Customized Command Headers" section.   [Top]
### The CAAAfrMRUHeader Use Case

CAAAfrMRUHeader is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities [Top]
#### What Does CAAAfrMRUHeader Do

CAAAfrMRUHeader is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities [Top]
CAAAfrMRUHeader creates a command header whose the graphic representation is a list of push items in the File menu. Before to explain the construction of such a command header, see the following scenario which shows the end user view.

  1. Launch CNEXT
  2. Select **File** menu

 Above **Exit** , you have a separator, and just above it the "standard" most recent used documents.
  3. Launch **Add Item in MRU** in the **General** toolbar
 This toolbar comes from an Add-in of the General workshop. Refer to the referenced use case to display this toolbar [3]. The **Add Item in MRU** command is a _CATDlgDialog_ command.

Above **Exit** , you have a separator, and just above it the "standard" most recent used documents.
3. Launch **Add Item in MRU** in the **General** toolbar
This toolbar comes from an Add-in of the General workshop. Refer to the referenced use case to display this toolbar [3]. The **Add Item in MRU** command is a _CATDlgDialog_ command.
  4. The following Dialog box appears
 In the editor, enter **Item 1** , then click **OK**

This toolbar comes from an Add-in of the General workshop. Refer to the referenced use case to display this toolbar [3]. The **Add Item in MRU** command is a _CATDlgDialog_ command.
4. The following Dialog box appears
In the editor, enter **Item 1** , then click **OK**
  5. Select **File** menu
 Now, after **Exit** , you have a new push item, **Item 1**

In the editor, enter **Item 1** , then click **OK**
5. Select **File** menu
Now, after **Exit** , you have a new push item, **Item 1**
  6. Launch **Add Item in MRU**(![](images/CAAAfrSampleMRUMAddItem.jpg))**** in the **General** toolbar
 In the editor, enter **Item 2** , then click **OK**

Now, after **Exit** , you have a new push item, **Item 1**
6. Launch **Add Item in MRU**(![](images/CAAAfrSampleMRUMAddItem.jpg))**** in the **General** toolbar
In the editor, enter **Item 2** , then click **OK**
  7. Select **File** menu
 Now, after **Exit** , you have two push items:

     * In first position**Item 2** : the last created (used) item,
     * In second position **Item 1** : ****the oldest created (used) item
---|---
7. Select **File** menu
Now, after **Exit** , you have two push items:
  8. Select **Item 1**  in **File** menu
 The **Selected item** dialog box appears. It displays the selected item (**Item 1**).**** Close the dialog box.

8. Select **Item 1**  in **File** menu
The **Selected item** dialog box appears. It displays the selected item (**Item 1**).**** Close the dialog box.
  9. Select **File** menu
 Now, after **Exit** , you always have two push items, but observe the new order:

     * In first position**Item 1:** the last used item,
     * In second position **Item 2:** the oldest used item
---|---
9. Select **File** menu
Now, after **Exit** , you always have two push items, but observe the new order:
  10. On the **File** menu click **New  **
  11. **New** Dialog box click any kind document type and click **OK**
  12. Select **File** menu, you have the same list of items.

In this scenario, you can see that there is a **list of strings**(or item). About this list :

  * It is always empty at the beginning of the session (no file save in this use case)
  * It is filled up by the Add Item in MRU command
  * It is reorder to set in first position the selected string
  * It is independent of the document. Whatever the opened document, and even if no document is opened, the displayed list is the same.

This list (named MRU list) is kept by a component called CAAAfrMRUManager. It controls data (list of strings)**** which are displayed in the push items of a menu through the _CAAIAfrMRUManagement_ interface. Since, the MRU list is unique, this component is unique during the session.

Fig.1 Manager of the MRU List  ![](images/CAAAfrSampleMRU_UMLMgt.jpg)
---

This list (named MRU list) is kept by a component called CAAAfrMRUManager. It controls data (list of strings)**** which are displayed in the push items of a menu through the _CAAIAfrMRUManagement_ interface. Since, the MRU list is unique, this component is unique during the session.
Fig.1 Manager of the MRU List  ![](images/CAAAfrSampleMRU_UMLMgt.jpg)
The **MRU header** is an instance of a class deriving from the _CATAfrDialogCommandHeader_ class _,_ like any command header whose the graphic representation is customized. The following UML diagram describes in detail the schema of classes:

Fig.2 MRU Header UML Diagram ![](images/CAAAfrSampleMRU_UMLHdr.jpg)

---

The **MRU header** is an instance of a class deriving from the _CATAfrDialogCommandHeader_ class _,_ like any command header whose the graphic representation is customized. The following UML diagram describes in detail the schema of classes:
Fig.2 MRU Header UML Diagram ![](images/CAAAfrSampleMRU_UMLHdr.jpg)
CAAAfrMRUHeader is a component which must implement the _CATIAfrCommandHeaderRep_ interface to provide the customized graphic representation _._ This interface contains three methods:

  * `CreateCtxMenuRep` and `CreateToolbarRep` which return nothing
  * `CreateMenuRep`:

CAAAfrMRUHeader is a component which must implement the _CATIAfrCommandHeaderRep_ interface to provide the customized graphic representation _._ This interface contains three methods:
It instantiates an instance of the _CAAAfrMRURep_ class describes just below.

Fig.3 Command Header Graphic Representation UML Diagram ![](images/CAAAfrSampleMRU_UMLRep.jpg)

---

It instantiates an instance of the _CAAAfrMRURep_ class describes just below.
Fig.3 Command Header Graphic Representation UML Diagram ![](images/CAAAfrSampleMRU_UMLRep.jpg)
The _CAAAfrMRURep_ class creates one or more _CATDlgPushItem_ [4] class instance according to the contents of the list managed by the CAAAfrMRUManager component. The _CAAAfrMRURep_ class also sets a callback method to be informed when this list changes.

The MRU header is instantiated in an Add-in of the General workshop [3]. The last step of the Step by Step section explains this instantiation.

[Top]
#### How to Launch CAAAfrMRUHeader

The MRU header is instantiated in an Add-in of the General workshop [3]. The last step of the Step by Step section explains this instantiation.
To launch CAAAfrMRUHeader, you will need to set up the build time environment, then compile CAAAfrMRUHeader and CAAAfrGeneralWksAddin[3] along with their prerequisites, set up the run time environment, and then execute the use case [5].

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CNext\code\dictionary\`

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CNext\code\dictionary\`
UNIX | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`

In this file, remove the "**#** " character before the two following lines:

    ...
    #CAAAfrGeneralWksAddin       CATIWorkbenchAddin          libCAAAfrGeneralWksAddin
    #CAAAfrGeneralWksAddin       CATIAfrGeneralWksAddin      libCAAAfrGeneralWksAddin
    ...

---

and then run mkCreateRuntimeView.

[Top]
#### Where to Find the CAAAfrMRUHeader Code

and then run mkCreateRuntimeView.
The CAAAfrMRUHeader use case is made of several classes located in four modules of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu`

The CAAAfrMRUHeader use case is made of several classes located in four modules of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

The `CAAAfrCustCommandHdrModel.m` module contains classes to define the **CAAAfrMRUManager component** and the **notification** sent by this component.

  * CAAAfrMRUManagerNotification.h (LocalInterfaces) and CAAAfrMRUManagerNotification.cpp (src)

> The notification sent when an element is added in the list, or when an element is selected (to become the first in the list)

  * CAAIAfrMRUManagement.cpp (src), CAAIAfrMRUManagement.h (PublicInterfaces), and TIE_CAAIAfrMRUManagement.tsrc (src)

> Interface to add an element, select one, retrieve the list.

  * CAAAfrMRUManager.h (LocalInterfaces) and CAAAfrMRUManager.cpp (src)

> The CAAAfrMRUManager component itself which implements the _CAAIAfrMRUManagement_ interface.

  * CAAAfrGetMRUManager.cpp (src), CAAAfrGetMRUManager.h (PublicInterfaces)

> The global function to retrieve the unique CAAAfrMRUManager component during the session.

The `CAAAfrCustomizedCommandHeader.m` module contains classes to define the **MRU heade** r:

  * CAAAfrMRURep.h (LocalInterfaces) and CAAAfrMRURep.cpp (src)
  * CAAEAfrCommandHeaderRepForMRU.h (LocalInterfaces) and CAAEAfrCommandHeaderRepForMRU.cpp (src)
  * CAAAfrMRUHeader.cpp (src),  CAAAfrMRUHeader.h (PrivateInterfaces)

The `CAAfrGeoCommands.m` ****module contains** _CATCommand_ **classes

  * CAAAfrMRUAddElementCmd.h (LocalInterfaces) and CAAAfrMRUAddElementCmd.cpp (src)

> It is a _CATDlgDialog_ class (see image)  executed when the end user clicks the "Add Item in MRU" command in the General toolbar.

  * CAAAfrMRUSelElementCmd.h (LocalInterfaces) and CAAAfrMRUSelElementCmd.cpp (src)

> It is a C _ATDlgDialog_ class (see image) executed when the end user selects an item among the MRU list.

The `CAAAfrGeneralWksAddin.m` module contains an Add-in of the General workshop

  * CAAAfrGeneralWksAdn.h (LocalInterfaces) and CAAAfrGeneralWksAdn.cpp (src)

[Top]
### Step-by-Step

There are four logical steps in CAAAfrMRUHeader:

There are four logical steps in CAAAfrMRUHeader:
  1. Creating the CAAAfrMRUManager Component
  2. Creating the Component Representing the MRU Command Header
  3. Creating the Class Instantiating the Graphic Representation
  4. Instantiating the MRU Header Class

[Top]
#### Creating the CAAAfrMRUManager Component

The CAAAfrMRUManager component controls the MRU list to display in a menu. This list is managed through the _CAAIAfrMRUManagement_ interface _._ The explanations about the creation of this interface are not given in this article, refer to the Creating Interfaces use case for more details [6].

    ...
    #define MRU_MAX_SIZE 5

    class  CAAAfrMRUManager : public CATBaseUnknown
    {
class  CAAAfrMRUManager : public CATBaseUnknown
       CATDeclareClass;

       public:

       CAAAfrMRUManager();
       virtual ~CAAAfrMRUManager();

       static HRESULT **GetMRUManager**(CAAAfrMRUManager ** oManager);

       virtual HRESULT **AddElement**(CATUnicodeString &iNewElement) ;
       virtual HRESULT **GetElementList**(CATListOfCATUnicodeString &ElementList) const  ;
       virtual HRESULT **SelectElement**(int iPosition) ;

     private:

       CAAAfrMRUManager(const CAAAfrMRUManager &iObjectToCopy);
       CAAAfrMRUManager & operator = (const CAAAfrMRUManager &iObjectToCopy);

     private:
       static **CATIniCleanerSettingCtrl** _Cleaner ;

       CATListOfCATUnicodeString       _NameList;

    };

---

  * The _CAAAfrMRUManager_ class derives from CATBaseUnknown - Fig.1 -
  * The `CATDeclareClass` macro declares that it belongs to a CAA component.
  * **`GetMRUManager`** is a static method to have only one CAAAfrMRUManager component during the session. The list is unique whatever the opened document, or even if no document is opened.
  * `AddElement`, `GetElementList` and `SelectElement` are methods of the****_CAAIAfrMRUManagement_ interface
  * `Copy constructor` and the `assignment operator` are not implemented in the source file. This prevents the compiler from creating them as public without you know.
  * `_Cleaner` keeps the pointer on the unique CAAAfrMRUManager component instance. When the session is killed, the `_Cleaner` instance is removed, and the _CAAAfrMRUManager_ class pointer is released. It avoids to have "MLK". In your own code, the static data can be directly the pointer on the _CAAAfrMRUManager_ class instance.
  * `_NameList` is a list of _CATUnicodeString_. This list is limited to five elements (`MRU_MAX_SIZE = 5`)

The source file of the _CAAAfrMRUManager_ class is as follows:

    ...
    **CATIniCleanerSettingCtrl** CAAAfrMRUManager::_Cleaner ;

    **CATImplementClass**(CAAAfrMRUManager, **Implementation** , CATBaseUnknown , CATNull);
    #include <TIE_CAAIAfrMRUManagement.h>
    TIE_**CAAIAfrMRUManagement**(CAAAfrMRUManager);

TIE_**CAAIAfrMRUManagement**(CAAAfrMRUManager);
    CAAAfrMRUManager::CAAAfrMRUManager() {}
    CAAAfrMRUManager::~CAAAfrMRUManager(){}

    ...

---

  * `_Cleaner` is initialized
  * The `CATImplementClass` macro makes the class _CAAAfrMRUManager_ a component main class (`Implementation`) that OM-derives [11] from _CATBaseUnknown._
  * The _CAAAfrMRUManager_   class states that it implements the _CAAIAfrMRUManagement_ __ interface thanks to the `TIE_CAAIAfrMRUManagement`` `macro.

    ...
    HRESULT CAAAfrMRUManager::GetMRUManager(CAAAfrMRUManager ** oManager)
    {
     ...
HRESULT CAAAfrMRUManager::GetMRUManager(CAAAfrMRUManager ** oManager)
          CATBaseUnknown * pManager = _Cleaner.**GetController**();
```vbscript
          if ( NULL == pManager )

```

          {
CATBaseUnknown * pManager = _Cleaner.**GetController**();
if ( NULL == pManager )
              CAAAfrMRUManager * Obj = NULL;
              Obj = new **CAAAfrMRUManager**();
```vbscript
```vbscript
              if ( NULL == Obj )

```

```

              {
CAAAfrMRUManager * Obj = NULL;
Obj = new **CAAAfrMRUManager**();
```vbscript
if ( NULL == Obj )
```

                 rc = E_OUTOFMEMORY ;

              }else
              {
                ***oManager** = Obj ;
                _Cleaner.**SetController**(Obj);
              }
           }else
           {
              ***oManager** = (CAAAfrMRUManager *) pManager ;
           }
    ...

---

The `GetMRUManager` method creates the only one instance of the _CAAAfrMRUManager_ class or retrieves the existing one. `_Cleaner` is a static data member, a  _CATIniCleanerSettingCtrl_ class instance. If the `GetController` method of the _CATIniCleanerSettingCtrl_ class returns a null pointer, a _CAAAfrMRUManager_ class instance is created, and kept by `_Cleaner` through the `SetController` method. Otherwise the `GetMRUManager` method returns the pointer kept by `_Cleaner` and retrieved thanks to the `GetController` method.

Now, lets us see the three methods of the _CAAIAfrMRUManagement_ __ interface.

    ...
Now, lets us see the three methods of the _CAAIAfrMRUManagement_ __ interface.
    HRESULT CAAAfrMRUManager::AddElement(CATUnicodeString &iNewElement)

    {
        if ( MRU_MAX_SIZE == _NameList.Size() )
        {
            // The list is full, the last element is removed
HRESULT CAAAfrMRUManager::AddElement(CATUnicodeString &iNewElement)
if ( MRU_MAX_SIZE == _NameList.Size() )
           _NameList.**RemovePosition**(MRU_MAX_SIZE);

        }
        // At the first position
_NameList.**RemovePosition**(MRU_MAX_SIZE);
        _NameList.**InsertBefore**(1,iNewElement);

        CATCallbackManager * pCBManager = ::**GetDefaultCallbackManager**(this) ;
```vbscript
        if ( NULL != pCBManager )

```

        {
_NameList.**InsertBefore**(1,iNewElement);
CATCallbackManager * pCBManager = ::**GetDefaultCallbackManager**(this) ;
if ( NULL != pCBManager )
             CAAAfrMRUManagerNotification * pNotification = new CAAAfrMRUManagerNotification();
             pCBManager->**DispatchCallbacks**(pNotification,this);
             pNotification->Release();

        }

CAAAfrMRUManagerNotification * pNotification = new CAAAfrMRUManagerNotification();
pCBManager->**DispatchCallbacks**(pNotification,this);
pNotification->Release();
        return S_OK ;

    }
    ...

---

```vbscript
While there are less than `MRU_MAX_SIZE` elements in the list, represented by `_NameList` the data member, the `AddElement` method just adds the new element (`iNewElement`) at the first position (`InsertBefore(1,...)`). But when there are already `MRU_MAX_SIZE` elements in the list, before adding the new element at the first position, the last element of the list is removed.

```

The second part of the `AddElement` method consists in to send a notification thanks to the callback manager [7]. So, all objects which will subscribe for this event, published by the MRU manager, will be informed and awaked. Refer to the callback use case [8], for explanations about the creation of a notification such as the _CAAAfrMRUManagerNotification_ class, and how to send a notification using the default callback manager.

    ...
The second part of the `AddElement` method consists in to send a notification thanks to the callback manager [7]. So, all objects which will subscribe for this event, published by the MRU manager, will be informed and awaked. Refer to the callback use case [8], for explanations about the creation of a notification such as the _CAAAfrMRUManagerNotification_ class, and how to send a notification using the default callback manager.
    HRESULT CAAAfrMRUManager::GetElementList(CATListOfCATUnicodeString & oElementList) const

    {
HRESULT CAAAfrMRUManager::GetElementList(CATListOfCATUnicodeString & oElementList) const
```vbscript
        for ( int i = 1 ; i <= _NameList.Size() ; i++)

```

        {
HRESULT CAAAfrMRUManager::GetElementList(CATListOfCATUnicodeString & oElementList) const
for ( int i = 1 ; i <= _NameList.Size() ; i++)
           oElementList.**Append**(_NameList[i]);

        }

```vbscript
for ( int i = 1 ; i <= _NameList.Size() ; i++)
oElementList.**Append**(_NameList[i]);
        return S_OK ;
```

    }
    ...

---

The `GetElementList` method returns the contents of the list of item kept by `_NameList` the data member. This method will be called by the MRU header to build its graphic representation. See the Creating the Class Instantiating the Graphic Representation step.

    ...
The `GetElementList` method returns the contents of the list of item kept by `_NameList` the data member. This method will be called by the MRU header to build its graphic representation. See the Creating the Class Instantiating the Graphic Representation step.
    HRESULT CAAAfrMRUManager::SelectElement(int iPosition)

    {
HRESULT CAAAfrMRUManager::SelectElement(int iPosition)
        HRESULT rc = E_FAIL ;

```vbscript
        if ( (iPosition >= 1) && (iPosition <= MRU_MAX_SIZE) )

```

        {
HRESULT rc = E_FAIL ;
if ( (iPosition >= 1) && (iPosition <= MRU_MAX_SIZE) )
            CATUnicodeString Sel = _NameList[iPosition] ;

           _NameList.**RemovePosition**(iPosition);

           _NameList.**InsertBefore**(1,Sel);

           CATCallbackManager * pCBManager = ::**GetDefaultCallbackManager**(this) ;

           ...
_NameList.**InsertBefore**(1,Sel);
CATCallbackManager * pCBManager = ::**GetDefaultCallbackManager**(this) ;
              CAAAfrMRUManagerNotification * pNotification = new CAAAfrMRUManagerNotification();

              pCBManager->**DispatchCallbacks**(pNotification,this);

              pNotification->Release();
              pNotification = NULL ;

    ...

---

The `SelectElement` method consists in to set at the first position the `iPosition` element of the list. So the element is first removed from the list (`RemovePosition`),**** and then reinserted at the first position (`InsertBefore``)`.

[Top]
#### Creating the Component Representing the MRU Command Header

The MRU header is a component which must Object Modeler and C++ derive from _CATAfrDialogCommandHeader_ and must implement the _CATIAfrCommandHeaderRep_ interface (Fig.2).
##### **Component Creation**

Here the CAAAfrMRUHeader header file:

    //ApplicationFrame framework
    #include "CATAfrDialogCommandHeader.h"

    class ExportedByCAAAfrCustomizedCommandHeader CAAAfrMRUHeader: public **CATAfrDialogCommandHeader**
    {
class ExportedByCAAAfrCustomizedCommandHeader CAAAfrMRUHeader: public **CATAfrDialogCommandHeader**
      CATDeclareClass ;

      public:
        CAAAfrMRUHeader(const CATString & iHeaderName);

        virtual ~CAAAfrMRUHeader();
        CATCommandHeader * **Clone**() ;

      private:

        **CAAAfrMRUHeader(CATCommandHeader *iHeaderToCopy);**
virtual ~CAAAfrMRUHeader();
CATCommandHeader * **Clone**() ;
private:
        CAAAfrMRUHeader(const CAAAfrMRUHeader & iObjectToCopy);
        CAAAfrMRUHeader& operator = (const CAAAfrMRUHeader & iObjectToCopy);

    };

---

_CAAAfrMRUHeader_ derives from _CATAfrDialogCommandHeader_. It is mandatory for a command header whose the graphic representation is customized. The `CATDeclareClass` macro declares that it belongs to a CAA component. The `CATDeclareHeaderResources` macro inserts the methods to manage the command header resources.

About the mandatory public methods:

  * A `constructor` with a reference to a `const CATString` as parameter,
  * A `destructor`,
  * The `Clone` method inherited from _CATCommandHeader_ and used to duplicate the command header instance. Refer to the "Customized Command Header Class Structure" section of the technical article about the command headers [2]. You will have all the details about the `Clone` method.

About the mandatory private methods:

  * A `constructor` taking a pointer to a _CATCommandHeader_ is dedicated to the `Clone` method.
  * Two other `constructor` are declared in the private part, and are not implemented in the source file. This prevents the compiler from creating them as public without you know.

Here the CAAAfrMRUHeader header file:

    #include "CAAAfrMRUHeader.h"

Here the CAAAfrMRUHeader header file:
    CATImplementClass(CAAAfrMRUHeader,
                      Implementation,
                      CATAfrDialogCommandHeader,
                      CATNull);

    CAAAfrMRUHeader::CAAAfrMRUHeader(const CATString & iHeaderName) :

        **CATAfrDialogCommandHeader**(iHeaderName){}

CATNull);
CAAAfrMRUHeader::CAAAfrMRUHeader(const CATString & iHeaderName) :
    CAAAfrMRUHeader::CAAAfrMRUHeader(){}

    CATCommandHeader * CAAAfrMRUHeader::**Clone** ()

    {
CAAAfrMRUHeader::CAAAfrMRUHeader(){}
CATCommandHeader * CAAAfrMRUHeader::**Clone** ()
        return new CAAAfrMRUHeader(this);

    }

CATCommandHeader * CAAAfrMRUHeader::**Clone** ()
return new CAAAfrMRUHeader(this);
    CAAAfrMRUHeader::CAAAfrMRUHeader(CATCommandHeader * iHeaderToCopy):

                              **CATAfrDialogCommandHeader**(iHeaderToCopy)
    {}

---

  * A customized command header is a CAA component. The `CATImplementClass` macro makes the class _CAAAfrMRUHeader_ a component main class (`Implementation`) that OM-derives [11] from _CATAfrDialogCommandHeader_.
  * The `Clone` method returns a copy construction instance of this.

Note: There is no `CATDeclareHeaderResources` macro in the header file, and neither `CATImplementHeaderResources` macro in the source file. There is no NLS resources for this header [10].

**_CATIAfrCommandHeaderRep_ implementation**

This interface of the ApplicationFrame framework must be implemented by all command header whose the graphic representation is customized. On Fig.2, you see that the _CAAEAfrCommandHeaderRepForMRU_ class is the implementation of this interface for the CAAAfrMRUHeader component.

Here the CAAEAfrCommandHeaderRepForMRU header file

    ...
Here the CAAEAfrCommandHeaderRepForMRU header file
    class CAAEAfrCommandHeaderRepForMRU : public CATBaseUnknown

    {
class CAAEAfrCommandHeaderRepForMRU : public CATBaseUnknown
      CATDeclareClass;

    public:
      CAAEAfrCommandHeaderRepForMRU ();
      virtual ~CAAEAfrCommandHeaderRepForMRU();

      virtual HRESULT  **CreateToolbarRep** (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      virtual HRESULT  **CreateMenuRep**    (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;
      virtual HRESULT  **CreateCtxMenuRep** (const CATDialog * iParent,
                                                CATAfrCommandHeaderRep ** oHdrRep) ;

    private:
      CAAEAfrCommandHeaderRepForMRU (const CAAEAfrCommandHeaderRepForMRU &iObjectToCopy);
      CAAEAfrCommandHeaderRepForMRU & operator = (const CAAEAfrCommandHeaderRepForMRU &iObjectToCopy);

    };

---

The `CATDeclareClass` macro declares that _CAAEAfrCommandHeaderRepForMRU_ belongs to a component. `CreateToolbarRep`, `CreateMenuRep`, and `CreateCtxMenuRep` are methods of the _CATIAfrCommandHeaderRep_ interface.

Here the CAAEAfrCommandHeaderRepForMRU __ source file

    ...
    #include <TIE_CATIAfrCommandHeaderRep.h>
Here the CAAEAfrCommandHeaderRepForMRU __ source file
    TIE_**CATIAfrCommandHeaderRep**(CAAEAfrCommandHeaderRepForMRU);

    CATImplementClass(CAAEAfrCommandHeaderRepForMRU,
                      DataExtension,
                      CATBaseUnknown,
                      CAAAfrMRUHeader);

    };
```vbscript
CATImplementClass(CAAEAfrCommandHeaderRepForMRU,
DataExtension,
CATBaseUnknown,
CAAAfrMRUHeader);
    CAAEAfrCommandHeaderRepForMRU::
               CAAEAfrCommandHeaderRepForMRU():CATBaseUnknown(){}

    CAAEAfrCommandHeaderRepForMRU::~CAAEAfrCommandHeaderRepForMRU){}
```

    ...

---

The _CAAEAfrCommandHeaderRepForMRU_ class states that it implements the _CATIAfrCommandHeaderRep_ __ interface thanks to the `TIE_CATIAfrCommandHeaderRep `macro. The `CATImplementClass` macro declares that the _CAAEAfrCommandHeaderRepForMRU_ class is a data extension, thanks to the `DataExtension` keyword, that extends CAAAfrMRUHeader. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.  The class constructor and the class destructor are empty.

    ...
The _CAAEAfrCommandHeaderRepForMRU_ class states that it implements the _CATIAfrCommandHeaderRep_ __ interface thanks to the `TIE_CATIAfrCommandHeaderRep `macro. The `CATImplementClass` macro declares that the _CAAEAfrCommandHeaderRepForMRU_ class is a data extension, thanks to the `DataExtension` keyword, that extends CAAAfrMRUHeader. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.  The class constructor and the class destructor are empty.
    HRESULT CAAEAfrCommandHeaderRepForMRU::**CreateMenuRep**
             (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)

    {
HRESULT CAAEAfrCommandHeaderRepForMRU::**CreateMenuRep**
(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
       HRESULT rc = E_FAIL ;

```vbscript
       if ( oHdrRep != NULL )

```

       {
HRESULT rc = E_FAIL ;
if ( oHdrRep != NULL )
          CATString Name = "CAAAfrMRURepId"  ;
          CAAAfrMRURep * pMRURep = new **CAAAfrMRURep**(iParent,Name);

          *oHdrRep = (CATAfrCommandHeaderRep *) pMRURep ;
CATString Name = "CAAAfrMRURepId"  ;
CAAAfrMRURep * pMRURep = new **CAAAfrMRURep**(iParent,Name);
          rc = S_OK ;

       }

       return rc ;
    }
    ...

---

The `CreateMenuRep` method provides the class instantiating the graphic representation of the MRU header. This method is called each time the header command must be represented in a menu.

The _CAAAfrMRURep_ class is a CATCommand class [Fig.3], which instantiates the graphic representation of the MRU header (_CATDlgPushItem_ instances). It is detailed in the Creating the Class Instantiating the Graphic Representation section, just below.

`iParent` is a _CATDialog_ component. It will be the dialog parent of all _CATDlgPushItem_ instances. `Name` is the command name of the _CAAAfrMRURep_ class instance. You can set the same identifier for all _CAAAfrMRURep_ class instances.

You do not have to take care of the _CAAAfrMRURep_ class instance destruction, the returned value, `oHdrRep` is kept by the frame application, and the deletion of this pointer is automatically done.

    ...
    HRESULT CAAEAfrCommandHeaderRepForMRU::
                 **CreateToolbarRep**(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
      return  **E_FAIL** ;
    }

    HRESULT CAAEAfrCommandHeaderRepForMRU::
              **CreateCtxMenuRep**(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
    {
      return **E_FAIL** ;
    }

---

The MRU header has no representation in the menu bar or in a contextual menu, so `CreateToolbarRep` and `CreateCtxMenuRep` return E_FAIL.

[Top]
#### Creating the Class Instantiating the Graphic Representation

This class is the _CAAAfrMRURep_ class. Its main roles are:

  * Set a callback to be informed when the contents or the order of the MRU list change
  * Create _CATDlgPushItem_ instances depending on the MRU list
  * Launch a command to display in a Dialog box (see picture) the selected item.

Here the CAAAfrMRURep header file:

    ...
    #define MRU_MAX_SIZE 5
Here the CAAAfrMRURep header file:
    class CAAAfrMRURep : public **CATAfrCommandHeaderRep**

    {
class CAAAfrMRURep : public **CATAfrCommandHeaderRep**
    public:
      CAAAfrMRURep (const CATDialog * iParent, CATString & iCommandName);
      virtual ~CAAAfrMRURep();

      HRESULT **Build**();

    private:
      void **SelectCB**(CATCommand * iPublishingCommand,
                    CATNotification * iNotification,
                    CATCommandClientData iData);

      void **ModifiedCB**(CATCallback       iEvent,
                      void            *       ,
                      CATNotification * iNotification,
                      CATCallbackEvent  iData,
    	         CATSubscriberData iCallBack);

      HRESULT **ModifyListItem**() ;

      CAAAfrMRURep (const CAAAfrMRURep &iObjectToCopy);
      CAAAfrMRURep & operator = (const CAAAfrMRURep &iObjectToCopy);

    private:
         CATDlgPushItem         * _pItemList[MRU_MAX_SIZE];
         CAAIAfrMRUManagement   * _pIAfrMRUManagement ;

    };

---

  * The _CAAAfrMRURep_ class derives from the _CATAfrCommandHeaderRep_ class. Fig.3

  * The `Build` method is a method of the _CATAfrCommandHeaderRep_ class. You must overwrite this method. In the _CATAfrCommandHeaderRep_ class it is a pure virtual method. This method is called by the frame application just after the _CAAAfrMRURep_ class instantiation, in other words just after the `CreateMenuRep` method call.

  * In private part:
    * The `SelectCB` method is a callback method when the end user selects an item in the dynamic list.
    * The `ModifiedCB` method is a callback method called when the data model sent a _CAAAfrMRUNotification_ notification. see the first step.
    * The `ModifyListItem` ****is called by`Build` and `ModifiedCB` methods to create or update the list of _CATDlgPushItem_ instances.
  * In data member
    * `_pItemList` a list of _CATDlgPushItem_ class instances created in the `ModifyListItem `method.
    * `_pIAfrMRUManagement` is a _CAAIAfrMRUManagement_ interface pointer on the _CAAAfrMRUManager_ component.

Here the CAAAfrMRURep source file:

  * The **constructor** class

First `_pItemList, `the data member which holds all pointers on _CATDlgPushItem_ class instances, is initialized.

        ...
First `_pItemList, `the data member which holds all pointers on _CATDlgPushItem_ class instances, is initialized.
        CAAAfrMRURep::CAAAfrMRURep(const CATDialog * iParent,CATString & iCommandName):
                         CATAfrCommandHeaderRep(iParent,iCommandName)

                        ,_pIAfrMRUManagement(NULL)
        {
CAAAfrMRURep::CAAAfrMRURep(const CATDialog * iParent,CATString & iCommandName):
CATAfrCommandHeaderRep(iParent,iCommandName)
```vbscript
```vbscript
           for ( int i = 0 ; i < MRU_MAX_SIZE ; i++ )

```

```

           {
```vbscript
CATAfrCommandHeaderRep(iParent,iCommandName)
```vbscript
for ( int i = 0 ; i < MRU_MAX_SIZE ; i++ )
```

              _pItemList[i] = NULL ;
```

           }
        ...

---

The second step consists in to retrieve the component which holds the MRU list. In the use case, it is the unique CAAAfrMRUManager component that you retrieve with the _CAAAfrGetMRUManager_ global function. The second argument of this method is a pointer on an interface implemented by the CAAAfrMRUManager component.

        ...
The second step consists in to retrieve the component which holds the MRU list. In the use case, it is the unique CAAAfrMRUManager component that you retrieve with the _CAAAfrGetMRUManager_ global function. The second argument of this method is a pointer on an interface implemented by the CAAAfrMRUManager component.
           HRESULT rc = ::**CAAAfrGetMRUManager**(IID_CAAIAfrMRUManagement,
                             (void**)&_pIAfrMRUManagement);

        ...

---

The last step consists in to set a callback method to be informed when the CAAAfrMRUManager component will send a _CAAAfrMRUManagerNotification_ notification, in other words when an element will be added in the list or an element will be selected.

        ...
           if ( SUCCEEDED(rc) )
           {
              ::**AddCallback**(this,
```vbscript
if ( SUCCEEDED(rc) )
                       _pIAfrMRUManagement,
```

        	           "CAAAfrMRUManagerNotification",
```vbscript
if ( SUCCEEDED(rc) )
_pIAfrMRUManagement,
        	            (CATSubscriberMethod)&CAAAfrMRURep::ModifiedCB,
        	            NULL);
```

           }
        }

---

`AddCallback` is a static global function whose the parameters are:

    * `this:` The subscriber
    * `_pIAfrMRUManagement`: The publisher
    * `CAAAfrMRUManagerNotification:`The notification class sent by the publisher
    * `ModifiedCB:`The method of this which is called when a _CAAAfrMRUManagerNotification_ notification _is sent_
    * `NULL**:**`No parameters for the callback method

  * The **destructor** class

        ...
        CAAAfrMRURep::~CAAAfrMRURep()
        {
           if ( NULL != _pIAfrMRUManagement )
           {
               ::**RemoveSubscriberCallbacks**(this, _pIAfrMRUManagement);
CAAAfrMRURep::~CAAAfrMRURep()
if ( NULL != _pIAfrMRUManagement )
               _pIAfrMRUManagement->Release();
               _pIAfrMRUManagement = NULL ;

           }

_pIAfrMRUManagement->Release();
_pIAfrMRUManagement = NULL ;
```vbscript
           for ( int i=0 ; i < MRU_MAX_SIZE ; i++)

```

           {
_pIAfrMRUManagement = NULL ;
for ( int i=0 ; i < MRU_MAX_SIZE ; i++)
```vbscript
```vbscript
               if ( NULL != _pItemList[i] )

```

```

               {
```vbscript
for ( int i=0 ; i < MRU_MAX_SIZE ; i++)
```vbscript
if ( NULL != _pItemList[i] )
```

                   _pItemList[i]->**RequestDelayedDestruction**();
                   _pItemList[i] = NULL ;
```

         ...

---

At the end, the callback set in the constructor must be removed from the callback manager [7], and all the _CATDlgPushItem_ instances must be released.

  * The **Build** method

You must overwrite this method. The goal of this method is to create the graphic representation and to initialize it. The `ModifyListItem` method does the work.

    ...
You must overwrite this method. The goal of this method is to create the graphic representation and to initialize it. The `ModifyListItem` method does the work.
    HRESULT  CAAAfrMRUoRep::Build()

    {
You must overwrite this method. The goal of this method is to create the graphic representation and to initialize it. The `ModifyListItem` method does the work.
HRESULT  CAAAfrMRUoRep::Build()
     ModifyListItem() ;

    }
    ...

---
  * The **ModifyCB** method

The `ModifyCB` method is called when the CAAAfrMRUManager component sends the _CAAAfrMRUManagerNotification_ notification. It informs the _CAAAfrMRURep_ class instance, that either a new item has been added, or an element has been selected. In both cases, the `ModifyListItem` method does the work.

        ...
The `ModifyCB` method is called when the CAAAfrMRUManager component sends the _CAAAfrMRUManagerNotification_ notification. It informs the _CAAAfrMRURep_ class instance, that either a new item has been added, or an element has been selected. In both cases, the `ModifyListItem` method does the work.
        void CAAAfrMRURep::ModifiedCB(CATCallback,
                                      void *,
                                      CATNotification * iNotification,
        			   CATCallbackEvent,
                                      CATSubscriberData)

        {
void *,
CATNotification * iNotification,
CATCallbackEvent,
CATSubscriberData)
           ModifyListItem();

        }
        ...

---
  * The **ModifyListItem** method

This method can be called by the `Build` Method, in this case any push item has already been created, or by the `ModifyCB` method and in this case some push items can already exist. This method consists in to:
    * Retrieve from the CAAAfrMRUManager component the list of items to display,
    * Check that there are as many instances of _CATDlgPushItem_ in the `_pItemList` list as in the list of items to display,
    * Associate the title to each _CATDlgPushItem_

The first step consists in to retrieve the Dialog parent of the graphic representation to create. This information is kept by the _CATAfrCommandHeaderRep_ class, and retrieved by its `GetDialogParent` method.

    ...
The first step consists in to retrieve the Dialog parent of the graphic representation to create. This information is kept by the _CATAfrCommandHeaderRep_ class, and retrieved by its `GetDialogParent` method.
    HRESULT CAAAfrMRURep::ModifyListItem()

    {
The first step consists in to retrieve the Dialog parent of the graphic representation to create. This information is kept by the _CATAfrCommandHeaderRep_ class, and retrieved by its `GetDialogParent` method.
HRESULT CAAAfrMRURep::ModifyListItem()
      const CATDialog * pParent = NULL ;

      **GetDialogParent**(&pParent);
    ...

---

Then, the list of item to displayed is retrieved from the CAAAfrMRUManager thanks to the `GetElementList` method  of the _CAAIAfrMRUManagement_ interface. `List` is this list, and `SizeList` is the count of element in this list.

    ...
Then, the list of item to displayed is retrieved from the CAAAfrMRUManager thanks to the `GetElementList` method  of the _CAAIAfrMRUManagement_ interface. `List` is this list, and `SizeList` is the count of element in this list.
          CATListOfCATUnicodeString List ;
          _pIAfrMRUManagement->**GetElementList**(List);
          int SizeList = List.**Size**();

    ...

---

Then, for the ith element of the list, if there is no _CATDlgPushItem_ instance at the ith position in `_pItemList`, the data member of the _CAAAfrMRURep_ class, a new instance is created:

    * `CATDlgPushItem`

The last argument of the _CATDlgPushItem_ class is the identifier of the dialog object. It is recommended to set as value a string with an index value. Here it is `MRUItem_num` where num is the index in the loop.

    * `AddAnalyseNotificationCB`

When an item in the menu is selected by the end user, the push item sends a _GetMenuIActivateNotification_ notification which will be processed in the SelectCB method to launch the command which displays the name of the selected item.

`CATINT32ToPtr` is the way to be 64 bits compliant.

    * `SetFather`

Finally, the _CATCommand_ parent of the push item is changed. By default, the command parent is the dialog parent, so it is `pParent`, the container in which the push item will be inserted. If you do not change the command parent, this, the current _CAAAfrMRURep_ instance, will do not receive the _GetMenuIActivateNotification_**** notification. Refer to the referenced article about the command tree [9].

    ...
Finally, the _CATCommand_ parent of the push item is changed. By default, the command parent is the dialog parent, so it is `pParent`, the container in which the push item will be inserted. If you do not change the command parent, this, the current _CAAAfrMRURep_ instance, will do not receive the _GetMenuIActivateNotification_**** notification. Refer to the referenced article about the command tree [9].
```vbscript
          for ( int i= 0 ; i < SizeList ; i++ )

```

          {
Finally, the _CATCommand_ parent of the push item is changed. By default, the command parent is the dialog parent, so it is `pParent`, the container in which the push item will be inserted. If you do not change the command parent, this, the current _CAAAfrMRURep_ instance, will do not receive the _GetMenuIActivateNotification_**** notification. Refer to the referenced article about the command tree [9].
for ( int i= 0 ; i < SizeList ; i++ )
             CATUnicodeString num;
             num.BuildFromNum(i+1);
```vbscript
             if ( _pItemList[i] == NULL )

```

             {
CATUnicodeString num;
num.BuildFromNum(i+1);
if ( _pItemList[i] == NULL )
                CATUnicodeString ItemName("**MRUItem_** ");

                **ItemName += num** ;

```vbscript
if ( _pItemList[i] == NULL )
CATUnicodeString ItemName("**MRUItem_** ");
                _pItemList[i] = new **CATDlgPushItem**((CATDialog *)pParent,
                                                    ItemName.CastToCharPtr());

```

                **AddAnalyseNotificationCB**(_pItemList[i],
_pItemList[i] = new **CATDlgPushItem**((CATDialog *)pParent,
ItemName.CastToCharPtr());
                                         _pItemList[i]->**GetMenuIActivateNotification**(),
                                        (CATCommandMethod)&CAAAfrMRURep::SelectCB,
                                        (CATCommandClientData) **CATINT32ToPtr**(i));

                _pItemList[i]->**SetFather**(this);

             }

    ...

---

Finally, for the ith element of `List,` the list kept by the CAAAfrMRUManager component and retrieved just above, there is a _CATDlgPushItem_ class instance into the `_pItemList` list, the data member of the _CAAAfrMRURep_ class. The title of the push item is the concatenation of the position of the element in the list and the name of the item. exemple: `2 MyItemName.` See the File Menu picture in the

    ...
Finally, for the ith element of `List,` the list kept by the CAAAfrMRUManager component and retrieved just above, there is a _CATDlgPushItem_ class instance into the `_pItemList` list, the data member of the _CAAAfrMRURep_ class. The title of the push item is the concatenation of the position of the element in the list and the name of the item. exemple: `2 MyItemName.` See the File Menu picture in the
             num += " ";
             num += List[i+1] ;
             _pItemList[i]->**SetTitle**(num);

    ...

---
  * The **SelectCB** method

The `SelectCB` method is called when the end user has selected an item among the displayed items. When an element of `_pItemList` sends a notification, this callback method is called. The goal of this method is double:
    * Retrieve the selected item

The `CATPtrToINT32`**** macro enables us to translate the data which is the argument of the `AddAnalyseNotificationCB` method. See just above.

    * Inform CAAAfrMRUManager that a given item has been selected

`_pIAfrMRUManagement` is a CAAIAfrMRUManagement interface pointer on the unique CAAAfrMRUManager  component of the session. This pointer, initialized in the constructor class, is a data member of the _CAAAfrMRURep_ class.

The `SelectElement` method, with `SelElement` as argument,  informs CAAAfrMRUManager that the element at the `SelElement `position has been selected. It can reorder its own list of items, and sends a notification. All _CAAAfrMRURep_ which have set a callback for a such notification, will may update their list of push items.

    * Launch the command which displays in a Dialog box  the selected item

The `CATAfrStartCommand` is a global function which enables us to launch a command header. This command header is identified by its name, `CAAAfrMRUSelElementHdr`. This command header instance has been created in the Add-in of the General workshop, see the next section for complete details about this command header instance.

    ...
The `CATAfrStartCommand` is a global function which enables us to launch a command header. This command header is identified by its name, `CAAAfrMRUSelElementHdr`. This command header instance has been created in the Add-in of the General workshop, see the next section for complete details about this command header instance.
    void CAAAfrMRURep::SelectCB(CATCommand      * iPublishingCommand,
                                CATNotification * iNotification,
    			                CATCommandClientData iData)

    {
void CAAAfrMRURep::SelectCB(CATCommand      * iPublishingCommand,
CATNotification * iNotification,
CATCommandClientData iData)
      int SelElement = **CATPtrToINT32**(iData) + 1;

      _pIAfrMRUManagement->**SelectElement**(SelElement);

      CATCommand * pCmd = NULL ;

      ::**CATAfrStartCommand**("CAAAfrMRUSelElementHdr",pCmd);
    ...

---

[Top]
#### Instantiating the MRU Header Class

The MRU header is independent of the document, so this header is instantiated in an Add-in of the General workshop [3]. Here is an extract of the _CAAAfrGeneralWksAdn_ class which is an implementation of the _CATIAfrGeneralWksAddin_ interface.

    ...
The MRU header is independent of the document, so this header is instantiated in an Add-in of the General workshop [3]. Here is an extract of the _CAAAfrGeneralWksAdn_ class which is an implementation of the _CATIAfrGeneralWksAddin_ interface.
    void CAAAfrGeneralWksAdn::CreateCommands()

    {
void CAAAfrGeneralWksAdn::CreateCommands()
      CATCommandHeader * pHdr = (CATCommandHeader*) new **CAAAfrMRUHeader**("CAAAfrMRUHdr");
      pHdr->**SetVisibility**(0);

    ...

---

The MRU command header is created using the constructor class. The most important thing in the usage of the `SetVisibility` method. This method of the _CATCommandHeader_ class allows us to hide the command header instance in the Tools/Customize command. This command displays a dialog box containing tab pages. One of them, the Command tab page, displays by category, all the "visible" command header instances. The two following pictures explains the difference when the `SetVisibility` method is used or not.

The MRU command header is created using the constructor class. The most important thing in the usage of the `SetVisibility` method. This method of the _CATCommandHeader_ class allows us to hide the command header instance in the Tools/Customize command. This command displays a dialog box containing tab pages. One of them, the Command tab page, displays by category, all the "visible" command header instances. The two following pictures explains the difference when the `SetVisibility` method is used or not.
 This picture shows the Command tab page of the Tools/Customize command. In the All Commands category, you see that the CAAAfrMRUHdr appears. To do that we have set a comment before the `SetVisibility`  instruction. The MRU header is without NLS resources [10], so the displayed name is the internal name of the command header instance (the argument of the constructor class).

The MRU command header is created using the constructor class. The most important thing in the usage of the `SetVisibility` method. This method of the _CATCommandHeader_ class allows us to hide the command header instance in the Tools/Customize command. This command displays a dialog box containing tab pages. One of them, the Command tab page, displays by category, all the "visible" command header instances. The two following pictures explains the difference when the `SetVisibility` method is used or not.
This picture shows the Command tab page of the Tools/Customize command. In the All Commands category, you see that the CAAAfrMRUHdr appears. To do that we have set a comment before the `SetVisibility`  instruction. The MRU header is without NLS resources [10], so the displayed name is the internal name of the command header instance (the argument of the constructor class).
 Now, using `SetVisibility` with `0` as argument, you can see that between Bulk Loading... and Capture,  CAAAfrMRUHdr is not there.

This picture shows the Command tab page of the Tools/Customize command. In the All Commands category, you see that the CAAAfrMRUHdr appears. To do that we have set a comment before the `SetVisibility`  instruction. The MRU header is without NLS resources [10], so the displayed name is the internal name of the command header instance (the argument of the constructor class).
Now, using `SetVisibility` with `0` as argument, you can see that between Bulk Loading... and Capture,  CAAAfrMRUHdr is not there.
The advantage to hidde a command header, is that the end user cannot drag and drop the command in a toolbar, or it cannot launch it from the power input since it do not know its name. But caution, `SetVisibility` method do not prohibit to launch the command header in the power input, if you know the name of the command header. For the MRU header, there is no effect since there is no _CATCommand_ associated with the MRU Header.

    ...
      pHdrMRU = (CATCommandHeader*) new CAAAfrGeneralWksAddinHeader("**CAAAfrMRUSelElementHdr** ",
                                 "CAAAfrGeoCommands",
                                 "CAAAfrMRUSelElementCmd",
pHdrMRU = (CATCommandHeader*) new CAAAfrGeneralWksAddinHeader("**CAAAfrMRUSelElementHdr** ",
                                 (void *) NULL);
      pHdrMRU->**SetVisibility**(0);

    ...

---

The next header instance name is `CAAAfrMRUSelElementHdr`. This header is a standard command header. So the _CAAAfrGeneralWksAddinHeader_ command header class is used to create an instance [3]. This instance launches the _CAAAfrMRUSelElementCmd_ command which is defined in the CAAAfrGeoCommands module of the CAAApplicationFrame.edu framework. This instance of command header is also hidden in Tools/Customize, because the use case want only to launch this command when the end user selects an item in the File Menu. But if you try to enter `CAAAfrMRUSelElementHdr` in the power input the Dialog command is lauched and the current item is displayed.

![](images/CAAAfrSampleMRUPowerCopy.jpg)
---

The last header about the MRU use case is the `CAAAfrMRUAddElementHdr`. It is a standard command header which launches the _CAAAfrMRUAddElementCmd_ command which is defined in the CAAAfrGeoCommands module of the CAAApplicationFrame.edu framework.

    ...
    new CAAAfrGeneralWksAddinHeader("CAAAfrMRUAddElementHdr",
                                 "CAAAfrGeoCommands",
                                 "CAAAfrMRUAddElementCmd",
                                 (void *) NULL);
    ...

---

In the CNext/resources/msgcatalog directory [10] you will find in the CAAAfrGeneralWksAddinHeader.CATNls file the following lines:

    ...
In the CNext/resources/msgcatalog directory [10] you will find in the CAAAfrGeneralWksAddinHeader.CATNls file the following lines:
    CAAAfrGeneralWksAddinHeader.CAAAfrMRUAddElementHdr.Category  = "File" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrMRUAddElementHdr.Title     = "Add Item in MRU" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrMRUAddElementHdr.ShortHelp = "Add Item in MRU" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrMRUAddElementHdr.Help      = "Add Item in MRU" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrMRUAddElementHdr.LongHelp  = "Add Item in MRU
    This command adds a new item in the MRU list." ;

    ...

---

and in the CAAAfrGeneralWksAddinHeader.CATRsc file

    ...
    CAAAfrGeneralWksAddinHeader.CAAAfrMRUAddElementHdr.Icon.Normal = "I_CAAMRUAddItem" ;
    ...

---

where I_CAAMRUAddItem is the following icon: ![](images/CAAAfrSampleMRUMAddItem.jpg) and that you retrieve in the CNext/resources/graphic/icons/normal directory.

[Top]

* * *
### In Short

This use case has explained how to create a command header whose the graphic representation is customized:

  * The command header is a component which OM and C++ derives from _CATAfrDialogCommandHeader_ and implements _CATIAfrCommandHeaderRep_
  * The customized graphic representation is created by a class which must derive from _CATAfrCommandHeaderRep_

The data model is kept by an unique instance during the session.

[Top]

* * *
### References

[1] | [Creating a Combo Command Header](CAAAfrSampleComboHdr.md)
---|---
[2] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)
[3] | [Making Your Document Independent Command Available in All Workbenches](CAAAfrSampleGeneralWksAddin.md)
[4] | [CATDlgPushItem](../CAADlgQuickRefs/CAADlgCATDlgPushItem.md)
[5] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[6] | [Creating Interfaces](../CAASysUseCases/CAASysSampleOMCreatingInt.md)
[7] | [The Callback Mechanism](../CAASysTechArticles/CAASysCallbacks.md) (Technical Article)
[8] | [The Callback Mechanism](../CAASysUseCases/CAASysSampleCallbacks.md) (Use Case)
[9] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
[10] | [Creating Resources for Command Headers](../CAAAfrTechArticles/CAAAfrI18NHeader.md)
[11] | [Object Modeler Inheritances](../CAASysTechArticles/CAASysOMInheritance.md)
[Top]

* * *
### History

Version: **1** [Feb 2004] | Document created
---|---
[Top]

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
