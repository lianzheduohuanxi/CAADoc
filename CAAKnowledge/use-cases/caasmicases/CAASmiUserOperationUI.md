---
```vbscript
title: "Customizing the Surface Machining Operation Editor"
category: use-case case"
module: "CAASmiUseCases"
tags: ["CATIMfgMacroEditorActivity", "CAASmiUserOperationUI", "CAAToolAngle", "CAAESmiUserOperationToolEditor", "CATICkeParamFrame_var", "CAASmgOperation", "CAAApproachDistance", "CAAESmiUserOperationStrategyEditor", "CATIMacroEditorActivity", "CAAESmiUserOperationMacroEditor", "CATIMfgResourceFactory", "CATIMfgStrategyActivity", "CATIMfgActivity", "CAAMaiToolEditionCustomization", "CATIMfgActivityParameters", "CATIMfgTool", "CAAStep", "CAASurfaceMachiningItf", "CATIMfgToolActivity"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationUI.htmmd"
converted: "2026-05-11T17:31:51.261386"
```

---
# Machining

|
## 3 Axis Surface Machining

|
### Customizing the Surface Machining Operation Editor

_Customize default operation tab pages_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAASmiUserOperationUI use case. It explains how to customize strategy, tool and macros tab pages of the surface machining operation editor. This paper accompanies the _Surface Machining Operation Sample_ [1], but it can be used for any Manufacturing Activities.

  * **What You Will Learn With This Use Case**
  * **The CAASmiUserOperationUI Use Case**
    * What Does CAASmiUserOperationUI Do
    * How to Launch CAASmiUserOperationUI
    * Where to Find the CAASmiUserOperationUI Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

When a surface machining operation is edited by double clicking or through its contextual menu, a default dialog box is displayed.

This use case is intended to help you to customize some of the tab pages of this panel. This involves the following:

  * Implementing _CATIMfgStrategyActivity_ to overload Strategy tab page. ![](images/CAASmiOperationUIStrategyIcon.jpg)
  * Implementing _CATIMfgMacroEditorActivity_ to overload Macros tab page. ![](images/CAASmiOperationUIMacrosIcon.jpg)
  * Implementing _CATIMfgToolActivity_ to define Tool tab page. ![](images/CAASmiOperationUIToolIcon.jpg)

[Top]
### The CAASmiUserOperationUI Use Case

CAASmiUserOperationUI is a use case of the CAASurfaceMachiningItf.edu framework that illustrates Surface Machining capabilities. It is a part of the sample described in the technical article [1].

[Top]
#### What Does CAASmiUserOperationUI Do

CAASmiUserOperationUI is a use case of the CAASurfaceMachiningItf.edu framework that illustrates Surface Machining capabilities. It is a part of the sample described in the technical article [1].
This use case customizes three tab pages of the **CAASmgOperation** editing panel:

  1. CAASmgOperation has 1 strategy parameter

![](images/CAASmiOperationUIStrategy.jpg)

  2. CAASmgOperation has 2 macros parameters

**![](images/CAASmiOperationUIMacros.jpg)**

  3. CAASmgOperation has 2 allowed types of tool and an End Mill default tool:

![](images/CAASmiOperationUITool.jpg)

[Top]
#### How to Launch CAASmiUserOperationUI

This use case is a part of _Surface Machining Operation Sample_ [1]. You should build all the modules of this sample at a time to be able to launch it [2].

This use case is a part of _Surface Machining Operation Sample_ [1]. You should build all the modules of this sample at a time to be able to launch it [2].
Don't forget to edit the interface dictionary located in:

Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`

Don't forget to edit the interface dictionary located in:
Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed, and uncomment the appropriate lines by removing the '#' character.

[Top]
#### Where to Find the CAASmiUserOperationUI Code

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed, and uncomment the appropriate lines by removing the '#' character.
This use case is made of source files located in the CAASmiUserOperationUI.m module of the CAASurfaceMachiningItf.edu framework:

Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m`

