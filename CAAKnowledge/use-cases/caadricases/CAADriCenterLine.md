---
title: "Creating Center Lines in a CATDrawing Document"
category: "use case"
module: "CAADriUseCases"
tags: ["CAADrwCenterLineCmd", "CAADrwAddin", "CAADrwCenterLine", "CAAUseCaseCommands", "CATI2Dxxx", "CAADraftingInterfaces", "CATIA", "CATI2Dxx", "CATIDrwAnnotationFactory"]
source_file: "Doc/online/CAADriUseCases/CAADriCenterLine.htm"
converted: "2026-05-11T17:31:50.937531"
---
# Mechanical Design

| 
## Drafting

| 
### Creating Center Lines in a CATDrawing Document

_How to create annotations on interactive or generative geometry_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article discusses the CAADrwCenterLine use case. This use case explains how to create center lines on interactive or generative geometry in a CATDrawing document.

  * **What You Will Learn With This Use Case**
  * **About the Use of IDMxxx2D and CATI2Dxxx Interfaces**
  * **The CAADrwCenterLine Use Case**
    * What Does CAADrwCenterLine Do
    * How to Launch CAADrwCenterLine
    * Where to Find the CAADrwCenterLine Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

In this use case you will learn how to create annotations (center lines) on interactive and generative geometry.

[Top]
### About the Use of IDMxxx2D and CATI2Dxx Interfaces

There are two levels of interfaces:

  1. IDMxxx2D for consulting 
  2. CATI2Dxxx for editing.

Fig. 1: The 2D Interfaces UML Diagram ![](images/CAADrwCenterLine2.jpg)  
---  
  
The IDM interfaces are standard interfaces (Interfaces for Design and Modeling). IDMs may be re-implemented for user-defined objects. This is the way to integrate those elements in:

  * Sketcher picking assistant
  * Drafting annotations.

[Top]
### The CAADrwCenterLine Use Case

CAADrwCenterLine is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwCenterLine Do

This use case is made of a state command that waits for a selection and creates center lines on selected circles.

Fig. 2: Running the Command on Generative and Interactive Geometry ![](images/CAADrwCenterLine1.jpg)  
---  
  
This picture represents two views :

  1. The generative view of a CATPart with additional geometry (the two green circles)
  2. The same view after applying the command on it. Center lines were created on the selected circles.

[Top]
#### How to Launch CAADrwCenterLine

To launch CAADrwCenterLine, you will need to set up the build time environment, then compile CAADrwCenterLine and CAADrwAddin along with its prerequisites, set up the run time environment.[1].

  1. Launch CATIA session.
  2. Right-click on Drafting workshop to activate CAAUseCaseCommands toolbar.
  3. Launch the Center line use case command, and select geometry.

Top]
#### Where to Find the CAADrwCenterLine Code

The CAADrwCenterLine use case is made of two source files named CAADrwCenterLine.h and CAADrwCenterLine.cpp located in the CAADrwCenterLine.m module of the CAADraftingInterfaces.edu framework:

Windows | `InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCenterLine.m\`  
---|---  
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCenterLine.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are two steps in CAADrwCenterLine:

  1. Building the State Chart and Creating the Appropriate Selection Agent.
  2. Retrieving the Selection and Creating the Center Line

[Top]
#### Building the State Chart and Creating the Appropriate Selection Agent
    
    
    void CAADrwCenterLineCmd::BuildGraph()
    {  
       // Creation of the acquisition agent
       _ObjectAgent = new CATPathElementAgent("_ObjectAgent A");
       _ObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation | 
                                   CATDlgEngMultiAcquisition | 
                                   CATDlgEngWithCSO); 
    
       // We only want to get circles
       _ObjectAgent ->AddElementType("**IDMCircle2D** ");
       AddCSOClient(_ObjectAgent);
       
       //  States definition
       CATDialogState* pState1 = GetInitialState("Sel circle");
       pState1->AddDialogAgent(_ObjectAgent);
       
       // Transition definition
       AddTransition(pState1, NULL, IsOutputSetCondition(_ObjectAgent),
                     Action((ActionMethod)&CAADrwCenterLineCmd::CreateCtrLine, NULL, NULL));
    }  
  
---  
  
In this section we create a CATPathElementAgent and set the corresponding element type to IDMCircle. So only circles could be selected [2].

[Top]
#### Retrieving the Selection and Creating the Center Line
    
    
    boolean CAADrwCenterLineCmd::CreateCtrLine(void *iData)
    { 
       CATSO* pObjSO = _ObjectAgent->GetListOfValues(); 
       CATPathElement *pElemPath = NULL;
       
       if (NULL != pObjSO)  
       {
          // We will scan the CSO from the begining
          pObjSO->InitElementList();
          while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement())  )
          {
             
             // Make sure the element is a circle type
             // This circle can be interactive or a generative result (from part, model, ...)
             IDMCircle2D *piElementRef = (IDMCircle2D *)pElemPath->**FindElement(IID_IDMCircle2D)** ;
             
             if (NULL != piElementRef)
             {
                // Find the annotation factory (on the view)
                **CATIDrwAnnotationFactory** *piDrwFact = (CATIDrwAnnotationFactory *)pElemPath->FindElement(IID_CATIDrwAnnotationFactory);
                if (NULL != piDrwFact)
                {
                   // Let's create the center line
                   piDrwFact->**CreateDrwCenterLine**((CATBaseUnknown *)piElementRef);
                   piDrwFact->Release();
                }
                piElementRef->Release();
             }
          }
          
          _ObjectAgent -> InitializeAcquisition();
          return TRUE;
       }
       return FALSE;
    }  
  
---  
  
The acquisition agent did put the selected circles into the CSO. So we get the SO and loop on it. The selected circles can be generative ones or interactive ones. We get the annotation factory on the view and call the center line factory method giving the circle as argument.

[Top]

* * *
### In Short

This use case shows how to create a state command dealing with geometry selections. The _IDMxx2D_ interfaces identificators are used as filters and allows the selection of interactive and generative geometry. Using the _CATIDrwAnnotationFactory,_ interface, implemented by the view, it is possible to create annotations on these geometries.

[Top]

* * *
### References

[1] | [Building and Lauching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [Implementing the Statechart Diagram](../CAADegUseCases/CAADegSampleGraph.md)  
[Top]  
  
* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
