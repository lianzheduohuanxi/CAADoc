---
```vbscript
title: "Editing Objects"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAASysPoint", "CAAISysPoint", "CAAAfrGeoEdition", "CAAEAfrEditPoint", "CATIModelEvents", "CAAGeometry", "CATIEdit", "CAAAfrPointEditDlg", "CAAAfrPointEditCmd", "CAAAfrPointEditDlgId", "CAAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleObjectEdit.htm"
converted: "2026-05-11T17:17:55.785009"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Editing Objects

_Make your objects editable_  
---|---|---  
Use Case  

* * *
### Abstract

This article shows how to make an object editable, and how to create the associated dialog. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrGeoEdition Use Case**
    * What Does CAAAfrGeoEdition Do
    * How to Launch CAAAfrGeoEdition
    * Where to Find the CAAAfrGeoEdition Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to create make an object editable, and which object to provide to edit it.

[Top]
### The CAAAfrGeoEdition Use Case

CAAAfrGeoEdition is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does CAAAfrGeoEdition Do

The CAAAfrGeoEdition use case makes the Point object an editable object, and provides it with an editing command and an editing dialog.

![CAAAfrPointEditMenu.gif \(27004 bytes\)](images/CAAAfrPointEditMenu.gif)

[Top]
#### How to Launch CAAAfrGeoEdition

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 

  * Select File->New
  * In the New box, select CAAGeometry and click OK
  * Create at least one point using the Basic Elements toolbar
  * Right click this point and select the Definition command.

[Top]
#### Where to Find the CAAAfrGeoEdition Code

The CAAAfrGeoEdition use case is made of three classes located in the CAAAfrGeoEdition.m module of the CAAApplicationFrame.edu framework:

The CAAAfrGeoEdition use case is made of three classes located in the CAAAfrGeoEdition.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoEdition.m\`  

The CAAAfrGeoEdition use case is made of three classes located in the CAAAfrGeoEdition.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoEdition.m\`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoEdition.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

These classes are:

_CAAEAfrEditPoint_ | Extension class for the _CAASysPoint_ component  

These classes are:
_CAAEAfrEditPoint_ | Extension class for the _CAASysPoint_ component
_CAAAfrPointEditCmd_ | Editing command class  
_CAAAfrPointEditDlg_ | Dialog class associated with the editing command class  

[Top]
### Step-by-Step

To make an object editable, there are three steps:
# | Step | Where  
---|---|---  
To make an object editable, there are three steps:
1 | Make the point object implement the _CATIEdit_ interface | _CAAEAfrEditPoint_ class  
2 | Create the editing command | _CAAAfrPointEditCmd_ class  
3 | Create the editing dialog | _CAAAfrPointEditDlg_ class  

[Top]
#### Making the Point Object Implement the _CATIEdit_ Interface

3 | Create the editing dialog | _CAAAfrPointEditDlg_ class
The _CATIEdit_ interface mainly provides the `Activate` method that should return the _CATCommand_ class instance that actually enables the object edition. `Activate` is called whenever the end user intends to edit the object by double clicking or through the object's contextual menu.

To make the _CAASysPoint_ component implements the _CATIEdit_ interface, we create a class that derives from the _CATExtIEdit_ adapter class as a data extension of the _CAASysPoint_ class, and that provides code for the `Activate` method. The other methods of the _CATIEdit_ interface are inherited from _CATExtIEdit_. 

  1. Create the header file for the _CAAEAfrEditPoint_ class 

         #include "CATExtIEdit.h"   //Needed to derive from CATExtIEdit

To make the _CAASysPoint_ component implements the _CATIEdit_ interface, we create a class that derives from the _CATExtIEdit_ adapter class as a data extension of the _CAASysPoint_ class, and that provides code for the `Activate` method. The other methods of the _CATIEdit_ interface are inherited from _CATExtIEdit_.
1. Create the header file for the _CAAEAfrEditPoint_ class
         class CAAEAfrEditPoint : public **CATExtIEdit**

         {
           **CATDeclareClass** ;
class CAAEAfrEditPoint : public **CATExtIEdit**
           public :
             CAAEAfrEditPoint();
             virtual ~CAAEAfrEditPoint();
             virtual CATCommand  * **Activate**(CATPathElement * iPath);
           private :
             CAAEAfrEditPoint(const CAAEAfrEditPoint &iObjectToCopy);

         };  

---  

```vbscript
CAAEAfrEditPoint(const CAAEAfrEditPoint &iObjectToCopy);
The `CATDeclareClass` macro declares that _CAAEAfrEditPoint_ belongs to a component. It only redefine the Activate method of _CATIEdit_.

  2. In the class source file, insert the object modeler part 

