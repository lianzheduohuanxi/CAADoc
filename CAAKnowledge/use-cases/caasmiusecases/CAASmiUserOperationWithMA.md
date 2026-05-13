---
title: "Untitled"
category: "use-case"
module: "CAASmiUseCases"
tags: ["CAASurfaceMachiningItf", "CAASmgOperationWithMA", "CAASmiConnectUserOperationWithMA", "CAAESmiUserOperationWithMAGeometryEditor", "CAASmiOperationSampleOverview", "CATIM3xFeature", "CAADocStyleSheets", "CAADocRunSample", "CATIMfgGeometryActivity", "CATIAlias", "CAASmiUserOperationWithMAToolPath", "CAASmiUserOperationWithMA", "CAASmiTechArticles", "CAASmiOperationWithMAPanel", "CATISmgFactory", "CAASmiUserOperationWithMAGeometryPanel", "CATIEdit", "CAADocUseCases"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationWithMA.htmmd"
converted: "2026-05-11T11:27:02.780633"
---

---

---

### What You Will Learn With This Use Case

Machining areas are V5 SMG native
features used to define different zones on a part.

This use case is intended to help you to manage geometry of a machining area
assigned to a surface machining operation.

More specifically, the CAASmiUserOperationWithMA Use Case shows how to:

  
- overload the geometry tab page of a surface machining operation.
  
- create a machining area.
  
- access to the user interactive of machining areas.

[Top]

### The CAASmiUserOperationWithMA Use Case

CAASmiUserOperationWithMA is a use case of the CAASurfaceMachiningItf.edu
framework that illustrates Surface Machining capabilities. It is a part of the
sample described in the technical article [1].

[Top]

#### What Does CAASmiUserOperationWithMA Do

The goal of this use case is to define the geometry interactive of **CAASmgOperationWithMA**,
using machining areas properties.

In the geometry tab page of CAASmgOperationWithMA**, **you can select a existing
machining area and set its geometrical components (parts, checks, limit line and
forbidden area):

![](images/CAASmiOperationWithMAPanel.jpg)

[Top]

#### How to Launch CAASmiUserOperationWithMA

This use case is a part of *Surface Machining Operation Sample* [1].
You should build all the modules of this sample at a time to be able to launch
it [2].

Don't forget to edit the interface dictionary located in:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed, and uncomment the appropriate lines by removing the '#' character.

[Top]

#### Where to Find the CAASmiUserOperationWithMA Code

This use case is made of source files located in the
CAASmiConnectUserOperationWithMA.m module of the CAASurfaceMachiningItf.edu
framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

[Top]

### Step-by-Step

CAASmiUserOperationWithMA is divided into the following steps:

  
- Implementing CATIMfgGeometryActivity
  
- Creating a geometry dialog frame

We now comment each of those sections by looking at the code.

[Top]

#### Implementing CATIMfgGeometryActivity

To overload the geometry tab page, we should create an extension class that
will implement *CATIMfgGeometryActivity*:

In *GetMainPanelEditor, *we create a machining area (with *CATISmgFactory*)
and associate it with CAASmgOperationWithMA. Then, we call the geometry dialog frame
described below.

[Top]

#### Creating a geometry dialog frame

*CAASmiUserOperationWithMAGeometryPanel* is the frame of the geometry
tab page of CAASmgOperationWithMA.

In the constructor class, we build a dialog combo filled with all the
machining areas in the model and we add a event notification sent whenever a
value is selected in the combo list. Then, we get the **default dialog frame **of
the selected** machining area** with the *CATIEdit* interface.

The *SelectMachArea* method is called whenever a new machining area is
selected in the combo list. Here, the default dialog frame is updated with the *CATIEdit*
interface:

[Top]

---

### In Short

This use case has demonstrated how to use machining areas with a surface
machining operation.

  
- It first shows how to implement the *CATIMfgGeometryActivity*
    interface to overload default geometry tab page.
  
- Then, it shows how to create a machining area.
  
- Finally, it describes how to access to default user interactive of
    machining areas.

We will see now how to compute the tool path of our operation [3].

[Top]

---

### References

---

### History

---

*Copyright  2002, Dassault Systmes. All rights reserved.*

```cpp
...
// Tie the implementation to its interface
#include &quot;TIE_CATIMfgGeometryActivity.h&quot;
TIE_CATIMfgGeometryActivity( CAAESmiUserOperationWithMAGeometryEditor);
...
```

```cpp
...
  if (!!spFeatCont)
  {
    CATISmgFactory * pSmgFactory = NULL;
    oRC = spFeatCont-&gt;QueryInterface(IID_CATISmgFactory, (void**) &amp;pSmgFactory);
    if (SUCCEEDED(oRC))
    {
      // Creates a empty machining area
      oRC = pSmgFactory-&gt;CreateMachiningArea(spMachFeature);
      if (SUCCEEDED(oRC))
      {
        // Link the machining area to the activity
        pActivity-&gt;SetFeature(spMachFeature);
      }
      pSmgFactory-&gt;Release(#);
      pSmgFactory = NULL;
    }
    ...
  }

  // Creates the geometry frame
  oFrame = new CAASmiUserOperationWithMAGeometryPanel(iFather,this);
  ...
```

```cpp
...
  // Creates a combo box
  _pDlgCombo = new CATDlgCombo(this,&quot;DlgCombo&quot;,CATDlgCmbDropDown);
  if (_pDlgCombo)
  {
    ...	
    // Fills the combo box
    if (!!spFeatCont)
    {
      // Finds all machining areas inside the model
      _pListOfMAs = spFeatCont-&gt;ListMembers(&quot;CATIM3xFeature&quot;);		
      int NumbOfMAs = _pListOfMAs.Size(#);
      for (int i=1;i&lt;=NumbOfMAs;i++)
      {  				
        CATUnicodeString Name;
        CATBaseUnknown_var spMachArea = _pListOfMAs[i];
        if (!!spMachArea)
        {
          CATIAlias * pAlias = NULL;
          HRESULT RC = spMachArea-&gt;QueryInterface(IID_CATIAlias, (void**) &amp;pAlias);
          if (SUCCEEDED(RC))
          {
            Name = pAlias-&gt;GetAlias(#);
            _pDlgCombo-&gt;SetLine(Name);
            pAlias-&gt;Release(#);
            pAlias = NULL;
          }

          if (spMachArea-&gt;IsEqual(spCurrentMachArea) == 1)
            _pDlgCombo-&gt;SetSelect(i-1,0);
        }
      }
    }

    // Adds a callback 
    AddAnalyseNotificationCB(
      _pDlgCombo,
      _pDlgCombo-&gt;GetComboSelectNotification(#),
      (CATCommandMethod) &amp;CAASmiUserOperationWithMAGeometryPanel::SelectMachArea,NULL);

    // Creates the Machining Area editor
    if (!!spCurrentMachArea)
    {
      CATIEdit * pEdit = NULL;
      RC = spCurrentMachArea-&gt;QueryInterface(IID_CATIEdit, (void**) &amp;pEdit);
      if (SUCCEEDED(RC))
      {
        CATDlgFrame * pMAFrame = pEdit-&gt;GetPanelItem(this,&quot;MAFrameID&quot;);
        if (pMAFrame) 
          pMAFrame-&gt;SetGridConstraints( 1, 0, 2, 1, CATGRID_4SIDES);
        pEdit-&gt;Release(#);
        pEdit = NULL;
      }
    }		
  ...
```

```cpp
...
  // Refresh Machining Area Editor
  CATIEdit * pEdit = NULL;
  RC = spMA-&gt;QueryInterface(IID_CATIEdit, (void**) &amp;pEdit);
  if (SUCCEEDED(RC))
  {
    // As a frame called &quot;MAFrameID&quot; has already been created, the method GetPanelItem
    // will refresh it
    pEdit-&gt;GetPanelItem(this,&quot;MAFrameID&quot;);
    pEdit-&gt;Release(#);
    pEdit = NULL;
  }
 ...
```