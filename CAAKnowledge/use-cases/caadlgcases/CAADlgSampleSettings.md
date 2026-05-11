---
```vbscript
title: "Saving and Restoring the Dialog Box State"
category: "use case"
module: "CAADlgUseCases"
tags: ["CAADlgDemoWindow", "CAADlgDialogDemonstrator", "CATISpecObject", "CAADlgFrameReplace", "CATInteractiveApplication", "CAADlgDemoApplication", "CAADialog", "CAADlgFrameReplaceDlg"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleSettings.htm"
converted: "2026-05-11T17:17:55.997189"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Dialogs

|
### Saving and Restoring the Dialog Box State

How to keep and retrieve the dialog object values
---|---|---
Use Case

* * *
### Abstract

This article shows how to save parameters so that one can find the Dialog box in the same state that it was before its closing.

  * **What You Will Learn With This Use Case**
  * **The CAADlgFrameReplace Use Case**
    * What Does CAADlgFrameReplace Do
    * How to Launch CAADlgFrameReplace
    * Where to Find the CAADlgFrameReplace Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to use a setting file and repository [1] to store and retrieve the values of Dialog Objects. The setting repository being the memory copy of a setting file. [Top]
### The CAADlgFrameReplace Use Case

CAADlgFrameReplace is a use case of the CAADialog.edu framework that illustrates Dialog and System framework capabilities. [Top]
#### What Does CAADlgFrameReplace Do

CAADlgFrameReplace simulates the  "Point Definition" V5 Dialog box. It creates the "Frame Replacement Demonstrator" Dialog box that you can see just below. The end user can select the mode of creation for the point: by coordinate values, by the center of a circle or between two points [2].   |  | _Fig. 1a_ _:Coordinates_
---
![](images/CAADlgTabulationFrameReplace2.jpg)
| _Fig. 1b: Circle Center_
---
![](images/CAADlgTabulationFrameReplace1.jpg)
| _Fig. 1c: Between_
---
![](images/CAADlgTabulationFrameReplace3.jpg)

When the end user clicks **OK** , the following values are kept:

  * The "`Point Type`" ( an integer )
  * The point coordinates (`X, Y, Z`)  (three double)

The others values are not kept, for the following reasons:

  * `Circle`, `P1` and `P2` : The values, in a V5 context, will be a string, the _GetDisplayName_ of a _CATISpecObject._ You can save a string, but it is not possible to save a _CATISpecObject_ instance, so there is no need to keep the value of these fields.
  * `Ratio` : The Dialog object is a _CATDlgEditor_ class. It is the only one Dialog object which natively keeps the last values. You retrieve them with the up and down arrows.

When the end user clicks **Cancel** or **closes** the window, the current values of the Dialog objects are not kept.

[Top]
#### How to Launch CAADlgFrameReplace

To launch the use case, you will need to set up the build time environment, then compile CAADlgDialogDemonstrator along with its prerequisites, set up the run time environment, and then execute the use case [3].

`mkrun -c CAADlgDialogDemonstrator `

When the `CAADlgDialogDemonstrator` application is launched:

  * On the **Tabulation**   menu click **Frame Replacement**
  * Click **Circle Center** in the combo
  * Click **OK**
  * On the **Tabulation**   menu click **Frame Replacement  **
  * Click **Coordinates** in the combo
  * Enter a value in **X** , **Y** and **Z** field
  * Click **OK  **
  * On the **Tabulation**   menu click **Frame Replacement  **
  * Click **Between** in the combo
  * Enter different values in the **Ratio** field
  * Click **OK  **
  * On the **Tabulation**   menu click **Frame Replacement  **
  * On the **Ratio** field retrieve the different value with the **up** and**down** arrows
  * On the **Tabulation**   menu click **Frame Replacement**
  * Click **Coordinates** in the combo
  * Enter a value in **X** , **Y** and **Z** field
  * Click **Cancel**
  * On the **Tabulation**   menu click **Frame Replacement  **
  * On the**File** menu click**Exit**

[Top]
#### Where to Find the CAADlgFrameReplace Code

The CAADlgFrameReplace use case is made of several classes located in the CAADlgDialogDemonstrator.m module of the CAADialog.edu framework:

The CAADlgFrameReplace use case is made of several classes located in the CAADlgDialogDemonstrator.m module of the CAADialog.edu framework:
Windows | `InstallRootDirectory\CAADialog.edu\CAADlgDialogDemonstrator.m\`

The CAADlgFrameReplace use case is made of several classes located in the CAADlgDialogDemonstrator.m module of the CAADialog.edu framework:
Windows | `InstallRootDirectory\CAADialog.edu\CAADlgDialogDemonstrator.m\`
Unix | `InstallRootDirectory/CAADialog.edu/CAADlgDialogDemonstrator.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