```

         ...
         **CATImplementClass**(CAAEAfrEditPoint,
                           **DataExtension** ,
                           CATBaseUnknown,
                           **CAASysPoint**);
         #include "TIE_CATIEdit.h"
         TIE_CATIEdit(CAAEAfrEditPoint);
         ...  

---  

```vbscript
TIE_CATIEdit(CAAEAfrEditPoint);
The `CATImplementClass` macro reads: _CAAEAfrEditPoint_ is a data extension of _CAASysPoint_. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension. The TIE macro creates the TIE class for the _CATIEdit_ interface.

  3. Implement the `Activate` method 

```

         ...
The `CATImplementClass` macro reads: _CAAEAfrEditPoint_ is a data extension of _CAASysPoint_. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension. The TIE macro creates the TIE class for the _CATIEdit_ interface.
3. Implement the `Activate` method
         CATCommand * CAAEAfrEditPoint::**Activate**(CATPathElement * pPath)

         {
3. Implement the `Activate` method
CATCommand * CAAEAfrEditPoint::**Activate**(CATPathElement * pPath)
           CAAAfrPointEditCmd *  pEdtCmd = NULL;
           CAAISysPoint * pISysPointOnPoint = NULL;                
           HRESULT rc = **QueryInterface**(**IID_CAAISysPoint** , (void**)&pISysPointOnPoint);
           if (SUCCEEDED(rc))

           {
CAAAfrPointEditCmd *  pEdtCmd = NULL;
CAAISysPoint * pISysPointOnPoint = NULL;
HRESULT rc = **QueryInterface**(**IID_CAAISysPoint** , (void**)&pISysPointOnPoint);
if (SUCCEEDED(rc))
             CAAAfrPointEditCmd *  pEdtCmd = new **CAAAfrPointEditCmd**(pISysPointOnPoint);
             pISysPointOnPoint->**Release**();

           }
```vbscript
if (SUCCEEDED(rc))
CAAAfrPointEditCmd *  pEdtCmd = new **CAAAfrPointEditCmd**(pISysPointOnPoint);
pISysPointOnPoint->**Release**();
           return (CATCommand*) pEdtCmd;
