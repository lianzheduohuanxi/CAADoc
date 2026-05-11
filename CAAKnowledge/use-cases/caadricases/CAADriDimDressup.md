---
title: "Editing Dimension Dress-Up"
category: "use case"
module: "CAADriUseCases"
tags: ["CAADrwDimDressupCmduse", "CAAUseCaseCommands", "CATIDrwDimDimension", "CATIDrwDimFormat", "CAADrwAddin", "CATIDrwDimValueComponent_var", "CATIDrwDimText_var", "CATIDrwDimExtensionLine", "CATIDrwDimExtensionLine_var", "CATIA", "CATIDrwDimExtensionLineLinear", "CATIDrwDimDimensionLine_var", "CATIDrwDimDimensionLine", "CATIDrwDimText", "CATIDrwDimValue_var", "CATIDrwDimValue", "CAADrwDimDressupCmd", "CATIDrwDimExtensionLineLinear_var", "CATISpecObject_var", "CAADrwDimDressup"]
source_file: "Doc/online/CAADriUseCases/CAADriDimDressup.md"
converted: "2026-05-11T17:31:50.992103"
---
# Mechanical Design

| 
## Drafting

| 
### Editing Dimension Dress-Up

_How to use dimension interfaces_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article discusses the CAADrwDimDressupCmd.cpp use case. This use case explains how to edit a dimension dress-up.

  * **What You Will Learn With This Use Case**
  * **The Main Dimension Interfaces**
  * **The CAADrwDimDressupCmd Use Case**
    * What Does CAADrwDimDressupCmd Do
    * How to Launch CAADrwDimDressupCmd
    * Where to Find the CAADrwDimDressupCmd Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

In this use case you will learn how to modify the dimension dress-up parameters.

[Top]
### The Main Dimension Interfaces

Fig. 1: The Dimension Interfaces UML Diagram ![](images/CAADrwDimDressup2.jpg)  
---  
  
[Top]
### The CAADrwDimDressupCmd Use Case

CAADrwDimDressupCmd is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwDimDressupCmd Do

This sample waits for a dimension selection and modifies the dress-up as follows:

Fig. 2: The Dimension After and Before Dress-Up ![](images/CAADrwDimDressup1.jpg) 

**Texts**     Prefix = L=, main text upper = Up main text lower = Down **Dual value**     On, in inch, side by side **Tolerance**     main and dual, alpha-numerical **Dimension Line**     Thickness = 0.2, color = blue **Extension Line**     Funnel, thickness = 0.2, color = yellow, over-run = 4, blanking = 4 **Symbol**     Circled cross, thickness = 0.2 color = green **Font**     5mm, color = red **Frame :**     Rectangle   
---|---  
  
[Top]
#### How to Launch CAADrwDimDressupCmd

To launch CAADrwDimDressupCmd, you will need to set up the build time environment, then compile CAADrwDimDressupCmd and CAADrwAddin along with its prerequisites, set up the run time environment, and then include the command in a workbench [1].

  1. Launch CATIA session.
  2. Right-click on Drafting workshop to activate CAAUseCaseCommands toolbar.
  3. Launch the DimDressup use case command, and select the annotation.

[Top]
#### Where to Find the CAADrwDimDressupCmd Code

The CAADrwDimDressupCmduse case is made of two source files named CAADrwDimDressupCmd.h and CAADrwDimDressupCmd.cpp located in the CAADrwDimDressup.m module of the CAADraftingInterfaces.edu framework:

Windows | `InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwDimDressup.m\`  
---|---  
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwDimDressup.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are 11 steps in CAADrwDimDressupCmd:

  1. Building the State Chart and Creating the Appropriate Selection Agent
  2. Retrieving the Selection
  3. Editing the Text
  4. Setting the Dual Value
  5. Adding the Tolerance
  6. Editing the Main Value
  7. Editing the Dual Value
  8. Editing the Dimension Line
  9. Editing the Extension Line
  10. Setting the Funnel
  11. Building the Dimension and Exit

[Top]
#### Building the State Chart and Creating the Appropriate Selection Agent
    
    
    void CAADrwDimDressupCmd::BuildGraph()
    {  
       // Creation of the acquisition agent
       _pObjectAgent = new CATPathElementAgent("_ObjectAgent A");
       _pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation | 
                                    CATDlgEngMultiAcquisition | 
                                    CATDlgEngWithCSO); 
    
       // We want to select dimensions
       _pObjectAgent ->AddElementType("**CATIDrwDimDimension** ");
       AddCSOClient(_pObjectAgent);
       
       //  States definition
       CATDialogState* state1 = GetInitialState("Sel dimension");
       state1->AddDialogAgent(_pObjectAgent);
       
       // Transition definition
       AddTransition(state1, NULL, IsOutputSetCondition(_pObjectAgent),
                     Action((ActionMethod)&CAADrwDimDressupCmd::DressUp, NULL, NULL));
    }  
  
---  
  
In this section we create a _CATPathElementAgent_ and set the corresponding element type to _CATIDrwDimDimension_. So only dimensions could be selected.

[Top]
#### Retrieving the Selection
    
    
    boolean CAADrwDimDressupCmd::DressUp(void *)
    { 
       // We get the Selected set of objects
       CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
       CATPathElement *pElemPath = NULL;
       
       if (pObjSO)  
       {
    
          // There is a selection, we will scan it from the beginning
          pObjSO->InitElementList();
          while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement()))
          {
             // Make sure the element is dimension
             **CATIDrwDimDimension** *piDim = (CATIDrwDimDimension *)pElemPath->FindElement(IID_CATIDrwDimDimension);
             
             if (NULL != piDim)
             {
    
    
    ...  
  
---  
  
The acquisition agent did put the selected dimension into the CSO. So we get the set of object and loop on it.

[Top]
#### Editing the Text
    
    
    ...
                // Text properties
                **CATIDrwTextProperties** _var spTextProperties = piDim;
                spTextProperties->**SetFontSize**(5);
                spTextProperties->**SetColor**(255, 0, 0, 255);
                spTextProperties->**SetFrameType**(CATDrwRectangle);
    
    
    ...  
  
---  
  
The dimension implements the _CATIDrwTextProperties_ interface. Using this interface, we modify the font size, color and the text frame format.

[Top]
#### Setting the Dual Value
    
    
    ...            
                // Dual value
                piDim->**ShowDualValue**();
    ...  
  
---  
  
The dual value is set using the _CATIDrwDimDimension_ interface.

[Top]
#### Adding the Tolerance
    
    
    ...
                // Tolerance
                piDim->**AddTolerance**("h7","g6",1,1);
    ...  
  
---  
  
The tolerance is set using the _CATIDrwDimDimension_ interface.

[Top]
#### Editing the Main Value
    
    
    ...
                // We get the dim value
                **CATIDrwDimValue** _var spDimValue = piDim->GetValue();
                spDimValue->**SetDualValueDisplay**(CATDrwDimDualSideBySide);
                
                // The main value
                **CATIDrwDimValueComponent** _var spMainValue = spDimValue->**GetFaceComponent**();
                **CATIDrwDimText** _var spMainText = spMainValue->**GetText**();
                spMainText->**SetPSText**("L=", "");
                spMainText->**SetBAULText**("", "", "Up", "Down");
    ...  
  
---  
  
The _CATGraphicAttributeSet_ will be used to convert RGBA data from a 4-integer representation to a 1-integer representation. First we get the dimension value. This feature manages the main and dual value representations. Then we get the main value from the dimension value. Using `SetPSText` we set:

  * The prefix
  * The suffix.

Using `SetBAULText` we set:

  * The text before
  * The text after
  * The text upper
  * The text lower.

[Top]
#### Editing the Dual Value
    
    
    ...
                // The dual value
                CATIDrwDimValueComponent_var spDualValue = spDimValue->**GetDualComponent**();
                **CATIDrwDimFormat** _var spDualFormat = spDualValue->**GetFormat**();
                spDualFormat->**SetUnit**(CATDrwDimUnitINCH);
    ...  
  
---  
  
We get the dual value from the dimension value and modify the format putting the unit to "INCH".

[Top]
#### Editing the Dimension Line
    
    
    ...
                // Useful to convert RGBA(4-int)<->RGBA(1-int)
                **CATGraphicAttributeSet** attrSet;            
    
    
                // DimensionLine
                **CATIDrwDimDimensionLine** _var spDimLine = piDim->**GetDimensionLine**();
                attrSet.SetColorRGBA(255,0,0,255);
                spDimLine->**SetGraphicParameters**(attrSet.GetColorRGBA(), 0.2);
                spDimLine->**SetSymbol**(CATDrwDimSymbCircledCross,CATDrwDimSymbCircledCross);
                attrSet.**SetColorRGBA**(0,255,0,255);
                spDimLine->**SetSymbolsGraphicParameters**(attrSet.GetColorRGBA(), 0.1, 
                                                       attrSet.GetColorRGBA(), 0.1);
    ...  
  
---  
  
We get the dimension line interface from the dimension. Using the _CATIDrwDimDimensionLine_ interface we modify :

  * The color and thickness (using the _CATGraphicAttributeSet_)
  * Both symbols
  * The symbol graphic parameters.

[Top]
#### Editing the Extension Line
    
    
    ...
                // ExtentionLine
                **CATIDrwDimExtensionLine** _var spExtLine = piDim->**GetExtensionLine**();
                attrSet.SetColorRGBA(0,255,255,255);
                spExtLine->**SetGraphicParameters**(attrSet.GetColorRGBA(), 0.2);
                spExtLine->**SetGap**(4);
                spExtLine->**SetOverRun**(4);
    ...  
  
---  
  
We get the extension line interface from the dimension.  
Using the _CATIDrwDimExtensionLine_ interface we modify :

  * The color and thickness (using the _CATGraphicAttributeSet_)
  * The gap and over-run.

[Top]
#### Setting the Funnel
    
    
    ...
                // Funnel
                **CATIDrwDimExtensionLineLinear** _var spLinearExtLine = spExtLine;
                spLinearExtLine->**SetFunnel**(1);
    ...  
  
---  
  
This is a distance dimension. So the extension line implements _CATIDrwDimExtensionLine_. `CATIDrwDimExtensionLineLinear::SetFunnel(1)` sets the funnel at true.

[Top]
#### Building the Dimension and Exit
    
    
    ...
                // Let's update the dimension after spec modifications
                **CATISpecObject** _var spDimSpec = piDim;
                spDimSpec->**Update**();
    
                piDim->Release();
             }
          }
          
          _pObjectAgent -> InitializeAcquisition();
          return TRUE;
       }
       return FALSE;
    }  
  
---  
  
We have to update the dimension to take into account the dress-up modifications.

[Top]

* * *
### In Short

This use case shows how to edit a dimension dress-up. The main dimension interfaces are _CATIDrwDimDimension, CATIDrwTextProperties, CATIDrwDimValue, CATIDrwDimValueComponent, CATIDrwDimText, CATIDrwDimFormat, CATIDrwDimDimensionLine, CATIDrwDimExtensionLine, CATIDrwDimExtensionLineLinear_ and _CATISpecObject_.

[Top]

* * *
### References

[1] | [Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)  
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