This use case is made of source files located in the CAASmiUserOperationUI.m module of the CAASurfaceMachiningItf.edu framework:
Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m`
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are three logical steps in CAASmiUserOperationUI:

  1. Implementing CATIMfgStrategyActivity
  2. Implementing CATIMfgMacroEditorActivity
  3. Implementing CATIMfgToolActivity

We now comment each of those sections by looking at the code.

[Top]
#### Implementing CATIMfgStrategyActivity

To overload the strategy tab page, we should create an extension class that will implement _CATIMfgStrategyActivity_

    ...
    // Tie the implementation to its interface
    #include "TIE_CATIMfgStrategyActivity.h"
    TIE_CATIMfgStrategyActivity( CAAESmiUserOperationStrategyEditor);
    ...

---

In _GetMainPanelEditor,_ we create a frame that contains the frame-editor of our strategy parameter "CAAStep"

      ...
In _GetMainPanelEditor,_ we create a frame that contains the frame-editor of our strategy parameter "CAAStep"
      oFrame = new CATDlgFrame (iFather, "StrategyFrame", CATDlgGridLayout|CATDlgFraNoTitle);
```vbscript
```vbscript
      if (oFrame)

```

```

      {
        // Gets strategy parameter
oFrame = new CATDlgFrame (iFather, "StrategyFrame", CATDlgGridLayout|CATDlgFraNoTitle);
```vbscript
if (oFrame)
```

        CATIMfgActivityParameters * pActivityParameters = NULL;
        oRC = QueryInterface(IID_CATIMfgActivityParameters, (void**) &pActivityParameters);
```vbscript
```vbscript
        if (SUCCEEDED(oRC))

```

```

        {
CATIMfgActivityParameters * pActivityParameters = NULL;
oRC = QueryInterface(IID_CATIMfgActivityParameters, (void**) &pActivityParameters);
```vbscript
if (SUCCEEDED(oRC))
```

          CATBaseUnknown_var spBaseParm = NULL_var;
          oRC = pActivityParameters->FindElement("CAAStep",spBaseParm);
          CATICkeParamFrame_var spParamFrame (spBaseParm);
```vbscript
          if (!!spParamFrame)

```

          {
            ...
            // Creates a frame-editor linked to the parameter
CATICkeParamFrame_var spParamFrame (spBaseParm);
if (!!spParamFrame)
            CATDlgFrame *pDlgFrame = spParamFrame->GetInPanelEdition(NULL_var,oFrame,CATCkeWithSpinner|CATCkeNoLabel);
            if (pDlgFrame)
              pDlgFrame->SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);

            ...
      }
      ...

---

[Top]
#### Implementing CATIMacroEditorActivity

To overload the macros tab page, we should create an extension class that will implement _CATIMacroEditorActivity_

    ...
    // Tie the implementation to its interface
    #include "TIE_CATIMfgMacroEditorActivity.h"
    TIE_CATIMfgMacroEditorActivity( CAAESmiUserOperationMacroEditor);
    ...

---

In _GetMainPanelEditor,_ we create a frame that contains frame-editors of our macros parameters "CAAToolAngle" and "CAAApproachDistance"

      ...
In _GetMainPanelEditor,_ we create a frame that contains frame-editors of our macros parameters "CAAToolAngle" and "CAAApproachDistance"
      oFrame = new CATDlgFrame (iFather, "MacrosFrame", CATDlgGridLayout|CATDlgFraNoTitle);
```vbscript
```vbscript
      if (oFrame)

```

```

      {
        ...
        // CAAToolAngle
oFrame = new CATDlgFrame (iFather, "MacrosFrame", CATDlgGridLayout|CATDlgFraNoTitle);
```vbscript
```vbscript
if (oFrame)
        oRC = pActivityParameters->FindElement("CAAToolAngle",spBaseParm);
```

```

        CATICkeParamFrame_var spParamFrame (spBaseParm);
```vbscript
        if (!!spParamFrame)

```

        {
          ...
          // Creates a frame-editor linked to the parameter
CATICkeParamFrame_var spParamFrame (spBaseParm);
if (!!spParamFrame)
          CATDlgFrame *pDlgFrame = spParamFrame ->GetInPanelEdition(NULL_var, oFrame  ,CATCkeWithSpinner|CATCkeNoLabel);
          if (pDlgFrame)
              pDlgFrame->SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);

        }

        //CAAApproachDistance
```vbscript
if (pDlgFrame)
pDlgFrame->SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);
        oRC = pActivityParameters->FindElement("CAAApproachDistance",spBaseParm);
        spParamFrame = spBaseParm;
        if (!!spParamFrame)