In the LocalInterfaces and src directory, you will find the following files:

  * CAADlgDemoApplication.h/CAADlgDemoApplication.cpp: The _" DialogDemonstrator"_ application definition. ( a _CATInteractiveApplication_ )
  * CAADlgDemoWindow.h/CAADlgDemoWindow.cpp : The _CATDlgDocument_ definition.
  * CAADlgFrameReplaceDlg.h/CAADlgFrameReplaceDlg.cpp : The "Frame Replacement Demonstrator" dialog box definition

[Top]
### Step-by-Step

There are four logical steps in the use case:

There are four logical steps in the use case:
  1. Creating the Class Header
  2. Retrieving the Setting Repository
  3. Retrieving the Last Values
  4. Saving the Values

[Top]
#### Creating the Class Header

The main contents of the CAADlgFrameReplaceDlg.h file is the following:

    #include "CATDlgDialog.h"   // To derive from
    ...
The main contents of the CAADlgFrameReplaceDlg.h file is the following:
    class **CATSettingRepository** ; // To manage values

    class CAADlgFrameReplaceDlg: public **CATDlgDialog**

    {
      ...
class **CATSettingRepository** ; // To manage values
class CAADlgFrameReplaceDlg: public **CATDlgDialog**
      public:

          CAADlgFrameReplaceDlg(CATDialog * pParentDlg);
          virtual ~CAADlgFrameReplaceDlg();

          void Build ();

      private:

          ...
void Build ();
private:
          virtual void **CloseWindowOK** (CATCommand * iSendingCommand,
                                    CATNotification * iSentNotification,
                                    CATCommandClientData iUsefulData);

          virtual void **CloseWindow** (CATCommand * iSendingCommand,
                                    CATNotification * iSentNotification,
                                    CATCommandClientData iUsefulData);

         ...
virtual void **CloseWindow** (CATCommand * iSendingCommand,
CATNotification * iSentNotification,
CATCommandClientData iUsefulData);
      private:

         ...
CATNotification * iSentNotification,
CATCommandClientData iUsefulData);
private:
         CATSettingRepository * _pSettingFrameReplace ;

    };

---

where

  * The `Build` method enables you to construct the Dialog objects and to initialize them with the values saved in the setting file.
  * The `CloseWindowOK` method is a callback method which is called when the end user pushes the Ok Button
  * The `CloseWindow` method is a callback method which is called when the end user pushes the Cancel Button or closes the window.
  * `_pSettingFrameReplace` is a _CATSettingRepository_ class pointer. It will be initialized in the constructor class. You should not release this pointer.

#### Retrieving the Setting Repository

In the _CAADlgFrameReplaceDlg_ class constructor you retrieve a setting repository pointer thanks to the static `GetRepository` method. The first and unique argument of this method is the name of the setting file.

In the _CAADlgFrameReplaceDlg_ class constructor you retrieve a setting repository pointer thanks to the static `GetRepository` method. The first and unique argument of this method is the name of the setting file.
    CAADlgFrameReplaceDlg::CAADlgFrameReplaceDlg(CATDialog * pParentDlg) :
      CATDlgDialog (pParentDlg,"CAADlgFrameReplaceDlg",
          CATDlgWndAutoResize | CATDlgWndBtnOKCancel |CATDlgWndNoResize ),
          _CurrentSelection(0),_pComboPointType(NULL),_pSpinnerX(NULL),