```

         }  

---  

The `Activate` method: 
     * First retrieves a pointer to an interface implemented by the object to pass to the dialog box. Here we choose to retrieve a pointer to the type interface of _CAASysPoint_ because this interface exposes methods that manages the object parameters we want to display in the dialog box for modification, that is the point coordinates
     * Then constructs the dialog command object. This is an instance of the _CAAAfrPointEditCmd_ described in Creating the Editing Command to which the previous pointer to the object to edit is passed
     * Finally, returns the editing command pointer as a _CATCommand_ pointer.

[Top]
#### Creating the Editing Command

The point editing command is named _CAAAfrPointEditCmd_ and directly derives from _CATCommand_. In addition to the three methods inherited from _CATCommand_ and redefined to manage its availability and lifecycle, that is, `Activate`, `Desactivate`, and `Cancel`, the command has also the `CloseBox` method that is called when the end user closes the dialog box to request the dialog destruction. The command data members are a pointer to the dialog and a pointer to the _CAAISysPoint_ interface.

The CAAAfrPointEditCmd.cpp file is as follows. Let's examine its body in an event driven way. 

  * The constructor is called by the command selector when the end user double clicks on the object, or select the Definition item of the point contextual menu. 

        ...
The CAAAfrPointEditCmd.cpp file is as follows. Let's examine its body in an event driven way.
        CAAAfrPointEditCmd::CAAAfrPointEditCmd(CAAISysPoint * ipEdit)					 

                     : CATCommand ("PointEditCommandId",**CATCommandModeExclusive**),
CAAAfrPointEditCmd::CAAAfrPointEditCmd(CAAISysPoint * ipEdit)
                       _pEdit(ipEdit),_DialogPoint(NULL)

        {
CAAAfrPointEditCmd::CAAAfrPointEditCmd(CAAISysPoint * ipEdit)
_pEdit(ipEdit),_DialogPoint(NULL)
          if (_pEdit) _pEdit -> AddRef();

        }
        ...  

---  

The constructor sets the command as exclusive thanks to `CATCommandModeExclusive` passed as second parameter of the _CATCommand_ constructor. This deletes all possible existing commands. Any command that modifies the document must be set as exclusive. The constructor also retrieves a pointer to the _CAAISysPoint_ interface on the object to edit.

  * The `Activate` method is called by the command selector just after its instantiation 

        ...
The constructor sets the command as exclusive thanks to `CATCommandModeExclusive` passed as second parameter of the _CATCommand_ constructor. This deletes all possible existing commands. Any command that modifies the document must be set as exclusive. The constructor also retrieves a pointer to the _CAAISysPoint_ interface on the object to edit.
        CATStatusChangeRC CAAAfrPointEditCmd::Activate(CATCommand      *iCmd,
                                                       CATNotification *iNotif)

        {
CATStatusChangeRC CAAAfrPointEditCmd::Activate(CATCommand      *iCmd,
CATNotification *iNotif)
          if ( ! _DialogPoint)

          {
CATStatusChangeRC CAAAfrPointEditCmd::Activate(CATCommand      *iCmd,
CATNotification *iNotif)
if ( ! _DialogPoint)
            CATDlgStyle style = CATDlgWndOK|CATDlgWndAPPLY|CATDlgWndCANCEL|
                                CATDlgWndHELP|         // help on Unix (LongHelp)
                                CATDlgWndTitleBarHelp| // help in the title bar (Windows only)
                                CATDlgGridLayout ;
            CATString id ("CAAAfrPointEditDlgId");
            CATDialog * pParent = (CATApplicationFrame::GetFrame())->GetMainWindow() ;

            _DialogPoint = new **CAAAfrPointEditDlg**(pParent,id,style,_pEdit);

            **AddAnalyseNotificationCB**(_DialogPoint, _DialogPoint->**GetWindCloseNotification**(),
CATDialog * pParent = (CATApplicationFrame::GetFrame())->GetMainWindow() ;
_DialogPoint = new **CAAAfrPointEditDlg**(pParent,id,style,_pEdit);
                                     (CATCommandMethod)&CAAAfrPointEditCmd::**CloseBox** ,
                                     NULL);

            _DialogPoint->**Build**();

          }

NULL);
_DialogPoint->**Build**();
          _DialogPoint->**SetVisibility**(CATDlgShow);
          return (CATStatusChangeRCCompleted);

        }
        ...  

---  

`Activate` is called whenever the command selector gives the focus to the command, whether because the end user clicks on it or because it takes the focus after being deactivated by a shared command. `Activate` creates the dialog if it does not already exists, makes it visible, and returns that the method normally completes.

To create the dialog box, the dialog box constructor is called with the following parameters: 
    1. As a _CATCommand_ class instance, its parent in the command tree structure is passed as first parameter. Since for a dialog, it should be another dialog, this is set as the frame window.
    2. The dialog box name is passed as the second parameter
    3. The style concatenation makes a dialog box with the three buttons OK (`CATDlgWndOK`), Apply (`CATDlgWndAPPLY`), and Cancel(`CATDlgWndCANCEL`). With UNIX, a Help button is added (`CATDlgWndHELP`). With Windows, a question mark is put in the title bar instead (`CATDlgWndHELP` and `CATDlgWndTitleBarHelp`). The dialog window is arranged using a grid (`CATDlgGridLayout`)
    4. The pointer to the interface _CAAISysPoint_ is passed as the fourth parameter.

A callback is set on the dialog box to be informed when the ned user closes it, and the dialog box `Build` method is called to actually fill it with appropriate controls. The constructor of a dialog object should only allocate storage for the dialog box, but should not set any of the labels or fields with values coming from resource files, since these files could be required before being allocated by the constructor. Valuation is dedicated to the `Build` method, and the dialog can be shown. The method returns that it is completed. Refer to Creating the Editing Dialog for more details.

  * The other methods are as follows. 

        ...
A callback is set on the dialog box to be informed when the ned user closes it, and the dialog box `Build` method is called to actually fill it with appropriate controls. The constructor of a dialog object should only allocate storage for the dialog box, but should not set any of the labels or fields with values coming from resource files, since these files could be required before being allocated by the constructor. Valuation is dedicated to the `Build` method, and the dialog can be shown. The method returns that it is completed. Refer to Creating the Editing Dialog for more details.
        CATStatusChangeRC CAAAfrPointEditCmd::**Desactivate**(CATCommand      * iCmd,
                                                          CATNotification * iNotif)

        {
CATStatusChangeRC CAAAfrPointEditCmd::**Desactivate**(CATCommand      * iCmd,
CATNotification * iNotif)
          _DialogPoint->SetVisibility(CATDlgHide);
          return (CATStatusChangeRCCompleted);

        }

_DialogPoint->SetVisibility(CATDlgHide);
return (CATStatusChangeRCCompleted);
        CATStatusChangeRC CAAAfrPointEditCmd::**Cancel**(CATCommand      * iCmd,
                                                     CATNotification * iNotif)

        {
CATStatusChangeRC CAAAfrPointEditCmd::**Cancel**(CATCommand      * iCmd,
CATNotification * iNotif)
          _DialogPoint->SetVisibility(CATDlgHide);
          RequestDelayedDestruction();  
          return (CATStatusChangeRCCompleted);

        }

_DialogPoint->SetVisibility(CATDlgHide);
RequestDelayedDestruction();
return (CATStatusChangeRCCompleted);
        void CAAAfrPointEditCmd::**CloseBox**(CATCommand           * iSendingCommand,
                                          CATNotification      * iSentNotification,
                                          CATCommandClientData   iUsefulData)

        {
void CAAAfrPointEditCmd::**CloseBox**(CATCommand           * iSendingCommand,
CATNotification      * iSentNotification,
CATCommandClientData   iUsefulData)
          _DialogPoint->SetVisibility(CATDlgHide);
          RequestDelayedDestruction();

        }  

---  

These methods do the following: 
    * `Desactivate` is called whenever the command selector withdraws the focus from it. This happens when a shared command takes the focus. The command remains in the command stack, ready to take the focus again as soon as the shared command completes. It simply hides the dialog to ensure that the end user will not click in it while the command is deactivated, but don't delete anything to be ready to restore the dialog if the focus is assigned to it afterward
    * `Cancel` is called whenever the command definitely looses the focus and should be deleted, usually when the end user selects another exclusive command. `Cancel` hides the dialog and requets the command destruction
    * `CloseBox` is called whenever the end user whenever the end user clicks OK or Cancel, or closes the dialog. It is equivalent to `Cancel`, but is not called as a callback of the dialog, and not by the command selector. `RequestDelayedDestruction` informs the command selector to release the focus from the command. The default command, usually Select, is activated instead.
  * The destructor is called by `RequestDelayedDestruction` and should first remove the callback set on the dialog before requesting the dialog destruction. 

        ...
        CAAAfrPointEditCmd::~CAAAfrPointEditCmd()
        {
CAAAfrPointEditCmd::~CAAAfrPointEditCmd()
          if (_DialogPoint)

          {
CAAAfrPointEditCmd::~CAAAfrPointEditCmd()
if (_DialogPoint)
            RemoveAnalyseNotificationCB(_DialogPoint,
                                        _DialogPoint->GetWindCloseNotification(),
                                        NULL);
            _DialogPoint->RequestDelayedDestruction();

          }
        }  

---  

[Top]
#### Creating the Editing Dialog

The editing command is the dialog box created using the `Activate` method of the _CATIEdit_ interface implementation. It highly depends on the object to edit and is designed and coded as any other dialog box, that is with an empty constructor and a `Build` method. The dialog box for the _CAASysPoint_ class is as follows:

 This dialog box shows three spinners to display and change the point x, y, and z coordinates. The OK button applies the new parameter values and closes the dialog box. The Apply button only applies the new parameter values, but the dialog box remains displayed. The Cancel button closes the window and restores the coordinate initial values.  
---|---  

The editing command is the dialog box created using the `Activate` method of the _CATIEdit_ interface implementation. It highly depends on the object to edit and is designed and coded as any other dialog box, that is with an empty constructor and a `Build` method. The dialog box for the _CAASysPoint_ class is as follows:
This dialog box shows three spinners to display and change the point x, y, and z coordinates. The OK button applies the new parameter values and closes the dialog box. The Apply button only applies the new parameter values, but the dialog box remains displayed. The Cancel button closes the window and restores the coordinate initial values.
The _CAAAfrPointEditDlg_ class derives from the _CATDlgDialog_ class, which is the base class for all dialog boxes. The constructor takes a pointer to the _CAAISysPoint_ interface. This is the main interface implemented by the object, and this pointer will be useful to get the object's parameter values to build the dialog box, and to modify the object when the end user clicks OK or Apply.

The `Build` method creates the controls, arranges them in the dialog box, and sets the labels and numerical values from resource files or using the pointer to the _CAAISysPoint_ interface. It sets the callbacks for the OK, Apply, and Cancel push buttons, and for the window closing event, that is, `ClickOK`, `ClickApply`, `ClickCancel`, and `CloseBox` respectively.

We'll examine the callback methods, then `CloseBox`, and finally `ModifyModelAndVisu` that modifies the document and request for a display refresh. 

  1. `ClickOK`  

         void CAAAfrPointEditDlg::ClickOK(CATCommand * iSendingCommmand,
                                          CATNotification * iSentNotification,
                                          CATCommandClientData UsefulData)

         {
void CAAAfrPointEditDlg::ClickOK(CATCommand * iSendingCommmand,
CATNotification * iSentNotification,
CATCommandClientData UsefulData)
           ModifyModelAndVisu(_XSpinner->GetCurrentValue(),
                              _YSpinner->GetCurrentValue(),
                              _ZSpinner->GetCurrentValue());
           CloseBox();

         }  

---  

```vbscript
CloseBox();
This method is executed whenever the end user clicks the OK push button. It first modifies the point and the display thanks to the `ModifyModelAndVisu` method using the current values of the spinners and calls the `CloseBox` method that takes appropriate actions to close the dialog.

  2. `ClickApply`  

         void CAAAfrPointEditDlg::ClickApply(CATCommand * iSendingCommmand,
                                             CATNotification * iSentNotification,
                                             CATCommandClientData UsefulData)
