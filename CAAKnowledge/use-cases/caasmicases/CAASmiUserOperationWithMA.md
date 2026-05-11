---
```vbscript
title: "Managing Geometry with Machining Areas"
category: "use case"
module: "CAASmiUseCases"
tags: ["CAASmiConnectUserOperationWithMA", "CATIM3xFeature", "CAASmiUserOperationWithMAGeometryPanel", "CATISmgFactory", "CAASmiUserOperationWithMA", "CATIMfgGeometryActivity", "CAASurfaceMachiningItf", "CATIAlias", "CAAESmiUserOperationWithMAGeometryEditor", "CATIEdit", "CAASmgOperationWithMA"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationWithMA.htm"
converted: "2026-05-11T17:31:51.267374"
```

---
# Machining

| 
## 3 Axis Surface Machining

| 
### Managing Geometry with Machining Areas

_Customize the geometry tab page of a surface machining operation with machining areas_  
---|---|---  
Use Case  

* * *
### Abstract

This article discusses the CAASmiUserOperationWithMA use case. It explains how to assign a surface machining operation to an existing machining area. This paper accompanies the second scenario of _Surface Machining Operation Sample_ [1].

  * **What You Will Learn With This Use Case**
  * **The CAASmiUserOperationWithMA Use Case**
    * What Does CAASmiUserOperationWithMA Do
    * How to Launch CAASmiUserOperationWithMA
    * Where to Find the CAASmiUserOperationWithMA Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

Machining areas are V5 SMG native features used to define different zones on a part.

Machining areas are V5 SMG native features used to define different zones on a part.
This use case is intended to help you to manage geometry of a machining area assigned to a surface machining operation.

More specifically, the CAASmiUserOperationWithMA Use Case shows how to:

  * overload the geometry tab page of a surface machining operation.
  * create a machining area.
  * access to the user interactive of machining areas.

[Top]
### The CAASmiUserOperationWithMA Use Case

CAASmiUserOperationWithMA is a use case of the CAASurfaceMachiningItf.edu framework that illustrates Surface Machining capabilities. It is a part of the sample described in the technical article [1].

[Top]
#### What Does CAASmiUserOperationWithMA Do

CAASmiUserOperationWithMA is a use case of the CAASurfaceMachiningItf.edu framework that illustrates Surface Machining capabilities. It is a part of the sample described in the technical article [1].
The goal of this use case is to define the geometry interactive of **CAASmgOperationWithMA** , using machining areas properties.

In the geometry tab page of CAASmgOperationWithMA**,** you can select a existing machining area and set its geometrical components (parts, checks, limit line and forbidden area):

![](images/CAASmiOperationWithMAPanel.jpg)

[Top]
#### How to Launch CAASmiUserOperationWithMA

This use case is a part of _Surface Machining Operation Sample_ [1]. You should build all the modules of this sample at a time to be able to launch it [2].

This use case is a part of _Surface Machining Operation Sample_ [1]. You should build all the modules of this sample at a time to be able to launch it [2].
Don't forget to edit the interface dictionary located in:

Windows | `InstallRootDirectory\CAASurfaceMachiningItf.edu\CNext\code\dictionary\`  

Don't forget to edit the interface dictionary located in:
Windows | `InstallRootDirectory\CAASurfaceMachiningItf.edu\CNext\code\dictionary\`
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed, and uncomment the appropriate lines by removing the '#' character.

[Top]
#### Where to Find the CAASmiUserOperationWithMA Code

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed, and uncomment the appropriate lines by removing the '#' character.
This use case is made of source files located in the CAASmiConnectUserOperationWithMA.m module of the CAASurfaceMachiningItf.edu framework:

Windows | `InstallRootDirectory\CAASurfaceMachiningItf.edu\CAASmiConnectUserOperationWithMA.m`  

This use case is made of source files located in the CAASmiConnectUserOperationWithMA.m module of the CAASurfaceMachiningItf.edu framework:
Windows | `InstallRootDirectory\CAASurfaceMachiningItf.edu\CAASmiConnectUserOperationWithMA.m`
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiConnectUserOperationWithMA.m`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