```vbscript
          _pSpinnerY(NULL),_pSpinnerZ(NULL)

```

    {
       ...
CATDlgWndAutoResize | CATDlgWndBtnOKCancel |CATDlgWndNoResize ),
_CurrentSelection(0),_pComboPointType(NULL),_pSpinnerX(NULL),
```vbscript
_pSpinnerY(NULL),_pSpinnerZ(NULL)
```vbscript
       _pSettingFrameReplace = CATSettingRepository::**GetRepository**("CAADlgFrameReplaceDlg" );

```

```

    }

---

In the _CAADlgFrameReplaceDlg_ class destructor you have just to set NULL the `_pSettingFrameReplace` pointer.

In the _CAADlgFrameReplaceDlg_ class destructor you have just to set NULL the `_pSettingFrameReplace` pointer.
    CAADlgFrameReplaceDlg::~CAADlgFrameReplaceDlg()

    {
In the _CAADlgFrameReplaceDlg_ class destructor you have just to set NULL the `_pSettingFrameReplace` pointer.
CAADlgFrameReplaceDlg::~CAADlgFrameReplaceDlg()
        _pSettingFrameReplace = NULL ;

        ...
    }

---

[Top]
#### Retrieving the Last Values

The `Build` method can be divided in three parts:

The `Build` method can be divided in three parts:
    void CAADlgFrameReplaceDlg::Build()

    {
The `Build` method can be divided in three parts:
void CAADlgFrameReplaceDlg::Build()
       a/ Creating the Dialog objects and Arranging them

       b/ Retrieving the initial values

       c/ Defining the callbacks

    }

---
##### a/ Creating the Dialog objects and Arranging them
##### This part is described in the use case about the tabulation layout [2].
##### b/ Retrieving the Initial Values

To retrieve a value in a setting repository use the `ReadSetting` method. The arguments of this method are

  * The name of the attribute
  * The value of the attribute

```vbscript
```vbscript
For the use case:

```

```

  * `XCoord`, `YCoord` and `ZCoord` are the names of the attributes to initialize the X, Y and Z spinner respectively. The value of each attribute is a double
  * `ComboPointType `is the name of the attribute to initialize the first selected element in the combo list. The value of the attribute is an integer.

    ...
          double X(0.0f),Y(0.0f),Z(0.0f);
double X(0.0f),Y(0.0f),Z(0.0f);
```vbscript
          if ( NULL != _pSettingFrameReplace )

```

          {
double X(0.0f),Y(0.0f),Z(0.0f);
if ( NULL != _pSettingFrameReplace )
             _pSettingFrameReplace->**ReadSetting**("**XCoord** ",&X);
             _pSettingFrameReplace->ReadSetting("**YCoord** ",&Y);
             _pSettingFrameReplace->ReadSetting("**ZCoord** ",&Z);

          }

_pSettingFrameReplace->**ReadSetting**("**XCoord** ",&X);
_pSettingFrameReplace->ReadSetting("**YCoord** ",&Y);
_pSettingFrameReplace->ReadSetting("**ZCoord** ",&Z);
          _pSpinnerX ->**SetValue**(X,0);
          _pSpinnerY ->SetValue(Y,0);
          _pSpinnerZ ->SetValue(Z,0);

          _CurrentSelection = Coordinates ;
```vbscript
          if ( NULL != _pSettingFrameReplace )

```

          {
_pSpinnerZ ->SetValue(Z,0);
_CurrentSelection = Coordinates ;
if ( NULL != _pSettingFrameReplace )
             _pSettingFrameReplace->**ReadSetting**("**ComboPointType** ",&_CurrentSelection);

          }
_CurrentSelection = Coordinates ;
if ( NULL != _pSettingFrameReplace )
_pSettingFrameReplace->**ReadSetting**("**ComboPointType** ",&_CurrentSelection);
          _pComboPointType->**SetSelect**(_CurrentSelection,0);

    ...
    }

