---
title: "Creating a Command that Consists in a Dialog Window"
category: "use-case case"
module: "CAAAfrUseCases"
tags: "["CAAAfrBoundingEltHdr", "CAAAfrBoundingElementId", "CAAAfrGeoCommands", "CAAGeometry", "CAAAfrGeoAnalysisWkbHeader", "CATISO", "CAAAfrBoundingElementCmd", "CAAAfrBoundingElement", "CAAApplicationFrame"]"
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleDialogOnly.htm"
converted: "2026-05-11T17:17:55.713101"
---
# 3D PLM Enterprise Architecture

|
## User Interface - Command

|
### Creating a Command that Consists in a Dialog Window

_Creating a command without states_
---|---|---
Use Case

* * *
### Abstract

This article shows how to create a command without states using a single dialog box.

  * **What You Will Learn With This Use Case**
  * **The CAAAfrBoundingElementCmd Use Case**
    * What Does CAAAfrBoundingElementCmd Do
    * How to Launch CAAAfrBoundingElementCmd
    * Where to Find the CAAAfrBoundingElement Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to use a dialog box as a standalone command without states. This command is an undefined command which is unknown by the command selector [1]. It means that it can run in parallel with the active command known by the command selector.

[Top]
### The CAAAfrBoundingElementCmd Use Case

CAAAfrBoundingElementCmd is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does CAAAfrBoundingElementCmd Do

CAAAfrBoundingElementCmd is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.
CAAAfrBoundingElementCmd is a dialog command made up of a dialog box. It creates a bounding element, namely a sphere, for all or some of the geometric objects currently existing in the document. While computing the bounding sphere, it displays a progress bar.

The dialog is as follows:

![CAAAfrBoundingElt1.jpg ](images/CAAAfrBoundingElt1.jpg)
---

The document displayed includes points, lines, planes and circles. Select the CAAAfrBoundingElementCmd command.

![CAAAfrBoundingElt2.jpg](images/CAAAfrBoundingElt2.jpg)
---

The Model Bounding Sphere dialog box is displayed. You can check the options that take the points and lines  into account in the bounding sphere computing, and press Compute. This launches the bounding sphere computation. A progress bar is shown in the dialog box to show the progress status.

![CAAAfrBoundingElt3.jpg](images/CAAAfrBoundingElt3.jpg)
---

The Model Bounding Sphere dialog box is displayed. You can check the options that take the points and lines  into account in the bounding sphere computing, and press Compute. This launches the bounding sphere computation. A progress bar is shown in the dialog box to show the progress status.
The bounding sphere is computed. The dialog box was moved to show the bounding sphere displayed using three of its great circles. You can create other elements or delete some elements and next click "Compute" : a new bounding sphere will be displayed. The command remains active as long as you don't click Close.

The CAAAfrBoundingElementCmd use case explains how to create such command but does not explain

  * How to create the progress bar. You can refer to the dedicated article [2]
  * How to create/manage the temporary circles visualized thanks to the CATISO. You can refer to the dedicated article. [3]

[Top]
#### How to Launch CAAAfrBoundingElementCmd

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

```vbscript
Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

```

  * Select Start->Infrastructure->CAA V5: Geometry Analysis
  * Create several geometric objects such as points, lines, planes, and so on, using the Basic Elements toolbar, or using the same commands in the Insert menu
  * Select Analyze->Bounding Element.

[Top]
#### Where to Find the CAAAfrBoundingElementCmd Code

The CAAAfrBoundingElementCmd use case is made of a single class named _CAAAfrBoundingElementCmd_ located in the CAAAfrGeoCommands.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoCommands.m/`

The CAAAfrBoundingElementCmd use case is made of a single class named _CAAAfrBoundingElementCmd_ located in the CAAAfrGeoCommands.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoCommands.m/`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoCommands.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

CAAAfrBoundingElementCmd is part of the "CAA V5: Geometry Analysis" workbench.

[Top]
### Step-by-Step