CAASmiUserOperationWithMA is divided into the following steps:

  * Implementing CATIMfgGeometryActivity
  * Creating a geometry dialog frame

We now comment each of those sections by looking at the code.

[Top]
#### Implementing CATIMfgGeometryActivity

To overload the geometry tab page, we should create an extension class that will implement _CATIMfgGeometryActivity_ :

    ...
    // Tie the implementation to its interface
    #include "TIE_CATIMfgGeometryActivity.h"
    TIE_CATIMfgGeometryActivity( CAAESmiUserOperationWithMAGeometryEditor);
    ...  

---  

In _GetMainPanelEditor,_ we create a machining area (with _CATISmgFactory_) and associate it with CAASmgOperationWithMA. Then, we call the geometry dialog frame described below.

      ...
In _GetMainPanelEditor,_ we create a machining area (with _CATISmgFactory_) and associate it with CAASmgOperationWithMA. Then, we call the geometry dialog frame described below.
      if (!!spFeatCont)

      {
```vbscript
if (!!spFeatCont)
        CATISmgFactory * pSmgFactory = NULL;
        oRC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**) &pSmgFactory);
        if (SUCCEEDED(oRC))
```

        {
          // Creates a empty machining area
CATISmgFactory * pSmgFactory = NULL;
oRC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**) &pSmgFactory);
if (SUCCEEDED(oRC))
          oRC = pSmgFactory->**CreateMachiningArea**(spMachFeature);
          if (SUCCEEDED(oRC))

          {
            // Link the machining area to the activity
oRC = pSmgFactory->**CreateMachiningArea**(spMachFeature);
if (SUCCEEDED(oRC))
            pActivity->SetFeature(spMachFeature);

          }
```vbscript
if (SUCCEEDED(oRC))
pActivity->SetFeature(spMachFeature);
          pSmgFactory->Release();
          pSmgFactory = NULL;
```

        }
        ...
      }

      // Creates the geometry frame
      oFrame = new CAASmiUserOperationWithMAGeometryPanel(iFather,this);
      ...  

---  

[Top]
#### Creating a geometry dialog frame

_CAASmiUserOperationWithMAGeometryPanel_ is the frame of the geometry tab page of CAASmgOperationWithMA.

In the constructor class, we build a dialog combo filled with all the machining areas in the model and we add a event notification sent whenever a value is selected in the combo list. Then, we get the **default dialog frame** of the selected**machining area** with the _CATIEdit_ interface.

      ...
      // Creates a combo box