```

         {
void CAAAfrPointEditDlg::ClickApply(CATCommand * iSendingCommmand,
CATNotification * iSentNotification,
CATCommandClientData UsefulData)
           ModifyModelAndVisu(_XSpinner->GetCurrentValue(),
                              _YSpinner->GetCurrentValue(),
                              _ZSpinner->GetCurrentValue());

         }  

---  

_ZSpinner->GetCurrentValue());
This method is executed whenever the end user clicks the Apply push button. It just modifies the point and the display like `ClickOK`, but leaves the dialog box displayed.

  3. `ClickCancel`  

         void CAAAfrPointEditDlg::ClickCancel(CATCommand * iSendingCommmand,
                                              CATNotification * iSentNotification,
                                              CATCommandClientData UsefulData)

         {
void CAAAfrPointEditDlg::ClickCancel(CATCommand * iSendingCommmand,
CATNotification * iSentNotification,
CATCommandClientData UsefulData)
           ModifyModelAndVisu(_Xfirst,_Yfirst,_Zfirst);
           CloseBox();

         }  

---  

```vbscript
CloseBox();
This method is executed whenever the end user clicks the Cancel push button. It just restores the point and the display using the point initial coordinates, and closes the dialog.

  4. `ClickClose`  

         void CAAAfrPointEditDlg::ClickClose(CATCommand * iSendingCommmand,
                                             CATNotification * iSentNotification,
                                             CATCommandClientData UsefulData)