```

        {
          ...
          // Creates a frame-editor linked to the parameter
spParamFrame = spBaseParm;
if (!!spParamFrame)
          CATDlgFrame *pDlgFrame = spParamFrame ->GetInPanelEdition(NULL_var, oFrame  ,CATCkeWithSpinner|CATCkeNoLabel);
          if (pDlgFrame)
              pDlgFrame->SetGridConstraints( 1, 1, 1, 1, CATGRID_4SIDES);

      }
      ...
     }
     ...

---

[Top]
#### Implementing CATIMfgToolActivity

To customize tool tab page, we should create an extension class that will implement _CATIMfgToolActivity_. This interface offers services to manage allowed and default tools. If you like to overload the whole tab page, see the _CAAMaiToolEditionCustomization_ use case [3].

    ...
    #include "TIE_CATIMfgToolActivity.h"
    TIE_CATIMfgToolActivity( CAAESmiUserOperationToolEditor);
    ...

---

In _GetAuthorizedToolTypeList,_ we set the types of allowed tools of our operation

     HRESULT CAAESmiUserOperationToolEditor::GetAuthorizedToolTypeList (CATListOfCATUnicodeString & oToolTypeList)
     {
       // Allowed Tools
HRESULT CAAESmiUserOperationToolEditor::GetAuthorizedToolTypeList (CATListOfCATUnicodeString & oToolTypeList)
       oToolTypeList.Append(CATEMfgEndMillTool);
       oToolTypeList.Append(CATEMfgDrillTool);

       return S_OK;

     }

---

In _CreateDefaultTool,_ we set the default tool of our operation

    HRESULT CAAESmiUserOperationToolEditor::CreateDefaultTool (CATBaseUnknown_var & oTool)
    {
      ...
          // Retrieves Resource Factory
HRESULT CAAESmiUserOperationToolEditor::CreateDefaultTool (CATBaseUnknown_var & oTool)
```vbscript
      if (!!spResourceContainer)

```

      {
```vbscript
if (!!spResourceContainer)
        CATIMfgResourceFactory * pResourceFactory = NULL;
        oRC = spResourceContainer->QueryInterface(IID_CATIMfgResourceFactory, (void**) &pResourceFactory);
```vbscript
        if (SUCCEEDED(oRC))
```

```

        {
          // Creates Default Tool
CATIMfgResourceFactory * pResourceFactory = NULL;
oRC = spResourceContainer->QueryInterface(IID_CATIMfgResourceFactory, (void**) &pResourceFactory);
```vbscript
if (SUCCEEDED(oRC))
```

          CATUnicodeString ToolTypeToCreate = MfgEndMillTool;
          oTool = pResourceFactory->CreateResource(ToolTypeToCreate);
          pResourceFactory->Release(#);
          pResourceFactory = NULL;

          // Defines a Default tool for our user operation
oTool = pResourceFactory->CreateResource(ToolTypeToCreate);
pResourceFactory->Release(#);
pResourceFactory = NULL;
          if(!!oTool)

          {
pResourceFactory = NULL;
if(!!oTool)
            CATIMfgTool * pMfgTool = NULL;
            oRC = oTool->QueryInterface(IID_CATIMfgTool, (void**) &pMfgTool);
```vbscript
```vbscript
            if (SUCCEEDED(oRC))

```

```

            {
CATIMfgTool * pMfgTool = NULL;
oRC = oTool->QueryInterface(IID_CATIMfgTool, (void**) &pMfgTool);
```vbscript
if (SUCCEEDED(oRC))
```

              pMfgTool->SetDefaultValues(#);
              pMfgTool->SetDefaultName(#);
              pMfgTool->Release(#);
              pMfgTool = NULL;

            }

pMfgTool->SetDefaultName(#);
pMfgTool->Release(#);
pMfgTool = NULL;
            CATIMfgActivity * pActivity = NULL;
            oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
```vbscript
```vbscript
            if (SUCCEEDED(oRC))

```

```

            {
CATIMfgActivity * pActivity = NULL;
oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
```vbscript
if (SUCCEEDED(oRC))
```

              pActivity->SetDefaultTool(oTool);
              pActivity->Release(#);
              pActivity = NULL;

            }
          }
        }
      }
      ...
    }

---

[Top]

* * *
### In Short

This article provides an example on how to customize strategy, tool and macros tab pages of the editing dialog panel of a surface machining operation. How to customize geometry tab page is described in the next use cases [4] & [5].

[Top]

* * *
### References

[1] | [Surface Machining Operation Sample Overview](../CAASmiTechArticles/CAASmiOperationSampleOverview.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [Customizing Tool Editor for Drilling Tool](../CAAMaiUseCases/CAAMaiToolEditionCustomization.md)
[4] | [Managing Geometry with User Machining Features](CAASmiUserOperationWithUserMF.md)
[5] | [Managing Geometry with Machining Areas](CAASmiUserOperationWithMA.md)
[Top]

* * *
### History

Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