CAAAfrBoundingElementCmd is part of the "CAA V5: Geometry Analysis" workbench.
To create the CAAAfrBoundingElementCmd command, there are four steps:

  1. Creating the Dialog Box Header File
  2. Enabling the Launching of the Command from a Command Header
  3. Creating the Dialog Box Constructor
  4. Managing the Lifecycle of the Command and of its Objects

[Top]
#### Creating the Dialog Box Header File

The CAAAfrBoundingElementCmd class header file is as follows.

    ...
    class CAAAfrBoundingElementCmd : public CATDlgDialog
    {
      **DeclareResource**(CAAAfrBoundingElementCmd, CATDlgDialog);

class CAAAfrBoundingElementCmd : public CATDlgDialog
```vbscript
      public :

```

        CAAAfrBoundingElementCmd(#);
        virtual ~CAAAfrBoundingElementCmd(#);

```vbscript
      private :

```

        ...
```cpp
CAAAfrBoundingElementCmd(#);
virtual ~CAAAfrBoundingElementCmd(#);
private :
        void **ClickClose**(CATCommand           * iSendingCommand,
                        CATNotification      * iSentNotification,
                        CATCommandClientData   iUsefulData);

        void **EditorClose**          (CATCallbackEvent  iEvent,
                               void             *iFrom,
                               CATNotification  *iNotification,
                               CATSubscriberData iData,
                               CATCallback       iCallBack );

     private :
```

        ...
        **CATFrmEditor**      * _pEditor ;
    };

---

This header file contains the following declaration:

  * The class derives from _CATDlgDialog_
  * The `DeclareResource` macro states that the resources of the _CAAAfrBoundingElementCmd_ command class are located in the CAAAfrBoundingElementCmd.CATNls file. If  resources were assigned to the _CATDlgDialog_ class, they would be concatenated with those of _CAAAfrBoundingElementCmd_
  * As usual, the class has a constructor and a destructor
  * Two callback methods contain the code to execute when the end user presses the Close button or closes the window in the banner.
  * A callback, `EditorClose` , when the current document is closed
  * The editor, associated with the document, is kept to compare which one which sends a close notification.

Now, there is the description of the source file.

[Top]
#### Enabling the Launching of the Command from a Command Header

The CAAAfrBoundingElementCmd command is launched from a _CATCommandHeader_ class instance [5]. In the CAA V5: Geometry Analysis" workbench, you have such line:

    ...
    new CAAAfrGeoAnalysisWkbHeader("CAAAfrBoundingEltHdr" ,
                                      "CAAAfrGeoCommands",
                                      "CAAAfrBoundingElementCmd" ,
                                      (void *) NULL);
    ...

---

So, to be able to create an instance of the command by its name you should have these two lines in its source file:

    ...
    #include "**CATCreateExternalObject**.h"
    **CATCreateClass**(CAAAfrBoundingElementCmd);
    ...

---

[Top]
#### Creating the Dialog Box Constructor

The CAAAfrBoundingElementCmd command is not seen by the command selector. Its starting mode is undefined: it is the default mode of a _CATDlgDialog_ class. For such commands, and contrary to the common usage with dialog boxes that use a `Build` method to instantiate the dialog objects contained in the dialog box, the constructor should perform this instantiation because the command header calls only this constructor. So the contents of the constructor is as a `Build` method [6] :

    ...
    CAAAfrBoundingElementCmd::CAAAfrBoundingElementCmd(#)
              :CATDlgDialog ((CATApplicationFrame::GetFrame(#))->GetMainWindow(#),
                              "CAAAfrBoundingElementId",
                              CATDlgGridLayout | **CATDlgWndBtnClose** )
    {

       // 1- Creating the dialog objects
       // 2- Arranging the dialog objects
       // 3- Declaring the callbacks associated with the dialog objects
       // 4- Declaring the callback for a document's closure
       ...
       _pEditor = **CATFrmEditor::GetCurrentEditor**(#);
    }
    ...

---

The dialog window has the application main window as parent [7]. The `CATDlgGridLayout` style enables you to use the grid layout for its internal arrangement [8] and the `CATDlgWndBtnClose` style is one of the fourth style recommended.

`_pEditor` is a data member which keeps the current editor when the command is launched. This data will be useful to check if the document that the end user want close is the document associated with this command- See the Managing the Lifecycle of the Command and of its Objects section.

 ![](../CAAIcons/images/warning.gif)The GetCurrentEditor method must not be used outside the _CATCommand_ class constructor .

  1. Creating the dialog objects

    ...
1. Creating the dialog objects
         CATDlgFrame * pPointLineGlobalFrame  = new CATDlgFrame(this, "PointLineGlobalFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
         CATDlgFrame * pPointLineCheckFrame  = new CATDlgFrame(pPointLineGlobalFrame, "PointLineCheckFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
         CATDlgFrame * pPointLineHeaderFrame  = new CATDlgFrame (pPointLineGlobalFrame, "PointLineHeaderFrameId",CATDlgGridLayout|CATDlgFraNoFrame);
         CATDlgLabel * pPointLineLabel = new CATDlgLabel(pPointLineHeaderFrame, "LabelPointLineId");

         ... See the code for the details
    ...

---
  2. Arranging the dialog objects

    ...
2. Arranging the dialog objects
         pPointLineLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
         pPointLineSep  ->SetGridConstraints(0,1,1,1,CATGRID_4SIDES|CATGRID_CST_HEIGHT);

         ... See the code for the details

pPointLineLabel->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
pPointLineSep  ->SetGridConstraints(0,1,1,1,CATGRID_4SIDES|CATGRID_CST_HEIGHT);
         _// Show the window_
         SetVisibility(CATDlgShow);

    ...

---
_// Show the window_
SetVisibility(CATDlgShow);
  3. Declaring the callbacks associated with the dialog object

         ...

3. Declaring the callbacks associated with the dialog object
           AddAnalyseNotificationCB(this, this->**GetWindCloseNotification**(#),
                         (CATCommandMethod)&CAAAfrBoundingElementCmd::ClickClose,
                                     NULL);
           AddAnalyseNotificationCB(this, this->**GetDiaCLOSENotification**(#),
                         (CATCommandMethod)&CAAAfrBoundingElementCmd::ClickClose,
                                     NULL);

           ...

---

NULL);
The `ClickClose` method is executed whenever the dialog window is closed: by the Close button (`GetDiaCLOSENotification`)**** or the banner (`GetWindCloseNotification`).

  4. Declaring the callback for a document's closure

This step is mandatory. If the end user closes the current document and the command is alive: it will not be automatically deleted once it is not seen by the command selector. So your command must set a callback when the document will send the "close" event.

    ...
4. Declaring the callback for a document's closure
This step is mandatory. If the end user closes the current document and the command is alive: it will not be automatically deleted once it is not seen by the command selector. So your command must set a callback when the document will send the "close" event.
```cpp
     if ( (NULL != _pEditor) && (NULL != **CATFrmLayout::GetCurrentLayout**(#)) )

```

      {
         ::AddCallback(this,
```cpp
if ( (NULL != _pEditor) && (NULL != **CATFrmLayout::GetCurrentLayout**(#)) )
                        CATFrmLayout::GetCurrentLayout(#),
```

    		  **CATFrmEditor::EDITOR_CLOSE_ENDED**(#),
```cpp
if ( (NULL != _pEditor) && (NULL != **CATFrmLayout::GetCurrentLayout**(#)) )
CATFrmLayout::GetCurrentLayout(#),
    		  (CATSubscriberMethod)&CAAAfrBoundingElementCmd::EditorClose,
    		  NULL);
```

      }
    ...

---

Refer to the technical article [7] to understand the role of the unique _CATFrmLayout_ class instance. It is the object which sends the `CATFrmEditor::EDITOR_CLOSE_ENDED` notification.

[Top]
#### Managing the Lifecycle of the Command and of its Objects

The command can be deleted for two reasons:

  * When the end user closes itself the window:

The command can be deleted for two reasons:
    void CAAAfrBoundingElementCmd::ClickClose(CATCommand           * iSendingCommand,
                                              CATNotification      * iSentNotification,
                                              CATCommandClientData   iUsefulData)

    {
      **SetVisibility**(CATDlgHide);

      ...

      **RequestDelayedDestruction**(#);

    }

---

In this case, the `ClickClose` method is called. It hides the dialog box and requests the dialog box to be deleted.

  * When the document is closed:

In this case, the `ClickClose` method is called. It hides the dialog box and requests the dialog box to be deleted.
    void CAAAfrBoundingElementCmd::**EditorClose**(CATCallbackEvent  iEvent, void  * iFrom,
                                                  CATNotification * iNotification,
                                                  CATSubscriberData iClientData,
                                                  CATCallback       iCallBack )

    {
void CAAAfrBoundingElementCmd::**EditorClose**(CATCallbackEvent  iEvent, void  * iFrom,
CATNotification * iNotification,
CATSubscriberData iClientData,
CATCallback       iCallBack )
```vbscript
       if ( _pEditor == **iFrom** )

```

       {
          **RequestDelayedDestruction**(#);
       }
    }

---

The unique _CATFrmLayout_ class instance sends a "`EDITOR_CLOSE_ENDED"` notification when anything document is closed. So the `EditorClose`**** method is called.  It is necessary to check that it is the "good" editor before closing the window. `iFrom` is the editor associated with the document which is closing. If `iFrom` is the good document the dialog box deletion is requested.

The destructor, as usual, releases the data members and set NULL the data member pointers. In addition, the current destructor must delete the callback on the _CATFrmLayout_ :

The unique _CATFrmLayout_ class instance sends a "`EDITOR_CLOSE_ENDED"` notification when anything document is closed. So the `EditorClose`**** method is called.  It is necessary to check that it is the "good" editor before closing the window. `iFrom` is the editor associated with the document which is closing. If `iFrom` is the good document the dialog box deletion is requested.
The destructor, as usual, releases the data members and set NULL the data member pointers. In addition, the current destructor must delete the callback on the _CATFrmLayout_ :
    CAAAfrBoundingElementCmd::~CAAAfrBoundingElementCmd(#)

    {
      // releases the data members and set NULL the data member pointers
      ...
       if ( (NULL != _pEditor) && ( NULL != CATFrmLayout::GetCurrentLayout(#)) )
       {
          ::**RemoveSubscriberCallbacks**(this,CATFrmLayout::GetCurrentLayout(#));
       }

       _pEditor = NULL ;
    }

---

![](../CAAIcons/images/warning.gif)If the command uses interactive objects such as the ISO, HSO, PSO objects [9], in the destructor you must not remove any objects from this interactive objects. The _CATFrmEditor_ which manages them has already made it. But if the window is closed by the end user, you must remove the objects in the `ClickClose` method.

[Top]

* * *
### In Short

This use case shows how to create a command without state that consists only in a dialog window and that in addition, is not known by the command selector.

[Top]

* * *
### References

[1] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
---|---
[2] | [Creating an Interruptible Task](CAAAfrSampleProgressTask.md)
[3] | [Creating Contextual Menus in a State Dialog Command](../CAADegUseCases/CAADegSampleCtxMenu.md)
[5] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)
[6] | [Dialog Programmer's Guide](../CAADlgTechArticles/CAADlgProgrammerGuide.md)
[7] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)
[8] | [Arranging the Dialog Objects Using the Grid Layout](../CAADlgTechArticles/CAADlgGridLayout.md)
[9] | [Application Frame Overview](../CAAAfrTechArticles/CAAAfrOverview.md)

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
Version: **2** [Fev 2003] | Document updated
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