```

         {
void CAAAfrPointEditDlg::ClickClose(CATCommand * iSendingCommmand,
CATNotification * iSentNotification,
CATCommandClientData UsefulData)
           CloseBox();

         }  

---  

```vbscript
CloseBox();
This method is executed whenever the end user closes the dialog. It calls the `CloseBox` method.

  5. `CloseBox`  

         void CAAAfrPointEditDlg::CloseBox()
```

         {
5. `CloseBox`
void CAAAfrPointEditDlg::CloseBox()
           SetVisibility(CATDlgHide);

           RemoveAnalyseNotificationCB(this, this->GetDiaOKNotification(),NULL);
           RemoveAnalyseNotificationCB(this, this->GetDiaAPPLYNotification(),NULL);
           RemoveAnalyseNotificationCB(this, this->GetDiaCANCELNotification(),NULL);
           RemoveAnalyseNotificationCB(this, this->GetWindCloseNotification(),NULL);

           SendNotification(GetFather(),CATDlgDialog::GetWindCloseNotification());

         }  

---  

```vbscript
SendNotification(GetFather(),CATDlgDialog::GetWindCloseNotification());
This method hides the dialog, and sends a notification to state that the dialog should be closed This notification is sent to the dialog father, set to the frame window as the first parameter of its constructor. This notification moves from a command to its parent along the command tree structure up to the first command that have set a callback for this notification and for this dialog. Since there are few chances that such a command exists, the notification reaches the command selector that resends it to the active command, which fortunately has set such a callback execute its own `CloseBox` method when such a notification is received from the dialog.

  6. The `ModifyModelAndVisu` method modifies the point in the document and sends a notification to request the display to update accordingly.  

         void CAAAfrPointEditDlg::ModifyModelAndVisu(const float iX, const float iY, const float iZ)
