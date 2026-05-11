---
title: "Untitled"
category: "use-case"
module: "CAADlgUseCases"
tags: ["CAADocStyleSheets", "CAADlgDemoWindow", "CAADlgGridLayout", "CAADlgTabulationFrameReplaceTech1", "CAADlgTabulationMoreLess1", "CAADialog", "CAADlgDemoApplication", "CAADlgTabulationMoreLessTech3", "CAADlgTabulationRadioTech2", "CAADlgMoreRadioDlg", "CAADocUseCases", "CAADlgTabulationRadio1", "CAADlgTabulationRadio2", "CATInteractiveApplication", "CAADlgFrameReplaceDlg", "CAADlgMoreButtonDlg", "CAADlgTabulationMoreLessTech1", "CAADlgTabulationMoreLessTech2", "CAADlgResources", "CAADlgTabulationRadioTech1"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleTabulation.htm"
converted: "2026-05-11T11:27:02.795626"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to show you how to create Dialog boxes with dynamic
frames. The frames appear and disappear and the dimensions of the dialog box are
automatically redefined. For such behavior the frame positioning must be done by
a tabulation
layout [1] and not by a grid layout [2].

[Top]

### The CAADlgTabulation Use Case

CAADlgTabulation is a use case of the CAADialog.edu framework that
illustrates Dialog framework capabilities.

[Top]

#### What Does CAADlgTabulation Do

CAADlgTabulation use case creates three Dialog boxes:

  
- 

The "**More/Less Push Button Demonstrato**r" Dialog box
  
      
      
        
      
    
  
  

When the end user clicks the "More" button, the Dialog box is
  expanded and when it clicks on the "Less" button, the dialog box
  retrieves its original size.
  
- 

The "**More & Radio Button Demonstrator**" Dialog box
  
      
    
  
  

When the end user select the "without frame" radio button, no
  frame is displayed. 
  
      
    
  
  

When the end user selects the "With more frame A" radio button,
  the frame entitled "Frame A" is displayed on the right side.
  
      
    
  
  

When the end user selects the "With more frame B" radio button,
  the frame entitled "Frame B" is displayed on the right side. 
  
- The "**Frame Replacement Demonstrator**" Dialog box
  

According to the selected value in the combo, the frame under the
  "Combo Frame" frame is not
  the same: "Coordinates Frame", "Circle Frame" or "
  Between Frame". 

  
      
      
        
      
      
        
      
    
  

To obtain such behavior, the frames must be attached in their
container by a tabulation layout. On the pictures below, the tabulations are
represented by thick lines and the frame's attachments are represented by a
green rectangular box.

  
- 
    

The "**More/Less Push Button Demonstrato**r" Dialog box
  
      
      
        
      
    
  
  

The "Left More Frame" frame is always visible and attached to the
  first (0) vertical line. The "Right More Frame" frame is 
  

  
- Invisible and detached when the dialog box has its original size. 
    Fig.1a and Fig.4a
  
- 

Visible and attached to the second (10) vertical line when the dialog box
    is extended.  Fig.1b and Fig.4b
  
    
- 
    

The "**More & Radio Button Demonstrator**" Dialog box
  

It is similar to the previous dialog box:
  
      
      
        
      
    
  
  

The "Radio Button Frame" frame is always visible and attached to
  the first (0) vertical line. 
  

  
- If the "Without frame" radio button is checked -  Fig.
    2a 
  

The "Frame A" and the "Frame B" are invisible and
  detached. Fig. 5a
  
- If the "With more frame A"  radio button is checked - 
    Fig. 2b 
  

The "Frame A" is visible and attached to the second (10) vertical line,
  and the "Frame B" is still invisible and detached. Fig.
  5b

  
- If the "With more frame B"  radio button is checked - 
    Fig. 2c
    

The "Frame B" is visible and attached to the second (10) vertical line,
  and the "Frame A" is yet invisible and detached. Fig.
    5b
  
  
- 
    

The "**Frame Replacement Demonstrator**" Dialog box
    

In this case the attachments are horizontal.
  
  

The "Combo Frame" frame is always visible and attached to
  the first (0) horizontal line. The frame attached to the second (5)
  horizontal line is the frame entitled either "Coordinates Frame" (Fig.
  3a) or
  "Circle Frame" (Fig. 3b) or ''Between Frame"
  (Fig. 3c) . When one of these three
  frames is attached and visible, the two others are invisible and detached.

Inside the frames entitled  "Left More Frame",
"Right More Frame", "Frame A" and so on, you can use the
grid layout [2] to locate the different
components. 

[Top]

#### How to Launch CAADlgTabulation

To launch the use case, you will need to set up the build time environment,
then compile CAADlgDialogDemonstrator along with its prerequisites, set up the run time
environment, and then execute the use case [3].

`mkrun -c CAADlgDialogDemonstrator `

When the `CAADlgDialogDemonstrator` application is launched:

  
- On the **Tabulation** menu click **More & Radio Button**
  
- Click **With more frame A**
  
- Click**  With more frame B**
  
- Click **Without frame**
  
- Click **OK **or** Cancel**
  
- On the **Tabulation**  menu click **More/Less Push Button**
  
- Click **More**
  
- Click** Less**
  
- Click **OK **or** Cancel**
  
- On the **Tabulation**  menu click **Frame Replacement**
  
- Click **Circle Center **in the combo
  
- Click **Between **in the combo
  
- Click **Coordinates **in the combo
  
- Click **OK **or** Cancel**
  
- On the** File** menu click** Exit**

[Top]

#### Where to Find the CAADlgTabulation Code

The CAADlgTabulation use case is made of several classes located in
the CAADlgDialogDemonstrator.m module of the CAADialog.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

In the LocalInterfaces and src directory, you will find the following files:

  
- CAADlgDemoApplication.h/CAADlgDemoApplication.cpp: The *"DialogDemonstrator"* application definition. ( a *CATInteractiveApplication*
  )
  
- CAADlgDemoWindow.h/CAADlgDemoWindow.cpp : The *CATDlgDocument* definition.
  
- CAADlgMoreButtonDlg.h/CAADlgMoreButtonDlg.cpp: The "More Button Demonstrator" dialog box definition. 
  
- CAADlgFrameReplaceDlg.h/CAADlgFrameReplaceDlg.cpp : The "Frame
    Replacement Demonstrator" dialog box definition
  
- CAADlgMoreRadioDlg.h/CAADlgMoreRadioDlg.cpp : The "More Radio Demonstrator" dialog box definition. 

[Top]

### Step-by-Step

There are three main steps to define the three Dialog boxes of the CAADlgTabulation
use case:

  
- Defining
    the Class Constructor
  
- Defining
    the Build Method 
  
- Defining
    the Callback Method

[Top]

#### Defining
the Class Constructor 

Each Dialog box is a class deriving from the *CATDlgDialog* class. The
arguments of the constructor are as follows:

  
- `pParentDlg` , the Dialog object which is the parent of the
    Dialog box.
  
- `CAADlgMoreButtonDlg, `the identifier of the Dialog box. This
    identifier is not used for the resources.
  
- The style is the concatenation of three values:
    

      
- `CATDlgWndBtnOKCancel:` The recommended option to have the
        OK and Cancel buttons
      
- `CATDlgWndAutoResize:` The Dialog box is automatically
        resized with respect of its content's modifications.
      
- `CATDlgWndNoResize``:` The Dialog Box can not be
        resized by the end user. It is recommended option with the `CATDlgWndAutoResize`
        style
      
- The `CATDlgGridLayout` style has not been used, and **must
        not be used**, to benefit of the attachment.
    
  

 

[Top]

#### Defining
the Build Method 

The contents of this section depends on the Dialog box. 

  
- The "**More/Less Push Button Demonstrato**r" Dialog box
  
- The "**More & Radio Button Demonstrator**" Dialog box
  
- 

The "**Frame Replacement Demonstrator**" Dialog box

  
- The "**More/Less Push Button Demonstrato**r" Dialog box
  
  

**Creating Dialog Objects**

  

  
- 

The "Left More Frame" frame is `pFrameLeftMore` a *CATDlgFrame*
    pointer; the argument of the constructor are the following:
  

  
- `this: `The frame is positioned in the Dialog box 
  
- `FrameLeftMore `is the identifier of frame. It will be useful
    to set resources [4] 
    
- 

The ` CATDlgGridLayout`  style enables to position its contents by a grid layout 
  
  
- 

The "Base Options Frame" frame is `pFrameBase` a *CATDlgFrame*
    pointer; the argument of the constructor are the following:
  

  
- `pFrameLeftMore: `The frame is positioned in the "Left More Frame" frame 
  
- `FrameBase` is the identifier of frame. It will be useful
    to set resources [4] 
    
- 

The ` CATDlgGridLayout`  style enables to position its
      contents by a grid layout
  
  
- The push button is `pPushButtonMore` a *CATDlgPushButton*
    pointer
  

`PushButtonMore` is the identifier of the push button. Its title
  is assigned by retrieving the "More" and "Less" NLS
  strings in the CAADlgMoreButtonDlg.CATNLs file [4]. 
  
- 

The "Right More Frame" frame is ` _pFrameRightMore` a *CATDlgFrame*
    pointer; the argument of the constructor are the following:
  

  
- `this: `The frame is positioned in the Dialog box 
  
- `FrameRightMore `is the identifier of frame. It will be useful
    to set resources [4] 
    
- 

The ` CATDlgGridLayout `style enables to position its
      contents by a grid layout 
  
  
  

**Arranging Dialog Objects**

For the "More/Less" Dialog box, the
layout is the following:

Inside the "Left More Frame" there are always a frame entitled
"Base Options Frame" located in (0,0) and a push button located in
(1,0). In the "Base Options Frame" frame you set all the options
always available whereas in the "Right More Frame" you set only the
"more" options.  

  

  
- 

The `pFrameLeftMore`  frame is always attached to the first
    (0) tabulation of the Dialog box. It is done with the `SetVerticalAttachment`
    method: 
  

  
- `0`: The index value. Note that the value of the index is not important. You must just
  respect an increasing order from left to right.
  
- `CATDlgTopOrLeft:` the frame is attached to the left side.See Fig.
    4a
  
- `pFrameLeftMore`: The frame's pointer attached to the tabulation
  
- 

`NULL`: To end the list of attachments. ( It is a method with no constant
    argument)
  
  
-  `pFrameBase` is located in (0,0) in the "Left More Frame" frame.
  
- `pPushButtonMore` is located in (1,0) in the "Left More Frame" frame and is
  right justified.
  
- `_pFrameRightMore` is not attached and is not visible. 
  
  

**The Callback Definition**

  

To be advised that the end user has clicked on the More button you set a
  callback thanks to the `AddAnalyseNotificationCB` method:
  

  
- `pPushButtonMore `is the *CATDlgPushButton* class
  pointer on the More Button. 
  
-  `GetPushBActivateNotification`
    is method returning the notification class when a push button is pushed. 
  
- 

`OnPushButtonMorePushBActivateNotification`
    is the method explained in the "Defining
  the Callback Methods" section. 
  
  
- The "**More & Radio Button Demonstrator**" Dialog box

  

**Creating Dialog Objects**

  

The three frames, `pFrameMain, _pFrameDetailA `
 and ` _pFrameDetailB`
  are created in the same way:
  

  
-   `this: `the frame is positioned in the Dialog box
  
- `"FrameMain", "FrameDetailA"`
 or ` "FrameDetailB"`
    are the frame's identifiers. It will be useful
    to set resources [4] 
  
- The ` CATDlgGridLayout`  style enables to position their contents by a grid layout 
  
  

**Arranging Dialog Objects**
  -  Fig. 5a

  

  
- 

The ` "FrameMain"`  frame, pointed by `pFrameMain`, is visible and attached to the first
    (0) vertical tabulation. It is done thanks to the `
    SetVerticalAttachment`  method:
    

  
- `0`: The index value. Note that the value of the index is not important. You must just
  respect an increasing order from left to right.
  
- `CATDlgTopOrLeft:` the frame is attached to the left side.
  
- `pFrameMain`: The frame's pointer attached to the tabulation
  
- 

`NULL`: To end the list of attachments. ( It is a method with no constant
    argument)
    
  
- 

The ` "FrameDetailA"`
 and ` "FrameDetailB"`
    frames, pointed by `_pFrameDetailA` and `_pFrameDetailB`
    respectively, are hidden and not attached. 
  
  

**The Callbacks Definition**

  

To be advised that the end user has clicked on a radio button you set callbacks thanks to the `AddAnalyseNotificationCB` method:
  

  
-  `pRadioButtonND `is the *CATDlgRadioButton* class
  pointer on the first radio button. 
  
-  `GetRadBModifyNotification`**
  **
    is the method returning the notification class when the radio button state changes:
  when the end user clicks on the button and when it chooses another radio
  button. 
  
- 

**`OnRadioButtonNDRadBModifyNotification` **
    is the method explained in the "Defining
  the Callback Methods" section. 
  

  

Same thing for the two other radio buttons.

  
- The "**Frame Replacement Demonstrator**" Dialog box

  

**Creating Dialog Objects**

  

The four `pFrameCombo, pFrameCoord, pFrameCircleCenter` and
  `pFrameBetween` frames are created on the same way:
  

  
- `this: `The frame is positioned in the Dialog box
  
- `"FrameCombo", "FrameCoord", "FrameCircleCenter" or "FrameBetween"`
    are the frame's identifiers. It will be useful
    to set resources [4] 
  
- The ` CATDlgGridLayout`  style enables to position their contents by a grid layout
  
  

`_pListFrame` is an array of *CATDlgFrame*  instances declared as data
  member of the *CAADlgFrameReplaceDlg* class. It keeps the list of frames
  to switch. See its usage in the "Defining
the Callback Method" section 
  

**Arranging Dialog Objects**  -
  Fig. 6

  

  
- `

The "FrameCombo"`  frame, pointed by `pFrameCombo`, is visible and attached to the first
    (0) horizontal tabulation thanks to the `SetHorizontalAttachment`
    method:` `
    

  
- `0`: The index value. 
  
- `CATDlgTopOrLeft:` the frame is attached to the top side.
  
- pFrameCombo: The frame's pointer attached to the tabulation
  
- 

`NULL`: To end the list of attachments. 
    
  
- `_pListFrame` is a data member of the *CAADlgFrameReplaceDlg*
  class which keeps the list of frames to switch. See the previous
    section 
  
-  `_CurrentSelection`
  is also a data member to keep the current attached frame on the second
  horizontal tabulation. 
  
-  The three frames are set invisible.  
  
- 

The current frame (one among the three possible) is set visible and attached to the second
    (5) horizontal tabulation thanks to the `SetHorizontalAttachment`
    method:
    

      
- `5`: The index value. 
      
- `CATDlgTopOrLeft:` the frame is attached to the top side.
      
- `pFrameCombo`: The frame's pointer attached to the tabulation
      
- 
        

`NULL`: To end the list of attachments.  
          
  

  

**Defining Callback**

  

To be advised that the end user has select a new item in the combo list, you set
  a callback thanks to the `AddAnalyseNotificationCB` method:
  

  
-  `_pComboPointType`** **is the *CATDlgCombo* class
  pointer.  It is a pointer to an object located in the "FrameCombo"
  frame but not explained here.  
  
-  `GetComboSelectNotification`** **
    is the method returning the notification class when
  a selection in the combo occurs. 
  
- 

`OnComboSelectNotification`**
  **
    is the method explained in the "Defining
  the Callback Methods" section. 
  

[Top]

#### Defining
the Callback Method 

In this section, we describe the methods which are called when the frame
layout must be changed.  

  
- The "**More/Less Push Button Demonstrato**r" Dialog box
  
- The "**More & Radio Button Demonstrator**" Dialog box
  
- 

The "**Frame Replacement Demonstrator**" Dialog box

  
- The "**More/Less Push Button Demonstrator**" Dialog box
  

The `OnPushButtonMorePushBActivateNotification` method is called when the end user clicks on the
  More/Less push 
  button.

  

`_IsMoreWindowOpen` is a data member of the *CAADlgMoreButtonDlg*
  class. It is a *CATBoolean* value set TRUE when the right frame is opened
  and FALSE otherwise. The value is initialized to FALSE in the class constructor.
  

  
- To hide the right frame ( `_IsMoreWindowOpen` = TRUE)
  

`_pFrameRightMore` the right frame is detached from its tabulation and
  hidden. The title of the push button becomes "More".
  
- To show the right frame ( `_IsMoreWindowOpen` = FALSE)
  

`_pFrameRightMore `the right frame is attached to the second vertical
  tabulation and shown. See Fig. 4b. The title of the
  push button becomes "Less".

  
  
- The "**More & Radio Button Demonstrator**" Dialog box
  

The `OnRadioButtonDARadBModifyNotification` method is called
  when the end user selects or deselects the "With more frame A" radio
  button. 

  

When the state of the button is:
   

   
- `CATDlgCheck: `The frame is attached to the second (10) vertical tabulation and the frame
   is shown- See Fig 5b 
  
- Otherwise `(CATDlgUncheck): `The current frame is detached and hidden.

  

  

The `OnRadioButtonDBRadBModifyNotification` method is called
  when the end user selects or deselects the "With more frame B" radio
  button. The contents of this method is similar to the previous one. 

  

The `OnRadioButtonNA``RadBModifyNotification` method
  is called when the end user selects or deselects the "Without frame"
  radio button. The contents of this method is empty once there is no frame to
  attach. 

  
- The "**Frame Replacement Demonstrator**" Dialog box
  

The `OnComboSelectNotification` method is called when the
  end user selects a new element in the combo list. 

The code is the following: See Fig. 6

  
- Retrieving the frame to detach : The ` _CurrentSelection` frame in the ` _pListFrame`
    table. See the Build method
  
- Detaching the old frame (`_CurrentSelection`) from its
    tabulation and hidding it 
  
- Retrieving the frame to attach: The current value in the combo list, `NewCurrentSelection` 
  
- Attaching the `NewCurrentSelection `frame to the
    fit tabulation and showing it

  

`NewCurrentSelection `becomes the new current index value kept
  in the `_CurrentSelection `data member. 

[Top]

 

---

### In Short

This use case explains how to use the tabulation layout to create dynamic
dialog boxes, such as a more and less dialog box. 

[Top]

---

### References

---

### History

---

*Copyright  2003, Dassault Systmes. All rights reserved.*



```vbscript
CAADlgMoreButtonDlg::CAADlgMoreButtonDlg(CATDialog * pParentDlg) :
  CATDlgDialog (pParentDlg,&quot;CAADlgMoreButtonDlg&quot;, CATDlgWndBtnOKCancel |
                                                  CATDlgWndAutoResize |
                                                  CATDlgWndNoResize ),
  ...
{
   ...
}
```

```vbscript
void CAADlgMoreButtonDlg::Build()
{
   a/ Creating Dialog Objects
   
   b/ Arranging Dialog Objects
   
   c/ Defining Callbacks
}
...
```

```vbscript
...
   CATDlgFrame * pFrameLeftMore = new CATDlgFrame(this, &quot;FrameLeftMore&quot;, 
                                                        CATDlgGridLayout );
                                           
      CATDlgFrame * pFrameBase = new CATDlgFrame(pFrameLeftMore, &quot;FrameBase&quot;, 
                                                                 CATDlgGridLayout );
                                                     
         ... The FrameBase contents is not detailed

      CATDlgPushButton * pPushButtonMore = new CATDlgPushButton(pFrameLeftMore, 
                                                &quot;PushButtonMore&quot;);
      
      _MoreMsg = CATMsgCatalog::BuildMessage(&quot;CAADlgMoreButtonDlg&quot;,&quot;ButtonMore&quot;,
                                                    NULL,0,&quot;More&gt;&gt;&quot;);
      _LessMsg = CATMsgCatalog::BuildMessage(&quot;CAADlgMoreButtonDlg&quot;,&quot;ButtonLess&quot;,
                                                    NULL,0,&quot;Less&gt;&gt;&quot;);                                       
      pPushButtonMore-&gt;SetTitle(_MoreMsg);

   _pFrameRightMore = new CATDlgFrame(this, &quot;FrameRightMore&quot;, CATDlgGridLayout );
   
      ... The FrameRightMore contents is not detailed
...
```

```vbscript
...
   SetVerticalAttachment(0, CATDlgTopOrLeft, pFrameLeftMore,NULL);
   pFrameBase -&gt; SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
   pPushButtonMore -&gt; SetGridConstraints(1, 0, 1, 1, CATGRID_RIGHT);
   _pFrameRightMore-&gt;SetVisibility(CATDlgHide);
...
```

```vbscript
...
   AddAnalyseNotificationCB  (pPushButtonMore, 
                              pPushButtonMore-&gt;GetPushBActivateNotification(),
     (CATCommandMethod)&amp;CAADlgMoreButtonDlg::OnPushButtonMorePushBActivateNotification,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
                   NULL);
...
```

```vbscript
...
void CAADlgMoreRadioDlg::Build()
{
  a/ Creating Dialog Objects

  b/ Arranging Dialog Objects
  
  c/ Defining Callbacks 
}
...
```

```vbscript
... 
  CATDlgFrame * pFrameMain = new CATDlgFrame(this, &quot;FrameMain&quot;, CATDlgGridLayout );
  
     ... FrameMain contents not explained

  _pFrameDetailA = new CATDlgFrame(this, &quot;FrameDetailA&quot;, CATDlgGridLayout);
  
     ... FrameDetailA contents not explained
     
  _pFrameDetailB = new CATDlgFrame(this, &quot;FrameDetailB&quot;, CATDlgGridLayout);
 
     ... FrameDetailB contents not explained
...
```

```vbscript
...
  SetVerticalAttachment(0, CATDlgTopOrLeft,pFrameMain,NULL);
  _pFrameDetailB-&gt;SetVisibility(CATDlgHide); 
  _pFrameDetailA-&gt;SetVisibility(CATDlgHide);
...
```

```vbscript
...
   AddAnalyseNotificationCB (pRadioButtonND, 
                               pRadioButtonND-&gt;GetRadBModifyNotification(),
     (CATCommandMethod)&amp;CAADlgMoreRadioDlg::OnRadioButtonNDRadBModifyNotification,
                               NULL);
   AddAnalyseNotificationCB (pRadioButtonDB, 
                               pRadioButtonDB-&gt;GetRadBModifyNotification(),
     (CATCommandMethod)&amp;CAADlgMoreRadioDlg::OnRadioButtonDBRadBModifyNotification,
                               NULL);

   AddAnalyseNotificationCB (pRadioButtonDA, 
                               pRadioButtonDA-&gt;GetRadBModifyNotification(),
     (CATCommandMethod)&amp;CAADlgMoreRadioDlg::OnRadioButtonDARadBModifyNotification,
                               NULL);
...
```

```vbscript
...
void CAADlgFrameReplaceDlg::Build()
{
   a/ Creating Dialog objects 

   b/ Arranging the Dialog Objects
   
   c/ Defining Callback 
}
```

```vbscript
...
   CATDlgFrame * pFrameCombo = new CATDlgFrame(this, &quot;FrameCombo&quot;,
                                                     CATDlgGridLayout );                                        
      ... FrameCombo contents not explained
      
   CATDlgFrame * pFrameCoord = new CATDlgFrame(this, &quot;FrameCoord&quot;, 
                                                     CATDlgGridLayout );                                          
      ... FrameCoord contents not explained

   CATDlgFrame * pFrameCircleCenter = new CATDlgFrame(this, &quot;FrameCircleCenter&quot;, 
                                                            CATDlgGridLayout );                                            
   _pListFrame[CircleCenter] = pFrameCircleCenter ;
   
      ... FrameCircleCenter contents not explained

   CATDlgFrame * pFrameBetween = new CATDlgFrame(this, &quot;FrameBetween&quot;, 
                                                       CATDlgGridLayout );                                     
   _pListFrame[Between] = pFrameBetween ;
   
      ... FrameBetween contents not explained
...
```

```vbscript
...   
   SetHorizontalAttachment(0,CATDlgTopOrLeft,pFrameCombo,NULL);
   _CurrentSelection = 0 ;
   ... 
   pFrameCoord-&gt;SetVisibility(CATDlgHide);
   pFrameCircleCenter-&gt;SetVisibility(CATDlgHide);
   pFrameBetween-&gt;SetVisibility(CATDlgHide);
   
   SetHorizontalAttachment(5,CATDlgTopOrLeft,_pListFrame[_CurrentSelection],NULL);
   _pListFrame[_CurrentSelection]-&gt;SetVisibility(CATDlgShow);
...
```

```vbscript
...
   AddAnalyseNotificationCB (_pComboPointType, 
                 _pComboPointType-&gt;GetComboSelectNotification(),
          (CATCommandMethod)&amp;CAADlgFrameReplaceDlg::OnComboSelectNotification,
                               NULL);
...
```

```vbscript
...
void CAADlgMoreButtonDlg::OnPushButtonMorePushBActivateNotification(CATCommand* cmd, 
                                   CATNotification* evt, CATCommandClientData data)
{
   CATDlgPushButton * pButton = (CATDlgPushButton *) cmd ;
   if ( (NULL != pButton ) &amp;&amp; (NULL !=_pFrameRightMore) )
   {
      if( TRUE == _IsMoreWindowOpen)
      {
         ResetAttachment(_pFrameRightMore);         
         _pFrameRightMore-&gt;SetVisibility(CATDlgHide);         

         pButton-&gt;SetTitle (_MoreMsg);

         _IsMoreWindowOpen= FALSE;
      }else
      {
         SetVerticalAttachment(10, CATDlgTopOrLeft, _pFrameRightMore, NULL);
         _pFrameRightMore-&gt;SetVisibility(CATDlgShow);         

         pButton-&gt;SetTitle (_LessMsg);

         _IsMoreWindowOpen = TRUE;
      }
   }
}
...
```

```vbscript
...
void CAADlgMoreRadioDlg::OnRadioButtonDARadBModifyNotification(CATCommand* cmd, 
                                CATNotification* evt, CATCommandClientData data)
{
  CATDlgRadioButton * pRadioButton = (CATDlgRadioButton *) cmd ;
  if ( (NULL != _pFrameDetailA) &amp;&amp; ( NULL != pRadioButton) )
  {
     if (pRadioButton-&gt;GetState() == CATDlgCheck) 
     {
        SetVerticalAttachment(10, CATDlgTopOrLeft, _pFrameDetailA, NULL);
        _pFrameDetailA-&gt;SetVisibility(CATDlgShow);         
     } 
     else 
     {
        ResetAttachment(_pFrameDetailA);         
       _pFrameDetailA-&gt;SetVisibility(CATDlgHide);         
     }
  }
}
...
```

```vbscript
...
void CAADlgFrameReplaceDlg::OnComboSelectNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
   if ( NULL != _pComboPointType )
   {
      ResetAttachment(_pListFrame[_CurrentSelection]);
      _pListFrame[_CurrentSelection]-&gt;SetVisibility(CATDlgHide);
      
      int NewCurrentSelection = _pComboPointType-&gt;GetSelect() ;
      SetHorizontalAttachment(5, CATDlgTopOrLeft
                                     , _pListFrame[NewCurrentSelection], NULL);
      _pListFrame[NewCurrentSelection]-&gt;SetVisibility(CATDlgShow);
      
      _CurrentSelection = NewCurrentSelection ;
   }
}
...
```