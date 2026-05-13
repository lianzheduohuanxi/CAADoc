---
title: "Untitled"
category: "use-case"
module: "CAADlgUseCases"
tags: ["CATInteractiveApplication", "CATISpecObject", "CAADialog", "CAADlgDemoApplication", "CAADlgFrameReplaceDlg", "CAASysTechArticles", "CAADocStyleSheets", "CAADlgTabulationFrameReplace1", "CAADlgDemoWindow", "CAADocRunSample", "CAASysSettingRepositories", "CAADlgDialogDemonstrator", "CAADlgSampleTabulation", "CAADlgTabulationFrameReplace3", "CAADocUseCases", "CAADlgTabulationFrameReplace2", "CAADlgFrameReplace"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleSettings.htmmd"
converted: "2026-05-11T11:27:02.782971"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to show you how to use a setting file and
repository [1] to store and retrieve the values of
Dialog Objects. The setting repository being the memory copy of a setting
file.

[Top]

### The CAADlgFrameReplace Use Case

CAADlgFrameReplace is a use case of the CAADialog.edu framework that
illustrates Dialog and System framework capabilities.

[Top]

#### What Does CAADlgFrameReplace Do

CAADlgFrameReplace simulates the  "Point Definition" V5 Dialog
box. It creates the "Frame Replacement Demonstrator" Dialog box that
you can see just below. The end user can select the mode of creation for the
point: by coordinate values, by the center of a circle or between two points [2].  

    
    
      
    
    
      
    
  

When the end user clicks **OK**, the following values are kept:

  
- The "`Point Type`" ( an integer )
  
- The point coordinates (`X, Y, Z`)  (three double)

The others values are not kept, for the following reasons:

  
- `Circle`, `P1` and `P2` : The values, in
    a V5 context, will be a string, the *GetDisplayName* of a *CATISpecObject.*
    You can save a string, but it is not possible to save a *CATISpecObject*
    instance, so there is no need to keep the value of these fields.
  
- `Ratio` : The Dialog object is a *CATDlgEditor* class. It
    is the only one Dialog object which natively keeps the last values. You
    retrieve them with the up and down arrows. 

When the end user clicks **Cancel** or **closes** the window, the
current values of the Dialog objects are not kept. 

[Top]

#### How to Launch CAADlgFrameReplace

To launch the use case, you will need to set up the build time environment,
then compile CAADlgDialogDemonstrator along with its prerequisites, set up the
run time environment, and then execute the use case [3].

`mkrun -c CAADlgDialogDemonstrator `

When the `CAADlgDialogDemonstrator` application is launched:

  
- On the **Tabulation**  menu click **Frame Replacement**
  
- Click **Circle Center **in the combo
  
- Click **OK**
  
- On the **Tabulation**  menu click **Frame Replacement **
  
- Click **Coordinates **in the combo
  
- Enter a value in **X**, **Y** and **Z** field 
  
- Click **OK **
  
- On the **Tabulation**  menu click **Frame Replacement **
  
- Click **Between **in the combo
  
- Enter different values in the **Ratio** field  
  
- Click **OK **
  
- On the **Tabulation**  menu click **Frame Replacement **
  
- On the **Ratio** field retrieve the different value with the **up **and**
    down** arrows 
  
- On the **Tabulation**  menu click **Frame Replacement**
  
- Click **Coordinates **in the combo
  
- Enter a value in **X**, **Y** and **Z** field 
  
- Click **Cancel**
  
- On the **Tabulation**  menu click **Frame Replacement **
  
- On the** File** menu click** Exit**

[Top]

#### Where to Find the CAADlgFrameReplace Code

The CAADlgFrameReplace use case is made of several classes located in the
CAADlgDialogDemonstrator.m module of the CAADialog.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

In the LocalInterfaces and src directory, you will find the following files:

  
- CAADlgDemoApplication.h/CAADlgDemoApplication.cpp: The *"DialogDemonstrator"*
    application definition. ( a *CATInteractiveApplication* )
  
- CAADlgDemoWindow.h/CAADlgDemoWindow.cpp : The *CATDlgDocument*
    definition.
  
- CAADlgFrameReplaceDlg.h/CAADlgFrameReplaceDlg.cpp : The "Frame
    Replacement Demonstrator" dialog box definition

[Top]

### Step-by-Step

There are four logical steps in the use case:

  
- Creating the Class Header
  
- Retrieving the Setting
    Repository
  
- Retrieving the Last Values
  
- Saving the Values

[Top]

#### Creating the Class Header

The main contents of the CAADlgFrameReplaceDlg.h file is the following:

where

  
- The `Build` method enables you to construct the Dialog objects
    and to initialize them with the values saved in the setting file. 
  
- The `CloseWindowOK` method is a callback method which is called
    when the end user pushes the Ok Button
  
- The `CloseWindow` method is a callback method which is called
    when the end user pushes the Cancel Button or closes the window.
  
- `_pSettingFrameReplace` is a *CATSettingRepository* class
    pointer. It will be initialized in the constructor class. You should not
    release this pointer. 

#### Retrieving the Setting
Repository

In the *CAADlgFrameReplaceDlg* class constructor you retrieve a setting
repository pointer thanks to the static `GetRepository` method. The
first and unique argument of this method is the name of the setting file. 

In the *CAADlgFrameReplaceDlg* class destructor you have
just to set NULL the `_pSettingFrameReplace` pointer. 

[Top]

#### Retrieving the Last Values

The `Build` method can be divided in three parts:

##### a/ Creating the
Dialog objects and Arranging them

##### This part is described in the use case about the tabulation layout [2].

##### b/ Retrieving the Initial Values

To retrieve a value in a setting repository use the `ReadSetting`
method. The arguments of this method are

  
- The name of the attribute
  
- The value of the attribute

For the use case:

  
- `XCoord`, `YCoord` and `ZCoord` are the
    names of the attributes to initialize the X, Y and Z spinner respectively.
    The value of each attribute is a double
  
- `ComboPointType `is the name of the attribute to initialize the
    first selected element in the combo list. The value of the attribute is an
    integer.

##### Where `_pSpinnerX, _pSpinnerY` and` _pSpinnerZ `are *CATDlgSpinner*
class instances created in the first part of the `Build` method, but
not explained in this article. `_pComboPointType` is a *CATDlgCombo*
class instance created in the first part of the `Build `method, but
also not explained in this article. 

##### c/ Defining the Callbacks

[Top]

#### Saving the Values

When the end user clicks OK, the dialog box must be closed. The current
values of the Dialog objects should be saved. To save the values in the setting
repository use the `WriteSetting` method. The arguments of this
method are

  
- The name of the attribute
  
- The value of the attribute

 

To retrieve the values after the session closing use the `SaveRepository`
method. The setting repository is saved in a setting file whose the name is
those of the setting repository.  

When the end user clicks Cancel or closes the window, there is nothing to
save. The end user will retrieve the values before the current
modifications. 

[Top]

---

### In Short

This use case explains how to use the setting file and repository to save and
restore the Dialog object values. 

[Top]

---

### References

---

### History

---

*Copyright  2003, Dassault Systmes. All rights reserved.*

```vbscript
#include &quot;CATDlgDialog.h&quot;   // To derive from
...
class CATSettingRepository ; // To manage values

class CAADlgFrameReplaceDlg: public CATDlgDialog
{
  ...
  public:

      CAADlgFrameReplaceDlg(CATDialog * pParentDlg);
      virtual ~CAADlgFrameReplaceDlg(#);

      void Build (#);

  private:
      ...
      virtual void CloseWindowOK (CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);

      virtual void CloseWindow (CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
     ...
  private:
     ...
     CATSettingRepository * _pSettingFrameReplace ;

};
```

```vbscript
CAADlgFrameReplaceDlg::CAADlgFrameReplaceDlg(CATDialog * pParentDlg) :
  CATDlgDialog (pParentDlg,&quot;CAADlgFrameReplaceDlg&quot;,
      CATDlgWndAutoResize | CATDlgWndBtnOKCancel |CATDlgWndNoResize ),
      _CurrentSelection(0),_pComboPointType(NULL),_pSpinnerX(NULL),
      _pSpinnerY(NULL),_pSpinnerZ(NULL)
{
   ...
   _pSettingFrameReplace = CATSettingRepository::GetRepository(&quot;CAADlgFrameReplaceDlg&quot; );
}
```

```vbscript
CAADlgFrameReplaceDlg::~CAADlgFrameReplaceDlg(#)
{
    _pSettingFrameReplace = NULL ;
    ...
}
```

```vbscript
void CAADlgFrameReplaceDlg::Build(#)
{
   a/ Creating the Dialog objects and Arranging them

   b/ Retrieving the initial values
 
   c/ Defining the callbacks
}
```

```vbscript
...
      double X(0.0f),Y(0.0f),Z(0.0f);
      if ( NULL != _pSettingFrameReplace )
      {
         _pSettingFrameReplace-&gt;ReadSetting(&quot;XCoord&quot;,&amp;X);
         _pSettingFrameReplace-&gt;ReadSetting(&quot;YCoord&quot;,&amp;Y);
         _pSettingFrameReplace-&gt;ReadSetting(&quot;ZCoord&quot;,&amp;Z);
      }
      
      _pSpinnerX -&gt;SetValue(X,0);
      _pSpinnerY -&gt;SetValue(Y,0);
      _pSpinnerZ -&gt;SetValue(Z,0);
      
      _CurrentSelection = Coordinates ;
      if ( NULL != _pSettingFrameReplace )
      {
         _pSettingFrameReplace-&gt;ReadSetting(&quot;ComboPointType&quot;,&amp;_CurrentSelection);
      }
      _pComboPointType-&gt;SetSelect(_CurrentSelection,0);
...
}
```

```vbscript
...
   AddAnalyseNotificationCB (this, 
                               GetDiaCANCELNotification(#),
                               (CATCommandMethod)&amp;CAADlgFrameReplaceDlg::CloseWindow,
                               NULL);

   AddAnalyseNotificationCB (this, 
                               GetDiaOKNotification(#),
                               (CATCommandMethod)&amp;CAADlgFrameReplaceDlg::CloseWindowOK,
                               NULL);
   AddAnalyseNotificationCB (this, 
                               GetWindCloseNotification(#),
                               (CATCommandMethod)&amp;CAADlgFrameReplaceDlg::CloseWindow,
                               NULL);
...
```

```vbscript
void CAADlgFrameReplaceDlg::CloseWindowOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   ...
   if ( NULL != _pSettingFrameReplace )
   {
       if ( NULL != _pComboPointType )
       {
          int PointType = _pComboPointType-&gt;GetSelect(#) ;
          _pSettingFrameReplace-&gt;WriteSetting(&quot;ComboPointType&quot;,&amp;PointType);
       }

       if ( (NULL !=_pSpinnerX) &amp;&amp; (NULL !=_pSpinnerY) &amp;&amp; (NULL !=_pSpinnerZ) )
       {
          double XVal = _pSpinnerX-&gt;GetValue(#) ;
          _pSettingFrameReplace-&gt;WriteSetting(&quot;XCoord&quot;,&amp;XVal);
          double YVal = _pSpinnerY-&gt;GetValue(#) ;
          _pSettingFrameReplace-&gt;WriteSetting(&quot;YCoord&quot;,&amp;YVal);
          double ZVal = _pSpinnerZ-&gt;GetValue(#) ;
          _pSettingFrameReplace-&gt;WriteSetting(&quot;ZCoord&quot;,&amp;ZVal);
       }
...
```

```vbscript
...
       _pSettingFrameReplace-&gt;SaveRepository(#);
 ...
}
```

```vbscript
void CAADlgFrameReplaceDlg::CloseWindow(CATCommand* cmd, CATNotification* evt, 
                                                          CATCommandClientData data)
{
 ...
}
```