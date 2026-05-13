---
title: "Untitled"
category: "use-case"
module: "CAASmiUseCases"
tags: ["CATIMfgActivityParameters", "CAAMaiToolEditionCustomization", "CAADocStyleSheets", "CATIMacroEditorActivity", "CATIMfgStrategyActivity", "CATIMfgTool", "CAAESmiUserOperationToolEditor", "CAAESmiUserOperationStrategyEditor", "CAASurfaceMachiningItf", "CAASmiOperationSampleOverview", "CAASmiUserOperationUI", "CAAESmiUserOperationMacroEditor", "CAASmiOperationUIStrategyIcon", "CAAToolAngle", "CAASmiOperationUIMacrosIcon", "CAADocUseCases", "CAASmgOperation", "CAASmiOperationUIMacros", "CATIMfgResourceFactory", "CAASmiOperationUIStrategy"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationUI.htmmd"
converted: "2026-05-11T11:27:02.771855"
---

---

---

### What You Will Learn With This Use Case

When a surface machining operation is edited by double clicking or through
its contextual menu, a default dialog box is displayed.

This use case is intended to help you to customize some of the tab pages of
this panel. This involves the following:

  
- Implementing *CATIMfgStrategyActivity* to overload Strategy tab page.
    ![](images/CAASmiOperationUIStrategyIcon.jpg)
  
- Implementing *CATIMfgMacroEditorActivity* to overload Macros tab
    page. ![](images/CAASmiOperationUIMacrosIcon.jpg)
  
- Implementing *CATIMfgToolActivity* to define Tool tab page. ![](images/CAASmiOperationUIToolIcon.jpg)

[Top]

### The CAASmiUserOperationUI Use Case

CAASmiUserOperationUI is a use case of the CAASurfaceMachiningItf.edu
framework that illustrates Surface Machining capabilities. It is a part of the
sample described in the technical article [1].

[Top]

#### What Does CAASmiUserOperationUI Do

This use case customizes three tab pages of the **CAASmgOperation**
editing panel:

  
- CAASmgOperation has 1 strategy parameter
    

![](images/CAASmiOperationUIStrategy.jpg)
  
  
- CAASmgOperation has 2 macros parameters
    

**![](images/CAASmiOperationUIMacros.jpg)**
  
  
- CAASmgOperation has 2 allowed types of tool and an End Mill default tool:
    

![](images/CAASmiOperationUITool.jpg)
  

[Top]

#### How to Launch CAASmiUserOperationUI

This use case is a part of *Surface Machining Operation Sample* [1].
You should build all the modules of this sample at a time to be able to launch
it [2].

Don't forget to edit the interface dictionary located in:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed, and uncomment the appropriate lines by removing the '#' character.

[Top]

#### Where to Find the CAASmiUserOperationUI Code

This use case is made of source files located in the CAASmiUserOperationUI.m
module of the CAASurfaceMachiningItf.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

[Top]

### Step-by-Step

There are three logical steps in CAASmiUserOperationUI:

  
- Implementing CATIMfgStrategyActivity
  
- Implementing CATIMfgMacroEditorActivity
  
- Implementing CATIMfgToolActivity

We now comment each of those sections by looking at the code.

[Top]

#### Implementing CATIMfgStrategyActivity

To overload the strategy tab page, we should create an extension class that
will implement *CATIMfgStrategyActivity*

In *GetMainPanelEditor, *we create a frame that contains the
frame-editor of our strategy parameter "CAAStep"

[Top]

#### Implementing CATIMacroEditorActivity

To overload the macros tab page, we should create an extension class that
will implement *CATIMacroEditorActivity*

In *GetMainPanelEditor, *we create a frame that contains frame-editors
of our macros parameters "CAAToolAngle" and
"CAAApproachDistance"

[Top]

#### Implementing CATIMfgToolActivity

To customize tool tab page, we should create an extension class that will
implement *CATIMfgToolActivity*. This interface offers services to manage
allowed and default tools. If you like to overload the whole tab page, see the *CAAMaiToolEditionCustomization*
use case [3].

In *GetAuthorizedToolTypeList, *we set the types of allowed tools of our
operation

In *CreateDefaultTool, *we set the default tool of our operation

[Top]

---

### In Short

This article provides an example on how to customize strategy, tool and
macros tab pages of the editing dialog panel of a surface machining operation.
How to customize geometry tab page is described in the next use cases [4]
& [5].

[Top]

---

### References

---

### History

---

*Copyright  2002, Dassault Systmes. All rights reserved.*

```vbscript
...
// Tie the implementation to its interface
#include &quot;TIE_CATIMfgStrategyActivity.h&quot;
TIE_CATIMfgStrategyActivity( CAAESmiUserOperationStrategyEditor);
...
```

```vbscript
...
  oFrame = new CATDlgFrame (iFather, &quot;StrategyFrame&quot;, CATDlgGridLayout|CATDlgFraNoTitle);
  if (oFrame)
  {
    // Gets strategy parameter
    CATIMfgActivityParameters * pActivityParameters = NULL;
    oRC = QueryInterface(IID_CATIMfgActivityParameters, (void**) &amp;pActivityParameters);
    if (SUCCEEDED(oRC))
    {
      CATBaseUnknown_var spBaseParm = NULL_var; 
      oRC = pActivityParameters-&gt;FindElement(&quot;CAAStep&quot;,spBaseParm);
      CATICkeParamFrame_var spParamFrame (spBaseParm);
      if (!!spParamFrame)
      {
        ...
        // Creates a frame-editor linked to the parameter
        CATDlgFrame *pDlgFrame = spParamFrame-&gt;GetInPanelEdition(NULL_var,oFrame,CATCkeWithSpinner|CATCkeNoLabel);
        if (pDlgFrame)
          pDlgFrame-&gt;SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);
        ...
  }
  ...
```

```vbscript
...
// Tie the implementation to its interface
#include &quot;TIE_CATIMfgMacroEditorActivity.h&quot;
TIE_CATIMfgMacroEditorActivity( CAAESmiUserOperationMacroEditor);
...
```

```vbscript
...
  oFrame = new CATDlgFrame (iFather, &quot;MacrosFrame&quot;, CATDlgGridLayout|CATDlgFraNoTitle);
  if (oFrame)
  {
    ...
    // CAAToolAngle
    oRC = pActivityParameters-&gt;FindElement(&quot;CAAToolAngle&quot;,spBaseParm);
    CATICkeParamFrame_var spParamFrame (spBaseParm);
    if (!!spParamFrame)
    {
      ...
      // Creates a frame-editor linked to the parameter
      CATDlgFrame *pDlgFrame = spParamFrame -&gt;GetInPanelEdition(NULL_var, oFrame  ,CATCkeWithSpinner|CATCkeNoLabel);
      if (pDlgFrame)
          pDlgFrame-&gt;SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);
    }

    //CAAApproachDistance
    oRC = pActivityParameters-&gt;FindElement(&quot;CAAApproachDistance&quot;,spBaseParm);
    spParamFrame = spBaseParm;
    if (!!spParamFrame)
    {
      ...
      // Creates a frame-editor linked to the parameter
      CATDlgFrame *pDlgFrame = spParamFrame -&gt;GetInPanelEdition(NULL_var, oFrame  ,CATCkeWithSpinner|CATCkeNoLabel);
      if (pDlgFrame)
          pDlgFrame-&gt;SetGridConstraints( 1, 1, 1, 1, CATGRID_4SIDES);
  }
  ...  
 } 
 ...
```

```vbscript
...
#include &quot;TIE_CATIMfgToolActivity.h&quot;
TIE_CATIMfgToolActivity( CAAESmiUserOperationToolEditor);
...
```

```vbscript
HRESULT CAAESmiUserOperationToolEditor::GetAuthorizedToolTypeList (CATListOfCATUnicodeString &amp; oToolTypeList)
 {
   // Allowed Tools
   oToolTypeList.Append(CATEMfgEndMillTool);
   oToolTypeList.Append(CATEMfgDrillTool);

   return S_OK;
 }
```

```vbscript
HRESULT CAAESmiUserOperationToolEditor::CreateDefaultTool (CATBaseUnknown_var &amp; oTool)
{
  ...
      // Retrieves Resource Factory
  if (!!spResourceContainer)
  {
    CATIMfgResourceFactory * pResourceFactory = NULL;
    oRC = spResourceContainer-&gt;QueryInterface(IID_CATIMfgResourceFactory, (void**) &amp;pResourceFactory);
    if (SUCCEEDED(oRC))
    {
      // Creates Default Tool
      CATUnicodeString ToolTypeToCreate = MfgEndMillTool;
      oTool = pResourceFactory-&gt;CreateResource(ToolTypeToCreate);
      pResourceFactory-&gt;Release(#);
      pResourceFactory = NULL;

      // Defines a Default tool for our user operation
      if(!!oTool)
      {
        CATIMfgTool * pMfgTool = NULL;
        oRC = oTool-&gt;QueryInterface(IID_CATIMfgTool, (void**) &amp;pMfgTool);
        if (SUCCEEDED(oRC))
        {
          pMfgTool-&gt;SetDefaultValues(#);
          pMfgTool-&gt;SetDefaultName(#);
          pMfgTool-&gt;Release(#);
          pMfgTool = NULL;
        }

        CATIMfgActivity * pActivity = NULL;
        oRC = QueryInterface(IID_CATIMfgActivity, (void**) &amp;pActivity);
        if (SUCCEEDED(oRC))
        {
          pActivity-&gt;SetDefaultTool(oTool);
          pActivity-&gt;Release(#);
          pActivity = NULL;
        }
      }
    }
  }
  ...
}
```