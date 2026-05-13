---
```vbscript
title: "Creating a Multi Sheet Interactive Command"
category: use-case case"
module: "CAADriUseCases"
tags: ["CATIADocument", "CATIModelEvents_var", "CAADrwMultiSheetCmd", "CAADrwAddin", "CAAUseCaseCommands", "CATIADrawingDocument", "CAADraftingInterfaces", "CATIA", "CATIDftMultiSheetCmd", "CATIDrwText", "CATIDftMultiSheetMode", "CATIAApplication"]
source_file: "Doc/online/CAADriUseCases/CAADriMultiSheetCmd.htmmd"
converted: "2026-05-11T17:31:51.012436"
```

---
# Mechanical Design

|
## Drafting

|
### Creating a Multi Sheet Interactive Command

_How to create an interactive command working on several sheets_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAADrwMultiSheetCmd use case. This use case explains how to create a command working on several sheets.

  * **What You Will Learn With This Use Case**
  * **The CAADrwMultiSheetCmd Use Case**
    * What Does CAADrwMultiSheetCmd Do
    * How to Launch CAADrwMultiSheetCmd
    * Where to Find the CAADrwMultiSheetCmd Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will You With This Use Case

In this use case you will learn how to create an interactive command working on several sheets.

[Top]
### The CAADrwMultiSheetCmd Use Case

CAADrwMultiSheetCmd is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwMultiSheetCmd Do

CAADrwMultiSheetCmd is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.
This use case shows a command working on several sheets. The use case interactive command has two steps:

  1. Select a reference text
  2. Select a text to move. The text position is modified according to the reference text position.

[Top]
#### How to Launch CAADrwMultiSheetCmd

2. Select a text to move. The text position is modified according to the reference text position.
To launch CAADrwMultiSheetCmd, you will need to set up the build time environment, then compile CAADrwMultiSheetCmd and CAADrwAddin along with its prerequisites, set up the run time environment, and then include the command in a workbench [1].

  1. Launch CATIA session.
  2. Right-click on Drafting workshop to activate CAAUseCaseCommands toolbar.
  3. Launch the MultiSheet use case command.
  4. Create a drawing document containing two sheets
  5. Create "TEXT SHEET 1" text in Sheet 1. (See Fig: 1)
  6. Create "TEXT SHEET 2" text in Sheet 2. (See Fig: 2)
  7. Launch the use case interactive command. (Sheet 2 is the current sheet)
  8. Select TEXT SHEET 1 text in Sheet 1. (Sheet 1 is the current sheet)
  9. Select TEXT SHEET 2 text in Sheet 2. (Sheet 2 is the current sheet). The TEXT SHEET2 is moved (See Fig: 3) recording to TEXT SHEET1 text position.

Fig 1: Sheet.1 is the current sheet ![](images/CAADrwMultiSheet1.jpg)

---
8. Select TEXT SHEET 1 text in Sheet 1. (Sheet 1 is the current sheet)
9. Select TEXT SHEET 2 text in Sheet 2. (Sheet 2 is the current sheet). The TEXT SHEET2 is moved (See Fig: 3) recording to TEXT SHEET1 text position.
Fig 1: Sheet.1 is the current sheet ![](images/CAADrwMultiSheet1.jpg)
Fig 2: Sheet.2 is the current sheet ![](images/CAADrwMultiSheet2.jpg)

---
Fig 1: Sheet.1 is the current sheet ![](images/CAADrwMultiSheet1.jpg)
Fig 2: Sheet.2 is the current sheet ![](images/CAADrwMultiSheet2.jpg)
Fig 3: Sheet.2 is the current sheet ![](images/CAADrwMultiSheet3.jpg)

---

[Top]
#### Where to Find the CAADrwMultiSheetCmd Code

The CAADrwMultiSheetCmd use case is made of two source files named CAADrwMultiSheetCmd.h and CAADrwMultiSheetCmd.cpp located in the CAADrwMultiSheetCmd.m module of the CAADraftingInterfaces.edu framework:

The CAADrwMultiSheetCmd use case is made of two source files named CAADrwMultiSheetCmd.h and CAADrwMultiSheetCmd.cpp located in the CAADrwMultiSheetCmd.m module of the CAADraftingInterfaces.edu framework:
Windows | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwMultiSheetCmd.m/`

The CAADrwMultiSheetCmd use case is made of two source files named CAADrwMultiSheetCmd.h and CAADrwMultiSheetCmd.cpp located in the CAADrwMultiSheetCmd.m module of the CAADraftingInterfaces.edu framework:
Windows | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwMultiSheetCmd.m/`
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwMultiSheetCmd.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are seven steps in CAADrwMultiSheetCmd:

  1. Retrieve the current drawing from the Frame
  2. Read the Current Multi Sheet Mode
  3. Active the Multi Sheet Mode
  4. Building the State Chart and Creating the Appropriate Selection Agent
  5. Select the Reference Text and Store its Coordinates
  6. Select the Text to Move and Store the New Position
  7. Restore the Previous Multi Sheet Mode Value

[Top]
#### Retrieving the Current Drawing from the Frame

    // ----------------------------------------------------------------------------
    CAADrwMultiSheetCmd::CAADrwMultiSheetCmd(#)
                        :CATStateCommand(CATString("AlignText")),
                                         _pObjectAgent(NULL)
    {
      // Get the current drawing from the frame
CAADrwMultiSheetCmd::CAADrwMultiSheetCmd(#)
_pObjectAgent(NULL)
      __piSheetsOnDrawing = NULL;
      CATApplicationFrame *appFrame = CATApplicationFrame::GetFrame(#);
      CATIAApplication *ptApp = NULL;
```vbscript
      if (SUCCEEDED(appFrame->QueryInterface(IID_CATIAApplication, (void**) &ptApp)))

```

      {
__piSheetsOnDrawing = NULL;
CATApplicationFrame *appFrame = CATApplicationFrame::GetFrame(#);
CATIAApplication *ptApp = NULL;
if (SUCCEEDED(appFrame->QueryInterface(IID_CATIAApplication, (void**) &ptApp)))
        CATIADocument *ptDoc = NULL;
```vbscript
        if (SUCCEEDED(ptApp->get_ActiveDocument(ptDoc)))

```

        {
```vbscript
if (SUCCEEDED(appFrame->QueryInterface(IID_CATIAApplication, (void**) &ptApp)))
CATIADocument *ptDoc = NULL;
if (SUCCEEDED(ptApp->get_ActiveDocument(ptDoc)))
          CATIADrawingDocument *piDrawing = NULL;
          if (SUCCEEDED(ptDoc->QueryInterface(IID_CATIADrawingDocument, (void**) &piDrawing)))
```

          {
```vbscript
if (SUCCEEDED(ptApp->get_ActiveDocument(ptDoc)))
CATIADrawingDocument *piDrawing = NULL;
if (SUCCEEDED(ptDoc->QueryInterface(IID_CATIADrawingDocument, (void**) &piDrawing)))
            piDrawing->get_Sheets(__piSheetsOnDrawing);
            piDrawing->Release(#);
```

          }
```vbscript
if (SUCCEEDED(ptDoc->QueryInterface(IID_CATIADrawingDocument, (void**) &piDrawing)))
piDrawing->get_Sheets(__piSheetsOnDrawing);
piDrawing->Release(#);
          ptDoc->Release(#);
```

        }
piDrawing->get_Sheets(__piSheetsOnDrawing);
piDrawing->Release(#);
ptDoc->Release(#);
        ptApp->Release(#);

      }
      // Save Multi sheet mode to restitute it at the end of the command
ptDoc->Release(#);
ptApp->Release(#);
      GetMultiSheetMode(_PreviousMode);

      // Activate Multi sheet mode
```vbscript
GetMultiSheetMode(_PreviousMode);
```vbscript
```vbscript
      if (!_PreviousMode) SetMultiSheetMode(TRUE);

```

```

      _Xposition =0.0;
      _Yposition =0.0;
```

    }

---

[Top]
#### Reading the Current Multi Sheet Mode

    // ----------------------------------------------------------------------------
    // Save Multi sheet mode to restore it at the end of the command
       GetMultiSheetMode(_PreviousMode);
    //
    ...
    // This internal method is used to manage CATIDftMultiSheetCmd Interfaces.
```vbscript
GetMultiSheetMode(_PreviousMode);
    void  CAADrwMultiSheetCmd::GetMultiSheetMode(boolean  &oMode)
```

    {
void  CAADrwMultiSheetCmd::GetMultiSheetMode(boolean  &oMode)
      oMode = FALSE;
```vbscript
      if (!!__piSheetsOnDrawing)

```

      {
void  CAADrwMultiSheetCmd::GetMultiSheetMode(boolean  &oMode)
oMode = FALSE;
if (!!__piSheetsOnDrawing)
        CATIDftMultiSheetMode *multiSheetManager=NULL;
```vbscript
        if (SUCCEEDED(__piSheetsOnDrawing->QueryInterface(IID_CATIDftMultiSheetMode, (void **) &multiSheetManager)))

```

        {
```vbscript
if (!!__piSheetsOnDrawing)
CATIDftMultiSheetMode *multiSheetManager=NULL;
if (SUCCEEDED(__piSheetsOnDrawing->QueryInterface(IID_CATIDftMultiSheetMode, (void **) &multiSheetManager)))
          multiSheetManager->GetMultiSheetMode(&oMode);
          multiSheetManager->Release(#);
```

        }
      }
    }

---

[Top]
#### Activating the Multi Sheet Mode

    // Active Multi sheet mode
    if (!_PreviousMode) SetMultiSheetMode(TRUE);
    ...
    //This internal method is used to manage CATIDftMultiSheetCmd Interfaces.
```vbscript
if (!_PreviousMode) SetMultiSheetMode(TRUE);
    void  CAADrwMultiSheetCmd::SetMultiSheetMode(boolean  iMode)
```

    {
```vbscript
if (!_PreviousMode) SetMultiSheetMode(TRUE);
void  CAADrwMultiSheetCmd::SetMultiSheetMode(boolean  iMode)
      if (!!__piSheetsOnDrawing)
```

      {
void  CAADrwMultiSheetCmd::SetMultiSheetMode(boolean  iMode)
if (!!__piSheetsOnDrawing)
        CATIDftMultiSheetMode *multiSheetManager=NULL;
```vbscript
        if (SUCCEEDED(__piSheetsOnDrawing->QueryInterface(IID_CATIDftMultiSheetMode, (void **) &multiSheetManager)))

```

        {
```vbscript
if (!!__piSheetsOnDrawing)
CATIDftMultiSheetMode *multiSheetManager=NULL;
if (SUCCEEDED(__piSheetsOnDrawing->QueryInterface(IID_CATIDftMultiSheetMode, (void **) &multiSheetManager)))
          multiSheetManager->SetMultiSheetMode(iMode);
          multiSheetManager->Release(#);
```

        }
      }
    }

---

[Top]
#### Building the State Chart and Creating the Appropriate Selection Agent

![](images/CAADrwMultiSheet4.jpg)
---

    // ----------------------------------------------------------------------------
    void CAADrwMultiSheetCmd::BuildGraph(#)
    {
      // Creation of the acquisition agent
void CAADrwMultiSheetCmd::BuildGraph(#)
      _pObjectAgent = new CATPathElementAgent("pObjectAgent");
      _pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation |
                                   CATDlgEngMultiAcquisition |
                                   CATDlgEngWithCSO);

      // We want to select text
_pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation |
CATDlgEngMultiAcquisition |
CATDlgEngWithCSO);
      _pObjectAgent ->SetElementType("CATIDrwText");
      AddCSOClient(_pObjectAgent);

      //  States definition
_pObjectAgent ->SetElementType("CATIDrwText");
AddCSOClient(_pObjectAgent);
      CATDialogState* state1 = GetInitialState("Sel reference text");
      CATDialogState* state2 = AddDialogState("Sel text to align");
      state1->AddDialogAgent(_pObjectAgent);
      state2->AddDialogAgent(_pObjectAgent);

      // Transition definition
CATDialogState* state2 = AddDialogState("Sel text to align");
state1->AddDialogAgent(_pObjectAgent);
state2->AddDialogAgent(_pObjectAgent);
      AddTransition(state1, state2, IsOutputSetCondition(_pObjectAgent),
```vbscript
                    Action((ActionMethod)&CAADrwMultiSheetCmd::CheckText, NULL, NULL));

```

      // Transition definition
```vbscript
AddTransition(state1, state2, IsOutputSetCondition(_pObjectAgent),
```vbscript
Action((ActionMethod)&CAADrwMultiSheetCmd::CheckText, NULL, NULL));
      AddTransition(state2, NULL, IsOutputSetCondition(_pObjectAgent),
                    Action((ActionMethod)&CAADrwMultiSheetCmd::MoveText, NULL, NULL));
```

```

    }

---

In this section we create a CATPathElementAgent and set the corresponding element type to CATIDrwText. So only Complex Texts could be selected.

[Top]
#### Selecting the Reference Text and Storing its Coordinates

    // ----------------------------------------------------------------------------
    boolean CAADrwMultiSheetCmd::CheckText(void *)
    {
      // We get the Selected set of objects
boolean CAADrwMultiSheetCmd::CheckText(void *)
      CATSO* pObjSO = _pObjectAgent->GetListOfValues(#);
      CATPathElement *pElemPath = NULL;

```vbscript
      if (NULL != pObjSO)

```

      {
        // There is a selection, we will scan it from the beginning
```vbscript
if (NULL != pObjSO)
        pObjSO->InitElementList(#);
        while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement(#)))
```

        {
          // Make sure the element is a text
pObjSO->InitElementList(#);
while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement(#)))
          CATIDrwText *piText = (CATIDrwText *)pElemPath->FindElement(IID_CATIDrwText);

```vbscript
          if (NULL != piText)

```

          {
CATIDrwText *piText = (CATIDrwText *)pElemPath->FindElement(IID_CATIDrwText);
if (NULL != piText)
            piText->GetPosition(_Xposition,_Yposition);
            piText->Release(#);

          }
        }
piText->GetPosition(_Xposition,_Yposition);
piText->Release(#);
      _pObjectAgent -> InitializeAcquisition(#);
      return TRUE;

      }
_pObjectAgent -> InitializeAcquisition(#);
return TRUE;
      return FALSE;

    }
    ...

---

The acquisition agent did put the selected text into the CSO. So we get the set of object and loop on it.

[Top]
#### Selecting the Text to Move and Storing the New Position

    // ----------------------------------------------------------------------------
    boolean CAADrwMultiSheetCmd::MoveText(void *)
    {
      // We get the Selected set of objects
boolean CAADrwMultiSheetCmd::MoveText(void *)
      CATSO* pObjSO = _pObjectAgent->GetListOfValues(#);
      CATPathElement *pElemPath = NULL;

```vbscript
      if (NULL != pObjSO)

```

      {
        // There is a selection, we will scan it from the beginning
CATPathElement *pElemPath = NULL;
if (NULL != pObjSO)
        pObjSO->InitElementList(#);
```vbscript
        while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement(#)))

```

        {
          // Make sure the element is a text
pObjSO->InitElementList(#);
while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement(#)))
          CATIDrwText *piText = (CATIDrwText *)pElemPath->FindElement(IID_CATIDrwText);

```vbscript
          if (NULL != piText)

```

          {
CATIDrwText *piText = (CATIDrwText *)pElemPath->FindElement(IID_CATIDrwText);
if (NULL != piText)
            piText->SetPosition(_Xposition,_Yposition);
            CATIModelEvents_var event(piText);
```vbscript
            if (event !=NULL_var)

```

            {
piText->SetPosition(_Xposition,_Yposition);
CATIModelEvents_var event(piText);
if (event !=NULL_var)
              CATModify info((CATBaseUnknown *)piText);
              event->Dispatch(info);

            }
```vbscript
if (event !=NULL_var)
CATModify info((CATBaseUnknown *)piText);
event->Dispatch(info);
            piText->Release(#);
```

          }
        }
event->Dispatch(info);
piText->Release(#);
        _pObjectAgent -> InitializeAcquisition(#);
        return TRUE;

      }
    ...

---

**Note** : When a text is modified and needs to regenerate its graphical representations, it just has to send CATModify event to warn all its.

[Top]
#### Restoring the Previous Multi Sheet Mode Value

    ...
    // Restore Active Multi sheet mode
      SetMultiSheetMode(_PreviousMode);
      return FALSE;
    }

---

**Note** : The Multi Sheet Mode Value has to be restore in the destructor.

[Top]

* * *
### In Short

This use case shows how to create a command working on several sheets: Retrieve current drawing, manage the multi sheet Mode and move a text.

[Top]

* * *
### References

[1] | [Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Implementing the Statechart Diagram](../CAADegUseCases/CAADegSampleGraph.md)
[Top]

* * *
### History

Version: **1** [Aug 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