In the constructor class, we build a dialog combo filled with all the machining areas in the model and we add a event notification sent whenever a value is selected in the combo list. Then, we get the **default dialog frame** of the selected**machining area** with the _CATIEdit_ interface.
      _pDlgCombo = new CATDlgCombo(this,"DlgCombo",CATDlgCmbDropDown);
      if (_pDlgCombo)

      {
        ...	
        // Fills the combo box
_pDlgCombo = new CATDlgCombo(this,"DlgCombo",CATDlgCmbDropDown);
if (_pDlgCombo)
        if (!!spFeatCont)

        {
          // Finds all machining areas inside the model
```vbscript
if (!!spFeatCont)
          _pListOfMAs = spFeatCont->ListMembers("CATIM3xFeature");		
          int NumbOfMAs = _pListOfMAs.Size();
          for (int i=1;i<=NumbOfMAs;i++)
```

          {  				
_pListOfMAs = spFeatCont->ListMembers("CATIM3xFeature");
int NumbOfMAs = _pListOfMAs.Size();
for (int i=1;i<=NumbOfMAs;i++)
            CATUnicodeString Name;
            CATBaseUnknown_var spMachArea = _pListOfMAs[i];
            if (!!spMachArea)

            {
CATUnicodeString Name;
CATBaseUnknown_var spMachArea = _pListOfMAs[i];
if (!!spMachArea)
              CATIAlias * pAlias = NULL;
              HRESULT RC = spMachArea->QueryInterface(IID_CATIAlias, (void**) &pAlias);
              if (SUCCEEDED(RC))

              {
CATIAlias * pAlias = NULL;
HRESULT RC = spMachArea->QueryInterface(IID_CATIAlias, (void**) &pAlias);
if (SUCCEEDED(RC))
                Name = pAlias->GetAlias();
                _pDlgCombo->SetLine(Name);
                pAlias->Release();
                pAlias = NULL;

              }

_pDlgCombo->SetLine(Name);
pAlias->Release();
pAlias = NULL;
              if (spMachArea->IsEqual(spCurrentMachArea) == 1)
                _pDlgCombo->SetSelect(i-1,0);

            }
          }
        }

        // Adds a callback 
```vbscript
        AddAnalyseNotificationCB(
          _pDlgCombo,
          _pDlgCombo->GetComboSelectNotification(),
          (CATCommandMethod) &CAASmiUserOperationWithMAGeometryPanel::SelectMachArea,NULL);

```

        // Creates the Machining Area editor
_pDlgCombo,
_pDlgCombo->GetComboSelectNotification(),
(CATCommandMethod) &CAASmiUserOperationWithMAGeometryPanel::SelectMachArea,NULL);
        if (!!spCurrentMachArea)

        {
(CATCommandMethod) &CAASmiUserOperationWithMAGeometryPanel::SelectMachArea,NULL);
if (!!spCurrentMachArea)
          CATIEdit * pEdit = NULL;
          RC = spCurrentMachArea->QueryInterface(IID_CATIEdit, (void**) &pEdit);
          if (SUCCEEDED(RC))

          {
CATIEdit * pEdit = NULL;
RC = spCurrentMachArea->QueryInterface(IID_CATIEdit, (void**) &pEdit);
if (SUCCEEDED(RC))
            CATDlgFrame * pMAFrame = pEdit->**GetPanelItem**(this,"**MAFrameID** ");
            if (pMAFrame) 
              pMAFrame->SetGridConstraints( 1, 0, 2, 1, CATGRID_4SIDES);
            pEdit->Release();
            pEdit = NULL;

          }
        }		
      ...  

---  

The _SelectMachArea_ method is called whenever a new machining area is selected in the combo list. Here, the default dialog frame is updated with the _CATIEdit_ interface:

      ...
      // Refresh Machining Area Editor
The _SelectMachArea_ method is called whenever a new machining area is selected in the combo list. Here, the default dialog frame is updated with the _CATIEdit_ interface:
      CATIEdit * pEdit = NULL;
      RC = spMA->QueryInterface(IID_CATIEdit, (void**) &pEdit);
      if (SUCCEEDED(RC))

      {
        // As a frame called "MAFrameID" has already been created, the method GetPanelItem
        // will refresh it
RC = spMA->QueryInterface(IID_CATIEdit, (void**) &pEdit);
if (SUCCEEDED(RC))
        pEdit->**GetPanelItem**(this,"**MAFrameID** ");
        pEdit->Release();
        pEdit = NULL;

      }
     ...  

---  

[Top]

* * *
### In Short

This use case has demonstrated how to use machining areas with a surface machining operation.

  * It first shows how to implement the _CATIMfgGeometryActivity_ interface to overload default geometry tab page.
  * Then, it shows how to create a machining area.
  * Finally, it describes how to access to default user interactive of machining areas.

We will see now how to compute the tool path of our operation [3].

[Top]

* * *
### References

[1] | [Surface Machining Operation Sample Overview](../CAASmiTechArticles/CAASmiOperationSampleOverview.md)  
---|---  
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[3] | [Computing a Tool Path with Machining Areas](CAASmiUserOperationWithMAToolPath.md)  
[Top]  

* * *
### History

Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