```

         {
6. The `ModifyModelAndVisu` method modifies the point in the document and sends a notification to request the display to update accordingly.
void CAAAfrPointEditDlg::ModifyModelAndVisu(const float iX, const float iY, const float iZ)
           _pPointEdit->SetCoord(iX, iY, iZ);

           CATIModelEvents * pModelEvents = NULL;
           HRESULT rc = _pPointEdit -> QueryInterface(IID_CATIModelEvents, (void**)&pModelEvents);
           if (SUCCEEDED(rc))

           {
CATIModelEvents * pModelEvents = NULL;
HRESULT rc = _pPointEdit -> QueryInterface(IID_CATIModelEvents, (void**)&pModelEvents);
if (SUCCEEDED(rc))
             CATModify * pNotif = new **CATModify**(pModelEvents);
             pModelEvents->Dispatch(*pNotif);
             delete pNotif;
             pModelEvents->Release();

           } 
         }  

---  

[Top]

* * *
### In Short

Any object can be edited using a dialog when the end user double clicks a representation of the object when the Select command is the active one, or from the object contextual menu, provided the object implements the `Activate` method of the _CATIEdit_ interface.

The object editing command is then made active. This command must be created in the exclusive mode to ensure that both its availability and its lifecycle are correctly managed by the command selector. The associated dialog box dedicated to editing the object is like any other dialog box. It updates the object's data using methods provided by the object, and its representation(s) by dispatching notifications to the visualiaztion manager, both by means of callbacks set on its different controls.

[Top]

* * *
### References

[Top]  
---  

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
