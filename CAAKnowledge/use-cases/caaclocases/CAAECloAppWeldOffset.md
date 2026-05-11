---
title: "Weld Offset Calculation"
category: "use case"
module: "CAACloUseCases"
tags: ["CAACommonLayoutItf", "CAAECloAppWeldOffset", "CAACloSetup", "CATICloAppWeldOffset"]
source_file: "Doc/online/CAACloUseCases/CAAECloAppWeldOffset.htm"
converted: "2026-05-11T17:33:49.540616"
---

Equipment & Systems |  Systems Layout |  Weld Offset Calculation _How to customize weld offset calculation_  
---|---|---  
Use Case  
  
* * *

Abstract This article discusses the CAAECloAppWeldOffset use case.
    * **What You Will Learn With This Use Case**
    * **The CAAECloAppWeldOffset Use Case**
      * What Does CAAECloAppWeldOffset Do
      * How to use CAAECloAppWeldOffset
      * Where to Find the CAAECloAppWeldOffset Code
    * **Step-by-Step**
    * **In Short**  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to show you how to customize the weld offset calculation using the interface CATICloAppWeldOffset. This interface is used by the welding design rule which is used to determine the type of weld that should be placed between two parts. For Piping Design, the rule also calculates the weld offset, which is necessary when placing a branch. An offset is the distance between the center line of the main pipe and the ends of the branch being placed. The offset value is used during parts placement to position the weld correctly with respect to the main pipe and branch. The weld gap that is defined on the weld is used to calculate the offset value. You can provide calculation of the weld offset by implementing the CAA Interface CATICloAppWeldOffset. If no implementation is found for CATICloAppWeldOffset, the default calculation is used. The default calculation is shown in the sample located in CAACommonLayoutItf.edu/CAACloSetup.m/src/CAAECloAppWeldOffset.cpp. [Top] The CAAECloAppWeldOffset Use Case CAAECloAppWeldOffset is a use case of the CAACommonLayoutItf.edu framework that illustrates the capabilities to provide custom code to calculate the weld offset used by part placement. [Top] What Does CAAECloAppWeldOffset Do The goal of CAAECloAppWeldOffset is to show you how to use the interfaces from CATCommonLayoutInterfaces framework to calculate the weld offset. [Top] How to Use CAAECloAppWeldOffset To use CAAECloAppWeldOffset , you will need to set up the build time environment, then compile CAAECloAppWeldOffset along with its prerequisites, set up the run time environment, and then place a part that require welding. There are five six steps to use this sample:
    1. Customize your implementation in CAAECloAppWeldOffset.cpp
    2. Remove #CAA# before CATPiping  CATICloAppWeldOffset in CNext/code/dictionary/CAACommonLayoutItf.dico to enable the implementation for CATICloAppWeldOffset.
    3. Compile the source code. See the compiler documentation for more information.
    4. Copy the shared library CAACloSetup.dll or libCAACloSetup depending on the operating system to your run time bin directory.
    5. Copy the CAACommonLayoutItf.edu.dico to your run time dictionary directory.
    6. Do the following to test your implementation: 
       * Start CNext and select Piping Design workbench.
       * Route a run and place an Elbow or value.
       * place a bendable next to the created part.
       * CAAECloAppWeldOffset should be invoked when a weld is placed.
[Top] Where to Find the CAAECloAppWeldOffset Code CAAECloAppWeldOffset code is located in the CAACloSetup.m use case module of the CAACommonLayoutItf.edu framework: Windows | `InstallRootDirectory\CAACommonLayoutItf.edu\CAACloSetup.m\src\CAAECloAppWeldOffset.cpp`  
---|---  
Unix | `InstallRootDirectory/CAACommonLayoutItf.edu/CAACloSetup.m/src/CAAECloAppWeldOffset.cpp`  
The following contains the dictionary file that references the implementation: Windows | `InstallRootDirectory\CAACommonLayoutItf.edu\CNext\code\dictionary\CAACommonLayoutItf.edu.dico`  
---|---  
Unix | `InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico`  
where `InstallRootDirectory` is the root directory of your CAA V5 installation. [Top] Step-by-Step
    1. Prolog
    2. Calculating the weld offset
[Top] Prolog The user will have to provide Implementation for CATICloAppWeldOffset. The interface is called directly by the commands that create the Piping object. [Top] Calculating the weld offset The CAAECloAppWeldOffset is a sample implementation for CATICloAppWeldOffset. The following code shows the default calculation:
    
    if ( offsetType == WeldLinear )
      {
        *odWeldOffset = idWeldGap;
      }
      else if ( offsetType == WeldCalculated )
      {
        *odWeldOffset = idWeldGap;
      }
      else if ( offsetType == WeldStubOn )
      {
        if ( idRunOutsideRadius > idBranchInsideRadius )
          *odWeldOffset = sqrt( idRunOutsideRadius*idRunOutsideRadius - 
                   idBranchInsideRadius*idBranchInsideRadius ) + idWeldGap;
        else 
          RC = E_FAIL;
      }
      else if ( offsetType == WeldStubIn )
      {
        double x = idBranchOutsideRadius + idWeldGap;
        if ( idRunInsideRadius > x )
          *odWeldOffset = sqrt ( idRunInsideRadius*idRunInsideRadius - x*x );
        else
          RC = E_FAIL;
      }
      else if ( offsetType == WeldSetOn )
      {
        *odWeldOffset = idRunOutsideRadius + idWeldGap;
      }
    
       
  
---  
[Top] [Top]

* * *

In Short This use case has demonstrated how to the interfaces from CATCommonLayoutInterfaces framework to calculate the weld offset. [Top]

* * *

References |   
---|---  
  
* * *

History Version: **1** [May 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