---
##### Where `_pSpinnerX, _pSpinnerY` and` _pSpinnerZ `are _CATDlgSpinner_ class instances created in the first part of the `Build` method, but not explained in this article. `_pComboPointType` is a _CATDlgCombo_ class instance created in the first part of the `Build `method, but also not explained in this article.
##### c/ Defining the Callbacks

    ...
       AddAnalyseNotificationCB (this,
```vbscript
                                   GetDiaCANCELNotification(),
```

                                   (CATCommandMethod)&CAADlgFrameReplaceDlg::**CloseWindow** ,
                                   NULL);

       AddAnalyseNotificationCB (this,
```vbscript
                                   GetDiaOKNotification(),
```

                                   (CATCommandMethod)&CAADlgFrameReplaceDlg::**CloseWindowOK** ,
                                   NULL);
       AddAnalyseNotificationCB (this,
```vbscript
                                   GetWindCloseNotification(),
```

                                   (CATCommandMethod)&CAADlgFrameReplaceDlg::**CloseWindow** ,
                                   NULL);

    ...

---

[Top]
#### Saving the Values

When the end user clicks OK, the dialog box must be closed. The current values of the Dialog objects should be saved. To save the values in the setting repository use the `WriteSetting` method. The arguments of this method are

  * The name of the attribute
  * The value of the attribute

    void CAADlgFrameReplaceDlg::CloseWindowOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
    {
       ...
void CAADlgFrameReplaceDlg::CloseWindowOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
```vbscript
       if ( NULL != _pSettingFrameReplace )

```

       {
void CAADlgFrameReplaceDlg::CloseWindowOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
if ( NULL != _pSettingFrameReplace )
```vbscript
```vbscript
           if ( NULL != _pComboPointType )

```

```

           {
```vbscript
if ( NULL != _pSettingFrameReplace )
```vbscript
if ( NULL != _pComboPointType )
```

              int PointType = _pComboPointType->GetSelect() ;
              _pSettingFrameReplace->**WriteSetting**("ComboPointType",&PointType);
```

           }

int PointType = _pComboPointType->GetSelect() ;
_pSettingFrameReplace->**WriteSetting**("ComboPointType",&PointType);
```vbscript
           if ( (NULL !=_pSpinnerX) && (NULL !=_pSpinnerY) && (NULL !=_pSpinnerZ) )

```

           {
_pSettingFrameReplace->**WriteSetting**("ComboPointType",&PointType);
if ( (NULL !=_pSpinnerX) && (NULL !=_pSpinnerY) && (NULL !=_pSpinnerZ) )
              double XVal = _pSpinnerX->GetValue() ;
              _pSettingFrameReplace->**WriteSetting**("XCoord",&XVal);
              double YVal = _pSpinnerY->GetValue() ;
              _pSettingFrameReplace->**WriteSetting**("YCoord",&YVal);
              double ZVal = _pSpinnerZ->GetValue() ;
              _pSettingFrameReplace->**WriteSetting**("ZCoord",&ZVal);

           }
    ...

---

To retrieve the values after the session closing use the `SaveRepository` method. The setting repository is saved in a setting file whose the name is those of the setting repository.

    ...
           _pSettingFrameReplace->**SaveRepository**();
     ...
    }

---

When the end user clicks Cancel or closes the window, there is nothing to save. The end user will retrieve the values before the current modifications.

When the end user clicks Cancel or closes the window, there is nothing to save. The end user will retrieve the values before the current modifications.
    void CAADlgFrameReplaceDlg::**CloseWindow**(CATCommand* cmd, CATNotification* evt,
                                                              CATCommandClientData data)

    {
     ...
    }

---

[Top]

* * *
### In Short

This use case explains how to use the setting file and repository to save and restore the Dialog object values.

[Top]

* * *
### References

[1] | [Setting Repositories and Attributes](../CAASysTechArticles/CAASysSettingRepositories.md)
---|---
[2] | [Creating Dialog Boxes Automatically Resizable](CAADlgSampleTabulation.md)
[3] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[Top]

* * *
### History

Version: **1** [Fev 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
